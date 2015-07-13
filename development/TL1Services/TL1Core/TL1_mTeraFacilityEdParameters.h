/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 30, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 EDIT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MTERAFACILITYEDPARAMETERS_H__
#define __TL1_MTERAFACILITYEDPARAMETERS_H__

#include <vector>
using namespace std;

#include <TL1Core/TL1_Entity.h>
#include <TL1Core/TL1_FacDomain.h>
#include <TL1Core/TL1_AlarmDomain.h>
#include <TL1Core/TL1_FacilityEdParameters.h>
#include <Response/TL1_Response.h>
#include <Response/TL1_FACRspBlk.h>
#include <LumosTypes/LT_System.h>


#define SET_VAL(X, Y) do \
{ \
    if ((Y) != NULL) \
    { \
        X##Val = *(Y); \
        X = &(X##Val); \
    } \
    else \
    { \
        X = NULL; \
    } \
}while(0);

class TL1_mTeraFacilityEdParameters: public TL1_FacilityEdParameters  
{
public:
    
    TL1_mTeraFacilityEdParameters();

    virtual ~TL1_mTeraFacilityEdParameters();

    TL1_mTeraFacilityEdParameters& operator=( const TL1_FacilityEdParameters& theBlock );

    bool operator==( const TL1_mTeraFacilityEdParameters& theBlock ) const;

    inline void                         SetAlarmProfile( CT_ProfileTableId* theAlarmProfile );

    inline void                         SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline void                         SetIsCommandForced( bool* theIsCommandForced );

    inline void                         SetIsProtectionEnabled( CT_FAC_Protection* theIsProtectionEnabled );

    inline void                         SetMaintPropagate( CT_FAC_MaintProp* theMaintProp );

    inline void                         SetIsAdaptiveEnabled( bool* theIsAdaptiveEnabled );

    inline void                         SetMaxRate( CT_TEL_daHz* theMaxRate );

    inline void                         SetExpectedSignalRate( CT_TL1_ExpectedRateRange* theExpectedSignalRate ); 

    inline void                         SetRateList( CT_FAC_SignalRateListType* theRateList );

    inline void                         SetIsOtuMapEnabled( bool* theIsOtuMapEnabled );

    inline void                         SetTrace( CT_Fac_TraceString* theTrace );

    inline void                         SetSentTrace( CT_Fac_TraceString* theSentTrace );

    inline void                         SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace );

    inline void                         SetIsMonitorOtiEnabled( bool* theIsMonitorOtiEnabled );

    inline void                         SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled );

    inline void                         SetIsInsertAisEnabled( bool* theIsInsertAisEnabled );

    inline void                         SetSFThreshold( CT_TEL_BERLevels* theSFThreshold );

    inline void                         SetSDThreshold( CT_TEL_BERLevels* theSFThreshold );

    inline void                         SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConnectivity );

    inline void                         SetSignalType( CT_TEL_SignalType* theSignalType );

    inline void                         SetClkType(CT_TEL_ClkType* theClkType);

    inline void                         SetOTIDStatus(CT_TEL_OTIDStatus* theOTIDStatus);

    inline void                         SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled );

    inline void                         SetIsAutoAdjustOutPowerEnabled( bool* theIsAutoAdjustOutPowerEnabled );

    inline void                         SetIsAutoAdjustInPowerEnabled( bool* theIsAutoAdjustInPowerEnabled );

    inline void                         SetIsAutoTxPowerShutdownEnabled( bool* theIsAutoTxPowerShutdownEnabled );

    inline void                         SetLineCode( CT_FAC_LineCode* theLineCode );

    inline void                         SetFrameFormat( CT_FAC_FrameFormat* theFrameFormat );

    inline void                         SetIsSsmConnected( bool* theIsSsmConnected );

    inline void                         SetConnectedTo( CT_Fac_ConnectedToString* theConnectedTo );

    inline void                         SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap );

    inline void                         SetProtFunc( CT_Fac_TraceString* theProtFunc );

    inline void                         SetGenTrc( bool* theGenTrc );

    inline void                         SetFecType( CT_TEL_FecType* theFecType );

    inline void                         SetSuperFec( CT_TEL_SuperFec* theSuperFec );

    inline void                         SetLOSThreshold( CT_TEL_mBm* theLOSThreshold );

    inline void                         SetSWThreshold( CT_TEL_mBm* theSWThreshold );

    inline void                         SetSignalBand( CT_TEL_OpticalWaveLength* theSignalBand );

    inline void                         SetNendALS( bool* theNendALS );

    inline void                         SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc );

    inline void                         SetAddCrsMap( CT_FAC_StsMap* theAddCrsMap );

    inline void                         SetDelCrsMap( CT_FAC_StsMap* theDelCrsMap );

    inline void                         SetIsEonMsgEnabled( bool* theIsEonMsgEnabled );

    inline void                         SetIsTrafficEnabled( bool* theIsTrafficEnabled );

    inline void                         SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen );

    inline void                         SetTapNumber( CT_TapNumber* theTapNumber ); 

    inline void                         SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled );

    inline void                         SetHandle( LT_Handle* theHandle );

    inline void                         SetPt( CT_TEL_PayloadSignalId* thePt );

    inline void                         SetGfpUpi( CT_TEL_GfpUpiId* theUpi );

    inline void                         SetQuarantine( bool* theQua );

    inline void                         SetCtag( LT_Ctag theCtag );

    inline void                         SetHoldOffProt( int* theHoldOffProt );

    inline void                         SetExtChannel( uint32* theExtChannel);

    inline void                         SetAddCstMap( CT_FAC_StsMap* theAddCstMap );

    inline void                         SetDelCstMap( CT_FAC_StsMap* theDelCstMap );

    inline void                         SetEthRate( CT_TEL_daHz* theEthRate );

    inline void                         SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode );

    inline void                         SetTcmMode( CT_TCM_Mode* theTcmMode );

    inline void                         SetFlowCtrlAd( CT_TEL_MAC_ADFLW_CTRL* theFlowAd );

    inline void                         SetFlowCtrlEnable( CT_TEL_MAC_FLOWCTRL* theFlowCtrl );

    inline void                         SetVLanTag( CT_TEL_VlanTag* theVTag );

    inline void                         SetTagMode( bool* theTagMode );

    inline void                         SetTPid( CT_TEL_Tpid* theTPid );

    inline void                         SetDiscardPause( bool* theDiscardPause );

    inline void                         SetPropFefi( bool* thePropFefi );

    inline void                         SetPmProfile( CT_PMProfileTableId* thePmProfile );

    inline void                         SetCFProfile( int* theCFProfile );

    inline void                  SetCbrMap(CT_TEL_PayloadType* theCbrMap);

    inline void                         SetTribSlot( CT_FAC_OduTsMap* theTribSlot);

    inline void                         SetTribFall(bool* theTribFall);

    inline void                         SetDmSource(bool* theDmSource);

    inline void                         SetGfpTs(uint8* theGfpTs);

    inline void                         SetGfpMux(CT_TEL_GFP_MUX * theGfpMux);

    inline void                         SetQualityLevel( CT_FAC_QualityLevelOverride* theQualityLevel );

    inline void              SetTimDef(CT_TEL_TimCriteriaMode* theTimDef);

    inline void                     SetExpDapi(CT_Fac_TraceString* theExceptedDapi);

    inline void                     SetExpSapi(CT_Fac_TraceString* theExceptedSapi);

    inline void                     SetTxDapi(CT_Fac_TraceString* theTxDapi);

    inline void                     SetTxSapi(CT_Fac_TraceString* theTxSapi);
    
    inline void                         SetOtsChanMap( CT_FAC_OtsChanMap* theOtsChanMap );

    inline void                         SetOtsChanType( CT_FAC_OtsChanType* theOtsChanType );
        
    inline void                         SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation );

    inline void                         SetLacpPriority( int* theLacpPriority );

    inline void                         SetAisType(CT_RS_IndicationType* theAisType);

    inline void                         SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval);

    inline void                         SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold);

    inline void                         SetTribSize( CT_TEL_TS_SIZE* theTribSize );

    inline void                         SetInterPacketGap(uint8* theInterPacketGap);

    inline void                         SetNpOwner( int* theNpOwner );

    inline void                         SetExpOperator( CT_Fac_TraceString* theExpOperator );

    inline void                         SetTxOperator( CT_Fac_TraceString* theTxOperator );

