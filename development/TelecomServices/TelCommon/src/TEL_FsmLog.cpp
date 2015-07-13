// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../TEL_FsmLog.h"
#include "../TEL_FsmLogger.h"
#include <ErrorService/FC_Error.h>

TEL_FsmLog::~TEL_FsmLog()
{

}

TEL_FsmLog::TEL_FsmLog(): 
    isTransition(false),
    myCurrentState(0xFF),
    myNextState(0xFF),
    myCondition(0xFF),
    myOccuringTime(0)
{};

    TEL_FsmLog::TEL_FsmLog(FC_StateId theCurrentState,  FC_ConditionId theCondition, FC_StateId theNextState, FC_Milliseconds theOccuringTime):
    isTransition(true),
    myCurrentState(theCurrentState),
    myNextState(theNextState),
    myCondition(theCondition),
    myOccuringTime(theOccuringTime)
{
};

    TEL_FsmLog::TEL_FsmLog(FC_ConditionId theCondition, FC_StateId theCurrentState, FC_Milliseconds theOccuringTime):
    isTransition(false), // it is a condition
    myCurrentState(theCurrentState),
    myNextState(0),
    myCondition(theCondition),
    myOccuringTime(theOccuringTime)
{
};

void TEL_FsmLog::SetTransition(FC_StateId theCurrentState,  FC_ConditionId theCondition, FC_StateId theNextState, FC_Milliseconds theOccuringTime)
{
    isTransition = true;
    myCurrentState = theCurrentState;
    myNextState = theNextState;
    myCondition = theCondition;
    myOccuringTime = theOccuringTime;
};

void TEL_FsmLog::SetCondition(FC_ConditionId theCondition, FC_StateId theCurrentState, FC_Milliseconds theOccuringTime)
{
    isTransition = false; // it is a condition
    myCurrentState = theCurrentState;
    myNextState = 0;
    myCondition = theCondition;
    myOccuringTime = theOccuringTime;
};

bool TEL_FsmLog::operator==(TEL_FsmLog& rhs) const
{
    return ((isTransition == rhs.isTransition) &&
            (myCurrentState == rhs.myCurrentState) &&
            (myNextState == rhs.myNextState) &&
            (myCondition == rhs.myCondition));
};
bool TEL_FsmLog::operator!=(TEL_FsmLog& rhs) const
{
    return !(*this == rhs);
};

void TEL_FsmLog::Report(ostream& theStream, TEL_FsmLogger& theLogger)
{
    char theTimeStr[40];
    TimeToString(myOccuringTime, theTimeStr);

    if (isTransition) // if it is a transition
    {
        theStream << theTimeStr
                  << ": FsmLog("                 << theLogger.GetId()
                  << "): Transition from state " << theLogger.StateIdToText(myCurrentState) 
                  << " to "                      << theLogger.StateIdToText(myNextState)
                  << " on condition "            << theLogger.ConditionIdToText(myCondition) << "\n";
    }
    else
    {
        theStream << theTimeStr 
                  << ": FsmLog("           << theLogger.GetId()
                  << "): Condition "       << theLogger.ConditionIdToText(myCondition) 
                  << " detected in state " << theLogger.StateIdToText(myCurrentState) << "\n";
    }
}

ostream& TEL_FsmLog::WriteObject( ostream& theStream )
{
    FC_THROW_ERROR(FC_NotSupportedError, "WriteObject() on TEL_FsmLog not implemented");
    return theStream;
}

istream& TEL_FsmLog::ReadObject( istream& theStream )
{
    FC_THROW_ERROR(FC_NotSupportedError, "ReadObject() on TEL_FsmLog not implemented");
    return theStream;
}

void TEL_FsmLog::TimeToString(FC_Milliseconds theTime, char* theTimeStr)
{
    int32 hours;
    int32 minutes;
    int32 sec;
    int32 msec;

    msec    = theTime % 1000;
    sec     = ((theTime - msec) / 1000) % 60;
    minutes = ((((theTime - msec) / 1000) - sec) / 60) % 60;
    hours   = (((theTime - msec) / 1000) - sec - minutes*60) / 3600;

    sprintf(theTimeStr, "%4d:%02d:%02d.%03d", hours, minutes, sec, msec);
    return;
}
