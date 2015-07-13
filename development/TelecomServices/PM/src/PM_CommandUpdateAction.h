/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Action invoked when the Cfg region has changed. It will set
                flags so that the PM_Processor knows that it should hunt for
                Inhibition setting changes.
--------------------------------------------------------------------------*/

#ifndef PM_COMMANDUPDATEACTION_H
#define PM_COMMANDUPDATEACTION_H

#include <ExecutionSupport/FC_Action.h>


//This action will simply set a flag (bool) when Run method is 
//called. This action is used to be registered to the update 
//notify region service. It is used to be adviced when the 
//region change, but the changing must be known at a precise moment 
//into the execution of an application. For example, if more than 
//one process running synchronously must be adviced that a given 
//region is changed, the flag set by this action can be
//polled to know either the given region is changed or not.
//##ModelId=3C1F6F6D03AB
class PM_CommandUpdateAction : public FC_Action
{
public:

    //Class default constructor.
    //##ModelId=3C1F6F6E01F4
    PM_CommandUpdateAction(void);

    //Class default destructor.
    //##ModelId=3C1F6F6E01FE
    virtual ~PM_CommandUpdateAction();

    //This method sets the state to true.
    //##ModelId=3C1F6F6E0200
    void Run(FC_Object* theObject = NULL);

    //Sets the current state.
    //##ModelId=3CBC723D01A7
    void SetState(bool theState);

    //Returns the current state.
    //##ModelId=3CBC723D01C5
    bool GetState(void);

private:

    //My state flag.
    //##ModelId=3C1F6F6E0209
    bool myState;

};

#endif // PM_COMMANDUPDATEACTION_H
