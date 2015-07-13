// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_MSAUTOMATICACTION_INCLUDED
#define _INC_CFG_MSAUTOMATICACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <CommonTypes/CT_FacilityIds.h>


// Forward declaration of class.
class MON_AppIf;
class FC_WakeUpProcessAction;
class FC_OneShotProcess;

//This class is an action that automatically performs
//some action on the transmission of Ms layer.
class CFG_MsAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_MsAutomaticAction(CFG_AppIf& theCfgIf,
                          CFG_AppIf* theSyncCfgApp,
                          CT_IntfId  theIntfId);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~CFG_MsAutomaticAction();

private:

    CFG_AppIf* mySyncCfgApp;
    CT_IntfId  myIntfId;
	FC_WakeUpProcessAction* myWakeUpAction;
	FC_OneShotProcess* myProcess;
};



#endif /* _INC_CFG_MSAUTOMATICACTION_INCLUDED */
