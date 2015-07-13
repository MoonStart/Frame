// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <BaseClass/FC_TextStream.h>
#include "SignalProtection/SP_CallbackTimer.h"
#include "T6100_Dispatcher.h"

//##ModelId=39ACEFCE02E4
SP_CallbackTimer::SP_CallbackTimer(FC_Action& theCallbackAction, bool highPriority):
    FC_BaseTimer(0),
	myProcess(theCallbackAction, (highPriority ==false) ? gTimerDispatcher : gHighTimerDispatcher ,0),
    isStarted(false)
{
}

//##ModelId=39ACEFCE02E3
SP_CallbackTimer::~SP_CallbackTimer()
{
}

//##ModelId=39ACEFCE02CF
void SP_CallbackTimer::Start(FC_Milliseconds thePeriod)
{
    // kill process create
    myProcess.SuspendImmediate();

    // create a Timed process that will callback the action
    // shortly after the timer expires
    myProcess.SetDelay(thePeriod + 1);

    //Set the period in the timer.
    SetPeriod(thePeriod);

    //Start timer.
    FC_BaseTimer::Start();

    // WakeUp process
    myProcess.WakeUp();

    // indicate that everything is started
    isStarted = true;
}

//##ModelId=39ACEFCE02CE
void SP_CallbackTimer::Stop()
{
    myProcess.SuspendImmediate();
    isStarted = false;
}

//##ModelId=3B8BCA030280
FC_Stream& SP_CallbackTimer::DisplayRemainingTime(FC_Stream& theStream)
{
    FC_Milliseconds aTimeRemaining = GetTimeRemaining();
    if (!IsStarted())
    {
        theStream << "timer stopped";
    }
    else if (IsExpired())
    {
        theStream << "timer expired";
    }
    else
    {
        theStream << aTimeRemaining << " ms";
    }
    return theStream;
}

//##ModelId=3BBC9B29022F
SP_CallbackTimer::TimerState SP_CallbackTimer::GetState()
{
    if (!isStarted)
        return STOPPED;
    else if (IsExpired())
        return EXPIRED;
    else
        return RUNNING;
}

//##ModelId=3BBC9B290243
void SP_CallbackTimer::SyncState(int theState, FC_Milliseconds theTimeRemaining)
{
    if (theState != GetState())
    {
        switch (theState)
        {
        case STOPPED:
            Stop();
            break;

        case EXPIRED:
            myProcess.SuspendImmediate();
            isStarted = true;
            SetPeriod(0);
            FC_BaseTimer::Start();
            break;

        case RUNNING:
            Start(theTimeRemaining);
            break;

        default:
            FC_THROW_ERROR(FC_RuntimeError, "Invalid timer state");
        }
    }
}

//##ModelId=3BBC9B29018F
ostream& SP_CallbackTimer::WriteObject(ostream& theStream)
{
    int aState = GetState();
    FC_Milliseconds aTimeRemaining = 0;
    if (aState == RUNNING)
    {
        aTimeRemaining = GetTimeRemaining();
        if (aTimeRemaining < 0) aTimeRemaining = 0;
    }
    theStream << FC_InsertVar(aState);
    theStream << FC_InsertVar(aTimeRemaining);
    return theStream;
}

//##ModelId=3BBC9B2901B7
istream& SP_CallbackTimer::ReadObject(istream& theStream)
{
    int             aState;
    FC_Milliseconds aTimeRemaining;
    theStream >> FC_ExtractVar(aState);
    theStream >> FC_ExtractVar(aTimeRemaining);
    SyncState(aState, aTimeRemaining);

    myStateHistory = static_cast<SP_CallbackTimer::TimerState> (aState);
    return theStream;
}

//##ModelId=3BBC9B2901D5
FC_Stream& SP_CallbackTimer::WriteObjectBinary(FC_Stream& theStream)
{
    int aState = GetState();
    FC_Milliseconds aTimeRemaining = 0;
    if (aState == RUNNING)
    {
        aTimeRemaining = GetTimeRemaining();
        if (aTimeRemaining < 0) aTimeRemaining = 0;
    }
    theStream << aState;
    theStream << aTimeRemaining;
    return theStream;
}

//##ModelId=3BBC9B2901FD
FC_Stream& SP_CallbackTimer::ReadObjectBinary(FC_Stream& theStream)
{
    int             aState;
    FC_Milliseconds aTimeRemaining;
    theStream >> aState;
    theStream >> aTimeRemaining;
    SyncState(aState, aTimeRemaining);

    myStateHistory = static_cast<SP_CallbackTimer::TimerState> (aState);
    return theStream;
}

//##ModelId=3BBC9B29021B
bool SP_CallbackTimer::HasChangedSinceLastCheck()
{
    TimerState aState = GetState();
    if (aState == myStateHistory)
    {
        return false;
    }
    else
    {
        myStateHistory = aState;
        return true;
    }
}
