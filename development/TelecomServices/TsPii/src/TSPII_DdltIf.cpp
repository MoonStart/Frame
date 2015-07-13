/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Mark Nash - Sept 2006
 DESCRIPTION:Definition of the class TSPII_DdltIf - Models the Generic 
             Framing Procedure termination entity.
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_DdltIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_DdltIf::TSPII_DdltIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DdltIf::~TSPII_DdltIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::RefreshGet()
{ 
    // Monitor attributes

    // Configuration attributes
    itsCommandSequence          = GetCommandSequence();

    itsIntfID                   = GetIntfID();
    itsProvisioned              = GetIsProvisioned();
    itsLinkRouterID             = GetLinkRouterID();
    itsRouterShelfID            = GetRouterShelfID();
    itsTransferMode             = GetTransferMode();
    itsMaxFrameSize             = GetMaxFrameSize();
    itsFollowProtection         = GetFollowProtection();

    itsProtocolLinkEnabled      = GetProtocolLinkEnabled();
    itsChecksumEnabled          = GetChecksumEnabled();
    itsHTMultiplier             = GetHoldingTimerMultiplier();
    itsConfigTimer              = GetConfigurationTimer();
    itsHelloTimer               = GetHelloTimer();
    itsDefaultMetric            = GetDefaultMetric();
    itsReDirectHoldingTimer     = GetReDirectHoldingTimer();
    itsLinkRoutingLevel         = GetLinkRoutingLevel();
    itsESConfigurationTimer     = GetESConfigurationTimer();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::RefreshSet()
{      
    // Configuration attributes
    SetCommandSequence(itsCommandSequence);

    SetIntfID(itsIntfID);
    SetIsProvisioned(itsProvisioned);
    SetLinkRouterID(itsLinkRouterID);
    SetRouterShelfID(itsRouterShelfID);
    SetTransferMode(itsTransferMode);
    SetMaxFrameSize(itsMaxFrameSize);
    SetFollowProtection(itsFollowProtection);

    SetProtocolLinkEnabled(itsProtocolLinkEnabled);
    SetChecksumEnabled(itsChecksumEnabled);
    SetHoldingTimerMultiplier(itsHTMultiplier);
    SetConfigurationTimer(itsConfigTimer);
    SetHelloTimer(itsHelloTimer);
    SetDefaultMetric(itsDefaultMetric);
    SetReDirectHoldingTimer(itsReDirectHoldingTimer);
    SetLinkRoutingLevel(itsLinkRoutingLevel);
    SetESConfigurationTimer(itsESConfigurationTimer);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes

    // Configuration attributes
    itsCommandSequence          = CT_DCC_IDLE;

    itsIntfID                   = 0;
    itsProvisioned              = false;
    itsLinkRouterID             = 0;
    itsRouterShelfID            = 0;
    itsTransferMode             = CT_LPF_AITS;
    itsMaxFrameSize             = 0;
    itsFollowProtection         = false;
    itsProtocolLinkEnabled      = false;

    itsChecksumEnabled          = false;
    itsHTMultiplier             = 0;
    itsConfigTimer              = 0;
    itsHelloTimer               = 0;
    itsDefaultMetric            = 0;
    itsReDirectHoldingTimer     = 0;
    itsLinkRoutingLevel         = 0;
    itsESConfigurationTimer     = 0;
}


// CONFIGURATION METHODS
// 

///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetCommandSequence(CT_DCC_Sequence theCommandSequence)
{
    itsCommandSequence = theCommandSequence;
}

///////////////////////////////////////////////////////////////////////////////
CT_DCC_Sequence TSPII_DdltIf::GetCommandSequence() const
{
    return itsCommandSequence;
}

// Configuration DCC Link Parameters

///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetIntfID(CT_IfIndexIdent theIntfID)
{
    itsIntfID = theIntfID;
}

///////////////////////////////////////////////////////////////////////////////
CT_IfIndexIdent TSPII_DdltIf::GetIntfID() const
{
    return itsIntfID;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetIsProvisioned(bool theProvisioned)
{
    itsProvisioned = theProvisioned;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DdltIf::GetIsProvisioned() const
{
    return itsProvisioned;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetLinkRouterID(CT_DCC_RouterId theLinkRouterID)
{
    itsLinkRouterID = theLinkRouterID;
}

///////////////////////////////////////////////////////////////////////////////
CT_DCC_RouterId TSPII_DdltIf::GetLinkRouterID() const
{
    return itsLinkRouterID;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetRouterShelfID(CT_ShelfId theShelfID)
{
    itsRouterShelfID = theShelfID;
}

///////////////////////////////////////////////////////////////////////////////
CT_ShelfId TSPII_DdltIf::GetRouterShelfID() const
{
    return itsRouterShelfID;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetProtocolLinkEnabled(bool theEnable)
{
    itsProtocolLinkEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DdltIf::GetProtocolLinkEnabled() const
{
    return itsProtocolLinkEnabled;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetTransferMode(CT_LPF_TxMode theTransferMode)
{
    itsTransferMode = theTransferMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_LPF_TxMode TSPII_DdltIf::GetTransferMode() const
{
    return itsTransferMode;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetMaxFrameSize(uint16 theMaxFrameSize)
{
    itsMaxFrameSize = theMaxFrameSize;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DdltIf::GetMaxFrameSize() const
{
    return itsMaxFrameSize;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetFollowProtection(bool theFollowProtection)
{
    itsFollowProtection = theFollowProtection;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DdltIf::GetFollowProtection() const
{
    return itsFollowProtection;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetChecksumEnabled(bool theEnable)
{
    itsChecksumEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DdltIf::GetChecksumEnabled() const
{
    return itsChecksumEnabled;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetHoldingTimerMultiplier(uint8 theHTMultiplier)
{
    itsHTMultiplier = theHTMultiplier;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DdltIf::GetHoldingTimerMultiplier() const
{
    return itsHTMultiplier;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetConfigurationTimer(uint16 theConfigTimer)
{
    itsConfigTimer = theConfigTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DdltIf::GetConfigurationTimer() const
{
    return itsConfigTimer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetHelloTimer(uint8 theHelloTimer)
{
    itsHelloTimer = theHelloTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DdltIf::GetHelloTimer() const
{
    return itsHelloTimer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetDefaultMetric(uint8 theDefaultMetric)
{
    itsDefaultMetric = theDefaultMetric;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DdltIf::GetDefaultMetric() const
{
    return itsDefaultMetric;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetReDirectHoldingTimer(uint16 theReDirectHoldingTimer)
{
    itsReDirectHoldingTimer = theReDirectHoldingTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DdltIf::GetReDirectHoldingTimer() const
{
    return itsReDirectHoldingTimer;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetLinkRoutingLevel(uint8 theLinkRoutingLevel)
{
    itsLinkRoutingLevel = theLinkRoutingLevel;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DdltIf::GetLinkRoutingLevel() const
{
    return itsLinkRoutingLevel;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::SetESConfigurationTimer(uint16 theESConfigurationTimer)
{
    itsESConfigurationTimer = theESConfigurationTimer;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DdltIf::GetESConfigurationTimer() const
{
    return itsESConfigurationTimer;
}



// MONITORING METHODS



///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DdltIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aTransferMode    = itsTransferMode;
    int aCommandSequence = itsCommandSequence;
    
    // Monitor attributes

    // Configuration attributes
    theStream << aCommandSequence;

    theStream << itsIntfID;
    theStream << itsProvisioned;
    theStream << itsLinkRouterID;
    theStream << itsRouterShelfID;
    theStream << itsProtocolLinkEnabled;
    theStream << aTransferMode;
    theStream << itsMaxFrameSize;
    theStream << itsFollowProtection;

    theStream << itsChecksumEnabled;
    theStream << itsHTMultiplier;
    theStream << itsConfigTimer;
    theStream << itsHelloTimer;
    theStream << itsDefaultMetric;
    theStream << itsReDirectHoldingTimer;
    theStream << itsLinkRoutingLevel;
    theStream << itsESConfigurationTimer;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DdltIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aTransferMode;
    int aCommandSequence;

    // Monitor attributes
    
    // Configuration attributes
    theStream >> aCommandSequence;

    theStream >> itsIntfID;
    theStream >> itsProvisioned;
    theStream >> itsLinkRouterID;
    theStream >> itsRouterShelfID;
    theStream >> itsProtocolLinkEnabled;
    theStream >> aTransferMode;
    theStream >> itsMaxFrameSize;
    theStream >> itsFollowProtection;

    theStream >> itsChecksumEnabled;
    theStream >> itsHTMultiplier;
    theStream >> itsConfigTimer;
    theStream >> itsHelloTimer;
    theStream >> itsDefaultMetric;
    theStream >> itsReDirectHoldingTimer;
    theStream >> itsLinkRoutingLevel;
    theStream >> itsESConfigurationTimer;

    itsTransferMode    = (CT_LPF_TxMode) aTransferMode;
    itsCommandSequence = (CT_DCC_Sequence) aCommandSequence;

    RefreshSet();
    
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_DdltIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aTransferMode    = itsTransferMode;
    int aCommandSequence = itsCommandSequence;

    // Monitor attributes
    
    // Configuration attributes
    theStream << FC_InsertVar(aCommandSequence);

    theStream << FC_InsertVar(itsIntfID);
    theStream << FC_InsertVar(itsProvisioned);
    theStream << FC_InsertVar(itsLinkRouterID);
    theStream << FC_InsertVar(itsRouterShelfID);
    theStream << FC_InsertVar(itsProtocolLinkEnabled);
    theStream << FC_InsertVar(aTransferMode);
    theStream << FC_InsertVar(itsMaxFrameSize);
    theStream << FC_InsertVar(itsFollowProtection);
     
    theStream << FC_InsertVar(itsChecksumEnabled);
    theStream << FC_InsertVar(itsHTMultiplier);
    theStream << FC_InsertVar(itsConfigTimer);
    theStream << FC_InsertVar(itsHelloTimer);
    theStream << FC_InsertVar(itsDefaultMetric);
    theStream << FC_InsertVar(itsReDirectHoldingTimer);
    theStream << FC_InsertVar(itsLinkRoutingLevel);
    theStream << FC_InsertVar(itsESConfigurationTimer);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_DdltIf::ReadObject(istream & theStream)
{
    int aTransferMode;
    int aCommandSequence;

    // Monitor attributes
    
    // Configuration attributes
    theStream >> FC_ExtractVar(aCommandSequence);

    theStream >> FC_ExtractVar(itsIntfID);
    theStream >> FC_ExtractVar(itsProvisioned);
    theStream >> FC_ExtractVar(itsLinkRouterID);
    theStream >> FC_ExtractVar(itsRouterShelfID);
    theStream >> FC_ExtractVar(itsProtocolLinkEnabled);
    theStream >> FC_ExtractVar(aTransferMode);
    theStream >> FC_ExtractVar(itsMaxFrameSize);
    theStream >> FC_ExtractVar(itsFollowProtection);

    theStream >> FC_ExtractVar(itsChecksumEnabled);
    theStream >> FC_ExtractVar(itsHTMultiplier);
    theStream >> FC_ExtractVar(itsConfigTimer);
    theStream >> FC_ExtractVar(itsHelloTimer);
    theStream >> FC_ExtractVar(itsDefaultMetric);
    theStream >> FC_ExtractVar(itsReDirectHoldingTimer);
    theStream >> FC_ExtractVar(itsLinkRoutingLevel);
    theStream >> FC_ExtractVar(itsESConfigurationTimer);
      
    itsTransferMode    = (CT_LPF_TxMode) aTransferMode;
    itsCommandSequence = (CT_DCC_Sequence) aCommandSequence;

    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::Display(FC_Stream & theStream)
{   
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  OSI Router Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Command Sequence         = " << DISPLAY_DCC_SEQUENCE(itsCommandSequence)       << "\n";
    theStream << "    Last DCC Link Parameters\n";
    theStream << "      Intf ID                  = " << hex << (itsIntfID)       << "\n";
    theStream << "      Link Provisioned         = " << DISPLAY_BOOL(itsProvisioned)       << "\n";
    theStream << "      Link Router ID           = " << static_cast<uint>(itsLinkRouterID)       << "\n";
    theStream << "      Router Shelf ID          = " << dec << (itsRouterShelfID)       << "\n";
    theStream << "      Protocol Link Enabled    = " << DISPLAY_BOOL(itsProtocolLinkEnabled)       << "\n";
    theStream << "      Transfer Mode            = " << DISPLAY_LPF_TRANSFER_MODE(itsTransferMode)       << "\n";
    theStream << "      Max Frame Size           = " << dec << (itsMaxFrameSize)       << " bytes\n";
    theStream << "      Follow Protection Enabled= " << DISPLAY_BOOL(itsFollowProtection)       << "\n";

    theStream << "      Checksum Enabled         = " << DISPLAY_BOOL(itsChecksumEnabled)       << "\n";
    theStream << "      Holding Timer Multiplier = " << static_cast<uint>(itsHTMultiplier)    << "\n";
    theStream << "      Config Timer             = " << dec << (itsConfigTimer)       << " sec\n";
    theStream << "      Hello Timer              = " << static_cast<uint>(itsHelloTimer)       << " sec\n";
    theStream << "      Default Metric           = " << static_cast<uint>(itsDefaultMetric)       << "\n";
    theStream << "      ReDirect Holding Timer   = " << dec << (itsReDirectHoldingTimer)       << " sec\n";
    theStream << "      Link Routing Level       = " << static_cast<uint>(itsLinkRoutingLevel)       << "\n";
    theStream << "      ES Configuration Timer   = " << dec << (itsESConfigurationTimer)       << " sec\n";

    theStream << "    MONITORING\n";
    
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DdltIf::Set(int argc, char ** argv)
{

    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "commandsequence") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_DCC_REFRESH; i++) 
        {
            if (strcmp(argv[1], DISPLAY_DCC_SEQUENCE(i)) == 0)
            {
                SetCommandSequence((CT_DCC_Sequence)i);
                printUsage = false;
                break;
            }
        }
    }
    // DCC Link Operations
    else if ((argc == 2) && strcmp(argv[0], "intfid") == 0)
    {
        SetIntfID((uint32)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "isprovisioned") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIsProvisioned(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIsProvisioned(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "linkrouterid") == 0)
    {
        SetLinkRouterID((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "routershelfid") == 0)
    {
        SetRouterShelfID((uint8)strtoul(argv[1], NULL, 0));
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
    else if ((argc == 2) && strcmp(argv[0], "maxframesize") == 0)
    {
        SetMaxFrameSize((uint16)strtoul(argv[1], NULL, 0));
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
 
    else if ((argc == 2) && strcmp(argv[0], "chksumenabled") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetChecksumEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetChecksumEnabled(false);
        }
        else
        {
            printUsage = true;
        }

    } 
    else if ((argc == 2) && strcmp(argv[0], "holdingtimermult") == 0)
    {
        SetHoldingTimerMultiplier((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "configtimer") == 0)
    {
        SetConfigurationTimer((uint16)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "hellotimer") == 0)
    {
        SetHelloTimer((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "metric") == 0)
    {
        SetDefaultMetric((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "redirecttimer") == 0)
    {
        SetReDirectHoldingTimer((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "linkroutelevel") == 0)
    {
        SetLinkRoutingLevel((uint8)strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && strcmp(argv[0], "esconfigtimer") == 0)
    {
        SetESConfigurationTimer((uint16)strtoul(argv[1], NULL, 0));
    }
    
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << 

                   "    commandsequence          <Idle|TIDIdBegin|TIDIdCommit|RouterBegin|RouterCommit|TarpBegin|TarpCommit|LinkBegin|LinkCommit>\n"
                   "    isprovisioned            <on|off>\n"
                   "    intfid                   <32bit>\n"
                   "    linkrouterid             <1 ... 15>\n"
                   "    routershelfid            <1 ... 16>\n"
                   "    linkenabled              <on|off>\n"
                   "    transfermode             <UITS|AITS>\n"
                   "    maxframesize             <512 ... 1500bytes>\n"
                   "    protectionenabled        <on|off>\n"
                   "    chksumenabled            <on|off>\n"
                   "    holdingtimermult         <2 ... 63>\n"
                   "    configtimer              <1 ... 3s>\n" 
                   "    hellotimer               <2 ... 50s>\n"
                   "    metric                   <0 ... 63>\n"
                   "    redirecttimer            <2 ... 600s>\n"
                   "    linkroutelevel           <2 ... 3>\n"
                   "    esconfigtimer            <1 ... 600s>\n" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DdltIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DdltIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
