/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 System Common Types
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __CT_TL1_SYSTEM_H__
#define __CT_TL1_SYSTEM_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

typedef enum {
    CT_TL1_Login,
    CT_TL1_Logout
} CT_TL1_LoginStatus;

typedef enum {
    WARM=1,
    COLD=3
} CT_TL1_InitPhase;

#endif
