/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 16, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 SYS Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SYSFACADE_H__
#define __TL1_SYSFACADE_H__

#ifndef __TL1_SYSENTITY_H__
#include <TL1Core/TL1_SysEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_SetDat( theDateAndTime, isDateSet, isTimeSet, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetDat( theDateAndTime, isDateSet, isTimeSet, theResponse ))

#define FACI_RtrvTod(theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTod( theResponse ))

#endif 
