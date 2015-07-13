// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../SP_EqptRedundFSM.h"
#include "../SP_ERSIF.h"
#include "../SP_ERSSwitchRegion.h"
#include "../SP_ERSSwitchResultRegion.h"
#include <BaseClass/FC_TextStream.h>
#include <Blackboard/FC_BbAction.h>
#include <Blackboard/FC_BoolRegion.h>
#include <CsPii/CSPII_ProtRam.h>
#include <CsPii/CSPII_AppParams.h>
#include <T6100_ControllerStatusRegion.h>

bool gEqptRdTrc = true;
bool gVerboseEqptRdTrc = false;
const FC_Milliseconds ERS_HOLDOFF_FOR_MATE_ACTIVE = 5 * 1000; //5 secs

//----------------------------------------------------------------------------
//STATE MACHINE RELATED STUFF
//----------------------------------------------------------------------------

//##ModelId=39170C470094
bool SP_EqptRedundFSM::fsmIsInitialized = false;

//============================================================================
//The order of appearance of the following macros is critical, it must follow
//the order in which the states and transitions are added to the Fsm. 
//
//See the InitFsm method below for the order.
//============================================================================

FC_FSM_STATE_FCT_BEGIN(SP_EqptRedundFSM)
    FC_FSM_STATE_FCT_ADD(FC_FsmClientImp<SP_EqptRedundFSM>::EntryNoCode,
                         SP_EqptRedundFSM::InitExit,
                         SP_EqptRedundFSM::InitRun)
    FC_FSM_STATE_FCT_ADD(SP_EqptRedundFSM::ActiveEntry,
                         SP_EqptRedundFSM::ActiveExit,
                         SP_EqptRedundFSM::ActiveRun)
    FC_FSM_STATE_FCT_ADD(SP_EqptRedundFSM::StandbyEntry,
                         SP_EqptRedundFSM::StandbyExit,
                         SP_EqptRedundFSM::StandbyRun)
    FC_FSM_STATE_FCT_ADD(SP_EqptRedundFSM::SwitchStandbyEntry,
                         SP_EqptRedundFSM::SwitchStandbyExit,
                         SP_EqptRedundFSM::SwitchStandbyRun)
FC_FSM_STATE_FCT_END(SP_EqptRedundFSM)

FC_FSM_TRANSITION_FCT_BEGIN(SP_EqptRedundFSM)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_EqptRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_EqptRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_EqptRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_EqptRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_EqptRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_EqptRedundFSM>::TransitionNoCode)
FC_FSM_TRANSITION_FCT_END(SP_EqptRedundFSM)


//##ModelId=39170C470116
void SP_EqptRedundFSM::InitFsm(FC_Fsm& theFsm)
{
    // don't initialize state machine twice
    if (fsmIsInitialized)
        return;

    // Register states and transition here....
    //             | the new state
    //             | the parent state       | has entry code | has exit code
    theFsm.AddState(S_ERS_EQPT_INIT,
                    FC_FSM_NIL_STATE,           false,           true);

    theFsm.AddState(S_ERS_EQPT_ACTIVE,
                    FC_FSM_NIL_STATE,           true,            true);

    theFsm.AddState(S_ERS_EQPT_STANDBY,
                    FC_FSM_NIL_STATE,           true,            true);

    theFsm.AddState(S_ERS_EQPT_SWITCH_STNBY,
                    FC_FSM_NIL_STATE,           true,            true);


    theFsm.SetInitialState(S_ERS_EQPT_INIT);

//                      | from state       |to state                           
//                      | the condition              
//                      | the transition 
//                      | has code

    theFsm.AddTransition(S_ERS_EQPT_INIT,S_ERS_EQPT_ACTIVE,
                         C_ERS_ACTIVE_MODE,
                         T_ERS_EQPT_INIT_2_ACTIVE,
                         false);

    theFsm.AddTransition(S_ERS_EQPT_INIT,S_ERS_EQPT_STANDBY,
                         C_ERS_STBY_MODE,
                         T_ERS_EQPT_INIT_2_STANDBY,
                         false);

    theFsm.AddTransition(S_ERS_EQPT_ACTIVE,S_ERS_EQPT_STANDBY,
                         C_ERS_STBY_MODE,
                         T_ERS_EQPT_ACTIVE_2_STANDBY,
                         false);

    theFsm.AddTransition(S_ERS_EQPT_ACTIVE,S_ERS_EQPT_SWITCH_STNBY,
                         C_ERS_SWITCH_COMMAND,
                         T_ERS_EQPT_ACTIVE_2_SWITCH_STNBY,
                         false);

    theFsm.AddTransition(S_ERS_EQPT_SWITCH_STNBY,S_ERS_EQPT_STANDBY,
                         C_ERS_STBY_MODE,
                         T_ERS_EQPT_SWITCH_STNBY_2_STANDBY,
                         false);

    theFsm.AddTransition(S_ERS_EQPT_STANDBY,S_ERS_EQPT_ACTIVE,
                         C_ERS_ACTIVE_MODE,
                         T_ERS_EQPT_STANDBY_2_ACTIVE,
                         false);

    fsmIsInitialized = true;
}


