/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  WIN32 - XC
 AUTHOR   :  Denham Reynolds - July 2003
 DESCRIPTION:Specialized implementation class of the crossconnect entity for
             use in win32 simulation environment.
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_XcSimIf.h"

const uint16  TSPII_XC_NOT_IN_USE = 0xFFFF;

///////////////////////////////////////////////////////////////////////////////
TSPII_XcSimIf::TSPII_XcSimIf(uint16 theNumPorts,
                             uint16 theNumTslotsPerPort) :
    TSPII_XcIf(false, theNumPorts, theNumTslotsPerPort)
{
    uint16 OutPort;

    // Dynamically allocate the memory for the XC Lookup table
    itsLuTbl = (TSPII_XcLuTblRecord **) malloc(sizeof(TSPII_XcLuTblRecord *) * itsNumPorts);
    for (OutPort=0; OutPort < itsNumPorts; OutPort++)
    {
        itsLuTbl[OutPort] = (TSPII_XcLuTblRecord *) malloc(sizeof(TSPII_XcLuTblRecord) *
                                                           itsNumTslotsPerPort);
    }

    itsCommitted.erase(itsCommitted.begin(), itsCommitted.end());  // initial clear
    Reset();        // this initializes the rest.
}

///////////////////////////////////////////////////////////////////////////////
TSPII_XcSimIf::~TSPII_XcSimIf()
{
    uint16 OutPort;

    for (OutPort = 0; OutPort < itsNumPorts; OutPort++)
    {
        free(itsLuTbl[OutPort]);    // release the memory for this XC port
    }
    free(itsLuTbl);                 // release top level pointer table
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcSimIf::Reset()
{
    vector<TSPII_XcRecord>::iterator aIter;

    TSPII_BaseIf::Reset();      // Call base class

    DeleteAllXconns();          // Clears out the Look Up Table
    RefreshGet();               // Get the current crossconnect list

    // Rebuild the itsLuTbl from the hardware view of crossconnects.
    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        itsLuTbl[aIter->OutPort][aIter->OutTslot].Type = aIter->Type;
        itsLuTbl[aIter->OutPort][aIter->OutTslot].InPort = aIter->InPort;
        itsLuTbl[aIter->OutPort][aIter->OutTslot].InTslot = aIter->InTslot;
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcSimIf::AddXconn(const TSPII_XcRecord & theXconn)
{

    if((theXconn.InPort >= itsNumPorts) ||
       (theXconn.OutPort >= itsNumPorts) ||
       (theXconn.InTslot >= itsNumTslotsPerPort) ||
       (theXconn.OutTslot >= itsNumTslotsPerPort))
    {
        // Out of range parameters - ignore
        return;
    }

    // Write the new crossconnect in to the look up table. Replaces any previous
    // crossconnect with the same destination port/timeslot. This is like an
    // automatic delete.
    itsLuTbl[theXconn.OutPort][theXconn.OutTslot].Type = theXconn.Type;
    itsLuTbl[theXconn.OutPort][theXconn.OutTslot].InPort = theXconn.InPort;
    itsLuTbl[theXconn.OutPort][theXconn.OutTslot].InTslot = theXconn.InTslot;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcSimIf::DeleteXconn(const TSPII_XcRecord & theXconn)
{

    if((theXconn.OutPort >= itsNumPorts) ||
       (theXconn.OutTslot >= itsNumTslotsPerPort))
    {
        // Out of range parameters - ignore
        return;
    }

    // Set the referenced crossconnect to the look up table to NOT_IN_USE
    itsLuTbl[theXconn.OutPort][theXconn.OutTslot].Type = TSPII_XC_TYPE_UNKNOWN;
    itsLuTbl[theXconn.OutPort][theXconn.OutTslot].InPort = TSPII_XC_NOT_IN_USE;
    itsLuTbl[theXconn.OutPort][theXconn.OutTslot].InTslot = TSPII_XC_NOT_IN_USE;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcSimIf::DeleteAllXconns()
{
    uint16 OutPort;
    uint16 OutTslot;

    for (OutPort = 0; OutPort < itsNumPorts; OutPort++)
    {
        for (OutTslot = 0; OutTslot < itsNumTslotsPerPort; OutTslot++)
        {
            // Set this crossconnect entry in the look up table to NOT_IN_USE
            itsLuTbl[OutPort][OutTslot].InPort = TSPII_XC_NOT_IN_USE;
            itsLuTbl[OutPort][OutTslot].InTslot = TSPII_XC_NOT_IN_USE;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcSimIf::CommitXconns()
{
    uint16         OutPort;
    uint16         OutTslot;
    TSPII_XcRecord aXconn;

    itsCommitted.erase(itsCommitted.begin(), itsCommitted.end());   // Erase the vector

    // Create a vector version of the internal lookup table.
    for (OutPort = 0; OutPort < itsNumPorts; OutPort++)
    {
        for (OutTslot = 0; OutTslot < itsNumTslotsPerPort; OutTslot++)
        {
            if (itsLuTbl[OutPort][OutTslot].InPort != TSPII_XC_NOT_IN_USE)
            {
                aXconn.Type = itsLuTbl[OutPort][OutTslot].Type;
                aXconn.InPort = itsLuTbl[OutPort][OutTslot].InPort;
                aXconn.InTslot = itsLuTbl[OutPort][OutTslot].InTslot;
                aXconn.OutPort = OutPort;
                aXconn.OutTslot = OutTslot;
                itsCommitted.push_back(aXconn);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
const vector<TSPII_XcRecord> & TSPII_XcSimIf::GetCommitXconns()
{
    return itsCommitted;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcSimIf::GetXconnsFromInput(uint16 theInPort, uint16 theInTslot,
                                       vector<TSPII_XcRecord> & theXconns)
{
    uint16         OutPort;
    uint16         OutTslot;
    TSPII_XcRecord aXconn;
    uint16         Count = 0;

    // Create a vector list of connections that match.
    for (OutPort = 0; OutPort < itsNumPorts; OutPort++)
    {
        for (OutTslot = 0; OutTslot < itsNumTslotsPerPort; OutTslot++)
        {
            if ((itsLuTbl[OutPort][OutTslot].InPort == theInPort) &&
                (itsLuTbl[OutPort][OutTslot].InTslot == theInTslot))
            {
                aXconn.Type = itsLuTbl[OutPort][OutTslot].Type;
                aXconn.InPort = itsLuTbl[OutPort][OutTslot].InPort;
                aXconn.InTslot = itsLuTbl[OutPort][OutTslot].InTslot;
                aXconn.OutPort = OutPort;
                aXconn.OutTslot = OutTslot;
                theXconns.push_back(aXconn);
                Count++;
            }
        }
    }

    if(Count != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcSimIf::GetXconnFromOutput(uint16 theOutPort, uint16 theOutTslot,
                                       TSPII_XcRecord & theXconn)
{
    if((theOutPort >= itsNumPorts) ||
       (theOutTslot >= itsNumTslotsPerPort))
    {
        // Out of range parameters - ignore
        return false;
    }

    // See if this Input is mapped to an output
    if(itsLuTbl[theOutPort][theOutTslot].InPort != TSPII_XC_NOT_IN_USE)
    {
        theXconn.Type = itsLuTbl[theOutPort][theOutTslot].Type;
        theXconn.InPort = itsLuTbl[theOutPort][theOutTslot].InPort;
        theXconn.InTslot = itsLuTbl[theOutPort][theOutTslot].InTslot;
        theXconn.OutPort = theOutPort;
        theXconn.OutTslot = theOutTslot;
        return true;
    }
    else
    {
        return false;
    }
}

