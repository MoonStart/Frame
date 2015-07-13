/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         Oct 5, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Environment Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_EnvRspBlk.h>


TL1_EnvRspBlk::TL1_EnvRspBlk( const TL1_SmartParameter<CT_TL1_LogicalAddr>& theAddr,
                                    const TL1_SmartParameter<CT_NotificationCode>& theNotifCode,
                                    const TL1_SmartParameter<CT_ConditionType>& theConditionType,
                                    const TL1_SmartParameter<CT_TimeTm>& theOccurenceTime,
                                    const TL1_SmartParameter<CT_AlarmMessage>& theAlarmMsg ) :
    itsAddr(theAddr),
    itsNotifCode(theNotifCode),
    itsConditionType(theConditionType),
    itsOccurenceTime(theOccurenceTime),
    itsAlarmMsg(theAlarmMsg)
{
}

TL1_EnvRspBlk::~TL1_EnvRspBlk()
{
}
  
TL1_EnvRspBlk::TL1_EnvRspBlk( const TL1_EnvRspBlk& theBlock ) :
    itsAddr(theBlock.itsAddr),
    itsNotifCode(theBlock.itsNotifCode),
    itsConditionType(theBlock.itsConditionType),
    itsOccurenceTime(theBlock.itsOccurenceTime),
    itsAlarmMsg(theBlock.itsAlarmMsg)
{
}

TL1_EnvRspBlk& TL1_EnvRspBlk::operator=( const TL1_EnvRspBlk& theBlock )
{
    itsAddr = theBlock.itsAddr;
    itsNotifCode = theBlock.itsNotifCode;
    itsConditionType = theBlock.itsConditionType;
    itsOccurenceTime = theBlock.itsOccurenceTime;
    itsAlarmMsg = theBlock.itsAlarmMsg;

    return *this;
}

const TL1_SmartParameter<CT_TL1_LogicalAddr>& TL1_EnvRspBlk::GetAddr() const
{
    return itsAddr;
}

const TL1_SmartParameter<CT_NotificationCode>& TL1_EnvRspBlk::GetNotifCode() const
{
    return itsNotifCode;
}

const TL1_SmartParameter<CT_ConditionType>& TL1_EnvRspBlk::GetConditionType() const
{
    return itsConditionType;
}

const TL1_SmartParameter<CT_TimeTm>& TL1_EnvRspBlk::GetOccurenceTime() const
{
    return itsOccurenceTime;
}

const TL1_SmartParameter<CT_AlarmMessage>& TL1_EnvRspBlk::GetAlarmMsg() const
{
    return itsAlarmMsg;
}