private:

    CT_ProfileTableId               myAlarmProfileVal;
    CT_SM_PST                       myPrimaryStateVal;
    bool                            myIsCommandForcedVal;
    CT_FAC_Protection               myIsProtectionEnabledVal;
    CT_FAC_MaintProp                myMaintPropVal;
    bool                            myIsAdaptiveEnabledVal;
    CT_TEL_daHz                     myMaxRateVal;
    CT_TL1_ExpectedRateRange        myExpectedSignalRateVal;
    CT_FAC_SignalRateListType       myRateListVal;
    bool                            myIsOtuMapEnabledVal;
    CT_Fac_TraceString              myTraceVal;
    CT_Fac_TraceString              mySentTraceVal;
    CT_Fac_TraceString              myExpectedTraceVal;
    bool                            myIsMonitorOtiEnabledVal;
    bool                            myIsMonitorTraceEnabledVal;
    bool                            myIsInsertAisEnabledVal;
    CT_TEL_BERLevels                mySFThresholdVal;
    CT_TEL_BERLevels                mySDThresholdVal;
    CT_FAC_ExternalConnectivity     myExternalConnectivityVal;
    CT_TEL_SignalType               mySignalTypeVal;
    CT_TEL_ClkType                  myClkTypeVal;
    CT_TEL_OTIDStatus               myOTIDStatusVal;
    bool                            myIsAutoAdjustAttenuationEnabledVal;
    bool                            myIsAutoAdjustOutPowerEnabledVal;
    bool                            myIsAutoAdjustInPowerEnabledVal;
    bool                            myIsAutoTxPowerShutdownEnabledVal;
    CT_FAC_LineCode                 myLineCodeVal;                       
    CT_FAC_FrameFormat              myFrameFormatVal;             
    bool                            myIsSsmConnectedVal;
    CT_Fac_ConnectedToString        myConnectedToVal;
    CT_TEL_GfpFramingMode           myGfpMapVal;
    CT_Fac_TraceString              myProtFuncVal;
    bool                            myGenTrcVal;
    CT_TEL_FecType                  myFecTypeVal;
    CT_TEL_SuperFec                 mySuperFecVal;
    CT_TEL_mBm                      myLOSThresholdVal;
    CT_TEL_mBm                      mySWThresholdVal;
    CT_TEL_OpticalWaveLength        mySignalBandVal;
    bool                            myNendALSVal;
    CT_Fac_TraceString              myOtuExpTrcVal;
    CT_FAC_StsMap                   myAddCrsMapVal;
    CT_FAC_StsMap                   myDelCrsMapVal;
    bool                            myIsEonMsgEnabledVal;
    bool                            myIsTrafficEnabledVal;
    CT_TEL_OEO_REGEN_MODE           myOeoRegenVal;
    CT_TapNumber                    myTapNumberVal;
    bool                            myIsAutoNegotiationEnabledVal;
    LT_Handle                       myHandleVal;
    CT_TEL_PayloadSignalId          myPtVal;
    CT_TEL_GfpUpiId                 myGfpUpiVal;
    bool                            myQuaVal;
    string                          myCtagVal;
    int                             myHoldOffProtVal;
    uint32                          myExtChannelVal;
    CT_FAC_StsMap                   myAddCstMapVal;
    CT_FAC_StsMap                   myDelCstMapVal;
    CT_TEL_daHz                     myEthRateVal;
    CT_TEL_MAC_DUPLEX_MODE          myDuplexModeVal;
    CT_TCM_Mode                     myTcmModeVal;
    CT_TEL_MAC_ADFLW_CTRL           myFlowAdVal;
    CT_TEL_MAC_FLOWCTRL             myFlowCtrlVal;
    CT_TEL_VlanTag                  myVlanTagVal;
    bool                            myTagModeVal;
    CT_TEL_Tpid                     myTpidVal;
    bool                            myDiscardPauseVal;
    bool                            myPropFefiVal;
    CT_PMProfileTableId             myPmProfileVal;
    int                             myCFProfileVal;
    CT_TEL_PayloadType              myCbrMapVal;
    CT_TL1_FacParamAddr             myAdjacnetVal;
    CT_FAC_OduTsMap                 myTribSlotVal;
    CT_TEL_GFP_MUX                  myGfpMuxVal;
    CT_TEL_TimCriteriaMode          myTimDefVal;
    CT_Fac_TraceString              myExpDapiVal;
    CT_Fac_TraceString              myExpSapiVal;
    CT_Fac_TraceString              myTxDapiVal;
    CT_Fac_TraceString              myTxSapiVal;
    CT_FAC_OtsChanMap               myOtsChanMapVal;
    CT_FAC_OtsChanType              myOtsChanTypeVal;
    CT_TEL_LacpPartiMode            myLacpParticipationVal;
    int                             myLacpPriorityVal;
    CT_RS_IndicationType            myAisTypeVal;
    uint16                          myBurstyBerSdIntervalVal;
    uint32                          myBurstyBerSdThresholdVal;
    CT_TEL_TS_SIZE                  myTribSizeVal;
    bool                            myTribFallVal;
    uint8                           myGfpTsVal;
    uint8                           myInterPacketGapVal;
    bool                            myDmSourceVal;
	CT_FAC_QualityLevelOverride     myQualityLevelVal;
    int                             myNpOwnerVal;
    CT_Fac_TraceString              myExpOperatorVal;
    CT_Fac_TraceString              myTxOperatorVal;
    
};

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetAlarmProfile( CT_ProfileTableId* theAlarmProfile )
{
    SET_VAL(myAlarmProfile, theAlarmProfile);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    SET_VAL(myPrimaryState, thePrimaryState);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    SET_VAL(myIsCommandForced, theIsCommandForced);
}

