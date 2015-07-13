// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_GFPPROTACTION_INCLUDED
#define _INC_CFG_GFPPROTACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
class FC_WakeUpProcessAction;
class FC_OneShotProcess;
class TSPII_MsIf;

//This class is an action that automatically performs
//some action on the transmission of MS layer.
class CFG_GfpProtAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_GfpProtAction(CFG_AppIf& theCfgIf, TSPII_GfpRegion& theGfpPiiRegion);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~CFG_GfpProtAction();

private:

    TSPII_GfpRegion& myGfpPiiRegion;
	FC_WakeUpProcessAction* myWakeUpAction;
	FC_OneShotProcess* myProcess;
};



#endif /* _INC_CFG_GFP_PROTACTION_INCLUDED */
