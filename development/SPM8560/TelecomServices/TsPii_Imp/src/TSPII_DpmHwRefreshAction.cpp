/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM  : TSPII
 TARGET     : DPM
 AUTHOR     : Anoop Mathew
 DESCRIPTION: Hardware low-level configuration refresh action.
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_DpmHwRefreshAction.h"
#include "ErrorService/FC_Error.h"
#include "ExecutionSupport/FC_PeriodicProcess.h"


const FC_Milliseconds REFRESH_PERIOD = 180000;

////////////////////////////////////////////////////////////////////////////////
TSPII_DpmHwRefreshAction::TSPII_DpmHwRefreshAction()
{
    myProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, REFRESH_PERIOD);
}

////////////////////////////////////////////////////////////////////////////////
TSPII_DpmHwRefreshAction::~TSPII_DpmHwRefreshAction()
{
    myProcess->SuspendImmediate();
    delete myProcess;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_DpmHwRefreshAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run method should not be called");
}

////////////////////////////////////////////////////////////////////////////////
FC_Object* TSPII_DpmHwRefreshAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
FC_PeriodicProcess & TSPII_DpmHwRefreshAction::GetProcess()
{
    return *myProcess;
}
