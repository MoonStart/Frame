/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 7, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Alarm response block
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ALARMRSPBLK_H__
#define __TL1_ALARMRSPBLK_H__

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

#ifndef __CT_TL1_CONTROLPLANEADDR_H__
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#ifndef _INC_CT_AM_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef CT_TIME_H
#include <CommonTypes/CT_Time.h>
#endif

#include <vector>

using namespace std;


class TL1_AlarmRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_AlarmRspBlk(){}

    TL1_AlarmRspBlk( const TL1_AlarmRspBlk& theBlock );

	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription );

	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription );

   	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_LogicalAddr >& theLogicalAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription );

	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_AdjacencyAddr >& theAdjacencyAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription );

	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_LinkAddr >& theLinkAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription );


    /** With this constructors, we can specify if it's a transient condition.
     */
    TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                     const TL1_SmartParameter< bool >& theIsTransientCondition );

    /** With this constructors, we can specify if it's a transient condition.
    */
    TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_LogicalAddr >& theSlotAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                     const TL1_SmartParameter< bool >& theIsTransientCondition );

    /** With this constructors, we can specify if it's a transient condition.
     */
	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                     const TL1_SmartParameter< bool >&  theIsTransientCondition );

    /** With this constructors, we can specify if it's a transient condition.
     */
	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_AdjacencyAddr >& theAdjacencyAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                     const TL1_SmartParameter< bool >&  theIsTransientCondition );

	TL1_AlarmRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_LinkAddr >& theAdjacencyAddr,
                     const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                     const TL1_SmartParameter< CT_ConditionType >& theConditionType,
                     const TL1_SmartParameter< CT_SAFlag >& theServiceAffectingFlag,
                     const TL1_SmartParameter< CT_TimeTm >& theOccurenceTime,
                     const TL1_SmartParameter< CT_NEFlag >& theLocation,
                     const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                     const TL1_SmartParameter< CT_AlarmMessage >& theDescription,
                     const TL1_SmartParameter< bool >&  theIsTransientCondition );

	virtual ~TL1_AlarmRspBlk();

    TL1_AlarmRspBlk& operator=( const TL1_AlarmRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_TL1_SlotAddr >&
        GetSlotAddr() const
    {
        return itsSlotAddr;
    }

    const TL1_SmartParameter< CT_TL1_FacAddr >&
        GetFacAddr() const
    {
        return itsFacAddr;
    }

    const TL1_SmartParameter< CT_TL1_LogicalAddr >&
        GetLogicalAddr() const
    {
        return itsLogicalAddr;
    }

    const TL1_SmartParameter< CT_TL1_AdjacencyAddr >&
        GetAdjacencyAddr() const
    {
        return itsAdjacencyAddr;
    }

    const TL1_SmartParameter< CT_TL1_LinkAddr >&
        GetLinkAddr() const
    {
        return itsLinkAddr;
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

    const TL1_SmartParameter< CT_TimeTm >&
        GetOccurenceTime() const
    {
        return itsOccurenceTime;
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

    const TL1_SmartParameter< CT_AlarmMessage >&
        GetDescription() const
    {
        return itsDescription;
    }

    const TL1_SmartParameter< bool >&
        GetIsTransientCondition() const
    {
        return itsIsTransientCondition;
    }

private:
    TL1_SmartParameter< string >                 itsEntityName;
    TL1_SmartParameter< CT_TL1_SlotAddr >        itsSlotAddr;
    TL1_SmartParameter< CT_TL1_FacAddr >         itsFacAddr;
    TL1_SmartParameter< CT_TL1_LogicalAddr >     itsLogicalAddr;
    TL1_SmartParameter< CT_TL1_AdjacencyAddr >   itsAdjacencyAddr;
    TL1_SmartParameter< CT_TL1_LinkAddr >        itsLinkAddr;
    TL1_SmartParameter< CT_NotificationCode >    itsNotifCode;
    TL1_SmartParameter< CT_ConditionType >       itsConditionType;
    TL1_SmartParameter< CT_SAFlag >              itsServiceAffectingFlag;
    TL1_SmartParameter< CT_TimeTm >              itsOccurenceTime;
    TL1_SmartParameter< CT_NEFlag >              itsLocation;
    TL1_SmartParameter< CT_DirectionFlag >       itsDirection;
    TL1_SmartParameter< CT_AlarmMessage >        itsDescription;
    TL1_SmartParameter< bool >                   itsIsTransientCondition;
};


typedef TL1_Rtv_Response< TL1_AlarmRspBlk > TL1_AlarmResponse;


#endif
