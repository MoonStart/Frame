/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_GCCOBJECT_H
#define CFG_GCCOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_NmGccBandwidthProfile.h>

#include "CFG_Object.h"

// This object contains all the generic GCC Link  
// section configuration for one GCC.
class CFG_Gcc
: public CFG_Object
{

public:

	//Constructor.
    CFG_Gcc(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Gcc(void);

    // This methods sets the GCC Identifies for GCC pools
    bool SetGccIdentifier(CT_ODU_Identifier theGccId);

    //This method returns the GCC Identifies for GCC pools
    CT_ODU_Identifier GetGccIdentifier() const; 

    bool SetGccType(CT_GCC_Type theGccType);
    CT_GCC_Type GetGccType() const;


    bool SetBandwidthGccType(CT_BANDWIDTH_GCC_TYPE theBdGccType);
    CT_BANDWIDTH_GCC_TYPE GetBandwidthGccType() const;
    

    // PPP specific configuration attributes
    bool SetPppProfileID(CT_Link_ProfileId theLprfId);
    CT_Link_ProfileId GetPppProfileID() const;

    bool SetProtocolLinkEnabled(bool theProtocolLinkEnabled);
    bool GetProtocolLinkEnabled() const;

    bool SetIsProvisioned(bool theProvisioned);
    bool GetIsProvisioned() const;


    // From TL (Topological Link) Command
    // Near End Address Type
    bool SetAddressType(CT_DCC_TL_AddrType theAddressType);
    CT_DCC_TL_AddrType GetAddressType() const;

    // Near End Address for Numbered ; Parent TL for Unnumbered
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

    // Channel (used in the mTera architecture)
    bool SetChannel(uint8 theChannel);
    uint8 GetChannel() const;

    // VLAN Tag (used in the mTera architecture)
    bool SetVlanTag(uint16 theVlanTag);
    uint16 GetVlanTag() const;

    // Not transferred via Framework
    // Whether the link is provisioned (or not)


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
    //GCC Identifier for GCC pools
    CT_ODU_Identifier  myGccIdentifier; 

    CT_GCC_Type        myGccType;

    CT_Link_ProfileId  myPprfId;

    bool               myProtocolLinkEnabled;

    bool               myIsProvisioned;

    // From TL (Topological Link) Command
    CT_DCC_TL_AddrType myAddressType;
    uint32             mySourceIpAddress;
    uint32             mySubnetMask;
    uint32             myDestIpAddress;
    bool               myAutoDiscEnabled;
    bool               myIpEnabled;
    uint32             myIfIndex;
    uint8              myChannel;
    uint16             myVlanTag;
    CT_BANDWIDTH_GCC_TYPE myBdGcctype;
};

#endif /* CFG_GCCPOBJECT_H */

