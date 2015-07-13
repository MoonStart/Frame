//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_DcclAltConfig.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_Dccp::CFG_Dccp(uint32 theIndex):
    CFG_Object(theIndex),
    myAddressType(CT_DCC_TL_UNKNOWN_TYPE),
    mySourceIpAddress(0),
    mySubnetMask(0),
    myDestIpAddress(0),
    myIfIndex(0),
    myAutoDiscEnabled(false),
    myIpEnabled(false),
    myPprfId(UNKNOWN_Link_Profile_ID),
    myIsProvisioned(false),
    myProtocolLinkEnabled(false),
    myFollowProtectionEnabled(false)
{
}

CFG_Dccp::~CFG_Dccp(void)
{
}

void CFG_Dccp::SetAddressType(CT_DCC_TL_AddrType theAddressType)
{
    myAddressType = theAddressType;
}

CT_DCC_TL_AddrType CFG_Dccp::GetAddressType() const
{
    return myAddressType;
}


void CFG_Dccp::SetSourceIpAddress(uint32 theSourceIpAddress)
{
    mySourceIpAddress = theSourceIpAddress;
}

uint32 CFG_Dccp::GetSourceIpAddress() const
{
    return mySourceIpAddress;
}


void CFG_Dccp::SetSubnetMask(uint32 theSubnetMask)
{
    mySubnetMask = theSubnetMask;
}

uint32 CFG_Dccp::GetSubnetMask() const
{
    return mySubnetMask;
}

void CFG_Dccp::SetIfIndex(uint32 theIfIndex)
{
    myIfIndex = theIfIndex;
}

uint32 CFG_Dccp::GetIfIndex() const
{
    return myIfIndex;
}

void CFG_Dccp::SetDestIpAddress(uint32 theDestIpAddress)
{
    myDestIpAddress = theDestIpAddress;
}

uint32 CFG_Dccp::GetDestIpAddress() const
{
    return myDestIpAddress;
}


void CFG_Dccp::SetAutoDiscEnabled(bool theEnabled)
{
    myAutoDiscEnabled = theEnabled;
}

bool CFG_Dccp::GetAutoDiscEnabled() const
{
    return myAutoDiscEnabled;
}


void CFG_Dccp::SetIpEnabled(bool theEnabled)
{
    myIpEnabled = theEnabled;
}

bool CFG_Dccp::GetIpEnabled() const
{
    return myIpEnabled;
}


void CFG_Dccp::SetPppProfileID(CT_Link_ProfileId thePprfId)
{
    myPprfId = thePprfId;
}

CT_Link_ProfileId CFG_Dccp::GetPppProfileID() const
{
    return myPprfId;
}


//Set Link Is Provisioned field
void CFG_Dccp::SetIsProvisioned(bool theIsProvisioned)
{
    myIsProvisioned = theIsProvisioned;
}

//Get Link s Provisioned field
bool CFG_Dccp::GetIsProvisioned() const
{
    return myIsProvisioned;
}


void CFG_Dccp::SetProtocolLinkEnabled(bool theEnabled)
{
    myProtocolLinkEnabled = theEnabled;
}

bool CFG_Dccp::GetProtocolLinkEnabled() const
{
    return myProtocolLinkEnabled;
}


void CFG_Dccp::SetFollowProtection(bool theFollowProtectionEnabled)
{
    myFollowProtectionEnabled = theFollowProtectionEnabled;
}

bool CFG_Dccp::GetFollowProtection() const
{
    return myFollowProtectionEnabled;
}


void CFG_Dccp::Reset(void)
{
    // Initialize all attributes to default values.
    myAddressType = CT_DCC_TL_UNKNOWN_TYPE;
    mySourceIpAddress = 0;
    mySubnetMask = 0;
    myDestIpAddress = 0;
    myAutoDiscEnabled = false;
    myIpEnabled = false;
    myPprfId = UNKNOWN_Link_Profile_ID;
    myIsProvisioned = 0;
    myProtocolLinkEnabled = false;
    myFollowProtectionEnabled = false;
    myIfIndex = 0;
}

// For Display
ostream& CFG_Dccp::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint8 aAddressType = myAddressType;

    theStream   << FC_InsertVar(myPprfId);
    theStream   << FC_InsertVar(myProtocolLinkEnabled);
    theStream   << FC_InsertVar(myIsProvisioned);
    theStream   << FC_InsertVar(myFollowProtectionEnabled);

    theStream   << FC_InsertVar(aAddressType);
    theStream   << FC_InsertVar(mySourceIpAddress);
    theStream   << FC_InsertVar(mySubnetMask);
    theStream   << FC_InsertVar(myDestIpAddress);
    theStream   << FC_InsertVar(myAutoDiscEnabled);
    theStream   << FC_InsertVar(myIpEnabled);
    theStream   << FC_InsertVar(myIfIndex);


    return theStream;
}

