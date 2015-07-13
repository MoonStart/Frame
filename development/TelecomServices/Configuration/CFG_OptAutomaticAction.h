// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_OPTAUTOMATICACTION_H
#define _CFG_OPTAUTOMATICACTION_H

#include "CFG_HwRefreshAction.h"
#include "CFG_Object.h"
#include <list>
#include <gdef.h>
#include "ITS/ITS_Definitions.h"
#include <ExecutionSupport/FC_BaseTimer.h>


// Forward declaration of class.
class MON_AppIf;

//This class is an action that automatically performs
//some action on the transmission of RS layer.
class CFG_OptAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_OptAutomaticAction(CFG_AppIf& theOutgoingOptLayerIf,
                           CFG_AppIf* theOptOtherSideCfgAppIf,
                           MON_AppIf* theRsMonApp,
                           MON_AppIf* theRsOtherSideMonApp,
                           MON_AppIf* theInternalMonApp,
                           MON_AppIf* theMsOtherSideMonApp,
                           MON_AppIf* theGfpMonApp,
                           ITS_ConfigRegionOnTrn* theItsConfigRegion,
                           CFG_AppIf* theEvcCfgApp,
                           CT_IntfId  theIntfId,
                           bool       theAllowNoOppositeSide = false);

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~CFG_OptAutomaticAction();
    void UpdateObject(unsigned theRunReason);

private:

    MON_AppIf* myRsMonApp;
    MON_AppIf* myRsOtherSideMonApp;
    CFG_AppIf* myOptOtherSideCfgApp;
    MON_AppIf* myInternalMonApp;
    MON_AppIf* myMsOtherSideMonApp;
    MON_AppIf* myGfpMonApp;

    CFG_AppIf* myEvcCfgApp;
    CT_IntfId  myIntfId;  

    ITS_ConfigRegionOnTrn* myItsConfigRegion;

    bool       myAllowNoOtherSide;
    bool       myUseOnlyLosForNEALS;
};



#endif /* _CFG_OPTAUTOMATICACTION_H */
