// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SLOTCLOCKUSAGEAPPLYACTION_INCLUDED
#define _INC_SP_SLOTCLOCKUSAGEAPPLYACTION_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SystemIds.h>

class FC_BbAction;
class SP_TimingModeRegion;


//This action is responsible for applying the slot clock usage information into the hardware
class SP_SlotClockUsageApplyAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_SlotClockUsageApplyAction( SP_TimingModeRegion& theTimingModeRegion);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_SlotClockUsageApplyAction();

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

private:

    FC_BbAction* myBbAction;
	SP_TimingModeRegion& myTimingModeRegion;

};

#endif /* _INC_SP_SLOTCLOCKUSAGEAPPLYACTION_INCLUDED */