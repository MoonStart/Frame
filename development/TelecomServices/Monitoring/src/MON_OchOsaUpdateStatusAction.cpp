/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        MON_OchOsaUpdateStatusAction.cpp
 *    DATE:          11/07/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     MON/OCH; LIAME/LRAME
 *    OVERVIEW:      MON och action for collecting OSA data from TSPII
 *    FEATURE PACK:  FP3.3
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:         - LIAME/LRAME does not have any och detection circuit
 *                     before the gain block. These values are computed for the
 *                     user by subtracting the current gain from the och power
 *                     after the gain block.
 *                   - Since we only have to do this in the LINE-to-PORT
 *                     direction, therefore ALT REQUEST/RESULT regions are NOT
 *                     required in the PORT-to-LINE direction.
 *
 ******************************************************************************/
#include "Monitoring/MON_OchOsaUpdateStatusAction.h"
#include "Monitoring/MON_PilotToneProcessorRequest.h"
#include "Monitoring/MON_OmsStatus.h"
#include "Monitoring/MON_OchStatus.h"
#include "Monitoring/MON_OchDefects.h"
#include "Monitoring/MON_OchConfig.h"
#include "Monitoring/MON_OchRequest.h"
#include "Monitoring/MON_OchResult.h"
#include "Monitoring/MON_AppIf.h"
#include <ErrorService/FC_Error.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_OsaIf.h>
#include "CsPii/CSPII_CardIF.h"
#include "CsPii/CSPII_ShelfIF.h"


////////////////////////////////////////////////////////////////////////////////
MON_OchOsaUpdateStatusAction::MON_OchOsaUpdateStatusAction(MON_AppIf&               theMonIf,
                                                           TSPII_OsaRegion*         thePiiOsaRegion,
                                                           uint32                   thePiiOsaUnit,
                                                           MON_OchStatusRegion*     theOchStatusRegion,
                                                           uint32                   theNumberOfWavelengths,
                                                           MON_AppIf*               theOmsLayerIf) :
    MON_UpdateStatusAction(theMonIf,NULL),
    myPiiOsaRegion(thePiiOsaRegion),
    myPiiOsaUnit(thePiiOsaUnit),
    myOchStatusRegion(theOchStatusRegion),
    myNumberOfWavelengths(theNumberOfWavelengths),
    myOmsLayerIf(theOmsLayerIf),
    myRequest(static_cast<MON_OchRequest&>((*GetMonIf().GetRequestRegion())[0])),
    myResult(static_cast<MON_OchResult&>((*GetMonIf().GetResultRegion())[0])),
    myOchPowerDebounceThreshold(TEL_DEFAULT_OCH_POWER_DEBOUNCE_THRESHOLD),
    myOchPowerDebouncePeriod(TEL_DEFAULT_OCH_POWER_DEBOUNCE_PERIOD),
    myHistoryIndex(0),
    myRecordHistoryFlag(false)
{
    FC_THROW_ERROR_IF(myPiiOsaRegion==NULL, FC_RuntimeError, "Unable to retrieve PII Osa region");
    GetBbAction()->AddInputRegion(myPiiOsaRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddInputRegion(GetMonIf().GetRequestRegion(), false);
    if(myPiiOsaUnit == TSPII_OSA_L2P)
        GetBbAction()->AddInputRegion(GetMonIf().GetAltRequestRegion(), false);

    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);


    GetBbAction()->AddOutputRegion(GetMonIf().GetResultRegion(),false, false);
    if(myPiiOsaUnit == TSPII_OSA_L2P)
        GetBbAction()->AddOutputRegion(GetMonIf().GetAltResultRegion(),false, false);

    ClearHistoryForAllCh();

    if(CSPII_ShelfIF::GetInstance()->IsFPNANOShelfType())
    {
        myOchPowerDebounceThreshold = TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_THRESHOLD;
        myOchPowerDebouncePeriod = TEL_DEFAULT_OCH_NANO_POWER_DEBOUNCE_PERIOD;
        myRecordHistoryFlag = true;
    }
}

////////////////////////////////////////////////////////////////////////////////
MON_OchOsaUpdateStatusAction::~MON_OchOsaUpdateStatusAction()
{
    if(myPiiOsaRegion)
        GetBbAction()->RemoveInputRegion(myPiiOsaRegion);

    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveInputRegion(GetMonIf().GetRequestRegion());

    if(GetMonIf().GetAltRequestRegion())
        GetBbAction()->RemoveInputRegion(GetMonIf().GetAltRequestRegion());

    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetResultRegion());

    if(GetMonIf().GetAltResultRegion())
        GetBbAction()->RemoveOutputRegion(GetMonIf().GetAltResultRegion());
}