//##ModelId=390584010156
SP_EqptRedundFSM::SP_EqptRedundFSM(FC_Fsm& theFsm, SP_ERSIF& theERSImpl,
                                   T6100_ControllerStatusRegion* theModeRegion,
                                   SP_ERSSwitchRegion* theSwitchRegion,
                                   SP_ERSSwitchResultRegion* theSwitchResultRegion,
                                   CT_SlotId theSlot,
                                   CT_SlotId theMateSlot):
    FC_FsmClientImp<SP_EqptRedundFSM>(theFsm, 1, NULL),
    myLastState(FC_FSM_NIL_STATE),
    myEqptRSImpl(theERSImpl),
    myModeRegion(theModeRegion),
    myPrevCounter(0),
    myLastCommandID(CT_SP_INVALID_COMMAND),
    ourSwitchRegion(theSwitchRegion),
    ourSwitchResultRegion(theSwitchResultRegion),
    mySlot(theSlot),
    myMateSlot(theMateSlot),
    myTimerHasStarted(false),
    myWaitTimer(ERS_HOLDOFF_FOR_MATE_ACTIVE)
{
}

//##ModelId=390584010188
SP_EqptRedundFSM::~SP_EqptRedundFSM()
{
}


//##ModelId=3937FD4C0181
void SP_EqptRedundFSM::ActiveEntry(FC_StateId theState)
{
    //Master entry function
    //Set PRAM to indicate that we are master
    if (gEqptRdTrc)
    {
        fc_cout << "SP_EqptRedundFSM::ActiveEntry Writing pref active and stnby no pref to PROT RAM" << endl;
    }
    //Set preference to say active
    CSPII_ProtRam_SetControllerActivePreference(ERS_PREFERENCE);
    CSPII_ProtRam_SetControllerStbyPreference(ERS_NO_PREFERENCE);

    //Update activity status
    if (myModeRegion)
    {
        myModeRegion->SetControllerMode(ACTIVE_MODE);
        myModeRegion->IncModificationCounter();
        myModeRegion->UpdateNotify();
    }

    myEqptRSImpl.SetHeartBeatState(true); /*Turn on heartbeat*/

    //Indicate the active/standby slot in the switch result region
    if (ourSwitchResultRegion)
    {
        (*ourSwitchResultRegion)[0].SetActiveSlot(mySlot);
        (*ourSwitchResultRegion)[0].SetStandbySlot(myMateSlot);
        (*ourSwitchResultRegion)[0].SetLastProcessedCommandID(myLastCommandID);
        ourSwitchResultRegion->IncModificationCounter(); 
    }

    //Update LED status (if supported)
    myEqptRSImpl.ControlActiveLED(true);

    myPrevCounter =0;
}
	