//--------------------------------------------------------------------------------
inline void                         
TL1_mTeraFacilityEdParameters::SetIsProtectionEnabled( CT_FAC_Protection* theIsProtectionEnabled )
{
    SET_VAL(myIsProtectionEnabled, theIsProtectionEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetMaintPropagate( CT_FAC_MaintProp* theMaintProp )
{
    SET_VAL(myMaintProp, theMaintProp);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsAdaptiveEnabled( bool* theIsAdaptiveEnabled )
{
    SET_VAL(myIsAdaptiveEnabled, theIsAdaptiveEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetMaxRate( CT_TEL_daHz* theMaxRate )
{
    SET_VAL(myMaxRate, theMaxRate);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetExpectedSignalRate( CT_TL1_ExpectedRateRange* theExpectedSignalRate ) 
{
    SET_VAL(myExpectedSignalRate, theExpectedSignalRate);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetRateList( CT_FAC_SignalRateListType* theRateList )
{
    SET_VAL(myRateList, theRateList);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsOtuMapEnabled( bool* theIsOtuMapEnabled )
{
    SET_VAL(myIsOtuMapEnabled, theIsOtuMapEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetTrace( CT_Fac_TraceString* theTrace )
{
    SET_VAL(myTrace, theTrace);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetSentTrace( CT_Fac_TraceString* theSentTrace )
{
    SET_VAL(mySentTrace, theSentTrace);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace )
{
    SET_VAL(myExpectedTrace, theExpectedTrace);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsMonitorOtiEnabled( bool* theIsMonitorOtiEnabled )
{
    SET_VAL(myIsMonitorOtiEnabled, theIsMonitorOtiEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled )
{
    SET_VAL(myIsMonitorTraceEnabled, theIsMonitorTraceEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsInsertAisEnabled( bool* theIsInsertAisEnabled )
{
    SET_VAL(myIsInsertAisEnabled, theIsInsertAisEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetSFThreshold( CT_TEL_BERLevels* theSFThreshold )
{
    SET_VAL(mySFThreshold, theSFThreshold);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetSDThreshold( CT_TEL_BERLevels* theSDThreshold )
{
    SET_VAL(mySDThreshold, theSDThreshold);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConnectivity )
{
    SET_VAL(myExternalConnectivity, theExternalConnectivity);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetSignalType( CT_TEL_SignalType* theSignalType )
{
    SET_VAL(mySignalType, theSignalType);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetClkType( CT_TEL_ClkType* theClkType ) 
{
    SET_VAL(myClkType, theClkType);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetOTIDStatus( CT_TEL_OTIDStatus* theOTIDStatus ) 
{
    SET_VAL(myOTIDStatus, theOTIDStatus);
}
//--------------------------------------------------------------------------------


inline void                         
TL1_mTeraFacilityEdParameters::SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled )
{
    SET_VAL(myIsAutoAdjustAttenuationEnabled, theIsAutoAdjustAttenuationEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsAutoAdjustOutPowerEnabled( bool* theIsAutoAdjustOutPowerEnabled )
{
    SET_VAL(myIsAutoAdjustOutPowerEnabled, theIsAutoAdjustOutPowerEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsAutoAdjustInPowerEnabled( bool* theIsAutoAdjustInPowerEnabled )
{   
    SET_VAL(myIsAutoAdjustInPowerEnabled, theIsAutoAdjustInPowerEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsAutoTxPowerShutdownEnabled( bool* theIsAutoTxPowerShutdownEnabled )
{
    SET_VAL(myIsAutoTxPowerShutdownEnabled, theIsAutoTxPowerShutdownEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetLineCode( CT_FAC_LineCode* theLineCode )
{
    SET_VAL(myLineCode, theLineCode);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetFrameFormat( CT_FAC_FrameFormat* theFrameFormat )
{
    SET_VAL(myFrameFormat, theFrameFormat);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsSsmConnected( bool* theIsSsmConnected )
{
    SET_VAL(myIsSsmConnected, theIsSsmConnected);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetConnectedTo( CT_Fac_ConnectedToString* theConnectedTo )
{
    SET_VAL(myConnectedTo, theConnectedTo);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap )
{
    SET_VAL(myGfpMap, theGfpMap);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetProtFunc( CT_Fac_TraceString* theProtFunc )
{
    SET_VAL(myProtFunc, theProtFunc);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetGenTrc( bool* theGenTrc )
{
    SET_VAL(myGenTrc, theGenTrc);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetFecType( CT_TEL_FecType* theFecType )
{
    SET_VAL(myFecType, theFecType);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetSuperFec( CT_TEL_SuperFec* theSuperFec )
{
    SET_VAL(mySuperFec, theSuperFec);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetLOSThreshold( CT_TEL_mBm* theLOSThreshold )
{
    SET_VAL(myLOSThreshold, theLOSThreshold);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetSWThreshold( CT_TEL_mBm* theSWThreshold )
{
    SET_VAL(mySWThreshold, theSWThreshold);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetSignalBand( CT_TEL_OpticalWaveLength* theSignalBand )
{
    SET_VAL(mySignalBand, theSignalBand);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetNendALS( bool* theNendALS )
{
    SET_VAL(myNendALS, theNendALS);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc )
{
    SET_VAL(myOtuExpTrc, theOtuExpTrc);
}
//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEdParameters::SetAddCrsMap( CT_FAC_StsMap* theAddCrsMap )
{
    SET_VAL(myAddCrsMap, theAddCrsMap);
}
//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEdParameters::SetDelCrsMap( CT_FAC_StsMap* theDelCrsMap )
{
    SET_VAL(myDelCrsMap, theDelCrsMap);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsEonMsgEnabled( bool* theIsEonMsgEnabled )
{
    SET_VAL(myIsEonMsgEnabled, theIsEonMsgEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsTrafficEnabled( bool* theIsTrafficEnabled )
{
    SET_VAL(myIsTrafficEnabled, theIsTrafficEnabled);
}

//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEdParameters::SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen )
{
    SET_VAL(myOeoRegen, theOeoRegen);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetTapNumber( CT_TapNumber* theTapNumber)
{
    SET_VAL(myTapNumber, theTapNumber);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled )
{
    SET_VAL(myIsAutoNegotiationEnabled, theIsAutoNegotiationEnabled);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetHandle( LT_Handle* theHandle )
{
    SET_VAL(myHandle, theHandle);
}
//--------------------------------------------------------------------------------
inline void                         
TL1_mTeraFacilityEdParameters::SetCtag( LT_Ctag theCtag )
{
    if (theCtag != NULL)
    {
        myCtagVal = string(theCtag);
        myCtag = (LT_Ctag)myCtagVal.c_str();
    }
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetHoldOffProt( int* theHoldOffProt )
{
    SET_VAL(myHoldOffProt, theHoldOffProt);

}

inline void                         
TL1_mTeraFacilityEdParameters::SetPt( CT_TEL_PayloadSignalId* thePt )
{
    SET_VAL(myPt, thePt);
}


inline void                         
TL1_mTeraFacilityEdParameters::SetGfpUpi( CT_TEL_GfpUpiId* theUpi )
{
    SET_VAL(myGfpUpi, theUpi);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetQuarantine( bool* theQua )
{
    SET_VAL(myQua, theQua);
}

inline void
TL1_mTeraFacilityEdParameters::SetAddCstMap( CT_FAC_StsMap* theAddCstMap )
{
    SET_VAL(myAddCstMap, theAddCstMap);
}
//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEdParameters::SetDelCstMap( CT_FAC_StsMap* theDelCstMap )
{
    SET_VAL(myDelCstMap, theDelCstMap);
}

inline void
TL1_mTeraFacilityEdParameters::SetEthRate( CT_TEL_daHz* theEthRate )
{
    SET_VAL(myEthRate, theEthRate);
}

//--------------------------------------------------------------------------------
inline void
TL1_mTeraFacilityEdParameters::SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode )
{
    SET_VAL(myDuplexMode, theDuplexMode);
}

//--------------------------------------------------------------------------------
inline void
TL1_mTeraFacilityEdParameters::SetTcmMode( CT_TCM_Mode* theTcmMode )
{
    SET_VAL(myTcmMode, theTcmMode);
}

//--------------------------------------------------------------------------------
inline void
TL1_mTeraFacilityEdParameters::SetFlowCtrlAd( CT_TEL_MAC_ADFLW_CTRL* theFlowAd )
{
    SET_VAL(myFlowAd, theFlowAd);
}

//--------------------------------------------------------------------------------
inline void
TL1_mTeraFacilityEdParameters::SetFlowCtrlEnable( CT_TEL_MAC_FLOWCTRL* theFlowCtrl )
{
    SET_VAL(myFlowCtrl, theFlowCtrl);
}
//-------------------------------------------------------------------------------
inline void
TL1_mTeraFacilityEdParameters::SetVLanTag( CT_TEL_VlanTag* theVTag )
{
    SET_VAL(myVlanTag, theVTag);
}
//-------------------------------------------------------------------------------
inline void
TL1_mTeraFacilityEdParameters::SetTagMode( bool* theTagMode )
{
    SET_VAL(myTagMode, theTagMode);
}
//-------------------------------------------------------------------------------
inline void
TL1_mTeraFacilityEdParameters::SetTPid( CT_TEL_Tpid* theTPid )
{
    SET_VAL(myTpid, theTPid);
}


//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetDiscardPause( bool* theDiscardPause )
{
    SET_VAL(myDiscardPause, theDiscardPause);
}


//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetPropFefi( bool* thePropFefi )
{
    SET_VAL(myPropFefi, thePropFefi);
}


//--------------------------------------------------------------------------------


inline void                         
TL1_mTeraFacilityEdParameters::SetExtChannel(uint32* theExtChannel)
{
    SET_VAL(myExtChannel, theExtChannel);
}

//--------------------------------------------------------------------------------
inline void                         
TL1_mTeraFacilityEdParameters::SetPmProfile( CT_PMProfileTableId* thePmProfile )
{
    SET_VAL(myPmProfile, thePmProfile);
}

//--------------------------------------------------------------------------------
inline void                         
TL1_mTeraFacilityEdParameters::SetCFProfile( int* theCFProfile )
{
    SET_VAL(myCFProfile, theCFProfile);
}

inline void 
TL1_mTeraFacilityEdParameters::SetCbrMap(CT_TEL_PayloadType * theCbrMap)
{
    SET_VAL(myCbrMap, theCbrMap);
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEdParameters::SetTribSlot( CT_FAC_OduTsMap* theTribSlot)
{
    SET_VAL(myTribSlot, theTribSlot);
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEdParameters::SetTribFall( bool* theTribFall)
{
    SET_VAL(myTribFall, theTribFall);
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEdParameters::SetDmSource( bool* theDmSource)
{
    SET_VAL(myDmSource, theDmSource);
}
//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEdParameters::SetGfpTs( uint8* theGfpTs)
{
    SET_VAL(myGfpTs, theGfpTs);
}
//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEdParameters::SetInterPacketGap( uint8* theInterPacketGap)
{
    SET_VAL(myInterPacketGap, theInterPacketGap);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetQualityLevel( CT_FAC_QualityLevelOverride* theQualityLevel )
{
    SET_VAL(myQualityLevel, theQualityLevel);
}

//--------------------------------------------------------------------------------
inline void 
TL1_mTeraFacilityEdParameters::SetGfpMux(CT_TEL_GFP_MUX * theGfpMux)
{
    SET_VAL(myGfpMux, theGfpMux);
}

inline void 
TL1_mTeraFacilityEdParameters::SetTimDef(CT_TEL_TimCriteriaMode * theTimDef)
{
    SET_VAL(myTimDef, theTimDef);
}

inline void 
TL1_mTeraFacilityEdParameters::SetExpDapi(CT_Fac_TraceString * theExpDapi)
{
    SET_VAL(myExpDapi, theExpDapi);
}

inline void 
TL1_mTeraFacilityEdParameters::SetExpSapi(CT_Fac_TraceString * theExpSapi)
{
    SET_VAL(myExpSapi, theExpSapi);
}

inline void 
TL1_mTeraFacilityEdParameters::SetTxDapi(CT_Fac_TraceString * theTxDapi)
{
    SET_VAL(myTxDapi, theTxDapi);
}

inline void 
TL1_mTeraFacilityEdParameters::SetTxSapi(CT_Fac_TraceString * theTxSapi)
{
    SET_VAL(myTxSapi, theTxSapi);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetOtsChanMap( CT_FAC_OtsChanMap* theOtsChanMap )
{
    SET_VAL(myOtsChanMap, theOtsChanMap);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetOtsChanType( CT_FAC_OtsChanType* theOtsChanType )
{
    SET_VAL(myOtsChanType, theOtsChanType);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEdParameters::SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation )
{
    SET_VAL(myLacpParticipation, theLacpParticipation);
}

//--------------------------------------------------------------------------------
inline void                         
TL1_mTeraFacilityEdParameters::SetLacpPriority( int* theLacpPriority )
{
    SET_VAL(myLacpPriority, theLacpPriority);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetAisType(CT_RS_IndicationType* theAisType)
{
    SET_VAL(myAisType, theAisType);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval)
{
    SET_VAL(myBurstyBerSdInterval, theBurstyBerSdInterval);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold)
{
    SET_VAL(myBurstyBerSdThreshold, theBurstyBerSdThreshold);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetTribSize( CT_TEL_TS_SIZE* theTribSize )
{
    SET_VAL(myTribSize, theTribSize);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetNpOwner( int* theNpOwner )
{
    SET_VAL(myNpOwner, theNpOwner);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetExpOperator( CT_Fac_TraceString* theExpOperator )
{
    SET_VAL(myExpOperator, theExpOperator);
}

inline void                         
TL1_mTeraFacilityEdParameters::SetTxOperator( CT_Fac_TraceString* theTxOperator )
{
    SET_VAL(myTxOperator, theTxOperator);
}

#endif
