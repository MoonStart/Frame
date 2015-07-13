// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_ClkSelIf.h>
#include "../CFG_HwRefreshSync.h"
#include "../CFG_Sync.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

CFG_HwRefreshSync::CFG_HwRefreshSync(CFG_AppIf& theCfgIf,
									 CFG_Region& theConfigRegion,
                                     TSPII_ClkSelRegion& theSyncPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    mySyncPiiRegion(theSyncPiiRegion),
	myConfigRegion(theConfigRegion)
{
	GetBbAction()->AddInputRegion(&theConfigRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshSync::~CFG_HwRefreshSync()
{
	GetBbAction()->RemoveInputRegion(&myConfigRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshSync::Process(unsigned theRunReason,
                                      FC_Object* theInvokerObj,
                                      FC_Object* theParam)
{
    CFG_Sync& aCfgObject = static_cast<CFG_Sync&>((myConfigRegion)[0]);
    TSPII_ClkSelIf& aSyncPiiObject = mySyncPiiRegion[0];
	
    //Set timing mode
    switch (aCfgObject.GetTimingMode()) 
    {
    case CT_TEL_LINE_TIMING:
    case CT_TEL_EXTERNAL_TIMING:
	case CT_TEL_MATE_TIMING:
	case CT_TEL_SPFAB_TIMING:
        aSyncPiiObject.SetTimingMode(CT_TEL_CLKSEL_MODE_REF);
        break;
    case CT_TEL_SELF_TIMING:
        aSyncPiiObject.SetTimingMode(CT_TEL_CLKSEL_MODE_INTERNAL);
        break;
    }
    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}
	

