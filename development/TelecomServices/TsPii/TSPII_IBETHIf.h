#ifndef _TSPII_IBETHIF_H
#define _TSPII_IBETHIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  
 DESCRIPTION:
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_IBETH_Definitions.h"
#include "CommonTypes/CT_DCC_Definitions.h"

class TSPII_IBETHIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                     TSPII_IBETHIf(bool theDefault = false);
    virtual                           ~TSPII_IBETHIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // IBETH Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual CT_IBETH_LinkState          GetLinkState();
     
    virtual void                      SetLinkEnabled(bool theEnabled);
    virtual bool                      GetLinkEnabled() const;

    virtual uint16                    GetP2PVlanId() const;
    virtual void                      SetP2PVlanId(uint16 theVlanId);

    virtual CT_LkType                 GetLkType() const;
	virtual void                      SetLkType(CT_LkType theLkType);
	
    virtual uint8                     GetBridgeId() const;
	virtual void                      SetBridgeId(uint8 theBridgeId);
	
	virtual uint8                     GetVSId() const ;
	virtual void                      SetVSId(uint8 theVSId);
	
	virtual uint16                    GetBridgeVlanId() const;
	virtual void                      SetBridgeVlanId(uint16 theVlanId);

	virtual void                      SetIsMaster(bool theIsMaster);
	virtual bool                      GetIsMaster() const; 
   
    // From TL (Topological Link) Command
    // Near End Address Type
    virtual void                      SetAddressType(CT_DCC_TL_AddrType theAddressType);
    virtual CT_DCC_TL_AddrType        GetAddressType() const;

    // Near End Address for Numbered ; Parent TL for Unnumbered 
    virtual void                      SetSourceIpAddress(uint32 theSourceIpAddress);
    virtual uint32                    GetSourceIpAddress() const;

    // Near End Mask 
    virtual void                      SetSubnetMask(uint32 theSubnetMask);
    virtual uint32                    GetSubnetMask() const;

    // Neighbor Node ID 
    virtual void                      SetDestIpAddress(uint32 theDestIpAddress);
    virtual uint32                    GetDestIpAddress() const;

    // Indicates whether the DestIpAdress is Auto Discovered or Provided above
    virtual void                      SetAutoDiscEnabled(bool theEnabled);
    virtual bool                      GetAutoDiscEnabled() const;

    // TL Link IS/OOS (IP Eanbled)
    virtual void                      SetIpEnabled(bool theEnabled);
    virtual bool                      GetIpEnabled() const;

   
    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);


protected:

    void                 RefreshGet();
    void                 RefreshSet();

    // Monitoring attributes
    CT_IBETH_LinkState     itsProtocolLinkState;
   
	uint16 itsP2PVlanId;
	CT_LkType itsLkType; 
	uint8  itsBridgeId;
	uint8  itsVSId;
	uint16 itsBridgeVlanId;
	bool   itsIsMaster;
	bool   itsLinkEnabled;

    // From TL (Topological Link) Command
    CT_DCC_TL_AddrType itsAddressType;
    uint32             itsSourceIpAddress;
    uint32             itsSubnetMask;
    uint32             itsDestIpAddress;
    bool               itsAutoDiscEnabled;
    bool               itsIpEnabled;
    uint32             itsIfIndex;
};

#endif 
