//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Gcc.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_OduDefinitions.h>

CFG_Gcc::CFG_Gcc(uint32 theIndex):
    CFG_Object(theIndex),
    myGccIdentifier(CT_DEFAULT_ODU_ID),
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
    myChannel(0),
    myVlanTag(0),
    myBdGcctype(BD_GCC_TYPE_UNKNOW)
{
}

CFG_Gcc::~CFG_Gcc(void)
{
}

bool CFG_Gcc::SetGccIdentifier(CT_ODU_Identifier theGccId)
{
    if (myGccIdentifier != theGccId)
    {
        myGccIdentifier = theGccId;
        return true;
    }
    else
    {
        return false;
    }
}

CT_ODU_Identifier CFG_Gcc::GetGccIdentifier() const
{
    return myGccIdentifier;
}


bool CFG_Gcc::SetGccType(CT_GCC_Type theGccType)
{
    if (myGccType != theGccType)
    {
        myGccType = theGccType;
        return true;
    }
    else
    {
        return false;
    }
}

CT_GCC_Type CFG_Gcc::GetGccType() const
{
    return myGccType;
}


bool CFG_Gcc::SetBandwidthGccType(CT_BANDWIDTH_GCC_TYPE theBdGccType)
{
    if (myBdGcctype != theBdGccType)
    {
        myBdGcctype = theBdGccType;
        return true;
    }
    else
    {
        return false;
    }
}

CT_BANDWIDTH_GCC_TYPE CFG_Gcc::GetBandwidthGccType() const
{
    return myBdGcctype;
}


bool CFG_Gcc::SetAddressType(CT_DCC_TL_AddrType theAddressType)
{
    if (myAddressType != theAddressType)
    {
        myAddressType = theAddressType;
        return true;
    }
    else
    {
        return false;
    }
}

CT_DCC_TL_AddrType CFG_Gcc::GetAddressType() const
{
    return myAddressType;
}


bool CFG_Gcc::SetSourceIpAddress(uint32 theSourceIpAddress)
{
    if (mySourceIpAddress != theSourceIpAddress)
    {
        mySourceIpAddress = theSourceIpAddress;
        return true;
    }
    else
    {
        return false;
    }
}

uint32 CFG_Gcc::GetSourceIpAddress() const
{
    return mySourceIpAddress;
}


bool CFG_Gcc::SetSubnetMask(uint32 theSubnetMask)
{
    if (mySubnetMask != theSubnetMask)
    {
        mySubnetMask = theSubnetMask;
        return true;
    }
    else
    {
        return false;
    }
}

uint32 CFG_Gcc::GetSubnetMask() const
{
    return mySubnetMask;
}

bool CFG_Gcc::SetIfIndex(uint32 theIfIndex)
{
    if (myIfIndex != theIfIndex)
    {
        myIfIndex = theIfIndex;
        return true;
    }
    else
    {
        return false;
    }
}

uint32 CFG_Gcc::GetIfIndex() const
{
    return myIfIndex;
}

bool CFG_Gcc::SetChannel(uint8 theChannel)
{
    if (myChannel != theChannel)
    {
        myChannel = theChannel;
        return true;
    }
    else
    {
        return false;
    }
}

uint8 CFG_Gcc::GetChannel() const
{
    return myChannel;
}

bool CFG_Gcc::SetVlanTag(uint16 theVlanTag)
{
    if (myVlanTag != theVlanTag)
    {
        myVlanTag = theVlanTag;
        return true;
    }
    else
    {
        return false;
    }
}

uint16 CFG_Gcc::GetVlanTag() const
{
    return myVlanTag;
}

bool CFG_Gcc::SetDestIpAddress(uint32 theDestIpAddress)
{
    if (myDestIpAddress != theDestIpAddress)
    {
        myDestIpAddress = theDestIpAddress;
        return true;
    }
    else
    {
        return false;
    }
}

uint32 CFG_Gcc::GetDestIpAddress() const
{
    return myDestIpAddress;
}


