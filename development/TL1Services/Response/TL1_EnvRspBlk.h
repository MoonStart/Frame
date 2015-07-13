/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         Oct 5, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Environment Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENVRSPBLK_H__
#define __TL1_ENVRSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_TIME_H__
#include <CommonTypes/CT_Time.h>
#endif
 
#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif


class TL1_EnvRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_EnvRspBlk() {}
    
    TL1_EnvRspBlk( const TL1_EnvRspBlk& );

    TL1_EnvRspBlk( const TL1_SmartParameter<CT_TL1_LogicalAddr>& theAddr,
                   const TL1_SmartParameter<CT_NotificationCode>& theNotifCode,
                   const TL1_SmartParameter<CT_ConditionType>& theConditionType,
                   const TL1_SmartParameter<CT_TimeTm>& theOccurenceTime,                   
                   const TL1_SmartParameter<CT_AlarmMessage>& theAlarmMsg );
    
    virtual ~TL1_EnvRspBlk();

    TL1_EnvRspBlk& operator=( const TL1_EnvRspBlk& theBlock );

    const TL1_SmartParameter<CT_TL1_LogicalAddr>& GetAddr() const;

    const TL1_SmartParameter<CT_NotificationCode>& GetNotifCode() const;

    const TL1_SmartParameter<CT_ConditionType>& GetConditionType() const;    

    const TL1_SmartParameter<CT_TimeTm>& GetOccurenceTime() const;

    const TL1_SmartParameter<CT_AlarmMessage>& GetAlarmMsg() const;

private:
    TL1_SmartParameter<CT_TL1_LogicalAddr> itsAddr;
    TL1_SmartParameter<CT_NotificationCode> itsNotifCode;
    TL1_SmartParameter<CT_ConditionType> itsConditionType;    
    TL1_SmartParameter<CT_TimeTm> itsOccurenceTime;
    TL1_SmartParameter<CT_AlarmMessage> itsAlarmMsg;
};

typedef TL1_Rtv_Response< TL1_EnvRspBlk > TL1_EnvResponse;

#endif


