// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_DrtrIf.h>
#include "../CFG_HwRefreshDrtr.h"
#include "../CFG_Drtr.h"
#include "../CFG_Tarp.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>


CFG_HwRefreshDrtr::CFG_HwRefreshDrtr(CFG_AppIf& theCfgIf,
                                     TSPII_DrtrRegion& theDrtrPiiRegion,
                                     CFG_AppIf* theTarpCfgApp,
                                     uint8 theNumRouters):

    CFG_HwRefreshAction(theCfgIf),
    myDrtrPiiRegion(theDrtrPiiRegion),
    myTarpCfgApp(theTarpCfgApp),
    myNumRouters(theNumRouters),
    myFirstRefreshAction(true)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    // Add Tarp
    if (myTarpCfgApp)
    {
        GetBbAction()->AddInputRegion(myTarpCfgApp->GetCfgRegion());
    }
}

CFG_HwRefreshDrtr::~CFG_HwRefreshDrtr()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    // Add Tarp
    if (myTarpCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myTarpCfgApp->GetCfgRegion());
    }
}

FC_Object* CFG_HwRefreshDrtr::Process(unsigned theRunReason,
                                      FC_Object* theInvokerObj,
                                      FC_Object* theParam)
{
    uint32 i;

    for (i = 0; i < GetCfgIf().GetCfgRegion()->Size(); i++)
    {
        CFG_Drtr& aCfgObject = static_cast<CFG_Drtr&>((*GetCfgIf().GetCfgRegion())[(bbindex_t)i]);
        TSPII_DrtrIf& aDrtrPiiObject = myDrtrPiiRegion[(bbindex_t)i];

        // TID Processing
        aDrtrPiiObject.SetCommandSequence(CT_DCC_TID_BEGIN);
        aDrtrPiiObject.SetTIDID(aCfgObject.GetTIDID());
        aDrtrPiiObject.SetCommandSequence(CT_DCC_TID_COMMIT);


        // OSI Router Parameters
        aDrtrPiiObject.SetCommandSequence(CT_DCC_ROUTER_BEGIN);
        aDrtrPiiObject.SetRouterID(aCfgObject.GetRouterID());
        aDrtrPiiObject.SetIsProvisioned(aCfgObject.GetIsProvisioned());
        aDrtrPiiObject.SetDCCRouterEnabled(aCfgObject.GetDCCRouterEnabled());
        aDrtrPiiObject.SetPrimaryAreaAddr(aCfgObject.GetPrimaryAreaAddr());
        aDrtrPiiObject.SetPgne1IpAddress(aCfgObject.GetPgne1IpAddress());
        aDrtrPiiObject.SetPgne2IpAddress(aCfgObject.GetPgne2IpAddress());
        aDrtrPiiObject.SetFirstAuxAreaAddr(aCfgObject.GetFirstAuxAreaAddr());
        aDrtrPiiObject.SetSecondAuxAreaAddr(aCfgObject.GetSecondAuxAreaAddr());
        aDrtrPiiObject.SetMaxNumAddr(aCfgObject.GetMaxNumAddr());
        aDrtrPiiObject.SetRoutingSystemID(aCfgObject.GetRoutingSystemID());
        aDrtrPiiObject.SetRoutingLevel(aCfgObject.GetRoutingLevel());
        aDrtrPiiObject.SetMaxLifetimeControl(aCfgObject.GetMaxLifetimeControl());
        aDrtrPiiObject.SetCommandSequence(CT_DCC_ROUTER_COMMIT);


        // TARP Parameters
        CFG_Region* aTarpCfgRegion = myTarpCfgApp->GetCfgRegion();
        CFG_Tarp&   aTarpCfgObject = static_cast<CFG_Tarp&>((*aTarpCfgRegion)[0]);

        aDrtrPiiObject.SetCommandSequence(CT_DCC_TARP_BEGIN);
        aDrtrPiiObject.SetFlushTimer(aTarpCfgObject.GetFlushTimer());
        aDrtrPiiObject.SetEntryTimer(aTarpCfgObject.GetEntryTimer());
        aDrtrPiiObject.SetType1Timer(aTarpCfgObject.GetType1Timer());
        aDrtrPiiObject.SetType2Timer(aTarpCfgObject.GetType2Timer());
        aDrtrPiiObject.SetType3Timer(aTarpCfgObject.GetType3Timer());
        aDrtrPiiObject.SetType4Timer(aTarpCfgObject.GetType4Timer());
        aDrtrPiiObject.SetProtocolAddr(aTarpCfgObject.GetProtocolAddr());
        aDrtrPiiObject.SetResetSequenceCounter(aTarpCfgObject.GetResetSequenceCounter());
        aDrtrPiiObject.SetLifetimeHops(aTarpCfgObject.GetLifetimeHops());
        aDrtrPiiObject.SetResetCacheCount(aTarpCfgObject.GetFlushCounter());
        aDrtrPiiObject.SetDCCTarpEnabled(aTarpCfgObject.GetDCCTarpEnabled());
        if ( 1 == aCfgObject.GetRouterID())
        {
            /// Currently only 1 TARP instance associated with the first router instance.
            aDrtrPiiObject.SetCommandSequence(CT_DCC_TARP_COMMIT);
        }
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;
}


