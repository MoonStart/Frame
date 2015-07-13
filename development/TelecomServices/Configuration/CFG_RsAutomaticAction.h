// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_RSAUTOMATICACTION_INCLUDED
#define _INC_CFG_RSAUTOMATICACTION_INCLUDED

#include "CFG_HwRefreshAction.h"
#include "CFG_Region.h"
#include "CFG_Opt.h"
#include "CFG_OptAutomatic.h"
#include "CFG_MsProt.h"
#include "CFG_Definitions.h"
#include <CommonTypes/CT_FacilityIds.h>

#include <list>

// Forward declaration of class.
class MON_AppIf;

//This class is an action that automatically performs
//some action on the transmission of RS layer.
class CFG_RsAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_RsAutomaticAction(CFG_AppIf& theCfgIf,
                          MON_AppIf* theRsMonApp,
                          MON_AppIf* theRsOtherSideMonApp,
                          CFG_AppIf* theOptCfgApp,
                          CFG_AppIf* theOptOtherSideCfgApp,
                          MON_AppIf* theMsMonApp,
                          CFG_AppIf* theMsProtCfgApp,
                          MON_AppIf* theMsOtherSideMonApp = NULL,
                          MON_AppIf* theGfpMonApp         = NULL,
                          CFG_AppIf* theEvcCfgApp         = NULL,
                          CT_IntfId  theIntfId            = CT_INTF_ID_UNKNOWN,
                          bool       theAllowNoOppositeSide = false);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    //Virtual destructor of the class.
	virtual ~CFG_RsAutomaticAction();

private:

    MON_AppIf* myRsMonApp;
    MON_AppIf* myMsMonApp;
    MON_AppIf* myRsOtherSideMonApp;
    MON_AppIf* myMsOtherSideMonApp;
    MON_AppIf* myGfpMonApp;

    CFG_AppIf* myOptCfgApp;
    CFG_AppIf* myOptOtherSideCfgApp;
    CFG_AppIf* myMsProtCfgApp;
    CFG_AppIf* myEvcCfgApp;
    CT_IntfId  myIntfId;

    MON_AppIf* myMsMFacMonApp;
    CT_IntfId  myMFacIntfId;

    bool       myAllowNoOtherSide;
};



#endif /* _INC_CFG_RSAUTOMATICACTION_INCLUDED */
