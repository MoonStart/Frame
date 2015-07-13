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


#include "../TL1_PmRspBlk.h"

using namespace std;

//-------------------------------------------------------------------------------------------
TL1_GeneralPmRspBlk::TL1_GeneralPmRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr)
{
    const CT_TL1_FacAddr* aFacAddr =
        dynamic_cast<const CT_TL1_FacAddr*>( theEntityAddr.GetValue() );

    if (aFacAddr)
    {
        itsFacAddr = *aFacAddr;
    }
    else
    {
        const CT_TL1_SlotAddr* aSlotAddr =
            dynamic_cast<const CT_TL1_SlotAddr*>( theEntityAddr.GetValue() );

        if (aSlotAddr)
        {
            itsSlotAddr = *aSlotAddr;
        }
        else
        {
            const CT_TL1_LogicalAddr* aLogicalAddr =
                dynamic_cast<const CT_TL1_LogicalAddr*>( theEntityAddr.GetValue() );

            if (aLogicalAddr)
            {
                itsLogicalAddr = *aLogicalAddr;
            }
            else
            {
                FC_THROW_ERROR( FC_RuntimeError,
                    "Wrong entity address type in TL1_GeneralPmRspBlk" );
            }
        }
    }
}

TL1_GeneralPmRspBlk::~TL1_GeneralPmRspBlk()
{
}

