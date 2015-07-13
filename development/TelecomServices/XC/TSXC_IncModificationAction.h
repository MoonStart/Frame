// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_INCMODIFICATIONACTION_INCLUDED
#define _INC_TSXC_INCMODIFICATIONACTION_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <XC/TSXC_ConfigRegion.h>
#include <XC/TSXC_Connect.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <ctime>


class FC_BbAction;


//
//This class is responsible for incrementing the modification
// counter of the xc ag config region when the card status
// changes
//

class TSXC_IncModificationAction : public FC_Action
{
public:

    // Constructor 
    TSXC_IncModificationAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_IncModificationAction();

    
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);

    //
    // Need to have a method to retrieve the FC_BbAction since
    // this action runs under the context of a process.
    //
    FC_BbAction* GetBbAction() { return myBbAction; }

    // 
    // Get Methods
    //
    TSXC_ConfigRegion<TSXC_Connect>* GetAgCfgRegion();
    

    // 
    // Set Methods.  SubApplications will be invoking the non-debug methods
    // to set region pointers for XC_Cfg Action since the subapplications
    // contain pointers to these regions.
    //
    void SetAgCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theAGCfgRegion);

    virtual void Run( FC_Object* theObject = NULL );

private:
    
    T6100_CardIf& myCardContext;
	CSM_CardStatusRegion* myCardStatusRegion;
    FC_BbAction* myBbAction;
	TSXC_ConfigRegion<TSXC_Connect>* myXCAgentConfig_Region;
	time_t myOccurTime;
};

#endif /* _INC_TSXC_INCMODIFICATIONACTION_INCLUDED */

