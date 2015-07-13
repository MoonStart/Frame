/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Equipment Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Equipment Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PMRSPBLK_H__
#define __TL1_PMRSPBLK_H__

#include <string>

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

#ifndef __CT_TL1_PM_H__
#include <CommonTypes/CT_TL1_Pm.h>
#endif

#ifndef CT_TIME_H
#include <CommonTypes/CT_Time.h>
#endif

#ifndef CT_PMA_CONFIG_H
#include <CommonTypes/CT_PMA_Config.h>
#endif

#ifndef CT_PMA_FTP_H
#include <CommonTypes/CT_PM_Ftp.h>
#endif

#ifndef CT_PMA_GENERAL_H
#include <CommonTypes/CT_PMA_General.h>
#endif

#ifndef CT_PMA_PARAMETER_H
#include <CommonTypes/CT_PMA_Parameter.h>
#endif

#ifndef CT_PMA_TCA_H
#include <CommonTypes/CT_PMA_Tca.h>
#endif

#ifndef __CT_IPSEC_H__
#include <CommonTypes/CT_IpSec.h>
#endif

using namespace std;


//-------------------------------------------------------------------------------------------
class TL1_GeneralPmRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_GeneralPmRspBlk(){}

    TL1_GeneralPmRspBlk( const TL1_GeneralPmRspBlk& theBlock );

    TL1_GeneralPmRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr);

	virtual ~TL1_GeneralPmRspBlk() = 0;

    TL1_GeneralPmRspBlk& operator=( const TL1_GeneralPmRspBlk& theBlock );

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

private:
    TL1_SmartParameter< CT_TL1_SlotAddr >     itsSlotAddr;
    TL1_SmartParameter< CT_TL1_FacAddr >      itsFacAddr;
    TL1_SmartParameter< CT_TL1_LogicalAddr >  itsLogicalAddr;
};    


