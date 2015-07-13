// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef PSOSP
#define __FUNCTION__ "UNKNOWN FUNCTION"
#endif

#include "../SP_1plus1APSController.h"
#include "../SP_1plus1K1K2Receiver.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_1plus1RequestParser.h"
#include "../SP_1plus1Selector.h"
#include "../SP_1plus1FsmLogger.h"
#include "../SP_1plus1K1K2Transmitter.h"
#include "../SP_OduKSnc.h"
#include <BaseClass/FC_TextStream.h>

//----------------------------------------------------------------------------
//STATE MACHINE RELATED STUFF
//----------------------------------------------------------------------------

//##ModelId=39170C470094
bool SP_1plus1APSController::fsmIsInitialized = false;
extern int gSP_DebugTraceSnc;

//============================================================================
//The order of appearance of the following macros is critical, it must follow
//the order in which the states and transitions are added to the Fsm. 
//
//See the InitFsm method below for the order.
//============================================================================

FC_FSM_STATE_FCT_BEGIN(SP_1plus1APSController)
    FC_FSM_STATE_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::EntryNoCode,
                         FC_FsmClientImp<SP_1plus1APSController>::ExitNoCode,
                         SP_1plus1APSController::InitRun)
    FC_FSM_STATE_FCT_ADD(SP_1plus1APSController::WorkingSelectedEntry,
                         FC_FsmClientImp<SP_1plus1APSController>::ExitNoCode,
                         SP_1plus1APSController::WorkingSelectedRun)
    FC_FSM_STATE_FCT_ADD(SP_1plus1APSController::ProtectionSelectedEntry,
                         FC_FsmClientImp<SP_1plus1APSController>::ExitNoCode,
                         SP_1plus1APSController::ProtectionSelectedRun)
    FC_FSM_STATE_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::EntryNoCode,
                         FC_FsmClientImp<SP_1plus1APSController>::ExitNoCode,
                         SP_1plus1APSController::NoDefectOnWorkingRun)
    FC_FSM_STATE_FCT_ADD(SP_1plus1APSController::CommandToProtectionEntry,
                         FC_FsmClientImp<SP_1plus1APSController>::ExitNoCode,
                         SP_1plus1APSController::CommandToProtectionRun)
    FC_FSM_STATE_FCT_ADD(SP_1plus1APSController::ProtectionNoRequestEntry,
                         FC_FsmClientImp<SP_1plus1APSController>::ExitNoCode,
                         SP_1plus1APSController::ProtectionNoRequestRun)
    FC_FSM_STATE_FCT_ADD(SP_1plus1APSController::WTREntry,
                         SP_1plus1APSController::WTRExit,
                         SP_1plus1APSController::WTRRun)
    FC_FSM_STATE_FCT_ADD(SP_1plus1APSController::DefectOnWorkingEntry,
                         FC_FsmClientImp<SP_1plus1APSController>::ExitNoCode,
                         SP_1plus1APSController::DefectOnworkingRun)
FC_FSM_STATE_FCT_END(SP_1plus1APSController)

FC_FSM_TRANSITION_FCT_BEGIN(SP_1plus1APSController)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_1plus1APSController>::TransitionNoCode)
FC_FSM_TRANSITION_FCT_END(SP_1plus1APSController)