void SP_EqptRedundFSM::ActiveExit(FC_StateId theState)
{
    //Master exit function

    //Release mastership
    myEqptRSImpl.ReleaseMastership();
    //Stop the heartbeat
    myEqptRSImpl.SetHeartBeatState(false);
    //Clear counter
    myPrevCounter =0;

    //Clear the active/standby slot in the switch result region
    if (ourSwitchResultRegion)
    {
        (*ourSwitchResultRegion)[0].SetActiveSlot(UNKNOWN_SLOT_ID);
        (*ourSwitchResultRegion)[0].SetStandbySlot(UNKNOWN_SLOT_ID);
        (*ourSwitchResultRegion)[0].SetLastProcessedCommandID(myLastCommandID);
        ourSwitchResultRegion->IncModificationCounter(); 
    }
}
    
FC_ConditionId SP_EqptRedundFSM::ActiveRun(FC_StateId theState)
{
    if (myEqptRSImpl.IsMateReady() && myEqptRSImpl.IsMateMaster())
    {
        //Dual master scenario
        if (myPrevCounter == 0)
        {
            myPrevCounter = myEqptRSImpl.GetRxMessageCounter();
        }
        else
        {
            if (myPrevCounter != myEqptRSImpl.GetRxMessageCounter())
            {
                if (gEqptRdTrc)
                {
                    fc_cout << "SP_EqptRedundFSM::ActiveRun: Dual master scenario detected..attempting to correct" <<endl;
                }
                myPrevCounter =0;
                return C_ERS_STBY_MODE; /*No need to synchronize with other side*/
            }
        }
    }
    else
    {
        myPrevCounter =0;
    }

    //Check whether there are any conditions that should trigger a switch
    //These include auto switches, manual switches
    if (myEqptRSImpl.IsModuleOOS())
    {
        return C_ERS_SWITCH_COMMAND;
    }

    if (ourSwitchRegion)
    {
        if (ourSwitchRegion->IsValid())
        {
            if ( myLastCommandID != ourSwitchRegion->GetCommandID() )
            {
                //Check whether the mate has seen and accepted this command prior to acting on the command
                if (ourSwitchRegion->GetCommand() == CT_SP_1PLUS1_MS_P)
                {
                    if (myEqptRSImpl.GetRxERSMessage() == ourSwitchRegion->GetCommandID())
                    {
                        myEqptRSImpl.SetTxERSMessage(ourSwitchRegion->GetCommandID());
                        myLastCommandID = ourSwitchRegion->GetCommandID();
                        return C_ERS_SWITCH_COMMAND;
                    }
                    else
                    {
                        if (gEqptRdTrc)
                        {
                            fc_cout << "SP_EqptRedundFSM::ActiveRun: Waiting for mate acknowledgement to manual switch command" <<endl;
                        }
                        myEqptRSImpl.SetTxERSMessage(ourSwitchRegion->GetCommandID());
                        return FC_FSM_NO_CONDITION;
                    }
                }
            }
        }
    }

    return FC_FSM_NO_CONDITION;
}

	
void SP_EqptRedundFSM::StandbyEntry(FC_StateId theState)
{
    if (gEqptRdTrc)
    {
        fc_cout << "SP_EqptRedundFSM::StandbyEntry: Writing no pref active and pref stnby to PROT RAM" << endl;
    }
    		
    //Set preference to say inactive
    CSPII_ProtRam_SetControllerActivePreference(ERS_NO_PREFERENCE);
    CSPII_ProtRam_SetControllerStbyPreference(ERS_PREFERENCE);

    if (myModeRegion)
    {
        myModeRegion->SetControllerMode(STNBY_MODE);
        myModeRegion->IncModificationCounter();
        myModeRegion->UpdateNotify();
    }

    //Indicate the active/standby slot in the switch result region
    if (ourSwitchResultRegion)
    {
        (*ourSwitchResultRegion)[0].SetActiveSlot(myMateSlot);
        (*ourSwitchResultRegion)[0].SetStandbySlot(mySlot);
        (*ourSwitchResultRegion)[0].SetLastProcessedCommandID(myLastCommandID);
        ourSwitchResultRegion->IncModificationCounter(); 
    }

    //Update LED status (if supported)
    myEqptRSImpl.ControlActiveLED(false);
}