//-------------------------------------------------------------------------------------------
class TL1_ReptEvtTcaRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_ReptEvtTcaRspBlk(){}

    TL1_ReptEvtTcaRspBlk( const TL1_ReptEvtTcaRspBlk& theBlock );

    TL1_ReptEvtTcaRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                          const TL1_SmartParameter< string >& theEntityName,
                          const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //ConditionType,
                          const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //ConditionType,
                          const TL1_SmartParameter< CT_TL1_ConditionEffect >& theConditionEffect,
                          const TL1_SmartParameter< CT_TimeTm >& theOcrDatOcrTim,
                          const TL1_SmartParameter< CT_NEFlag >& theLocation,
                          const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                          const TL1_SmartParameter< CT_PMA_ParamType >& theParamType, //theMonitorValue, ThresholdLevel
                          const TL1_SmartParameter< CT_PMA_64BitTcaValue >& theValue,         //theMonitorValue
                          const TL1_SmartParameter< CT_PMA_64BitTcaValue >& theThresholdValue, //theThresholdLevel,
                          const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
                          const TL1_SmartParameter< string >& theDescription );

    TL1_ReptEvtTcaRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                          const TL1_SmartParameter< string >& theEntityName,
                          const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //ConditionType,
                          const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //ConditionType,
                          const TL1_SmartParameter< CT_TL1_ConditionEffect >& theConditionEffect,
                          const TL1_SmartParameter< CT_TimeTm >& theOcrDatOcrTim,
                          const TL1_SmartParameter< CT_NEFlag >& theLocation,
                          const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                          const TL1_SmartParameter< CT_PMA_ParamType >& theParamType, //theMonitorValue, ThresholdLevel
                          const TL1_SmartParameter< CT_PMA_TcaValue >& theValue,         //theMonitorValue
                          const TL1_SmartParameter< CT_PMA_TcaValue >& theThresholdValue, //theThresholdLevel,
                          const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
                          const TL1_SmartParameter< string >& theDescription );

	virtual ~TL1_ReptEvtTcaRspBlk();

    TL1_ReptEvtTcaRspBlk& operator=( const TL1_ReptEvtTcaRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_PMA_ParamId >& //GetConditionType
        GetParamId() const
    {
        return itsParamId;
    }
    const TL1_SmartParameter< CT_PMA_MonTypeJust >& //GetConditionType
        GetMonTypeJust() const
    {
        return itsMonTypeJust;
    }

    const TL1_SmartParameter< CT_TL1_ConditionEffect >&
        GetConditionEffect() const
    {
        return itsConditionEffect;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetOcrDatOcrTim() const
    {
        return itsOcrDatOcrTim;
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
    
    const TL1_SmartParameter< CT_PMA_ParamType >& //GetMonitorValue, GetThresholdLevel
        GetParamType() const
    {
        return itsParamType;
    }

    const TL1_SmartParameter< CT_PMA_64BitTcaValue >& //GetMonitorValue
        GetValue() const
    {
        return itsValue;
    }

    const TL1_SmartParameter< CT_PMA_64BitTcaValue >& //GetThresholdLevel
        GetThresholdValue() const
    {
        return itsThresholdValue;
    }

    const TL1_SmartParameter< CT_PMA_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }

    const TL1_SmartParameter< string >&
        GetDescription() const
    {
        return itsDescription;
    }

private:
    TL1_SmartParameter< string >                   itsEntityName;
    TL1_SmartParameter< CT_PMA_ParamId >           itsParamId; //ConditionType
    TL1_SmartParameter< CT_PMA_MonTypeJust >       itsMonTypeJust; //ConditionType
    TL1_SmartParameter< CT_TL1_ConditionEffect >   itsConditionEffect;
    TL1_SmartParameter< CT_TimeTm >                itsOcrDatOcrTim;
    TL1_SmartParameter< CT_NEFlag >                itsLocation;
    TL1_SmartParameter< CT_DirectionFlag >         itsDirection;
    TL1_SmartParameter< CT_PMA_ParamType >         itsParamType; //MonitorValue, ThresholdLevel
    TL1_SmartParameter< CT_PMA_64BitTcaValue>      itsValue;     //MonitorValue
    TL1_SmartParameter< CT_PMA_64BitTcaValue >     itsThresholdValue; //itsThresholdLevel
    TL1_SmartParameter< CT_PMA_Period >            itsTimePeriod;
    TL1_SmartParameter< string >                   itsDescription;
};    
    
typedef TL1_Rtv_Response< TL1_ReptEvtTcaRspBlk > TL1_PmTcaResponse;



//-------------------------------------------------------------------------------------------
class TL1_RtrvPmRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvPmRspBlk(){}

    TL1_RtrvPmRspBlk( const TL1_RtrvPmRspBlk& theBlock );

    TL1_RtrvPmRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                      const TL1_SmartParameter< string >& theEntityName,
                      const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                      const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                      const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //theMonitorValue,
                                                CT_PMA_64BitGaugeInt * theValue,           //theMonitorValue,
                      const TL1_SmartParameter< CT_PMA_Validity >& theValidity,
                      const TL1_SmartParameter< CT_NEFlag >& theLocation,
                      const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                      const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
                      const TL1_SmartParameter< CT_TimeTm >& theMonDatMonTim );

    TL1_RtrvPmRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                      const TL1_SmartParameter< string >& theEntityName,
                      const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                      const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                      const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //theMonitorValue,
                                                CT_PMA_GaugeInt * theValue,           //theMonitorValue,
                      const TL1_SmartParameter< CT_PMA_Validity >& theValidity,
                      const TL1_SmartParameter< CT_NEFlag >& theLocation,
                      const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                      const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
                      const TL1_SmartParameter< CT_TimeTm >& theMonDatMonTim );

	virtual ~TL1_RtrvPmRspBlk();

    TL1_RtrvPmRspBlk& operator=( const TL1_RtrvPmRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_PMA_ParamId >& //GetMonitoringType
        GetParamId() const
    {
        return itsParamId;
    }

    const TL1_SmartParameter< CT_PMA_MonTypeJust >& //GetMonitoringType
        GetMonTypeJust() const
    {
        return itsMonTypeJust;
    }

    const TL1_SmartParameter< CT_PMA_ParamType >& //GetMonitorValue
        GetParamType() const
    {
        return itsParamType;
    }

    CT_PMA_64BitGaugeInt GetValue() const //GetMonitorValue 
    {
        return itsValue;
    }

    const TL1_SmartParameter< CT_PMA_Validity >&
                                    GetValidity() const
    {
        return itsValidity;
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

    const TL1_SmartParameter< CT_PMA_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetMonDatMonTim() const
    {
        return itsMonDatMonTim;
    }
   

private:
    TL1_SmartParameter< string >              itsEntityName;
    TL1_SmartParameter< CT_PMA_ParamId >      itsParamId;     //itsMonitoringType
    TL1_SmartParameter< CT_PMA_MonTypeJust >  itsMonTypeJust; //itsMonitoringType
    TL1_SmartParameter< CT_PMA_ParamType >    itsParamType; //MonitorValue
                        CT_PMA_64BitGaugeInt       itsValue;     //MonitorValue
    TL1_SmartParameter< CT_PMA_Validity >     itsValidity;
    TL1_SmartParameter< CT_NEFlag >           itsLocation;
    TL1_SmartParameter< CT_DirectionFlag >    itsDirection;
    TL1_SmartParameter< CT_PMA_Period >       itsTimePeriod;
    TL1_SmartParameter< CT_TimeTm >           itsMonDatMonTim;
};
    
typedef TL1_Rtv_Response< TL1_RtrvPmRspBlk > TL1_RtrvPmResponse;


//-------------------------------------------------------------------------------------------
class TL1_RtrvPmDayRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RtrvPmDayRspBlk(){}

    TL1_RtrvPmDayRspBlk( const TL1_RtrvPmDayRspBlk& theBlock );

    TL1_RtrvPmDayRspBlk( const TL1_SmartParameter< CT_TimeTm >& thePmDayStart );

	virtual ~TL1_RtrvPmDayRspBlk();

    TL1_RtrvPmDayRspBlk& operator=( const TL1_RtrvPmDayRspBlk& theBlock );

    const TL1_SmartParameter< CT_TimeTm >&
        GetPmDayStart() const
    {
        return itsPmDayStart;
    }
   

private:
    TL1_SmartParameter< CT_TimeTm >         itsPmDayStart;
};    
    
