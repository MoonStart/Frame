// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_TxOchAutomaticAction.h"
#include "../CFG_Opt.h"
#include "../CFG_OptAutomatic.h"
#include "../CFG_TxOchAutomatic.h"
#include "../CFG_AppIf.h"

#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_OchStatus.h>
#include <Monitoring/MON_OptDefects.h>
#include <Monitoring/MON_OtuStatus.h>
#include <Monitoring/MON_OchPower.h>
#include <Monitoring/MON_OchConfig.h>
#include <Monitoring/MON_SubNodeParameters.h>
#include <Blackboard/FC_BbAction.h>
#include <BaseClass/FC_Stream.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <Monitoring/MON_OchPower.h>
#include <TsPii/TSPII_PilotToneIf.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <T6100_Dispatcher.h>
#include <CsPii/CSPII_CardIF.h>
#include <T6100_CardIf.h>
#include <T6100_MainAppIf.h>
#include <time.h>

#ifdef __TARGET__
extern "C" uint32 ppcTBLrd();
#endif

const FC_Milliseconds MON_FAST_UPDATE_RATE = 500;
const FC_Milliseconds MON_SLOW_UPDATE_RATE = 20000;
const FC_Milliseconds MON_FAST_TO_SLOW_PERIOD = 10000;

const float MON_TARGET_MOD_RATIO = 1.00f; // 4% is adapted in PII
const float MON_AUTO_ID_MAX_RAND_DELAY = 30000; //ms

const CT_TEL_mBm MON_TXOCH_LOSS_OF_INPUT_POWER_THRESHOLD = -2800; //(mbm)

CFG_TxOchAutomaticAction::CFG_TxOchAutomaticAction(CFG_AppIf& theAppIf,
                                                   CFG_AppIf* theCfgOptAppIf,
                                                   MON_AppIf* theMonAppIf,
                                                   MON_OchStatusRegion* theAcStatusRegion,
                                                   TSPII_PilotToneRegion* theTspiiPilotToneRegion,
                                                   TSPII_OpticalRegion* theTspiiOpticalRegion,
                                                   MON_OptDefectsRegion& theOptDefectsRegion,
                                                   CT_CardType theCardType,
                                                   MON_AppIf* theMonOchLineAppIf):
    CFG_HwRefreshAction(theAppIf),
    myCfgOptAppIf(theCfgOptAppIf),
    myOtuStatusRegion(NULL),
    myOchStatusRegion(NULL),
    myOptDefectsRegion(theOptDefectsRegion),
    myTspiiPilotToneRegion(theTspiiPilotToneRegion),
    myTspiiOpticalRegion(theTspiiOpticalRegion),
    myDcStatusRegion("MON_DC",1),
    myAcStatusRegion(theAcStatusRegion),
    myRefreshRequestTime(0),
    myUpdateRate(MON_SLOW_UPDATE_RATE),
    myCorrectionFilter(false),
    myTimedProcess(NULL),
    myNextUpdateTime(0),
    myLastIdChangeExpirationTimer(0),
    myLastIdChangeExpirationTimerStopped(true),
    myRetrieveTxIdFromPII(true),
    myPtMaxTxAmp(0),
    myPtMinTxAmp(0),
    myTraceEnabled(false),
    myMonOchLineAppIf(theMonOchLineAppIf)
{
    FC_THROW_ERROR_IF ((myCfgOptAppIf==NULL) || (theMonAppIf==NULL) || (myMonOchLineAppIf==NULL),
                       FC_InvalidArgumentError,
                       "Invalid appif provided to action");

    GetBbAction()->AddInputRegion(theMonAppIf->GetStatusRegion());
    GetBbAction()->AddInputRegion(&myOptDefectsRegion);
    GetBbAction()->AddInputRegion(myCfgOptAppIf->GetCfgRegion());
    GetBbAction()->AddInputRegion(myMonOchLineAppIf->GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion(),false);

    GetBbAction()->AddInputRegion(&myDcStatusRegion, false);
    if(myAcStatusRegion) GetBbAction()->AddInputRegion(myAcStatusRegion, false);

    myTimedProcess = new FC_TimedProcess(*GetBbAction(), gTimerDispatcher, MON_FAST_UPDATE_RATE);
    myTimedProcess->WakeUp();


    // Find the type of status region we have to deal with.
    // We can support either OTU or OCH.
    MON_Region* aStatusRegion = theMonAppIf->GetStatusRegion();
    MON_Object* aOtuStatus = dynamic_cast<MON_OtuStatus*>(&aStatusRegion->ElementAt(0));
    if (aOtuStatus)
        myOtuStatusRegion = static_cast<MON_OtuStatusRegion*>(aStatusRegion);
    MON_Object* aOchStatus = dynamic_cast<MON_OchStatus*>(&aStatusRegion->ElementAt(0));
    if (aOchStatus)
        myOchStatusRegion = static_cast<MON_OchStatusRegion*>(aStatusRegion);

    //Seed the randomizer
#ifdef __TARGET__
    srand(ppcTBLrd());
#else
    time_t aTime = 0;
    srand((uint32)time(&aTime));
#endif

    //fill in the min/max pt amplitude values
    myPtMaxTxAmp = (*myTspiiOpticalRegion)[0].GetMaxTxPTAmplitude();
    myPtMinTxAmp = (*myTspiiOpticalRegion)[0].GetMinTxPTAmplitude();

    myAmpliRatioNeeded = (*myTspiiOpticalRegion)[0].GetAmpliRatioNeeded();
    myPtMaxTxAmpRatio  = (*myTspiiOpticalRegion)[0].GetMaxTxPTAmpliRatio();
    myPtMinTxAmpRatio  = (*myTspiiOpticalRegion)[0].GetMinTxPTAmpliRatio();
    //fc_cout << " / myPtMinTxAmpRatio = " << myPtMinTxAmpRatio;
    //fc_cout << " / myPtMaxTxAmpRatio = " << myPtMaxTxAmpRatio << endl;     
    myRestartType = T6100_MainAppIf::Instance().GetRestartType();
}

