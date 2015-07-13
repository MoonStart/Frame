// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_1plus1SelPosnUpdateAction.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_SelectorPositionRegion.h"
#include "../SP_1plus1Selector.h"
#include "../SP_1plus1RequestParser.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>
#include <ExecutionSupport/FC_PeriodicProcess.h>


////-----Special action-------------------------------------------
//##ModelId=3BBC9B0F02A0
SP_1plus1SelPosnUpdateAction::SP_1plus1SelPosnUpdateAction( 
	SP_SelectorPositionRegion& theSelectorPosnRegion,
	SP_SelectorPositionRegion* theAltSelectorPosnRegion,
	SP_ProtectionActions& theProtectionActions):
    theirSelectorPosnRegion(theSelectorPosnRegion),
	theirAltSelectorPosnRegion(theAltSelectorPosnRegion),
    theirProtectionActions(theProtectionActions)
{
    myProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, 60*3*1000);
    myProcess->WakeUp();
}

//##ModelId=38EDF51800A6
SP_1plus1SelPosnUpdateAction::~SP_1plus1SelPosnUpdateAction()
{
	myProcess->SuspendImmediate();
	delete myProcess;
}

//##ModelId=3B8BC9D30390
void SP_1plus1SelPosnUpdateAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_1plus1SelPosnUpdateAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
	bool hasRegionChanged = false;
	bool rc = false;
	int i=0;
	SP_1plus1ProtectionAction* theProtAction = NULL;
	SP_SelectorPosition* aSelectorPosn = NULL;
	SP_ProtectionActions::iterator theProtectionActionIterator;

	for (theProtectionActionIterator = theirProtectionActions.begin(),i=0;
	     theProtectionActionIterator != theirProtectionActions.end();
		 ++theProtectionActionIterator, i++ )
	{
	    if ((*theProtectionActionIterator)->IsEnabled())
		{
			theProtAction = dynamic_cast<SP_1plus1ProtectionAction*>((*theProtectionActionIterator));
			aSelectorPosn = GetSelectorPosnObject(theProtAction, i);
            rc = aSelectorPosn->SetSelectorPostion(theProtAction->mySelectorPtr->GetSelection());
			hasRegionChanged = (hasRegionChanged || rc);
			if (theProtAction->myRequestParserPtr->IsBestSideUsable() == false)
			{
                rc = aSelectorPosn->SetSelectorPostion(CT_SP_INVALID_PROTECTION_SIDE);
			    hasRegionChanged = (hasRegionChanged || rc);
			}
		}
	}

    if (hasRegionChanged)
	{
        theirSelectorPosnRegion.IncModificationCounter();
		theirSelectorPosnRegion.UpdateNotify();

		if (theirAltSelectorPosnRegion)
		{
			theirAltSelectorPosnRegion->IncModificationCounter();
		    theirAltSelectorPosnRegion->UpdateNotify();
		}
	}
	return NULL;
}

SP_SelectorPosition* SP_1plus1SelPosnUpdateAction::GetSelectorPosnObject(SP_1plus1ProtectionAction* theProtectionAction, int theIndex)
{
	//By default always return the location in the selector position region
	return ( dynamic_cast<SP_SelectorPosition*>( (&(theirSelectorPosnRegion)[theIndex])) );
}
