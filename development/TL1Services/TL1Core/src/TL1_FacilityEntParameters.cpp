/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 16, 2005 - Thomas J. Novak
DESCRIPTION:    Implementation file for TL1 ETN Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FACILITYENTPARAMETERS_H__
#include <TL1Core/TL1_FacilityEntParameters.h>
#endif

#ifndef __FAC_TRNPORTGENMONBEH_H__
#include <TL1Facility/T7100_TL1FacilityEntity.h>
#endif

#ifndef __T7100_TL1AGENTUTILITY_H__
#include <TL1Core/T7100_TL1AgentUtility.h>
#endif

TL1_FacilityEntParameters::TL1_FacilityEntParameters()
{
    myAlarmProfile=             (CT_ProfileTableId*)0;
    myTrace=                    (CT_Fac_TraceString*)0;
    myExpectedTrace=            (CT_Fac_TraceString*)0;
    myIsMonitorTraceEnabled=    (bool*)0;
    myIsInsertAisEnabled=       (bool*)0;
    myMapping=                  (CT_TEL_HopSpeMapping*)0;
    mySFThreshold=              (CT_TEL_BERLevels*)0;
    mySDThreshold=              (CT_TEL_BERLevels*)0;
    myExternalConectivity=      (CT_FAC_ExternalConnectivity*)0;
    myIsProtectionEnabled=      (CT_FAC_Protection*)0;
    myMaintProp=                (CT_FAC_MaintProp*)0;
    myIsAdaptiveEnabled=        (bool*)0;
    myMaxRate=                  (CT_TEL_daHz*)0;
    myExpectedSignalRate=       (CT_TL1_ExpectedRateRange*)0;
    myRateList=                 (CT_FAC_SignalRateListType*)0;
    mySignalType=               (CT_TEL_SignalType*)0;
    myStsMap=                   (CT_FAC_StsMap*)0;
    myPrimaryState=             (CT_SM_PST*)0;
    myLineCode=                 (CT_FAC_LineCode*)0;
    mySignalFrameFormat=        (CT_FAC_FrameFormat*)0;
    myIsTransparent=            (bool*)0;
    myIsSsmConnected=           (bool*)0;
    myConectedTo=               (CT_Fac_ConnectedToString*)0;
    myGbeFramingMode=           (CT_TEL_GbeFramingMode*)0;
    myGenTrc=                   (bool*)0;
    myIsTrafficEnabled=         (bool*)0;
    myGfpMap=                   (CT_TEL_GfpFramingMode*)0;
    myNendALS=                  (bool*)0;
    myHgeMap=                   (CT_TEL_Map_ENUM*)0;
    myNValue =                  (CT_FAC_NValue*)0;
    myFecType=                  (CT_TEL_FecType*)0;     
    myOtuExpTrc=                (CT_Fac_TraceString*)0;
    myOtuTrc=                   (CT_Fac_TraceString*)0; 
    myTransMap=                 (CT_TEL_SignalType*)0;
    myClkType=                  (CT_TEL_SignalType*)0;
    myTapNumber=                (CT_TapNumber*)0;
    myIsAutoNegotiationEnabled= (bool*)0;
    myOeoRegen=                 (CT_TEL_OEO_REGEN_MODE*)0;
    myCnvTermType=              (CT_TEL_TermSize*)0;
    myPt=                      (CT_TEL_PayloadSignalId*)0;
    myGfpUpi=                   (CT_TEL_GfpUpiId*)0;
    myEthRate=                  (CT_TEL_daHz*)0;
    myDuplexMode=               (CT_TEL_MAC_DUPLEX_MODE*)0;
    myTcmMode=                  (CT_TCM_Mode*)0;
    myFlowAd=                   (CT_TEL_MAC_ADFLW_CTRL*)0;
    myFlowCtrl=                 (CT_TEL_MAC_FLOWCTRL*)0;
    myVlanTag=                  (CT_TEL_VlanTag*)0;
    myTagMode=                  (bool*)0;
    myTpid=                     (CT_TEL_Tpid*)0;
    myDiscardPause=             (bool*)0;
    myPropFefi=                 (bool*)0;
    myHandle=                   (LT_Handle*)0;             
    myCtag=                     (LT_Ctag)0;
    myPmProfile=                (CT_PMProfileTableId*)0;
    myCFProfile=                (int*)0;
    myCbrMap=                   (CT_TEL_PayloadType*)0;
    myGfpMux=                   (CT_TEL_GFP_MUX*)0;
    myAdjacent=                 (CT_TCM_ADJACENT*)0;
    myTribSlot=                 (CT_FAC_OduTsMap *)0;
    myTribFall=                 (bool*)0;
    myDmSource=                 (bool*)0;
    myOpuConfig=                (CT_TEL_OPU_FORMAT*)0;
	myLtcActMode=               (bool*)0;
    myGfpTs=                    (uint8*)0;
    myInterPacketGap=           (uint8*)0;
    myTimDef=                   (CT_TEL_TimCriteriaMode*)0;
    myExpDapi=                  (CT_Fac_TraceString*)0;
    myExpSapi=                  (CT_Fac_TraceString*)0;
    myTxDapi=                   (CT_Fac_TraceString*)0;
    myTxSapi=                   (CT_Fac_TraceString*)0;    
    myExtChannel=               (uint32*)0;
    myOTIDStatus=               (CT_TEL_OTIDStatus*)0;
    myHoldOffProt=              (int*)0;
    myLacpPriority=             (int*)0;
    myLacpParticipation=        (CT_TEL_LacpPartiMode*)0;
    myAisType=                  (CT_RS_IndicationType*)0;
    myTribSize =                (CT_TEL_TS_SIZE*)0;
    myBurstyBerSdInterval=      (uint16*)0;
    myBurstyBerSdThreshold=     (uint32*)0;
    myQualityLevel=             (CT_FAC_QualityLevelOverride*)0;
    myIsAutoAdjustAttenuationEnabled= (bool*)0;
    myExpOperator=              (CT_Fac_TraceString*)0;
    myTxOperator=               (CT_Fac_TraceString*)0;
    myOTNMap =                  (bool *)0;
    myMapMode =                 (CT_TEL_PayloadType*)0;
    myQua =                     (bool *)0;
    myPluggableReach=           (CT_FAC_PluggableReach*)0;
}



