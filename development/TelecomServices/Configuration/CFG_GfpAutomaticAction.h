// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_GFPAUTOMATICACTION_INCLUDED
#define _INC_CFG_GFPAUTOMATICACTION_INCLUDED

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
//some action on the transmission of GFP layer.
class CFG_GfpAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_GfpAutomaticAction(CFG_AppIf& theCfgIf,
                           CFG_AppIf* theOptCfgApp,
                           MON_AppIf* theRsMonApp = NULL,
                           MON_AppIf* theGfpMonApp = NULL,
                           MON_AppIf* theMsOtherSideMonApp = NULL,
                           CFG_AppIf* theOptOtherSideCfgApp = NULL,
						   CT_IntfId  theIntfId = CT_INTF_ID_UNKNOWN,
                           T6100_TelecomIf* theRsApp = NULL,
                           T6100_TelecomIf* theOptApp = NULL,
                           T6100_TelecomIf* theMacApp = NULL,
                           CFG_AppIf* theEvcCfgApp = NULL,
                           uint8 theNumPorts = 1,
                           unsigned int theNumEvcs = 1,
                           uint8 theNumGfps = 1,
                           CFG_AppIf* theRsCfgApp = NULL);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
	//Virtual destructor of the class.
	virtual ~CFG_GfpAutomaticAction();

private:
    bool DoubleCheckDisableExternalErrorSignaling(bool isSrc, bool isDst);

    CFG_AppIf* myOptCfgApp;
    CFG_AppIf* myOptOtherSideCfgApp;
    CFG_AppIf* myRsCfgApp;

    MON_AppIf* myRsMonApp;
    MON_AppIf* myGfpMonApp;
    MON_AppIf* myMsOtherSideMonApp;

    T6100_TelecomIf* myRsApp;
    T6100_TelecomIf* myOptApp;
    T6100_TelecomIf* myMacApp;
    CFG_AppIf* myEvcCfgApp;
    uint8 myNumPorts;
    uint8 myNumGfps;
    unsigned int myNumEvcs;

    CFG_Region* myOptCfgObject[CT_TEL_NBR_OF_ETH_PORTS];
    CFG_Region* myRsCfgObject[CT_TEL_NBR_OF_ETH_PORTS];
    MON_Region* myRsMonObject[CT_TEL_NBR_OF_ETH_PORTS];
    MON_Region* myMacMonObject[CT_TEL_NBR_OF_ETH_PORTS];
    MON_Region* myMacMonStatus[CT_TEL_NBR_OF_ETH_PORTS];
    CFG_Region* myMacCfgObject[CT_TEL_NBR_OF_ETH_PORTS];

	FC_WakeUpProcessAction* myWakeUpAction;
	FC_OneShotProcess* myProcess;

	CT_IntfId    myIntfId;

    bool         myHoldoffTimerActive[CT_TEL_NBR_OF_GFPS];
    bool         myAltHoldoffTimerActive[CT_TEL_NBR_OF_GFPS];
    bool         myNeedRealTimeDefectsDuringHoldoff;

    // Debug
    uint32       myRealTimeDefectReadPasses;
    uint32       myNormalReadPasses;  
    uint32       myAltRealTimeDefectReadPasses;
    uint32       myAltNormalReadPasses;
         
};



#endif /* _INC_CFG_GFPAUTOMATICACTION_INCLUDED */
