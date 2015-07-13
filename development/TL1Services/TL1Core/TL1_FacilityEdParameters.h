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

#ifndef __TL1_FACILITYEDPARAMETERS_H__
#define __TL1_FACILITYEDPARAMETERS_H__

#include <vector>
using namespace std;

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_FACDOMAIN_H__
#include <TL1Core/TL1_FacDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_FACRSPBLK_H__
#include <Response/TL1_FACRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>

class TL1_FacilityEdParameters  
{
public:
    
    TL1_FacilityEdParameters();

    virtual ~TL1_FacilityEdParameters();

    TL1_FacilityEdParameters& operator=( const TL1_FacilityEdParameters& theBlock );

    bool operator==( const TL1_FacilityEdParameters& theBlock ) const;

    inline CT_ProfileTableId*           GetAlarmProfile( ) const;
    inline void                         SetAlarmProfile( CT_ProfileTableId* theAlarmProfile );

    inline CT_SM_PST*                   GetPrimaryState( ) const;
    inline void                         SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline bool*                        GetIsCommandForced( ) const;
    inline void                         SetIsCommandForced( bool* theIsCommandForced );

    inline bool                         GetIsCommandFRCD( ) const;
    inline bool                         GetIsCommandNORM( ) const;

    inline CT_FAC_Protection*           GetIsProtectionEnabled( ) const;
    inline void                         SetIsProtectionEnabled( CT_FAC_Protection* theIsProtectionEnabled );

    inline CT_FAC_MaintProp*            GetMaintPropagate( ) const;
    inline void                         SetMaintPropagate( CT_FAC_MaintProp* theMaintProp );

    inline bool*                        GetIsAdaptiveEnabled( ) const;
    inline void                         SetIsAdaptiveEnabled( bool* theIsAdaptiveEnabled );

    inline CT_TEL_daHz*                 GetMaxRate( ) const;
    inline void                         SetMaxRate( CT_TEL_daHz* theMaxRate );

    inline CT_TL1_ExpectedRateRange*    GetExpectedSignalRate( ) const;
    inline void                         SetExpectedSignalRate( CT_TL1_ExpectedRateRange* theExpectedSignalRate ); 

    inline CT_FAC_SignalRateListType*   GetRateList( ) const;
    inline void                         SetRateList( CT_FAC_SignalRateListType* theRateList );

    inline bool*                        GetIsOtuMapEnabled( ) const;
    inline void                         SetIsOtuMapEnabled( bool* theIsOtuMapEnabled );

    inline CT_Fac_TraceString*          GetTrace( ) const;
    inline void                         SetTrace( CT_Fac_TraceString* theTrace );

    inline CT_Fac_TraceString*          GetSentTrace( ) const;
    inline void                         SetSentTrace( CT_Fac_TraceString* theSentTrace );

