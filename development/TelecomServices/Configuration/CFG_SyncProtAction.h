// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_SYNCC_VER) && (_SYNCC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_SYNCPROTACTION_INCLUDED
#define _INC_CFG_SYNCPROTACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
class FC_WakeUpProcessAction;
class FC_OneShotProcess;
class TSPII_ClkSelIf;

//This class is an action that automatically performs
//some action on SYNC layer based on signal protection input
class CFG_SyncProtAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_SyncProtAction(CFG_AppIf& theCfgIf, TSPII_ClkSelRegion& theSyncPiiRegion);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~CFG_SyncProtAction();

private:

    TSPII_ClkSelRegion& mySyncPiiRegion;
	FC_WakeUpProcessAction* myWakeUpAction;
	FC_OneShotProcess* myProcess;
};



#endif /* _INC_CFG_SYNCPROTACTION_INCLUDED */
