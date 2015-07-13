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

#ifndef __TL1_FACILITYENTPARAMETERS_H__
#define __TL1_FACILITYENTPARAMETERS_H__

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


class TL1_FacilityEntParameters  
{
public:
    
    TL1_FacilityEntParameters();

    virtual ~TL1_FacilityEntParameters();

    TL1_FacilityEntParameters& operator=( const TL1_FacilityEntParameters& theBlock );

    bool operator==( const TL1_FacilityEntParameters& theBlock ) const;

    inline CT_ProfileTableId*           GetAlarmProfile( ) const;
    inline void                         SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile );

    inline CT_Fac_TraceString*          GetTrace( ) const;
    inline void                         SetTrace( CT_Fac_TraceString* theTrace );

    inline CT_Fac_TraceString*          GetExpectedTrace( ) const;
    inline void                         SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace );

    inline bool*                        GetIsMonitorTraceEnabled( ) const;
    inline void                         SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled );

    inline bool*                        GetIsInsertAisEnabled( ) const;
    inline void                         SetIsInsertAisEnabled( bool* theIsInsertAisEnabled );

    inline CT_TEL_HopSpeMapping*        GetMapping( ) const;
    inline void                         SetMapping( CT_TEL_HopSpeMapping* theMapping );

    inline CT_TEL_BERLevels*            GetSFThreshold( ) const;
    inline void                         SetSFThreshold( CT_TEL_BERLevels* theSFThreshold );
 
    inline CT_TEL_BERLevels*            GetSDThreshold( ) const;
    inline void                         SetSDThreshold( CT_TEL_BERLevels* theSDThreshold ); 

    inline CT_FAC_ExternalConnectivity* GetExternalConnectivity( ) const;
    inline void                         SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConnectivity ); 

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

    inline CT_TEL_SignalType*           GetSignalType( ) const;
    inline void                         SetSignalType( CT_TEL_SignalType* theSignalType );

    inline CT_FAC_StsMap*               GetStsMap( ) const;
    inline void                         SetStsMap( CT_FAC_StsMap* theStsMap ); 

    inline CT_SM_PST*                   GetPrimaryState( ) const;
    inline void                         SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline CT_FAC_LineCode*             GetLineCode( ) const;   
    inline void                         SetLineCode( CT_FAC_LineCode* theLineCode );

    inline CT_FAC_FrameFormat*          GetSignalFrameFormat( ) const;
    inline void                         SetSignalFrameFormat( CT_FAC_FrameFormat* theSignalFrameFormat ); 

    inline bool*                        GetIsTransparent( ) const;
    inline void                         SetIsTransparent( bool* theIsTransparent );

    inline bool*                        GetIsSsmConnected( ) const;
    inline void                         SetIsSsmConnected( bool* theIsSsmConnected ); 

    inline CT_Fac_ConnectedToString*    GetConnectedTo( ) const;
    inline void                         SetConnectedTo( CT_Fac_ConnectedToString* theConectedTo ); 

    inline CT_TEL_GbeFramingMode*       GetGbeFramingMode( ) const;
    inline void                         SetGbeFramingMode( CT_TEL_GbeFramingMode* theGbeFramingMode ); 

    inline bool*                        GetGenTrc( ) const;
    inline void                         SetGenTrc( bool* theGenTrc ); 

    inline bool*                        GetIsTrafficEnabled( ) const;
    inline void                         SetIsTrafficEnabled( bool* theIsTrafficEnabled ); 

    inline CT_TEL_GfpFramingMode*       GetGfpMap( ) const;
    inline void                         SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap ); 

    inline bool*                        GetNendALS( ) const;
    inline void                         SetNendALS( bool* theNendALS ); 

    inline CT_TEL_Map_ENUM*             GetHgeMap( ) const;
    inline void                         SetHgeMap( CT_TEL_Map_ENUM* theHgeMap ); 

    inline CT_FAC_NValue*               GetNValue( ) const;
    inline void                         SetNValue( CT_FAC_NValue* theNValue ); 

    inline CT_TEL_FecType*              GetFecType( ) const;
    inline void                         SetFecType( CT_TEL_FecType* theFecType ); 

    inline CT_Fac_TraceString*          GetOtuExpTrc( ) const;
    inline void                         SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc ); 

    inline CT_Fac_TraceString*          GetOtuTrc( ) const;
    inline void                         SetOtuTrc( CT_Fac_TraceString* theOtuTrc ); 

    inline CT_TEL_SignalType*           GetTransMap( ) const;
    inline void                         SetTransMap( CT_TEL_SignalType* theTransMap ); 

    inline CT_TEL_SignalType*           GetClkType( ) const;
    inline void                         SetClkType( CT_TEL_SignalType* theClkType ); 

    inline CT_TapNumber*                GetTapNumber( ) const;
    inline void                         SetTapNumber( CT_TapNumber* theTapNumber ); 

    inline bool*                        GetIsAutoNegotiationEnabled( ) const;
    inline void                         SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled );

    inline CT_TEL_OEO_REGEN_MODE*       GetOeoRegen( ) const;
    inline void                         SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen );

    inline CT_TEL_TermSize*             GetCnvTermType( ) const;
    inline void                         SetCnvTermType( CT_TEL_TermSize* theCnvTermType );
    
    inline CT_TEL_PayloadSignalId*      GetPt() const;
    inline void                         SetPt( CT_TEL_PayloadSignalId* thePt );

    inline CT_TEL_GfpUpiId*             GetGfpUpi() const;
    inline void                         SetGfpUpi( CT_TEL_GfpUpiId* theUpi );

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

    inline LT_Handle*                   GetHandle( ) const;
    inline void                         SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                      GetCtag( ) const;
    inline void                         SetCtag( LT_Ctag theCtag );

    inline CT_PMProfileTableId*         GetPmProfile( ) const;
    inline void                         SetPmProfile(  CT_PMProfileTableId* thePmProfile );

    inline int*                         GetCFProfile( ) const;
    inline void                         SetCFProfile(  int* theCFProfile );

    inline CT_TEL_PayloadType*  GetCbrMap() const;
    inline void                  SetCbrMap(CT_TEL_PayloadType* theCbrMap);

    inline CT_TCM_ADJACENT*                GetAdjacent() const;
    inline void                         SetAdjacent( CT_TCM_ADJACENT* theAdjacentBuf );

    inline CT_FAC_OduTsMap *            GetTribSlot() const;
    inline void                         SetTribSlot(CT_FAC_OduTsMap* theTribSlot);

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

    inline CT_FAC_QualityLevelOverride* GetQualityLevel() const;
    inline void                         SetQualityLevel(CT_FAC_QualityLevelOverride* theQualityLevel);

    inline CT_TEL_TimCriteriaMode* GetTimDef() const;
    inline void              SetTimDef(CT_TEL_TimCriteriaMode* theTimDef);

    inline CT_Fac_TraceString*   GetExpDapi() const;
    inline void                     SetExpDapi(CT_Fac_TraceString* theExceptedDapi);

    inline CT_Fac_TraceString*   GetExpSapi() const;
    inline void                     SetExpSapi(CT_Fac_TraceString* theExceptedSapi);

    inline CT_Fac_TraceString*   GetTxDapi() const;
    inline void                     SetTxDapi(CT_Fac_TraceString * theTxDapi);

    inline CT_Fac_TraceString*   GetTxSapi() const;
    inline void                     SetTxSapi(CT_Fac_TraceString * theTxSapi);
    
    inline uint32*               GetExtChannel() const;
    inline void                         SetExtChannel(uint32* theExtChannel);

    inline CT_TEL_OTIDStatus*           GetOTIDStatus( ) const;
    inline void                         SetOTIDStatus(CT_TEL_OTIDStatus* theOTIDStatus);

    inline int*                         GetHoldOffProt( ) const;
    inline void                         SetHoldOffProt( int* theHoldOffProt );

    inline CT_TEL_LacpPartiMode*        GetLacpParticipation( ) const;
    inline void                         SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation );

    inline int*                         GetLacpPriority( ) const;
    inline void                         SetLacpPriority( int* theLacpPriority );

    inline CT_RS_IndicationType*        GetAisType() const;
    inline void                         SetAisType(CT_RS_IndicationType* theAisType);

    inline CT_TEL_TS_SIZE*              GetTribSize( ) const;
    inline void                         SetTribSize( CT_TEL_TS_SIZE* theTribSize );

    inline uint16*                      GetBurstyBerSdInterval() const;
    inline void                         SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval);

    inline uint32*                      GetBurstyBerSdThreshold() const;
    inline void                         SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold);

    inline uint8 *                      GetInterPacketGap() const;
    inline void                         SetInterPacketGap(uint8* theInterPacketGap);

    bool                                IsControlPlaneRequest();

    inline bool*                        GetIsAutoAdjustAttenuationEnabled( ) const;
    inline void                         SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled );

    inline CT_Fac_TraceString*          GetExpOperator() const;
    inline void                         SetExpOperator(CT_Fac_TraceString* theExpOperator);

    inline CT_Fac_TraceString*          GetTxOperator() const;
    inline void                         SetTxOperator(CT_Fac_TraceString* theTxOperator);

    inline CT_TEL_OPU_FORMAT*           GetOpuConfig() const;
    inline void                         SetOpuConfig(CT_TEL_OPU_FORMAT* theOpuConfig);

    inline bool*                        GetOTNMap() const;
    inline void                         SetOTNMap(bool* theOTNMap);

    inline CT_TEL_PayloadType*          GetMapMode() const;
    inline void                         SetMapMode(CT_TEL_PayloadType* theOTNMap);

    inline bool*                        GetQuarantine( ) const;
    inline void                         SetQuarantine( bool* theQua );

    inline CT_FAC_PluggableReach*       GetPluggableReach( ) const;
    inline void                         SetPluggableReach( CT_FAC_PluggableReach* thePluggableReach );

