/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     May, 2009        Kumar C Solai
    DESCRIPTION:   TSXC Base Action Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_BASEACTION_INCLUDED
#define _INC_TSXC_BASEACTION_INCLUDED

#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <ExecutionSupport/FC_EventLogger.h>
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_QrsTypes.h>
#include <CommonTypes/CT_SwitchDomainMap.h>
#include <T6100_CardIf.h>

class QRS_ResponseRegion;

//-----------------------------------------------------------------------------
// This is a base class obstracting common fuctionality 
// for configuration actions
//-----------------------------------------------------------------------------
class TSXC_BaseAction : public FC_Action
{
public:

    // Constructor 
    TSXC_BaseAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_BaseAction();

    //--------------------------------------------------------------------------
    // This method causes this object to execute its main
    // function of applying Currect Configurations.
    //--------------------------------------------------------------------------
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);

    //--------------------------------------------------------------------------
    // Need to have a method to retrieve the FC_BbAction since
    // this action runs under the context of a process.
    //--------------------------------------------------------------------------
    FC_BbAction* GetBbAction();

    //--------------------------------------------------------------------------
    // SubApplications will be invoking this method to add/delete
    // input regions for approprate Action since the subapplicatoins
    // contain pointers to the input regions.
    //--------------------------------------------------------------------------
    void AddInputRegion( FC_BbRegion* theInputRegion, bool theCheckValid = true, 
                         int obsPriority = FC_BbRegObsPriority::LOW, bool theRefreshTrigger = false);
    void RemoveInputRegion( FC_BbRegion* theInputRegion );
    void AddOutputRegion( FC_BbRegion* theOutputRegion );
    void RemoveOutputRegion( FC_BbRegion* theOutputRegion );
    void SetDebugLevel(int theValue);
    virtual void Run( FC_Object* theObject = NULL );
    void SetResponseRegion(QRS_ResponseRegion* theRegion){myResponseRegion = theRegion;}
    void Respond(CT_XC_CQMID theResponse);
    uint8 PhysToLogicalShelf(uint8 thePhysShelf, 
                             CT_TEL_SwitchMode theLocalSwitchMode,
                             CT_SwitchDomainMode theSwitchDomainMode);
    
protected:
    
    T6100_CardIf&                                           myCardContext;
    FC_BbAction*                                            myBbAction;

    INT32                                                   myDebugLevel;    
    FC_Milliseconds                                         myTimeStart;             
    FC_Milliseconds                                         myTimeEnd;

    QRS_ResponseRegion*                                     myResponseRegion;
    CT_XC_CQMID                                             myLastResponse;

    CT_ShelfId                                              myShelfId;
};
#endif /* _INC_TSXC_BASEACTION_INCLUDED */
