// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../SP_TimingRedundFSM.h"
#include "../SP_TimingRSIF.h"
#include "../SP_TimingModeRegion.h"
#include <BaseClass/FC_TextStream.h>
#include <Blackboard/FC_BoolRegion.h>
#include <Blackboard/FC_BbAction.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_SyncStatus.h>

const FC_Milliseconds SP_TIMING_REDUND_OPER_TIMEOUT = 5 * 1000; //5 secs
const FC_Milliseconds SP_TIMING_REDUND_HOLDOFF_TIMER = 30 * 1000; //30 secs
bool gTmgRdTrc = true;

//----------------------------------------------------------------------------
//STATE MACHINE RELATED STUFF
//----------------------------------------------------------------------------

//##ModelId=39170C470094
bool SP_TimingRedundFSM::fsmIsInitialized = false;

//============================================================================
//The order of appearance of the following macros is critical, it must follow
//the order in which the states and transitions are added to the Fsm. 
//
//See the InitFsm method below for the order.
//============================================================================

FC_FSM_STATE_FCT_BEGIN(SP_TimingRedundFSM)
    FC_FSM_STATE_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::EntryNoCode,
                         SP_TimingRedundFSM::InitExit,
                         SP_TimingRedundFSM::InitRun)
	FC_FSM_STATE_FCT_ADD(SP_TimingRedundFSM::MasterEntry,
                         SP_TimingRedundFSM::MasterExit,
                         SP_TimingRedundFSM::MasterRun)
    FC_FSM_STATE_FCT_ADD(SP_TimingRedundFSM::SlaveEntry,
                         SP_TimingRedundFSM::SlaveExit,
                         SP_TimingRedundFSM::SlaveRun)
    FC_FSM_STATE_FCT_ADD(SP_TimingRedundFSM::HoldoverEntry,
                         SP_TimingRedundFSM::HoldoverExit,
                         SP_TimingRedundFSM::HoldoverRun)
FC_FSM_STATE_FCT_END(SP_TimingRedundFSM)

FC_FSM_TRANSITION_FCT_BEGIN(SP_TimingRedundFSM)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::TransitionNoCode)
    FC_FSM_TRANSITION_FCT_ADD(FC_FsmClientImp<SP_TimingRedundFSM>::TransitionNoCode)
FC_FSM_TRANSITION_FCT_END(SP_TimingRedundFSM)


//##ModelId=39170C470116
void SP_TimingRedundFSM::InitFsm(FC_Fsm& theFsm)
{
    // don't initialize state machine twice
    if (fsmIsInitialized)
        return;

    // Register states and transition here....
    //             | the new state
    //             | the parent state       | has entry code | has exit code
    theFsm.AddState(S_TMG_INIT,
                    FC_FSM_NIL_STATE,           false,           true);

    theFsm.AddState(S_MASTER,
                    FC_FSM_NIL_STATE,           true,            true);

    theFsm.AddState(S_SLAVE,
                    FC_FSM_NIL_STATE,           true,            true);

    theFsm.AddState(S_HOLDOVER,
                    FC_FSM_NIL_STATE,           true,            true);


    theFsm.SetInitialState(S_TMG_INIT);

//                      | from state       |to state                           
//                      | the condition              
//                      | the transition 
//                      | has code

    theFsm.AddTransition(S_TMG_INIT,S_HOLDOVER,
                         C_HOLDOVER_MODE,
                         T_TMG_INIT_2_HOLDOVER,
                         false);

    theFsm.AddTransition(S_TMG_INIT,S_MASTER,
                         C_MASTER_MODE,
                         T_TMG_INIT_2_MASTER,
                         false);

    theFsm.AddTransition(S_TMG_INIT,S_SLAVE,
                         C_SLAVE_MODE,
                         T_TMG_INIT_2_SLAVE,
                         false);

    theFsm.AddTransition(S_MASTER,S_HOLDOVER,
                         C_HOLDOVER_MODE,
                         T_MASTER_2_HOLDOVER,
                         false);

    theFsm.AddTransition(S_SLAVE,S_HOLDOVER,
                         C_HOLDOVER_MODE,
                         T_SLAVE_2_HOLDOVER,
                         false);

	theFsm.AddTransition(S_HOLDOVER,S_MASTER,
                         C_MASTER_MODE,
                         T_HOLDOVER_2_MASTER,
                         false);

	theFsm.AddTransition(S_HOLDOVER,S_SLAVE,
                         C_SLAVE_MODE,
                         T_HOLDOVER_2_SLAVE,
                         false);

    fsmIsInitialized = true;
}


