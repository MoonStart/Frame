/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive FAC Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive FAC Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_FAC_RESPONSE_BLOCK_H_
#define __TL1_FAC_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TestAccessTypes.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_PM_Definition.h>

#include <utility>

class TL1_FACRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_FACRspBlk();
    
    TL1_FACRspBlk(const string*                         theEntityName,
                  const CT_TL1_FacAddr*                 theAddr,
                  const CT_CardType*                    theCardType,
                  const CT_SubCardType*                 theSubCardType,
                  const bool*                           isAdaptiveEnabled,
                  const CT_TEL_daHz*                    theMaxRate,
                  const CT_FAC_SignalRateListType*      theRateList,
                  const CT_TL1_ExpectedRateRange*       theExpectedSignalRate,
                  const CT_TEL_SignalType*              theSignalType,
                  const CT_FAC_StsMap*                  theStsMap,
                  const CT_Fac_TraceString*             theTrace,
                  const CT_Fac_TraceString*             theExpectedTrace,
                  const CT_Fac_TraceString*             theIncomingTrace,
                  const bool*                           isMonitorTraceEnabled,
                  const bool*                           isInsertAisEnabled,
                  const CT_FAC_Protection*              isProtectionEnabled,                  
                  const CT_FAC_MaintProp*               theMaintPropagate,                  
                  const CT_TEL_HopSpeMapping*           theMapping,
                  const CT_FAC_ExternalConnectivity*    theExternalConectivity,
                  const CT_TEL_BERLevels*               theSFThreshold,
                  const CT_TEL_BERLevels*               theSDThreshold,
                  const uint16*                         theBurstyBerSdInterval,
                  const uint32*                         theBurstyBerSdThreshold,
                  const CT_Fac_ConnectedToString*       theConnectedTo,
                  const bool*                           theTransparent,
                  const bool*                           theSsmSupported,
                  const CT_FAC_RxSsm*                   theSsmReceived,
                  const CT_TEL_MsTref*                  theTimingReference,
                  const bool*                           theProtection,
                  const CT_TEL_daHz*                    theActualRate,
                  const CT_FAC_LineCode*                theLineCode,
                  const CT_FAC_FrameFormat*             theFrameFormat,
                  const CT_FAC_SaBit*                   theSaBit,
                  const CT_FAC_QualityLevelOverride*    theQualityLevelOverride,
                  const CT_TEL_GfpFramingMode*          theGfpMapping,
                  const bool*                           theGenTrc,
                  const CT_TEL_mBm*                     theLOSThreshold,
                  const CT_TEL_mBm*                     theSWThreshold,
                  const CT_TEL_OpticalWaveLength*       theSignalBand,
                  const bool*                           theNendALS,
                  const CT_FAC_NValue*                  theNValue,
                  const CT_TEL_FecType*                 theFecType,
                  const CT_TEL_SignalType*              theTransMap,
                  const CT_Fac_TraceString*             theOtuExpTrc,
                  const CT_Fac_TraceString*             theOtuTrc,
                  const bool*                           isOtuMonitorTraceEnabled,
                  const CT_Fac_TraceString*             theOtuIncTrc,
                  const CT_TEL_OEO_REGEN_MODE*          theOeoRegen,
                  const CT_FAC_StsMap*                  theStsCstMap,
                  const CT_FAC_StsMap*                  theAddCrsMap,
                  const CT_FAC_StsMap*                  theDelCrsMap,
                  const CT_TEL_TermSize*                theCnvType,
                  const CT_TEL_SignalType*              theClkType,
                  const CT_TapNumber*                   theTapNumber,
                  const bool*                           isAutoNegotiationEnabled,
                  const CT_ProfileTableId*              theAlarmProfile, 
                  const CT_TEL_PayloadSignalId*         thePt,
                  const CT_TEL_PayloadSignalId*         thePtRx,
                  const CT_TEL_GfpUpiId*                theUpi,
                  const CT_FAC_StsMap*                  theAddCstMap,
                  const CT_FAC_StsMap*                  theDelCstMap,
                  const bool*                           theAutoCfg,
                  const int*                            theNpOwner,
                  const bool*                           theQuarantine,
                  const bool*                           theDiscardPause,
                  const bool*                           thePropFefi,
                  const CT_PMProfileTableId*            thePmProfile, 
                  const int*                            theCFProfile,
                  const CT_TEL_PayloadType*             theCbrMap,
                  const CT_TEL_GFP_MUX*                 theGfpMux,
                  const CT_TEL_TimCriteriaMode*         theTimDef,
                  const CT_Fac_TraceString*             theExpDapi,
                  const CT_Fac_TraceString*             theExpSapi,
                  const CT_Fac_TraceString*             theTxDapi,
                  const CT_Fac_TraceString*             theTxSapi,
                  const uint32*                         theChannel,
                  //const CT_RelativeWavelength*          theChannel,
                  const CT_TEL_LacpPartiMode*           theLacpPartiMode,
                  const int*                            theLacpPriority,
                  const CT_TEL_OPU_FORMAT*              theOpuFmt,
                  const CT_TEL_TS_SIZE*                 theOpTribSize,
                  const CT_TEL_TS_SIZE*                 theTribSize,
                  const CT_TCM_Mode*                    theTcmMode,
                  const CT_TL1_FacParamAddr*            theOpadjacent,
                  const bool*                           theTribFall,
                  const bool*                           theDmSource,
                  const bool*                           theLtcActMode,
                  const uint8*                          theGfpTs,
                  const uint8*                          theInterPacketGap,
                  const CT_TEL_OPU_FORMAT*              theOpuConfig,
                  const CT_SM_PST*                      thePST,
                  const CT_SM_PSTQ*                     thePSTQ,
                  const CT_SM_SST*                      theSST,
                  const CT_FAC_QualityLevelOverride*    theQualityLevel,
                  const bool*                           theOTNMap,
                  const CT_TEL_Map_ENUM*                theHgeMap,
                  const CT_TEL_PayloadType*             theMapMode,
                  const string*                         theMacAddr,
                  const CT_FAC_PluggableReach*          thePluggableReach);

    TL1_FACRspBlk(const string* theEntityName,
                  const CT_TL1_FacAddr* theAddr,
                  const CT_SM_PST*  thePST,
                  const CT_SM_PSTQ* thePSTQ,
                  const CT_SM_SST*  theSST);

    TL1_FACRspBlk(const string* theEntityName,
                  const CT_TL1_FacAddr* theAddr,
                  const CT_TL1_FacAddr* theMemberAddr);

    TL1_FACRspBlk(const TL1_FACRspBlk& facBlk);
    
    virtual ~TL1_FACRspBlk();

    TL1_FACRspBlk& operator=( const TL1_FACRspBlk& theBlock );

    bool operator==( const TL1_FACRspBlk& theBlock ) const;
    bool operator<( const TL1_FACRspBlk& theBlock ) const;

    bool GetEntityName(string& ) const;    
    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    bool GetCardType(CT_CardType& ) const;
    bool GetSubCardType( CT_SubCardType&) const ;
    bool GetAdaptive( bool& ) const;
    bool GetMaxRate( CT_TEL_daHz& ) const;
    bool GetRateList( CT_FAC_SignalRateListType&) const;
    bool GetExpectedSignalRate( CT_TEL_daHz&) const;
    bool GetExpectedRateRange( CT_TL1_ExpectedRateRange&) const;
    bool GetActRate( CT_TEL_daHz&) const;
    bool GetSignalType(CT_TEL_SignalType&) const;
    bool GetStsMap(CT_FAC_StsMap&) const;
    bool GetTrace(CT_Fac_TraceString&) const;
    bool GetExpectedTrace( CT_Fac_TraceString&) const;
    bool GetIncomingTrace( CT_Fac_TraceString&) const;
    bool GetMonitorTraceEnabled( bool& ) const;
    bool GetInsertAisEnabled( bool& ) const;
    bool GetProtectionEnabled( CT_FAC_Protection&) const;    
    bool GetMaintPropagate( CT_FAC_MaintProp&) const;    
    bool GetMapping(CT_TEL_HopSpeMapping&) const;
    bool GetExternalConectivity(CT_FAC_ExternalConnectivity&) const;
    bool GetSFThreshold(CT_TEL_BERLevels&) const;
    bool GetSDThreshold(CT_TEL_BERLevels&) const;
    bool GetBurstyBerSdInterval(uint16&) const;
    bool GetBurstyBerSdThreshold(uint32&) const;
    bool GetAlarmProfile( CT_ProfileTableId&) const;
    bool GetPST( CT_SM_PST&) const;
    bool GetPSTQ( CT_SM_PSTQ&) const;
    bool GetSST( CT_SM_SST&) const;
    bool GetConnectedTo( CT_Fac_ConnectedToString& ) const;
    bool GetTransparent( bool& ) const;
    bool GetSsmSupported( bool& ) const;
    bool GetSsmReceived( CT_FAC_RxSsm& ) const;
    bool GetQualityLevel( CT_FAC_QualityLevelOverride& ) const;
    bool GetTimingRef( CT_TEL_MsTref& ) const;
    bool GetLineCode( CT_FAC_LineCode& ) const;
    bool GetFrameFormat( CT_FAC_FrameFormat& ) const;
    bool GetSaBit( CT_FAC_SaBit& ) const;
    bool GetQualityLevelOverride( CT_FAC_QualityLevelOverride& ) const;
    bool GetGfpMapping( CT_TEL_GfpFramingMode& ) const;
    bool GetGenTrc( bool& ) const;
    bool GetLOSThreshold( CT_TEL_mBm& ) const;
    bool GetSWThreshold( CT_TEL_mBm& ) const;
    bool GetSignalBand( CT_TEL_OpticalWaveLength& ) const;
    bool GetNendALS( bool& ) const;
    bool GetNValue( CT_FAC_NValue& ) const;
    bool GetFecType( CT_TEL_FecType& ) const;
    bool GetTransMap( CT_TEL_SignalType& ) const;
    bool GetOtuExpTrc( CT_Fac_TraceString& ) const;
    bool GetOtuTrc( CT_Fac_TraceString& ) const;
    bool GetOtuMonTrc( bool& ) const;     
    bool GetOtuIncTrc( CT_Fac_TraceString& ) const;
    bool GetOeoRegen( CT_TEL_OEO_REGEN_MODE& ) const;
    bool GetStsCstMap(CT_FAC_StsMap&) const;
    bool GetAddCrsMap(CT_FAC_StsMap&) const;
    bool GetDelCrsMap(CT_FAC_StsMap&) const;
    bool GetCnvType(CT_TEL_TermSize&) const;
    bool GetClkType( CT_TEL_SignalType& ) const;
    bool GetTapNumber( CT_TapNumber& ) const;
    bool GetAutoNegotiationEnabled( bool& ) const;     
    bool GetPt( CT_TEL_PayloadSignalId& ) const;    
    bool GetPtRx( CT_TEL_PayloadSignalId& ) const;   
    bool GetGfpUpi( CT_TEL_GfpUpiId& ) const;    
    bool GetAddCstMap(CT_FAC_StsMap&) const;
    bool GetDelCstMap(CT_FAC_StsMap&) const;
    bool GetAutoCfg(bool&) const;
    bool GetNpOwner(int& theNpOwner ) const;
    bool GetQuarantine(bool& theQuarantine) const;
    bool GetEthRate(CT_TEL_daHz& theEthRate) const;
    bool GetOpEthRate(CT_TEL_daHz& theOpEthRate) const;
    bool GetDuplexMode(CT_TEL_MAC_DUPLEX_MODE& theDuplexMode) const;
    bool GetOpDuplexMode(CT_TEL_MAC_DUPLEX_MODE& theDuplexMode) const;
    bool GetTcmMode(CT_TCM_Mode& theTcmMode) const;
    bool GetFlowControl(CT_TEL_MAC_FLOWCTRL& theFlowControl) const;
    bool GetOpFlowControl(CT_TEL_MAC_FLOWCTRL& theOpFlowControl) const;
    bool GetAutonegStatus(CT_TEL_MAC_AUTONEGSTATUS& theAutonegStatus) const;
    bool GetAutonegRmtSgl(bool& theAutonegRmtSgl) const;
    bool GetAdvFlowCtrl(CT_TEL_MAC_ADFLW_CTRL& theAdvFlowCtrl) const;
    bool GetOpAutoneg(bool& theOpAutoneg) const;
    bool GetVcgName(string& ) const;    
    bool GetVcgAddr( CT_TL1_FacAddr&) const ;
    bool GetVlanTag( CT_TEL_VlanTag& theVTag) const;
    bool GetTagMode( bool& theTagMode) const;
    bool GetTpid( CT_TEL_Tpid& theTpid) const;
    bool GetDiscardPause( bool& ) const;
    bool GetPropFefi( bool& ) const;
    bool GetPMProfile( CT_PMProfileTableId&) const;
    bool GetCbrMap(CT_TEL_PayloadType&) const;
    bool GetCFProfile( int& ) const;
    bool GetGfpMux(CT_TEL_GFP_MUX&) const;
    bool GetOduMux(CT_TL1_FacParamAddr&) const;
    bool GetOpadjacent(CT_TL1_FacParamAddr&) const;
    bool GetTimDef(CT_TEL_TimCriteriaMode&) const;
    bool GetExpDapi(CT_Fac_TraceString&) const;
    bool GetExpSapi(CT_Fac_TraceString&) const;     
    bool GetTxDapi(CT_Fac_TraceString&) const;
    bool GetTxSapi(CT_Fac_TraceString&) const;
    //bool GetChannel(CT_RelativeWavelength&)const;
    bool GetChannel(uint32&)const;
    bool GetConnected1(CT_TL1_FacParamAddr& theConnected1) const;
    bool GetConnected2(CT_TL1_FacParamAddr& theConnected2) const;
    bool GetTribSlot(CT_FAC_OduTsMap& theTribSlot) const;
    bool GetTribFall(bool& theTribFall) const;
    bool GetDmSource(bool& theDmSource) const;
    bool GetLtcActMode(bool& theLtcActMode) const;
    bool GetGfpTs(uint8& theGfpTs) const;
    bool GetMemberAddr(CT_TL1_FacAddr&) const;
    bool GetLacpPartiMode(CT_TEL_LacpPartiMode&)const;
    bool GetLacpPriority(int& thePriority)const;
    bool GetAisType(CT_RS_IndicationType& theAisType)const;
    bool GetOpuFmt(CT_TEL_OPU_FORMAT&) const;
    bool GetTribSize(CT_TEL_TS_SIZE&) const;
    bool GetOpTribSize(CT_TEL_TS_SIZE&) const;
    bool GetInterPacketGap(uint8& theInterPacketGap) const;
    bool GetOpuConfig(CT_TEL_OPU_FORMAT& theOpuConfig) const;
    bool GetOTNMap(bool &) const;
    bool GetHgeMap(CT_TEL_Map_ENUM& theHgeMap) const;
    bool GetMapMode(CT_TEL_PayloadType &theMapMode) const;
    bool GetMacAddr(string& ) const;   
    bool GetPluggableReach(CT_FAC_PluggableReach& ) const;   
    
    void SetEntityName(const string& theEntityName);    
    void SetFacAddr(const CT_TL1_FacAddr& theFacAddr);
    void SetCardType(const CT_CardType& theCardType);
    void SetSubCardType( const CT_SubCardType& theSubCardType);
    void SetAdaptive( const bool& theAdaptive);
    void SetMaxRate( const CT_TEL_daHz& theMaxRate);
    void SetRateList( const CT_FAC_SignalRateListType& theRateList);
    void SetExpectedSignalRate( CT_TEL_daHz& theExpectedSignalRate);
    void SetExpectedRateRange( CT_TL1_ExpectedRateRange& theExpectedRateRange);
    void SetActRate( const CT_TEL_daHz& theActRate);
    void SetSignalType(const CT_TEL_SignalType& theSignalType);
    void SetStsMap(const CT_FAC_StsMap& theStsMap);
    void SetTrace(const CT_Fac_TraceString& theTrace);
    void SetExpectedTrace( const CT_Fac_TraceString& theExpectedTrace);
    void SetIncomingTrace( const CT_Fac_TraceString& theIncomingTrace);
    void SetMonitorTraceEnabled( const bool& theMonitorTraceEnabled);
    void SetInsertAisEnabled(const  bool& theInsertAisEnabled);
    void SetProtectionEnabled( const CT_FAC_Protection& theProtectionEnabled);    
    void SetMaintPropagate( const CT_FAC_MaintProp& theMaintPropagate);    
    void SetMapping(CT_TEL_HopSpeMapping& theMapping);
    void SetExternalConectivity(const CT_FAC_ExternalConnectivity& theExternalConectivity);
    void SetSFThreshold(const CT_TEL_BERLevels& theSFThreshold);
    void SetSDThreshold(const CT_TEL_BERLevels& theSDThreshold);
    void SetBurstyBerSdInterval(const uint16& theBurstyBerSdInterval);
    void SetBurstyBerSdThreshold(const uint32& theBurstyBerSdThreshold);
    void SetAlarmProfile( CT_ProfileTableId& theAlarmProfile);
    void SetPST( CT_SM_PST& thePST);
    void SetPSTQ( const CT_SM_PSTQ& thePSTQ);
    void SetSST( CT_SM_SST& theSST);
    void SetConnectedTo(const CT_Fac_ConnectedToString& theConnectedTo );
    void SetTransparent( const bool& theTransparent);
    void SetSsmSupported(const  bool& theSsmSupported);
    void SetSsmReceived(const  CT_FAC_RxSsm& theSsmReceived);
    void SetQualityLevel(const  CT_FAC_QualityLevelOverride& theQualityLevel);
    void SetTimingRef( const CT_TEL_MsTref& theTimingRef);
    void SetLineCode( const CT_FAC_LineCode& theLineCode);
    void SetFrameFormat( const CT_FAC_FrameFormat& theFrameFormat);
    void SetSaBit( const CT_FAC_SaBit& theSaBit);
    void SetQualityLevelOverride( const CT_FAC_QualityLevelOverride& theQualityLevelOverride);
    void SetGfpMapping(const CT_TEL_GfpFramingMode& theGfpMapping);
    void SetGenTrc( const bool& theGenTrc);
    void SetLOSThreshold( const CT_TEL_mBm& theLOSThreshold);
    void SetSWThreshold( const CT_TEL_mBm& theSWThreshold);
    void SetSignalBand( const CT_TEL_OpticalWaveLength& theSignalBand);
    void SetNendALS( const bool& theNendALS);
    void SetNValue( const CT_FAC_NValue& theNValue);
    void SetFecType( const CT_TEL_FecType& theFecType);
    void SetTransMap( const CT_TEL_SignalType& theTransMap);
    void SetOtuExpTrc( const CT_Fac_TraceString& theOtuExpTrc);
    void SetOtuTrc( const CT_Fac_TraceString& theOtuTrc );
    void SetOtuMonTrc( const bool& theOtuMonTrc);     
    void SetOtuIncTrc( const CT_Fac_TraceString& theOtuIncTrc );
    void SetOeoRegen( const CT_TEL_OEO_REGEN_MODE& theOeoRegen );
    void SetStsCstMap(const CT_FAC_StsMap& theStsCstMap);
    void SetAddCrsMap(const CT_FAC_StsMap& theAddCrsMap);
    void SetDelCrsMap(const CT_FAC_StsMap& theDelCrsMap);
    void SetCnvType(const CT_TEL_TermSize& theCnvType);
    void SetClkType( const CT_TEL_SignalType& theClkType);
    void SetTapNumber( const CT_TapNumber& theTapNumber);
    void SetAutoNegotiationEnabled( const bool& theAutoNegotiation);     
    void SetPt( const CT_TEL_PayloadSignalId& thePt);
    void SetPtRx( const CT_TEL_PayloadSignalId& thePtRx);
    void SetGfpUpi( const CT_TEL_GfpUpiId& theUpi);
    void SetAddCstMap(const CT_FAC_StsMap& theAddCrsMap);
    void SetDelCstMap(const CT_FAC_StsMap& theDelCrsMap);
    void SetAutoCfg(const bool& theAutoCfg);
    void SetNpOwner(const int& theNpOwner );
    void SetQuarantine( const bool& theQuarantine);
    void SetEthRate(const CT_TEL_daHz& theEthRate) ;
    void SetOpEthRate(const CT_TEL_daHz& theOpEthRate);
    void SetDuplexMode(const CT_TEL_MAC_DUPLEX_MODE& theDuplexMode);
    void SetOpDuplexMode(const CT_TEL_MAC_DUPLEX_MODE& theDuplexMode);
    void SetTcmMode(const CT_TCM_Mode& theTcmMode);
    void SetFlowControl(const CT_TEL_MAC_FLOWCTRL& theFlowControl);
    void SetOpFlowControl(const CT_TEL_MAC_FLOWCTRL& theOpFlowControl);
    void SetAutonegStatus(const CT_TEL_MAC_AUTONEGSTATUS& theAutonegStatus);
    void SetAutonegRmtSgl(const bool& theAutonegRmtSgl);
    void SetAdvFlowCtrl(const CT_TEL_MAC_ADFLW_CTRL& theAdvFlowCtrl);
    void SetOpAutoneg(const bool& theOpAutoneg);
    void SetVcgName(const string& theEntityName);    
    void SetVcgAddr(const CT_TL1_FacAddr& theFacAddr);
    void SetVlanTag(const CT_TEL_VlanTag& theVTag);
    void SetTagMode(const bool& theTagMode);
    void SetTpid(const CT_TEL_Tpid& theTpid);
    void SetDiscardPause( const bool& theDiscardPause);
    void SetPropFefi( const bool& thePropFefi);
    void SetPMProfile( const CT_PMProfileTableId& thePmProfile);
    void SetCFProfile( int& theCFProfile );
    void SetCbrMap(const CT_TEL_PayloadType& theCbrMap);
    void SetGfpMux(const CT_TEL_GFP_MUX& theGfpMux);
    void SetOpadjacent(const CT_TL1_FacParamAddr& theOpadjacent);
    void SetTimDef(const CT_TEL_TimCriteriaMode& theTimDef);
    void SetExpDapi(const CT_Fac_TraceString& theExpDapi);
    void SetExpSapi(const CT_Fac_TraceString& theExpiSapi);
    void SetTxDapi(const CT_Fac_TraceString& theTxDapi);
    void SetTxSapi(const CT_Fac_TraceString& theTxSapi);
    void SetChannel(const uint32& theChannel);
    //void SetChannel(const CT_RelativeWavelength& theChannel);
    void SetConnected1(const CT_TL1_FacParamAddr& theConnected1);
    void SetConnected2(const CT_TL1_FacParamAddr& theConnected2);
    void SetTribSlot(const CT_FAC_OduTsMap& theTribSlot);
    void SetTribFall(const bool& theTribFall);
    void SetDmSource(const bool& theDmSource);
    void SetLtcActMode(const bool& theLtcActMode);
    void SetGfpTs(const uint8& theGfpTs);
    void SetMemberAddr(const CT_TL1_FacAddr& theFacAddr);
    void SetMemberType();
    void SetLacpPartiMode(CT_TEL_LacpPartiMode theMode);
    void SetLacpPriority(int thePriority);
    void SetAisType(CT_RS_IndicationType theAisType);
    void SetOpuFmt(const CT_TEL_OPU_FORMAT& theOpuFmt);
    void SetTribSize(const CT_TEL_TS_SIZE& theTribSize);
    void SetOpTribSize(const CT_TEL_TS_SIZE& theOpTribSize);
    void SetInterPacketGap(const uint8& theInterPacketGap);
    void SetOpuConfig(const CT_TEL_OPU_FORMAT& theOpuConfig);
    void SetOTNMap(const bool &theOTNMap);
    void SetHgeMap(const CT_TEL_Map_ENUM &theHgeMap);
    void SetMapMode(const CT_TEL_PayloadType &theMapMode);
	void SetMacAddr(const string& theMacAddr);
    void SetPluggableReach(const CT_FAC_PluggableReach& thePluggableReach);

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_Adaptive,
        INDEX_MaxRate,
        INDEX_RateList,
        INDEX_ExpectedSignalRate,
        INDEX_ExpectedSignalRateRange,
        INDEX_SignalType,
        INDEX_StsMap,
        INDEX_Trace,
        INDEX_ExpectedTrace,
        INDEX_IncomingTrace,
        INDEX_MonitorTraceEnabled,
        INDEX_InsertAisEnabled,
        INDEX_ProtectionEnabled,
        INDEX_MaintPropagate,
        INDEX_AlarmProfile,
        INDEX_Mapping,
        INDEX_ExternalConectivity,
        INDEX_ConnectedTo,
        INDEX_Transparent,
        INDEX_SsmSupported,
        INDEX_SsmReceived,
        INDEX_TimingReference,
        INDEX_SFThreshold,
        INDEX_SDThreshold,
        INDEX_BurstyBerSdInterval,
        INDEX_BurstyBerSdThreshold,
        INDEX_ActualRate,
        INDEX_LineCode,
        INDEX_FrameFormat,
        INDEX_SaBit,
        INDEX_GfpMapping,
        INDEX_GenTrc,
        INDEX_LOSThreshold,
        INDEX_SWThreshold,
        INDEX_SignalBand,
        INDEX_NendALS,
        INDEX_NValue,
        INDEX_FecType,
        INDEX_TransMap,
        INDEX_OtuExpTrc,
        INDEX_OtuTrc,
        INDEX_OtuMonTrc,
        INDEX_OtuIncTrc,
        INDEX_OeoRegen,
        INDEX_StsCstMap,
        INDEX_AddCrsMap,
        INDEX_DelCrsMap,
        INDEX_CnvType,
        INDEX_ClkType,
        INDEX_TapNumber,
        INDEX_AutoNegotiation,
        INDEX_Pt,    
        INDEX_PtRx,
        INDEX_GfpUpi,      
        INDEX_AddCstMap,
        INDEX_DelCstMap,
        INDEX_AutoCfg,
        INDEX_NpOwner,
        INDEX_Quarantine,
        INDEX_EthRate,
        INDEX_OpEthRate,
        INDEX_DuplexMode,
        INDEX_OpDuplexMode,
        INDEX_TcmMode,
        INDEX_FlowControl,
        INDEX_OpFlowControl,
        INDEX_AutonegStatus,
        INDEX_AutonegRmtSgl,
        INDEX_AdvFlowCtrl,
        INDEX_OpAutoneg,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_VcgName,
        INDEX_VcgAddr,
        INDEX_VlanTag,
        INDEX_TagMode,
        INDEX_Tpid,
        INDEX_DiscardPause,
        INDEX_PropFefi,
        INDEX_PmProfile,
        INDEX_CFProfile,
        INDEX_CbrMap,
        INDEX_GfpMux,
        INDEX_Opadjacent,
        INDEX_TimDef,
        INDEX_ExpDapi,
        INDEX_ExpSapi,
        INDEX_TxDapi,
        INDEX_TxSapi,
        INDEX_QualityLevelOverride,
        INDEX_Channel,
        INDEX_Connected1,
        INDEX_Connected2,
        INDEX_TribSlot,
        INDEX_MemberAddr,
        INDEX_LacpPartiMode,
        INDEX_LacpPriority,
        INDEX_AisType,
        INDEX_Opu,
        INDEX_OpTribSize,
        INDEX_TribSize,
        INDEX_TribFall,
        INDEX_GfpTs,
        INDEX_DmSource,
        INDEX_LtcActMode,
        INDEX_QualityLevel,
        INDEX_InterPacketGap,
        INDEX_OpuConfig,
        INDEX_OTNMap,
        INDEX_HGEMAP,
        INDEX_MAPMODE,
        INDEX_MACADDR,
        INDEX_PluggableReach,
        INDEX_END
    };

    vector<bool>       myBitSet;

    string                      myEntityName;
    CT_TL1_FacAddr              myFacAddr;
    CT_CardType                 myCardType;
    CT_SubCardType              mySubCardType;
    bool                        myAdaptive;
    CT_TEL_daHz                 myMaxRate;
    CT_FAC_SignalRateListType   myRateList;
    CT_TEL_SignalType           mySignalType;
    CT_FAC_StsMap               myStsMap;
    CT_Fac_TraceString          myTrace;
    CT_Fac_TraceString          myExpectedTrace;
    CT_Fac_TraceString          myIncomingTrace;
    bool                        myMonitorTraceEnabled;
    bool                        myInsertAisEnabled;
    CT_FAC_Protection           myProtectionEnabled;    
    CT_FAC_MaintProp            myMaintProp;    
    CT_ProfileTableId           myAlarmProfile;
    CT_TEL_HopSpeMapping        myMapping;
    CT_TL1_ExpectedRateRange    myExpectedSignalRateRange;
    CT_TEL_daHz                 myExpectedSignalRate;
    CT_TEL_daHz                 myActRate;
    CT_FAC_ExternalConnectivity myExternalConectivity;
    CT_TEL_BERLevels            mySFThreshold;
    CT_TEL_BERLevels            mySDThreshold;
    uint16                      myBurstyBerSdInterval;
    uint32                      myBurstyBerSdThreshold;
    CT_Fac_ConnectedToString    myConnectedTo;
    bool                        myTransparent;
    bool                        mySsmSupported;
    CT_FAC_RxSsm                mySsmReceived;
    CT_TEL_MsTref               myTimingReference;
    CT_FAC_LineCode             myLineCode;
    CT_FAC_FrameFormat          myFrameFormat;
    CT_FAC_SaBit                mySaBit;
    CT_FAC_QualityLevelOverride myQualityLevelOverride;
    CT_TEL_GfpFramingMode   myGfpMapping;
    bool                        myGenTrc;
    CT_TEL_mBm                  myLOSThreshold;
    CT_TEL_mBm                  mySWThreshold;
    CT_TEL_OpticalWaveLength    mySignalBand;
    bool                        myNendALS;
    CT_FAC_NValue               myNValue;
    CT_TEL_FecType              myFecType;
    CT_TEL_SignalType           myTransMap;
    CT_Fac_TraceString          myOtuExpTrc;
    CT_Fac_TraceString          myOtuTrc;
    bool                        myOtuMonTrc;     
    CT_Fac_TraceString          myOtuIncTrc;
    CT_TEL_OEO_REGEN_MODE       myOeoRegen;
    CT_FAC_StsMap               myStsCstMap;
    CT_FAC_StsMap               myAddCrsMap;
    CT_FAC_StsMap               myDelCrsMap;
    CT_TEL_TermSize             myCnvType;
    CT_TEL_SignalType           myClkType;
    CT_TapNumber                myTapNumber;
    bool                        myAutoNegotiationEnabled;     
    CT_TEL_PayloadSignalId      myPt;
    CT_TEL_PayloadSignalId      myPtRx;
    CT_TEL_GfpUpiId             myGfpUpi;   
    CT_FAC_StsMap               myAddCstMap;
    CT_FAC_StsMap               myDelCstMap;
    bool                        myAutoCfg;
    int                         myNpOwner;
    bool                        myQuarantine;
    CT_TEL_daHz                 myEthRate;
    CT_TEL_daHz                 myOpEthRate;
    CT_TEL_MAC_DUPLEX_MODE      myDuplexMode;
    CT_TEL_MAC_DUPLEX_MODE      myOpDuplexMode;
    CT_TCM_Mode                 myTcmMode;
    CT_TEL_MAC_FLOWCTRL         myFlowControl;
    CT_TEL_MAC_FLOWCTRL         myOpFlowControl;
    CT_TEL_MAC_AUTONEGSTATUS    myAutonegStatus;
    bool                        myAutonegRmtSgl;
    CT_TEL_MAC_ADFLW_CTRL       myAdvFlowCtrl;
    bool                        myOpAutoneg;
    CT_SM_PST                   myPST;
    CT_SM_PSTQ                  myPSTQ;
    CT_SM_SST                   mySST;
    string                      myVcgName;
    CT_TL1_FacAddr              myVcgAddr;
    CT_TEL_VlanTag              myVlanTag;
    bool                        myTagMode;
    CT_TEL_Tpid                 myTpid;
    bool                        myDiscardPause;
    bool                        myPropFefi;
    CT_PMProfileTableId         myPmProfile;
    int                         myCFProfile;
    CT_TEL_PayloadType          myCbrMap;
    CT_TEL_GFP_MUX              myGfpMux;
    CT_TL1_FacParamAddr         myOpadjacent;
    CT_Fac_TraceString          myExpDapi;
    CT_Fac_TraceString          myExpSapi;
    CT_Fac_TraceString          myTxDapi;
    CT_Fac_TraceString          myTxSapi;
    CT_TEL_TimCriteriaMode      myTimDefMode;
    uint32                      myChannel;
    //CT_RelativeWavelength       myChannel;
    CT_TL1_FacParamAddr         myConnected1;
    CT_TL1_FacParamAddr         myConnected2;
    CT_FAC_OduTsMap             myTribSlot;
    bool                        myTribFall;
    bool                        myDmSource;
    bool                        myLtcActMode;
    uint8                       myGfpTs;
    uint8                       myInterPacketGap;
    CT_TEL_OPU_FORMAT           myOpuConfig;

    CT_TL1_FacAddr              myMemberAddr;
    CT_TEL_LacpPartiMode        myLacpPartiMode;
    int                         myLacpPriority;
    CT_RS_IndicationType        myAisType;
    CT_TEL_OPU_FORMAT           myOpuFmt;
    CT_TEL_TS_SIZE              myOpTribSize;
    CT_TEL_TS_SIZE              myTribSize;
    CT_FAC_QualityLevelOverride myQualityLevel;
    bool                        myOTNMap;
    CT_TEL_Map_ENUM             myHgeMap;
    CT_TEL_PayloadType          myMapMode;
	string                      myMacAddr;
    CT_FAC_PluggableReach       myPluggableReach;
};

typedef TL1_Rtv_Response< TL1_FACRspBlk > TL1_FACResponse;

#endif  // #ifndef __TL1_FAC_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