typedef TL1_Rtv_Response< TL1_RtrvPmDayRspBlk > TL1_RtrvPmDayResponse;


//-------------------------------------------------------------------------------------------
class TL1_RtrvPmModeRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvPmModeRspBlk(){}

    TL1_RtrvPmModeRspBlk( const TL1_RtrvPmModeRspBlk& theBlock );

    TL1_RtrvPmModeRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                          const TL1_SmartParameter< string >& theEntityName,
                          const TL1_SmartParameter< CT_NEFlag >& theLocation,
                          const TL1_SmartParameter< CT_TL1_ModeType >& theModeType,
                          const TL1_SmartParameter< bool >& thePmState);

	virtual ~TL1_RtrvPmModeRspBlk();

    TL1_RtrvPmModeRspBlk& operator=( const TL1_RtrvPmModeRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_NEFlag >&
        GetLocation() const
    {
        return itsLocation;
    }

    const TL1_SmartParameter< CT_TL1_ModeType >&
        GetModeType() const
    {
        return itsModeType;
    }

    const TL1_SmartParameter< bool >&
        GetPmState() const
    {
        return itsPmState;
    }

private:
    TL1_SmartParameter< string >           itsEntityName;
    TL1_SmartParameter< CT_NEFlag >        itsLocation;
    TL1_SmartParameter< CT_TL1_ModeType >  itsModeType;
    TL1_SmartParameter< bool >             itsPmState;
};    
    
typedef TL1_Rtv_Response< TL1_RtrvPmModeRspBlk > TL1_RtrvPmModeResponse;