//##ModelId=39170C470116
void SP_1plus1APSController::InitFsm(FC_Fsm& theFsm)
{
    // don't initialize state machine twice
    if (fsmIsInitialized)
        return;

    // Register states and transition here....
    //             | the new state
    //             | the parent state       | has entry code | has exit code
    theFsm.AddState(S_1PLUS1_INIT,
                    FC_FSM_NIL_STATE,           false,           false);

    theFsm.AddState(S_WORKING_SELECTED,
                    FC_FSM_NIL_STATE,           true,            false);

    theFsm.AddState(S_PROTECTION_SELECTED,
                    FC_FSM_NIL_STATE,           true,            false);

    theFsm.AddState(S_NO_DEFECT_ON_WORKING,
                    S_PROTECTION_SELECTED,      false,           false);

    theFsm.AddState(S_COMMAND_TO_PROTECTION,
                    S_NO_DEFECT_ON_WORKING,     true,            false);

    theFsm.AddState(S_PROTECTION_NO_REQUEST,
                    S_NO_DEFECT_ON_WORKING,     true,            false);

    theFsm.AddState(S_WTR,
                    S_NO_DEFECT_ON_WORKING,     true,            true);

    theFsm.AddState(S_DEFECT_ON_WORKING,
                    S_PROTECTION_SELECTED,      true,            false);

    theFsm.SetInitialState(S_1PLUS1_INIT);

//                      | from state       |to state                           
//                      | the condition              
//                      | the transition 
//                      | has code

    theFsm.AddTransition(S_WORKING_SELECTED,S_COMMAND_TO_PROTECTION,
                         C_PROTECTION_COMMAND,
                         T_WORKING_SELECTED_2_COMMAND_TO_PROTECTION,
                         false);

    theFsm.AddTransition(S_PROTECTION_SELECTED,S_COMMAND_TO_PROTECTION,
                         C_PROTECTION_COMMAND,
                         T_PROTECTION_SELECTED_2_COMMAND_TO_PROTECTION,
                         false);

    theFsm.AddTransition(S_PROTECTION_NO_REQUEST,S_WORKING_SELECTED,
                         C_REVERTIVE,
                         T_PROTECTION_NO_REQUEST_2_WORKING_SELECTED,
                         false);

    theFsm.AddTransition(S_NO_DEFECT_ON_WORKING,S_WORKING_SELECTED,
                         C_CLEAR_REVERTIVE,
                         T_NO_DEFECT_ON_WORKING_2_WORKING_SELECTED,
                         false);

    theFsm.AddTransition(S_WTR,S_WORKING_SELECTED,
                         C_1PLUS1_WTR_EXPIRED,
                         T_WTR_2_WORKING_SELECTED,
                         false);

    theFsm.AddTransition(S_PROTECTION_SELECTED,S_WORKING_SELECTED,
                         C_WORKING_HIGHER,
                         T_PROTECTION_SELECTED_2_WORKING_SELECTED,
                         false);

    theFsm.AddTransition(S_WORKING_SELECTED,S_DEFECT_ON_WORKING,
                         C_WORKING_DEFECT,
                         T_WORKING_SELECTED_2_DEFECT_ON_WORKING,
                         false);

    theFsm.AddTransition(S_COMMAND_TO_PROTECTION,S_PROTECTION_NO_REQUEST,
                         C_CLEAR_NOT_REVERTIVE,
                         T_COMMAND_TO_PROTECTION_2_PROTECTION_NO_REQUEST,
                         false);

    theFsm.AddTransition(S_WTR,S_PROTECTION_NO_REQUEST,
                         C_NOT_REVERTIVE,
                         T_WTR_2_PROTECTION_NO_REQUEST,
                         false);

    theFsm.AddTransition(S_DEFECT_ON_WORKING,S_WTR,
                         C_WORKING_DEFECT_CLEARED,
                         T_DEFECT_ON_WORKING_2_WTR,
                         false);

    theFsm.AddTransition(S_NO_DEFECT_ON_WORKING,S_DEFECT_ON_WORKING,
                         C_WORKING_DEFECT,
                         T_NO_DEFECT_ON_WORKING_2_DEFECT_ON_WORKING,
                         false);

    theFsm.AddTransition(S_1PLUS1_INIT,S_WORKING_SELECTED,
                         C_1PLUS1_INIT,
                         T_1PLUS1_INIT_2_WORKING_SELECTED,
                         false);

    theFsm.AddTransition(S_WTR, S_PROTECTION_NO_REQUEST,
                         C_1PLUS1_REMOTE_REQUEST,
                         T_WTR_2_PROTECTION_NO_REQUEST,
                         false);

    // refer to MR 224330
    theFsm.AddTransition(S_NO_DEFECT_ON_WORKING, S_PROTECTION_NO_REQUEST,
                         C_1PLUS1_REMOTE_REQUEST,
                         T_NO_DEFECT_ON_WORKING_2_PROTECTION_NO_REQUEST,
                         false);

    fsmIsInitialized = true;
}


//##ModelId=390584010156
SP_1plus1APSController::SP_1plus1APSController(
                            SP_1plus1ProtectionAction& theProtectionAction, 
                            SP_1plus1RequestParser& theRequestParser, 
                            SP_1plus1K1K2Transmitter& theK1K2Transmitter,
                            SP_1plus1FsmLogger* theLogger,
                            FC_Fsm& theFsm):
    FC_FsmClientImp<SP_1plus1APSController>(theFsm, SP_MAX_FSM_ITERATION_COUNT, theLogger),
    SP_APSController(theProtectionAction),
    myProtectionAction(theProtectionAction),
    myRequestParser(theRequestParser),
    myK1K2Transmitter(theK1K2Transmitter),
    myLastState(FC_FSM_NIL_STATE)
{
}

