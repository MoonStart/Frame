// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1APSCONTROLLER_38FDC6E60242_INCLUDED
#define _INC_SP_1PLUS1APSCONTROLLER_38FDC6E60242_INCLUDED

#include <Fsm/FC_FsmClientImp.h>
#include <ErrorService/FC_Error.h>
#include <CommonTypes/CT_SignalProtection.h>
#include "SP_Definitions.h"
#include "SP_APSController.h"
#include "SP_1plus1Selector.h"

class SP_1plus1K1K2Transmitter;
class SP_1plus1FsmLogger;
class SP_1plus1Selector;

//##ModelId=3BBC9B3A02DD
typedef uint8 SP_1plus1Condition;

const SP_1plus1Condition C_PROTECTION_COMMAND       = 0;
const SP_1plus1Condition C_REVERTIVE                = 1;
const SP_1plus1Condition C_CLEAR_REVERTIVE          = 2;
const SP_1plus1Condition C_1PLUS1_WTR_EXPIRED       = 3;
const SP_1plus1Condition C_WORKING_HIGHER           = 4;
const SP_1plus1Condition C_WORKING_DEFECT           = 5;
const SP_1plus1Condition C_CLEAR_NOT_REVERTIVE      = 6;
const SP_1plus1Condition C_NOT_REVERTIVE            = 7;
const SP_1plus1Condition C_WORKING_DEFECT_CLEARED   = 8;
const SP_1plus1Condition C_1PLUS1_INIT              = 9;
const SP_1plus1Condition C_1PLUS1_SYNC              = 10;
const SP_1plus1Condition C_1PLUS1_REMOTE_REQUEST    = 11;
const SP_1plus1Condition C_1PLUS1_MAX_CONDITION     = 12; // Limit must be last

//##ModelId=3BBC9B3A0388
typedef uint8 SP_1plus1Transition;

const SP_1plus1Transition T_WORKING_SELECTED_2_COMMAND_TO_PROTECTION        = 0;
const SP_1plus1Transition T_PROTECTION_SELECTED_2_COMMAND_TO_PROTECTION     = 1;
const SP_1plus1Transition T_PROTECTION_NO_REQUEST_2_WORKING_SELECTED        = 2;
const SP_1plus1Transition T_NO_DEFECT_ON_WORKING_2_WORKING_SELECTED         = 3;
const SP_1plus1Transition T_WTR_2_WORKING_SELECTED                          = 4;
const SP_1plus1Transition T_PROTECTION_SELECTED_2_WORKING_SELECTED          = 5;
const SP_1plus1Transition T_WORKING_SELECTED_2_DEFECT_ON_WORKING            = 6;
const SP_1plus1Transition T_COMMAND_TO_PROTECTION_2_PROTECTION_NO_REQUEST   = 7;
const SP_1plus1Transition T_WTR_2_PROTECTION_NO_REQUEST                     = 8;
const SP_1plus1Transition T_DEFECT_ON_WORKING_2_WTR                         = 9;
const SP_1plus1Transition T_NO_DEFECT_ON_WORKING_2_DEFECT_ON_WORKING        = 10;
const SP_1plus1Transition T_1PLUS1_INIT_2_WORKING_SELECTED                  = 11;
const SP_1plus1Transition T_1PLUS1_SYNC                                     = 12;
const SP_1plus1Transition T_NO_DEFECT_ON_WORKING_2_PROTECTION_NO_REQUEST    = 13; //mr 224330
const SP_1plus1Transition T_1PLUS1_MAX_TRANSITION                           = 14; // Limit must be last

//##ModelId=3BBC9B3B005E
typedef uint8 SP_1plus1State;

const SP_1plus1State S_1PLUS1_INIT              = 0;
const SP_1plus1State S_WORKING_SELECTED         = 1;
const SP_1plus1State S_PROTECTION_SELECTED      = 2;
const SP_1plus1State S_NO_DEFECT_ON_WORKING     = 3;
const SP_1plus1State S_COMMAND_TO_PROTECTION    = 4;
const SP_1plus1State S_PROTECTION_NO_REQUEST    = 5;
const SP_1plus1State S_WTR                      = 6;
const SP_1plus1State S_DEFECT_ON_WORKING        = 7;
const SP_1plus1State S_1PLUS1_MAX_STATE         = 8; // Limit must be last

