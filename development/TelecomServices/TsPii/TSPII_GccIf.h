#ifndef _TSPII_GCCIF_H
#define _TSPII_GCCIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Jessica Chen - April 2011
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for Gcc Hardware.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_DCC_Definitions.h"

class TSPII_GccIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_GccIf(bool theDefault = false);
    virtual                           ~TSPII_GccIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Gcc Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual CT_DCC_LinkState          GetProtocolLinkState();
    virtual bool                      GetTunnelSessionState();
    virtual uint32                    GetDroppedPacketsCount();  
    virtual bool                      GetDefectsChanged();

    virtual uint32                    GetMagicNumber() const;  

    // -----------------------------------------------------------------------------------
    // SONET/SDH Config Interfaces
    // -----------------------------------------------------------------------------------
   
    // From GCC Command
    virtual void                      UpdatePppLinkState(int theGccIndex);
    virtual void                      SetGCCLinkEnabled(bool theEnabled);
    virtual bool                      GetGCCLinkEnabled() const;

    virtual void                      SetIntfID(CT_IfIndexIdent theIntfID);
    virtual CT_IfIndexIdent           GetIntfID() const;

    // From PPP Profile
    virtual void                      SetMaxReceiveUnits(uint16 theMaxReceiveUnits);
    virtual uint16                    GetMaxReceiveUnits() const;

    virtual void                      SetRestartTimer(uint8 theRestartTimer);
    virtual uint8                     GetRestartTimer() const;

    virtual void                      SetMaxTerminateValue(uint8 theMaxTerminateValue);
    virtual uint8                     GetMaxTerminateValue() const;

    virtual void                      SetMaxConfigureValue(uint8 theMaxConfigureValue);
    virtual uint8                     GetMaxConfigureValue() const;

    virtual void                      SetMaxFailureValue(uint8 theMaxFailureValue);
    virtual uint8                     GetMaxFailureValue() const;

    virtual void                      SetFCS(uint8 theFCS);
    virtual uint8                     GetFCS() const;

    // From TL (Topological Link) Command
    // Near End Address Type
    virtual void                      SetAddressType(CT_DCC_TL_AddrType theAddressType);
    virtual CT_DCC_TL_AddrType        GetAddressType() const;

    // Near End Address for Numbered ; Parent TL for Unnumbered 
    virtual void                      SetSourceIpAddress(uint32 theSourceIpAddress);
    virtual uint32                    GetSourceIpAddress() const;

    // Near End Mask 
    virtual void                      SetSubnetMask(uint32 theSubnetMask);
    virtual uint32                    GetSubnetMask() const;

    // Neighbor Node ID 
    virtual void                      SetDestIpAddress(uint32 theDestIpAddress);
    virtual uint32                    GetDestIpAddress() const;

    // Indicates whether the DestIpAdress is Auto Discovered or Provided above
    virtual void                      SetAutoDiscEnabled(bool theEnabled);
    virtual bool                      GetAutoDiscEnabled() const;

    // TL Link IS/OOS (IP Eanbled)
    virtual void                      SetIpEnabled(bool theEnabled);
    virtual bool                      GetIpEnabled() const;

    virtual void                      SetVlanChannel(uint16 theVlanTag,uint8 theChannel);

	// Channel (used in the mTera architecture)
    virtual void                      SetChannel(uint8 theChannel);
    virtual uint8                     GetChannel() const;

    // VLAN Tag (used in the mTera architecture)
    virtual void                      SetVlanTag(uint16 theVlanTag);
    virtual uint16                    GetVlanTag() const;

    // Shell test Debugging for PPP
    virtual void                      DebugPPPCommand(char command);

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                      Display(FC_Stream & theStream);
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv);
    virtual void                      DisplayUnitID(FC_Stream & theStream);
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);

protected:

    void                 RefreshGet();
    void                 RefreshSet();

    // Monitoring attributes
    CT_DCC_LinkState     itsProtocolLinkState;
    bool                 itsTunnelSessionState;
    uint32               itsDroppedPacketsCount;
    bool                 itsDefectsChanged;

    // Mon PPP specific attributes
    uint32               itsMagicNumber; 
    
    // Configuration attributes 
  
    // GCC Specific configuration attributes
    bool                    itsGccLinkEnabled;
    CT_IfIndexIdent         itsIntfID;

    // PPP specific configuration attributes
    // From TL (Topological Link) Command
    CT_DCC_TL_AddrType      itsAddressType;
    uint32                  itsSourceIpAddress;
    uint32                  itsSubnetMask;
    uint32                  itsDestIpAddress;
    bool                    itsAutoDiscEnabled;
    bool                    itsIpEnabled;
    uint8                   itsChannel;
    uint16                  itsVlanTag;

    // PPP Profile
    uint16                  itsMaxReceiveUnits;
    uint8                   itsRestartTimer;
    uint8                   itsMaxTerminateValue;
    uint8                   itsMaxConfigureValue;
    uint8                   itsMaxFailureValue;
    uint8                   itsFCS;
};

#endif // TSPII_GCCIF_H
