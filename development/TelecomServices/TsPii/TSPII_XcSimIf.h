/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  WIN32 - XC
 AUTHOR   :  Denham Reynolds - July 2003
 DESCRIPTION:Specialized class for the Crossconnect implementation
             in the win32 simulation environment.
 MODIFIED :
--------------------------------------------------------------------------*/

#ifndef TSPII_XCSIMIF_H
#define TSPII_XCSIMIF_H

#include "TsPii/TSPII_XcIf.h"

class TSPII_XcLuTblRecord
{
public:
    TSPII_XcType Type;
    uint16       InPort;
    uint16       InTslot;

    TSPII_XcLuTblRecord()
    {
        Type = TSPII_XC_TYPE_UNKNOWN; InPort = 0;  InTslot = 0;
    }
};

class TSPII_XcSimIf : public TSPII_XcIf
{
public:

    /* Constructor */           TSPII_XcSimIf(uint16 theNumPorts,
                                              uint16 theNumTslotsPerPort);
    virtual                     ~TSPII_XcSimIf();

    virtual void                Reset();

                                // Add a single connection
    virtual void                AddXconn(const TSPII_XcRecord & theXconn);

                                // Delete a single connection
    virtual void                DeleteXconn(const TSPII_XcRecord & theXconn);

                                // Delete all the connections
    virtual void                DeleteAllXconns();

                                // Write the Adds and Deletes to hardware
    virtual void                CommitXconns();

                                // Get the committed xcons
    virtual const vector<TSPII_XcRecord> & GetCommitXconns();

                                // Get the list of Output connections given an Input
    virtual bool                GetXconnsFromInput(uint16 theInPort, uint16 theInTslot,
                                                   vector<TSPII_XcRecord> & theXconns);

                                // Get the Input connection given the Output
    virtual bool                GetXconnFromOutput(uint16 theOutPort, uint16 theOutTslot,
                                                   TSPII_XcRecord & theXconn);

private:

    TSPII_XcLuTblRecord     **itsLuTbl;         // Simulation crossconnect lookup table
    vector<TSPII_XcRecord>  itsCommittedBuf;    // Buffer used for simulation only
};

#endif // TSPII_XCSIMIF_H
