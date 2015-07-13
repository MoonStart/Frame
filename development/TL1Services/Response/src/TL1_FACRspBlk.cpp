/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 FAC Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 FAC Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_FACRspBlk.h>

TL1_FACRspBlk::TL1_FACRspBlk():
//myEntityName(NULL),
//myFacAddr(),
myCardType(CARD_TYPE_UNKNOWN),
mySubCardType(UNKNOWN_SUB_CT),
myAdaptive(false),
myMaxRate(0),
//myRateList(NULL),
mySignalType(CT_TEL_SIGNAL_UNKNOWN),
//myStsMap(),
//myTrace(),
//myExpectedTrace(),
//myIncomingTrace(),
myMonitorTraceEnabled(false),
myInsertAisEnabled(false),
myProtectionEnabled(CT_FAC_PROT_NO),   
myMaintProp(CT_FAC_MP_NA),   
myAlarmProfile(CT_UNKNOWN_PT),                                           
myMapping(CT_TEL_HOP_MAPPING_UNKNOWN),
myExpectedSignalRate(0),
myActRate(0),
myExternalConectivity(CT_FAC_EXT_NO),
mySFThreshold(CT_TEL_NO_BER),
mySDThreshold(CT_TEL_NO_BER),
myBurstyBerSdInterval(0),
myBurstyBerSdThreshold(0),
//myConnectedTo(),
myTransparent(false),
mySsmSupported(false),
mySsmReceived(CT_RxSsm_ALL),
myTimingReference(CT_TEL_MS_TREF_NONE),
myLineCode(CT_LineCode_UNKNOWN),
myFrameFormat(CT_FrameFormat_UNKNOWN),
mySaBit(CT_SaBit_UNKNOWN),
myQualityLevelOverride(CT_QualityLevelOverride_DISABLED),
myGfpMapping(CT_TEL_GFP_FRAMING_UNKNOWN),
myGenTrc(false),
myLOSThreshold(0),
mySWThreshold(0),
mySignalBand(CT_TEL_UNKNOWN_BAND),
myNendALS(false),
myNValue(0),
myFecType(CT_TEL_FEC_TYPE_UNKNOWN),
myTransMap(CT_TEL_SIGNAL_UNKNOWN),
//myOtuExpTrc(),
//myOtuTrc(),
myOtuMonTrc(false),     
//myOtuIncTrc(),
myOeoRegen(CT_TEL_OEO_REGEN_OFF),
//myStsCstMap(),
// myAddCrsMap(),
// myDelCrsMap(),
myCnvType(CT_TEL_TERMSIZE_STS1),
myClkType(CT_TEL_SIGNAL_UNKNOWN),
myTapNumber(0),
myAutoNegotiationEnabled(false),     
myPt(0),
myPtRx(0),
myGfpUpi(0),
//myAddCstMap(),
//myDelCstMap(),
myAutoCfg(false),
myNpOwner(0),
myQuarantine(false),
myEthRate(0),
myOpEthRate(0),
myDuplexMode(CT_TEL_MAC_DUPLEX_UNKNOWN),
myTcmMode(CT_TCM_MODE_UNKNOWN),
myOpDuplexMode(CT_TEL_MAC_DUPLEX_UNKNOWN),
myFlowControl(CT_TEL_MAC_FLW_UNKNOWN),
myOpFlowControl(CT_TEL_MAC_FLW_UNKNOWN),
myAutonegStatus(CT_TEL_MAC_AUTONEG_UNKNOWN),
myAutonegRmtSgl(false),
myAdvFlowCtrl(CT_TEL_MAC_ADFLW_UNKNOWN),
myOpAutoneg(false),
myDiscardPause(true),
myPropFefi(false),
myPmProfile(CT_PM_UNKNOWN_PT),
myCFProfile(99),
myCbrMap(NULL_MAPPING),
myGfpMux(CT_TEL_GFPMUX_NA),
myOpadjacent(),
myTimDefMode(CT_TEL_TIM_UNKNOWN),
//myExpDapi(),
//myExpSapi(),
//myTxDapi(),
//myTxSapi(),
myPST(0),
myPSTQ(0),
mySST(0),
//myVcgName(NULL),
//myVcgAddr(),
myVlanTag(CT_TEL_VlanNone),
myTagMode(false),
myTpid(CT_TEL_Tpid_STagStd),
//myChannel(CT_UNKNOWN_WAVELENGTH_INDEX),
myChannel(0),
myConnected1(),
myConnected2(),
myTribSlot(),
myLacpPartiMode(CT_TEL_LacpPartiMode_UNKNOWN),
myLacpPriority(0),
myAisType(CT_RS_INDICATION_NONE),
myOpuFmt(CT_TEL_OPU_UNKNOWN),
myOpTribSize(CT_TEL_TS_UNKNOWN),
myTribSize(CT_TEL_TS_UNKNOWN),
myTribFall(false),
myDmSource(false),
myLtcActMode(false),
myGfpTs(0),
myInterPacketGap(0),
myOpuConfig(CT_TEL_OPU_UNKNOWN),
myQualityLevel(CT_QualityLevelOverride_DISABLED),
myOTNMap(true),
myHgeMap(CT_TEL_GMP_MAPPING),
myMapMode(BIT_SYNC_CBR_MAPPING),
myPluggableReach(CT_FAC_PluggableReach_UNKNOWN),
myBitSet(INDEX_END, false)
{
    myExpectedSignalRateRange.begin = 0;
    myExpectedSignalRateRange.end = 0;
    
}


TL1_FACRspBlk::TL1_FACRspBlk(const string*                         theEntityName,
                             const CT_TL1_FacAddr*                 theAddr,
                             const CT_TL1_FacAddr*                 theMemberAddr):
myEntityName(*theEntityName),
myFacAddr(*theAddr),
myMemberAddr(*theMemberAddr),
myBitSet(INDEX_END, false)
{

}

TL1_FACRspBlk:: TL1_FACRspBlk(const string*                         theEntityName,
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
                              const CT_FAC_MaintProp*               theMaintProp,
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
                              const CT_TEL_OEO_REGEN_MODE*      theOeoRegen,
                              const CT_FAC_StsMap*                  theStsCstMap,
                              const CT_FAC_StsMap*                  theAddCrsMap,
                              const CT_FAC_StsMap*                  theDelCrsMap,
                              const CT_TEL_TermSize*                theCnvType,
                              const CT_TEL_SignalType*              theClkType,
                              const CT_TapNumber*                   theTapNumber,
                              const bool*                           isAutoNegotiationEnabled,
                              const CT_ProfileTableId*              theAlarmProfile,
                              const CT_TEL_PayloadSignalId*     thePt,
                              const CT_TEL_PayloadSignalId*     thePtRx,
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
                              const CT_TEL_PayloadType*      theCbrMap,
                              const CT_TEL_GFP_MUX*                 theGfpMux,
                              const CT_TEL_TimCriteriaMode*              theTimDef,
                              const CT_Fac_TraceString*         theExpDapi,
                              const CT_Fac_TraceString*         theExpSapi,
                              const CT_Fac_TraceString*         theTxDapi,
                              const CT_Fac_TraceString*         theTxSapi,
                              const uint32*                     theChannel,
                            //  const CT_RelativeWavelength*      theChannel,
                              const CT_TEL_LacpPartiMode*       theLacpPartiMode,
                              const int*                        theLacpPriority,
                              const CT_TEL_OPU_FORMAT*          theOpuFmt,
                              const CT_TEL_TS_SIZE*             theOpTribSize,
                              const CT_TEL_TS_SIZE*             theTribSize,
                              const CT_TCM_Mode*                    theTcmMode,
                              const CT_TL1_FacParamAddr*            theOpadjacent,
                              const bool*                           theTribFall,
                              const bool*                           theDmSource,
                              const bool*                           theLtcActMode,
                              const uint8*                      theGfpTs,
                              const uint8*                      theInterPacketGap,
                              const CT_TEL_OPU_FORMAT*          theOpuConfig,
                              const CT_SM_PST*                  thePST,
                              const CT_SM_PSTQ*                 thePSTQ,
                              const CT_SM_SST*                  theSST,
                              const CT_FAC_QualityLevelOverride*    theQualityLevel,
                              const bool*                           theOTNMap,
                              const CT_TEL_Map_ENUM*                theHgeMap,
                              const CT_TEL_PayloadType*            theMapMode,
                              const string*                         theMacAddr,
                              const CT_FAC_PluggableReach*          thePluggableReach)
    : myBitSet( INDEX_END, false ),