void SP_EqptRedundFSM::StandbyExit(FC_StateId theState)
{

    //Clear the active/standby slot in the switch result region
    if (ourSwitchResultRegion)
    {
        (*ourSwitchResultRegion)[0].SetActiveSlot(UNKNOWN_SLOT_ID);
        (*ourSwitchResultRegion)[0].SetStandbySlot(UNKNOWN_SLOT_ID);
        (*ourSwitchResultRegion)[0].SetLastProcessedCommandID(myLastCommandID);
        ourSwitchResultRegion->IncModificationCounter(); 
    }
}

FC_ConditionId SP_EqptRedundFSM::StandbyRun(FC_StateId theState)
{
    //Set hearbeat state appropriately.
    //Try to acquire ers mastership if needed
    if (!myEqptRSImpl.IsMaster())
    {
        //Only try to acquire mastership if the module is allowed to do so
        if (!myEqptRSImpl.IsModuleOOS())
        {
            if (!myEqptRSImpl.IsMateMaster() && myEqptRSImpl.IsMateReady())
            {
                myEqptRSImpl.AcquireMastership();
            }
            else if (myEqptRSImpl.IsMateMaster())
            {
                myEqptRSImpl.SetHeartBeatState(true); /*Turn on heartbeat since module is IS and mate is master*/
            }
        }
        else
        {
            myEqptRSImpl.SetHeartBeatState(false); /*Turn off heartbeat since module is OOS*/
            if (gVerboseEqptRdTrc)
            {
                fc_cout << "SP_EqptRedundFSM::StandbyRun: Mate is not master but I can't take over due to OOS state" <<endl;
            }
        }
    }

    if (myEqptRSImpl.IsMaster())
    {
        if (gEqptRdTrc)
        {
            fc_cout << "SP_EqptRedundFSM::StandbyRun: Mastership acquired..transitioning for takeover" <<endl;
        }
        //Save off last processed command id
        if (ourSwitchRegion)
        {
            myLastCommandID = ourSwitchRegion->GetCommandID();
        }
        //If mastership was acquired, start the transition to active
        return C_ERS_ACTIVE_MODE;
    }

    //Check to see whether a manual command is pending. If so then send request id to mate and wait for response
    if (ourSwitchRegion)
    {
        if (ourSwitchRegion->IsValid())
        {
            if ( myLastCommandID != ourSwitchRegion->GetCommandID() )
            {
                //Check whether the mate has seen and accepted this command prior to acting on the command
                if (ourSwitchRegion->GetCommand() == CT_SP_1PLUS1_MS_P)
                {
                    myEqptRSImpl.SetTxERSMessage(ourSwitchRegion->GetCommandID());
                }
            }
        }
    }

    return FC_FSM_NO_CONDITION;
}

void SP_EqptRedundFSM::SwitchStandbyEntry(FC_StateId theState)
{
    //Start the wait timer
    myWaitTimer.Start();
    myTimerHasStarted = true;
}

void SP_EqptRedundFSM::SwitchStandbyExit(FC_StateId theState)
{
    //Cancel timer
    myTimerHasStarted = false;
}
    

FC_ConditionId SP_EqptRedundFSM::SwitchStandbyRun(FC_StateId theState)
{
    //Wait here until the mate has become master or the wait timer has expired
    //@TO DO: Do we need to check present??
    if ( (myEqptRSImpl.IsMateMaster()) || (myTimerHasStarted && myWaitTimer.IsExpired()) )
    {
        return C_ERS_STBY_MODE;
    }

    return FC_FSM_NO_CONDITION;
}