TL1_FacilityEntParameters::~TL1_FacilityEntParameters()
{
}

TL1_FacilityEntParameters& 
TL1_FacilityEntParameters::operator=( const TL1_FacilityEntParameters& theBlock )
{
    myAlarmProfile=             theBlock.myAlarmProfile;
    myTrace=                    theBlock.myTrace;
    myExpectedTrace=            theBlock.myExpectedTrace;
    myIsMonitorTraceEnabled=    theBlock.myIsMonitorTraceEnabled;
    myIsInsertAisEnabled=       theBlock.myIsInsertAisEnabled;
    myMapping=                  theBlock.myMapping;
    mySFThreshold=              theBlock.mySFThreshold;
    mySDThreshold=              theBlock.mySDThreshold;
    myExternalConectivity=      theBlock.myExternalConectivity;
    myIsProtectionEnabled=      theBlock.myIsProtectionEnabled;
    myMaintProp=                theBlock.myMaintProp;
    myIsAdaptiveEnabled=        theBlock.myIsAdaptiveEnabled;
    myMaxRate=                  theBlock.myMaxRate;
    myExpectedSignalRate=       theBlock.myExpectedSignalRate;
    myRateList=                 theBlock.myRateList;
    mySignalType=               theBlock.mySignalType;
    myStsMap=                   theBlock.myStsMap;
    myPrimaryState=             theBlock.myPrimaryState;
    myLineCode=                 theBlock.myLineCode;
    mySignalFrameFormat=        theBlock.mySignalFrameFormat;
    myIsTransparent=            theBlock.myIsTransparent;
    myIsSsmConnected=           theBlock.myIsSsmConnected;
    myConectedTo=               theBlock.myConectedTo;
    myGbeFramingMode=           theBlock.myGbeFramingMode;
    myGenTrc=                   theBlock.myGenTrc;
    myIsTrafficEnabled=         theBlock.myIsTrafficEnabled;
    myGfpMap=                   theBlock.myGfpMap;
    myNendALS=                  theBlock.myNendALS;
    myHgeMap=                   theBlock.myHgeMap;
    myNValue=                   theBlock.myNValue;
    myFecType=                  theBlock.myFecType;     
    myOtuExpTrc=                theBlock.myOtuExpTrc;
    myOtuTrc=                   theBlock.myOtuTrc; 
    myTransMap=                 theBlock.myTransMap;
    myClkType=                  theBlock.myClkType;
    myTapNumber=                theBlock.myTapNumber;
    myIsAutoNegotiationEnabled= theBlock.myIsAutoNegotiationEnabled;
    myOeoRegen=                 theBlock.myOeoRegen;
    myCnvTermType=              theBlock.myCnvTermType;
    myPt=                       theBlock.myPt;
    myGfpUpi=                   theBlock.myGfpUpi;
    myEthRate=                  theBlock.myEthRate;
    myDuplexMode=               theBlock.myDuplexMode;
    myTcmMode=                  theBlock.myTcmMode;
    myFlowAd=                   theBlock.myFlowAd;
    myFlowCtrl=                 theBlock.myFlowCtrl;
    myVlanTag=                  theBlock.myVlanTag;
    myTagMode=                  theBlock.myTagMode;
    myTpid=                     theBlock.myTpid;
    myDiscardPause=             theBlock.myDiscardPause;
    myPropFefi=                 theBlock.myPropFefi;
    myHandle=                   theBlock.myHandle;             
    myCtag=                     theBlock.myCtag;
    myPmProfile=                theBlock.myPmProfile;
    myCFProfile=                theBlock.myCFProfile;
    myCbrMap=                   theBlock.myCbrMap;
    myGfpMux=                   theBlock.myGfpMux;
    myAdjacent=                 theBlock.myAdjacent;
    myTribSlot=                 theBlock.myTribSlot;
    myTribFall=                 theBlock.myTribFall;
    myDmSource=                 theBlock.myDmSource;
    myOpuConfig=                theBlock.myOpuConfig;
	myLtcActMode=               theBlock.myLtcActMode;
    myGfpTs=                    theBlock.myGfpTs;
    myInterPacketGap=           theBlock.myInterPacketGap;
    myExtChannel=               theBlock.myExtChannel;
    myOTIDStatus=               theBlock.myOTIDStatus;
    myHoldOffProt=              theBlock.myHoldOffProt;
    myTimDef=                   theBlock.myTimDef;
    myExpDapi=                  theBlock.myExpDapi;
    myExpSapi=                  theBlock.myExpSapi;
    myTxDapi=                   theBlock.myTxDapi;
    myTxSapi=                   theBlock.myTxSapi;
    myLacpPriority=             theBlock.myLacpPriority;
    myLacpParticipation=        theBlock.myLacpParticipation;
    myAisType=                  theBlock.myAisType;
    myTribSize =                theBlock.myTribSize;
    myBurstyBerSdInterval=              theBlock.myBurstyBerSdInterval;
    myBurstyBerSdThreshold=             theBlock.myBurstyBerSdThreshold;
    myQualityLevel=                     theBlock.myQualityLevel;
    myIsAutoAdjustAttenuationEnabled=   theBlock.myIsAutoAdjustAttenuationEnabled;
    myExpOperator=              theBlock.myExpOperator;
    myTxOperator=               theBlock.myTxOperator;
    myOTNMap =                  theBlock.myOTNMap;
    myMapMode =                 theBlock.myMapMode;
    myQua =                     theBlock.myQua;
    myPluggableReach =          theBlock.myPluggableReach;

    return *this;
}

