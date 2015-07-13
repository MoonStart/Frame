// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_GCCAUTOMATICACTION_INCLUDED
#define _INC_CFG_GCCAUTOMATICACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"

// Forward declaration of class.
class MON_AppIf;

//This class is an action that automatically performs
//some action on the transmission of Gcc layer.
class CFG_GccAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_GccAutomaticAction(CFG_AppIf& theCfgIf,
                            MON_AppIf* theGccMonApp,
                            uint8      theNumLinks,
                            CFG_AppIf* theOptCfgApp = NULL);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    //Virtual destructor of the class.
	virtual ~CFG_GccAutomaticAction();

private:

    MON_AppIf* myGccMonApp;

    CFG_AppIf* myOptCfgApp;

    uint8      myNumLinks;
};



#endif /* _INC_CFG_GCCAUTOMATICACTION_INCLUDED */
