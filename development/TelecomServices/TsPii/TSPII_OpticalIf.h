#ifndef _TSPII_OPTICALIF_H
#define _TSPII_OPTICALIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Eric Bernier November 30th 2001
 DESCRIPTION:Base class for the hardware independent interface.
             Provides the interface for optical layer
--------------------------------------------------------------------------*/

#define TSPII_OPT_PRBS_DELAY          (2000)     // Number of milliseconds to wait before
                                                 // considering PRBS info valid.

// new constants for Pilot Tone - when the DQPSK (and a new way of doing things) was introduced 
const bool   TSPII_OPT_PT_AMPLI_RATIO_NEEDED    = false;
const float  TSPII_OPT_PT_MIN_AMPLI_RATIO       = 0.0;
const float  TSPII_OPT_PT_MAX_AMPLI_RATIO       = 12.5;
const float  TSPII_OPT_PT_TARGET_POWER_BOOST    = 20.0;
const float  TSPII_OPT_PT_POWER_TOLERANCE       = 0.5;

#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_SignalProtection.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_UpdateAction.h"

class TSPII_OpticalIf : public TSPII_BaseIf
{
    friend class SP_FsmTestParser;

public:

    /* Constructor */            TSPII_OpticalIf(bool theDefault                       = false,
                                                 bool theTxPilotToneControlSupported   = true,
                                                 bool theOpticalPowerReceivedSupported = true,
                                                 bool theOpticalPowerTransmittedSupported = false,
                                                 bool theOpticalPowerTransmittedByPeerSupported = false,
                                                 bool theOpticalActualGainSupported = false,
                                                 bool theLanePowerSupported = false);
    virtual                      ~TSPII_OpticalIf();
    virtual void                 Reset();

    // -----------------------------------------------------------------------------------
    // Optical Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual bool                GetLaserState();
    virtual uint32              GetOptLOS();

    //DEPRECATED!!! DO NOT USE IN FUTURE LINE CARDS
    //LOSS OF CLOCK SHOULD BE REPORTED AS PART OF RS LOF INDICATION
    virtual uint32              GetLossOfClock();


