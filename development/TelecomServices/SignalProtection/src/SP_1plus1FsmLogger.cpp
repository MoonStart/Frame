// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <cstdlib>
#include "../SP_1plus1FsmLogger.h"
#include "../SP_1plus1APSController.h"

using namespace std;

//##ModelId=3B8BC9E301B2
uint32 SP_1plus1FsmLogger::ourStateTable[TEL_FSM_MAX_STATE];
//##ModelId=3B8BC9E301A9
uint32 SP_1plus1FsmLogger::ourConditionTable[TEL_FSM_MAX_CONDITION];
//##ModelId=3B8BC9E301A8
uint32 SP_1plus1FsmLogger::ourTransitionTable[TEL_FSM_MAX_TRANSITION];

//##ModelId=39ACEFBB00FE
SP_1plus1FsmLogger::SP_1plus1FsmLogger(const char* theID):
    TEL_FsmLogger(theID, ourStateTable, ourConditionTable, ourTransitionTable)
{
}

//##ModelId=39ACEFBB00FD
SP_1plus1FsmLogger::~SP_1plus1FsmLogger()
{
}

//##ModelId=3B8BC9E301B5
uint32 SP_1plus1FsmLogger::GetMaxState()
{
    return S_1PLUS1_MAX_STATE;
}

//##ModelId=3B8BC9E301B4
uint32 SP_1plus1FsmLogger::GetMaxCondition()
{
    return C_1PLUS1_MAX_CONDITION;
}

//##ModelId=3B8BC9E301B3
uint32 SP_1plus1FsmLogger::GetMaxTransition()
{
    return T_1PLUS1_MAX_TRANSITION;
}

//##ModelId=39ACEFBB00FB
const char* SP_1plus1FsmLogger::ConditionIdToText(FC_ConditionId theCondition)
{
    return SP_1plus1APSController::ConvertConditionIdToText(theCondition);
}

//##ModelId=39ACEFBB00F0
const char* SP_1plus1FsmLogger::StateIdToText(FC_StateId theState)
{
    return SP_1plus1APSController::ConvertStateIdToText(theState);
}

//##ModelId=3B8BC9E301BC
const char* SP_1plus1FsmLogger::TransitionIdToText(FC_TransitionId theTransition)
{
    return SP_1plus1APSController::ConvertTransitionIdToText(theTransition);
}
