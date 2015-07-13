// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TEL_FSMLOG_INCLUDED
#define _INC_TEL_FSMLOG_INCLUDED

#include <Fsm/FC_FsmTypes.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <BaseClass/FC_Object.h>

using namespace std;

class TEL_FsmLogger;

class TEL_FsmLog : public FC_Object  
{
public:
	virtual ~TEL_FsmLog();
    TEL_FsmLog();
    TEL_FsmLog(FC_StateId theCurrentState,  
              FC_ConditionId theCondition, 
              FC_StateId theNextState, 
              FC_Milliseconds theOccuringTime);
    TEL_FsmLog(FC_ConditionId theCondition, 
              FC_StateId theCurrentState, 
              FC_Milliseconds theOccuringTime);
    void SetTransition(FC_StateId theCurrentState,  
                       FC_ConditionId theCondition, 
                       FC_StateId theNextState, 
                       FC_Milliseconds theOccuringTime);
    void SetCondition(FC_ConditionId theCondition, 
                      FC_StateId theCurrentState, 
                      FC_Milliseconds theOccuringTime);
    bool operator==(TEL_FsmLog& rhs) const;
    bool operator!=(TEL_FsmLog& rhs) const;
    virtual ostream& WriteObject( ostream& theStream );
	virtual istream& ReadObject( istream& theStream );
    void Report(ostream& theStream, TEL_FsmLogger& theLogger);

private:
    void TimeToString(FC_Milliseconds theTime, char* theTimeStr);
    bool isTransition;
    FC_StateId myCurrentState;
    FC_StateId myNextState;
    FC_ConditionId myCondition;
    FC_Milliseconds myOccuringTime;
};

#endif // 