class SP_1plus1K1K2Receiver;

//This class is responsible for handling signal protection 
//request through commands and signal defectss. It runs a 
//state machine to perform the linear unidirectional 1+1 
//protocol.
class SP_1plus1ProtectionAction;
class SP_1plus1RequestParser;

//This class is responsible for handling signal protection 
//request through commands and signal defectss. It runs a 
//state machine to perform the linear unidirectional 1+1 
//protocol.
class SP_1plus1Selector;

//This class is responsible for implementing the automatic 
//protection switch and commands. It inherits from the base 
//class SP_ApsController as well as the template class 
//FC_FsmClientImp<> which provide state machine feature.  It 
//runs a state machine to perform the linear unidirectional 
//1+1 protocol. See state diagram about detail on the state 
//machine design.
//##ModelId=38FDC6E60242
class SP_1plus1APSController 
: public SP_APSController,
  public FC_FsmClientImp<SP_1plus1APSController>

{
    friend class FC_FsmClientImp<SP_1plus1APSController>;
    friend class SP_SCTestMenu;
public:

	//Constructor. Takes a request parser, a protection 
	//action, a K1K2 transmitter and a FSM.
    //##ModelId=390584010156
    SP_1plus1APSController( SP_1plus1ProtectionAction& theProtectionAction, 
                            SP_1plus1RequestParser& theRequestParser, 
                            SP_1plus1K1K2Transmitter& theK1K2Transmitter,
                            SP_1plus1FsmLogger* theLogger,
                            FC_Fsm& theFsm);

    //Destructor.
    //##ModelId=390584010188
    virtual ~SP_1plus1APSController();

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

    //Convert a SP request to its corresponding K1 byte value.
    //##ModelId=39ACEFCB0310
    inline SP_K1Request ConvertRequestToK1Request(CT_SP_Request theRequest);

private:

	//Previous state since last check.
	//##ModelId=3B8BC9FC01E0
    FC_StateId myLastState;

	//Reference to the protection action it is part of.
    //##ModelId=38FDD24C0067
    SP_1plus1ProtectionAction& myProtectionAction;

	//Reference to the request parser.
    //##ModelId=38FDC70000F5
    SP_1plus1RequestParser& myRequestParser;

	//Reference to the K1K2 transmitter.
    //##ModelId=38FDC800017F
    SP_1plus1K1K2Transmitter& myK1K2Transmitter;

    //True if the FSM was initialized.
    //##ModelId=39170C470094
    static bool fsmIsInitialized;


	//Selects the working line and update signaling (K1) with 
	//working channel code.

    //##ModelId=3937FD4C0181
    void WorkingSelectedEntry(FC_StateId theState);
	//If protection is not the best side, update the 
	//transmitter K1 with current working request. If not, 
	//check if request is a command (C_PROTECTION_COMMAND) or 
	//a defect (C_WORKING_DEFECT).
    //##ModelId=3937FD4C011D
    FC_ConditionId WorkingSelectedRun(FC_StateId theState);

	//Selects the protection line and update signaling (K1) 
	//with protection channel code.
    //##ModelId=3937FD4C00C3
    void ProtectionSelectedEntry(FC_StateId theState);
	//Check if best side is no working (C_WORKING_HIGHER). If 
	//not, checks if the request is now a switching command 
	//(C_PROTECTION_COMMAND).
    //##ModelId=3937FD4C0073
    FC_ConditionId ProtectionSelectedRun(FC_StateId theState);

	//Checks if switching command was cleared, with 
	//(C_CLEAR_REVERTIVE) or without (C_CLEAR_NOT_REVERTIVE) 
	//revertive mode active.
    //##ModelId=3937FD4C0023
    FC_ConditionId NoDefectOnWorkingRun(FC_StateId theState);

	//Updates transmitted K1 with current request.
    //##ModelId=3937FD4B03B1
    void CommandToProtectionEntry(FC_StateId theState);
	//Updates transmitted K1 with current request.
    //##ModelId=3937FD4B0361
    FC_ConditionId CommandToProtectionRun(FC_StateId theState);

	//Update transmitted K1 to Do not revert.
    //##ModelId=3937FD4B0311
    void ProtectionNoRequestEntry(FC_StateId theState);
	//Check if mode is now revertive (C_REVERTIVE).
    //##ModelId=3937FD4B02C0
    FC_ConditionId ProtectionNoRequestRun(FC_StateId theState);

	//Update transmitted K1 with WTR. Start the WTR timer if 
	//non zero.
    //##ModelId=3937FD4B027A
    void WTREntry(FC_StateId theState);
	//Check if revertive mode is still in effect 
	//(C_NOT_REVERTIVE) or if WTR timer has expired 
	//(C_1PLUS1_WTR_EXPIRED).
    //##ModelId=3937FD4B01E4
    FC_ConditionId WTRRun(FC_StateId theState);
	//Stop the WTR timer.
    //##ModelId=3937FD4B022A
    void WTRExit(FC_StateId theState);

	//Updates the transmitted K1 with current request.
    //##ModelId=3937FD4B019E
    void DefectOnWorkingEntry(FC_StateId theState);
	//This method clears any remaining commands. It updates 
	//the current request to send in K1. It checks if there 
	//is no more requests (C_WORKING_DEFECT_CLEARED).
    //##ModelId=3937FD4B013A
    FC_ConditionId DefectOnworkingRun(FC_StateId theState);

	//Reset the state machine to the initial state.
    //##ModelId=39ACEFCB02CA
    FC_ConditionId InitRun(FC_StateId theState);

};