CFG_TxOchAutomaticAction::~CFG_TxOchAutomaticAction()
{
    if (myOtuStatusRegion) GetBbAction()->RemoveInputRegion(myOtuStatusRegion);
    if (myOchStatusRegion) GetBbAction()->RemoveInputRegion(myOchStatusRegion);

    GetBbAction()->RemoveInputRegion(&myOptDefectsRegion);
    GetBbAction()->RemoveInputRegion(myCfgOptAppIf->GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());

    GetBbAction()->RemoveInputRegion(&myDcStatusRegion);
    if(myAcStatusRegion) GetBbAction()->RemoveInputRegion(myAcStatusRegion);
    delete myTimedProcess;
}

FC_Object* CFG_TxOchAutomaticAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    if(MON_SubNodeParameters::GetInstance().IsSubNodeParametersReady())
        UpdateObject(theRunReason);

    return NULL;
}



MON_RelativeTraceId CFG_TxOchAutomaticAction::GetActualRelativeTraceId(const CT_Wavelength& theChannelId,
                                                                       bool theG709Enable) const
{

    // if we have a LOS of signal, return UNKNOWN immediatly
    MON_OptDefects& aDefects   = static_cast<MON_OptDefects&>(myOptDefectsRegion[0]);
    bool aLosState = false;
    uint32 aCount=0;
    aDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &aCount, &aLosState);
    if (aLosState)
        return MON_ID_UNKNOWN;

    CFG_Opt&          aOptConfig                = static_cast<CFG_Opt&>((*myCfgOptAppIf->GetCfgRegion())[0]);

    // if G.709 digital wrapper is enabled, and not in a line terminal loopback, use OTU trace to get trace ID
    if (theG709Enable && !aOptConfig.GetTerminalLoopBackEnable())
    {
        FC_THROW_ERROR_IF(myOtuStatusRegion==NULL, FC_RuntimeError, "No OTU context available to read current received trace ID");
        MON_OtuStatus& aStatus = (*myOtuStatusRegion)[0];
        CT_TEL_PilotToneID aTraceId = 0;
        if (aStatus.IsValidated())
            aTraceId = aStatus.GetTraceMessage().GetTraceID();

        // check that an good ID is detected
        if (aTraceId!=0)
        {
            // check that channel ID matches
            if (MON_OchPower::GetChannelId(aTraceId) == theChannelId)
                return MON_OchPower::GetRelativeTraceId(aTraceId);
            else
                return MON_ID_UNKNOWN;
        }
        else
            return MON_ID_UNKNOWN;
    }
    // use pilot tone to get ID
    else if (myOchStatusRegion)
    {
        MON_OchStatus& aStatus     = (*myOchStatusRegion)[0];
        const MON_OchPower& aPower = aStatus.GetMostPowerfullId();
        if ((aPower.GetSnr() > TEL_DEFAULT_MINIMUM_SN_RATIO) &&
            (aPower.GetAmplitude() > MON_TXOCH_LOSS_OF_INPUT_POWER_THRESHOLD))
            return aPower.GetTraceId();
        else
            return MON_ID_UNKNOWN;
    }
    // we have no means of observing receive trace
    else
    {
        return MON_ID_UNKNOWN;
    }
}

