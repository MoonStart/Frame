// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TEL_FSMLOGGER_INCLUDED
#define _INC_TEL_FSMLOGGER_INCLUDED


#include <Fsm/FC_FsmLogger.h>
#include <Fsm/src/FC_FsmTransitionInfo.h>
#include <vector>
#include <cstring>
#include "TEL_FsmLog.h"

using namespace std;

const int TEL_FSM_LOG_SIZE       =  25;
const int TEL_FSM_MAX_ID_SIZE    =  15;
const int TEL_FSM_MAX_TRANSITION = 256;
const int TEL_FSM_MAX_STATE      = 256;
const int TEL_FSM_MAX_CONDITION  = 256;

class TEL_FsmLogger : public FC_FsmLogger  
{
public:

    TEL_FsmLogger(const char* theID,
                  uint32*     theStateTable      = NULL,
                  uint32*     theConditionTable  = NULL,
                  uint32*     theTransitionTable = NULL);
    virtual ~TEL_FsmLogger();
    virtual void LogTransition(FC_StateId theCurrentState,  FC_FsmTransitionInfo & theTransition);
    virtual void LogCondition (FC_ConditionId theCondition, FC_StateId theCurrentState);
    virtual void ResetHistory ();
    virtual void DumpHistory  (ostream& theStream, int aMaxNumberOfLogs = 0); 
    virtual const char* ConditionIdToText(FC_ConditionId theCondition);
    virtual const char* StateIdToText(FC_StateId theState);

    virtual const char* TransitionIdToText(FC_TransitionId theTransition);

    virtual uint32 GetMaxState();

    virtual uint32 GetMaxCondition();

    virtual uint32 GetMaxTransition();

    void ResetStats();

    void DumpConditionStats(FC_Stream& theStream);

    void DumpStateStats(FC_Stream& theStream);

    void DumpTransitionStats(FC_Stream& theStream);

    const char* GetId() { return myID; }

private:
    void IncrementLog();
    void FormatStatLine(FC_Stream& theStream, int theIndex, uint32 theCount, uint32 theTotal, const char* theName);
    int currentLogIndex;
    unsigned int logSize;
    TEL_FsmLog myLogs[TEL_FSM_LOG_SIZE];
    FC_StateId myLastState;
    char myID[TEL_FSM_MAX_ID_SIZE];

    uint32* myTransitionTable;
    uint32* myStateTable;
    uint32* myConditionTable;
};

#endif // _INC_TEL_FSMLOGGER_INCLUDED
