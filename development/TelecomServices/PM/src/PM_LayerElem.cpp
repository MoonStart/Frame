/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM: 	Performance Monitoring.
 TARGET   : 	All.
 AUTHOR   : 	15 June, 1998 Jean-Francois Birtz.
 DESCRIPTION:	The Layer element is all that is common to each layer for
				updating the PM parameters.
--------------------------------------------------------------------------*/

#include "../PM_Def.h"
#include "PM_LayerElem.h"


//-----------------------------------------------------------------
//##ModelId=3C1F6F6C01E7
PM_LayerElem::PM_LayerElem () :
    mySecInOstate(0),
    myUAstate(false)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6C01F1
PM_LayerElem::~PM_LayerElem ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6C01F2
bool PM_LayerElem::UpdateUA(bool theSES) 
{
    // If the SES can change the UA state, see if the UA
    // state has to change (10 consecutif seconds with
    // the same SES).
    if (myUAstate != theSES)
    {
        mySecInOstate++;
        if (mySecInOstate >= PM_NB_SES_FOR_UA)
        {
            myUAstate = !myUAstate;
            mySecInOstate = 0;
        }
    }

    else
    {
        mySecInOstate = 0;
    }

    return myUAstate;

}