void CFG_TxOchAutomaticAction::UpdateObject(unsigned theRunReason)
{
    static const char myFunctionName[] = "***** CFG_TxOchAutomaticAction: ";
    CFG_TxOchAutomatic& aTxOchAutomaticConfig   = static_cast<CFG_TxOchAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    CFG_Opt&          aOptConfig                = static_cast<CFG_Opt&>((*myCfgOptAppIf->GetCfgRegion())[0]);
    MON_OchConfig&    aOchMonConfig             = static_cast<MON_OchConfig&>((*myMonOchLineAppIf->GetConfigRegion())[0]);

    // cannot control anything if wavelength is unspecified
    if ( (aOptConfig.GetWavelength()           == UNKNOWN_WAVELENGHT) ||
         (aOchMonConfig.GetExpectedChannelId() == UNKNOWN_WAVELENGHT) )
        return;

    // Get current tick timer count
    FC_Milliseconds aCurrentTime = PII_TickTimer::readTimer();

    // Set default random delay
    FC_Milliseconds aRandomDelay = (FC_Milliseconds)MON_AUTO_ID_MAX_RAND_DELAY;

    // Retrieve the currently transmitted ID
    MON_RelativeTraceId aTxId = MON_ID_UNKNOWN;

    if(myRetrieveTxIdFromPII)
    {
        CT_TEL_Hz aTxPilotToneFreq = (*myTspiiOpticalRegion)[0].GetTxPilotTone();
        if(aTxPilotToneFreq != 0)
        {
            CT_TEL_PilotToneID aTxPtId = CFG_PilotToneAssignment::GetInstance().PT_FREQ_TO_OTID(aTxPilotToneFreq);
            aTxId = MON_OchPower::GetRelativeTraceId(aTxPtId);
            // at this point we need to figure out if the card just did a warm start
            // if it was warm start, then retrieve values from TSPII (from the hardware)
            // in order to seed the automatic action variables. This should minimize
            // changes to configuration settings and most important the modulation amplitude.
            if ( myRestartType == WARM_RST )
            {
                (void) aTxOchAutomaticConfig.SetToneAmplitude((*myTspiiOpticalRegion)[0].GetTxPTAmplitude());
                (void) aTxOchAutomaticConfig.SetToneAmpliRatio((*myTspiiOpticalRegion)[0].GetTxPTAmpliRatio());
                (void) aTxOchAutomaticConfig.SetTraceId(aTxPtId);
                fc_cout << myFunctionName << "aTxPtId = " << int(aTxPtId) << endl;
                fc_cout << myFunctionName << "aTxPilotToneFreq = " << int(aTxPilotToneFreq) << endl;
            }
            else
            {
                fc_cout << myFunctionName << "RestartCause is NOT warm start" << endl;
            }
        }
        else
        {
            fc_cout << myFunctionName << "Pilot Tone frequency is unknown" << endl;
        }
        myRetrieveTxIdFromPII = false;
    }
    else
    {
        aTxId = MON_OchPower::GetRelativeTraceId(aTxOchAutomaticConfig.GetTraceId());
    }

    MON_RelativeTraceId aNewTxId = aTxId;

    if (!aOptConfig.GetDebugTraceEnable())
    {
        // Get actual received trace ID
        MON_RelativeTraceId aCurrentRxId = GetActualRelativeTraceId(aOptConfig.GetWavelength(),
                                                                    aOptConfig.GetDigitalWrapperEnable()==CT_OTN_MODE_G709);

        // If we were transmitting UNKNOWN or DEBUG,
        // force a conflict so that we change to correct one immediatly
        bool aForcedChange = ((aTxId == MON_ID_DEBUG) || (aTxId == MON_ID_UNKNOWN));
        // Hold the negotiation if we are not close to the target value on transmit. (NOT applicable for card that does not control amplitude)
        bool aHoldChange = (myTspiiPilotToneRegion && (myUpdateRate == MON_FAST_UPDATE_RATE)) && !aForcedChange;

        // Change TX ID if we are receiving the same as we are transmitting
        if (!aHoldChange && (((aCurrentRxId == aTxId) && aOptConfig.GetIdAutoNegEnable()) || aForcedChange))
        {
            if(aForcedChange)
            {
                // Change the TX ID since we do not transmit a valid one
                switch (aCurrentRxId)
                {
                case MON_ID_FIRST:
                    aNewTxId = MON_ID_SECOND;
                    break;
                case MON_ID_SECOND:
                    aNewTxId = MON_ID_FIRST;
                    break;
                case MON_ID_UNKNOWN:
                case MON_ID_DEBUG:
                    aNewTxId = MON_ID_FIRST; // let's start with something!
                    break;
                default:
                    FC_THROW_ERROR(FC_RuntimeError, "Unexpected relative rate ID");
                }
            }
            else if(myLastIdChangeExpirationTimerStopped)
            {
                //Start random timer to hold on the change of the ID
                aRandomDelay = (FC_Milliseconds)(MON_AUTO_ID_MAX_RAND_DELAY * rand()/RAND_MAX);
                myLastIdChangeExpirationTimer.SetPeriod(aRandomDelay);
                myLastIdChangeExpirationTimer.Start();
                myLastIdChangeExpirationTimerStopped = false;
            }
            else if (myLastIdChangeExpirationTimer.IsExpired())
            {
                // Change the TX ID if the random timer is expired
                switch (aCurrentRxId)
                {
                case MON_ID_FIRST:
                    aNewTxId = MON_ID_SECOND;
                    break;
                case MON_ID_SECOND:
                    aNewTxId = MON_ID_FIRST;
                    break;
                case MON_ID_UNKNOWN:
                case MON_ID_DEBUG:
                    // For other cases, leave as is unless not set to good value
                    break;
                default:
                    FC_THROW_ERROR(FC_RuntimeError, "Unexpected relative rate ID");
                }

                myLastIdChangeExpirationTimerStopped = true;
            }
        }
        else
        {
            //Stop the random timer since we do not need to change the ID.
            myLastIdChangeExpirationTimerStopped = true;
        }
    }
    else
    {
        // Force ID to debug trace
        aNewTxId = MON_ID_DEBUG;
    }
    // convert relative ID to absolute ID according to wavelengh to transmit
    CT_TEL_PilotToneID aTraceId = MON_OchPower::GetTraceId(aOptConfig.GetWavelength(), aNewTxId);

    // store new ID
    bool hasTraceIdChanged = aTxOchAutomaticConfig.SetTraceId(aTraceId);

    // if trace ID had changed, make sure we get in FAST update mode
    if (hasTraceIdChanged)
    {
        myUpdateRate = MON_FAST_UPDATE_RATE;
        myNextUpdateTime = aCurrentTime;

        //Set the amplitude to 0 to avoid interference when changing ID
        aTxOchAutomaticConfig.SetToneAmplitude(0);
        aTxOchAutomaticConfig.SetToneAmpliRatio(0);
    }

    // check that we have a valid pilot tone pii
    bool hasChanged = hasTraceIdChanged;
    if (myTspiiPilotToneRegion)
    {

        // check if were are due for a correction
        // and trigger a refresh of measurements
        if (((int32)(aCurrentTime - myNextUpdateTime) >= 0 ) &&
            !myDcPilotToneAction.IsInProgress() &&
            ((int32)(myRefreshRequestTime - myNextUpdateTime) < 0))
        {
            myRefreshRequestTime = aCurrentTime;
            myDcStatusRegion[0].Invalidate();
            // also make sure that we do not re-use this AC power since amplitude change makes it obsolete
            (*myAcStatusRegion)[0].Invalidate();
        }

        // check if measurements were successfull
        bool aMeasurementFailure = false;
        if ((!myDcPilotToneAction.IsInProgress() && myDcPilotToneAction.GetState()==MON_PilotToneAction::FAILED))
             aMeasurementFailure = true;

        //update DC power
        UpdatePowerStatus(myDcStatusRegion,
                          MON_PT_FASTMODE_NUM_SAMPLE,
                          myDcPilotToneAction,
                          MON_ID_FIRST);

        // compute modulation index and new amplitude correction
        // only if value are not expired
        // and if we are due to correct
        bool aControlFailure=false;

        if (myAcStatusRegion &&
            myAcStatusRegion->IsValid() &&
            (*myAcStatusRegion)[0].IsValidated() &&
            myDcStatusRegion[0].IsValidated() &&
            ((int32)(aCurrentTime - myNextUpdateTime) > 0 ))
        {
            //Copy AC power for modulation ratio computation
            aTxOchAutomaticConfig.SetAcPower((*myAcStatusRegion)[0].GetTraceIdPower(MON_OchPower::GetRelativeTraceId(aTraceId)));

            float aRatio = 0;
            if (myAmpliRatioNeeded) 
            {  
                aTxOchAutomaticConfig.SetTargetPowerBoost((*myTspiiOpticalRegion)[0].GetTargetPowerBoost());
                aTxOchAutomaticConfig.SetPowerTolerance((*myTspiiOpticalRegion)[0].GetPowerTolerance());
                bool isValidRead = aTxOchAutomaticConfig.IsAcPowerInRange();

                aTxOchAutomaticConfig.SetNewModulationRatio();
                aRatio = aTxOchAutomaticConfig.GetNewModulationRatio();  

                // New AmpliRatio (amplitude percentage) needed for new DQPSK devices
                float anAmpliRatio = myPtMinTxAmpRatio;
                if (aRatio != 0.0 )
                {
                    anAmpliRatio = aTxOchAutomaticConfig.GetToneAmpliRatio() *  MON_TARGET_MOD_RATIO/aRatio;
                }
                else
                {
                    anAmpliRatio = myPtMaxTxAmpRatio;
                }

                /* add damping to correction */
                if (myCorrectionFilter)
                {
                    anAmpliRatio = 0.9 * aTxOchAutomaticConfig.GetToneAmpliRatio() + 0.1 * anAmpliRatio;
                }

                if ( anAmpliRatio >= myPtMaxTxAmpRatio)
                {
                    anAmpliRatio = myPtMaxTxAmpRatio;
                }
                else if ( anAmpliRatio < myPtMinTxAmpRatio ) 
                {
                    anAmpliRatio = myPtMinTxAmpRatio;
                }

                // Set the transmit Amplitude if it needs any adjustment
                hasChanged |= aTxOchAutomaticConfig.SetToneAmpliRatio(anAmpliRatio);

            }

            // else part uses the regular (older) code that calculates the amplitude
            else  // if (myAmpliRatioNeeded)
            {
                aRatio = aTxOchAutomaticConfig.GetModulationRatio(); 

                //-------------------------------------------------------
                // predict the transmit amplitude as following
                //-------------------------------------------------------
         
                float anAmplitude;
                if (aRatio != 0.0 ) 
                    anAmplitude = aTxOchAutomaticConfig.GetToneAmplitude() *  MON_TARGET_MOD_RATIO/aRatio;
                else
                    anAmplitude = myPtMaxTxAmp;

                /* add damping to correction */
                if (myCorrectionFilter)
                    anAmplitude = 0.9 * aTxOchAutomaticConfig.GetToneAmplitude() + 0.1 * anAmplitude;

                if ( anAmplitude >= myPtMaxTxAmp) 
                    anAmplitude = myPtMaxTxAmp;
                else if ( anAmplitude < myPtMinTxAmp ) 
                    anAmplitude = myPtMinTxAmp;

                // Set the transmit Amplitude if it needs any adjustment
                hasChanged |= aTxOchAutomaticConfig.SetToneAmplitude(anAmplitude);
            }  // if (myAmpliRatioNeeded)


            //------------------------------------------------------
            // Estimate when should we do the next correction
            //------------------------------------------------------
            /* calculate how far we are from target */
            float error = 0;
            if (aRatio == 0)
                error = 0; /* maximum error */
            else if (MON_TARGET_MOD_RATIO < aRatio)
                error = MON_TARGET_MOD_RATIO / aRatio;
            else if (aRatio < MON_TARGET_MOD_RATIO)
                error = aRatio / MON_TARGET_MOD_RATIO;
            else
                error = 1; //(100% = right on target)

            /* we expect error not to exceed 100% (target) */
            FC_THROW_ERROR_IF(error >1, FC_RuntimeError, "Unexpected error on ratio");

            /* When we are near from target, enable correction filter and slow down correction speed*/
            FC_Milliseconds aLastDelayChange = 0;
            if (error > 0.9)
            {
                myCorrectionFilter = true;
                if (myUpdateRate == MON_FAST_UPDATE_RATE)
                {
                    aLastDelayChange = aCurrentTime;
                    myUpdateRate = MON_SLOW_UPDATE_RATE;
                }
            }
            /* if we are away from target, increase correction speed. */
            /* if we don't reach target after a while, disable filter to reach it faster. */
            else
            {
                if (myUpdateRate == MON_SLOW_UPDATE_RATE)
                {
                    aLastDelayChange = aCurrentTime;
                    myUpdateRate = MON_FAST_UPDATE_RATE;
                }
                if ( aLastDelayChange + MON_FAST_TO_SLOW_PERIOD < aCurrentTime)
                    myCorrectionFilter = false;
            }

            // set new correction due time
            myNextUpdateTime = aCurrentTime + myUpdateRate;

        }
        // check for transmit  out of loop control, lastAmpSet already reached limits. 
        if (myAmpliRatioNeeded) 
        {
            aControlFailure = ( (aTxOchAutomaticConfig.GetToneAmpliRatio() >= myPtMaxTxAmpRatio) || 
                                (aTxOchAutomaticConfig.GetToneAmpliRatio() <= myPtMinTxAmpRatio));
        }
        else
        {
            aControlFailure = ( (aTxOchAutomaticConfig.GetToneAmplitude() >= myPtMaxTxAmp) || 
                                (aTxOchAutomaticConfig.GetToneAmplitude() <= myPtMinTxAmp));
        }


        CT_SubCardType aSubCardType = CSPII_CardIF::GetInstance()->GetSubCardType();
        //update failure indicator
        //if the Card is an MRTMS we do not want to set the config region based on a control failure.
        if(aSubCardType == TRN_32P_NOOEO_TUNABLE)
        {
            hasChanged |= aTxOchAutomaticConfig.SetControlFailure(aMeasurementFailure);
        }
        else
        {
            hasChanged |= aTxOchAutomaticConfig.SetControlFailure(aMeasurementFailure || aControlFailure);
        }
    }

    aTxOchAutomaticConfig.Validate();
    if (hasChanged)
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();

    // wakeup process for next correction
    myTimedProcess->SetDelay( (myUpdateRate < aRandomDelay) ?  myUpdateRate : aRandomDelay );
    myTimedProcess->WakeUp();

}


