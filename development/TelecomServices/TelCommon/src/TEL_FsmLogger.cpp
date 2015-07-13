// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../TEL_FsmLogger.h"
#include <ErrorService/FC_Error.h>
#include <PII_TickTimer.h>
#include <ExecutionSupport/FC_Milliseconds.h>

TEL_FsmLogger::TEL_FsmLogger(const char* theID,
                             uint32*     theStateTable,
                             uint32*     theConditionTable,
                             uint32*     theTransitionTable):
    currentLogIndex(0),
    logSize(0),
    myLastState(0xFF),
    myStateTable(theStateTable),
    myConditionTable(theConditionTable),
    myTransitionTable(theTransitionTable)
{
    if (strlen(theID) <= TEL_FSM_MAX_ID_SIZE)
        strcpy(myID, theID);
    else
        FC_THROW_ERROR(FC_ValueOutOfRangeError, "Logger identification string too long");
}

TEL_FsmLogger::~TEL_FsmLogger()
{
}

void TEL_FsmLogger::LogTransition(FC_StateId theCurrentState,  FC_FsmTransitionInfo & theTransition)
{
    FC_Milliseconds theOccurTime(PII_TickTimer::readTimer());

    // log only if the transition is to another state
    // or if it is forced
    if (IsLogTransitionToSameStateEnabled() || (theTransition.GetNextState() != myLastState))
    {
        if (myTransitionTable != NULL && theTransition.GetId() < GetMaxTransition())
            ++myTransitionTable[theTransition.GetId()];
        if (myStateTable != NULL && theTransition.GetNextState() < GetMaxState())
            ++myStateTable[theTransition.GetNextState()];
        IncrementLog();
        myLogs[currentLogIndex].SetTransition(theCurrentState,
                                              theTransition.GetConditionId(),
                                              theTransition.GetNextState(),
                                              theOccurTime);
        if (IsTraceEnabled())
        {
            myLogs[currentLogIndex].Report(GetOutputStream(), *this);
            GetOutputStream().flush();
        }
        myLastState = theTransition.GetNextState();
    }
}

void TEL_FsmLogger::LogCondition (FC_ConditionId theCondition, FC_StateId theCurrentState)
{
    FC_Milliseconds theOccurTime(PII_TickTimer::readTimer());

    TEL_FsmLog tmpLog(theCondition, theCurrentState, theOccurTime);
    // log only if there is not already the same condition (in the same state) in the log
    // or if it is forced
    if (IsLogEveryConditionEnabled() || (tmpLog != myLogs[currentLogIndex]))
    {
        if (myConditionTable != NULL && theCondition < GetMaxCondition())
            ++myConditionTable[theCondition];
        IncrementLog();
        myLogs[currentLogIndex].SetCondition (theCondition, theCurrentState, theOccurTime);
        if (IsTraceEnabled())
        {
            myLogs[currentLogIndex].Report(GetOutputStream(), *this);
            GetOutputStream().flush();
        }
    }
}

void TEL_FsmLogger::ResetHistory ()
{
    logSize = 0;
}

void TEL_FsmLogger::DumpHistory  (ostream& theStream, int aMaxNumberOfLogs)
{
    unsigned int size = 0;

    if ((aMaxNumberOfLogs==0) || ((unsigned int)aMaxNumberOfLogs >= logSize))
        size = logSize;

    theStream << "Begin of logs (recent)" << "\n";
    for (unsigned int i=0; i<size; i++)
    {
        int aIndex =  (currentLogIndex - i ) % TEL_FSM_LOG_SIZE;
        if (aIndex < 0 ) aIndex += TEL_FSM_LOG_SIZE;
        myLogs[aIndex].Report(theStream, *this);
    }
    theStream << "End of logs (old)" << endl;
}

const char* TEL_FsmLogger::ConditionIdToText(FC_ConditionId theCondition)
{
    return "Unknown condition";
}

const char* TEL_FsmLogger::StateIdToText(FC_StateId theState)
{
    return "Unknown state";
}

