/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_DCCLOBJECT_H
#define CFG_DCCLOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_DCC_Definitions.h>


#include "CFG_Object.h"


// This object contains all the generic DCC Link  
// section configuration for one DCCL.
class CFG_Dccl
: public CFG_Object
{

public:

	//Constructor.
    CFG_Dccl(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Dccl(void);


    void SetLinkRouterID(CT_DCC_RouterId theRouterId);
    CT_DCC_RouterId GetLinkRouterID() const;

    void SetRouterShelfID(CT_ShelfId theRouterShelfId);
    CT_ShelfId GetRouterShelfID() const;

    void SetIntfID(CT_IfIndexIdent theIfIndexId);
    CT_IfIndexIdent GetIntfID() const;

    void SetLinkProfileID(CT_Link_ProfileId theLprfId);
    CT_Link_ProfileId GetLinkProfileID() const;


    // Not transferred via Framework
    // Whether the link is provisioned (or not)
    void SetIsProvisioned(bool theProvisioned);
    bool GetIsProvisioned() const;


    // From LAPD Command
    void SetProtocolLinkEnabled(bool theProtocolLinkEnabled);
    bool GetProtocolLinkEnabled() const;

    void SetChecksumEnabled(bool theChecksumEnabled);
    bool GetChecksumEnabled() const;

    void SetHoldingTimerMultiplier(uint8 theHTMultiplier);
    uint8 GetHoldingTimerMultiplier() const;

    void SetConfigurationTimer(uint16 theConfigTimer);
    uint16 GetConfigurationTimer() const;

    void SetHelloTimer(uint8 theHelloTimer);
    uint8 GetHelloTimer() const;

    void SetDefaultMetric(uint8 theDefaultMetric);
    uint8 GetDefaultMetric() const;

    void SetReDirectHoldingTimer(uint16 theReDirectHoldingTimer);
    uint16 GetReDirectHoldingTimer() const;

    void SetLinkRoutingLevel(uint8 theRoutingLevel);
    uint8 GetLinkRoutingLevel() const;

    void SetESConfigurationTimer(uint16 theESConfigurationTimer);
    uint16 GetESConfigurationTimer() const;

    void SetFollowProtection(bool theFollowProtectionEnabled);
    bool GetFollowProtection() const;


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

    bool              myIsProvisioned;

    CT_DCC_RouterId   myLinkRouterId;
    CT_ShelfId        myRouterShelfId;
    CT_IfIndexIdent   myIfIndexId;
    CT_Link_ProfileId myLprfId;

    bool              myProtocolLinkEnabled;
    bool              myChecksumEnabled;
    uint8             myHTMultiplier;
    uint16            myConfigTimer;
    uint8             myHelloTimer;
    uint8             myDefaultMetric;
    uint16            myReDirectHoldingTimer;
    uint8             myLinkRoutingLevel;
    uint16            myESConfigurationTimer;
    bool              myFollowProtectionEnabled;

};

#endif /* CFG_DCCLOBJECT_H */

