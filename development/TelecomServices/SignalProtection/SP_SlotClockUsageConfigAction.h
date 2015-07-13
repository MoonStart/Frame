// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SLOTCLOCKUSAGECONFIGACTION_INCLUDED
#define _INC_SP_SLOTCLOCKUSAGECONFIGACTION_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SystemIds.h>

class FC_BbAction;
class SP_TimingModeRegion;
class SCFG_ParamRegion;


//This action is responsible for configuring the timing mode config region
//with the slt clock usage
class SP_SlotClockUsageConfigAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_SlotClockUsageConfigAction(SP_TimingModeRegion& theTimingModeRegion,
                                  SCFG_ParamRegion* theSyncModeRegion,
                                  CT_ShelfId theShelfId,
                                  CT_SlotId theFirstSlot,
                                  CT_SlotId theLastSlot);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_SlotClockUsageConfigAction();

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

    SP_TimingModeRegion& myTimingModeRegion;
    SCFG_ParamRegion* mySyncModeRegion;
    FC_BbAction* myBbAction;
	CT_ShelfId myShelfId;
    CT_SlotId myFirstSlot;
    CT_SlotId myLastSlot;

};

#endif /* _INC_SP_SLOTCLOCKUSAGECONFIGACTION_INCLUDED */