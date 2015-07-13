/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_LAGOBJECT_H
#define CFG_LAGOBJECT_H

#include <gdef.h>
#include <list>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_AgentFacility.h>
#include "CFG_Object.h"


//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Lag
: public CFG_Object
{

public:

	//Constructor.
    CFG_Lag(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Lag(void);

    // Get Lag Id.
    int GetLagId() const;

    // Set Lag Id.
    void SetLagId(int theLagMaster);

    // Get Lag List.
    const list<CT_Port>& GetLagList();

    // Set Lag List.
    void SetLagList(list<CT_Port>& theLagList);

    // Get Lag Master.
    bool GetLagMaster() const;

    // Set Lag Master.
    void SetLagMaster(bool theLagMaster);

    // Methods to get the start and end of the lag list.
    list<CT_Port>::iterator GetLagListBegin();
    list<CT_Port>::iterator GetLagListEnd();

    // Whether the LAG is provisioned (or not)
    void SetIsProvisioned(bool theProvisioned);
    bool GetIsProvisioned() const;


    // Whether Lacp is enabled for this LAG (or not)
    void SetLacpEnabled(bool theLacpEnabled);
    bool GetLacpEnabled() const;

    // Set Lacp System ID
    void SetLacpSystemID(CT_LacpSystemId theLacpSystemID);
    CT_LacpSystemId GetLacpSystemID() const;

    // Set Lacp System Priority
    void   SetLacpSystemPriority(uint16 theLacpSystemPriority);
    uint16 GetLacpSystemPriority() const;

    // Set Lacp Timeout Mode
    void SetLacpTimeoutMode(CT_TEL_LacpTimeoutMode theLacpTimeoutMode);
    CT_TEL_LacpTimeoutMode GetLacpTimeoutMode() const;

    // Set the Administrative Key for the Aggregator
    void   SetAdminKey(uint16 theAdminKey);
    uint16 GetAdminKey() const;

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

    // Lag Id
    int myLagId;

    // Lag List.
    list<CT_Port> myLagList;

    // SlotId of Lag Master.
    bool myLagMaster;

    // Whether the LAG is provisioned (or not)
    bool myIsProvisioned;

    // Whether Lacp is Enabled
    bool myLacpEnabled;

    // The Lacp System ID
    CT_LacpSystemId myLacpSystemID;

    // The Lacp System ID
    uint16 myLacpSystemPriority;

    // The Lacp Timeout Mode (long/short)
    CT_TEL_LacpTimeoutMode myLacpTimeout;

    // The Administrative Key for the Aggregator
    uint16 myAdminKey;
};

#endif /* CFG_LAGOBJECT_H */

