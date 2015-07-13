/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_IBETHOBJECT_H
#define CFG_IBETHOBJECT_H

#include <gdef.h>
#include "CFG_Object.h"
#include <CommonTypes/CT_IBETH_Definitions.h>
#include <CommonTypes/CT_DCC_Definitions.h>


class CFG_IbEth
: public CFG_Object
{

public:

    CFG_IbEth(uint32 theIndex);
    virtual ~CFG_IbEth(void);

	uint16 GetP2PVlanId() const;
    bool SetP2PVlanId(uint16 theVlanId);

    CT_LkType GetLkType() const;
	bool SetLkType(CT_LkType theLkType);
	
    uint8 GetBridgeId() const;
	bool  SetBridgeId(uint8 theBridgeId);
	
	uint8 GetVSId() const ;
	bool  SetVSId(uint8 theVSId);
	
	uint16 GetBridgeVlanId() const;
	bool SetBridgeVlanId(uint16 theVlanId);

	bool SetMaster(bool theIsMaster);
	bool GetMaster() const; 

	bool SetLinkEnabled(bool theLinkEnabled);
    bool GetLinkEnabled() const;
	
    bool SetIsProvisioned(bool theProvisioned);
    bool GetIsProvisioned() const;

    // From TL (Topological Link) Command or bridge command
    
    // Near End Address for Numbered ; Parent TL for Unnumbered
    bool SetAddressType(CT_DCC_TL_AddrType theAddressType);
    CT_DCC_TL_AddrType GetAddressType() const;
	
    bool SetSourceIpAddress(uint32 theSourceIpAddress);
    uint32 GetSourceIpAddress() const;

    // Near End Mask 
    bool SetSubnetMask(uint32 theSubnetMask);
    uint32 GetSubnetMask() const;

    // Neighbor Node ID 
    bool SetDestIpAddress(uint32 theDestIpAddress);
    uint32 GetDestIpAddress() const;

    // Indicates whether the DestIpAdress is Auto Discovered or Provided above
    bool SetAutoDiscEnabled(bool theEnabled);
    bool GetAutoDiscEnabled() const;

    // TL Link IS/OOS (IP Eanbled)
    bool SetIpEnabled(bool theEnabled);
    bool GetIpEnabled() const;

    // TL IfIndex (useful for state changes!)
    bool SetIfIndex(uint32 theIfIndex);
    uint32 GetIfIndex() const;

	//Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    uint16 myP2PVlanId;
	CT_LkType myLkType; 
	uint8  myBridgeId;
	uint8  myVSId;
	uint16 myBridgeVlanId;
	bool   myIsMaster;
	bool   myLinkEnabled;
    bool   myIsProvisioned;

    // From TL (Topological Link) Command
    CT_DCC_TL_AddrType myAddressType;
    uint32             mySourceIpAddress;
    uint32             mySubnetMask;
    uint32             myDestIpAddress;
    bool               myAutoDiscEnabled;
    bool               myIpEnabled;
    uint32             myIfIndex;
   
};

#endif 