    inline CT_Fac_TraceString*          GetExpectedTrace( ) const;
    inline void                         SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace );

    inline bool*                        GetIsMonitorOtiEnabled( ) const;
    inline void                         SetIsMonitorOtiEnabled( bool* theIsMonitorOtiEnabled );

    inline bool*                        GetIsMonitorTraceEnabled( ) const;
    inline void                         SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled );

    inline bool*                        GetIsInsertAisEnabled( ) const;
    inline void                         SetIsInsertAisEnabled( bool* theIsInsertAisEnabled );

    inline CT_TEL_BERLevels*            GetSFThreshold( ) const;
    inline void                         SetSFThreshold( CT_TEL_BERLevels* theSFThreshold );

    inline CT_TEL_BERLevels*            GetSDThreshold( ) const;
    inline void                         SetSDThreshold( CT_TEL_BERLevels* theSFThreshold );

    inline CT_FAC_ExternalConnectivity* GetExternalConnectivity( ) const;
    inline void                         SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConnectivity );

    inline CT_TEL_SignalType*           GetSignalType( ) const;
    inline void                         SetSignalType( CT_TEL_SignalType* theSignalType );

    inline CT_TEL_ClkType*              GetClkType( ) const;
    inline void                         SetClkType(CT_TEL_ClkType* theClkType);

    inline CT_TEL_OTIDStatus*           GetOTIDStatus( ) const;
    inline void                         SetOTIDStatus(CT_TEL_OTIDStatus* theOTIDStatus);

    inline bool*                        GetIsAutoAdjustAttenuationEnabled( ) const;
    inline void                         SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled );

   inline bool*                        GetIsAutoAdjustOutPowerEnabled( ) const;
    inline void                         SetIsAutoAdjustOutPowerEnabled( bool* theIsAutoAdjustOutPowerEnabled );

    inline bool*                        GetIsAutoAdjustInPowerEnabled( ) const;
    inline void                         SetIsAutoAdjustInPowerEnabled( bool* theIsAutoAdjustInPowerEnabled );

    inline bool*                        GetIsAutoTxPowerShutdownEnabled( ) const;
    inline void                         SetIsAutoTxPowerShutdownEnabled( bool* theIsAutoTxPowerShutdownEnabled );

    inline CT_FAC_LineCode*             GetLineCode( ) const; 
    inline void                         SetLineCode( CT_FAC_LineCode* theLineCode );

    inline CT_FAC_FrameFormat*          GetFrameFormat( ) const;  
    inline void                         SetFrameFormat( CT_FAC_FrameFormat* theFrameFormat );

    inline bool*                        GetIsSsmConnected( ) const;
    inline void                         SetIsSsmConnected( bool* theIsSsmConnected );

    inline CT_Fac_ConnectedToString*    GetConnectedTo( ) const;
    inline void                         SetConnectedTo( CT_Fac_ConnectedToString* theConnectedTo );

    inline CT_TEL_GfpFramingMode*       GetGfpMap( ) const;
    inline void                         SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap );

    inline CT_Fac_TraceString*          GetProtFunc( ) const;
    inline void                         SetProtFunc( CT_Fac_TraceString* theProtFunc );

    inline bool*                        GetGenTrc( ) const;
    inline void                         SetGenTrc( bool* theGenTrc );

    inline CT_TEL_FecType*              GetFecType( ) const;
    inline void                         SetFecType( CT_TEL_FecType* theFecType );

    inline CT_TEL_SuperFec*             GetSuperFec( ) const;
    inline void                         SetSuperFec( CT_TEL_SuperFec* theSuperFec );

    inline CT_TEL_mBm*                  GetLOSThreshold( ) const;
    inline void                         SetLOSThreshold( CT_TEL_mBm* theLOSThreshold );

    inline CT_TEL_mBm*                  GetSWThreshold( ) const;
    inline void                         SetSWThreshold( CT_TEL_mBm* theSWThreshold );

    inline CT_TEL_OpticalWaveLength*    GetSignalBand( ) const;
    inline void                         SetSignalBand( CT_TEL_OpticalWaveLength* theSignalBand );

    inline bool*                        GetNendALS( ) const;
    inline void                         SetNendALS( bool* theNendALS );

    inline CT_Fac_TraceString*          GetOtuExpTrc( ) const;
    inline void                         SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc );

    inline CT_FAC_StsMap*               GetAddCrsMap( ) const;
    inline void                         SetAddCrsMap( CT_FAC_StsMap* theAddCrsMap );

    inline CT_FAC_StsMap*               GetDelCrsMap( ) const;
    inline void                         SetDelCrsMap( CT_FAC_StsMap* theDelCrsMap );

    inline bool*                        GetIsEonMsgEnabled( ) const;
    inline void                         SetIsEonMsgEnabled( bool* theIsEonMsgEnabled );

    inline bool*                        GetIsTrafficEnabled( ) const;
    inline void                         SetIsTrafficEnabled( bool* theIsTrafficEnabled );

    inline CT_TEL_OEO_REGEN_MODE*       GetOeoRegen( ) const;
    inline void                         SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen );

    inline CT_TapNumber*                GetTapNumber( ) const;
    inline void                         SetTapNumber( CT_TapNumber* theTapNumber ); 

    inline bool*                        GetIsAutoNegotiationEnabled( ) const;
    inline void                         SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled );

    inline LT_Handle*                   GetHandle( ) const;
    inline void                         SetHandle( LT_Handle* theHandle );

    inline CT_TEL_PayloadSignalId*      GetPt() const;
    inline void                         SetPt( CT_TEL_PayloadSignalId* thePt );

    inline CT_TEL_GfpUpiId*             GetGfpUpi() const;
    inline void                         SetGfpUpi( CT_TEL_GfpUpiId* theUpi );

    inline bool*                        GetQuarantine( ) const;
    inline void                         SetQuarantine( bool* theQua );

    inline LT_Ctag                      GetCtag( ) const;
    inline void                         SetCtag( LT_Ctag theCtag );

    inline int*                         GetHoldOffProt( ) const;
    inline void                         SetHoldOffProt( int* theHoldOffProt );

    inline uint32*                      GetExtChannel() const;
    inline void                         SetExtChannel(uint32* theExtChannel);

    inline CT_FAC_StsMap*               GetAddCstMap( ) const;
    inline void                         SetAddCstMap( CT_FAC_StsMap* theAddCstMap );

    inline CT_FAC_StsMap*               GetDelCstMap( ) const;
    inline void                         SetDelCstMap( CT_FAC_StsMap* theDelCstMap );

    inline CT_TEL_daHz*                 GetEthRate( ) const;
    inline void                         SetEthRate( CT_TEL_daHz* theEthRate );

    inline CT_TEL_MAC_DUPLEX_MODE*      GetDuplexMode( ) const;
    inline void                         SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode );

    inline CT_TCM_Mode*                 GetTcmMode( ) const;
    inline void                         SetTcmMode( CT_TCM_Mode* theTcmMode );

    inline CT_TEL_MAC_ADFLW_CTRL*       GetFlowCtrlAd( ) const;
    inline void                         SetFlowCtrlAd( CT_TEL_MAC_ADFLW_CTRL* theFlowAd );

    inline CT_TEL_MAC_FLOWCTRL*         GetFlowCtrlEnable( ) const;
    inline void                         SetFlowCtrlEnable( CT_TEL_MAC_FLOWCTRL* theFlowCtrl );

    inline CT_TEL_VlanTag*              GetVLanTag( ) const;
    inline void                         SetVLanTag( CT_TEL_VlanTag* theVTag );

    inline bool*                        GetTagMode( ) const;
    inline void                         SetTagMode( bool* theTagMode );

    inline CT_TEL_Tpid*                 GetTPid( ) const;
    inline void                         SetTPid( CT_TEL_Tpid* theTPid );

    inline bool*                        GetDiscardPause( ) const;
    inline void                         SetDiscardPause( bool* theDiscardPause );

    inline bool*                        GetPropFefi( ) const;
    inline void                         SetPropFefi( bool* thePropFefi );

    inline CT_PMProfileTableId*         GetPmProfile( ) const;
    inline void                         SetPmProfile( CT_PMProfileTableId* thePmProfile );

    inline int*                         GetCFProfile( ) const;
    inline void                         SetCFProfile( int* theCFProfile );

    inline CT_TEL_PayloadType*  GetCbrMap() const;
    inline void                  SetCbrMap(CT_TEL_PayloadType* theCbrMap);

    inline CT_FAC_OduTsMap *            GetTribSlot() const;
    inline void                         SetTribSlot( CT_FAC_OduTsMap* theTribSlot);

    inline bool *                       GetTribFall() const;
    inline void                         SetTribFall(bool* theTribFall);

    inline bool *                       GetDmSource() const;
    inline void                         SetDmSource(bool* theDmSource);

    inline bool *                       GetLtcActMode() const;
    inline void                         SetLtcActMode(bool* theLtcActMode);

    inline uint8 *                      GetGfpTs() const;
    inline void                         SetGfpTs(uint8* theGfpTs);

    inline CT_TEL_GFP_MUX*              GetGfpMux() const;
    inline void                         SetGfpMux(CT_TEL_GFP_MUX * theGfpMux);

    inline CT_FAC_QualityLevelOverride* GetQualityLevel( ) const;
    inline void                         SetQualityLevel( CT_FAC_QualityLevelOverride* theQualityLevel );

    inline CT_TEL_TimCriteriaMode*      GetTimDef() const;
    inline void                         SetTimDef(CT_TEL_TimCriteriaMode* theTimDef);

    inline CT_Fac_TraceString*          GetExpDapi() const;
    inline void                         SetExpDapi(CT_Fac_TraceString* theExceptedDapi);

    inline CT_Fac_TraceString*          GetExpSapi() const;
    inline void                         SetExpSapi(CT_Fac_TraceString* theExceptedSapi);

    inline CT_Fac_TraceString*          GetTxDapi() const;
    inline void                         SetTxDapi(CT_Fac_TraceString* theTxDapi);

    inline CT_Fac_TraceString*          GetTxSapi() const;
    inline void                         SetTxSapi(CT_Fac_TraceString* theTxSapi);
    
    inline CT_FAC_OtsChanMap*           GetOtsChanMap( ) const;
    inline void                         SetOtsChanMap( CT_FAC_OtsChanMap* theOtsChanMap );

    inline uint8 *                      GetWcgChanReserve( ) const;
    inline void                         SetWcgChanReserve( uint8 * theWcgChanReserve );

    inline uint8 *                      GetWcgChanRelease( ) const;
    inline void                         SetWcgChanRelease( uint8 * theWcgChanRelease );

    inline CT_FAC_OtsChanType*          GetOtsChanType( ) const;
    inline void                         SetOtsChanType( CT_FAC_OtsChanType* theOtsChanType );
        
    inline CT_TEL_LacpPartiMode*        GetLacpParticipation( ) const;
    inline void                         SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation );

    inline int*                         GetLacpPriority( ) const;
    inline void                         SetLacpPriority( int* theLacpPriority );

    inline CT_RS_IndicationType*        GetAisType() const;
    inline void                         SetAisType(CT_RS_IndicationType* theAisType);

    inline uint16*                      GetBurstyBerSdInterval() const;
    inline void                         SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval);

    inline uint32*                      GetBurstyBerSdThreshold() const;
    inline void                         SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold);

    inline CT_TEL_TS_SIZE*              GetTribSize( ) const;
    inline void                         SetTribSize( CT_TEL_TS_SIZE* theTribSize );

    inline uint8 *                      GetInterPacketGap() const;
    inline void                         SetInterPacketGap(uint8* theInterPacketGap);

    inline int*                         GetNpOwner( ) const;
    inline void                         SetNpOwner( int* theNpOwner );

    inline CT_TEL_OPU_FORMAT*           GetOpuConfig( ) const;
    inline void                         SetOpuConfig(CT_TEL_OPU_FORMAT* theOpuConfig);

    inline CT_Fac_TraceString*          GetExpOperator() const;
    inline void                         SetExpOperator(CT_Fac_TraceString* theExpOperator);

    inline CT_Fac_TraceString*          GetTxOperator() const;
    inline void                         SetTxOperator(CT_Fac_TraceString* theTxOperator);

    bool                                IsControlPlaneRequest();

    inline bool*                        GetOTNMap() const;
    inline void                         SetOTNMap(bool* theOTNMap);
    
    inline CT_TEL_PayloadType*          GetMapMode() const;
    inline void                         SetMapMode(CT_TEL_PayloadType* theMapMode);

