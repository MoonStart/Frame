/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 16, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 ENTER Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MTERAFACILITYENTPARAMETERS_H__
#define __TL1_MTERAFACILITYENTPARAMETERS_H__

#include <vector>
using namespace std;

#include <TL1Core/TL1_Entity.h>
#include <TL1Core/TL1_FacDomain.h>
#include <TL1Core/TL1_AlarmDomain.h>
#include <TL1Core/TL1_FacilityEntParameters.h>
#include <Response/TL1_Response.h>
#include <Response/TL1_FACRspBlk.h>

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

class TL1_mTeraFacilityEntParameters : public TL1_FacilityEntParameters
{
public:
    
    TL1_mTeraFacilityEntParameters();

    virtual ~TL1_mTeraFacilityEntParameters();

    TL1_mTeraFacilityEntParameters& operator=( const TL1_FacilityEntParameters& theBlock );

    inline void                         SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile );

    inline void                         SetTrace( CT_Fac_TraceString* theTrace );

    inline void                         SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace );

    inline void                         SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled );

    inline void                         SetIsInsertAisEnabled( bool* theIsInsertAisEnabled );

    inline void                         SetMapping( CT_TEL_HopSpeMapping* theMapping );

    inline void                         SetSFThreshold( CT_TEL_BERLevels* theSFThreshold );
 
    inline void                         SetSDThreshold( CT_TEL_BERLevels* theSDThreshold ); 

    inline void                         SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConnectivity ); 

    inline void                         SetIsProtectionEnabled( CT_FAC_Protection* theIsProtectionEnabled );

    inline void                         SetMaintPropagate( CT_FAC_MaintProp* theMaintProp );

    inline void                         SetIsAdaptiveEnabled( bool* theIsAdaptiveEnabled );

    inline void                         SetMaxRate( CT_TEL_daHz* theMaxRate ); 

    inline void                         SetExpectedSignalRate( CT_TL1_ExpectedRateRange* theExpectedSignalRate ); 

    inline void                         SetRateList( CT_FAC_SignalRateListType* theRateList );

    inline void                         SetSignalType( CT_TEL_SignalType* theSignalType );

    inline void                         SetStsMap( CT_FAC_StsMap* theStsMap ); 

    inline void                         SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline void                         SetLineCode( CT_FAC_LineCode* theLineCode );

    inline void                         SetSignalFrameFormat( CT_FAC_FrameFormat* theSignalFrameFormat ); 

    inline void                         SetIsTransparent( bool* theIsTransparent );

    inline void                         SetIsSsmConnected( bool* theIsSsmConnected ); 

    inline void                         SetConnectedTo( CT_Fac_ConnectedToString* theConectedTo ); 

    inline void                         SetGbeFramingMode( CT_TEL_GbeFramingMode* theGbeFramingMode ); 

    inline void                         SetGenTrc( bool* theGenTrc ); 

    inline void                         SetIsTrafficEnabled( bool* theIsTrafficEnabled ); 

    inline void                         SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap ); 

    inline void                         SetNendALS( bool* theNendALS ); 

    inline void                         SetNValue( CT_FAC_NValue* theNValue ); 

    inline void                         SetFecType( CT_TEL_FecType* theFecType ); 

    inline void                         SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc ); 

    inline void                         SetOtuTrc( CT_Fac_TraceString* theOtuTrc ); 

    inline void                         SetTransMap( CT_TEL_SignalType* theTransMap ); 

    inline void                         SetClkType( CT_TEL_SignalType* theClkType ); 

    inline void                         SetTapNumber( CT_TapNumber* theTapNumber ); 

    inline void                         SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled );

    inline void                         SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen );

    inline void                         SetCnvTermType( CT_TEL_TermSize* theCnvTermType );
    
    inline void                         SetPt( CT_TEL_PayloadSignalId* thePt );

    inline void                         SetGfpUpi( CT_TEL_GfpUpiId* theUpi );

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

    inline void                         SetHandle( LT_Handle* theHandle );

    inline void                         SetCtag( LT_Ctag theCtag );

    inline void                         SetPmProfile(  CT_PMProfileTableId* thePmProfile );

    inline void                         SetCFProfile(  int* theCFProfile );

    inline void                  SetCbrMap(CT_TEL_PayloadType* theCbrMap);

    inline void                         SetAdjacent( CT_TCM_ADJACENT* theAdjacentBuf );

    inline void                         SetTribSlot(CT_FAC_OduTsMap* theTribSlot);

    inline void                         SetTribFall(bool* theTribFall);

    inline void                         SetDmSource(bool* theDmSource);

    inline void                         SetGfpTs(uint8* theGfpTs);

    inline void                         SetGfpMux(CT_TEL_GFP_MUX * theGfpMux);

    inline void                         SetQualityLevel(CT_FAC_QualityLevelOverride* theQualityLevel);

    inline void              SetTimDef(CT_TEL_TimCriteriaMode* theTimDef);

    inline void                     SetExpDapi(CT_Fac_TraceString* theExceptedDapi);

    inline void                     SetExpSapi(CT_Fac_TraceString* theExceptedSapi);

    inline void                     SetTxDapi(CT_Fac_TraceString * theTxDapi);

    inline void                     SetTxSapi(CT_Fac_TraceString * theTxSapi);
    
    inline void                         SetExtChannel(uint32* theExtChannel);

    inline void                         SetOTIDStatus(CT_TEL_OTIDStatus* theOTIDStatus);

    inline void                         SetHoldOffProt( int* theHoldOffProt );

    inline void                         SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation );

    inline void                         SetLacpPriority( int* theLacpPriority );

    inline void                         SetAisType(CT_RS_IndicationType* theAisType);

    inline void                         SetTribSize( CT_TEL_TS_SIZE* theTribSize );

    inline void                         SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval);

    inline void                         SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold);

    inline void                         SetInterPacketGap(uint8* theInterPacketGap);

    inline void                         SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled );

    inline void                         SetExpOperator( CT_Fac_TraceString* theExpOperator );

    inline void                         SetTxOperator( CT_Fac_TraceString* theTxOperator );