//-------------------------------------------------------------------------------------------
class TL1_RtrvPmFileSchedRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvPmFileSchedRspBlk(){};

    TL1_RtrvPmFileSchedRspBlk( const TL1_RtrvPmFileSchedRspBlk& theBlock );

    TL1_RtrvPmFileSchedRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                               const TL1_SmartParameter< string >& theEntityName,
                               const TL1_SmartParameter< string >& theFtpServer,
                               const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
                               const TL1_SmartParameter< bool >& theInhibitionMode );
    
    virtual ~TL1_RtrvPmFileSchedRspBlk(){};

    TL1_RtrvPmFileSchedRspBlk& operator=( const TL1_RtrvPmFileSchedRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< string >&
        GetFtpServer() const
    {
        return itsFtpServer;
    }

    const TL1_SmartParameter< CT_PMA_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }

    const TL1_SmartParameter< bool >&
        GetInhibitionMode() const
    {
        return itsInhibitionMode;
    }

private:
    TL1_SmartParameter< string > itsEntityName;
    TL1_SmartParameter< string > itsFtpServer;
    TL1_SmartParameter< CT_PMA_Period > itsTimePeriod;
    TL1_SmartParameter< bool > itsInhibitionMode;
};

typedef TL1_Rtv_Response< TL1_RtrvPmFileSchedRspBlk > TL1_RtrvPmFileSchedResponse;

