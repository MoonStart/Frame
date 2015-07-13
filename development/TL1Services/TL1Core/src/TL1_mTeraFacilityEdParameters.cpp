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

#include <TL1Core/TL1_mTeraFacilityEdParameters.h>
#include <TL1Facility/T7100_TL1FacilityEntity.h>
#include <TL1Core/T7100_TL1AgentUtility.h>

TL1_mTeraFacilityEdParameters::TL1_mTeraFacilityEdParameters():
TL1_FacilityEdParameters()
{
    myAlarmProfileVal =                     (CT_ProfileTableId)0;
    myPrimaryStateVal =                     (CT_SM_PST)0;
    myIsCommandForcedVal =                  (bool)0;
    myIsProtectionEnabledVal =              (CT_FAC_Protection)0;
    myMaintPropVal =                        (CT_FAC_MaintProp)0;
    myIsAdaptiveEnabledVal =                (bool)0;
    myMaxRateVal =                          (CT_TEL_daHz)0;
    memset(&myExpectedSignalRateVal, 0, sizeof(CT_TL1_ExpectedRateRange));
    myIsOtuMapEnabledVal =                  (bool)0;
    myIsMonitorOtiEnabledVal =              (bool)0;
    myIsMonitorTraceEnabledVal =            (bool)0;
    myIsInsertAisEnabledVal =               (bool)0;
    mySFThresholdVal =                      (CT_TEL_BERLevels)0;
    mySDThresholdVal =                      (CT_TEL_BERLevels)0;
    myExternalConnectivityVal =             (CT_FAC_ExternalConnectivity)0;
    mySignalTypeVal =                       (CT_TEL_SignalType)0;
    myClkTypeVal =                          (CT_TEL_ClkType)0;
    myOTIDStatusVal =                       (CT_TEL_OTIDStatus)0;
    myIsAutoAdjustAttenuationEnabledVal =   (bool)0;
    myIsAutoAdjustOutPowerEnabledVal =      (bool)0;
    myIsAutoAdjustInPowerEnabledVal =       (bool)0;
    myIsAutoTxPowerShutdownEnabledVal =     (bool)0;
    myLineCodeVal =                         (CT_FAC_LineCode)0;                       
    myFrameFormatVal =                      (CT_FAC_FrameFormat)0;             
    myIsSsmConnectedVal =                   (bool)0;
    myGfpMapVal =                           (CT_TEL_GfpFramingMode)0;
    myGenTrcVal =                           (bool)0;
    myFecTypeVal =                          (CT_TEL_FecType)0;
    mySuperFecVal =                         (CT_TEL_SuperFec)0;
    myLOSThresholdVal =                     (CT_TEL_mBm)0;
    mySWThresholdVal =                      (CT_TEL_mBm)0;
    mySignalBandVal =                       (CT_TEL_OpticalWaveLength)0;
    myNendALSVal =                          (bool)0;
    myIsEonMsgEnabledVal =                  (bool)0;
    myIsTrafficEnabledVal =                 (bool)0;
    myOeoRegenVal =                         (CT_TEL_OEO_REGEN_MODE)0;
    myTapNumberVal =                        (CT_TapNumber)0;
    myIsAutoNegotiationEnabledVal =         (bool)0;
    myHandleVal =                           (LT_Handle)0;             
    myPtVal =                               (CT_TEL_PayloadSignalId)0;
    myGfpUpiVal =                           (CT_TEL_GfpUpiId)0;
    myQuaVal =                              (bool)0;
    myHoldOffProtVal =                      (int)0;
    myEthRateVal =                          (CT_TEL_daHz)0;
    myDuplexModeVal =                       (CT_TEL_MAC_DUPLEX_MODE)0;
    myTcmModeVal =                          (CT_TCM_Mode)0;
    myFlowAdVal =                           (CT_TEL_MAC_ADFLW_CTRL)0;
    myFlowCtrlVal =                         (CT_TEL_MAC_FLOWCTRL)0;
    myVlanTagVal =                          (CT_TEL_VlanTag)0;
    myTagModeVal =                          (bool)0;
    myTpidVal =                             (CT_TEL_Tpid)0;
    myDiscardPauseVal =                     (bool)0;
    myPropFefiVal =                         (bool)0;
    myPmProfileVal =                        (CT_PMProfileTableId)0;
    myCFProfileVal =                        (int)0;
    myCbrMapVal =                           (CT_TEL_PayloadType)0;
    myTribFallVal =                         (bool )0;
    myDmSourceVal =                         (bool )0;
    myGfpTsVal =                            (uint8)0;
    myInterPacketGapVal =                   (uint8)0;
    myGfpMuxVal =                           (CT_TEL_GFP_MUX)0;
    myTimDefVal =                           (CT_TEL_TimCriteriaMode)0;
    myOtsChanTypeVal =                      (CT_FAC_OtsChanType)0;
    myLacpPriorityVal =                     (int)0;
    myLacpParticipationVal =                (CT_TEL_LacpPartiMode)0;
    myAisTypeVal =                          (CT_RS_IndicationType)0;
    myTribSizeVal =                         (CT_TEL_TS_SIZE)0;
    myBurstyBerSdIntervalVal =              (uint16)0;
    myBurstyBerSdThresholdVal =             (uint32)0;
    myQualityLevelVal =                     (CT_FAC_QualityLevelOverride)0;
    myNpOwnerVal =                          (int)0;
}


