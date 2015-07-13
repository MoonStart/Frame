/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Jessica Chen - April 2011
 DESCRIPTION:Definition of the class TSPII_GccIf - Models the Generic 
             Framing Procedure termination entity.
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_GccIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_GccIf::TSPII_GccIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_GccIf::~TSPII_GccIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::RefreshGet()
{   
    // Monitor attributes
    itsProtocolLinkState        = GetProtocolLinkState();
    itsTunnelSessionState       = GetTunnelSessionState();
    itsDroppedPacketsCount      = GetDroppedPacketsCount();
    itsDefectsChanged           = GetDefectsChanged();

    // Mon PPP specific attributes
    itsMagicNumber              = GetMagicNumber();
    
    // Configuration attributes 
    itsGccLinkEnabled           = GetGCCLinkEnabled(); 
    itsIntfID                   = GetIntfID();
  
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
    itsChannel                  = GetChannel();
    itsVlanTag                  = GetVlanTag();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::RefreshSet()
{   
    // Configuration attributes    
    SetGCCLinkEnabled(itsGccLinkEnabled);
    SetIntfID(itsIntfID);    
  
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
    SetVlanChannel(itsVlanTag,itsChannel);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::Reset()
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
    itsGccLinkEnabled           = false;  
    itsIntfID                   = 0;
      
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
    itsChannel                  = 0;
    itsVlanTag                  = 0;
    RefreshSet();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetGCCLinkEnabled(bool theEnable)
{
    itsGccLinkEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccIf::GetGCCLinkEnabled() const
{
    return itsGccLinkEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetIntfID(CT_IfIndexIdent theIntfID)
{
    itsIntfID = theIntfID;
}

///////////////////////////////////////////////////////////////////////////////
CT_IfIndexIdent TSPII_GccIf::GetIntfID() const
{
    return itsIntfID;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetAddressType(CT_DCC_TL_AddrType theAddressType)
{
    itsAddressType = theAddressType;
}

/////////////////////////////////////////////////////////////////////////////
CT_DCC_TL_AddrType TSPII_GccIf::GetAddressType() const
{
    return(itsAddressType);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetSourceIpAddress(uint32 theSourceIpAddress)
{
    itsSourceIpAddress = theSourceIpAddress;
}

///////////////////////////////////////////////////////////////////////////
uint32 TSPII_GccIf::GetSourceIpAddress() const
{
    return(itsSourceIpAddress);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetSubnetMask(uint32 theSubnetMask)
{
    itsSubnetMask = theSubnetMask;
}

///////////////////////////////////////////////////////////////////////////
uint32 TSPII_GccIf::GetSubnetMask() const
{
    return(itsSubnetMask);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetDestIpAddress(uint32 theDestIpAddress)
{
    itsDestIpAddress = theDestIpAddress;
}

///////////////////////////////////////////////////////////////////////////
uint32 TSPII_GccIf::GetDestIpAddress() const
{
    return(itsDestIpAddress);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetAutoDiscEnabled(bool theEnabled)
{
    itsAutoDiscEnabled = theEnabled;
}

///////////////////////////////////////////////////////////////////////////
bool TSPII_GccIf::GetAutoDiscEnabled() const
{
    return(itsAutoDiscEnabled);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetIpEnabled(bool theEnabled)
{
    itsIpEnabled = theEnabled;
}

///////////////////////////////////////////////////////////////////////////
bool TSPII_GccIf::GetIpEnabled() const
{
    return(itsIpEnabled);
}


void TSPII_GccIf::SetVlanChannel(uint16 theVlanTag,uint8 theChannel)
{
	itsChannel = theChannel;
    itsVlanTag = theVlanTag;
}

///////////////////////////////////////////////////////////////////////////

void TSPII_GccIf::SetChannel(uint8 theChannel)
{
   itsChannel = theChannel;
}


///////////////////////////////////////////////////////////////////////////
uint8 TSPII_GccIf::GetChannel() const
{
    return (itsChannel);
}

///////////////////////////////////////////////////////////////////////////

void TSPII_GccIf::SetVlanTag(uint16 theVlanTag)
{
    itsVlanTag = theVlanTag;
}

///////////////////////////////////////////////////////////////////////////
uint16 TSPII_GccIf::GetVlanTag() const
{
    return (itsVlanTag);
}

////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetMaxReceiveUnits(uint16 theMaxReceiveUnits)
{
    itsMaxReceiveUnits = theMaxReceiveUnits;
}

///////////////////////////////////////////////////////////////////////////
uint16 TSPII_GccIf::GetMaxReceiveUnits() const
{
    return(itsMaxReceiveUnits);
}

///////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetRestartTimer(uint8 theRestartTimer)
{
    itsRestartTimer = theRestartTimer;
}

//////////////////////////////////////////////////////////////////////////
uint8 TSPII_GccIf::GetRestartTimer() const
{
    return(itsRestartTimer);
}

//////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetMaxTerminateValue(uint8 theMaxTerminateValue)
{
    itsMaxTerminateValue = theMaxTerminateValue;
}

/////////////////////////////////////////////////////////////////////////
uint8 TSPII_GccIf::GetMaxTerminateValue() const
{
    return (itsMaxTerminateValue);
}

/////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetMaxConfigureValue(uint8 theMaxConfigureValue)
{
    itsMaxConfigureValue = theMaxConfigureValue;
}

/////////////////////////////////////////////////////////////////////////
uint8 TSPII_GccIf::GetMaxConfigureValue() const
{
    return (itsMaxConfigureValue);
}

//////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetMaxFailureValue(uint8 theMaxFailureValue)
{
    itsMaxFailureValue = theMaxFailureValue;
}

//////////////////////////////////////////////////////////////////////////
uint8 TSPII_GccIf::GetMaxFailureValue() const
{
    return(itsMaxFailureValue);
}
//////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::SetFCS(uint8 theFCS)
{
    itsFCS = theFCS;
}

//////////////////////////////////////////////////////////////////////////
uint8 TSPII_GccIf::GetFCS() const
{
    return(itsFCS);
}
///////////////////////////////////////////////////////////////////////////////
CT_DCC_LinkState TSPII_GccIf::GetProtocolLinkState()
{
    return itsProtocolLinkState;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccIf::GetTunnelSessionState()
{
    return itsTunnelSessionState;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GccIf::GetDroppedPacketsCount()
{
    return itsDroppedPacketsCount;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccIf::GetDefectsChanged()
{
    return itsDefectsChanged;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_GccIf::GetMagicNumber() const
{
    return itsMagicNumber;
}

void TSPII_GccIf::UpdatePppLinkState(int theGccIndex)
{
    return;
}

//////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::DebugPPPCommand(char command)
{
    // Does nothing in simulation
    fc_cout << " DebugPPPCommand: " << command<< " for target test." << endl;
    return;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_GccIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLinkState = itsProtocolLinkState;    
    int aAddressType = itsAddressType;
    

    // Monitor attributes
    theStream << aLinkState;
    theStream << itsTunnelSessionState;
    theStream << itsDroppedPacketsCount;
    theStream << itsDefectsChanged;
    theStream << itsMagicNumber;    
    // Configuration attributes    
    theStream << itsGccLinkEnabled; 
    theStream << itsIntfID;
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
    theStream << itsChannel;
    theStream << itsVlanTag;
    
    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_GccIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aLinkState; 
    int aAddressType;

    // Monitor attributes
    theStream >> aLinkState;
    theStream >> itsTunnelSessionState;
    theStream >> itsDroppedPacketsCount;
    theStream >> itsDefectsChanged;
    theStream >> itsMagicNumber;
    
    // Configuration attributes    
    theStream >> itsGccLinkEnabled; 
    theStream >> itsIntfID;
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
    theStream >> itsChannel;
    theStream >> itsVlanTag;

    itsProtocolLinkState = (CT_DCC_LinkState) aLinkState;
    itsAddressType = (CT_DCC_TL_AddrType) aAddressType;

    RefreshSet();
    
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_GccIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLinkState = itsProtocolLinkState;
    int aAddressType = itsAddressType;
   

    // Monitor attributes
    theStream << FC_InsertVar(aLinkState);
    theStream << FC_InsertVar(itsTunnelSessionState);
    theStream << FC_InsertVar(itsDroppedPacketsCount);
    theStream << FC_InsertVar(itsDefectsChanged);
    theStream << FC_InsertVar(itsMagicNumber);
    
    // Configuration attributes   
    theStream << FC_InsertVar(itsGccLinkEnabled); 
    theStream << FC_InsertVar(itsIntfID);
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
    theStream << FC_InsertVar(itsChannel);
    theStream << FC_InsertVar(itsVlanTag);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_GccIf::ReadObject(istream & theStream)
{
    int aLinkState;
    int aAddressType;
    

    // Monitor attributes   
    theStream >> FC_ExtractVar(aLinkState);
    theStream >> FC_ExtractVar(itsTunnelSessionState);
    theStream >> FC_ExtractVar(itsDroppedPacketsCount);
    theStream >> FC_ExtractVar(itsDefectsChanged);
    theStream >> FC_ExtractVar(itsMagicNumber);
    
    // Configuration attributes    
    theStream >> FC_ExtractVar(itsGccLinkEnabled); 
    theStream >> FC_ExtractVar(itsIntfID);
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
    theStream >> FC_ExtractVar(itsChannel);
    theStream >> FC_ExtractVar(itsVlanTag);

    itsProtocolLinkState = (CT_DCC_LinkState) aLinkState;
    itsAddressType = (CT_DCC_TL_AddrType) aAddressType;    

    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::Display(FC_Stream & theStream)
{   
    // Update H/W
    UpdateValues();
    RefreshGet();

    DisplayUnitID(theStream);
    theStream << "  GCC Link Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      GCC Link Enabled         = " << DISPLAY_BOOL(itsGccLinkEnabled)       << "\n";
    theStream << "      Intf ID                  = " << hex << (itsIntfID)       << "\n";
    theStream << "      Address Type             = " << DISPLAY_DCC_TL_AddrType(itsAddressType)       << "\n";
    theStream << "      Source IP address        = " << dec << (itsSourceIpAddress)       << "\n";
    theStream << "      Subnet Mask              = " << dec << (itsSubnetMask)       << "\n";
    theStream << "      Destination IP address   = " << dec << (itsDestIpAddress)       << "\n";
    theStream << "      Auto Discovery Enabled   = " << DISPLAY_BOOL(itsAutoDiscEnabled)       << "\n";
    theStream << "      IP Enabled               = " << DISPLAY_BOOL(itsIpEnabled)       << "\n";
    theStream << "      Max Frame Size           = " << dec << (itsMaxReceiveUnits)       << " bytes\n";
    theStream << "      Restart Timer            = " << static_cast<uint>(itsRestartTimer)       << " secs\n";
    theStream << "      Max Terminate Value      = " << static_cast<uint>(itsMaxTerminateValue)       << " packets\n";
    theStream << "      Max Configure Value      = " << static_cast<uint>(itsMaxConfigureValue)       << " packets\n";
    theStream << "      Max Failure Value        = " << static_cast<uint>(itsMaxFailureValue)       << " packets\n";
    theStream << "      PPP Frame Check Sequence = " << static_cast<uint>(itsFCS)       << " bits\n";
    theStream << "      GCC channel              = " << static_cast<uint>(itsChannel)       << " bits\n";
    theStream << "      interface vlan id         = " << static_cast<uint>(itsVlanTag)       << " bits\n";
    
    theStream << "    MONITORING\n";
    theStream << "      Protocol Link State      = " << DISPLAY_DCC_LinkState(itsProtocolLinkState)         << "\n";
    theStream << "      Tunnel Session State     = " << DISPLAY_BOOL(itsTunnelSessionState)        << "\n";
    theStream << "      Dropped Packets Count    = " << dec << itsDroppedPacketsCount        << "\n";
    theStream << "      Defects Changed          = " << DISPLAY_BOOL(itsDefectsChanged)        << "\n";
    theStream << "      MagicNumber              = " << dec << itsMagicNumber        << "\n";
    
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccIf::DisplayUnitID(FC_Stream & theStream)
{
    //Do display the GCC Channel in target
    theStream << "  GCC Channel (1 based):  ? " << endl;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccIf::Set(int argc, char ** argv)
{

    bool printUsage = false;

    
    if ((argc == 2) && strcmp(argv[0], "linkenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetGCCLinkEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetGCCLinkEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }  
    else if ((argc == 2) && strcmp(argv[0], "intfid") == 0)
    {
        SetIntfID((uint32)strtoul(argv[1], NULL, 0));
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
    else if ((argc == 2) && strcmp(argv[0], "channel") == 0)
    {
        SetChannel((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "vlan") == 0)
    {
        SetVlanTag((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "debug") == 0)
    {
        DebugPPPCommand((char)argv[1][0]);
    }    
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    linkenabled              <on|off>\n"
                   "    intfid                   <32bit>\n"                 
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
                   "    fcs                      <16|32(bit)>\n"
                   "    channel                  <0 ... 60>\n"
                   "    vlan                     <32bit>\n"
                   "    debug                    <e|d|b|w|o|c|m>\n" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccIf::Simul(int argc, char ** argv)
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
void TSPII_GccIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