//-------------------------------------------------------------------------------------------
class TL1_RtrvPmSchedRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvPmSchedRspBlk(){}

    TL1_RtrvPmSchedRspBlk( const TL1_RtrvPmSchedRspBlk& theBlock );

    TL1_RtrvPmSchedRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                          const TL1_SmartParameter< string >& theEntityName,
                          const TL1_SmartParameter< CT_TimeTm >& theReportInterval,
                          const TL1_SmartParameter< CT_TimeTm >& theDateAndTime,
                          const TL1_SmartParameter< int >& theNumberInterval,
                          const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                          const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                          const TL1_SmartParameter< CT_PMA_DirnUpOrDn >& theDirnUpOrDn, //theMonitorLevel
                          const TL1_SmartParameter< long long >& theLevel,                    //theMonitorLevel
                          const TL1_SmartParameter< CT_NEFlag >& theLocation,
                          const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                          const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
                          const TL1_SmartParameter<  CT_TimeTm >& theTimeOffset,
                          const TL1_SmartParameter< bool >& theInhibitionMode );

    TL1_RtrvPmSchedRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                          const TL1_SmartParameter< string >& theEntityName,
                          const TL1_SmartParameter< CT_TimeTm >& theReportInterval,
                          const TL1_SmartParameter< CT_TimeTm >& theDateAndTime,
                          const TL1_SmartParameter< int >& theNumberInterval,
                          const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                          const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                          const TL1_SmartParameter< CT_PMA_DirnUpOrDn >& theDirnUpOrDn, //theMonitorLevel
                          const TL1_SmartParameter< int >& theLevel,                    //theMonitorLevel
                          const TL1_SmartParameter< CT_NEFlag >& theLocation,
                          const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                          const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
                          const TL1_SmartParameter<  CT_TimeTm >& theTimeOffset,
                          const TL1_SmartParameter< bool >& theInhibitionMode );


	virtual ~TL1_RtrvPmSchedRspBlk();

    TL1_RtrvPmSchedRspBlk& operator=( const TL1_RtrvPmSchedRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetReportInterval() const
    {
        return itsReportInterval;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetDateAndTime() const
    {
        return itsDateAndTime;
    }

    const TL1_SmartParameter< int >&
        GetNumberInterval() const
    {
        return itsNumberInterval;
    }

    const TL1_SmartParameter< CT_PMA_ParamId >& //GetMonitoringType
        GetParamId() const
    {
        return itsParamId;
    }

    const TL1_SmartParameter< CT_PMA_MonTypeJust >& //GetMonitoringType
        GetMonTypeJust() const
    {
        return itsMonTypeJust;
    }

    const TL1_SmartParameter< CT_PMA_DirnUpOrDn >& //GetMonitorLevel
        GetDirnUpOrDn() const
    {
        return itsDirnUpOrDn;
    }

    const TL1_SmartParameter< long long >&              //GetMonitorLevel
        GetLevel() const
    {
        return itsLevel;
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

    const TL1_SmartParameter< CT_PMA_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }
    
    const TL1_SmartParameter<  CT_TimeTm >&
        GetTimeOffset() const
    {
        return itsTimeOffset;
    }

    const TL1_SmartParameter< bool >&
        GetInhibitionMode() const
    {
        return itsInhibitionMode;
    }

private:
    TL1_SmartParameter< string >                itsEntityName;
    TL1_SmartParameter< CT_TimeTm >             itsReportInterval;
    TL1_SmartParameter< CT_TimeTm >             itsDateAndTime;
    TL1_SmartParameter< int >                   itsNumberInterval;
    TL1_SmartParameter< CT_PMA_ParamId >        itsParamId;     //itsMonitoringType
    TL1_SmartParameter< CT_PMA_MonTypeJust >    itsMonTypeJust; //itsMonitoringType
    TL1_SmartParameter< CT_PMA_DirnUpOrDn >     itsDirnUpOrDn;  //itsMonitorLevel
    TL1_SmartParameter< long long >             itsLevel;       //itsMonitorLevel
    TL1_SmartParameter< CT_NEFlag >             itsLocation;
    TL1_SmartParameter< CT_DirectionFlag >      itsDirection;
    TL1_SmartParameter< CT_PMA_Period >         itsTimePeriod;
    TL1_SmartParameter<  CT_TimeTm >            itsTimeOffset;
    TL1_SmartParameter< bool >                  itsInhibitionMode;
};    
    
typedef TL1_Rtv_Response< TL1_RtrvPmSchedRspBlk > TL1_RtrvPmSchedResponse;


//-------------------------------------------------------------------------------------------
class TL1_RtrvTcaRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvTcaRspBlk(){}

    TL1_RtrvTcaRspBlk( const TL1_RtrvTcaRspBlk& theBlock );

    TL1_RtrvTcaRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                       const TL1_SmartParameter< string >& theEntityName,
                       const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theConditionType,
                       const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theConditionType,
                       const TL1_SmartParameter< CT_TimeTm >& theOcrDatOcrTim,
                       const TL1_SmartParameter< CT_NEFlag >& theLocation,
                       const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                       const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod);

	virtual ~TL1_RtrvTcaRspBlk();

    TL1_RtrvTcaRspBlk& operator=( const TL1_RtrvTcaRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_PMA_ParamId >& //GetConditionType
        GetParamId() const
    {
        return itsParamId;
    }

    const TL1_SmartParameter< CT_PMA_MonTypeJust >& //GetConditionType
        GetMonTypeJust() const
    {
        return itsMonTypeJust;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetOcrDatOcrTim() const
    {
        return itsOcrDatOcrTim;
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

    const TL1_SmartParameter< CT_PMA_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }
   

private:
    TL1_SmartParameter< string >              itsEntityName;
    TL1_SmartParameter< CT_PMA_ParamId >      itsParamId;     //ConditionType
    TL1_SmartParameter< CT_PMA_MonTypeJust >  itsMonTypeJust; //ConditionType
    TL1_SmartParameter< CT_TimeTm >           itsOcrDatOcrTim;
    TL1_SmartParameter< CT_NEFlag >           itsLocation;
    TL1_SmartParameter< CT_DirectionFlag >    itsDirection;
    TL1_SmartParameter< CT_PMA_Period >       itsTimePeriod;
};    
    
typedef TL1_Rtv_Response< TL1_RtrvTcaRspBlk > TL1_RtrvTcaResponse;


//-------------------------------------------------------------------------------------------
class TL1_RtrvTcaModeRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvTcaModeRspBlk(){}

    TL1_RtrvTcaModeRspBlk( const TL1_RtrvTcaModeRspBlk& theBlock );

    TL1_RtrvTcaModeRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                           const TL1_SmartParameter< string >& theEntityName,
                           const TL1_SmartParameter< CT_NEFlag >& theLocation,
                           const TL1_SmartParameter< CT_TL1_ModeType >& theModeType,
                           const TL1_SmartParameter< bool >& theTcaMode );

	virtual ~TL1_RtrvTcaModeRspBlk();

    TL1_RtrvTcaModeRspBlk& operator=( const TL1_RtrvTcaModeRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_NEFlag >&
        GetLocation() const
    {
        return itsLocation;
    }

    const TL1_SmartParameter< CT_TL1_ModeType >&
        GetModeType() const
    {
        return itsModeType;
    }

    const TL1_SmartParameter< bool >&
        GetTcaMode() const
    {
        return itsTcaMode;
    }

private:
    TL1_SmartParameter< string >              itsEntityName;
    TL1_SmartParameter< CT_NEFlag >           itsLocation;
    TL1_SmartParameter< CT_TL1_ModeType >     itsModeType;
    TL1_SmartParameter< bool >                itsTcaMode;
};    
    
