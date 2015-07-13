//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Drtr.h"
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>
#include <CommonTypes/CT_FacilityIds.h>


CFG_Drtr::CFG_Drtr(uint32 theIndex):
    CFG_Object(theIndex)
{
    Reset();
}

CFG_Drtr::~CFG_Drtr(void)
{
}

//Set Command Sequence
void CFG_Drtr::SetCommandSequence(CT_DCC_Sequence theCommandSequence)
{
    myCommandSequence = theCommandSequence;
}

//Get Command Sequence
CT_DCC_Sequence CFG_Drtr::GetCommandSequence() const
{
    return myCommandSequence;
}


// Set Drtr TID ID
void CFG_Drtr::SetTIDID(CT_AreaAddr& theTIDID)
{
    myTIDID = theTIDID;
}

//Get TID ID
CT_AreaAddr CFG_Drtr::GetTIDID() const
{
    return myTIDID;
}


//Set Router ID
void CFG_Drtr::SetRouterID(CT_DCC_RouterId theRouterID)
{
    myRouterID = theRouterID;
}

//Get Router ID
CT_DCC_RouterId CFG_Drtr::GetRouterID() const
{
    return myRouterID;
}


//This method is used to indicate that the Drtr facility is configured (for LED)
void CFG_Drtr::SetDCCRouterEnabled(bool theDCCRouterEnabled)
{
    myDCCRouterEnabled = theDCCRouterEnabled;
}

//This method returns the state of the Drtr facility.
bool CFG_Drtr::GetDCCRouterEnabled() const
{
    return myDCCRouterEnabled;
}


//Set Router Is Provisioned field
void CFG_Drtr::SetIsProvisioned(bool theIsProvisioned)
{
    myIsProvisioned = theIsProvisioned;
}

//Get Router Is Provisioned field
bool CFG_Drtr::GetIsProvisioned() const
{
    return myIsProvisioned;
}


// Set Drtr Primary Address
void CFG_Drtr::SetPrimaryAreaAddr(CT_AreaAddr& thePrimaryAreaAddr)
{
    myPrimaryAreaAddr = thePrimaryAreaAddr;
}

//Get Drtr Primary Address
CT_AreaAddr CFG_Drtr::GetPrimaryAreaAddr() const
{
    return myPrimaryAreaAddr;
}


// Set Drtr First Aux Address
void CFG_Drtr::SetFirstAuxAreaAddr(CT_AreaAddr& theFirstAuxAreaAddr)
{
    myFirstAuxAreaAddr = theFirstAuxAreaAddr;
}

//Get Drtr First Aux Address
CT_AreaAddr CFG_Drtr::GetFirstAuxAreaAddr() const
{
    return myFirstAuxAreaAddr;
}

// Set Drtr Second Aux Address
void CFG_Drtr::SetSecondAuxAreaAddr(CT_AreaAddr& theSecondAuxAreaAddr)
{
    mySecondAuxAreaAddr = theSecondAuxAreaAddr;
}

//Get Drtr Second Aux Address
CT_AreaAddr CFG_Drtr::GetSecondAuxAreaAddr() const
{
    return mySecondAuxAreaAddr;
}

// Set the PGNE 1 IP Address for the GRE Tunnel.
void CFG_Drtr::SetPgne1IpAddress(uint32 thePgneIpAddress)
{
    myPgne1IpAddress = thePgneIpAddress;
}

// Get the PGNE 1 IP Address for the GRE Tunnel.
uint32 CFG_Drtr::GetPgne1IpAddress() const
{
    return myPgne1IpAddress;
}

// Set the PGNE 2 IP Address for the GRE Tunnel.
void CFG_Drtr::SetPgne2IpAddress(uint32 thePgneIpAddress)
{
    myPgne2IpAddress = thePgneIpAddress;
}

// Get the PGNE 2 IP Address for the GRE Tunnel.
uint32 CFG_Drtr::GetPgne2IpAddress() const
{
    return myPgne2IpAddress;
}

// Set DRTR Maximum Number of Area Addresses
void CFG_Drtr::SetMaxNumAddr(uint8 theMaxNumAddr)
{
    myMaxNumAddr = theMaxNumAddr;
}

//Get DRTR Maximum Number of Area Addresses
uint8 CFG_Drtr::GetMaxNumAddr() const
{
    return myMaxNumAddr;
}


// Set Drtr Routing System ID
void CFG_Drtr::SetRoutingSystemID(CT_AreaAddr& theRoutingSystemID)
{
    myRoutingSystemID = theRoutingSystemID;
}

//Get Drtr Routing System ID
CT_AreaAddr CFG_Drtr::GetRoutingSystemID() const
{
    return myRoutingSystemID;
}


// Set DRTR Routing Level
void CFG_Drtr::SetRoutingLevel(uint8 theRoutingLevel)
{
    myRoutingLevel = theRoutingLevel;
}

// Get DRTR Routing Level
uint8 CFG_Drtr::GetRoutingLevel() const
{
    return myRoutingLevel;
}


