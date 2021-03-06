// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_DCCLAUTOMATICACTION_INCLUDED
#define _INC_CFG_DCCLAUTOMATICACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <list>

// Forward declaration of class.
class MON_AppIf;

//This class is an action that automatically performs
//some action on the transmission of Dccl layer.
class CFG_DcclAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_DcclAutomaticAction(CFG_AppIf& theCfgIf,
                            MON_AppIf* theDcclMonApp,
                            uint8      theNumLinks,
                            CFG_AppIf* theOptCfgApp = NULL,
                            CFG_AppIf* theOptOtherSideCfgApp = NULL);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    //Virtual destructor of the class.
	virtual ~CFG_DcclAutomaticAction();

private:

    MON_AppIf* myDcclMonApp;

    CFG_AppIf* myOptCfgApp;
    CFG_AppIf* myOptOtherSideCfgApp;

    uint8      myNumLinks;
};



#endif /* _INC_CFG_DCCLAUTOMATICACTION_INCLUDED */
