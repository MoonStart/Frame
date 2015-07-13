// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_T1E1AUTOMATICACTION_INCLUDED
#define _INC_CFG_T1E1AUTOMATICACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <list>

// Forward declaration of class.
class MON_AppIf;

//This class is an action that automatically performs
//some action on the transmission of T1E1 layer.
class CFG_T1E1AutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_T1E1AutomaticAction(CFG_AppIf& theCfgIf,
                            MON_AppIf* theT1E1MonApp);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    //Virtual destructor of the class.
	virtual ~CFG_T1E1AutomaticAction();

private:

    MON_AppIf* myT1E1MonApp;
};



#endif /* _INC_CFG_T1E1AUTOMATICACTION_INCLUDED */
