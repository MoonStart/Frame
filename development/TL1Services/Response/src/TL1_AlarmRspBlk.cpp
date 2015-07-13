/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 7, 2003- Jean-Francois Tremblay
DESCRIPTION:    Implementation file for TL1 Alarm response block
-----------------------------------------------------------------------------*/ 

#include <Response/TL1_AlarmRspBlk.h>

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription ) :
    itsEntityName( theEntityName ),
    itsSlotAddr( theSlotAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription ) :
    itsEntityName( theEntityName ),
    itsFacAddr( theFacAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_AdjacencyAddr >& theAdjacencyAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription ) :
    itsEntityName( theEntityName ),
    itsAdjacencyAddr( theAdjacencyAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_LinkAddr >& theLinkAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription ) :
    itsEntityName( theEntityName ),
    itsLinkAddr( theLinkAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription )
{
}


TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_LogicalAddr >& theLogicalAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription ) :
    itsEntityName( theEntityName ),
    itsLogicalAddr( theLogicalAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                                  const TL1_SmartParameter< bool >& theIsTransientCondition ) :
    itsEntityName( theEntityName ),
    itsSlotAddr( theSlotAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription ),
    itsIsTransientCondition( theIsTransientCondition )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                                  const TL1_SmartParameter< bool >& theIsTransientCondition ) :
    itsEntityName( theEntityName ),
    itsFacAddr( theFacAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription ),
    itsIsTransientCondition( theIsTransientCondition )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_AdjacencyAddr >& theAdjacencyAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                                  const TL1_SmartParameter< bool >& theIsTransientCondition ) :
    itsEntityName( theEntityName ),
    itsAdjacencyAddr( theAdjacencyAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription ),
    itsIsTransientCondition( theIsTransientCondition )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_LinkAddr >& theLinkAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                                  const TL1_SmartParameter< bool >& theIsTransientCondition ) :
    itsEntityName( theEntityName ),
    itsLinkAddr( theLinkAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription ),
    itsIsTransientCondition( theIsTransientCondition )
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_LogicalAddr >& theLogicalAddr,
                                  const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                                  const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                                  const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                                  const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                                  const TL1_SmartParameter< CT_NEFlag >& theLocation,
                                  const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                                  const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                                  const TL1_SmartParameter< bool >& theIsTransientCondition ) :
    itsEntityName( theEntityName ),
    itsLogicalAddr( theLogicalAddr ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsOccurenceTime( theOccurenceTime ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsDescription( theDescription ),
    itsIsTransientCondition( theIsTransientCondition )
{
}

TL1_AlarmRspBlk::~TL1_AlarmRspBlk()
{
}

TL1_AlarmRspBlk::TL1_AlarmRspBlk( const TL1_AlarmRspBlk& theBlock ) :
    itsEntityName( theBlock.itsEntityName ),
    itsSlotAddr( theBlock.itsSlotAddr ),
    itsFacAddr( theBlock.itsFacAddr ),
    itsLogicalAddr( theBlock.itsLogicalAddr ),
    itsAdjacencyAddr( theBlock.itsAdjacencyAddr ),
    itsLinkAddr( theBlock.itsLinkAddr ),
    itsNotifCode( theBlock.itsNotifCode ),
    itsConditionType( theBlock.itsConditionType ),
    itsServiceAffectingFlag( theBlock.itsServiceAffectingFlag ),
    itsOccurenceTime( theBlock.itsOccurenceTime ),
    itsLocation( theBlock.itsLocation ),
    itsDirection( theBlock.itsDirection ),
    itsDescription( theBlock.itsDescription ),
    itsIsTransientCondition ( theBlock.itsIsTransientCondition )
{
}

TL1_AlarmRspBlk& TL1_AlarmRspBlk::operator=( const TL1_AlarmRspBlk& theBlock )
{
    itsEntityName = theBlock.itsEntityName;
    itsSlotAddr = theBlock.itsSlotAddr;
    itsFacAddr = theBlock.itsFacAddr;
    itsLogicalAddr = theBlock.itsLogicalAddr;
    itsAdjacencyAddr = theBlock.itsAdjacencyAddr;
    itsLinkAddr = theBlock.itsLinkAddr;
    itsNotifCode = theBlock.itsNotifCode;           
    itsConditionType = theBlock.itsConditionType;
    itsServiceAffectingFlag = theBlock.itsServiceAffectingFlag;
    itsOccurenceTime = theBlock.itsOccurenceTime;
    itsLocation = theBlock.itsLocation;
    itsDirection = theBlock.itsDirection;    
    itsDescription = theBlock.itsDescription;
    itsIsTransientCondition = theBlock.itsIsTransientCondition;

    return *this;
}
