/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 28, 2003- Jean-Francois Tremblay
DESCRIPTION:    Implementation file for TL1 Alarm Profile response block
-----------------------------------------------------------------------------*/ 

#include <Response/TL1_AlarmProfileRspBlk.h>

TL1_AlarmProfileRspBlk::TL1_AlarmProfileRspBlk(
        const TL1_SmartParameter< CT_EntityType >& theEntityType,
        const TL1_SmartParameter< CT_ProfileTableId >& theProfileId,
        const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
        const TL1_SmartParameter< CT_ConditionType >& theConditionType,
        const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection ) :
    itsEntityType( theEntityType ),
    itsProfileId( theProfileId ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsLocation( theLocation ),
    itsDirection( theDirection )
{
}

TL1_AlarmProfileRspBlk::TL1_AlarmProfileRspBlk(
        const TL1_SmartParameter< CT_EntityType >& theEntityType,
        const TL1_SmartParameter< CT_ProfileTableId >& theProfileId,
        const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
        const TL1_SmartParameter< CT_ConditionType >& theConditionType,
        const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PM_Period >& theTimePeriod ) :
    itsEntityType( theEntityType ),
    itsProfileId( theProfileId ),
    itsNotifCode( theNotifCode ),
    itsConditionType( theConditionType ),
    itsServiceAffectingFlag( theServiceAffectingFlag ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsTimePeriod( theTimePeriod )
{
}

TL1_AlarmProfileRspBlk::~TL1_AlarmProfileRspBlk()
{
}

TL1_AlarmProfileRspBlk::TL1_AlarmProfileRspBlk( const TL1_AlarmProfileRspBlk& theBlock ) :
    itsEntityType( theBlock.itsEntityType ),
    itsProfileId( theBlock.itsProfileId ),
    itsNotifCode( theBlock.itsNotifCode ),
    itsConditionType( theBlock.itsConditionType ),
    itsServiceAffectingFlag( theBlock.itsServiceAffectingFlag ),
    itsLocation( theBlock.itsLocation ),
    itsDirection( theBlock.itsDirection ),
    itsTimePeriod( theBlock.itsTimePeriod )
{
}

TL1_AlarmProfileRspBlk& TL1_AlarmProfileRspBlk::operator=( const TL1_AlarmProfileRspBlk& theBlock )
{
    itsEntityType = theBlock.itsEntityType;
    itsProfileId = theBlock.itsProfileId;
    itsNotifCode = theBlock.itsNotifCode;           
	itsConditionType = theBlock.itsConditionType;
	itsServiceAffectingFlag = theBlock.itsServiceAffectingFlag;
	itsLocation = theBlock.itsLocation;
	itsDirection = theBlock.itsDirection;
    itsTimePeriod = theBlock.itsTimePeriod;

    return *this;
}
