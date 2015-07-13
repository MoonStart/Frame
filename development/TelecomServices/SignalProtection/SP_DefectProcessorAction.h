// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_DEFECTPROCESSORACTION_38E35B0900D0_INCLUDED
#define _INC_SP_DEFECTPROCESSORACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_ListOfAction.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <list>
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include "SP_Definitions.h"
#include <CommonTypes/CT_Port.h>


class SP_ProtectionAction;
class MON_Region;
class FC_BbAction;
class SP_Application;
class FC_WakeUpProcessAction;
class FC_OneShotProcess;
class FC_TimedProcess;
class SP_SsmRegion;

//This class handles defect processing for protection actions. 
//Protection Actions register to the defect processor action
//to be woken up on MON defect and status regions
//This is the base class for all defect processor actions of signal protection.
//##ModelId=38E35B0900D0
class SP_DefectProcessorAction 
: public FC_ListOfAction
{
public:
	//Constructor. Requires the layer that the
	//defect processor is monitoring. 
    //##ModelId=3BBC9B0F02A0
    SP_DefectProcessorAction(SP_ProtectionLayer theLayer, SP_ProtectionSide theSide, SP_Application& theApplIf, CT_IntfId thePortId = CT_INTF_ID_UNKNOWN);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_DefectProcessorAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles changes in MON defect and status regions.
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL) = 0;

	//allow a protection action to register for defects/status
	//being monitored by this defect processor
	virtual void RegisterForDefects(SP_ProtectionAction* theProtectionAction, 
		                            CT_ShelfId theWShelf, CT_SlotId theWSlot, CT_IntfId theWFacility, 
									CT_ShelfId thePShelf, CT_SlotId thePSlot, CT_IntfId thePFacility) = 0;

	//allow a protection action to stop receiving defect/status indication
	//from the defect processor
	virtual void UnregisterFromDefects(SP_ProtectionAction* theProtectionAction) = 0;

	//get MON regions
    virtual MON_Region* GetMONDefectRegion(CT_ShelfId theShelf, CT_SlotId theSlot, CT_IntfId theFacility) = 0;
	virtual MON_Region* GetMONStatusRegion(CT_ShelfId theShelf, CT_SlotId theSlot, CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType) = 0;
	virtual SP_SsmRegion* GetSPSystemStatusRegion(CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType) = 0;
    virtual SP_SsmRegion* GetSPShelfStatusRegion(CT_IntfId theFacility, CT_SP_1plus1SubType the1plus1SubType) = 0;

	MON_Region* GetMONDefectRegion(CT_SP_Protection theProtSide);
	MON_Region* GetMONStatusRegion(CT_SP_Protection theProtSide);

	//set/get the usage status of this defect processor
	void SetUsageStatus(bool theUsageStatus);
	bool GetUsageStatus();

    SP_ProtectionLayer GetLayer();
	SP_ProtectionSide GetSide();
	CT_IntfId GetPortId();

	CT_SP_ProtectionPair<MON_Region*> myMonDefectsRegion;
    CT_SP_ProtectionPair<MON_Region*> myMonStatusRegion;
	CT_SP_ProtectionPair<SP_SsmRegion*> mySpSystemStatusRegion;
    CT_SP_ProtectionPair<SP_SsmRegion*> mySpShelfStatusRegion;


	//Forces the defect processor action to start if it was 
	//stopped(debug).
    //##ModelId=39ACEFB00072
    inline void Start();
	//Forces the configuration action to stop (debug).
    //##ModelId=39ACEFB0005E
    inline void Stop();
	//Returns a reference to the high priority wake up action.
	//##ModelId=3B8BC9BF0156
    inline FC_WakeUpProcessAction& GetHighPriorityWakeUpAction();

    FC_BbAction* GetBbAction() { return myBbAction; }

	SP_Application& GetAppIf() const { return myApplIf;}

protected:

	//The layer that this defect processor is monitoring
	SP_ProtectionLayer myLayer;

	//The side that this defect processor is performing
	//the monitoring on
	SP_ProtectionSide mySide;

	//Any particalar port that this defect processor 
	//is associated with 
	CT_IntfId myPortId;

	//Pointer to the high priority wake up action usually 
	//execute for high priority event (failures, APS 
	//messages).
	//##ModelId=3B8BC9BD0208
    FC_WakeUpProcessAction* myHighPriorityCallbackAction;

	//High priority process running high priority action.
	//##ModelId=39ACEF9F029E
    FC_OneShotProcess* myHighPriorityProcess;

	//True if processing is stop (debug).
    //##ModelId=39ACEFB0002C
    bool stopped;

	//True if the defect processor is being used
	bool myUsageStatus;


private:
    FC_BbAction* myBbAction;
	SP_Application& myApplIf;

};

//##ModelId=39ACEFB00072
inline void SP_DefectProcessorAction::Start() { stopped = false; }
//##ModelId=39ACEFB0005E
inline void SP_DefectProcessorAction::Stop() { stopped = true; }

//##ModelId=3B8BC9BF0156
inline FC_WakeUpProcessAction& SP_DefectProcessorAction::GetHighPriorityWakeUpAction()
{
    return *myHighPriorityCallbackAction;
}


#endif /* _INC_SP_DEFECTPROCESSORACTION_38E35B0900D0_INCLUDED */
