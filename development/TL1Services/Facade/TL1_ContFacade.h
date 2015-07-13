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

#ifndef __TL1_CONTFACADE_H__
#define __TL1_CONTFACADE_H__

#ifndef __TL1_CONTDOMAIN_H__
#include <TL1Core/TL1_ContDomain.h>
#endif

#ifndef __FC_BBOBJECT_H__
#include <Blackboard/FC_BbObject.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_OprExtCont( theAddr, theContType, theContDuration, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprExtCont( theAddr, theContType, theContDuration, theResponse ))

#define FACI_RlsExtCont( theAddr, theContType, theContDuration, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RlsExtCont( theAddr, theContType, theContDuration, theResponse ))

#define FACI_RtrvAttrCont( theAddr, theContType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAttrCont( theAddr, theContType, theResponse ))

#define FACI_RtrvExtCont( theAddr, theContType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvExtCont( theAddr, theContType, theResponse ))

#define FACI_SetAttrCont( theAddr, theContType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetAttrCont( theAddr, theContType, theResponse ))

#define FACI_OprAco( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprAco( theResponse ))

#endif 
