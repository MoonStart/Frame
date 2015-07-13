// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_OpticalIf.h>
#include <ErrorService/FC_Error.h>
#include "../CFG_HwRefreshOpt.h"
#include "../CFG_Opt.h"
#include "../CFG_OptProt.h"
#include "../CFG_OptAutomatic.h"
#include "../CFG_OptAutoRateLock.h"
#include "../CFG_TxOchAutomatic.h"
#include "../CFG_AppIf.h"
#include <Configuration/CFG_OptSubApplication.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OchPower.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_SubNodeParameters.h>
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>
#include <T6100_CardIf.h>
#include <math.h>
#include <CsPii/CSPII_CardIF.h>


//##ModelId=3C17AE9400E1
CFG_HwRefreshOpt::CFG_HwRefreshOpt(CFG_AppIf& theCfgIf,
                                   TSPII_OpticalRegion& theOptPiiRegion,
                                   CFG_OptAutoRateLockRegion& theOptAutoRateLockRegion,
                                   CFG_OptProtCfgRegion* theOptProtRegion):

    CFG_HwRefreshAction(theCfgIf),
    myOptPiiRegion(theOptPiiRegion),
    myOptAutoRateLockRegion(theOptAutoRateLockRegion),
    myTxOchAutomaticConfigRegion(NULL),
    myLocalPrbsRxSessionCounter(0),
    myCfgApp(static_cast<CFG_OptSubApplication&>(theCfgIf)),
    myOptStatusRegion(NULL),
    myOptProtRegion(theOptProtRegion)
{

    GetBbAction()->AddInputRegion(theCfgIf.GetAutomaticCfgRegion());
    GetBbAction()->AddInputRegion(&myOptAutoRateLockRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    bool isCXM = false;

    // also register to ochStatus region if TsPii is not supporting rx power
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {
        T6100_TelecomIf* aOchContext = aCardContext->GetOchIfPtr();
        if (aOchContext)
        {
            if(aCardContext->GetCardFamily() == SMTM_FAM ||
               aCardContext->GetCardFamily() == TRN_FAM  ||
               aCardContext->GetCardFamily() == PACKET_FAM ||
               aCardContext->GetCardFamily() == OTNM_FAM ||
               aCardContext->GetCardFamily() == FGTMM_FAM ||
               aCardContext->GetCardFamily() == SSM_FAM)
            {
                CT_CardType cardType = (CSPII_CardIF::GetInstance())->GetCardType();
                if (cardType == HGTM || cardType == HGTMS ) // Coriant HGTMS
                {
                    myTxOchAutomaticConfigRegion = NULL;
                }
                else
                {
                    CFG_AppIf& aCfgIf = aOchContext->GetCfgLineSideApp(CT_LINE_SIDE_1);
                    CFG_Region* aRegion = aCfgIf.GetAutomaticCfgRegion();
                    myTxOchAutomaticConfigRegion = static_cast<CFG_TxOchAutomaticCfgRegion*>(aRegion);
                }
            }
            else if(aCardContext->GetCardFamily() != OSC_FAM)
            {
                CFG_AppIf& aCfgIf = aOchContext->GetCfgLineApp();
                CFG_Region* aRegion = aCfgIf.GetAutomaticCfgRegion();
                myTxOchAutomaticConfigRegion = static_cast<CFG_TxOchAutomaticCfgRegion*>(aRegion);
            }
        }
        if (aCardContext->GetCardFamily() == CXM_FAM)
        {
            isCXM = true;
        }
    }

    if (myTxOchAutomaticConfigRegion && !isCXM)
        GetBbAction()->AddInputRegion(myTxOchAutomaticConfigRegion);

    if (myOptProtRegion && !isCXM)
       GetBbAction()->AddInputRegion(myOptProtRegion);

    if(myCfgApp.IsOscRelated())
    {
        MON_AppIf* aMonApp = myCfgApp.GetMonOptApp();

        if(aMonApp)
        {
            myOptStatusRegion = static_cast<MON_OptStatusRegion*>(aMonApp->GetStatusRegion());
            GetBbAction()->AddInputRegion(myOptStatusRegion);
        }

        GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion(), false, false);
    }
    else if (!isCXM)
    {
        GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    }
}