// Set DRTR Maximum Lifetime Control
void CFG_Drtr::SetMaxLifetimeControl(uint8 theMaxLifetimeControl)
{
    myMaxLifetimeControl = theMaxLifetimeControl;
}

// Set DRTR Maximum Lifetime Control
uint8 CFG_Drtr::GetMaxLifetimeControl() const
{
    return myMaxLifetimeControl;
}


void CFG_Drtr::Reset(void)
{
    // Initialize all attributes to default values.
    myCommandSequence = CT_DCC_IDLE;

    // For Router
    CT_AreaAddr aTID("aTIDDefault");
    SetTIDID(aTID);
    myRouterID = 0;
    myDCCRouterEnabled = false;
    myIsProvisioned = false;
    //string aMessage(" "); aMessage.resize(13,"anAreaDefault");
    CT_AreaAddr anAddr("anAreaDefault");
    SetPrimaryAreaAddr(anAddr);
    SetFirstAuxAreaAddr(anAddr);
    SetSecondAuxAreaAddr(anAddr);
    myMaxNumAddr = 0;
    CT_AreaAddr anID("SystemID");
    SetRoutingSystemID(anID);
    myRoutingLevel = 0;
    myMaxLifetimeControl = 0;
    myPgne1IpAddress = 0;
    myPgne2IpAddress = 0;
}

ostream& CFG_Drtr::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint8 aCommandSequence = (uint8) myCommandSequence;

    theStream   << FC_InsertVar(aCommandSequence);

    theStream   << FC_InsertVar(myTIDID);
    theStream   << FC_InsertVar(myRouterID);
    theStream   << FC_InsertVar(myDCCRouterEnabled);
    theStream   << FC_InsertVar(myIsProvisioned);
    theStream   << FC_InsertVar(myPrimaryAreaAddr);
    theStream   << FC_InsertVar(myFirstAuxAreaAddr);
    theStream   << FC_InsertVar(mySecondAuxAreaAddr);
    theStream   << FC_InsertVar(myMaxNumAddr);
    theStream   << FC_InsertVar(myRoutingSystemID);
    theStream   << FC_InsertVar(myRoutingLevel);
    theStream   << FC_InsertVar(myMaxLifetimeControl);
    theStream   << FC_InsertVar(myPgne1IpAddress);
    theStream   << FC_InsertVar(myPgne2IpAddress);

    return theStream;
}

istream& CFG_Drtr::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint8 aCommandSequence = 0;

    theStream   >> FC_ExtractVar(aCommandSequence);

    theStream   >> FC_ExtractVar(myTIDID);
    theStream   >> FC_ExtractVar(myRouterID);
    theStream   >> FC_ExtractVar(myDCCRouterEnabled);
    theStream   >> FC_ExtractVar(myIsProvisioned);
    theStream   >> FC_ExtractVar(myPrimaryAreaAddr);
    theStream   >> FC_ExtractVar(myFirstAuxAreaAddr);
    theStream   >> FC_ExtractVar(mySecondAuxAreaAddr);
    theStream   >> FC_ExtractVar(myMaxNumAddr);
    theStream   >> FC_ExtractVar(myRoutingSystemID);
    theStream   >> FC_ExtractVar(myRoutingLevel);
    theStream   >> FC_ExtractVar(myMaxLifetimeControl);
    theStream   >> FC_ExtractVar(myPgne1IpAddress);
    theStream   >> FC_ExtractVar(myPgne2IpAddress);

    // Set the enums
    myCommandSequence = (CT_DCC_Sequence) aCommandSequence;

    return theStream;
}

FC_Stream& CFG_Drtr::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << (uint8) myCommandSequence;

    theStream   << myTIDID;
    theStream   << myRouterID;
    theStream   << myDCCRouterEnabled;
    theStream   << myIsProvisioned;
    theStream   << myPrimaryAreaAddr;
    theStream   << myFirstAuxAreaAddr;
    theStream   << mySecondAuxAreaAddr;
    theStream   << myMaxNumAddr;
    theStream   << myRoutingSystemID;
    theStream   << myRoutingLevel;
    theStream   << myMaxLifetimeControl;
    theStream   << myPgne1IpAddress;
    theStream   << myPgne2IpAddress;

    return theStream;
}

