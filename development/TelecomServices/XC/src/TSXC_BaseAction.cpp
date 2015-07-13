/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     May, 2009            Kumar C Solai
    DESCRIPTION:   TSXC Base Action Class Implementaion.
--------------------------------------------------------------------------*/
#include <Blackboard/FC_BbXferTxAction.h>
#include <Blackboard/FC_BbReason.h>
#include <XC/TSXC_BaseAction.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <QRS/QRS_ResponseRegion.h>
#include <CsPii/CSPII_CardIF.h>

//---------------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------------
TSXC_BaseAction::TSXC_BaseAction(T6100_CardIf& theCardContext):
        myCardContext(theCardContext),  myBbAction(NULL), myResponseRegion(NULL)
{
    myDebugLevel = 0;
    myBbAction   = new FC_BbAction(this);

    myLastResponse.type = 0;
    myLastResponse.reqid = -1;
    myLastResponse.shelf = 0;
    myLastResponse.slot = 0;
    myLastResponse.port = 0;
    myLastResponse.step = 0;
    myLastResponse.qmgrIdx = 0;

    myShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
}

//---------------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------------
TSXC_BaseAction::~TSXC_BaseAction()
{
    delete myBbAction;
}

//---------------------------------------------------------------------------------
FC_BbAction* TSXC_BaseAction::GetBbAction()
{ 
    return myBbAction; 
}

//---------------------------------------------------------------------------------
void TSXC_BaseAction::AddInputRegion( FC_BbRegion* theInputRegion, bool theCheckValid, int obsPriority, bool theRefreshTrigger)
{
    GetBbAction()->AddInputRegion( theInputRegion, theCheckValid, true, true, obsPriority, theRefreshTrigger);
}

//----------------------------------------------------------------------------------
void TSXC_BaseAction::RemoveInputRegion( FC_BbRegion* theInputRegion )
{
    GetBbAction()->RemoveInputRegion( theInputRegion );
}

//----------------------------------------------------------------------------------
void TSXC_BaseAction::AddOutputRegion( FC_BbRegion* theOutputRegion )
{
    GetBbAction()->AddOutputRegion( theOutputRegion );
}

//----------------------------------------------------------------------------------
void TSXC_BaseAction::RemoveOutputRegion( FC_BbRegion* theOutputRegion )
{
    GetBbAction()->RemoveOutputRegion( theOutputRegion );
}

//----------------------------------------------------------------------------------
void TSXC_BaseAction::SetDebugLevel(int theValue)
{
    myDebugLevel = theValue;
}

//----------------------------------------------------------------------------------
FC_Object* TSXC_BaseAction::DoRunWithReason(unsigned theRunReason, 
                            FC_Object* theInvokerObj, FC_Object* theParam)
{
    FC_THROW_ERROR(FC_NotSupportedError, "Unexpected call to the base action class");
    return NULL;
}
    
//----------------------------------------------------------------------------------
void TSXC_BaseAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
//----------------------------------------------------------------------------------
void TSXC_BaseAction::Respond(CT_XC_CQMID theResponse )
{
    if (myResponseRegion != NULL)
    {
        if (!(myLastResponse == theResponse))
        {
            (*myResponseRegion)[0].Type = theResponse.type;
            (*myResponseRegion)[0].ReqId = theResponse.reqid;
            (*myResponseRegion)[0].Shelf = theResponse.shelf;
            (*myResponseRegion)[0].Slot = theResponse.slot;
            (*myResponseRegion)[0].Port = theResponse.port;
            (*myResponseRegion)[0].Step = theResponse.step;
            (*myResponseRegion)[0].QmgrIdx = theResponse.qmgrIdx;

            myResponseRegion->IncModificationCounter();

            // Region transfer is more efficient on MTERA so
            // there is no need to invoke ImmediateXfer().
            if (myShelfId == MTERA_SHELF_1)
            {
                myResponseRegion->UpdateNotify();
            }
            else
            {
                /* ImmediateXfer() has been temporarily modified to
                   disable immediate transfer so explicitly immediately
                   transfer the response region here
                // Transfer region immediately to speed up qrs requests
                myResponseRegion->ImmediateXfer();
                */

                FC_BbXferTxAction  aTxAction( myResponseRegion->GetTxAction().GetStream() );
                aTxAction.DoRunWithReason(FC_BbReason::MODIFICATION, NULL, (myResponseRegion));
            }

            myLastResponse = theResponse;
        }
    }
}

//----------------------------------------------------------------------------------
uint8 TSXC_BaseAction::PhysToLogicalShelf(uint8 thePhysShelf, CT_TEL_SwitchMode theSwitchMode, CT_SwitchDomainMode theSwitchDomainMode)
{
    uint8  logicalShelf = 0;

    //For the scenario of a multishelf switchdomain, or single expandable, the logical shelf number should 
    //simply be a 0-based version of its physical shelf number
    if (theSwitchDomainMode != CT_SWITCHDOMAINMODE_ALL &&
        theSwitchDomainMode != CT_SWITCHDOMAINMODE_UNKNOWN)
    {
        logicalShelf = thePhysShelf-1; // make it zero base.
    }
    else if (theSwitchMode == CT_TEL_SwitchMode_Cntr_Switch)
    {
        if (thePhysShelf == myShelfId)
        {
            logicalShelf = 0;
        }
        else
        {
            logicalShelf = 1;
        }
    }
    else if (theSwitchMode == CT_TEL_SwitchMode_Repeater)
    {
        if (thePhysShelf == myShelfId)
        {
            logicalShelf = 1;
        }
        else
        {
            logicalShelf = 0;
        }
    }

    return logicalShelf;
}

//----------------------------------------------------------------------------------
