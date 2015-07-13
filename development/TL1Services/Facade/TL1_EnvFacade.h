/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         Oct 1, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 External Control Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENVFACADE_H__
#define __TL1_ENVFACADE_H__

#ifndef __TL1_ENVDOMAIN_H__
#include <TL1Core/TL1_EnvDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvAlmEnv( theAddr, theNotifCode, theCondType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAlmEnv( theAddr, theNotifCode, theCondType, theResponse ))

#define FACI_RtrvAttrEnv( theAddr, theNotifCode, theCondType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAttrEnv( theAddr, theNotifCode, theCondType, theResponse ))

#define FACI_SetAttrEnv( theAddr, theNotifCode, theCondType, theAlarmMsg, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetAttrEnv( theAddr, theNotifCode, theCondType, theAlarmMsg, theResponse ))



#endif 
