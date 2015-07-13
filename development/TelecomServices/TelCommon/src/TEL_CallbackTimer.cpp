// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <BaseClass/FC_TextStream.h>
#include "../TEL_CallbackTimer.h"
#include <T6100_Dispatcher.h>


TEL_CallbackTimer::TEL_CallbackTimer(FC_Action& theCallbackAction):
    FC_BaseTimer(0),
    myProcess(theCallbackAction, gTimerDispatcher ,0),
    isStarted(false)
{
}


TEL_CallbackTimer::~TEL_CallbackTimer()
{
}


void TEL_CallbackTimer::Start(FC_Milliseconds thePeriod)
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


void TEL_CallbackTimer::Stop()
{
    myProcess.SuspendImmediate();
    isStarted = false;
}


FC_Stream& TEL_CallbackTimer::DisplayRemainingTime(FC_Stream& theStream)
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


TEL_CallbackTimer::TimerState TEL_CallbackTimer::GetState()
{
    if (!isStarted)
        return STOPPED;
    else if (IsExpired())
        return EXPIRED;
    else
        return RUNNING;
}


void TEL_CallbackTimer::SyncState(int theState, FC_Milliseconds theTimeRemaining)
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


ostream& TEL_CallbackTimer::WriteObject(ostream& theStream)
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


istream& TEL_CallbackTimer::ReadObject(istream& theStream)
{
    int             aState;
    FC_Milliseconds aTimeRemaining;
    theStream >> FC_ExtractVar(aState);
    theStream >> FC_ExtractVar(aTimeRemaining);
    SyncState(aState, aTimeRemaining);

    myStateHistory = static_cast<TEL_CallbackTimer::TimerState> (aState);
    return theStream;
}


FC_Stream& TEL_CallbackTimer::WriteObjectBinary(FC_Stream& theStream)
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


FC_Stream& TEL_CallbackTimer::ReadObjectBinary(FC_Stream& theStream)
{
    int             aState;
    FC_Milliseconds aTimeRemaining;
    theStream >> aState;
    theStream >> aTimeRemaining;
    SyncState(aState, aTimeRemaining);

    myStateHistory = static_cast<TEL_CallbackTimer::TimerState> (aState);
    return theStream;
}


bool TEL_CallbackTimer::HasChangedSinceLastCheck()
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
