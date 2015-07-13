// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <Blackboard/FC_BbRegionId.h>
#include "../MON_AppIf.h"
#include "../MON_PilotToneAction.h"
#include "../MON_OchStatus.h"
#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_PilotToneIf.h>
#include <Monitoring/MON_PilotToneProcessor.h>
#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_OchResult.h>
#include <math.h>
#include "ExecutionSupport/FC_EventLogger.h"

int MON_PilotToneAction::PilotToneActionCounter = 0;

//Constructor.
//##ModelId=3C7170DF0185
MON_PilotToneAction::MON_PilotToneAction():
    myState(READY),
    myOchStatus(0),
    myOchDestinationStatusRegion(NULL),
    myOchDestinationIndex(0),
    myCallbackAction(NULL),
    myChannelId(UNKNOWN_WAVELENGHT),
    myCurrentPilotToneRegion(NULL),
    myComputedAmplitude(0),
    myComputedPeakAutocorr(0),
    myComputedNotchAutocorr(0),
    myComputedRelativeId(MON_ID_UNKNOWN),
    saveCollectedData(false),
    saveDebugData(false),
    myDebugCount(0),
    myObjCount(++PilotToneActionCounter)
{
}

//Override of Run method from FC_Action.
//##ModelId=3C7170DF0199
void MON_PilotToneAction::Run(FC_Object* theObject)
{
    DoRunWithReason(0,NULL, theObject);
}

//##ModelId=3C7170DF01AD
FC_Object* MON_PilotToneAction::DoRunWithReason(unsigned theRunReason,
                                                FC_Object* theInvokerObj,
                                                FC_Object* theParam)
{
    // we expect to be call only once a completion is done
    FC_THROW_ERROR_IF( myState!=COLLECTION_IN_PROGRESS, FC_RuntimeError, "Unexpected call to run");

    // check if collection was successfull
    if (GetStatus()!=TSPII_PILOT_TONE_SUCCESS)
    {
        myState = FAILED;

        //we we have been unsuccessfully in collecting the pilot tone
        FC_EventRecord(EVENT_PT_COLLECT_FAILED, (unsigned long)myChannelId.WavelengthIndex());

        char aErrorString[256];
        FC_THROW_ERROR_IF(myCurrentPilotToneRegion==NULL,
                          FC_RuntimeError,
                          "Invalid TSPII region");

        FC_BbRegionId aRegionId(*myCurrentPilotToneRegion);
        string aKeyName;
        aRegionId.GetFullKeyAsString(aKeyName);
        sprintf(aErrorString, "Pilot tone data collection failed : %s", aKeyName.c_str());
        FC_REPORT_ERROR(FC_RuntimeError, aErrorString);

        SaveResults();
    }
    else
    {
        myState = COLLECTION_COMPLETED;

        //we we have successfully collected the pilot tone
        FC_EventRecord(EVENT_PT_COLLECT_END, (unsigned long)myChannelId.WavelengthIndex());

        Process();
    }

    return NULL;
}


//Virtual destructor.
//##ModelId=3C7170DF01D5
MON_PilotToneAction::~MON_PilotToneAction()
{
}


void MON_PilotToneAction::Collect(MON_PilotToneProcessorRequest& theRequest,
                                  MON_Region* theOchDestinationStatusRegion,
                                  uint32 theOchDestinationIndex,
                                  TSPII_PilotToneRegion* theTspiiRegion,
                                  FC_Action* theCallbackAction)
{
    FC_THROW_ERROR_IF(myState==COLLECTION_IN_PROGRESS, FC_RuntimeError, "Collection already in progress");
    FC_THROW_ERROR_IF(myState==FFT_IN_PROGRESS, FC_RuntimeError, "FFT already in progress");


    // assume other sampling mode is only for DC measures
    CT_TEL_Hz aFrequency = 0;
    if (theRequest.GetSamplingMode() == MON_PT_EXACTMODE_NUM_SAMPLE)
        aFrequency = MON_OchPower::ConvertChannelToCenterFrequency(theRequest.GetChannelId());
    SetCenterFrequency(aFrequency);

    // set other params
    SetSampleCount(theRequest.GetSamplingMode());
    SetPriority(theRequest.GetPriority());

    // check if request not already being processed.
    if (myState!=READY && myState!=FAILED && myState!=FFT_COMPLETED)
        FC_REPORT_ERROR(FC_RuntimeError, "aborting current pilot tone request");

    // store destination region
    MON_OchStatus* aStatus = dynamic_cast<MON_OchStatus*>(&theOchDestinationStatusRegion->ElementAt((bbindex_t)theOchDestinationIndex));
    FC_THROW_ERROR_IF ( aStatus==NULL, FC_InvalidArgumentError, "Expecting an MON_OchStatus type");
    myOchDestinationStatusRegion = reinterpret_cast<MON_OchStatusRegion*>(theOchDestinationStatusRegion);
    myOchDestinationIndex = theOchDestinationIndex;
    myCallbackAction = theCallbackAction;
    myChannelId = theRequest.GetChannelId();

    // reset to ready and begin
    myCurrentPilotToneRegion = theTspiiRegion;
    myState = COLLECTION_IN_PROGRESS;
    myOchStatus.Invalidate();

    //we are about to collect the pilot tone of the channel
    FC_EventRecord(EVENT_PT_COLLECT_START, (unsigned long)myChannelId.WavelengthIndex());

    (*theTspiiRegion)[0].GetPTRawData(this);
}

