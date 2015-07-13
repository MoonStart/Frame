/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 30, 2005 - Thomas J. Novak
DESCRIPTION:    Implementation file for TL1 EDIT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FACILITYEDPARAMETERS_H__
#include <TL1Core/TL1_FacilityEdParameters.h>
#endif

#ifndef __FAC_TRNPORTGENMONBEH_H__
#include <TL1Facility/T7100_TL1FacilityEntity.h>
#endif

#ifndef __T7100_TL1AGENTUTILITY_H__
#include <TL1Core/T7100_TL1AgentUtility.h>
#endif

TL1_FacilityEdParameters::TL1_FacilityEdParameters()
{
    myAlarmProfile=                     (CT_ProfileTableId*)0;
    myPrimaryState=                     (CT_SM_PST*)0;
    myIsCommandForced=                  (bool*)0;
    myIsProtectionEnabled=              (CT_FAC_Protection*)0;
    myMaintProp=                        (CT_FAC_MaintProp*)0;
    myIsAdaptiveEnabled=                (bool*)0;
    myMaxRate=                          (CT_TEL_daHz*)0;
    myExpectedSignalRate=               (CT_TL1_ExpectedRateRange*)0;
    myRateList=                         (CT_FAC_SignalRateListType*)0;
    myIsOtuMapEnabled =                 (bool*)0;
    myTrace=                            (CT_Fac_TraceString*)0;
    mySentTrace=                        (CT_Fac_TraceString*)0;
    myExpectedTrace=                    (CT_Fac_TraceString*)0;
    myIsMonitorOtiEnabled=              (bool*)0;
    myIsMonitorTraceEnabled=            (bool*)0;
    myIsInsertAisEnabled=               (bool*)0;
    mySFThreshold=                      (CT_TEL_BERLevels*)0;
    mySDThreshold=                      (CT_TEL_BERLevels*)0;
    myExternalConnectivity=             (CT_FAC_ExternalConnectivity*)0;
    mySignalType=                       (CT_TEL_SignalType*)0;
    myClkType=                          (CT_TEL_ClkType*)0;
    myOTIDStatus=                       (CT_TEL_OTIDStatus*)0;
    myIsAutoAdjustAttenuationEnabled=   (bool*)0;
    myIsAutoAdjustOutPowerEnabled=      (bool*)0;
    myIsAutoAdjustInPowerEnabled=       (bool*)0;
    myIsAutoTxPowerShutdownEnabled=     (bool*)0;
    myLineCode=                         (CT_FAC_LineCode*)0;                       
    myFrameFormat=                      (CT_FAC_FrameFormat*)0;             
    myIsSsmConnected=                   (bool*)0;
    myConnectedTo=                      (CT_Fac_ConnectedToString*)0;
    myGfpMap=                           (CT_TEL_GfpFramingMode*)0;
    myProtFunc=                         (CT_Fac_TraceString*)0;
    myGenTrc=                           (bool*)0;
    myFecType=                          (CT_TEL_FecType*)0;
    mySuperFec=                         (CT_TEL_SuperFec*)0;
    myLOSThreshold=                     (CT_TEL_mBm*)0;
    mySWThreshold=                      (CT_TEL_mBm*)0;
    mySignalBand=                       (CT_TEL_OpticalWaveLength*)0;
    myNendALS=                          (bool*)0;
    myOtuExpTrc=                        (CT_Fac_TraceString*)0;
    myAddCrsMap=                        (CT_FAC_StsMap*)0;
    myDelCrsMap=                        (CT_FAC_StsMap*)0;
    myIsEonMsgEnabled=                  (bool*)0;
    myIsTrafficEnabled=                 (bool*)0;
    myOeoRegen=                         (CT_TEL_OEO_REGEN_MODE*)0;
    myTapNumber=                        (CT_TapNumber*)0;
    myIsAutoNegotiationEnabled=         (bool*)0;
    myHandle=                           (LT_Handle*)0;             
    myPt=                              (CT_TEL_PayloadSignalId*)0;
    myGfpUpi=                           (CT_TEL_GfpUpiId*)0;
    myQua=                              (bool*)0;
    myCtag=                             (LT_Ctag)0;
    myHoldOffProt=                      (int*)0;
    myExtChannel=                       (uint32*)0;
    myAddCstMap=                        (CT_FAC_StsMap*)0;
    myDelCstMap=                        (CT_FAC_StsMap*)0;
    myEthRate=                          (CT_TEL_daHz*)0;
    myDuplexMode=                       (CT_TEL_MAC_DUPLEX_MODE*)0;
    myTcmMode=                          (CT_TCM_Mode*)0;
    myFlowAd=                           (CT_TEL_MAC_ADFLW_CTRL*)0;
    myFlowCtrl=                         (CT_TEL_MAC_FLOWCTRL*)0;
    myVlanTag=                          (CT_TEL_VlanTag*)0;
    myTagMode=                          (bool*)0;
    myTpid=                             (CT_TEL_Tpid*)0;
    myDiscardPause=                     (bool*)0;
    myPropFefi=                         (bool*)0;
    myPmProfile=                        (CT_PMProfileTableId*)0;
    myCFProfile=                        (int*)0;
    myCbrMap=                           (CT_TEL_PayloadType*)0;
    myTribSlot=                         (CT_FAC_OduTsMap *)0;
    myTribFall=                         (bool *)0;
    myDmSource=                         (bool *)0;
	myLtcActMode=                       (bool *)0;
    myGfpTs=                            (uint8*)0;
    myInterPacketGap=                   (uint8*)0;
    myGfpMux=                           (CT_TEL_GFP_MUX*)0;
    myTimDef=                           (CT_TEL_TimCriteriaMode*)0;
    myExpDapi=                          (CT_Fac_TraceString*)0;
    myExpSapi=                          (CT_Fac_TraceString*)0;
    myTxDapi=                           (CT_Fac_TraceString*)0;
    myTxSapi=                           (CT_Fac_TraceString*)0;  
    myOtsChanMap=                       (CT_FAC_OtsChanMap*)0;
    myOtsChanType=                       (CT_FAC_OtsChanType*)0;
    myLacpPriority=                     (int*)0;
    myLacpParticipation=                (CT_TEL_LacpPartiMode*)0;
    myAisType=                          (CT_RS_IndicationType*)0;
    myTribSize =                        (CT_TEL_TS_SIZE*)0;
    myBurstyBerSdInterval=              (uint16*)0;
    myBurstyBerSdThreshold=             (uint32*)0;
    myQualityLevel=                     (CT_FAC_QualityLevelOverride*)0;
    myNpOwner=                          (int*)0;
    myOpuConfig=                        (CT_TEL_OPU_FORMAT*)0;
    myExpOperator=                      (CT_Fac_TraceString*)0;
    myTxOperator=                       (CT_Fac_TraceString*)0;
    myWcgChanReserve=                   (uint8 *)0;
    myWcgChanRelease=                   (uint8 *)0;
    myOTNMap =                          (bool *)0;
    myMapMode =                         (CT_TEL_PayloadType*)0;
}


