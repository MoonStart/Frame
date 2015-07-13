/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  C Kleinrichert - Sept 2006
 DESCRIPTION:Definition of the class TSPII_DcclIf - Models the Generic 
             Framing Procedure termination entity.
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_DcclIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_DcclIf::TSPII_DcclIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DcclIf::~TSPII_DcclIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::RefreshGet()
{   
    // Monitor attributes
    itsProtocolLinkState        = GetProtocolLinkState();
    itsTunnelSessionState       = GetTunnelSessionState();
    itsDroppedPacketsCount      = GetDroppedPacketsCount();
    itsDefectsChanged           = GetDefectsChanged();

    // Mon PPP specific attributes
    itsMagicNumber              = GetMagicNumber();
    
    // Configuration attributes
    itsDccLinkType              = GetDccLinkType();

    itsProtocolLinkEnabled      = GetProtocolLinkEnabled();
    itsLinkRouterId             = GetLinkRouterID();
    itsRouterShelfId            = GetRouterShelfID();
    itsIntfID                   = GetIntfID();
    itsTransferMode             = GetTransferMode();
    itsRetransmissionCount      = GetRetransmissionCount();
    itsAckWaitTimer             = GetAckWaitTimer();
    itsMaxFrameSize             = GetMaxFrameSize();
    itsFrameCount               = GetFrameCount();
    itsInactivityTimer          = GetInactivityTimer();
    itsSideAssignment           = GetSideAssignment();
    itsFollowProtection         = GetFollowProtection();
    itsSequenceRange            = GetSequenceRange();

    // PPP configuration attributes
    itsAddressType              = GetAddressType();
    itsSourceIpAddress          = GetSourceIpAddress();
    itsSubnetMask               = GetSubnetMask();
    itsDestIpAddress            = GetDestIpAddress();
    itsAutoDiscEnabled          = GetAutoDiscEnabled();
    itsIpEnabled                = GetIpEnabled();

    itsMaxReceiveUnits          = GetMaxReceiveUnits();
    itsRestartTimer             = GetRestartTimer();
    itsMaxTerminateValue        = GetMaxTerminateValue();
    itsMaxConfigureValue        = GetMaxConfigureValue();
    itsMaxFailureValue          = GetMaxFailureValue();
    itsFCS                      = GetFCS(); 

    // LAPS Broadcast Support
    itsBroadcastMode            = GetDccBroadcastMode();
    itsSelectionMode            = GetDccSelectionMode();
    itsRemoteSfp                = GetDccRemoteSfp();
    itsRxSelected               = GetRxSelected();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::RefreshSet()
{   
    // Configuration attributes
    SetDccLinkType(itsDccLinkType);

    SetProtocolLinkEnabled(itsProtocolLinkEnabled);
    SetLinkRouterID(itsLinkRouterId);
    SetRouterShelfID(itsRouterShelfId);
    SetIntfID(itsIntfID);
    SetTransferMode(itsTransferMode);
    SetRetransmissionCount(itsRetransmissionCount);
    SetAckWaitTimer(itsAckWaitTimer);
    SetMaxFrameSize(itsMaxFrameSize);
    SetFrameCount(itsFrameCount);
    SetInactivityTimer(itsInactivityTimer);
    SetSideAssignment(itsSideAssignment);
    SetSequenceRange(itsSequenceRange);
    SetFollowProtection(itsFollowProtection);

    //PPP specific Configuration attributes
    SetAddressType(itsAddressType);
    SetSourceIpAddress(itsSourceIpAddress);
    SetSubnetMask(itsSubnetMask);
    SetDestIpAddress(itsDestIpAddress);
    SetAutoDiscEnabled(itsAutoDiscEnabled);
    SetIpEnabled(itsIpEnabled);

    SetMaxReceiveUnits(itsMaxReceiveUnits);
    SetRestartTimer(itsRestartTimer);
    SetMaxTerminateValue(itsMaxTerminateValue);
    SetMaxConfigureValue(itsMaxConfigureValue);
    SetMaxFailureValue(itsMaxFailureValue);
    SetFCS(itsFCS);  

    // LAPS Broadcast Support
    SetDccBroadcastMode(itsBroadcastMode);
    SetDccSelectionMode(itsSelectionMode);
    SetDccRemoteSfp(itsRemoteSfp);
    SetRxSelected(itsRxSelected);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsProtocolLinkState        = CT_DCC_LINK_INCOMPLETE;
    itsTunnelSessionState       = false;
    itsDroppedPacketsCount      = 0;
    itsDefectsChanged           = false;

    // Mon PPP specific attributes
    itsMagicNumber              = 0;
    
    // Configuration attributes
    // Link type identifier
    itsDccLinkType              = CT_DCC_UNKNOWN_LINK;

    itsProtocolLinkEnabled      = false;
    itsLinkRouterId             = 0;
    itsRouterShelfId            = 0;
    itsIntfID                   = 0;
    itsTransferMode             = CT_LPF_AITS;
    itsRetransmissionCount      = 3;
    itsAckWaitTimer             = 25;
    itsMaxFrameSize             = 512;
    itsFrameCount               = 7;
    itsInactivityTimer          = 50;
    itsSideAssignment           = CT_LPF_Auto;
    itsSequenceRange            = 128;
    itsFollowProtection         = false;

    
    // PPP Configuration attributes
    itsAddressType              = CT_DCC_TL_NONE;
    itsSourceIpAddress          = 0;
    itsSubnetMask               = 0;
    itsDestIpAddress            = 0;
    itsAutoDiscEnabled          = false;
    itsIpEnabled                = false;

    itsMaxReceiveUnits          = 1500;
    itsRestartTimer             = 10;
    itsMaxTerminateValue        = 2;
    itsMaxConfigureValue        = 10;
    itsMaxFailureValue          = 5;
    itsFCS                      = 16; //16 is default,32 need to be set   
 

    // LAPS Broadcast Support
    itsBroadcastMode            = CT_DCC_TERMINATE;
    itsSelectionMode            = CT_DCC_LOCAL;
    itsRxSelected               = true;
    itsRemoteSfp                = 0;
    RefreshSet();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetProtocolLinkEnabled(bool theEnable)
{
    itsProtocolLinkEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::GetProtocolLinkEnabled() const
{
    return itsProtocolLinkEnabled;
}
    
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetFollowProtection(bool theFollowProtection)
{
    itsFollowProtection = theFollowProtection;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::GetFollowProtection() const
{
    return itsFollowProtection;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetLinkRouterID(CT_DCC_RouterId theLinkRouterId)
{
    itsLinkRouterId = theLinkRouterId;
}

///////////////////////////////////////////////////////////////////////////////
CT_DCC_RouterId TSPII_DcclIf::GetLinkRouterID() const
{
    return itsLinkRouterId;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetRouterShelfID(CT_ShelfId theShelfId)
{
    itsRouterShelfId = theShelfId;
}

///////////////////////////////////////////////////////////////////////////////
CT_ShelfId TSPII_DcclIf::GetRouterShelfID() const
{
    return itsRouterShelfId;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetIntfID(CT_IfIndexIdent theIntfID)
{
    itsIntfID = theIntfID;
}

///////////////////////////////////////////////////////////////////////////////
CT_IfIndexIdent TSPII_DcclIf::GetIntfID() const
{
    return itsIntfID;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetTransferMode(CT_LPF_TxMode theTransferMode)
{
    itsTransferMode = theTransferMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_LPF_TxMode TSPII_DcclIf::GetTransferMode() const
{
    return itsTransferMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetRetransmissionCount(uint8 theRetransmissionCount)
{
    itsRetransmissionCount = theRetransmissionCount;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetRetransmissionCount() const
{
    return itsRetransmissionCount;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetAckWaitTimer(uint16 theAckWaitTimer)
{
    itsAckWaitTimer = theAckWaitTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DcclIf::GetAckWaitTimer() const
{
    return itsAckWaitTimer;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetMaxFrameSize(uint16 theMaxFrameSize)
{
    itsMaxFrameSize = theMaxFrameSize;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DcclIf::GetMaxFrameSize() const
{
    return itsMaxFrameSize;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetFrameCount(uint8 theFrameCount)
{
    itsFrameCount = theFrameCount;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetFrameCount() const
{
    return itsFrameCount;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetInactivityTimer(uint16 theInactivityTimer)
{
    itsInactivityTimer = theInactivityTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DcclIf::GetInactivityTimer() const
{
    return itsInactivityTimer;
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetSideAssignment(CT_LPF_Side theSideAssignment)
{
    itsSideAssignment = theSideAssignment;
}

///////////////////////////////////////////////////////////////////////////////
CT_LPF_Side TSPII_DcclIf::GetSideAssignment() const
{
    return itsSideAssignment;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetSequenceRange(uint8 theSequenceRange)
{
    itsSequenceRange = theSequenceRange;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetSequenceRange() const
{
    return itsSequenceRange;
}


//////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetDccLinkType(CT_DCC_LinkType theDccLinkType)
{
    itsDccLinkType = theDccLinkType;
}

/////////////////////////////////////////////////////////////////////////////
CT_DCC_LinkType TSPII_DcclIf::GetDccLinkType() const
{
    return(itsDccLinkType);
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetAddressType(CT_DCC_TL_AddrType theAddressType)
{
    itsAddressType = theAddressType;
}

/////////////////////////////////////////////////////////////////////////////
CT_DCC_TL_AddrType TSPII_DcclIf::GetAddressType() const
{
    return(itsAddressType);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetSourceIpAddress(uint32 theSourceIpAddress)
{
    itsSourceIpAddress = theSourceIpAddress;
}

///////////////////////////////////////////////////////////////////////////
uint32 TSPII_DcclIf::GetSourceIpAddress() const
{
    return(itsSourceIpAddress);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetSubnetMask(uint32 theSubnetMask)
{
    itsSubnetMask = theSubnetMask;
}

///////////////////////////////////////////////////////////////////////////
uint32 TSPII_DcclIf::GetSubnetMask() const
{
    return(itsSubnetMask);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetDestIpAddress(uint32 theDestIpAddress)
{
    itsDestIpAddress = theDestIpAddress;
}

///////////////////////////////////////////////////////////////////////////
uint32 TSPII_DcclIf::GetDestIpAddress() const
{
    return(itsDestIpAddress);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetAutoDiscEnabled(bool theEnabled)
{
    itsAutoDiscEnabled = theEnabled;
}

///////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::GetAutoDiscEnabled() const
{
    return(itsAutoDiscEnabled);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetIpEnabled(bool theEnabled)
{
    itsIpEnabled = theEnabled;
}

///////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::GetIpEnabled() const
{
    return(itsIpEnabled);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetMaxReceiveUnits(uint16 theMaxReceiveUnits)
{
    itsMaxReceiveUnits = theMaxReceiveUnits;
}

///////////////////////////////////////////////////////////////////////////
uint16 TSPII_DcclIf::GetMaxReceiveUnits() const
{
    return(itsMaxReceiveUnits);
}

///////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetRestartTimer(uint8 theRestartTimer)
{
    itsRestartTimer = theRestartTimer;
}

//////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetRestartTimer() const
{
    return(itsRestartTimer);
}

//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetMaxTerminateValue(uint8 theMaxTerminateValue)
{
    itsMaxTerminateValue = theMaxTerminateValue;
}

/////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetMaxTerminateValue() const
{
    return (itsMaxTerminateValue);
}

/////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetMaxConfigureValue(uint8 theMaxConfigureValue)
{
    itsMaxConfigureValue = theMaxConfigureValue;
}

/////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetMaxConfigureValue() const
{
    return (itsMaxConfigureValue);
}

//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetMaxFailureValue(uint8 theMaxFailureValue)
{
    itsMaxFailureValue = theMaxFailureValue;
}

//////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetMaxFailureValue() const
{
    return(itsMaxFailureValue);
}
//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetFCS(uint8 theFCS)
{
    itsFCS = theFCS;
}

//////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetFCS() const
{
    return(itsFCS);
}
///////////////////////////////////////////////////////////////////////////////
CT_DCC_LinkState TSPII_DcclIf::GetProtocolLinkState()
{
    return itsProtocolLinkState;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::GetTunnelSessionState()
{
    return itsTunnelSessionState;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DcclIf::GetDroppedPacketsCount()
{
    return itsDroppedPacketsCount;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::GetDefectsChanged()
{
    return itsDefectsChanged;
}


///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DcclIf::GetMagicNumber() const
{
    return itsMagicNumber;
}

//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetDccBroadcastMode(CT_DCC_BroadcastMode theMode)
{
    itsBroadcastMode = theMode;
}

//////////////////////////////////////////////////////////////////////////
CT_DCC_BroadcastMode TSPII_DcclIf::GetDccBroadcastMode() const
{
    return(itsBroadcastMode);
}

//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetDccSelectionMode(CT_DCC_SelectionMode theMode)
{
    itsSelectionMode = theMode;
}

//////////////////////////////////////////////////////////////////////////
CT_DCC_SelectionMode TSPII_DcclIf::GetDccSelectionMode() const
{
    return(itsSelectionMode);
}

//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetDccRemoteSfp(uint8 theRemoteSfp)
{
    itsRemoteSfp = theRemoteSfp;
}

//////////////////////////////////////////////////////////////////////////
uint8 TSPII_DcclIf::GetDccRemoteSfp() const
{
    return(itsRemoteSfp);
}
//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::SetRxSelected(bool theSelected)
{
    itsRxSelected = theSelected;
}
//////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::GetRxSelected() const
{
    return(itsRxSelected);
}

//////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::DebugPPPCommand(char command)
{
    // Does nothing in simulation
    return;
}

void   TSPII_DcclIf::DebugLapdCommand(char command)
{
    return;
}


///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DcclIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLinkState = itsProtocolLinkState;
    int aDccLinkType = itsDccLinkType;
    int aTransferMode = itsTransferMode;
    int aSideAssignment = itsSideAssignment;
    int aAddressType = itsAddressType;
    int aBroadcastMode = itsBroadcastMode;
    int aSelectionMode = itsSelectionMode;

    // Monitor attributes
    theStream << aLinkState;
    theStream << itsTunnelSessionState;
    theStream << itsDroppedPacketsCount;
    theStream << itsDefectsChanged;
    theStream << itsMagicNumber;
    
    // Configuration attributes
    theStream << aDccLinkType;
    theStream << itsProtocolLinkEnabled;
    theStream << itsLinkRouterId;
    theStream << itsRouterShelfId;
    theStream << itsIntfID;
    theStream << aTransferMode;
    theStream << itsRetransmissionCount;
    theStream << itsAckWaitTimer;
    theStream << itsMaxFrameSize;
    theStream << itsFrameCount;
    theStream << itsInactivityTimer;
    theStream << aSideAssignment;
    theStream << itsSequenceRange;
    theStream << itsFollowProtection;
    theStream << aAddressType;
    theStream << itsSourceIpAddress;
    theStream << itsSubnetMask;
    theStream << itsDestIpAddress;
    theStream << itsAutoDiscEnabled;
    theStream << itsIpEnabled;
    theStream << itsMaxReceiveUnits;
    theStream << itsRestartTimer;
    theStream << itsMaxTerminateValue;
    theStream << itsMaxConfigureValue;
    theStream << itsMaxFailureValue;
    theStream << itsFCS;
    theStream << aBroadcastMode;
    theStream << aSelectionMode;
    theStream << itsRemoteSfp;
    theStream << itsRxSelected;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DcclIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aLinkState;
    int aDccLinkType;
    int aTransferMode;
    int aSideAssignment;
    int aAddressType;
    int aBroadcastMode;
    int aSelectionMode;

    // Monitor attributes
    theStream >> aLinkState;
    theStream >> itsTunnelSessionState;
    theStream >> itsDroppedPacketsCount;
    theStream >> itsDefectsChanged;
    theStream >> itsMagicNumber;
    
    // Configuration attributes
    theStream >> aDccLinkType;
    theStream >> itsProtocolLinkEnabled;
    theStream >> itsLinkRouterId;
    theStream >> itsRouterShelfId;
    theStream >> itsIntfID;
    theStream >> aTransferMode;
    theStream >> itsRetransmissionCount;
    theStream >> itsAckWaitTimer;
    theStream >> itsMaxFrameSize;
    theStream >> itsFrameCount;
    theStream >> itsInactivityTimer;
    theStream >> aSideAssignment;
    theStream >> itsSequenceRange;
    theStream >> itsFollowProtection;
    theStream >> aAddressType;
    theStream >> itsSourceIpAddress;
    theStream >> itsSubnetMask;
    theStream >> itsDestIpAddress;
    theStream >> itsAutoDiscEnabled;
    theStream >> itsIpEnabled;
    theStream >> itsMaxReceiveUnits;
    theStream >> itsRestartTimer;
    theStream >> itsMaxTerminateValue;
    theStream >> itsMaxConfigureValue;
    theStream >> itsMaxFailureValue;
	theStream >> itsFCS;
    theStream >> aBroadcastMode;
    theStream >> aSelectionMode;
    theStream >> itsRemoteSfp;
    theStream >> itsRxSelected;

    itsProtocolLinkState = (CT_DCC_LinkState) aLinkState;
    itsDccLinkType = (CT_DCC_LinkType) aDccLinkType;
    itsTransferMode = (CT_LPF_TxMode)  aTransferMode;
    itsSideAssignment = (CT_LPF_Side)  aSideAssignment;
    itsAddressType = (CT_DCC_TL_AddrType) aAddressType;
    itsBroadcastMode = (CT_DCC_BroadcastMode) aBroadcastMode;
    itsSelectionMode = (CT_DCC_SelectionMode) aSelectionMode;

    RefreshSet();
    
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_DcclIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLinkState = itsProtocolLinkState;
    int aDccLinkType = itsDccLinkType;
    int aTransferMode = itsTransferMode;
    int aSideAssignment = itsSideAssignment;
    int aAddressType = itsAddressType;
    int aBroadcastMode = itsBroadcastMode;
    int aSelectionMode = itsSelectionMode;

    // Monitor attributes
    theStream << FC_InsertVar(aLinkState);
    theStream << FC_InsertVar(itsTunnelSessionState);
    theStream << FC_InsertVar(itsDroppedPacketsCount);
    theStream << FC_InsertVar(itsDefectsChanged);
    theStream << FC_InsertVar(itsMagicNumber);
    
    // Configuration attributes
    theStream << FC_InsertVar(aDccLinkType);
    theStream << FC_InsertVar(itsProtocolLinkEnabled);
    theStream << FC_InsertVar(itsLinkRouterId);
    theStream << FC_InsertVar(itsRouterShelfId);
    theStream << FC_InsertVar(itsIntfID);
    theStream << FC_InsertVar(aTransferMode);
    theStream << FC_InsertVar(itsRetransmissionCount);
    theStream << FC_InsertVar(itsAckWaitTimer);
    theStream << FC_InsertVar(itsMaxFrameSize);
    theStream << FC_InsertVar(itsFrameCount);
    theStream << FC_InsertVar(itsInactivityTimer);
    theStream << FC_InsertVar(aSideAssignment);
    theStream << FC_InsertVar(itsSequenceRange);
    theStream << FC_InsertVar(itsFollowProtection);
    theStream << FC_InsertVar(aAddressType);
    theStream << FC_InsertVar(itsSourceIpAddress);
    theStream << FC_InsertVar(itsSubnetMask);
    theStream << FC_InsertVar(itsDestIpAddress);
    theStream << FC_InsertVar(itsAutoDiscEnabled);
    theStream << FC_InsertVar(itsIpEnabled);
    theStream << FC_InsertVar(itsMaxReceiveUnits);
    theStream << FC_InsertVar(itsRestartTimer);
    theStream << FC_InsertVar(itsMaxTerminateValue);
    theStream << FC_InsertVar(itsMaxConfigureValue);
    theStream << FC_InsertVar(itsMaxFailureValue);
    theStream << FC_InsertVar(itsFCS);
    theStream << FC_InsertVar(aBroadcastMode);
    theStream << FC_InsertVar(aSelectionMode);
    theStream << FC_InsertVar(itsRemoteSfp);
    theStream << FC_InsertVar(itsRxSelected);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_DcclIf::ReadObject(istream & theStream)
{
    int aLinkState;
    int aDccLinkType;
    int aTransferMode;
    int aSideAssignment;
    int aAddressType;
    int aBroadcastMode;
    int aSelectionMode;

    // Monitor attributes
    // 
    theStream >> FC_ExtractVar(aLinkState);
    theStream >> FC_ExtractVar(itsDroppedPacketsCount);
    theStream >> FC_ExtractVar(itsDefectsChanged);
    theStream >> FC_ExtractVar(itsMagicNumber);
    
    // Configuration attributes
    theStream >> FC_ExtractVar(aDccLinkType);
    theStream >> FC_ExtractVar(itsProtocolLinkEnabled);
    theStream >> FC_ExtractVar(itsLinkRouterId);
    theStream >> FC_ExtractVar(itsRouterShelfId);
    theStream >> FC_ExtractVar(itsIntfID);
    theStream >> FC_ExtractVar(aTransferMode);
    theStream >> FC_ExtractVar(itsRetransmissionCount);
    theStream >> FC_ExtractVar(itsAckWaitTimer);
    theStream >> FC_ExtractVar(itsMaxFrameSize);
    theStream >> FC_ExtractVar(itsFrameCount);
    theStream >> FC_ExtractVar(itsInactivityTimer);
    theStream >> FC_ExtractVar(aSideAssignment);
    theStream >> FC_ExtractVar(itsSequenceRange);
    theStream >> FC_ExtractVar(itsFollowProtection);
    theStream >> FC_ExtractVar(aAddressType);
    theStream >> FC_ExtractVar(itsSourceIpAddress);
    theStream >> FC_ExtractVar(itsSubnetMask);
    theStream >> FC_ExtractVar(itsDestIpAddress);
    theStream >> FC_ExtractVar(itsAutoDiscEnabled);
    theStream >> FC_ExtractVar(itsIpEnabled);
    theStream >> FC_ExtractVar(itsMaxReceiveUnits);
    theStream >> FC_ExtractVar(itsRestartTimer);
    theStream >> FC_ExtractVar(itsMaxTerminateValue);
    theStream >> FC_ExtractVar(itsMaxConfigureValue);
    theStream >> FC_ExtractVar(itsMaxFailureValue);
    theStream >> FC_ExtractVar(itsFCS);
    theStream >> FC_ExtractVar(aBroadcastMode);
    theStream >> FC_ExtractVar(aSelectionMode);
    theStream >> FC_ExtractVar(itsRemoteSfp);
    theStream >> FC_ExtractVar(itsRxSelected);

    itsProtocolLinkState = (CT_DCC_LinkState) aLinkState;
    itsDccLinkType = (CT_DCC_LinkType) aDccLinkType;
    itsTransferMode = (CT_LPF_TxMode)  aTransferMode;
    itsSideAssignment = (CT_LPF_Side)  aSideAssignment;
    itsAddressType = (CT_DCC_TL_AddrType) aAddressType;
    itsBroadcastMode = (CT_DCC_BroadcastMode) aBroadcastMode;
    itsSelectionMode = (CT_DCC_SelectionMode) aSelectionMode;

    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::Display(FC_Stream & theStream)
{   
    // Update H/W
    UpdateValues();
    RefreshGet();

    DisplayUnitID(theStream);
    theStream << "  DCC Link Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Link Type                = " << DISPLAY_DCC_LinkType(itsDccLinkType)       << "\n";
    theStream << "      Protocol Link Enabled    = " << DISPLAY_BOOL(itsProtocolLinkEnabled)       << "\n";
    theStream << "      Follow Protection Enabled= " << DISPLAY_BOOL(itsFollowProtection)       << "\n";
    theStream << "      Router Logical Id        = " << static_cast<uint>(itsLinkRouterId)       << "\n";
    theStream << "      Router Shelf Id          = " << dec << (itsRouterShelfId)       << "\n";
    theStream << "      Intf ID                  = " << hex << (itsIntfID)       << "\n";
    theStream << "      Transfer Mode            = " << DISPLAY_LPF_TRANSFER_MODE(itsTransferMode)       << "\n";
    theStream << "      Retransmission Count     = " << static_cast<uint>(itsRetransmissionCount)       << "\n";
    theStream << "      Ack Wait Timer           = " << dec << (itsAckWaitTimer)       << " ms\n";
    theStream << "      Max Frame Size           = " << dec << (itsMaxFrameSize)       << " bytes\n";
    theStream << "      Frame Count              = " << static_cast<uint>(itsFrameCount)       << "\n";
    theStream << "      Inactivity Timer         = " << dec << (itsInactivityTimer)       << " sec\n";
    theStream << "      Side Assignment          = " << DISPLAY_LPF_SIDE(itsSideAssignment)       << "\n";
    theStream << "      Sequence Range           = " << static_cast<uint>(itsSequenceRange)       << "\n";
    theStream << "      Address Type             = " << DISPLAY_DCC_TL_AddrType(itsAddressType)       << "\n";
	
   // theStream << "      Source IP address        = " << dec << (itsSourceIpAddress)       << "\n";
   //theStream << " 	 Subnet Mask			  = " << dec << (itsSubnetMask) 	  << "\n";
   //theStream << " 	 Destination IP address   = " << dec << (itsDestIpAddress)		 << "\n"; 

	theStream << "      Source IP address        = " << dec << 						  
		   ((itsSourceIpAddress & 0xFF000000) >> 24) << "." << 
		   ((itsSourceIpAddress & 0x00FF0000) >> 16) << "." <<
	        ((itsSourceIpAddress & 0x0000FF00) >> 8) << "." <<
                   (itsSourceIpAddress & 0x000000FF) << "\n";
	
	theStream << "      Subnet Mask              = " << dec <<
				   ((itsSubnetMask & 0xFF000000) >> 24) << "." << 
				   ((itsSubnetMask & 0x00FF0000) >> 16) << "." <<
				   ((itsSubnetMask & 0x0000FF00) >> 8) << "." <<
				   (itsSubnetMask & 0x000000FF) << "\n";
	
/*
	theStream << "      Destination IP address   = " << dec << 						  
		   ((itsDestIpAddress & 0xFF000000) >> 24) << "." << 
		   ((itsDestIpAddress & 0x00FF0000) >> 16) << "." <<
	        ((itsDestIpAddress & 0x0000FF00) >> 8) << "." <<
                   (itsDestIpAddress & 0x000000FF) << "\n";
*/
	
    theStream << "      Auto Discovery Enabled   = " << DISPLAY_BOOL(itsAutoDiscEnabled)       << "\n";
    theStream << "      IP Enabled               = " << DISPLAY_BOOL(itsIpEnabled)       << "\n";
    theStream << "      Max Frame Size           = " << dec << (itsMaxReceiveUnits)       << " bytes\n";
    theStream << "      Restart Timer            = " << static_cast<uint>(itsRestartTimer)       << " secs\n";
    theStream << "      Max Terminate Value      = " << static_cast<uint>(itsMaxTerminateValue)       << " packets\n";
    theStream << "      Max Configure Value      = " << static_cast<uint>(itsMaxConfigureValue)       << " packets\n";
    theStream << "      Max Failure Value        = " << static_cast<uint>(itsMaxFailureValue)       << " packets\n";
    theStream << "      PPP Frame Check Sequence = " << static_cast<uint>(itsFCS)       << " bits\n";
    theStream << "      Broadcast Mode           = " << DISPLAY_DCC_BroadcastMode(itsBroadcastMode) << "\n";
    theStream << "      Selection Mode           = " << DISPLAY_DCC_SelectionMode(itsSelectionMode) << "\n";
    theStream << "      Remote Sfp               = " << static_cast<uint>(itsRemoteSfp)             << "\n";
    theStream << "      Selected for Rx traffic  = " << DISPLAY_BOOL(itsRxSelected)                   << "\n";

    theStream << "    MONITORING\n";
    theStream << "      Protocol Link State      = " << DISPLAY_DCC_LinkState(itsProtocolLinkState)         << "\n";
    theStream << "      Tunnel Session State     = " << DISPLAY_BOOL(itsTunnelSessionState)        << "\n";
    theStream << "      Dropped Packets Count    = " << dec << itsDroppedPacketsCount        << "\n";
    theStream << "      Defects Changed          = " << DISPLAY_BOOL(itsDefectsChanged)        << "\n";
    theStream << "      MagicNumber              = " << dec << itsMagicNumber        << "\n";
    
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::DisplayUnitID(FC_Stream & theStream)
{
    // To be implemented in application
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::Set(int argc, char ** argv)
{

    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "linktype") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_DCC_PPP_LINK; i++) 
        {
            if (strcmp(argv[1], DISPLAY_DCC_LinkType(i)) == 0)
            {
                SetDccLinkType((CT_DCC_LinkType)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "linkenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetProtocolLinkEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetProtocolLinkEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "protectionenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetFollowProtection(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetFollowProtection(false);
        }
        else
        {
            printUsage = true;
        }

    }
    else if ((argc == 2) && strcmp(argv[0], "routerlogicalid") == 0)
    {
        SetLinkRouterID((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "routershelfid") == 0)
    {
        SetRouterShelfID((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "intfid") == 0)
    {
        SetIntfID((uint32)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "transfermode") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_LPF_AITS; i++) 
        {
            if (strcmp(argv[1], DISPLAY_LPF_TRANSFER_MODE(i)) == 0)
            {
                SetTransferMode((CT_LPF_TxMode)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "rexmitcount") == 0)
    {
        SetRetransmissionCount((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "ackwaittimer") == 0)
    {
        SetAckWaitTimer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxframesize") == 0)
    {
        SetMaxFrameSize((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "framecount") == 0)
    {
        SetFrameCount((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "inactivitytimer") == 0)
    {
        SetInactivityTimer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "side") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_LPF_Auto; i++) 
        {
            if (strcmp(argv[1], DISPLAY_LPF_SIDE(i)) == 0)
            {
                SetSideAssignment((CT_LPF_Side)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "sequence") == 0)
    {
        if ((strcmp(argv[1], "8") == 0) || 
            (strcmp(argv[1], "128") == 0))
        {
            SetSequenceRange((uint8)strtoul(argv[1], NULL, 0));
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "addresstype") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_DCC_PPP_LINK; i++) 
        {
            if (strcmp(argv[1], DISPLAY_DCC_TL_AddrType(i)) == 0)
            {
                SetAddressType((CT_DCC_TL_AddrType)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "sourceipaddr") == 0)
    {
        SetSourceIpAddress((uint32)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "subnetmask") == 0)
    {
        SetSubnetMask((uint32)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "destipaddr") == 0)
    {
        SetDestIpAddress((uint32)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "autodisc") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAutoDiscEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAutoDiscEnabled(false);
        }
        else
        {
            printUsage = true;
        }

    }
    else if ((argc == 2) && strcmp(argv[0], "ipenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIpEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIpEnabled(false);
        }
        else
        {
            printUsage = true;
        }

    }
    else if ((argc == 2) && strcmp(argv[0], "maxrecvunits") == 0)
    {
        SetMaxReceiveUnits((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "restarttimer") == 0)
    {
        SetRestartTimer((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxtermvalue") == 0)
    {
        SetMaxTerminateValue((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxconfvalue") == 0)
    {
        SetMaxConfigureValue((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "maxfailurevalue") == 0)
    {
        SetMaxFailureValue((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "fcs") == 0)
    {
        SetFCS((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "debug") == 0)
    {
        if(itsDccLinkType == CT_DCC_LAPD_LINK)
        {
            DebugLapdCommand((char)argv[1][0]);

        }
        else
        {
            DebugPPPCommand((char)argv[1][0]);
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "broadcastmode") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_DCC_MASTER; i++) if (strcmp(argv[1], DISPLAY_DCC_BroadcastMode(i)) == 0)
        {
            SetDccBroadcastMode((CT_DCC_BroadcastMode)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "selectionmode") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_DCC_REMOTE; i++) if (strcmp(argv[1], DISPLAY_DCC_SelectionMode(i)) == 0)
        {
            SetDccSelectionMode((CT_DCC_SelectionMode)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "remotesfp") == 0)
    {
        SetDccRemoteSfp((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "rxselected") == 0)
    {
        SetRxSelected( (argv[1][0]=='y') ? true : false);
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    linktype                 <PppLink|LapdLink|NotConfigured|Unknown>\n"
                   "    linkenabled              <on|off>\n"
                   "    protectionenabled        <on|off>\n"
                   "    routerlogicalid          <1 ... 15>\n"
                   "    routershelfid            <1 ... 16>\n"
                   "    intfid                   <32bit>\n"
                   "    transfermode             <UITS|AITS>\n"
                   "    rexmitcount              <2 ... 16>\n"
                   "    ackwaittimer             <200 ... 20000ms>\n"
                   "    maxframesize             <512 ... 1500bytes>\n"
                   "    framecount               <1 ... 127>\n"
                   "    inactivitytimer          <4 ... 300s>\n"
                   "    side                     <User|Network|Auto>\n"
                   "    sequence                 <8|128>\n"
                   "    addresstype              <Numbered|UnNumbered|None|Unknown>\n"
                   "    sourceipaddr             <32bit>\n"
                   "    subnetmask               <32bit>\n"
                   "    destipaddr               <32bit>\n"
                   "    autodisc                 <on|off>\n"
                   "    ipenabled                <on|off>\n"
                   "    maxrecvunits             <64 ... 65535>\n"
                   "    restarttimer             <1 ... 10>\n"
                   "    maxtermvalue             <2 ... 10>\n"
                   "    maxconfvalue             <4 ... 20>\n"
                   "    maxfailurevalue          <2 ... 10>\n"
                   "    broadcastmode            <TRANSPARENT|TERMINATE|SLAVE|MASTER>\n"  
                   "    selectionmode            <LOCAL|REMOTE>\n"  
                   "    remotespf                <1 .. 14 | 15(no protection)>\n" 
                   "    rxselected               <yes|no>\n" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DcclIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "linkstate") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_DCC_LINK_STATE_UNKNOWN; i++) 
        {
            if (strcmp(argv[1], DISPLAY_DCC_LinkState(i)) == 0)
            {
                itsProtocolLinkState = ((CT_DCC_LinkState)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "tunnelsessionmon") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsTunnelSessionState = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsTunnelSessionState = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "defectsmon") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsDefectsChanged = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsDefectsChanged = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "droppedpacketcount") == 0))
    {
        itsDroppedPacketsCount = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "incdroppedpacketcount") == 0))
    {
        itsDroppedPacketsCount += strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "magicnumber") == 0))
    {
        itsMagicNumber = strtoul(argv[1], NULL, 0);
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    droppedpacketcount    <0 ... 0xFFFFFFFF>\n"
                   "    incdroppedpacketcount <0 ... 0xFFFFFFFF>\n"
                   "    magicnumber           <32bit>\n"
                   "    defectsmon            <on|off>\n"
                   "    tunnelsessionmon      <on|off>\n"
                   "    linkstate             <Incomplete|Down|Up|Unknown>" << endl;
    }
    
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DcclIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
