// //Copyright(c) Tellabs Transport Group. All rights reserved.
/*
#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_SsmIf.h>
#include "../CFG_HwRefreshMesh.h"
#include "../CFG_Mesh.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <CommonTypes/CT_FacilityIds.h>


CFG_HwRefreshMesh::CFG_HwRefreshMesh(CFG_AppIf& theCfgIf,
                                     TSPII_SsmRegion& theSsmPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    mySsmPiiRegion(theSsmPiiRegion)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion(),true, true, true, FC_BbRegObsPriority::HIGH);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}


CFG_HwRefreshMesh::~CFG_HwRefreshMesh()
{
}

FC_Object* CFG_HwRefreshMesh::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Mesh& aCfgObject = static_cast<CFG_Mesh&>((*GetCfgIf().GetCfgRegion())[0]);
    TSPII_SsmIf& aSsmPiiObject = mySsmPiiRegion[0];
    
    if (aCfgObject.GetSwitchMode() == CT_TEL_SwitchMode_Mesh)
    {
        int aNbrOfSlots = aCfgObject.GetNbrOfSlots(); 
        for (int aSlot = 0; aSlot < aNbrOfSlots; aSlot++) 
        {
            aSsmPiiObject.SetBackplaneSlotEnabled(aSlot,aCfgObject.GetLinkStatus(aSlot));
        }
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

} */
	

