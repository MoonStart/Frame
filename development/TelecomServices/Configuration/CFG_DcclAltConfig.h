/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_DCCPOBJECT_H
#define CFG_DCCPOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_DCC_Definitions.h>


#include "CFG_Object.h"


// This object contains all the generic DCC Link  
// section configuration for one DCCL.
class CFG_Dccp
: public CFG_Object
{

public:

	//Constructor.
    CFG_Dccp(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Dccp(void);


    // PPP specific configuration attributes
    void SetPppProfileID(CT_Link_ProfileId theLprfId);
    CT_Link_ProfileId GetPppProfileID() const;

    void SetProtocolLinkEnabled(bool theProtocolLinkEnabled);
    bool GetProtocolLinkEnabled() const;

    void SetIsProvisioned(bool theProvisioned);
    bool GetIsProvisioned() const;

    void SetFollowProtection(bool theFollowProtectionEnabled);
    bool GetFollowProtection() const;


    // From TL (Topological Link) Command
    // Near End Address Type
    void SetAddressType(CT_DCC_TL_AddrType theAddressType);
    CT_DCC_TL_AddrType GetAddressType() const;

    // Near End Address for Numbered ; Parent TL for Unnumbered
    void SetSourceIpAddress(uint32 theSourceIpAddress);
    uint32 GetSourceIpAddress() const;

    // Near End Mask 
    void SetSubnetMask(uint32 theSubnetMask);
    uint32 GetSubnetMask() const;

    // Neighbor Node ID 
    void SetDestIpAddress(uint32 theDestIpAddress);
    uint32 GetDestIpAddress() const;

    // Indicates whether the DestIpAdress is Auto Discovered or Provided above
    void SetAutoDiscEnabled(bool theEnabled);
    bool GetAutoDiscEnabled() const;

    // TL Link IS/OOS (IP Eanbled)
    void SetIpEnabled(bool theEnabled);
    bool GetIpEnabled() const;

    // TL IfIndex (useful for state changes!)
    void SetIfIndex(uint32 theIfIndex);
    uint32 GetIfIndex() const;

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

    CT_Link_ProfileId  myPprfId;

    bool               myProtocolLinkEnabled;

    bool               myIsProvisioned;

    bool               myFollowProtectionEnabled;

    // From TL (Topological Link) Command
    CT_DCC_TL_AddrType myAddressType;
    uint32             mySourceIpAddress;
    uint32             mySubnetMask;
    uint32             myDestIpAddress;
    bool               myAutoDiscEnabled;
    bool               myIpEnabled;
    uint32             myIfIndex;
};

#endif /* CFG_DCCPOBJECT_H */

