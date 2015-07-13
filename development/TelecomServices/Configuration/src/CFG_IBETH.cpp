//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_IBETH.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_IbEth::CFG_IbEth(uint32 theIndex):
    CFG_Object(theIndex),
    myP2PVlanId(0),
    myLkType(CT_lktype_broadcast),
    myBridgeId(0),
    myBridgeVlanId(0),
    myVSId(0),
    myIsMaster(false),
    myLinkEnabled(false),
    myAddressType(CT_DCC_TL_UNKNOWN_TYPE),
    mySourceIpAddress(0),
    mySubnetMask(0),
    myDestIpAddress(0),
    myIfIndex(0),
    myAutoDiscEnabled(false),
    myIpEnabled(false),
    myIsProvisioned(false)
{
}

CFG_IbEth::~CFG_IbEth(void)
{
}

uint8 CFG_IbEth::GetBridgeId() const 
{
   return myBridgeId;
}

bool  CFG_IbEth::SetP2PVlanId(uint16 theVlanId)
{
	if (myP2PVlanId!= theVlanId)
	{
	   myP2PVlanId = theVlanId;
	   return true;
	}
	else
	{
	   return false;
	}

}

uint16 CFG_IbEth::GetP2PVlanId() const
{
    return myP2PVlanId;
}

bool CFG_IbEth::SetLkType(CT_LkType theLkType)
{
	if (myLkType != theLkType)
	{
	   myLkType = theLkType;
	   return true;
	}
	else
	{
	   return false;
	}
}

CT_LkType CFG_IbEth::GetLkType() const
{
   return myLkType;
}

bool  CFG_IbEth::SetBridgeId(uint8 theBridgeId)
{
	if (myBridgeId != theBridgeId)
	{
	   myBridgeId = theBridgeId;
	   return true;
	}
	else
	{
	   return false;
	}

}

bool CFG_IbEth::SetVSId(uint8 theVSId)
{
    if (myVSId != theVSId)
    {
        myVSId = theVSId;
        return true;
    }
    else
    {
        return false;
    }
}

uint8 CFG_IbEth::GetVSId() const
{
    return myVSId;
}

bool CFG_IbEth::SetBridgeVlanId(uint16 theVlanId)
{
    if (myBridgeVlanId!= theVlanId)
    {
        myBridgeVlanId = theVlanId;
        return true;
    }
    else
    {
        return false;
    }
}

uint16 CFG_IbEth::GetBridgeVlanId() const
{
    return myBridgeVlanId;
}

bool CFG_IbEth::SetMaster(bool theIsMaster)
{
	if (myIsMaster != theIsMaster)
	{
	    myIsMaster = theIsMaster;
		return true;
	}
	else
	{
	  return false;
	}
}

bool CFG_IbEth::GetMaster() const
{
    return myIsMaster;
}

bool CFG_IbEth::SetAddressType(CT_DCC_TL_AddrType theAddressType)
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

CT_DCC_TL_AddrType CFG_IbEth::GetAddressType() const
{
    return myAddressType;
}


bool CFG_IbEth::SetSourceIpAddress(uint32 theSourceIpAddress)
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

uint32 CFG_IbEth::GetSourceIpAddress() const
{
    return mySourceIpAddress;
}


bool CFG_IbEth::SetSubnetMask(uint32 theSubnetMask)
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

uint32 CFG_IbEth::GetSubnetMask() const
{
    return mySubnetMask;
}

bool CFG_IbEth::SetIfIndex(uint32 theIfIndex)
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

uint32 CFG_IbEth::GetIfIndex() const
{
    return myIfIndex;
}


bool CFG_IbEth::SetDestIpAddress(uint32 theDestIpAddress)
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

uint32 CFG_IbEth::GetDestIpAddress() const
{
    return myDestIpAddress;
}


bool CFG_IbEth::SetAutoDiscEnabled(bool theEnabled)
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

bool CFG_IbEth::GetAutoDiscEnabled() const
{
    return myAutoDiscEnabled;
}


bool CFG_IbEth::SetIpEnabled(bool theEnabled)
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

bool CFG_IbEth::GetIpEnabled() const
{
    return myIpEnabled;
}

//Set Link Is Provisioned field
bool CFG_IbEth::SetIsProvisioned(bool theIsProvisioned)
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
bool CFG_IbEth::GetIsProvisioned() const
{
    return myIsProvisioned;
}