const char* TEL_FsmLogger::TransitionIdToText(FC_TransitionId theTransition)
{
    return "Unknown transition";
}

uint32 TEL_FsmLogger::GetMaxState()
{
    return TEL_FSM_MAX_STATE;
}

uint32 TEL_FsmLogger::GetMaxCondition()
{
    return TEL_FSM_MAX_CONDITION;
}

uint32 TEL_FsmLogger::GetMaxTransition()
{
    return TEL_FSM_MAX_TRANSITION;
}

void TEL_FsmLogger::ResetStats()
{
    int i;
    if (myStateTable      != NULL) for (i = 0; i < TEL_FSM_MAX_STATE;      i++) myStateTable[i]      = 0;
    if (myConditionTable  != NULL) for (i = 0; i < TEL_FSM_MAX_CONDITION;  i++) myConditionTable[i]  = 0;
    if (myTransitionTable != NULL) for (i = 0; i < TEL_FSM_MAX_TRANSITION; i++) myTransitionTable[i] = 0;
}

void TEL_FsmLogger::FormatStatLine(FC_Stream& theStream, int theIndex, uint32 theCount, uint32 theTotal, const char* theName)
{
    const int    TEL_FSM_HISTOGRAM_LENGTH = 80;
    const char * TEL_FSM_HISTOGRAM_SYMBOL =
        "********************************************************************************";

    int  histogramIndex = TEL_FSM_HISTOGRAM_LENGTH - (TEL_FSM_HISTOGRAM_LENGTH*theCount + theTotal/2)/theTotal;
    theStream.Setf(ios::left, ios::adjustfield);
    theStream.Width(50); theStream << theName;
    theStream.Setf(ios::right, ios::adjustfield);
    theStream.Width( 0); theStream << " (";
    theStream.Width( 2); theStream << theIndex;
    theStream.Width( 0); theStream << ") =";
    theStream.Width( 6); theStream << theCount;
    theStream.Width( 0); theStream << " " << &TEL_FSM_HISTOGRAM_SYMBOL[histogramIndex] << "\n";
}

void TEL_FsmLogger::DumpStateStats(FC_Stream& theStream)
{
    if (myStateTable == NULL)
    {
        theStream << "No state logging table." << endl;
        return;
    }
    uint32 total = 0;
    uint32    i;
    for (i = 0; i < GetMaxState(); i++) total += myStateTable[i];
    if (total == 0) total = 1;
    for (i = 0; i < GetMaxState(); i++) FormatStatLine(theStream, (int)i, myStateTable[i], total, StateIdToText(i));
    theStream.Flush();
}

void TEL_FsmLogger::DumpConditionStats(FC_Stream& theStream)
{
    if (myConditionTable == NULL)
    {
        theStream << "No condition logging table." << endl;
        return;
    }
    uint32 total = 0;
    uint32    i;
    for (i = 0; i < GetMaxCondition(); i++) total += myStateTable[i];
    if (total == 0) total = 1;
    for (i = 0; i < GetMaxCondition(); i++) FormatStatLine(theStream, (int)i, myConditionTable[i], total, ConditionIdToText(i));
    theStream.Flush();
}

void TEL_FsmLogger::DumpTransitionStats(FC_Stream& theStream)
{
    if (myTransitionTable == NULL)
    {
        theStream << "No transition logging table." << endl;
        return;
    }
    uint32 total = 0;
    uint32    i;
    for (i = 0; i < GetMaxTransition(); i++) total += myTransitionTable[i];
    if (total == 0) total = 1;
    for (i = 0; i < GetMaxTransition(); i++) FormatStatLine(theStream, (int)i, myTransitionTable[i], total, TransitionIdToText(i));
    theStream.Flush();
}

void TEL_FsmLogger::IncrementLog()
{
    currentLogIndex = (currentLogIndex + 1) % TEL_FSM_LOG_SIZE;
    logSize = (logSize==TEL_FSM_LOG_SIZE) ? logSize : logSize + 1;
}