protected:

    CT_ProfileTableId*              myAlarmProfile;
    CT_SM_PST*                      myPrimaryState;
    bool*                           myIsCommandForced;
    CT_FAC_Protection*              myIsProtectionEnabled;
    CT_FAC_MaintProp*               myMaintProp;
    bool*                           myIsAdaptiveEnabled;
    CT_TEL_daHz*                    myMaxRate;
    CT_TL1_ExpectedRateRange*       myExpectedSignalRate;
    CT_FAC_SignalRateListType*      myRateList;
    bool*                           myIsOtuMapEnabled;
    CT_Fac_TraceString*             myTrace;
    CT_Fac_TraceString*             mySentTrace;
    CT_Fac_TraceString*             myExpectedTrace;
    bool*                           myIsMonitorOtiEnabled;
    bool*                           myIsMonitorTraceEnabled;
    bool*                           myIsInsertAisEnabled;
    CT_TEL_BERLevels*               mySFThreshold;
    CT_TEL_BERLevels*               mySDThreshold;
    CT_FAC_ExternalConnectivity*    myExternalConnectivity;
    CT_TEL_SignalType*              mySignalType;
    CT_TEL_ClkType*                 myClkType;
    CT_TEL_OTIDStatus*              myOTIDStatus;
    bool*                           myIsAutoAdjustAttenuationEnabled;
    bool*                           myIsAutoAdjustOutPowerEnabled;
    bool*                           myIsAutoAdjustInPowerEnabled;
    bool*                           myIsAutoTxPowerShutdownEnabled;
    CT_FAC_LineCode*                myLineCode;                       
    CT_FAC_FrameFormat*             myFrameFormat;             
    bool*                           myIsSsmConnected;
    CT_Fac_ConnectedToString*       myConnectedTo;
    CT_TEL_GfpFramingMode*          myGfpMap;
    CT_Fac_TraceString*             myProtFunc;
    bool*                           myGenTrc;
    CT_TEL_FecType*                 myFecType;
    CT_TEL_SuperFec*                mySuperFec;
    CT_TEL_mBm*                     myLOSThreshold;
    CT_TEL_mBm*                     mySWThreshold;
    CT_TEL_OpticalWaveLength*       mySignalBand;
    bool*                           myNendALS;
    CT_Fac_TraceString*             myOtuExpTrc;
    CT_FAC_StsMap*                  myAddCrsMap;
    CT_FAC_StsMap*                  myDelCrsMap;
    bool*                           myIsEonMsgEnabled;
    bool*                           myIsTrafficEnabled;
    CT_TEL_OEO_REGEN_MODE*          myOeoRegen;
    CT_TapNumber*                   myTapNumber;
    bool*                           myIsAutoNegotiationEnabled;
    LT_Handle*                      myHandle;
    CT_TEL_PayloadSignalId*         myPt;
    CT_TEL_GfpUpiId*                myGfpUpi;
    bool*                           myQua;
    LT_Ctag                         myCtag;
    int*                            myHoldOffProt;
    uint32*                         myExtChannel;
    CT_FAC_StsMap*                  myAddCstMap;
    CT_FAC_StsMap*                  myDelCstMap;
    CT_TEL_daHz*                    myEthRate;
    CT_TEL_MAC_DUPLEX_MODE*         myDuplexMode;
    CT_TCM_Mode*                    myTcmMode;
    CT_TEL_MAC_ADFLW_CTRL*          myFlowAd;
    CT_TEL_MAC_FLOWCTRL*            myFlowCtrl;
    CT_TEL_VlanTag*                 myVlanTag;
    bool*                           myTagMode;
    CT_TEL_Tpid*                    myTpid;
    bool*                           myDiscardPause;
    bool*                           myPropFefi;
    CT_PMProfileTableId*            myPmProfile;
    int*                            myCFProfile;
    CT_TEL_PayloadType*             myCbrMap;
    CT_TL1_FacParamAddr*            myAdjacnet;
    CT_FAC_OduTsMap*                myTribSlot;
    CT_TEL_GFP_MUX*                 myGfpMux;
    CT_TEL_TimCriteriaMode*         myTimDef;
    CT_Fac_TraceString*             myExpDapi;
    CT_Fac_TraceString*             myExpSapi;
    CT_Fac_TraceString*             myTxDapi;
    CT_Fac_TraceString*             myTxSapi;
    CT_FAC_OtsChanMap*              myOtsChanMap;
    CT_FAC_OtsChanType*             myOtsChanType;
    CT_TEL_LacpPartiMode*           myLacpParticipation;
    int*                            myLacpPriority;
    CT_RS_IndicationType*           myAisType;
    uint16*                         myBurstyBerSdInterval;
    uint32*                         myBurstyBerSdThreshold;
    CT_TEL_TS_SIZE*                 myTribSize;
    bool *                          myTribFall;
    uint8*                          myGfpTs;
    uint8*                          myInterPacketGap;
    bool *                          myDmSource;
    bool *                          myLtcActMode;
    CT_FAC_QualityLevelOverride*    myQualityLevel;
    int*                            myNpOwner;
    CT_TEL_OPU_FORMAT*              myOpuConfig;
    CT_Fac_TraceString*             myExpOperator;
    CT_Fac_TraceString*             myTxOperator;
    uint8*                          myWcgChanReserve;
    uint8*                          myWcgChanRelease;
    bool *                          myOTNMap;
    CT_TEL_PayloadType*             myMapMode;
};

