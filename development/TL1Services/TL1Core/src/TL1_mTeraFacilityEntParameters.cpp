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

#include <TL1Core/TL1_mTeraFacilityEntParameters.h>
#include <TL1Facility/T7100_TL1FacilityEntity.h>
#include <TL1Core/T7100_TL1AgentUtility.h>

TL1_mTeraFacilityEntParameters::TL1_mTeraFacilityEntParameters():
TL1_FacilityEntParameters()
{
    myAlarmProfileVal =             (CT_ProfileTableId)0;
    myIsMonitorTraceEnabledVal =    (bool)0;
    myIsInsertAisEnabledVal =       (bool)0;
    myMappingVal =                  (CT_TEL_HopSpeMapping)CT_TEL_HOP_MAPPING_UNKNOWN;
    mySFThresholdVal =              (CT_TEL_BERLevels)CT_TEL_NO_BER;
    mySDThresholdVal =              (CT_TEL_BERLevels)CT_TEL_NO_BER;
    myExternalConectivityVal =      (CT_FAC_ExternalConnectivity)0;
    myIsProtectionEnabledVal =      (CT_FAC_Protection)0;
    myMaintPropVal =                (CT_FAC_MaintProp)0;
    myIsAdaptiveEnabledVal =        (bool)0;
    myMaxRateVal =                  (CT_TEL_daHz)0;
    memset(&myExpectedSignalRateVal, 0 ,sizeof(myExpectedSignalRateVal));
    mySignalTypeVal =               (CT_TEL_SignalType)0;
    myPrimaryStateVal =             (CT_SM_PST)0;
    myLineCodeVal =                 (CT_FAC_LineCode)0;
    mySignalFrameFormatVal =        (CT_FAC_FrameFormat)0;
    myIsTransparentVal =            (bool)0;
    myIsSsmConnectedVal =           (bool)0;
    myGbeFramingModeVal =           (CT_TEL_GbeFramingMode)0;
    myGenTrcVal =                   (bool)0;
    myIsTrafficEnabledVal =         (bool)0;
    myGfpMapVal =                   (CT_TEL_GfpFramingMode)0;
    myNendALSVal =                  (bool)0;
    myNValueVal =                  (CT_FAC_NValue)0;
    myFecTypeVal =                  (CT_TEL_FecType)0;     
    myTransMapVal =                 (CT_TEL_SignalType)0;
    myClkTypeVal =                  (CT_TEL_SignalType)0;
    myTapNumberVal =                (CT_TapNumber)0;
    myIsAutoNegotiationEnabledVal = (bool)0;
    myOeoRegenVal =                 (CT_TEL_OEO_REGEN_MODE)0;
    myCnvTermTypeVal =              (CT_TEL_TermSize)0;
    myPtVal =                       (CT_TEL_PayloadSignalId)0;
    myGfpUpiVal =                   (CT_TEL_GfpUpiId)0;
    myEthRateVal =                  (CT_TEL_daHz)0;
    myDuplexModeVal =               (CT_TEL_MAC_DUPLEX_MODE)0;
    myTcmModeVal =                  (CT_TCM_Mode)0;
    myFlowAdVal =                   (CT_TEL_MAC_ADFLW_CTRL)0;
    myFlowCtrlVal =                 (CT_TEL_MAC_FLOWCTRL)0;
    myVlanTagVal =                  (CT_TEL_VlanTag)0;
    myTagModeVal =                  (bool)0;
    myTpidVal =                     (CT_TEL_Tpid)0;
    myDiscardPauseVal =             (bool)0;
    myPropFefiVal =                 (bool)0;
    myHandleVal =                   (LT_Handle)0;             
    myPmProfileVal =                (CT_PMProfileTableId)0;
    myCFProfileVal =                (int)0;
    myCbrMapVal =                   (CT_TEL_PayloadType)0;
    myGfpMuxVal =                   (CT_TEL_GFP_MUX)0;
    myAdjacentVal =                 (CT_TCM_ADJACENT)0;
    myTribFallVal =                 (bool)0;
    myDmSourceVal =                 (bool)0;
    myGfpTsVal =                    (uint8)0;
    myInterPacketGapVal =           (uint8)0;
    myTimDefVal =                   (CT_TEL_TimCriteriaMode)0;
    myOTIDStatusVal =               (CT_TEL_OTIDStatus)0;
    myHoldOffProtVal =              (int)0;
    myLacpPriorityVal =             (int)0;
    myLacpParticipationVal =        (CT_TEL_LacpPartiMode)0;
    myAisTypeVal =                  (CT_RS_IndicationType)0;
    myTribSizeVal =                 (CT_TEL_TS_SIZE)0;
    myBurstyBerSdIntervalVal =      (uint16)0;
    myBurstyBerSdThresholdVal =     (uint32)0;
    myQualityLevelVal =             (CT_FAC_QualityLevelOverride)0;
    myIsAutoAdjustAttenuationEnabledVal = (bool)0;
}



TL1_mTeraFacilityEntParameters::~TL1_mTeraFacilityEntParameters()
{
}