void MON_PilotToneAction::Process()
{
    // make sure were are ready to process collected data
    FC_THROW_ERROR_IF(myState!=COLLECTION_COMPLETED, FC_RuntimeError, "Cannot process because collection not completed");

    if (GetSampleCount() == MON_PT_EXACTMODE_NUM_SAMPLE)
    {
        // Start FFT processing
        myState = FFT_IN_PROGRESS;
        MON_PilotToneProcessor::GetInstance().ProcessFFT(this);
    }
    else // assume DC power measurement
    {
        // compute average of i time samples
        unsigned int c=0;
        int32 aTotal=0;
        for (c=0; c<GetSampleCount(); c++)
            aTotal += myTimeData[c].i;
        int32 anAverage = aTotal/GetSampleCount();

        // use first ID location for DC power
        MON_OchPower aFirstId (MON_ID_FIRST, (CT_TEL_mBm)(CT_TEL_POWER_FACTOR*Convert((float)anAverage)), TEL_DEFAULT_MINIMUM_SN_RATIO+2 );

        // save all three powers is OCH status
        myOchStatus.SetTraceIdPowers(aFirstId);
        myOchStatus.SetTraceIdPowers(MON_ID_SECOND);
        myOchStatus.SetTraceIdPowers(MON_ID_DEBUG);
        myOchStatus.SetChannelId(myChannelId);
        myOchStatus.Validate();

        // migth need to be relocated (e.g. Compute FFT) if re-entrance becomes an issue
        myState = FFT_COMPLETED;
        SaveResults();
    }

}

void MON_PilotToneAction::ComputeFFT()
{
    //we are about to start the pilot tone FFT calculation
    FC_EventRecord(EVENT_PT_FFT_START, (unsigned long)myChannelId.WavelengthIndex());

    TSPII_PilotToneAction::ComputeFFT();

    //save the collected data for dumping
    if(saveCollectedData)
    {
        SaveCollectedData();
        DumpFreqRawData();
        saveCollectedData = false;
    }

    AnalyseSignature();
    myState = FFT_COMPLETED;

    //we have completed the pilot tone FFT calculation
    FC_EventRecord(EVENT_PT_FFT_END, (unsigned long)myChannelId.WavelengthIndex());
}

#define SNR(peakSignal, peakNoise, notchSignal)  \
    ((peakSignal>0) ?      \
        ((peakNoise+notchSignal>0) ?                       \
            (log10(peakSignal*2/(peakNoise+notchSignal))): \
            (-(float)TRAFFIC_DEFAULT_POWER / CT_TEL_POWER_FACTOR)   ): \
        ((float)TRAFFIC_DEFAULT_POWER / CT_TEL_POWER_FACTOR))

