/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Opm
 AUTHOR   :  Eric Bernier November 30th 1999
 DESCRIPTION:Definition of the class TSPII_OtsOHIf
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_OtsOHIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_OtsOHIf::TSPII_OtsOHIf(bool theDefault):
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OtsOHIf::~TSPII_OtsOHIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::RefreshGet()
{
    // Monitoring attributes
    itsPMI              = GetPMI();
    itsBDIP             = GetBDIP();
    itsBDIO             = GetBDIO();
    itsRxTrace          = GetRxTTI();

    // Configuration attributes
    itsForcePMI         = GetForcePMI();
    itsForceBDIP        = GetForceBDIP();
    itsForceBDIO        = GetForceBDIO();
    itsTxTrace          = GetTxTTI();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::RefreshSet()
{
    // Configuration attributes
    ForcePMI(itsForcePMI);
    ForceBDIP(itsForceBDIP);
    ForceBDIO(itsForceBDIO);
    SetTxTTI(itsTxTrace);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsPMI              = 0;
    itsBDIP             = 0;
    itsBDIO             = 0;
    itsRxTrace          = CT_G709Trace();
    // Configuration attributes
    itsForcePMI         = false;
    itsForceBDIP        = false;
    itsForceBDIO        = false;
    itsTxTrace          = CT_G709Trace();
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OtsOHIf::GetPMI()
{
    return itsPMI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OtsOHIf::GetBDIP()
{
    return itsBDIP;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OtsOHIf::GetBDIO()
{
    return itsBDIO;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace& TSPII_OtsOHIf::GetRxTTI()
{
    return itsRxTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::ForceBDIP(bool theForceBDIP)
{
    itsForceBDIP = theForceBDIP;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::ForceBDIO(bool theForceBDIO)
{
    itsForceBDIO = theForceBDIO;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::ForcePMI(bool theForcePMI)
{
    itsForcePMI = theForcePMI;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::SetTxTTI(const CT_G709Trace & theTrace)
{
    itsTxTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OtsOHIf::GetForceBDIP() const
{
    return itsForceBDIP;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OtsOHIf::GetForceBDIO() const
{
    return itsForceBDIO;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OtsOHIf::GetForcePMI() const
{
    return itsForcePMI;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_OtsOHIf::GetTxTTI() const
{
    return itsTxTrace;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OtsOHIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << itsPMI;
    theStream << itsBDIP;
    theStream << itsBDIO;
    theStream << itsRxTrace;

    // Configuration
    theStream << itsForcePMI;
    theStream << itsForceBDIP;
    theStream << itsForceBDIO;
    theStream << itsTxTrace;
    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OtsOHIf::ReadObjectBinary(FC_Stream & theStream)
{
    // Monitoring
    theStream >> itsPMI;
    theStream >> itsBDIP;
    theStream >> itsBDIO;
    theStream >> itsRxTrace;

    // Configuration
    theStream >> itsForcePMI;
    theStream >> itsForceBDIP;
    theStream >> itsForceBDIO;
    theStream >> itsTxTrace;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_OtsOHIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << FC_InsertVar(itsPMI);
    theStream << FC_InsertVar(itsBDIP);
    theStream << FC_InsertVar(itsBDIO);
    theStream << itsRxTrace;

    // Configuration
    theStream << FC_InsertVar(itsForcePMI);
    theStream << FC_InsertVar(itsForceBDIP);
    theStream << FC_InsertVar(itsForceBDIO);
    theStream << itsTxTrace;

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_OtsOHIf::ReadObject(istream & theStream)
{
    // Monitoring
    theStream >> FC_ExtractVar(itsPMI);
    theStream >> FC_ExtractVar(itsBDIP);
    theStream >> FC_ExtractVar(itsBDIO);
    theStream >> itsRxTrace;

    // Configuration
    theStream >> FC_ExtractVar(itsForcePMI);
    theStream >> FC_ExtractVar(itsForceBDIP);
    theStream >> FC_ExtractVar(itsForceBDIO);
    theStream >> itsTxTrace;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::Display(FC_Stream & theStream)
{
    // Refresh H/W
    UpdateValues();
    RefreshGet();

    theStream << "  OTS Overhead Configuration/Status \n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Force PMI             = " << TEXT_ON_OFF(itsForcePMI)                   << "\n";
    theStream << "      Force BDIP            = " << TEXT_ON_OFF(itsForceBDIP)                  << "\n";
    theStream << "      Force BDIO            = " << TEXT_ON_OFF(itsForceBDIO)                  << "\n";
    theStream << "      OTS TX TTI  =   Sapi  = " << itsTxTrace.GetSapiPrintable()              << "\n";
    theStream << "                      Dapi  = " << itsTxTrace.GetDapiPrintable()              << "\n";
    theStream << "                   Operator = " << itsTxTrace.GetOperatorSpecificPrintable()  << "\n";
    theStream << "                      CRC7  = " << (uint32)itsTxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsTxTrace.IsValid())          << "\n";
    theStream << "    MONITORING " << "\n";
    theStream << "      PMI  Defect           = " << TEXT_DEFECT(itsPMI)  << " \n";
    theStream << "      BDIP Defect           = " << TEXT_DEFECT(itsBDIP) << " \n";
    theStream << "      BDIO Defect           = " << TEXT_DEFECT(itsBDIO) << " \n";
    theStream << "      OTS RX TTI  =   Sapi  = " << itsRxTrace.GetSapiPrintable()              << "\n";
    theStream << "                      Dapi  = " << itsRxTrace.GetDapiPrintable()              << "\n";
    theStream << "                   Operator = " << itsRxTrace.GetOperatorSpecificPrintable()  << "\n";
    theStream << "                      CRC7  = " << (uint32)itsRxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsRxTrace.IsValid())          << "\n";
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OtsOHIf::Set(int argc, char ** argv)
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
    else if (argc == 4 && strcmp(argv[0], "txtti") == 0)
    {
        CT_G709Trace trace(argv[1], argv[2], argv[3]);
        SetTxTTI(trace);
    }
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    forcepmi        <on|off> \n"
                   "    forcebdip       <on|off> \n"
                   "    forcebdio       <on|off> \n"
                   "    txtti           <sapi(15 char max)> <dapi(15 char max)> <operator(28 char max)>" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OtsOHIf::Simul(int argc, char ** argv)
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
    else if (argc == 4 && strcmp(argv[0], "rxtti") == 0)
    {
        itsRxTrace = CT_G709Trace(argv[1], argv[2], argv[3]);
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
                   "    rxtti           <sapi(15 char max)> <dapi(15 char max)> <trace(28 char max)>\n" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OtsOHIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}