//##ModelId=390584010156
SP_TimingRedundFSM::SP_TimingRedundFSM(FC_Fsm& theFsm,
                                       SP_TimingRSIF& theTmgRSImpl,
									   CSM_CardConfigStatusRegion& theUsrCfgRegion,
					                   FC_BoolRegion& theControlRegion):
    FC_FsmClientImp<SP_TimingRedundFSM>(theFsm, 1, NULL),
    myLastState(FC_FSM_NIL_STATE),
    myTimingRSImpl(theTmgRSImpl),
    myUsrCfgRegion(theUsrCfgRegion),
    myControlRegion(theControlRegion),
	myTimeoutTimerHasStarted(false),
    myTimeoutTimer(SP_TIMING_REDUND_OPER_TIMEOUT),
    myHoldOffTimerHasStarted(false),
    myHoldOffTimer(SP_TIMING_REDUND_HOLDOFF_TIMER)
{
}

//##ModelId=390584010188
SP_TimingRedundFSM::~SP_TimingRedundFSM()
{
}


//##ModelId=3937FD4C0181
void SP_TimingRedundFSM::MasterEntry(FC_StateId theState)
{
	//Master entry function
	//Allow hw auto switch
	//Set timing mode to master
	myTimingRSImpl.SetHwAutoSwitchMode(true); //Enable HW auto switch
	myTimingRSImpl.SetClockMode(CT_TEL_CLKMODE_MASTER);
	if (gTmgRdTrc)
	    fc_cout << "SP_TimingRedundFSM::MasterEntry: Setting timing mode to master" <<endl;
}
	
void SP_TimingRedundFSM::MasterExit(FC_StateId theState)
{
	//Master exit function
	//Modify  control to indicate OOS
	myControlRegion.Set(true);
	myControlRegion.IncModificationCounter();

	//Set timing mode to holdover
	myTimingRSImpl.SetClockMode(CT_TEL_CLKMODE_HOLDOVER);
    
	//Release timing mastership
	myTimingRSImpl.ReleaseTimingMastership();

	if (gTmgRdTrc)
	{
	    fc_cout << "SP_TimingRedundFSM::MasterExit: Setting timing mode to hold" <<endl;
		fc_cout << "SP_TimingRedundFSM::MasterExit: Setting  Control Region to OOS" <<endl;
		fc_cout << "SP_TimingRedundFSM::MasterExit: Releasing timing mastership" <<endl;
	}
}
    
FC_ConditionId SP_TimingRedundFSM::MasterRun(FC_StateId theState)
{
    //Get the tx ssm value for selected master reference
    myTimingRSImpl.RetrieveSelectedTxSsm();

    //If user configured as master, bypass all redundancy operation
    if (myTimingRSImpl.IsConfiguredMaster())
        return FC_FSM_NO_CONDITION;

    //If a condition that requires a switch or user has changed configured then cause a transition
    if (myTimingRSImpl.IsSwitchRequired() || myTimingRSImpl.HasConfigurationChanged())
	{
		if (gTmgRdTrc)
		{
	        fc_cout << "SP_TimingRedundFSM::MasterRun: Switching condition detected...transitioning to hold for switch" <<endl;
		}
		return C_HOLDOVER_MODE;
	}
	return FC_FSM_NO_CONDITION;
}

	
void SP_TimingRedundFSM::SlaveEntry(FC_StateId theState)
{
	//Enable/disable hardware auto switch based on configuration
	CSM_PersistentConfigStatus* aPersConfigPtr = &(myUsrCfgRegion[0]);
	CT_AdministrativeConfigType theCardAdminState = aPersConfigPtr->GetAdministrativeConfig();
    if (theCardAdminState == CARD_UNLOCK)
	{
		myTimingRSImpl.SetHwAutoSwitchMode(true); //Enable HW auto switch
	}
	else
	{
		myTimingRSImpl.SetHwAutoSwitchMode(false); //Disable HW auto switch since module is OOS
	}


	//Set timing mode to slave
	myTimingRSImpl.SetClockMode(CT_TEL_CLKMODE_SLAVE);

	if (gTmgRdTrc)
	{
	    fc_cout << "SP_TimingRedundFSM::SlaveEntry: Setting timing mode to slave" <<endl;
	}
}

