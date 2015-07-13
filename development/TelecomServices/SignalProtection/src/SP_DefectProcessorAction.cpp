// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_ProtectionAction.h"
#include "../SP_DefectProcessorAction.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>


//##ModelId=3BBC9B0F02A0
SP_DefectProcessorAction::SP_DefectProcessorAction(	
    SP_ProtectionLayer theLayer,
	SP_ProtectionSide theSide,
	SP_Application& theApplIf,
	CT_IntfId thePortId):
    stopped(false),
	myUsageStatus(false),
	myLayer(theLayer),
	mySide(theSide),
	myApplIf(theApplIf),
	myPortId(thePortId),
    myBbAction(NULL),
	myMonDefectsRegion(NULL,NULL),
    myMonStatusRegion(NULL,NULL),
	mySpSystemStatusRegion(NULL,NULL),
    mySpShelfStatusRegion(NULL,NULL)
{
    myBbAction = new FC_BbAction(this);

	myHighPriorityProcess = new FC_OneShotProcess(*myBbAction, gHighDispatcher);
    myHighPriorityCallbackAction = new FC_WakeUpProcessAction(*myHighPriorityProcess);
}

//##ModelId=38EDF51800A6
SP_DefectProcessorAction::~SP_DefectProcessorAction()
{
	delete myHighPriorityProcess;
    delete myHighPriorityCallbackAction;
    delete myBbAction;
	if (!IsEmpty())
	{
		Clear();
	}
}

void SP_DefectProcessorAction::SetUsageStatus(bool theUseStatus) 
{
	myUsageStatus = theUseStatus;
}
bool SP_DefectProcessorAction::GetUsageStatus() 
{
	return myUsageStatus;
}

SP_ProtectionLayer SP_DefectProcessorAction::GetLayer()
{
	return myLayer;
}

SP_ProtectionSide SP_DefectProcessorAction::GetSide()
{
	return mySide;
}

CT_IntfId SP_DefectProcessorAction::GetPortId()
{
	return myPortId;
}

//##ModelId=3B8BC9D30390
void SP_DefectProcessorAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}


MON_Region* SP_DefectProcessorAction::GetMONDefectRegion(CT_SP_Protection theProtSide)
{
	if (theProtSide == CT_SP_WORKING_SIDE)
		return myMonDefectsRegion.working;
    else if (theProtSide == CT_SP_PROTECTION_SIDE)
	    return myMonDefectsRegion.protection;
	else
	    return NULL;
}

MON_Region* SP_DefectProcessorAction::GetMONStatusRegion(CT_SP_Protection theProtSide)
{
	if (theProtSide == CT_SP_WORKING_SIDE)
		return myMonStatusRegion.working;
    else if (theProtSide == CT_SP_PROTECTION_SIDE)
	    return myMonStatusRegion.protection;
	else
	    return NULL;
}
