#ifndef _TSPII_DCCLIF_H
#define _TSPII_DCCLIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Mark Nash/Denham Reynolds - August 2006
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for Dcc Hardware.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_DCC_Definitions.h"

class TSPII_DcclIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_DcclIf(bool theDefault = false);
    virtual                           ~TSPII_DcclIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Dcc Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual CT_DCC_LinkState          GetProtocolLinkState();
    virtual bool                      GetTunnelSessionState();
    virtual uint32                    GetDroppedPacketsCount();  
    virtual bool                      GetDefectsChanged();

    virtual uint32                    GetMagicNumber() const;  

    // -----------------------------------------------------------------------------------
    // SONET/SDH Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetLinkRouterID(CT_DCC_RouterId theLinkRouterId);
    virtual CT_DCC_RouterId           GetLinkRouterID() const;

    virtual void                      SetRouterShelfID(CT_ShelfId theRouterShelf);
    virtual CT_ShelfId                GetRouterShelfID() const;

    virtual void                      SetIntfID(CT_IfIndexIdent theIntfID);
    virtual CT_IfIndexIdent           GetIntfID() const;

    // Method to identify LAPD or PPP link
    virtual void                      SetDccLinkType(CT_DCC_LinkType theDccLinkType);
    virtual CT_DCC_LinkType           GetDccLinkType() const;

    // From LAPD Profile
    virtual void                      SetTransferMode(CT_LPF_TxMode theTransferMode);
    virtual CT_LPF_TxMode             GetTransferMode() const;

    virtual void                      SetRetransmissionCount(uint8 theRetransmissionCount);
    virtual uint8                     GetRetransmissionCount() const;

    virtual void                      SetAckWaitTimer(uint16 theAckWaitTimer);
    virtual uint16                    GetAckWaitTimer() const;

    virtual void                      SetMaxFrameSize(uint16 theMaxFrameSize);
    virtual uint16                    GetMaxFrameSize() const;

    virtual void                      SetFrameCount(uint8 theFrameCount);
    virtual uint8                     GetFrameCount() const;

    virtual void                      SetInactivityTimer(uint16 theInactivityTimer);
    virtual uint16                    GetInactivityTimer() const;

    virtual void                      SetSideAssignment(CT_LPF_Side theSideAssignment);
    virtual CT_LPF_Side               GetSideAssignment() const;

    virtual void                      SetSequenceRange(uint8 theSequenceRange);
    virtual uint8                     GetSequenceRange() const;


    // From LAPD Command
    virtual void                      SetProtocolLinkEnabled(bool theEnabled);
    virtual bool                      GetProtocolLinkEnabled() const;

    virtual void                      SetFollowProtection(bool theFollowProtection);
    virtual bool                      GetFollowProtection() const;

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

    // LAPS Broadcast Support
    virtual void                      SetDccBroadcastMode(CT_DCC_BroadcastMode theMode);
    virtual CT_DCC_BroadcastMode      GetDccBroadcastMode() const;

    virtual void                      SetDccSelectionMode(CT_DCC_SelectionMode theSelMode);
    virtual CT_DCC_SelectionMode      GetDccSelectionMode() const;

    virtual void                      SetDccRemoteSfp(uint8 theRemoteSfp);
    virtual uint8                     GetDccRemoteSfp() const;

    virtual void                      SetRxSelected(bool theSelected);
    virtual bool                      GetRxSelected() const;

    // Shell test Debugging for PPP
    virtual void                      DebugPPPCommand(char command);
    virtual void                      DebugLapdCommand(char command);

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
    // LAPD or PPP link type identifier
    CT_DCC_LinkType         itsDccLinkType;

    // Lapd Specific configuration attributes
    bool                    itsProtocolLinkEnabled;
    CT_DCC_RouterId         itsLinkRouterId;
    CT_ShelfId              itsRouterShelfId;
    CT_IfIndexIdent         itsIntfID;
    CT_LPF_TxMode           itsTransferMode;
    uint8                   itsRetransmissionCount;
    uint16                  itsAckWaitTimer;
    uint16                  itsMaxFrameSize;
    uint8                   itsFrameCount;
    uint16                  itsInactivityTimer;
    CT_LPF_Side             itsSideAssignment;
    uint8                   itsSequenceRange;

    // LAPS Broadcast Support
    CT_DCC_BroadcastMode    itsBroadcastMode;
    CT_DCC_SelectionMode    itsSelectionMode;
    bool                    itsRxSelected;
    uint8                   itsRemoteSfp;
    
    bool                    itsFollowProtection;

    // PPP specific configuration attributes
    // From TL (Topological Link) Command
    CT_DCC_TL_AddrType      itsAddressType;
    uint32                  itsSourceIpAddress;
    uint32                  itsSubnetMask;
    uint32                  itsDestIpAddress;
    bool                    itsAutoDiscEnabled;
    bool                    itsIpEnabled;

    // PPP Profile
    uint16                  itsMaxReceiveUnits;
    uint8                   itsRestartTimer;
    uint8                   itsMaxTerminateValue;
    uint8                   itsMaxConfigureValue;
    uint8                   itsMaxFailureValue;
	uint8                   itsFCS;
};

#endif // TSPII_DCCLIF_H