bool CFG_IbEth::SetLinkEnabled(bool theEnabled)
{
    if (myLinkEnabled != theEnabled)
    {
        myLinkEnabled = theEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_IbEth::GetLinkEnabled() const
{
    return myLinkEnabled;
}

void CFG_IbEth::Reset(void)
{
    // Initialize all attributes to default values. 
    myLkType = CT_lktype_broadcast;
	myP2PVlanId = 0;
	myBridgeId = 0;
	myVSId = 0;
	myBridgeVlanId = 0;
	myIsMaster = false;
    myAddressType = CT_DCC_TL_UNKNOWN_TYPE;
    mySourceIpAddress = 0;
    mySubnetMask = 0;
    myDestIpAddress = 0;
    myAutoDiscEnabled = false;
    myIpEnabled = false;
    myIsProvisioned = 0;
    myLinkEnabled = false;
    myIfIndex = 0;
}

// For Display
ostream& CFG_IbEth::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint8 aAddressType = myAddressType;
	uint8 aLkType = myLkType;
	 
	theStream	<< FC_InsertVar(myP2PVlanId);
	theStream	<< FC_InsertVar(aLkType);
	theStream	<< FC_InsertVar(myBridgeId);
    theStream   << FC_InsertVar(myVSId);
    theStream   << FC_InsertVar(myBridgeVlanId);
    theStream   << FC_InsertVar(myIsMaster);
    theStream   << FC_InsertVar(myLinkEnabled);
    theStream   << FC_InsertVar(myIsProvisioned);

    theStream   << FC_InsertVar(aAddressType);
    theStream   << FC_InsertVar(mySourceIpAddress);
    theStream   << FC_InsertVar(mySubnetMask);
    theStream   << FC_InsertVar(myDestIpAddress);
    theStream   << FC_InsertVar(myAutoDiscEnabled);
    theStream   << FC_InsertVar(myIpEnabled);
    theStream   << FC_InsertVar(myIfIndex);
 
    return theStream;
}

istream& CFG_IbEth::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint8 aAddressType = 0;
    uint8 aLkType = 0;
	
	
    theStream	>> FC_ExtractVar(myP2PVlanId);
	theStream	>> FC_ExtractVar(aLkType);
	theStream	>> FC_ExtractVar(myBridgeId);
    theStream   >> FC_ExtractVar(myVSId);
    theStream   >> FC_ExtractVar(myBridgeVlanId);
    theStream   >> FC_ExtractVar(myIsMaster);
    theStream   >> FC_ExtractVar(myLinkEnabled);
    theStream   >> FC_ExtractVar(myIsProvisioned);

    theStream   >> FC_ExtractVar(aAddressType);
    theStream   >> FC_ExtractVar(mySourceIpAddress);
    theStream   >> FC_ExtractVar(mySubnetMask);
    theStream   >> FC_ExtractVar(myDestIpAddress);
    theStream   >> FC_ExtractVar(myAutoDiscEnabled);
    theStream   >> FC_ExtractVar(myIpEnabled);
    theStream   >> FC_ExtractVar(myIfIndex);
  
    myAddressType   = (CT_DCC_TL_AddrType) aAddressType;
    myLkType        = (CT_LkType) aLkType;
	
    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_IbEth::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    uint8 aAddressType = myAddressType;
    uint8 aLkType = myLkType;
	
	
    theStream	<< myP2PVlanId;
	theStream	<< aLkType;
	theStream	<< myBridgeId;
    theStream   << myVSId;
    theStream   << myBridgeVlanId;
    theStream   << myIsMaster;
    theStream   << myLinkEnabled;
    theStream   << myIsProvisioned;

    theStream   << aAddressType;
    theStream   << mySourceIpAddress;
    theStream   << mySubnetMask;
    theStream   << myDestIpAddress;
    theStream   << myAutoDiscEnabled;
    theStream   << myIpEnabled;
    theStream   << myIfIndex;
   
    return theStream;
}

FC_Stream& CFG_IbEth::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint8 aAddressType = 0;
    uint8 aLkType = 0;
	
    theStream	>> myP2PVlanId;
	theStream	>> aLkType;
	theStream	>> myBridgeId;
    theStream   >> myVSId;
    theStream   >> myBridgeVlanId;
    theStream   >> myIsMaster;
    theStream   >> myLinkEnabled;
    theStream   >> myIsProvisioned;

    theStream   >> aAddressType;
    theStream   >> mySourceIpAddress;
    theStream   >> mySubnetMask;
    theStream   >> myDestIpAddress;
    theStream   >> myAutoDiscEnabled;
    theStream   >> myIpEnabled;
    theStream   >> myIfIndex;
   
    myAddressType   = (CT_DCC_TL_AddrType) aAddressType;
    myLkType        = (CT_LkType) aLkType;
    return theStream;
}

