// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_HopAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_Hop.h"
#include "../CFG_HopAutomatic.h"
#include "../CFG_Opt.h"
#include "../CFG_OptAutomatic.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>

CFG_HopAutomaticAction::CFG_HopAutomaticAction(CFG_AppIf& theCfgIf,
                                               MON_AppIf* theHopMonApp,
                                               CT_NumberOfHops theHopsOnCard,
                                               CFG_AppIf* theOptCfgApp,
                                               CFG_AppIf* theOptOtherSideCfgApp):
    CFG_HwRefreshAction(theCfgIf),
    myHopMonApp(theHopMonApp),
    myOptCfgApp(theOptCfgApp),
    myOptOtherSideCfgApp(theOptOtherSideCfgApp),
    myHopsOnCard(theHopsOnCard)
{
    // register about config changes or defect changes
    if (myHopMonApp)
    {
        GetBbAction()->AddInputRegion(myHopMonApp->GetDefectsRegion());
    }

    if (myOptCfgApp)
    {
        GetBbAction()->AddInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->AddInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }
    if (myOptOtherSideCfgApp)
    {
        GetBbAction()->AddInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
    }

    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_HopAutomaticAction::~CFG_HopAutomaticAction()
{
    if (myHopMonApp)
    {
        GetBbAction()->RemoveInputRegion(myHopMonApp->GetDefectsRegion());
    }

    if (myOptCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }
    if (myOptOtherSideCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
    }

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_HopAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{

    bool hasChanged = false;
    bool aConsiderLockForInternalSignaling    = false;
    bool aConsiderDefectsForInternalSignaling = false;
    bool aForceInternalAIS = false;
    bool aDisableSignaling = false;

    CFG_Region* aCfgRegion = (GetCfgIf().GetCfgRegion());
    // Use myHopsOnCard constructor variable rather than size of region
    // due to Context Collapse changes
    // uint32 aCfgRegionSize = 0;
    // if (aCfgRegion)
    // {
    //     aCfgRegionSize = aCfgRegion->Size();
    // }

    for (uint32 anIndex = 0; anIndex < myHopsOnCard; anIndex++)
    {
        aForceInternalAIS = false;
        aDisableSignaling = false;

        CFG_HopAutomatic& aAutomaticCfgObject  = static_cast<CFG_HopAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[(bbindex_t)anIndex]);

        if (myHopMonApp)
        {
            MON_Defects& aHopDefects = static_cast<MON_Defects&>((*myHopMonApp->GetDefectsRegion())[(bbindex_t)anIndex]);

            if (myOptCfgApp)
            {
                CFG_Opt& aOptConfig              = static_cast<CFG_Opt&>((*myOptCfgApp->GetCfgRegion())[0]);
                CFG_OptAutomatic& aOptAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptCfgApp->GetAutomaticCfgRegion())[0]);

                if (aOptConfig.GetPrbsRxEnable() || aOptConfig.GetPrbsTxEnable())
                {
                    aDisableSignaling = true;
                }

                aConsiderLockForInternalSignaling    = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aOptAutoConfig.GetLineSideProtExists());
                aConsiderDefectsForInternalSignaling = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aOptAutoConfig.GetLineSideProtExists());

                // Now check if later is locked
                aForceInternalAIS =  aHopDefects.IsLayerLocked() && aConsiderLockForInternalSignaling ;

                // First, check if the layer is in defects
                aForceInternalAIS |= aHopDefects.IsLayerInDefects() && aConsiderDefectsForInternalSignaling;
            }

            if (myOptOtherSideCfgApp)
            {
                CFG_Opt& aOptOtherSideConfig              = static_cast<CFG_Opt&>((*myOptOtherSideCfgApp->GetCfgRegion())[0]);

                if (aOptOtherSideConfig.GetPrbsRxEnable() || aOptOtherSideConfig.GetPrbsTxEnable())
                {
                    aDisableSignaling = true;
                }
            }
        } // if (myHopMonApp)

        // Also, if any PRBS BER Testing is turned on, don't force any signaling
        if (aDisableSignaling)
        {
        aForceInternalAIS = false;
        }

        hasChanged |= aAutomaticCfgObject.SetForceInternalAIS(aForceInternalAIS);

    } // for (uint32 anIndex = 0; anIndex < myHopsOnCard; anIndex++)


    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }

    return NULL;
}
