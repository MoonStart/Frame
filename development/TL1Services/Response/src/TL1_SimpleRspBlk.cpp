/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_SimpleRspBlk.h>

TL1_SimpleRspBlk::TL1_SimpleRspBlk( TL1_COMPLETION_CODE tcc, TL1_ERROR_CODE tec )
    : mytcc( tcc ), mytec( tec )
{
}

TL1_SimpleRspBlk::~TL1_SimpleRspBlk()
{
}