FC_CmdProcessor::STATUS CFG_IbEth::Set(int argc, char **argv)
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

    if(!strcmp(aParam,"P2PVlan"))
    {
        SetP2PVlanId(static_cast<uint16>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"lktype",6))
    {
        SetLkType(static_cast<CT_LkType>(strtoul(argv[1], NULL, 0)));
    }
	else if (!strncmp(aParam,"bridgeId",8))
    {
        SetBridgeId(static_cast<uint8>(strtoul(argv[1], NULL, 0)));
    }
	else if (!strncmp(aParam,"vsId",4))
    {
        SetVSId(static_cast<uint8>(strtoul(argv[1], NULL, 0)));
    }
	else if (!strncmp(aParam,"bridgeVlan",10))
    {
        SetBridgeVlanId(static_cast<uint16>(strtoul(argv[1], NULL, 0)));
    }
	else if (!strncmp(aParam,"master",6))
    {
        SetMaster(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"link",4))
    {
        SetLinkEnabled(argv[1][0]=='e');
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
    else
    {
        goto GCCERROR;
    }


    return FC_CmdProcessor::E_SUCCESS;

GCCERROR:
    {        
        fc_cout << "ibbr P2PVlan       <short integer>" << endl;
        fc_cout << "ibbr lktype        <integer > " << endl;
		fc_cout << "ibbr bridgeId      <short integer> "  << endl;
		fc_cout << "ibbr vsId          <short integer> "  << endl;
		fc_cout << "ibbr bridgeVlan    <short integer> "  << endl;
		fc_cout << "ibbr master        <e-nable|d-isable> "  << endl;
        fc_cout << "ibbr linkenable    <e-nable|d-isable> "  << endl;
        fc_cout << "ibbr isprovisioned <e-nable|d-isable> "  << endl;
        fc_cout << "ibbr addrtype      <UnNumbered|Numbered|None|Unknown> "  << endl;
        fc_cout << "ibbr sourceip      <long integer <ip addr> "  << endl;
        fc_cout << "ibbr subnet        <long integer "  << endl;
        fc_cout << "ibbr destip        <long integer <ip addr> "  << endl;
        fc_cout << "ibbr autodisc      <e-nable|d-isable> "  << endl;
        fc_cout << "ibbr ipenabled     <e-nable|d-isable> "  << endl;
        fc_cout << "ibbr ifindex       <long integer> "  << endl;
        
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

//return FC_CmdProcessor::E_SUCCESS;
}

void CFG_IbEth::Display( FC_Stream& theStream )
{

    theStream   << "ibbr Parameters:" << endl;
    theStream   << "  ibbr  - ibbr Is Provisioned  [isprovisioned] = " << DISPLAY_BOOL(myIsProvisioned) << endl;              
    theStream   << "  ibbr  - ibbr Link Enabled    [linkenable]    = " << DISPLAY_BOOL(myLinkEnabled) << endl;        
    theStream   << "  ibbr  - P2PVlan             [P2PVlan]        = " << uint32(myP2PVlanId) << endl;
	theStream   << "  ibbr  - lktype              [lktype]          = " << uint8(myLkType) << endl;   
    theStream   << "  ibbr  - Source Address Type [addrtype]      = " << DISPLAY_DCC_TL_AddrType(myAddressType) << endl;     
    theStream   << "  ibbr  - Source IP Address   [sourceip]      = " << uint32(mySourceIpAddress) << endl;                  
    theStream   << "  ibbr  - Source Subnet Mask  [subnet]        = " << uint32(mySubnetMask) << endl;                       
    theStream   << "  ibbr  - Dest IP Address     [destip]        = " << uint32(myDestIpAddress) << endl;                    
    theStream   << "  ibbr  - Auto Discovery Enab [autodisc]      = " << DISPLAY_BOOL(myAutoDiscEnabled) << endl;            
    theStream   << "  ibbr  - IP Enabled          [ipenabled]     = " << DISPLAY_BOOL(myIpEnabled) << endl;                  
    theStream   << "  ibbr  - IfIndex             [ifindex]       = " << uint32(myIfIndex) << endl;                                              
                           
}

