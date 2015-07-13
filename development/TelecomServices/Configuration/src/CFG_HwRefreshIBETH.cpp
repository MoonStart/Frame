// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_IBETHIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include "../CFG_HwRefreshIBETH.h"
#include "../CFG_IBETH.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>


CFG_HwRefreshIBETH::CFG_HwRefreshIBETH(CFG_AppIf& theCfgIf,                  
                     TSPII_IBETHRegion& theIBETHPiiRegion,
                     uint8 theNumLinks):

    CFG_HwRefreshAction(theCfgIf),
    myIBETHPiiRegion(theIBETHPiiRegion),
    myNumLinks(theNumLinks)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
   
}

CFG_HwRefreshIBETH::~CFG_HwRefreshIBETH()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshIBETH::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    return NULL;
}


