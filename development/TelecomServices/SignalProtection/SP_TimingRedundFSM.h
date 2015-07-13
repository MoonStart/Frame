// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_TIMINGREDUNDFSM_INCLUDED
#define _INC_SP_TIMINGREDUNDFSM_INCLUDED

#include <Fsm/FC_FsmClientImp.h>
#include <ErrorService/FC_Error.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <ExecutionSupport/FC_BaseTimer.h>


//##ModelId=3BBC9B3A02DD
typedef uint8 SP_TimingRedundCondition;

const SP_TimingRedundCondition C_MASTER_MODE              = 0;
const SP_TimingRedundCondition C_SLAVE_MODE               = 1;
const SP_TimingRedundCondition C_HOLDOVER_MODE            = 2;
const SP_TimingRedundCondition C_TMG_MAX_CONDITION        = 3; // Limit must be last

//##ModelId=3BBC9B3A0388
typedef uint8 CR_CntrlRedundTransition;

const CR_CntrlRedundTransition T_TMG_INIT_2_HOLDOVER                             = 0;
const CR_CntrlRedundTransition T_TMG_INIT_2_MASTER                               = 1;
const CR_CntrlRedundTransition T_TMG_INIT_2_SLAVE                                = 2;
const CR_CntrlRedundTransition T_MASTER_2_HOLDOVER                               = 3;
const CR_CntrlRedundTransition T_SLAVE_2_HOLDOVER                                = 4;
const CR_CntrlRedundTransition T_HOLDOVER_2_MASTER                               = 5;
const CR_CntrlRedundTransition T_HOLDOVER_2_SLAVE                                = 6;
const CR_CntrlRedundTransition T_TMG_MAX_TRANSITION                              = 7; // Limit must be last

//##ModelId=3BBC9B3B005E
typedef uint8 CR_CntrlRedundState;

const CR_CntrlRedundState S_TMG_INIT                 = 0;
const CR_CntrlRedundState S_MASTER                   = 1;
const CR_CntrlRedundState S_SLAVE                    = 2;
const CR_CntrlRedundState S_HOLDOVER                 = 3;
const CR_CntrlRedundState S_TMG_MAX_STATE            = 4; // Limit must be last

//Forward Declare any classes needed
class CSM_CardConfigStatusRegion;
class FC_BoolRegion;
class SP_TimingModeRegion;
class FC_BbAction;
class FC_PeriodicProcess;
class SP_TimingRSIF;

//This class is responsible for implementing the automatic 
//protection switch and commands. It inherits from the template class 
//FC_FsmClientImp<> which provide state machine feature.  It 
//runs a state machine to perform the controller redundancy
// protocol. See state diagram about detail on the state 
//machine design.
//##ModelId=38FDC6E60242
class SP_TimingRedundFSM 
: public FC_FsmClientImp<SP_TimingRedundFSM>

{
    friend class FC_FsmClientImp<SP_TimingRedundFSM>;
public:

	//Constructor. 
    //##ModelId=390584010156
    SP_TimingRedundFSM(FC_Fsm& theFsm,
                       SP_TimingRSIF& theTmgRSImpl,
		               CSM_CardConfigStatusRegion& theUsrCfgRegion,
					   FC_BoolRegion& theControlRegion);

    //Destructor.
    //##ModelId=390584010188
    virtual ~SP_TimingRedundFSM();

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

    //Return the RS IF
    SP_TimingRSIF& GetTimingRsIf();

private:

	//Previous state since last check.
	//##ModelId=3B8BC9FC01E0
    FC_StateId myLastState;

    //Add any references here

    //True if the FSM was initialized.
    //##ModelId=39170C470094
    static bool fsmIsInitialized;

    //##ModelId=3937FD4C0181
    void MasterEntry(FC_StateId theState);
	void MasterExit(FC_StateId theState);
    FC_ConditionId MasterRun(FC_StateId theState);

	//##ModelId=3937FD4C0181
    void SlaveEntry(FC_StateId theState);
	void SlaveExit(FC_StateId theState);
    FC_ConditionId SlaveRun(FC_StateId theState);

	//##ModelId=3937FD4C0181
    void HoldoverEntry(FC_StateId theState);
	void HoldoverExit(FC_StateId theState);
    FC_ConditionId HoldoverRun(FC_StateId theState);
	
	//Reset the state machine to the initial state.
    //##ModelId=39ACEFCB02CA
    FC_ConditionId InitRun(FC_StateId theState);
	void InitExit(FC_StateId theState);

	//Helper functions

	//Region references/pointers
    SP_TimingRSIF& myTimingRSImpl;
	CSM_CardConfigStatusRegion& myUsrCfgRegion;
    FC_BoolRegion& myControlRegion;
    
    //Timeout timer
	bool myTimeoutTimerHasStarted;
	FC_BaseTimer myTimeoutTimer;

    //Holdoff timer
    bool myHoldOffTimerHasStarted;
    FC_BaseTimer myHoldOffTimer;

};

//Action that runs the above state machine
/** This action runs the FSM*/
class SP_TimingRedundAction : public FC_Action
{
public:
    /** Constructor*/
    SP_TimingRedundAction(SP_TimingRSIF& theTmgRSImpl,
                          CSM_CardConfigStatusRegion& theUsrCfgRegion,
					      FC_BoolRegion& theControlRegion,
                          SP_TimingModeRegion& theTimingModeRegion,
                          bool theAutoUpdate);

	SP_TimingRedundFSM* GetTimingFSMPtr()
	{
		return myFsmImplPtr;
	}

    virtual ~SP_TimingRedundAction();
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
	SP_TimingRedundFSM* myFsmImplPtr;

	FC_BbAction* myBbAction;

    bool myAutoUpdate;
    SP_TimingModeRegion& myTimingModeRegion;
};




#endif /* _INC_SP_TIMINGREDUNDFSM_INCLUDED */

