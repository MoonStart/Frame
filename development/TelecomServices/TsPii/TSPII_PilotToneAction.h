#ifndef TSPII_PILOT_TONE_ACTION_H
#define TSPII_PILOT_TONE_ACTION_H

/*-----------------------------------------------------------------------------
 *Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:         TSPII 
AUTHOR:         M. Piotte, 2002/12/11
DESCRIPTION:    Pilot tone collection class
-----------------------------------------------------------------------------*/

#include <ss_gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <ExecutionSupport/FC_Action.h>

#define TSPII_MAX_PILOT_TONE_SAMPLE 1024

struct TSPII_PilotToneIQData
{
    int32 i;
    int32 q;
};

enum TSPII_PilotToneStatus
{
    TSPII_PILOT_TONE_FAILURE,
    TSPII_PILOT_TONE_SUCCESS
};

enum TSPII_PilotTonePriority
{
    TSPII_PT_HIGH_PRIORITY,
    TSPII_PT_LOW_PRIORITY,
    TSPII_PT_PRIORITY_COUNT
};

class TSPII_PilotToneAction : public FC_Action
{
    friend class TSPII_PilotToneIf;

public:
    TSPII_PilotToneAction(int theSampleCount = TSPII_MAX_PILOT_TONE_SAMPLE, CT_TEL_Hz theCenterFrequency = 750000);
    virtual ~TSPII_PilotToneAction();

    void                    SetCenterFrequency(CT_TEL_Hz theCenterFrequency);
    void                    SetSampleCount(unsigned int theSampleCount);
    void                    SetPriority(TSPII_PilotTonePriority thePriority);
    void                    SetStatus(TSPII_PilotToneStatus theStatus);
    void                    SetCalibration(float theGain, float theOffset = 0.0f);

    CT_TEL_Hz               GetCenterFrequency() const;
    unsigned int            GetSampleCount() const;
    TSPII_PilotTonePriority GetPriority() const;
    TSPII_PilotToneStatus   GetStatus() const;
    TSPII_PilotToneIQData * GetData();

    float                   Convert(float theValue) const; // returns dBm

protected:
    static float            Median(float theV1, float theV2, float theV3);
    void                    ComputeFFT();

    CT_TEL_Hz               myCenterFrequency;
    unsigned int            mySampleCount;
    TSPII_PilotTonePriority myPriority;
    TSPII_PilotToneStatus   myStatus;
    float                   myGain;
    float                   myOffset;
    TSPII_PilotToneIQData   myTimeData[TSPII_MAX_PILOT_TONE_SAMPLE];
    float                   myFreqData[2*TSPII_MAX_PILOT_TONE_SAMPLE]; // First TSPII_MAX_PILOT_TONE_SAMPLE are ampl^2

private:
    float                   myWindowData[TSPII_MAX_PILOT_TONE_SAMPLE];
    int                     myWindowLength;
};

#endif // TSPII_PILOT_TONE_ACTION_H 
