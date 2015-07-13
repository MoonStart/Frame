// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_ProtectionAction.h"
#include "../SP_ConfigAction.h"
#include "../SP_SwitchingCommand.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <T6100_Dispatcher.h>

const FC_Milliseconds CONFIG_TIMED_PROCESS_DELAY = 1 * 60 * 1000;

//##ModelId=3BBC9B0F02A0
SP_ConfigAction::SP_ConfigAction(	
    SP_ProtectionGroupConfigRegion& theConfigRegion,
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
	TEL_BbRegionBaseImp<SP_SwitchingCommand>& theSwitchCommandRegion,
    SP_ProtectionActions& theProtectionActions,
	uint32 theGroupCount):
	myConfigRegion(theConfigRegion),
    myAppStatusRegion(theAppStatusRegion),
	mySwitchCommandRegion(theSwitchCommandRegion),
	myProtectionActions(theProtectionActions),
    stopped(false),
    myBbAction(NULL),
	myGroupCount(theGroupCount)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion(&myConfigRegion);
    myBbAction->AddInputRegion(&mySwitchCommandRegion);
    myBbAction->AddOutputRegion(&myAppStatusRegion);
	myLowPriorityProcess = new FC_OneShotProcess(*myBbAction, gLowDispatcher);
    myLowPriorityCallbackAction = new FC_WakeUpProcessAction(*myLowPriorityProcess);
	myTimedProcess = new FC_TimedProcess(*myBbAction, gTimerDispatcher, CONFIG_TIMED_PROCESS_DELAY);
}

//##ModelId=38EDF51800A6
SP_ConfigAction::~SP_ConfigAction()
{
	myTimedProcess->SuspendImmediate();
    delete myBbAction;
	delete myLowPriorityProcess;
	delete myLowPriorityCallbackAction;
	delete myTimedProcess;
}

//##ModelId=3B8BC9D30390
void SP_ConfigAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
