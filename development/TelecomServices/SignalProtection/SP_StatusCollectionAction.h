// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_STATUSCOLLECTIONACTION_38E4CE450389_INCLUDED
#define _INC_SP_STATUSCOLLECTIONACTION_38E4CE450389_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <vector>
#include "SP_SwitchingStatistic.h"
#include "SP_Definitions.h"
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_SP_ProtectionPair.h>

class SP_ProtectionAction;
class FC_BbAction;
class SP_ProtectionGroupStatus;
class SP_ProtectionGroupStatusRegion;


//This class is an action used to force a protection action 
//to update its current status to a region. This action is 
//usually attached to a re-triggable timed process that a 
//invoked each time the protection action runs. Using a timed 
//process period of 100ms, this allows status update to be 
//done only if protection action has become stable for more 
//than 100ms. This is one status collection action for each 
//protection action in the system.
//##ModelId=3B8BC9DE00D9
class SP_StatusCollectionAction 
: public FC_Action
{
public:
	//Not supported.
	//##ModelId=3B8BC9DE012F
    virtual void Run( FC_Object* theObject = NULL );

	//Forces the protection action to update its status to 
	//proper location.
	//##ModelId=3B8BC9DE012B
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Constructor. Takes the protection action to report 
	//about.
	//##ModelId=3B8BC9DE0129
    SP_StatusCollectionAction(SP_ProtectionGroupStatusRegion* theStatusRegion,
                              CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*> theStatRegions,
                              SP_ProtectionActions& theProtectionActions);

	//Destructor.
	//##ModelId=3B8BC9DE0121
	virtual ~SP_StatusCollectionAction();

	//Starts the status collection processing. (debug)
	//##ModelId=3B8BC9DE0120
    inline void Start();
	//Stops the status collection processing. (debug)
	//##ModelId=3B8BC9DE011F
    inline void Stop();

    FC_BbAction* GetBbAction() { return myBbAction; }

private:

	//Pointer to protection actions to report about.
	//##ModelId=3B8BC9DE0119
    SP_ProtectionActions& myProtectionActions;
	//True is status collection is stopped (debug).
	//##ModelId=3B8BC9DE0116
    bool stopped;

	//Pair to pointers to the statistics region.
	//##ModelId=3BBC9B3702BC
    CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*> myStatRegions;

    SP_ProtectionGroupStatusRegion* myStatusRegion;

    FC_BbAction* myBbAction;
};

//##ModelId=3B8BC9DE0120
inline void SP_StatusCollectionAction::Start() { stopped = false; }
//##ModelId=3B8BC9DE011F
inline void SP_StatusCollectionAction::Stop() { stopped = true; }

#endif /* _INC_SP_STATUSCOLLECTIONACTION_38E4CE450389_INCLUDED */

