#ifndef __TSPII_CTRLLOOP__H__
#define __TSPII_CTRLLOOP__H__
/*-----------------------------------------------------------------------------
 *Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 22, 2002 - Eric Bernier
DESCRIPTION:    
-----------------------------------------------------------------------------*/
#include <gdef.h>
#include "ExecutionSupport/FC_BaseStopwatch.h"

const int TSPII_CL_MAX_NUMBER_OF_POINTS = 200;

class TSPII_ControlLoop
{
    friend class TSPII_Trn10GTestMenu;
public:

    /* Constructor */ TSPII_ControlLoop(FC_Milliseconds theMaxAllowedPeriod);
    virtual           ~TSPII_ControlLoop();

    // Method used by control loop manager and/or diags.
    virtual void      Shutdown() = 0; // Configure loop dependant safe output then call Inhibit();
    void              Inhibit();
    void              Activate();
    void              Iterate();
    bool              IsStable();
    bool              IsInAlarm();
    void              SetK(float theK1, float theK2);

    // Used for debug - overload to provide debug specific to each loop
    virtual void      Dump();
    virtual bool      Menu(int argc, char ** argv);

protected:
    virtual bool      GetError(float * theError)                              = 0; // returns stability
    virtual void      SetOutput(int32 theOuputValue)                          = 0;
    virtual int32     GetOutput()                                             = 0;
    virtual void      GetOutputLimits(int32 * theMinimum, int32 * theMaximum) = 0;
    void              DoIterate();
    void              ResetIntegrator();

    FC_BaseStopwatch  itsPeriodStopwatch;
    FC_BaseStopwatch  itsStableStopwatch;
    FC_BaseStopwatch  itsAlarmStopwatch;
    uint32            itsCurveIterator;
    FC_Milliseconds   itsTimeCurve[TSPII_CL_MAX_NUMBER_OF_POINTS];
    int32             itsOutputCurve[TSPII_CL_MAX_NUMBER_OF_POINTS];
    float             itsErrorCurve[TSPII_CL_MAX_NUMBER_OF_POINTS];
    int32             itsInitialOutput;
    float             itsInitialError;
    float             itsK1;
    float             itsK2;
    float             itsIntegrator;
    bool              itsLoopActivated;
    bool              itsLoopStarted;
    bool              itsStable;
    bool              itsAlarm;
    FC_Milliseconds   itsStableDelay;
    FC_Milliseconds   itsAlarmDelay;
    FC_Milliseconds   itsMaxAllowedPeriod;
};

#endif  //  __TSPII_CTRLLOOP__H__ 
