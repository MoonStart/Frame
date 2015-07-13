/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Steve Thiffault, April 15, 2002.
 DESCRIPTION:   PM base class object.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include "../PM_BbObject.h"


//-----------------------------------------------------------------
//##ModelId=3CBC724001C1
PM_BbObject::PM_BbObject()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC724001CA
PM_BbObject::~PM_BbObject()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC724001D4
void PM_BbObject::Init(restart_type theRestartType)
{
    // Reset all parameters to their default value.
    Reset();

}