    virtual CT_TEL_mBm          GetOpticalPowerReceived();
    virtual CT_TEL_mBm          GetOpticalPowerTransmitted();
    virtual CT_TEL_mBm          GetOpticalPowerTransmittedByPeer();
    virtual CT_TEL_mBm          GetOpticalPowerTransmittedToPeer();
    virtual CT_TEL_mBm          GetOmsPowerTransmittedByPeer();
    virtual CT_TEL_mBm          GetOmsPowerTransmittedToPeer();
    virtual CT_TEL_mBm          GetOmsPowerTransmitted();
    virtual CT_TEL_mBm          GetLaneLowReceivedPower();
    virtual CT_TEL_mBm          GetLaneHighReceivedPower();
    virtual vector<CT_TEL_mBm>& GetLaneReceivedPower();
    virtual CT_TEL_mBm          GetLaneLowTransmittedPower();
    virtual CT_TEL_mBm          GetLaneHighTransmittedPower();
    virtual vector<CT_TEL_mBm>& GetLaneTransmittedPower();
    virtual CT_TEL_uAmps        GetLaserBiasCurrentAbsolute();
    virtual CT_TEL_Percent      GetLaserBiasCurrent();
    virtual CT_TEL_milliCelcius GetLaserTemperatureAbsolute();
    virtual CT_TEL_milliCelcius GetLaserTemperature();
    virtual uint32              GetPrbsRxLosync();
    virtual bool                GetPrbsRxErrors(uint32 & theCountHigh, uint32 & theCountLow, uint32 & theTime);
    virtual CT_TEL_mBm          GetOpticalReturnLoss();
    virtual CT_TEL_mBm          GetOpticalActualGain();
    virtual bool                GetIsDualOcmPresent();
    // Dispersion compensation interfaces
    virtual int32               GetChromaticDispersion();
    virtual uint16              GetDifferentialGroupDelay();
    virtual uint16              Get2ndOrderPolarModeDispersion();
    virtual uint32              GetStateOfPolarization();
    virtual CT_TEL_mBm          GetPolarDependentLoss();
    virtual CT_TEL_mBm          GetQvalue();
    virtual CT_TEL_mBm          GetCarrierFrequencyOffset();
    virtual CT_TEL_mBm          GetSignalNoiseRatio();
    virtual uint8               GetRxYCableMessage();
    virtual CT_TEL_ClkType      GetClockType();
    virtual CT_TEL_OTIDStatus   GetOTIDStatus();
    // -----------------------------------------------------------------------------------
    // Optical Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                SetLaserEnable(bool theLaserEnable);
    virtual void                SetFacilityLoopbackEnable(bool theEnable);
    virtual void                SetTerminalLoopbackEnable(bool theEnable);
    virtual void                SetAutomaticLaserShutdown(bool theState);
    virtual void                SetConsiderAISforALS(bool theState);
    virtual void                SetNearEndAutomaticLaserShutdown(bool theState);
    virtual void                SetOutputPower(CT_TEL_mBm theOutputPower);
    virtual void                SetBitRate(CT_TEL_daHz theBitRate);
    virtual void                SetOTNMode(CT_TEL_OTNMode theMode);
    virtual void                SetTxTraceID(CT_TEL_PilotToneID theTraceID);
    virtual void                SetTxPilotTone(CT_TEL_Hz theFrequency);
    virtual void                SetTxPTAmplitude(uint32 theAmplitude);
    virtual void                SetTxPTAmpliRatio(float theAmpliRatio);
    virtual void                SetWavelength(uint32 theWavelength);
    virtual void                SetFrequency(uint32 theFrequency);
    virtual void                SetBand(CT_TEL_OpticalWaveLength theBand);
    virtual void                SetFreqPlan(CT_TEL_FreqencyPlan thePlan);
    virtual void                SetLOSThreshold(CT_TEL_mBm theLOSThreshold);
    virtual void                SetOEORegenMode(CT_TEL_OEO_REGEN_MODE theMode);
    virtual void                SetPrbsTxEnable(bool theEnable);
    virtual void                SetPrbsRxEnable(bool theEnable);
    virtual void                SetPrbsRxSessionCounter(uint32 thePrbsRxSessionCounter);
    virtual void                SetOpticalPowerTransmittedToPeer();
    virtual void                SetOmsPowerTransmittedToPeer();
    virtual void                SetAlsHoldOffDelay(uint32 theDelay);
    virtual void                SetMaxTxPTAmplitude(uint16 theMaxTxPTAmplitude);
    virtual void                SetMinTxPTAmplitude(uint16 theMinTxPTAmplitude);
    virtual void                SetAmpliRatioNeeded(bool theAmpliRatioNeeded);
    virtual void                SetTargetPowerBoost(float theTargetPowerBoost);
    virtual void                SetPowerTolerance(float thePowerTolerance);
    virtual void                SetMaxTxPTAmpliRatio(float theMaxTxAmpliRatio);
    virtual void                SetMinTxPTAmpliRatio(float theMinTxPTAmpliRatio);
    virtual void                SetYCableProtectionEnable(bool theEnable);
    virtual void                SetTxYCableMessage(uint8 theMessage);
    virtual void                SetMateChannelEnabled(bool theEnable);
    virtual void                SetMateChannelSlotId(uint16 theSlotId);
    virtual void                SetMateChannelPortId(uint16 thePortId);
    virtual void                SetClockType(CT_TEL_ClkType theMode);
    virtual void                SetOTIDStatus(CT_TEL_OTIDStatus theOTIDStatus);
    virtual void                SetConnectionMap(uint16 theMap);
    virtual void                SetFefiForced(bool theForce);
    virtual void                SetDwdmFault(bool theEnable);
    virtual void                SetPrbsFormat(CT_TEL_PrbsFormat thePrbsFormat);
    virtual bool                GetLaserEnable() const;
    virtual bool                GetFacilityLoopbackEnable() const;
    virtual bool                GetTerminalLoopbackEnable() const;
    virtual bool                GetAutomaticLaserShutdown() const;
    virtual bool                GetConsiderAISforALS() const;
    virtual bool                GetNearEndAutomaticLaserShutdown() const;
    virtual CT_TEL_mBm          GetOutputPower() const;
    virtual CT_TEL_daHz         GetBitRate() const;
    virtual CT_TEL_OTNMode      GetOTNMode() const;
    virtual CT_TEL_PilotToneID  GetTxTraceID() const;
    virtual CT_TEL_Hz           GetTxPilotTone() const;
    virtual uint32              GetTxPTAmplitude() const;
    virtual float               GetTxPTAmpliRatio() const;
    virtual uint32              GetWavelength() const;
    virtual uint32              GetFrequency() const;
    virtual CT_TEL_OpticalWaveLength GetBand() const;
    virtual CT_TEL_FreqencyPlan GetFreqPlan() const;
    virtual CT_TEL_mBm          GetLOSThreshold() const;
    virtual CT_TEL_OEO_REGEN_MODE GetOEORegenMode() const;
    virtual bool                GetPrbsTxEnable() const;
    virtual bool                GetPrbsRxEnable() const;
    virtual uint32              GetPrbsRxSessionCounter() const;
    virtual uint32              GetAlsHoldOffDelay() const;
    virtual uint16              GetMaxTxPTAmplitude() const;
    virtual uint16              GetMinTxPTAmplitude() const;
    virtual bool                GetAmpliRatioNeeded() const;
    virtual float               GetTargetPowerBoost() const;
    virtual float               GetPowerTolerance() const;
    virtual float               GetMaxTxPTAmpliRatio() const;
    virtual float               GetMinTxPTAmpliRatio() const;
    virtual bool                GetYCableProtectionEnable() const;
    virtual uint8               GetTxYCableMessage() const;
    virtual bool                GetMateChannelEnabled() const;
    virtual uint16              GetMateChannelSlotId() const;
    virtual uint16              GetMateChannelPortId() const;
    virtual uint16              GetConnectionMap() const;
    virtual bool                GetFefiForced() const;
    virtual bool                GetDwdmFault() const;
    virtual CT_TEL_PrbsFormat   GetPrbsFormat() const;
	// debugging command for the fgtm tunable drift control
	virtual void                DebugDriftControlFilter(int argc, char ** argv);