void SP_TimingRedundFSM::SlaveExit(FC_StateId theState)
{
	//Set timing mode to holdover
	myTimingRSImpl.SetClockMode(CT_TEL_CLKMODE_HOLDOVER);
    
	if (gTmgRdTrc)
	{
	    fc_cout << "SP_TimingRedundFSM::SlaveExit: Setting timing mode to hold" <<endl;
	}
}

FC_ConditionId SP_TimingRedundFSM::SlaveRun(FC_StateId theState)
{

    //Retrieve the tx ssm value
    myTimingRSImpl.RetrieveSelectedTxSsm();

    //If user configured as slave, bypass all redundancy operation
    if (myTimingRSImpl.IsConfiguredSlave())
        return FC_FSM_NO_CONDITION;


	CSM_PersistentConfigStatus* aPersConfigPtr = &(myUsrCfgRegion[0]);
	CT_AdministrativeConfigType theCardAdminState = aPersConfigPtr->GetAdministrativeConfig();
	//Only attempt to do anything if our module is in service
    if (theCardAdminState == CARD_UNLOCK)
	{
		//Set the clock mode to slave
		//SetClockMode(CT_TEL_CLKMODE_SLAVE);
		myTimingRSImpl.SetHwAutoSwitchMode(true); //Enable HW auto switch

	    //Modify  control to indicate IS if needed
		if (myControlRegion.Get() == true)
		{
	        myControlRegion.Set(false);
			myControlRegion.IncModificationCounter();
		}
		//Try to acquire timing mastership if needed
        if (!myTimingRSImpl.IsMaster() || myTimingRSImpl.HasConfigurationChanged())
		{
		    if (!myTimingRSImpl.IsMateMaster() && myTimingRSImpl.IsMateReady())
		    {
		        myTimingRSImpl.AcquireTimingMastership();
		    }
        }

		if (myTimingRSImpl.IsMaster())
		{
			if (gTmgRdTrc)
			{
	            fc_cout << "SP_TimingRedundFSM::SlaveRun: Mastership acquired..transitioning for takeover" <<endl;
			}
			//If mastership was acquired, start the transition to holdover so we can take over
			return C_HOLDOVER_MODE;
		}
		else
		{
		    //Set the clock mode to slave
		    myTimingRSImpl.SetClockMode(CT_TEL_CLKMODE_SLAVE);
		}
	}
	else
	{
		myTimingRSImpl.SetHwAutoSwitchMode(false); //Disable HW auto switch since module is OOS
	}

	return FC_FSM_NO_CONDITION;
}


void SP_TimingRedundFSM::HoldoverEntry(FC_StateId theState)
{
	//Start the timeout timer
	myTimeoutTimerHasStarted = true;
    myTimeoutTimer.Start();

    //Start the holdoff timer
    myHoldOffTimerHasStarted = true;
    myHoldOffTimer.Start();

	if (gTmgRdTrc)
	{
	    fc_cout << "SP_TimingRedundFSM::HoldoverEntry: Starting timeout and holdoff timers" <<endl;
	}
}

void SP_TimingRedundFSM::HoldoverExit(FC_StateId theState)
{
	//Cancel timers
	myTimeoutTimerHasStarted = false;
    myHoldOffTimerHasStarted = false;
	if (gTmgRdTrc)
	{
	    fc_cout << "SP_TimingRedundFSM::HoldoverExit: Canceling timeout and holdoff timers" <<endl;
	}
}

