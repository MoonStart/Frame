/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_RSOBJECT_H
#define CFG_RSOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SDH16ByteTrace.h>

#include "CFG_Object.h"


//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Rs 
: public CFG_Object
{

public:

	//Constructor.
    CFG_Rs(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Rs(void);

  	//This method sets the signal type.
	bool SetSignalType(CT_TEL_SignalType theSignalType);

	//This method returns the current signal type.
	CT_TEL_SignalType GetSignalType() const;

    //This method sets the Clock Type
    bool SetClockType(CT_TEL_ClkType theClkType);

    //This method gets the Clock Type
    CT_TEL_ClkType GetClockType() const;


    //This method sets the first and second device for the route from the Sfp (and adds clock type because there wasn't enough yet)
    bool SetSfpRouteAndSignalType(CT_TEL_FrontEndDevice theDevice, 
                                  CT_TEL_FrontEndDevice theCrossover, 
                                  CT_TEL_SignalType theSignalType, 
                                  CT_TEL_ClkType theClkType = CT_TEL_CLK_UNKNOWN);

    //This method gets second device for the route from the Sfp
    CT_TEL_FrontEndDevice GetDeviceInSfpRoute() const;

    //This method gets first device for the route from the Sfp
    CT_TEL_FrontEndDevice GetCrossoverInSfpRoute() const;


    //This method sets the Internal Signaling Disabled flag of the facility (YES or NO).
    bool SetInternalSignalingDisabled(bool theDisable);

    //This method returns the Internal Signaling Disabled flag of the facility.
    bool GetInternalSignalingDisabled() const;

    //This method sets the External Signaling Disabled flag of the facility (YES or NO).
    bool SetExternalSignalingDisabled(bool theDisable);

    //This method returns the External Signaling Disabled flag of the facility.
    bool GetExternalSignalingDisabled() const;


    //This method force AIS Line generation in one direction.
    bool SetForceAISL(bool theForceAISL);

	//This method retrieves the current state of AIS Line forced in one direction.
    bool GetForceAISL() const;


    //This method force TLAB AIS generation in one direction.
    bool SetForceTlabAIS(bool theForceTlabAIS);

    //This method retrieves the current state of TLAB AIS forced in one direction.
    bool GetForceTlabAIS() const;


    //This method sets the indication type for the maintenance signal.
    bool SetIndicationType(CT_RS_IndicationType theIndicationType);

    //This method retrieves  the indication type for the maintenance signal.
    CT_RS_IndicationType GetIndicationType() const;

    //This method sets the internal indication type for the maintenance signal.
    bool SetInternalIndType(CT_RS_IndicationType theIndicationType);

    //This method retrieves the internal indication type for the maintenance signal.
    CT_RS_IndicationType GetInternalIndType() const;


    //This method allows setting the current sent section trace message (J0).
    bool SetSentTrace( const CT_SDH16ByteTrace& theSentTrace);

	//This method allows retrieving the current setting for the sent section trace message (J0).
     CT_SDH16ByteTrace GetSentTrace() const;

    //This method enables or not AISL on detection of loss of signal.
    //(DEBUG PURPOSE ONLY)
    bool SetAutomaticAISL(bool theAutomaticAISL);

	//This method returns the current state (enabled or disabled) of the automatic AISL.
    //(DEBUG PURPOSE ONLY)
	bool GetAutomaticAISL() const;


    //This method sets automatic (upon defects) TLAB AIS generation in one direction.
    bool SetAutoTlabAIS(bool theAutoTlabAIS);

    //This method retrieves the current state (enabled or disabled) of automatic (upon defects) TLAB AIS generation in one direction.
    bool GetAutoTlabAIS() const;


    //This method returns the current state (enabled or disabled) JO trace transparency.
	bool GetSentTraceTransparent() const;

	//This method allows to enable or disable JO trace transparency.
	bool SetSentTraceTransparent(bool theTraceTransparent);

    //This method returns the current state (enabled or disabled) for Messaging 
    // (i.e., EON Messaging on the OSC).
	bool GetMessagingEnabled() const;

	//This method allows to enable or disable Messaging 
    // (i.e., EON Messaging on the OSC).
	bool SetMessagingEnabled(bool theMessagingEnabled);

    //This method returns the current state (enabled or disabled) for true SDH.
    bool GetSDHTrueMode() const;

    //This method allows to enable or disabled true SDH.
    bool SetSDHTrueMode(bool mySDHTrueMode);

    //This method allows to set the CBR Mapping mode to bit synchronously or asynchronously.
    CT_TEL_PayloadType GetCBRMappingMode() const;

    //This method returns the current CBR Mapping mode.
    bool SetCBRMappingMode(CT_TEL_PayloadType theCBRMappingMode);

    //This method allows to set the Inter Packet Gap for Data facilities.
    uint8 GetInterPacketGap() const;

    //This method returns the current CBR Mapping mode.
    bool SetInterPacketGap(uint8 theInterPacketGap);

    // This method allows enabling or disabling the Ignore GFP defect flag.
    // When set, CFG/MON will not force insert NOS when line RX receive GFP-LOS/LOSYNC, now it is added
    // for HDTG FC8G.
    bool SetIgnoreCsfLosCsfLosyncFlag(bool theIgnoreFlag);

    // This method allows retrieving the state of Ignore GFP defect flag.
    bool GetIgnoreCsfLosCsfLosyncFlag() const;


    static bool IsPayloadTypeSONETSDH(CT_TEL_SignalType theSignalType);

    static bool IsSignalTypeOTN(CT_TEL_SignalType theSignalType);

	//Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    void    DisplayDevices();
    void    DisplayIndications();

private:

    // The current signal type
    CT_TEL_SignalType mySignalType;

    //The OCHP Clock Rate
    CT_TEL_ClkType myClockType;

    //End device ID for routing port facility 
    CT_TEL_FrontEndDevice myDevice;

    //Middle device ID for routing port facility 
    CT_TEL_FrontEndDevice myCrossover;

	//The 16 byte trace message to transmit into J0 bytes.
	CT_SDH16ByteTrace mySentTrace;

    //The indication type for the maintenance signal configured
    CT_RS_IndicationType myIndicationType;

    //The internal indication type for the maintenance signal configured
    CT_RS_IndicationType myInternalIndType;

    //Set to sync or async.
    CT_TEL_PayloadType myCBRMappingMode;

    uint8 myInterPacketGap;


    // Generic Provisioning Parameter.  The bits can be used for whatever porpose.
    // Combine all the bools into one uint parameter to reduce space used.
    // bool myAutomaticAISL;              AUTO_AISL_RS_GENERIC_PROV_MASK        = 0x0001
    // bool myAutoTlabAIS;                AUTO_TLABAIS_RS_GENERIC_PROV_MASK     = 0x0002
    // bool myForceAISL;                  FORCE_AISL_RS_GENERIC_PROV_MASK       = 0x0004
    // bool myForceTlabAIS;               FORCE_TLABAIS_RS_GENERIC_PROV_MASK    = 0x0008
    // bool myInternalSignalingDisabled;  INT_SIG_DISABLED_RS_GENERIC_PROV_MASK = 0x0010
    // bool myExternalSignalingDisabled;  EXT_SIG_DISABLED_RS_GENERIC_PROV_MASK = 0x0020
    // bool myMessagingEnabled;           MESS_ENABLED_RS_GENERIC_PROV_MASK     = 0x0040
    // bool mySentTraceTransparent;       SENT_TRACE_TRANS_RS_GENERIC_PROV_MASK = 0x0080
    // bool mySDHTrueMode;                SDH_TRUE_RS_GENERIC_PROV_MASK         = 0x0100
    // bool myIgnoreCsfLosCsfLosync;      IGNORE_CSFLOS_CSFLOSYNC_RS_GENERIC_PROV_MASK  = 0x0200
    uint16 myGenericProvisioning;

};

#endif /* CFG_RSOBJECT_H */

