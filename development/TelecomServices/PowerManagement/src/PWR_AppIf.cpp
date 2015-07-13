/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/

#include "../PWR_AppIf.h"
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include "CsPii/CSPII_ShelfIF.h"
#include <CsPii/CSPII_CardIF.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <CommonTypes/CT_CardTypes.h>


////////////////////////////////////////////////////////////////////////////////
PWR_AppIf::PWR_AppIf(T6100_CardIf & theContext) :
    myContext(theContext)
{
}

////////////////////////////////////////////////////////////////////////////////
PWR_AppIf::~PWR_AppIf()
{
}


T6100_CardIf& PWR_AppIf::GetContext()
{
    return myContext;
}



