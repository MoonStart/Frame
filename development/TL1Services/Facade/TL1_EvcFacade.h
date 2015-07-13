/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 16, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 cross-connection Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EVCFACADE_H__
#define __TL1_EVCFACADE_H__

#ifndef __FC_BBOBJECT_H__
#include <Blackboard/FC_BbObject.h>
#endif

#ifndef __TL1_EVCDOMAIN_H__
#include <TL1Core/TL1_EvcDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvEvc( theAid, theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvEvc( theAid, theAddr, theResponse ))

#define FACI_EntEvc( theAid, theAddr, theCircuitId, theRdld, theSVid, theAddCVid, theAddSVid, theBwpfCOS0, theIsAllFrame, theDiscPause, thePbitRegen, theAisState, theAisInterval, theAisMegLevel, theDestMacMode, theAlarmProfile, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntEvc( theAid, theAddr, theCircuitId, theRdld,  theSVid, theAddCVid, theAddSVid, theBwpfCOS0, theIsAllFrame, theDiscPause, thePbitRegen, theAisState, theAisInterval, theAisMegLevel, theDestMacMode, theAlarmProfile, theResponse, theHandle, theCtag ))

#define FACI_EdEvc( theAid, theCircuitId, theRdld, theIncl, theQua, theSVid, theAddCVid, theAddSVid, theRmvCVid, theRmvSVid, theBwpfCOS0, theDiscPause, thePbitRegen, theAisState, theAisInterval, theAisMegLevel, theDestMacMode, theLoopbackState, theLoopbackType, theAlarmProfile, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdEvc( theAid, theCircuitId, theRdld, theIncl, theQua, theSVid, theAddCVid, theAddSVid, theRmvCVid, theRmvSVid, theBwpfCOS0, theDiscPause, thePbitRegen, theAisState, theAisInterval, theAisMegLevel, theDestMacMode, theLoopbackState, theLoopbackType, theAlarmProfile, theResponse, theHandle, theCtag ))

#define FACI_DltEvc( theAid, theIncl, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltEvc( theAid, theIncl, theResponse, theHandle, theCtag ))

#define FACI_RtrvAlm( theAddr, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAlm( theAddr, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theResponse, true ))
 
#define FACI_RtrvCond( theAddr, theCondType, theLocation, theDirection, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCond( theAddr, theCondType, theLocation, theDirection, theResponse ))

#endif
