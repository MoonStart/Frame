// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_OPTPROTCFGACTION_38E35B0900D0_INCLUDED
#define _INC_SP_OPTPROTCFGACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include "SP_ProtectionGroupConfigRegion.h"
#include <TelCommon/TEL_BbRegionBaseImp.h>

class SP_Application;
class SP_ApplicationStatus;
class FC_BbAction;

//This action is responsible for validating the opt prot config region
//when no YCable protection schemes exist. It also controls the force laser
//shutdown depending on facility OOS configuration
class SP_OptProtCfgAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_OptProtCfgAction( SP_Application& theApplIf,
                         SP_ProtectionGroupConfigRegion& theConfigRegion,
	                     TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
                         CT_ShelfId theShelfId,
                         CT_SlotId theSlotId,
                         CT_IntfId thePortId,
                         uint8 theStartIndex /*0 based*/,
                         uint8 theNumNodes);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_OptProtCfgAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles config request coming from the 
	//admin. 
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    FC_BbAction* GetBbAction() { return myBbAction; }

private:

    bool IsYCableProtectionConfiguredOnPort();

	//Reference to the app ready region
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & myAppStatusRegion;
	//Reference to the config region.
    //##ModelId=394102B8010F
    SP_ProtectionGroupConfigRegion & myConfigRegion;
    FC_BbAction* myBbAction;
	SP_Application& myAppIf;
    CT_ShelfId myShelfId;
    CT_SlotId  mySlotId;
    CT_IntfId  myPortId;
    uint8 myStartIndex;
    uint myNumNodes;

};

#endif /* _INC_SP_OPTPROTCFGACTION_38E35B0900D0_INCLUDED */