protected:

    CT_ProfileTableId*            myAlarmProfile;
    CT_Fac_TraceString*           myTrace;
    CT_Fac_TraceString*           myExpectedTrace;
    bool*                         myIsMonitorTraceEnabled;
    bool*                         myIsInsertAisEnabled;
    CT_TEL_HopSpeMapping*         myMapping;
    CT_TEL_BERLevels*             mySFThreshold;
    CT_TEL_BERLevels*             mySDThreshold;
    CT_FAC_ExternalConnectivity*  myExternalConectivity;
    CT_FAC_Protection*            myIsProtectionEnabled;
    CT_FAC_MaintProp*             myMaintProp;
    bool*                         myIsAdaptiveEnabled;
    CT_TEL_daHz*                  myMaxRate;
    CT_TL1_ExpectedRateRange*     myExpectedSignalRate;
    CT_FAC_SignalRateListType*    myRateList;
    CT_TEL_SignalType*            mySignalType;
    CT_FAC_StsMap*                myStsMap;
    CT_SM_PST*                    myPrimaryState;
    CT_FAC_LineCode*              myLineCode;           
    CT_FAC_FrameFormat*           mySignalFrameFormat;
    bool*                         myIsTransparent;
    bool*                         myIsSsmConnected;
    CT_Fac_ConnectedToString*     myConectedTo;
    CT_TEL_GbeFramingMode*        myGbeFramingMode;
    bool*                         myGenTrc;
    bool*                         myIsTrafficEnabled;
    CT_TEL_GfpFramingMode*        myGfpMap;
    bool*                         myNendALS;
    CT_TEL_Map_ENUM*              myHgeMap;
    CT_FAC_NValue*                myNValue;
    CT_TEL_FecType*               myFecType;     
    CT_Fac_TraceString*           myOtuExpTrc;
    CT_Fac_TraceString*           myOtuTrc; 
    CT_TEL_SignalType*            myTransMap;
    CT_TEL_SignalType*            myClkType;
    CT_TapNumber*                 myTapNumber;
    bool*                         myIsAutoNegotiationEnabled;
    CT_TEL_OEO_REGEN_MODE*        myOeoRegen;
    CT_TEL_TermSize*              myCnvTermType;
    CT_TEL_PayloadSignalId*       myPt;
    CT_TEL_PayloadSignalId*       myGfpUpi;
    CT_TEL_daHz*                  myEthRate;
    CT_TEL_MAC_DUPLEX_MODE*       myDuplexMode;
    CT_TCM_Mode*                  myTcmMode;
    CT_TEL_MAC_ADFLW_CTRL*        myFlowAd;
    CT_TEL_MAC_FLOWCTRL*          myFlowCtrl;
    CT_TEL_VlanTag*               myVlanTag;
    bool*                         myTagMode;
    CT_TEL_Tpid*                  myTpid;
    bool*                         myDiscardPause;
    bool*                         myPropFefi;
    LT_Handle*                    myHandle;
    LT_Ctag                       myCtag;
    CT_PMProfileTableId*          myPmProfile;
    int*                          myCFProfile;
    CT_TEL_PayloadType*           myCbrMap;
    CT_TCM_ADJACENT*              myAdjacent;
    CT_FAC_OduTsMap*              myTribSlot;
    CT_TEL_GFP_MUX*               myGfpMux;
    //CT_RelativeWavelength*        myExtChannel;
    uint32*                       myExtChannel;
    CT_TEL_OTIDStatus*            myOTIDStatus;
    int*                          myHoldOffProt;
    CT_TEL_TimCriteriaMode*       myTimDef;
    CT_Fac_TraceString*           myExpDapi;
    CT_Fac_TraceString*           myExpSapi;
    CT_Fac_TraceString*           myTxDapi;
    CT_Fac_TraceString*           myTxSapi;
    CT_TEL_LacpPartiMode*         myLacpParticipation;
    int *                         myLacpPriority;
    CT_RS_IndicationType*         myAisType;
    CT_TEL_TS_SIZE*               myTribSize;
    uint16*                       myBurstyBerSdInterval;
    uint32*                       myBurstyBerSdThreshold;
    bool *                        myTribFall;
    uint8*                        myGfpTs;
    uint8*                        myInterPacketGap;
    bool *                        myLtcActMode;
    bool *                        myDmSource;
    CT_TEL_OPU_FORMAT*            myOpuConfig;
    CT_FAC_QualityLevelOverride*  myQualityLevel;   // Tx SSM forcing
    bool*                         myIsAutoAdjustAttenuationEnabled;
    CT_Fac_TraceString*           myExpOperator;
    CT_Fac_TraceString*           myTxOperator;
    bool *                        myOTNMap;
    CT_TEL_PayloadType*           myMapMode;
    bool *                        myQua;
    CT_FAC_PluggableReach*        myPluggableReach;
};

