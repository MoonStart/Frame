/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - February 2008
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for ports hardware
 MODIFIED :
--------------------------------------------------------------------------*/

#ifndef TSPII_LAGIF_H
#define TSPII_LAGIF_H

#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_AgentFacility.h"
#include "TsPii/TSPII_BaseIf.h"

// This class describes one Link Aggregation Group member
class TSPII_LagMember
{
public:
    uint16        Port;       // Port - "0" based
    uint16        Slot;       // Card slot - "0" based

    TSPII_LagMember()
    {
        Port=0; Slot=0;
    }

    void Clear()
    {
        Port=0; Slot=0;
    }

    void operator=(const TSPII_LagMember &right)
    {
        this->Port = right.Port;
        this->Slot = right.Slot;
    }

    bool operator==( const TSPII_LagMember &right) const
    {
        if((this->Port == right.Port) &&
           (this->Slot == right.Slot))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class TSPII_LagIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_LagIf(bool theDefault = false);
    virtual                           ~TSPII_LagIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Monitor Interfaces
    // -----------------------------------------------------------------------------------
    
    // -----------------------------------------------------------------------------------
    // Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetMaster(bool theEnable);
    virtual bool                      GetMaster() const;

    virtual void                      SetLagId(uint8 theLagId);
    virtual uint8                     GetLagId() const;

    virtual void                            SetMembers(const vector<TSPII_LagMember> & theMembers); 
    virtual const vector<TSPII_LagMember> & GetMembers();

    // Whether Lacp is enabled for this LAG (or not)
    virtual void                      SetLacpEnabled(bool theLacpEnabled);
    virtual bool                      GetLacpEnabled() const;

    // Set Lacp System ID
    virtual void                      SetLacpSystemID(const CT_LacpSystemId & theLacpSystemID);
    virtual const CT_LacpSystemId   & GetLacpSystemID() const;

    // Set Lacp System Priority
    virtual void                      SetLacpSystemPriority(uint16 theLacpSystemPriority);
    virtual uint16                    GetLacpSystemPriority() const;

    // Set Lacp Timeout Mode
    virtual void                      SetLacpTimeoutMode(CT_TEL_LacpTimeoutMode theLacpTimeoutMode);
    virtual CT_TEL_LacpTimeoutMode    GetLacpTimeoutMode() const;

    // Set the Administrative Key for the Aggregator
    virtual void                      SetAdminKey(uint16 theAdminKey);
    virtual uint16                    GetAdminKey() const;

    // Warm Restart
    virtual void                      InitWarm();

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                      Display(FC_Stream & theStream);
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);

protected:

    void                 RefreshGet();
    void                 RefreshSet();
    string               DisplayMembers(vector<TSPII_LagMember> theMembers);

    // Monitoring attributes
    
    // Configuration attributes
    bool                    itsMaster;
    uint8                   itsLagId;
	int                     itsSlotId;
    vector<TSPII_LagMember> itsMembers;
    bool                    itsLacpEnabled;
    CT_LacpSystemId         itsLacpSystemID;
    uint16                  itsLacpSystemPriority;
    CT_TEL_LacpTimeoutMode  itsLacpTimeout;
    uint16                  itsAdminKey;

};

#endif // TSPII_LAGIF_H