myTribSlot(),
myOpTribSize(CT_TEL_TS_UNKNOWN),
myTribSize(CT_TEL_TS_UNKNOWN),
myTribFall(false),
myDmSource(false),
myLtcActMode(false),
myGfpTs(0),
myConnected1(),
myConnected2(),
myEthRate(0),
myOpEthRate(0),
myDuplexMode(CT_TEL_MAC_DUPLEX_UNKNOWN),
myOpDuplexMode(CT_TEL_MAC_DUPLEX_UNKNOWN),
myFlowControl(CT_TEL_MAC_FLW_UNKNOWN),
myOpFlowControl(CT_TEL_MAC_FLW_UNKNOWN),
myAutonegStatus(CT_TEL_MAC_AUTONEG_UNKNOWN),
myAutonegRmtSgl(false),
myAdvFlowCtrl(CT_TEL_MAC_ADFLW_UNKNOWN),
myOpAutoneg(false),
myVlanTag(CT_TEL_VlanNone),
myTagMode(false),
myTpid(CT_TEL_Tpid_STagStd),
myDiscardPause(true),
myPropFefi(false),
myAutoCfg(false),
myExpectedSignalRate(0),
myNpOwner(0),
myQuarantine(false),
myTapNumber(0),
myAisType(CT_RS_INDICATION_NONE)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *theAddr;
    }

    if( theCardType)
    {
        myBitSet[ INDEX_CardType ] = true;
        myCardType = *theCardType;
    }
    else
        myCardType = 0;

    if( theSubCardType)
    {
        myBitSet[ INDEX_SubCardType ] = true;
        mySubCardType = *theSubCardType;
    }
    else
        mySubCardType = 0;

    if( isAdaptiveEnabled )
    {
        myBitSet[ INDEX_Adaptive ] = true;
        myAdaptive = *isAdaptiveEnabled;
    }
    else
        myAdaptive = 0;

    if( theMaxRate )
    {
        myBitSet[ INDEX_MaxRate ] = true;
        myMaxRate = *theMaxRate;
    }
    else 
        myMaxRate = 0;

    if( theRateList )
    {
        myBitSet[ INDEX_RateList ] = true;
        myRateList = *theRateList;
    }

    if( theExpectedSignalRate )
    {
        myBitSet[ INDEX_ExpectedSignalRateRange ] = true;
        myExpectedSignalRateRange = *theExpectedSignalRate;
    }
    else
    {
        myExpectedSignalRate = 0;
        myExpectedSignalRateRange.begin = 0;
        myExpectedSignalRateRange.end = 0;
    }

    if( theSignalType )
    {
        myBitSet[ INDEX_SignalType ] = true;
        mySignalType = *theSignalType;
    }
    else
        mySignalType = CT_TEL_SIGNAL_UNKNOWN;

    if( theStsMap )
    {
        myBitSet[ INDEX_StsMap ] = true;
        myStsMap = *theStsMap;
    }

    if( theTrace )
    {
        myBitSet[ INDEX_Trace ] = true;
        myTrace = *theTrace;
    }

    if( theExpectedTrace )
    {
        myBitSet[ INDEX_ExpectedTrace ] = true;
        myExpectedTrace = *theExpectedTrace;
    }

    if( theIncomingTrace )
    {
        myBitSet[ INDEX_IncomingTrace ] = true;
        myIncomingTrace = *theIncomingTrace;
    }

    if( isMonitorTraceEnabled )
    {
        myBitSet[ INDEX_MonitorTraceEnabled ] = true;
        myMonitorTraceEnabled = *isMonitorTraceEnabled;
    }
    else 
       myMonitorTraceEnabled = 0;

    if( isInsertAisEnabled )
    {
        myBitSet[ INDEX_InsertAisEnabled ] = true;
        myInsertAisEnabled = *isInsertAisEnabled;
    }
    else 
        myInsertAisEnabled = 0;

    if( isProtectionEnabled )
    {
        myBitSet[ INDEX_ProtectionEnabled ] = true;
        myProtectionEnabled = *isProtectionEnabled;
    }
    else 
        myProtectionEnabled = 0;

    if( theMaintProp)
    {
        myBitSet[ INDEX_MaintPropagate ] = true;
        myMaintProp = *theMaintProp;
    }
    else
        myMaintProp = 0;

    if(theMapping)
    {
        myBitSet[ INDEX_Mapping ] = true;
        myMapping = *theMapping;
    }
    else
        myMapping = CT_TEL_HOP_MAPPING_UNKNOWN;

    if(theExternalConectivity)
    {
        myBitSet[ INDEX_ExternalConectivity ] = true;
        myExternalConectivity = *theExternalConectivity;
    }
    else
        myExternalConectivity = CT_FAC_EXT_NO;

    if(theSFThreshold)
    {
        myBitSet[ INDEX_SFThreshold ] = true;
        mySFThreshold = *theSFThreshold;
    }
    else 
        mySFThreshold = CT_TEL_NO_BER;

    if(theSDThreshold)
    {
        myBitSet[ INDEX_SDThreshold ] = true;
        mySDThreshold = *theSDThreshold;
    }
    else
        mySDThreshold = CT_TEL_NO_BER;

    if(theBurstyBerSdInterval)
    {
        myBitSet[ INDEX_BurstyBerSdInterval ] = true;
        myBurstyBerSdInterval = *theBurstyBerSdInterval;
    }
    else
        myBurstyBerSdInterval = 0;

    if(theBurstyBerSdThreshold)
    {
        myBitSet[ INDEX_BurstyBerSdThreshold ] = true;
        myBurstyBerSdThreshold = *theBurstyBerSdThreshold;
    }
    else
        myBurstyBerSdThreshold = 0;

    if( theConnectedTo )
    {
        myBitSet[ INDEX_ConnectedTo ] = true;
        myConnectedTo = *theConnectedTo;
    }
    else
        myConnectedTo.SetToDefault(true);

    if ( theTransparent )
    {
        myBitSet[ INDEX_Transparent ] = true;
        myTransparent = *theTransparent;
    }
    else
        myTransparent = 0;

    if ( theSsmSupported )
    {
        myBitSet[ INDEX_SsmSupported ] = true;
        mySsmSupported = *theSsmSupported;
    }
    else 
        mySsmSupported = 0;

    if ( theSsmReceived )
    {
        myBitSet[ INDEX_SsmReceived ] = true;
        mySsmReceived = *theSsmReceived;
    }
    else
        mySsmReceived = CT_RxSsm_ALL;

    if ( theActualRate )
    {
        myBitSet[ INDEX_ActualRate ] = true;
        myActRate = *theActualRate;
    }
    else
        myActRate = 0;

    if ( theLineCode )
    {
        myBitSet[ INDEX_LineCode ] = true;
        myLineCode = *theLineCode;
    }
    else
        myLineCode = CT_LineCode_UNKNOWN;

    if ( theFrameFormat )
    {
        myBitSet[ INDEX_FrameFormat ] = true;
        myFrameFormat = *theFrameFormat;
    }
    else
        myFrameFormat = CT_FrameFormat_UNKNOWN;

    if ( theSaBit )
    {
        myBitSet[ INDEX_SaBit ] = true;
        mySaBit = *theSaBit;
    }
    else
        mySaBit = CT_SaBit_UNKNOWN;

    if ( theQualityLevelOverride )
    {
        myBitSet[ INDEX_QualityLevelOverride] = true;
        myQualityLevelOverride = *theQualityLevelOverride;
    }
    else
        myQualityLevelOverride = CT_QualityLevelOverride_DISABLED;

    if ( theTimingReference )
    {   
        myBitSet[ INDEX_TimingReference ] = true;
        myTimingReference = *theTimingReference;
    }
    else
        myTimingReference = CT_TEL_MS_TREF_NONE;

    if ( theGfpMapping )
    {
        myBitSet[ INDEX_GfpMapping ] = true;
        myGfpMapping = *theGfpMapping;
    }
    else
        myGfpMapping = CT_TEL_GFP_FRAMING_UNKNOWN;

    if ( theGenTrc )
    {
        myBitSet[ INDEX_GenTrc ] = true;
        myGenTrc = *theGenTrc;
    }
    else
        myGenTrc = 0;

    if ( theLOSThreshold )
    {
        myBitSet[ INDEX_LOSThreshold ] = true;
        myLOSThreshold = *theLOSThreshold;
    }
    else
        myLOSThreshold = 0;

    if ( theSWThreshold )
    {
        myBitSet[ INDEX_SWThreshold ] = true;
        mySWThreshold = *theSWThreshold;
    }
    else
        mySWThreshold = 0;

    if ( theSignalBand )
    {
        myBitSet[ INDEX_SignalBand ] = true;
        mySignalBand = *theSignalBand;
    }
    else
        mySignalBand = CT_TEL_UNKNOWN_BAND;

    if ( theNendALS )
    {
        myBitSet[ INDEX_NendALS ] = true;
        myNendALS = *theNendALS;
    }
    else
        myNendALS = 0;

    if ( theNValue )
    {
        myBitSet[ INDEX_NValue ] = true;
        myNValue = *theNValue;
    }
    else
        myNValue = CT_FAC_NVALUE_NA;


    if ( theFecType )
    {
        myBitSet[ INDEX_FecType ] = true;
        myFecType = *theFecType;
    }
    else
        myFecType = CT_TEL_FEC_TYPE_NONE;

    if ( theTransMap )
    {
        myBitSet[ INDEX_TransMap ] = true;
        myTransMap = *theTransMap;
    }
    else
        myTransMap = CT_TEL_SIGNAL_TGLAN;

    if ( theClkType )
    {
        myBitSet[ INDEX_ClkType ] = true;
        myClkType = *theClkType;
    }
    else
        myClkType = CT_TEL_SIGNAL_OTU2;

    if ( theTapNumber)
    {
        myBitSet[ INDEX_TapNumber] = true;
        myTapNumber= *theTapNumber;
    }

    if ( isAutoNegotiationEnabled )
    {
        myBitSet[ INDEX_AutoNegotiation ] = true;
        myAutoNegotiationEnabled= *isAutoNegotiationEnabled;
    }
    else 
        myAutoNegotiationEnabled = false;

    if ( theOtuExpTrc )
    {
        myBitSet[ INDEX_OtuExpTrc ] = true;
        myOtuExpTrc = *theOtuExpTrc;
    }

    if ( theOtuTrc )
    {
        myBitSet[ INDEX_OtuTrc ] = true;
        myOtuTrc = *theOtuTrc;
    }

    if ( isOtuMonitorTraceEnabled )
    {
        myBitSet[ INDEX_OtuMonTrc ] = true;
        myOtuMonTrc = *isOtuMonitorTraceEnabled;
    }
    else 
        myOtuMonTrc = 0;

    if ( theOtuIncTrc )
    {
        myBitSet[ INDEX_OtuIncTrc ] = true;
        myOtuIncTrc = *theOtuIncTrc;
    }

    if ( theOeoRegen )
    {
        myBitSet[ INDEX_OeoRegen ] = true;
        myOeoRegen = *theOeoRegen;
    }
    else
        myOeoRegen = CT_TEL_OEO_REGEN_OFF;

    if( theStsCstMap )
    {
        myBitSet[ INDEX_StsCstMap ] = true;
        myStsCstMap = *theStsCstMap;
    }

    if( theAddCrsMap )
    {
        myBitSet[ INDEX_AddCrsMap ] = true;
        myAddCrsMap = *theAddCrsMap;
    }

    if( theDelCrsMap )
    {
        myBitSet[ INDEX_DelCrsMap ] = true;
        myDelCrsMap = *theDelCrsMap;
    }

    if ( theCnvType )
    {
        myBitSet[ INDEX_CnvType ] = true;
        myCnvType = *theCnvType;
    }
    else
        myCnvType = CT_TEL_TERMSIZE_STS1;

    if( theAlarmProfile )
    {
        myBitSet[ INDEX_AlarmProfile ] = true;
        myAlarmProfile = *theAlarmProfile;
    }
    else
        myAlarmProfile = CT_UNKNOWN_PT;

    if( thePt )
    {
        myBitSet[ INDEX_Pt ] = true;
        myPt = *thePt;
    }
    else
        myPt = 0;

    if( thePtRx )
    {
        myBitSet[ INDEX_PtRx ] = true;
        myPtRx = *thePtRx;
    }
    else
        myPtRx = 0;

    
    if( theUpi )
    {
        myBitSet[ INDEX_GfpUpi ] = true;
        myGfpUpi = *theUpi;
    }
    else
        myGfpUpi = 0;

    if( theAddCstMap )
    {
        myBitSet[ INDEX_AddCstMap ] = true;
        myAddCstMap = *theAddCstMap;
    }

    if( theDelCstMap )
    {
        myBitSet[ INDEX_DelCstMap ] = true;
        myDelCstMap = *theDelCstMap;
    }

    if( theAutoCfg )
    {
        myBitSet[ INDEX_AutoCfg ] = true;
        myAutoCfg = *theAutoCfg;
    }

    if ( theNpOwner )
    {
        myBitSet[ INDEX_NpOwner ] = true;
        myNpOwner = *theNpOwner;
    }

    if ( theQuarantine )
    {
        myBitSet[ INDEX_Quarantine ] = true;
        myQuarantine = *theQuarantine;
    }

    if ( theDiscardPause )
    {
        myBitSet[ INDEX_DiscardPause ] = true;
        myDiscardPause = *theDiscardPause;
    }
    else
        myDiscardPause = 0;

    if ( thePropFefi )
    {
        myBitSet[ INDEX_PropFefi ] = true;
        myPropFefi = *thePropFefi;
    }
    else
        myPropFefi = 0;

    if( thePST )
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }
    else
        myPST = 0;

    if( thePSTQ )
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
    else 
        myPSTQ = 0;

    if( theSST )
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
    else
        mySST = 0;

    if( thePmProfile )
    {
        myBitSet[ INDEX_PmProfile ] = true;
        myPmProfile = *thePmProfile;
    }
    else
        myPmProfile = CT_PM_UNKNOWN_PT;

    if( theCbrMap )
    {
        myBitSet[ INDEX_CbrMap ] = true;
        myCbrMap = *theCbrMap;
    }
    else
        myCbrMap = NULL_MAPPING;
    

    if( theGfpMux )
    {
        myBitSet[ INDEX_GfpMux ] = true;
        myGfpMux = *theGfpMux;
    }
    else
        myGfpMux = CT_TEL_GFPMUX_NA;

    if( myOpuFmt )
    {
        myBitSet[ INDEX_Opu ] = true;
        myOpuFmt = *theOpuFmt;
    }
    else
        myOpuFmt = CT_TEL_OPU_UNKNOWN;

    if( theOpTribSize )
    {
        myBitSet[ INDEX_OpTribSize ] = true;
        myOpTribSize = *theOpTribSize;
    }
    else
    {
        myOpTribSize = CT_TEL_TS_UNKNOWN;
    }

    if( myTribSize )
    {
        myBitSet[ INDEX_TribSize ] = true;
        myTribSize = *theTribSize;
    }
    else
        myTribSize = CT_TEL_TS_UNKNOWN;    

    if( theOpadjacent )
    {
        myBitSet[ INDEX_Opadjacent ] = true;

        myOpadjacent = *theOpadjacent;
    }
    else
        myOpadjacent.Reset();

    if( theTcmMode )
    {
        myBitSet[ INDEX_TcmMode ] = true;
        myTcmMode = *theTcmMode;
    }
    else
        myTcmMode = CT_TCM_MODE_UNKNOWN;


    if( theCFProfile )
    {
        myBitSet[ INDEX_CFProfile ] = true;
        myCFProfile = *theCFProfile;
    }
    else
        {
        myCFProfile = 99;
    }


    if( theTimDef )
    {
        myBitSet[INDEX_TimDef] = true;
        myTimDefMode = *theTimDef;
    }
    else
    {
        myTimDefMode = CT_TEL_TIM_UNKNOWN;
    }

    if ( theExpDapi )
    {
        myBitSet[INDEX_ExpDapi] = true;
        myExpDapi = *theExpDapi;
    }
    
    if ( theExpSapi )
    {
        myBitSet[INDEX_ExpSapi] = true;
        myExpSapi = *theExpSapi;
    }
    
    if ( theTxDapi )
    {
        myBitSet[INDEX_TxDapi] = true;
        myTxDapi = *theTxDapi;
    }

    if ( theTxSapi )
    {
        myBitSet[INDEX_TxSapi] = true;
        myTxSapi = *theTxSapi;
    }

    if ( theChannel )
    {
        myBitSet[INDEX_Channel] = true;
        myChannel = *theChannel;
    }
    else
    {
        //myChannel = CT_RelativeWavelength(CT_UNKNOWN_WAVELENGTH_INDEX);
        myChannel = 0xff;
    }

    if( theLacpPartiMode )
    {
        myBitSet[ INDEX_LacpPartiMode ] = true;
        myLacpPartiMode = *theLacpPartiMode;
    }
    else
    {
        myLacpPartiMode = CT_TEL_LacpPartiMode_UNKNOWN;
    }

    if( theLacpPriority )
    {
        myBitSet[ INDEX_LacpPriority ] = true;
        myLacpPriority = *theLacpPriority;
    }
    else
    {
        myLacpPriority = 0;
    }

    if( theTribFall )
    {
        myBitSet[ INDEX_TribFall ] = true;
        myTribFall = *theTribFall;
    }
    else
    {
        myTribFall = false;
    }

    if( theDmSource )
    {
        myBitSet[ INDEX_DmSource ] = true;
        myDmSource = *theDmSource;
    }
    else
    {
        myDmSource = false;
    }

	if( theLtcActMode)
    {
        myBitSet[ INDEX_LtcActMode] = true;
        myLtcActMode= *theLtcActMode;
    }
    else
    {
        myLtcActMode = false;
    }

    if( theGfpTs )
    {
        myBitSet[ INDEX_GfpTs ] = true;
        myGfpTs = *theGfpTs;
    }
    else
    {
        myGfpTs = 0;
    }

    if( theInterPacketGap )
    {
        myBitSet[ INDEX_InterPacketGap ] = true;
        myInterPacketGap = *theInterPacketGap;
    }
    else
        myInterPacketGap = 0;

    if( theOpuConfig )
    {
        myBitSet[ INDEX_OpuConfig ] = true;
        myOpuConfig = *theOpuConfig;
    }
    else
        myOpuConfig = CT_TEL_OPU_UNKNOWN;

    if ( theQualityLevel)
    {
        myBitSet[ INDEX_QualityLevel] = true;
        myQualityLevel= *theQualityLevel;
    }
    else
        myQualityLevel = CT_QualityLevelOverride_DISABLED;

    if ( theOTNMap )
    {
        myBitSet[ INDEX_OTNMap ] = true;
        myOTNMap = *theOTNMap;
    }
    else
        myOTNMap = 0;

    if ( theHgeMap )
    {
        myBitSet[ INDEX_HGEMAP ] = true;
        myHgeMap = *theHgeMap;
    }
    else
        myHgeMap = CT_TEL_GMP_MAPPING;

    if ( theMapMode )
    {
        myBitSet[ INDEX_MAPMODE] = true;
        myMapMode= *theMapMode;
    }
    else
        myMapMode = BIT_SYNC_CBR_MAPPING;


    if (theMacAddr)
    {
        myBitSet[ INDEX_MACADDR ] = true;
        myMacAddr = *theMacAddr;
    }
    if(thePluggableReach)
    {
        myBitSet[ INDEX_PluggableReach ] = true;
        myPluggableReach = *thePluggableReach;
    }
    else
        myPluggableReach = CT_FAC_PluggableReach_UNKNOWN;
}