//##ModelId=390584010188
SP_1plus1APSController::~SP_1plus1APSController()
{
}

//##ModelId=39ACEFCB03A6
void SP_1plus1APSController::Reset()
{
    ResetToInitialState();
    MarkAsStable();
}

//##ModelId=3937FD4C0181
void 
SP_1plus1APSController::WorkingSelectedEntry(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);
    
    //Set selector to working.
    myProtectionAction.mySelectorPtr->SelectWorking();

    //Set selected channel in K-bytes.
    myProtectionAction.myK1K2TransmitterPtr->SetAPSChannel(CT_SP_WORKING_SIDE);

    //Get the highest request on the protection and set it in the K-bytes.
    CT_SP_Request aProtectionRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().protection;


    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        myProtectionAction.PrepareTxApsBytes(0, aProtectionRequest , myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().protection);
    }

    myProtectionAction.myK1K2TransmitterPtr->SetRequest(ConvertRequestToK1Request(aProtectionRequest)); 
}

//##ModelId=3937FD4C011D
FC_ConditionId 
SP_1plus1APSController::WorkingSelectedRun(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);
    
    FC_ConditionId aReturnCondition = FC_FSM_NO_CONDITION;

    //Set selector to working.
    myProtectionAction.mySelectorPtr->SelectWorking();

    // Clear any remaining CLEAR command from the request parser
    // to prevent from hiding lower priority request (such as a SF-W)
    myProtectionAction.myRequestParserPtr->GetClearCommand();

    //Verify if the working is still the best side.
    if(myProtectionAction.myRequestParserPtr->GetBestSide() != CT_SP_PROTECTION_SIDE)
    {
      //Update status in K-bytes.
        //Get the highest request on the protection and set it in the K-bytes.
        CT_SP_Request aProtectionRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().protection;

        if (myProtectionAction.Get1plus1Config().IsBiSwitching())
        {
            myProtectionAction.PrepareTxApsBytes(0, aProtectionRequest, myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().protection);
        }

        myProtectionAction.myK1K2TransmitterPtr->SetRequest(ConvertRequestToK1Request(aProtectionRequest));

        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");

        aReturnCondition = FC_FSM_NO_CONDITION;
    }
    else //Protection is the best side.
    {
        switch(myProtectionAction.myRequestParserPtr->GetHighestRequest().working)
        {
            //If the highest request is a command to protection: return C_PROTECTION_COMMAND.
            case CT_SP_1PLUS1_FS_P:
            case CT_SP_1PLUS1_MS_P:
                 if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_PROTECTION_COMMAND\n");
                 aReturnCondition =  C_PROTECTION_COMMAND;
                break;
            //Otherwise, we assume it is a defect on the working.
            case CT_SP_1PLUS1_SD_W:
			case CT_SP_1PLUS1_SF_LOW_W:
            case CT_SP_1PLUS1_SF_W:
                if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_WORKING_DEFECT\n");
                aReturnCondition = C_WORKING_DEFECT;
                break;
            case CT_SP_1PLUS1_RR:
                if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");
                aReturnCondition = FC_FSM_NO_CONDITION;
                break;
            default:
                FC_THROW_ERROR(FC_InvalidArgumentError, "Unexpected request on working.");
                break;
        }
    }

    return aReturnCondition;
}

//##ModelId=3937FD4C00C3
void 
SP_1plus1APSController::ProtectionSelectedEntry(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    //Set selector to protection.
    myProtectionAction.mySelectorPtr->SelectProtection();

    //Set selected channel in K-bytes.
    myProtectionAction.myK1K2TransmitterPtr->SetAPSChannel(CT_SP_PROTECTION_SIDE);
}

