/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM  : TSPII
 TARGET     : SPM8560
 AUTHOR     : Anoop Mathew
 DESCRIPTION: Hardware low-level configuration refresh action.
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_SPM8560HwRefreshAction.h"
#include "ErrorService/FC_Error.h"
#include "ExecutionSupport/FC_PeriodicProcess.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"

const FC_Milliseconds REFRESH_PERIOD = 180000;

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560HwRefreshAction::TSPII_SPM8560HwRefreshAction() :
    myOscMapperFpgaCtrl(TSPII_OscMapperFpgaCtrl::GetInstance())
{
    myProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, REFRESH_PERIOD);
}

////////////////////////////////////////////////////////////////////////////////
TSPII_SPM8560HwRefreshAction::~TSPII_SPM8560HwRefreshAction()
{
    myProcess->SuspendImmediate();
    delete myProcess;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_SPM8560HwRefreshAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run method should not be called");
}

////////////////////////////////////////////////////////////////////////////////
FC_Object* TSPII_SPM8560HwRefreshAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    myOscMapperFpgaCtrl.Refresh();
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
FC_PeriodicProcess & TSPII_SPM8560HwRefreshAction::GetProcess()
{
    return *myProcess;
}