//##ModelId=39ACEFCB0310
inline SP_K1Request SP_1plus1APSController::ConvertRequestToK1Request(CT_SP_Request theRequest)
{
    SP_K1Request aK1Request = SP_1PLUS1_K1_NO_REQUEST;

    switch(theRequest)
    {
        case CT_SP_NO_REQUEST:  aK1Request = SP_1PLUS1_K1_NO_REQUEST;
            break;
        case CT_SP_1PLUS1_LK_P:     aK1Request = SP_1PLUS1_K1_LP;
            break;
        case CT_SP_1PLUS1_FS_P:     aK1Request = SP_1PLUS1_K1_FS;
            break;
        case CT_SP_1PLUS1_SF_P:     aK1Request = SP_1PLUS1_K1_SF_H;
            break;
        case CT_SP_1PLUS1_SF_LOW_P: aK1Request = SP_1PLUS1_K1_SF_L;
            break;
        case CT_SP_1PLUS1_SD_P:     aK1Request = SP_1PLUS1_K1_SD_H;
            break;
        case CT_SP_1PLUS1_MS_P:     aK1Request = SP_1PLUS1_K1_MS;
            break;
        case CT_SP_1PLUS1_FS_W:     aK1Request = SP_1PLUS1_K1_FS;
            break;
        case CT_SP_1PLUS1_SF_W:     aK1Request = SP_1PLUS1_K1_SF_H;
            break;
        case CT_SP_1PLUS1_SF_LOW_W: aK1Request = SP_1PLUS1_K1_SF_L;
            break;
        case CT_SP_1PLUS1_SD_W:     aK1Request = SP_1PLUS1_K1_SD_H;
            break;
        case CT_SP_1PLUS1_MS_W:     aK1Request = SP_1PLUS1_K1_MS;
            break;
        case CT_SP_1PLUS1_WTR:      aK1Request = SP_1PLUS1_K1_WTR;
            break;
        case CT_SP_1PLUS1_EXER_W:
        case CT_SP_1PLUS1_EXER_P:   aK1Request = SP_1PLUS1_K1_EXER;
            break;
        case CT_SP_1PLUS1_DO_NOT_REVERT: aK1Request = SP_1PLUS1_K1_DO_NOT_REVERT;
            break;
        case CT_SP_1PLUS1_RR: aK1Request = SP_1PLUS1_K1_NO_REQUEST;
            break;
        default: FC_THROW_ERROR(FC_InvalidArgumentError, "CT_SP_Request cannot be converted to SP_K1Request.");
            break;
    }

    return aK1Request;
}


#endif /* _INC_SP_1PLUS1APSCONTROLLER_38FDC6E60242_INCLUDED */

