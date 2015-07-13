/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - July 2003
 DESCRIPTION:Definition of the class TSPII_XcIf. Provides abstract 
             interface to the Crossconnect (TSI) hardware
             NOTE: The win32 simulation of this entity is implemented in
             TsPii/src/TSPII_XcSimIf.cpp / .h  due to conflicts between
             the derived target class and the simulation being in the base
             class.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_XcIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>
#include "CommonTypes/CT_AgentFacility.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_XcIf::TSPII_XcIf(bool   theDefault,
                       uint16 theNumPorts,
                       uint16 theNumTslotsPerPort) :
    TSPII_BaseIf(theDefault),
    itsNumPorts(theNumPorts),
    itsNumTslotsPerPort(theNumTslotsPerPort),
    itsCommitted(itsDummyBuf)     // initially force a pointer to a dummy something
{
}

///////////////////////////////////////////////////////////////////////////////
TSPII_XcIf::~TSPII_XcIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::RefreshGet()
{
    itsCommitted = GetCommitXconns();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::RefreshSet()
{
    CommitXconns();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::UpdateValues()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::HwInit()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::Reset()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::AddXconn(const TSPII_XcRecord & theXconn)
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::AddMux(uint16 highOdu, uint16 lowOdu, uint16* tribslot)
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::DeleteXconn(const TSPII_XcRecord & theXconn)
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::DeleteAllXconns()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::CommitXconns()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::HwConfigChanged(bool theIsSwitchModeNew)
{
}

///////////////////////////////////////////////////////////////////////////////
const vector<TSPII_XcRecord> & TSPII_XcIf::GetCommitXconns()
{
    return itsCommitted;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::GetXconnsFromInput(uint16 theInPort, uint16 theInTslot,
                                    vector<TSPII_XcRecord> & theXconns)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::GetXconnFromOutput(uint16 theOutPort, uint16 theOutTslot, 
                                    TSPII_XcRecord & theXconn)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::GetXconnListFromOutput(uint16 theOutPort, uint16 theOutTslot, 
                                            vector<TSPII_XcRecord> & theXconns)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::IsInputPortConnected(uint16 theInPort, bool autoDisconnect)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::IsOutputPortConnected(uint16 theOutPort, bool autoDisconnect)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::AddPortSonetXconns(uint16 thePort)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::DeletePortSonetXconns(uint16 thePort)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_XcIf::TsPortToTspiiPort(uint16 theTsPort)
{
    return theTsPort - 1;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_XcIf::TspiiPortToTsPort(uint16 theTspiiPort)
{
    return theTspiiPort + 1;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_XcIf::TsPortToTspiiPortMux(uint16 theTsPort)
{
    return theTsPort - 1;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_XcIf::TspiiPortToTsPortMux(uint16 theTspiiPort)
{
    return theTspiiPort + 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
CT_FAC_StsMap TSPII_XcIf::GetPointCIngressAlloc()
{
    CT_FAC_StsMap  aStsMap;

    aStsMap.Reset();
    return aStsMap;
}

/////////////////////////////////////////////////////////////////////////////////////////
CT_FAC_StsMap TSPII_XcIf::GetPointCEgressAlloc()
{
    CT_FAC_StsMap  aStsMap;

    aStsMap.Reset();
    return aStsMap;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_XcIf::WriteObjectBinary(FC_Stream & theStream)
{
    int      aXconnCount;
    char     aXconnStr[256];
    vector<TSPII_XcRecord>::iterator aIter;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // write out the size of the list of committed connections
    aXconnCount = itsCommitted.size();
    theStream << aXconnCount;                // Committed

    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        // Write out each Xconn record as a comma seperated string
        sprintf(aXconnStr, "%05d,%05d,%05d,%05d,%s", aIter->InPort,  aIter->InTslot,
                                                  aIter->OutPort, aIter->OutTslot,
                                                  TSPII_XC_TYPE_DISPLAY(aIter->Type));
        theStream << aXconnStr;
    }
    
    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_XcIf::ReadObjectBinary(FC_Stream & theStream)
{
    int            aXconnCount;
    char           aXconnStr[256];
    TSPII_XcRecord aXconn;

    // Delete all the current crossconnects
    DeleteAllXconns();

    // read in the list size
    theStream >> aXconnCount;

    // The timeslot list must be converted from a char string to a vector
    while (aXconnCount > 0)
    {
        // Read each Xconn record as a comma seperated string - write to driver. 
        theStream >> aXconnStr;
        aXconn.InPort   = (uint16) atoi(strtok(aXconnStr, ","));
        aXconn.InTslot  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutPort  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutTslot = (uint16) atoi(strtok(NULL, ","));
        aXconn.Type     = TSPII_XC_TYPE_GET(strtok(NULL, ","));
        AddXconn(aXconn);
        aXconnCount--;
    }

    // Update H/W
    RefreshSet();
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_XcIf::WriteObject(ostream & theStream)
{   
    int      aXconnCount;
    char     aXconnStr[256];
    vector<TSPII_XcRecord>::iterator aIter;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // write out the sizes of each of the three lists
    aXconnCount = itsCommitted.size();
    theStream << FC_InsertVar(aXconnCount);

    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        // Write out each Xconn record as a comma seperated string
        sprintf(aXconnStr, "%05d,%05d,%05d,%05d,%s", aIter->InPort,  aIter->InTslot,
                                                  aIter->OutPort, aIter->OutTslot,
                                                  TSPII_XC_TYPE_DISPLAY(aIter->Type));
        theStream << FC_InsertVar(aXconnStr);
    }
    
    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_XcIf::ReadObject(istream & theStream)
{
    int            aXconnCount;
    char           aXconnStr[256];    // big to avoid overflow
    TSPII_XcRecord aXconn;

    // Delete all the current crossconnects
    DeleteAllXconns();

    // read in the list size
    theStream >> FC_ExtractVar(aXconnCount);
    
    // The timeslot list must be converted from a char string to a vector
    while (aXconnCount > 0)
    {
        // Read each Xconn record as a comma seperated string - write to driver. 
        theStream >> FC_ExtractVar(aXconnStr);
        aXconn.InPort   = (uint16) atoi(strtok(aXconnStr, ","));
        aXconn.InTslot  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutPort  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutTslot = (uint16) atoi(strtok(NULL, ","));
        aXconn.Type     = TSPII_XC_TYPE_GET(strtok(NULL, ","));
        AddXconn(aXconn);
        aXconnCount--;
    }

    // Update H/W
    RefreshSet();
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::Display(FC_Stream & theStream)
{
    int      aXconnCount;
    char     aOutBuf[256];
    int      aIndex;
    vector<TSPII_XcRecord>::const_iterator aIter;
    
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  XC Configuration/Status" << endl;

    aXconnCount = itsCommitted.size();
    theStream << "        itsNumPorts: " << itsNumPorts << endl;
    theStream << "itsNumTslotsPerPort: " << itsNumTslotsPerPort << endl;
    theStream << "       itsCommitted: " << aXconnCount << endl;    
    aIndex = 0;
    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        // Write out each Xconn record as a comma seperated string
        // Convert to "1" based numbering
        sprintf(aOutBuf, "%3d: %05d,%05d,%05d,%05d - %s", aIndex, aIter->InPort + 1,  
                aIter->InTslot + 1, aIter->OutPort + 1, aIter->OutTslot + 1,
                TSPII_XC_TYPE_DISPLAY(aIter->Type));
        theStream << "           " << aOutBuf << endl;
        aIndex++;
    }
    
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
void TSPII_XcIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    int      aXconnCount;
    char     aOutBuf[256];
    int      aIndex;
    uint16   aInPort = 0;
    uint16   aOutPort = 0;
    uint16   aInTslot = 0;
    uint16   aOutTslot = 0;
    bool     printUsage = false;
    bool     aMatch;
    vector<TSPII_XcRecord>::const_iterator aIter;
    
    // Update H/W
    UpdateValues();
    RefreshGet();

    if (argc == 1)
    {
        strcpy(aOutBuf, argv[0]);
        strcat(aOutBuf, ",0,0,0,0,");    // force some tokens in the string.
        aInPort   = (uint16) atoi(strtok(aOutBuf, ","));
        aInTslot  = (uint16) atoi(strtok(NULL, ","));
        aOutPort  = (uint16) atoi(strtok(NULL, ","));
        aOutTslot = (uint16) atoi(strtok(NULL, ","));
        if ((aInPort > itsNumPorts) ||
            (aOutPort > itsNumPorts) ||
            (aInTslot > itsNumTslotsPerPort) ||
            (aOutTslot > itsNumTslotsPerPort))
        {
            printUsage = true;
        }
    }

    if (printUsage)
    {
        fc_cout << "Usage: tspii display xc [ip,it,op,ot]\n"
                   "       ip = Inupt Port [1-" << itsNumPorts << "] (or x for don't care)\n"
                   "       it = Input Timeslot [1-" << itsNumTslotsPerPort << "] (or x for don't care)\n"
                   "       op = Output Port [1-" << itsNumPorts << "] (or x for don't care)\n"
                   "       ot = Output Timeslot [1-" << itsNumTslotsPerPort << "] (or x for don't care)\n"
                << endl;
        return;
    }

    theStream << "  XC Configuration/Status" << endl;

    aXconnCount = itsCommitted.size();
    theStream << "        itsNumPorts: " << itsNumPorts << endl;
    theStream << "itsNumTslotsPerPort: " << itsNumTslotsPerPort << endl;
    theStream << "       itsCommitted: " << aXconnCount << endl;    
    aIndex = 0;
    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        aMatch = true;
        if ((aInPort != 0) && ((aInPort != aIter->InPort + 1)))
        {
            aMatch = false;
        }
        if ((aInTslot != 0) && ((aInTslot != aIter->InTslot + 1)))
        {
            aMatch = false;
        }
        if ((aOutPort != 0) && ((aOutPort != aIter->OutPort + 1)))
        {
            aMatch = false;
        }
        if ((aOutTslot != 0) && ((aOutTslot != aIter->OutTslot + 1)))
        {
            aMatch = false;
        }

        if(aMatch == true)
        {
            // If this connection matches the filter -
            // write out each Xconn record as a comma seperated string
            // Convert to "1" based numbering
            sprintf(aOutBuf, "%3d: %05d,%05d,%05d,%05d - %s", aIndex, aIter->InPort + 1,  
                    aIter->InTslot + 1, aIter->OutPort + 1, aIter->OutTslot + 1,
                    TSPII_XC_TYPE_DISPLAY(aIter->Type));
            theStream << "           " << aOutBuf << endl;
        }
        aIndex++;
    }
    
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::Set(int argc, char ** argv)
{
    TSPII_XcRecord   aXconn;
    char             aOutBuf[256];
    bool             printUsage = false;

    if (((argc == 2) && (strcmp(argv[0], "add") == 0)) ||
        ((argc == 3) && (strcmp(argv[0], "add") == 0)))
    {
        // Read the Xconn record as a comma seperated string. 
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,");    // force some tokens in the string.
        aXconn.InPort   = (uint16) atoi(strtok(aOutBuf, ","));
        aXconn.InTslot  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutPort  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutTslot = (uint16) atoi(strtok(NULL, ","));
        aXconn.Type = TSPII_XC_TYPE_UNKNOWN;   // default type
        if((aXconn.InPort > 0) && (aXconn.InPort <= itsNumPorts) &&
           (aXconn.InTslot > 0) && (aXconn.InTslot <= itsNumTslotsPerPort) &&
           (aXconn.OutPort > 0) && (aXconn.OutPort <= itsNumPorts) &&
           (aXconn.OutTslot > 0) && (aXconn.OutTslot <= itsNumTslotsPerPort))
        {
            // Convert it to "0" based numbering 
            aXconn.InPort--;
            aXconn.InTslot--;
            aXconn.OutPort--;
            aXconn.OutTslot--;
            if(argc == 3)
            {
                // If a third argument it is the type
                aXconn.Type = TSPII_XC_TYPE_GET(argv[2]);
            }
            AddXconn(aXconn);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (((argc == 2) && (strcmp(argv[0], "delete") == 0)) ||
             ((argc == 3) && (strcmp(argv[0], "delete") == 0)))
    {
        // Read the Xconn record as a comma seperated string. 
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,");    // force some tokens in the string.
        aXconn.InPort   = (uint16) atoi(strtok(aOutBuf, ","));
        aXconn.InTslot  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutPort  = (uint16) atoi(strtok(NULL, ","));
        aXconn.OutTslot = (uint16) atoi(strtok(NULL, ","));
        aXconn.Type = TSPII_XC_TYPE_UNKNOWN;   // default type
        if((aXconn.OutPort > 0) &&
           (aXconn.OutTslot > 0))
        {
            // Convert it to "0" based numbering 
            aXconn.InPort--;
            aXconn.InTslot--;
            aXconn.OutPort--;
            aXconn.OutTslot--;
            if(argc == 3)
            {
                // If a third argument it is the type
                aXconn.Type = TSPII_XC_TYPE_GET(argv[2]);
            }
            DeleteXconn(aXconn);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "getfromin") == 0))
    {
        uint16 aInPort;
        uint16 aInTslot;
        int    aIndex;
        vector<TSPII_XcRecord> aXconns;
        vector<TSPII_XcRecord>::const_iterator aIter;

        // Read the input as a comma seperated string. 
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,");    // force some tokens in the string.
        aInPort   = (uint16) atoi(strtok(aOutBuf, ","));
        aInTslot  = (uint16) atoi(strtok(NULL, ","));
        if((aInPort > 0) &&
           (aInTslot > 0))
        {
            // Convert it to "0" based numbering 
            aInPort--;
            aInTslot--;
            if(GetXconnsFromInput(aInPort, aInTslot, aXconns) == true)
            {
                aIndex = 0;
                for(aIter=aXconns.begin(); aIter != aXconns.end(); ++aIter)
                {
                    // We have a match
                    // Write out each Xconn record as a comma seperated string
                    // Convert to "1" based numbering
                    sprintf(aOutBuf, "%3d: %05d,%05d,%05d,%05d - %s", aIndex, aIter->InPort + 1,  
                            aIter->InTslot + 1, aIter->OutPort + 1, aIter->OutTslot + 1, 
                            TSPII_XC_TYPE_DISPLAY(aIter->Type));
                    fc_cout << "           " << aOutBuf << endl;
                    aIndex++;
                }
            }
            else
            {
                fc_cout << "No match found" << endl;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "getfromout") == 0))
    {
        uint16 aOutPort;
        uint16 aOutTslot;

        // Read the input as a comma seperated string. 
        strcpy(aOutBuf, argv[1]);
        strcat(aOutBuf, ",0,0,0,0,");    // force some tokens in the string.
        aOutPort  = (uint16) atoi(strtok(aOutBuf, ","));
        aOutTslot = (uint16) atoi(strtok(NULL, ","));
        if((aOutPort > 0) &&
           (aOutTslot > 0))
        {
            // Convert it to "0" based numbering 
            aOutPort--;
            aOutTslot--;
            if (GetXconnFromOutput(aOutPort, aOutTslot, aXconn) == true)
            {
                // We have a match
                // Write out the Xconn record as a comma seperated string
                // Convert to "1" based numbering
                sprintf(aOutBuf, "     %05d,%05d,%05d,%05d - %s", aXconn.InPort + 1,  
                        aXconn.InTslot + 1, aXconn.OutPort + 1, aXconn.OutTslot + 1, 
                        TSPII_XC_TYPE_DISPLAY(aXconn.Type));
                fc_cout << "           " << aOutBuf << endl;
            }
            else
            {
                fc_cout << "No match found" << endl;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "deleteall") == 0))
    {
        DeleteAllXconns();
    }
    else if ((argc == 1) && (strcmp(argv[0], "commit") == 0))
    {
        CommitXconns();
    }
    else if ((argc == 2) && (strcmp(argv[0], "hwchg") == 0))
    {
        HwConfigChanged(atoi(argv[1]) == 0 ? false : true);
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    add           <ip,it,op,ot> [1 Based] <type=optional>\n"
                   "                  type=lambda,oc3m,oc12m,oc48m,oc3u,oc12u,oc48u,ochm,sts3t,sts12t,sts48t\n"
                   "                       sts1,sts3c,sts12c,sts48c,sts192c,sts1c22v,stsnv,stsnv3,optd1m,optd3m\n"
                   "                       odu0,odu1,odu2\n"
                   "    delete        <ip,it,op,ot> [1 Based] <type=optional>\n"
                   "    deleteall\n"
                   "    commit\n"
                   "    getfromin     <ip,it> [1 Based]\n"
                   "    getfromout    <op,ot> [1 Based]\n"
                   "    hwchg         <0 | 1>\n"
                   << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    return printUsage;
}
             
///////////////////////////////////////////////////////////////////////////////
bool TSPII_XcIf::DisplayTables(int argc, char ** argv)
{
    fc_cout << "Not supported in simulation environment\n";
    bool printUsage = false;

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
DEV_XcTbl* TSPII_XcIf::GetXcTbl()
{
    return NULL;
}

