/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         February 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Alarm Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#define __TL1_ALARMDOMAIN_H__

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef _INC_CT_ARC_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_ARC_Definitions.h>
#endif

class CT_TL1_EntityAddr;

/**
   CLASS TL1_AlarmDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of Alarm related TL1 command a TL1 Entity
   to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_AlarmDomain
{
public:
    virtual void RtrvAlm( const CT_TL1_EntityAddr&,
                          CT_NotificationCode* theNotifCode,
                          CT_ConditionType* theCondType,
                          CT_SAFlag* theServAffectingFlag,
                          CT_NEFlag* theLocation,
                          CT_DirectionFlag* theDirection,
                          TL1_Response& theResponse,
                          bool includeNR = false ) const = 0;

    virtual void RtrvCond( const CT_TL1_EntityAddr&,
                          CT_ConditionType* theCondType,
                          CT_NEFlag* theLocation,
                          CT_DirectionFlag* theDirection,
                          TL1_Response& theResponse ) const = 0;

    virtual void OprArc( const CT_TL1_EntityAddr& theAddr,
                         const CT_ARC_Config* theArcMode,
                         const CT_ARCInterval* theArcHour,
                         const CT_ARCInterval* theArcMinutes,
                         TL1_Response& theResponse ) = 0;

    virtual void RlsArc( const CT_TL1_EntityAddr& theAddr, 
                         TL1_Response& theResponse ) = 0;

    virtual void RtrvArc( const CT_TL1_EntityAddr& theAddr,
                          const CT_ARC_Config* theArcMode,
                          TL1_Response& theResponse) const = 0;
};

#endif

