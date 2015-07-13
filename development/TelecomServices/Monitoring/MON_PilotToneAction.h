// //Copyright(c) Tellabs Transport Group. All rights reserved.


#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_PILOTTONEACTION_3C4833B2003A_INCLUDED
#define _INC_MON_PILOTTONEACTION_3C4833B2003A_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <TsPii/TSPII_PilotToneAction.h>
#include <TsPii/TSPII_Region.h>
#include "MON_PilotToneProcessorRequest.h"
#include <Monitoring/MON_OchStatus.h>

//##ModelId=3C4833B2003A
class MON_PilotToneAction: public TSPII_PilotToneAction
{
public:
    enum State
    {
        FFT_COMPLETED,
        FAILED,
        INIT,
        READY,
        COLLECTION_IN_PROGRESS,
        COLLECTION_COMPLETED,
        FFT_IN_PROGRESS
    };

	//Constructor.
	//##ModelId=3C7170DF0185
    MON_PilotToneAction();

	//Override of Run method from FC_Action.
	//##ModelId=3C7170DF0199
    void Run(FC_Object* theObject = NULL);
	//##ModelId=3C7170DF01AD
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);


	//Virtual destructor.
	//##ModelId=3C7170DF01D5
    virtual ~MON_PilotToneAction();

    void Collect(MON_PilotToneProcessorRequest& theRequest, 
                 MON_Region* theOchDestinationStatusRegion, 
                 uint32 theOchDestinationIndex,
                 TSPII_PilotToneRegion* theTspiiRegion,
                 FC_Action* theCallbackAction);

    void Process();
    void ComputeFFT();

    State GetState() const { return myState; }
    bool IsInProgress() const;
    void SaveResults();
    void ForceFailure() { myState = FAILED; }
    void Menu(int argc, char ** argv);
    int GetObjectCount();

private:
    void AnalyseSignature();
    void DumpSignatureTrace();
    void ClearDebugData(int i);
    void DumpConstants();
    void DumpFreqRawData();
    void SaveCollectedData();

    void ComputeIdPower(MON_RelativeTraceId theRelativeId); 
    void GetIdPower(MON_RelativeTraceId theRelativeId, 
                    float& theAmplitude,
                    double& thePeakAutocorr, 
                    double& theNotchAutocorr);
    MON_RelativeTraceId myComputedRelativeId;
    float myComputedAmplitude;
    double myComputedPeakAutocorr;
    double myComputedNotchAutocorr;

    State myState;
    MON_OchStatus myOchStatus;
    MON_OchStatusRegion* myOchDestinationStatusRegion;
    uint32 myOchDestinationIndex;
    FC_Action* myCallbackAction;
    CT_Wavelength myChannelId;
    TSPII_PilotToneRegion* myCurrentPilotToneRegion;

    //debug
    bool                    saveCollectedData;
    bool                    saveDebugData;
    int                     myDebugCount;

    int                     myObjCount;     //Object Counter
    static int              PilotToneActionCounter;

    typedef struct
    {
        int   pos;
        float amp;
    } SD; //sample data
    
    typedef struct
    {
        int myLowerBandBegins;
        MON_RelativeTraceId myId;
        SD mySD[4];
        float median;
        float  myComputedAmp;
        double myComputedPeakAutocorrect;
        double myComputedNotchAutocorrect;
    } DD; //debug Data
    
    typedef struct
    {
        DD myDD[4];
        MON_OchPower myPwr[3];
    } dbg; //debug info

    dbg myDbg;


    typedef struct
    {
        TSPII_PilotToneIQData   myTD[TSPII_MAX_PILOT_TONE_SAMPLE]; //debug time data
        float                   myFD[2*TSPII_MAX_PILOT_TONE_SAMPLE]; //debug frequency data
    } freqRawData;

    freqRawData myFreqRawData;
};

#endif /* _INC_MON_PILOTTONEACTION_3C4833B2003A_INCLUDED */