FC_ConditionId SP_TimingRedundFSM::HoldoverRun(FC_StateId theState)
{
	if (myTimingRSImpl.IsMaster())
	{
		//if mastership was obtained and the timer expired, mate has transitioned to slave mode,
		//or mate is absent, then go to master state
		if ( ( myTimingRSImpl.SwitchOnTimeoutAllowed() && myTimeoutTimerHasStarted && myTimeoutTimer.IsExpired() ) ||
			 ( myTimingRSImpl.SwitchOnTimeoutAllowed() && myTimingRSImpl.GetMateClockMode() == CT_TEL_CLKMODE_SLAVE ) ||
             ( !myTimingRSImpl.SwitchOnTimeoutAllowed() && myHoldOffTimerHasStarted && myHoldOffTimer.IsExpired() && myTimingRSImpl.GetMateClockMode() == CT_TEL_CLKMODE_SLAVE ) ||
             ( myTimingRSImpl.IsConfiguredMaster() ) ||
			 ( myTimingRSImpl.IsMatePresent() == false)
		   )
		{
			if (gTmgRdTrc)
			{
	            fc_cout << "SP_TimingRedundFSM::HoldoverRun: Transitioning to master mode" <<endl;
			}
			return C_MASTER_MODE;
		}
	}
	else
	{
		//if mastership was not obtained and the timer expired or the mate has transitioned to holdover or master
		//or the mate is no longer present, then go to slave state
		if ( (myTimingRSImpl.SwitchOnTimeoutAllowed()&& myTimeoutTimerHasStarted && myTimeoutTimer.IsExpired()) ||
             (myTimingRSImpl.GetMateClockMode() == CT_TEL_CLKMODE_MASTER) ||
			 (myTimingRSImpl.GetMateClockMode() == CT_TEL_CLKMODE_HOLDOVER) ||
             (myTimingRSImpl.IsConfiguredSlave() ) ||
             (myTimingRSImpl.IsMatePresent() == false)
		   )
		{
			if (gTmgRdTrc)
			{
	            fc_cout << "SP_TimingRedundFSM::HoldoverRun: Transitioning to slave mode" <<endl;
			}
		    return C_SLAVE_MODE;
		}
	}
	return FC_FSM_NO_CONDITION;
}
	
