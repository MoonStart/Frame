// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_RsIf.h>
#include "Monitoring/MON_AppIf.h"
#include "Monitoring/MON_RsConfig.h"
#include "Configuration/CFG_RsSubApplication.h"
#include "../CFG_HwRefreshRs.h"
#include "../CFG_Rs.h"
#include "../CFG_RsAutomatic.h"
#include "../CFG_OptAutoRateLock.h"
#include "../CFG_HoldOffTimer.h"
#include "../CFG_OptProt.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include "SignalProtection/SP_1plus1BaseApplication.h"

#define YCABLE_PRIORITY_DEFECT_SW_AIS_DELEY 500

CFG_HwRefreshRs::CFG_HwRefreshRs(CFG_AppIf& theCfgIf,
                                 CFG_RsAutomaticCfgRegion* theAutomaticCfgRegion,
                                 CFG_OptAutoRateLockRegion* theAutoRateLockRegion,
                                 TSPII_RsRegion& theRsPiiRegion,
                                 CFG_OptProtCfgRegion* theOptProtCfgRegion):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myAutoRateLockRegion(theAutoRateLockRegion),
    myRsPiiRegion(theRsPiiRegion),
    myRsMonConfigRegion(NULL),
    myOptProtCfgRegion(theOptProtCfgRegion),
    myPreivousIsYcableStandby(false)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    if (myAutoRateLockRegion) GetBbAction()->AddInputRegion(myAutoRateLockRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {
        if(aCardContext->GetCardFamily() == OSM_FAM)
        {
            CFG_RsSubApplication & aRsCfgApp = (static_cast<CFG_RsSubApplication&>(theCfgIf));
            myRsMonConfigRegion = static_cast<MON_RsConfigRegion*>(aRsCfgApp.GetIncomingMonApp()->GetConfigRegion());
            GetBbAction()->AddInputRegion(myRsMonConfigRegion);
        }
    }
}

CFG_HwRefreshRs::~CFG_HwRefreshRs()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    if (myAutoRateLockRegion) GetBbAction()->RemoveInputRegion(myAutoRateLockRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    if (myRsMonConfigRegion)
    {
        GetBbAction()->RemoveInputRegion(myRsMonConfigRegion);
    }
}

