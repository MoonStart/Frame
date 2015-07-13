// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef SP_1PLUS1DEFECTPROCESSORACTION_H
#define SP_1PLUS1DEFECTPROCESSORACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include "SP_DefectProcessorAction.h"


class SP_ProtectionAction;


//This class is an action that manages defect
// processing for 1+1 protection actions
//##ModelId=3BBC9B39030E
class SP_1plus1DefectProcessorAction 
: public SP_DefectProcessorAction
{
public:
	//Constructor.  Requires the the layer being monitored.
	//##ModelId=3BBC9B390387
    SP_1plus1DefectProcessorAction(    
        SP_ProtectionLayer theLayer,
		SP_ProtectionSide theSide,
		SP_Application& theApplIf,
		CT_IntfId thePortId = CT_INTF_ID_UNKNOWN);

    //Destructor.
	//##ModelId=3BBC9B3903A4
    virtual ~SP_1plus1DefectProcessorAction();

	//allow a protection action to register for defects/status
	//being monitored by this defect processor
	virtual void RegisterForDefects(SP_ProtectionAction* theProtectionAction, 
		                            CT_ShelfId theWShelf, CT_SlotId theWSlot, CT_IntfId theWFacility, 
									CT_ShelfId thePShelf, CT_SlotId thePSlot, CT_IntfId thePFacility);

	//allow a protection action to stop receiving defect/status indication
	//from the defect processor
	virtual void UnregisterFromDefects(SP_ProtectionAction* theProtectionAction);

	//get MON regions
    virtual MON_Region* GetMONDefectRegion(CT_ShelfId theShelf, CT_SlotId theSlot, CT_IntfId theFacility);
	virtual MON_Region* GetMONStatusRegion(CT_ShelfId theShelf, CT_SlotId theSlot, CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType);
	virtual SP_SsmRegion* GetSPSystemStatusRegion(CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType);
    virtual SP_SsmRegion* GetSPShelfStatusRegion(CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType);

	//check for validity of monitored regions
	bool CheckValidity();

	//This method handles changes in MON defect and status regions.
	//Wakes up registered protection actions to perform APS selection
	//##ModelId=3BBC9B3903A6
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);


	

private:
    
	
};

#endif /* SP_1PLUS1CONFIGACTION_H */