FC_ConditionId SP_TimingRedundFSM::InitRun(FC_StateId theState)
{
    //If user configuration forces a state, then transition to it
    if (myTimingRSImpl.IsConfiguredMaster())
    {
        if (gTmgRdTrc)
	    {
	        fc_cout << "SP_TimingRedundFSM::InitRun: Transitioning to Master due to RS Config of Master" <<endl;
	    }
        return C_MASTER_MODE;
    }
    else if (myTimingRSImpl.IsConfiguredSlave())
    {
        if (gTmgRdTrc)
	    {
	        fc_cout << "SP_TimingRedundFSM::InitRun: Transitioning to Slave due to RS Config of Slave" <<endl;
	    }
        return C_SLAVE_MODE;
    }
    else
    {
        if (myTimingRSImpl.SwitchOnTimeoutAllowed())
        {
            CSM_PersistentConfigStatus* aPersConfigPtr = &(myUsrCfgRegion[0]);
	        CT_AdministrativeConfigType theCardAdminState = aPersConfigPtr->GetAdministrativeConfig();
	        //If the card is in service attempt to acquire timing mastership.
            if (theCardAdminState == CARD_UNLOCK)
	        {
		        if (gTmgRdTrc)
		        {
	                fc_cout << "SP_TimingRedundFSM::InitRun: Attempting to acquire mastership" <<endl;
		            fc_cout << "SP_TimingRedundFSM::InitRun: Setting Control Region to IS" <<endl;
		        }
		        myTimingRSImpl.AcquireTimingMastership();
	            myControlRegion.Set(false);		
	        }
	        else
	        {
                myControlRegion.Set(true);
		        if (gTmgRdTrc)
		        {
		            fc_cout << "SP_TimingRedundFSM::InitRun: Setting Control Region to OOS" <<endl;
		        }
	        }

	        myControlRegion.IncModificationCounter();

	        if (gTmgRdTrc)
	        {
	            fc_cout << "SP_TimingRedundFSM::InitRun: Transitioning to hold mode" <<endl;
	        }

            //Set timing mode region to indicate that we are in holdover
	        myTimingRSImpl.SetClockMode(CT_TEL_CLKMODE_HOLDOVER);
    
	        if (gTmgRdTrc)
	        {
	            fc_cout << "SP_TimingRedundFSM::InitRun: Setting time mode to hold" <<endl;
	        }

	        return C_HOLDOVER_MODE;
        }
        else
        {
            //
            CSM_PersistentConfigStatus* aPersConfigPtr = &(myUsrCfgRegion[0]);
	        CT_AdministrativeConfigType theCardAdminState = aPersConfigPtr->GetAdministrativeConfig();
            if (theCardAdminState == CARD_UNLOCK)
	        {
                if (gTmgRdTrc)
		        {
		            //fc_cout << "SP_TimingRedundFSM::InitRun: Setting Control Region to IS" <<endl;
		        }
	            myControlRegion.Set(false);		
	        }
	        else
	        {
                myControlRegion.Set(true);
		        if (gTmgRdTrc)
		        {
		            //fc_cout << "SP_TimingRedundFSM::InitRun: Setting Control Region to OOS" <<endl;
		        }
	        }

	        myControlRegion.IncModificationCounter();

            if (myTimingRSImpl.GetLocalClockMode() == CT_TEL_CLKMODE_SLAVE)
            {
                //If mate is ready, then transition
                if (myTimingRSImpl.IsMateReady())
                {
                    if (gTmgRdTrc)
	                {
                        fc_cout << "SP_TimingRedundFSM::InitRun: Transitioning to slave mode due to clock config" <<endl;
                    }

                    myTimingRSImpl.ReleaseTimingMastership();
                    return C_SLAVE_MODE;
                }
                else
                {
                    //To let the other side know of state
                    myTimingRSImpl.SendTRSMessage(SP_TMG_SLAVE);
                    return FC_FSM_NO_CONDITION;
                }
            }
            else
            {
                if (myTimingRSImpl.IsMateReady())
                {
                    myTimingRSImpl.AcquireTimingMastership();
                    if (myTimingRSImpl.IsMaster() == true)
	                {
                        if (gTmgRdTrc)
	                    {
	                        fc_cout << "SP_TimingRedundFSM::InitRun: Transitioning to master mode" <<endl;
	                    }
	                    return C_MASTER_MODE;
                    }
                    else
                    {
	                    if (gTmgRdTrc)
	                    {
	                        fc_cout << "SP_TimingRedundFSM::InitRun: Transitioning to slave mode" <<endl;
	                    }
	                    return C_SLAVE_MODE;
                    }
                }
                else
                {
                    //To let the other side know of state
                    myTimingRSImpl.SendTRSMessage(SP_TMG_MASTER);
                    return FC_FSM_NO_CONDITION;
                }
            }
        }
    }
}