bool CFG_Gcc::SetAutoDiscEnabled(bool theEnabled)
{
    if (myAutoDiscEnabled != theEnabled)
    {
        myAutoDiscEnabled = theEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Gcc::GetAutoDiscEnabled() const
{
    return myAutoDiscEnabled;
}


bool CFG_Gcc::SetIpEnabled(bool theEnabled)
{
    if (myIpEnabled != theEnabled)
    {
        myIpEnabled = theEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Gcc::GetIpEnabled() const
{
    return myIpEnabled;
}


bool CFG_Gcc::SetPppProfileID(CT_Link_ProfileId thePprfId)
{
    if (myPprfId != thePprfId)
    {
        myPprfId = thePprfId;
        return true;
    }
    else
    {
        return false;
    }
}

CT_Link_ProfileId CFG_Gcc::GetPppProfileID() const
{
    return myPprfId;
}


//Set Link Is Provisioned field
bool CFG_Gcc::SetIsProvisioned(bool theIsProvisioned)
{
    if (myIsProvisioned != theIsProvisioned)
    {
        myIsProvisioned = theIsProvisioned;
        return true;
    }
    else
    {
        return false;
    }
}

//Get Link s Provisioned field
bool CFG_Gcc::GetIsProvisioned() const
{
    return myIsProvisioned;
}


bool CFG_Gcc::SetProtocolLinkEnabled(bool theEnabled)
{
    if (myProtocolLinkEnabled != theEnabled)
    {
        myProtocolLinkEnabled = theEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Gcc::GetProtocolLinkEnabled() const
{
    return myProtocolLinkEnabled;
}

void CFG_Gcc::Reset(void)
{
    // Initialize all attributes to default values.
    myGccIdentifier = CT_DEFAULT_ODU_ID;
    myGccType       = CT_GCC_UNKNOWN;
    myAddressType = CT_DCC_TL_UNKNOWN_TYPE;
    mySourceIpAddress = 0;
    mySubnetMask = 0;
    myDestIpAddress = 0;
    myAutoDiscEnabled = false;
    myIpEnabled = false;
    myPprfId = UNKNOWN_Link_Profile_ID;
    myIsProvisioned = 0;
    myProtocolLinkEnabled = false;
    myIfIndex = 0;
    myChannel = 0;
    myVlanTag = 0;
    myBdGcctype = BD_GCC_TYPE_UNKNOW;
}

// For Display
ostream& CFG_Gcc::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint8 aAddressType = myAddressType;
    uint32 anGccIdentifier = myGccIdentifier.GetIdValue(); 
    uint8  aGccType = (uint8) myGccType;
    uint8 aBdGccType = (uint8)myBdGcctype;

    theStream   << FC_InsertVar(anGccIdentifier);
    theStream   << FC_InsertVar(aGccType);

    theStream   << FC_InsertVar(myPprfId);
    theStream   << FC_InsertVar(myProtocolLinkEnabled);
    theStream   << FC_InsertVar(myIsProvisioned);

    theStream   << FC_InsertVar(aAddressType);
    theStream   << FC_InsertVar(mySourceIpAddress);
    theStream   << FC_InsertVar(mySubnetMask);
    theStream   << FC_InsertVar(myDestIpAddress);
    theStream   << FC_InsertVar(myAutoDiscEnabled);
    theStream   << FC_InsertVar(myIpEnabled);
    theStream   << FC_InsertVar(myIfIndex);
    theStream   << FC_InsertVar(myChannel);
    theStream   << FC_InsertVar(myVlanTag);
    theStream   << FC_InsertVar(aBdGccType);

    return theStream;
}

istream& CFG_Gcc::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint8 aAddressType = 0;
    uint32 anGccIdentifier; 
    uint8  aGccType;
    uint8 aBdGccType;

    theStream   >> FC_ExtractVar(anGccIdentifier);
    theStream   >> FC_ExtractVar(aGccType);

    theStream   >> FC_ExtractVar(myPprfId);
    theStream   >> FC_ExtractVar(myProtocolLinkEnabled);
    theStream   >> FC_ExtractVar(myIsProvisioned);

    theStream   >> FC_ExtractVar(aAddressType);
    theStream   >> FC_ExtractVar(mySourceIpAddress);
    theStream   >> FC_ExtractVar(mySubnetMask);
    theStream   >> FC_ExtractVar(myDestIpAddress);
    theStream   >> FC_ExtractVar(myAutoDiscEnabled);
    theStream   >> FC_ExtractVar(myIpEnabled);
    theStream   >> FC_ExtractVar(myIfIndex);
    theStream   >> FC_ExtractVar(myChannel);
    theStream   >> FC_ExtractVar(myVlanTag);
    theStream   >> FC_ExtractVar(aBdGccType);
    

    myAddressType   = (CT_DCC_TL_AddrType) aAddressType;
    myGccIdentifier = (CT_ODU_Identifier) anGccIdentifier;
    myGccType       = (CT_GCC_Type) aGccType;
    myBdGcctype = (CT_BANDWIDTH_GCC_TYPE)aBdGccType;

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Gcc::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    uint8 aAddressType = myAddressType;
    uint32 anGccIdentifier = myGccIdentifier.GetIdValue();
    uint8  aGccType = (uint8) myGccType; 
    uint8 aBdGccType = (uint8)myBdGcctype;

    theStream   << anGccIdentifier;
    theStream   << aGccType;
    theStream   << myPprfId;
    theStream   << myProtocolLinkEnabled;
    theStream   << myIsProvisioned;

    theStream   << aAddressType;
    theStream   << mySourceIpAddress;
    theStream   << mySubnetMask;
    theStream   << myDestIpAddress;
    theStream   << myAutoDiscEnabled;
    theStream   << myIpEnabled;
    theStream   << myIfIndex;
    theStream   << myChannel;
    theStream   << myVlanTag;
    theStream   << aBdGccType;

    return theStream;
}

FC_Stream& CFG_Gcc::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint8 aAddressType = 0;
    uint32 anGccIdentifier;
    uint8  aGccType;
    uint8 aBdGccType;

    theStream   >> anGccIdentifier;
    theStream   >> aGccType;

    theStream   >> myPprfId;
    theStream   >> myProtocolLinkEnabled;
    theStream   >> myIsProvisioned;

    theStream   >> aAddressType;
    theStream   >> mySourceIpAddress;
    theStream   >> mySubnetMask;
    theStream   >> myDestIpAddress;
    theStream   >> myAutoDiscEnabled;
    theStream   >> myIpEnabled;
    theStream   >> myIfIndex;
    theStream   >> myChannel;
    theStream   >> myVlanTag;
    theStream   >> aBdGccType;

    myAddressType   = (CT_DCC_TL_AddrType) aAddressType;
    myGccIdentifier = (CT_ODU_Identifier) anGccIdentifier;
    myGccType       = (CT_GCC_Type) aGccType;
    myBdGcctype = (CT_BANDWIDTH_GCC_TYPE)aBdGccType;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Gcc::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto GCCERROR;

    // avoid copy overflow.
    if (strlen(argv[0]) > 32)
        goto GCCERROR;
    //Copy arguments
    strcpy(aParam, argv[0]);

    if(!strcmp(aParam,"gccid"))
    {
        SetGccIdentifier(CT_ODU_Identifier(atol(argv[1])));
    }
    else if (!strncmp(aParam,"type",4))
    {
        SetGccType(CFG_STRING_TO_GCC_TYPE(argv[1]));
    }
    else if (!strncmp(aParam,"pprf",4))
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
    else if (!strncmp(aParam,"channel",7))
    {
        SetChannel(static_cast<uint8>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"vlan",4))
    {
        SetVlanTag(static_cast<uint16>(strtoul(argv[1], NULL, 0)));
    }
    else
    {
        goto GCCERROR;
    }


    return FC_CmdProcessor::E_SUCCESS;

GCCERROR:
    {        
        fc_cout << "gcc gccid         <uint32 ID definition> " << endl;
        fc_cout << "gcc pprfid        <integer (id)> " << endl;
        fc_cout << "gcc linkenable    <e-nable|d-isable> "  << endl;
        fc_cout << "gcc isprovisioned <e-nable|d-isable> "  << endl;
        fc_cout << "gcc addrtype      <UnNumbered|Numbered|None|Unknown> "  << endl;
        fc_cout << "gcc sourceip      <long integer <ip addr> "  << endl;
        fc_cout << "gcc subnet        <long integer "  << endl;
        fc_cout << "gcc destip        <long integer <ip addr> "  << endl;
        fc_cout << "gcc autodisc      <e-nable|d-isable> "  << endl;
        fc_cout << "gcc ipenabled     <e-nable|d-isable> "  << endl;
        fc_cout << "gcc ifindex       <long integer> "  << endl;
        fc_cout << "gcc channel       <long integer> "  << endl;
        fc_cout << "gcc vlan          <short integer> "  << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

//return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Gcc::Display( FC_Stream& theStream )
{
    uint32 aGccIdentifier = myGccIdentifier.GetIdValue();
    theStream   << "  GCC  - Gcc ID              [gccid]         = 0x " << hex << aGccIdentifier << myGccIdentifier.DisplayOduIdentifier() << endl;

    theStream   << "PPP Parameters:" << endl;
    theStream   << "  GCC  - PPP Is Provisioned  [isprovisioned] = " << DISPLAY_BOOL(myIsProvisioned) << endl;              
    theStream   << "  GCC  - PPP Link Enabled    [linkenable]    = " << DISPLAY_BOOL(myProtocolLinkEnabled) << endl;        
    theStream   << "  GCC  - PPP Profile ID      [pprfid]        = " << uint32(myPprfId) << endl;                           
    theStream   << "  GCC  - Source Address Type [addrtype]      = " << DISPLAY_DCC_TL_AddrType(myAddressType) << endl;     
    theStream   << "  GCC  - Source IP Address   [sourceip]      = " << uint32(mySourceIpAddress) << endl;                  
    theStream   << "  GCC  - Source Subnet Mask  [subnet]        = " << uint32(mySubnetMask) << endl;                       
    theStream   << "  GCC  - Dest IP Address     [destip]        = " << uint32(myDestIpAddress) << endl;                    
    theStream   << "  GCC  - Auto Discovery Enab [autodisc]      = " << DISPLAY_BOOL(myAutoDiscEnabled) << endl;            
    theStream   << "  GCC  - IP Enabled          [ipenabled]     = " << DISPLAY_BOOL(myIpEnabled) << endl;                  
    theStream   << "  GCC  - IfIndex             [ifindex]       = " << uint32(myIfIndex) << endl;                          
    theStream   << "  GCC  - Channel             [channel]       = " << uint16(myChannel) << endl;                          
    theStream   << "  GCC  - Vlan Tag            [vlan]          = " << uint8(myVlanTag) << endl;                          
}

