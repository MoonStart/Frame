/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/12
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_OmsOHIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_OmsOHIf::TSPII_OmsOHIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OmsOHIf::~TSPII_OmsOHIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::RefreshGet()
{
    // Monitoring attributes
    itsPMI              = GetPMI();
    itsBDIP             = GetBDIP();
    itsBDIO             = GetBDIO();
    itsFDIP             = GetFDIP();
    itsFDIO             = GetFDIO();

    // Configuration attributes
    itsForcePMI         = GetForcePMI();
    itsForceBDIP        = GetForceBDIP();
    itsForceBDIO        = GetForceBDIO();
    itsForceFDIP        = GetForceFDIP();
    itsForceFDIO        = GetForceFDIO();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::RefreshSet()
{
    // Configuration attributes
    ForcePMI(itsForcePMI);
    ForceBDIP(itsForceBDIP);
    ForceBDIO(itsForceBDIO);
    ForceFDIP(itsForceFDIP);
    ForceFDIO(itsForceFDIO);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsPMI              = 0;
    itsBDIP             = 0;
    itsBDIO             = 0;
    itsFDIP             = 0;
    itsFDIO             = 0;

    // Configuration attributes
    itsForcePMI         = false;
    itsForceBDIP        = false;
    itsForceBDIO        = false;
    itsForceFDIP        = false;
    itsForceFDIO        = false;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OmsOHIf::GetPMI()
{
    return itsPMI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OmsOHIf::GetBDIP()
{
    return itsBDIP;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OmsOHIf::GetBDIO()
{
    return itsBDIO;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OmsOHIf::GetFDIP()
{
    return itsFDIP;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OmsOHIf::GetFDIO()
{
    return itsFDIO;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::ForcePMI(bool theForcePMI)
{
    itsForcePMI = theForcePMI;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::ForceBDIP(bool theForceBDIP)
{
    itsForceBDIP = theForceBDIP;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::ForceBDIO(bool theForceBDIO)
{
    itsForceBDIO = theForceBDIO;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::ForceFDIP(bool theForceFDIP)
{
    itsForceFDIP = theForceFDIP;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::ForceFDIO(bool theForceFDIO)
{
    itsForceFDIO = theForceFDIO;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OmsOHIf::GetForcePMI() const
{
    return itsForcePMI;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OmsOHIf::GetForceBDIP() const
{
    return itsForceBDIP;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OmsOHIf::GetForceBDIO() const
{
    return itsForceBDIO;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OmsOHIf::GetForceFDIP() const
{
    return itsForceFDIP;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OmsOHIf::GetForceFDIO() const
{
    return itsForceFDIO;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OmsOHIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << itsPMI;
    theStream << itsFDIP;
    theStream << itsFDIO;
    theStream << itsBDIP;
    theStream << itsBDIO;

    // Configuration
    theStream << itsForcePMI;
    theStream << itsForceFDIP;
    theStream << itsForceFDIO;
    theStream << itsForceBDIP;
    theStream << itsForceBDIO;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OmsOHIf::ReadObjectBinary(FC_Stream & theStream)
{
    // Monitoring
    theStream >> itsPMI;
    theStream >> itsFDIP;
    theStream >> itsFDIO;
    theStream >> itsBDIP;
    theStream >> itsBDIO;

    // Configuration
    theStream >> itsForcePMI;
    theStream >> itsForceFDIP;
    theStream >> itsForceFDIO;
    theStream >> itsForceBDIP;
    theStream >> itsForceBDIO;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_OmsOHIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << FC_InsertVar(itsPMI);
    theStream << FC_InsertVar(itsFDIP);
    theStream << FC_InsertVar(itsFDIO);
    theStream << FC_InsertVar(itsBDIP);
    theStream << FC_InsertVar(itsBDIO);

    // Configuration
    theStream << FC_InsertVar(itsForcePMI);
    theStream << FC_InsertVar(itsForceFDIP);
    theStream << FC_InsertVar(itsForceFDIO);
    theStream << FC_InsertVar(itsForceBDIP);
    theStream << FC_InsertVar(itsForceBDIO);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_OmsOHIf::ReadObject(istream & theStream)
{
    // Monitoring
    theStream >> FC_ExtractVar(itsPMI);
    theStream >> FC_ExtractVar(itsFDIP);
    theStream >> FC_ExtractVar(itsFDIO);
    theStream >> FC_ExtractVar(itsBDIP);
    theStream >> FC_ExtractVar(itsBDIO);

    // Configuration
    theStream >> FC_ExtractVar(itsForcePMI);
    theStream >> FC_ExtractVar(itsForceFDIP);
    theStream >> FC_ExtractVar(itsForceFDIO);
    theStream >> FC_ExtractVar(itsForceBDIP);
    theStream >> FC_ExtractVar(itsForceBDIO);

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  OMS Overhead Configuration/Status \n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Force PMI             = " << TEXT_ON_OFF(itsForcePMI)   << " \n";
    theStream << "      Force BDIP            = " << TEXT_ON_OFF(itsForceBDIP)  << " \n";
    theStream << "      Force BDIO            = " << TEXT_ON_OFF(itsForceBDIO)  << " \n";
    theStream << "      Force FDIP            = " << TEXT_ON_OFF(itsForceFDIP)  << " \n";
    theStream << "      Force FDIO            = " << TEXT_ON_OFF(itsForceFDIO)  << " \n";
    theStream << "    MONITORING " << "\n";
    theStream << "      PMI  Defect           = " << TEXT_DEFECT(itsPMI)  << " \n";
    theStream << "      BDIP Defect           = " << TEXT_DEFECT(itsBDIP) << " \n";
    theStream << "      BDIO Defect           = " << TEXT_DEFECT(itsBDIO) << " \n";
    theStream << "      FDIP Defect           = " << TEXT_DEFECT(itsFDIP) << " \n";
    theStream << "      FDIO Defect           = " << TEXT_DEFECT(itsFDIO) << " \n";
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OmsOHIf::Set(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "forcepmi") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            ForcePMI(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            ForcePMI(true);
        }
        else
        {
            printUsage = true;
        }
    }    
    else if (argc == 2 && strcmp(argv[0], "forcebdip") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            ForceBDIP(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            ForceBDIP(true);
        }
        else
        {
            printUsage = true;
        }
    }    
    else if (argc == 2 && strcmp(argv[0], "forcebdio") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            ForceBDIO(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            ForceBDIO(true);
        }
        else
        {
            printUsage = true;
        }
    }    
    else if (argc == 2 && strcmp(argv[0], "forcefdip") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            ForceFDIP(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            ForceFDIP(true);
        }
        else
        {
            printUsage = true;
        }
    }    
    else if (argc == 2 && strcmp(argv[0], "forcefdio") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            ForceFDIO(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            ForceFDIO(true);
        }
        else
        {
            printUsage = true;
        }
    }    
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    forcepmi        <on|off>\n"
                   "    forcebdip       <on|off>\n"
                   "    forcebdio       <on|off>\n"
                   "    forcefdip       <on|off>\n"
                   "    forcefdio       <on|off>" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OmsOHIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    
    if (argc == 2 && strcmp(argv[0], "pmi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsPMI)) itsPMI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsPMI)) itsPMI++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "bdip") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBDIP)) itsBDIP++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBDIP)) itsBDIP++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "bdio") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBDIO)) itsBDIO++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBDIO)) itsBDIO++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "fdip") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsFDIP)) itsFDIP++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsFDIP)) itsFDIP++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "fdio") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsFDIO)) itsFDIO++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsFDIO)) itsFDIO++;
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    pmi             <on|off>\n"
                   "    bdip            <on|off>\n"
                   "    bdio            <on|off>\n" 
                   "    fdip            <on|off>\n"
                   "    fdio            <on|off>\n" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OmsOHIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
