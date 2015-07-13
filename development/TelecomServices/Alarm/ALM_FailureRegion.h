/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   Blackboard region for Signal Alarm BB objects
--------------------------------------------------------------------------*/

#ifndef ALM_FAILUREREGION_H
#define ALM_FAILUREREGION_H


#include <TelCommon/TEL_BbRegionBase.h>

#include "ALM_FPCommon.h"

// Foward declaration of classes
class FC_Action;


//Blackboard region for Signal Alarm BB objects. This region contained many BB objects.
//##ModelId=3C506C3900CF
class ALM_FailureRegion : public TEL_BbRegionBase
{

public:

	//Constructor for this class.
    //
    //PARAM const FC_BbKey theKey: the BB key use at the region creation.
	//##ModelId=3C506C390151
    ALM_FailureRegion(const FC_BbKey theKey);

    //Destructor for this class.
	//##ModelId=3C506C390153
    virtual ~ALM_FailureRegion();

	//Reset the alarm condition (set status to false and occurring time to 0, i.e. at 00:00:00 1970).
	//##ModelId=3C506C39015B
    virtual void Reset() = 0;

	//Print the failure statuses of the region.
	//##ModelId=3C506C39015D
    void PrintYourSelf( int anObjectIndex = -1) const;

	//Set the action that is called when one object of the region has changed.
    //
    //PARAM FC_Action* theAction: the action to run when the region is modified.
	//##ModelId=3C506C39016F
    virtual void SetNotifyAction(FC_Action* theAction) = 0;

	//Reset the notify action.
	//##ModelId=3C506C390172
    virtual void ResetNotifyAction() = 0;
};



#endif //ALM_FAILUREREGION_H
