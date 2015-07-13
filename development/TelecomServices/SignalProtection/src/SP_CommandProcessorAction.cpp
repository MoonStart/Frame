// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <CommonTypes/CT_SP_CommandType.h>
#include "../SP_SwitchingCommand.h"
#include "../SP_SwitchingCommandResult.h"
#include "../SP_ProtectionAction.h"
#include "../SP_CommandProcessorAction.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>
#include "SP_ApplicationStatus.h"

//##ModelId=3BBC9B0F02A0
SP_CommandProcessorAction::SP_CommandProcessorAction(	
    TEL_BbRegionBaseImp<SP_SwitchingCommand>& theSwitchCommandRegion,
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
    SP_ProtectionActions& theProtectionActions,
	uint32 theGroupCount):
	mySwitchCommandRegion(theSwitchCommandRegion),
    myAppStatusRegion(theAppStatusRegion),
	myProtectionActions(theProtectionActions),
    stopped(false),
    myBbAction(NULL),
    myLowPriorityProcess(NULL),
	myLowPriorityCallbackAction(NULL),
	myGroupCount(theGroupCount)

{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion(&mySwitchCommandRegion);
    myBbAction->AddInputRegion(&theAppStatusRegion);

	myLowPriorityProcess = new FC_OneShotProcess(*myBbAction, gLowDispatcher);
    myLowPriorityCallbackAction = new FC_WakeUpProcessAction(*myLowPriorityProcess);
}

//##ModelId=38EDF51800A6
SP_CommandProcessorAction::~SP_CommandProcessorAction()
{
    delete myBbAction;
	delete myLowPriorityProcess;
	delete myLowPriorityCallbackAction;
}

//##ModelId=3B8BC9D30390
void SP_CommandProcessorAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
