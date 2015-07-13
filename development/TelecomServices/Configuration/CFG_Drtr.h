/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_DRTROBJECT_H
#define CFG_DRTROBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include <vector>

#include "CFG_Object.h"


//This object contains all the DRTR configuration.
class CFG_Drtr
: public CFG_Object
{

public:

	//Constructor.
    CFG_Drtr(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Drtr(void);

    //Set Command Sequence
    void  SetCommandSequence(CT_DCC_Sequence theCommandSequence);

    //Get Command Sequence
    CT_DCC_Sequence GetCommandSequence() const;

    // OSI Router Parameters

    //This method is used to set the TID ID for the Dcc Router.
    void SetTIDID(CT_AreaAddr& theTIDID);

    //This method returns the TID ID for the Dcc Router.
    CT_AreaAddr GetTIDID() const;

    //This method is used to set the Router ID for the Dcc Router.
    void SetRouterID(CT_DCC_RouterId theRouterID);

    //This method returns the Router ID for the Dcc Router.
    CT_DCC_RouterId GetRouterID() const;

    //This method is used to Enable the Dcc Router.
    void SetDCCRouterEnabled(bool theDCCRouterEnabled);

    //This method returns the state of the Dcc Router.
    bool GetDCCRouterEnabled() const;

    //This method is used to set the Router Operation counter.
    void SetIsProvisioned(bool theIsProvisioned);

    //This method returns the value of the Router Operation count.
    bool GetIsProvisioned() const;

    //This method is used to set the Primary address of the Dcc Router.
    void SetPrimaryAreaAddr(CT_AreaAddr& thePrimaryAreaAddr);

    //This method returns the Primary address of the Dcc Router.
    CT_AreaAddr GetPrimaryAreaAddr() const;

    //This method is used to set the First Auxilliary address of the Dcc Router.
    void SetFirstAuxAreaAddr(CT_AreaAddr& theFirstAuxAreaAddr);

    //This method returns the First Auxilliary address of the Dcc Router.
    CT_AreaAddr GetFirstAuxAreaAddr() const;

    //This method is used to set the Second Auxilliary address of the Dcc Router.
    void SetSecondAuxAreaAddr(CT_AreaAddr& theSecondAuxAreaAddr);

    //This method returns the Second Auxilliary address of the Dcc Router.
    CT_AreaAddr GetSecondAuxAreaAddr() const;

    //This method is used to set the PGNE 1 IP Address for the GRE Tunnel.
    void SetPgne1IpAddress(uint32 thePgneIpAddress);

    //This method returns the PGNE 1 IP Address for the GRE Tunnel.
    uint32 GetPgne1IpAddress() const;

    //This method is used to set the PGNE 2 IP Address for the GRE Tunnel.
    void SetPgne2IpAddress(uint32 thePgneIpAddress);

    //This method returns the PGNE 2 IP Address for the GRE Tunnel.
    uint32 GetPgne2IpAddress() const;

    // Set DRTR Maximum Number of Area Addresses
    void SetMaxNumAddr(uint8 theMaxNumAddr);

    //Get DRTR Maximum Number of Area Addresses
    uint8 GetMaxNumAddr() const;


    //This method is used to set the Routing System ID.
    void SetRoutingSystemID(CT_AreaAddr& theRoutingSystemID);

    //This method returns the Routing System ID.
    CT_AreaAddr GetRoutingSystemID() const;


    // Set DRTR Routing Level
    void SetRoutingLevel(uint8 theRoutingLevel);

    //Get DRTR Routing Level
    uint8 GetRoutingLevel() const;

    // Set DRTR Maximum Lifetime Control
    void SetMaxLifetimeControl(uint8 theMaxLifetimeControl);

    //Get DRTR Maximum Lifetime Control
    uint8 GetMaxLifetimeControl() const;


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

    CT_DCC_Sequence  myCommandSequence;

    // For Router
    CT_AreaAddr myTIDID;
    CT_DCC_RouterId myRouterID;
    bool myDCCRouterEnabled;
    bool myIsProvisioned;
    CT_AreaAddr myPrimaryAreaAddr;
    CT_AreaAddr myFirstAuxAreaAddr;
    CT_AreaAddr mySecondAuxAreaAddr;
    uint8 myMaxNumAddr;
    CT_AreaAddr myRoutingSystemID;
    uint8 myRoutingLevel;
    uint8 myMaxLifetimeControl;
    uint32 myPgne1IpAddress;
    uint32 myPgne2IpAddress;
};

#endif /* CFG_DRTROBJECT_H */