class TL1_FacilityValidateEntParameters  
{
public:

    enum EnterableParameters 
    {
        AlarmProfileEnterable = 0,
        TraceEnterable,
        ExpectedTraceEnterable,
        IsMonitorTraceEnabledEnterable,
        IsInsertAisEnabledEnterable,
        MappingEnterable,
        SFThresholdEnterable,
        SDThresholdEnterable,
        ExternalConnectivityEnterable,
        IsProtectionEnabledEnterable,
        MaintPropEnterable,
        IsAdaptiveEnabledEnterable,
        MaxRateEnterable,
        ExpectedSignalRateEnterable,
        RateListEnterable,
        SignalTypeEnterable,
        StsMapEnterable,
        PrimaryStateEnterable,
        LineCodeEnterable,
        SignalFrameFormatEnterable,
        IsTransparentEnterable,
        IsSsmConnectedEnterable,
        ConnectedToEnterable,
        GbeFramingModeEnterable,
        GenTrcEnterable,
        IsTrafficEnabledEnterable,
        GfpMapEnterable,
        NendALSEnterable,
        HgeMap,
        NValueEnterable,
        FecTypeEnterable,     
        OtuExpTrcEnterable,
        OtuTrcEnterable, 
        TransMapEnterable,
        ClkTypeEnterable,
        TapNumberEnterable,
        IsAutoNegotiationEnabledEnterable,
        OeoRegenEnterable,
        CnvTermTypeEnterable,
        PtEnterable,
        GfpUpiEnterable,
        HandleEnterable,
        CtagEnterable,
        EthRateEnterable,
        DuplexModeEnterable,
        TcmModeEnterable,
        FlowAdEnterable,
        FlowCtrlEnterable,
        VlanTagEnterable,
        TagModeEnterable,
        TpidEnterable,
        DiscardPauseEnterable,
        PropFefiEnterable,
        PmProfileEnterable,
        CFProfileEnterable,
        CbrMapEnterable,
        AdjacentEntable,
        TribSlotEnterable,
        GfpMuxEnterable,
        TimDefEnterable,
        ExpDapiEnterable,
        ExpSapiEnterable,
        TxDapiEnterable,
        TxSapiEnterable,
        ExtChannelEnterable,
        OTIDStatusEnterable,
        HoldOffProtEnterable,
        LacpParticipationEnterable,
        LacpPriorityEnterable,
        AisTypeEnterable,
        TribSizeEnterable,
        BurstyBerSdIntervalEnterable,
        BurstyBerSdThresholdEnterable,
        TribFallEnterable,
        GfpTsEnterable,
        DmSourceEnterable,
        OpuConfigEnterable,
        LtcActModeEnterable,
        QualityLevelEnterable,
        InterPacketGapEnterable,
        AutoAdjustAttenuationEnabledEnterable,
        ExpOperatorEnterable,
        TxOperatorEnterable,
        OTNMapEnable,
        MapModeEnable,
        QuaEnterable,
        PluggableReachEnterable,
        AnyParameters               /* this should always be the last enum */
    };
    
