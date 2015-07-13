// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_EQPTREDUNDFSM_INCLUDED
#define _INC_SP_EQPTREDUNDFSM_INCLUDED

#include <Fsm/FC_FsmClientImp.h>
#include <ErrorService/FC_Error.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <ExecutionSupport/FC_BaseTimer.h>


//##ModelId=3BBC9B3A02DD
typedef uint8 SP_EqptRedundCondition;

const SP_EqptRedundCondition C_ERS_ACTIVE_MODE              = 0;
const SP_EqptRedundCondition C_ERS_STBY_MODE                = 1;
const SP_EqptRedundCondition C_ERS_SWITCH_COMMAND           = 2;
const SP_EqptRedundCondition C_ERS_EQPT_MAX_CONDITION       = 3; // Limit must be last

//##ModelId=3BBC9B3A0388
typedef uint8 SP_EqptRedundTransition;

const SP_EqptRedundTransition T_ERS_EQPT_INIT_2_ACTIVE                               = 0;
const SP_EqptRedundTransition T_ERS_EQPT_INIT_2_STANDBY                              = 1;
const SP_EqptRedundTransition T_ERS_EQPT_ACTIVE_2_STANDBY                            = 2;
const SP_EqptRedundTransition T_ERS_EQPT_ACTIVE_2_SWITCH_STNBY                       = 3;
const SP_EqptRedundTransition T_ERS_EQPT_SWITCH_STNBY_2_STANDBY                      = 4;
const SP_EqptRedundTransition T_ERS_EQPT_STANDBY_2_ACTIVE                            = 5;
const SP_EqptRedundTransition T_ERS_EQPT_MAX_TRANSITION                              = 6; // Limit must be last

//##ModelId=3BBC9B3B005E
typedef uint8 SP_EqptRedundState;

const SP_EqptRedundState S_ERS_EQPT_INIT                = 0;
const SP_EqptRedundState S_ERS_EQPT_ACTIVE              = 1;
const SP_EqptRedundState S_ERS_EQPT_STANDBY             = 2;
const SP_EqptRedundState S_ERS_EQPT_SWITCH_STNBY        = 3;
const SP_EqptRedundState S_ERS_EQPT_MAX_STATE           = 4; // Limit must be last

typedef uint8 SP_EQPT_REDUND_PREF;
const SP_EQPT_REDUND_PREF ERS_PREFERENCE    = 0xab;
const SP_EQPT_REDUND_PREF ERS_NO_PREFERENCE = 0x00;

//Forward Declare any classes needed
class FC_BbAction;
class FC_PeriodicProcess;
class SP_ERSIF;
class T6100_ControllerStatusRegion;
class SP_ERSSwitchRegion;
class SP_ERSSwitchResultRegion;
class FC_BoolRegion;

//This class is responsible for implementing the automatic 
//protection switch and commands. It inherits from the template class 
//FC_FsmClientImp<> which provide state machine feature.  It 
//runs a state machine to perform the controller redundancy
// protocol. See state diagram about detail on the state 
//machine design.
//##ModelId=38FDC6E60242
class SP_EqptRedundFSM 
: public FC_FsmClientImp<SP_EqptRedundFSM>