//##ModelId=3C17AE9302B7
CFG_HwRefreshOpt::~CFG_HwRefreshOpt()
{
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    bool isCxm = false;
    if (aCardContext)
    {
        if (aCardContext->GetCardFamily() == CXM_FAM)
        {
            isCxm = true;
        }
    }
    
    if (myTxOchAutomaticConfigRegion && !isCxm)
        GetBbAction()->RemoveInputRegion(myTxOchAutomaticConfigRegion);

    if (myOptProtRegion && !isCxm)
       GetBbAction()->RemoveInputRegion(myOptProtRegion);
    
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetAutomaticCfgRegion());
    if (!isCxm)
    {
        GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    }
    
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());

    if(myOptStatusRegion)
        GetBbAction()->RemoveInputRegion(myOptStatusRegion);
}


FC_Object* CFG_HwRefreshOpt::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    UpdateObject(theRunReason, myOptPiiRegion[0]);

    return NULL;
}

void CFG_HwRefreshOpt::UpdateObject(unsigned theRunReason, TSPII_OpticalIf& theOptPii)
{
    // Refresh the hardware related to facility config object according
    // to current configuration within this object.

    CFG_Opt& aCfgObject = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]);
    CFG_OptAutomatic& aAutomaticCfgObject = static_cast<CFG_OptAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    CFG_OptAutoRateLock& aAutoRateLockObject = myOptAutoRateLockRegion[0];

    //if the OSC Tx has changed then send new power to the peer NE
    if(myOptStatusRegion)
    {
        if(myCfgApp.GetMonOptApp()->GetStatusRegion()->IsModified())
        {
            theOptPii.SetOpticalPowerTransmittedToPeer();
            theOptPii.SetOmsPowerTransmittedToPeer();
        }
    }

    // Allow autoshutdown only if no facility loopback
    bool aForceLaserShutdown = false;
    bool aForceNearEndLaserShutdown = false;

    //Automatic laser shutdown is disabled in the hardware regardless of configuration
    //data under the following conditions.
    //1. If line side protection exists. This is to prevent ALS from getting in the way
    //   of protection switching.
    //2. If a facility loopback exists.
    if (!aAutomaticCfgObject.GetLineSideProtExists() && !aCfgObject.GetFacilityLoopBackEnable())
        theOptPii.SetAutomaticLaserShutdown(aCfgObject.GetAutomaticLaserShutdown());
    else
        theOptPii.SetAutomaticLaserShutdown(false);

    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext && aCardContext->GetCardFamily() == CXM_FAM)
    {
        theOptPii.SetAutomaticLaserShutdown(aAutomaticCfgObject.GetAutomaticLaserShutdown());
    }

    // Send whether to consider AIS-L for ALS based on Maintenance Propagation
    // If it is set to ALS (meaning we want to shut off the laser and Maint Prop
    // is enabled), the AIS-L should be considered.
    if (aCfgObject.GetMaintPropMode() == CT_TEL_MAINT_PROP_ALS)
    {
        theOptPii.SetConsiderAISforALS(true);
    }
    else
    {
        theOptPii.SetConsiderAISforALS(false);
    }
    theOptPii.SetAlsHoldOffDelay(aCfgObject.GetAlsHoldOffDelay());
    theOptPii.SetNearEndAutomaticLaserShutdown(aCfgObject.GetNearEndAutomaticLaserShutdown());

    aForceLaserShutdown = aCfgObject.GetAutomaticLaserShutdown() &&
                          aAutomaticCfgObject.GetAutomaticLaserShutdown();

    if (myOptProtRegion)
    {
        CFG_OptProt& aProtObject = (*myOptProtRegion)[0];
        aForceLaserShutdown |= aProtObject.GetForceLaserShutdown();
    }

    aForceNearEndLaserShutdown = aCfgObject.GetNearEndAutomaticLaserShutdown() &&
                                 aAutomaticCfgObject.GetNearEndAutomaticLaserShutdown();

    // Update laser state according to config and autoshutdown state
    theOptPii.SetLaserEnable(aCfgObject.GetLaserEnable() && !aForceLaserShutdown && !aForceNearEndLaserShutdown);
    theOptPii.SetFacilityLoopbackEnable(aCfgObject.GetFacilityLoopBackEnable());
    theOptPii.SetTerminalLoopbackEnable(aCfgObject.GetTerminalLoopBackEnable());
    theOptPii.SetLOSThreshold(aCfgObject.GetLosThreshold());
    theOptPii.SetOTNMode(aCfgObject.GetDigitalWrapperEnable());
    theOptPii.SetWavelength(aCfgObject.GetWavelength().WavelengthIndex());
    theOptPii.SetBand(aCfgObject.GetBand());
    theOptPii.SetFreqPlan(aCfgObject.GetFreqPlan());
    theOptPii.SetFrequency(aCfgObject.GetFrequency());
    theOptPii.SetPrbsFormat(aCfgObject.GetPrbsFormat());
    theOptPii.SetPrbsTxEnable(aCfgObject.GetPrbsTxEnable());
    theOptPii.SetClockType(aCfgObject.GetClockType());
    theOptPii.SetOTIDStatus(aCfgObject.GetOTIDStatus());

    // Before setting PRBS Rx enable, check to see if the session counter
    // has changed.  The session counter is used to detect the case where the
    // user turns off and on the Rx enable quickly (before this refresh action
    // has a chance to execute) and wants a new session, which results in
    // clearing the PRBX status data.  Note that TSPII resets these counters
    // when it is turned off and on.  Hence, the following code.
    if ((aCfgObject.GetPrbsRxEnable()) &&
        (aCfgObject.GetPrbsRxSessionCounter() != myLocalPrbsRxSessionCounter))
    {
        myLocalPrbsRxSessionCounter = aCfgObject.GetPrbsRxSessionCounter();
        theOptPii.SetPrbsRxEnable(false);
    }
    theOptPii.SetPrbsRxEnable(aCfgObject.GetPrbsRxEnable());
    theOptPii.SetPrbsRxSessionCounter(aCfgObject.GetPrbsRxSessionCounter());

    // Update transmitted pilot tone accodring to Tx Och automatic configuration
    if (myTxOchAutomaticConfigRegion && (aCardContext && aCardContext->GetCardFamily() != CXM_FAM))
    {
        CFG_TxOchAutomatic& aTxOchAutomatic = static_cast<CFG_TxOchAutomatic&>((*myTxOchAutomaticConfigRegion)[0]);
        theOptPii.SetTxTraceID(aTxOchAutomatic.GetTraceId());
        theOptPii.SetTxPilotTone( (aTxOchAutomatic.GetTraceId()==0) ? 0 : MON_OchPower::GetFrequency(aTxOchAutomatic.GetTraceId()));
        if (theOptPii.IsTxPilotToneControlSupported())
        {
            theOptPii.SetTxPTAmpliRatio(aTxOchAutomatic.GetToneAmpliRatio());
            theOptPii.SetTxPTAmplitude((uint32)floor(aTxOchAutomatic.GetToneAmplitude()+0.5f));
        }
    }

    // Update clock rate using default or the one provided by Auto Rate Lock down feature if its enabled.
    if (aCfgObject.GetAutoRateLockDown())
    {
        theOptPii.SetBitRate(aAutoRateLockObject.GetSignalRate());
    }
    else
    {
        theOptPii.SetBitRate(aCfgObject.GetSignalRate());
    }

    // Update OEO Regen Mode
    theOptPii.SetOEORegenMode(aCfgObject.GetOEORegenMode());

    // Forced Fefi when desired
    theOptPii.SetFefiForced(aAutomaticCfgObject.GetForceFefi());

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();
}

