/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Opm
 AUTHOR   :  Eric Bernier November 30th 1999
 DESCRIPTION:Definition of the class TSPII_OpticalIf
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_OpticalIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include "CommonTypes/CT_Equipment.h"
#include <string.h>

const CT_TEL_mBm    MIN_POWER_VALID     = -5000;
const CT_TEL_mBm    MAX_POWER_VALID     =  700;
const CT_TEL_mBm    MAX_VALID_OMS_POWER = 3000;
const CT_TEL_mBm    LOS_POWER_THRESHOLD_DEFAULT_POWER = -3000;  // -30 dBm

///////////////////////////////////////////////////////////////////////////////
TSPII_OpticalIf::TSPII_OpticalIf(bool theDefault,
                                 bool theTxPilotToneControlSupported,
                                 bool theOpticalPowerReceivedSupported,
                                 bool theOpticalPowerTransmittedSupported,
                                 bool theOpticalPowerTransmittedByPeerSupported,
                                 bool theOpticalActualGainSupported,
                                 bool theLanePowerSupported ) :
    TSPII_BaseIf(theDefault),
    itsTxPilotToneControlSupported(theTxPilotToneControlSupported),
    itsOpticalPowerReceivedSupported(theOpticalPowerReceivedSupported),
    itsOpticalPowerTransmittedSupported(theOpticalPowerTransmittedSupported),
    itsOpticalPowerTransmittedByPeerSupported(theOpticalPowerTransmittedByPeerSupported),
    itsLanePowerSupported(theLanePowerSupported),
    itsOpticalActualGainSupported(theOpticalActualGainSupported),
    itsManualPtAmplMax(0),
    itsMaxTxPTAmplitude(CT_TEL_PT_MAX_TX_AMP),
    itsMinTxPTAmplitude(CT_TEL_PT_MIN_TX_AMP),
    itsAmpliRatioNeeded(TSPII_OPT_PT_AMPLI_RATIO_NEEDED),
    itsTargetPowerBoost(TSPII_OPT_PT_TARGET_POWER_BOOST),
    itsPowerTolerance(TSPII_OPT_PT_POWER_TOLERANCE),
    itsMaxTxPTAmpliRatio(TSPII_OPT_PT_MAX_AMPLI_RATIO),
    itsMinTxPTAmpliRatio(TSPII_OPT_PT_MIN_AMPLI_RATIO),
    itsUpdatePeriod(TSPII_UPDATE_PERIOD),
    itsNumOfLanes(0)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OpticalIf::~TSPII_OpticalIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::RefreshGet()
{
    // Availability
    itsTxPilotToneControlSupported   = IsTxPilotToneControlSupported();
    itsOpticalPowerReceivedSupported = IsOpticalPowerReceivedSupported();
    itsOpticalPowerTransmittedSupported = IsOpticalPowerTransmittedSupported();
    itsOpticalPowerTransmittedByPeerSupported = IsOpticalPowerTransmittedByPeerSupported();
    itsLanePowerSupported = IsLanePowerSupported();
    itsOpticalActualGainSupported = IsOpticalActualGainSupported();    

    // Mon Attributes
    itsLaserState                    = GetLaserState();
    itsLOS                           = GetOptLOS();
    itsLossOfClock                   = GetLossOfClock();
    if (IsOpticalPowerReceivedSupported())
    {
        itsOptPowerReceived = GetOpticalPowerReceived();
    }
    itsOptPowerTransmitted           = GetOpticalPowerTransmitted();
    if (IsOpticalPowerTransmittedByPeerSupported())
    {
        itsOptPowerTransmittedByPeer = GetOpticalPowerTransmittedByPeer();
        itsOptPowerTransmittedToPeer = GetOpticalPowerTransmittedToPeer();
        itsOmsPowerTransmittedByPeer = GetOmsPowerTransmittedByPeer();
        itsOmsPowerTransmittedToPeer = GetOmsPowerTransmittedToPeer();
        itsOmsPowerTransmitted       = GetOmsPowerTransmitted();
    }
    if (IsLanePowerSupported())
    {
        itsLaneLowReceivedPower      = GetLaneLowReceivedPower();
        itsLaneHighReceivedPower     = GetLaneHighReceivedPower();
        itsLaneLowTransmittedPower   = GetLaneLowTransmittedPower();
        itsLaneHighTransmittedPower  = GetLaneHighTransmittedPower();
        itsLaneReceivedPower         = GetLaneReceivedPower();
        itsLaneTransmittedPower      = GetLaneTransmittedPower();
    }
    if (IsOpticalActualGainSupported()) itsOptActualGain = GetOpticalActualGain();   
    itsLaserBiasCurrentAbsolute      = GetLaserBiasCurrentAbsolute();
    itsLaserBiasCurrentPercent       = GetLaserBiasCurrent();
    itsLaserTemperatureAbsolute      = GetLaserTemperatureAbsolute();
    itsLaserTemperatureError         = GetLaserTemperature();
    itsPrbsRxLosync                  = GetPrbsRxLosync();
    GetPrbsRxErrors(itsPrbsRxErrorCountHigh, itsPrbsRxErrorCountLow, itsPrbsRxErrorTime);
    itsOpticalReturnLoss             = GetOpticalReturnLoss();
    itsIsDualOcmPresent              = GetIsDualOcmPresent();
    itsChromaticDispersion           = GetChromaticDispersion();
    itsDifferentialGroupDelay        = GetDifferentialGroupDelay();
    its2ndOrderPolarModeDispersion   = Get2ndOrderPolarModeDispersion();
    itsStateOfPolarization           = GetStateOfPolarization();
    itsPolarDependentLoss            = GetPolarDependentLoss();
    itsQvalue                        = GetQvalue();
    itsCarrierFrequencyOffset        = GetCarrierFrequencyOffset();
    itsSignalNoiseRatio              = GetSignalNoiseRatio();
    itsYCableRxMessage               = GetRxYCableMessage();
    itsMapMaskSet                    = IsMapMaskReady();
    itsConnectionMap                 = GetConnectionMap();

    // Cfg Attributes
    itsLaserEnable                   = GetLaserEnable();
    itsFacLoop                       = GetFacilityLoopbackEnable();
    itsTerLoop                       = GetTerminalLoopbackEnable();
    itsALS                           = GetAutomaticLaserShutdown();
    itsConsiderAISforALS             = GetConsiderAISforALS();
    itsNeALS                         = GetNearEndAutomaticLaserShutdown();
    itsOutputPower                   = GetOutputPower();
    itsBitRate                       = GetBitRate();
    itsOTNMode                       = GetOTNMode();
    itsTxTraceID                     = GetTxTraceID();
    itsPilotToneFreq                 = GetTxPilotTone();
    if (IsTxPilotToneControlSupported()) itsTxPTAmplitude  = GetTxPTAmplitude();
    if (IsTxPilotToneControlSupported()) itsTxPTAmpliRatio = GetTxPTAmpliRatio();
    if (IsTxPilotToneControlSupported()) itsTargetPowerBoost  = GetTargetPowerBoost();
    if (IsTxPilotToneControlSupported()) itsPowerTolerance    = GetPowerTolerance();
    if (IsTxPilotToneControlSupported()) itsAmpliRatioNeeded  = GetAmpliRatioNeeded();
    if (IsTxPilotToneControlSupported()) itsMaxTxPTAmpliRatio = GetMaxTxPTAmpliRatio();
    if (IsTxPilotToneControlSupported()) itsMinTxPTAmpliRatio = GetMinTxPTAmpliRatio();
    itsWavelength                    = GetWavelength();
    itsBand                          = GetBand();
    itsPlan                          = GetFreqPlan();
    itsLOSThreshold                  = GetLOSThreshold();
    itsOEORegenMode                  = GetOEORegenMode();
    itsPrbsTxEnable                  = GetPrbsTxEnable();
    itsPrbsRxEnable                  = GetPrbsRxEnable();
    itsPrbsRxSessionCounter          = GetPrbsRxSessionCounter();
    itsAlsDelay                      = GetAlsHoldOffDelay();
    itsYCableProtectionEnable        = GetYCableProtectionEnable();
    itsYCableTxMessage               = GetTxYCableMessage();
    itsClockType                     = GetClockType();
    itsOTIDStatus                    = GetOTIDStatus();
    itsFefiForced                    = GetFefiForced();
    itsDwdmFault                     = GetDwdmFault();
    itsMateChannelEnable             = GetMateChannelEnabled();
    itsMateChannelSlotId             = GetMateChannelSlotId();
    itsMateChannelPortId             = GetMateChannelPortId();
    itsUpdatePeriod                  = GetUpdatePeriod();
    itsPrbsFormat                    = GetPrbsFormat();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::RefreshSet()
{
    // Cfg Attributes
    SetLaserEnable(itsLaserEnable);
    SetFacilityLoopbackEnable(itsFacLoop);
    SetTerminalLoopbackEnable(itsTerLoop);
    SetAutomaticLaserShutdown(itsALS);
    SetConsiderAISforALS(itsConsiderAISforALS);
    SetNearEndAutomaticLaserShutdown(itsNeALS);
    SetOutputPower(itsOutputPower);
    SetBitRate(itsBitRate);
    SetOTNMode(itsOTNMode);
    SetTxTraceID(itsTxTraceID);
    SetTxPilotTone(itsPilotToneFreq);
    if (IsTxPilotToneControlSupported()) SetTxPTAmplitude(itsTxPTAmplitude);
    if (IsTxPilotToneControlSupported()) SetTxPTAmpliRatio(itsTxPTAmpliRatio);
    if (IsTxPilotToneControlSupported()) SetTargetPowerBoost(itsTargetPowerBoost);
    if (IsTxPilotToneControlSupported()) SetPowerTolerance(itsPowerTolerance);
    if (IsTxPilotToneControlSupported()) SetAmpliRatioNeeded(itsAmpliRatioNeeded);
    if (IsTxPilotToneControlSupported()) SetMaxTxPTAmpliRatio(itsMaxTxPTAmpliRatio);
    if (IsTxPilotToneControlSupported()) SetMinTxPTAmpliRatio(itsMinTxPTAmpliRatio);
    SetWavelength(itsWavelength);
    SetBand(itsBand);
    SetFreqPlan(itsPlan);
    SetLOSThreshold(itsLOSThreshold);
    SetOEORegenMode(itsOEORegenMode);
    SetPrbsTxEnable(itsPrbsTxEnable);
    SetPrbsRxEnable(itsPrbsRxEnable);
    SetPrbsRxSessionCounter(itsPrbsRxSessionCounter);
    if (IsOpticalPowerTransmittedByPeerSupported()) SetOpticalPowerTransmittedToPeer();
    if (IsOpticalPowerTransmittedByPeerSupported()) SetOmsPowerTransmittedToPeer();
    SetAlsHoldOffDelay(itsAlsDelay);
    SetYCableProtectionEnable(itsYCableProtectionEnable);
    SetTxYCableMessage(itsYCableTxMessage);
    SetClockType(itsClockType);
    SetOTIDStatus(itsOTIDStatus);
    SetFefiForced(itsFefiForced);
    SetDwdmFault(itsDwdmFault);
    SetMateChannelEnabled(itsMateChannelEnable);
    SetMateChannelSlotId(itsMateChannelSlotId);
    SetMateChannelPortId(itsMateChannelPortId);
    SetUpdatePeriod(itsUpdatePeriod);
    SetPrbsFormat(itsPrbsFormat);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Mon Attributes
    itsLaserState                    = false;
    itsLOS                           = 0;
    itsLossOfClock                   = 0;
    itsOptPowerReceived              = TRAFFIC_DEFAULT_POWER;
    itsOptPowerTransmitted           = TRAFFIC_DEFAULT_POWER;
    itsOptPowerTransmittedByPeer     = TRAFFIC_DEFAULT_POWER;
    itsOptPowerTransmittedToPeer     = TRAFFIC_DEFAULT_POWER;
    itsOmsPowerTransmittedByPeer     = TRAFFIC_DEFAULT_POWER;
    itsOmsPowerTransmittedToPeer     = TRAFFIC_DEFAULT_POWER;
    itsOmsPowerTransmitted           = TRAFFIC_DEFAULT_POWER;
    itsLaneLowReceivedPower          = TRAFFIC_DEFAULT_POWER;
    itsLaneHighReceivedPower         = TRAFFIC_DEFAULT_POWER;
    itsLaneLowTransmittedPower       = TRAFFIC_DEFAULT_POWER;
    itsLaneHighTransmittedPower      = TRAFFIC_DEFAULT_POWER;
    itsNumOfLanes                    = 1;
    itsLaneReceivedPower.clear();     // Erase the vector
    itsLaneTransmittedPower.clear();  // Erase the vector
    itsLaneReceivedPower.push_back(TRAFFIC_DEFAULT_POWER);
    itsLaneTransmittedPower.push_back(TRAFFIC_DEFAULT_POWER);
    itsOptActualGain                 = 0;
    itsLaserBiasCurrentAbsolute      = 0;
    itsLaserBiasCurrentPercent       = TRAFFIC_DEFAULT_RATIO;
    itsLaserTemperatureAbsolute      = TRAFFIC_DEFAULT_TEMP;
    itsLaserTemperatureError         = 0;
    itsPrbsRxLosync                  = 0;
    itsPrbsRxErrorCountHigh          = 0;
    itsPrbsRxErrorCountLow           = 0;
    itsPrbsRxErrorTime               = 0;
    itsOpticalReturnLoss             = 0;
    itsIsDualOcmPresent              = false;
    itsChromaticDispersion           = 0;
    itsDifferentialGroupDelay        = 0;
    its2ndOrderPolarModeDispersion   = 0;
    itsStateOfPolarization           = 0;
    itsPolarDependentLoss            = 0;
    itsQvalue                        = 0;
    itsCarrierFrequencyOffset        = 0;
    itsSignalNoiseRatio              = 0;
    itsYCableRxMessage               = 0;
    itsMapMaskSet                    = false;
    itsConnectionMap                 = 0;

    // Cfg Attributes
    itsLaserEnable                   = false;
    itsFacLoop                       = false;
    itsTerLoop                       = false;
    itsALS                           = false;
    itsConsiderAISforALS             = false;
    itsNeALS                         = false;
    itsOutputPower                   = TRAFFIC_DEFAULT_POWER;
    itsBitRate                       = BIT_RATE_OC48;
    itsOTNMode                       = CT_OTN_MODE_G709;
    itsTxTraceID                     = 0;
    itsPilotToneFreq                 = 0;
    itsTxPTAmplitude                 = 0;
    itsTxPTAmpliRatio                = 0.0;
    itsWavelength                    = 0;
    itsBand                          = CT_TEL_1310_NM;
    itsPlan                          = CT_TEL_UNKNOWN_PLAN;
    itsLOSThreshold                  = LOS_POWER_THRESHOLD_DEFAULT_POWER;
    itsOEORegenMode                  = CT_TEL_OEO_REGEN_UNKNOWN;
    itsPrbsTxEnable                  = false;
    itsPrbsRxEnable                  = false;
    itsPrbsRxSessionCounter          = 0;
    itsAlsDelay                      = 0;
    itsYCableProtectionEnable        = false;
    itsYCableTxMessage               = 0;
    itsFefiForced                    = false;
    itsMateChannelEnable             = false;
    itsMateChannelSlotId             = 0;
    itsMateChannelPortId             = 0;
    itsDwdmFault                     = false;
    itsSfpRouteEnd                   = 0;
    itsSfpRouteMiddle                = 0;
    itsPrbsFormat                    = CT_TEL_PRBS_G709;

    //Debug attributes
    itsManualPtAmplMax               = 0;

    itsMaxTxPTAmplitude              = CT_TEL_PT_MAX_TX_AMP;    
    itsMinTxPTAmplitude              = CT_TEL_PT_MIN_TX_AMP;

    itsAmpliRatioNeeded              = TSPII_OPT_PT_AMPLI_RATIO_NEEDED;
    itsTargetPowerBoost              = TSPII_OPT_PT_TARGET_POWER_BOOST;
    itsPowerTolerance                = TSPII_OPT_PT_POWER_TOLERANCE;
    itsMaxTxPTAmpliRatio             = TSPII_OPT_PT_MAX_AMPLI_RATIO;
    itsMinTxPTAmpliRatio             = TSPII_OPT_PT_MIN_AMPLI_RATIO;

    itsClockType                     = CT_TEL_CLK_UNKNOWN;
    itsOTIDStatus                    = CT_TEL_OTID_DISABLED;
    
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetLaserState()
{
    return itsLaserState;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetOptLOS()
{
    return itsLOS;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetLossOfClock()
{
    return itsLossOfClock;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOpticalPowerReceived()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerReceivedSupported(), FC_NotSupportedError, "GetOpticalPowerReceived not supported");
    return itsOptPowerReceived;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOpticalPowerTransmitted()
{
    return itsOptPowerTransmitted;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOpticalPowerTransmittedByPeer()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerTransmittedByPeerSupported(), FC_NotSupportedError, "GetOpticalPowerTransmittedByPeer not supported");
    return itsOptPowerTransmittedByPeer;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOpticalPowerTransmittedToPeer()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerTransmittedByPeerSupported(), FC_NotSupportedError, "GetOpticalPowerTransmittedByPeer not supported");
    return itsOptPowerTransmittedToPeer;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOmsPowerTransmittedByPeer()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerTransmittedByPeerSupported(), FC_NotSupportedError, "GetOpticalPowerTransmittedByPeer not supported");
    return itsOmsPowerTransmittedByPeer;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOmsPowerTransmittedToPeer()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerTransmittedByPeerSupported(), FC_NotSupportedError, "GetOpticalPowerTransmittedByPeer not supported");
    return itsOmsPowerTransmittedToPeer;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOmsPowerTransmitted()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerTransmittedByPeerSupported(), FC_NotSupportedError, "GetOpticalPowerTransmittedByPeer not supported");
    return itsOmsPowerTransmitted;
}