TL1_mTeraFacilityEntParameters& 
TL1_mTeraFacilityEntParameters::operator=( const TL1_FacilityEntParameters& theBlock )
{
    TL1_FacilityEntParameters::operator=(theBlock);
    SET_VAL(myAlarmProfile,             myAlarmProfile);
    SET_VAL(myTrace,                    myTrace);
    SET_VAL(myExpectedTrace,            myExpectedTrace);
    SET_VAL(myIsMonitorTraceEnabled,    myIsMonitorTraceEnabled);
    SET_VAL(myIsInsertAisEnabled,       myIsInsertAisEnabled);
    SET_VAL(myMapping,                  myMapping);
    SET_VAL(mySFThreshold,              mySFThreshold);
    SET_VAL(mySDThreshold,              mySDThreshold);
    SET_VAL(myExternalConectivity,      myExternalConectivity);
    SET_VAL(myIsProtectionEnabled,      myIsProtectionEnabled);
    SET_VAL(myMaintProp,                myMaintProp);
    SET_VAL(myIsAdaptiveEnabled,        myIsAdaptiveEnabled);
    SET_VAL(myMaxRate,                  myMaxRate);
    SET_VAL(myExpectedSignalRate,       myExpectedSignalRate);
    SET_VAL(myRateList,                 myRateList);
    SET_VAL(mySignalType,               mySignalType);
    SET_VAL(myStsMap,                   myStsMap);
    SET_VAL(myPrimaryState,             myPrimaryState);
    SET_VAL(myLineCode,                 myLineCode);
    SET_VAL(mySignalFrameFormat,        mySignalFrameFormat);
    SET_VAL(myIsTransparent,            myIsTransparent);
    SET_VAL(myIsSsmConnected,           myIsSsmConnected);
    SET_VAL(myConectedTo,               myConectedTo);
    SET_VAL(myGbeFramingMode,           myGbeFramingMode);
    SET_VAL(myGenTrc,                   myGenTrc);
    SET_VAL(myIsTrafficEnabled,         myIsTrafficEnabled);
    SET_VAL(myGfpMap,                   myGfpMap);
    SET_VAL(myNendALS,                  myNendALS);
    SET_VAL(myNValue,                   myNValue);
    SET_VAL(myFecType,                  myFecType);     
    SET_VAL(myOtuExpTrc,                myOtuExpTrc);
    SET_VAL(myOtuTrc,                   myOtuTrc); 
    SET_VAL(myTransMap,                 myTransMap);
    SET_VAL(myClkType,                  myClkType);
    SET_VAL(myTapNumber,                myTapNumber);
    SET_VAL(myIsAutoNegotiationEnabled, myIsAutoNegotiationEnabled);
    SET_VAL(myOeoRegen,                 myOeoRegen);
    SET_VAL(myCnvTermType,              myCnvTermType);
    SET_VAL(myPt,                       myPt);
    SET_VAL(myGfpUpi,                   myGfpUpi);
    SET_VAL(myEthRate,                  myEthRate);
    SET_VAL(myDuplexMode,               myDuplexMode);
    SET_VAL(myTcmMode,                  myTcmMode);
    SET_VAL(myFlowAd,                   myFlowAd);
    SET_VAL(myFlowCtrl,                 myFlowCtrl);
    SET_VAL(myVlanTag,                  myVlanTag);
    SET_VAL(myTagMode,                  myTagMode);
    SET_VAL(myTpid,                     myTpid);
    SET_VAL(myDiscardPause,             myDiscardPause);
    SET_VAL(myPropFefi,                 myPropFefi);
    SET_VAL(myHandle,                   myHandle);
    if (myCtag != NULL)
    {
        myCtagVal = string(myCtag);
        myCtag = (LT_Ctag)myCtagVal.c_str();
    }
    SET_VAL(myPmProfile,                myPmProfile);
    SET_VAL(myCFProfile,                myCFProfile);
    SET_VAL(myCbrMap,                   myCbrMap);
    SET_VAL(myGfpMux,                   myGfpMux);
    SET_VAL(myAdjacent,                 myAdjacent);
    SET_VAL(myTribSlot,                 myTribSlot);
    SET_VAL(myTribFall,                 myTribFall);
    SET_VAL(myDmSource,                 myDmSource);
    SET_VAL(myGfpTs,                    myGfpTs);
    SET_VAL(myInterPacketGap,           myInterPacketGap);
    SET_VAL(myExtChannel,               myExtChannel);
    SET_VAL(myOTIDStatus,               myOTIDStatus);
    SET_VAL(myHoldOffProt,              myHoldOffProt);
    SET_VAL(myTimDef,                   myTimDef);
    SET_VAL(myExpDapi,                  myExpDapi);
    SET_VAL(myExpSapi,                  myExpSapi);
    SET_VAL(myTxDapi,                   myTxDapi);
    SET_VAL(myTxSapi,                   myTxSapi);
    SET_VAL(myLacpPriority,             myLacpPriority);
    SET_VAL(myLacpParticipation,        myLacpParticipation);
    SET_VAL(myAisType,                  myAisType);
    SET_VAL(myTribSize ,                myTribSize);
    SET_VAL(myBurstyBerSdInterval,              myBurstyBerSdInterval);
    SET_VAL(myBurstyBerSdThreshold,             myBurstyBerSdThreshold);
    SET_VAL(myQualityLevel,                     myQualityLevel);
    SET_VAL(myIsAutoAdjustAttenuationEnabled,   myIsAutoAdjustAttenuationEnabled);
    SET_VAL(myExpOperator,              myExpOperator);
    SET_VAL(myTxOperator,               myTxOperator);

    return *this;
}

