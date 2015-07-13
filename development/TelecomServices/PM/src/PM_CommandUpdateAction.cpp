/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Action invoked when the Cfg region has changed. It will set
                flags so that the PM_Processor knows that it should hunt for
                Inhibition/Reset or Threshold setting changes.
--------------------------------------------------------------------------*/

#include "PM_CommandUpdateAction.h"

//-----------------------------------------------------------------
//##ModelId=3C1F6F6E01F4
PM_CommandUpdateAction::PM_CommandUpdateAction(void):
    myState(false)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6E01FE
PM_CommandUpdateAction::~PM_CommandUpdateAction()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6E0200
void PM_CommandUpdateAction::Run(FC_Object* theObject)
{
    // Set flag to trig.
    myState = true;

}


//-----------------------------------------------------------------
//##ModelId=3CBC723D01A7
void PM_CommandUpdateAction::SetState(bool theState) 
{ 
    myState = theState;

}


//-----------------------------------------------------------------
//##ModelId=3CBC723D01C5
bool PM_CommandUpdateAction::GetState(void) 
{
    return myState;

}
