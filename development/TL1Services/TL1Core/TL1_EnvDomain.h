/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Environment Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENVDOMAIN_H__
#define __TL1_ENVDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif


/**
   CLASS TL1_EnvDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of environment related TL1 commands, that a TL1
   Entities for an environment is expected to implement. This class contains
   no data member nor any default implementation.
 */
class TL1_EnvDomain
{
public:

    virtual void RtrvAlmEnv( const CT_TL1_LogicalAddr& theAddr,
                             CT_NotificationCode* theNotifCode,
                             CT_ConditionType* theCondType,
                             TL1_Response& theResponse,
                             bool includeNR = false )const = 0;

    virtual void RtrvAttrEnv(const CT_TL1_LogicalAddr& addr,
                             CT_NotificationCode* theNotifCode,
                             CT_ConditionType* theCondType,
                             TL1_Response& theResponse )const = 0;

    virtual void SetAttrEnv( const CT_TL1_LogicalAddr& theAddr,
                             CT_NotificationCode* theNotifCode,
                             CT_ConditionType* theCondType,
                             CT_AlarmMessage* theAlarmMsg,
                             TL1_Response& theResponse )= 0;

};

#endif