////////////////////////////////////////////////////////////////////////////////
FC_Object* MON_OchOsaUpdateStatusAction::Suspend(unsigned theRunReason,
                                                 FC_Object* theInvokerObj,
                                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetResultRegion()->Reset();

    if(GetMonIf().GetAltResultRegion())
        GetMonIf().GetAltResultRegion()->Reset();

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
FC_Object* MON_OchOsaUpdateStatusAction::Process(unsigned theRunReason,
                                                 FC_Object* theInvokerObj,
                                                 FC_Object* theParam)
{
    bool incStatusModCounter    = false;
    bool incDefectsModCounter   = false;
    bool hasStatusChanged       = false;
    bool hasDefectsChanged      = false;
    bool *prtHasStatusChanged   = &hasStatusChanged;
    bool *prtHasDefectsChanged  = &hasDefectsChanged;

    TSPII_OsaIf& aPiiOsa = (*myPiiOsaRegion)[0];

    for(uint32 aIndex = 0; aIndex < myNumberOfWavelengths; aIndex++)
    {
        UpdateObject(theRunReason, aIndex, aPiiOsa, &prtHasStatusChanged, &prtHasDefectsChanged);

        //if for any of the objects in the region the gain
        //has changed then we will increment the modification
        //counter
        if(hasStatusChanged)
            incStatusModCounter = true;

        if(hasDefectsChanged)
            incDefectsModCounter = true;
    }

    if(incStatusModCounter)
        GetMonIf().GetStatusRegion()->IncModificationCounter();

    if(incDefectsModCounter)
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    //--------------------------------------------------------------
    // On-Demand Data
    //--------------------------------------------------------------
    if(GetMonIf().GetRequestRegion()->IsModified())
    {
        uint8 wIndex = myRequest.GetChannelId().WavelengthIndex();
        if( wIndex <= (*GetMonIf().GetStatusRegion()).Size())
        {
        MON_OchStatus&  aStatus = static_cast<MON_OchStatus&>((*GetMonIf().GetStatusRegion())[myRequest.GetChannelId().WavelengthIndex()]);
        MON_OchPower aOchPower(aStatus.GetTraceIdPower(MON_ID_FIRST));

        myResult.Reset();
        myResult.SetTraceIdPowers(aOchPower);
        myResult.SetChannelId(myRequest.GetChannelId());

        MON_PilotToneProcessorRequest* aPilotToneRequest = new MON_PilotToneProcessorRequest(myRequest.GetChannelId(), myRequest.GetRequestID(), 0, TSPII_PT_LOW_PRIORITY);
        myResult.SetRequestInformation(*aPilotToneRequest);
        myResult.Validate();

        GetMonIf().GetResultRegion()->IncModificationCounter();
        GetMonIf().GetResultRegion()->UpdateNotify();
        }
    }

    if(GetMonIf().GetAltRequestRegion() && GetMonIf().GetAltRequestRegion()->IsModified())
    {
        MON_OchRequest& myAltRequest = static_cast<MON_OchRequest&>((*GetMonIf().GetAltRequestRegion())[0]);
        MON_OchResult&  myAltResult  = static_cast<MON_OchResult&>((*GetMonIf().GetAltResultRegion())[0]);

        uint8 wIndex = myAltRequest.GetChannelId().WavelengthIndex();
        if(wIndex <= (*GetMonIf().GetStatusRegion()).Size())
        {
        MON_OchStatus&  aStatus = static_cast<MON_OchStatus&>((*GetMonIf().GetStatusRegion())[myAltRequest.GetChannelId().WavelengthIndex()]);

        CT_TEL_mBm LSR_Amplitude = aStatus.GetPreAmpPower();
        CT_TEL_mBm LSR_Snr       = TRAFFIC_DEFAULT_POWER;
        MON_OchPower* aOchPower = new MON_OchPower(MON_ID_FIRST, LSR_Amplitude, LSR_Snr);

        myAltResult.Reset();
        myAltResult.SetTraceIdPowers(*aOchPower);
        myAltResult.SetChannelId(myAltRequest.GetChannelId());

        MON_PilotToneProcessorRequest* aPilotToneRequest = new MON_PilotToneProcessorRequest(myAltRequest.GetChannelId(), myAltRequest.GetRequestID(), 0, TSPII_PT_LOW_PRIORITY);
        myAltResult.SetRequestInformation(*aPilotToneRequest);
        myAltResult.Validate();

        GetMonIf().GetAltResultRegion()->IncModificationCounter();
        GetMonIf().GetAltResultRegion()->UpdateNotify();
        }
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::UpdateObject(unsigned theRunReason,
                                                uint32 theIndex,
                                                TSPII_OsaIf& thePiiOsa,
                                                bool **hasStatusChanged,
                                                bool **hasDefectsChanged)
{
    MON_OchDefects& aDefects    = static_cast<MON_OchDefects&>((*GetMonIf().GetDefectsRegion())[(bbindex_t)theIndex]);
    MON_OchStatus&  aStatus     = static_cast<MON_OchStatus&>((*GetMonIf().GetStatusRegion())[(bbindex_t)theIndex]);
    MON_OchConfig&  aConfig     = static_cast<MON_OchConfig&>((*GetMonIf().GetConfigRegion())[(bbindex_t)theIndex]);
    bool aStatusChanged   = false;
    bool aDefectsChanged  = false;

    //--------------------------------------------------------------
    // STATUSES
    // Read current statuses

    // Invalidate status region if the monitoring is disabled
    if(!aConfig.IsValidated())
    {
        aStatus.Invalidate();
        aStatus.Reset();
    }
    else
    {
        //--------------------------------------------------------------
        // STATUS
        // Read current status
        //--------------------------------------------------------------

        if(GetMonIf().GetStatusRegion()->IsValid())
        {
            //if the data from the hw checks out then we proceed
            //if the condition is either overflow or underflow
            //then still proceed since this relates to power
            //management and power management could clear this
            //condition by moving EOVAs and/or Amp Gain

            uint32 opmStatus = thePiiOsa.GetOpmStatus();
            if(opmStatus & TSPII_OPM_STATUS_MASK_WAVELENGTH_RANGE ||
               opmStatus & TSPII_OPM_STATUS_MASK_CH_SPACING       ||
               opmStatus & TSPII_OPM_STATUS_MASK_CH_NUMBER)
            {
                aStatusChanged |= aStatus.Invalidate();
                FC_REPORT_ERROR(FC_RuntimeError, "OPM data integrity check failed");
            }
            else
            {
                //debounce power value
                bool setOchPower = true;

                // Only debounce Nano shelf applications. TSPII does it for USS shelf
                // TSPII will keep the current OSNR and debounced power synchronized.
                // This means that MON must call GetPower first, followed by GetOsnr
                MON_RelativeTraceId aTraceId = MON_ID_FIRST;
                CT_TEL_mBm curPwr         = thePiiOsa.GetPower(theIndex);
                CT_TEL_mBm curSnr         = thePiiOsa.GetOsnr(theIndex);
                bool SnrValid             = thePiiOsa.IsOsnrValid(theIndex);
                time_t     curSampleTime  = CSPII_CardIF::GetInstance()->GetUTCTime();

                CT_TEL_mBm prevPwr        = aStatus.GetTraceIdPower(aTraceId).GetAmplitude();
                time_t     prevSampleTime = aStatus.GetSampleTime();

                if ( myRecordHistoryFlag )
                {
                    if( (abs(curPwr - prevPwr) > myOchPowerDebounceThreshold) &&
                        (curSampleTime - prevSampleTime < myOchPowerDebouncePeriod) )
                    {
                        setOchPower = false;
                        RecordHistory(theIndex, prevPwr, curPwr, curSampleTime, MON_PWR_SPIKE);
                    }
                }

                if(setOchPower)
                {
                    const MON_OchPower aOchPower(aTraceId, curPwr, curSnr, SnrValid);
                    aStatusChanged |= aStatus.SetTraceIdPowers(aOchPower);
                    aStatusChanged |= aStatus.Validate();
                    RecordHysteresis(theIndex, prevPwr, curPwr, curSampleTime);
                }
            }
        }
        else
            aStatusChanged |= aStatus.Invalidate();

        // Calculate the PreAmp Power when the Oms Layer us given
        // (i.e., for the LIAM).  This is done by finding the power
        // (from the OCH layer) and subtracting the gain (from the OMS layer).
        if(myPiiOsaUnit == TSPII_OSA_L2P && myOmsLayerIf && aStatus.IsValidated())
        {
            // compute power gain from the OMS region
            MON_OmsStatus& aOmsStatus = static_cast<MON_OmsStatus&>( (*myOmsLayerIf->GetStatusRegion())[0] );

            // Actual gain is computed by subtracting Output
            // oms photodiode value from the input oms photodiode, it is
            // not reilable. Also a bug in the hardware was discovered
            // which caused both of the these values to be set to the same
            // causing us to compute incorrect actual gain.
            // So instead of using the actual gain now we will rely on
            // the configured gain.
            CT_TEL_mBm aPowerGain = aOmsStatus.GetConfiguredGain();

            // get the power measurement from the OCH region
            CT_TEL_mBm aPowerReading = aStatus.GetPower();

            // Calculate PreAmp Power and then write to the Status Region
            CT_TEL_mBm aPreAmpPower = TRAFFIC_DEFAULT_POWER;
            if(aPowerReading != TRAFFIC_DEFAULT_POWER)
            {
                aPreAmpPower = aPowerReading - aPowerGain;
            }

            aStatusChanged |= aStatus.SetPreAmpPower(aPreAmpPower);
        }

        //--------------------------------------------------------------
        // DEFECTS
        // Read current defects
        //--------------------------------------------------------------
        bool aLossPwrState       = false;
        bool aDebugTraceDetected = false;
        if(aStatus.IsValidated() || aConfig.IsValidated())
        {
            // get previous defect state
            uint32 aCount=0;
            aDefects.GetDefectStatus(CT_TEL_OCH_LOSS_PTONE_DEFECT, &aCount, &aLossPwrState);

            // get most powerfull signal ID
            const MON_OchPower& aPower = aStatus.GetMostPowerfullId();

            // get current S/N ration
            CT_TEL_mBm aSignalToNoiseRatio = aPower.GetSnr();
            CT_TEL_mBm aPowerLevel = aPower.GetAmplitude();

            // get current loss defect threshold
            CT_TEL_mBm aMinimumSN = aConfig.GetMinimumSNRatio();
            CT_TEL_mBm aLossThreshold = aConfig.GetLossOfInputPowerThreshold();

            //remove additional LOS

            // Since the OSNR reading from the OPM device is not reliable,
            // OSNR reading is esentially irnored.
            // if defect is already set, clear it only of power exceeds threshold +1 dB
            // to avoid toggling
            if(aLossPwrState)
            {
                aMinimumSN     += 0 * CT_TEL_POWER_FACTOR;
                aLossThreshold += 1 * CT_TEL_POWER_FACTOR;
                if(aPowerLevel > aLossThreshold &&  aSignalToNoiseRatio > aMinimumSN)
                    aLossPwrState = false;
            }
            // otherwise compare with normal thresholds
            else
            {
                if(aPowerLevel < aLossThreshold || aSignalToNoiseRatio < aMinimumSN)
                    aLossPwrState = true;
            }

            // set value to a stable one
            aDefectsChanged |= aDefects.SetDetectedId(MON_ID_FIRST);
            aDefectsChanged |= aDefects.Validate();
        }
        else
        {
            aDefectsChanged |= aDefects.Invalidate();
            aDefects.Reset();
        }

        // update actual defect
        aDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OCH_LOSS_PTONE_DEFECT,           aLossPwrState,       0);

        //this is left here for historical purpose, there is no notion of debug trace id in the OSA
        //capable modules
        aDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OCH_DEBUG_TRACE_DETECTED_DEFECT, aDebugTraceDetected, 0);
    }

    *(*hasStatusChanged)  = aStatusChanged;
    *(*hasDefectsChanged) = aDefectsChanged;
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::ClearHistoryForAllCh()
{
    for(uint32 aIndex = 0; aIndex < myNumberOfWavelengths; aIndex++)
        ClearHistoryForCh(aIndex);
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::ClearHistoryForCh(uint32 theIndex)
{
    myHistory[theIndex].myHistMax.event  = MON_UNKNOWN;
    myHistory[theIndex].myHistMax.prevPwr= TRAFFIC_DEFAULT_POWER;
    myHistory[theIndex].myHistMax.curPwr = TRAFFIC_DEFAULT_POWER;

    myHistory[theIndex].myHistMin.event  = MON_UNKNOWN;
    myHistory[theIndex].myHistMin.prevPwr= TRAFFIC_DEFAULT_POWER;
    myHistory[theIndex].myHistMin.curPwr = TRAFFIC_DEFAULT_POWER;

    for(int i = 0; i < MON_OCH_PWR_HISTORY_SIZE; i++)
    {
        myHistory[theIndex].myHistEvent[i].event   = MON_UNKNOWN;
        myHistory[theIndex].myHistEvent[i].prevPwr = TRAFFIC_DEFAULT_POWER;
        myHistory[theIndex].myHistEvent[i].curPwr  = TRAFFIC_DEFAULT_POWER;
    }
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::RecordHistory(uint32 theIndex,
                                                 CT_TEL_mBm prevPwr,
                                                 CT_TEL_mBm curPwr,
                                                 time_t curSampleTime,
                                                 eMON_Event event)
{
    if (++myHistoryIndex >= MON_OCH_PWR_HISTORY_SIZE) myHistoryIndex = 0;
    myHistory[theIndex].myHistEvent[myHistoryIndex].myTimestamp = curSampleTime;
    myHistory[theIndex].myHistEvent[myHistoryIndex].event = event;
    myHistory[theIndex].myHistEvent[myHistoryIndex].prevPwr = prevPwr;
    myHistory[theIndex].myHistEvent[myHistoryIndex].curPwr = curPwr;
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::RecordHysteresis(uint32 theIndex,
                                                    CT_TEL_mBm prevPwr,
                                                    CT_TEL_mBm curPwr,
                                                    time_t curSampleTime)
{
    if(myHistory[theIndex].myHistMin.curPwr > curPwr ||
       myHistory[theIndex].myHistMin.curPwr == TRAFFIC_DEFAULT_POWER)
    {
        myHistory[theIndex].myHistMin.myTimestamp = curSampleTime;

        if(myHistory[theIndex].myHistMin.curPwr == TRAFFIC_DEFAULT_POWER)
            myHistory[theIndex].myHistMin.prevPwr = curPwr;
        else
            myHistory[theIndex].myHistMin.prevPwr = myHistory[theIndex].myHistMin.curPwr;

        myHistory[theIndex].myHistMin.curPwr = curPwr;
    }

    if(myHistory[theIndex].myHistMax.curPwr < curPwr ||
       myHistory[theIndex].myHistMax.curPwr == TRAFFIC_DEFAULT_POWER)
    {
        myHistory[theIndex].myHistMax.myTimestamp = curSampleTime;

        if(myHistory[theIndex].myHistMax.curPwr == TRAFFIC_DEFAULT_POWER)
            myHistory[theIndex].myHistMax.prevPwr = curPwr;
        else
            myHistory[theIndex].myHistMax.prevPwr = myHistory[theIndex].myHistMax.curPwr;

        myHistory[theIndex].myHistMax.curPwr = curPwr;
    }
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::DisplayHistoryForAllCh()
{
    for(uint32 aIndex = 0; aIndex < myNumberOfWavelengths; aIndex++)
        DisplayHistoryForCh(aIndex);
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len)
{
    if(*pBuf == NULL)
        return;

    memset(*pBuf, 0x00, len);

    struct tm *stamp = NULL;

    if( (stamp = localtime(&theTime)) != NULL)
    {
        sprintf(*pBuf, "%2.2d/%2.2d/%4.4d-%2.2d:%2.2d:%2.2d",
                stamp->tm_mon+1, stamp->tm_mday, stamp->tm_year+1900,
                stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
    }
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::DisplayHistoryForCh(uint32 theIndex)
{
    char line[160];

    char tstamp[20];
    char *pBuf = &tstamp[0];
    GetDateTimeStampStr(CSPII_CardIF::GetInstance()->GetUTCTime(), &pBuf, sizeof(tstamp));

    fc_cout << "\nMonOchPowerHistory-"<<theIndex<<": "<<tstamp<<endl;

    //display should not exceed 80 columns
    //                  10        20        30        40        50        60        70        80
    //          01234567890123456789012345678901234567890123456789012345678901234567890123456789
    fc_cout << "                                        prev  cur   " << endl;
    fc_cout << " Date       Time     Num  Event         pwr   pwr   " << endl;
    fc_cout << "----------------------------------------------------" << endl;
    for(int i = 0; i < MON_OCH_PWR_HISTORY_SIZE; i++)
    {
        if(myHistory[theIndex].myHistEvent[i].event != MON_UNKNOWN)
        {
            GetDateTimeStampStr(myHistory[theIndex].myHistEvent[i].myTimestamp, &pBuf, sizeof(tstamp));

            sprintf(line, " %s %-4d %13s %5d %5d",
                    tstamp,
                    i,
                    DISPLAY_MON_EVENT(myHistory[theIndex].myHistEvent[i].event),
                    myHistory[theIndex].myHistEvent[i].prevPwr,
                    myHistory[theIndex].myHistEvent[i].curPwr);

            fc_cout << line << endl;
        }
    }
    fc_cout << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////
void MON_OchOsaUpdateStatusAction::DisplayHysteresis()
{
    char line[160];

    char tstamp[20];
    char *pBuf = &tstamp[0];

    char tempstamp[20];
    char *pTempBuf = &tempstamp[0];

    GetDateTimeStampStr(CSPII_CardIF::GetInstance()->GetUTCTime(), &pBuf, sizeof(tstamp));

    fc_cout << "\nMonOchPowerHysteresis-"<<tstamp<<endl<<endl;

    //display should not exceed 80 columns
    //                  10        20        30        40        50        60        70        80
    //          01234567890123456789012345678901234567890123456789012345678901234567890123456789
    fc_cout << "               Minimum               |            Maximum              "    << endl;
    fc_cout << "                         prev  cur   |                     prev  cur   "    << endl;
    fc_cout << " Ch  Date       Time     pwr   pwr   | Date       Time     pwr   pwr   "    << endl;
    fc_cout << "-----------------------------------------------------------------------"    << endl;
    for(uint32 i = 0; i < myNumberOfWavelengths; i++)
    {
        GetDateTimeStampStr(myHistory[i].myHistMin.myTimestamp, &pBuf, sizeof(tstamp));
        GetDateTimeStampStr(myHistory[i].myHistMax.myTimestamp, &pTempBuf, sizeof(tempstamp));

        sprintf(line, " %-3d %s %5d %5d | %s %5d %5d",
                i,
                tstamp,
                myHistory[i].myHistMin.prevPwr,
                myHistory[i].myHistMin.curPwr,
                tempstamp,
                myHistory[i].myHistMax.prevPwr,
                myHistory[i].myHistMax.curPwr);

            fc_cout << line << endl;
    }
    fc_cout << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////
bool MON_OchOsaUpdateStatusAction::Set(int argc, char ** argv)
{
    bool status = true;

    if(argc >= 3 && argv[0][0] == 'h')
    {
        if(argv[1][0] == 'c')
        {
            if(strncmp(argv[2], "all", 3) == 0)
            {
                ClearHistoryForAllCh();
            }
            else
            {
                uint32 idx = strtoul(argv[2], NULL, 0);
                ClearHistoryForCh(idx);
            }
        }

        else if(argv[1][0] == 'd')
        {
            if(argc == 3)
            {
                if(argv[2][0] == 'h')
                    DisplayHysteresis();
                else
                    status = false;
            }
            else if(argv[2][0] == 'e')
            {
                if(strncmp(argv[3], "all", 3) == 0)
                {
                    DisplayHistoryForAllCh();
                }
                else
                {
                    uint32 idx = strtoul(argv[3], NULL, 0);
                    DisplayHistoryForCh(idx);
                }
            }
        }
        else
            status = false;
    }

    else if(argc >= 1 && argv[0][0] == 'p')
    {
        if(argc == 2)
        {
            time_t period = strtoul(argv[1], NULL, 0);
            myOchPowerDebouncePeriod = period;
        }
        fc_cout << "Debounce Period = " << (unsigned long) myOchPowerDebouncePeriod << " Sec" << endl;
    }

    else if(argc >= 1 && argv[0][0] == 't')
    {
        if(argc == 2)
        {
            CT_TEL_mBm threshold = strtoul(argv[1], NULL, 0);
            myOchPowerDebounceThreshold = threshold;
        }
        fc_cout << "Debounce Threshold = " << myOchPowerDebounceThreshold << " mBm" << endl;
    }


    else
    {
        fc_cout << "\n h(istory)"                           << endl;
        fc_cout << " ...d(display) <e(vent)> <och# | all>"  << endl;
        fc_cout << " ...d(display) <h(ysteresis)>"          << endl;
        fc_cout << " ...c(lear) <och# | all>"               << endl;
        fc_cout << " p(eriod for Debounce) [value(sec)]"    << endl;
        fc_cout << " t(hreshold for Debounce) [value(mBm)]" << endl;


        status = false;
    }

    return(status);
}