FC_Stream& CFG_Drtr::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint8 aCommandSequence = 0;

    theStream   >> aCommandSequence;

    theStream   >> myTIDID;
    theStream   >> myRouterID;
    theStream   >> myDCCRouterEnabled;
    theStream   >> myIsProvisioned;
    theStream   >> myPrimaryAreaAddr;
    theStream   >> myFirstAuxAreaAddr;
    theStream   >> mySecondAuxAreaAddr;
    theStream   >> myMaxNumAddr;
    theStream   >> myRoutingSystemID;
    theStream   >> myRoutingLevel;
    theStream   >> myMaxLifetimeControl;
    theStream   >> myPgne1IpAddress;
    theStream   >> myPgne2IpAddress;

    // Set the enums
    myCommandSequence = (CT_DCC_Sequence) aCommandSequence;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Drtr::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto DrtrERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);


    if (!strncmp(aParam,"comman",6))
    {
        SetCommandSequence(CFG_STRING_TO_DCC_SEQUENCE(argv[1]));
    }
    else if (!strncmp(aParam,"tid",3))
    {
        string aMessage(argv[1]); aMessage.resize(13,' ');
        CT_AreaAddr aTID(aMessage);
        SetTIDID(aTID);
    }
    else if (!strncmp(aParam,"routerid",8))
    {
        SetRouterID(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"routeren",8))
    {
        SetDCCRouterEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"isprov",6))
    {
        SetIsProvisioned(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"prim",4))
    {
        string aMessage(argv[1]); aMessage.resize(13,' ');
        CT_AreaAddr anAddr(aMessage);
        SetPrimaryAreaAddr(anAddr);
    }
    else if (!strncmp(aParam,"first",5))
    {
        string aMessage(argv[1]); aMessage.resize(13,' ');
        CT_AreaAddr anAddr(aMessage);
        SetFirstAuxAreaAddr(anAddr);
    }
    else if (!strncmp(aParam,"secon",5))
    {
        string aMessage(argv[1]); aMessage.resize(13,' ');
        CT_AreaAddr anAddr(aMessage);
        SetSecondAuxAreaAddr(anAddr);
    }
    else if (!strncmp(aParam,"maxnum",6))
    {
        SetMaxNumAddr(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"sys",3))
    {
        string aMessage(argv[1]); aMessage.resize(13,' ');
        CT_AreaAddr anAddr(aMessage);
        SetRoutingSystemID(anAddr);
    }
    else if (!strncmp(aParam,"level",5))
    {
        SetRoutingLevel(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"maxlif",6))
    {
        SetMaxLifetimeControl(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"greenable",9))
    {
        SetPgne1IpAddress(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else
    {
        goto DrtrERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

DrtrERROR:
    {
        fc_cout << "drtr <commandseq>    <Idle|tidbegin|tidcommit|routerbegin|routercommit|tarpbegin|tarpcommit|linkbegin|linkcrouterbommit>" << endl;
        fc_cout << "drtr <tidid>         <13-byte hex value> " << endl;
        fc_cout << "drtr <routerid>      <1-15> " << endl;
        fc_cout << "drtr <routeren>      <e-nable|d-isable> " << endl;
        fc_cout << "drtr <isprovisioned> <e-nable|d-isable> " << endl;
        fc_cout << "drtr <primaryaddr>   <13-byte hex value> " << endl;
        fc_cout << "drtr <firstaux>      <13-byte hex value> " << endl;
        fc_cout << "drtr <secondaux>     <13-byte hex value> " << endl;
        fc_cout << "drtr <maxnumaddr>    <1-3> " << endl;
        fc_cout << "drtr <systemid>      <8-byte hex value> " << endl;
        fc_cout << "drtr <level>         <1-3> " << endl;
        fc_cout << "drtr <maxlifetime>   <1-255> " << endl;
        fc_cout << "drtr <greenable>     <4 byte hex value> " <<endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Drtr::Display( FC_Stream& theStream )
{
    theStream   << "DRTR       - Command Sequence      [commandseq]       = " << DISPLAY_DCC_SEQUENCE(myCommandSequence) << endl;

    theStream   << "DRTR       - TID ID                [tidid]            = " << myTIDID.GetAreaPrintable(false)   << endl;
    theStream   << "DRTR       - Router ID             [routerid]         = " << uint32(myRouterID) << endl;
    theStream   << "DRTR       - Router Enabled        [routerenabled]    = " << DISPLAY_BOOL(myDCCRouterEnabled) << endl;
    theStream   << "DRTR       - Router Is Provisioned [isprovisioned]    = " << DISPLAY_BOOL(myIsProvisioned) << endl;
    theStream   << "DRTR       - Primary Address       [primaryaddr]      = " << myPrimaryAreaAddr.GetAreaPrintable(false)   << endl;
    theStream   << "DRTR       - First Aux Address     [firstauxaddr]     = " << myFirstAuxAreaAddr.GetAreaPrintable(false)   << endl;
    theStream   << "DRTR       - Second Aux Address    [secondauxaddr]    = " << mySecondAuxAreaAddr.GetAreaPrintable(false)   << endl;
    theStream   << "DRTR       - Max Num Area Addr     [maxnumaddr]       = " << uint32(myMaxNumAddr) << endl;
    theStream   << "DRTR       - System ID             [systemid]         = " << myRoutingSystemID.GetAreaPrintable(false)   << endl;
    theStream   << "DRTR       - Routing Level         [level]            = " << uint32(myRoutingLevel) << endl;
    theStream   << "DRTR       - Max Lifetime Control  [maxlifetime]      = " << uint32(myMaxLifetimeControl) << endl;
    theStream   <<" DRTR       - PGNE 1 IP Address     [greenable1]       = " << uint32(myPgne1IpAddress) <<endl;
    theStream   <<" DRTR       - PGNE 2 IP Address     [greenable2]       = " << uint32(myPgne2IpAddress) <<endl;
    theStream   << endl;
}