void MON_PilotToneAction::AnalyseSignature()
{
    float measAmp1 = 0.0;
    float measAmp2 = 0.0;
    float measAmp3 = 0.0;
    float measNoise = 0.0;

    double peakAutocorr1=0.0;
    double peakAutocorr2=0.0;
    double peakAutocorr3=0.0;
    double peakAutocorrNoise=0.0;

    double notchAutocorr1=0.0;
    double notchAutocorr2=0.0;
    double notchAutocorr3=0.0;
    double notchAutocorrNoise=0.0;

    // get power for all three possible signal and noise
    ComputeIdPower(MON_ID_FIRST);
    GetIdPower(MON_ID_FIRST,  measAmp1,  peakAutocorr1,    notchAutocorr1);

    ComputeIdPower(MON_ID_SECOND);
    GetIdPower(MON_ID_SECOND, measAmp2,  peakAutocorr2,    notchAutocorr2);

    ComputeIdPower(MON_ID_DEBUG);
    GetIdPower(MON_ID_DEBUG,  measAmp3,  peakAutocorr3,    notchAutocorr3);

    ComputeIdPower(MON_ID_NOISE);
    GetIdPower(MON_ID_NOISE,  measNoise, peakAutocorrNoise,notchAutocorrNoise);

    // compute overall noise by average of peak power in noise area and power of notches around IDs

    float snrP1 = (float)(SNR(peakAutocorr1, peakAutocorrNoise, notchAutocorr1));
    float snrP2 = (float)(SNR(peakAutocorr2, peakAutocorrNoise, notchAutocorr2));
    float snrP3 = (float)(SNR(peakAutocorr3, peakAutocorrNoise, notchAutocorr3));

    // convert to mBm
    MON_OchPower aFirstId (MON_ID_FIRST, (CT_TEL_mBm)(CT_TEL_POWER_FACTOR*Convert(measAmp1)), (CT_TEL_mBm)(CT_TEL_POWER_FACTOR*snrP1) );
    MON_OchPower aSecondId(MON_ID_SECOND, (CT_TEL_mBm)(CT_TEL_POWER_FACTOR*Convert(measAmp2)), (CT_TEL_mBm)(CT_TEL_POWER_FACTOR*snrP2));
    MON_OchPower aDebugId (MON_ID_DEBUG, (CT_TEL_mBm)(CT_TEL_POWER_FACTOR*Convert(measAmp3)), (CT_TEL_mBm)(CT_TEL_POWER_FACTOR*snrP3));

    // save all three powers is OCH status
    myOchStatus.SetTraceIdPowers(aFirstId);
    myOchStatus.SetTraceIdPowers(aSecondId);
    myOchStatus.SetTraceIdPowers(aDebugId);
    myOchStatus.SetChannelId(myChannelId);
    myOchStatus.Validate();

    if(saveDebugData)
    {
        myDbg.myPwr[0] = aFirstId;
        myDbg.myPwr[1] = aSecondId;
        myDbg.myPwr[2] = aDebugId;

        saveDebugData = false;
        DumpSignatureTrace();
    }

}

void MON_PilotToneAction::GetIdPower(MON_RelativeTraceId theRelativeId,
                                     float& theAmplitude,
                                     double& thePeakAutocorr,
                                     double& theNotchAutocorr)
{
    FC_THROW_ERROR_IF(myComputedRelativeId != theRelativeId, FC_RuntimeError, "Asking for result of wrong ID");
    theAmplitude     = myComputedAmplitude;
    thePeakAutocorr  = myComputedPeakAutocorr;
    theNotchAutocorr = myComputedNotchAutocorr;
}

void MON_PilotToneAction::SaveResults()
{
    bool hasChanged=false;
    MON_OchStatus& aDestinationStatus = (*myOchDestinationStatusRegion)[(bbindex_t)myOchDestinationIndex];

    // check if an expected event occured
    if (myState != FFT_COMPLETED && myState != FAILED)
    {
        FC_REPORT_ERROR(FC_RuntimeError, "Unexpected state for saving FFT results");

        // store default values
        myOchStatus = MON_OchStatus(0);
        myOchStatus.Invalidate();
    }

    //DO NOT SAVE RESULT IF COLLECTION FAILED
    if(myState != FAILED)
    {
        // Notify only if power are different
        if (!(aDestinationStatus == myOchStatus))
        {
            hasChanged = true;
        }

        // Update the status object. NOTE: this is always done to have latest timer value
        aDestinationStatus = myOchStatus;
    }

    // update error code if object is a MON_OchResult
    MON_OchResult* aResult = dynamic_cast<MON_OchResult*>(&(*myOchDestinationStatusRegion)[(bbindex_t)myOchDestinationIndex]);
    if (aResult)
    {
        aResult->SetErrorCode(GetState());
        // force change since on-demand
        hasChanged = true;
    }

    // flush any remainer about previous collection
    myCurrentPilotToneRegion = NULL;

    // notify region of modif
    if (hasChanged)
    {
        myOchDestinationStatusRegion->IncModificationCounter();
    }

    myOchDestinationStatusRegion->UpdateNotify();

    // invoke callback if provided
    if (myCallbackAction)
        myCallbackAction->RunWithReason(0, NULL, this);
}

bool MON_PilotToneAction::IsInProgress() const
{
    return (myState==COLLECTION_IN_PROGRESS ||
            myState==FFT_IN_PROGRESS ||
            myState==COLLECTION_COMPLETED);
}