class TL1_FacilityValidateEdParameters  
{
public:

    enum EditableParameters 
    {
        AlarmProfileEditable = 0,
        PrimaryStateEditable,
        IsCommandForcedEditable,
        IsProtectionEnabledEditable,
        MaintPropEditable,
        IsAdaptiveEnabledEditable,
        MaxRateEditable,
        RateListEditable,
        IsOtuMapEnabledEditable,
        TraceEditable,
        SentTraceEditable,
        ExpectedTraceEditable,
        IsMonitorOtiEnabledEditable,
        IsMonitorTraceEnabledEditable,
        IsInsertAisEnabledEditable,
        SFThresholdEditable,
        SDThresholdEditable,
        ExternalConnectivityEditable,
        SignalTypeEditable,
        ClkTypeEditable,
        OTIDStatusEditable,
        IsAutoAdjustAttenuationEnabledEditable,
        IsAutoAdjustOutPowerEnabledEditable,
        IsAutoAdjustInPowerEnabledEditable,
        IsAutoTxPowerShutdownEnabledEditable,
        LineCodeEditable,                       
        FrameFormatEditable,             
        IsSsmConnectedEditable,
        ConnectedToEditable,
        GfpMapEditable,
        ProtFuncEditable,
        GenTrcEditable,
        FecTypeEditable,
        LOSThresholdEditable,
        SWThresholdEditable,
        SignalBandEditable,
        NendALSEditable,
        OtuExpTrcEditable,
        AddCrsMapEditable,
        DelCrsMapEditable,
        IsEonMsgEnabledEditable,
        IsTrafficEnabledEditable,
        OeoRegenEditable,
        TapNumberEditable,
        IsAutoNegotiationEnabledEditable,
        HandleEditable,
        PtEditable,
        GfpUpiEditable,
        QuaEditable,
        CtagEditable,
        HoldOffProtEditable,
        AddCstMapEditable,
        DelCstMapEditable,
        ExtChannelEditable,
        EthRateEditable,
        DuplexModeEditable,
        TcmModeEditerable,
        FlowAdEditable,
        FlowCtrlEditable,
        VlanTagEditable,
        TagModeEditable,
        TpidEditable,
        DiscardPauseEditable,
        PropFefiEditable,
        PmProfileEditable,
        CFProfileEditable,
        CbrMapEditable,
        TribSlotEditable,
        GfpMuxEditable,
        TimDefEditable,
        ExpDapiEditable,
        ExpSapiEditable,
        TxDapiEditable,
        TxSapiEditable,
        OtsChanMapEditable,
        LacpParticipationEditable,
        LacpPriorityEditable,
        AisTypeEditable,
        BurstyBerSdIntervalEditable,
        BurstyBerSdThresholdEditable,
        TribSizeEditable,
        TribFallEditable,
        GfpTsEditable,
        DmSourceEditable,
        LtcActModeEditable,
        ExpectedSignalRateEditable,
        QualityLevelEditable,
        InterPacketGapEditable,
        SuperFecEditable,
        NpOwnerEditable,
        OpuConfigEditable,
        ExpOperatorEditable,
        TxOperatorEditable,
        OTNMapEditable,
        MapModeEditable,

        // Generic ValidateEditParamters() will be bypass in
        // T7100_TL1WcgEntity::DoEdFac(). So no need to add:
        // WcgChanReserveEditable,   
        // WcgChanReleaseEditable,   

        AnyParameters               /* this should always be the last enum */
    };

    TL1_FacilityValidateEdParameters();

    virtual ~TL1_FacilityValidateEdParameters();

    void ValidateEditParameters( const TL1_FacilityEdParameters& theEdParameters ) const;

    inline vector<bool>& GetEdParametersSet( );

private:
    vector<bool>       myEdParametersSet;
};

//--------------------------------------------------------------------------------

inline CT_ProfileTableId*           
TL1_FacilityEdParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}
inline void                         
TL1_FacilityEdParameters::SetAlarmProfile( CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}
//--------------------------------------------------------------------------------

inline CT_SM_PST*                   
TL1_FacilityEdParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_FacilityEdParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_FacilityEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}

inline bool                         
TL1_FacilityEdParameters::GetIsCommandFRCD( ) const
{
    if ( GetIsCommandForced( ) )
    {
        if ( *GetIsCommandForced( ) )
        {
            return true;
        }
    }

    return false;
}

