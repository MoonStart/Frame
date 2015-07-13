/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/12
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_OchOHIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_OchOHIf::TSPII_OchOHIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OchOHIf::~TSPII_OchOHIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::RefreshGet()
{
    // Monitoring attributes
    itsOCI              = GetOCI();
    itsFDIP             = GetFDIP();
    itsFDIO             = GetFDIO();

    // Configuration attributes
    itsForceOCI         = GetForceOCI();
    itsForceFDIP        = GetForceFDIP();
    itsForceFDIO        = GetForceFDIO();
    itsIgnoreForce      = GetIgnoreForce();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::RefreshSet()
{
    // Configuration attributes
    ForceOCI(itsForceOCI);
    ForceFDIP(itsForceFDIP);
    ForceFDIO(itsForceFDIO);
    IgnoreTheForce(itsIgnoreForce);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsOCI              = 0;
    itsFDIP             = 0;
    itsFDIO             = 0;
    // Configuration attributes
    itsForceOCI         = false;
    itsForceFDIP        = false;
    itsForceFDIO        = false;
    itsIgnoreForce      = false;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OchOHIf::GetOCI()
{
    return itsOCI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OchOHIf::GetFDIP()
{
    return itsFDIP;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OchOHIf::GetFDIO()
{
    return itsFDIO;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::ForceOCI(bool theForceOCI)
{
    itsForceOCI = theForceOCI;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::ForceFDIP(bool theForceFDIP)
{
    itsForceFDIP = theForceFDIP;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::ForceFDIO(bool theForceFDIO)
{
    itsForceFDIO = theForceFDIO;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::IgnoreTheForce(bool theEnable)
{
    itsIgnoreForce = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OchOHIf::GetForceOCI() const
{
    return itsForceOCI;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OchOHIf::GetForceFDIP() const
{
    return itsForceFDIP;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OchOHIf::GetForceFDIO() const
{
    return itsForceFDIO;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OchOHIf::GetIgnoreForce() const
{
    return itsIgnoreForce;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OchOHIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << itsOCI;
    theStream << itsFDIP;
    theStream << itsFDIO;

    // Configuration
    theStream << itsForceOCI;
    theStream << itsForceFDIP;
    theStream << itsForceFDIO;
    theStream << itsIgnoreForce;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OchOHIf::ReadObjectBinary(FC_Stream & theStream)
{
    // Monitoring
    theStream >> itsOCI;
    theStream >> itsFDIP;
    theStream >> itsFDIO;

    // Configuration
    theStream >> itsForceOCI;
    theStream >> itsForceFDIP;
    theStream >> itsForceFDIO;
    theStream >> itsIgnoreForce;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_OchOHIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << FC_InsertVar(itsOCI);
    theStream << FC_InsertVar(itsFDIP);
    theStream << FC_InsertVar(itsFDIO);

    // Configuration
    theStream << FC_InsertVar(itsForceOCI);
    theStream << FC_InsertVar(itsForceFDIP);
    theStream << FC_InsertVar(itsForceFDIO);
    theStream << FC_InsertVar(itsIgnoreForce);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_OchOHIf::ReadObject(istream & theStream)
{
    // Monitoring
    theStream >> FC_ExtractVar(itsOCI);
    theStream >> FC_ExtractVar(itsFDIP);
    theStream >> FC_ExtractVar(itsFDIO);

    // Configuration
    theStream >> FC_ExtractVar(itsForceOCI);
    theStream >> FC_ExtractVar(itsForceFDIP);
    theStream >> FC_ExtractVar(itsForceFDIO);
    theStream >> FC_ExtractVar(itsIgnoreForce);

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::DisplayVerbose(FC_Stream & theStream)
{
     // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  OCh Overhead Configuration/Status \n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Force OCI             = " << TEXT_ON_OFF(itsForceOCI)  << "\n";
    theStream << "      Force FDIP            = " << TEXT_ON_OFF(itsForceFDIP) << "\n";
    theStream << "      Force FDIO            = " << TEXT_ON_OFF(itsForceFDIO) << "\n";
    theStream << "      Ignore The Force      = " << TEXT_ON_OFF(itsIgnoreForce) << "\n";
    theStream << "    MONITORING\n";
    theStream << "      OCI  Defect           = " << TEXT_DEFECT(itsOCI)  << "\n";
    theStream << "      FDIP Defect           = " << TEXT_DEFECT(itsFDIP) << "\n";
    theStream << "      FDIO Defect           = " << TEXT_DEFECT(itsFDIO) << "\n";
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    if (IsDefault()) theStream << " DEFAULT";
    theStream << " CONF:";
    if (itsForceOCI ) theStream << " OCI";
    if (itsForceFDIP) theStream << " FDI-P";
    if (itsForceFDIO) theStream << " FDI-O";
    if (itsIgnoreForce) theStream << " IgnoreTheForce";
    theStream << " MON:";
    if (TSPII_DEFECT(itsOCI )) theStream << " OCI";
    if (TSPII_DEFECT(itsFDIP)) theStream << " FDI-P";
    if (TSPII_DEFECT(itsFDIO)) theStream << " FDI-O";
    theStream << endl;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OchOHIf::Set(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "forceoci") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            ForceOCI(false);
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            ForceOCI(true);
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
    else if (argc == 2 && strcmp(argv[0], "ignore") == 0)
    {
        if (strcmp(argv[1], "off") == 0)
        {
            IgnoreTheForce(false);
            RefreshSet();
        }
        else if (strcmp(argv[1], "on") == 0)
        {
            IgnoreTheForce(true);
            RefreshSet();
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
        fc_cout << "    forceoci        <on|off>\n"
                   "    forcefdip       <on|off>\n"
                   "    forcefdio       <on|off>\n"
                   "    ignore          <on|off>" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OchOHIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    
    if (argc == 2 && strcmp(argv[0], "oci") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsOCI)) itsOCI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsOCI)) itsOCI++;
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
        fc_cout << "    oci             <on|off>\n"
                   "    fdip            <on|off>\n"
                   "    fdio            <on|off>" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OchOHIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
