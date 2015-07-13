// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_MACAUTOMATICACTION_INCLUDED
#define _INC_CFG_MACAUTOMATICACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <CommonTypes/CT_FacilityIds.h>
#include <T6100_TelecomIf.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>

// Forward declaration of class.
class MON_AppIf;
class MON_Region;
class FC_WakeUpProcessAction;
class FC_OneShotProcess;

//This class is an action that automatically performs
//some action on the transmission of MAC layer.
class CFG_MacAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_MacAutomaticAction(CFG_AppIf& theCfgIf,
                           //MON_AppIf* theMacMonApp = NULL,
                           MON_AppIf* theGfpMonApp = NULL,
                           CFG_AppIf* theOptCfgApp = NULL,
                           CFG_AppIf* theEvcCfgApp = NULL,
						   CT_IntfId  theIntfId = CT_INTF_ID_UNKNOWN);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~CFG_MacAutomaticAction();

private:


    MON_AppIf* myGfpMonApp;
    //MON_AppIf* myMacMonApp;

    CFG_AppIf* myEvcCfgApp;
	CFG_AppIf* myOptCfgApp;

    CT_IntfId    myIntfId;

    uint8 myNumGfps;
    unsigned int myNumEvcs;

	FC_WakeUpProcessAction* myWakeUpAction;
	FC_OneShotProcess* myProcess;

};



#endif /* _INC_CFG_MACAUTOMATICACTION_INCLUDED */