typedef TL1_Rtv_Response< TL1_RtrvTcaModeRspBlk > TL1_RtrvTcaModeResponse;


//-------------------------------------------------------------------------------------------
class TL1_RtrvThRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvThRspBlk(){}

    TL1_RtrvThRspBlk( const TL1_RtrvThRspBlk& theBlock );

    TL1_RtrvThRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                      const TL1_SmartParameter< string >& theEntityName,
                      const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                      const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                      const TL1_SmartParameter< CT_NEFlag >& theLocation,
                      const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                      const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                      CT_PMA_64BitGaugeThreshold * theThresholdValue,                 //theThresholdLevel,
                      const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod );

    TL1_RtrvThRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                      const TL1_SmartParameter< string >& theEntityName,
                      const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                      const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                      const TL1_SmartParameter< CT_NEFlag >& theLocation,
                      const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                      const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                      CT_PMA_GaugeThreshold * theThresholdValue,                     //theThresholdLevel,
                      const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod );

	virtual ~TL1_RtrvThRspBlk();

    TL1_RtrvThRspBlk& operator=( const TL1_RtrvThRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_PMA_ParamId >& //GetMonitoringType
        GetParamId() const
    {
        return itsParamId;
    }

    const TL1_SmartParameter< CT_PMA_MonTypeJust >& //GetMonitoringType
        GetMonTypeJust() const
    {
        return itsMonTypeJust;
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

    const TL1_SmartParameter< CT_PMA_ParamType >& //GetThresholdLevel
        GetParamType() const
    {
        return itsParamType;
    }

    CT_PMA_64BitGaugeThreshold GetThresholdValue() const //GetThresholdLevel
    {
        return itsThresholdValue;
    }

    const TL1_SmartParameter< CT_PMA_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }

private:
    TL1_SmartParameter< string >                 itsEntityName;
    TL1_SmartParameter< CT_PMA_ParamId >         itsParamId;     //itsMonitoringType
    TL1_SmartParameter< CT_PMA_MonTypeJust >     itsMonTypeJust; //itsMonitoringType
    TL1_SmartParameter< CT_NEFlag >              itsLocation;
    TL1_SmartParameter< CT_DirectionFlag >       itsDirection;
    TL1_SmartParameter< CT_PMA_ParamType >       itsParamType;      //ThresholdLevel
                        CT_PMA_64BitGaugeThreshold itsThresholdValue; //itsThresholdLevel
    TL1_SmartParameter< CT_PMA_Period >          itsTimePeriod;
};    
    
typedef TL1_Rtv_Response< TL1_RtrvThRspBlk > TL1_RtrvThResponse;


