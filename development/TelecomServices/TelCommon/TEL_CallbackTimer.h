// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_CALLBACK_TIMER_INCLUDED
#define _INC_SP_CALLBACK_TIMER_INCLUDED

#include <ExecutionSupport/FC_BaseTimer.h>
#include <ExecutionSupport/FC_TimedProcess.h>

class FC_Stream;

//This is a specialized version of the FC_BaseTimer that 
//allows a callback action to be invoked on expiration of the 
//timer. It actually contains a timed process to is schedule 
//to invoke at the same time the timer expires.

class TEL_CallbackTimer: public FC_BaseTimer, public FC_Object
{
public:
	//Constructor. Requires a callback action.

    TEL_CallbackTimer(FC_Action& theCallbackAction);

	//Destructor.

    virtual ~TEL_CallbackTimer();
	//Configures the process to the delay value and wakes it 
	//up. Start the basetimer as well. Indicate the timer has 
	//been started.

    void Start(FC_Milliseconds thePeriod);
	//Suspends the process and indicate that timer is stopped.

    void Stop();
	//True if the timer is still running.

    bool IsStarted() { return isStarted; }
	//Returns true if the timer is expired.

    bool IsExpired( void ) const
    {
        if (isStarted)
            return FC_BaseTimer::IsExpired();
        else
            return false;
    }
	//Writes the remaining time before expiration to a stream.

    FC_Stream& DisplayRemainingTime(FC_Stream& theStream);
	//Writes the atttribute to a stream.

    virtual ostream&   WriteObject(ostream& theStream);
	//Reads the atrribute from a stream.

    virtual istream&   ReadObject(istream& theStream);
	//Writes the atttribute to a binary stream.

	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the atrribute from a binary stream.

	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
	//True if timer state (not count) has changes since last 
	//call.

    bool               HasChangedSinceLastCheck();

private:
	//Define the possible state of a callback timer.

    enum TimerState 
    { 

        STOPPED, 

        EXPIRED, 

        RUNNING 
    };
	//Returns stop, expired or running.

    TEL_CallbackTimer::TimerState  GetState();
	//Forces the timer to uses the given state and count.

    void SyncState(int theState, FC_Milliseconds theTimeRemaining);

	//True if the timer is still running.

    bool       isStarted;
	//State of the timer after last check.

    TimerState myStateHistory;
	//Pointer to the timed process.

    FC_TimedProcess myProcess;
};

#endif // _INC_SP_CALLBACK_TIMER_INCLUDED