    virtual void                SetUpdatePeriod(FC_Milliseconds theUpdatePeriod);
    virtual FC_Milliseconds     GetUpdatePeriod() const;

    virtual void                registerEventHandlers() {}

    // -----------------------------------------------------------------------------------
    // Availability Interfaces
    // -----------------------------------------------------------------------------------
    virtual bool                IsTxPilotToneControlSupported() const;
    virtual bool                IsOpticalPowerReceivedSupported() const;
    virtual bool                IsOpticalPowerTransmittedSupported() const;
    virtual bool                IsOpticalPowerTransmittedByPeerSupported() const;
    virtual bool                IsLanePowerSupported() const;
    virtual bool                IsOpticalActualGainSupported() const;
    virtual bool                IsMapMaskReady() const;

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &         WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &         ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   &         WriteObject(ostream & theStream);
    virtual istream   &         ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                Display(FC_Stream & theStream);
    virtual void                Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                Set(int argc, char ** argv);
    virtual bool                Simul(int argc, char ** argv);

protected:

    void                RefreshGet();
    void                RefreshSet();

    // Monitoring attributes
    bool                itsLaserState;
    uint32              itsLOS;
    uint32              itsLossOfClock;
    CT_TEL_mBm          itsOptPowerReceived;
    CT_TEL_mBm          itsOptPowerTransmitted;
    CT_TEL_mBm          itsOptPowerTransmittedByPeer;
    CT_TEL_mBm          itsOptPowerTransmittedToPeer;
    CT_TEL_mBm          itsOmsPowerTransmittedByPeer;
    CT_TEL_mBm          itsOmsPowerTransmittedToPeer;
    CT_TEL_mBm          itsOmsPowerTransmitted;
    CT_TEL_mBm          itsLaneLowReceivedPower;
    CT_TEL_mBm          itsLaneHighReceivedPower;
    vector<CT_TEL_mBm>  itsLaneReceivedPower;
    CT_TEL_mBm          itsLaneLowTransmittedPower;
    CT_TEL_mBm          itsLaneHighTransmittedPower;
    vector<CT_TEL_mBm>  itsLaneTransmittedPower;
    uint32              itsNumOfLanes;           // num of network lanes on CFP type devices
    CT_TEL_mBm          itsOptActualGain;    
    CT_TEL_uAmps        itsLaserBiasCurrentAbsolute;
    CT_TEL_Percent      itsLaserBiasCurrentPercent;
    CT_TEL_milliCelcius itsLaserTemperatureAbsolute;
    uint32              itsPrbsRxLosync;
    uint32              itsPrbsRxErrorCountHigh;
    uint32              itsPrbsRxErrorCountLow;
    uint32              itsPrbsRxErrorTime;
    CT_TEL_milliCelcius itsLaserTemperatureError;
    CT_TEL_mBm          itsOpticalReturnLoss;
    bool                itsIsDualOcmPresent;
    int32               itsChromaticDispersion;
    uint16              its2ndOrderPolarModeDispersion;
    uint32              itsStateOfPolarization;
    CT_TEL_mBm          itsPolarDependentLoss;
    CT_TEL_mBm          itsQvalue;
    CT_TEL_mBm          itsCarrierFrequencyOffset;
    CT_TEL_mBm          itsSignalNoiseRatio;
    uint16              itsDifferentialGroupDelay;
    uint8               itsYCableRxMessage;
    
