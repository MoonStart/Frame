/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OPTOBJECT_H
#define CFG_OPTOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Wavelength.h>
#include <BaseClass/FC_VectorImp.h>
#include "CFG_Object.h"
#include <map>

class CFG_AppIf;


typedef map< CT_TEL_daHz, CT_TEL_SignalType, greater<CT_TEL_daHz> > CFG_ClockRateMap;


//This object contains all the generic optical configuration 
//for one port.
class CFG_Opt 
: public CFG_Object
{

public:

    //Constructor.
    CFG_Opt(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Opt(void);

    //This method sets the current state of laser.
    bool SetLaserEnable(bool theLaserEnable);

    //This method returns the current state of laser.
    bool GetLaserEnable() const;

    //This method enables or not automatic laser shutdown on detection of loss of signal.
    bool SetAutomaticLaserShutdown(bool theAutomaticLaserShutdown);

    //This method returns the current state (enabled or disabled) of the automatic laser shutdown.
    bool GetAutomaticLaserShutdown() const;

    //This method enables or not near end automatic laser shutdown on detection of loss of signal.
    bool SetNearEndAutomaticLaserShutdown(bool theAutomaticLaserShutdown);

    //This method returns the current state (enabled or disabled) of the near end automatic laser shutdown.
    bool GetNearEndAutomaticLaserShutdown() const;

    //This method sets the Hold Off Timer for automatic laser shutdown (in milliseconds).
    bool SetAlsHoldOffDelay(uint32 theAlsHoldOffDelay);

    //This method returns the Hold Off Timer for automatic laser shutdown (in milliseconds).
    uint32 GetAlsHoldOffDelay() const;

    //This method sets the maintenance signal insertion delay (in milliseconds).
    bool SetMaintSigDelay(uint32 theMaintSigDelay);

    //This method returns the maintenance signal insertion delay (in milliseconds).
    uint32 GetMaintSigDelay() const;

    //This method allows enabling or disabling the facility 
    //loopback. Traffic is loop backed as soon as it enters 
    //the equipment. This will also enable or disable 
    //generation of AIS-L in ingress direction.
    bool SetFacilityLoopBackEnable(bool theFacilityLoopBackEnable);

    //This method allows retrieving the state of the facility 
    //loopback: enabled or disabled.
    bool GetFacilityLoopBackEnable() const;

    //This method allows enabling or disabling the terminal 
    //loopback. Traffic is loop backed as late as possible, 
    //just before it should come out of the equipment. This 
    //will also enable or disable generation of AIS-L in 
    //egress direction
    bool SetTerminalLoopBackEnable(bool theTerminalLoopBackEnable);

    //This method allows retrieving the state of the terminal 
    //loopback: enabled or disabled.
    bool GetTerminalLoopBackEnable() const;

    //Set LOS threshold for Optical Power
    bool SetLosThreshold(CT_TEL_mBm theLosThreshold);

    //Get LOS threshold for Optical Power
    CT_TEL_mBm GetLosThreshold() const;

    //This method allows enabling or disabling of the automaticrate lock down.
    bool SetAutoRateLockDown(bool theAutoRateLockDown);

    //This method allows retrieving the state of Automatic rate lock down: enable or disable.
    bool GetAutoRateLockDown() const;

    //This method allows setting of the Signal Bit rate.
    bool SetSignalRate(CT_TEL_daHz theSignalRate);

    //This method allows retrieving of the default signal rate configured.
    CT_TEL_daHz GetSignalRate() const;

    //This method allows setting of the clock rate map.
    bool SetClockRateMap(CFG_ClockRateMap& theMap);

    //This method allows retrieving of the clock rate map.
    const CFG_ClockRateMap& GetClockRateMap() const;

    //This method allows enabling or disabling of the digital wrapper.
    bool SetDigitalWrapperEnable(CT_TEL_OTNMode theDigitalWrapperEnable);

    //This method allows retrieving the state of the digital wrapper: enable or disable.
    CT_TEL_OTNMode GetDigitalWrapperEnable() const;

    //This method allows setting of the configurable wavelength.
    bool SetWavelength(const CT_Wavelength& theWavelength);

    //This method allows retrieving of the configurable wavelength.
    const CT_Wavelength& GetWavelength() const;

    //This method allows setting of the configurable frequency.
    bool SetFrequency(const uint32 theFrequency);

    //This method allows retrieving of the configurable frequency.
    uint32 GetFrequency() const;


    //This method allows setting of the configurable frequency band.
    bool SetBand(const CT_TEL_OpticalWaveLength& theBand);

    //This method allows retrieving of the configurable frequency band.
    const CT_TEL_OpticalWaveLength& GetBand() const;

    //This method allows setting of the configurable frequency plan.
    bool SetFreqPlan(const CT_TEL_FreqencyPlan& thePlan);

    //This method allows retrieving of the configurable frequency plan.
    const CT_TEL_FreqencyPlan& GetFreqPlan() const;

    //This method allows enabling or disabling of the transmission of the Debug optical trace ID.
    void SetDebugTraceEnable(bool theDebugTrace);

    //This method allows retrieving the state of the debug trace: enable or disable.
    bool GetDebugTraceEnable() const;

    bool SetProvisionningActive(bool theProvisionningActive);
    bool GetProvisionningActive() const;

    //This method allows enabling or disabling of the trace ID auto negotiation. (DEBUG PURPOSE)
    bool SetIdAutoNegEnable(bool theIdAutoNeg);

    //This method allows retrieving the state of trace ID auto negotiation. (DEBUG PURPOSE)
    bool GetIdAutoNegEnable() const;


    //This method sets the current state of the PRBS BER Transmit Enable.
    bool SetPrbsTxEnable(bool thePrbsTxEnable);

    //This method returns the current state of the PRBS BER Transmit Enable.
    bool GetPrbsTxEnable() const;

    //This method sets the current state of the PRBS BER Receive Enable.
    bool SetPrbsRxEnable(bool thePrbsRxEnable);

    //This method returns the current state of the PRBS BER Receive Enable.
    bool GetPrbsRxEnable() const;

    //This method sets the PRBS BER Receive Seesion Counter.
    bool SetPrbsRxSessionCounter(uint32 thePrbsRxSessionCounter);

    //This method returns the PRBS BER Receive Seesion Counter.
    uint32 GetPrbsRxSessionCounter() const;


    //This method sets the OEO Regen Mode
    bool SetOEORegenMode(CT_TEL_OEO_REGEN_MODE theMode);

    //This method gets the OEO Regen Mode
    CT_TEL_OEO_REGEN_MODE GetOEORegenMode() const;

    //This method sets the Clock Type
    bool SetClockType(CT_TEL_ClkType theMode);

    //This method gets the Clock Type
    CT_TEL_ClkType GetClockType() const;

    //This method sets the OTID Status
    bool SetOTIDStatus(CT_TEL_OTIDStatus theOTIDStatsu);

    //This method gets the OTID Status
    CT_TEL_OTIDStatus GetOTIDStatus() const;

    //This method sets the Maintenance Propagation Mode
    bool SetMaintPropMode(CT_TEL_MAINT_PROP_MODE theMode);

    //This method gets the Maintenance Propagation Mode
    CT_TEL_MAINT_PROP_MODE GetMaintPropMode() const;

    // This method allows enabling or disabling Fefi Propagation.
    // It will use the first bit of the Generic Provisioning parameter.
    bool SetPropFefiEnabled(bool thePropFefiEnabled);

    // This method allows retrieving the state of Fefi Propagation
    // It uses the first bit of the Generic Provisioning parameter.
    bool GetPropFefiEnabled() const;

    // This method allows enabling or disabling the Ignore CSF LOSync flag.
    // When set, the OptAutomaticAction will not shut off the laser for CSF-LOSYNC.
    bool SetIgnoreCsfLOSyncFlag(bool theIgnoreFlag);

    // This method allows retrieving the state of Ignore CSF LOSync flag
    bool GetIgnoreCsfLOSyncFlag() const;

    //This method set the PRBS format: G709(no fixed stuff) or FixedStuff
    bool SetPrbsFormat(CT_TEL_PrbsFormat thePrbsFormat);

    //This method returns the PRBS format: G709(no fixed stuff) or FixedStuff
    CT_TEL_PrbsFormat GetPrbsFormat() const;

    //Debug methods
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The Hold Off Timer for automatic laser shutdown (in milliseconds).
    uint32 myAlsHoldOffDelay;

    //The maintenance signal insertion delay (in milliseconds).
    uint32 myMaintSigDelay;
   
    // The configured LOS Threshold for hardware (if available)
    CT_TEL_mBm  myLosThreshold;

    //The default bit rate of the optical signal
    CT_TEL_daHz mySignalRate;

    //The valid clock rate map configured
    CFG_ClockRateMap myClockRateMap;

    //The digital wrapper enable state configured
    CT_TEL_OTNMode myDigitalWrapperEnable;

    //The wavelength configured
    CT_Wavelength myWavelength;

    //The frequency configured
    uint32 myFrequency;

    //The frequency band configured
    CT_TEL_OpticalWaveLength myBand;

    //The frequency plan configured
    CT_TEL_FreqencyPlan myPlan;

    //The session number for an Rx PRBS BER collection on a facility.
    uint32 myPrbsRxSessionCounter;

    //The OEO Regen Mode
    CT_TEL_OEO_REGEN_MODE myOEORegenMode;

    //The OCHP Clock Rate
    CT_TEL_ClkType myClockType;
    CT_TEL_OTIDStatus myOTIDStatus;

    //The Maintenance Propagation Mode
    CT_TEL_MAINT_PROP_MODE myMaintPropMode;

    //the PRBS format: G709(no fixed stuff) or FixedStuff
    CT_TEL_PrbsFormat myPrbsFormat;

    // Generic Provisioning Parameter.  The bits can be used for whatever porpose.
    // Combine all the bools into one uint parameter to reduce space used.
    // bool myLaserEnable;                    LASER_ENABLE_OPT_GENERIC_PROV_MASK     = 0x0001
    // bool myProvisionningActive;            PROV_ACTIVE_OPT_GENERIC_PROV_MASK      = 0x0002
    // bool myFacilityLoopBackEnable;         FAC_LOOP_OPT_GENERIC_PROV_MASK         = 0x0004
    // bool myTerminalLoopBackEnable;         TER_LOOP_OPT_GENERIC_PROV_MASK         = 0x0008
    // bool myAutomaticLaserShutdown;         ALS_OPT_GENERIC_PROV_MASK              = 0x0010
    // bool myNearEndAutomaticLaserShutdown;  NEAR_END_ALS_OPT_GENERIC_PROV_MASK     = 0x0020
    // bool myPrbsTxEnable;                   TX_PRBS_OPT_GENERIC_PROV_MASK          = 0x0040
    // bool myPrbsRxEnable;                   RX_PRBS_OPT_GENERIC_PROV_MASK          = 0x0080
    // bool myIdAutoNegEnable;                ID_AUTO_NEG_OPT_GENERIC_PROV_MASK      = 0x0100
    // bool myDebugTraceEnable;               DEBUG_TRACE_OPT_GENERIC_PROV_MASK      = 0x0200
    // bool myAutoRateLockDown;               AUTO_RATE_LOCK_OPT_GENERIC_PROV_MASK   = 0x0400
    // bool myPropFefi;                       PROP_FEFI_OPT_GENERIC_PROV_MASK        = 0x0800
    // bool myIgnoreCsfLOSyncFlag             IGNORE_CSFLOSYNC_OPT_GENERIC_PROV_MASK = 0x1000
    uint16 myGenericProvisioning;

};

#endif /* CFG_OPTOBJECT_H */

