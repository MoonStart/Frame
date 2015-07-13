/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         February 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Alarm Profile Entity declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ALARMPROFILEENTITY_H__
#define __TL1_ALARMPROFILEENTITY_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __TL1_ALARMPROFILERSPBLK_H__
#include <Response/TL1_AlarmProfileRspBlk.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#include <AP/AP_AlarmProfile.h>

/**
   CLASS TL1_AlarmProfileEntity

   This is a logical entity which provides an interface to query and edit
   alarm profile.
 */
class TL1_AlarmProfileEntity : public TL1_Entity
{
public:
    TL1_AlarmProfileEntity();

    virtual ~TL1_AlarmProfileEntity();

    virtual void EdAlmProfile( const CT_EntityType& theEntityType,
                               const CT_ProfileTableId& theProfile,
                               CT_NotificationCode* theNotifCode,
                               CT_ConditionType* theCondType,
                               CT_NEFlag* theLocation,
                               CT_DirectionFlag* theDirection,
                               CT_SAFlag* theServAffectingFlag,
                               CT_PM_Period* theTimePeriod,
                               TL1_Response& theResponse ) const = 0;

    virtual void RtrvAlmProfile( const CT_EntityType& theEntityType,
                                 const CT_ProfileTableId& theProfile,
                                 CT_NotificationCode* theNotifCode,
                                 CT_ConditionType* theCondType,
                                 CT_SAFlag* theServiceAffectingFlag,
                                 CT_NEFlag* theLocation,
                                 CT_DirectionFlag* theDirection,
                                 CT_PM_Period* theTimePeriod,
                                 TL1_Response& theResponse ) const = 0;


    /** CLASS AppendAlarmProfileFunctor
    This functor append an alarm response block to a TL1Response
    given an entity, entity address and an alarm object
    */
    class AppendAlarmProfileFunctor : public unary_function< AP_AlarmProfile, void >
    {
    public:
        AppendAlarmProfileFunctor( const CT_EntityType& theEntityType,
            const CT_ProfileTableId& theProfile,
            TL1_Response& theResponse ) :
        itsEntityType( theEntityType ),
            itsProfileId( theProfile ),
            itsResponse( theResponse )
        {}
        
        void operator()( const AP_AlarmProfile& theProfile ) const
        {
            // CT_TimeTm temporary object due to bogus interface
            CT_TimeTm tempo;
            if ( theProfile.GetTimePeriod() != CT_PM_PERIOD_UNKNOWN )
            {
                TL1_AlarmProfileRspBlk respBlock( itsEntityType,
                    itsProfileId,
                    theProfile.GetNotificationCode(),
                    theProfile.GetConditionType(),
                    theProfile.GetSAFlag(),
                    theProfile.GetLocation(),
                    theProfile.GetDirection(),
                    theProfile.GetTimePeriod() ); 
                itsResponse.AddResponseBlock( respBlock );
            }
            else
            {
                TL1_AlarmProfileRspBlk respBlock( itsEntityType,
                    itsProfileId,
                    theProfile.GetNotificationCode(),
                    theProfile.GetConditionType(),
                    theProfile.GetSAFlag(),
                    theProfile.GetLocation(),
                    theProfile.GetDirection() ); 
                itsResponse.AddResponseBlock( respBlock );
            }
            
        }
        
    private:
        const CT_EntityType& itsEntityType;
        const CT_ProfileTableId& itsProfileId;
        TL1_Response& itsResponse;
    };
    
    
    class TL1_AlarmProfileFilter : public unary_function< AP_AlarmProfile, bool >
    {
    public:
        TL1_AlarmProfileFilter( const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
            const TL1_SmartParameter< CT_ConditionType >& theCondType,
            const TL1_SmartParameter< CT_SAFlag >& theServAffectingFlag,
            const TL1_SmartParameter< CT_NEFlag >& theLocation,
            const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
            const TL1_SmartParameter< CT_PM_Period >& theTimePeriod) :
            itsNotifCode(theNotifCode),
            itsCondType(theCondType),
            itsServAffectingFlag(theServAffectingFlag),
            itsLocation(theLocation),
            itsDirection(theDirection),
            itsTimePeriod(theTimePeriod)
        {}
        
        bool operator()( const AP_AlarmProfile& theProfile ) const
        {
            bool result = true;
            
            if ( itsNotifCode.IsPresent() &&
                (itsNotifCode.GetValue() != theProfile.GetNotificationCode()) )
            {
                result = false;
            }
            
            if ( itsCondType.IsPresent() &&
                (itsCondType.GetValue() != theProfile.GetConditionType()) )
            {
                result = false;
            }
            
            if ( itsServAffectingFlag.IsPresent() &&
                (itsServAffectingFlag.GetValue() != theProfile.GetSAFlag()) )
            {
                result = false;
            }

            if ( itsLocation.IsPresent() &&
                (itsLocation.GetValue() != theProfile.GetLocation()) )
            {
                result = false;
            }
            
            if ( itsDirection.IsPresent() &&
                 ( itsDirection.GetValue() != theProfile.GetSimpleDirection() ) )
            {
                // In case we have both directions, NA direction shall not be sent.
                if ( ( itsDirection.GetValue() != CT_BOTH ) ||
                     ( itsDirection.GetValue() == CT_BOTH && theProfile.GetSimpleDirection() == CT_DIR_DONT_CARE ) )
                {
                    result = false;
                }
            }

            if ( itsTimePeriod.IsPresent() &&
                (itsTimePeriod.GetValue() != theProfile.GetTimePeriod()) )
            {
                result = false;
            }
            
            return result;
        }
        
    private:
        const TL1_SmartParameter< CT_NotificationCode > itsNotifCode;
        const TL1_SmartParameter< CT_ConditionType > itsCondType;
        const TL1_SmartParameter< CT_SAFlag > itsServAffectingFlag;
        const TL1_SmartParameter< CT_NEFlag > itsLocation;
        const TL1_SmartParameter< CT_DirectionFlag > itsDirection;
        const TL1_SmartParameter< CT_PM_Period > itsTimePeriod;
    };
    

};


#endif