//##ModelId=3937FD4C0073
FC_ConditionId 
SP_1plus1APSController::ProtectionSelectedRun(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    FC_ConditionId aReturnCondition = FC_FSM_NO_CONDITION;

    //Set selector to protection.
    myProtectionAction.mySelectorPtr->SelectProtection();

    //Verify if the working is now the best side.
    if(myProtectionAction.myRequestParserPtr->GetBestSide() == CT_SP_WORKING_SIDE)
    {
        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_WORKING_HIGHER\n");

        aReturnCondition = C_WORKING_HIGHER;
    }
    else //Protection is still the best side.
    {
        //If the highest request is a command to the protection: return C_PROTECTION_COMMAND.
        //GUARD: S_COMMAND_TO_PROTECTION. If the latter is the current state, do not verify the above condition.
        if(GetCurrentState() == S_COMMAND_TO_PROTECTION)
        {
            if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");

            aReturnCondition = FC_FSM_NO_CONDITION;
        }
        else 
        {
            CT_SP_Request aRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().working;
            
            if( (aRequest == CT_SP_1PLUS1_FS_P) || 
                (aRequest == CT_SP_1PLUS1_MS_P) ||
                (aRequest == CT_SP_1PLUS1_EXER_P))
            {
                if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_PROTECTION_COMMAND\n");

                aReturnCondition = C_PROTECTION_COMMAND;
            }
            else 
            {
                if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");

                aReturnCondition = FC_FSM_NO_CONDITION;
            }
        }
    }

    return aReturnCondition;
}


//##ModelId=3937FD4C0023
FC_ConditionId 
SP_1plus1APSController::NoDefectOnWorkingRun(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    FC_ConditionId aReturnCondition = FC_FSM_NO_CONDITION;

    bool clearCommandReceived = myProtectionAction.myRequestParserPtr->GetClearCommand();

    if(clearCommandReceived)
    {
        //If I am revertive: return C_CLEAR_REVERTIVE.
        if(myProtectionAction.Get1plus1Config().GetRevertiveMode())
        {
            if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_CLEAR_REVERTIVE\n");
            aReturnCondition = C_CLEAR_REVERTIVE;
        }
        else //I am not revertive: return C_CLEAR_NOT_REVERTIVE.
        {
            if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_CLEAR_NOT_REVERTIVE\n");
            aReturnCondition = C_CLEAR_NOT_REVERTIVE;
        }
    }


    //If the highest request is a defect on the working: return C_WORKING_DEFECT.
    CT_SP_Request aRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().working;
    
    if( (aRequest == CT_SP_1PLUS1_SD_W) || 
		(aRequest == CT_SP_1PLUS1_SF_LOW_W) ||
        (aRequest == CT_SP_1PLUS1_SF_W))
    {
        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_WORKING_DEFECT\n");

        aReturnCondition = C_WORKING_DEFECT;
    }
    
    if (myProtectionAction.myRequestParserPtr->IsEffectiveRequestFromRemote() &&
        ((aRequest == CT_SP_1PLUS1_RR) || (aRequest == CT_SP_1PLUS1_WTR)))
    {
        if (S_WTR == GetCurrentState() && (aRequest == CT_SP_1PLUS1_RR)) 
        {
            // maitain previous condition
        }
        else
        {
            if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_1PLUS1_REMOTE_REQUEST\n");
            aReturnCondition = C_1PLUS1_REMOTE_REQUEST; 
        }

    }
    
    if (gSP_DebugTraceSnc && aReturnCondition == FC_FSM_NO_CONDITION) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");

    return aReturnCondition;
}


//##ModelId=3937FD4B03B1
void 
SP_1plus1APSController::CommandToProtectionEntry(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    //Get the highest request on the working and set it in the K-bytes.
    CT_SP_Request aWorkingRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().working;

    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        myProtectionAction.PrepareTxApsBytes(1,aWorkingRequest,myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().working);
    }

    myProtectionAction.myK1K2TransmitterPtr->SetRequest(ConvertRequestToK1Request(aWorkingRequest));
}

//##ModelId=3937FD4B0361
FC_ConditionId 
SP_1plus1APSController::CommandToProtectionRun(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    //Get the highest request on the working and set it in the K-bytes.
    CT_SP_Request aWorkingRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().working;

    // remote command is cleared
    if (aWorkingRequest == CT_SP_NO_REQUEST || aWorkingRequest == CT_SP_1PLUS1_DO_NOT_REVERT)
    {
        FC_ConditionId aReturnCondition = FC_FSM_NO_CONDITION;

        //If I am revertive: return C_CLEAR_REVERTIVE.
        if(myProtectionAction.Get1plus1Config().GetRevertiveMode())
        {
            if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_CLEAR_REVERTIVE\n");
            aReturnCondition = C_CLEAR_REVERTIVE;
        }
        else //I am not revertive: return C_CLEAR_NOT_REVERTIVE.
        {
            if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_CLEAR_NOT_REVERTIVE\n");
            aReturnCondition = C_CLEAR_NOT_REVERTIVE;
        }
        return aReturnCondition;
    }

    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        myProtectionAction.PrepareTxApsBytes(1,aWorkingRequest,myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().working);
    }

    myProtectionAction.myK1K2TransmitterPtr->SetRequest(ConvertRequestToK1Request(aWorkingRequest));

    if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");

    return FC_FSM_NO_CONDITION;
}


