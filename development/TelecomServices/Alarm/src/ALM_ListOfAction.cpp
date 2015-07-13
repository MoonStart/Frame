/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   TThis class is an action that wake-up a one-shot process.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_ListOfAction.h>
#include <Blackboard/FC_BbRegion.h>
#include <BaseClass/FC_Object.h>
#include <T6100_CardActiveRegion.h>

#include <Alarm/ALM_SubApplicationOnCard.h>

#include "ALM_ListOfAction.h"

//-----------------------------------------------------------------
//##ModelId=3C506C3301CB
ALM_ListOfAction::ALM_ListOfAction (ALM_SubApplicationOnCard& theApplication):
    myApplication(theApplication),
    itsFirstExec(true),
    itsTransferEnable(false),
    itsPreviousContextActive(false)
{
}


//-----------------------------------------------------------------
//##ModelId=3C506C3301D5
ALM_ListOfAction::~ALM_ListOfAction ()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C3301E9
void ALM_ListOfAction::InsertRegion( FC_BbRegion* theRegion)
{
    itsRegionVector.push_back( theRegion );
}

//-----------------------------------------------------------------
//##ModelId=3C506C3301F2
FC_Object* ALM_ListOfAction::DoRunWithReason(unsigned theRunReason,
					     FC_Object* theInvoker,
					     FC_Object* theParam)
{
    vector<FC_BbRegion*>::iterator aPtr = itsRegionVector.begin();
    vector<FC_BbRegion*>::iterator aLast = itsRegionVector.end();

    //Verify if context is active. If not, then reset all action once
    bool aContextActive = myApplication.GetContextStatusRegion().GetActive();
    if (aContextActive != itsPreviousContextActive)
    {
        itsPreviousContextActive = aContextActive;
        if (!aContextActive)
        {
            myApplication.ResetAllActions();
        }
    }

    // Run all action within the action list
    FC_ListOfAction::DoRunWithReason( theRunReason, theInvoker, theParam );

    // Update notify all regions about the change, force a transfer of region,
    // only when transfer is allowed (after booting time is elapsed).
    if (itsTransferEnable)
    {
        while ( aPtr != aLast)
        {
            (*aPtr++)->UpdateNotify();
        }
    }
    else if (itsFirstExec)
    {
        myApplication.WakeUpTimeBeforeTransfer();   
        itsFirstExec = false;
    }

    return NULL;
}

//-----------------------------------------------------------------
//##ModelId=3DBFFAE700E8
void ALM_ListOfAction::IncModifyCounterOfAllRegion()
{
    vector<FC_BbRegion*>::iterator aPtr = itsRegionVector.begin();
    vector<FC_BbRegion*>::iterator aLast = itsRegionVector.end();

    // Update notify all regions about the change, force a transfer of region,
    // only when transfer is allowed (after booting time is elapsed).
    while ( aPtr != aLast)
    {
        (*aPtr++)->IncModificationCounter();
    }
}

//-----------------------------------------------------------------
//##ModelId=3C603CA102A4
void ALM_ListOfAction::DeleteAllAction()
{
    FC_ListOfAction::iterator anIterator = Begin();
    while (anIterator != End())
    {
        delete *anIterator;
        anIterator++;
    }
}

//-----------------------------------------------------------------
//##ModelId=3C95FE090149
FC_Action* ALM_ListOfAction::operator[](int theIndex)
{
    int aCount;
    FC_ListOfAction::iterator anIterator;
    for (anIterator = Begin(), aCount = 0; anIterator != End(); anIterator++, aCount++)
    {
        if (aCount == theIndex)
            return *anIterator;
    }
    return NULL;
}

//-----------------------------------------------------------------
//##ModelId=3CC4D1D3012B
const char* ALM_ListOfAction::GetInstanceName(void ) const
{
    return myApplication.GetInstanceName();
}