{
    friend class FC_FsmClientImp<SP_EqptRedundFSM>;
public:

	//Constructor. 
    //##ModelId=390584010156
    SP_EqptRedundFSM(FC_Fsm& theFsm,
                     SP_ERSIF& theERSImpl,
                     T6100_ControllerStatusRegion* theModeRegion,
                     SP_ERSSwitchRegion* theSwitchRegion = NULL,
			         SP_ERSSwitchResultRegion* theSwitchResultRegion = NULL,
					 CT_SlotId theSlot = UNKNOWN_SLOT_ID,
					 CT_SlotId theMateSlot = UNKNOWN_SLOT_ID);

    //Destructor.
    //##ModelId=390584010188
    virtual ~SP_EqptRedundFSM();

	//Resets the state machine to its initial state and marks 
	//the object as stable (for synchronization).
    //##ModelId=39ACEFCB03A6
    void Reset();

	//Initializes the states and transitions of the 1+1 state 
	//machine. This is done only one in the system.
    //##ModelId=39170C470116
    static void InitFsm(FC_Fsm& theFsm);
    // Used to set last state after Restart()
    inline void SetLastState(FC_StateId theState){myLastState = theState;}

	//Converts a condition ID to a string.
    //##ModelId=39ACEFCB036A
    static const char* ConvertConditionIdToText(FC_ConditionId theCondition);
	//Converts a state ID to a string.
    //##ModelId=39ACEFCB0342
    static const char* ConvertStateIdToText(FC_StateId theState);
	//Converts a transition ID to a string.
	//##ModelId=3B8BC9FC02DA
    static const char* ConvertTransitionIdToText(FC_TransitionId theTransition);

	//True if current state is different that last time is 
	//was checked.
	//##ModelId=3B8BC9FC02C6
    virtual bool HasChangedSinceLastCheck();

	//Send the current state to a stream.
	//##ModelId=3B8BC9FC028A
    virtual ostream& WriteObject( ostream& theStream );
	//Extract the state from a stream and resets the state 
	//machine to this state.
	//##ModelId=3B8BC9FC0258
    virtual istream& ReadObject( istream& theStream );
	//Send the current state to a binary stream.
	//##ModelId=3B8BC9FC0226
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Extract the state from a binary stream and resets the 
	//state machine to this state.
	//##ModelId=3B8BC9FC01F4
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Enable/disable debug tracing
    void SetDebugTraceMode(bool theMode);

private:

	//Previous state since last check.
	//##ModelId=3B8BC9FC01E0
    FC_StateId myLastState;

    //Add any references here
    SP_ERSIF& myEqptRSImpl;
    T6100_ControllerStatusRegion* myModeRegion;

    //True if the FSM was initialized.
    //##ModelId=39170C470094
    static bool fsmIsInitialized;

    //##ModelId=3937FD4C0181
    void ActiveEntry(FC_StateId theState);
	void ActiveExit(FC_StateId theState);
    FC_ConditionId ActiveRun(FC_StateId theState);

	//##ModelId=3937FD4C0181
    void StandbyEntry(FC_StateId theState);
	void StandbyExit(FC_StateId theState);
    FC_ConditionId StandbyRun(FC_StateId theState);

    //##ModelId=3937FD4C0181
    void SwitchStandbyEntry(FC_StateId theState);
	void SwitchStandbyExit(FC_StateId theState);
    FC_ConditionId SwitchStandbyRun(FC_StateId theState);
	
	//Reset the state machine to the initial state.
    //##ModelId=39ACEFCB02CA
    FC_ConditionId InitRun(FC_StateId theState);
	void InitExit(FC_StateId theState);

	//Helper functions

	//Region pointers
    SP_ERSSwitchRegion* ourSwitchRegion;
    SP_ERSSwitchResultRegion* ourSwitchResultRegion;

    //Message counter
    uint32 myPrevCounter;

    //Last processed command id
    CT_SP_CommandID myLastCommandID;

    //Timer
    FC_BaseTimer myWaitTimer;
	bool myTimerHasStarted;

	//Slot information
	CT_SlotId mySlot;
	CT_SlotId myMateSlot;

};

//Action that runs the above state machine
/** This action runs the FSM*/
class SP_EqptRedundAction : public FC_Action
{
public:
    /** Constructor*/
    SP_EqptRedundAction(SP_ERSIF& theERSImpl,
                        T6100_ControllerStatusRegion* theModeRegion,
                        SP_ERSSwitchRegion* theSwitchRegion = NULL,
			            SP_ERSSwitchResultRegion* theSwitchResultRegion = NULL,
                        FC_BoolRegion* theIsrMonRegion = NULL,
					    CT_SlotId theSlot = UNKNOWN_SLOT_ID,
					    CT_SlotId theMateSlot = UNKNOWN_SLOT_ID);

	SP_EqptRedundFSM* GetEqptFSMPtr()
	{
		return myFsmImplPtr;
	}

    virtual ~SP_EqptRedundAction();
//-----------------------------------------------------------------------------

    virtual void Run( FC_Object* theObject = 0 );

	virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
//-----------------------------------------------------------------------------

	FC_BbAction* GetBbAction() { return myBbAction; }


private:
    //The state machine implementing the timing redundancy 
	//protocol.
    static FC_Fsm ourFsm;

	//The class that implements above state machine
	SP_EqptRedundFSM* myFsmImplPtr;
    //Mode region
    T6100_ControllerStatusRegion* myModeRegion;
    FC_BoolRegion* myIsrMonRegion;
    SP_ERSSwitchResultRegion* mySwitchResultRegion;
	FC_BbAction* myBbAction;

};




#endif /* _INC_SP_TIMINGREDUNDFSM_INCLUDED */