//##ModelId=3937FD4B0311
void 
SP_1plus1APSController::ProtectionNoRequestEntry(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    //Send DNR (DO NOT REVERT) code.

    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        // Remote request takes effect, send RR.
        if (myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().working)
        {
            myProtectionAction.PrepareTxApsBytes(1, myProtectionAction.myRequestParserPtr->GetHighestRequest().working, true);
        }
        // Lemote request takes effect, send DNR.
        else
        {
            myProtectionAction.PrepareTxApsBytes(1, CT_SP_1PLUS1_DO_NOT_REVERT, false);
        }
    }       

    myProtectionAction.myK1K2TransmitterPtr->SetRequest(SP_1PLUS1_K1_DO_NOT_REVERT);
}

//##ModelId=3937FD4B02C0
FC_ConditionId 
SP_1plus1APSController::ProtectionNoRequestRun(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    // Remote request takes effect, send RR, don't transmit to other states.
    if (myProtectionAction.Get1plus1Config().IsBiSwitching() && 
        myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().working)
    {
        myProtectionAction.PrepareTxApsBytes(1, myProtectionAction.myRequestParserPtr->GetHighestRequest().working, true);

        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- BI and Remote, C_NO_CONDITION\n");

        return FC_FSM_NO_CONDITION;
    }

    //If we are in revertive mode: return C_REVERTIVE.
    if(myProtectionAction.Get1plus1Config().GetRevertiveMode())
    {
        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_REVERTIVE\n");

        return C_REVERTIVE;
    }
    else
    {
        //Send DNR (DO NOT REVERT) code.

        if (myProtectionAction.Get1plus1Config().IsBiSwitching())
        {
            myProtectionAction.PrepareTxApsBytes(1, CT_SP_1PLUS1_DO_NOT_REVERT, false);
        }

        myProtectionAction.myK1K2TransmitterPtr->SetRequest(SP_1PLUS1_K1_DO_NOT_REVERT);

        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");

        return FC_FSM_NO_CONDITION;
    }
}


//##ModelId=3937FD4B027A
void 
SP_1plus1APSController::WTREntry(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    //Send WTR code.
    myProtectionAction.myK1K2TransmitterPtr->SetRequest(SP_1PLUS1_K1_WTR);

    //Start WTR timer using my WTR period config.
    // if WTR period is 0, do not start it.
    if (myProtectionAction.Get1plus1Config().GetWTR() != 0)
        myWTRTimer.Start( (myProtectionAction.Get1plus1Config().GetWTR()*1000) + myProtectionAction.GetWTROffset());

}


//##ModelId=3937FD4B01E4
FC_ConditionId 
SP_1plus1APSController::WTRRun(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    // remote request takes effect
    if (myProtectionAction.Get1plus1Config().IsBiSwitching() && 
        myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().working)
    {
        if ( myProtectionAction.myRequestParserPtr->GetHighestRequest().working == CT_SP_1PLUS1_RR)
    {
            // if request is CT_SP_1PLUS1_RR, stay in WTR status
        }
        else
        {
        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_1PLUS1_REMOTE_REQUEST\n");

        return C_1PLUS1_REMOTE_REQUEST;
    }

    }

    //If we are now in non-revertive mode: return C_NOT_REVERTIVE.
    if(myProtectionAction.Get1plus1Config().GetRevertiveMode() == false)
        return C_NOT_REVERTIVE;

    //If my WTR timer is expired or if not started at all: return C_WTR_EXPIRED.
    if (myWTRTimer.IsExpired() || !myWTRTimer.IsStarted() )
        return C_1PLUS1_WTR_EXPIRED;

    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        myProtectionAction.PrepareTxApsBytes(1, CT_SP_1PLUS1_WTR, false);
    }
    
    return FC_FSM_NO_CONDITION;
}

