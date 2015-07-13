/*-----------------------------------------------------------------------------
 *Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:         TSPII
AUTHOR:         M. Piotte, 2002/12/17
DESCRIPTION:    Pilot tone collection class
-----------------------------------------------------------------------------*/

#include <math.h>
#include "TsPii/TSPII_PilotToneIf.h"
#include "BaseClass/FC_TextStream.h"
#include "ExecutionSupport/FC_TimerDispatcher.h"
#include "ExecutionSupport/FC_SelfDestroyTimedProcess.h"
#include "TsPii/TSPII_Common.h"
#include "TsPii/TSPII_PilotToneAction.h"
#include <string.h>


//
// I don't know how this ever works, because math.h also defines M_PI to pi.
// I am only changing things for linux now. aer 08/16/06
//
#ifdef LINUX
#undef M_PI
#endif

const float M_PI = 3.1415926535897932384626433832795f;

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotToneIf::TSPII_PilotToneIf(FC_TimerDispatcher * theDispatcher, bool theDefault, bool theDCPowerSupported) :
    TSPII_BaseIf(theDefault),
    myDispatcher(theDispatcher),
    myGain(1.0f),
    myDCPowerSupported(theDCPowerSupported)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotToneIf::~TSPII_PilotToneIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneIf::RefreshGet()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneIf::RefreshSet()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneIf::Reset()
{
    int i;

    TSPII_BaseIf::Reset();

    // for simulation, let collection be successfull by default
    // to avoid anoying error reports
#ifdef __SIMULATION__
    myFailure    = false;
#else
    myFailure    = true;
#endif

    myNoiseLevel = 0.0;
    for (i = 0; i < TSPII_MAX_PT_SIM; i++)
    {
        myPTAmpl[i] = 0.0f;
        myPTFreq[i] = 0.0f;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PilotToneIf::IsDCPowerSupported() const
{
    return myDCPowerSupported;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneIf::GetPTRawData(TSPII_PilotToneAction * theAction)
{
    int n = theAction->GetSampleCount();

    if (myFailure)
    {
        theAction->SetStatus(TSPII_PILOT_TONE_FAILURE);
    }
    else
    {
        theAction->SetStatus(TSPII_PILOT_TONE_SUCCESS);
        theAction->SetCalibration(myGain);
        float center = (float)theAction->GetCenterFrequency();
        int   fcount = 0;
        int   i;
        int   pt;
        float angle[TSPII_MAX_PT_SIM];
        float freq1[TSPII_MAX_PT_SIM];
        float freq2[TSPII_MAX_PT_SIM];
        float ampl[TSPII_MAX_PT_SIM];
        for (pt = 0; pt < TSPII_MAX_PT_SIM; pt++) if (center - 500.0 < myPTFreq[pt] && myPTFreq[pt] < center + 500)
        {
            float offset  = myPTFreq[pt] == 0.0f ? 0.0f : 11.6020517353366f;
            angle[fcount] = 0.0;
            ampl[fcount]  = myPTAmpl[pt];
            freq1[fcount] = myPTFreq[pt] - center - offset;
            freq2[fcount] = myPTFreq[pt] - center + offset;
            fcount++;
        }
        for (i = 0; i < n; i++)
        {
            float noiseAmpl  = myNoiseLevel*rand()/RAND_MAX;
            float noiseAngle = 2*M_PI*rand()/RAND_MAX;
            float p          = noiseAmpl*cos(noiseAngle);
            float q          = noiseAmpl*sin(noiseAngle);
            for (pt = 0; pt < fcount; pt++)
            {
                float freq = (i / 50) & 1 ? freq1[pt] : freq2[pt]; // toggle every 50 samples
                angle[pt]  += (float)(0.002*M_PI*freq);                     // each sample lasts 0.001 sec
                p          += ampl[pt]*cos(angle[pt]);
                q          += ampl[pt]*sin(angle[pt]);
            }
            theAction->myTimeData[i].i = (int32)floor(p + 0.5);
            theAction->myTimeData[i].q = (int32)floor(q + 0.5);
        }
    }
    if (myDispatcher)
    {
        FC_SelfDestroyTimedProcess * process = new FC_SelfDestroyTimedProcess(*theAction, *myDispatcher, n + 50);
        process->WakeUp();
    }
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_PilotToneIf::WriteObjectBinary(FC_Stream & theStream)
{
    int i;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Availability
    theStream << myDCPowerSupported;

    // Monitoring (simulation only).
    theStream << myFailure;
    theStream << myNoiseLevel;

    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream << myPTFreq[i];
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream << myPTAmpl[i];

    // Configuration (none)

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_PilotToneIf::ReadObjectBinary(FC_Stream & theStream)
{
    int i;

    // Availability
    theStream >> myDCPowerSupported;

    // Monitoring (simulation only).
    theStream >> myFailure;
    theStream >> myNoiseLevel;
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream >> myPTFreq[i];
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream >> myPTAmpl[i];

    // Configuration (none)

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_PilotToneIf::WriteObject(ostream & theStream)
{
    int i;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Availability
    theStream << FC_InsertVar(myDCPowerSupported);

    // Monitoring (simulation only).
    theStream << FC_InsertVar(myFailure);
    theStream << FC_InsertVar(myNoiseLevel);
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream << FC_InsertArrayVar(myPTFreq, i);
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream << FC_InsertArrayVar(myPTAmpl, i);

    // Configuration (none)

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_PilotToneIf::ReadObject(istream & theStream)
{
    int i;

    // Availability
    theStream >> FC_ExtractVar(myDCPowerSupported);

    // Monitoring (simulation only).
    theStream >> FC_ExtractVar(myFailure);
    theStream >> FC_ExtractVar(myNoiseLevel);
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream >> FC_ExtractVar(myPTFreq[i]);
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) theStream >> FC_ExtractVar(myPTAmpl[i]);

    // Configuration (none)

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneIf::Display(FC_Stream & theStream)
{
    int i;

    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  Pilot Tone Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      N/A\n";
    theStream << "    MONITORING (SIMULATION)\n";
    theStream << "      Acquisition failure   = " << TEXT_ON_OFF(myFailure) << "\n";
    theStream << "      Noise level           = " << myNoiseLevel           << "\n";
    theStream << "      DC Power Supported    = " << TEXT_ON_OFF(myDCPowerSupported)   << "\n";
    for (i = 0; i < TSPII_MAX_PT_SIM; i++) if (myPTAmpl[i] != 0.0)
    theStream << "      PT #" << (i + 1) <<
                            "                 = " << myPTAmpl[i] << " @ " << myPTFreq[i] << " Hz\n";
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PilotToneIf::Set(int argc, char ** argv)
{
    return TSPII_BaseIf::Set(argc, argv);;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_PilotToneIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if (argc == 2 && strcmp(argv[0], "failure") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myFailure = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myFailure = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "gain") == 0)
    {
        myGain = (float)atof(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "noise") == 0)
    {
        myNoiseLevel = (float)atof(argv[1]);
    }
    else if (argc == 3 && strcmp(argv[0], "freq") == 0)
    {
        unsigned int id = strtoul(argv[1], NULL, 0) - 1;
        if (id < TSPII_MAX_PT_SIM)
        {
            myPTFreq[id] = (float)strtoul(argv[2], NULL, 0);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 3 && strcmp(argv[0], "ampl") == 0)
    {
        unsigned int id = strtoul(argv[1], NULL, 0) - 1;
        if (id < TSPII_MAX_PT_SIM)
        {
            myPTAmpl[id] = (float)strtoul(argv[2], NULL, 0);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "dcpwravail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myDCPowerSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myDCPowerSupported = false;
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
        fc_cout << "    failure         <on|off>\n"
                   "    dcpwravail      <on|off>\n"
                   "    gain            <value>\n"
                   "    noise           <amplitude>\n"
                   "    freq            <id 1-6> <Hz>\n"
                   "    ampl            <id 1-6> <amplitude>" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