private:
    CT_ProfileTableId             myAlarmProfileVal;
    CT_Fac_TraceString            myTraceVal;
    CT_Fac_TraceString            myExpectedTraceVal;
    bool                          myIsMonitorTraceEnabledVal;
    bool                          myIsInsertAisEnabledVal;
    CT_TEL_HopSpeMapping          myMappingVal;
    CT_TEL_BERLevels              mySFThresholdVal;
    CT_TEL_BERLevels              mySDThresholdVal;
    CT_FAC_ExternalConnectivity   myExternalConectivityVal;
    CT_FAC_Protection             myIsProtectionEnabledVal;
    CT_FAC_MaintProp              myMaintPropVal;
    bool                          myIsAdaptiveEnabledVal;
    CT_TEL_daHz                   myMaxRateVal;
    CT_TL1_ExpectedRateRange      myExpectedSignalRateVal;
    CT_FAC_SignalRateListType     myRateListVal;
    CT_TEL_SignalType             mySignalTypeVal;
    CT_FAC_StsMap                 myStsMapVal;
    CT_SM_PST                     myPrimaryStateVal;
    CT_FAC_LineCode               myLineCodeVal;           
    CT_FAC_FrameFormat            mySignalFrameFormatVal;
    bool                          myIsTransparentVal;
    bool                          myIsSsmConnectedVal;
    CT_Fac_ConnectedToString      myConectedToVal;
    CT_TEL_GbeFramingMode         myGbeFramingModeVal;
    bool                          myGenTrcVal;
    bool                          myIsTrafficEnabledVal;
    CT_TEL_GfpFramingMode         myGfpMapVal;
    bool                          myNendALSVal;
    CT_FAC_NValue                 myNValueVal;
    CT_TEL_FecType                myFecTypeVal;     
    CT_Fac_TraceString            myOtuExpTrcVal;
    CT_Fac_TraceString            myOtuTrcVal; 
    CT_TEL_SignalType             myTransMapVal;
    CT_TEL_SignalType             myClkTypeVal;
    CT_TapNumber                  myTapNumberVal;
    bool                          myIsAutoNegotiationEnabledVal;
    CT_TEL_OEO_REGEN_MODE         myOeoRegenVal;
    CT_TEL_TermSize               myCnvTermTypeVal;
    CT_TEL_PayloadSignalId        myPtVal;
    CT_TEL_PayloadSignalId        myGfpUpiVal;
    CT_TEL_daHz                   myEthRateVal;
    CT_TEL_MAC_DUPLEX_MODE        myDuplexModeVal;
    CT_TCM_Mode                   myTcmModeVal;
    CT_TEL_MAC_ADFLW_CTRL         myFlowAdVal;
    CT_TEL_MAC_FLOWCTRL           myFlowCtrlVal;
    CT_TEL_VlanTag                myVlanTagVal;
    bool                          myTagModeVal;
    CT_TEL_Tpid                   myTpidVal;
    bool                          myDiscardPauseVal;
    bool                          myPropFefiVal;
    LT_Handle                     myHandleVal;
    string                        myCtagVal;
    CT_PMProfileTableId           myPmProfileVal;
    int                           myCFProfileVal;
    CT_TEL_PayloadType            myCbrMapVal;
    CT_TCM_ADJACENT               myAdjacentVal;
    CT_FAC_OduTsMap               myTribSlotVal;
    CT_TEL_GFP_MUX                myGfpMuxVal;
    uint32                        myExtChannelVal;
    CT_TEL_OTIDStatus             myOTIDStatusVal;
    int                           myHoldOffProtVal;
    CT_TEL_TimCriteriaMode        myTimDefVal;
    CT_Fac_TraceString            myExpDapiVal;
    CT_Fac_TraceString            myExpSapiVal;
    CT_Fac_TraceString            myTxDapiVal;
    CT_Fac_TraceString            myTxSapiVal;
    CT_TEL_LacpPartiMode          myLacpParticipationVal;
    int                           myLacpPriorityVal;
    CT_RS_IndicationType          myAisTypeVal;
    CT_TEL_TS_SIZE                myTribSizeVal;
    uint16                        myBurstyBerSdIntervalVal;
    uint32                        myBurstyBerSdThresholdVal;
    bool                          myTribFallVal;
    uint8                         myGfpTsVal;
    uint8                         myInterPacketGapVal;
    bool                          myDmSourceVal;
    CT_FAC_QualityLevelOverride   myQualityLevelVal;   // Tx SSM forcing
    bool                          myIsAutoAdjustAttenuationEnabledVal;
    CT_Fac_TraceString            myExpOperatorVal; 
    CT_Fac_TraceString            myTxOperatorVal; 
};