//##ModelId=3937FD4B022A
void SP_1plus1APSController::WTRExit(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    myWTRTimer.Stop();
}

//##ModelId=3937FD4B019E
void 
SP_1plus1APSController::DefectOnWorkingEntry(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    //Get the highest request on the working and set it in the K-bytes.
    CT_SP_Request aWorkingRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().working;

    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        myProtectionAction.PrepareTxApsBytes(1,aWorkingRequest,myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().working);
    }

    myProtectionAction.myK1K2TransmitterPtr->SetRequest(ConvertRequestToK1Request(aWorkingRequest));
}

//##ModelId=3937FD4B013A
FC_ConditionId 
SP_1plus1APSController::DefectOnworkingRun(FC_StateId theState)
{
    if (gSP_DebugTraceSnc) printf("BISNC:++++: %s\n", __FUNCTION__);

    // Clear any remaining CLEAR command from the request parser
    // to prevent from hiding lower priority request
    myProtectionAction.myRequestParserPtr->GetClearCommand();

    //Get the highest request on the working and set it in the K-bytes.
    CT_SP_Request aWorkingRequest = myProtectionAction.myRequestParserPtr->GetHighestRequest().working;

    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        myProtectionAction.PrepareTxApsBytes(1,aWorkingRequest,myProtectionAction.myRequestParserPtr->GetHighestRequestIsRemote().working);
    }

    myProtectionAction.myK1K2TransmitterPtr->SetRequest(ConvertRequestToK1Request(aWorkingRequest));

    //If I have No Request on the working: return C_WORKING_DEFECT_CLEARED.
    if (aWorkingRequest == CT_SP_NO_REQUEST || aWorkingRequest == CT_SP_1PLUS1_WTR || aWorkingRequest == CT_SP_1PLUS1_DO_NOT_REVERT  || aWorkingRequest == CT_SP_1PLUS1_RR)
    {
        if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_WORKING_DEFECT_CLEARED\n");

        return C_WORKING_DEFECT_CLEARED;
    }

    if (gSP_DebugTraceSnc) printf("BISNC:++++: Condition -- C_NO_CONDITION\n");

    return FC_FSM_NO_CONDITION;
}

//##ModelId=39ACEFCB02CA
FC_ConditionId SP_1plus1APSController::InitRun(FC_StateId theState)
{
    return C_1PLUS1_INIT;
}


//##ModelId=39ACEFCB036A
const char* SP_1plus1APSController::ConvertConditionIdToText(FC_ConditionId theCondition)
{
    switch(theCondition)
    {
    case C_PROTECTION_COMMAND      :    return "C_PROTECTION_COMMAND";
    case C_REVERTIVE               :    return "C_REVERTIVE";
    case C_CLEAR_REVERTIVE         :    return "C_CLEAR_REVERTIVE";
    case C_1PLUS1_WTR_EXPIRED      :    return "C_1PLUS1_WTR_EXPIRED";
    case C_WORKING_HIGHER          :    return "C_WORKING_HIGHER";
    case C_WORKING_DEFECT          :    return "C_WORKING_DEFECT";
    case C_CLEAR_NOT_REVERTIVE     :    return "C_CLEAR_NOT_REVERTIVE";
    case C_NOT_REVERTIVE           :    return "C_NOT_REVERTIVE";
    case C_WORKING_DEFECT_CLEARED  :    return "C_WORKING_DEFECT_CLEARED";
    case C_1PLUS1_INIT             :    return "C_1PLUS1_INIT";
    case C_1PLUS1_SYNC             :    return "C_1PLUS1_SYNC";
    default: FC_THROW_ERROR(FC_RuntimeError,"Invalid condition ID");
        return NULL;
    }
}

//##ModelId=39ACEFCB0342
const char* SP_1plus1APSController::ConvertStateIdToText(FC_StateId theState)
{
    switch(theState)
    {
    case S_WORKING_SELECTED     :return "S_WORKING_SELECTED";
    case S_PROTECTION_SELECTED  :return "S_PROTECTION_SELECTED";
    case S_NO_DEFECT_ON_WORKING :return "S_NO_DEFECT_ON_WORKING";
    case S_COMMAND_TO_PROTECTION:return "S_COMMAND_TO_PROTECTION";
    case S_PROTECTION_NO_REQUEST:return "S_PROTECTION_NO_REQUEST";
    case S_WTR                  :return "S_WTR";
    case S_DEFECT_ON_WORKING    :return "S_DEFECT_ON_WORKING";
    case S_1PLUS1_INIT          :return "S_1PLUS1_INIT";
    default: FC_THROW_ERROR(FC_RuntimeError,"Invalid state ID"); return NULL;
    }
}