///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetLaneLowReceivedPower()
{
    FC_THROW_ERROR_IF(!IsLanePowerSupported(), FC_NotSupportedError, "GetLaneLowReceivedPower not supported");
    return itsLaneLowReceivedPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetLaneHighReceivedPower()
{
    FC_THROW_ERROR_IF(!IsLanePowerSupported(), FC_NotSupportedError, "GetLaneHighReceivedPower not supported");
    return itsLaneHighReceivedPower;
}

///////////////////////////////////////////////////////////////////////////////
vector<CT_TEL_mBm>& TSPII_OpticalIf::GetLaneReceivedPower()
{
    FC_THROW_ERROR_IF(!IsLanePowerSupported(), FC_NotSupportedError, "GetLaneReceivedPower not supported");
    return itsLaneReceivedPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetLaneLowTransmittedPower()
{
    FC_THROW_ERROR_IF(!IsLanePowerSupported(), FC_NotSupportedError, "GetLaneLowTransmittedPower not supported");
    return itsLaneLowTransmittedPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetLaneHighTransmittedPower()
{
    FC_THROW_ERROR_IF(!IsLanePowerSupported(), FC_NotSupportedError, "GetLaneHighTransmittedPower not supported");
    return itsLaneHighTransmittedPower;
}

///////////////////////////////////////////////////////////////////////////////
vector<CT_TEL_mBm>& TSPII_OpticalIf::GetLaneTransmittedPower()
{
    FC_THROW_ERROR_IF(!IsLanePowerSupported(), FC_NotSupportedError, "GetLaneTransmittedPower not supported");
    return itsLaneTransmittedPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOpticalActualGain()
{
    FC_THROW_ERROR_IF(!IsOpticalActualGainSupported(), FC_NotSupportedError, "GetOpticalActualGain not supported");
    return itsOptActualGain;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_uAmps TSPII_OpticalIf::GetLaserBiasCurrentAbsolute()
{
    return itsLaserBiasCurrentAbsolute;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_Percent TSPII_OpticalIf::GetLaserBiasCurrent()
{
    return itsLaserBiasCurrentPercent;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_milliCelcius TSPII_OpticalIf::GetLaserTemperatureAbsolute()
{
    return itsLaserTemperatureAbsolute;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_milliCelcius TSPII_OpticalIf::GetLaserTemperature()
{
    return itsLaserTemperatureError;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetPrbsRxLosync()
{
    return itsPrbsRxLosync;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetPrbsRxErrors(uint32 & theCountHigh, uint32 & theCountLow, uint32 & theTime)
{
    bool foundIt = true;   // Can be set to false with debugger to simulate failure

    theCountHigh = itsPrbsRxErrorCountHigh;
    theCountLow = itsPrbsRxErrorCountLow;
    theTime = itsPrbsRxErrorTime;
    return foundIt;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOpticalReturnLoss()
{
    return itsOpticalReturnLoss;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetIsDualOcmPresent()
{
    return itsIsDualOcmPresent;
}

///////////////////////////////////////////////////////////////////////////////
int32 TSPII_OpticalIf::GetChromaticDispersion()
{
    return itsChromaticDispersion;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_OpticalIf::GetDifferentialGroupDelay()
{
    return itsDifferentialGroupDelay;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_OpticalIf::Get2ndOrderPolarModeDispersion()
{
    return its2ndOrderPolarModeDispersion;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetStateOfPolarization()
{
    return itsStateOfPolarization;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm  TSPII_OpticalIf::GetPolarDependentLoss()
{
    return itsPolarDependentLoss;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm  TSPII_OpticalIf::GetQvalue()
{
    return itsQvalue;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm  TSPII_OpticalIf::GetCarrierFrequencyOffset()
{
    return itsCarrierFrequencyOffset;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm  TSPII_OpticalIf::GetSignalNoiseRatio()
{
    return itsSignalNoiseRatio;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_OpticalIf::GetRxYCableMessage()
{
    return itsYCableRxMessage;
}

CT_TEL_ClkType TSPII_OpticalIf::GetClockType()
{
    return itsClockType;
}
CT_TEL_OTIDStatus TSPII_OpticalIf::GetOTIDStatus()
{
    return itsOTIDStatus;
}

//////////////////////////////////
// Optical Config Interfaces
// //////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetLaserEnable(bool theLaserEnable)
{
    itsLaserEnable = theLaserEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetFacilityLoopbackEnable(bool theEnable)
{
    itsFacLoop = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetTerminalLoopbackEnable(bool theEnable)
{
    itsTerLoop = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetAutomaticLaserShutdown(bool theState)
{
    itsALS = theState;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetConsiderAISforALS(bool theState)
{
    itsConsiderAISforALS = theState;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetNearEndAutomaticLaserShutdown(bool theState)
{
    itsNeALS = theState;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetOutputPower(CT_TEL_mBm theOutputPower)
{
    itsOutputPower = theOutputPower;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetBitRate(CT_TEL_daHz theBitRate)
{
    itsBitRate = theBitRate;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetOTNMode(CT_TEL_OTNMode theMode)
{
    itsOTNMode = theMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetTxTraceID(CT_TEL_PilotToneID theTraceID)
{
    itsTxTraceID = theTraceID;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetTxPilotTone(CT_TEL_Hz theFrequency)
{
    itsPilotToneFreq = theFrequency;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetTxPTAmplitude(uint32 theAmplitude)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetTxPTAmplitude not supported");
    itsTxPTAmplitude = theAmplitude;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetTxPTAmpliRatio(float theAmpliRatio)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetTxPTAmpliRatio not supported");
    itsTxPTAmpliRatio = theAmpliRatio;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetWavelength(uint32 theWavelength)
{
    itsWavelength = theWavelength;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetFrequency(uint32 theFrequency)
{
    itsFrequency = theFrequency;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetBand(CT_TEL_OpticalWaveLength theBand)
{
    itsBand = theBand;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetFreqPlan(CT_TEL_FreqencyPlan thePlan)
{
    itsPlan = thePlan;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetLOSThreshold(CT_TEL_mBm theLOSThreshold)
{
    itsLOSThreshold = theLOSThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetOEORegenMode(CT_TEL_OEO_REGEN_MODE theMode)
{
    itsOEORegenMode = theMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetPrbsTxEnable(bool theEnable)
{
    itsPrbsTxEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetPrbsRxEnable(bool theEnable)
{
    if((theEnable != itsPrbsRxEnable) && (theEnable == true))
    {
        // Reset the error counts and time when we transition to enabled
        itsPrbsRxErrorCountHigh = 0;
        itsPrbsRxErrorCountLow = 0;
        itsPrbsRxErrorTime = 0;
    }
    itsPrbsRxEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetPrbsRxSessionCounter(uint32 thePrbsRxSessionCounter) 
{
    itsPrbsRxSessionCounter = thePrbsRxSessionCounter;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetAlsHoldOffDelay(uint32 theDelay)
{
    itsAlsDelay = theDelay;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetYCableProtectionEnable(bool theEnable)
{
    itsYCableProtectionEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetTxYCableMessage(uint8 theMessage)
{
    itsYCableTxMessage = theMessage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetConnectionMap(uint16 theMapMask) 
{
    itsMapMaskSet    = true;
    itsConnectionMap = theMapMask;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetOpticalPowerTransmittedToPeer()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerTransmittedByPeerSupported(), FC_NotSupportedError, "SetOpticalPowerTransmittedToPeer not supported");
    itsOptPowerTransmittedToPeer = itsOptPowerTransmitted;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetOmsPowerTransmittedToPeer()
{
    FC_THROW_ERROR_IF(!IsOpticalPowerTransmittedByPeerSupported(), FC_NotSupportedError, "SetOpticalPowerTransmittedToPeer not supported");
    itsOmsPowerTransmittedToPeer = itsOmsPowerTransmitted;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetMaxTxPTAmplitude(uint16 theMaxTxPTAmplitude)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetMaxTxPTAmplitude not supported");
    itsMaxTxPTAmplitude = theMaxTxPTAmplitude;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetMinTxPTAmplitude(uint16 theMinTxPTAmplitude)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetMinTxPTAmplitude not supported");
    itsMinTxPTAmplitude = theMinTxPTAmplitude;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetAmpliRatioNeeded(bool theAmpliRatioNeeded)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetAmpliRatioNeeded not supported");
    itsAmpliRatioNeeded = theAmpliRatioNeeded;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetTargetPowerBoost(float theTargetPowerBoost)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetTargetPowerBoost not supported");
    itsTargetPowerBoost = theTargetPowerBoost;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetPowerTolerance(float thePowerTolerance)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetPowerTolerance not supported");
    itsPowerTolerance = thePowerTolerance;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetMaxTxPTAmpliRatio(float theMaxTxAmpliRatio)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetMaxTxPTAmpliRatio not supported");
    itsMaxTxPTAmpliRatio = theMaxTxAmpliRatio;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetMinTxPTAmpliRatio(float theMinTxPTAmpliRatio)
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "SetMinTxPTAmpliRatio not supported");
    itsMinTxPTAmpliRatio = theMinTxPTAmpliRatio;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetClockType(CT_TEL_ClkType theMode)
{
    itsClockType = theMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetOTIDStatus(CT_TEL_OTIDStatus theOTIDStatus)
{
    itsOTIDStatus = theOTIDStatus;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetFefiForced(bool theForce)
{
    itsFefiForced = theForce;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetMateChannelEnabled(bool theEnable)
{
    itsMateChannelEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetMateChannelSlotId(uint16 theSlotId)
{
    itsMateChannelSlotId = theSlotId;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetMateChannelPortId(uint16 thePortId)
{
    itsMateChannelPortId = thePortId;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetDwdmFault(bool theEnable)
{
    itsDwdmFault = theEnable;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetLaserEnable() const
{
    return itsLaserEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetFacilityLoopbackEnable() const
{
    return itsFacLoop;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetTerminalLoopbackEnable() const
{
    return itsTerLoop;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetAutomaticLaserShutdown() const
{
    return itsALS;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetConsiderAISforALS() const
{
    return itsConsiderAISforALS;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetNearEndAutomaticLaserShutdown() const
{
    return itsNeALS;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetOutputPower() const
{
    return itsOutputPower;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_daHz TSPII_OpticalIf::GetBitRate() const
{
    return itsBitRate;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_OTNMode TSPII_OpticalIf::GetOTNMode() const
{
    return itsOTNMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_PilotToneID TSPII_OpticalIf::GetTxTraceID() const
{
    return itsTxTraceID;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_Hz TSPII_OpticalIf::GetTxPilotTone() const
{
    return itsPilotToneFreq;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetTxPTAmplitude() const
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "GetTxPTAmplitude not supported");
    return itsTxPTAmplitude;
}

///////////////////////////////////////////////////////////////////////////////
float TSPII_OpticalIf::GetTxPTAmpliRatio() const
{
    FC_THROW_ERROR_IF(!IsTxPilotToneControlSupported(), FC_NotSupportedError, "GetTxPTAmpliRatio not supported");
    return itsTxPTAmpliRatio;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_OpticalIf::GetMaxTxPTAmplitude() const
{
    return itsMaxTxPTAmplitude;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_OpticalIf::GetMinTxPTAmplitude() const
{
    return itsMinTxPTAmplitude;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetAmpliRatioNeeded() const
{
    return itsAmpliRatioNeeded;
}

///////////////////////////////////////////////////////////////////////////////
float TSPII_OpticalIf::GetTargetPowerBoost() const
{
    return itsTargetPowerBoost;
}

///////////////////////////////////////////////////////////////////////////////
float TSPII_OpticalIf::GetPowerTolerance() const
{
    return itsPowerTolerance;
}

///////////////////////////////////////////////////////////////////////////////
float TSPII_OpticalIf::GetMaxTxPTAmpliRatio() const
{
    return itsMaxTxPTAmpliRatio;
}

///////////////////////////////////////////////////////////////////////////////
float TSPII_OpticalIf::GetMinTxPTAmpliRatio() const
{
    return itsMinTxPTAmpliRatio;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetWavelength() const
{
    return itsWavelength;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetFrequency() const
{
    return itsFrequency;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_OpticalWaveLength TSPII_OpticalIf::GetBand() const
{
    return itsBand;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_FreqencyPlan TSPII_OpticalIf::GetFreqPlan() const
{
    return itsPlan;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OpticalIf::GetLOSThreshold() const
{
    return itsLOSThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_OEO_REGEN_MODE TSPII_OpticalIf::GetOEORegenMode() const
{
    return itsOEORegenMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetPrbsTxEnable() const
{
    return itsPrbsTxEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetPrbsRxEnable() const
{
    return itsPrbsRxEnable;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetPrbsRxSessionCounter() const
{
    return itsPrbsRxSessionCounter;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OpticalIf::GetAlsHoldOffDelay() const
{
    return itsAlsDelay;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetYCableProtectionEnable() const
{
    return itsYCableProtectionEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::IsTxPilotToneControlSupported() const
{
    return itsTxPilotToneControlSupported;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::IsOpticalPowerReceivedSupported() const
{
    return itsOpticalPowerReceivedSupported;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::IsOpticalPowerTransmittedSupported() const
{
    return itsOpticalPowerTransmittedSupported;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::IsOpticalPowerTransmittedByPeerSupported() const
{
    return itsOpticalPowerTransmittedByPeerSupported;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::IsLanePowerSupported() const
{
    return itsLanePowerSupported;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::IsOpticalActualGainSupported() const
{
    return itsOpticalActualGainSupported;
}
///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::IsMapMaskReady() const
{
    return itsMapMaskSet;
}
///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_OpticalIf::GetTxYCableMessage() const
{
    return itsYCableTxMessage;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_OpticalIf::GetConnectionMap() const
{
    return itsConnectionMap;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetFefiForced() const
{
    return itsFefiForced;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetMateChannelEnabled() const
{
    return itsMateChannelEnable;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_OpticalIf::GetMateChannelSlotId() const
{
    return itsMateChannelSlotId;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_OpticalIf::GetMateChannelPortId() const
{
    return itsMateChannelPortId;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::GetDwdmFault() const
{
    return itsDwdmFault;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::DebugDriftControlFilter(int argc, char ** argv)
{
    // Does nothing here.  This is implemented in the FGTM OPtical IF and no where else
    return;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetUpdatePeriod(FC_Milliseconds theUpdatePeriod)
{
    itsUpdatePeriod = theUpdatePeriod;
}

///////////////////////////////////////////////////////////////////////////////
FC_Milliseconds TSPII_OpticalIf::GetUpdatePeriod() const
{
    return itsUpdatePeriod;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::SetPrbsFormat(CT_TEL_PrbsFormat thePrbsFormat)
{
    itsPrbsFormat = thePrbsFormat;
}


///////////////////////////////////////////////////////////////////////////////
CT_TEL_PrbsFormat TSPII_OpticalIf::GetPrbsFormat() const
{
    return itsPrbsFormat;
}


///////////////////////////////////////////////////////////////////////////////
///// For persitance and region transfer
FC_Stream & TSPII_OpticalIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();
    vector<CT_TEL_mBm>::iterator aIter;
    CT_TEL_mBm    tempPower;
    int otnMode    = itsOTNMode;

    // Monitoring
    theStream << itsLaserState;
    theStream << itsLOS;
    theStream << itsLossOfClock;
    theStream << itsOptPowerReceived;
    theStream << itsOptPowerTransmitted;
    theStream << itsOptPowerTransmittedByPeer;
    theStream << itsOptPowerTransmittedToPeer;
    theStream << itsOmsPowerTransmittedByPeer;
    theStream << itsOmsPowerTransmittedToPeer;
    theStream << itsOmsPowerTransmitted;
    theStream << itsLaneLowReceivedPower;
    theStream << itsLaneHighReceivedPower;
    theStream << itsLaneLowTransmittedPower;
    theStream << itsLaneHighTransmittedPower;
    if(itsNumOfLanes <= CT_NUM_PSX_LANES)
    {
        theStream << itsNumOfLanes;
        for(aIter=itsLaneTransmittedPower.begin(); 
            aIter != itsLaneTransmittedPower.end(); ++aIter)
        {
            tempPower = (*aIter);
            theStream << tempPower;
        }
        for(aIter=itsLaneReceivedPower.begin(); 
            aIter != itsLaneReceivedPower.end(); ++aIter)
        {
            tempPower = (*aIter);
            theStream << tempPower;
        }
    }
    theStream << itsOptActualGain;
    theStream << itsLaserBiasCurrentAbsolute;
    theStream << itsLaserBiasCurrentPercent;
    theStream << itsLaserTemperatureAbsolute;
    theStream << itsLaserTemperatureError;
    theStream << itsPrbsRxErrorCountHigh;
    theStream << itsPrbsRxErrorCountLow;
    theStream << itsPrbsRxErrorTime;
    theStream << itsPrbsRxLosync;
    theStream << itsOpticalReturnLoss;
    theStream << itsIsDualOcmPresent;
    theStream << itsChromaticDispersion;
    theStream << itsDifferentialGroupDelay;
    theStream << its2ndOrderPolarModeDispersion;
    theStream << itsStateOfPolarization;
    theStream << itsPolarDependentLoss;
    theStream << itsQvalue;
    theStream << itsCarrierFrequencyOffset;
    theStream << itsSignalNoiseRatio;
    theStream << itsYCableRxMessage;
    theStream << itsMapMaskSet;
    theStream << itsConnectionMap;

    // Configuration
    theStream << itsLaserEnable;
    theStream << itsFacLoop;
    theStream << itsTerLoop;
    theStream << itsALS;
    theStream << itsConsiderAISforALS;
    theStream << itsNeALS;
    theStream << itsOutputPower;
    theStream << itsBitRate;
    theStream << otnMode;
    theStream << itsTxTraceID;
    theStream << itsPilotToneFreq;
    theStream << itsTxPTAmplitude;
    theStream << itsTxPTAmpliRatio;
    theStream << itsWavelength;
    theStream << itsFrequency;
    theStream << (uint32)itsBand;
    theStream << (uint32)itsPlan;
    theStream << itsLOSThreshold;
    theStream << (uint32)itsOEORegenMode;
    theStream << itsPrbsTxEnable;
    theStream << itsPrbsRxEnable;
    theStream << itsPrbsRxSessionCounter;
    theStream << itsAlsDelay;
    theStream << itsYCableProtectionEnable;
    theStream << itsYCableTxMessage;
    theStream << (uint32)itsClockType;
    theStream << (uint32)itsOTIDStatus;
    theStream << itsFefiForced;
    theStream << itsMateChannelEnable;
    theStream << itsMateChannelSlotId;
    theStream << itsMateChannelPortId;
    theStream << itsDwdmFault;
    theStream << itsUpdatePeriod;
    theStream << itsPrbsFormat;

    // Availability
    theStream << itsTxPilotToneControlSupported;
    theStream << itsOpticalPowerReceivedSupported;
    theStream << itsOpticalPowerTransmittedSupported;
    theStream << itsOpticalPowerTransmittedByPeerSupported;
    theStream << itsLanePowerSupported;
    theStream << itsOpticalActualGainSupported;
    

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
///// For persitance and region transfer
FC_Stream & TSPII_OpticalIf::ReadObjectBinary(FC_Stream & theStream)
{
    uint32 aBand = (uint32)itsBand;
    uint32 aPlan = (uint32)itsPlan;
    uint32 aMode = (uint32)itsOEORegenMode;
    uint32 aClockType = (uint32)itsClockType;
    uint32 aOTIDStatus = (uint32)itsOTIDStatus;
    uint32 aPrbsFormat = (uint32)itsPrbsFormat;
    int otnMode;
    uint32        i;
    CT_TEL_mBm    tempPower;

    // Monitoring
    theStream >> itsLaserState;
    theStream >> itsLOS;
    theStream >> itsLossOfClock;
    theStream >> itsOptPowerReceived;
    theStream >> itsOptPowerTransmitted;
    theStream >> itsOptPowerTransmittedByPeer;
    theStream >> itsOptPowerTransmittedToPeer;
    theStream >> itsOmsPowerTransmittedByPeer;
    theStream >> itsOmsPowerTransmittedToPeer;
    theStream >> itsOmsPowerTransmitted;
    theStream >> itsLaneLowReceivedPower;
    theStream >> itsLaneHighReceivedPower;
    theStream >> itsLaneLowTransmittedPower;
    theStream >> itsLaneHighTransmittedPower;
    // get number of lanes for receive/transmit power
    theStream >> itsNumOfLanes;
    if(itsNumOfLanes <= CT_NUM_PSX_LANES)
    {
        for (i = 0; i < itsNumOfLanes;i++)
        {
            theStream >> tempPower;
            itsLaneTransmittedPower.push_back(tempPower);
        }
        for (i = 0; i < itsNumOfLanes;i++)
        {
            theStream >> tempPower;
            itsLaneReceivedPower.push_back(tempPower);
        }
    }
    theStream >> itsOptActualGain;
    theStream >> itsLaserBiasCurrentAbsolute;
    theStream >> itsLaserBiasCurrentPercent;
    theStream >> itsLaserTemperatureAbsolute;
    theStream >> itsLaserTemperatureError;
    theStream >> itsPrbsRxErrorCountHigh;
    theStream >> itsPrbsRxErrorCountLow;
    theStream >> itsPrbsRxErrorTime;
    theStream >> itsPrbsRxLosync;
    theStream >> itsOpticalReturnLoss;
    theStream >> itsIsDualOcmPresent;
    theStream >> itsChromaticDispersion;
    theStream >> itsDifferentialGroupDelay;
    theStream >> its2ndOrderPolarModeDispersion;
    theStream >> itsStateOfPolarization;
    theStream >> itsPolarDependentLoss;
    theStream >> itsQvalue;
    theStream >> itsCarrierFrequencyOffset;
    theStream >> itsSignalNoiseRatio;
    theStream >> itsYCableRxMessage;
    theStream >> itsMapMaskSet;
    theStream >> itsConnectionMap;

    // Configuration
    theStream >> itsLaserEnable;
    theStream >> itsFacLoop;
    theStream >> itsTerLoop;
    theStream >> itsALS;
    theStream >> itsConsiderAISforALS;
    theStream >> itsNeALS;
    theStream >> itsOutputPower;
    theStream >> itsBitRate;
    theStream >> otnMode;
    theStream >> itsTxTraceID;
    theStream >> itsPilotToneFreq;
    theStream >> itsTxPTAmplitude;
    theStream >> itsTxPTAmpliRatio;
    theStream >> itsWavelength;
    theStream >> itsFrequency;
    theStream >> aBand;
    theStream >> aPlan;
    theStream >> itsLOSThreshold;
    theStream >> aMode;
    theStream >> itsPrbsTxEnable;
    theStream >> itsPrbsRxEnable;
    theStream >> itsPrbsRxSessionCounter;
    theStream >> itsAlsDelay;
    theStream >> itsYCableProtectionEnable;
    theStream >> itsYCableTxMessage;
    theStream >> aClockType;
    theStream >> aOTIDStatus;
    theStream >> itsFefiForced;
    theStream >> itsMateChannelEnable;
    theStream >> itsMateChannelSlotId;
    theStream >> itsMateChannelPortId;
    theStream >> itsDwdmFault;
    theStream >> itsUpdatePeriod;
    theStream >> aPrbsFormat;

    // Availability
    theStream >> itsTxPilotToneControlSupported;
    theStream >> itsOpticalPowerReceivedSupported;
    theStream >> itsOpticalPowerTransmittedSupported;
    theStream >> itsOpticalPowerTransmittedByPeerSupported;
    theStream >> itsLanePowerSupported;
    theStream >> itsOpticalActualGainSupported;
    

    // Update H/W
    itsOTNMode   = (CT_TEL_OTNMode)otnMode;
    itsBand      = (CT_TEL_OpticalWaveLength)aBand;
    itsPlan      = (CT_TEL_FreqencyPlan)aPlan;
    itsClockType = (CT_TEL_ClkType)aClockType;
    itsOTIDStatus = (CT_TEL_OTIDStatus)aOTIDStatus;
    itsPrbsFormat = (CT_TEL_PrbsFormat)aPrbsFormat;
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
///// For Display
ostream & TSPII_OpticalIf::WriteObject(ostream & theStream)
{
    UpdateValues();
    RefreshGet();
    vector<CT_TEL_mBm>::iterator aIter;
    CT_TEL_mBm    tempPower;

    uint32 aBand = (uint32)itsBand;
    uint32 aPlan = (uint32)itsPlan;
    uint32 aMode = (uint32)itsOEORegenMode;
    uint32 aClockType = (uint32)itsClockType;
    uint32 aOTIDStatus = (uint32)itsOTIDStatus;
    uint32 aPrbsFormat = (uint32)itsPrbsFormat;
    int otnMode  = itsOTNMode;

    theStream << FC_InsertVar(itsLaserState);
    theStream << FC_InsertVar(itsLOS);
    theStream << FC_InsertVar(itsLossOfClock);
    theStream << FC_InsertVar(itsOptPowerReceived);
    theStream << FC_InsertVar(itsOptPowerTransmitted);
    theStream << FC_InsertVar(itsOptPowerTransmittedByPeer);
    theStream << FC_InsertVar(itsOptPowerTransmittedToPeer);
    theStream << FC_InsertVar(itsOmsPowerTransmittedByPeer);
    theStream << FC_InsertVar(itsOmsPowerTransmittedToPeer);
    theStream << FC_InsertVar(itsOmsPowerTransmitted);
    theStream << FC_InsertVar(itsLaneLowReceivedPower);
    theStream << FC_InsertVar(itsLaneHighReceivedPower);
    theStream << FC_InsertVar(itsLaneLowTransmittedPower);
    theStream << FC_InsertVar(itsLaneHighTransmittedPower);
    if(itsNumOfLanes <= CT_NUM_PSX_LANES)
    {
        // write out the size of the list of per lane receive/transmit power
        theStream << FC_InsertVar(itsNumOfLanes);
        for(aIter=itsLaneTransmittedPower.begin(); 
            aIter != itsLaneTransmittedPower.end(); ++aIter)
        {
            tempPower = (*aIter);
            theStream << FC_InsertVar(tempPower);
        }
        for(aIter=itsLaneReceivedPower.begin(); 
            aIter != itsLaneReceivedPower.end(); ++aIter)
        {
            tempPower = (*aIter);
            theStream << FC_InsertVar(tempPower);
        }
    }
    theStream << FC_InsertVar(itsOptActualGain);
    theStream << FC_InsertVar(itsLaserBiasCurrentAbsolute);
    theStream << FC_InsertVar(itsLaserBiasCurrentPercent);
    theStream << FC_InsertVar(itsLaserTemperatureAbsolute);
    theStream << FC_InsertVar(itsLaserTemperatureError);
    theStream << FC_InsertVar(itsPrbsRxErrorCountHigh);
    theStream << FC_InsertVar(itsPrbsRxErrorCountLow);
    theStream << FC_InsertVar(itsPrbsRxErrorTime);
    theStream << FC_InsertVar(itsPrbsRxLosync);
    theStream << FC_InsertVar(itsOpticalReturnLoss);
    theStream << FC_InsertVar(itsIsDualOcmPresent);
    theStream << FC_InsertVar(itsChromaticDispersion);
    theStream << FC_InsertVar(itsDifferentialGroupDelay);
    theStream << FC_InsertVar(its2ndOrderPolarModeDispersion);
    theStream << FC_InsertVar(itsStateOfPolarization);
    theStream << FC_InsertVar(itsPolarDependentLoss);
    theStream << FC_InsertVar(itsQvalue);
    theStream << FC_InsertVar(itsCarrierFrequencyOffset);
    theStream << FC_InsertVar(itsSignalNoiseRatio);
    theStream << FC_InsertVar(itsYCableRxMessage);
    theStream << FC_InsertVar(itsMapMaskSet);
    theStream << FC_InsertVar(itsConnectionMap);

    theStream << FC_InsertVar(itsLaserEnable);
    theStream << FC_InsertVar(itsFacLoop);
    theStream << FC_InsertVar(itsTerLoop);
    theStream << FC_InsertVar(itsALS);
    theStream << FC_InsertVar(itsConsiderAISforALS);
    theStream << FC_InsertVar(itsNeALS);
    theStream << FC_InsertVar(itsOutputPower);
    theStream << FC_InsertVar(itsBitRate);
    theStream << FC_InsertVar(otnMode);
    theStream << FC_InsertVar(itsTxTraceID);
    theStream << FC_InsertVar(itsPilotToneFreq);
    theStream << FC_InsertVar(itsTxPTAmplitude);
    theStream << FC_InsertVar(itsTxPTAmpliRatio);
    theStream << FC_InsertVar(itsWavelength);
    theStream << FC_InsertVar(itsFrequency);
    theStream << FC_InsertVar(aBand);
    theStream << FC_InsertVar(aPlan);
    theStream << FC_InsertVar(itsLOSThreshold);
    theStream << FC_InsertVar(aMode);
    theStream << FC_InsertVar(itsPrbsTxEnable);
    theStream << FC_InsertVar(itsPrbsRxEnable);
    theStream << FC_InsertVar(itsAlsDelay);
    theStream << FC_InsertVar(itsYCableProtectionEnable);
    theStream << FC_InsertVar(itsYCableTxMessage);
    theStream << FC_InsertVar(aClockType);
    theStream << FC_InsertVar(aOTIDStatus);
    theStream << FC_InsertVar(itsFefiForced);
    theStream << FC_InsertVar(itsMateChannelEnable);
    theStream << FC_InsertVar(itsMateChannelSlotId);
    theStream << FC_InsertVar(itsMateChannelPortId);
    theStream << FC_InsertVar(itsDwdmFault);
    theStream << FC_InsertVar(itsUpdatePeriod);
    theStream << FC_InsertVar(aPrbsFormat);

    theStream << FC_InsertVar(itsMaxTxPTAmplitude);
    theStream << FC_InsertVar(itsMinTxPTAmplitude);

    theStream << FC_InsertVar(itsAmpliRatioNeeded);
    theStream << FC_InsertVar(itsTargetPowerBoost);
    theStream << FC_InsertVar(itsPowerTolerance);
    theStream << FC_InsertVar(itsMaxTxPTAmpliRatio);
    theStream << FC_InsertVar(itsMinTxPTAmpliRatio);

    theStream << FC_InsertVar(itsTxPilotToneControlSupported);
    theStream << FC_InsertVar(itsOpticalPowerReceivedSupported);
    theStream << FC_InsertVar(itsOpticalPowerTransmittedSupported);
    theStream << FC_InsertVar(itsOpticalPowerTransmittedByPeerSupported);
    theStream << FC_InsertVar(itsLanePowerSupported);
    theStream << FC_InsertVar(itsOpticalActualGainSupported);
    

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
///// For Display
istream & TSPII_OpticalIf::ReadObject(istream & theStream)
{
    uint32 aBand;
    uint32 aPlan;
    uint32 aMode;
    uint32 aClockType;
    uint32 aOTIDStatus;
    uint32 aPrbsFormat;
    int otnMode;
    uint32        i;
    CT_TEL_mBm    tempPower;

    // Monitoring
    theStream >> FC_ExtractVar(itsLaserState);
    theStream >> FC_ExtractVar(itsLOS);
    theStream >> FC_ExtractVar(itsLossOfClock);
    theStream >> FC_ExtractVar(itsOptPowerReceived);
    theStream >> FC_ExtractVar(itsOptPowerTransmitted);
    theStream >> FC_ExtractVar(itsOptPowerTransmittedByPeer);
    theStream >> FC_ExtractVar(itsOptPowerTransmittedToPeer);
    theStream >> FC_ExtractVar(itsOmsPowerTransmittedByPeer);
    theStream >> FC_ExtractVar(itsOmsPowerTransmittedToPeer);
    theStream >> FC_ExtractVar(itsOmsPowerTransmitted);
    theStream >> FC_ExtractVar(itsLaneLowReceivedPower);
    theStream >> FC_ExtractVar(itsLaneHighReceivedPower);
    theStream >> FC_ExtractVar(itsLaneLowTransmittedPower);
    theStream >> FC_ExtractVar(itsLaneHighTransmittedPower);
    theStream >> FC_ExtractVar(itsNumOfLanes);
    if(itsNumOfLanes <= CT_NUM_PSX_LANES)
    {
        for (i = 0; i < itsNumOfLanes;i++)
        {
            theStream >> FC_ExtractVar(tempPower);
            itsLaneTransmittedPower.push_back(tempPower);
        }
        for (i = 0; i < itsNumOfLanes;i++)
        {
            theStream >> FC_ExtractVar(tempPower);
            itsLaneReceivedPower.push_back(tempPower);
        }
    }
    theStream >> FC_ExtractVar(itsOptActualGain);
    theStream >> FC_ExtractVar(itsLaserBiasCurrentAbsolute);
    theStream >> FC_ExtractVar(itsLaserBiasCurrentPercent);
    theStream >> FC_ExtractVar(itsLaserTemperatureAbsolute);
    theStream >> FC_ExtractVar(itsLaserTemperatureError);
    theStream >> FC_ExtractVar(itsPrbsRxErrorCountHigh);
    theStream >> FC_ExtractVar(itsPrbsRxErrorCountLow);
    theStream >> FC_ExtractVar(itsPrbsRxErrorTime);
    theStream >> FC_ExtractVar(itsPrbsRxLosync);
    theStream >> FC_ExtractVar(itsOpticalReturnLoss);
    theStream >> FC_ExtractVar(itsIsDualOcmPresent);
    theStream >> FC_ExtractVar(itsChromaticDispersion);
    theStream >> FC_ExtractVar(itsDifferentialGroupDelay);
    theStream >> FC_ExtractVar(its2ndOrderPolarModeDispersion);
    theStream >> FC_ExtractVar(itsStateOfPolarization);
    theStream >> FC_ExtractVar(itsPolarDependentLoss);
    theStream >> FC_ExtractVar(itsQvalue);
    theStream >> FC_ExtractVar(itsCarrierFrequencyOffset);
    theStream >> FC_ExtractVar(itsSignalNoiseRatio);
    theStream >> FC_ExtractVar(itsYCableRxMessage);
    theStream >> FC_ExtractVar(itsMapMaskSet);
    theStream >> FC_ExtractVar(itsConnectionMap);

    // Configuration
    theStream >> FC_ExtractVar(itsLaserEnable);
    theStream >> FC_ExtractVar(itsFacLoop);
    theStream >> FC_ExtractVar(itsTerLoop);
    theStream >> FC_ExtractVar(itsALS);
    theStream >> FC_ExtractVar(itsConsiderAISforALS);
    theStream >> FC_ExtractVar(itsNeALS);
    theStream >> FC_ExtractVar(itsOutputPower);
    theStream >> FC_ExtractVar(itsBitRate);
    theStream >> FC_ExtractVar(otnMode);
    theStream >> FC_ExtractVar(itsTxTraceID);
    theStream >> FC_ExtractVar(itsPilotToneFreq);
    theStream >> FC_ExtractVar(itsTxPTAmplitude);
    theStream >> FC_ExtractVar(itsTxPTAmpliRatio);
    theStream >> FC_ExtractVar(itsWavelength);
    theStream >> FC_ExtractVar(itsFrequency);
    theStream >> FC_ExtractVar(aBand);
    theStream >> FC_ExtractVar(aPlan);
    theStream >> FC_ExtractVar(itsLOSThreshold);
    theStream >> FC_ExtractVar(aMode);
    theStream >> FC_ExtractVar(itsSfpRouteMiddle);
    theStream >> FC_ExtractVar(itsPrbsTxEnable);
    theStream >> FC_ExtractVar(itsPrbsRxEnable);
    theStream >> FC_ExtractVar(itsPrbsRxSessionCounter);
    theStream >> FC_ExtractVar(itsAlsDelay);
    theStream >> FC_ExtractVar(itsYCableProtectionEnable);
    theStream >> FC_ExtractVar(itsYCableTxMessage);
    theStream >> FC_ExtractVar(aClockType);
    theStream >> FC_ExtractVar(aOTIDStatus);
    theStream >> FC_ExtractVar(itsFefiForced);
    theStream >> FC_ExtractVar(itsMateChannelEnable);
    theStream >> FC_ExtractVar(itsMateChannelSlotId);
    theStream >> FC_ExtractVar(itsMateChannelPortId);
    theStream >> FC_ExtractVar(itsDwdmFault);
    theStream >> FC_ExtractVar(itsUpdatePeriod);
    theStream >> FC_ExtractVar(aPrbsFormat);

    theStream >> FC_ExtractVar(itsMaxTxPTAmplitude);
    theStream >> FC_ExtractVar(itsMinTxPTAmplitude);
    theStream >> FC_ExtractVar(itsAmpliRatioNeeded);
    theStream >> FC_ExtractVar(itsTargetPowerBoost);
    theStream >> FC_ExtractVar(itsPowerTolerance);
    theStream >> FC_ExtractVar(itsMaxTxPTAmpliRatio);
    theStream >> FC_ExtractVar(itsMinTxPTAmpliRatio);

    // Availability
    theStream >> FC_ExtractVar(itsTxPilotToneControlSupported);
    theStream >> FC_ExtractVar(itsOpticalPowerReceivedSupported);
    theStream >> FC_ExtractVar(itsOpticalPowerTransmittedSupported);
    theStream >> FC_ExtractVar(itsOpticalPowerTransmittedByPeerSupported);
    theStream >> FC_ExtractVar(itsLanePowerSupported);
    theStream >> FC_ExtractVar(itsOpticalActualGainSupported);
    

    // Update H/W
    itsBand         = (CT_TEL_OpticalWaveLength)aBand;
    itsPlan         = (CT_TEL_FreqencyPlan)aPlan;
    itsOEORegenMode = (CT_TEL_OEO_REGEN_MODE)aMode;
    itsOTNMode      = (CT_TEL_OTNMode)otnMode;
    itsClockType    = (CT_TEL_ClkType)aClockType;
    itsOTIDStatus   = (CT_TEL_OTIDStatus)aOTIDStatus;
    itsPrbsFormat   = (CT_TEL_PrbsFormat)aPrbsFormat;
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();
    uint i;
    vector<CT_TEL_mBm>::iterator aIter;
    CT_TEL_mBm    tempPower;

    theStream << "  Optical Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Laser Enable          = " << TEXT_ON_OFF(itsLaserEnable)                    << "\n";
    theStream << "      FacilityLoopback      = " << TEXT_ON_OFF(itsFacLoop)                        << "\n";
    theStream << "      TerminalLoopback      = " << TEXT_ON_OFF(itsTerLoop)                        << "\n";
    theStream << "      Auto Laser Shutdown   = " << TEXT_ON_OFF(itsALS)                            << "\n";
    theStream << "      Consider AIS for ALS  = " << TEXT_ON_OFF(itsConsiderAISforALS)                            << "\n";
    theStream << "      NE Auto Laser Shutdown= " << TEXT_ON_OFF(itsNeALS)                          << "\n";
    theStream << "      FEFI Forced           = " << TEXT_ON_OFF(itsFefiForced)                     << "\n";
    theStream << "      DWDM Fault            = " << TEXT_ON_OFF(itsDwdmFault)                      << "\n";
    theStream << "      Output Power          = " << itsOutputPower                                 << " mBm\n";
    theStream << "      Bit Rate              = " << itsBitRate                                     << " daHz\n";
    theStream << "      OTN Mode              = " << DISPLAY_OTN_MODE(itsOTNMode)                   << "\n";
    theStream << "      Tx Pilot Tone TraceID = " << itsTxTraceID                                   << "\n";
    theStream << "      Tx Pilot Tone Freq    = " << itsPilotToneFreq                               << " Hz\n";

    if (IsTxPilotToneControlSupported())
    {
        theStream << "      Pilot Tone Amplitude  = " << itsTxPTAmplitude                               << "\n";
        theStream << "      Pilot Tone Ampli Ratio= " << itsTxPTAmpliRatio                              << "\n";
    }
    theStream << "      Wavelength            = " << itsWavelength                                  << "\n";
    theStream << "      Frequency             = " << itsFrequency                                   << "\n";
    theStream << "      Band                  = " << DISPLAY_BAND(itsBand)                          << " nm\n";
    theStream << "      Freq Plan             = " << DISPLAY_FREQ_PLAN(itsPlan)                     << "\n";
    theStream << "      LOS Power Threshold   = " << itsLOSThreshold                                << " mBm\n";
    theStream << "      OEO Regen             = " << DISPLAY_OEO_REGEN_MODE(itsOEORegenMode)        << "\n";
    theStream << "      PRBS Tx Enable        = " << TEXT_ON_OFF(itsPrbsTxEnable)                   << "\n";
    theStream << "      PRBS Rx Enable        = " << TEXT_ON_OFF(itsPrbsRxEnable)                   << "\n";
    theStream << "      PRBS Rx Session Counter = " << itsPrbsRxSessionCounter                      << "\n";
    theStream << "      ALS Delay             = " << itsAlsDelay                                    << "\n";
    theStream << "      Y-Cable Prot Enable   = " << TEXT_ON_OFF(itsYCableProtectionEnable)         << "\n";
    theStream << "      Y-Cable Tx Message    = 0x" << hex << static_cast<uint16>(itsYCableTxMessage) << dec << "\n";
    theStream << "      Y-Cable Mate Channel  = " << TEXT_ON_OFF(itsMateChannelEnable)              << "\n";
    theStream << "      Y-Cable Mate Channel-S= " << itsMateChannelSlotId                           << "\n";
    theStream << "      Y-Cable Mate Channel-P= " << itsMateChannelPortId + 1                       << "\n";
    theStream << "      Clock Type            = " << DISPLAY_CLOCK_TYPE(itsClockType)               << "\n";
    theStream << "      OTID Status            = " << DISPLAY_OTID_STATUS(itsOTIDStatus)            << "\n";
    theStream << "      Update Period (msecs) = " << itsUpdatePeriod                                << "\n";
    theStream << "      Prbs Format            = "<< DISPLAY_PRBS_FORMAT(itsPrbsFormat)             << "\n";

    theStream << "    MONITORING " << "\n";

    theStream << "      Laser State           = " << TEXT_ON_OFF(itsLaserState)                     << "\n";
    theStream << "      Opt LOS Defect        = " << TEXT_DEFECT(itsLOS)                            << "\n";
    theStream << "      Loss of CLK Defect    = " << TEXT_DEFECT(itsLossOfClock)                    << "\n";
    theStream << "      PRBS Rx Losync        = " << TEXT_DEFECT(itsPrbsRxLosync)                   << "\n";
    theStream << "      Optical Power TX      = " << itsOptPowerTransmitted                         << " mBm\n";
    if (itsOptPowerReceived > MAX_POWER_VALID || itsOptPowerReceived < MIN_POWER_VALID || !itsOpticalPowerReceivedSupported)
    {
        theStream << "      Optical Power RX      = INVALID INPUT POWER\n";
        theStream << "      Optical Power RX Min  = INVALID INPUT POWER\n";
        theStream << "      Optical Power RX Max  = INVALID INPUT POWER\n";
    }
    else
    {
        theStream << "      Optical Power RX      = " << itsOptPowerReceived                            << " mBm\n";
    }
    if (itsOptPowerTransmittedByPeer > MAX_POWER_VALID || itsOptPowerTransmittedByPeer < MIN_POWER_VALID || !itsOpticalPowerTransmittedByPeerSupported)
    {
        theStream << "      Optical Pwr TX By Peer= INVALID INPUT POWER\n";
    }
    else
    {
        theStream << "      Optical Pwr TX By Peer= " << itsOptPowerTransmittedByPeer                   << " mBm\n";
    }
    if (itsOptPowerTransmittedToPeer > MAX_POWER_VALID || itsOptPowerTransmittedToPeer < MIN_POWER_VALID || !itsOpticalPowerTransmittedByPeerSupported)
    {
        theStream << "      Optical Pwr TX To Peer= INVALID INPUT POWER\n";
    }
    else
    {
        theStream << "      Optical Pwr TX To Peer= " << itsOptPowerTransmittedToPeer                   << " mBm\n";
    }
    if (itsOmsPowerTransmittedByPeer > MAX_VALID_OMS_POWER || itsOmsPowerTransmittedByPeer < MIN_POWER_VALID || !itsOpticalPowerTransmittedByPeerSupported)
    {
        theStream << "      Oms Pwr TX By Peer    = INVALID INPUT POWER\n";
    }
    else
    {
        theStream << "      Oms Pwr TX By Peer    = " << itsOmsPowerTransmittedByPeer                   << " mBm\n";
    }
    if (itsOmsPowerTransmittedToPeer > MAX_VALID_OMS_POWER || itsOmsPowerTransmittedToPeer < MIN_POWER_VALID || !itsOpticalPowerTransmittedByPeerSupported)
    {
        theStream << "      Oms Pwr TX To Peer    = INVALID INPUT POWER\n";
    }
    else
    {
        theStream << "      Oms Pwr TX To Peer    = " << itsOmsPowerTransmittedToPeer                   << " mBm\n";
    }
    if (itsOmsPowerTransmitted > MAX_VALID_OMS_POWER || itsOmsPowerTransmitted < MIN_POWER_VALID || !itsOpticalPowerTransmittedByPeerSupported)
    {
        theStream << "      Oms Pwr TX            = INVALID INPUT POWER\n";
    }
    else
    {
        theStream << "      Oms Pwr TX            = " << itsOmsPowerTransmitted                         << " mBm\n";
    }
    if (itsLanePowerSupported)
    {
        theStream << "      Lowest  Lane RX Power = " << itsLaneLowReceivedPower                        << " mBm\n";
        theStream << "      Highest Lane RX Power = " << itsLaneHighReceivedPower                       << " mBm\n";
        theStream << "      Lowest  Lane TX Power = " << itsLaneLowTransmittedPower                     << " mBm\n";
        theStream << "      Highest Lane TX Power = " << itsLaneHighTransmittedPower                    << " mBm\n";
        i = 0;
        for(aIter=itsLaneReceivedPower.begin(); aIter != itsLaneReceivedPower.end(); ++aIter)
        {
            tempPower = (*aIter);
            theStream << "      Lane[" << i << "] RX Power = " << tempPower         << " mBm\n";
            i++;
        }
        i = 0;
        for(aIter=itsLaneTransmittedPower.begin(); aIter != itsLaneTransmittedPower.end(); ++aIter)
        {
            tempPower = (*aIter);
            theStream << "      Lane[" << i << "] TX Power = " << tempPower         << " mBm\n";
            i++;
        }
    }
    if (itsOpticalActualGainSupported)
    {
        theStream << "      Optical Actual Gain   = " << itsOptActualGain                               << " mBm\n";    
    }
    
    theStream << "      Laser Bias Curr. Abs. = " << itsLaserBiasCurrentAbsolute                    << " uAmps\n";
    theStream << "      Laser Bias Curr.      = " << itsLaserBiasCurrentPercent                     << " %\n";
    theStream << "      Laser Temperature Abs = " << itsLaserTemperatureAbsolute                    << " milliCelsius\n";
    theStream << "      Laser Temperature     = " << itsLaserTemperatureError                       << " milliCelsius from Nominal\n";
    theStream << "      PRBS Rx Errors        = " << itsPrbsRxErrorCountHigh << ", " << itsPrbsRxErrorCountLow << " \n";
    theStream << "      PRBS Rx Time          = " << itsPrbsRxErrorTime                             << " milliSeconds\n";
    theStream << "      Optical Return Loss   = " << itsOpticalReturnLoss                           << " mBm\n";
    theStream << "      Dual OCM Present      = " << TEXT_ON_OFF(itsIsDualOcmPresent)               << "\n";
    theStream << "      Chromatic Dispersion  = " << itsChromaticDispersion                         << " ps per nm\n";
    theStream << "      Differ Group Delay    = " << itsDifferentialGroupDelay                      << " ps\n";
    theStream << "      2 Ord Polar Mode Disp = " << its2ndOrderPolarModeDispersion                 << " ps squared\n";
    theStream << "      State Of Polarization = " << itsStateOfPolarization                         << " rad/s\n";
    theStream << "      Polar Dependent Loss  = " << itsPolarDependentLoss                          << " mBm\n";
    theStream << "      Q value               = " << itsQvalue                                      << " mBm\n";
    theStream << "      Carrier Freq Offset   = " << itsCarrierFrequencyOffset                      << " mHz\n";
    theStream << "      Signal-to-Noise Ratio = " << itsSignalNoiseRatio                            << " mBm\n";
    theStream << "      Y-Cable Rx Message    = 0x" << hex << static_cast<uint16>(itsYCableRxMessage) << dec << "\n";
    theStream << "      Connection MapMask set= " << TEXT_ON_OFF(itsMapMaskSet)                       << "\n";
    theStream << "      Connection Mapping    = 0x" << hex << static_cast<uint16>(itsConnectionMap)      << dec << "\n";
    theStream << "    AVAILABILITY\n";
    theStream << "      Tx PT ampl. control   = " << TEXT_ON_OFF(itsTxPilotToneControlSupported)    << "\n";
    theStream << "      Opt Power Rx avail.   = " << TEXT_ON_OFF(itsOpticalPowerReceivedSupported)  << endl;
    theStream << "      Opt Power Tx avail.   = " << TEXT_ON_OFF(itsOpticalPowerTransmittedSupported)  << endl;
    theStream << "      Opt Pwr Peer Tx avail = " << TEXT_ON_OFF(itsOpticalPowerTransmittedByPeerSupported)  << endl;
    theStream << "      Lane Opt Power avail  = " << TEXT_ON_OFF(itsLanePowerSupported)  << endl;
    theStream << "      Opt Actual Gain avail = " << TEXT_ON_OFF(itsOpticalActualGainSupported)  << endl;
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::Set(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "laser") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetLaserEnable(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetLaserEnable(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "facloop") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetFacilityLoopbackEnable(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetFacilityLoopbackEnable(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "terloop") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetTerminalLoopbackEnable(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetTerminalLoopbackEnable(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "als") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetAutomaticLaserShutdown(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetAutomaticLaserShutdown(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strncmp(argv[0], "aisforals", 4) == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetConsiderAISforALS(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetConsiderAISforALS(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "alsdelay") == 0)
    {
        uint32 delay = strtoul(argv[1], NULL, 0);
        SetAlsHoldOffDelay(delay);
    }
    else if (argc == 2 && strcmp(argv[0], "neals") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetNearEndAutomaticLaserShutdown(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetNearEndAutomaticLaserShutdown(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "outpwr") == 0)
    {
        uint32 tmp = strtoul(argv[1], NULL, 0);
        SetOutputPower(tmp);
    }
    else if (argc == 2 && strcmp(argv[0], "bitrate") == 0)
    {
        CT_TEL_daHz bitrate = strtoul(argv[1], NULL, 0);
        SetBitRate(bitrate);
    }
    else if (argc == 2 && strcmp(argv[0], "otnmode") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_OTN_MODE_G709; i++) if (strcmp(argv[1], DISPLAY_OTN_MODE(i)) == 0)
        {
            SetOTNMode((CT_TEL_OTNMode)i);
            printUsage = false;
            break;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "txtraceid") == 0)
    {
        CT_TEL_PilotToneID txtraceid = strtoul(argv[1], NULL, 0);
        SetTxTraceID(txtraceid);
    }
    else if (argc == 2 && strcmp(argv[0], "txpt") == 0)
    {
        CT_TEL_Hz ptfreq = strtoul(argv[1], NULL, 0);
        SetTxPilotTone(ptfreq);
    }
    else if (argc == 2 && strcmp(argv[0], "txptampl") == 0)
    {
        uint32 ptampl = strtoul(argv[1], NULL, 0);
        SetTxPTAmplitude(ptampl);
    }
    else if (argc == 2 && strcmp(argv[0], "txptampratio") == 0)
    {
        float ptamprat = static_cast<float>(atof(argv[1]));
        SetTxPTAmpliRatio(ptamprat);
    }
    else if (argc == 2 && strcmp(argv[0], "wavelength") == 0)
    {
        uint32 wavelength = strtoul(argv[1], NULL, 0);
        SetWavelength(wavelength);
    }
    else if (argc == 2 && strcmp(argv[0], "frequency") == 0)
    {
        uint32 frequency = strtoul(argv[1], NULL, 0);
        SetFrequency(frequency);
    }
    else if (argc == 2 && strcmp(argv[0], "band") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_TEL_15xx_NM; i++) if (strcmp(argv[1], DISPLAY_BAND(i)) == 0)
        {
            SetBand((CT_TEL_OpticalWaveLength)i);
            printUsage = false;
            break;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "plan") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_TEL_UNKNOWN_PLAN; i++) if (strcmp(argv[1], DISPLAY_FREQ_PLAN(i)) == 0)
        {
            SetFreqPlan((CT_TEL_FreqencyPlan)i);
            printUsage = false;
            break;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "losthresh") == 0)
    {
        uint32 tmp = strtoul(argv[1], NULL, 0);
        SetLOSThreshold(tmp);
    }
    else if (argc == 2 && strcmp(argv[0], "oeoregen") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_TEL_OEO_REGEN_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_OEO_REGEN_MODE(i)) == 0)
        {
            SetOEORegenMode((CT_TEL_OEO_REGEN_MODE)i);
            printUsage = false;
            break;
        }
    }

    else if (argc == 2 && strcmp(argv[0], "prbstx") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetPrbsTxEnable(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetPrbsTxEnable(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "prbsrx") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetPrbsRxEnable(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetPrbsRxEnable(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "txptamplmax") == 0)
    {
        itsManualPtAmplMax = static_cast<uint16>(strtoul(argv[1], NULL, 0));
    }
    else if(argc == 2 && strcmp(argv[0], "ycableprot") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetYCableProtectionEnable(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetYCableProtectionEnable(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ycabletx") == 0)
    {
        SetTxYCableMessage(static_cast<uint8>(strtoul(argv[1], NULL, 0)));
    }
    else if (argc == 2 && strcmp(argv[0], "connectionmap") == 0)
    {
        SetConnectionMap(static_cast<uint16>(strtoul(argv[1], NULL, 0)));
    }
    else if(argc == 2 && strcmp(argv[0], "clktype") == 0)
    {
        if (strcmp(argv[1], "G709") == 0)
        {
            SetClockType(CT_TEL_CLK_G709);
        }
        else if (strcmp(argv[1], "OVRCLKFS") == 0)
        {
            SetClockType(CT_TEL_CLK_OVRCLKFS);
        }
        else if (strcmp(argv[1], "UNKNOWN") == 0)
        {
            SetClockType(CT_TEL_CLK_UNKNOWN);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "OTID") == 0)
    {
        if (strcmp(argv[1], "Disabled") == 0)
        {
            SetOTIDStatus(CT_TEL_OTID_DISABLED);
        }
        else if (strcmp(argv[1], "Enabled") == 0)
        {
            SetOTIDStatus(CT_TEL_OTID_ENABLED);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "forcefefi") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetFefiForced(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetFefiForced(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ycablemate") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            SetMateChannelEnabled(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            SetMateChannelEnabled(true);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ycablemateslot") == 0)
    {
        uint16 slot = static_cast<uint16>(atoi(argv[1]));
        SetMateChannelSlotId(slot);
    }
    else if (argc == 2 && strcmp(argv[0], "ycablemateport") == 0)
    {
        uint16 port = static_cast<uint16>(atoi(argv[1]));
        SetMateChannelPortId(port);
    }    
    else if(argc == 2 && strcmp(argv[0], "dwdmfault") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetDwdmFault(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetDwdmFault(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "prbsformat") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_TEL_PRBS_FIXEDSTUFF; i++) 
        {
            if (strcmp(argv[1], DISPLAY_PRBS_FORMAT(i)) == 0)
            {
                SetPrbsFormat((CT_TEL_PrbsFormat)i);
                printUsage = false;
                break;
            }
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);;
    }
    if (printUsage)
    {
        fc_cout << "    laser           <on|off>\n"
                   "    als             <on|off>\n"
                   "    aisforals       <on|off>\n"
                   "    alsdelay        <0-2000 ms>\n"
                   "    neals           <on|off>\n"
                   "    forcefefi       <on|off>\n"
                   "    facloop         <on|off>\n"
                   "    terloop         <on|off>\n"
                   "    outpwr          <mBm>\n"
                   "    bitrate         <daHz>\n"
                   "    otnmode         <NONE|G709>\n"
                   "    wavelength      <0-(plan size - 1>\n"
                   "    frequency       <0-(19135-19610>\n"
                   "    band            <1310|15xx>\n"
                   "    plan            <44BSTCHAN|44CHAN|88CHAN|UNKNOWN>\n"
                   "    losthresh       <mBm>\n"
                   "    oeoregen        <OFF|ON|NON|LMATE|LLOOP|UNKNOWN>\n"
                   "    prbstx          <on|off>\n"
                   "    prbsrx          <on|off>\n"
                   "    txtraceid       <0-656>\n"
                   "    txpt            <Hz>\n"
                   "    txptampl        <0-255>\n"
                   "    txptampratio    <0.0-12.5>\n"
                   "    txptamplmax     <0-4095> (0 for default)\n"
                   "    ycableprot      <on|off>\n"
                   "    ycabletx        <message>\n"
                   "    ycablemate      <on|off>\n"
                   "    ycablemateslot  <slotId>\n"
                   "    ycablemateport  <portId>\n"
                   "    connectionmap   <mapMask>\n"
                   "    clktype         <G709|OVRCLKFS|UNKNOWN>\n"
                   "    OTIDStatus      <Disabled|Enabled|UNKNOWN>\n"
                   "    dwdmfault       <on|off>\n"
                   "    prbsformat      <G709|FIXEDSTUFF>\n"
                   << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OpticalIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "lasermon") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsLaserState = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsLaserState = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "los") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLOS)) itsLOS++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLOS)) itsLOS++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "losclk") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLossOfClock)) itsLossOfClock++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLossOfClock)) itsLossOfClock++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "opr") == 0)
    {
        itsOptPowerReceived = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "opt") == 0)
    {
        itsOptPowerTransmitted = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "optbypeer") == 0)
    {
        itsOptPowerTransmittedByPeer = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "opttopeer") == 0)
    {
        itsOptPowerTransmittedToPeer = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "omsbypeer") == 0)
    {
        itsOmsPowerTransmittedByPeer = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "omstopeer") == 0)
    {
        itsOmsPowerTransmittedToPeer = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "omstx") == 0)
    {
        itsOmsPowerTransmitted = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "lanelowrx") == 0)
    {
        itsLaneLowReceivedPower = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "lanehighrx") == 0)
    {
        itsLaneHighReceivedPower = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "lanelowtx") == 0)
    {
        itsLaneLowTransmittedPower = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "lanehightx") == 0)
    {
        itsLaneHighTransmittedPower = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "numlanes") == 0)
    {
        itsNumOfLanes = strtol(argv[1], NULL, 0);
        if(itsLaneTransmittedPower.size() > 0)
        {
            itsLaneTransmittedPower.clear();
        }
        if(itsLaneReceivedPower.size() > 0)
        {
            itsLaneReceivedPower.clear();
        }

        for(uint i = 0; i < itsNumOfLanes;i++)
        {
            itsLaneReceivedPower.push_back(TRAFFIC_DEFAULT_POWER);
            itsLaneTransmittedPower.push_back(TRAFFIC_DEFAULT_POWER);
        }
    }
    else if (argc == 3 && strcmp(argv[0], "lanetx") == 0)
    {
        uint32 i;
        i = strtol(argv[1], NULL, 0);
        if(i < itsLaneTransmittedPower.size())
        {
            itsLaneTransmittedPower[i] = strtol(argv[2], NULL, 0);
        }
        else
        {
            fc_cout << "Max number of lanes is " << itsNumOfLanes;
            fc_cout << ", Use 'tspii simopt port <n> numlanes <n>' option to change" << endl;
        }
    }
    else if (argc == 3 && strcmp(argv[0], "lanerx") == 0)
    {
        uint32 i;
        i = strtol(argv[1], NULL, 0);
        if(i < itsLaneReceivedPower.size())
        {
            itsLaneReceivedPower[i] = strtol(argv[2], NULL, 0);
        }
        else
        {
            fc_cout << "Max number of lanes is " << itsNumOfLanes << endl;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "optactgain") == 0)
    {
        itsOptActualGain = strtoul(argv[1], NULL, 0);
    } 
    else if (argc == 2 && strcmp(argv[0], "lsrbiasabs") == 0)
    {
        itsLaserBiasCurrentAbsolute = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "lsrbias") == 0)
    {
        itsLaserBiasCurrentPercent = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "lsrtempabs") == 0)
    {
        itsLaserTemperatureAbsolute = strtol(argv[1], NULL, 0);
        itsLaserTemperatureError    = itsLaserTemperatureAbsolute - TRAFFIC_DEFAULT_TEMP;
    }
    else if (argc == 2 && strcmp(argv[0], "prbsrxlosync") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsPrbsRxLosync)) itsPrbsRxLosync++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsPrbsRxLosync)) itsPrbsRxLosync++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 3 && strcmp(argv[0], "prbsrxerrs") == 0)
    {
        itsPrbsRxErrorCountHigh = strtoul(argv[1], NULL, 0);
        itsPrbsRxErrorCountLow = strtoul(argv[2], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "prbsrxtime") == 0)
    {
        itsPrbsRxErrorTime = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "dualocmpresent") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsIsDualOcmPresent = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsIsDualOcmPresent = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ptamplavail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsTxPilotToneControlSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsTxPilotToneControlSupported = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "oppeertxavail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsOpticalPowerTransmittedByPeerSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsOpticalPowerTransmittedByPeerSupported = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "laneavail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsLanePowerSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsLanePowerSupported = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "opravail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsOpticalPowerReceivedSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsOpticalPowerReceivedSupported = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "optavail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsOpticalPowerTransmittedSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsOpticalPowerTransmittedSupported = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "gainavail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsOpticalActualGainSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsOpticalActualGainSupported = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "retloss") == 0)
    {
        itsOpticalReturnLoss = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "chromdisper") == 0)
    {
        itsChromaticDispersion = static_cast<int32>(strtol(argv[1], NULL, 0));
    }
    else if (argc == 2 && strcmp(argv[0], "diffgrpdly") == 0)
    {
        itsDifferentialGroupDelay = static_cast<uint16>(strtoul(argv[1], NULL, 0));
    }
    else if (argc == 2 && strcmp(argv[0], "2orderpolar") == 0)
    {
        its2ndOrderPolarModeDispersion = static_cast<int16>(strtol(argv[1], NULL, 0));
    }
    else if (argc == 2 && strcmp(argv[0], "stateofpolar") == 0)
    {
        itsStateOfPolarization = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "polardeploss") == 0)
    {
        itsPolarDependentLoss = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "qvalue") == 0)
    {
        itsQvalue = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "carrierfreqoff") == 0)
    {
        itsCarrierFrequencyOffset = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "signalnoiseratio") == 0)
    {
        itsSignalNoiseRatio = strtol(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "ycablerx") == 0)
    {
        itsYCableRxMessage = static_cast<uint8>(strtoul(argv[1], NULL, 0));
    }
    else if (argc == 2 && strcmp(argv[0], "connectionmap") == 0)
    {
        itsMapMaskSet    = true;
        itsConnectionMap = static_cast<uint16>(strtoul(argv[1], NULL, 0));
    }
    else if (argc == 2 && strcmp(argv[0], "clktype") == 0)
    {
        if (strcmp(argv[1], "G709") == 0)
        {
            itsClockType = CT_TEL_CLK_G709;
        }
        else if (strcmp(argv[1], "OVRCLKFS") == 0)
        {
            itsClockType = CT_TEL_CLK_OVRCLKFS;
        }
        else if (strcmp(argv[1], "UNKNOWN") == 0)
        {
            itsClockType = CT_TEL_CLK_UNKNOWN;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "OTID") == 0)
    {
        if (strcmp(argv[1], "Disabled") == 0)
        {
            itsOTIDStatus = CT_TEL_OTID_DISABLED;
        }
        else if (strcmp(argv[1], "Enabled") == 0)
        {
            itsOTIDStatus = CT_TEL_OTID_ENABLED;
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    lasermon         <on|off>\n"
                   "    los              <on|off>\n"
                   "    losclk           <on|off>\n"
                   "    opr              <mBm>\n"
                   "    opt              <mBm>\n"
                   "    optbypeer        <mBm>\n"
                   "    opttopeer        <mBm>\n"
                   "    omsbypeer        <mBm>\n"
                   "    omstopeer        <mBm>\n"
                   "    omstx            <mBm>\n"
                   "    lanelowrx        <mBm>\n"
                   "    lanehighrx       <mBm>\n"
                   "    lanelowtx        <mBm>\n"
                   "    lanehightx       <mBm>\n"
                   "    numlanes         <uint32>\n"
                   "    lanetx           <lane number> <mBm>\n"
                   "    lanerx           <lane number> <mBm>\n"
                   "    optactgain       <mBm>\n"
                   "    lsrbiasabs       <uA>\n"
                   "    lsrbias          <%>\n"
                   "    lsrtempabs       <mC>\n"
                   "    prbsrxlosync     <on|off>\n"
                   "    prbsrxerrs       <counth countl>\n"
                   "    prbsrxtime       <time>\n"
                   "    ptamplavail      <on|off>\n"
                   "    oppeertxavail    <on|off>\n"
                   "    optavail         <on|off>\n"
                   "    opravail         <on|off>\n"
                   "    laneavail        <on|off>\n"
                   "    gainavail        <on|off>\n"
                   "    retloss          <mBm>\n"
                   "    dualocmpresent   <on|off>\n"
                   "    chromdisper      <ps-per-nm>\n"
                   "    diffgrpdly       <ps>\n" 
                   "    2orderpolar      <ps2>\n" 
                   "    stateofpolar     <rad/s>\n" 
                   "    polardeploss     <mBm>\n"
                   "    qvalue           <mBm>\n"
                   "    carrierfreqoff   <mHz>\n"
                   "    signalnoiseratio <mBm>\n"
                   "    ycablerx         <message>\n"
                   "    connectionmap    <16 bit mask>\n"
                   "    clktype          <G709|OVRCLKFS|UNKNOWN>\n"
                   "    OTIDStatus       <Disabled|Enabled|UNKNOWN>\n" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OpticalIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
