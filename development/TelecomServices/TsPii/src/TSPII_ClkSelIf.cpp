/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - March 2004
 DESCRIPTION:Definition of the class TSPII_ClkSelIf. Provides abstract 
             interface to SONET/SDH Clock Selection hardware. 
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_ClkSelIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_ClkSelIf::TSPII_ClkSelIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_ClkSelIf::~TSPII_ClkSelIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::RefreshGet()
{
    // Monitoring attributes
    itsTimingState = GetTimingState();
    itsFreerunSsm = GetFreerunSsm();
	itsMateClockMode = GetMateClockMode();

    // Configuration attributes
    itsTimingMode  = GetTimingMode();
    itsSelectedRef = GetSelectedRef();
	itsClockMode   = GetClockMode();
    itsFramedTimingInputsEnable = GetFramedTimingInputsEnable();
    itsClockBandwidth = GetClockBandwidth();
    itsClkOutEnable = GetClkOutEnable();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::RefreshSet()
{
    // Configuration attributes
    SetTimingMode(itsTimingMode);
    SetSelectedRef(itsSelectedRef);
	SetClockMode(itsClockMode);
    SetFramedTimingInputsEnable(itsFramedTimingInputsEnable);
    SetClockBandwidth(itsClockBandwidth);
    SetClkOutEnable(itsClkOutEnable);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsTimingState    = CT_TEL_CLKSEL_STATE_FREERUN;
    itsFreerunSsm     = CT_RxSsm_SMC;
	itsMateClockMode  = CT_TEL_CLKMODE_UNKNOWN;

    // Configuration attributes
    itsTimingMode    = CT_TEL_CLKSEL_MODE_INTERNAL;
    itsSelectedRef   = CT_TEL_CLKSEL_REF_INTERNAL;
	itsClockMode     = CT_TEL_CLKMODE_UNKNOWN;
    itsFramedTimingInputsEnable = false;
    itsClockBandwidth = CT_TEL_CLKBW_UNKNOWN;
    itsClkOutEnable = false;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClkSelState TSPII_ClkSelIf::GetTimingState() 
{
    return itsTimingState;
}

///////////////////////////////////////////////////////////////////////////////
CT_FAC_RxSsm TSPII_ClkSelIf::GetFreerunSsm()
{
    return itsFreerunSsm;
} 

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClkMode TSPII_ClkSelIf::GetMateClockMode()
{
    return itsMateClockMode;
} 
 
///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::SetTimingMode(CT_TEL_ClkSelMode theMode)
{
    itsTimingMode = theMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClkSelMode TSPII_ClkSelIf::GetTimingMode() const
{
    return itsTimingMode;
}
 
///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::SetSelectedRef(CT_TEL_ClkSelRef theRef)
{
    itsSelectedRef = theRef;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClkSelRef TSPII_ClkSelIf::GetSelectedRef() const
{
    return itsSelectedRef;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::SetClockMode(const CT_TEL_ClkMode theClkMode)
{
    itsClockMode = theClkMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClkMode TSPII_ClkSelIf::GetClockMode() const
{
    return itsClockMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::SetFramedTimingInputsEnable(bool theFramedEnable)
{
    itsFramedTimingInputsEnable = theFramedEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_ClkSelIf::GetFramedTimingInputsEnable()
{
    return itsFramedTimingInputsEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::SetClockBandwidth(CT_TEL_ClockBandwidth theBandwidth)
{
    itsClockBandwidth = theBandwidth;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClockBandwidth TSPII_ClkSelIf::GetClockBandwidth()
{
    return itsClockBandwidth;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::SetClkOutEnable(bool theClkOutEnable)
{
    itsClkOutEnable = theClkOutEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_ClkSelIf::GetClkOutEnable()
{
    return itsClkOutEnable;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_ClkSelIf::WriteObjectBinary(FC_Stream & theStream)
{    
    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    theStream << itsTimingState;
    theStream << itsFreerunSsm;
	theStream << itsMateClockMode;

    // Configuration
    theStream << itsTimingMode;
    theStream << itsSelectedRef;
	theStream << itsClockMode;
    theStream << itsFramedTimingInputsEnable;
    theStream << itsClockBandwidth;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_ClkSelIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aTimingState;
    int aTimingMode;
    int aSelectedRef;
    int aFreerunSsm;
	int aMateClockMode;
	int aClockMode;
    int aClockBandwidth;

    // Monitoring
    theStream >> aTimingState;
    itsTimingState = (CT_TEL_ClkSelState) aTimingState;
    theStream >> aFreerunSsm;
    itsFreerunSsm = (CT_FAC_RxSsm) aFreerunSsm;
	theStream >> aMateClockMode;
	itsMateClockMode = (CT_TEL_ClkMode)aMateClockMode;

    // Configuration
    theStream >> aTimingMode;
    itsTimingMode = (CT_TEL_ClkSelMode) aTimingMode;
    theStream >> aSelectedRef;
    itsSelectedRef = (CT_TEL_ClkSelRef) aSelectedRef;
	theStream >> aClockMode;
	itsClockMode = (CT_TEL_ClkMode) aClockMode;
    theStream >> itsFramedTimingInputsEnable;
    theStream >> aClockBandwidth;
    itsClockBandwidth = (CT_TEL_ClockBandwidth) aClockBandwidth;
    
    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_ClkSelIf::WriteObject(ostream & theStream)
{
    int aTimingState;
    int aTimingMode;
    int aSelectedRef;
    int aFreerunSsm;
	int aMateClockMode;
	int aClockMode;
    int aClockBandwidth;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring
    aTimingState = itsTimingState;
    theStream << FC_InsertVar(aTimingState);
    aFreerunSsm = itsFreerunSsm;
    theStream << FC_InsertVar(aFreerunSsm);
	aMateClockMode = itsMateClockMode;
	theStream << FC_InsertVar(aMateClockMode);

    // Configuration
    aTimingMode = itsTimingMode;
    theStream << FC_InsertVar(aTimingMode);
    aSelectedRef = itsSelectedRef;
    theStream << FC_InsertVar(aSelectedRef);
	aClockMode = itsClockMode;
	theStream << FC_InsertVar(aClockMode);
    theStream << FC_InsertVar(itsFramedTimingInputsEnable);
    aClockBandwidth = itsClockBandwidth;
	theStream << FC_InsertVar(aClockBandwidth);
     
    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_ClkSelIf::ReadObject(istream & theStream)
{
    int aTimingState;
    int aTimingMode;
    int aSelectedRef;
    int aFreerunSsm;
	int aMateClockMode;
	int aClockMode;
    int aClockBandwidth;

    // Monitoring
    theStream >> FC_ExtractVar(aTimingState);
    itsTimingState = (CT_TEL_ClkSelState) aTimingState;
    theStream >> FC_ExtractVar(aFreerunSsm);
    itsFreerunSsm = (CT_FAC_RxSsm) aFreerunSsm;
	theStream >> FC_ExtractVar(aMateClockMode);
    itsMateClockMode = (CT_TEL_ClkMode) aMateClockMode;

    // Configuration
    theStream >> FC_ExtractVar(aTimingMode);
    itsTimingMode = (CT_TEL_ClkSelMode) aTimingMode;
    theStream >> FC_ExtractVar(aSelectedRef);
    itsSelectedRef = (CT_TEL_ClkSelRef) aSelectedRef;
	theStream >> FC_ExtractVar(aClockMode);
	itsClockMode = (CT_TEL_ClkMode) aClockMode;
    theStream >> FC_ExtractVar(itsFramedTimingInputsEnable);
    theStream >> FC_ExtractVar(aClockBandwidth);
	itsClockBandwidth = (CT_TEL_ClockBandwidth) aClockBandwidth;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::Display(FC_Stream & theStream)
{ 
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  CLKSEL Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      timingmode            = " << DISPLAY_CLKSEL_MODE(itsTimingMode) << "\n";
    theStream << "      selectedref           = " << DISPLAY_CLKSEL_REF(itsSelectedRef) << "\n";
	theStream << "      clockmode             = " << DISPLAY_CLK_MODE(itsClockMode) << "\n";
    theStream << "      framedtmginputs       = " << DISPLAY_BOOL(itsFramedTimingInputsEnable) << "\n";
    theStream << "      clockbandwidth        = " << DISPLAY_TEL_ClockBandwidth(itsClockBandwidth) << "\n";
    theStream << "      clkout                = " << DISPLAY_BOOL(itsClkOutEnable) << "\n";
    theStream << "    MONITORING\n";
    theStream << "      timingstate           = " << DISPLAY_CLKSEL_STATE(itsTimingState) << "\n";
    theStream << "      freerunssm            = " << display_RXSSM(itsFreerunSsm) << "\n";
    theStream << "      mateclockmode         = " << DISPLAY_CLK_MODE(itsMateClockMode) << endl;
    
    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_ClkSelIf::Set(int argc, char ** argv)
{

    bool printUsage = true;

    if ((argc == 2) && (strcmp(argv[0], "timingmode") == 0))
    {
        for (int i = 0; i < CT_TEL_CLKSEL_MODE_UNKNOWN; i++)
        {
            if (strcmp(argv[1], DISPLAY_CLKSEL_MODE(i)) == 0)
            {
                SetTimingMode((CT_TEL_ClkSelMode)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "selectedref") == 0))             
    {
        for (int i = 0; i < CT_TEL_CLKSEL_REF_UNKNOWN; i++)
        {
            if (strcmp(argv[1], DISPLAY_CLKSEL_REF(i)) == 0)
            {
                SetSelectedRef((CT_TEL_ClkSelRef)i);
                printUsage = false;
                break;
            }
        }
    }
	else if ((argc == 2) && (strcmp(argv[0], "clockmode") == 0))             
    {
        for (int i = 0; i < CT_TEL_CLKMODE_UNKNOWN; i++)
        {
            if (strcmp(argv[1], DISPLAY_CLK_MODE(i)) == 0)
            {
                SetClockMode((CT_TEL_ClkMode)i);
                printUsage = false;
                break;
            }
        }
    }
    else if (argc == 2 && strcmp(argv[0], "framedtmginputs") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetFramedTimingInputsEnable(true);
            printUsage = false;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetFramedTimingInputsEnable(false);
            printUsage = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "clkout") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetClkOutEnable(true);
            printUsage = false;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetClkOutEnable(false);
            printUsage = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    timingmode       <Ref|Internal>\n"; 
        fc_cout << "    selectedref      <Primary|Secondary|Internal>\n";
		fc_cout << "    clockmode        <Master|Slave|Holdover>\n";
        fc_cout << "    framedtmginputs  <on|off>\n";
        fc_cout << "    clkout           <on|off>\n" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_ClkSelIf::Simul(int argc, char ** argv)
{
    bool printUsage = true;

    if ((argc == 2) && (strcmp(argv[0], "timingstate") == 0))
    {
        for (int i = 0; i < CT_TEL_CLKSEL_STATE_UNKNOWN; i++)
        {
            if (strcmp(argv[1], DISPLAY_CLKSEL_STATE(i)) == 0)
            {
                itsTimingState = ((CT_TEL_ClkSelState)i);
                printUsage = false;
                break;
            }
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "freerunssm") == 0))
    {
        for (int i = 0; i < CT_RxSsm_ALL; i++)
        {
            if (strcmp(argv[1], display_RXSSM(i)) == 0)
            {
                itsFreerunSsm = ((CT_FAC_RxSsm)i);
                printUsage = false;
                break;
            }
        }
    }
	else if ((argc == 2) && (strcmp(argv[0], "mateclockmode") == 0))
    {
        for (int i = 0; i < CT_TEL_CLKMODE_UNKNOWN; i++)
        {
            if (strcmp(argv[1], DISPLAY_CLK_MODE(i)) == 0)
            {
                itsMateClockMode = ((CT_TEL_ClkMode)i);
                printUsage = false;
                break;
            }
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    timingstate      <Freerun|Holdover|Acquiring|Locked>\n"
                   "    freerunssm       <PRS|STU|ST2|TNC|ST3E|ST3|SMC|ST4|PNO|DUS>\n"
		           "    MateClockMode    <Master|Slave|Holdover>" << endl;
    }
    
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_ClkSelIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