//-------------------------------------------------------------------------------------------
class TL1_RtrvPmFtpConfigRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvPmFtpConfigRspBlk(){};

    TL1_RtrvPmFtpConfigRspBlk( const TL1_RtrvPmFtpConfigRspBlk& theBlock );

    TL1_RtrvPmFtpConfigRspBlk( const TL1_SmartParameter< string >& theFtpServer,
                               const TL1_SmartParameter< string >& theUserId,
                               const TL1_SmartParameter< string >& thePasswd,
                               const TL1_SmartParameter< string >& theIpAddr,
                               CT_PM_PortId* thePortId,
                               const TL1_SmartParameter< string >& theUrlPath );
    
    virtual ~TL1_RtrvPmFtpConfigRspBlk(){};

    TL1_RtrvPmFtpConfigRspBlk& operator=( const TL1_RtrvPmFtpConfigRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetFtpServer() const
    {
        return itsFtpServer;
    }

    const TL1_SmartParameter< string >&
        GetUserId() const
    {
        return itsUserId;
    }

    const TL1_SmartParameter< string >&
        GetPasswd() const
    {
        return itsPasswd;
    }

    const TL1_SmartParameter< string >&
        GetIpAddr() const
    {
        return itsIpAddr;
    }

    const TL1_SmartParameter< string >&
        GetFtpUrl() const
    {
        return itsFtpUrl;
    }

    CT_PM_PortId GetPortId() const
    {
        return itsPortId;
    }

private:
    TL1_SmartParameter< string > itsFtpServer;
    TL1_SmartParameter< string > itsUserId;
    TL1_SmartParameter< string > itsPasswd;
    TL1_SmartParameter< string > itsIpAddr;
    TL1_SmartParameter< string > itsFtpUrl;
    CT_PM_PortId itsPortId;
};

typedef TL1_Rtv_Response< TL1_RtrvPmFtpConfigRspBlk > TL1_RtrvPmFtpConfigResponse;

//--------------------------------------------------------------------------
// Path PM profile Response
//--------------------------------------------------------------------------
class TL1_PmProfileRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_PmProfileRspBlk(){}

    TL1_PmProfileRspBlk( const TL1_PmProfileRspBlk& theBlock );

    TL1_PmProfileRspBlk( const TL1_SmartParameter< CT_EntityType >& theEntityType,
                         const TL1_SmartParameter< CT_PMProfileTableId >& theProfileId,
                         const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                         const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                         const TL1_SmartParameter< CT_NEFlag >& theLocation,
                         const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                         const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                         CT_PMA_64BitGaugeThreshold * theThresholdValue,                      //theThresholdLevel,
                         const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod);

    TL1_PmProfileRspBlk( const TL1_SmartParameter< CT_EntityType >& theEntityType,
                         const TL1_SmartParameter< CT_PMProfileTableId >& theProfileId,
                         const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
                         const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
                         const TL1_SmartParameter< CT_NEFlag >& theLocation,
                         const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                         const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                         CT_PMA_GaugeThreshold * theThresholdValue,                      //theThresholdLevel,
                         const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod);

    virtual ~TL1_PmProfileRspBlk();

    TL1_PmProfileRspBlk& operator=( const TL1_PmProfileRspBlk& theBlock );

    const TL1_SmartParameter< CT_EntityType >&
        GetEntityType() const
    {
        return itsEntityType;
    }

    const TL1_SmartParameter< CT_PMProfileTableId >&
        GetProfileId() const
    {
        return itsProfileId;
    }

    const TL1_SmartParameter< CT_PMA_ParamId >& //GetMonitoringType
        GetParamId() const
    {
        return itsParamId;
    }

    const TL1_SmartParameter< CT_PMA_MonTypeJust >& //GetMonitoringType
        GetMonTypeJust() const
    {
        return itsMonTypeJust;
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

    const TL1_SmartParameter< CT_PMA_ParamType >& //GetThresholdLevel
        GetParamType() const
    {
        return itsParamType;
    }

    CT_PMA_64BitGaugeThreshold GetThresholdValue() const //GetThresholdLevel
    {
        return itsThresholdValue;
    }

    const TL1_SmartParameter< CT_PMA_Period >&
        GetTimePeriod() const
    {
        return itsTimePeriod;
    }

private:
    TL1_SmartParameter< CT_EntityType >          itsEntityType;
    TL1_SmartParameter< CT_PMProfileTableId >      itsProfileId;
    TL1_SmartParameter< CT_PMA_ParamId >         itsParamId;     //itsMonitoringType
    TL1_SmartParameter< CT_PMA_MonTypeJust >     itsMonTypeJust; //itsMonitoringType
    TL1_SmartParameter< CT_NEFlag >              itsLocation;
    TL1_SmartParameter< CT_DirectionFlag >       itsDirection;
    TL1_SmartParameter< CT_PMA_ParamType >       itsParamType;      //ThresholdLevel
                        CT_PMA_64BitGaugeThreshold itsThresholdValue; //itsThresholdLevel
    TL1_SmartParameter< CT_PMA_Period >          itsTimePeriod;
};


