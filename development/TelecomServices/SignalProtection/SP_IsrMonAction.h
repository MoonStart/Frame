// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_ISRMONACTION_38E35B0900D0_INCLUDED
#define _INC_SP_ISRMONACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_Milliseconds.h>

class SP_1plus1SubApplication;
class SP_ApplicationStatus;
class FC_BbAction;
class FC_TimedProcess;
class FC_WakeUpProcessAction;

//This action is responsible for reacting to an interrupt generated on the card
class SP_IsrMonAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
    //##ModelId=3BBC9B0F02A0
    SP_IsrMonAction( SP_1plus1SubApplication& theApplIf,
                     FC_Milliseconds theInterval = 1000);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_IsrMonAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles config request coming from the 
	//admin. 
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    FC_BbAction* GetBbAction() { return myBbAction; }
    FC_BbAction* GetDelayedBbAction() {return myDelayedBbAction; }

	void Disable();

private:

    FC_BbAction* myBbAction;
    FC_BbAction* myDelayedBbAction;
    FC_TimedProcess* myProcessPtr;
    FC_WakeUpProcessAction* myCallbackAction;
	SP_1plus1SubApplication& myAppIf;
	bool myEnableFlag;
};

#endif /* _INC_SP_ISRMONACTION_38E35B0900D0_INCLUDED */