// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef SP_1PLUS1FSMLOGGER_H
#define SP_1PLUS1FSMLOGGER_H


#include <TelCommon/TEL_FsmLogger.h>

//##ModelId=39ACEFBB0032
class SP_1plus1FsmLogger : public TEL_FsmLogger  
{
public:
    //##ModelId=39ACEFBB00FE
    SP_1plus1FsmLogger(const char* theID);
    //##ModelId=39ACEFBB00FD
    virtual ~SP_1plus1FsmLogger();
    //##ModelId=39ACEFBB00FB
    virtual const char* ConditionIdToText(FC_ConditionId theCondition);
    //##ModelId=39ACEFBB00F0
    virtual const char* StateIdToText(FC_StateId theState);
	//##ModelId=3B8BC9E301BC
    virtual const char* TransitionIdToText(FC_TransitionId theTransition);
	//##ModelId=3B8BC9E301B5
    virtual uint32 GetMaxState();
	//##ModelId=3B8BC9E301B4
    virtual uint32 GetMaxCondition();
	//##ModelId=3B8BC9E301B3
    virtual uint32 GetMaxTransition();
private:
	//##ModelId=3B8BC9E301B2
    static uint32 ourStateTable[TEL_FSM_MAX_STATE];
	//##ModelId=3B8BC9E301A9
    static uint32 ourConditionTable[TEL_FSM_MAX_CONDITION];
	//##ModelId=3B8BC9E301A8
    static uint32 ourTransitionTable[TEL_FSM_MAX_TRANSITION];

};

#endif // SP_1PLUS1FSMLOGGER_H
