/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  James Jackson June 2012
 DESCRIPTION:Hardware low-level configuration refresh action.
 MODIFIED :
--------------------------------------------------------------------------*/
#include "TsPii/TSPII_VcgResequenceAction.h"
#include <ExecutionSupport/FC_Action.h>
#include "T6100_Dispatcher.h"
#include "ErrorService/FC_Error.h"
#include "TsPii/TSPII_VcgIf.h"


//#include "TsPii/TSPII_VcgMemberMap.h"
//extern TspiiVcgGroupMemberMap gVcgGroupMemberMap;

const FC_Milliseconds TSPII_VCG_RESEQUENCE_WAKEUP = 25; // 25 millisec

///////////////////////////////////////////////////////////////////////////////
/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  TSPII_VcgResequenceAction                                  **/
/**                                                                        **/
/**  Description:                                                          **/
/**      VcgResequence Action constructor                                  **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      None.                                                             **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
TSPII_VcgResequenceAction::TSPII_VcgResequenceAction()
//theVcgGroupMemberMapRef(gVcgGroupMemberMap)
{
    myProcess = new FC_TimedProcess(*this, gHighTimerDispatcher, TSPII_VCG_RESEQUENCE_WAKEUP);
}

///////////////////////////////////////////////////////////////////////////////
/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  ~TSPII_VcgResequenceAction                                 **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Tspii_VcgReSequenceAction destructor                              **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      None.                                                             **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
TSPII_VcgResequenceAction::~TSPII_VcgResequenceAction()
{
    myProcess->SuspendImmediate();
    delete myProcess;
}

///////////////////////////////////////////////////////////////////////////////
/***********************************BEGIN************************************/
/**                                                                        **/
/**  Function:  Run                                                        **/
/**                                                                        **/
/**  Description:                                                          **/
/**      Base Class Run method , which should be exteneded to a module     **/
/**      specific run method                                               **/
/**                                                                        **/
/**  Inputs:                                                               **/
/**      theObject -                                                       **/
/**                                                                        **/
/**  Outputs:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/**  Returns:                                                              **/
/**      None.                                                             **/
/**                                                                        **/
/************************************END*************************************/
void TSPII_VcgResequenceAction::Run(FC_Object* theObject)
{

}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_VcgResequenceAction::IsWakeUp() const
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgResequenceAction::WakeUp()
{
    myProcess->WakeUp();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_VcgResequenceAction::Suspend()
{

    myProcess->SuspendImmediate();
}

