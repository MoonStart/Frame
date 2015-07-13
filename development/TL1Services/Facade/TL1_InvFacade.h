/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 16, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Slot Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_INVFACADE_H__
#define __TL1_INVFACADE_H__

#ifndef __TL1_INVDOMAIN_H__
#include <TL1Core/TL1_InvDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvInv( theAddr, theFWStatus, theSWStatus, theResponse, rtrvParameters ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvInv( theAddr, theFWStatus, theSWStatus, theResponse, rtrvParameters ))

#endif //__TL1_NEFACADE_H__