FC_Object* CFG_HwRefreshRs::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    bool aAutomaticAis         = false;
    bool aAutomaticTlabAis     = false;
    bool aAutomaticAisInternal = false;
    bool aAutomaticRdi         = false;
    bool aAutomaticCSFOPUInternal = false;
    bool aAutomaticSuppressBI  = false;
	bool aLspActive            = false;
    bool aDrop                 = false;
    bool aAdd                  = false;
    bool isYcableStandby       = false;


	CFG_Rs& aCfgObject = static_cast<CFG_Rs&>((*GetCfgIf().GetCfgRegion())[0]);
    TSPII_RsIf& aRsPiiObject = myRsPiiRegion[0];
    CFG_OptAutoRateLock* aAutoRateLock = NULL; 
    if(myAutoRateLockRegion) aAutoRateLock = &(*myAutoRateLockRegion)[0];

    // Indication (and Internal Indication) Type require special processing.
    // Agent sends down the type, but it can be over-written by the automatic action.
    // Finally, after all that work, it is only sent down to Tspii if ForceAIS is on
    // (otherwise, NONE should be sent down).
    // Here, read the Configuration from Agent
    CT_RS_IndicationType anIndicationType  = aCfgObject.GetIndicationType();
    CT_RS_IndicationType anInternalIndType = aCfgObject.GetInternalIndType();
    
    if(myOptProtCfgRegion)
    {
        isYcableStandby = (*myOptProtCfgRegion)[0].GetForceLaserShutdown();
    }
	
    if (myAutomaticCfgRegion)
    {
        CFG_RsAutomatic& aAutomaticCfgObject = (*myAutomaticCfgRegion)[0];
        
        if( (myPreivousIsYcableStandby && !isYcableStandby) ) //this indicates the instance when laser turned on
        {
            /*  MR216114
                AIS was not expected to insert when Ycable switched to a side with defects cleared.
                We could only SetForceAIS once here because myPreivousIsYcableStandby
                & isYcableStandby flag only indicated the time point when laser was turned on.
                But force AIS would be set to true when ran into RS_AutomaticAction for next time.
                This would cause two hits and long switch time on TB.
                Thus a holdoff timer was set here to holdoff AIS for 500ms.
            */
            /*    MR219938
                OOS transponder then IS again switch over time.
                Increase holdoff time to 500ms.
            */
            aAutomaticCfgObject.SetForceAIS(false);
            CFG_HoldOffTimer* aTimer = GetCfgIf().GetHoldOffTimer();
            if (aTimer) 
            {
                bool theHoldOffTimerIsActive = false;
                aTimer->ApplyConditionAfterHoldoff(false, theHoldOffTimerIsActive, (uint32)(YCABLE_PRIORITY_DEFECT_SW_AIS_DELEY));
            }
        }

        // Set TLAB AIS based on config and automatic config
        // Note: TLAB AIS takes precedent
        aAutomaticTlabAis = aCfgObject.GetAutoTlabAIS() && aAutomaticCfgObject.GetForceAIS();

        // Set the AIS based on config and automatic config
        aAutomaticAis = aCfgObject.GetAutomaticAISL() && aAutomaticCfgObject.GetForceAIS();

        // Set RDI force flag (also check whether the suppress backward indicator allows RDI
        aAutomaticRdi = aAutomaticCfgObject.GetForceRDI() && (!aAutomaticCfgObject.GetSuppressBackwardInd());

        // Set Suppress Backward Indicator flag.
        aAutomaticSuppressBI = aAutomaticCfgObject.GetSuppressBackwardInd();
       
        // Set internal AIS force flag
        aAutomaticAisInternal = aAutomaticCfgObject.GetForceAISInternal();

        // Set Internal CSF-OPU flag
        aAutomaticCSFOPUInternal = aAutomaticCfgObject.GetForceCSFOPUInternal();

		aLspActive = aAutomaticCfgObject.GetLineSideProtExists();

        // Set 1 Way XC Add and Drop flags.
        aDrop = aAutomaticCfgObject.GetDrop();
        aAdd  = aAutomaticCfgObject.GetAdd();

        // Use the Indication Type from automatic Config only if it is set (not UNKNOWN)
        CT_RS_IndicationType anAutoIndicationType  = aAutomaticCfgObject.GetAutoIndicationType();
        if (anAutoIndicationType  != CT_RS_INDICATION_UNKNOWN) 
        {
            anIndicationType  = anAutoIndicationType;
        }

        // Use the Internal Indication Type from automatic Config only if it is set (not UNKNOWN)
        CT_RS_IndicationType anAutoInternalIndType = aAutomaticCfgObject.GetAutoInternalIndType();
        if (anAutoInternalIndType  != CT_RS_INDICATION_UNKNOWN) 
        {
            anInternalIndType = anAutoInternalIndType;
        }
    }

	//Automatic TLAB AIS generation is disabled in the hardware regardless of configuration
	//data under the following conditions.
	//1. If line side protection exists. This is to prevent TLAB AIS generation from getting in the way
	//   of protection switching.
    //2. If external signaling is disabled
	if (aLspActive || aCfgObject.GetExternalSignalingDisabled())
	{
		aRsPiiObject.SetAutoTlabAIS(false);
	}
	else
	{
        aRsPiiObject.SetAutoTlabAIS(aCfgObject.GetAutoTlabAIS());
	}

    // Check if external signaling is disabled
    if (!aCfgObject.GetExternalSignalingDisabled()) 
    {
        aRsPiiObject.SetForceTlabAIS(aAutomaticTlabAis || aCfgObject.GetForceTlabAIS());
        if(isYcableStandby)
        {
            aRsPiiObject.ForceAIS(false);
        }
        else
        {
            aRsPiiObject.ForceAIS(aAutomaticAis || aCfgObject.GetForceAISL());
        }
        aRsPiiObject.SetRdiReiAutomatic(!aAutomaticSuppressBI);
        aRsPiiObject.SetForceRDI(aAutomaticRdi);

        // The Indication Type to be sent when ForceAIS is ON has been deternmined above
        // However, send NONE to indicate that ForceIAS is OFF.
        if ( ((aAutomaticAis == false) && (aCfgObject.GetForceAISL() == false)) || isYcableStandby)
        {
            anIndicationType  = CT_RS_INDICATION_NONE;
        }            
        aRsPiiObject.ForceRsIndication(anIndicationType);
    }
    else
    {
        aRsPiiObject.SetForceTlabAIS(false);
        aRsPiiObject.ForceAIS(false);
        aRsPiiObject.SetRdiReiAutomatic(false);
        aRsPiiObject.SetForceRDI(false);
        aRsPiiObject.ForceRsIndication(CT_RS_INDICATION_NONE);
    }
    myPreivousIsYcableStandby = isYcableStandby;

    // Check if internal signaling is disabled
    if (!aCfgObject.GetInternalSignalingDisabled()) 
    {
        aRsPiiObject.SetForceInternalAIS(aAutomaticAisInternal);

        // The Internal Indication to be sent when ForceInternalAIS is ON 
        // has been deternmined above.
        // However, send NONE to indicate that ForceInternalAIS is OFF.
        if (aAutomaticAisInternal == false)
        {
            anInternalIndType = CT_RS_INDICATION_NONE;
        }            
        aRsPiiObject.ForceInternalRsIndication(anInternalIndType);

        aRsPiiObject.SetForceInternalCSFOPU(aAutomaticCSFOPUInternal);
    }
    else
    {
        aRsPiiObject.SetForceInternalAIS(false);
        aRsPiiObject.ForceInternalRsIndication(CT_RS_INDICATION_NONE);
        aRsPiiObject.SetForceInternalCSFOPU(false);
    }

    //Set the trace in transparent mode if neccesary
    aRsPiiObject.SetTxTraceTransparent(aCfgObject.GetSentTraceTransparent());
    aRsPiiObject.SetTxTrace(aCfgObject.GetSentTrace());

    //Set the Messaging mode
    aRsPiiObject.SetEnableMessaging(aCfgObject.GetMessagingEnabled());

    if (myRsMonConfigRegion)
    {
        aRsPiiObject.SetExpectedTrace((*myRsMonConfigRegion)[0].GetExpectedTrace());
        aRsPiiObject.SetTIMMonitoringEnable((*myRsMonConfigRegion)[0].GetTIMMonitoringEnable());
        aRsPiiObject.SetLayerFailOnTIM((*myRsMonConfigRegion)[0].GetLayerFailOnTIM());
    }

    //Set the True SDH mode
    aRsPiiObject.SetTrueSDHMode(aCfgObject.GetSDHTrueMode());

    //Set the CBR Mapping mode    
    aRsPiiObject.SetCBRMappingMode(aCfgObject.GetCBRMappingMode());

    //Set Add and Drop XC flags.
    aRsPiiObject.SetDroponly(aDrop);
    aRsPiiObject.SetAddonly(aAdd);
    aRsPiiObject.SetReplaceSig(aCfgObject.GetIndicationType()); 

    // NOTE:  The code isn't exactly the cleanest for writing down the signal to TSPII
    // because the SMTMU needed the Sfp Routing Information and Signla Type on the same call.
    // It works because the SetSfpRouteAndSignalType (SMTMU) and SetSignalType (all other cards)
    // are mutually exclusive. In simulation, however, both are called.  Therefore,
    // this ordering is used so that the proper value is written during AutoRateLock.
    //   
    // Update Signal Type and the device info for SFP routing
    aRsPiiObject.SetSfpRouteAndSignalType(aCfgObject.GetDeviceInSfpRoute(), aCfgObject.GetCrossoverInSfpRoute(), aCfgObject.GetSignalType(), aCfgObject.GetClockType());
    //
    // Configure the signal type from the auto rate lock down if the feature is enabled
    // Otherwise, send down the signal type information that was configured from Agent.
    if(aAutoRateLock && aAutoRateLock->GetLockState() != CFG_RATE_DISABLED)
    {
        aRsPiiObject.SetSignalType(aAutoRateLock->GetSignalType());               
        aRsPiiObject.SetAutoRateLockActive(true);               
    }
    else
    {
        aRsPiiObject.SetSignalType(aCfgObject.GetSignalType());
        aRsPiiObject.SetAutoRateLockActive(false);
    }

    aRsPiiObject.SetInterPacketGap(aCfgObject.GetInterPacketGap());

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();


    return NULL;

}
	

