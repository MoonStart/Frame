/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   : 
 DESCRIPTION:
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_IBETHIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

TSPII_IBETHIf::TSPII_IBETHIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

TSPII_IBETHIf::~TSPII_IBETHIf()
{
}

void TSPII_IBETHIf::RefreshGet()
{   
    itsProtocolLinkState        = GetLinkState();    	
 
    itsP2PVlanId                = GetP2PVlanId();
	itsLkType                   = GetLkType();
	itsBridgeId                 = GetBridgeId();
	itsVSId                     = GetVSId();
	itsBridgeVlanId             = GetBridgeVlanId();
	itsIsMaster                 = GetIsMaster();
    itsLinkEnabled              = GetLinkEnabled(); 
  
    itsAddressType              = GetAddressType();
    itsSourceIpAddress          = GetSourceIpAddress();
    itsSubnetMask               = GetSubnetMask();
    itsDestIpAddress            = GetDestIpAddress();
    itsAutoDiscEnabled          = GetAutoDiscEnabled();
    itsIpEnabled                = GetIpEnabled();
    
}

void TSPII_IBETHIf::RefreshSet()
{  
    SetP2PVlanId(itsP2PVlanId);
    SetLkType(itsLkType);
	SetBridgeId(itsBridgeId);
	SetVSId(itsVSId);
	SetBridgeVlanId(itsBridgeVlanId);
	SetIsMaster(itsIsMaster);
    SetLinkEnabled(itsLinkEnabled);
   
    SetAddressType(itsAddressType);
    SetSourceIpAddress(itsSourceIpAddress);
    SetSubnetMask(itsSubnetMask);
    SetDestIpAddress(itsDestIpAddress);
    SetAutoDiscEnabled(itsAutoDiscEnabled);
    SetIpEnabled(itsIpEnabled);
    
}

void TSPII_IBETHIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsProtocolLinkState        = CT_IBETH_LINK_INCOMPLETE;
  
    // Configuration attributes    
    itsLinkEnabled           = false;  
    itsP2PVlanId             = 0;
	itsLkType                = CT_lktype_broadcast;  
	itsBridgeId              = 0;
	itsVSId                  = 0;
	itsBridgeVlanId          = 0;
	itsIsMaster              = false;
	itsLinkEnabled           = false;
      
    itsAddressType              = CT_DCC_TL_NONE;
    itsSourceIpAddress          = 0;
    itsSubnetMask               = 0;
    itsDestIpAddress            = 0;
    itsAutoDiscEnabled          = false;
    itsIpEnabled                = false;
	itsIfIndex                  = 0 ;
 
    RefreshSet();
}



void TSPII_IBETHIf::SetLinkEnabled(bool theEnable)
{
    itsLinkEnabled = theEnable;
}

bool TSPII_IBETHIf::GetLinkEnabled() const
{
    return itsLinkEnabled;
}

uint16 TSPII_IBETHIf::GetP2PVlanId() const
{
	return itsP2PVlanId;
}

void  TSPII_IBETHIf::SetP2PVlanId(uint16 theVlanId)
{
    itsP2PVlanId = theVlanId;
}

CT_LkType TSPII_IBETHIf::GetLkType() const
{
   return itsLkType;
}


void  TSPII_IBETHIf::SetLkType(CT_LkType theLkType)
{
   itsLkType = theLkType;
}
   
uint8 TSPII_IBETHIf::GetBridgeId() const
{
   return itsBridgeId;
}

void  TSPII_IBETHIf::SetBridgeId(uint8 theBridgeId)
{
   itsBridgeId = theBridgeId;
}
   
uint8  TSPII_IBETHIf::GetVSId() const 
{
   return itsVSId;
}

void TSPII_IBETHIf::SetVSId(uint8 theVSId)
{
    itsVSId = theVSId;
}
   

uint16 TSPII_IBETHIf::GetBridgeVlanId() const
{
    return itsBridgeVlanId;
}

void TSPII_IBETHIf::SetBridgeVlanId(uint16 theVlanId)
{
    itsBridgeVlanId = theVlanId;
}

void TSPII_IBETHIf::SetIsMaster(bool theIsMaster)
{
	itsIsMaster = theIsMaster;

}

bool TSPII_IBETHIf::GetIsMaster() const
{
    return itsIsMaster;
}

void TSPII_IBETHIf::SetAddressType(CT_DCC_TL_AddrType theAddressType)
{
    itsAddressType = theAddressType;
}


CT_DCC_TL_AddrType TSPII_IBETHIf::GetAddressType() const
{
    return(itsAddressType);
}


void TSPII_IBETHIf::SetSourceIpAddress(uint32 theSourceIpAddress)
{
    itsSourceIpAddress = theSourceIpAddress;
}


uint32 TSPII_IBETHIf::GetSourceIpAddress() const
{
    return(itsSourceIpAddress);
}


void TSPII_IBETHIf::SetSubnetMask(uint32 theSubnetMask)
{
    itsSubnetMask = theSubnetMask;
}

uint32 TSPII_IBETHIf::GetSubnetMask() const
{
    return(itsSubnetMask);
}


