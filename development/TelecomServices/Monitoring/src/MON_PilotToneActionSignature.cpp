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
#include <OSPortability/mathFPU.h>

///////////////////////////////////////////////////////////////////////////////
// NOTE:    This method was put in a separate file in order to compile
//          with and without floating point unit enabled on CPU
// WARNING: If this file is compiled with FPU enabled on CPU, but
//          linked with other objects that are using S/W FP emulation,
//          this function must not make function calls to other with floating
//          parameters (calling convention is different between S/W and H/W FP).
///////////////////////////////////////////////////////////////////////////////

#define FREQUENCY_TO_SAMPLE_NUMBER(freq)    \
    (((INT32)(((float)(freq)+MON_PT_SIGNAL_BANDWIDTH/2)/MON_PT_SIGNAL_BANDWIDTH * MON_PT_EXACTMODE_NUM_SAMPLE + 0.5)))

#ifdef WIN32
#define max _cpp_max
#endif


void MON_PilotToneAction::ComputeIdPower(MON_RelativeTraceId theRelativeId)
{

    /*************************/
    /* Find lower band offset*/
    /*************************/
    int32 lowerBandBegin = FREQUENCY_TO_SAMPLE_NUMBER(MON_OchPower::GetFrequencyOffset(theRelativeId))- MON_PT_EXACT_MODE_TONE_NUM_SAMPLE/2;

    /***************************/
    /* Perform autocorrelation */
    /***************************/

    /* Find maximum to get center frequency */
    static double mSqr5Table[MON_PT_EXACTMODE_NUM_SAMPLE];
    double maxFind = 0;
    int32 maxFindIndex = -1;
    float sample1,sample2,sample3,sample4,sample5;
    for (int k=MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING; k< MON_PT_EXACT_MODE_TONE_NUM_SAMPLE-MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING; k++)
    {
        sample1 = myFreqData[lowerBandBegin+k-MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING];
        sample2 = myFreqData[lowerBandBegin+k-MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING];
        sample3 = myFreqData[lowerBandBegin+k];
        sample4 = myFreqData[lowerBandBegin+k+MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING];
        sample5 = myFreqData[lowerBandBegin+k+MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING];
        mSqr5Table[k] = 1.0*sample1 * sample2 * sample3 * sample4 * sample5;
        /* look if maximum is found */
        if ( (k>=MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING+MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING/2) &&
            (k< MON_PT_EXACT_MODE_TONE_NUM_SAMPLE - MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING-MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING/2) &&
            ( mSqr5Table[k] >= maxFind) )
        {
            maxFind = mSqr5Table[k];
            maxFindIndex = k;
        }
    }

    /* check if max was found */
    if (maxFindIndex == -1)
    {
        FC_REPORT_ERROR(FC_RuntimeError, "Could not find a maximum during auto-correlation");
        maxFindIndex = MON_PT_TX_FSK_2ND_HARMONIC_SAMPLE_SPACING+MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING/2+1;
    }

    /**************************************************************/
    /* Select median power amoung all three peaks as signal power */
    /**************************************************************/
    float peak1 = myFreqData[lowerBandBegin+maxFindIndex - MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING];
    float peak2 = myFreqData[lowerBandBegin+maxFindIndex];
    float peak3 = myFreqData[lowerBandBegin+maxFindIndex + MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING];

    /* Adjust power measured for consider harmonic power compared to single peak power.*/
    float low  = peak1;
    float high = peak2;
    if (peak1 > peak2)
    {
        low  = peak2;
        high = peak1;
    }
    float median = 0;
    if (peak3 > high )
        median = high;
    else if (peak3 < low  )
        median = low;
    else
        median = peak3;

    //---------------------------------------------------------------------
    //We are using this to return values since we cannot use function calls
    //---------------------------------------------------------------------

    myComputedAmplitude = sqrt(median) / MON_PT_TX_FSK_BASE_HARMONIC_POWER_FACTOR;

    /* also return maxfind for eventual SNR purpose */
    myComputedPeakAutocorr=maxFind;

    /*********************************/
    /* find average power of notches */
    /*********************************/
    double notchLeft = mSqr5Table[maxFindIndex - MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING/2];
    double notchRight= mSqr5Table[maxFindIndex + MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING/2];
    myComputedNotchAutocorr=(notchLeft + notchRight)/2;

    myComputedRelativeId = theRelativeId;

    //save the debug data for dumping
    if(saveDebugData && myDebugCount < 4)
    {
        int myIdx = MON_OchPower::GetFrequencyOffset(theRelativeId);
        int myDebugIdx;

        myDebugCount++;

        if(myIdx == -250) myDebugIdx = 0;
        else if(myIdx == 0) myDebugIdx = 1;
        else if(myIdx == 250) myDebugIdx = 2;
        else if(myIdx == 500) myDebugIdx = 3;

        ClearDebugData(myDebugIdx);
        myDbg.myDD[myDebugIdx].myLowerBandBegins = lowerBandBegin;
        myDbg.myDD[myDebugIdx].myId = theRelativeId;
        myDbg.myDD[myDebugIdx].mySD[0].pos = maxFindIndex;
        myDbg.myDD[myDebugIdx].mySD[0].amp = (float)maxFind;
        myDbg.myDD[myDebugIdx].mySD[1].pos = lowerBandBegin+maxFindIndex - MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING;
        myDbg.myDD[myDebugIdx].mySD[1].amp = peak1;
        myDbg.myDD[myDebugIdx].mySD[2].pos = lowerBandBegin+maxFindIndex;
        myDbg.myDD[myDebugIdx].mySD[2].amp = peak2;
        myDbg.myDD[myDebugIdx].mySD[3].pos = lowerBandBegin+maxFindIndex + MON_PT_TX_FSK_1ST_HARMONIC_SAMPLE_SPACING;
        myDbg.myDD[myDebugIdx].mySD[3].amp = peak3;
        myDbg.myDD[myDebugIdx].median = median;
        myDbg.myDD[myDebugIdx].myComputedAmp = myComputedAmplitude;
        myDbg.myDD[myDebugIdx].myComputedPeakAutocorrect = myComputedPeakAutocorr;
        myDbg.myDD[myDebugIdx].myComputedNotchAutocorrect = myComputedNotchAutocorr;

        if(myDebugCount != 0 && myDebugCount%4 == 0)
            myDebugCount = 0;
    }
}