    TL1_FacilityValidateEntParameters();

    virtual ~TL1_FacilityValidateEntParameters();

    void ValidateEnterParameters( const TL1_FacilityEntParameters& theEntParameters ) const;

    inline vector<bool>& GetEntParametersSet( );

private:
    vector<bool>       myEntParametersSet;

};

//--------------------------------------------------------------------------------
inline CT_ProfileTableId*           
TL1_FacilityEntParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_FacilityEntParameters::SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEntParameters::GetTrace( ) const
{
    return myTrace;
}

inline void                         
TL1_FacilityEntParameters::SetTrace( CT_Fac_TraceString* theTrace )
{
    myTrace = theTrace;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEntParameters::GetExpectedTrace( ) const
{
    return myExpectedTrace;
}

inline void                         
TL1_FacilityEntParameters::SetExpectedTrace( CT_Fac_TraceString* theExpectedTrace )
{
    myExpectedTrace = theExpectedTrace;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetIsMonitorTraceEnabled( ) const
{
    return myIsMonitorTraceEnabled;
}

inline void                         
TL1_FacilityEntParameters::SetIsMonitorTraceEnabled( bool* theIsMonitorTraceEnabled )
{
    myIsMonitorTraceEnabled = theIsMonitorTraceEnabled;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetIsInsertAisEnabled( ) const
{
    return myIsInsertAisEnabled;
}

inline void                         
TL1_FacilityEntParameters::SetIsInsertAisEnabled( bool* theIsInsertAisEnabled )
{
    myIsInsertAisEnabled = theIsInsertAisEnabled;
}
//--------------------------------------------------------------------------------

inline CT_TEL_HopSpeMapping*        
TL1_FacilityEntParameters::GetMapping( ) const
{
    return myMapping;
}

inline void                         
TL1_FacilityEntParameters::SetMapping( CT_TEL_HopSpeMapping* theMapping )
{
    myMapping = theMapping;
}
//--------------------------------------------------------------------------------

inline CT_TEL_BERLevels*            
TL1_FacilityEntParameters::GetSFThreshold( ) const
{
    return mySFThreshold;
}

inline void                         
TL1_FacilityEntParameters::SetSFThreshold( CT_TEL_BERLevels* theSFThreshold )
{
    mySFThreshold = theSFThreshold;
}
//-------------------------------------------------------------------------------- 

inline CT_TEL_BERLevels*            
TL1_FacilityEntParameters::GetSDThreshold( ) const
{
    return mySDThreshold;
}

inline void                         
TL1_FacilityEntParameters::SetSDThreshold( CT_TEL_BERLevels* theSDThreshold ) 
{
    mySDThreshold = theSDThreshold;
}
//--------------------------------------------------------------------------------

inline CT_FAC_ExternalConnectivity* 
TL1_FacilityEntParameters::GetExternalConnectivity( ) const
{
    return myExternalConectivity;
}

inline void                         
TL1_FacilityEntParameters::SetExternalConnectivity( CT_FAC_ExternalConnectivity* theExternalConectivity ) 
{
    myExternalConectivity = theExternalConectivity;
}
//--------------------------------------------------------------------------------

inline CT_FAC_Protection*                        
TL1_FacilityEntParameters::GetIsProtectionEnabled( ) const
{
    return myIsProtectionEnabled;
}

inline void                         
TL1_FacilityEntParameters::SetIsProtectionEnabled( CT_FAC_Protection* theIsProtectionEnabled )
{
    myIsProtectionEnabled = theIsProtectionEnabled;
}
//--------------------------------------------------------------------------------

inline CT_FAC_MaintProp*                        
TL1_FacilityEntParameters::GetMaintPropagate( ) const
{
    return myMaintProp;
}

inline void                         
TL1_FacilityEntParameters::SetMaintPropagate( CT_FAC_MaintProp* theMaintProp )
{
    myMaintProp = theMaintProp;
}

//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetIsAdaptiveEnabled( ) const
{
    return myIsAdaptiveEnabled;
}

inline void                         
TL1_FacilityEntParameters::SetIsAdaptiveEnabled( bool* theIsAdaptiveEnabled )
{
    myIsAdaptiveEnabled = theIsAdaptiveEnabled;
}
//--------------------------------------------------------------------------------

inline CT_TEL_daHz*                 
TL1_FacilityEntParameters::GetMaxRate( ) const
{
    return myMaxRate;
}

inline void                         
TL1_FacilityEntParameters::SetMaxRate( CT_TEL_daHz* theMaxRate ) 
{
    myMaxRate = theMaxRate;
}
//--------------------------------------------------------------------------------

inline CT_TL1_ExpectedRateRange*    
TL1_FacilityEntParameters::GetExpectedSignalRate( ) const
{
    return myExpectedSignalRate;
}

inline void                         
TL1_FacilityEntParameters::SetExpectedSignalRate( CT_TL1_ExpectedRateRange* theExpectedSignalRate ) 
{
    myExpectedSignalRate = theExpectedSignalRate;
}
//--------------------------------------------------------------------------------

inline CT_FAC_SignalRateListType*   
TL1_FacilityEntParameters::GetRateList( ) const
{
    return myRateList;
}

inline void                         
TL1_FacilityEntParameters::SetRateList( CT_FAC_SignalRateListType* theRateList )
{
    myRateList = theRateList;
}
//--------------------------------------------------------------------------------

inline CT_TEL_SignalType*           
TL1_FacilityEntParameters::GetSignalType( ) const
{
    return mySignalType;
}

inline void                         
TL1_FacilityEntParameters::SetSignalType( CT_TEL_SignalType* theSignalType )
{
    mySignalType = theSignalType;
}
//--------------------------------------------------------------------------------

inline CT_FAC_StsMap*               
TL1_FacilityEntParameters::GetStsMap( ) const
{
    return myStsMap;
}

inline void                         
TL1_FacilityEntParameters::SetStsMap( CT_FAC_StsMap* theStsMap ) 
{
    myStsMap = theStsMap;
}
//--------------------------------------------------------------------------------

inline CT_SM_PST*                   
TL1_FacilityEntParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_FacilityEntParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}
//--------------------------------------------------------------------------------

inline CT_FAC_LineCode*             
TL1_FacilityEntParameters::GetLineCode( ) const     
{
    return myLineCode;
}

inline void                         
TL1_FacilityEntParameters::SetLineCode( CT_FAC_LineCode* theLineCode )
{
    myLineCode = theLineCode;
}
//--------------------------------------------------------------------------------

inline CT_FAC_FrameFormat*          
TL1_FacilityEntParameters::GetSignalFrameFormat( ) const
{
    return mySignalFrameFormat;
}

inline void                         
TL1_FacilityEntParameters::SetSignalFrameFormat( CT_FAC_FrameFormat* theSignalFrameFormat ) 
{
    mySignalFrameFormat = theSignalFrameFormat;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetIsTransparent( ) const
{
    return myIsTransparent;
}

inline void                         
TL1_FacilityEntParameters::SetIsTransparent( bool* theIsTransparent )
{
    myIsTransparent = theIsTransparent;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetIsSsmConnected( ) const
{
    return myIsSsmConnected;
}

inline void                         
TL1_FacilityEntParameters::SetIsSsmConnected( bool* theIsSsmConnected ) 
{
    myIsSsmConnected = theIsSsmConnected;
}
//--------------------------------------------------------------------------------

inline CT_Fac_ConnectedToString*    
TL1_FacilityEntParameters::GetConnectedTo( ) const
{
    return myConectedTo;
}

inline void                         
TL1_FacilityEntParameters::SetConnectedTo( CT_Fac_ConnectedToString* theConectedTo ) 
{
    myConectedTo = theConectedTo;
}
//--------------------------------------------------------------------------------

inline CT_TEL_GbeFramingMode*       
TL1_FacilityEntParameters::GetGbeFramingMode( ) const
{
    return myGbeFramingMode;
}

inline void                         
TL1_FacilityEntParameters::SetGbeFramingMode( CT_TEL_GbeFramingMode* theGbeFramingMode ) 
{
    myGbeFramingMode = theGbeFramingMode;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetGenTrc( ) const
{   
    return myGenTrc;
}

inline void                         
TL1_FacilityEntParameters::SetGenTrc( bool* theGenTrc ) 
{
    myGenTrc = theGenTrc;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetIsTrafficEnabled( ) const
{   
    return myIsTrafficEnabled;
}

inline void                         
TL1_FacilityEntParameters::SetIsTrafficEnabled( bool* theIsTrafficEnabled ) 
{
    myIsTrafficEnabled = theIsTrafficEnabled;
}
//--------------------------------------------------------------------------------

inline CT_TEL_GfpFramingMode*       
TL1_FacilityEntParameters::GetGfpMap( ) const
{   
    return myGfpMap;
}

inline void                         
TL1_FacilityEntParameters::SetGfpMap( CT_TEL_GfpFramingMode* theGfpMap ) 
{
    myGfpMap = theGfpMap;
}
//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetNendALS( ) const
{
    return myNendALS;
}

inline void                         
TL1_FacilityEntParameters::SetNendALS( bool* theNendALS ) 
{
    myNendALS = theNendALS;
}
//--------------------------------------------------------------------------------

inline CT_TEL_Map_ENUM*                        
TL1_FacilityEntParameters::GetHgeMap( ) const
{
    return myHgeMap;
}

inline void                         
TL1_FacilityEntParameters::SetHgeMap( CT_TEL_Map_ENUM* theHgeMap ) 
{
    myHgeMap = theHgeMap;
}
//--------------------------------------------------------------------------------

inline CT_FAC_NValue*               
TL1_FacilityEntParameters::GetNValue( ) const
{
    return myNValue;
}

inline void                         
TL1_FacilityEntParameters::SetNValue( CT_FAC_NValue* theNValue ) 
{
    myNValue = theNValue;
}
//--------------------------------------------------------------------------------

inline CT_TEL_FecType*              
TL1_FacilityEntParameters::GetFecType( ) const
{
    return myFecType;
}

inline void                         
TL1_FacilityEntParameters::SetFecType( CT_TEL_FecType* theFecType ) 
{
    myFecType = theFecType;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEntParameters::GetOtuExpTrc( ) const
{
    return myOtuExpTrc;
}

inline void                         
TL1_FacilityEntParameters::SetOtuExpTrc( CT_Fac_TraceString* theOtuExpTrc ) 
{
    myOtuExpTrc = theOtuExpTrc;
}
//--------------------------------------------------------------------------------

inline CT_Fac_TraceString*          
TL1_FacilityEntParameters::GetOtuTrc( ) const
{
    return myOtuTrc;
}

inline void                         
TL1_FacilityEntParameters::SetOtuTrc( CT_Fac_TraceString* theOtuTrc ) 
{
    myOtuTrc = theOtuTrc;
}
//--------------------------------------------------------------------------------

inline CT_TEL_SignalType*           
TL1_FacilityEntParameters::GetTransMap( ) const
{
    return myTransMap;
}

inline void                         
TL1_FacilityEntParameters::SetTransMap( CT_TEL_SignalType* theTransMap ) 
{
    myTransMap = theTransMap;
}
//--------------------------------------------------------------------------------

inline CT_TEL_SignalType*           
TL1_FacilityEntParameters::GetClkType( ) const
{
    return myClkType;
}

inline void                         
TL1_FacilityEntParameters::SetClkType( CT_TEL_SignalType* theClkType ) 
{
    myClkType = theClkType;
}

//--------------------------------------------------------------------------------

inline CT_TapNumber*           
TL1_FacilityEntParameters::GetTapNumber( ) const
{
    return myTapNumber;
}

inline void                         
TL1_FacilityEntParameters::SetTapNumber( CT_TapNumber* theTapNumber ) 
{
    myTapNumber = theTapNumber;
}

//--------------------------------------------------------------------------------

inline bool*
TL1_FacilityEntParameters::GetIsAutoNegotiationEnabled( ) const
{
    return myIsAutoNegotiationEnabled;
}

inline void
TL1_FacilityEntParameters::SetIsAutoNegotiationEnabled( bool* theIsAutoNegotiationEnabled )
{
    myIsAutoNegotiationEnabled = theIsAutoNegotiationEnabled;
}

//--------------------------------------------------------------------------------

inline CT_TEL_OEO_REGEN_MODE*
TL1_FacilityEntParameters::GetOeoRegen( ) const
{
    return myOeoRegen;
}

inline void
TL1_FacilityEntParameters::SetOeoRegen( CT_TEL_OEO_REGEN_MODE* theOeoRegen )
{
    myOeoRegen = theOeoRegen;
}

//--------------------------------------------------------------------------------

inline CT_TEL_TermSize*
TL1_FacilityEntParameters::GetCnvTermType( ) const
{
    return myCnvTermType;
}

inline void
TL1_FacilityEntParameters::SetCnvTermType( CT_TEL_TermSize* theCnvTermType )
{
    myCnvTermType = theCnvTermType;
}

//---------------------------------------------------------------------------------

inline LT_Handle*                   
TL1_FacilityEntParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_FacilityEntParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}
//--------------------------------------------------------------------------------

inline LT_Ctag                    
TL1_FacilityEntParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_FacilityEntParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}
//--------------------------------------------------------------------------------

inline CT_TEL_PayloadSignalId*
TL1_FacilityEntParameters::GetPt( ) const
{
    return myPt;
}

inline void
TL1_FacilityEntParameters::SetPt( CT_TEL_PayloadSignalId* thePt )
{
    myPt = thePt;
}

//--------------------------------------------------------------------------------

inline CT_TEL_GfpUpiId*
TL1_FacilityEntParameters::GetGfpUpi( ) const
{
    return myGfpUpi;
}

inline void
TL1_FacilityEntParameters::SetGfpUpi( CT_TEL_GfpUpiId* theUpi )
{
    myGfpUpi = theUpi;
}

//--------------------------------------------------------------------------------
inline CT_TEL_daHz* 
TL1_FacilityEntParameters::GetEthRate( ) const
{
    return myEthRate;
}
inline void
TL1_FacilityEntParameters::SetEthRate( CT_TEL_daHz* theEthRate )
{
    myEthRate = theEthRate;
}

//--------------------------------------------------------------------------------
inline CT_TEL_MAC_DUPLEX_MODE*
TL1_FacilityEntParameters::GetDuplexMode( ) const
{
    return myDuplexMode;
}
inline void
TL1_FacilityEntParameters::SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode )
{
    myDuplexMode = theDuplexMode;
}

//--------------------------------------------------------------------------------
inline CT_TCM_Mode*
TL1_FacilityEntParameters::GetTcmMode( ) const
{
    return myTcmMode;
}
inline void
TL1_FacilityEntParameters::SetTcmMode( CT_TCM_Mode* theTcmMode )
{
    myTcmMode = theTcmMode;
}

//--------------------------------------------------------------------------------
inline CT_TEL_MAC_ADFLW_CTRL*
TL1_FacilityEntParameters::GetFlowCtrlAd( ) const
{
    return myFlowAd;
}
inline void
TL1_FacilityEntParameters::SetFlowCtrlAd( CT_TEL_MAC_ADFLW_CTRL* theFlowAd )
{
    myFlowAd = theFlowAd;
}

//--------------------------------------------------------------------------------
inline CT_TEL_MAC_FLOWCTRL*
TL1_FacilityEntParameters::GetFlowCtrlEnable( ) const
{
    return myFlowCtrl;
}
inline void
TL1_FacilityEntParameters::SetFlowCtrlEnable( CT_TEL_MAC_FLOWCTRL* theFlowCtrl )
{
    myFlowCtrl = theFlowCtrl;
}
//-------------------------------------------------------------------------------
inline CT_TEL_VlanTag*
TL1_FacilityEntParameters::GetVLanTag( ) const
{
    return myVlanTag;
}
inline void
TL1_FacilityEntParameters::SetVLanTag( CT_TEL_VlanTag* theVTag )
{
    myVlanTag = theVTag;
}
//-------------------------------------------------------------------------------
inline bool*
TL1_FacilityEntParameters::GetTagMode( ) const
{
    return myTagMode;
}
inline void
TL1_FacilityEntParameters::SetTagMode( bool* theTagMode )
{
    myTagMode = theTagMode;
}
//-------------------------------------------------------------------------------
inline CT_TEL_Tpid*
TL1_FacilityEntParameters::GetTPid( ) const
{
    return myTpid;
}
inline void
TL1_FacilityEntParameters::SetTPid( CT_TEL_Tpid* theTPid )
{
    myTpid = theTPid;
}


//--------------------------------------------------------------------------------
inline bool*                        
TL1_FacilityEntParameters::GetDiscardPause( ) const
{
    return myDiscardPause;
}

inline void                         
TL1_FacilityEntParameters::SetDiscardPause( bool* theDiscardPause ) 
{
    myDiscardPause = theDiscardPause;
}


//--------------------------------------------------------------------------------
inline bool*                        
TL1_FacilityEntParameters::GetPropFefi( ) const
{
    return myPropFefi;
}

inline void                         
TL1_FacilityEntParameters::SetPropFefi( bool* thePropFefi ) 
{
    myPropFefi = thePropFefi;
}


//--------------------------------------------------------------------------------

inline vector<bool>& 
TL1_FacilityValidateEntParameters::GetEntParametersSet( )
{
    return myEntParametersSet;
}
//--------------------------------------------------------------------------------
inline CT_PMProfileTableId*           
TL1_FacilityEntParameters::GetPmProfile( ) const
{
    return myPmProfile;
}

inline void                         
TL1_FacilityEntParameters::SetPmProfile(  CT_PMProfileTableId* thePmProfile )
{
    myPmProfile = thePmProfile;
}

//--------------------------------------------------------------------------------
inline int*           
TL1_FacilityEntParameters::GetCFProfile( ) const
{
    return myCFProfile;
}

inline void                         
TL1_FacilityEntParameters::SetCFProfile(  int* theCFProfile )
{
    myCFProfile = theCFProfile;
}

inline CT_TEL_PayloadType* 
TL1_FacilityEntParameters::GetCbrMap() const
{
    return myCbrMap;
}

inline void 
TL1_FacilityEntParameters::SetCbrMap(CT_TEL_PayloadType * theCbrMap)
{
    myCbrMap = theCbrMap;
}


//--------------------------------------------------------------------------------
inline CT_TCM_ADJACENT*    TL1_FacilityEntParameters::GetAdjacent() const
{
    return myAdjacent;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEntParameters::SetAdjacent(CT_TCM_ADJACENT* theAdjacentBuf )
{
    myAdjacent = theAdjacentBuf;
}

//--------------------------------------------------------------------------------

inline CT_FAC_OduTsMap *  TL1_FacilityEntParameters::GetTribSlot() const
{
    return myTribSlot;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEntParameters::SetTribSlot(CT_FAC_OduTsMap* theTribSlot)
{
    myTribSlot = theTribSlot;
}

//--------------------------------------------------------------------------------
inline bool *              TL1_FacilityEntParameters::GetTribFall() const
{
    return myTribFall;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEntParameters::SetTribFall(bool* theTribFall)
{
    myTribFall = theTribFall;
}

//--------------------------------------------------------------------------------
inline bool *              TL1_FacilityEntParameters::GetDmSource() const
{
    return myDmSource;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEntParameters::SetDmSource(bool* theDmSource)
{
    myDmSource = theDmSource;
}

inline bool * TL1_FacilityEntParameters::GetLtcActMode() const
{
   return myLtcActMode;
}

inline void TL1_FacilityEntParameters::SetLtcActMode(bool* theLtcActMode)
{
  myLtcActMode = theLtcActMode;
}
//--------------------------------------------------------------------------------
inline uint8 *              TL1_FacilityEntParameters::GetGfpTs() const
{
    return myGfpTs;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEntParameters::SetGfpTs(uint8* theGfpTs)
{
    myGfpTs = theGfpTs;
}
//--------------------------------------------------------------------------------
inline uint8 *              TL1_FacilityEntParameters::GetInterPacketGap() const
{
    return myInterPacketGap;
}
//--------------------------------------------------------------------------------
inline void               TL1_FacilityEntParameters::SetInterPacketGap(uint8* theInterPacketGap)
{
    myInterPacketGap = theInterPacketGap;
}
//--------------------------------------------------------------------------------


inline CT_TEL_GFP_MUX* 
TL1_FacilityEntParameters::GetGfpMux() const
{
    return myGfpMux;
}

inline void 
TL1_FacilityEntParameters::SetGfpMux(CT_TEL_GFP_MUX * theGfpMux)
{
    myGfpMux= theGfpMux;
}

inline CT_FAC_QualityLevelOverride*
TL1_FacilityEntParameters::GetQualityLevel( ) const
{
    return myQualityLevel;
}

inline void                         
TL1_FacilityEntParameters::SetQualityLevel( CT_FAC_QualityLevelOverride* theQualityLevel )
{
    myQualityLevel = theQualityLevel;
}

inline CT_TEL_TimCriteriaMode* 
TL1_FacilityEntParameters::GetTimDef() const
{
    return myTimDef;
}

inline void 
TL1_FacilityEntParameters::SetTimDef(CT_TEL_TimCriteriaMode * theTimDef)
{
    myTimDef = theTimDef;
}

inline CT_Fac_TraceString* 
TL1_FacilityEntParameters::GetExpDapi() const
{
    return myExpDapi;
}

inline void 
TL1_FacilityEntParameters::SetExpDapi(CT_Fac_TraceString * theExpDapi)
{
    myExpDapi = theExpDapi;
}

inline CT_Fac_TraceString* 
TL1_FacilityEntParameters::GetExpSapi() const
{
    return myExpSapi;
}

inline void 
TL1_FacilityEntParameters::SetExpSapi(CT_Fac_TraceString * theExpSapi)
{
    myExpSapi = theExpSapi;
}

inline CT_Fac_TraceString* 
TL1_FacilityEntParameters::GetTxDapi() const
{
    return myTxDapi;
}

inline void 
TL1_FacilityEntParameters::SetTxDapi(CT_Fac_TraceString * theTxDapi)
{
    myTxDapi = theTxDapi;
}

inline CT_Fac_TraceString* 
TL1_FacilityEntParameters::GetTxSapi() const
{
    return myTxSapi;
}

inline void 
TL1_FacilityEntParameters::SetTxSapi(CT_Fac_TraceString * theTxSapi)
{
    myTxSapi = theTxSapi;
}

//--------------------------------------------------------------------------------

inline uint32*                         
TL1_FacilityEntParameters::GetExtChannel( ) const
{
    return myExtChannel;
}

inline void                         
TL1_FacilityEntParameters::SetExtChannel(uint32* theExtChannel)
{
    myExtChannel = theExtChannel;
}

//--------------------------------------------------------------------------------

inline CT_TEL_OTIDStatus*           
TL1_FacilityEntParameters::GetOTIDStatus( ) const
{
    return myOTIDStatus;
}

inline void                         
TL1_FacilityEntParameters::SetOTIDStatus( CT_TEL_OTIDStatus* theOTIDStatus ) 
{
    myOTIDStatus = theOTIDStatus;
}
//--------------------------------------------------------------------------------

inline int*                         
TL1_FacilityEntParameters::GetHoldOffProt( ) const
{
    return myHoldOffProt;
}

inline void                         
TL1_FacilityEntParameters::SetHoldOffProt( int* theHoldOffProt )
{
    myHoldOffProt = theHoldOffProt;

}

//--------------------------------------------------------------------------------
inline CT_TEL_LacpPartiMode*           
TL1_FacilityEntParameters::GetLacpParticipation( ) const
{
    return myLacpParticipation;
}

inline void                         
TL1_FacilityEntParameters::SetLacpParticipation( CT_TEL_LacpPartiMode* theLacpParticipation )
{
    myLacpParticipation = theLacpParticipation;
}


//--------------------------------------------------------------------------------
inline int*           
TL1_FacilityEntParameters::GetLacpPriority( ) const
{
    return myLacpPriority;
}

inline void                         
TL1_FacilityEntParameters::SetLacpPriority( int* theLacpPriority )
{
    myLacpPriority = theLacpPriority;
}


inline CT_RS_IndicationType*        
TL1_FacilityEntParameters::GetAisType() const
{
    return myAisType;
}

inline void                         
TL1_FacilityEntParameters::SetAisType(CT_RS_IndicationType* theAisType)
{
    myAisType = theAisType;
}

inline uint16*        
TL1_FacilityEntParameters::GetBurstyBerSdInterval() const
{
    return myBurstyBerSdInterval;
}

inline void                         
TL1_FacilityEntParameters::SetBurstyBerSdInterval(uint16* theBurstyBerSdInterval)
{
    myBurstyBerSdInterval = theBurstyBerSdInterval;
}

inline uint32*        
TL1_FacilityEntParameters::GetBurstyBerSdThreshold() const
{
    return myBurstyBerSdThreshold;
}

inline void                         
TL1_FacilityEntParameters::SetBurstyBerSdThreshold(uint32* theBurstyBerSdThreshold)
{
    myBurstyBerSdThreshold = theBurstyBerSdThreshold;
}

//--------------------------------------------------------------------------------
inline CT_TEL_TS_SIZE*           
TL1_FacilityEntParameters::GetTribSize( ) const
{
    return myTribSize;
}

inline void                         
TL1_FacilityEntParameters::SetTribSize( CT_TEL_TS_SIZE* theTribSize )
{
    myTribSize = theTribSize;
}

//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetIsAutoAdjustAttenuationEnabled( ) const
{
    return myIsAutoAdjustAttenuationEnabled;
}

inline void                         
TL1_FacilityEntParameters::SetIsAutoAdjustAttenuationEnabled( bool* theIsAutoAdjustAttenuationEnabled )
{
    myIsAutoAdjustAttenuationEnabled = theIsAutoAdjustAttenuationEnabled;
}

inline CT_Fac_TraceString* TL1_FacilityEntParameters::GetExpOperator() const
{
    return myExpOperator;
}

inline void TL1_FacilityEntParameters::SetExpOperator(CT_Fac_TraceString* theExpOperator)
{
    myExpOperator = theExpOperator;
}

inline CT_Fac_TraceString* TL1_FacilityEntParameters::GetTxOperator() const
{
    return myTxOperator;
}

inline void TL1_FacilityEntParameters::SetTxOperator(CT_Fac_TraceString* theTxOperator)
{
    myTxOperator = theTxOperator;
}

//--------------------------------------------------------------------------------
inline CT_TEL_OPU_FORMAT* TL1_FacilityEntParameters::GetOpuConfig() const
{
    return myOpuConfig;
}
//--------------------------------------------------------------------------------
inline void TL1_FacilityEntParameters::SetOpuConfig(CT_TEL_OPU_FORMAT* theOpuConfig)
{
    myOpuConfig = theOpuConfig;
}

//--------------------------------------------------------------------------------
inline bool* TL1_FacilityEntParameters::GetOTNMap() const
{
    return myOTNMap;
}

inline void TL1_FacilityEntParameters::SetOTNMap(bool* theOTNMap)
{
    myOTNMap = theOTNMap;
}

//--------------------------------------------------------------------------------
inline void TL1_FacilityEntParameters::SetMapMode(CT_TEL_PayloadType* theMapMode)
{
    myMapMode = theMapMode;
}

inline CT_TEL_PayloadType* TL1_FacilityEntParameters::GetMapMode() const
{
    return myMapMode;
}

//--------------------------------------------------------------------------------

inline bool*                        
TL1_FacilityEntParameters::GetQuarantine( ) const
{
    return myQua;
}

inline void                         
TL1_FacilityEntParameters::SetQuarantine( bool* theQua )
{
    myQua = theQua;
}

//--------------------------------------------------------------------------------

inline CT_FAC_PluggableReach*                        
TL1_FacilityEntParameters::GetPluggableReach( ) const
{
    return myPluggableReach;
}

inline void                        
TL1_FacilityEntParameters::SetPluggableReach( CT_FAC_PluggableReach* thePluggableReach )
{
    myPluggableReach = thePluggableReach;
}
#endif