TL1_FACRspBlk:: TL1_FACRspBlk(const string *theEntityName,
                              const CT_TL1_FacAddr* theAddr,
                              const CT_SM_PST*  thePST,
                              const CT_SM_PSTQ* thePSTQ,
                              const CT_SM_SST*  theSST)
    : myBitSet( INDEX_END, false )
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *theAddr;
    }

    if( thePST )
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }
    else
        myPST = 0;

    if( thePSTQ )
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
    else 
        myPSTQ = 0;

    if( theSST )
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
    else
        mySST = 0;
}

TL1_FACRspBlk::TL1_FACRspBlk(const TL1_FACRspBlk& facBlk)
    : myBitSet( INDEX_END, false )
{
    myBitSet                    = facBlk.myBitSet;
    myEntityName                = facBlk.myEntityName;
    myFacAddr                   = facBlk.myFacAddr;
    myCardType                  = facBlk.myCardType;
    mySubCardType               = facBlk.mySubCardType;
    myAdaptive                  = facBlk.myAdaptive;
    myMaxRate                   = facBlk.myMaxRate;
    myRateList                  = facBlk.myRateList;
    myExpectedSignalRate        = facBlk.myExpectedSignalRate;
    myExpectedSignalRateRange   = facBlk.myExpectedSignalRateRange;
    mySignalType                = facBlk.mySignalType;
    myStsMap                    = facBlk.myStsMap;
    myTrace                     = facBlk.myTrace;
    myExpectedTrace             = facBlk.myExpectedTrace;
    myIncomingTrace             = facBlk.myIncomingTrace;
    myMonitorTraceEnabled       = facBlk.myMonitorTraceEnabled;
    myInsertAisEnabled          = facBlk.myInsertAisEnabled;
    myProtectionEnabled         = facBlk.myProtectionEnabled;
    myMaintProp                 = facBlk.myMaintProp;
    myMapping                   = facBlk.myMapping;
    myExternalConectivity       = facBlk.myExternalConectivity;
    mySFThreshold               = facBlk.mySFThreshold;
    mySDThreshold               = facBlk.mySDThreshold;
    myBurstyBerSdInterval       = facBlk.myBurstyBerSdInterval;
    myBurstyBerSdThreshold      = facBlk.myBurstyBerSdThreshold;
    myConnectedTo               = facBlk.myConnectedTo;
    myTransparent               = facBlk.myTransparent;
    mySsmSupported              = facBlk.mySsmSupported;
    mySsmReceived               = facBlk.mySsmReceived;
    myTimingReference           = facBlk.myTimingReference;
    myActRate                   = facBlk.myActRate;
    myLineCode                  = facBlk.myLineCode;
    myFrameFormat               = facBlk.myFrameFormat;
    mySaBit                     = facBlk.mySaBit;
    myQualityLevelOverride      = facBlk.myQualityLevelOverride;
    myGfpMapping                = facBlk.myGfpMapping;
    myGenTrc                    = facBlk.myGenTrc;
    myLOSThreshold              = facBlk.myLOSThreshold;
    mySWThreshold               = facBlk.mySWThreshold;
    mySignalBand                = facBlk.mySignalBand;
    myNendALS                   = facBlk.myNendALS;
    myNValue                    = facBlk.myNValue;
    myFecType                   = facBlk.myFecType;
    myTransMap                  = facBlk.myTransMap;
    myOtuExpTrc                 = facBlk.myOtuExpTrc;
    myOtuTrc                    = facBlk.myOtuTrc;
    myOtuMonTrc                 = facBlk.myOtuMonTrc; 
    myOtuIncTrc                 = facBlk.myOtuIncTrc; 
    myOeoRegen                  = facBlk.myOeoRegen;
    myStsCstMap                 = facBlk.myStsCstMap;
    myAddCrsMap                 = facBlk.myAddCrsMap;
    myDelCrsMap                 = facBlk.myDelCrsMap;
    myCnvType                   = facBlk.myCnvType;
    myClkType                   = facBlk.myClkType;
    myTapNumber                 = facBlk.myTapNumber;
    myAutoNegotiationEnabled    = facBlk.myAutoNegotiationEnabled;
    myAlarmProfile              = facBlk.myAlarmProfile;
    myPt                       = facBlk.myPt;
    myPtRx                       = facBlk.myPtRx;
    myGfpUpi                    = facBlk.myGfpUpi;
    myAddCstMap                 = facBlk.myAddCstMap;
    myDelCstMap                 = facBlk.myDelCstMap;
    myAutoCfg                   = facBlk.myAutoCfg;
    myNpOwner                   = facBlk.myNpOwner;
    myQuarantine                = facBlk.myQuarantine;
    myEthRate                   = facBlk.myEthRate;
    myOpEthRate                 = facBlk.myOpEthRate;
    myDuplexMode                = facBlk.myDuplexMode;
    myOpDuplexMode              = facBlk.myOpDuplexMode;
    myTcmMode                   = facBlk.myTcmMode;
    myFlowControl               = facBlk.myFlowControl;
    myOpFlowControl             = facBlk.myOpFlowControl;
    myAutonegStatus             = facBlk.myAutonegStatus;
    myAutonegRmtSgl             = facBlk.myAutonegRmtSgl;
    myAdvFlowCtrl               = facBlk.myAdvFlowCtrl;
    myOpAutoneg                 = facBlk.myOpAutoneg;
    myDiscardPause              = facBlk.myDiscardPause;
    myPropFefi                  = facBlk.myPropFefi;
    myPST                       = facBlk.myPST;
    myPSTQ                      = facBlk.myPSTQ;
    mySST                       = facBlk.mySST;
    myVcgName                   = facBlk.myVcgName;
    myVcgAddr                   = facBlk.myVcgAddr;
    myVlanTag                   = facBlk.myVlanTag;
    myTagMode                   = facBlk.myTagMode;
    myTpid                      = facBlk.myTpid;
    myPmProfile                 = facBlk.myPmProfile;
    myCFProfile                 = facBlk.myCFProfile;
    myCbrMap                    = facBlk.myCbrMap;
    myGfpMux                    = facBlk.myGfpMux;
    myOpuFmt                    = facBlk.myOpuFmt;
    myOpTribSize                = facBlk.myOpTribSize;
    myTribSize                  = facBlk.myTribSize;
    myOpadjacent                = facBlk.myOpadjacent;
    myTimDefMode                = facBlk.myTimDefMode;
    myExpDapi                   = facBlk.myExpDapi;
    myExpSapi                   = facBlk.myExpSapi;
    myTxDapi                    = facBlk.myTxDapi;
    myTxSapi                    = facBlk.myTxSapi;
    myChannel                   = facBlk.myChannel;
    myConnected1                = facBlk.myConnected1;
    myConnected2                = facBlk.myConnected2;
    myLacpPriority              = facBlk.myLacpPriority;
    myLacpPartiMode             = facBlk.myLacpPartiMode;
    myTribSlot                  = facBlk.myTribSlot;
    myAisType                   = facBlk.myAisType;
    myTribFall                  = facBlk.myTribFall;
    myDmSource                  = facBlk.myDmSource;
	myLtcActMode                = facBlk.myLtcActMode;
    myGfpTs                     = facBlk.myGfpTs;
    myInterPacketGap            = facBlk.myInterPacketGap;
    myQualityLevel              = facBlk.myQualityLevel;
    myOpuConfig                 = facBlk.myOpuConfig;
    myOTNMap                    = facBlk.myOTNMap;
    myHgeMap                    = facBlk.myHgeMap;
    myMapMode                   = facBlk.myMapMode;
	myMacAddr                   = facBlk.myMacAddr;
    myPluggableReach            = facBlk.myPluggableReach;
}

TL1_FACRspBlk::~TL1_FACRspBlk()
{
}

