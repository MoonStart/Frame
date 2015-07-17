/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM  : TSPII
 TARGET     : DPM
 AUTHOR     : Anoop Mathew
 DESCRIPTION: Hardware low-level configuration refresh action.
--------------------------------------------------------------------------*/

#ifndef TSPII_DPMHwRefreshAction_H
#define TSPII_DPMHwRefreshAction_H

#include "T6100_Dispatcher.h"
#include "ExecutionSupport/FC_Action.h"

class FC_PeriodicProcess;

class TSPII_DpmHwRefreshAction : public FC_Action
{
public:

    /* CONSTRUCTOR */    TSPII_DpmHwRefreshAction();
    virtual              ~TSPII_DpmHwRefreshAction();
    virtual void         Run(FC_Object* theObject = NULL);
    virtual FC_Object *  DoRunWithReason(unsigned theRunReason, FC_Object * theInvokerObj, FC_Object * theParam = NULL);
    FC_PeriodicProcess & GetProcess();

private:
    FC_PeriodicProcess *      myProcess;      
};

#endif  //  TSPII_DPMHwRefreshAction_H 
