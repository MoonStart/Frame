/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Eric Bernier April 23 2002
 DESCRIPTION:Definition of the class TSPII_ControlLoop
 MODIFIED :
--------------------------------------------------------------------------*/

#include "BaseClass/FC_Stream.h"
#include "PII_TickTimer.h"
#include "TsPii/TSPII_ControlLoop.h"
#include <string.h>  // for strcmp
#include <cstdlib>   // for atof

////////////////////////////////////////////////////////////////////////////////
TSPII_ControlLoop::TSPII_ControlLoop(FC_Milliseconds theMaxAllowedPeriod) :
    itsK1(0.0f),
    itsK2(0.0f),
    itsIntegrator(0.0f),
    itsInitialError(0.0f),
    itsInitialOutput(0),
    itsCurveIterator(0),
    itsLoopStarted(true),
    itsLoopActivated(false),
    itsStable(false),
    itsAlarm(false),
    itsStableDelay(500),  // Default value, normally overriden by derived class
    itsAlarmDelay(60000), // Default value, normally overriden by derived class
    itsMaxAllowedPeriod(theMaxAllowedPeriod)
{
    itsPeriodStopwatch.Start();
    itsStableStopwatch.Start();
    itsAlarmStopwatch.Start();
}

////////////////////////////////////////////////////////////////////////////////
TSPII_ControlLoop::~TSPII_ControlLoop()
{
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_ControlLoop::Iterate()
{
    if (itsLoopActivated && itsLoopStarted) DoIterate();
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_ControlLoop::Activate()
{
    if (!itsLoopActivated)
    {
        ResetIntegrator();
        itsStableStopwatch.Start();
        itsAlarmStopwatch.Start();
        itsLoopActivated = true;
    }
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_ControlLoop::Inhibit()
{
    itsStable        = false;
    itsAlarm         = false;
    itsLoopActivated = false;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_ControlLoop::IsStable()
{
    return itsStable;
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_ControlLoop::IsInAlarm()
{
    return itsAlarm;
}

///////////////////////////////////////////////////////////////////////////////
// Debug methods
///////////////////////////////////////////////////////////////////////////////
void TSPII_ControlLoop::SetK(float theK1, float theK2)
{
    itsK1 = theK1;
    itsK2 = theK2;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_ControlLoop::Dump()
{
    char line[80];
    float anError;
    bool  withinThreshold = GetError(&anError);

    fc_cout << "\tLoop started       = " << (itsLoopStarted   ? "YES" : "NO")             << "\n";
    fc_cout << "\tLoop activated     = " << (itsLoopActivated ? "YES" : "NO")             << "\n";
    fc_cout << "\tWithin threshold   = " << (withinThreshold  ? "YES" : "NO")             << "\n";
    fc_cout << "\tStable             = " << (itsStable        ? "YES" : "NO")             << "\n";
    fc_cout << "\tIn alarm           = " << (itsAlarm         ? "YES" : "NO")             << "\n";
    fc_cout << "\tK1                 = " << (sprintf(line, "%8.2f", itsK1), line)         << "\n";
    fc_cout << "\tK2                 = " << (sprintf(line, "%8.2f", itsK2), line)         << "\n";
    fc_cout << "\tError              = " << (sprintf(line, "%8.2f", anError), line)       << "\n";
    fc_cout << "\tIntegrator         = " << (sprintf(line, "%8.2f", itsIntegrator), line) << "\n";
    fc_cout << "\tOutput             = " << GetOutput()                                   << "\n";
    fc_cout << "\tPeriod stopwatch   = " << itsPeriodStopwatch.GetElapsedTime()           << "\n";
    fc_cout << "\tStable stopwatch   = " << itsStableStopwatch.GetElapsedTime()           << "\n";
    fc_cout << "\tUnstable stopwatch = " << itsAlarmStopwatch.GetElapsedTime()            << "\n";
}

////////////////////////////////////////////////////////////////////////////////
bool TSPII_ControlLoop::Menu(int argc, char ** argv)
{
    uint32   i;
    char  line[80];
    float anError;

    if (argc == 1 && strcmp(argv[0], "start") == 0)
    {
        itsLoopStarted = true;
        itsPeriodStopwatch.Start();
        fc_cout << "Loop started." << endl;
    }
    else if (argc == 1 && strcmp(argv[0], "stop") == 0)
    {
        itsLoopStarted = false;
        fc_cout << "Loop stopped." << endl;
    }
    else if (argc == 1 && strcmp(argv[0], "reset") == 0)
    {
        itsCurveIterator  = 0;
        itsInitialError   = (GetError(&anError), anError);
        itsInitialOutput  = GetOutput();
        fc_cout << "Data collection reset." << endl;
    }
    else if (argc == 1 && strcmp(argv[0], "display") == 0)
    {
        fc_cout << "# Time Error Command\n";
        for (i = 0; i < itsCurveIterator; i++)
        {
            sprintf(line, "%2d %6d %8.4f %5d\n", i, itsTimeCurve[i] - itsTimeCurve[0], itsErrorCurve[i], itsOutputCurve[i]);
            fc_cout << line;
        }
        fc_cout << endl;
    }
    else if (argc == 1 && strcmp(argv[0], "analyze") == 0)
    {
        if (itsCurveIterator != TSPII_CL_MAX_NUMBER_OF_POINTS)
        {
            fc_cout << "Analysis procedure:"       << endl;
            fc_cout << "1) stop"                   << endl;
            fc_cout << "2) reset"                  << endl;
            fc_cout << "3) k 0 0"                  << endl;
            fc_cout << "4) integrator VALUE"       << endl;
            fc_cout << "5) start"                  << endl;
            fc_cout << "6) (wait for acquisition)" << endl;
            fc_cout << "7) display"                << endl;
            fc_cout << "8) analyze"                << endl;
        }
        else
        {
            float a1 = 0.0f;
            float a2 = 0.0f;
            float b1 = 0.0f;
            float b2 = 0.0f;
            float c1 = 0.0f;
            float c2 = 0.0f;
            for (i = 1; i < TSPII_CL_MAX_NUMBER_OF_POINTS; i++)
            {
                float dy = itsErrorCurve[i] - itsErrorCurve[i - 1];
                float xt = 0.001f*(itsTimeCurve[i] - itsTimeCurve[i - 1])*(itsOutputCurve[i - 1] - itsInitialOutput);
                float yt = (0.5f*itsErrorCurve[i] + 0.5f*itsErrorCurve[i - 1] - itsInitialError)*(itsTimeCurve[i] - itsTimeCurve[i - 1])*0.001f;
                a1 += dy*dy;
                b1 += dy*xt;
                c1 += dy*yt;
                a2 += xt*dy;
                b2 += xt*xt;
                c2 += xt*yt;
            }
            float det = a1*b2 - a2*b1;
            if (det == 0.0)
            {
                fc_cout << "Singular matrix." << endl;
            }
            float tau  = (c1*b2 - c2*b1)/det;
            float gain = (a1*c2 - a2*c1)/det;
            float k1   = 0.25f/(gain*tau);
            fc_cout << "Collected system:" << endl;
            fc_cout << "\t" << a1 << "\t" << b1 << "\t" << c1 << endl;
            fc_cout << "\t" << a2 << "\t" << b2 << "\t" << c2 << endl;
            fc_cout << "Initial error           = " << itsInitialError  << endl;
            fc_cout << "Initial output          = " << itsInitialOutput << endl;
            fc_cout << "Estimated gain          = " << gain             << endl;
            fc_cout << "Estimated time constant = " << tau              << endl;
            fc_cout << "Fastest K1              = " << k1               << endl;
        }
    }
    else if (argc == 1 && strcmp(argv[0], "dump") == 0)
    {
        Dump();
    }
    else if (argc == 3 && strcmp(argv[0], "k") == 0)
    {
        itsK1 = (float)atof(argv[1]);
        itsK2 = (float)atof(argv[2]);
        fc_cout << "K1/K2 set" << endl;
    }
    else if (argc == 2 && strcmp(argv[0], "integrator") == 0)
    {
        itsIntegrator = (float)atof(argv[1]);
    }
    else
    {
        fc_cout << "    <start|stop>"     << endl;
        fc_cout << "    <reset|display>"  << endl;
        fc_cout << "    analyze"          << endl;
        fc_cout << "    dump"             << endl;
        fc_cout << "    k K1 K2"          << endl;
        fc_cout << "    integrator VALUE" << endl;
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Private methods
///////////////////////////////////////////////////////////////////////////////
void TSPII_ControlLoop::DoIterate()
{
    // Get integration period
    FC_Milliseconds elapsed = itsPeriodStopwatch.GetElapsedTime();
    itsPeriodStopwatch.Start();
    if (elapsed > itsMaxAllowedPeriod) elapsed = itsMaxAllowedPeriod;
    float elapsedF = elapsed*0.001f;

    // Get output limits
    int32 aMinimum;
    int32 aMaximum;
    GetOutputLimits(&aMinimum, &aMaximum);
    float aMinimumF = (float)aMinimum;
    float aMaximumF = (float)aMaximum;

    // Integrate the error signal
    float anError;
    bool  withinThreshold = GetError(&anError);
    itsIntegrator += itsK1*elapsedF*anError;
    if (itsIntegrator < aMinimumF) itsIntegrator = aMinimumF;
    if (itsIntegrator > aMaximumF) itsIntegrator = aMaximumF;

    // Evaluate the output command
    float aCommand = itsIntegrator + itsK2*anError;
    if (aCommand < aMinimumF) aCommand = aMinimumF;
    if (aCommand > aMaximumF) aCommand = aMaximumF;
    int32 anOutput = (int32)float(aCommand + 0.5);
    SetOutput(anOutput);

    // Log curve for debug purposes.
    if (itsCurveIterator < TSPII_CL_MAX_NUMBER_OF_POINTS)
    {
        itsTimeCurve[itsCurveIterator]   = PII_TickTimer::readTimer();
        itsErrorCurve[itsCurveIterator]  = anError;
        itsOutputCurve[itsCurveIterator] = anOutput;
        itsCurveIterator++;
    }

    // Evaluate stability
    if (!withinThreshold)
        itsStableStopwatch.Start();

    //since it is not possible for the elapsed time to be -ve, if we
    //get the a -ve elapsed time this must mean that the time counter
    //is wrapped.
    //By resetting the stable/alarm stop watch we will clear this condition,
    //we will be unstable for (itsStableDelay) but we will become stable
    //before the alarm could be raised ==> we should never see the alarm
    //if we get a -ve elapsed time...
    if(itsStableStopwatch.GetElapsedTime() < 0)
    {
        itsStableStopwatch.Start();
        itsAlarmStopwatch.Start();
    }

    //debounce the stablity, the loop is not stable till we the system is
    //with in threshold for more atleast (itsStableDelay)...
    FC_Milliseconds itsStableElapsedTime = itsStableStopwatch.GetElapsedTime();
    if(itsStableElapsedTime >= itsStableDelay)
        itsStable = TRUE;
    else
        itsStable = FALSE;

    //by restarting the alarm watch here we are making sure that the alarm
    //will not be raised, since (itsStableDelay) will always be less than
    //(itsAlarmDelay)
    if(itsStable == TRUE)
        itsAlarmStopwatch.Start();

    //debounce the alarm here, so if the system has been decleared as unstable
    //then it must be unstable for at least (istAlarmDelay) for us to raise an
    //alarm.
    FC_Milliseconds itsAlarmElapsedTime = itsAlarmStopwatch.GetElapsedTime();
    if(itsAlarmElapsedTime >= itsAlarmDelay)
        itsAlarm = TRUE;
    else
        itsAlarm = FALSE;
}

////////////////////////////////////////////////////////////////////////////////
void TSPII_ControlLoop::ResetIntegrator()
{
    // Get output limits
    int32 aMinimum;
    int32 aMaximum;
    GetOutputLimits(&aMinimum, &aMaximum);
    float aMinimumF = (float)aMinimum;
    float aMaximumF = (float)aMaximum;

    // Set integrator to avoid discontinuities
    float anError;
    GetError(&anError);
    int32 anOutput = GetOutput();
    itsIntegrator  = anOutput - itsK2*anError;
    if (itsIntegrator < aMinimumF) itsIntegrator = aMinimumF;
    if (itsIntegrator > aMaximumF) itsIntegrator = aMaximumF;
}