inline bool                         
TL1_FacilityEdParameters::GetIsCommandNORM( ) const
{
    if ( GetIsCommandForced( ) )
    {
        if ( *GetIsCommandForced( ) )
        {
            return false;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------

inline CT_FAC_Protection*                        
TL1_FacilityEdParameters::GetIsProtectionEnabled( ) const
{
    return myIsProtectionEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsProtectionEnabled( CT_FAC_Protection* theIsProtectionEnabled )
{
    myIsProtectionEnabled = theIsProtectionEnabled;
}
//--------------------------------------------------------------------------------

inline CT_FAC_MaintProp*                        
TL1_FacilityEdParameters::GetMaintPropagate( ) const
{
    return myMaintProp;
}

inline void                         
TL1_FacilityEdParameters::SetMaintPropagate( CT_FAC_MaintProp* theMaintProp )
{
    myMaintProp = theMaintProp;
}

//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsAdaptiveEnabled( ) const
{
    return myIsAdaptiveEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsAdaptiveEnabled( bool* theIsAdaptiveEnabled )
{
    myIsAdaptiveEnabled = theIsAdaptiveEnabled;
}
//--------------------------------------------------------------------------------

inline CT_TEL_daHz*                 
TL1_FacilityEdParameters::GetMaxRate( ) const
{
    return myMaxRate;
}

inline void                         
TL1_FacilityEdParameters::SetMaxRate( CT_TEL_daHz* theMaxRate )
{
    myMaxRate = theMaxRate;
}
//--------------------------------------------------------------------------------

inline CT_TL1_ExpectedRateRange*    
TL1_FacilityEdParameters::GetExpectedSignalRate( ) const
{
    return myExpectedSignalRate;
}

inline void                         
TL1_FacilityEdParameters::SetExpectedSignalRate( CT_TL1_ExpectedRateRange* theExpectedSignalRate ) 
{
    myExpectedSignalRate = theExpectedSignalRate;
}
//--------------------------------------------------------------------------------

inline CT_FAC_SignalRateListType*   
TL1_FacilityEdParameters::GetRateList( ) const
{
    return myRateList;
}

inline void                         
TL1_FacilityEdParameters::SetRateList( CT_FAC_SignalRateListType* theRateList )
{
    myRateList = theRateList;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsOtuMapEnabled( ) const
{
    return myIsOtuMapEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsOtuMapEnabled( bool* theIsOtuMapEnabled )
{
    myIsOtuMapEnabled = theIsOtuMapEnabled;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEdParameters::GetTrace( ) const
{
    return myTrace;
}

inline void                         
TL1_FacilityEdParameters::SetTrace( CT_Fac_TraceString* theTrace )
{
    myTrace = theTrace;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEdParameters::GetSentTrace( ) const
{
    return mySentTrace;
}

inline void                         
TL1_FacilityEdParameters::SetSentTrace( CT_Fac_TraceString* theSentTrace )
{
    mySentTrace = theSentTrace;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEdParameters::GetExpectedTrace( ) const
{
    return myExpectedTrace;
}

inline void                         
TL1_FacilityEdParameters::SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace )
{
    myExpectedTrace = theExpectedTrace;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsMonitorOtiEnabled( ) const
{
    return myIsMonitorOtiEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsMonitorOtiEnabled( bool* theIsMonitorOtiEnabled )
{
    myIsMonitorOtiEnabled = theIsMonitorOtiEnabled;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsMonitorTraceEnabled( ) const
{
    return myIsMonitorTraceEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled )
{
    myIsMonitorTraceEnabled = theIsMonitorTraceEnabled;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsInsertAisEnabled( ) const
{
    return myIsInsertAisEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsInsertAisEnabled( bool* theIsInsertAisEnabled )
{
    myIsInsertAisEnabled = theIsInsertAisEnabled;
}
//--------------------------------------------------------------------------------

inline CT_TEL_BERLevels*            
TL1_FacilityEdParameters::GetSFThreshold( ) const
{
    return mySFThreshold;
}

inline void                         
TL1_FacilityEdParameters::SetSFThreshold( CT_TEL_BERLevels* theSFThreshold )
{
    mySFThreshold = theSFThreshold;
}
//--------------------------------------------------------------------------------

inline CT_TEL_BERLevels*            
TL1_FacilityEdParameters::GetSDThreshold( ) const
{
    return mySDThreshold;
}

inline void                         
TL1_FacilityEdParameters::SetSDThreshold( CT_TEL_BERLevels* theSDThreshold )
{
    mySDThreshold = theSDThreshold;
}
//--------------------------------------------------------------------------------

inline CT_FAC_ExternalConnectivity* 
TL1_FacilityEdParameters::GetExternalConnectivity( ) const
{
    return myExternalConnectivity;
}

inline void                         
TL1_FacilityEdParameters::SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConnectivity )
{
    myExternalConnectivity = theExternalConnectivity;
}
//--------------------------------------------------------------------------------

inline CT_TEL_SignalType*           
TL1_FacilityEdParameters::GetSignalType( ) const
{
    return mySignalType;
}

inline void                         
TL1_FacilityEdParameters::SetSignalType( CT_TEL_SignalType* theSignalType )
{
    mySignalType = theSignalType;
}
//--------------------------------------------------------------------------------

inline CT_TEL_ClkType*           
TL1_FacilityEdParameters::GetClkType( ) const
{
    return myClkType;
}

inline void                         
TL1_FacilityEdParameters::SetClkType( CT_TEL_ClkType* theClkType ) 
{
    myClkType = theClkType;
}
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------

inline CT_TEL_OTIDStatus*           
TL1_FacilityEdParameters::GetOTIDStatus( ) const
{
    return myOTIDStatus;
}

inline void                         
TL1_FacilityEdParameters::SetOTIDStatus( CT_TEL_OTIDStatus* theOTIDStatus ) 
{
    myOTIDStatus = theOTIDStatus;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsAutoAdjustAttenuationEnabled( ) const
{
    return myIsAutoAdjustAttenuationEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled )
{
    myIsAutoAdjustAttenuationEnabled = theIsAutoAdjustAttenuationEnabled;
}

//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsAutoAdjustOutPowerEnabled( ) const
{
    return myIsAutoAdjustOutPowerEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsAutoAdjustOutPowerEnabled( bool* theIsAutoAdjustOutPowerEnabled )
{
    myIsAutoAdjustOutPowerEnabled = theIsAutoAdjustOutPowerEnabled;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsAutoAdjustInPowerEnabled( ) const
{
    return myIsAutoAdjustInPowerEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsAutoAdjustInPowerEnabled( bool* theIsAutoAdjustInPowerEnabled )
{   
    myIsAutoAdjustInPowerEnabled = theIsAutoAdjustInPowerEnabled;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsAutoTxPowerShutdownEnabled( ) const
{
    return myIsAutoTxPowerShutdownEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsAutoTxPowerShutdownEnabled( bool* theIsAutoTxPowerShutdownEnabled )
{
    myIsAutoTxPowerShutdownEnabled = theIsAutoTxPowerShutdownEnabled;
}
//--------------------------------------------------------------------------------

inline CT_FAC_LineCode*             
TL1_FacilityEdParameters::GetLineCode( ) const 
{
    return myLineCode;
}

inline void                         
TL1_FacilityEdParameters::SetLineCode( CT_FAC_LineCode* theLineCode )
{
    myLineCode = theLineCode;
}
//--------------------------------------------------------------------------------

inline CT_FAC_FrameFormat*          
TL1_FacilityEdParameters::GetFrameFormat( ) const  
{
    return myFrameFormat;
}

inline void                         
TL1_FacilityEdParameters::SetFrameFormat( CT_FAC_FrameFormat* theFrameFormat )
{
    myFrameFormat = theFrameFormat;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsSsmConnected( ) const
{
    return myIsSsmConnected;
}

inline void                         
TL1_FacilityEdParameters::SetIsSsmConnected( bool* theIsSsmConnected )
{
    myIsSsmConnected = theIsSsmConnected;
}
//--------------------------------------------------------------------------------

inline CT_Fac_ConnectedToString*    
TL1_FacilityEdParameters::GetConnectedTo( ) const
{
    return myConnectedTo;
}

inline void                         
TL1_FacilityEdParameters::SetConnectedTo( CT_Fac_ConnectedToString* theConnectedTo )
{
    myConnectedTo = theConnectedTo;
}
//--------------------------------------------------------------------------------

inline CT_TEL_GfpFramingMode*       
TL1_FacilityEdParameters::GetGfpMap( ) const
{
    return myGfpMap;
}

inline void                         
TL1_FacilityEdParameters::SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap )
{
    myGfpMap = theGfpMap;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEdParameters::GetProtFunc( ) const
{
    return myProtFunc;
}

inline void                         
TL1_FacilityEdParameters::SetProtFunc( CT_Fac_TraceString* theProtFunc )
{
    myProtFunc = theProtFunc;
}
//--------------------------------------------------------------------------------

inline bool*                 
TL1_FacilityEdParameters::GetGenTrc( ) const
{
    return myGenTrc;
}

inline void                         
TL1_FacilityEdParameters::SetGenTrc( bool* theGenTrc )
{
    myGenTrc = theGenTrc;
}
//--------------------------------------------------------------------------------

inline CT_TEL_FecType*              
TL1_FacilityEdParameters::GetFecType( ) const
{
    return myFecType;
}

inline void                         
TL1_FacilityEdParameters::SetFecType( CT_TEL_FecType* theFecType )
{
    myFecType = theFecType;
}
//--------------------------------------------------------------------------------

inline CT_TEL_SuperFec*              
TL1_FacilityEdParameters::GetSuperFec( ) const
{
    return mySuperFec;
}

inline void                         
TL1_FacilityEdParameters::SetSuperFec( CT_TEL_SuperFec* theSuperFec )
{
    mySuperFec = theSuperFec;
}
//--------------------------------------------------------------------------------

inline CT_TEL_mBm*                  
TL1_FacilityEdParameters::GetLOSThreshold( ) const
{
    return myLOSThreshold;
}

inline void                         
TL1_FacilityEdParameters::SetLOSThreshold( CT_TEL_mBm* theLOSThreshold )
{
    myLOSThreshold = theLOSThreshold;
}
//--------------------------------------------------------------------------------

inline CT_TEL_mBm*                  
TL1_FacilityEdParameters::GetSWThreshold( ) const
{
    return mySWThreshold;
}

inline void                         
TL1_FacilityEdParameters::SetSWThreshold( CT_TEL_mBm* theSWThreshold )
{
    mySWThreshold = theSWThreshold;
}
//--------------------------------------------------------------------------------

inline CT_TEL_OpticalWaveLength*    
TL1_FacilityEdParameters::GetSignalBand( ) const
{
    return mySignalBand;
}

inline void                         
TL1_FacilityEdParameters::SetSignalBand( CT_TEL_OpticalWaveLength* theSignalBand )
{
    mySignalBand = theSignalBand;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetNendALS( ) const
{
    return myNendALS;
}

inline void                         
TL1_FacilityEdParameters::SetNendALS( bool* theNendALS )
{
    myNendALS = theNendALS;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEdParameters::GetOtuExpTrc( ) const
{
    return myOtuExpTrc;
}

inline void                         
TL1_FacilityEdParameters::SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc )
{
    myOtuExpTrc = theOtuExpTrc;
}
//--------------------------------------------------------------------------------

inline CT_FAC_StsMap*
TL1_FacilityEdParameters::GetAddCrsMap( ) const
{
    return myAddCrsMap;
}

inline void
TL1_FacilityEdParameters::SetAddCrsMap( CT_FAC_StsMap* theAddCrsMap )
{
    myAddCrsMap = theAddCrsMap;
}
//--------------------------------------------------------------------------------

inline CT_FAC_StsMap*
TL1_FacilityEdParameters::GetDelCrsMap( ) const
{
    return myDelCrsMap;
}

inline void
TL1_FacilityEdParameters::SetDelCrsMap( CT_FAC_StsMap* theDelCrsMap )
{
    myDelCrsMap = theDelCrsMap;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsEonMsgEnabled( ) const
{
    return myIsEonMsgEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsEonMsgEnabled( bool* theIsEonMsgEnabled )
{
    myIsEonMsgEnabled = theIsEonMsgEnabled;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsTrafficEnabled( ) const
{
    return myIsTrafficEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsTrafficEnabled( bool* theIsTrafficEnabled )
{
    myIsTrafficEnabled = theIsTrafficEnabled;
}

//--------------------------------------------------------------------------------

inline CT_TEL_OEO_REGEN_MODE*
TL1_FacilityEdParameters::GetOeoRegen( ) const
{
    return myOeoRegen;
}

inline void
TL1_FacilityEdParameters::SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen )
{
    myOeoRegen = theOeoRegen;
}

//--------------------------------------------------------------------------------

inline CT_TapNumber*
TL1_FacilityEdParameters::GetTapNumber( ) const
{
    return myTapNumber;
}

inline void                         
TL1_FacilityEdParameters::SetTapNumber( CT_TapNumber* theTapNumber)
{
    myTapNumber = theTapNumber;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetIsAutoNegotiationEnabled( ) const
{
    return myIsAutoNegotiationEnabled;
}

inline void                         
TL1_FacilityEdParameters::SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled )
{
    myIsAutoNegotiationEnabled = theIsAutoNegotiationEnabled;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_FacilityEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_FacilityEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}
//--------------------------------------------------------------------------------

inline LT_Ctag                     
TL1_FacilityEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_FacilityEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------

inline int*                         
TL1_FacilityEdParameters::GetHoldOffProt( ) const
{
    return myHoldOffProt;
}

inline void                         
TL1_FacilityEdParameters::SetHoldOffProt( int* theHoldOffProt )
{
    myHoldOffProt = theHoldOffProt;

}

//--------------------------------------------------------------------------------

inline CT_TEL_PayloadSignalId*                        
TL1_FacilityEdParameters::GetPt( ) const
{
    return myPt;
}

inline void                         
TL1_FacilityEdParameters::SetPt( CT_TEL_PayloadSignalId* thePt )
{
    myPt = thePt;
}

//--------------------------------------------------------------------------------

inline CT_TEL_GfpUpiId*                        
TL1_FacilityEdParameters::GetGfpUpi( ) const
{
    return myGfpUpi;
}

inline void                         
TL1_FacilityEdParameters::SetGfpUpi( CT_TEL_GfpUpiId* theUpi )
{
    myGfpUpi = theUpi;
}

//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetQuarantine( ) const
{
    return myQua;
}

inline void                         
TL1_FacilityEdParameters::SetQuarantine( bool* theQua )
{
    myQua = theQua;
}

//--------------------------------------------------------------------------------

inline CT_FAC_StsMap*
TL1_FacilityEdParameters::GetAddCstMap( ) const
{
    return myAddCstMap;
}

inline void
TL1_FacilityEdParameters::SetAddCstMap( CT_FAC_StsMap* theAddCstMap )
{
    myAddCstMap = theAddCstMap;
}
//--------------------------------------------------------------------------------

inline CT_FAC_StsMap*
TL1_FacilityEdParameters::GetDelCstMap( ) const
{
    return myDelCstMap;
}

inline void
TL1_FacilityEdParameters::SetDelCstMap( CT_FAC_StsMap* theDelCstMap )
{
    myDelCstMap = theDelCstMap;
}

//--------------------------------------------------------------------------------
inline CT_TEL_daHz* 
TL1_FacilityEdParameters::GetEthRate( ) const
{
    return myEthRate;
}
inline void
TL1_FacilityEdParameters::SetEthRate( CT_TEL_daHz* theEthRate )
{
    myEthRate = theEthRate;
}

//--------------------------------------------------------------------------------
inline CT_TEL_MAC_DUPLEX_MODE*
TL1_FacilityEdParameters::GetDuplexMode( ) const
{
    return myDuplexMode;
}
inline void
TL1_FacilityEdParameters::SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode )
{
    myDuplexMode = theDuplexMode;
}

//--------------------------------------------------------------------------------
inline CT_TCM_Mode*
TL1_FacilityEdParameters::GetTcmMode( ) const
{
    return myTcmMode;
}
inline void
TL1_FacilityEdParameters::SetTcmMode( CT_TCM_Mode* theTcmMode )
{
    myTcmMode = theTcmMode;
}

//--------------------------------------------------------------------------------
inline CT_TEL_MAC_ADFLW_CTRL*
TL1_FacilityEdParameters::GetFlowCtrlAd( ) const
{
    return myFlowAd;
}
inline void
TL1_FacilityEdParameters::SetFlowCtrlAd( CT_TEL_MAC_ADFLW_CTRL* theFlowAd )
{
    myFlowAd = theFlowAd;
}

//--------------------------------------------------------------------------------
inline CT_TEL_MAC_FLOWCTRL*
TL1_FacilityEdParameters::GetFlowCtrlEnable( ) const
{
    return myFlowCtrl;
}
inline void
TL1_FacilityEdParameters::SetFlowCtrlEnable( CT_TEL_MAC_FLOWCTRL* theFlowCtrl )
{
    myFlowCtrl = theFlowCtrl;
}
//-------------------------------------------------------------------------------
inline CT_TEL_VlanTag*
TL1_FacilityEdParameters::GetVLanTag( ) const
{
    return myVlanTag;
}
inline void
TL1_FacilityEdParameters::SetVLanTag( CT_TEL_VlanTag* theVTag )
{
    myVlanTag = theVTag;
}
//-------------------------------------------------------------------------------
inline bool*
TL1_FacilityEdParameters::GetTagMode( ) const
{
    return myTagMode;
}
inline void
TL1_FacilityEdParameters::SetTagMode( bool* theTagMode )
{
    myTagMode = theTagMode;
}
//-------------------------------------------------------------------------------
inline CT_TEL_Tpid*
TL1_FacilityEdParameters::GetTPid( ) const
{
    return myTpid;
}
inline void
TL1_FacilityEdParameters::SetTPid( CT_TEL_Tpid* theTPid )
{
    myTpid = theTPid;
}


//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetDiscardPause( ) const
{
    return myDiscardPause;
}

inline void                         
TL1_FacilityEdParameters::SetDiscardPause( bool* theDiscardPause )
{
    myDiscardPause = theDiscardPause;
}


//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEdParameters::GetPropFefi( ) const
{
    return myPropFefi;
}

inline void                         
TL1_FacilityEdParameters::SetPropFefi( bool* thePropFefi )
{
    myPropFefi = thePropFefi;
}


//--------------------------------------------------------------------------------

inline vector<bool>& 
TL1_FacilityValidateEdParameters::GetEdParametersSet( )
{
    return myEdParametersSet;
}

//--------------------------------------------------------------------------------

inline uint32*                         
TL1_FacilityEdParameters::GetExtChannel( ) const
{
    return myExtChannel;
}

inline void                         
TL1_FacilityEdParameters::SetExtChannel(uint32* theExtChannel)
{
    myExtChannel = theExtChannel;
}

//--------------------------------------------------------------------------------

inline CT_PMProfileTableId*           
TL1_FacilityEdParameters::GetPmProfile( ) const
{
    return myPmProfile;
}
inline void                         
TL1_FacilityEdParameters::SetPmProfile( CT_PMProfileTableId* thePmProfile )
{
    myPmProfile = thePmProfile;
}

//--------------------------------------------------------------------------------

inline int*           
TL1_FacilityEdParameters::GetCFProfile( ) const
{
    return myCFProfile;
}
inline void                         
TL1_FacilityEdParameters::SetCFProfile( int* theCFProfile )
{
    myCFProfile = theCFProfile;
}

inline CT_TEL_PayloadType* 
TL1_FacilityEdParameters::GetCbrMap() const
{
    return myCbrMap;
}

inline void 
TL1_FacilityEdParameters::SetCbrMap(CT_TEL_PayloadType * theCbrMap)
{
    myCbrMap = theCbrMap;
}

//--------------------------------------------------------------------------------

inline CT_FAC_OduTsMap *  TL1_FacilityEdParameters::GetTribSlot() const
{
    return myTribSlot;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEdParameters::SetTribSlot( CT_FAC_OduTsMap* theTribSlot)
{
    myTribSlot = theTribSlot;
}
//--------------------------------------------------------------------------------
inline bool *              TL1_FacilityEdParameters::GetTribFall() const
{
    return myTribFall;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEdParameters::SetTribFall( bool* theTribFall)
{
    myTribFall = theTribFall;
}
//--------------------------------------------------------------------------------
inline bool *              TL1_FacilityEdParameters::GetDmSource() const
{
    return myDmSource;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEdParameters::SetDmSource( bool* theDmSource)
{
    myDmSource = theDmSource;
}


inline bool *              TL1_FacilityEdParameters::GetLtcActMode() const
{
    return myLtcActMode;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEdParameters::SetLtcActMode( bool* theLtcActMode)
{
    myLtcActMode= theLtcActMode;
}
//--------------------------------------------------------------------------------
inline uint8 *              TL1_FacilityEdParameters::GetGfpTs() const
{
    return myGfpTs;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEdParameters::SetGfpTs( uint8* theGfpTs)
{
    myGfpTs = theGfpTs;
}
//--------------------------------------------------------------------------------
inline uint8 *              TL1_FacilityEdParameters::GetInterPacketGap() const
{
    return myInterPacketGap;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEdParameters::SetInterPacketGap( uint8* theInterPacketGap)
{
    myInterPacketGap = theInterPacketGap;
}
//--------------------------------------------------------------------------------

inline CT_FAC_QualityLevelOverride*                        
TL1_FacilityEdParameters::GetQualityLevel( ) const
{
    return myQualityLevel;
}

inline void                         
TL1_FacilityEdParameters::SetQualityLevel( CT_FAC_QualityLevelOverride* theQualityLevel )
{
    myQualityLevel = theQualityLevel;
}

//--------------------------------------------------------------------------------

inline CT_TEL_GFP_MUX* 
TL1_FacilityEdParameters::GetGfpMux() const
{
    return myGfpMux;
}

inline void 
TL1_FacilityEdParameters::SetGfpMux(CT_TEL_GFP_MUX * theGfpMux)
{
    myGfpMux= theGfpMux;
}

inline CT_TEL_TimCriteriaMode* 
TL1_FacilityEdParameters::GetTimDef() const
{
    return myTimDef;
}

inline void 
TL1_FacilityEdParameters::SetTimDef(CT_TEL_TimCriteriaMode * theTimDef)
{
    myTimDef = theTimDef;
}

inline CT_Fac_TraceString* 
TL1_FacilityEdParameters::GetExpDapi() const
{
    return myExpDapi;
}

inline void 
TL1_FacilityEdParameters::SetExpDapi(CT_Fac_TraceString * theExpDapi)
{
    myExpDapi = theExpDapi;
}

inline CT_Fac_TraceString* 
TL1_FacilityEdParameters::GetExpSapi() const
{
    return myExpSapi;
}

inline void 
TL1_FacilityEdParameters::SetExpSapi(CT_Fac_TraceString * theExpSapi)
{
    myExpSapi = theExpSapi;
}

inline CT_Fac_TraceString* 
TL1_FacilityEdParameters::GetTxDapi() const
{
    return myTxDapi;
}

inline void 
TL1_FacilityEdParameters::SetTxDapi(CT_Fac_TraceString * theTxDapi)
{
    myTxDapi = theTxDapi;
}

inline CT_Fac_TraceString* 
TL1_FacilityEdParameters::GetTxSapi() const
{
    return myTxSapi;
}

inline void 
TL1_FacilityEdParameters::SetTxSapi(CT_Fac_TraceString * theTxSapi)
{
    myTxSapi = theTxSapi;
}

//--------------------------------------------------------------------------------
inline CT_FAC_OtsChanMap*           
TL1_FacilityEdParameters::GetOtsChanMap( ) const
{
    return myOtsChanMap;
}

inline void                         
TL1_FacilityEdParameters::SetOtsChanMap( CT_FAC_OtsChanMap* theOtsChanMap )
{
    myOtsChanMap = theOtsChanMap;
}

//--------------------------------------------------------------------------------
inline uint8*
TL1_FacilityEdParameters::GetWcgChanReserve( ) const
{
    return myWcgChanReserve;
}

inline void
TL1_FacilityEdParameters::SetWcgChanReserve( uint8* theWcgChanReserve )
{
    myWcgChanReserve = theWcgChanReserve;
}

//--------------------------------------------------------------------------------
inline uint8*
TL1_FacilityEdParameters::GetWcgChanRelease( ) const
{
    return myWcgChanRelease;
}

inline void
TL1_FacilityEdParameters::SetWcgChanRelease( uint8* theWcgChanRelease )
{
    myWcgChanRelease = theWcgChanRelease;
}

//--------------------------------------------------------------------------------
inline CT_FAC_OtsChanType*           
TL1_FacilityEdParameters::GetOtsChanType( ) const
{
    return myOtsChanType;
}

inline void                         
TL1_FacilityEdParameters::SetOtsChanType( CT_FAC_OtsChanType* theOtsChanType )
{
    myOtsChanType = theOtsChanType;
}

//--------------------------------------------------------------------------------
inline CT_TEL_LacpPartiMode*           
TL1_FacilityEdParameters::GetLacpParticipation( ) const
{
    return myLacpParticipation;
}

inline void                         
TL1_FacilityEdParameters::SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation )
{
    myLacpParticipation = theLacpParticipation;
}

//--------------------------------------------------------------------------------
inline int*           
TL1_FacilityEdParameters::GetLacpPriority( ) const
{
    return myLacpPriority;
}

inline void                         
TL1_FacilityEdParameters::SetLacpPriority( int* theLacpPriority )
{
    myLacpPriority = theLacpPriority;
}


inline CT_RS_IndicationType*        
TL1_FacilityEdParameters::GetAisType() const
{
    return myAisType;
}

inline void                         
TL1_FacilityEdParameters::SetAisType(CT_RS_IndicationType* theAisType)
{
    myAisType = theAisType;
}

inline uint16*        
TL1_FacilityEdParameters::GetBurstyBerSdInterval() const
{
    return myBurstyBerSdInterval;
}

inline void                         
TL1_FacilityEdParameters::SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval)
{
    myBurstyBerSdInterval = theBurstyBerSdInterval;
}

inline uint32*        
TL1_FacilityEdParameters::GetBurstyBerSdThreshold() const
{
    return myBurstyBerSdThreshold;
}

inline void                         
TL1_FacilityEdParameters::SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold)
{
    myBurstyBerSdThreshold = theBurstyBerSdThreshold;
}

//--------------------------------------------------------------------------------
inline CT_TEL_TS_SIZE*           
TL1_FacilityEdParameters::GetTribSize( ) const
{
    return myTribSize;
}

inline void                         
TL1_FacilityEdParameters::SetTribSize( CT_TEL_TS_SIZE* theTribSize )
{
    myTribSize = theTribSize;
}

//--------------------------------------------------------------------------------
inline int*           
TL1_FacilityEdParameters::GetNpOwner( ) const
{
    return myNpOwner;
}

inline void                         
TL1_FacilityEdParameters::SetNpOwner( int* theNpOwner )
{
    myNpOwner = theNpOwner;
}

inline CT_Fac_TraceString* TL1_FacilityEdParameters::GetExpOperator() const
{
    return myExpOperator;
}

inline void TL1_FacilityEdParameters::SetExpOperator(CT_Fac_TraceString* theExpOperator)
{
    myExpOperator = theExpOperator;
}

inline CT_Fac_TraceString* TL1_FacilityEdParameters::GetTxOperator() const
{
    return myTxOperator;
}

inline void TL1_FacilityEdParameters::SetTxOperator(CT_Fac_TraceString* theTxOperator)
{
    myTxOperator = theTxOperator;
}

//--------------------------------------------------------------------------------
inline CT_TEL_OPU_FORMAT* TL1_FacilityEdParameters::GetOpuConfig() const
{
    return myOpuConfig;
}

//--------------------------------------------------------------------------------
inline void TL1_FacilityEdParameters::SetOpuConfig(CT_TEL_OPU_FORMAT* theOpuConfig)
{
    myOpuConfig = theOpuConfig;
}

//--------------------------------------------------------------------------------
inline bool* TL1_FacilityEdParameters::GetOTNMap() const
{
    return myOTNMap;
}

inline void TL1_FacilityEdParameters::SetOTNMap(bool* theOTNMap)
{
    myOTNMap = theOTNMap;
}
//--------------------------------------------------------------------------------
inline CT_TEL_PayloadType* TL1_FacilityEdParameters::GetMapMode() const
{
    return myMapMode;
}

inline void TL1_FacilityEdParameters::SetMapMode(CT_TEL_PayloadType* theMapMode)
{
    myMapMode = theMapMode;
}
//--------------------------------------------------------------------------------

#endif
