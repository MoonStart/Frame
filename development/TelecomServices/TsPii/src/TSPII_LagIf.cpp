/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds February 2008
 DESCRIPTION:Definition of the class TSPII_LagIf. Models the Link Aggregation
             Group entity.
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_LagIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_LagIf::TSPII_LagIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_LagIf::~TSPII_LagIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::RefreshGet()
{
    // Monitoring attributes

    // Configuration attributes
    itsMembers = GetMembers();
    itsLacpEnabled = GetLacpEnabled();
    itsLacpSystemID = GetLacpSystemID();
    itsLacpSystemPriority = GetLacpSystemPriority();
    itsLacpTimeout = GetLacpTimeoutMode();
    itsAdminKey = GetAdminKey();

}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::RefreshSet()
{
    // Configuration attributes
    SetMembers(itsMembers);
    SetLacpEnabled(itsLacpEnabled);
    SetLacpSystemID(itsLacpSystemID);
    SetLacpSystemPriority(itsLacpSystemPriority);
    SetLacpTimeoutMode(itsLacpTimeout);
    SetAdminKey(itsAdminKey);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes

    // Configuration attributes
    itsMembers.erase(itsMembers.begin(), itsMembers.end());
    itsLacpEnabled = false;
    itsLacpSystemID = CT_LacpSystemId();
    itsLacpSystemPriority = 0;
    itsLacpTimeout = CT_TEL_LacpTimeoutMode_UNKNOWN;
    itsAdminKey = 0;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::InitWarm()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetMaster(bool theEnable)
{
    itsMaster = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_LagIf::GetMaster() const
{
    return itsMaster;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetLagId(uint8 theLagId)
{
    itsLagId = theLagId;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_LagIf::GetLagId() const
{
    return itsLagId;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetMembers(const vector<TSPII_LagMember> & theMembers)
{
    itsMembers = theMembers;
}

///////////////////////////////////////////////////////////////////////////////
const vector<TSPII_LagMember> & TSPII_LagIf::GetMembers()
{
    return itsMembers;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetLacpEnabled(bool theLacpEnabled)
{
    itsLacpEnabled = theLacpEnabled;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_LagIf::GetLacpEnabled() const
{
    return itsLacpEnabled;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetLacpSystemID(const CT_LacpSystemId & theLacpSystemID)
{
    itsLacpSystemID = theLacpSystemID;
}

///////////////////////////////////////////////////////////////////////////////
const CT_LacpSystemId & TSPII_LagIf::GetLacpSystemID() const
{
    return itsLacpSystemID;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetLacpSystemPriority(uint16 theLacpSystemPriority)
{
    itsLacpSystemPriority = theLacpSystemPriority;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_LagIf::GetLacpSystemPriority() const
{
    return itsLacpSystemPriority;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetLacpTimeoutMode(CT_TEL_LacpTimeoutMode theLacpTimeoutMode)
{
    itsLacpTimeout = theLacpTimeoutMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_LacpTimeoutMode TSPII_LagIf::GetLacpTimeoutMode() const
{
    return itsLacpTimeout;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::SetAdminKey(uint16 theAdminKey)
{
    itsAdminKey = theAdminKey;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_LagIf::GetAdminKey() const
{
    return itsAdminKey;
}


///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_LagIf::WriteObjectBinary(FC_Stream & theStream)
{
    int     aMembersSize;
    char    aPort[4];
    char    aSlot[4];
    string  aMembers;
    int     aIndex;
    int     aTimeoutMode;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring attributes

    // Configuration attributes
    theStream << itsMaster;
    theStream << itsLagId;
    theStream << itsLacpEnabled;
    theStream << itsLacpSystemID;
    theStream << itsLacpSystemPriority;
    aTimeoutMode = int(itsLacpTimeout);
    theStream << aTimeoutMode;
    theStream << itsAdminKey;

    // Convert the Members vector into a char string for serialization
    aMembersSize = itsMembers.size();
    theStream << aMembersSize;
    aIndex = 0;
    while (aMembersSize > 0)
    {
        sprintf(aPort, "%3d", itsMembers[aIndex].Port);
        aPort[3] = 0;        // force null termination
        aMembers += aPort;   // add to the running string

        sprintf(aSlot, "%3d", itsMembers[aIndex].Slot);
        aSlot[3] = 0;        // force null termination
        aMembers += aSlot;   // add to the running string

        aMembersSize--;
        aIndex++;
    }
    theStream << aMembers;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_LagIf::ReadObjectBinary(FC_Stream & theStream)
{
    int     aMembersSize;
    char    aMembersBuf[256];
    char    *aPort;
    char    *aSlot;
    TSPII_LagMember aMember;
    int     aTimeoutMode;

    // Monitoring attributes

    // Configuration attributes
    theStream >> itsMaster;
    theStream >> itsLagId;
    theStream >> itsLacpEnabled;
    theStream >> itsLacpSystemID;
    theStream >> itsLacpSystemPriority;
    theStream >> aTimeoutMode;
    itsLacpTimeout = (CT_TEL_LacpTimeoutMode) aTimeoutMode;
    theStream >> itsAdminKey;

    theStream >> aMembersSize;
    theStream >> aMembersBuf;

    // The Member list must be converted from a char string to a vector
    itsMembers.erase(itsMembers.begin(), itsMembers.end());
    aPort = strtok(aMembersBuf, " ");
    if(aPort != NULL)
    {
        aSlot = strtok(NULL, " ");
    }
    while (aMembersSize > 0)
    {
        aMember.Port = ((uint16) atoi(aPort));
        aMember.Slot = ((uint16) atoi(aSlot));
        itsMembers.push_back(aMember);
        aPort = strtok(NULL, " ");
        if(aPort != NULL)
        {
            aSlot = strtok(NULL, " ");
        }
        aMembersSize--;
    }

    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_LagIf::WriteObject(ostream & theStream)
{
    int     aMembersSize;
    char    aPort[4];
    char    aSlot[4];
    string  aMembers;
    int     aIndex;
    int     aTimeoutMode;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring attributes

    // Configuration attributes
    theStream << FC_InsertVar(itsMaster);
    theStream << FC_InsertVar(itsLagId);
    theStream << FC_InsertVar(itsLacpEnabled);
    theStream << FC_InsertVar(itsLacpSystemID);
    theStream << FC_InsertVar(itsLacpSystemPriority);
    aTimeoutMode = int(itsLacpTimeout);
    theStream << FC_InsertVar(aTimeoutMode);
    theStream << FC_InsertVar(itsAdminKey);

    aMembersSize = itsMembers.size();
    theStream << FC_InsertVar(aMembersSize);
    aIndex = 0;
    while (aMembersSize > 0)
    {
        sprintf(aPort, "%3d", itsMembers[aIndex].Port);
        aPort[3] = 0;        // force null termination
        aMembers += aPort;   // add to the running string

        sprintf(aSlot, "%3d", itsMembers[aIndex].Slot);
        aSlot[3] = 0;        // force null termination
        aMembers += aSlot;   // add to the running string

        aMembersSize--;
        aIndex++;
    }
    theStream << FC_InsertVar(aMembers);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_LagIf::ReadObject(istream & theStream)
{
    int     aMembersSize;
    char    aMembersBuf[256];
    char    *aPort;
    char    *aSlot;
    TSPII_LagMember aMember;
    int     aTimeoutMode;

    // Monitoring attributes

    // Configuration attributes
    theStream >> FC_ExtractVar(itsMaster);
    theStream >> FC_ExtractVar(itsLagId);
    theStream >> FC_ExtractVar(itsLacpEnabled);
    theStream >> FC_ExtractVar(itsLacpSystemID);
    theStream >> FC_ExtractVar(itsLacpSystemPriority);
    theStream >> FC_ExtractVar(aTimeoutMode);
    itsLacpTimeout = (CT_TEL_LacpTimeoutMode) aTimeoutMode;
    theStream >> FC_ExtractVar(itsAdminKey);

    theStream >> FC_ExtractVar(aMembersSize);
    theStream >> FC_ExtractVar(aMembersBuf);

    // The Member list must be converted from a char string to a vector
    itsMembers.erase(itsMembers.begin(), itsMembers.end());
    aPort = strtok(aMembersBuf, " ");
    if(aPort != NULL)
    {
        aSlot = strtok(NULL, " ");
    }
    while (aMembersSize > 0)
    {
        aMember.Port = ((uint16) atoi(aPort));
        aMember.Slot = ((uint16) atoi(aSlot));
        itsMembers.push_back(aMember);
        aPort = strtok(NULL, " ");
        if(aPort != NULL)
        {
            aSlot = strtok(NULL, " ");
        }
        aMembersSize--;
    }

    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  Lag Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Master  = " << DISPLAY_BOOL(itsMaster)       << "\n";
    theStream << "      Lag Id  = " << static_cast<uint>(itsLagId)   << "\n";
    theStream << "      Members = " << DisplayMembers(itsMembers)    << "\n";
    theStream << "      Lacp Enabled         = " << DISPLAY_BOOL(itsLacpEnabled)      << "\n";
    theStream << "      Lacp System ID       = " << itsLacpSystemID.DisplayAddr()      << "\n";
    theStream << "      Lacp System Priority = " << itsLacpSystemPriority        << "\n";
    theStream << "      Lacp Timeout Mode    = " << DISPLAY_TIMEOUT_MODE(itsLacpTimeout) << "\n";
    theStream << "      Administrative Key   = " << itsAdminKey        << "\n";

    theStream << "    MONITORING\n";
    theStream << endl;

    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_LagIf::Set(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "master") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetMaster(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetMaster(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "members") == 0) &&
             (strcmp(argv[1], "empty") == 0))
    {
        vector<TSPII_LagMember> aMembers;

        printUsage = false;
        aMembers.erase(aMembers.begin(), aMembers.end());
        SetMembers(aMembers);
    }
    else if ((argc == 2) && (strcmp(argv[0], "id") == 0))
    {
        SetLagId(uint8(strtoul(argv[1], NULL, 0)));
    }
    else if ((argc == 2) && (strcmp(argv[0], "members") == 0))
    {
        vector<TSPII_LagMember> aMembers;
        TSPII_LagMember aMember;
        char            *aPort;
        char            *aSlot;

        printUsage = false;
        aMembers.erase(aMembers.begin(), aMembers.end());
        aPort = strtok(argv[1], ",");
        if(aPort != NULL)
        {
            aSlot = strtok(NULL, ",");
        }
        while ((aPort != NULL) && (aSlot != NULL))
        {
            aMember.Port = ((uint16) atoi(aPort) - 1);      // convert to zero base
            aMember.Slot = ((uint16) atoi(aSlot));      // convert to zero base
            aMembers.push_back(aMember);
            aPort = strtok(NULL, ",");
            if(aPort != NULL)
            {
                aSlot = strtok(NULL, ",");
            }
        }
        SetMembers(aMembers);
    }
    else if ((argc == 2) && (strcmp(argv[0], "lacpen") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetLacpEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetLacpEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 7) && (strcmp(argv[0], "lacpsysid") == 0))
    {
        CT_LacpSystemId systemid(argv[1][0], argv[2][0], argv[3][0], argv[4][0], argv[5][0], argv[6][0]);
        SetLacpSystemID(systemid);
    }
    else if ((argc == 2) && (strcmp(argv[0], "lacpsyspri") == 0))
    {
        uint16 priority = (uint16) atoi(argv[1]);
        SetLacpSystemPriority(priority);
    }
    else if ((argc == 2) && (strcmp(argv[0], "lacptimeout") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_LacpTimeoutMode_ALL; i++) if (strcmp(argv[1], DISPLAY_TIMEOUT_MODE(i)) == 0)
        {
            SetLacpTimeoutMode((CT_TEL_LacpTimeoutMode)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strncmp(argv[0], "adminkey", 5) == 0))
    {
        uint16 key = (uint16) atoi(argv[1]);
        SetAdminKey(key);
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    master         <on, off>" << "\n"
                << "    lacpen         <on, off>, Enable Lacp" << "\n"
                << "    lacpsysid      <ch1 ch2 ch3 ch4 ch5 ch6 (six chars - space separated - System ID)>" << "\n"
                << "    lacpsyspi      <0-65535>, System Priority" << "\n"
                << "    lacptimeout    <TIMEOUT_MODE_SHORT | TIMEOUT_MODE_LONG>" << "\n"
                << "    adminkey       <0-65535>" << "\n"
                << "    id             <1-256> 1 Based" << "\n"
                << "    members        <1,2,3,8|empty> PORT is 0-based || SLOT is 1-based" << "\n"
                << "              where 1=port 2=slot, 3=port, 8=slot " << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_LagIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
string TSPII_LagIf::DisplayMembers(vector<TSPII_LagMember> theMembers)
{
    int     aMembersSize;
    char    aMember[30];
    string  aMembers;
    int     aIndex;

    aIndex = 0;
    aMembersSize = theMembers.size();
    while (aMembersSize > 0)
    {
        sprintf(aMember, "%d,%d, ", (theMembers[aIndex].Port ), (theMembers[aIndex].Slot));  // Convert to 1 base
        //aMember[9] = 0;          // force null termination
        aMembers += aMember;     // add to the running string
        aMembersSize--;
        aIndex++;
    }
    return aMembers;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_LagIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