TL1_FACRspBlk& TL1_FACRspBlk::operator=( const TL1_FACRspBlk& theBlock )
{
    myBitSet                    = theBlock.myBitSet;
    myEntityName                = theBlock.myEntityName;
    myFacAddr                   = theBlock.myFacAddr;
    myCardType                  = theBlock.myCardType;
    mySubCardType               = theBlock.mySubCardType;
    myAdaptive                  = theBlock.myAdaptive;
    myMaxRate                   = theBlock.myMaxRate;
    myRateList                  = theBlock.myRateList;
    myExpectedSignalRate        = theBlock.myExpectedSignalRate;
    myExpectedSignalRateRange   = theBlock.myExpectedSignalRateRange;
    mySignalType                = theBlock.mySignalType;
    myStsMap                    = theBlock.myStsMap;
    myTrace                     = theBlock.myTrace;
    myExpectedTrace             = theBlock.myExpectedTrace;
    myIncomingTrace             = theBlock.myIncomingTrace;
    myMonitorTraceEnabled       = theBlock.myMonitorTraceEnabled;
    myInsertAisEnabled          = theBlock.myInsertAisEnabled;
    myProtectionEnabled         = theBlock.myProtectionEnabled;
    myMaintProp                 = theBlock.myMaintProp;
    myMapping                   = theBlock.myMapping;
    myExternalConectivity       = theBlock.myExternalConectivity;
    mySFThreshold               = theBlock.mySFThreshold;
    mySDThreshold               = theBlock.mySDThreshold;
    myBurstyBerSdInterval       = theBlock.myBurstyBerSdInterval;
    myBurstyBerSdThreshold      = theBlock.myBurstyBerSdThreshold;
    myConnectedTo               = theBlock.myConnectedTo;
    myTransparent               = theBlock.myTransparent;
    mySsmSupported              = theBlock.mySsmSupported;
    mySsmReceived               = theBlock.mySsmReceived;
    myTimingReference           = theBlock.myTimingReference;
    myActRate                   = theBlock.myActRate;
    myLineCode                  = theBlock.myLineCode;
    myFrameFormat               = theBlock.myFrameFormat;
    mySaBit                     = theBlock.mySaBit;
    myQualityLevelOverride      = theBlock.myQualityLevelOverride;
    myGfpMapping                = theBlock.myGfpMapping;
    myGenTrc                    = theBlock.myGenTrc;
    myLOSThreshold              = theBlock.myLOSThreshold;
    mySWThreshold               = theBlock.mySWThreshold;
    mySignalBand                = theBlock.mySignalBand;
    myNendALS                   = theBlock.myNendALS;
    myNValue                    = theBlock.myNValue;
    myFecType                   = theBlock.myFecType;
    myTransMap                  = theBlock.myTransMap;
    myOtuExpTrc                 = theBlock.myOtuExpTrc;
    myOtuTrc                    = theBlock.myOtuTrc;
    myOtuMonTrc                 = theBlock.myOtuMonTrc; 
    myOtuIncTrc                 = theBlock.myOtuIncTrc; 
    myOeoRegen                  = theBlock.myOeoRegen;
    myStsCstMap                 = theBlock.myStsCstMap;
    myAddCrsMap                 = theBlock.myAddCrsMap;
    myDelCrsMap                 = theBlock.myDelCrsMap;
    myCnvType                   = theBlock.myCnvType;
    myClkType                   = theBlock.myClkType;
    myTapNumber                 = theBlock.myTapNumber;
    myAutoNegotiationEnabled    = theBlock.myAutoNegotiationEnabled;
    myAlarmProfile              = theBlock.myAlarmProfile;
    myPt                       = theBlock.myPt;
    myPtRx                       = theBlock.myPtRx;
    myGfpUpi                    = theBlock.myGfpUpi;
    myAddCstMap                 = theBlock.myAddCstMap;
    myDelCstMap                 = theBlock.myDelCstMap;
    myAutoCfg                   = theBlock.myAutoCfg;
    myNpOwner                   = theBlock.myNpOwner;
    myQuarantine                = theBlock.myQuarantine;
    myEthRate                   = theBlock.myEthRate;
    myOpEthRate                 = theBlock.myOpEthRate;
    myDuplexMode                = theBlock.myDuplexMode;
    myOpDuplexMode              = theBlock.myOpDuplexMode;
    myTcmMode                   = theBlock.myTcmMode;
    myFlowControl               = theBlock.myFlowControl;
    myOpFlowControl             = theBlock.myOpFlowControl;
    myAutonegStatus             = theBlock.myAutonegStatus;
    myAutonegRmtSgl             = theBlock.myAutonegRmtSgl;
    myAdvFlowCtrl               = theBlock.myAdvFlowCtrl;
    myOpAutoneg                 = theBlock.myOpAutoneg;
    myDiscardPause              = theBlock.myDiscardPause;
    myPropFefi                  = theBlock.myPropFefi;
    myPST                       = theBlock.myPST;
    myPSTQ                      = theBlock.myPSTQ;
    mySST                       = theBlock.mySST;
    myVcgName                   = theBlock.myVcgName;
    myVcgAddr                   = theBlock.myVcgAddr;
    myVlanTag                   = theBlock.myVlanTag;
    myTagMode                   = theBlock.myTagMode;
    myTpid                      = theBlock.myTpid;
    myPmProfile                 = theBlock.myPmProfile;
    myCFProfile                 = theBlock.myCFProfile;
    myCbrMap                    = theBlock.myCbrMap;
    myGfpMux                    = theBlock.myGfpMux;
    myOpuFmt                    = theBlock.myOpuFmt;
    myOpTribSize                = theBlock.myOpTribSize;
    myTribSize                  = theBlock.myTribSize;
    myOpadjacent                = theBlock.myOpadjacent;
    myTimDefMode                = theBlock.myTimDefMode;
    myExpDapi                   = theBlock.myExpDapi;
    myExpSapi                   = theBlock.myExpSapi; 
    myTxDapi                    = theBlock.myTxDapi;
    myTxSapi                    = theBlock.myTxSapi;
    myChannel                   = theBlock.myChannel;
    myConnected1                = theBlock.myConnected1;
    myConnected2                = theBlock.myConnected2;
    myLacpPriority              = theBlock.myLacpPriority;
    myLacpPartiMode             = theBlock.myLacpPartiMode;
    myTribSlot                  = theBlock.myTribSlot;
    myAisType                   = theBlock.myAisType;
    myTribFall                  = theBlock.myTribFall;
    myDmSource                  = theBlock.myDmSource;
	myLtcActMode                = theBlock.myLtcActMode;
    myGfpTs                     = theBlock.myGfpTs;
    myInterPacketGap            = theBlock.myInterPacketGap;
    myQualityLevel              = theBlock.myQualityLevel;
    myOpuConfig                 = theBlock.myOpuConfig;
    myOTNMap                    = theBlock.myOTNMap;
    myHgeMap                    = theBlock.myHgeMap;
    myMapMode                   = theBlock.myMapMode;
    myMacAddr                   = theBlock.myMacAddr;
    myPluggableReach            = theBlock.myPluggableReach;
    return *this;
}

bool TL1_FACRspBlk::operator==( const TL1_FACRspBlk& theBlock ) const
{
    return ( myBitSet                           == theBlock.myBitSet &&
             myEntityName                       == theBlock.myEntityName &&
             myFacAddr                          == theBlock.myFacAddr &&
             myCardType                         == theBlock.myCardType &&
             mySubCardType                      == theBlock.mySubCardType &&
             myAdaptive                         == theBlock.myAdaptive &&
             myMaxRate                          == theBlock.myMaxRate &&
             myRateList                         == theBlock.myRateList &&
             myExpectedSignalRate               == theBlock.myExpectedSignalRate &&
             myExpectedSignalRateRange.begin    == theBlock.myExpectedSignalRateRange.begin &&
             myExpectedSignalRateRange.end      == theBlock.myExpectedSignalRateRange.end &&
             mySignalType                       == theBlock.mySignalType &&
             myStsMap                           == theBlock.myStsMap &&
             myTrace                            == theBlock.myTrace &&
             myExpectedTrace                    == theBlock.myExpectedTrace &&
             myIncomingTrace                    == theBlock.myIncomingTrace &&
             myMonitorTraceEnabled              == theBlock.myMonitorTraceEnabled &&
             myInsertAisEnabled                 == theBlock.myInsertAisEnabled &&
             myProtectionEnabled                == theBlock.myProtectionEnabled &&
             myMaintProp                        == theBlock.myMaintProp&&
             myMapping                          == theBlock.myMapping &&
             myExternalConectivity              == theBlock.myExternalConectivity &&
             mySFThreshold                      == theBlock.mySFThreshold &&
             mySDThreshold                      == theBlock.mySDThreshold &&
             myBurstyBerSdInterval              == theBlock.myBurstyBerSdInterval &&
             myBurstyBerSdThreshold             == theBlock.myBurstyBerSdThreshold &&
             myConnectedTo                      == theBlock.myConnectedTo &&
             myTransparent                      == theBlock.myTransparent &&
             mySsmSupported                     == theBlock.mySsmSupported &&
             mySsmReceived                      == theBlock.mySsmReceived &&
             myTimingReference                  == theBlock.myTimingReference &&
             myActRate                          == theBlock.myActRate &&
             myLineCode                         == theBlock.myLineCode &&
             myFrameFormat                      == theBlock.myFrameFormat &&
             mySaBit                            == theBlock.mySaBit &&
             myQualityLevelOverride             == theBlock.myQualityLevelOverride &&
             myGfpMapping                       == theBlock.myGfpMapping &&
             myGenTrc                           == theBlock.myGenTrc &&
             myLOSThreshold                     == theBlock.myLOSThreshold &&
             mySWThreshold                      == theBlock.mySWThreshold &&
             mySignalBand                       == theBlock.mySignalBand &&
             myNendALS                          == theBlock.myNendALS &&
             myNValue                           == theBlock.myNValue &&
             myFecType                          == theBlock.myFecType &&
             myTransMap                         == theBlock.myTransMap &&
             myOtuExpTrc                        == theBlock.myOtuExpTrc &&
             myOtuTrc                           == theBlock.myOtuTrc &&
             myOtuMonTrc                        == theBlock.myOtuMonTrc&& 
             myOtuIncTrc                        == theBlock.myOtuIncTrc&& 
             myOeoRegen                         == theBlock.myOeoRegen&&
             myStsCstMap                        == theBlock.myStsCstMap &&
             myAddCrsMap                        == theBlock.myAddCrsMap &&
             myDelCrsMap                        == theBlock.myDelCrsMap &&
             myCnvType                          == theBlock.myCnvType &&
             myClkType                          == theBlock.myClkType &&
             myTapNumber                        == theBlock.myTapNumber&&
             myAutoNegotiationEnabled           == theBlock.myAutoNegotiationEnabled &&
             myAlarmProfile                     == theBlock.myAlarmProfile &&
             myPt                              == theBlock.myPt &&
             myPtRx                              == theBlock.myPtRx &&
             myGfpUpi                           == theBlock.myGfpUpi &&
             myAddCstMap                        == theBlock.myAddCstMap &&
             myDelCstMap                        == theBlock.myDelCstMap &&
             myAutoCfg                          == theBlock.myAutoCfg &&
             myNpOwner                          == theBlock.myNpOwner &&
             myQuarantine                       == theBlock.myQuarantine &&
             myEthRate                          == theBlock.myEthRate &&
             myOpEthRate                        == theBlock.myOpEthRate &&
             myDuplexMode                       == theBlock.myDuplexMode &&
             myOpDuplexMode                     == theBlock.myOpDuplexMode &&
             myTcmMode                          == theBlock.myTcmMode &&
             myFlowControl                      == theBlock.myFlowControl &&
             myOpFlowControl                    == theBlock.myOpFlowControl &&
             myAutonegStatus                    == theBlock.myAutonegStatus &&
             myAutonegRmtSgl                    == theBlock.myAutonegRmtSgl &&
             myAdvFlowCtrl                      == theBlock.myAdvFlowCtrl &&
             myOpAutoneg                        == theBlock.myOpAutoneg &&
             myPST                              == theBlock.myPST &&
             myPSTQ                             == theBlock.myPSTQ &&
             mySST                              == theBlock.mySST &&
             myVcgName                          == theBlock.myVcgName &&
             myVcgAddr                          == theBlock.myVcgAddr &&
             myVlanTag                          == theBlock.myVlanTag &&
             myTagMode                          == theBlock.myTagMode &&
             myDiscardPause                     == theBlock.myDiscardPause &&
             myPropFefi                         == theBlock.myPropFefi &&
             myTpid                             == theBlock.myTpid &&
             myPmProfile                        == theBlock.myPmProfile &&
             myCFProfile                        == theBlock.myCFProfile &&
             myGfpMux                           == theBlock.myGfpMux &&
             myOpuFmt                           == theBlock.myOpuFmt &&
             myOpTribSize                       == theBlock.myOpTribSize &&
             myTribSize                         == theBlock.myTribSize &&
             myOpadjacent                       == theBlock.myOpadjacent &&
             myCbrMap                           == theBlock.myCbrMap &&
             myTimDefMode                       == theBlock.myTimDefMode &&
             myExpDapi                          == theBlock.myExpDapi &&
             myExpSapi                          == theBlock.myExpSapi &&
             myTxDapi                           == theBlock.myTxDapi &&
             myTxSapi                           == theBlock.myTxSapi &&
             myConnected1                       == theBlock.myConnected1 &&
             myConnected2                       == theBlock.myConnected2 &&
             myTribSlot                         == theBlock.myTribSlot &&
             myTribFall                         == theBlock.myTribFall &&
             myDmSource                         == theBlock.myDmSource &&
             myLtcActMode                       == theBlock.myLtcActMode &&
             myGfpTs                            == theBlock.myGfpTs &&
             myInterPacketGap                   == theBlock.myInterPacketGap &&
             myChannel                          == theBlock.myChannel &&
             myLacpPriority                     == theBlock.myLacpPriority &&
             myLacpPartiMode                    == theBlock.myLacpPartiMode &&
             myAisType                          == theBlock.myAisType &&
             myLacpPartiMode                    == theBlock.myLacpPartiMode &&
             myQualityLevel                     == theBlock.myQualityLevel &&
             myOpuConfig                        == theBlock.myOpuConfig &&
             myOTNMap                           == theBlock.myOTNMap &&
             myHgeMap                           == theBlock.myHgeMap &&
             myMapMode                          == theBlock.myMapMode &&
             myMacAddr                          == theBlock.myMacAddr &&
             myPluggableReach                   == theBlock.myPluggableReach);

}