void SP_TimingRedundFSM::InitExit(FC_StateId theState)
{
    //Populates default value;
    bool hasChanged = myTimingRSImpl.HasConfigurationChanged();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Helper functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////


//##ModelId=39ACEFCB036A
const char* SP_TimingRedundFSM::ConvertConditionIdToText(FC_ConditionId theCondition)
{
    switch(theCondition)
    {
    case C_MASTER_MODE                :    return "C_MASTER_MODE"; break;
    case C_SLAVE_MODE                 :    return "C_SLAVE_MODE"; break;
    case C_HOLDOVER_MODE              :    return "C_HOLDOVER_MODE"; break;
    default: FC_THROW_ERROR(FC_RuntimeError,"Invalid condition ID");
        return NULL;
    }
}

//##ModelId=39ACEFCB0342
const char* SP_TimingRedundFSM::ConvertStateIdToText(FC_StateId theState)
{
    switch(theState)
    {
    case S_TMG_INIT               :return "S_TMG_INIT"; break;     
    case S_MASTER                 :return "S_MASTER"; break;  
    case S_SLAVE                  :return "S_SLAVE"; break; 
    case S_HOLDOVER               :return "S_HOLDOVER"; break;
    default: FC_THROW_ERROR(FC_RuntimeError,"Invalid state ID"); return NULL;
    }
}

//##ModelId=3B8BC9FC02DA
const char* SP_TimingRedundFSM::ConvertTransitionIdToText(FC_TransitionId theTransition)
{
    switch(theTransition)
    {
    case T_TMG_INIT_2_HOLDOVER                : return "T_TMG_INIT_2_HOLDOVER";         break;
    case T_TMG_INIT_2_MASTER                  : return "T_TMG_INIT_2_MASTER";         break;
    case T_TMG_INIT_2_SLAVE                   : return "T_TMG_INIT_2_SLAVE";         break;
    case T_MASTER_2_HOLDOVER                  : return "T_MASTER_2_HOLDOVER";      break;
    case T_SLAVE_2_HOLDOVER                   : return "T_SLAVE_2_HOLDOVER";         break;
    case T_HOLDOVER_2_MASTER                  : return "T_HOLDOVER_2_MASTER";          break;
    case T_HOLDOVER_2_SLAVE                   : return "T_HOLDOVER_2_SLAVE";                           break;
                                            
    default: FC_THROW_ERROR(FC_RuntimeError, "Invalid transition ID"); return NULL;
    }
}

//##ModelId=3B8BC9FC02C6
bool SP_TimingRedundFSM::HasChangedSinceLastCheck()
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
ostream& SP_TimingRedundFSM::WriteObject( ostream& theStream )
{
    return theStream;
}

//##ModelId=3B8BC9FC0258
istream& SP_TimingRedundFSM::ReadObject( istream& theStream )
{
    return theStream;
}

//##ModelId=3B8BC9FC0226
FC_Stream& SP_TimingRedundFSM::WriteObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

//##ModelId=3B8BC9FC01F4
FC_Stream& SP_TimingRedundFSM::ReadObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

SP_TimingRSIF& SP_TimingRedundFSM::GetTimingRsIf()
{
    return myTimingRSImpl;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//Action that runs the above state machine
FC_Fsm SP_TimingRedundAction::ourFsm;

//-----------------------------------------------------------------------------
SP_TimingRedundAction::SP_TimingRedundAction(SP_TimingRSIF& theTmgRSImpl,
                                             CSM_CardConfigStatusRegion& theUsrCfgRegion,
					                         FC_BoolRegion& theControlRegion,
                                             SP_TimingModeRegion& theTimingModeRegion,
                                             bool theAutoUpdate):
                                             myTimingModeRegion(theTimingModeRegion),
                                             myAutoUpdate(theAutoUpdate)
{
    // Make sure the FSM is initialized before creating our FSM.
    SP_TimingRedundFSM::InitFsm(ourFsm);
	myFsmImplPtr   = new SP_TimingRedundFSM(ourFsm, theTmgRSImpl, theUsrCfgRegion, theControlRegion);
	myBbAction = new FC_BbAction(this);
}

//-----------------------------------------------------------------------------
SP_TimingRedundAction::~SP_TimingRedundAction()
{
    delete myBbAction;
	delete myFsmImplPtr;
}

//-----------------------------------------------------------------------------
void SP_TimingRedundAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//-----------------------------------------------------------------------------
FC_Object* SP_TimingRedundAction::DoRunWithReason(unsigned theRunReason,
                                                  FC_Object* theInvokerObj,
                                                  FC_Object* theParam)
{
	//Run the state machine
	myFsmImplPtr->Run(theInvokerObj);

    //Update notify in the following states
    if (myAutoUpdate == false)
    {
        if (myFsmImplPtr->GetCurrentState() != S_TMG_INIT)
        {
            myTimingModeRegion.UpdateNotify();
        }
    }
	return NULL;
}