typedef TL1_Rtv_Response< TL1_PmProfileRspBlk > TL1_PmProfileResponse;

//--------------------------------------------------------------------------
// Path PMPFUSE Response
//--------------------------------------------------------------------------

class TL1_PmPfUseRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_PmPfUseRspBlk(){}

    TL1_PmPfUseRspBlk( const TL1_PmPfUseRspBlk& theBlock );

    TL1_PmPfUseRspBlk( const TL1_SmartParameter< CT_EntityType >& theEntityType,
                         const TL1_SmartParameter< CT_PMProfileTableId >& theProfileId,
                         const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
                         const TL1_SmartParameter< CT_Yes_No >& theInUse);

    virtual ~TL1_PmPfUseRspBlk();

    TL1_PmPfUseRspBlk& operator=( const TL1_PmPfUseRspBlk& theBlock );

    const TL1_SmartParameter< CT_EntityType >&
        GetEntityType() const
    {
        return itsEntityType;
    }

    const TL1_SmartParameter< CT_PMProfileTableId >&
        GetProfileId() const
    {
        return itsProfileId;
    }

    const TL1_SmartParameter< CT_DirectionFlag >&
        GetDirection() const
    {
        return itsDirection;
    }

    const TL1_SmartParameter< CT_Yes_No >&
        GetInUse() const
    {
        return itsInUse;
    }

private:
    TL1_SmartParameter< CT_EntityType >          itsEntityType;
    TL1_SmartParameter< CT_PMProfileTableId >      itsProfileId;
    TL1_SmartParameter< CT_DirectionFlag >       itsDirection;
    TL1_SmartParameter< CT_Yes_No >       itsInUse;
};

typedef TL1_Rtv_Response< TL1_PmPfUseRspBlk > TL1_PmPfUseResponse;



//-------------------------------------------------------------------------------------------
class TL1_RtrvStatsRspBlk : public TL1_GeneralPmRspBlk
{
public:
    TL1_RtrvStatsRspBlk(){}

    TL1_RtrvStatsRspBlk( const TL1_RtrvStatsRspBlk& theBlock );

    TL1_RtrvStatsRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                            const TL1_SmartParameter< string >& theEntityName,
                            const TL1_SmartParameter< uint8 >&  theStatType,
                            const TL1_SmartParameter< uint8 >&  theParamId,
                            const TL1_SmartParameter< int >& theIntValue,
                            const TL1_SmartParameter< string >& theStringValue );

	virtual ~TL1_RtrvStatsRspBlk();

    TL1_RtrvStatsRspBlk& operator=( const TL1_RtrvStatsRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< uint8 >& 
        GetStatType() const
    {
        return itsStatType;
    }

    const TL1_SmartParameter< uint8 >& 
        GetParamId() const
    {
        return itsParamId;
    }

    const TL1_SmartParameter< int >& 
        GetIntValue() const
    {
        return itsIntValue;
    } 

    const TL1_SmartParameter< string >& 
        GetStringValue() const
    {
        return itsStringValue;
    }   

private:
    TL1_SmartParameter< string >            itsEntityName;
    TL1_SmartParameter< uint8 >             itsStatType; 
    TL1_SmartParameter< uint8 >             itsParamId;  
    TL1_SmartParameter< int >               itsIntValue;  
    TL1_SmartParameter< string >            itsStringValue;  
};
    
typedef TL1_Rtv_Response< TL1_RtrvStatsRspBlk > TL1_RtrvStatsResponse;


#endif  // #ifndef __TL1_PMRSPBLK_H_
