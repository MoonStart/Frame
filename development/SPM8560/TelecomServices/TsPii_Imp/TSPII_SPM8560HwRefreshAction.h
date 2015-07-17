/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM  : TSPII
 TARGET     : SPM8560
 AUTHOR     : Anoop Mathew
 DESCRIPTION: Hardware low-level configuration refresh action.
--------------------------------------------------------------------------*/

#ifndef TSPII_SPM8560HwRefreshAction_H
#define TSPII_SPM8560HwRefreshAction_H

#include "T6100_Dispatcher.h"
#include "ExecutionSupport/FC_Action.h"

class FC_PeriodicProcess;
class TSPII_OscMapperFpgaCtrl;

class TSPII_SPM8560HwRefreshAction : public FC_Action
{
public:

    /* CONSTRUCTOR */    TSPII_SPM8560HwRefreshAction();
    virtual              ~TSPII_SPM8560HwRefreshAction();
    virtual void         Run(FC_Object* theObject = NULL);
    virtual FC_Object *  DoRunWithReason(unsigned theRunReason, FC_Object * theInvokerObj, FC_Object * theParam = NULL);
    FC_PeriodicProcess & GetProcess();

private:
    TSPII_OscMapperFpgaCtrl & myOscMapperFpgaCtrl;
    FC_PeriodicProcess *      myProcess;      
};

#endif  //  TSPII_OSC8250HwRefreshAction_H 