void TSPII_IBETHIf::SetDestIpAddress(uint32 theDestIpAddress)
{
    itsDestIpAddress = theDestIpAddress;
}

uint32 TSPII_IBETHIf::GetDestIpAddress() const
{
    return(itsDestIpAddress);
}

void TSPII_IBETHIf::SetAutoDiscEnabled(bool theEnabled)
{
    itsAutoDiscEnabled = theEnabled;
}

bool TSPII_IBETHIf::GetAutoDiscEnabled() const
{
    return(itsAutoDiscEnabled);
}

void TSPII_IBETHIf::SetIpEnabled(bool theEnabled)
{
    itsIpEnabled = theEnabled;
}

bool TSPII_IBETHIf::GetIpEnabled() const
{
    return(itsIpEnabled);
}


CT_IBETH_LinkState TSPII_IBETHIf::GetLinkState()
{
    return itsProtocolLinkState;
}



FC_Stream & TSPII_IBETHIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLinkState = itsProtocolLinkState;    
    int aAddressType = itsAddressType;
    int aLkType = itsLkType;

    // Monitor attributes
    theStream << aLinkState;
    theStream << itsP2PVlanId;
    theStream << aLkType;
    theStream << itsBridgeId;
    theStream << itsVSId;      
    theStream << itsBridgeVlanId; 
    theStream << itsIsMaster;
	theStream << itsLinkEnabled;
    theStream << aAddressType;
    theStream << itsSourceIpAddress;
    theStream << itsSubnetMask;
    theStream << itsDestIpAddress;
    theStream << itsAutoDiscEnabled;
    theStream << itsIpEnabled;
  
    return TSPII_BaseIf::WriteObjectBinary(theStream);
}


FC_Stream & TSPII_IBETHIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aLinkState; 
    int aAddressType;
	int aLkType;

    // Monitor attributes
    theStream >> aLinkState;
    theStream >> itsP2PVlanId;
    theStream >> aLkType;
    theStream >> itsBridgeId;
    theStream >> itsVSId;
    theStream >> itsBridgeVlanId; 
    theStream >> itsIsMaster;
    theStream >> itsLinkEnabled;
    theStream >> aAddressType;
    theStream >> itsSourceIpAddress;
    theStream >> itsSubnetMask;
    theStream >> itsDestIpAddress;
    theStream >> itsAutoDiscEnabled;
    theStream >> itsIpEnabled;

    itsProtocolLinkState = (CT_IBETH_LinkState) aLinkState;
    itsAddressType = (CT_DCC_TL_AddrType) aAddressType;
    itsLkType = (CT_LkType)aLkType;
    RefreshSet();
    
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}


ostream & TSPII_IBETHIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aLinkState = itsProtocolLinkState;
    int aAddressType = itsAddressType;
    int aLkType = itsLkType;

  
    theStream << FC_InsertVar(aLinkState);
    theStream << FC_InsertVar(itsP2PVlanId);
    theStream << FC_InsertVar(aLkType);
    theStream << FC_InsertVar(itsBridgeId);
    theStream << FC_InsertVar(itsVSId);
    theStream << FC_InsertVar(itsBridgeVlanId); 
    theStream << FC_InsertVar(itsIsMaster);
	theStream << FC_InsertVar(itsLinkEnabled);
    theStream << FC_InsertVar(aAddressType);
    theStream << FC_InsertVar(itsSourceIpAddress);
    theStream << FC_InsertVar(itsSubnetMask);
    theStream << FC_InsertVar(itsDestIpAddress);
    theStream << FC_InsertVar(itsAutoDiscEnabled);
    theStream << FC_InsertVar(itsIpEnabled);
  

    return TSPII_BaseIf::WriteObject(theStream);
}

istream & TSPII_IBETHIf::ReadObject(istream & theStream)
{
    int aLinkState;
    int aAddressType;
    int aLkType;

    // Monitor attributes   
    theStream >> FC_ExtractVar(aLinkState);
    theStream >> FC_ExtractVar(itsP2PVlanId);
    theStream >> FC_ExtractVar(aLkType);
    theStream >> FC_ExtractVar(itsBridgeId);
    theStream >> FC_ExtractVar(itsVSId);
    theStream >> FC_ExtractVar(itsBridgeVlanId); 
    theStream >> FC_ExtractVar(itsIsMaster);
	theStream >> FC_ExtractVar(itsLinkEnabled);
    theStream >> FC_ExtractVar(aAddressType);
    theStream >> FC_ExtractVar(itsSourceIpAddress);
    theStream >> FC_ExtractVar(itsSubnetMask);
    theStream >> FC_ExtractVar(itsDestIpAddress);
    theStream >> FC_ExtractVar(itsAutoDiscEnabled);
    theStream >> FC_ExtractVar(itsIpEnabled);
  
    itsProtocolLinkState = (CT_IBETH_LinkState) aLinkState;
    itsAddressType = (CT_DCC_TL_AddrType) aAddressType;    
    itsLkType = (CT_LkType) aLkType;
	
    RefreshSet();
    
    return TSPII_BaseIf::ReadObject(theStream);
}