TL1_FacilityEdParameters::~TL1_FacilityEdParameters()
{
}

TL1_FacilityEdParameters& 
TL1_FacilityEdParameters::operator=( const TL1_FacilityEdParameters& theBlock )
{
    myAlarmProfile=                     theBlock.myAlarmProfile;
    myPrimaryState=                     theBlock.myPrimaryState;
    myIsCommandForced=                  theBlock.myIsCommandForced;
    myIsProtectionEnabled=              theBlock.myIsProtectionEnabled;
    myMaintProp=                        theBlock.myMaintProp;
    myIsAdaptiveEnabled=                theBlock.myIsAdaptiveEnabled;  
    myMaxRate=                          theBlock.myMaxRate;
    myExpectedSignalRate=               theBlock.myExpectedSignalRate;
    myRateList=                         theBlock.myRateList;
    myIsOtuMapEnabled=                  theBlock.myIsOtuMapEnabled;
    myTrace=                            theBlock.myTrace;
    mySentTrace=                        theBlock.mySentTrace;
    myExpectedTrace=                    theBlock.myExpectedTrace;
    myIsMonitorOtiEnabled=              theBlock.myIsMonitorOtiEnabled;
    myIsMonitorTraceEnabled=            theBlock.myIsMonitorTraceEnabled;
    myIsInsertAisEnabled=               theBlock.myIsInsertAisEnabled;
    mySFThreshold=                      theBlock.mySFThreshold;
    mySDThreshold=                      theBlock.mySDThreshold;
    myExternalConnectivity=             theBlock.myExternalConnectivity;
    mySignalType=                       theBlock.mySignalType;
    myClkType=                          theBlock.myClkType;
    myOTIDStatus=                       theBlock.myOTIDStatus;
    myIsAutoAdjustAttenuationEnabled=   theBlock.myIsAutoAdjustAttenuationEnabled;
    myIsAutoAdjustOutPowerEnabled=      theBlock.myIsAutoAdjustOutPowerEnabled;
    myIsAutoAdjustInPowerEnabled=       theBlock.myIsAutoAdjustInPowerEnabled;
    myIsAutoTxPowerShutdownEnabled=     theBlock.myIsAutoTxPowerShutdownEnabled;
    myLineCode=                         theBlock.myLineCode;                       
    myFrameFormat=                      theBlock.myFrameFormat;             
    myIsSsmConnected=                   theBlock.myIsSsmConnected;
    myConnectedTo=                      theBlock.myConnectedTo;
    myGfpMap=                           theBlock.myGfpMap;
    myProtFunc=                         theBlock.myProtFunc;
    myGenTrc=                           theBlock.myGenTrc;
    myFecType=                          theBlock.myFecType;
    myLOSThreshold=                     theBlock.myLOSThreshold;
    mySWThreshold=                      theBlock.mySWThreshold;
    mySignalBand=                       theBlock.mySignalBand;
    myNendALS=                          theBlock.myNendALS;
    myOtuExpTrc=                        theBlock.myOtuExpTrc;
    myAddCrsMap=                        theBlock.myAddCrsMap;
    myDelCrsMap=                        theBlock.myDelCrsMap;
    myIsEonMsgEnabled=                  theBlock.myIsEonMsgEnabled;
    myIsTrafficEnabled=                 theBlock.myIsTrafficEnabled;
    myOeoRegen=                         theBlock.myOeoRegen;
    myTapNumber=                        theBlock.myTapNumber;
    myIsAutoNegotiationEnabled=         theBlock.myIsAutoNegotiationEnabled;
    myHandle=                           theBlock.myHandle;             
    myGfpUpi=                           theBlock.myGfpUpi;
    myPt=                               theBlock.myPt;
    myQua=                              theBlock.myQua;
    myCtag=                             theBlock.myCtag;
    myHoldOffProt=                      theBlock.myHoldOffProt;
    myExtChannel=                       theBlock.myExtChannel;
    myAddCstMap=                        theBlock.myAddCstMap;
    myDelCstMap=                        theBlock.myDelCstMap;
    myEthRate=                          theBlock.myEthRate;
    myDuplexMode=                       theBlock.myDuplexMode;
    myTcmMode=                          theBlock.myTcmMode;
    myFlowAd=                           theBlock.myFlowAd;
    myFlowCtrl=                         theBlock.myFlowCtrl;
    myVlanTag=                          theBlock.myVlanTag;
    myTagMode=                          theBlock.myTagMode;
    myTpid=                             theBlock.myTpid;
    myDiscardPause=                     theBlock.myDiscardPause;
    myPropFefi=                         theBlock.myPropFefi;
    myPmProfile=                        theBlock.myPmProfile;
    myCFProfile=                        theBlock.myCFProfile;
    myCbrMap=                           theBlock.myCbrMap;
    myGfpMux=                           theBlock.myGfpMux;
    myTribSlot=                         theBlock.myTribSlot;
    myTribFall=                         theBlock.myTribFall;
    myDmSource=                         theBlock.myDmSource;
	myLtcActMode=                       theBlock.myLtcActMode;
    myGfpTs=                            theBlock.myGfpTs;
    myInterPacketGap=                   theBlock.myInterPacketGap;
    myTimDef=                           theBlock.myTimDef;
    myExpDapi=                          theBlock.myExpDapi;
    myExpSapi=                          theBlock.myExpSapi;
    myTxDapi=                           theBlock.myTxDapi;
    myTxSapi=                           theBlock.myTxSapi;
    myLacpPriority=                     theBlock.myLacpPriority;
    myLacpParticipation=                theBlock.myLacpParticipation;
    myOtsChanMap=                       theBlock.myOtsChanMap;
    myOtsChanType=                      theBlock.myOtsChanType;
    myAisType=                          theBlock.myAisType;
    myTribSize =                        theBlock.myTribSize;
    myBurstyBerSdInterval=              theBlock.myBurstyBerSdInterval;
    myBurstyBerSdThreshold=             theBlock.myBurstyBerSdThreshold;
    myQualityLevel=                     theBlock.myQualityLevel;
    myNpOwner=                          theBlock.myNpOwner;
    myOpuConfig=                        theBlock.myOpuConfig;
    myWcgChanReserve=                   theBlock.myWcgChanReserve;
    myWcgChanRelease=                   theBlock.myWcgChanRelease;
       
    myExpOperator=                      theBlock.myExpOperator;
    myTxOperator=                       theBlock.myTxOperator;
    myOTNMap =                          theBlock.myOTNMap;
    myMapMode =                         theBlock.myMapMode;
    return *this;
}

