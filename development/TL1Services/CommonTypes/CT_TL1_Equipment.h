/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Equipment Common Types
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __CT_TL1_EQUIPMENT_H__
#define __CT_TL1_EQUIPMENT_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif


class CT_TL1_OpticalSignal
{
};

class CT_TL1_OpticalPathId
{
};


/**
   CLASS CT_TL1_PeriodSec

   This common type is used to specify a period in second
 */
class CT_TL1_PeriodSec
{
};

class CT_TL1_EqptMode
{
};


#endif