inline void                         
TL1_mTeraFacilityEntParameters::SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile )
{
    SET_VAL(myAlarmProfile, theAlarmProfile);
}

inline void                         
TL1_mTeraFacilityEntParameters::SetTrace( CT_Fac_TraceString* theTrace )
{
    SET_VAL(myTrace, theTrace);
}

inline void                         
TL1_mTeraFacilityEntParameters::SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace )
{
    SET_VAL(myExpectedTrace, theExpectedTrace);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled )
{
    SET_VAL(myIsMonitorTraceEnabled, theIsMonitorTraceEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsInsertAisEnabled( bool* theIsInsertAisEnabled )
{
    SET_VAL(myIsInsertAisEnabled, theIsInsertAisEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetMapping( CT_TEL_HopSpeMapping* theMapping )
{
    SET_VAL(myMapping, theMapping);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetSFThreshold( CT_TEL_BERLevels* theSFThreshold )
{
    SET_VAL(mySFThreshold, theSFThreshold);
}
//-------------------------------------------------------------------------------- 

inline void                         
TL1_mTeraFacilityEntParameters::SetSDThreshold( CT_TEL_BERLevels* theSDThreshold ) 
{
    SET_VAL(mySDThreshold, theSDThreshold);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConectivity ) 
{
    SET_VAL(myExternalConectivity, theExternalConectivity);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsProtectionEnabled( CT_FAC_Protection* theIsProtectionEnabled )
{
    SET_VAL(myIsProtectionEnabled, theIsProtectionEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetMaintPropagate( CT_FAC_MaintProp* theMaintProp )
{
    SET_VAL(myMaintProp, theMaintProp);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsAdaptiveEnabled( bool* theIsAdaptiveEnabled )
{
    SET_VAL(myIsAdaptiveEnabled, theIsAdaptiveEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetMaxRate( CT_TEL_daHz* theMaxRate ) 
{
    SET_VAL(myMaxRate, theMaxRate);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetExpectedSignalRate( CT_TL1_ExpectedRateRange* theExpectedSignalRate ) 
{
    SET_VAL(myExpectedSignalRate, theExpectedSignalRate);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetRateList( CT_FAC_SignalRateListType* theRateList )
{
    SET_VAL(myRateList, theRateList);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetSignalType( CT_TEL_SignalType* theSignalType )
{
    SET_VAL(mySignalType, theSignalType);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetStsMap( CT_FAC_StsMap* theStsMap ) 
{
    SET_VAL(myStsMap, theStsMap);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    SET_VAL(myPrimaryState, thePrimaryState);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetLineCode( CT_FAC_LineCode* theLineCode )
{
    SET_VAL(myLineCode, theLineCode);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetSignalFrameFormat( CT_FAC_FrameFormat* theSignalFrameFormat ) 
{
    SET_VAL(mySignalFrameFormat, theSignalFrameFormat);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsTransparent( bool* theIsTransparent )
{
    SET_VAL(myIsTransparent, theIsTransparent);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsSsmConnected( bool* theIsSsmConnected ) 
{
    SET_VAL(myIsSsmConnected, theIsSsmConnected);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetConnectedTo( CT_Fac_ConnectedToString* theConectedTo ) 
{
    SET_VAL(myConectedTo, theConectedTo);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetGbeFramingMode( CT_TEL_GbeFramingMode* theGbeFramingMode ) 
{
    SET_VAL(myGbeFramingMode, theGbeFramingMode);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetGenTrc( bool* theGenTrc ) 
{
    SET_VAL(myGenTrc, theGenTrc);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsTrafficEnabled( bool* theIsTrafficEnabled ) 
{
    SET_VAL(myIsTrafficEnabled, theIsTrafficEnabled);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap ) 
{
    SET_VAL(myGfpMap, theGfpMap);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetNendALS( bool* theNendALS ) 
{
    SET_VAL(myNendALS, theNendALS);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetNValue( CT_FAC_NValue* theNValue ) 
{
    SET_VAL(myNValue, theNValue);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetFecType( CT_TEL_FecType* theFecType ) 
{
    SET_VAL(myFecType, theFecType);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc ) 
{
    SET_VAL(myOtuExpTrc, theOtuExpTrc);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetOtuTrc( CT_Fac_TraceString* theOtuTrc ) 
{
    SET_VAL(myOtuTrc, theOtuTrc);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetTransMap( CT_TEL_SignalType* theTransMap ) 
{
    SET_VAL(myTransMap, theTransMap);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetClkType( CT_TEL_SignalType* theClkType ) 
{
    SET_VAL(myClkType, theClkType);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetTapNumber( CT_TapNumber* theTapNumber ) 
{
    SET_VAL(myTapNumber, theTapNumber);
}

//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEntParameters::SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled )
{
    SET_VAL(myIsAutoNegotiationEnabled, theIsAutoNegotiationEnabled);
}

//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEntParameters::SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen )
{
    SET_VAL(myOeoRegen, theOeoRegen);
}

//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEntParameters::SetCnvTermType( CT_TEL_TermSize* theCnvTermType )
{
    SET_VAL(myCnvTermType, theCnvTermType);
}

//---------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetHandle( LT_Handle* theHandle )
{
    SET_VAL(myHandle, theHandle);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetCtag( LT_Ctag theCtag )
{
    if (theCtag != NULL)
    {
        myCtagVal = string(theCtag);
        myCtag = (LT_Ctag)myCtagVal.c_str();
    }
}
//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEntParameters::SetPt( CT_TEL_PayloadSignalId* thePt )
{
    SET_VAL(myPt, thePt);
}

//--------------------------------------------------------------------------------

inline void
TL1_mTeraFacilityEntParameters::SetGfpUpi( CT_TEL_GfpUpiId* theUpi )
{
    SET_VAL(myGfpUpi, theUpi);
}

inline void
TL1_mTeraFacilityEntParameters::SetEthRate( CT_TEL_daHz* theEthRate )
{
    SET_VAL(myEthRate, theEthRate);
}

inline void
TL1_mTeraFacilityEntParameters::SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode )
{
    SET_VAL(myDuplexMode, theDuplexMode);
}

inline void
TL1_mTeraFacilityEntParameters::SetTcmMode( CT_TCM_Mode* theTcmMode )
{
    SET_VAL(myTcmMode, theTcmMode);
}

inline void
TL1_mTeraFacilityEntParameters::SetFlowCtrlAd( CT_TEL_MAC_ADFLW_CTRL* theFlowAd )
{
    SET_VAL(myFlowAd, theFlowAd);
}

inline void
TL1_mTeraFacilityEntParameters::SetFlowCtrlEnable( CT_TEL_MAC_FLOWCTRL* theFlowCtrl )
{
    SET_VAL(myFlowCtrl, theFlowCtrl);
}
inline void
TL1_mTeraFacilityEntParameters::SetVLanTag( CT_TEL_VlanTag* theVTag )
{
    SET_VAL(myVlanTag, theVTag);
}
inline void
TL1_mTeraFacilityEntParameters::SetTagMode( bool* theTagMode )
{
    SET_VAL(myTagMode, theTagMode);
}
inline void
TL1_mTeraFacilityEntParameters::SetTPid( CT_TEL_Tpid* theTPid )
{
    SET_VAL(myTpid, theTPid);
}

inline void                         
TL1_mTeraFacilityEntParameters::SetDiscardPause( bool* theDiscardPause ) 
{
    SET_VAL(myDiscardPause, theDiscardPause);
}


inline void                         
TL1_mTeraFacilityEntParameters::SetPropFefi( bool* thePropFefi ) 
{
    SET_VAL(myPropFefi, thePropFefi);
}


//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetPmProfile(  CT_PMProfileTableId* thePmProfile )
{
    SET_VAL(myPmProfile, thePmProfile);
}

inline void                         
TL1_mTeraFacilityEntParameters::SetCFProfile(  int* theCFProfile )
{
    SET_VAL(myCFProfile, theCFProfile);
}

inline void 
TL1_mTeraFacilityEntParameters::SetCbrMap(CT_TEL_PayloadType * theCbrMap)
{
    SET_VAL(myCbrMap, theCbrMap);
}

//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEntParameters::SetAdjacent(CT_TCM_ADJACENT* theAdjacentBuf )
{
    SET_VAL(myAdjacent, theAdjacentBuf);
}

//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEntParameters::SetTribSlot(CT_FAC_OduTsMap* theTribSlot)
{
    SET_VAL(myTribSlot, theTribSlot);
}

inline void               TL1_mTeraFacilityEntParameters::SetTribFall(bool* theTribFall)
{
    SET_VAL(myTribFall, theTribFall);
}
//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEntParameters::SetDmSource(bool* theDmSource)
{
    SET_VAL(myDmSource, theDmSource);
}
//--------------------------------------------------------------------------------
inline void               TL1_mTeraFacilityEntParameters::SetGfpTs(uint8* theGfpTs)
{
    SET_VAL(myGfpTs, theGfpTs);
}
inline void               TL1_mTeraFacilityEntParameters::SetInterPacketGap(uint8* theInterPacketGap)
{
    SET_VAL(myInterPacketGap, theInterPacketGap);
}
//--------------------------------------------------------------------------------


inline void 
TL1_mTeraFacilityEntParameters::SetGfpMux(CT_TEL_GFP_MUX * theGfpMux)
{
    SET_VAL(myGfpMux, theGfpMux);
}

inline void                         
TL1_mTeraFacilityEntParameters::SetQualityLevel( CT_FAC_QualityLevelOverride* theQualityLevel )
{
    SET_VAL(myQualityLevel, theQualityLevel);
}

inline void 
TL1_mTeraFacilityEntParameters::SetTimDef(CT_TEL_TimCriteriaMode * theTimDef)
{
    SET_VAL(myTimDef, theTimDef);
}

inline void 
TL1_mTeraFacilityEntParameters::SetExpDapi(CT_Fac_TraceString * theExpDapi)
{
    SET_VAL(myExpDapi, theExpDapi);
}

inline void 
TL1_mTeraFacilityEntParameters::SetExpSapi(CT_Fac_TraceString * theExpSapi)
{
    SET_VAL(myExpSapi, theExpSapi);
}

inline void 
TL1_mTeraFacilityEntParameters::SetTxDapi(CT_Fac_TraceString * theTxDapi)
{
    SET_VAL(myTxDapi, theTxDapi);
}

inline void 
TL1_mTeraFacilityEntParameters::SetTxSapi(CT_Fac_TraceString * theTxSapi)
{
    SET_VAL(myTxSapi, theTxSapi);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetExtChannel(uint32* theExtChannel)
{
    SET_VAL(myExtChannel, theExtChannel);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetOTIDStatus( CT_TEL_OTIDStatus* theOTIDStatus ) 
{
    SET_VAL(myOTIDStatus, theOTIDStatus);
}
//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetHoldOffProt( int* theHoldOffProt )
{
    SET_VAL(myHoldOffProt, theHoldOffProt);

}


inline void                         
TL1_mTeraFacilityEntParameters::SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation )
{
    SET_VAL(myLacpParticipation, theLacpParticipation);
}



inline void                         
TL1_mTeraFacilityEntParameters::SetLacpPriority( int* theLacpPriority )
{
    SET_VAL(myLacpPriority, theLacpPriority);
}


inline void                         
TL1_mTeraFacilityEntParameters::SetAisType(CT_RS_IndicationType* theAisType)
{
    SET_VAL(myAisType, theAisType);
}

inline void                         
TL1_mTeraFacilityEntParameters::SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval)
{
    SET_VAL(myBurstyBerSdInterval, theBurstyBerSdInterval);
}

inline void                         
TL1_mTeraFacilityEntParameters::SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold)
{
    SET_VAL(myBurstyBerSdThreshold, theBurstyBerSdThreshold);
}


inline void                         
TL1_mTeraFacilityEntParameters::SetTribSize( CT_TEL_TS_SIZE* theTribSize )
{
    SET_VAL(myTribSize, theTribSize);
}

//--------------------------------------------------------------------------------

inline void                         
TL1_mTeraFacilityEntParameters::SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled )
{
    SET_VAL(myIsAutoAdjustAttenuationEnabled, theIsAutoAdjustAttenuationEnabled);
}

//--------------------------------------------------------------------------------
inline void                         
TL1_mTeraFacilityEntParameters::SetExpOperator( CT_Fac_TraceString* theExpOperator ) 
{
    SET_VAL(myExpOperator, theExpOperator);
}

//--------------------------------------------------------------------------------
inline void                         
TL1_mTeraFacilityEntParameters::SetTxOperator( CT_Fac_TraceString* theTxOperator ) 
{
    SET_VAL(myTxOperator, theTxOperator);
}
	
#endif