istream& CFG_Dccp::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint8 aAddressType = 0;

    theStream   >> FC_ExtractVar(myPprfId);
    theStream   >> FC_ExtractVar(myProtocolLinkEnabled);
    theStream   >> FC_ExtractVar(myIsProvisioned);
    theStream   >> FC_ExtractVar(myFollowProtectionEnabled);

    theStream   >> FC_ExtractVar(aAddressType);
    theStream   >> FC_ExtractVar(mySourceIpAddress);
    theStream   >> FC_ExtractVar(mySubnetMask);
    theStream   >> FC_ExtractVar(myDestIpAddress);
    theStream   >> FC_ExtractVar(myAutoDiscEnabled);
    theStream   >> FC_ExtractVar(myIpEnabled);
    theStream   >> FC_ExtractVar(myIfIndex);

    myAddressType = (CT_DCC_TL_AddrType) aAddressType;

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Dccp::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    uint8 aAddressType = myAddressType;

    theStream   << myPprfId;
    theStream   << myProtocolLinkEnabled;
    theStream   << myIsProvisioned;
    theStream   << myFollowProtectionEnabled;

    theStream   << aAddressType;
    theStream   << mySourceIpAddress;
    theStream   << mySubnetMask;
    theStream   << myDestIpAddress;
    theStream   << myAutoDiscEnabled;
    theStream   << myIpEnabled;
    theStream   << myIfIndex;

    return theStream;
}

FC_Stream& CFG_Dccp::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint8 aAddressType = 0;

    theStream   >> myPprfId;
    theStream   >> myProtocolLinkEnabled;
    theStream   >> myIsProvisioned;
    theStream   >> myFollowProtectionEnabled;

    theStream   >> aAddressType;
    theStream   >> mySourceIpAddress;
    theStream   >> mySubnetMask;
    theStream   >> myDestIpAddress;
    theStream   >> myAutoDiscEnabled;
    theStream   >> myIpEnabled;
    theStream   >> myIfIndex;

    myAddressType = (CT_DCC_TL_AddrType) aAddressType;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Dccp::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto DCCLERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"pprf",4))
    {
        SetPppProfileID(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"link",4))
    {
        SetProtocolLinkEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"ispro",5))
    {
        SetIsProvisioned(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"fol",3))
    {
        SetFollowProtection(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"addr",4))
    {
        SetAddressType(CFG_STRING_TO_TL_ADDR_TYPE(argv[1]));
    }
    else if (!strncmp(aParam,"sourc",5))
    {
        SetSourceIpAddress(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"sub",3))
    {
        SetSubnetMask(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"dest",4))
    {
        SetDestIpAddress(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"auto",4))
    {
        SetAutoDiscEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"ipen",4))
    {
        SetIpEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"ifindex",7))
    {
        SetIfIndex(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else
    {
        goto DCCLERROR;
    }


    return FC_CmdProcessor::E_SUCCESS;

DCCLERROR:
    {
        fc_cout << "dccp pprfid        <integer (id)> " << endl;
        fc_cout << "dccp linkenable    <e-nable|d-isable> "  << endl;
        fc_cout << "dccp isprovisioned <e-nable|d-isable> "  << endl;
        fc_cout << "dccp follprot      <e-nable|d-isable> "  << endl;
        fc_cout << "dccp addrtype      <UnNumbered|Numbered|None|Unknown> "  << endl;
        fc_cout << "dccp sourceip      <long integer <ip addr> "  << endl;
        fc_cout << "dccp subnet        <long integer "  << endl;
        fc_cout << "dccp destip        <long integer <ip addr> "  << endl;
        fc_cout << "dccp autodisc      <e-nable|d-isable> "  << endl;
        fc_cout << "dccp ipenabled     <e-nable|d-isable> "  << endl;
        fc_cout << "dccp ifindex       <long integer> "  << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Dccp::Display( FC_Stream& theStream )
{

    theStream   << "PPP Parameters:" << endl;
    theStream   << "  DCCP  - PPP Is Provisioned  [isprovisioned] = " << DISPLAY_BOOL(myIsProvisioned) << endl;
    theStream   << "  DCCP  - PPP Link Enabled    [linkenable]    = " << DISPLAY_BOOL(myProtocolLinkEnabled) << endl;
    theStream   << "  DCCP  - PPP Profile ID      [pprfid]        = " << uint32(myPprfId) << endl;
    theStream   << "  DCCP  - Follow Protection   [followprotect] = " << DISPLAY_BOOL(myFollowProtectionEnabled) << endl;

    theStream   << "  DCCP  - Source Address Type [addrtype]      = " << DISPLAY_DCC_TL_AddrType(myAddressType) << endl;
    theStream   << "  DCCP  - Source IP Address   [sourceip]      = " << uint32(mySourceIpAddress) << endl;
    theStream   << "  DCCP  - Source Subnet Mask  [subnet]        = " << uint32(mySubnetMask) << endl;
    theStream   << "  DCCP  - Dest IP Address     [destip]        = " << uint32(myDestIpAddress) << endl;
    theStream   << "  DCCP  - Auto Discovery Enab [autodisc]      = " << DISPLAY_BOOL(myAutoDiscEnabled) << endl;
    theStream   << "  DCCP  - IP Enabled          [ipenabled]     = " << DISPLAY_BOOL(myIpEnabled) << endl;
    theStream   << "  DCCP  - IfIndex             [ifindex]       = " << uint32(myIfIndex) << endl;
}

