/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Alarm Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ALMFACADE_H__
#define __TL1_ALMFACADE_H__

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_ALARMPROFILEENTITY_H__
#include <TL1Core/TL1_AlarmProfileEntity.h>
#endif

#define FACI_RtrvAlm( theAddr, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAlm( theAddr, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theResponse, true ))

#define FACI_RtrvCond( theAddr, theCondType, theLocation, theDirection, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCond( theAddr, theCondType, theLocation, theDirection, theResponse ))

#define FACI_RtrvArc( theAddr, theArcMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvArc( theAddr, theArcMode, theResponse ))

#define FACI_OprArc( theAddr, theArcMode, theArcHour, theArcMinutes, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprArc( theAddr, theArcMode, theArcHour, theArcMinutes, theResponse ))

#define FACI_RlsArc( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RlsArc( theAddr, theResponse ))

#define FACI_EdAlmProfile( theAidType, theProfile, theNotifCode, theCondType, theLocation, theDirection, theServAffectingFlag, theTimePeriod, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdAlmProfile( theAidType, theProfile, theNotifCode, theCondType, theLocation, theDirection, theServAffectingFlag, theTimePeriod, theResponse ))

#define FACI_RtrvAlmProfile( theAidType, theProfile, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theTimePeriod, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAlmProfile( theAidType, theProfile, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theTimePeriod, theResponse ))

#endif