void CFG_TxOchAutomaticAction::UpdatePowerStatus(MON_OchStatusRegion& aRegion,
                                                 uint32 theSamples,
                                                 MON_PilotToneAction& theAction,
                                                 MON_RelativeTraceId theTraceId)
{
    CFG_TxOchAutomatic& aTxOchAutomaticConfig   = static_cast<CFG_TxOchAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    CFG_Opt&          aOptConfig                = static_cast<CFG_Opt&>((*myCfgOptAppIf->GetCfgRegion())[0]);

    // do nothing if collection already in progress
    if (!theAction.IsInProgress())
    {
        // start collection if power measurement is expired
        if (!aRegion[0].IsValidated())
        {
            // read DC power directly fom OPT if not supported by HW
            if (!(*myTspiiPilotToneRegion)[0].IsDCPowerSupported())
            {
                //Retrieve DC power from TSPII optical
                CT_TEL_mBm aOpticalPowerTransmitted = (*myTspiiOpticalRegion)[0].GetOpticalPowerTransmitted();

                if(aOpticalPowerTransmitted != TRAFFIC_DEFAULT_POWER)
                {
                    // use first ID location for DC power
                    MON_OchPower aFirstId (MON_ID_FIRST,
                                           aOpticalPowerTransmitted,
                                           TEL_DEFAULT_MINIMUM_SN_RATIO+2);

                    // save all three powers in OCH status
                    MON_OchStatus aOchStatus(0);
                    aOchStatus.SetTraceIdPowers(aFirstId);
                    aOchStatus.SetTraceIdPowers(MON_ID_SECOND);
                    aOchStatus.SetTraceIdPowers(MON_ID_DEBUG);
                    aOchStatus.SetChannelId(UNKNOWN_WAVELENGHT);

                    // copy local power value to region
                    aRegion[0] = aOchStatus;
                    aRegion[0].Validate();
                    aRegion.IncModificationCounter();
                }
            }
            else // use pilot tone interface to get power
            {

#if defined (LINUX) || defined (WIN32)
                static MON_RequestID asRequestId = 0;
#else
                static MON_RequestID asRequestId = 0;
#endif
                MON_PilotToneProcessorRequest aRequest(aOptConfig.GetWavelength(),
                                                       ++asRequestId,
                                                       theSamples,
                                                       TSPII_PT_HIGH_PRIORITY);
                theAction.Collect(aRequest, &aRegion, 0, myTspiiPilotToneRegion, NULL);
            }
        }
        else
        {
            // Copy power measurements in output region
            if (&aRegion)
            {
                //Retrieve laser state from TSPII optical
                bool aLaserState = (*myTspiiOpticalRegion)[0].GetLaserState();
                MON_OchPower aNewDcPower = aRegion[0].GetTraceIdPower(theTraceId);

                //Do not correct if the laser is OFF or if new DC power is invalid
                if (!aLaserState  || (aNewDcPower.GetAmplitude() == TRAFFIC_DEFAULT_POWER))
                    aRegion[0].Invalidate();

                // Save new value of DC power
                aTxOchAutomaticConfig.SetDcPower(aNewDcPower);
            }
            else
                FC_THROW_ERROR(FC_InvalidArgumentError, "unexpected region");
        }
    }
}

void CFG_TxOchAutomaticAction::EnableTrace(bool theTraceEnable)
{
    myTraceEnabled = theTraceEnable;
    fc_cout << "\rCFG_TxOchAutomaticAction: Trace is " << DISPLAY_BOOL(myTraceEnabled) << endl;
}
