/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 23, 2004 Maggie Zhang
DESCRIPTION:    Header file for TL1 Protection Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PROTNFACADE_H__
#define __TL1_PROTNFACADE_H__

#ifndef __FC_BBOBJECT_H__
#include <Blackboard/FC_BbObject.h>
#endif

#ifndef __TL1_PROTNDOMAIN_H__
#include <TL1Core/TL1_ProtnDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvProtn( theAddr, theProtMod, theFacMod, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvProtn( theAddr, theProtMod, theFacMod, theResponse ))

#define FACI_EntProtn( theAddr, theType, theRtrtv, theWtr, theProtHoldOffTime, theProtType, theBiDirSwitching, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntProtn( theAddr, theType, theRtrtv, theWtr, theProtHoldOffTime, theProtType, theBiDirSwitching, theResponse, theHandle, theCtag ))

#define FACI_EntSync( theAddr, theType, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntSync( theAddr, theType,theResponse, theHandle, theCtag ))

#define FACI_EdProtn( theAddr, theRvrtv, theWtr, theProtHoldOffTime, theBiDirSwitching, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdProtn( theAddr, theRvrtv, theWtr, theProtHoldOffTime, theBiDirSwitching, theResponse, theHandle, theCtag ))

#define FACI_DltProtn( theAddr, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltProtn( theAddr, theResponse, theHandle, theCtag ))

#define FACI_OprProtnSw( theAddr, theSwtchCmd, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprProtnSw( theAddr, theSwtchCmd, theResponse, theHandle, theCtag ))



#endif
