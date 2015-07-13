// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_OptAutomaticAction.h"
#include "../CFG_Opt.h"
#include "../CFG_OptAutomatic.h"
#include "../CFG_AppIf.h"
#include "../CFG_HoldOffTimer.h"
#include "../CFG_Evc.h"
#include "../CFG_EvcAutomatic.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_RsDefects.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>
#include <ITS/ITS_ConfigOnTrn.h>
#include <ITS/ITS_Region.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <CsPii/CSPII_CardIF.h>


CFG_OptAutomaticAction::CFG_OptAutomaticAction(CFG_AppIf& theOutgoingOptLayerIf,
                                               CFG_AppIf* theOptOtherSideCfgApp,
                                               MON_AppIf* theRsMonApp,
                                               MON_AppIf* theRsOtherSideMonApp,
                                               MON_AppIf* theInternalMonApp,
                                               MON_AppIf* theMsOtherSideMonApp,
                                               MON_AppIf* theGfpMonApp,
                                               ITS_ConfigRegionOnTrn* theItsConfigRegion,
                                               CFG_AppIf* theEvcCfgApp,
                                               CT_IntfId  theIntfId,
                                               bool       theAllowNoOppositeSide):
    CFG_HwRefreshAction(theOutgoingOptLayerIf),
    myOptOtherSideCfgApp(theOptOtherSideCfgApp),
    myAllowNoOtherSide(theAllowNoOppositeSide),
    myRsMonApp(theRsMonApp),
    myRsOtherSideMonApp(theRsOtherSideMonApp),
    myInternalMonApp(theInternalMonApp),
    myMsOtherSideMonApp(theMsOtherSideMonApp),
    myGfpMonApp(theGfpMonApp),
    myItsConfigRegion(theItsConfigRegion),
    myEvcCfgApp(theEvcCfgApp),
    myUseOnlyLosForNEALS(false),
    myIntfId(theIntfId)
{
    // register about config changes or defect changes
	GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());
    if (myOptOtherSideCfgApp)
    {
        GetBbAction()->AddInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
    }
    if (myRsMonApp) 
    {
        GetBbAction()->AddInputRegion(myRsMonApp->GetDefectsRegion());
    }
    if (myRsOtherSideMonApp) 
    {
        GetBbAction()->AddInputRegion(myRsOtherSideMonApp->GetDefectsRegion());
    }
    if (myInternalMonApp) 
    {
        GetBbAction()->AddInputRegion(myInternalMonApp->GetDefectsRegion());
    }
    if (myMsOtherSideMonApp) 
    {
        GetBbAction()->AddInputRegion(myMsOtherSideMonApp->GetDefectsRegion());
    }
    if (myGfpMonApp) 
    {
        GetBbAction()->AddInputRegion(myGfpMonApp->GetDefectsRegion());
    }
    if (myItsConfigRegion)      
    {
        GetBbAction()->AddInputRegion(myItsConfigRegion);
    }
    if (myEvcCfgApp) 
    {
        GetBbAction()->AddInputRegion(myEvcCfgApp->GetAutomaticCfgRegion());
    }

    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());  
    
    // Use Link Fail defect for NEALS on the SSM family
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {   
        if (aCardContext->GetCardFamily() == SSM_FAM) 
        {
            myUseOnlyLosForNEALS = true;
        }
    } // if (aCardContext) 
}

CFG_OptAutomaticAction::~CFG_OptAutomaticAction()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myOptOtherSideCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myOptOtherSideCfgApp->GetCfgRegion()); 
    }
    if (myRsMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myRsMonApp->GetDefectsRegion());
    }
    if (myRsOtherSideMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myRsOtherSideMonApp->GetDefectsRegion());
    }
    if (myInternalMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myInternalMonApp->GetDefectsRegion());
    }
    if (myMsOtherSideMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myMsOtherSideMonApp->GetDefectsRegion());
    }
    if (myGfpMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myGfpMonApp->GetDefectsRegion());
    }
    if (myItsConfigRegion)      
    {
        GetBbAction()->RemoveInputRegion(myItsConfigRegion);
    }
    if (myEvcCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myEvcCfgApp->GetAutomaticCfgRegion());
    }
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_OptAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{
    
    UpdateObject(theRunReason);

    return NULL;
}

