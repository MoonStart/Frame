// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_EVCAUTOMATICACTION_INCLUDED
#define _INC_CFG_EVCAUTOMATICACTION_INCLUDED

#include <CommonTypes/CT_SystemIds.h>
#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <list>


// Forward declaration of class.
class MON_AppIf;


//This class is an action that automatically performs
//some action on the transmission of Dccl layer.
class CFG_EvcAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_EvcAutomaticAction(CFG_AppIf&   theCfgIf,
                           unsigned int theNumEvcs,
                           MON_AppIf*   theGfpMonApp,
                           MON_AppIf*   theVcgMonApp);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    //Virtual destructor of the class.
	virtual ~CFG_EvcAutomaticAction();

private:

    unsigned int      myNumEvcs;

    MON_AppIf*        myGfpMonApp;
    MON_AppIf*        myVcgMonApp;

    CT_SlotId         mySlotId;
};



#endif /* _INC_CFG_EVCAUTOMATICACTION_INCLUDED */