FC_ConditionId SP_EqptRedundFSM::InitRun(FC_StateId theState)
{
    bool allowedToInit = ( (myEqptRSImpl.InitOnOOSAllowed() == true) || ( myEqptRSImpl.InitOnOOSAllowed() == false && myEqptRSImpl.IsModuleOOS() == false) );

    if (allowedToInit)
    {
        //If previously configured as standby
        if (CSPII_ProtRam_GetControllerActivePreference() == ERS_NO_PREFERENCE &&
            CSPII_ProtRam_GetControllerStbyPreference() == ERS_PREFERENCE)
        {
            //If mate is ready, then transition
            if (myEqptRSImpl.IsMateReady())
            {
                if (gEqptRdTrc)
                {
                    fc_cout << "SP_EqptRedundFSM::InitRun: Transitioning to standby mode due to PRAM settings" <<endl;
                }

                myEqptRSImpl.ReleaseMastership();
                return C_ERS_STBY_MODE;
            }
            else
            {
                //To let the other side know of state
                myEqptRSImpl.SendERSMessage(STNBY_MODE);
                return FC_FSM_NO_CONDITION;
            }
        }
        else
        {
            if (myEqptRSImpl.IsMateReady())
            {
                myEqptRSImpl.AcquireMastership();
                if (myEqptRSImpl.IsMaster() == true)
                {
                    if (gEqptRdTrc)
                    {
                        fc_cout << "SP_EqptRedundFSM::InitRun: Transitioning to active mode" <<endl;
                    }
                    return C_ERS_ACTIVE_MODE;
                }
                else
                {
                    if (gEqptRdTrc)
                    {
                        fc_cout << "SP_EqptRedundFSM::InitRun: Transitioning to standby mode" <<endl;
                    }
                    return C_ERS_STBY_MODE;
                }
            }
            else
            {
                if (CSPII_ProtRam_GetControllerActivePreference() == ERS_PREFERENCE &&
                    CSPII_ProtRam_GetControllerStbyPreference() == ERS_NO_PREFERENCE)
                {
                    //To let the other side know of state
                    myEqptRSImpl.SendERSMessage(ACTIVE_MODE);
                }
                else
                {
                    //To let the other side know of state
                    myEqptRSImpl.SendERSMessage(STNBY_MODE);
                }
                return FC_FSM_NO_CONDITION;
            }
        }
        return FC_FSM_NO_CONDITION;
    }
    else
    {
        if (gVerboseEqptRdTrc)
        {
            fc_cout << "SP_EqptRedundFSM::InitRun: ERS init waiting due to OOS state!!!!" <<endl;
        }
        return FC_FSM_NO_CONDITION;
    }
}

void SP_EqptRedundFSM::InitExit(FC_StateId theState)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Helper functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////


//##ModelId=39ACEFCB036A
const char* SP_EqptRedundFSM::ConvertConditionIdToText(FC_ConditionId theCondition)
{
    switch(theCondition)
    {
    case C_ERS_ACTIVE_MODE                :    return "C_ERS_ACTIVE_MODE"; break;
    case C_ERS_STBY_MODE                  :    return "C_ERS_STBY_MODE"; break;
    case C_ERS_SWITCH_COMMAND             :    return "C_ERS_SWITCH_COMMAND"; break;
    default: FC_THROW_ERROR(FC_RuntimeError,"Invalid condition ID");
        return NULL;
    }
}

//##ModelId=39ACEFCB0342
const char* SP_EqptRedundFSM::ConvertStateIdToText(FC_StateId theState)
{
    switch(theState)
    {
    case S_ERS_EQPT_INIT               :return "S_ERS_EQPT_INIT"; break;     
    case S_ERS_EQPT_ACTIVE             :return "S_ERS_EQPT_ACTIVE"; break;  
    case S_ERS_EQPT_STANDBY            :return "S_ERS_EQPT_STANDBY"; break; 
    case S_ERS_EQPT_SWITCH_STNBY       :return "S_ERS_EQPT_SWITCH_STNBY"; break;
    default: FC_THROW_ERROR(FC_RuntimeError,"Invalid state ID"); return NULL;
    }
}