bool 
TL1_FacilityEdParameters::operator==( const TL1_FacilityEdParameters& theBlock ) const
{
    if ( myAlarmProfile != theBlock.myAlarmProfile )
        return false;

    if ( myPrimaryState != theBlock.myPrimaryState )
        return false;

    if ( myIsCommandForced != theBlock.myIsCommandForced )
        return false;

    if ( myIsProtectionEnabled != theBlock.myIsProtectionEnabled )
        return false;

    if ( myMaintProp != theBlock.myMaintProp )
        return false;

    if ( myIsAdaptiveEnabled != theBlock.myIsAdaptiveEnabled )  
        return false;

    if ( myMaxRate != theBlock.myMaxRate )
        return false;

     if( myExpectedSignalRate != theBlock.myExpectedSignalRate )
         return false;

    if ( myRateList != theBlock.myRateList )
        return false;

    if ( myIsOtuMapEnabled != theBlock.myIsOtuMapEnabled )
        return false;

    if ( myTrace != theBlock.myTrace )
        return false;

    if ( mySentTrace != theBlock.mySentTrace )
        return false;

    if ( myExpectedTrace != theBlock.myExpectedTrace )
        return false;

    if ( myIsMonitorOtiEnabled != theBlock.myIsMonitorOtiEnabled )
        return false;

    if ( myIsMonitorTraceEnabled != theBlock.myIsMonitorTraceEnabled )
        return false;

    if ( myIsInsertAisEnabled != theBlock.myIsInsertAisEnabled )
        return false;

    if ( mySFThreshold != theBlock.mySFThreshold )
        return false;

    if ( mySDThreshold != theBlock.mySDThreshold )
        return false;

    if ( myExternalConnectivity != theBlock.myExternalConnectivity )
        return false;

    if ( mySignalType != theBlock.mySignalType )
        return false;

    if (myClkType != theBlock.myClkType)
    {
        return false;
    }
    if (myOTIDStatus != theBlock.myOTIDStatus)
    {
        return false;
    }
    if ( myIsAutoAdjustAttenuationEnabled != theBlock.myIsAutoAdjustAttenuationEnabled )
        return false;

    if ( myIsAutoAdjustOutPowerEnabled != theBlock.myIsAutoAdjustOutPowerEnabled )
        return false;

    if ( myIsAutoAdjustInPowerEnabled != theBlock.myIsAutoAdjustInPowerEnabled )
        return false;

    if ( myIsAutoTxPowerShutdownEnabled != theBlock.myIsAutoTxPowerShutdownEnabled )
        return false;

    if ( myLineCode != theBlock.myLineCode )                       
        return false;

    if ( myFrameFormat != theBlock.myFrameFormat )             
        return false;

    if ( myIsSsmConnected != theBlock.myIsSsmConnected )
        return false;

    if ( myConnectedTo != theBlock.myConnectedTo )
        return false;

    if ( myGfpMap != theBlock.myGfpMap )
        return false;

    if ( myProtFunc != theBlock.myProtFunc )
        return false;

    if ( myGenTrc != theBlock.myGenTrc )
        return false;

    if ( myFecType!= theBlock.myFecType )
        return false;

    if ( myLOSThreshold != theBlock.myLOSThreshold )
        return false;

    if ( mySWThreshold != theBlock.mySWThreshold )
        return false;

    if ( mySignalBand != theBlock.mySignalBand )
        return false;

    if ( myNendALS != theBlock.myNendALS )
        return false;

    if ( myOtuExpTrc != theBlock.myOtuExpTrc )
        return false;

    if ( myAddCrsMap != theBlock.myAddCrsMap )
        return false;

    if ( myDelCrsMap != theBlock.myDelCrsMap )
        return false;

    if ( myIsEonMsgEnabled != theBlock.myIsEonMsgEnabled )
        return false;

    if ( myIsTrafficEnabled != theBlock.myIsTrafficEnabled )
        return false;

     if( myOeoRegen != theBlock.myOeoRegen )
        return false;

    if ( myTapNumber != theBlock.myTapNumber)
        return false;

    if ( myIsAutoNegotiationEnabled != theBlock.myIsAutoNegotiationEnabled )
        return false;

    if ( myHandle != theBlock.myHandle )
        return false;

    if ( myPt != theBlock.myPt )
        return false;

    if ( myGfpUpi != theBlock.myGfpUpi )
        return false;

    if ( myQua != theBlock.myQua )
        return false;

    if ( myCtag != theBlock.myCtag )
        return false;

    if ( myHoldOffProt != theBlock.myHoldOffProt )
        return false;

    if ( myExtChannel != theBlock.myExtChannel )
        return false;
    
    if ( myAddCstMap != theBlock.myAddCstMap )
        return false;

    if ( myDelCstMap != theBlock.myDelCstMap )
        return false;

    if ( myEthRate!= theBlock.myEthRate )
        return false;

    if ( myDuplexMode!= theBlock.myDuplexMode)
        return false;

    if ( myTcmMode!= theBlock.myTcmMode)
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

    if ( myDiscardPause != theBlock.myDiscardPause )
        return false;

    if ( myPropFefi != theBlock.myPropFefi )
        return false;

    if ( myPmProfile != theBlock.myPmProfile )
        return false;
    
    if( myCbrMap!= theBlock.myCbrMap )
         return false;
    
    if ( myCFProfile != theBlock.myCFProfile )
        return false;
    
    if( myGfpMux!= theBlock.myGfpMux )
         return false;

    if( myTribSlot!= theBlock.myTribSlot )
         return false;

    if( myTribFall!= theBlock.myTribFall )
         return false;

    if( myDmSource!= theBlock.myDmSource )
         return false;

	if( myLtcActMode!= theBlock.myLtcActMode)
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

     if ( myOtsChanMap != theBlock.myOtsChanMap )
        return false;       
         
     if ( myOtsChanType != theBlock.myOtsChanType )
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

    if ( myInterPacketGap != theBlock.myInterPacketGap )
        return false;

    if ( myNpOwner != theBlock.myNpOwner )
        return false;

    if ( myOpuConfig != theBlock.myOpuConfig )
        return false;

    if ( myWcgChanReserve != theBlock.myWcgChanReserve)
         return false;
	
    if ( myWcgChanRelease != theBlock.myWcgChanRelease)
         return false;
	
    if (myExpOperator != theBlock.myExpOperator)
        return false;

    if (myTxOperator != theBlock.myTxOperator)
        return false;

    if (myOTNMap != theBlock.myOTNMap)
        return false;

    if (myMapMode != theBlock.myMapMode)
        return false;

    return true;
}