///////////////////////////////////////////////////////////////////////////////
int MON_PilotToneAction::GetObjectCount()
{
    return(myObjCount);
}

///////////////////////////////////////////////////////////////////////////////
void MON_PilotToneAction::DumpConstants()
{
    fc_cout << endl << endl << "\rObject: " << myObjCount << endl;
    fc_cout << "\r\tWavelengthIndex(0-based)                  = " << (int)(myChannelId.WavelengthIndex()) << endl;
    fc_cout << "\r\tCenterFrequency                           = " << GetCenterFrequency() << " Hz" << endl;
    fc_cout << "\r\tFrequencyOffset: "<< DISPLAY_REL_TRACE_ID(MON_ID_FIRST)<< "                    = " << MON_OchPower::GetFrequencyOffset(MON_ID_FIRST) << endl;
    fc_cout << "\r\tFrequencyOffset: "<< DISPLAY_REL_TRACE_ID(MON_ID_SECOND)<< "                   = " << MON_OchPower::GetFrequencyOffset(MON_ID_SECOND) << endl;
    fc_cout << "\r\tFrequencyOffset: "<< DISPLAY_REL_TRACE_ID(MON_ID_DEBUG)<< "                    = " << MON_OchPower::GetFrequencyOffset(MON_ID_DEBUG) << endl;
    fc_cout << "\r\tFrequencyOffset: "<< DISPLAY_REL_TRACE_ID(MON_ID_NOISE)<< "                    = " << MON_OchPower::GetFrequencyOffset(MON_ID_NOISE) << endl;
    fc_cout << "\r\tMON_NUMBER_OF_ID_PER_LAMBDA               = " << (int)MON_NUMBER_OF_ID_PER_LAMBDA << endl;
    fc_cout << "\r\tMON_PT_EXACTMODE_NUM_SAMPLE               = " << MON_PT_EXACTMODE_NUM_SAMPLE << endl;
    fc_cout << "\r\tMON_PT_FASTMODE_NUM_SAMPLE                = " << MON_PT_FASTMODE_NUM_SAMPLE << endl;
    fc_cout << "\r\tMON_PT_BAND_LOWER_FREQ                    = " << MON_PT_BAND_LOWER_FREQ << endl;
    fc_cout << "\r\tMON_PT_SIGNAL_BANDWIDTH                   = " << MON_PT_SIGNAL_BANDWIDTH << endl;
    fc_cout << "\r\tMON_PT_TONE_BANDWIDTH                     = " << MON_PT_TONE_BANDWIDTH << endl;
    fc_cout << "\r\tMON_PT_EXACT_MODE_TONE_NUM_SAMPLE         = " << MON_PT_EXACT_MODE_TONE_NUM_SAMPLE << endl;
    fc_cout << "\r\tMON_PT_TX_FSK_RATE                        = " << MON_PT_TX_FSK_RATE << endl;
    fc_cout << "\r\tMON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING = " << MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING << endl;
    fc_cout << "\r\tMON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING = " << MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING << endl;
    fc_cout << "\r\tMON_PT_TX_FSK_BASE_HARMONIC_POWER_FACTOR  = " << MON_PT_TX_FSK_BASE_HARMONIC_POWER_FACTOR << endl;
    fc_cout << "\r\tsaveDebugData                             = " << DISPLAY_BOOL(saveDebugData) << endl;
    fc_cout << "\r\tsaveCollectedData                         = " << DISPLAY_BOOL(saveCollectedData) << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////
void MON_PilotToneAction::ClearDebugData(int i)
{
    myDbg.myDD[i].myLowerBandBegins = 0;
    myDbg.myDD[i].myId = MON_ID_UNKNOWN;
    myDbg.myDD[i].mySD[0].pos = 0;
    myDbg.myDD[i].mySD[0].amp = 0;
    myDbg.myDD[i].mySD[1].pos = 0;
    myDbg.myDD[i].mySD[1].amp = 0;
    myDbg.myDD[i].mySD[2].pos = 0;
    myDbg.myDD[i].mySD[2].amp = 0;
    myDbg.myDD[i].mySD[3].pos = 0;
    myDbg.myDD[i].mySD[3].amp = 0;
    myDbg.myDD[i].median = 0;
    myDbg.myDD[i].myComputedAmp = 0;
    myDbg.myDD[i].myComputedPeakAutocorrect = 0;
    myDbg.myDD[i].myComputedNotchAutocorrect = 0;
}

///////////////////////////////////////////////////////////////////////////////
void MON_PilotToneAction::DumpSignatureTrace()
{
    fc_cout << endl << endl;
    for(int i = 0; i < 4; i++)
    {
        fc_cout << "\r" << DISPLAY_REL_TRACE_ID(myDbg.myDD[i].myId) << "..." << endl;
        fc_cout << "\r\tmyLowerBandBegins       = " << myDbg.myDD[i].myLowerBandBegins << endl;
        fc_cout << "\r\tMax:   ["<<myDbg.myDD[i].mySD[0].pos<<"] = " << myDbg.myDD[i].mySD[0].amp << endl;
        fc_cout << "\r\tPeak1: ["<<myDbg.myDD[i].mySD[1].pos<<"] = " << myDbg.myDD[i].mySD[1].amp << endl;
        fc_cout << "\r\tPeak2: ["<<myDbg.myDD[i].mySD[2].pos<<"] = " << myDbg.myDD[i].mySD[2].amp << endl;
        fc_cout << "\r\tPeak3: ["<<myDbg.myDD[i].mySD[3].pos<<"] = " << myDbg.myDD[i].mySD[3].amp << endl;
        fc_cout << "\r\tmedian                  = " << myDbg.myDD[i].median << endl;
        fc_cout << "\r\tmyComputedAmplitude     = " << myDbg.myDD[i].myComputedAmp << endl;
        fc_cout << "\r\tmyComputedPeakAutocorr  = " << myDbg.myDD[i].myComputedPeakAutocorrect << endl;
        fc_cout << "\r\tmyComputedNotchAutocorr = " << myDbg.myDD[i].myComputedNotchAutocorrect << endl << endl;
    }

    fc_cout << "\r" << DISPLAY_REL_TRACE_ID(MON_ID_FIRST) << ":  PWR = " << DISPLAY_MBM(myDbg.myPwr[0].GetAmplitude()) << " dBm; SNR = " << DISPLAY_MBM(myDbg.myPwr[0].GetSnr()) << " dB" << endl;
    fc_cout << "\r" << DISPLAY_REL_TRACE_ID(MON_ID_SECOND)<< ": PWR = " << DISPLAY_MBM(myDbg.myPwr[1].GetAmplitude()) << " dBm; SNR = " << DISPLAY_MBM(myDbg.myPwr[1].GetSnr()) << " dB" << endl;
    fc_cout << "\r" << DISPLAY_REL_TRACE_ID(MON_ID_DEBUG) << ":  PWR = " << DISPLAY_MBM(myDbg.myPwr[2].GetAmplitude()) << " dBm; SNR = " << DISPLAY_MBM(myDbg.myPwr[2].GetSnr()) << " dB" << endl;
    fc_cout << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////
void MON_PilotToneAction::SaveCollectedData()
{
    for(int i = 0; i < TSPII_MAX_PILOT_TONE_SAMPLE; i++)
    {
        myFreqRawData.myTD[i].i = myTimeData[i].i;
        myFreqRawData.myTD[i].q = myTimeData[i].q;
    }

    for(int j = 0; j < 2*TSPII_MAX_PILOT_TONE_SAMPLE; j++)
        myFreqRawData.myFD[j] = myFreqData[j];
}

///////////////////////////////////////////////////////////////////////////////
void MON_PilotToneAction::DumpFreqRawData()
{
    char line[80];
    unsigned int myLine;

    fc_cout << "\n\nSample I        Q        Frequency             Amplitude" << endl;
    for(myLine = 0; myLine < mySampleCount; myLine++)
    {
        sprintf(line, "%6d %8d %8d %9.1f %16.1f\0",
                myLine,
                myFreqRawData.myTD[myLine].i,
                myFreqRawData.myTD[myLine].q,
                myCenterFrequency - 500.0f + myLine*1000.0f/mySampleCount,
                sqrt(myFreqRawData.myFD[myLine]));
        fc_cout << line << endl;
    }
    fc_cout << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////
void MON_PilotToneAction::Menu(int argc, char ** argv)
{
    if(argc >= 1)
    {
        //dump
        if(argc == 2 && argv[0][0] == 'd')
        {
            if(argv[1][0] == 'c')
            {
                DumpConstants();
            }
            else if(argv[1][0] == 'd')
            {
                saveDebugData = true;
                fc_cout << "\rPilotTone Debug Data for object: " << myObjCount << endl;
            }
            else if(argv[1][0] == 'f')
            {
                saveCollectedData = true;
                fc_cout << "\rPilotTone Frequency Raw Data for object: " << myObjCount << endl;
            }
        }
    }
    else
    {
        fc_cout << "\r... d(ump) <c(onstants)|d(ebugData)|f(reqRawData)>" << endl;
    }
}