void CFG_OptAutomaticAction::UpdateObject(unsigned theRunReason)
{
    bool hasChanged = false;
    bool aConsiderOppositeSide = false;
    bool aConsiderLock = false;
    bool aNearEndAlsActive = false;
    bool aLSPActive = false;
    bool aForceFefi               = false;
    bool aConsiderIncomingDefects = false;
    bool aConsiderInternalDefects = false;


    bool aRsOtherSideLayerLocked  = false;
    bool aRsOtherSideLayerDefects = false;

    bool aInternalLayerDefects = false;
    bool aInternalLayerLocked = false;
    bool aGfpLayerDefects = false;
    bool aMsOtherSideLayerDefects = false;

    // Indicates that the ALS Condition is active (ALS could be set)
    bool aAlsConditionActive = false;
    // Indicates to set the ALS Condition (when condition is active
    // and after holdoff timer has expired).  A base class method 
    // determines this value.
    bool aSetAlsActive = false;
    // The Current Configured Hold Off Delay
    uint32 aCfgAlsHoldOffDelay;

    CFG_OptAutomatic& aOptAutomaticConfig      = static_cast<CFG_OptAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    CFG_Opt&          aOptConfig               = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]);

    //Get the current configured holdoff delay
    aCfgAlsHoldOffDelay = aOptConfig.GetAlsHoldOffDelay();

    // Determine if Line Side Protection is active 
    // from information stored in ITS Config Region
    if (myItsConfigRegion)      
    {       
        if (myItsConfigRegion->IsValid()) 
        {
            ITS_ConfigOnTrn& aItsConfig = (*myItsConfigRegion)[0];
            aLSPActive = (aItsConfig.GetInfo(ITS_LSP) || aItsConfig.GetInfo(ITS_LSP_OTNM));

            //If line side protection is configured, add a line side protection holdoff value
            //to the configured timer to give enough time for the protection switch to happen prior
            //to any action by CFG.
            if (aLSPActive)
                aCfgAlsHoldOffDelay = aCfgAlsHoldOffDelay + LINE_SIDE_PROTECTION_HOLDOFF;
        }   
    }

    // Update Line Side Prot Exists accordingly in the automatic config region
    hasChanged |= aOptAutomaticConfig.SetLineSideProtExists(aLSPActive);

    // TEMP = make this a state variable that is configured
    myAllowNoOtherSide = true;

    // Determine ALS (Automatic Laser Shutdown)
    // and Near End ALS
    //
    // Note:  Either need other side Rs Mon layer  
    //        OR both this sides Ms Mon and Gfp Mon layers.
    // Note 2: HGTM does not have Gfp, so allow Rs to takes its place
    if ( myRsMonApp && 
        (myOptOtherSideCfgApp || myAllowNoOtherSide) && 
        (myRsOtherSideMonApp  || myInternalMonApp)   )
    {
        MON_RsDefects& aRsDefects             = static_cast<MON_RsDefects&>((*myRsMonApp->GetDefectsRegion())[0]); 
    
        // Automatically shutdown laser if :
        // 1- Other side in defects (including Internal AIS) and other side not in terminal loopback and current side not in facility loopback
        // 2- Other side locked and other side not in terminal loopback and current side not in facility loopback
        // 3- Current side is locked and not in facility loopback and not in terminal loopback
        aConsiderLock            = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aOptConfig.GetFacilityLoopBackEnable());

        // For forcing FEFI based on LOS, which is taken from RS (see Rdi in Rs Automatic Action)
        aConsiderIncomingDefects = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aLSPActive);
        // For Forcing FEFI from internal defects (see Generic Layer fail in Gfp Automatic Action)
        aConsiderInternalDefects = (!aOptConfig.GetFacilityLoopBackEnable());

        // Also, if any PRBS BER Testing is turned on, don't set ALS 
        // Do this by setting both ConsiderOppositeSide and ConsiderLoock to false
        if (aOptConfig.GetPrbsRxEnable() || aOptConfig.GetPrbsTxEnable()) 
        {
            aConsiderOppositeSide = false;
            aConsiderLock         = false;
            aConsiderIncomingDefects = false;
            aConsiderInternalDefects = false;
        }

        if (myOptOtherSideCfgApp) 
        {
            CFG_Opt&       aOptOtherSideConfig    = static_cast<CFG_Opt&>((*myOptOtherSideCfgApp->GetCfgRegion())[0]);

            aConsiderOppositeSide = (!aOptOtherSideConfig.GetTerminalLoopBackEnable()) && (!aOptConfig.GetFacilityLoopBackEnable());

            if (aOptOtherSideConfig.GetPrbsRxEnable() || aOptOtherSideConfig.GetPrbsTxEnable()) 
            {
                aConsiderOppositeSide = false;
                aConsiderLock         = false;
                aConsiderIncomingDefects = false;
                aConsiderInternalDefects = false;
            }
        }
        else if (myAllowNoOtherSide) 
        {
            aConsiderOppositeSide = true;
        }


        uint32 aDefectCount     = 0L;
        bool aDefectState       = false;

        // Determine Force Fefi (moved from Mac/Gfp Layer)
        // This can either be forced from a lock or LOS 
        // or from receiving a CSF-FEFI when FEFI Propagation is on.
        // Note:  the CSF-FEFI case is checked in the next segment.
        aForceFefi |= aRsDefects.IsLayerLocked() && aConsiderLock;

        // Removed in 6.1F2 due to customer (Verizon) request 
        //if (aRsDefects.IsConnectedAsSrc()) 
        //{
        //    // Also force FEFI when there is LOS, but only if we are receiving a signal
        //    aRsDefects.GetDefectStatus(CT_TEL_RS_LOS_DEFECT, &aDefectCount, &aDefectState);
        //    aForceFefi |= aDefectState && aConsiderIncomingDefects;
        //}

        if (myGfpMonApp) 
        { 
            uint16 aGfpIdx = CT_TEL_INVALID_VCG_IDX; 
            if (myEvcCfgApp)
            {
                CFG_EvcAutomatic& aEvcAutoConfig = static_cast<CFG_EvcAutomatic&>((*myEvcCfgApp->GetAutomaticCfgRegion())[0]);
                aGfpIdx = aEvcAutoConfig.GetGfpIdx(myIntfId);
            }
            else
            {
                aGfpIdx = 0;
            }
                
            // Check if we have a valid VCG index. A valid VCG index will be found, if we have
            // an ETH facility as part of the EVC or the normal Gfp region with one instance is used.
            if (aGfpIdx != CT_TEL_INVALID_VCG_IDX)
            {
                // Check if Gfp Layer has defects.
                // If present, treat like defects from the RS layer.
                MON_Defects& aGfpDefects = static_cast<MON_Defects&>((*myGfpMonApp->GetDefectsRegion())[aGfpIdx]); 
                aGfpLayerDefects = aGfpDefects.IsLayerInDefects();

                // Special processing to not turn off laser on CSF-LOSYNC.
                // otherwise, just use the layer in defects from above
                if (aOptConfig.GetIgnoreCsfLOSyncFlag()) 
                {
                    uint32 aCsfLosCount = 0,   aLOFDCount=0,     aUpperLayerInternalFailTACount = 0;  
                    bool   aCsfLosState=false, aLOFDState=false, aUpperLayerInternalFailTAState=false;  
                    aGfpDefects.GetDefectStatus(CT_TEL_GFP_CSF_LOS_DEFECT, &aCsfLosCount, &aCsfLosState);
                    aGfpDefects.GetDefectStatus(CT_TEL_GFP_LOFD_DEFECT,    &aLOFDCount,   &aLOFDState);
                    aGfpDefects.GetDefectStatus(CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, &aUpperLayerInternalFailTACount, &aUpperLayerInternalFailTAState);
                    // Should match MON GfpDefects.IsLayerInDefects() without the LOSync 
                    aGfpLayerDefects = (aLOFDState || aCsfLosState || aUpperLayerInternalFailTAState);
                }

                // Need different behavior for handling CSF-FEFI and forcing FEFI depending
                // on the state of the PROP_FEFI flag.
                aGfpDefects.GetDefectStatus(CT_TEL_GFP_CSF_FEFI_DEFECT, &aDefectCount, &aDefectState);
                if (aOptConfig.GetPropFefiEnabled()) 
                {
                    // a. If PROP_FEFI is ON, then force FEFI when CSF-FEFI is present or
                    //    when the GFP layer is failed.
                    aForceFefi |= ((aDefectState || aGfpDefects.IsLayerForMaintSigInDefects()) && aConsiderInternalDefects);
                }
                else
                {
                    // b. Else (PROP_FEFI is OFF), then fail the layer if the CSF_FEFI defect is present.                
                    aGfpLayerDefects |= aDefectState;
                }
            }  // if (aGfpIdx != CT_TEL_INVALID_VCG_IDX)
        }  // if (myGfpMonApp) 

        // Now Set Force Fefi, which doesn't have the HoldOff Timer
        hasChanged |= aOptAutomaticConfig.SetForceFefi(aForceFefi);


        // If we have myInternalMonApp, then check that for internal defects/lock also.
        if (myInternalMonApp) 
        { 
            // In 7.1, CSF-OPU defect is added in the Rs layer.
            // This does not fail the layer because we don't want maintenance signaling, 
            // but we do want it shut off the laser for ALS.
            // Since we always have the Rs layer, we can check that easily enough
            // For some cards (i.e., HGTM) that don't have an MS layer, the
            // Rs layer will also be the Internal MON App and the internal defects,
            // so those generic calls are only made once.
            aDefectCount   = 0L;
            aDefectState   = false;

            aRsDefects.GetDefectStatus(CT_TEL_RS_INTERNAL_CSF_OPU_DEFECT, &aDefectCount, &aDefectState);
            aInternalLayerDefects |= aDefectState;

            // Also check INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER in the same manner
            // and Interanl CSF-OPU.  It shuts off the laser, but does not fail the layer
            aRsDefects.GetDefectStatus(CT_TEL_RS_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, &aDefectCount, &aDefectState);
            aInternalLayerDefects |= aDefectState;

            // Also check CT_TEL_RS_INTERNAL_GENAIS_DEFECT in the same manner
            // as Interanl CSF-OPU.  It shuts off the laser, but does not fail the layer
            aRsDefects.GetDefectStatus(CT_TEL_RS_INTERNAL_GENAIS_DEFECT, &aDefectCount, &aDefectState);
            aInternalLayerDefects |= aDefectState;

            //
            // Check if Internal AIS Defect, which is in the Ms Layer.
            // If present, treat like any other side (RS) defect
            MON_Defects& aInternalDefects = static_cast<MON_Defects&>((*myInternalMonApp->GetDefectsRegion())[0]); 
            aInternalLayerDefects |= aInternalDefects.IsLayerInternalInDefects();
            aInternalLayerLocked  |= aInternalDefects.IsLayerInternalLocked();
        }
         

        // For 4.0.5 (End to End Circuit LOS), only conside the Ms (Line) layer
        // of the other side if it is present and the Maintenance Propagation is set to ALS
        if ((myMsOtherSideMonApp) && (aOptConfig.GetMaintPropMode() == CT_TEL_MAINT_PROP_ALS))
        { 
            //
            // Check if Other Side Ms Layer has defects.
            // If present, treat like defects from the RS layer.
            MON_Defects& aMsOtherSideDefects = static_cast<MON_Defects&>((*myMsOtherSideMonApp->GetDefectsRegion())[0]); 
            aMsOtherSideLayerDefects = aMsOtherSideDefects.IsLayerForMaintSigInDefects();
        }


        // Determine Near End ALS, which doesn't have the HoldOff Timer
        if (myUseOnlyLosForNEALS)
        {
            // For Near End ALS on SSM (and some other new cards), 
            // need to only check LOS.
            uint32 aRsLosCount=0;
            bool   aRsLosState = false;
            aRsDefects.GetDefectStatus(CT_TEL_RS_LOS_DEFECT, &aRsLosCount, &aRsLosState);
            aNearEndAlsActive     = (aRsLosState) && aConsiderLock;        
        }
        else
        {
            // Normal Processing
            aNearEndAlsActive     = aRsDefects.IsLayerInDefects() && aConsiderLock;        
        }
        hasChanged |= aOptAutomaticConfig.SetNearEndAutomaticLaserShutdown(aNearEndAlsActive);


        // Change for SMTMU ALS because on SMTMU port side, the selected line side
        // may come from multiple sources.  Therefore, look at internal signals 
        // (this sides Ms and Gfp Mon layers) and don't check other side mon layers,
        // which won't be passed in (pointers will be NULL).
        if (myRsOtherSideMonApp) 
        { 
            //
            // Check if Other Side Ms Layer has defects.
            // If present, treat like defects from the RS layer.
            MON_Defects& aRsOtherSideDefects = static_cast<MON_Defects&> ((*myRsOtherSideMonApp->GetDefectsRegion())[0]);
            aRsOtherSideLayerDefects = aRsOtherSideDefects.IsLayerInDefects();
            aRsOtherSideLayerLocked  = aRsOtherSideDefects.IsLayerLocked();
        }

        
        // First determine if the ALS condition is active
        aAlsConditionActive = (aGfpLayerDefects || aInternalLayerDefects || aInternalLayerLocked || aMsOtherSideLayerDefects || aRsOtherSideLayerDefects || aRsOtherSideLayerLocked) && aConsiderOppositeSide;
        aAlsConditionActive |= aRsDefects.IsLayerLocked() && aConsiderLock;

        // Use ApplyConditionAfterHoldoff method to check if the Condition found
        // should be applied based on the HoldOff Timer (Delay)
        bool aHoldoffTimerActive = false;
        CFG_HoldOffTimer* aTimer = GetCfgIf().GetHoldOffTimer();
        if (aTimer) 
        {
            aSetAlsActive = aTimer->ApplyConditionAfterHoldoff(aAlsConditionActive, aHoldoffTimerActive, aCfgAlsHoldOffDelay);
        }
        else
        {
            aSetAlsActive = aAlsConditionActive;
        }

        // Update the Automatic Config Region with the results of this fine code.
        hasChanged |= aOptAutomaticConfig.SetAutomaticLaserShutdown(aSetAlsActive);

        
    } // if (myOptOtherSideCfgApp && myRsMonApp && myRsOtherSideMonApp)


    


    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }
}




