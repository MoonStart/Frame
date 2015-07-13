// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_DcclAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_Dccl.h"
#include "../CFG_DcclAutomatic.h"
#include "../CFG_Opt.h"
#include "../CFG_OptAutomatic.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>

CFG_DcclAutomaticAction::CFG_DcclAutomaticAction(CFG_AppIf& theCfgIf,
                                               MON_AppIf* theDcclMonApp,
                                               uint8      theNumLinks,
                                               CFG_AppIf* theOptCfgApp,
                                               CFG_AppIf* theOptOtherSideCfgApp):
    CFG_HwRefreshAction(theCfgIf),
    myDcclMonApp(theDcclMonApp),
    myOptCfgApp(theOptCfgApp),
    myOptOtherSideCfgApp(theOptOtherSideCfgApp),
    myNumLinks(theNumLinks)
{
    // register about config changes or defect changes
    if (myDcclMonApp)
    {
        GetBbAction()->AddInputRegion(myDcclMonApp->GetDefectsRegion());
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

CFG_DcclAutomaticAction::~CFG_DcclAutomaticAction()
{
    if (myDcclMonApp)
    {
        GetBbAction()->RemoveInputRegion(myDcclMonApp->GetDefectsRegion());
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


FC_Object* CFG_DcclAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{

    bool hasChanged = false;
    bool aConsiderLockForInternalSignaling    = false;
    bool aConsiderDefectsForInternalSignaling = false;
    bool aDisableLink;
    //bool aDisableSignaling;

    CFG_Region* aCfgRegion = (GetCfgIf().GetCfgRegion());

    for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)
    {
        aDisableLink = false;
        //aDisableSignaling = false;

        CFG_DcclAutomatic& aAutomaticCfgObject  = static_cast<CFG_DcclAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[(bbindex_t)anIndex]);

        if (myDcclMonApp)
        {
            MON_Defects& aDcclDefects = static_cast<MON_Defects&>((*myDcclMonApp->GetDefectsRegion())[(bbindex_t)anIndex]);

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
                aDisableLink =  aDcclDefects.IsLayerLocked() && aConsiderLockForInternalSignaling ;

                // First, check if the layer is in defects
                aDisableLink |= aDcclDefects.IsLayerInDefects() && aConsiderDefectsForInternalSignaling;
            }

            if (myOptOtherSideCfgApp)
            {
                /*
                CFG_Opt& aOptOtherSideConfig              = static_cast<CFG_Opt&>((*myOptOtherSideCfgApp->GetCfgRegion())[0]);

                if (aOptOtherSideConfig.GetPrbsRxEnable() || aOptOtherSideConfig.GetPrbsTxEnable())
                {
                    aDisableSignaling = true;
                }*/
            }
        } // if (myDcclMonApp)

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
