// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_IsrMonAction.h"
#include <SignalProtection/SP_1plus1SubApplication.h>
#include <Blackboard/FC_BbAction.h>
#include <Blackboard/FC_BoolRegion.h>
#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////-----Action to monitor for protection interrupts
//##ModelId=3BBC9B0F02A0
SP_IsrMonAction::SP_IsrMonAction(    
    SP_1plus1SubApplication& theApplIf,
    FC_Milliseconds theInterval):
    myAppIf(theApplIf),
    myEnableFlag(true)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion( &theApplIf.GetMonIsrRegion(), false, true, true, FC_BbRegObsPriority::HIGH);
    myProcessPtr = new FC_TimedProcess(*this, gTimerDispatcher, theInterval);
    myCallbackAction = new FC_WakeUpProcessAction(*myProcessPtr);
    myDelayedBbAction = new FC_BbAction(myCallbackAction);
}

//##ModelId=38EDF51800A6
SP_IsrMonAction::~SP_IsrMonAction()
{
    myProcessPtr->SuspendImmediate();
    myBbAction->RemoveInputRegion( &myAppIf.GetMonIsrRegion() );
    delete myDelayedBbAction;
    delete myCallbackAction;
    delete myProcessPtr;
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_IsrMonAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}


FC_Object* SP_IsrMonAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    if (!myEnableFlag)
    {
        return NULL;
    }

    //FC_EventRecord(EVENT_SP_PII_SWITCH_START,0);
    //fc_cout << "Starting bulk switch" << endl;
    //FC_BaseStopwatch aStopwatch;
    //aStopwatch.Start();
    myAppIf.BulkSwitch();
    //fc_cout << "Elapsed time is " << aStopwatch.GetElapsedTime() << endl;
    //fc_cout << "Ending bulk switch" << endl;
    //FC_EventRecord(EVENT_SP_PII_SWITCH_END,0);

    return NULL;
}

void SP_IsrMonAction::Disable()
{
    myEnableFlag = false;
}