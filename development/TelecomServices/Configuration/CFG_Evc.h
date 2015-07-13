/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_EVCOBJECT_H
#define CFG_EVCOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_AgentFacility.h>
#include "CFG_Object.h"
#include <list>

//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Evc
: public CFG_Object
{

public:

	//Constructor.
    CFG_Evc(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Evc(void);

    // Set All Frames Forwarded across EVC.
    bool GetAllFrames() const;

    // Get All Frames Forwarded across EVC.
    void SetAllFrames(bool theAllFrames);

    // Get Destination Facility.
    CT_Port GetDestPort() const;

    // Set Source Facility.
    void SetDestPort(CT_Port theDestPort);

    // Get Source Facility.
    CT_Port GetSrcPort() const;

    // Set Source Facility.
    void SetSrcPort(CT_Port theSrcPort);
    
    // Get EVC Pair ID.
    uint32 GetEvcPairId() const;

    // Set EVC Pair ID.
    void SetEvcPairId(uint32 theEvcPairId);

    // Whether the source port is part of any EVC
    // Used in the deletion of EVCs
    void SetSrcIncludedInAnyEVC(bool theIncluded);
    bool GetSrcIncludedInAnyEVC() const;

    // Whether the destinaiton port is part of any EVC
    // Used in the deletion of EVCs
    void SetDestIncludedInAnyEVC(bool theIncluded);
    bool GetDestIncludedInAnyEVC() const;

    // Whether the EVC is provisioned (or not)
    void SetIsProvisioned(bool theProvisioned);
    bool GetIsProvisioned() const;
    
    // Whether the EVC is protected (or not)
    void SetIsProtected(bool theProtected);
    bool GetIsProtected() const;

    // Get BandWidth Profile.
    int GetBWPF() const;

    // Set BandWidth Profile.
    void SetBWPF(int theBWPF);
        
    // Get Control Frame Profile.
    int GetCFPF() const;

    // Set Control Frame Profile.
    void SetCFPF(int theCFPF);

    // Get S-VLAN ID to tag.
    uint32 GetSTAG() const;

    // Set S-VLAN ID to tag.
    void SetSTAG(uint32 theSTAG);

    // Set list of supported S-VLAN ID.
    void SetSVID(vector<uint16>& theSVID);

    // Get list of supported S-VLAN ID.
    const vector<uint16>& GetSVID();

    // Set list of supported C-VLAN ID.
    void SetCVID(vector<uint16>& theCVID);

    // Get list of supported C-VLAN ID.
    const vector<uint16>& GetCVID();

    // Set Pause frame discard .
    void SetPauseDiscardEnabled(bool thePauseDiscardEnabled);

    // Get Pause frame discard .
    bool GetPauseDiscardEnabled() const;
    
    // Set Pause frame discard .
    void SetPbitRegen(CT_TEL_PbitRegen thePbitRegen);

    // Get Pause frame discard .
    CT_TEL_PbitRegen GetPbitRegen() const;


    // Whether ETH-AIS is enabled 
    void SetAisEnabled(bool theAisEnabled);
    bool GetAisEnabled() const;

    // Set the AIS transmission interval
    void   SetAisInterval(uint16 theAisInterval);
    uint16 GetAisInterval() const;

    // Set the MEG level included in the AIS message
    void  SetAisMegLevel(uint8 theAisMegLevel);
    uint8 GetAisMegLevel() const;

    // Set the destination MAC Address Mode (unicast or multicast)
    void           SetAisDestMacMode(CT_TEL_MacMode theAisDestMacMode);
    CT_TEL_MacMode GetAisDestMacMode() const;

    // Set destination MAC Address
    void SetAisDestMacAddr(CT_LacpSystemId theMacAddr);
    CT_LacpSystemId GetAisDestMacAddr() const;

    //This method allows enabling or disabling the facility 
    //loopback. Traffic is loop backed toward the source of the EVC 
    //(normally the client)
    void SetFacilityLoopBackEnable(bool theEnable);
    bool GetFacilityLoopBackEnable() const;

    //This method allows enabling or disabling the terminal 
    //loopback. Traffic is loop backed toward the destination 
    //of the EVC (normally back toward the system)
    void SetTerminalLoopBackEnable(bool theEnable);
    bool GetTerminalLoopBackEnable() const;


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

private:
    
    // All Frames Forwarded across EVC.
    bool myAllFrames;

    // Whether the EVC is provisioned (or not)
    bool myIsProvisioned;

        // Whether the EVC is protected (or not)
    bool myIsProtected;
    
    // Destination Facility.
    CT_Port myDestPort;
	
    // Source Facility.
    CT_Port mySrcPort;

    // Pair Id
    uint32 myEvcPairId;

    // Is Source part of any EVC
    bool mySrcIncludedInAnyEVC;

    // Is Destination part of any EVC
    bool myDestIncludedInAnyEVC;

    // BandWidth Profile for this port.
    int myBWPF;

    // Control Frame Profile for this port.
    int myCFPF;

    // S-VLAN ID to tag.
    uint32 mySTAG;
    
    // Pause frame discard Enabled
    bool myPauseDiscardEnabled;

    // Priority BITS regen.
    CT_TEL_PbitRegen myPbitRegen;

    // S-VLAN ID.
    vector<uint16> mySVID;
   
    // C-VLAN ID.
    vector<uint16> myCVID;

    // Whether ETH-AIS is enabled 
    bool myAisEnabled;

    // AIS transmission interval
    uint16 myAisInterval;

    // MEG level included in the AIS message
    uint8 myAisMegLevel;

    // Destination MAC Address Mode (unicast or multicast)
    CT_TEL_MacMode myAisDestMacMode;

    // Destination MAC Address
    CT_LacpSystemId myAisDestMacAddr;

    //The current facility loopback state configured.
    bool myFacilityLoopBackEnable;

    //The current terminal loopback state configured.
    bool myTerminalLoopBackEnable;

};

#endif /* CFG_EVCOBJECT_H */