//##ModelId=3B8BC9FC02DA
const char* SP_EqptRedundFSM::ConvertTransitionIdToText(FC_TransitionId theTransition)
{
    switch(theTransition)
    {
    case T_ERS_EQPT_INIT_2_ACTIVE                : return "T_ERS_EQPT_INIT_2_ACTIVE";          break;
    case T_ERS_EQPT_INIT_2_STANDBY               : return "T_ERS_EQPT_INIT_2_STANDBY";         break;
    case T_ERS_EQPT_ACTIVE_2_STANDBY             : return "T_ERS_EQPT_ACTIVE_2_STANDBY";       break;
    case T_ERS_EQPT_ACTIVE_2_SWITCH_STNBY        : return "T_ERS_EQPT_ACTIVE_2_SWITCH_STNBY";  break;
    case T_ERS_EQPT_SWITCH_STNBY_2_STANDBY       : return "T_ERS_EQPT_SWITCH_STNBY_2_STANDBY"; break;
    case T_ERS_EQPT_STANDBY_2_ACTIVE             : return "T_ERS_EQPT_STANDBY_2_ACTIVE";       break;
    
                                            
    default: FC_THROW_ERROR(FC_RuntimeError, "Invalid transition ID"); return NULL;
    }
}

//##ModelId=3B8BC9FC02C6
bool SP_EqptRedundFSM::HasChangedSinceLastCheck()
{
    bool hasChanged =false;

    if (myLastState == GetCurrentState())
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
ostream& SP_EqptRedundFSM::WriteObject( ostream& theStream )
{
    return theStream;
}

//##ModelId=3B8BC9FC0258
istream& SP_EqptRedundFSM::ReadObject( istream& theStream )
{
    return theStream;
}

//##ModelId=3B8BC9FC0226
FC_Stream& SP_EqptRedundFSM::WriteObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

//##ModelId=3B8BC9FC01F4
FC_Stream& SP_EqptRedundFSM::ReadObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

void SP_EqptRedundFSM::SetDebugTraceMode(bool theMode)
{
    if (theMode ==true)
    {
        gEqptRdTrc = true;
    }
    else
    {
        gEqptRdTrc = false;
    }
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//Action that runs the above state machine
FC_Fsm SP_EqptRedundAction::ourFsm;

//-----------------------------------------------------------------------------
SP_EqptRedundAction::SP_EqptRedundAction(
    SP_ERSIF& theERSImpl,
    T6100_ControllerStatusRegion* theModeRegion,
    SP_ERSSwitchRegion* theSwitchRegion,
    SP_ERSSwitchResultRegion* theSwitchResultRegion,
    FC_BoolRegion* theIsrMonRegion,
    CT_SlotId theSlot,
    CT_SlotId theMateSlot):
    myModeRegion(theModeRegion),
    myIsrMonRegion(theIsrMonRegion),
    mySwitchResultRegion(theSwitchResultRegion)
{
    // Make sure the FSM is initialized before creating our FSM.
    SP_EqptRedundFSM::InitFsm(ourFsm);
    myFsmImplPtr   = new SP_EqptRedundFSM(ourFsm, theERSImpl, theModeRegion, theSwitchRegion, theSwitchResultRegion, theSlot, theMateSlot);
    myBbAction = new FC_BbAction(this);
    if (myIsrMonRegion)
    {
        myBbAction->AddInputRegion(myIsrMonRegion, false);
    }
    if (mySwitchResultRegion)
    {
        myBbAction->AddOutputRegion(mySwitchResultRegion, false, false, false);
    }
}

//-----------------------------------------------------------------------------
SP_EqptRedundAction::~SP_EqptRedundAction()
{
    if (myIsrMonRegion)
    {
        myBbAction->RemoveInputRegion(myIsrMonRegion);
    }

    if (mySwitchResultRegion)
    {
        myBbAction->RemoveOutputRegion(mySwitchResultRegion);
    }

    delete myBbAction;
    delete myFsmImplPtr;
}

//-----------------------------------------------------------------------------
void SP_EqptRedundAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//-----------------------------------------------------------------------------
FC_Object* SP_EqptRedundAction::DoRunWithReason(unsigned theRunReason,
                                                  FC_Object* theInvokerObj,
                                                  FC_Object* theParam)
{
    //Run the state machine
    myFsmImplPtr->Run(theInvokerObj);

    //Update the switch result region if we are initialized
    if (myFsmImplPtr->GetCurrentState() != S_ERS_EQPT_INIT)
    {
        if (mySwitchResultRegion)
        {
            mySwitchResultRegion->UpdateNotify();
        }
    }

    return NULL;
}