TL1_mTeraFacilityEdParameters::~TL1_mTeraFacilityEdParameters()
{
}

TL1_mTeraFacilityEdParameters& 
TL1_mTeraFacilityEdParameters::operator=( const TL1_FacilityEdParameters& theBlock )
{
    TL1_FacilityEdParameters::operator=(theBlock);
    SET_VAL(myAlarmProfile,                     myAlarmProfile);
    SET_VAL(myPrimaryState,                     myPrimaryState);
    SET_VAL(myIsCommandForced,                  myIsCommandForced);
    SET_VAL(myIsProtectionEnabled,              myIsProtectionEnabled);
    SET_VAL(myMaintProp,                        myMaintProp);
    SET_VAL(myIsAdaptiveEnabled,                myIsAdaptiveEnabled);  
    SET_VAL(myMaxRate,                          myMaxRate);
    SET_VAL(myExpectedSignalRate,               myExpectedSignalRate);
    SET_VAL(myRateList,                         myRateList);
    SET_VAL(myIsOtuMapEnabled,                  myIsOtuMapEnabled);
    SET_VAL(myTrace,                            myTrace);
    SET_VAL(mySentTrace,                        mySentTrace);
    SET_VAL(myExpectedTrace,                    myExpectedTrace);
    SET_VAL(myIsMonitorOtiEnabled,              myIsMonitorOtiEnabled);
    SET_VAL(myIsMonitorTraceEnabled,            myIsMonitorTraceEnabled);
    SET_VAL(myIsInsertAisEnabled,               myIsInsertAisEnabled);
    SET_VAL(mySFThreshold,                      mySFThreshold);
    SET_VAL(mySDThreshold,                      mySDThreshold);
    SET_VAL(myExternalConnectivity,             myExternalConnectivity);
    SET_VAL(mySignalType,                       mySignalType);
    SET_VAL(myClkType,                          myClkType);
    SET_VAL(myOTIDStatus,                       myOTIDStatus);
    SET_VAL(myIsAutoAdjustAttenuationEnabled,   myIsAutoAdjustAttenuationEnabled);
    SET_VAL(myIsAutoAdjustOutPowerEnabled,      myIsAutoAdjustOutPowerEnabled);
    SET_VAL(myIsAutoAdjustInPowerEnabled,       myIsAutoAdjustInPowerEnabled);
    SET_VAL(myIsAutoTxPowerShutdownEnabled,     myIsAutoTxPowerShutdownEnabled);
    SET_VAL(myLineCode,                         myLineCode);                       
    SET_VAL(myFrameFormat,                      myFrameFormat);             
    SET_VAL(myIsSsmConnected,                   myIsSsmConnected);
    SET_VAL(myConnectedTo,                      myConnectedTo);
    SET_VAL(myGfpMap,                           myGfpMap);
    SET_VAL(myProtFunc,                         myProtFunc);
    SET_VAL(myGenTrc,                           myGenTrc);
    SET_VAL(myFecType,                          myFecType);
    SET_VAL(myLOSThreshold,                     myLOSThreshold);
    SET_VAL(mySWThreshold,                      mySWThreshold);
    SET_VAL(mySignalBand,                       mySignalBand);
    SET_VAL(myNendALS,                          myNendALS);
    SET_VAL(myOtuExpTrc,                        myOtuExpTrc);
    SET_VAL(myAddCrsMap,                        myAddCrsMap);
    SET_VAL(myDelCrsMap,                        myDelCrsMap);
    SET_VAL(myIsEonMsgEnabled,                  myIsEonMsgEnabled);
    SET_VAL(myIsTrafficEnabled,                 myIsTrafficEnabled);
    SET_VAL(myOeoRegen,                         myOeoRegen);
    SET_VAL(myTapNumber,                        myTapNumber);
    SET_VAL(myIsAutoNegotiationEnabled,         myIsAutoNegotiationEnabled);
    SET_VAL(myHandle,                           myHandle);             
    SET_VAL(myGfpUpi,                           myGfpUpi);
    SET_VAL(myPt,                               myPt);
    SET_VAL(myQua,                              myQua);
    if (myCtag != NULL)
    {
        myCtagVal = string(myCtag);
        myCtag = (LT_Ctag)myCtagVal.c_str();
    }
    SET_VAL(myHoldOffProt,                      myHoldOffProt);
    SET_VAL(myExtChannel,                       myExtChannel);
    SET_VAL(myAddCstMap,                        myAddCstMap);
    SET_VAL(myDelCstMap,                        myDelCstMap);
    SET_VAL(myEthRate,                          myEthRate);
    SET_VAL(myDuplexMode,                       myDuplexMode);
    SET_VAL(myTcmMode,                          myTcmMode);
    SET_VAL(myFlowAd,                           myFlowAd);
    SET_VAL(myFlowCtrl,                         myFlowCtrl);
    SET_VAL(myVlanTag,                          myVlanTag);
    SET_VAL(myTagMode,                          myTagMode);
    SET_VAL(myTpid,                             myTpid);
    SET_VAL(myDiscardPause,                     myDiscardPause);
    SET_VAL(myPropFefi,                         myPropFefi);
    SET_VAL(myPmProfile,                        myPmProfile);
    SET_VAL(myCFProfile,                        myCFProfile);
    SET_VAL(myCbrMap,                           myCbrMap);
    SET_VAL(myGfpMux,                           myGfpMux);
    SET_VAL(myTribSlot,                         myTribSlot);
    SET_VAL(myTribFall,                         myTribFall);
    SET_VAL(myDmSource,                         myDmSource);
    SET_VAL(myGfpTs,                            myGfpTs);
    SET_VAL(myInterPacketGap,                   myInterPacketGap);
    SET_VAL(myTimDef,                           myTimDef);
    SET_VAL(myExpDapi,                          myExpDapi);
    SET_VAL(myExpSapi,                          myExpSapi);
    SET_VAL(myTxDapi,                           myTxDapi);
    SET_VAL(myTxSapi,                           myTxSapi);
    SET_VAL(myLacpPriority,                     myLacpPriority);
    SET_VAL(myLacpParticipation,                myLacpParticipation);
    SET_VAL(myOtsChanMap,                       myOtsChanMap);
    SET_VAL(myOtsChanType,                      myOtsChanType);
    SET_VAL(myAisType,                          myAisType);
    SET_VAL(myTribSize ,                        myTribSize);
    SET_VAL(myBurstyBerSdInterval,              myBurstyBerSdInterval);
    SET_VAL(myBurstyBerSdThreshold,             myBurstyBerSdThreshold);
    SET_VAL(myQualityLevel,                     myQualityLevel);
    SET_VAL(myNpOwner,                          myNpOwner);
    SET_VAL(myExpOperator,                      myExpOperator);
    SET_VAL(myTxOperator,                       myTxOperator);
   
    return *this;
}

