/*-----------------------------------------------------------------------------
 *Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:         TSPII
AUTHOR:         M. Piotte, 2002/12/11
DESCRIPTION:    Pilot tone collection class
-----------------------------------------------------------------------------*/

#include <math.h>
#include "TsPii/TSPII_PilotToneAction.h"
#include <ErrorService/FC_Error.h>

//const int   MIN_FREQUENCY =  750000; // Hz
//const int   MAX_FREQUENCY = 1500000; // Hz

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotToneAction::TSPII_PilotToneAction(int theSampleCount, CT_TEL_Hz theCenterFrequency) :
    myStatus(TSPII_PILOT_TONE_FAILURE),
    myGain(1.0f),
    myOffset(0.0f),
    myWindowLength(-1)
{
    SetSampleCount(theSampleCount);
    SetCenterFrequency(theCenterFrequency);
    SetPriority(TSPII_PT_LOW_PRIORITY);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotToneAction::~TSPII_PilotToneAction()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneAction::SetCenterFrequency(CT_TEL_Hz theCenterFrequency)
{
    myCenterFrequency = theCenterFrequency;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneAction::SetSampleCount(unsigned int theSampleCount)
{
    FC_THROW_ERROR_IF(theSampleCount > TSPII_MAX_PILOT_TONE_SAMPLE, FC_DomainError, "Invalid number of PT samples");
    mySampleCount = theSampleCount;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneAction::SetPriority(TSPII_PilotTonePriority thePriority)
{
    FC_THROW_ERROR_IF(thePriority < TSPII_PT_HIGH_PRIORITY || TSPII_PT_PRIORITY_COUNT <= thePriority, FC_DomainError, "Invalid PT priority");
    myPriority = thePriority;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneAction::SetStatus(TSPII_PilotToneStatus theStatus)
{
    myStatus = theStatus;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneAction::SetCalibration(float theGain, float theOffset)
{
    myGain   = theGain;
    myOffset = theOffset;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_Hz TSPII_PilotToneAction::GetCenterFrequency() const
{
    return myCenterFrequency;
}

///////////////////////////////////////////////////////////////////////////////
unsigned int TSPII_PilotToneAction::GetSampleCount() const
{
    return mySampleCount;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotTonePriority TSPII_PilotToneAction::GetPriority() const
{
    return myPriority;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotToneStatus TSPII_PilotToneAction::GetStatus() const
{
    return myStatus;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_PilotToneIQData * TSPII_PilotToneAction::GetData()
{
    return myTimeData;
}

///////////////////////////////////////////////////////////////////////////////
float TSPII_PilotToneAction::Convert(float theValue) const
{
    if (theValue <= 0.0) return 0.01f*TRAFFIC_DEFAULT_POWER;
    return (float)(10.0*log10(theValue*myGain + myOffset));
}

///////////////////////////////////////////////////////////////////////////////
float TSPII_PilotToneAction::Median(float theV1, float theV2, float theV3)
{
    float low  = theV1;
    float high = theV2;
    if (theV1 > theV2) low  = theV2, high = theV1;
    if (theV3 > high ) return high;
    if (theV3 < low  ) return low;
    return theV3;
}