bool 
TL1_FacilityEntParameters::operator==( const TL1_FacilityEntParameters& theBlock ) const
{
     if( myAlarmProfile != theBlock.myAlarmProfile )
         return false;

     if( myTrace != theBlock.myTrace )
         return false;

     if( myExpectedTrace != theBlock.myExpectedTrace )
         return false;

     if( myIsMonitorTraceEnabled != theBlock.myIsMonitorTraceEnabled )
         return false;

     if( myIsInsertAisEnabled != theBlock.myIsInsertAisEnabled )
         return false;

     if( myMapping != theBlock.myMapping )
         return false;

     if( mySFThreshold != theBlock.mySFThreshold )
         return false;

     if( mySDThreshold != theBlock.mySDThreshold )
         return false;

     if( myExternalConectivity != theBlock.myExternalConectivity )
         return false;

     if( myIsProtectionEnabled != theBlock.myIsProtectionEnabled )
         return false;

     if( myMaintProp != theBlock.myMaintProp )
         return false;

     if( myIsAdaptiveEnabled != theBlock.myIsAdaptiveEnabled )
         return false;

     if( myMaxRate != theBlock.myMaxRate )
         return false;

     if( myExpectedSignalRate != theBlock.myExpectedSignalRate )
         return false;

     if( myRateList != theBlock.myRateList )
         return false;

     if( mySignalType != theBlock.mySignalType )
         return false;

     if( myStsMap != theBlock.myStsMap )
         return false;

     if( myPrimaryState != theBlock.myPrimaryState )
         return false;

     if( myLineCode != theBlock.myLineCode )            
         return false;

     if( mySignalFrameFormat != theBlock.mySignalFrameFormat )
         return false;

     if( myIsTransparent != theBlock.myIsTransparent )
         return false;

     if( myIsSsmConnected != theBlock.myIsSsmConnected )
         return false;

     if( myConectedTo != theBlock.myConectedTo )
         return false;

     if( myGbeFramingMode != theBlock.myGbeFramingMode )
         return false;

     if( myGenTrc != theBlock.myGenTrc )
         return false;

     if( myIsTrafficEnabled != theBlock.myIsTrafficEnabled )
         return false;

     if( myGfpMap != theBlock.myGfpMap )
         return false;

     if( myNendALS != theBlock.myNendALS )
         return false;

     if( myHgeMap != theBlock.myHgeMap)
         return false;

     if( myNValue != theBlock.myNValue )
         return false;

     if( myFecType != theBlock.myFecType )     
         return false;

     if( myOtuExpTrc != theBlock.myOtuExpTrc )
         return false;

     if( myOtuTrc != theBlock.myOtuTrc ) 
         return false;

     if( myTransMap != theBlock.myTransMap )
         return false;

     if( myClkType != theBlock.myClkType )
         return false;

     if( myTapNumber != theBlock.myTapNumber )
         return false;

     if( myIsAutoNegotiationEnabled != theBlock.myIsAutoNegotiationEnabled)
         return false;

     if( myOeoRegen != theBlock.myOeoRegen )
         return false;

     if( myCnvTermType != theBlock.myCnvTermType )
         return false;

    if ( myPt != theBlock.myPt )
        return false;

    if ( myGfpUpi != theBlock.myGfpUpi )
        return false;

    if ( myEthRate!= theBlock.myEthRate )
        return false;

    if ( myDuplexMode!= theBlock.myDuplexMode)
        return false;

    if ( myTcmMode!=theBlock.myTcmMode )
        return false;

    if ( myFlowAd!= theBlock.myFlowAd)
        return false;

    if ( myFlowCtrl!= theBlock.myFlowCtrl)
        return false;

    if ( myVlanTag!= theBlock.myVlanTag)
        return false;

    if ( myTagMode!= theBlock.myTagMode)
        return false;

    if ( myTpid!= theBlock.myTpid)
        return false;

    if( myDiscardPause != theBlock.myDiscardPause )
        return false;

    if( myPropFefi != theBlock.myPropFefi )
        return false;

    if ( myHandle != theBlock.myHandle )
        return false;

    if ( myCtag != theBlock.myCtag )
        return false;

     if( myPmProfile != theBlock.myPmProfile )
         return false;

     if( myCbrMap!= theBlock.myCbrMap )
         return false;
     
     if( myCFProfile != theBlock.myCFProfile )
         return false;

     if( myGfpMux!= theBlock.myGfpMux )
         return false;

     if( myAdjacent!= theBlock.myAdjacent )
         return false;

     if( myTribSlot!= theBlock.myTribSlot )
         return false;

     if( myTribFall!= theBlock.myTribFall )
         return false;

     if( myDmSource!= theBlock.myDmSource )
         return false;

    if (myOpuConfig != theBlock.myOpuConfig)
        return false;

	 if(myLtcActMode!= theBlock.myLtcActMode)
	 	return false;
	 
     if( myGfpTs!= theBlock.myGfpTs )
         return false;

     if( myTimDef != theBlock.myTimDef)
        return false;

     if( myExpDapi != theBlock.myExpDapi)
        return false;

     if( myExpSapi != theBlock.myExpSapi)
        return false;

     if( myTxDapi != theBlock.myTxDapi)
        return false;

     if( myTxSapi != theBlock.myTxSapi)
        return false;
     
     if( myExtChannel!= theBlock.myExtChannel )
         return false;
     
     if( myOTIDStatus!= theBlock.myOTIDStatus )
         return false;
     
     if( myHoldOffProt!= theBlock.myHoldOffProt )
         return false;
     
    if ( myLacpPriority != theBlock.myLacpPriority)
        return false;

    if ( myLacpParticipation != theBlock.myLacpParticipation )
        return false;

    if ( myAisType != theBlock.myAisType )
        return false;

    if ( myTribSize != theBlock.myTribSize )
        return false;

    if ( myBurstyBerSdInterval != theBlock.myBurstyBerSdInterval )
        return false;

    if ( myBurstyBerSdThreshold != theBlock.myBurstyBerSdThreshold )
        return false;

    if ( myQualityLevel != theBlock.myQualityLevel )
        return false;

    if( myInterPacketGap != theBlock.myInterPacketGap )
        return false;

    if ( myIsAutoAdjustAttenuationEnabled != theBlock.myIsAutoAdjustAttenuationEnabled )
        return false;

    if (myExpOperator != theBlock.myExpOperator)
        return false;

    if (myTxOperator != theBlock.myTxOperator)
        return false;

    if (myOTNMap != theBlock.myOTNMap)
        return false;

    if (myMapMode != theBlock.myMapMode)
        return false;

    if (myQua != theBlock.myQua)
        return false;

    if (myPluggableReach != theBlock.myPluggableReach)
        return false;
    
    return true;
}

