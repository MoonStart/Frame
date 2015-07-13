// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_RsAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_HoldOffTimer.h"
#include "../CFG_Rs.h"
#include "../CFG_RsAutomatic.h"
#include "../CFG_Evc.h"
#include "../CFG_EvcAutomatic.h"
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_GfpDefects.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>

CFG_RsAutomaticAction::CFG_RsAutomaticAction(CFG_AppIf& theCfgIf,
                                             MON_AppIf* theRsMonApp,
                                             MON_AppIf* theRsOtherSideMonApp,
                                             CFG_AppIf* theOptCfgApp,
                                             CFG_AppIf* theOptOtherSideCfgApp,
                                             MON_AppIf* theMsMonApp,
                                             CFG_AppIf* theMsProtCfgApp,
                                             MON_AppIf* theMsOtherSideMonApp,
                                             MON_AppIf* theGfpMonApp,
                                             CFG_AppIf* theEvcCfgApp,
                                             CT_IntfId  theIntfId,
                                             bool       theAllowNoOppositeSide):
    CFG_HwRefreshAction(theCfgIf),
    myRsMonApp(theRsMonApp),
    myRsOtherSideMonApp(theRsOtherSideMonApp),
    myOptCfgApp(theOptCfgApp),
    myAllowNoOtherSide(theAllowNoOppositeSide),
    myOptOtherSideCfgApp(theOptOtherSideCfgApp),
    myMsMonApp(theMsMonApp),
    myMsProtCfgApp(theMsProtCfgApp),
    myMsOtherSideMonApp(theMsOtherSideMonApp),
    myGfpMonApp(theGfpMonApp),
    myEvcCfgApp(theEvcCfgApp),
    myIntfId(theIntfId),
    myMsMFacMonApp(NULL),
    myMFacIntfId(CT_INTF_ID_UNKNOWN)    
{ 
    GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());

    // register about config changes or defect changes
    if (myRsMonApp) 
    {
        GetBbAction()->AddInputRegion(myRsMonApp->GetDefectsRegion());
    }
    if (myRsOtherSideMonApp) 
    {
        GetBbAction()->AddInputRegion(myRsOtherSideMonApp->GetDefectsRegion());
    }
    if (myOptCfgApp) 
    {
        GetBbAction()->AddInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->AddInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }
    if (myOptOtherSideCfgApp) 
    {
        GetBbAction()->AddInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
        GetBbAction()->AddInputRegion(myOptOtherSideCfgApp->GetAutomaticCfgRegion());
    }
    if (myMsMonApp) 
    {
        GetBbAction()->AddInputRegion(myMsMonApp->GetDefectsRegion());
    }
    if (myGfpMonApp) 
    {
        GetBbAction()->AddInputRegion(myGfpMonApp->GetDefectsRegion());
    }
    if (myEvcCfgApp) 
    {
        GetBbAction()->AddInputRegion(myEvcCfgApp->GetAutomaticCfgRegion());
    }
    if (myMsOtherSideMonApp) 
    {
        GetBbAction()->AddInputRegion(myMsOtherSideMonApp->GetDefectsRegion());
    }
    if (myMsProtCfgApp) 
    {
        GetBbAction()->AddInputRegion(myMsProtCfgApp->GetProtCfgRegion());
    }

  	GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_RsAutomaticAction::~CFG_RsAutomaticAction()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());

    if (myRsMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myRsMonApp->GetDefectsRegion());
    }
    if (myRsOtherSideMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myRsOtherSideMonApp->GetDefectsRegion());
    }
    if (myOptCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }
    if (myOptOtherSideCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
        GetBbAction()->RemoveInputRegion(myOptOtherSideCfgApp->GetAutomaticCfgRegion());
    }
    if (myMsMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myMsMonApp->GetDefectsRegion());
    }
    if (myGfpMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myGfpMonApp->GetDefectsRegion());
    }
    if (myEvcCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myEvcCfgApp->GetAutomaticCfgRegion());
    }
    if (myMsOtherSideMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myMsOtherSideMonApp->GetDefectsRegion());
    }
    if (myMsProtCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myMsProtCfgApp->GetProtCfgRegion());
    }

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_RsAutomaticAction::Process(unsigned theRunReason,
                                          FC_Object* theInvokerObj,
                                          FC_Object* theParam)
{
    bool aConsiderOppositeSideForExternalSignaling = false;
    bool aConsiderLockForExternalSignaling = false;
    bool aConsiderLockForInternalSignaling = false;
    bool aConsiderDefectsForInternalSignaling = false;
    bool aForceAis = false;
    bool aForceInternalAis = false;
    bool aForceRdi = false;
    bool aForceCSFOPUInternal = false;
    uint32 aRsLfDefectCount = 0;
    bool   aRsLfDefectState = false;
    uint32 aRsIntGenAISDefectCount = 0;
    bool   aRsIntGenAISDefectState = false;
    uint32 aMsAisDefectCount = 0;
    bool   aMsAisDefectState = false;
    uint32 aMsPropInternalAISLDefectCount = 0;
    bool   aMsPropInternalAISLDefectState = false;
    uint32 aMsInternalAISLDefectCount = 0;
    bool   aMsInternalAISLDefectState = false;
    bool   aInternalLayerDefects = false;
    bool   aInternalLayerLocked = false;
    bool   aGfpLayerDefects = false;
    bool   aDisableSignaling = false;
    uint32 aHoldOffDelay = CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO;
    uint32 aAltHoldOffDelay = CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO;
	bool   aLSPActive = false;
    bool   aSetForceTASignalingActive = false;
    bool   aSetAltForceTASignalActive = false;
    bool   aSuppressBackwardInd = false;
    bool   aDrop = false;
    bool   aAdd  = false;
    CT_RS_IndicationType anAutoIndicationType  = CT_RS_INDICATION_UNKNOWN;
    CT_RS_IndicationType anAutoInternalIndType = CT_RS_INDICATION_UNKNOWN;
    uint32 aGfpCsfRdiDefectCount = 0;
    bool   aGfpCsfRdiDefectState = false;

    


    CT_IntfId  aRetrieveIntfId = CT_INTF_ID_UNKNOWN;
    CFG_RsAutomatic& aAutomaticCfgObject  = static_cast<CFG_RsAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    CFG_Rs&          aRsConfig           = static_cast<CFG_Rs&>((*GetCfgIf().GetCfgRegion())[0]);


    if (myOptCfgApp)
    {
        CFG_Opt& aOptConfig              = static_cast<CFG_Opt&>((*myOptCfgApp->GetCfgRegion())[0]);
        CFG_OptAutomatic& aOptAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptCfgApp->GetAutomaticCfgRegion())[0]);

        aLSPActive = aOptAutoConfig.GetLineSideProtExists();

        // Get HoldOffDelay in CFG Opt for ALS to use later in the method
        // to hold off forcing AIS-L
        // Delay TDTC maintenance signal insertion, the default is 0
        aHoldOffDelay = aOptConfig.GetAlsHoldOffDelay() + aOptConfig.GetMaintSigDelay();
        aAltHoldOffDelay = aOptConfig.GetAlsHoldOffDelay();

        aConsiderLockForExternalSignaling    = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aOptConfig.GetFacilityLoopBackEnable());
        aConsiderLockForInternalSignaling    = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aLSPActive);
        aConsiderDefectsForInternalSignaling = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aLSPActive);

        if (aOptConfig.GetPrbsRxEnable() || aOptConfig.GetPrbsTxEnable())
        {
            aDisableSignaling = true;
        }


        //
        // This section processes RS the signaling related to the facility state and defects
        //
        // Automatically force AIS upstream (external) if:
        // -   ((Facility is not in facility loopback (traffic is looped))    &&
        //      (Facility is not in terminal loopback (traffic is continued)) &&  
        //      (Facility is locked))
        //
        // Automatically force AIS downstream (internal) if:    
        // -   ((Facility is not in terminal loopback (traffic is looped))    &&
        //      (Facility is not in Line Side Protection)                     &&
        //      (Facility is locked)) 
        // -   ((Facility is not in terminal loopback (traffic is looped))    &&
        //      (Facility is not in Line Side Protection)                     &&
        //      (Facility is defective))
        //
        if (myRsMonApp) 
        {   
            MON_RsDefects& aRsDefects = static_cast<MON_RsDefects&>((*myRsMonApp->GetDefectsRegion())[0]);
            // Add checks for internal layer in defects and internal layer lock that used to be done in Ms layer
            // This will help in case some future cards do not have the Ms layer.
            aInternalLayerDefects = aRsDefects.IsLayerInternalForMaintSigInDefects();
            aInternalLayerLocked  = aRsDefects.IsLayerInternalLocked(); 
            aForceAis = (aRsDefects.IsLayerLocked() || aInternalLayerDefects || aInternalLayerLocked) && aConsiderLockForExternalSignaling; 
            
            // When GEN AIS is detected and the indication type is AIS, forcing AIS 
            // will be turned to on too.
            if (aRsConfig.GetIndicationType() == CT_RS_INDICATION_AIS)
            {
                aRsDefects.GetDefectStatus(CT_TEL_RS_INTERNAL_GENAIS_DEFECT, &aRsIntGenAISDefectCount, &aRsIntGenAISDefectState);
                aForceAis |= (aRsIntGenAISDefectState) && aConsiderOppositeSideForExternalSignaling;
            }

            aForceInternalAis = aRsDefects.IsLayerLocked() && aConsiderLockForInternalSignaling;
            aForceInternalAis |= aRsDefects.IsLayerForMaintSigInDefects() && aConsiderDefectsForInternalSignaling;

            // Determine whether to send CSF-OPU Internal based on the Rs layer (lock, layer fail, or LF defect)
            aRsLfDefectState = aRsDefects.GetDefectForMaintSig(CT_TEL_RS_LOCAL_FAULT_DEFECT);
            aForceCSFOPUInternal =  aRsDefects.IsLayerLocked() && aConsiderLockForInternalSignaling;
            aForceCSFOPUInternal |= (aRsDefects.IsLayerForMaintSigInDefects() || aRsLfDefectState) && aConsiderDefectsForInternalSignaling;

            // Determine if this is a one-way cross connect with the direction of traffic being
            // toward the interior of the card (to the other side of the card).  In this case, 
            // we will supress backward indicators.
            aSuppressBackwardInd = (aRsDefects.IsConnectedAsDst() && (!aRsDefects.IsConnectedAsSrc()));

            //Set 1 Way Drop XC.
            aDrop = (aRsDefects.IsConnectedAsDst() && (!aRsDefects.IsConnectedAsSrc()));

            //Set 1 Way Add XC
            aAdd = (!aRsDefects.IsConnectedAsDst() && (aRsDefects.IsConnectedAsSrc()));

            myAllowNoOtherSide = true;
            aConsiderOppositeSideForExternalSignaling = false;
            if (myOptOtherSideCfgApp) 
            {        
                CFG_Opt& aOptOtherSideConfig              = static_cast<CFG_Opt&>((*myOptOtherSideCfgApp->GetCfgRegion())[0]); 
                CFG_OptAutomatic& aOptOtherSideAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptOtherSideCfgApp->GetAutomaticCfgRegion())[0]);

                aLSPActive |= aOptOtherSideAutoConfig.GetLineSideProtExists();

                aConsiderOppositeSideForExternalSignaling = (!aOptOtherSideConfig.GetTerminalLoopBackEnable()) && 
                                                            (!aOptConfig.GetFacilityLoopBackEnable());
            }
            else if (myAllowNoOtherSide)             
            {
                // when there is nothing there, consider opposite side based on facility loopback
                aConsiderOppositeSideForExternalSignaling = (!aOptConfig.GetFacilityLoopBackEnable());
            }

            if (myMsMonApp) 
            { 
                // Since we don't terminate the Ms layer, we want to allow AIS (in both directions)
                // to pass through.  However for some cards (i.e., the SMTMU), there is a proprietary AIS.
                // For that special, we have to force AIS.  
                // For this reason, the code will not check the generic IsLayerInternalInDefects and 
                // IsLayerInDefects methods, but rather check specific defects for whether 
                // to force AIS and internal AIS.
                // 
              
                // For forcing AIS, check if the Ms layer has Proprietary Internal AIS defect 
                // Note: the Upper Layer Internal Fail and Internal Layer Locked are checked 
                // by the Rs layer above (assuming Rs is always the upper layer of Ms).
                MON_Defects& aMsDefects = static_cast<MON_Defects&>((*myMsMonApp->GetDefectsRegion())[0]); 
                aMsDefects.GetDefectStatus(CT_TEL_MS_PROPRIETARY_INTERNAL_AISL_DEFECT,  &aMsPropInternalAISLDefectCount, &aMsPropInternalAISLDefectState);
                aForceAis |= (aMsPropInternalAISLDefectState) && aConsiderOppositeSideForExternalSignaling;

                // When internal AIS detected and the indication type is GEN-AIS, forcing AIS 
                // will be turned to on too.
                if (aRsConfig.GetIndicationType() == CT_RS_INDICATION_PN11AIS)
                {
                    aMsDefects.GetDefectStatus(CT_TEL_MS_INTERNAL_AISL_DEFECT,  &aMsInternalAISLDefectCount, &aMsInternalAISLDefectState);
                    aForceAis |= (aMsInternalAISLDefectState) && aConsiderOppositeSideForExternalSignaling;
                }

                //
                // Only want to force internal AIS-L for MS AIS when the internal
                // indication is set to AIS PROPRIETARY.  In this case, we are setting 
                // special bits in the overhead for AIS.  For other cases, the AIS should
                // pass through.  Note that internal AIS is set above for Rs Layer defects. 
                // Also, force CSF-OPU when Ms Layer is failed and force RDI-L for MS AIS only.
                //
                if (aRsConfig.GetInternalIndType() == CT_RS_INDICATION_AIS_PROPRIETARY)
                {
                    aForceInternalAis |= (aMsDefects.IsLayerForMaintSigInDefects() && aConsiderDefectsForInternalSignaling);
                }
                aForceCSFOPUInternal |= (aMsDefects.IsLayerForMaintSigInDefects() && aConsiderDefectsForInternalSignaling);

                aMsDefects.GetDefectStatus(CT_TEL_MS_AIS_DEFECT, &aMsAisDefectCount, &aMsAisDefectState);
                aForceRdi = (aMsAisDefectState && aConsiderDefectsForInternalSignaling);
            }  // if (myMsMonApp) 

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
                    // Check Gfp layer for internal defects (as was done for Ms layer internla AIS).
                    // If present, treat like any other side (RS) defect and Force AIS
                    // Note: Normally, the Ms layer will be present, so checking the intrnal layer lock
                    // is redundant, but it doesn't hurt and there is a chance the Gfp layer 
                    // may be present without the Ms layer in this action.
                    MON_Defects& aGfpDefects = static_cast<MON_Defects&>((*myGfpMonApp->GetDefectsRegion())[aGfpIdx]);

                    if( aRsConfig.GetIgnoreCsfLosCsfLosyncFlag() )   //Only for HDTG FC8G                    
                    {
                        uint32 aLOFDCount=0,     aUpperLayerInternalFailTACount = 0;  
                        bool   aLOFDState=false, aUpperLayerInternalFailTAState=false;  
                        aGfpDefects.GetDefectStatus(CT_TEL_GFP_LOFD_DEFECT,    &aLOFDCount,   &aLOFDState);
                        aGfpDefects.GetDefectStatus(CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, &aUpperLayerInternalFailTACount, &aUpperLayerInternalFailTAState);
                        // Should match MON GfpDefects.IsLayerInDefects() without the LOSync and LOS
                        aGfpLayerDefects = (aLOFDState || aUpperLayerInternalFailTAState);                            
                    }
                    else
                    {
                        aGfpLayerDefects      = aGfpDefects.IsLayerForMaintSigInDefects();
                    }
                    aInternalLayerLocked  = aGfpDefects.IsLayerInternalLocked();
                    aForceAis |= (aGfpLayerDefects || aInternalLayerLocked) && aConsiderOppositeSideForExternalSignaling;

                    // Set Indication Type to RF (as override) for certain signal types
                    // and when the Gfp layer has a CSF-RDI defect
                    // Otherwise, don't set here and let the default type (UNKNOWN) specify
                    // that there is no override.
                    CT_TEL_SignalType aSignalType = aRsConfig.GetSignalType();
                    aGfpCsfRdiDefectState = aGfpDefects.GetDefectForMaintSig(CT_TEL_GFP_CSF_RDI_DEFECT);

                    if ((aSignalType == CT_TEL_SIGNAL_TGLAN_FRAME_STD) &&
                        (aGfpCsfRdiDefectState)) 
                    {
                        anAutoIndicationType = CT_RS_INDICATION_RF;

                        //aForceAis needs to be set to get the RF maintenance signaling to be sent.
                        aForceAis |= aConsiderOppositeSideForExternalSignaling;
                    }
                }  //  if (aGfpIdx != CT_TEL_INVALID_VCG_IDX)
            }  // if (myGfpMonApp)
        }
    
    
        //
        // This section processes the RS signaling related to the opposite facility state and defects
        // 
        // NOTE: The assumption here is that myRsMonApp is not NULL and therefor will have already 
        // processed defects on its own side (i.e., myMsMonApp and myGfpMonApp).  
        // 
        // Automatically force AIS upstream (external) if:
        // -   ((Facility is not in facility loopback (traffic is looped))           &&
        //      (Opposite facility is not in terminal loopback (traffic is looped))  &&
        //      (Opposite facility is not in Line Side Protection)                   &&
        //      ((Opposite facility is locked) || (Opposite facility is defective)))
        //
        aConsiderOppositeSideForExternalSignaling = false;
        if (myOptOtherSideCfgApp && myRsOtherSideMonApp)
        {
            CFG_Opt& aOptOtherSideConfig              = static_cast<CFG_Opt&>((*myOptOtherSideCfgApp->GetCfgRegion())[0]);
            CFG_OptAutomatic& aOptOtherSideAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptOtherSideCfgApp->GetAutomaticCfgRegion())[0]);

            aLSPActive |= aOptOtherSideAutoConfig.GetLineSideProtExists();

            aConsiderOppositeSideForExternalSignaling = (!aOptOtherSideConfig.GetTerminalLoopBackEnable()) && 
                                                        (!aOptConfig.GetFacilityLoopBackEnable());

            if (aOptOtherSideConfig.GetPrbsRxEnable() || aOptOtherSideConfig.GetPrbsTxEnable())
            {
                aDisableSignaling = true;
            }

            // The code for checking MsOtherSide is removed in 7.1 to allow AIS to pass through
            // because we are not terminating the MS layer. 
            // Note: Below we checking aRsOtherSideDefects so there is no reason to check 
            // the upper layer failures of MsOtherSide (assume Rs is always the upper layer of Ms).  
            //if (myMsOtherSideMonApp) 
            //{ 
            //    ...
            //}

            MON_Defects& aRsOtherSideDefects = static_cast<MON_Defects&>((*myRsOtherSideMonApp->GetDefectsRegion())[0]); 

            aForceAis |= (aRsOtherSideDefects.IsLayerForMaintSigInDefects() || aRsOtherSideDefects.IsLayerLocked()) && 
                          aConsiderOppositeSideForExternalSignaling;
        }
    }

    // Special code for M facility lock propagation
    if (myMsProtCfgApp)
    {
        CFG_MsProt& aMsProtConfig = static_cast<CFG_MsProt&>((*myMsProtCfgApp->GetProtCfgRegion())[0]);

        // Check if this facility is connected with an M facility 
        // (Retrieved Interface ID will not be CT_INTF_ID_UNKNOWN)
        aRetrieveIntfId = aMsProtConfig.GetMateIntfId();

        // If the M Facility Interface ID has changed (old ID disconnected), 
        // then remove the input region
        if (aRetrieveIntfId != myMFacIntfId) 
        {
            // Set the class variable to the Retrieved Interface Id
            myMFacIntfId = aRetrieveIntfId;
            // Remove the input region and reset the myMsMFacMonApp class variable
            if (myMsMFacMonApp) 
            {
                GetBbAction()->RemoveInputRegion(myMsMFacMonApp->GetDefectsRegion());
                myMsMFacMonApp = NULL;
            }

        } // if (aRetrieveIntfId != myMFacIntfId)


        // Look for lock propagation only when an M facility is connected
        if (myMFacIntfId != CT_INTF_ID_UNKNOWN)
        {
            // Check to see if there is a M Facility Ms Mon Application already
            // (based on the myMsMFacMonApp class variable).
            // If there is not, then use it to add the input region
            if (myMsMFacMonApp == NULL) 
            {
                T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
                if (aCardContext)
                {
                    MON_AppIf* aMsMFacMonApp = &(aCardContext->GetMsIf().GetMonPortSideApp(myMFacIntfId)); 
                    // Add the input region and set the myMsMFacMonApp class variable
                    if (aMsMFacMonApp) 
                    {
                        GetBbAction()->AddInputRegion(aMsMFacMonApp->GetDefectsRegion());
                        myMsMFacMonApp = aMsMFacMonApp;
                    }
                }

            } // if (myMsMFacMonApp == NULL)

            if (myMsMFacMonApp) 
            {
                // Now retrieve the defects to see if any action is needed
                MON_Defects& aMsMFacDefects = static_cast<MON_Defects&>((*myMsMFacMonApp->GetDefectsRegion())[0]); 
                aForceInternalAis |= (aMsMFacDefects.IsLayerLocked());
            } // if (myMsMFacMonApp)
    
        }  // if (myMFacIntfId != CT_INTF_ID_UNKNOWN)

    }  // if (myMsProtCfgApp)

    //If line side protection is configured, add a line side protection holdoff value
    //to the configured timer to give enough time for the protection switch to happen prior
    //to any action by CFG.
    if (aLSPActive)
    {
        aHoldOffDelay = aHoldOffDelay + LINE_SIDE_PROTECTION_HOLDOFF;
        aAltHoldOffDelay = aAltHoldOffDelay + LINE_SIDE_PROTECTION_HOLDOFF;
    }

    // For Traffic Affecting Maintenance Signlaing (AIS), use ApplyConditionAfterHoldoff 
    // method to check if the Condition found should be applied based on the HoldOff Timer (Delay)
    bool aHoldoffTimerActive = false;
    CFG_HoldOffTimer* aTimer = GetCfgIf().GetHoldOffTimer();
    if (aTimer) 
    {
        aSetForceTASignalingActive = aTimer->ApplyConditionAfterHoldoff(aForceAis, aHoldoffTimerActive, aHoldOffDelay);
    }
    else
    {
        aSetForceTASignalingActive = true;
    }

    // Now check for internal (alternate) direction       
    CFG_HoldOffTimer* aAltTimer = GetCfgIf().GetAltHoldOffTimer();
    if (aAltTimer) 
    {
        aSetAltForceTASignalActive  = aAltTimer->ApplyConditionAfterHoldoff((aForceInternalAis || aForceCSFOPUInternal), aHoldoffTimerActive, aAltHoldOffDelay);
    }
    else
    {
        aSetAltForceTASignalActive  = true;
    }

    // If the aSetForceTASignalingActive is not set, then don't force any maintenance signaling.
    if (!aSetForceTASignalingActive) 
    {
        aForceAis = false;
    }
    if (!aSetAltForceTASignalActive)   
    {
        aForceInternalAis = false;
        aForceCSFOPUInternal = false;
    }

    // Also, if any PRBS BER Testing is turned on, don't force any signaling 
    if (aDisableSignaling)   
    {
        aForceAis = false;
        aForceInternalAis = false;
        aForceCSFOPUInternal = false;
        aForceRdi = false;    
    }

    // Update automatic config object
    // NOTE that we always update notify the region to disbale the force AIS bit that stays on 
    // on 10 gig card. When there is glitches of defects
    //
    aAutomaticCfgObject.SetForceAIS(aForceAis);
    aAutomaticCfgObject.SetForceAISInternal(aForceInternalAis);
    aAutomaticCfgObject.SetForceRDI(aForceRdi);
    aAutomaticCfgObject.SetForceCSFOPUInternal(aForceCSFOPUInternal);
	// Update Line Side Prot Exists accordingly in the automatic config region
    aAutomaticCfgObject.SetLineSideProtExists(aLSPActive);

    aAutomaticCfgObject.SetSuppressBackwardInd(aSuppressBackwardInd);       

    aAutomaticCfgObject.SetDrop(aDrop);
    aAutomaticCfgObject.SetAdd(aAdd);

    aAutomaticCfgObject.SetAutoIndicationType(anAutoIndicationType);
    aAutomaticCfgObject.SetAutoInternalIndType(anAutoInternalIndType);

    GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();

    return NULL;
}


