// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_HOPAUTOMATICACTION_INCLUDED
#define _INC_CFG_HOPAUTOMATICACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <CommonTypes/CT_FacilityIds.h>
#include <list>

// Forward declaration of class.
class MON_AppIf;

//This class is an action that automatically performs
//some action on the transmission of Hop layer.
class CFG_HopAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_HopAutomaticAction(CFG_AppIf& theCfgIf,
                           MON_AppIf* theHopMonApp,
                           CT_NumberOfHops theHopsOnCard,
                           CFG_AppIf* theOptCfgApp = NULL,
                           CFG_AppIf* theOptOtherSideCfgApp = NULL);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    //Virtual destructor of the class.
	virtual ~CFG_HopAutomaticAction();

private:

    MON_AppIf* myHopMonApp;

    CFG_AppIf* myOptCfgApp;
    CFG_AppIf* myOptOtherSideCfgApp;

    CT_NumberOfHops myHopsOnCard;
};



#endif /* _INC_CFG_HOPAUTOMATICACTION_INCLUDED */
