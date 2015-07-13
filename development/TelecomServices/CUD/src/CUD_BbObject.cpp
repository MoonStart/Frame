/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Configuration file Upload/Download.
 TARGET   :     All.
 AUTHOR   :     April, 2007  Jim Beck
 DESCRIPTION:   CUD base class object.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include "../CUD_BbObject.h"


//-----------------------------------------------------------------
CUD_BbObject::CUD_BbObject()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
CUD_BbObject::~CUD_BbObject()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void CUD_BbObject::Init(restart_type theRestartType)
{
    // Reset all parameters to their default value.
    Reset();
}
