// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_StatusCollectionAction.h"
#include "../SP_ProtectionAction.h"
#include <Blackboard/FC_BbAction.h>
#include "../SP_ProtectionGroupStatus.h"
#include <ErrorService/FC_Error.h>

//##ModelId=3B8BC9DE012B
FC_Object*  SP_StatusCollectionAction::DoRunWithReason(unsigned theRunReason,
                                                       FC_Object* theInvokerObj,
                                                       FC_Object* theParam)
{
    if (stopped) return NULL;
    bool changed = false;
	bool isUpdated = false;
	//get the status for the protection actions
    SP_ProtectionActions::iterator theProtectionActionIterator;
	for (theProtectionActionIterator = myProtectionActions.begin();
	     theProtectionActionIterator != myProtectionActions.end();
		 ++theProtectionActionIterator )
	{
	    isUpdated = (*theProtectionActionIterator)->DelayedUpdateStatus(*myStatusRegion,myStatRegions);
		if (isUpdated)
			changed = true;
	}

	if (changed)
	{
		myStatusRegion->IncModificationCounter();
		myStatRegions.working->IncModificationCounter();
		myStatRegions.protection->IncModificationCounter();	
	}

    return NULL;

}

//##ModelId=3B8BC9DE0129
SP_StatusCollectionAction::SP_StatusCollectionAction(
                              SP_ProtectionGroupStatusRegion* theStatusRegion,
                              CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*> theStatRegions,
                              SP_ProtectionActions& theProtectionActions):
    myProtectionActions(theProtectionActions),
    stopped(false),
    myStatRegions(theStatRegions),
    myStatusRegion(theStatusRegion),
    myBbAction(NULL)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddOutputRegion(myStatusRegion);
    myBbAction->AddOutputRegion(myStatRegions.working);
    myBbAction->AddOutputRegion(myStatRegions.protection);
}

//##ModelId=3B8BC9DE0121
SP_StatusCollectionAction::~SP_StatusCollectionAction()
{
	delete myBbAction;
}

//##ModelId=3B8BC9DE012F
void SP_StatusCollectionAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