TL1_GeneralPmRspBlk::TL1_GeneralPmRspBlk( const TL1_GeneralPmRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_GeneralPmRspBlk& TL1_GeneralPmRspBlk::operator=( const TL1_GeneralPmRspBlk& theBlock )
{
    itsSlotAddr = theBlock.itsSlotAddr;
    itsFacAddr = theBlock.itsFacAddr;
    itsLogicalAddr = theBlock.itsLogicalAddr;

    return *this;
}


//-------------------------------------------------------------------------------------------
TL1_ReptEvtTcaRspBlk::TL1_ReptEvtTcaRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
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
        const TL1_SmartParameter< string >& theDescription ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsConditionEffect( theConditionEffect ),
    itsOcrDatOcrTim( theOcrDatOcrTim ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsParamType( theParamType ),
    itsValue( theValue ),
    itsThresholdValue( theThresholdValue ),
    itsTimePeriod( theTimePeriod ),
    itsDescription( theDescription )
{
}

TL1_ReptEvtTcaRspBlk::TL1_ReptEvtTcaRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
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
        const TL1_SmartParameter< string >& theDescription ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsConditionEffect( theConditionEffect ),
    itsOcrDatOcrTim( theOcrDatOcrTim ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsParamType( theParamType ),
    itsTimePeriod( theTimePeriod ),
    itsDescription( theDescription )
{
    CT_PMA_64BitTcaValue a64BitTcaValue; 
    CT_PMA_64BitTcaValue a64BitThresholdValue;

    if ( itsParamType == PMA_GAUGE_TYPE )
    {
        a64BitTcaValue.signed_int       = static_cast<long long>(theValue.GetValue().signed_int);
        a64BitThresholdValue.signed_int = static_cast<long long>(theThresholdValue.GetValue().signed_int);
    }
    else // PMA_COUNTER_TYPE
    {
        a64BitTcaValue.unsigned_int       = static_cast<unsigned long long>(theValue.GetValue().unsigned_int);
        a64BitThresholdValue.unsigned_int = static_cast<unsigned long long>(theThresholdValue.GetValue().unsigned_int);
    }

    itsValue          = a64BitTcaValue;
    itsThresholdValue = a64BitThresholdValue;
}

TL1_ReptEvtTcaRspBlk::~TL1_ReptEvtTcaRspBlk()
{
}

TL1_ReptEvtTcaRspBlk::TL1_ReptEvtTcaRspBlk( const TL1_ReptEvtTcaRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_ReptEvtTcaRspBlk& TL1_ReptEvtTcaRspBlk::operator=( const TL1_ReptEvtTcaRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsParamId = theBlock.itsParamId;
    itsMonTypeJust = theBlock.itsMonTypeJust;
	itsConditionEffect = theBlock.itsConditionEffect;
	itsOcrDatOcrTim = theBlock.itsOcrDatOcrTim;
	itsLocation = theBlock.itsLocation;
	itsDirection = theBlock.itsDirection;    
    itsParamType = theBlock.itsParamType;
    itsValue = theBlock.itsValue;
    itsThresholdValue = theBlock.itsThresholdValue;
	itsTimePeriod = theBlock.itsTimePeriod;
	itsDescription = theBlock.itsDescription;

    return *this;
}


//-------------------------------------------------------------------------------------------
TL1_RtrvPmRspBlk::TL1_RtrvPmRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_ParamType >& theParamType, //theMonitorValue,
                                  CT_PMA_64BitGaugeInt* theValue,        //theMonitorValue,
        const TL1_SmartParameter< CT_PMA_Validity >& theValidity,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
        const TL1_SmartParameter< CT_TimeTm >& theMonDatMonTim ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsParamType( theParamType ),
    itsValidity( theValidity ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsTimePeriod( theTimePeriod ),
    itsMonDatMonTim( theMonDatMonTim )
{
    itsValue = (*(dynamic_cast<CT_PMA_64BitGaugeInt *>(theValue)));
}

//-------------------------------------------------------------------------------------------
TL1_RtrvPmRspBlk::TL1_RtrvPmRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_ParamType >& theParamType, //theMonitorValue,
                                  CT_PMA_GaugeInt* theValue,        //theMonitorValue,
        const TL1_SmartParameter< CT_PMA_Validity >& theValidity,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
        const TL1_SmartParameter< CT_TimeTm >& theMonDatMonTim ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsParamType( theParamType ),
    itsValidity( theValidity ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsTimePeriod( theTimePeriod ),
    itsMonDatMonTim( theMonDatMonTim )
{
    CT_PMA_GaugeInt a32GaugeInt = (*(dynamic_cast<CT_PMA_GaugeInt *>(theValue)));

    //We must compare type to accurate cast the 32-bit signed/unsigned into the appropriate 64-bit signed/unsigned.
    switch(itsParamType.GetValue())
    {
        case PMA_GAUGE_TYPE:
            itsValue.value.gauge = static_cast<long long>(a32GaugeInt.value.gauge);
            break;
        case PMA_COUNTER_TYPE:
        default:
            itsValue.value.counter = static_cast<unsigned long long>(a32GaugeInt.value.counter);
            break;
    }

    itsValue.maximumValue = a32GaugeInt.maximumValue;
    itsValue.minimumValue = a32GaugeInt.minimumValue;
}

TL1_RtrvPmRspBlk::~TL1_RtrvPmRspBlk()
{
}

TL1_RtrvPmRspBlk::TL1_RtrvPmRspBlk( const TL1_RtrvPmRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvPmRspBlk& TL1_RtrvPmRspBlk::operator=( const TL1_RtrvPmRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsParamId = theBlock.itsParamId;
    itsMonTypeJust = theBlock.itsMonTypeJust;
    itsParamType = theBlock.itsParamType;
    itsValue = theBlock.itsValue;
    itsValidity = theBlock.itsValidity;
    itsLocation = theBlock.itsLocation;
    itsDirection = theBlock.itsDirection;
    itsTimePeriod = theBlock.itsTimePeriod;
    itsMonDatMonTim = theBlock.itsMonDatMonTim;

    return *this;
}


//-------------------------------------------------------------------------------------------
TL1_RtrvPmDayRspBlk::TL1_RtrvPmDayRspBlk( 
        const TL1_SmartParameter< CT_TimeTm >& thePmDayStart ) :
    itsPmDayStart( thePmDayStart )
{
}

TL1_RtrvPmDayRspBlk::~TL1_RtrvPmDayRspBlk()
{
}

TL1_RtrvPmDayRspBlk::TL1_RtrvPmDayRspBlk( const TL1_RtrvPmDayRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvPmDayRspBlk& TL1_RtrvPmDayRspBlk::operator=( const TL1_RtrvPmDayRspBlk& theBlock )
{
    itsPmDayStart = theBlock.itsPmDayStart;

    return *this;
}


//-------------------------------------------------------------------------------------------
TL1_RtrvPmModeRspBlk::TL1_RtrvPmModeRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_TL1_ModeType >& theModeType,
        const TL1_SmartParameter< bool >& thePmState) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsLocation( theLocation ),
    itsModeType( theModeType ),
    itsPmState( thePmState )
{
}

TL1_RtrvPmModeRspBlk::~TL1_RtrvPmModeRspBlk()
{
}

TL1_RtrvPmModeRspBlk::TL1_RtrvPmModeRspBlk( const TL1_RtrvPmModeRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvPmModeRspBlk& TL1_RtrvPmModeRspBlk::operator=( const TL1_RtrvPmModeRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsLocation = theBlock.itsLocation;
    itsModeType = theBlock.itsModeType;
    itsPmState = theBlock.itsPmState;

    return *this;
}
//-------------------------------------------------------------------------------------------
TL1_RtrvPmFileSchedRspBlk::TL1_RtrvPmFileSchedRspBlk( const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
                                                      const TL1_SmartParameter< string >& theEntityName,
                                                      const TL1_SmartParameter< string >& theFtpServer,
                                                      const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod,
						      const TL1_SmartParameter< bool >& theInhibitionMode ):
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsFtpServer( theFtpServer ),
    itsTimePeriod( theTimePeriod ),
    itsInhibitionMode( theInhibitionMode )  
{
}

TL1_RtrvPmFileSchedRspBlk::TL1_RtrvPmFileSchedRspBlk( const TL1_RtrvPmFileSchedRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsFtpServer = theBlock.itsFtpServer;
    itsTimePeriod = theBlock.itsTimePeriod;
    itsInhibitionMode = theBlock.itsInhibitionMode;
}

TL1_RtrvPmFileSchedRspBlk& TL1_RtrvPmFileSchedRspBlk::operator=( const TL1_RtrvPmFileSchedRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsFtpServer = theBlock.itsFtpServer;
    itsTimePeriod = theBlock.itsTimePeriod;
    itsInhibitionMode = theBlock.itsInhibitionMode;

    return *this;
}

//-------------------------------------------------------------------------------------------
TL1_RtrvPmSchedRspBlk::TL1_RtrvPmSchedRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
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
        const TL1_SmartParameter< bool >& theInhibitionMode ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsReportInterval( theReportInterval ),
    itsDateAndTime( theDateAndTime ),
    itsNumberInterval( theNumberInterval ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsDirnUpOrDn( theDirnUpOrDn ),
    itsLevel( theLevel ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsTimePeriod( theTimePeriod ),
    itsTimeOffset( theTimeOffset ),
    itsInhibitionMode( theInhibitionMode )
{
}

TL1_RtrvPmSchedRspBlk::TL1_RtrvPmSchedRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
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
        const TL1_SmartParameter< bool >& theInhibitionMode ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsReportInterval( theReportInterval ),
    itsDateAndTime( theDateAndTime ),
    itsNumberInterval( theNumberInterval ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsDirnUpOrDn( theDirnUpOrDn ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsTimePeriod( theTimePeriod ),
    itsTimeOffset( theTimeOffset ),
    itsInhibitionMode( theInhibitionMode )
{
    if (theLevel.IsPresent())
    {
        TL1_SmartParameter<long long> aLevel(static_cast<long long>(theLevel.GetValue()));
        itsLevel = aLevel;
    }
    else
    {
        TL1_SmartParameter<long long> aLevel;
        itsLevel = aLevel;
    }
}

TL1_RtrvPmSchedRspBlk::~TL1_RtrvPmSchedRspBlk()
{
}

TL1_RtrvPmSchedRspBlk::TL1_RtrvPmSchedRspBlk( const TL1_RtrvPmSchedRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvPmSchedRspBlk& TL1_RtrvPmSchedRspBlk::operator=( const TL1_RtrvPmSchedRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsReportInterval = theBlock.itsReportInterval;
    itsDateAndTime = theBlock.itsDateAndTime;
    itsNumberInterval = theBlock.itsNumberInterval;
    itsParamId = theBlock.itsParamId;
    itsMonTypeJust = theBlock.itsMonTypeJust;
    itsDirnUpOrDn = theBlock.itsDirnUpOrDn;
    itsLevel = theBlock.itsLevel;
	itsLocation = theBlock.itsLocation;
	itsDirection = theBlock.itsDirection;    
	itsTimePeriod = theBlock.itsTimePeriod;
   itsTimeOffset = theBlock.itsTimeOffset;
	itsInhibitionMode = theBlock.itsInhibitionMode;

    return *this;
}


//-------------------------------------------------------------------------------------------
TL1_RtrvTcaRspBlk::TL1_RtrvTcaRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //ConditionType,
        const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //ConditionType,
        const TL1_SmartParameter< CT_TimeTm >& theOcrDatOcrTim,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsOcrDatOcrTim( theOcrDatOcrTim ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsTimePeriod( theTimePeriod )
{
}

TL1_RtrvTcaRspBlk::~TL1_RtrvTcaRspBlk()
{
}

TL1_RtrvTcaRspBlk::TL1_RtrvTcaRspBlk( const TL1_RtrvTcaRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvTcaRspBlk& TL1_RtrvTcaRspBlk::operator=( const TL1_RtrvTcaRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsParamId = theBlock.itsParamId;
    itsMonTypeJust = theBlock.itsMonTypeJust;
    itsOcrDatOcrTim = theBlock.itsOcrDatOcrTim;
    itsLocation = theBlock.itsLocation;
    itsDirection = theBlock.itsDirection;
    itsTimePeriod = theBlock.itsTimePeriod;

    return *this;
}

//-------------------------------------------------------------------------------------------
TL1_RtrvTcaModeRspBlk::TL1_RtrvTcaModeRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_TL1_ModeType >& theModeType,
        const TL1_SmartParameter< bool >& theTcaMode ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsLocation( theLocation ),
    itsModeType( theModeType ),
    itsTcaMode( theTcaMode )    
{
}

TL1_RtrvTcaModeRspBlk::~TL1_RtrvTcaModeRspBlk()
{
}

TL1_RtrvTcaModeRspBlk::TL1_RtrvTcaModeRspBlk( const TL1_RtrvTcaModeRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvTcaModeRspBlk& TL1_RtrvTcaModeRspBlk::operator=( const TL1_RtrvTcaModeRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsLocation = theBlock.itsLocation;
    itsModeType = theBlock.itsModeType;
    itsTcaMode = theBlock.itsTcaMode;

    return *this;
}

//-------------------------------------------------------------------------------------------
TL1_RtrvThRspBlk::TL1_RtrvThRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                                  CT_PMA_64BitGaugeThreshold* theThresholdValue, //theThresholdLevel,
        const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsParamType( theParamType ),
    itsTimePeriod( theTimePeriod )
{
    itsThresholdValue = (*(dynamic_cast<CT_PMA_64BitGaugeThreshold *>(theThresholdValue)));
}

//-------------------------------------------------------------------------------------------
TL1_RtrvThRspBlk::TL1_RtrvThRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                                  CT_PMA_GaugeThreshold* theThresholdValue, //theThresholdLevel,
        const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod ) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsParamType( theParamType ),
    itsTimePeriod( theTimePeriod )
{
    CT_PMA_GaugeThreshold aTemp32BitGaugeThreshold = (*(dynamic_cast<CT_PMA_GaugeThreshold *>(theThresholdValue)));
    itsThresholdValue = aTemp32BitGaugeThreshold;
}
TL1_RtrvThRspBlk::~TL1_RtrvThRspBlk()
{
}

TL1_RtrvThRspBlk::TL1_RtrvThRspBlk( const TL1_RtrvThRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvThRspBlk& TL1_RtrvThRspBlk::operator=( const TL1_RtrvThRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsParamId = theBlock.itsParamId;
    itsMonTypeJust = theBlock.itsMonTypeJust;
    itsLocation = theBlock.itsLocation;
    itsDirection = theBlock.itsDirection;
    itsParamType = theBlock.itsParamType;
    itsThresholdValue = theBlock.itsThresholdValue;
    itsTimePeriod = theBlock.itsTimePeriod;

    return *this;
}

//-------------------------------------------------------------------------------------------
TL1_RtrvPmFtpConfigRspBlk::TL1_RtrvPmFtpConfigRspBlk( const TL1_SmartParameter< string >& theFtpServer,
                                                      const TL1_SmartParameter< string >& theUserId,
                                                      const TL1_SmartParameter< string >& thePasswd,
                                                      const TL1_SmartParameter< string >& theIpAddr,
                                                      CT_PM_PortId* thePortId,
                                                      const TL1_SmartParameter< string >& theFtpUrl) :
    itsFtpServer( theFtpServer ),
    itsUserId( theUserId ),
    itsPasswd( thePasswd ),
    itsIpAddr( theIpAddr ),
    itsFtpUrl( theFtpUrl ),
    itsPortId(0)
{
    if(thePortId)
        itsPortId = *thePortId;
}

TL1_RtrvPmFtpConfigRspBlk::TL1_RtrvPmFtpConfigRspBlk( const TL1_RtrvPmFtpConfigRspBlk& theBlock )
{
    // Let's call base class assignment operator
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsFtpServer = theBlock.itsFtpServer;
    itsUserId = theBlock.itsUserId;
    itsPasswd = theBlock.itsPasswd;
    itsIpAddr = theBlock.itsIpAddr;
    itsFtpUrl = theBlock.itsFtpUrl;
    itsPortId = theBlock.itsPortId;
}

TL1_RtrvPmFtpConfigRspBlk& TL1_RtrvPmFtpConfigRspBlk::operator=( const TL1_RtrvPmFtpConfigRspBlk& theBlock )
{
    itsFtpServer = theBlock.itsFtpServer;
    itsUserId = theBlock.itsUserId;
    itsPasswd = theBlock.itsPasswd;
    itsIpAddr = theBlock.itsIpAddr;
    itsFtpUrl = theBlock.itsFtpUrl;
    itsPortId = theBlock.itsPortId;

    return *this;
}

//------------------------------------------------------------------------------------------
// Path PM profile response
//------------------------------------------------------------------------------------------
TL1_PmProfileRspBlk::TL1_PmProfileRspBlk(
        const TL1_SmartParameter< CT_EntityType >& theEntityType,
        const TL1_SmartParameter< CT_PMProfileTableId >& theProfileId,
        const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                                  CT_PMA_64BitGaugeThreshold* theThresholdValue, //theThresholdLevel,
        const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod ) :

    itsEntityType( theEntityType ),
    itsProfileId( theProfileId ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsParamType( theParamType ),
    itsTimePeriod( theTimePeriod )
{
    itsThresholdValue = (*(dynamic_cast<CT_PMA_64BitGaugeThreshold *>(theThresholdValue)));
}

TL1_PmProfileRspBlk::TL1_PmProfileRspBlk(
        const TL1_SmartParameter< CT_EntityType >& theEntityType,
        const TL1_SmartParameter< CT_PMProfileTableId >& theProfileId,
        const TL1_SmartParameter< CT_PMA_ParamId >&  theParamId,        //theMonitoringType,
        const TL1_SmartParameter< CT_PMA_MonTypeJust >& theMonTypeJust, //theMonitoringType,
        const TL1_SmartParameter< CT_NEFlag >& theLocation,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_PMA_ParamType >& theParamType,     //ThresholdLevel,
                                  CT_PMA_GaugeThreshold* theThresholdValue, //theThresholdLevel,
        const TL1_SmartParameter< CT_PMA_Period >& theTimePeriod ) :

    itsEntityType( theEntityType ),
    itsProfileId( theProfileId ),
    itsParamId( theParamId ),
    itsMonTypeJust( theMonTypeJust ),
    itsLocation( theLocation ),
    itsDirection( theDirection ),
    itsParamType( theParamType ),
    itsTimePeriod( theTimePeriod )
{
    CT_PMA_GaugeThreshold a32BitThresholdValue = (*(dynamic_cast<CT_PMA_GaugeThreshold *>(theThresholdValue)));
    itsThresholdValue = a32BitThresholdValue;
}

TL1_PmProfileRspBlk::~TL1_PmProfileRspBlk()
{
}

TL1_PmProfileRspBlk::TL1_PmProfileRspBlk( const TL1_PmProfileRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_PmProfileRspBlk& TL1_PmProfileRspBlk::operator=( const TL1_PmProfileRspBlk& theBlock )
{
    itsEntityType = theBlock.itsEntityType;
    itsProfileId = theBlock.itsProfileId;
    itsParamId = theBlock.itsParamId;
    itsMonTypeJust = theBlock.itsMonTypeJust;
    itsLocation = theBlock.itsLocation;
    itsDirection = theBlock.itsDirection;
    itsParamType = theBlock.itsParamType;
    itsThresholdValue = theBlock.itsThresholdValue;
    itsTimePeriod = theBlock.itsTimePeriod;
    return *this;
}

//------------------------------------------------------------------------------------------
// PMPFUSE response
//------------------------------------------------------------------------------------------
TL1_PmPfUseRspBlk::TL1_PmPfUseRspBlk(
        const TL1_SmartParameter< CT_EntityType >& theEntityType,
        const TL1_SmartParameter< CT_PMProfileTableId >& theProfileId,
        const TL1_SmartParameter< CT_DirectionFlag >& theDirection,
        const TL1_SmartParameter< CT_Yes_No>& theInUse ) :

    itsEntityType( theEntityType ),
    itsProfileId( theProfileId ),
    itsDirection( theDirection ),
    itsInUse(theInUse)
{
}

TL1_PmPfUseRspBlk::~TL1_PmPfUseRspBlk()
{
}

TL1_PmPfUseRspBlk::TL1_PmPfUseRspBlk( const TL1_PmPfUseRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_PmPfUseRspBlk& TL1_PmPfUseRspBlk::operator=( const TL1_PmPfUseRspBlk& theBlock )
{
    itsEntityType = theBlock.itsEntityType;
    itsProfileId = theBlock.itsProfileId;
    itsDirection = theBlock.itsDirection;
    itsInUse = theBlock.itsInUse;
    return *this;
}

//-------------------------------------------------------------------------------------------
TL1_RtrvStatsRspBlk::TL1_RtrvStatsRspBlk(
        const TL1_SmartParameter< const CT_TL1_EntityAddr* >& theEntityAddr,
        const TL1_SmartParameter< string >& theEntityName,
        const TL1_SmartParameter< uint8 >&  theStatType,       
        const TL1_SmartParameter< uint8 >&  theParamId,
        const TL1_SmartParameter< int >&  theIntValue,
        const TL1_SmartParameter< string >&  theStringValue) :
    TL1_GeneralPmRspBlk( theEntityAddr ),
    itsEntityName( theEntityName ),
    itsStatType(theStatType),
    itsParamId(theParamId),
    itsIntValue(theIntValue),
    itsStringValue(theStringValue) 
{
}

TL1_RtrvStatsRspBlk::~TL1_RtrvStatsRspBlk()
{
}

TL1_RtrvStatsRspBlk::TL1_RtrvStatsRspBlk( const TL1_RtrvStatsRspBlk& theBlock )
{
    (*this) = theBlock;
}

TL1_RtrvStatsRspBlk& TL1_RtrvStatsRspBlk::operator=( const TL1_RtrvStatsRspBlk& theBlock )
{
    (static_cast<TL1_GeneralPmRspBlk&>(*this)) = theBlock;
    itsEntityName = theBlock.itsEntityName;
    itsStatType = theBlock.itsStatType;
    itsParamId = theBlock.itsParamId;   
    itsIntValue = theBlock.itsIntValue;
    itsStringValue = theBlock.itsStringValue;

    return *this;
}


