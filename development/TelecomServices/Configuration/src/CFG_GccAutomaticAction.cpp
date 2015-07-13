// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_GccAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_Gcc.h"
#include "../CFG_GccAutomatic.h"
#include "../CFG_Opt.h"
#include "../CFG_OptAutomatic.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>

CFG_GccAutomaticAction::CFG_GccAutomaticAction(CFG_AppIf& theCfgIf,
                                                MON_AppIf* theGccMonApp,
                                                uint8      theNumLinks,
                                                CFG_AppIf* theOptCfgApp):
    CFG_HwRefreshAction(theCfgIf),
    myGccMonApp(theGccMonApp),
    myOptCfgApp(theOptCfgApp),
    myNumLinks(theNumLinks)
{
    // register about config changes or defect changes
    if (myGccMonApp)
    {
        GetBbAction()->AddInputRegion(myGccMonApp->GetDefectsRegion());
    }

    if (myOptCfgApp)
    {
        GetBbAction()->AddInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->AddInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }

    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_GccAutomaticAction::~CFG_GccAutomaticAction()
{
    if (myGccMonApp)
    {
        GetBbAction()->RemoveInputRegion(myGccMonApp->GetDefectsRegion());
    }

    if (myOptCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetCfgRegion());
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetAutomaticCfgRegion());
    }

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_GccAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{

    bool hasChanged = false;
    bool aConsiderLockForInternalSignaling    = false;
    bool aConsiderDefectsForInternalSignaling = false;
    bool aDisableLink;
    //bool aDisableSignaling;

    // unused varible
    //CFG_Region* aCfgRegion = (GetCfgIf().GetCfgRegion());

    for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)
    {
        aDisableLink = false;
        //aDisableSignaling = false;

        CFG_GccAutomatic& aAutomaticCfgObject  = static_cast<CFG_GccAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[(bbindex_t)anIndex]);

        if (myGccMonApp)
        {
            MON_Defects& aGccDefects = static_cast<MON_Defects&>((*myGccMonApp->GetDefectsRegion())[(bbindex_t)anIndex]);

            if (myOptCfgApp)
            {
                CFG_Opt& aOptConfig              = static_cast<CFG_Opt&>((*myOptCfgApp->GetCfgRegion())[0]);
                CFG_OptAutomatic& aOptAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptCfgApp->GetAutomaticCfgRegion())[0]);
                /*
                if (aOptConfig.GetPrbsRxEnable() || aOptConfig.GetPrbsTxEnable())
                {
                    aDisableSignaling = true;
                }*/

                aConsiderLockForInternalSignaling    = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aOptAutoConfig.GetLineSideProtExists());
                aConsiderDefectsForInternalSignaling = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aOptAutoConfig.GetLineSideProtExists());

                // Now check if later is locked
                aDisableLink =  aGccDefects.IsLayerLocked() && aConsiderLockForInternalSignaling ;

                // First, check if the layer is in defects
                aDisableLink |= aGccDefects.IsLayerInDefects() && aConsiderDefectsForInternalSignaling;
            }

        } // if (myGccMonApp)

        // Also, if any PRBS BER Testing is turned on, don't force any signaling
        //if (aDisableSignaling)
        //{
        //aDisableLink = false;
        //}

        hasChanged |= aAutomaticCfgObject.SetDisableLink(aDisableLink);

    } // for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)


    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }

    return NULL;
}