    // Configuration attributes
    bool                itsLaserEnable;
    bool                itsFacLoop;
    bool                itsTerLoop;
    bool                itsALS;
    bool                itsConsiderAISforALS;
    bool                itsNeALS;
    CT_TEL_mBm          itsOutputPower;
    CT_TEL_daHz         itsBitRate;
    CT_TEL_OTNMode      itsOTNMode;
    CT_TEL_PilotToneID  itsTxTraceID;
    CT_TEL_Hz           itsPilotToneFreq;
    uint32              itsTxPTAmplitude;
    float               itsTxPTAmpliRatio;
    uint32              itsWavelength;
    uint32              itsFrequency;
    CT_TEL_OpticalWaveLength itsBand;
    CT_TEL_FreqencyPlan itsPlan;
    CT_TEL_mBm          itsLOSThreshold;
    CT_TEL_OEO_REGEN_MODE itsOEORegenMode;
    uint32              itsSfpRouteEnd;
    uint32              itsSfpRouteMiddle;
    bool                itsPrbsTxEnable;
    bool                itsPrbsRxEnable;
    uint32              itsPrbsRxSessionCounter;
    uint32              itsAlsDelay;
    bool                itsYCableProtectionEnable;
    uint8               itsYCableTxMessage;
    uint16              itsConnectionMap;    
    bool                itsFefiForced;
    bool                itsDwdmFault;
    bool                itsMateChannelEnable;
    uint16              itsMateChannelSlotId;
    uint16              itsMateChannelPortId;
    CT_TEL_PrbsFormat   itsPrbsFormat;

    FC_Milliseconds     itsUpdatePeriod;

    // Availability attributes.
    bool                itsTxPilotToneControlSupported;
    bool                itsOpticalPowerReceivedSupported;
    bool                itsOpticalPowerTransmittedSupported;
    bool                itsOpticalPowerTransmittedByPeerSupported;
    bool                itsLanePowerSupported;
    bool                itsOpticalActualGainSupported;
    bool                itsMapMaskSet;

    //Debug attributes
    uint16              itsManualPtAmplMax;

	//Max/Min DAC count
    bool                itsAmpliRatioNeeded;
	uint16				itsMaxTxPTAmplitude;
	uint16				itsMinTxPTAmplitude;
    float               itsTargetPowerBoost;
    float               itsPowerTolerance;
    float               itsMaxTxPTAmpliRatio;
    float               itsMinTxPTAmpliRatio;
    CT_TEL_ClkType      itsClockType;
    CT_TEL_OTIDStatus   itsOTIDStatus;
};
#endif // _TSPII_OPTICALIF_H
