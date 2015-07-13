/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 28, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Alarm Profile response block
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ALARMPROFILERSPBLK_H__
#define __TL1_ALARMPROFILERSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef _INC_CT_AM_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef CT_TIME_H
#include <CommonTypes/CT_Time.h>
#endif

#ifndef CT_PM_DEFINITION_H
#include <CommonTypes/CT_PM_Definition.h>
#endif

#include <vector>

using namespace std;


class TL1_AlarmProfileRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_AlarmProfileRspBlk(){}

    TL1_AlarmProfileRspBlk( const TL1_AlarmProfileRspBlk& theBlock );

    TL1_AlarmProfileRspBlk( const TL1_SmartParameter< CT_EntityType >& theEntityType,
                            const TL1_SmartParameter< CT_ProfileTableId >& theProfileId,
                            const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                            const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                            const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                            const TL1_SmartParameter< CT_NEFlag >& theLocation,
                            const TL1_SmartParameter< CT_DirectionFlag >& theDirection );

	TL1_AlarmProfileRspBlk( const TL1_SmartParameter< CT_EntityType >& theEntityType,
                            const TL1_SmartParameter< CT_ProfileTableId >& theProfileId,
                            const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                            const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                            const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                            const TL1_SmartParameter< CT_NEFlag >& theLocation,
                            const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                            const TL1_SmartParameter< CT_PM_Period >& theTimePeriod );

	virtual ~TL1_AlarmProfileRspBlk();

    TL1_AlarmProfileRspBlk& operator=( const TL1_AlarmProfileRspBlk& theBlock );

    const TL1_SmartParameter< CT_EntityType >&
        GetEntityType() const
    {
        return itsEntityType;
    }

    const TL1_SmartParameter< CT_ProfileTableId >&
        GetProfileId() const
    {
        return itsProfileId;
    }

    const TL1_SmartParameter< CT_NotificationCode >&
        GetNotificationCode() const
    {
        return itsNotifCode;
    }

    const TL1_SmartParameter< CT_ConditionType >&
        GetConditionType() const
    {
        return itsConditionType;
    }

    const TL1_SmartParameter< CT_SAFlag >&
        GetServiceAffectingFlag() const
    {
        return itsServiceAffectingFlag;
    }

    const TL1_SmartParameter< CT_NEFlag >&
        GetLocation() const
    {
        return itsLocation;
    }

    const TL1_SmartParameter< CT_DirectionFlag >&
        GetDirection() const
    {
        return itsDirection;
    }

    const TL1_SmartParameter< CT_PM_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }

private:
	TL1_SmartParameter< CT_EntityType >       itsEntityType;
    TL1_SmartParameter< CT_ProfileTableId >   itsProfileId;
	TL1_SmartParameter< CT_NotificationCode > itsNotifCode;
	TL1_SmartParameter< CT_ConditionType >    itsConditionType;
	TL1_SmartParameter< CT_SAFlag >           itsServiceAffectingFlag;
	TL1_SmartParameter< CT_NEFlag >           itsLocation;
	TL1_SmartParameter< CT_DirectionFlag >    itsDirection;
    TL1_SmartParameter< CT_PM_Period >        itsTimePeriod;
};


typedef TL1_Rtv_Response< TL1_AlarmProfileRspBlk > TL1_AlarmProfileResponse;


#endif