//------------------------------------------------------------------------
bool TL1_FacilityEntParameters::IsControlPlaneRequest()
{
    return T7100_TL1AgentUtility::IsControlPlaneRequest( GetHandle() );
}

TL1_FacilityValidateEntParameters::TL1_FacilityValidateEntParameters( ) :
    myEntParametersSet( (int)AnyParameters + 1, false )
{
    myEntParametersSet[HandleEnterable] = true;
    myEntParametersSet[CtagEnterable]   = true;
}

TL1_FacilityValidateEntParameters::~TL1_FacilityValidateEntParameters( )
{
}

void 
TL1_FacilityValidateEntParameters::ValidateEnterParameters( const TL1_FacilityEntParameters& theEntParameters ) const
{
    if ( true == myEntParametersSet[AnyParameters] )
    {
        return;
    }

    if ( ( false == myEntParametersSet[AlarmProfileEnterable] ) &&
         ( theEntParameters.GetAlarmProfile( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TraceEnterable] ) &&
         ( theEntParameters.GetTrace( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[ExpectedTraceEnterable] ) &&
         ( theEntParameters.GetExpectedTrace( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsMonitorTraceEnabledEnterable] ) &&
         ( theEntParameters.GetIsMonitorTraceEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsInsertAisEnabledEnterable] ) &&
         ( theEntParameters.GetIsInsertAisEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[MappingEnterable] ) &&
         ( theEntParameters.GetMapping( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[SFThresholdEnterable] ) &&
         ( theEntParameters.GetSFThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[SDThresholdEnterable] ) &&
         ( theEntParameters.GetSDThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[ExternalConnectivityEnterable] ) &&
         ( theEntParameters.GetExternalConnectivity( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsProtectionEnabledEnterable] ) &&
         ( theEntParameters.GetIsProtectionEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[MaintPropEnterable] ) &&
         ( theEntParameters.GetMaintPropagate( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsAdaptiveEnabledEnterable] ) &&
         ( theEntParameters.GetIsAdaptiveEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[MaxRateEnterable] ) &&
         ( theEntParameters.GetMaxRate( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[ExpectedSignalRateEnterable] ) &&
         ( theEntParameters.GetExpectedSignalRate( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[RateListEnterable] ) &&
         ( theEntParameters.GetRateList( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[SignalTypeEnterable] ) &&
         ( theEntParameters.GetSignalType( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }


    if ( ( false == myEntParametersSet[StsMapEnterable] ) &&
         ( theEntParameters.GetStsMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[PrimaryStateEnterable] ) &&
         ( theEntParameters.GetPrimaryState( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[LineCodeEnterable] ) &&
         ( theEntParameters.GetLineCode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[SignalFrameFormatEnterable] ) &&
         ( theEntParameters.GetSignalFrameFormat( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsTransparentEnterable] ) &&
         ( theEntParameters.GetIsTransparent( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsSsmConnectedEnterable] ) &&
         ( theEntParameters.GetIsSsmConnected( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[ConnectedToEnterable] ) &&
         ( theEntParameters.GetConnectedTo( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[GbeFramingModeEnterable] ) &&
         ( theEntParameters.GetGbeFramingMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[GenTrcEnterable] ) &&
         ( theEntParameters.GetGenTrc( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsTrafficEnabledEnterable] ) &&
         ( theEntParameters.GetIsTrafficEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[GfpMapEnterable] ) &&
         ( theEntParameters.GetGfpMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[NendALSEnterable] ) &&
         ( theEntParameters.GetNendALS( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[NValueEnterable] ) &&
         ( theEntParameters.GetNValue( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[FecTypeEnterable] ) &&
         ( theEntParameters.GetFecType( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[OtuExpTrcEnterable] ) &&
         ( theEntParameters.GetOtuExpTrc( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[OtuTrcEnterable] ) &&
         ( theEntParameters.GetOtuTrc( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TransMapEnterable] ) &&
         ( theEntParameters.GetTransMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[ClkTypeEnterable] ) &&
         ( theEntParameters.GetClkType( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TapNumberEnterable] ) &&
         ( theEntParameters.GetTapNumber( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[IsAutoNegotiationEnabledEnterable] ) &&
         ( theEntParameters.GetIsAutoNegotiationEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[OeoRegenEnterable] ) &&
         ( theEntParameters.GetOeoRegen() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[CnvTermTypeEnterable] ) &&
         ( theEntParameters.GetCnvTermType() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[PtEnterable] ) &&
         ( theEntParameters.GetPt() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[GfpUpiEnterable] ) &&
         ( theEntParameters.GetGfpUpi() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[HandleEnterable] ) &&
         ( theEntParameters.GetHandle( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[CtagEnterable] ) &&
         ( theEntParameters.GetHandle( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[EthRateEnterable] ) &&
         ( theEntParameters.GetEthRate( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[DuplexModeEnterable] ) &&
         ( theEntParameters.GetDuplexMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TcmModeEnterable] ) &&
         ( theEntParameters.GetTcmMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[FlowAdEnterable] ) &&
         ( theEntParameters.GetFlowCtrlAd( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[FlowCtrlEnterable] ) &&
         ( theEntParameters.GetFlowCtrlEnable( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[VlanTagEnterable] ) &&
         (theEntParameters.GetVLanTag() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TagModeEnterable] ) &&
         (theEntParameters.GetTagMode() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TpidEnterable] ) &&
         (theEntParameters.GetTPid() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[DiscardPauseEnterable] ) &&
         ( theEntParameters.GetDiscardPause( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[PropFefiEnterable] ) &&
         ( theEntParameters.GetPropFefi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[PmProfileEnterable] ) &&
         ( theEntParameters.GetPmProfile( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[CbrMapEnterable] ) &&
         ( theEntParameters.GetCbrMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[CFProfileEnterable] ) &&
         ( theEntParameters.GetCFProfile( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[GfpMuxEnterable] ) &&
         ( theEntParameters.GetGfpMux( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( (( false == myEntParametersSet[AdjacentEntable] ) &&
         ( theEntParameters.GetAdjacent( ) ) ) || ((true == myEntParametersSet[AdjacentEntable]) && 
         CT_TCM_ADJACENT_UNKNOWN == *(theEntParameters.GetAdjacent())))
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[TribSlotEnterable] ) &&
         ( theEntParameters.GetTribSlot( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    
    if ( ( false == myEntParametersSet[TimDefEnterable] ) &&
         ( theEntParameters.GetTimDef( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[ExpDapiEnterable] ) &&
         ( theEntParameters.GetExpDapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[ExpSapiEnterable] ) &&
         ( theEntParameters.GetExpSapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[TxDapiEnterable] ) &&
         ( theEntParameters.GetTxDapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[TxSapiEnterable] ) &&
         ( theEntParameters.GetTxSapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }    
    if ( ( false == myEntParametersSet[ExtChannelEnterable] ) &&
         ( theEntParameters.GetExtChannel( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[OTIDStatusEnterable] ) &&
         ( theEntParameters.GetOTIDStatus( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[HoldOffProtEnterable] ) &&
         ( theEntParameters.GetHoldOffProt( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEntParametersSet[LacpPriorityEnterable] ) &&
         ( theEntParameters.GetLacpPriority( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[LacpParticipationEnterable] ) &&
         ( theEntParameters.GetLacpParticipation( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    
    if ( ( false == myEntParametersSet[AisTypeEnterable] ) &&
         ( theEntParameters.GetAisType( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TribSizeEnterable] ) &&
         ( theEntParameters.GetTribSize( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[BurstyBerSdIntervalEnterable] ) &&
         ( theEntParameters.GetBurstyBerSdInterval( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[BurstyBerSdThresholdEnterable] ) &&
         ( theEntParameters.GetBurstyBerSdThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TribFallEnterable] ) &&
         ( theEntParameters.GetTribFall( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[GfpTsEnterable] ) &&
         ( theEntParameters.GetGfpTs( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[DmSourceEnterable] ) &&
         ( theEntParameters.GetDmSource( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[OpuConfigEnterable] ) &&
         ( theEntParameters.GetOpuConfig( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

	if ( ( false == myEntParametersSet[LtcActModeEnterable] ) &&
         ( theEntParameters.GetLtcActMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[QualityLevelEnterable] ) &&
         ( theEntParameters.GetQualityLevel( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[InterPacketGapEnterable] ) &&
         ( theEntParameters.GetInterPacketGap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[AutoAdjustAttenuationEnabledEnterable] ) &&
         ( theEntParameters.GetIsAutoAdjustAttenuationEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[ExpOperatorEnterable] ) &&
         ( theEntParameters.GetExpOperator( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[TxOperatorEnterable] ) &&
         ( theEntParameters.GetTxOperator( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[OTNMapEnable] ) &&
         ( theEntParameters.GetOTNMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[MapModeEnable] ) &&
         ( theEntParameters.GetMapMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEntParametersSet[QuaEnterable] ) &&
         ( theEntParameters.GetQuarantine( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
}