bool TL1_FACRspBlk::operator<( const TL1_FACRspBlk& theBlock ) const
{
    CT_TL1_FacAddr theFacAddr;
    string theEntityName;
    //first compare the AID, then compare the FacAddr
	if(true == myBitSet[INDEX_EntityName] && theBlock.GetEntityName(theEntityName))
	{
        if((myEntityName=="ODUF"||myEntityName=="ODU0"||myEntityName=="ODU1"||myEntityName=="ODU2"||myEntityName=="ODU3"||myEntityName=="ODU4")
    		&&(theEntityName=="ODUF"||theEntityName=="ODU0"||theEntityName=="ODU1"||theEntityName=="ODU2"||theEntityName=="ODU3"||theEntityName=="ODU4"))
        {
            if(myEntityName=="ODUF" && theEntityName!="ODUF")
            {
                return true;
            }
			else if(myEntityName!="ODUF" && theEntityName=="ODUF")
			{
			    return false;
			}
			else if(myEntityName!=theEntityName)
			{
			    return myEntityName<theEntityName;
			}
        }
	}
	
    if(true == myBitSet[INDEX_FacAddr] && theBlock.GetFacAddr(theFacAddr))
    {
        return myFacAddr < theFacAddr;
    }
    return false;
}

bool TL1_FACRspBlk::GetTribSlot(CT_FAC_OduTsMap& theTribSlot) const
{
    if (true == myBitSet[ INDEX_TribSlot ])
    {
        theTribSlot = myTribSlot;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetTribFall(bool& theTribFall) const
{
    if (true == myBitSet[ INDEX_TribFall ])
    {
        theTribFall = myTribFall;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetDmSource(bool& theDmSource) const
{
    if (true == myBitSet[ INDEX_DmSource ])
    {
        theDmSource = myDmSource;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetLtcActMode(bool& theLtcActMode) const
{
    if (true == myBitSet[ INDEX_LtcActMode])
    {
        theLtcActMode = myLtcActMode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetGfpTs(uint8& theGfpTs) const
{
    if (true == myBitSet[ INDEX_GfpTs ])
    {
        theGfpTs = myGfpTs;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetInterPacketGap(uint8& theInterPacketGap) const
{
    if (true == myBitSet[ INDEX_InterPacketGap ])
    {
        theInterPacketGap = myInterPacketGap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetConnected1(CT_TL1_FacParamAddr& theConnected1) const
{
    if (true == myBitSet[ INDEX_Connected1 ])
    {
        theConnected1 = myConnected1;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetConnected2(CT_TL1_FacParamAddr& theConnected2) const
{
    if (true == myBitSet[ INDEX_Connected2 ])
    {
        theConnected2 = myConnected2;
        return true;
    }
    else
    {
        return false;
    }
}

bool
TL1_FACRspBlk::GetChannel( uint32& theChannel ) const
{
    if (true == myBitSet[ INDEX_Channel ])
    {
        theChannel = myChannel;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetConnectedTo( CT_Fac_ConnectedToString& theConnectedTo ) const
{
    if( true == myBitSet[ INDEX_ConnectedTo ] )
    {
        theConnectedTo = myConnectedTo;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetTransparent( bool& theTransparent ) const
{
    if( true == myBitSet[ INDEX_Transparent ] )
    {
        theTransparent = myTransparent;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetSsmSupported( bool& theSsmSupported ) const
{
    if( true == myBitSet[ INDEX_SsmSupported ] )
    {
        theSsmSupported = mySsmSupported;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetSsmReceived( CT_FAC_RxSsm& theSsmReceived ) const
{
    if( true == myBitSet[ INDEX_SsmReceived ] )
    {
        theSsmReceived = mySsmReceived;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetTimingRef( CT_TEL_MsTref& theTimingReference ) const
{
    if( true == myBitSet[ INDEX_TimingReference ] )
    {
        theTimingReference = myTimingReference;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetEntityName(string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetFacAddr(CT_TL1_FacAddr& theFacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        theFacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_FACRspBlk::GetMemberAddr(CT_TL1_FacAddr& theFacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        theFacAddr = myMemberAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetCardType(CT_CardType& theCardType ) const
{
    if( true == myBitSet[ INDEX_CardType ] )
    {
        theCardType = myCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetSubCardType(CT_SubCardType& theSubCardType ) const
{
    if( true == myBitSet[ INDEX_SubCardType ] )
    {
        theSubCardType = mySubCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetAdaptive( bool& theAdaptive ) const
{
    if( true == myBitSet[ INDEX_Adaptive ] )
    {
        theAdaptive = myAdaptive;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetMaxRate( CT_TEL_daHz& theMaxRate ) const
{    
    if( true == myBitSet[ INDEX_MaxRate ] )
    {
        theMaxRate = myMaxRate;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetRateList( CT_FAC_SignalRateListType& theRateList ) const
{    
    if( true == myBitSet[ INDEX_RateList ] )
    {
        theRateList = myRateList;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetExpectedSignalRate( CT_TEL_daHz& theExpectedSignalRate ) const
{    
    if( true == myBitSet[ INDEX_ExpectedSignalRate ] )
    {
        theExpectedSignalRate = myExpectedSignalRate;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetExpectedRateRange( CT_TL1_ExpectedRateRange& theExpRateRange) const
{    
    if( true == myBitSet[ INDEX_ExpectedSignalRateRange ] )
    {
        theExpRateRange.begin = myExpectedSignalRateRange.begin;
        theExpRateRange.end = myExpectedSignalRateRange.end;

        return true;
    }
    else
    {
        return false;
    }
}
             

bool TL1_FACRspBlk::GetSignalType( CT_TEL_SignalType& theSignalType ) const
{    
    if( true == myBitSet[ INDEX_SignalType ] )
    {
        theSignalType = mySignalType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetStsMap( CT_FAC_StsMap& theStsMap ) const
{    
    if( true == myBitSet[ INDEX_StsMap ] )
    {
        theStsMap = myStsMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetStsCstMap( CT_FAC_StsMap& theStsCstMap ) const
{    
    if( true == myBitSet[ INDEX_StsCstMap ] )
    {
        theStsCstMap = myStsCstMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetAddCrsMap( CT_FAC_StsMap& theAddCrsMap ) const
{    
    if( true == myBitSet[ INDEX_AddCrsMap ] )
    {
        theAddCrsMap = myAddCrsMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetDelCrsMap( CT_FAC_StsMap& theDelCrsMap ) const
{    
    if( true == myBitSet[ INDEX_DelCrsMap ] )
    {
        theDelCrsMap = myDelCrsMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetTrace( CT_Fac_TraceString& theTrace ) const
{    
    if( true == myBitSet[ INDEX_Trace ] )
    {
        theTrace = myTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetExpectedTrace( CT_Fac_TraceString& ExpectedTrace ) const
{
    if( true == myBitSet[ INDEX_ExpectedTrace ] )
    {
        ExpectedTrace = myExpectedTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetIncomingTrace( CT_Fac_TraceString& theIncomingTrace ) const
{
    if( true == myBitSet[ INDEX_IncomingTrace ] )
    {
        theIncomingTrace = myIncomingTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetMonitorTraceEnabled(bool& theMonitorTraceEnabled ) const
{
    if( true == myBitSet[ INDEX_MonitorTraceEnabled ] )
    {
        theMonitorTraceEnabled = myMonitorTraceEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetInsertAisEnabled(bool& theInsertAisEnabled ) const
{
    if( true == myBitSet[ INDEX_InsertAisEnabled ] )
    {
        theInsertAisEnabled = myInsertAisEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetProtectionEnabled( CT_FAC_Protection& theProtectionEnabled ) const
{
    if( true == myBitSet[ INDEX_ProtectionEnabled ] )
    {
        theProtectionEnabled = myProtectionEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetMaintPropagate( CT_FAC_MaintProp& theMaintProp ) const
{
    if( true == myBitSet[ INDEX_MaintPropagate ] )
    {
        theMaintProp = myMaintProp;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
{
    if( true == myBitSet[ INDEX_AlarmProfile ] )
    {
        theAlarmProfile = myAlarmProfile;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetMapping( CT_TEL_HopSpeMapping& theMapping ) const
{
    if( true == myBitSet[ INDEX_Mapping ] )
    {
        theMapping = myMapping;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetExternalConectivity( CT_FAC_ExternalConnectivity& theExternalConectivity ) const
{
    if( true == myBitSet[ INDEX_ExternalConectivity ] )
    {
        theExternalConectivity = myExternalConectivity;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetSFThreshold( CT_TEL_BERLevels& theSFThreshold ) const
{
    if( true == myBitSet[ INDEX_SFThreshold ] )
    {
        theSFThreshold = mySFThreshold;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetSDThreshold( CT_TEL_BERLevels& theSDThreshold ) const
{
    if( true == myBitSet[ INDEX_SDThreshold ] )
    {
        theSDThreshold = mySDThreshold;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetBurstyBerSdInterval( uint16& theBurstyBerSdInterval ) const
{
    if( true == myBitSet[ INDEX_BurstyBerSdInterval ] )
    {
        theBurstyBerSdInterval = myBurstyBerSdInterval;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetBurstyBerSdThreshold( uint32& theBurstyBerSdThreshold ) const
{
    if( true == myBitSet[ INDEX_BurstyBerSdThreshold ] )
    {
        theBurstyBerSdThreshold = myBurstyBerSdThreshold;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetNpOwner( int& theNpOwner ) const
{
    if( true == myBitSet[ INDEX_NpOwner ] )
    {
        theNpOwner = myNpOwner;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetQuarantine( bool& theQuarantine ) const
{
    if( true == myBitSet[ INDEX_Quarantine ] )
    {
        theQuarantine = myQuarantine;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetEthRate(CT_TEL_daHz& theEthRate) const
{
    if( true == myBitSet[ INDEX_EthRate ] )
    {
        theEthRate = myEthRate;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetOpEthRate(CT_TEL_daHz& theOpEthRate) const
{
    if( true == myBitSet[ INDEX_OpEthRate ] )
    {
        theOpEthRate = myOpEthRate;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetDuplexMode(CT_TEL_MAC_DUPLEX_MODE& theDuplexMode) const
{
    if( true == myBitSet[ INDEX_DuplexMode ] )
    {
        theDuplexMode = myDuplexMode;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetOpDuplexMode(CT_TEL_MAC_DUPLEX_MODE& theOpDuplexMode) const
{
    if( true == myBitSet[ INDEX_OpDuplexMode ] )
    {
        theOpDuplexMode = myOpDuplexMode;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetTcmMode(CT_TCM_Mode& theTcmMode) const
{
    if( true == myBitSet[ INDEX_TcmMode ] )
    {
        theTcmMode = myTcmMode;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetFlowControl(CT_TEL_MAC_FLOWCTRL& theFlowControl) const
{
    if( true == myBitSet[ INDEX_FlowControl ] )
    {
        theFlowControl = myFlowControl;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetOpFlowControl(CT_TEL_MAC_FLOWCTRL& theOpFlowControl) const
{
    if( true == myBitSet[ INDEX_OpFlowControl ] )
    {
        theOpFlowControl = myOpFlowControl;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetAutonegStatus(CT_TEL_MAC_AUTONEGSTATUS& theAutonegStatus) const
{
    if( true == myBitSet[ INDEX_AutonegStatus ] )
    {
        theAutonegStatus = myAutonegStatus;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetAutonegRmtSgl(bool& theAutonegRmtSgl) const
{
    if( true == myBitSet[ INDEX_AutonegRmtSgl ] )
    {
        theAutonegRmtSgl = myAutonegRmtSgl;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetAdvFlowCtrl(CT_TEL_MAC_ADFLW_CTRL& theAdvFlowCtrl) const
{
    if( true == myBitSet[ INDEX_AdvFlowCtrl ] )
    {
        theAdvFlowCtrl = myAdvFlowCtrl;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetOpAutoneg(bool& theOpAutoneg) const
{
    if( true == myBitSet[ INDEX_OpAutoneg ] )
    {
        theOpAutoneg = myOpAutoneg;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetPST( CT_SM_PST& thePST ) const
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        thePST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        thePSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetSST( CT_SM_SST& theSST ) const
{
    if( true == myBitSet[ INDEX_SST ] )
    {
        theSST = mySST;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetActRate( CT_TEL_daHz& theActualRate ) const
{
    if( true == myBitSet[ INDEX_ActualRate ] )
    {
        theActualRate = myActRate;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetLineCode( CT_FAC_LineCode& theLineCode ) const
{
    if( true == myBitSet[ INDEX_LineCode ] )
    {
        theLineCode = myLineCode;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetFrameFormat( CT_FAC_FrameFormat& theFrameFormat ) const
{
    if( true == myBitSet[ INDEX_FrameFormat ] )
    {
        theFrameFormat = myFrameFormat;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetSaBit( CT_FAC_SaBit& theSaBit ) const
{
    if( true == myBitSet[ INDEX_SaBit ] )
    {
        theSaBit = mySaBit;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetQualityLevelOverride( CT_FAC_QualityLevelOverride& theQualityLevelOverride ) const
{
    if( true == myBitSet[ INDEX_QualityLevelOverride] )
    {
        theQualityLevelOverride = myQualityLevelOverride;
        return true;
    }
    else
    {
        return false;
    }
}

bool
TL1_FACRspBlk::GetGfpMapping( CT_TEL_GfpFramingMode& theGfpMapping ) const
{
    if( true == myBitSet[ INDEX_GfpMapping ] )
    {
        theGfpMapping = myGfpMapping;
        return true;
    }
    else
    {
        return false;
    }
}

bool
TL1_FACRspBlk::GetGenTrc( bool& theGenTrc ) const
{
    if ( true == myBitSet[ INDEX_GenTrc ] )
    {
        theGenTrc = myGenTrc;
        return true;
    }
    else
    { 
        return false;
    }
}

bool
TL1_FACRspBlk::GetLOSThreshold( CT_TEL_mBm& theLOSThreshold ) const
{
    if ( true == myBitSet[ INDEX_LOSThreshold ] )
    {
        theLOSThreshold = myLOSThreshold;
        return true;
    }
    else
    { 
        return false;
    }
}

bool
TL1_FACRspBlk::GetSWThreshold( CT_TEL_mBm& theSWThreshold ) const
{
    if ( true == myBitSet[ INDEX_SWThreshold ] )
    {
        theSWThreshold = mySWThreshold;
        return true;
    }
    else
    { 
        return false;
    }
}

bool
TL1_FACRspBlk::GetSignalBand( CT_TEL_OpticalWaveLength& theSignalBand ) const
{
    if ( true == myBitSet[ INDEX_SignalBand ] )
    {
        theSignalBand = mySignalBand;
        return true;
    }
    else
    { 
        return false;
    }
}

bool
TL1_FACRspBlk::GetNendALS( bool& theNendALS ) const
{
    if ( true == myBitSet[ INDEX_NendALS ] )
    {
        theNendALS = myNendALS;
        return true;
    }
    else
    {
        return false;
    }
}

bool
TL1_FACRspBlk::GetNValue( CT_FAC_NValue& theNValue ) const
{
    if ( true == myBitSet[ INDEX_NValue ] )
    {
        theNValue = myNValue;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetFecType( CT_TEL_FecType& theFecType ) const
{
    if ( true == myBitSet[ INDEX_FecType ] )
    {
        theFecType = myFecType;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetTransMap( CT_TEL_SignalType& theTransMap ) const
{
    if ( true == myBitSet[ INDEX_TransMap ] )
    {
        theTransMap = myTransMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetClkType( CT_TEL_SignalType& theClkType ) const
{
    if ( true == myBitSet[ INDEX_ClkType ] )
    {
        theClkType = myClkType;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetTapNumber( CT_TapNumber& theTapNumber ) const
{
    if ( true == myBitSet[ INDEX_TapNumber ] )
    {
        theTapNumber = myTapNumber;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetAutoNegotiationEnabled( bool& theAutoNegotiation ) const     
{
   if ( true == myBitSet[ INDEX_AutoNegotiation ] )
   {
      theAutoNegotiation = myAutoNegotiationEnabled;
      return true;
   }
   else
   {
      return false;
   }
}

bool
TL1_FACRspBlk::GetOtuExpTrc( CT_Fac_TraceString& theOtuExpTrc ) const
{
    if ( true == myBitSet[ INDEX_OtuExpTrc ] )
    {
        theOtuExpTrc = myOtuExpTrc;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetOtuTrc( CT_Fac_TraceString& theOtuTrc ) const
{
    if ( true == myBitSet[ INDEX_OtuTrc ] )
    {
        theOtuTrc = myOtuTrc;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetOtuMonTrc( bool& theOtuMonTrc ) const     
{
    if ( true == myBitSet[ INDEX_OtuMonTrc ] )
    {
        theOtuMonTrc = myOtuMonTrc;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetOtuIncTrc( CT_Fac_TraceString& theOtuIncTrc ) const
{
    if ( true == myBitSet[ INDEX_OtuIncTrc ] )
    {
        theOtuIncTrc = myOtuIncTrc;
        return true;
    }
    else
    {
        return false;
    }
}

bool
TL1_FACRspBlk::GetOeoRegen( CT_TEL_OEO_REGEN_MODE& theOeoRegen ) const
{
    if ( true == myBitSet[ INDEX_OeoRegen ] )
    {
        theOeoRegen = myOeoRegen;
        return true;
    }
    else
    {
        return false;
    }
}

bool
TL1_FACRspBlk::GetCnvType( CT_TEL_TermSize& theCnvType ) const
{
    if ( true == myBitSet[ INDEX_CnvType ] )
    {
        theCnvType = myCnvType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetPt(CT_TEL_PayloadSignalId& thePt ) const
{
    if( true == myBitSet[ INDEX_Pt ] )
    {
        thePt = myPt;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetPtRx(CT_TEL_PayloadSignalId& thePtRx ) const
{
    if( true == myBitSet[ INDEX_PtRx ] )
    {
        thePtRx = myPtRx;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetGfpUpi(CT_TEL_GfpUpiId& theUpi ) const
{
    if( true == myBitSet[ INDEX_GfpUpi ] )
    {
        theUpi = myGfpUpi;
        return true;
    }
    else
    {
        return false;
    }
}


bool
TL1_FACRspBlk::GetDiscardPause( bool& theDiscardPause ) const
{
    if ( true == myBitSet[ INDEX_DiscardPause ] )
    {
        theDiscardPause = myDiscardPause;
        return true;
    }
    else
    {
        return false;
    }
}

bool
TL1_FACRspBlk::GetPropFefi( bool& thePropFefi ) const
{
    if ( true == myBitSet[ INDEX_PropFefi ] )
    {
        thePropFefi = myPropFefi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetAddCstMap( CT_FAC_StsMap& theAddCstMap ) const
{    
    if( true == myBitSet[ INDEX_AddCstMap ] )
    {
        theAddCstMap = myAddCstMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetDelCstMap( CT_FAC_StsMap& theDelCstMap ) const
{    
    if( true == myBitSet[ INDEX_DelCstMap ] )
    {
        theDelCstMap = myDelCstMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetAutoCfg( bool& theAutoCfg ) const
{
    if( true == myBitSet[ INDEX_AutoCfg ] )
    {
        theAutoCfg = myAutoCfg;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetVcgName(string& theVcgName ) const
{
    if( true == myBitSet[ INDEX_VcgName ] )
    {
        theVcgName = myVcgName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetVcgAddr(CT_TL1_FacAddr& theVcgAddr ) const
{
    if( true == myBitSet[ INDEX_VcgAddr ] )
    {
        theVcgAddr = myVcgAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetVlanTag(CT_TEL_VlanTag& theVTag ) const
{
    if( true == myBitSet[ INDEX_VlanTag ] )
    {
        theVTag = myVlanTag;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetTagMode(bool& theTagMode ) const
{
    if( true == myBitSet[ INDEX_TagMode ] )
    {
        theTagMode = myTagMode;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_FACRspBlk::GetTpid(CT_TEL_Tpid& theTpid ) const
{
    if( true == myBitSet[ INDEX_Tpid ] )
    {
        theTpid = myTpid;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetPMProfile( CT_PMProfileTableId& thePmProfile ) const
{
    if( true == myBitSet[ INDEX_PmProfile ] )
    {
        thePmProfile = myPmProfile;
        return true;
    }
    else
    {
        return false;
    }
}   
    
bool TL1_FACRspBlk::GetCFProfile( int& theCFProfile ) const
{
    if( true == myBitSet[ INDEX_CFProfile ] )
    {
        theCFProfile = myCFProfile;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetCbrMap( CT_TEL_PayloadType& theCbrMap ) const
{
    if( true == myBitSet[ INDEX_CbrMap ] )
    {
        theCbrMap = myCbrMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetGfpMux(CT_TEL_GFP_MUX & theGfpMux) const
{
    if( true == myBitSet[ INDEX_GfpMux ])
    {
        theGfpMux = myGfpMux;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetOpuFmt( CT_TEL_OPU_FORMAT& theOpuFmt) const
{
    if( true == myBitSet[ INDEX_Opu ])
    {
        theOpuFmt = myOpuFmt;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetOpTribSize(CT_TEL_TS_SIZE& theOpTribSize) const
{
    if( true == myBitSet[ INDEX_OpTribSize ])
    {
        theOpTribSize = myOpTribSize;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetTribSize(CT_TEL_TS_SIZE& theTribSize) const
{
    if( true == myBitSet[ INDEX_TribSize ])
    {
        theTribSize = myTribSize;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetOpadjacent(CT_TL1_FacParamAddr & theOpadjacent) const
{
    if( true == myBitSet[ INDEX_Opadjacent ])
    {
        theOpadjacent = myOpadjacent;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetTimDef(CT_TEL_TimCriteriaMode & theTimDef) const
{
    if( true == myBitSet[ INDEX_TimDef ])
    {
        theTimDef = myTimDefMode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetExpDapi(CT_Fac_TraceString & theExpDapi) const
{
    if(true == myBitSet[ INDEX_ExpDapi])
    {
        theExpDapi = myExpDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetExpSapi(CT_Fac_TraceString & theExpSapi) const
{
    if(true == myBitSet[ INDEX_ExpSapi ])
    {
        theExpSapi = myExpSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetTxDapi(CT_Fac_TraceString & theTxDapi) const
{
    if(true == myBitSet[ INDEX_TxDapi ])
    {
        theTxDapi = myTxDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetTxSapi(CT_Fac_TraceString & theTxSapi) const
{
    if(true == myBitSet[ INDEX_TxSapi ])
    {
        theTxSapi = myTxSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetLacpPartiMode(CT_TEL_LacpPartiMode& theMode) const
{
    if( true == myBitSet[ INDEX_LacpPartiMode ] )
    {
        theMode = myLacpPartiMode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetLacpPriority(int& thePriority) const
{
    if( true == myBitSet[ INDEX_LacpPriority ] )
    {
        thePriority = myLacpPriority;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetAisType(CT_RS_IndicationType& theAisType) const
{
    if( true == myBitSet[ INDEX_AisType ] )
    {
        theAisType = myAisType;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_FACRspBlk::GetQualityLevel( CT_FAC_QualityLevelOverride& theQualityLevel) const
{
    if( true == myBitSet[ INDEX_QualityLevel] )
    {
        theQualityLevel= myQualityLevel;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetOpuConfig(CT_TEL_OPU_FORMAT& theOpuConfig) const
{
    if (true == myBitSet[ INDEX_OpuConfig ])
    {
        theOpuConfig = myOpuConfig;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetOTNMap(bool &theOTNMap) const
{
    if ( true == myBitSet[ INDEX_OTNMap ] )
    {
        theOTNMap = myOTNMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetHgeMap(CT_TEL_Map_ENUM &theHgeMap) const
{
    if ( true == myBitSet[ INDEX_HGEMAP ] )
    {
        theHgeMap = myHgeMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetMapMode(CT_TEL_PayloadType &theMapMode) const
{
    if ( true == myBitSet[ INDEX_MAPMODE] )
    {
        theMapMode = myMapMode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FACRspBlk::GetMacAddr(string &theMacAddr) const
{
	if( true == myBitSet[ INDEX_MACADDR] )
	{
		theMacAddr = myMacAddr;
	    return true;
	}
	else
	{
		return false;
	}

}

bool TL1_FACRspBlk::GetPluggableReach(CT_FAC_PluggableReach &thePluggableReach) const
{
	if( true == myBitSet[ INDEX_PluggableReach] )
	{
		thePluggableReach = myPluggableReach;
	    return true;
	}
	else
	{
		return false;
	}

}

//--------------------------Set Fields----------------------------------------

void 
TL1_FACRspBlk::SetTribSlot( const CT_FAC_OduTsMap& theTribSlot )
{
    myBitSet[ INDEX_TribSlot] = true;
    myTribSlot = theTribSlot;
}
void 
TL1_FACRspBlk::SetTribFall( const bool& theTribFall )
{
    myBitSet[ INDEX_TribFall] = true;
    myTribFall = theTribFall;
}
void 
TL1_FACRspBlk::SetDmSource( const bool& theDmSource )
{
    myBitSet[ INDEX_DmSource] = true;
    myDmSource = theDmSource;
}

void 
TL1_FACRspBlk::SetLtcActMode( const bool& theLtcActMode )
{
    myBitSet[ INDEX_LtcActMode] = true;
    myLtcActMode= theLtcActMode;
}
void 
TL1_FACRspBlk::SetGfpTs( const uint8& theGfpTs )
{
    myBitSet[ INDEX_GfpTs] = true;
    myGfpTs = theGfpTs;
}
void 
TL1_FACRspBlk::SetInterPacketGap( const uint8& theInterPacketGap )
{
    myBitSet[ INDEX_InterPacketGap] = true;
    myInterPacketGap = theInterPacketGap;
}
void 
TL1_FACRspBlk::SetConnected1( const CT_TL1_FacParamAddr& theConnected1 )
{
    myBitSet[ INDEX_Connected1] = true;
    myConnected1 = theConnected1;
}
void 
TL1_FACRspBlk::SetConnected2( const CT_TL1_FacParamAddr& theConnected2 )
{
    myBitSet[ INDEX_Connected2] = true;
    myConnected2 = theConnected2;
}

void 
TL1_FACRspBlk::SetChannel( const uint32& theChannel )
{
    myBitSet[ INDEX_Channel] = true;
    myChannel = theChannel;
}

void 
TL1_FACRspBlk::SetConnectedTo( const CT_Fac_ConnectedToString& theConnectedTo )  
{
    myBitSet[ INDEX_ConnectedTo ] = true;
    myConnectedTo = theConnectedTo;
}
void 
TL1_FACRspBlk::SetTransparent( const bool& theTransparent )  
{
    myBitSet[ INDEX_Transparent ] = true;
    myTransparent = theTransparent;
}

void 
TL1_FACRspBlk::SetSsmSupported(const bool& theSsmSupported )  
{
    myBitSet[ INDEX_SsmSupported ] = true;
    mySsmSupported = theSsmSupported;
}

void 
TL1_FACRspBlk::SetSsmReceived( const CT_FAC_RxSsm& theSsmReceived )  
{
    myBitSet[ INDEX_SsmReceived ] = true; 
    mySsmReceived = theSsmReceived;
}

void 
TL1_FACRspBlk::SetTimingRef( const CT_TEL_MsTref& theTimingReference )  
{
    myBitSet[ INDEX_TimingReference ] = true; 
    myTimingReference = theTimingReference;
}

void TL1_FACRspBlk::SetEntityName(const string& theEntityName )  
{
    myBitSet[ INDEX_EntityName ] = true; 
    myEntityName = theEntityName;
}

void TL1_FACRspBlk::SetFacAddr(const CT_TL1_FacAddr& theFacAddr )  
{
    myBitSet[ INDEX_FacAddr ] = true; 
    myFacAddr = theFacAddr;
}

void TL1_FACRspBlk::SetCardType(const CT_CardType& theCardType )  
{
    myBitSet[ INDEX_CardType ] = true; 
    myCardType = theCardType;
}

void TL1_FACRspBlk::SetSubCardType(const CT_SubCardType& theSubCardType )  
{
    myBitSet[ INDEX_SubCardType ] = true; 
    mySubCardType = theSubCardType;
}

void TL1_FACRspBlk::SetAdaptive( const bool& theAdaptive )  
{
    myBitSet[ INDEX_Adaptive ] = true; 
    myAdaptive = theAdaptive;
}

void TL1_FACRspBlk::SetMaxRate( const CT_TEL_daHz& theMaxRate )  
{    
    myBitSet[ INDEX_MaxRate ] = true; 
    myMaxRate = theMaxRate;
}

void TL1_FACRspBlk::SetRateList( const CT_FAC_SignalRateListType& theRateList )  
{    
    myBitSet[ INDEX_RateList ] = true; 
    myRateList = theRateList;
}

void TL1_FACRspBlk::SetExpectedSignalRate( CT_TEL_daHz& theExpectedSignalRate )  
{    
    myBitSet[ INDEX_ExpectedSignalRate ] = true;
    myExpectedSignalRate = theExpectedSignalRate;
}

void TL1_FACRspBlk::SetExpectedRateRange( CT_TL1_ExpectedRateRange& theExpRateRange)  
{    
    myBitSet[ INDEX_ExpectedSignalRateRange ] = true; 
    myExpectedSignalRateRange.begin = theExpRateRange.begin;
    myExpectedSignalRateRange.end = theExpRateRange.end;

}
             

void TL1_FACRspBlk::SetSignalType( const CT_TEL_SignalType& theSignalType )  
{    
    myBitSet[ INDEX_SignalType ] = true;
    mySignalType = theSignalType;
}

void TL1_FACRspBlk::SetStsMap( const CT_FAC_StsMap& theStsMap )  
{    
    myBitSet[ INDEX_StsMap ] = true; 
    myStsMap = theStsMap;
}

void TL1_FACRspBlk::SetStsCstMap( const CT_FAC_StsMap& theStsCstMap )  
{    
    myBitSet[ INDEX_StsCstMap ] = true; 
    myStsCstMap = theStsCstMap;
}

void TL1_FACRspBlk::SetAddCrsMap( const CT_FAC_StsMap& theAddCrsMap )  
{    
    myBitSet[ INDEX_AddCrsMap ] = true; 
    myAddCrsMap = theAddCrsMap;
}

void TL1_FACRspBlk::SetDelCrsMap( const CT_FAC_StsMap& theDelCrsMap )  
{    
    myBitSet[ INDEX_DelCrsMap ] = true; 
    myDelCrsMap = theDelCrsMap;
}

void TL1_FACRspBlk::SetTrace( const CT_Fac_TraceString& theTrace )  
{    
    myBitSet[ INDEX_Trace ] = true; 
    myTrace = theTrace;
}

void TL1_FACRspBlk::SetExpectedTrace( const CT_Fac_TraceString& ExpectedTrace )  
{
    myBitSet[ INDEX_ExpectedTrace ] = true;
    myExpectedTrace = ExpectedTrace;
}

void TL1_FACRspBlk::SetIncomingTrace( const CT_Fac_TraceString& theIncomingTrace )  
{
    myBitSet[ INDEX_IncomingTrace ] = true; 
    myIncomingTrace = theIncomingTrace;
}

void TL1_FACRspBlk::SetMonitorTraceEnabled(const bool& theMonitorTraceEnabled )  
{
    myBitSet[ INDEX_MonitorTraceEnabled ] = true; 
    myMonitorTraceEnabled = theMonitorTraceEnabled;
}

void TL1_FACRspBlk::SetInsertAisEnabled(const bool& theInsertAisEnabled )  
{
    myBitSet[ INDEX_InsertAisEnabled ] = true; 
    myInsertAisEnabled = theInsertAisEnabled;
}

void TL1_FACRspBlk::SetProtectionEnabled( const CT_FAC_Protection& theProtectionEnabled )  
{
    myBitSet[ INDEX_ProtectionEnabled ] = true;
    myProtectionEnabled = theProtectionEnabled;
}

void TL1_FACRspBlk::SetMaintPropagate( const CT_FAC_MaintProp& theMaintProp )  
{
    myBitSet[ INDEX_MaintPropagate ] = true;
    myMaintProp = theMaintProp;
}

void TL1_FACRspBlk::SetAlarmProfile( CT_ProfileTableId& theAlarmProfile )  
{
    myBitSet[ INDEX_AlarmProfile ]  = true;
    myAlarmProfile = theAlarmProfile;
}

void TL1_FACRspBlk::SetMapping( CT_TEL_HopSpeMapping& theMapping )  
{
    myBitSet[ INDEX_Mapping ] = true; 
    myMapping = theMapping;
}

void TL1_FACRspBlk::SetExternalConectivity( const CT_FAC_ExternalConnectivity& theExternalConectivity )  
{
    myBitSet[ INDEX_ExternalConectivity ] = true;
    myExternalConectivity = theExternalConectivity;
}

void TL1_FACRspBlk::SetSFThreshold( const CT_TEL_BERLevels& theSFThreshold )  
{
    myBitSet[ INDEX_SFThreshold ] = true; 
    mySFThreshold = theSFThreshold;
}

void TL1_FACRspBlk::SetSDThreshold( const CT_TEL_BERLevels& theSDThreshold )  
{
    myBitSet[ INDEX_SDThreshold ] = true; 
    mySDThreshold = theSDThreshold;
}

void TL1_FACRspBlk::SetBurstyBerSdInterval( const uint16& theBurstyBerSdInterval )  
{
    myBitSet[ INDEX_BurstyBerSdInterval ] = true; 
    myBurstyBerSdInterval = theBurstyBerSdInterval;
}

void TL1_FACRspBlk::SetBurstyBerSdThreshold( const uint32& theBurstyBerSdThreshold )  
{
    myBitSet[ INDEX_BurstyBerSdThreshold ] = true; 
    myBurstyBerSdThreshold = theBurstyBerSdThreshold;
}

void TL1_FACRspBlk::SetNpOwner( const int& theNpOwner )
{
    myBitSet[ INDEX_NpOwner ] = true;
    myNpOwner = theNpOwner;
}

void TL1_FACRspBlk::SetQuarantine( const bool& theQuarantine ) 
{
    myBitSet[ INDEX_Quarantine ] = true;
    myQuarantine = theQuarantine;
}

void TL1_FACRspBlk::SetEthRate(const CT_TEL_daHz& theEthRate) 
{
    myBitSet[ INDEX_EthRate ] = true;
    myEthRate = theEthRate;
}
void TL1_FACRspBlk::SetOpEthRate(const CT_TEL_daHz& theOpEthRate)
{
    myBitSet[ INDEX_OpEthRate ] = true;
    myOpEthRate = theOpEthRate;
}
void TL1_FACRspBlk::SetDuplexMode(const CT_TEL_MAC_DUPLEX_MODE& theDuplexMode)
{
    myBitSet[ INDEX_DuplexMode ] = true;
    myDuplexMode = theDuplexMode;
}
void TL1_FACRspBlk::SetOpDuplexMode(const CT_TEL_MAC_DUPLEX_MODE& theOpDuplexMode)
{
    myBitSet[ INDEX_OpDuplexMode ] = true;
    myOpDuplexMode = theOpDuplexMode;
}
void TL1_FACRspBlk::SetTcmMode(const CT_TCM_Mode& theTcmMode )
{
    myBitSet[ INDEX_TcmMode ] = true;
    myTcmMode = theTcmMode;
}
void TL1_FACRspBlk::SetFlowControl(const CT_TEL_MAC_FLOWCTRL& theFlowControl)
{
    myBitSet[ INDEX_FlowControl ] = true;
    myFlowControl = theFlowControl;
}
void TL1_FACRspBlk::SetOpFlowControl(const CT_TEL_MAC_FLOWCTRL& theOpFlowControl)
{
    myBitSet[ INDEX_OpFlowControl ] = true;
    myOpFlowControl = theOpFlowControl;
}
void TL1_FACRspBlk::SetAutonegStatus(const CT_TEL_MAC_AUTONEGSTATUS& theAutonegStatus)
{
    myBitSet[ INDEX_AutonegStatus ] = true;
    myAutonegStatus = theAutonegStatus;
}
void TL1_FACRspBlk::SetAutonegRmtSgl(const bool& theAutonegRmtSgl)
{
    myBitSet[ INDEX_AutonegRmtSgl ] = true;
    myAutonegRmtSgl = theAutonegRmtSgl;
}
void TL1_FACRspBlk::SetAdvFlowCtrl(const CT_TEL_MAC_ADFLW_CTRL& theAdvFlowCtrl)
{
    myBitSet[ INDEX_AdvFlowCtrl ] = true;
    myAdvFlowCtrl = theAdvFlowCtrl;
}
void TL1_FACRspBlk::SetOpAutoneg(const bool& theOpAutoneg)
{
    myBitSet[ INDEX_OpAutoneg ] = true;
    myOpAutoneg = theOpAutoneg;
}

void TL1_FACRspBlk::SetPST( CT_SM_PST& thePST )  
{
    myBitSet[ INDEX_PST ] = true; 
    myPST = thePST;
}

void TL1_FACRspBlk::SetPSTQ( const CT_SM_PSTQ& thePSTQ )  
{
    myBitSet[ INDEX_PSTQ ] = true; 
    myPSTQ = thePSTQ;
}

void TL1_FACRspBlk::SetSST( CT_SM_SST& theSST )  
{
    myBitSet[ INDEX_SST ] = true; 
    mySST = theSST;
}

void 
TL1_FACRspBlk::SetActRate( const CT_TEL_daHz& theActualRate )  
{
    myBitSet[ INDEX_ActualRate ] = true; 
    myActRate = theActualRate;
}

void 
TL1_FACRspBlk::SetLineCode( const CT_FAC_LineCode& theLineCode )  
{
    myBitSet[ INDEX_LineCode ] = true; 
    myLineCode = theLineCode;
}

void 
TL1_FACRspBlk::SetFrameFormat( const CT_FAC_FrameFormat& theFrameFormat )  
{
    myBitSet[ INDEX_FrameFormat ] = true; 
    myFrameFormat = theFrameFormat;
}

void 
TL1_FACRspBlk::SetSaBit( const CT_FAC_SaBit& theSaBit )  
{
    myBitSet[ INDEX_SaBit ] = true; 
    mySaBit = theSaBit;
}

void 
TL1_FACRspBlk::SetQualityLevelOverride( const CT_FAC_QualityLevelOverride& theQualityLevelOverride )  
{
    myBitSet[ INDEX_QualityLevelOverride] = true; 
    myQualityLevelOverride = theQualityLevelOverride;
}

void
TL1_FACRspBlk::SetGfpMapping( const CT_TEL_GfpFramingMode& theGfpMapping )  
{
    myBitSet[ INDEX_GfpMapping ] = true;
    myGfpMapping = theGfpMapping;
}

void
TL1_FACRspBlk::SetGenTrc( const bool& theGenTrc )  
{
    myBitSet[ INDEX_GenTrc ] = true; 
    myGenTrc = theGenTrc;
}

void
TL1_FACRspBlk::SetLOSThreshold(const CT_TEL_mBm& theLOSThreshold )  
{
    myBitSet[ INDEX_LOSThreshold ] = true; 
    myLOSThreshold = theLOSThreshold;
}

void
TL1_FACRspBlk::SetSWThreshold( const CT_TEL_mBm& theSWThreshold )  
{
    myBitSet[ INDEX_SWThreshold ] = true; 
    mySWThreshold = theSWThreshold;
}

void
TL1_FACRspBlk::SetSignalBand( const CT_TEL_OpticalWaveLength& theSignalBand )  
{
    myBitSet[ INDEX_SignalBand ] = true; 
    mySignalBand = theSignalBand;
}

void
TL1_FACRspBlk::SetNendALS( const bool& theNendALS )  
{
    myBitSet[ INDEX_NendALS ] = true; 
    myNendALS = theNendALS;
}

void
TL1_FACRspBlk::SetNValue( const CT_FAC_NValue& theNValue )  
{
    myBitSet[ INDEX_NValue ] = true; 
    myNValue = theNValue;
}

void 
TL1_FACRspBlk::SetFecType( const CT_TEL_FecType& theFecType )  
{
    myBitSet[ INDEX_FecType ] = true; 
    myFecType = theFecType;
}

void 
TL1_FACRspBlk::SetTransMap( const CT_TEL_SignalType& theTransMap )  
{
    myBitSet[ INDEX_TransMap ] = true; 
    myTransMap = theTransMap;
}

void 
TL1_FACRspBlk::SetClkType( const CT_TEL_SignalType& theClkType)  
{
    myBitSet[ INDEX_ClkType ] = true; 
    myClkType = theClkType;
}

void 
TL1_FACRspBlk::SetTapNumber( const CT_TapNumber& theTapNumber)  
{
    myBitSet[ INDEX_TapNumber ] = true; 
    myTapNumber = theTapNumber;
}

void 
TL1_FACRspBlk::SetAutoNegotiationEnabled( const bool& theAutoNegotiation )       
{
    myBitSet[ INDEX_AutoNegotiation ] = true; 
    myAutoNegotiationEnabled = theAutoNegotiation;
}

void
TL1_FACRspBlk::SetDiscardPause( const bool& theDiscardPause )  
{
    myBitSet[ INDEX_DiscardPause ] = true; 
    myDiscardPause = theDiscardPause;
}

void
TL1_FACRspBlk::SetPropFefi( const bool& thePropFefi )  
{
    myBitSet[ INDEX_PropFefi ] = true; 
    myPropFefi = thePropFefi;
}

void 
TL1_FACRspBlk::SetOtuExpTrc( const CT_Fac_TraceString& theOtuExpTrc )  
{
    myBitSet[ INDEX_OtuExpTrc ] = true; 
    myOtuExpTrc = theOtuExpTrc;
}

void 
TL1_FACRspBlk::SetOtuTrc( const CT_Fac_TraceString& theOtuTrc )  
{
    myBitSet[ INDEX_OtuTrc ] = true; 
    myOtuTrc = theOtuTrc;
}

void 
TL1_FACRspBlk::SetOtuMonTrc( const bool& theOtuMonTrc )       
{
    myBitSet[ INDEX_OtuMonTrc ] = true; 
    myOtuMonTrc = theOtuMonTrc;
}

void 
TL1_FACRspBlk::SetOtuIncTrc( const CT_Fac_TraceString& theOtuIncTrc )  
{
    myBitSet[ INDEX_OtuIncTrc ] = true; 
    myOtuIncTrc = theOtuIncTrc;
}

void 
TL1_FACRspBlk::SetOeoRegen( const CT_TEL_OEO_REGEN_MODE& theOeoRegen )
{
    myBitSet[ INDEX_OeoRegen ] = true;
    myOeoRegen = theOeoRegen;
}

void 
TL1_FACRspBlk::SetCnvType( const CT_TEL_TermSize&  theCnvType )
{
    myBitSet[ INDEX_CnvType ] = true;
    myCnvType = theCnvType;
}

void TL1_FACRspBlk::SetPt(const CT_TEL_PayloadSignalId& thePt )  
{
    myBitSet[ INDEX_Pt ] = true; 
    myPt = thePt;
}

void TL1_FACRspBlk::SetPtRx(const CT_TEL_PayloadSignalId& thePtRx )  
{
    myBitSet[ INDEX_PtRx ] = true; 
    myPtRx = thePtRx;
}

void TL1_FACRspBlk::SetGfpUpi(const CT_TEL_GfpUpiId& theUpi )  
{
    myBitSet[ INDEX_GfpUpi ] = true; 
    myGfpUpi = theUpi;
}

void TL1_FACRspBlk::SetAddCstMap( const CT_FAC_StsMap& theAddCstMap )  
{    
    myBitSet[ INDEX_AddCstMap ] = true; 
    myAddCstMap = theAddCstMap;
}

void TL1_FACRspBlk::SetDelCstMap( const CT_FAC_StsMap& theDelCstMap )  
{    
    myBitSet[ INDEX_DelCstMap ] = true; 
    myDelCstMap = theDelCstMap;
}

void TL1_FACRspBlk::SetAutoCfg( const bool& theAutoCfg )
{
    myBitSet[ INDEX_AutoCfg ] = true;
    myAutoCfg = theAutoCfg;
}

void TL1_FACRspBlk::SetVcgName(const string& theVcgName )  
{
    myBitSet[ INDEX_VcgName ] = true; 
    myVcgName = theVcgName;
}

void TL1_FACRspBlk::SetVcgAddr(const CT_TL1_FacAddr& theVcgAddr )  
{
    myBitSet[ INDEX_VcgAddr ] = true; 
    myVcgAddr = theVcgAddr;
}

void TL1_FACRspBlk::SetVlanTag(const CT_TEL_VlanTag& theVTag )  
{
    myBitSet[ INDEX_VlanTag ] = true; 
    myVlanTag = theVTag;
}
void TL1_FACRspBlk::SetTagMode(const bool& theTagMode )  
{
    myBitSet[ INDEX_TagMode ] = true; 
    myTagMode = theTagMode;
}
void TL1_FACRspBlk::SetTpid(const CT_TEL_Tpid& theTpid )  
{
    myBitSet[ INDEX_Tpid ] = true; 
    myTpid = theTpid;
}
void TL1_FACRspBlk::SetPMProfile( const CT_PMProfileTableId& thePmProfile )  
{
    myBitSet[ INDEX_PmProfile ]  = true;
    myPmProfile = thePmProfile;
}
void TL1_FACRspBlk::SetCbrMap(const CT_TEL_PayloadType& theCbrMap )  
{
    myBitSet[ INDEX_CbrMap ]  = true;
    myCbrMap = theCbrMap;
}
void TL1_FACRspBlk::SetGfpMux(const CT_TEL_GFP_MUX& theGfpMux )  
{
    myBitSet[ INDEX_GfpMux ]  = true;
    myGfpMux = theGfpMux;
}
void TL1_FACRspBlk::SetOpuFmt(const CT_TEL_OPU_FORMAT& theOpuFmt )  
{
    myBitSet[ INDEX_Opu ]  = true;
    myOpuFmt = theOpuFmt;
}
void TL1_FACRspBlk::SetOpTribSize(const CT_TEL_TS_SIZE& theOpTribSize )  
{
    myBitSet[ INDEX_OpTribSize ]  = true;
    myOpTribSize = theOpTribSize;
}
void TL1_FACRspBlk::SetTribSize(const CT_TEL_TS_SIZE& theTribSize )  
{
    myBitSet[ INDEX_TribSize ]  = true;
    myTribSize = theTribSize;
}
void TL1_FACRspBlk::SetOpadjacent(const CT_TL1_FacParamAddr& theOpadjacent )  
{
    myBitSet[ INDEX_Opadjacent ]  = true;
    myOpadjacent = theOpadjacent;
}

void TL1_FACRspBlk::SetCFProfile( int& theCFProfile )  
{
    myBitSet[ INDEX_CFProfile ]  = true;
    myCFProfile = theCFProfile;
}

void TL1_FACRspBlk::SetTimDef(const CT_TEL_TimCriteriaMode & theTimDef)
{
    myBitSet[ INDEX_TimDef ] = true;
    myTimDefMode = theTimDef;
}
void TL1_FACRspBlk::SetExpDapi(const CT_Fac_TraceString & theExpDapi)
{
    myBitSet[ INDEX_ExpDapi ] = true;
    myExpDapi = theExpDapi;
}
void TL1_FACRspBlk::SetExpSapi(const CT_Fac_TraceString & theExpSapi)
{
    myBitSet[ INDEX_ExpSapi ] = true;
    myExpSapi = theExpSapi;
}
void TL1_FACRspBlk::SetTxDapi(const CT_Fac_TraceString & theTxDapi)
{
    myBitSet[ INDEX_TxDapi ] = true;
    myTxDapi = theTxDapi;
}
void TL1_FACRspBlk::SetTxSapi(const CT_Fac_TraceString & theTxSapi)
{
    myBitSet[ INDEX_TxSapi ] = true;
    myTxSapi = theTxSapi;
}
void TL1_FACRspBlk::SetMemberAddr( const CT_TL1_FacAddr& theMemberAddr ) 
{
    myBitSet[ INDEX_MemberAddr ]  = true;
    myMemberAddr = theMemberAddr;
}

void TL1_FACRspBlk::SetLacpPartiMode(CT_TEL_LacpPartiMode theMode)
{
    myBitSet[ INDEX_LacpPartiMode ]  = true;
    myLacpPartiMode = theMode;
}

void TL1_FACRspBlk::SetLacpPriority(int thePriority)
{
    myBitSet[ INDEX_LacpPriority ]  = true;
    myLacpPriority = thePriority;
}

void TL1_FACRspBlk::SetAisType(CT_RS_IndicationType theAisType)
{
    myBitSet[ INDEX_AisType ]  = true;
    myAisType = theAisType;
}

void TL1_FACRspBlk::SetQualityLevel(const CT_FAC_QualityLevelOverride& theQualityLevel)  
{
    myBitSet[ INDEX_QualityLevel] = true; 
    myQualityLevel= theQualityLevel;
}

void 
TL1_FACRspBlk::SetOpuConfig( const CT_TEL_OPU_FORMAT& theOpuConfig )
{
    myBitSet[ INDEX_OpuConfig] = true;
    myOpuConfig = theOpuConfig;
}

void 
TL1_FACRspBlk::SetOTNMap(const bool &theOTNMap)
{
    myBitSet[ INDEX_OTNMap] = true;
    myOTNMap= theOTNMap;
}

void 
TL1_FACRspBlk::SetHgeMap(const CT_TEL_Map_ENUM& theHgeMap)
{
    myBitSet[ INDEX_HGEMAP] = true;
    myHgeMap= theHgeMap;
}

void 
TL1_FACRspBlk::SetMapMode(const CT_TEL_PayloadType &theMapMode)
{
    myBitSet[ INDEX_MAPMODE] = true;
    myMapMode= theMapMode;
}

void 
TL1_FACRspBlk::SetMacAddr(const string & theMacAddr)
{
	myBitSet[ INDEX_MACADDR] = true; 
	myMacAddr = theMacAddr;
}

void 
TL1_FACRspBlk::SetPluggableReach(const CT_FAC_PluggableReach & thePluggableReach)
{
	myBitSet[ INDEX_PluggableReach] = true; 
	myPluggableReach = thePluggableReach;
}