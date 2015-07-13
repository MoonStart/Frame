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
//##ModelId=39ACEFCE01F2
class SP_CallbackTimer: public FC_BaseTimer, public FC_Object
{
public:
	//Constructor. Requires a callback action.
	//@param bool: indicates whether this is a high priority timer
	//##ModelId=39ACEFCE02E4
    SP_CallbackTimer(FC_Action& theCallbackAction, bool highPriority = false);

	//Destructor.
	//##ModelId=39ACEFCE02E3
    virtual ~SP_CallbackTimer();
	//Configures the process to the delay value and wakes it 
	//up. Start the basetimer as well. Indicate the timer has 
	//been started.
	//##ModelId=39ACEFCE02CF
    void Start(FC_Milliseconds thePeriod);
	//Suspends the process and indicate that timer is stopped.
	//##ModelId=39ACEFCE02CE
    void Stop();
	//True if the timer is still running.
	//##ModelId=39ACEFCE02C5
    bool IsStarted() { return isStarted; }
	//Returns true if the timer is expired.
	//##ModelId=3B8BCA030294
    bool IsExpired( void ) const
    {
        if (isStarted)
            return FC_BaseTimer::IsExpired();
        else
            return false;
    }
	//Writes the remaining time before expiration to a stream.
	//##ModelId=3B8BCA030280
    FC_Stream& DisplayRemainingTime(FC_Stream& theStream);
	//Writes the atttribute to a stream.
	//##ModelId=3BBC9B29018F
    virtual ostream&   WriteObject(ostream& theStream);
	//Reads the atrribute from a stream.
	//##ModelId=3BBC9B2901B7
    virtual istream&   ReadObject(istream& theStream);
	//Writes the atttribute to a binary stream.
	//##ModelId=3BBC9B2901D5
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the atrribute from a binary stream.
	//##ModelId=3BBC9B2901FD
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
	//True if timer state (not count) has changes since last 
	//call.
	//##ModelId=3BBC9B29021B
    bool               HasChangedSinceLastCheck();

private:
	//Define the possible state of a callback timer.
	//##ModelId=3BBC9B2902B1
    enum TimerState 
    { 
		//##ModelId=3BBC9B290301
        STOPPED, 
		//##ModelId=3BBC9B29030B
        EXPIRED, 
		//##ModelId=3BBC9B290315
        RUNNING 
    };
	//Returns stop, expired or running.
	//##ModelId=3BBC9B29022F
    SP_CallbackTimer::TimerState  GetState();
	//Forces the timer to uses the given state and count.
	//##ModelId=3BBC9B290243
    void SyncState(int theState, FC_Milliseconds theTimeRemaining);

	//True if the timer is still running.
	//##ModelId=39ACEFCE02C4
    bool       isStarted;
	//State of the timer after last check.
	//##ModelId=3BBC9B29028A
    TimerState myStateHistory;
	//Pointer to the timed process.
	//##ModelId=39ACEFCE02A8
    FC_TimedProcess myProcess;
};

#endif // _INC_SP_CALLBACK_TIMER_INCLUDED
