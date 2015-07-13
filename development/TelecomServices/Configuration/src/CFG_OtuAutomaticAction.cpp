// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_OtuAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbAction.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Defects.h>
#include "../CFG_AppIf.h"
#include "../CFG_OtuAutomatic.h"
#include "../CFG_Rs.h"

CFG_OtuAutomaticAction::CFG_OtuAutomaticAction(CFG_AppIf& theCfgIf,
                                               MON_AppIf& theIncomingMonApp,
                                               CFG_AppIf* theRsPortSideCfgApp,
                                               CFG_AppIf* theOptCfgApp,
                                               MON_AppIf* theRsIncomingMonApp):
    CFG_HwRefreshAction(theCfgIf),
    myRsPortSideCfgApp(theRsPortSideCfgApp),
    myOptCfgApp(theOptCfgApp),
    myRsIncomingMonApp(theRsIncomingMonApp),
    myIncomingMonApp(theIncomingMonApp)
{
	GetBbAction()->AddInputRegion(myIncomingMonApp.GetDefectsRegion());

    if (myRsPortSideCfgApp) 
    {
        GetBbAction()->AddInputRegion(myRsPortSideCfgApp->GetCfgRegion());
    }

    if (myOptCfgApp) 
    {
        GetBbAction()->AddInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->AddInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }

    if (myRsIncomingMonApp) 
    {
        GetBbAction()->AddInputRegion(myRsIncomingMonApp->GetConfigRegion());
    }

	GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_OtuAutomaticAction::~CFG_OtuAutomaticAction()
{
    GetBbAction()->RemoveInputRegion(myIncomingMonApp.GetDefectsRegion());

    if (myRsPortSideCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myRsPortSideCfgApp->GetCfgRegion());
    }

    if (myOptCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }

    if (myRsIncomingMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myRsIncomingMonApp->GetConfigRegion());
    }


    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_OtuAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{
    bool hasChanged = false;
    CFG_OtuAutomatic& aOtuAutomaticConfig = static_cast<CFG_OtuAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    MON_Region& aDefectsRegion  = *myIncomingMonApp.GetDefectsRegion();
    MON_Defects& aDefectsIf = static_cast<MON_Defects&>(aDefectsRegion[0]);

    // In most cases (all line side), the card is Otu Terminating.
    // For Port, it depends on the signal type.  Therefore, should only have 
    // the myRsPortSideCfgApp if it is the Port Side.
    // If the Port Side Cfg App is there, then most signal types are false, 
    // except for the otu/odu signal types.  If one of these, the the port side 
    // is otu terminating as well.
    bool aOtuTerminating = true;
    bool aSuppressBackwardInd = false;
    bool aSuppressAutomaticBackwardInd = false;
    bool aForceBDI = false;
    bool aSendDefectToMate = false;
    bool aLSPActive = false;
    bool aConsiderDefectsForBackwardInd = true;
    bool aDisableSignaling = false;
    bool aMateLineOEORegen = false;
    bool aLoopLineOEORegen = false;

    if (myOptCfgApp)
    {
        CFG_Opt& aOptConfig              = static_cast<CFG_Opt&>((*myOptCfgApp->GetCfgRegion())[0]);
        CFG_OptAutomatic& aOptAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptCfgApp->GetAutomaticCfgRegion())[0]);

		aLSPActive = aOptAutoConfig.GetLineSideProtExists();

        aConsiderDefectsForBackwardInd = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aLSPActive);

        if (aOptConfig.GetPrbsRxEnable() || aOptConfig.GetPrbsTxEnable() ||
            (aOptConfig.GetOEORegenMode() == CT_TEL_OEO_REGEN_LINE_LOOPBACK))
        {
            aDisableSignaling = true;
        }

        if (aOptConfig.GetOEORegenMode() == CT_TEL_OEO_REGEN_LINE_MATE) 
        {
            aMateLineOEORegen = true;
        }

        if (aOptConfig.GetOEORegenMode() == CT_TEL_OEO_REGEN_LINE_LOOPBACK) 
        {
            aLoopLineOEORegen = true;
        }
    }

    if (myRsIncomingMonApp) 
    {
        MON_RsConfig& aRsIncomingMonConfig = static_cast<MON_RsConfig&>((*myRsIncomingMonApp->GetConfigRegion())[0]);

        // Determine if this is a one-way cross connect with the direction of traffic being
        // toward the exterior of the facility (not to the other side of the card).  In this case, 
        // we will supress backward indicators. Note that these methods are based one
        // the reference point at the center of the card.
        // Also, some new line OEO Regen types will affect backward indicators and for the
        // first time, we may want to send backward indicators though software, but suppress
        // automatic BDI/BEI in HW.  Therefore, we have two flags.
        aSuppressBackwardInd = ((aRsIncomingMonConfig.GetIsConnectedAsDst() && (!aRsIncomingMonConfig.GetIsConnectedAsSrc())) || aLoopLineOEORegen);
        aSuppressAutomaticBackwardInd = ((aRsIncomingMonConfig.GetIsConnectedAsDst() && (!aRsIncomingMonConfig.GetIsConnectedAsSrc())) || aMateLineOEORegen  || aLoopLineOEORegen);
    }

    if (myRsPortSideCfgApp) 
    {
        aOtuTerminating = false;
        // Get regions and check Signal Type
        CFG_Rs& aRsPortSideConfig = static_cast<CFG_Rs&>((*myRsPortSideCfgApp->GetCfgRegion())[0]);

        CT_TEL_SignalType aRsPortSignalType = aRsPortSideConfig.GetSignalType();
        aOtuTerminating = aRsPortSideConfig.IsSignalTypeOTN(aRsPortSignalType);
    }  // if (myRsPortSideCfgApp)

    
    if (aOtuTerminating) 
    {
        if (aMateLineOEORegen) 
        {
            // For Mate Line OEO Regen processing, what would normally force BDI, 
            // will now send a defect to the mate to let the mate know to force BDI
            aSendDefectToMate |= ( (aDefectsIf.IsLayerInDefects()    ||
                                    aDefectsIf.IsLayerInDefectsNTA() ||
                                    aDefectsIf.IsLayerInNonPropagateDefectsNTA())  &&
                                   aConsiderDefectsForBackwardInd );

            aForceBDI |= (aDefectsIf.IsMateLayerInDefects()  && 
                          aConsiderDefectsForBackwardInd);
        }
        else
        {
            // Normal Processing - Note that aSendDefectToMate is always false 
            // in this mode, which is set by default.
            // 
            // Force OTU-BDI on OTU layer failure.
            aForceBDI |= ( (aDefectsIf.IsLayerForMaintSigInDefects()    ||
                            aDefectsIf.IsLayerInDefectsNTA() ||
                            aDefectsIf.IsLayerForMaintSigInNonPropagateDefectsNTA())  &&
                           aConsiderDefectsForBackwardInd );
        }
    }
    else
    {
        // Make sure OTU-BDI is turned off and backward indicators are suppressed when non-OTU terminating
        aSuppressBackwardInd = true;
        aSuppressAutomaticBackwardInd = true;
        aSendDefectToMate = false;
        aForceBDI = false;      
    }

    if (aDisableSignaling) 
    {
        aForceBDI = false;
        aSendDefectToMate = false;
    }

    // The SetSuppressBackwardInd will only be used to set the Automatic Backward Indicators 
    // in HW using the SetBDIAndBEIAllowed method in the HwRefreshAction.  
    // for forcing BDI via software, disable it here using the other flag.
    hasChanged |= aOtuAutomaticConfig.SetSuppressBackwardInd(aSuppressAutomaticBackwardInd);       
    hasChanged |= aOtuAutomaticConfig.SetForceBDI(aForceBDI && (!aSuppressBackwardInd));       
    hasChanged |= aOtuAutomaticConfig.SetSendDefectToMate(aSendDefectToMate);       

    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }

    return NULL;
}