//------------------------------------------------------------------------
bool TL1_FacilityEdParameters::IsControlPlaneRequest()
{
    return T7100_TL1AgentUtility::IsControlPlaneRequest( GetHandle() );
}

TL1_FacilityValidateEdParameters::TL1_FacilityValidateEdParameters( ) :
    myEdParametersSet( (int)AnyParameters + 1, false )
{
        myEdParametersSet[HandleEditable]   = true;
        myEdParametersSet[CtagEditable]     =  true;
}

TL1_FacilityValidateEdParameters::~TL1_FacilityValidateEdParameters( )
{
}

void 
TL1_FacilityValidateEdParameters::ValidateEditParameters( const TL1_FacilityEdParameters& theEdParameters ) const
{

    if ( true == myEdParametersSet[AnyParameters] )
    {
        return;
    }

    if ( ( false == myEdParametersSet[AlarmProfileEditable] ) &&
         ( theEdParameters.GetAlarmProfile( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[PrimaryStateEditable] ) &&
         ( theEdParameters.GetPrimaryState( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsCommandForcedEditable] ) &&
         ( theEdParameters.GetIsCommandForced( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsProtectionEnabledEditable] ) &&
         ( theEdParameters.GetIsProtectionEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[MaintPropEditable] ) &&
         ( theEdParameters.GetMaintPropagate( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsAdaptiveEnabledEditable] ) &&
         ( theEdParameters.GetIsAdaptiveEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[MaxRateEditable] ) &&
         ( theEdParameters.GetMaxRate( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[ExpectedSignalRateEditable] ) &&
         ( theEdParameters.GetExpectedSignalRate( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[RateListEditable] ) &&
         ( theEdParameters.GetRateList( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsOtuMapEnabledEditable] ) &&
         ( theEdParameters.GetIsOtuMapEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[TraceEditable] ) &&
         ( theEdParameters.GetTrace( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[SentTraceEditable] ) &&
         ( theEdParameters.GetSentTrace( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[ExpectedTraceEditable] ) &&
         ( theEdParameters.GetExpectedTrace( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsMonitorOtiEnabledEditable] ) &&
         ( theEdParameters.GetIsMonitorOtiEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsMonitorTraceEnabledEditable] ) &&
         ( theEdParameters.GetIsMonitorTraceEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    
    if ( ( false == myEdParametersSet[IsInsertAisEnabledEditable] ) &&
         ( theEdParameters.GetIsInsertAisEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[SFThresholdEditable] ) &&
         ( theEdParameters.GetSFThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[SDThresholdEditable] ) &&
         ( theEdParameters.GetSDThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[ExternalConnectivityEditable] ) &&
         ( theEdParameters.GetExternalConnectivity( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[SignalTypeEditable] ) &&
         ( theEdParameters.GetSignalType( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if((false == myEdParametersSet[ClkTypeEditable]) &&
       (theEdParameters.GetClkType()))
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if((false == myEdParametersSet[OTIDStatusEditable]) &&
       (theEdParameters.GetOTIDStatus()))
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsAutoAdjustAttenuationEnabledEditable] ) &&
         ( theEdParameters.GetIsAutoAdjustAttenuationEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsAutoAdjustOutPowerEnabledEditable] ) &&
         ( theEdParameters.GetIsAutoAdjustOutPowerEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsAutoAdjustInPowerEnabledEditable] ) &&
         ( theEdParameters.GetIsAutoAdjustInPowerEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsAutoTxPowerShutdownEnabledEditable] ) &&
         ( theEdParameters.GetIsAutoTxPowerShutdownEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[LineCodeEditable] ) &&
         ( theEdParameters.GetLineCode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[FrameFormatEditable] ) &&
         ( theEdParameters.GetFrameFormat( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsSsmConnectedEditable] ) &&
         ( theEdParameters.GetIsSsmConnected( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[ConnectedToEditable] ) &&
         ( theEdParameters.GetConnectedTo( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[GfpMapEditable] ) &&
         ( theEdParameters.GetGfpMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[ProtFuncEditable] ) &&
         ( theEdParameters.GetProtFunc( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[GenTrcEditable] ) &&
         ( theEdParameters.GetGenTrc( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[FecTypeEditable] ) &&
         ( theEdParameters.GetFecType( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[SuperFecEditable] ) &&
         ( theEdParameters.GetSuperFec( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[LOSThresholdEditable] ) &&
         ( theEdParameters.GetLOSThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }      

    if ( ( false == myEdParametersSet[SWThresholdEditable] ) &&
         ( theEdParameters.GetSWThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    } 

    if ( ( false == myEdParametersSet[SignalBandEditable] ) &&
         ( theEdParameters.GetSignalBand( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    } 

    if ( ( false == myEdParametersSet[NendALSEditable] ) &&
         ( theEdParameters.GetNendALS( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    } 

    if ( ( false == myEdParametersSet[OtuExpTrcEditable] ) &&
         ( theEdParameters.GetOtuExpTrc( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }    

    if ( ( false == myEdParametersSet[AddCrsMapEditable] ) &&
         ( theEdParameters.GetAddCrsMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }    

    if ( ( false == myEdParametersSet[DelCrsMapEditable] ) &&
         ( theEdParameters.GetDelCrsMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }   

    if ( ( false == myEdParametersSet[AddCstMapEditable] ) &&
         ( theEdParameters.GetAddCstMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }    

    if ( ( false == myEdParametersSet[DelCstMapEditable] ) &&
         ( theEdParameters.GetDelCstMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }    

    // ADDCRSMAP and DELCRSMAP can not be exist in the same command
    if ( ( theEdParameters.GetAddCrsMap( ) ) && ( theEdParameters.GetDelCrsMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    // ADDCSTMAP and DELCSTMAP can not be exist in the same command
    if ( ( theEdParameters.GetAddCstMap( ) ) && ( theEdParameters.GetDelCstMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[IsEonMsgEnabledEditable] ) &&
         ( theEdParameters.GetIsEonMsgEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
 
    if ( ( false == myEdParametersSet[IsTrafficEnabledEditable] ) &&
         ( theEdParameters.GetIsTrafficEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[OeoRegenEditable] ) &&
         ( theEdParameters.GetOeoRegen() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
 
    if ( ( false == myEdParametersSet[TapNumberEditable] ) &&
         ( theEdParameters.GetTapNumber( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
 
    if ( ( false == myEdParametersSet[IsAutoNegotiationEnabledEditable] ) &&
         ( theEdParameters.GetIsAutoNegotiationEnabled( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
 
    if ( ( false == myEdParametersSet[HandleEditable] ) &&
         ( theEdParameters.GetHandle( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[PtEditable] ) &&
         ( theEdParameters.GetPt( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[GfpUpiEditable] ) &&
         ( theEdParameters.GetGfpUpi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[QuaEditable] ) &&
         ( theEdParameters.GetQuarantine( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[CtagEditable] ) &&
         ( theEdParameters.GetHandle( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[HoldOffProtEditable] ) &&
         ( theEdParameters.GetHoldOffProt( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[ExtChannelEditable] ) &&
         (theEdParameters.GetExtChannel() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[EthRateEditable] ) &&
         (theEdParameters.GetEthRate() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[DuplexModeEditable] ) &&
         (theEdParameters.GetDuplexMode() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[TcmModeEditerable] ) &&
         ( theEdParameters.GetTcmMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[FlowAdEditable] ) &&
         (theEdParameters.GetFlowCtrlAd() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[FlowCtrlEditable] ) &&
         (theEdParameters.GetFlowCtrlEnable() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[VlanTagEditable] ) &&
         (theEdParameters.GetVLanTag() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[TagModeEditable] ) &&
         (theEdParameters.GetTagMode() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[TpidEditable] ) &&
         (theEdParameters.GetTPid() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[DiscardPauseEditable] ) &&
         (theEdParameters.GetDiscardPause() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[PropFefiEditable] ) &&
         (theEdParameters.GetPropFefi() ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[PmProfileEditable] ) &&
         ( theEdParameters.GetPmProfile( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[CbrMapEditable] ) &&
         ( theEdParameters.GetCbrMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[CFProfileEditable] ) &&
         ( theEdParameters.GetCFProfile( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[TimDefEditable] ) &&
         ( theEdParameters.GetTimDef( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[GfpMuxEditable] ) &&
         ( theEdParameters.GetGfpMux( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[TribSlotEditable] ) &&
         ( theEdParameters.GetTribSlot( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[ExpDapiEditable] ) &&
         ( theEdParameters.GetExpDapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[ExpSapiEditable] ) &&
         ( theEdParameters.GetExpSapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[TxDapiEditable] ) &&
         ( theEdParameters.GetTxDapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[TxSapiEditable] ) &&
         ( theEdParameters.GetTxSapi( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }
    if ( ( false == myEdParametersSet[OtsChanMapEditable] ) &&
         ( theEdParameters.GetOtsChanMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }


    if ( ( false == myEdParametersSet[LacpPriorityEditable] ) &&
         ( theEdParameters.GetLacpPriority( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[LacpParticipationEditable] ) &&
         ( theEdParameters.GetLacpParticipation( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[AisTypeEditable] ) &&
         ( theEdParameters.GetAisType( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[TribSizeEditable] ) &&
         ( theEdParameters.GetTribSize( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[BurstyBerSdIntervalEditable] ) &&
         ( theEdParameters.GetBurstyBerSdInterval( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[BurstyBerSdThresholdEditable] ) &&
         ( theEdParameters.GetBurstyBerSdThreshold( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[TribFallEditable] ) &&
         ( theEdParameters.GetTribFall( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[GfpTsEditable] ) &&
         ( theEdParameters.GetGfpTs( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[DmSourceEditable] ) &&
         ( theEdParameters.GetDmSource( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

	if ( ( false == myEdParametersSet[LtcActModeEditable] ) &&
         ( theEdParameters.GetLtcActMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[QualityLevelEditable] ) &&
         ( theEdParameters.GetQualityLevel( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[InterPacketGapEditable] ) &&
         ( theEdParameters.GetInterPacketGap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[NpOwnerEditable] ) &&
         ( theEdParameters.GetNpOwner( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }  

    if ( ( false == myEdParametersSet[OpuConfigEditable] ) &&
         ( theEdParameters.GetOpuConfig( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }  

    if ( ( false == myEdParametersSet[ExpOperatorEditable] ) &&
         ( theEdParameters.GetExpOperator( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[TxOperatorEditable] ) &&
         ( theEdParameters.GetTxOperator( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[OTNMapEditable] ) &&
         ( theEdParameters.GetOTNMap( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

    if ( ( false == myEdParametersSet[MapModeEditable] ) &&
         ( theEdParameters.GetMapMode( ) ) )
    {
        throw CT_TL1_IPNVError(CT_TL1_IPNVError::ER_IPNV_PRM_INC);
    }

}