//##ModelId=3B8BC9FC02DA
const char* SP_1plus1APSController::ConvertTransitionIdToText(FC_TransitionId theTransition)
{
    switch(theTransition)
    {
    case T_WORKING_SELECTED_2_COMMAND_TO_PROTECTION        : return "T_WORKING_SELECTED_2_COMMAND_TO_PROTECTION";
    case T_PROTECTION_SELECTED_2_COMMAND_TO_PROTECTION     : return "T_PROTECTION_SELECTED_2_COMMAND_TO_PROTECTION";
    case T_PROTECTION_NO_REQUEST_2_WORKING_SELECTED        : return "T_PROTECTION_NO_REQUEST_2_WORKING_SELECTED";
    case T_NO_DEFECT_ON_WORKING_2_WORKING_SELECTED         : return "T_NO_DEFECT_ON_WORKING_2_WORKING_SELECTED";
    case T_WTR_2_WORKING_SELECTED                          : return "T_WTR_2_WORKING_SELECTED";
    case T_PROTECTION_SELECTED_2_WORKING_SELECTED          : return "T_PROTECTION_SELECTED_2_WORKING_SELECTED";
    case T_WORKING_SELECTED_2_DEFECT_ON_WORKING            : return "T_WORKING_SELECTED_2_DEFECT_ON_WORKING";
    case T_COMMAND_TO_PROTECTION_2_PROTECTION_NO_REQUEST   : return "T_COMMAND_TO_PROTECTION_2_PROTECTION_NO_REQUEST";
    case T_WTR_2_PROTECTION_NO_REQUEST                     : return "T_WTR_2_PROTECTION_NO_REQUEST";
    case T_DEFECT_ON_WORKING_2_WTR                         : return "T_DEFECT_ON_WORKING_2_WTR";
    case T_NO_DEFECT_ON_WORKING_2_DEFECT_ON_WORKING        : return "T_NO_DEFECT_ON_WORKING_2_DEFECT_ON_WORKING";
    case T_1PLUS1_INIT_2_WORKING_SELECTED                  : return "T_1PLUS1_INIT_2_WORKING_SELECTED";
    case T_1PLUS1_SYNC                                     : return "T_1PLUS1_SYNC";
    default: FC_THROW_ERROR(FC_RuntimeError, "Invalid transition ID"); return NULL;
    }
}

//##ModelId=3B8BC9FC02C6
bool SP_1plus1APSController::HasChangedSinceLastCheck()
{
    bool hasChanged = SP_APSController::HasChangedSinceLastCheck();

    if (!hasChanged &&
        (myLastState == GetCurrentState()))
    {
        return false;
    }
    else
    {
        myLastState = GetCurrentState();
        return true;
    }
}

//##ModelId=3B8BC9FC028A
ostream& SP_1plus1APSController::WriteObject( ostream& theStream )
{
    SP_APSController::WriteObject(theStream);

    FC_StateId currentState = GetCurrentState();

    theStream<<FC_InsertVar(currentState);

    return theStream;
}

//##ModelId=3B8BC9FC0258
istream& SP_1plus1APSController::ReadObject( istream& theStream )
{
    FC_StateId aState;

    SP_APSController::ReadObject(theStream);

    theStream>>FC_ExtractVar(aState);

    Restart(aState, C_1PLUS1_SYNC, T_1PLUS1_SYNC);

    myLastState = GetCurrentState();

    return theStream;
}

//##ModelId=3B8BC9FC0226
FC_Stream& SP_1plus1APSController::WriteObjectBinary( FC_Stream& theStream )
{
    SP_APSController::WriteObjectBinary(theStream);

    theStream<<GetCurrentState();

    return theStream;
}

//##ModelId=3B8BC9FC01F4
FC_Stream& SP_1plus1APSController::ReadObjectBinary( FC_Stream& theStream )
{
    FC_StateId aState;

    SP_APSController::ReadObjectBinary(theStream);

    theStream>>aState;

    Restart(aState, C_1PLUS1_SYNC, T_1PLUS1_SYNC);

    myLastState = GetCurrentState();

    return theStream;
}

