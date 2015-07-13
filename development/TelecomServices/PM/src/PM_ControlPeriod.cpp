/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Control period class.
--------------------------------------------------------------------------*/

#include <cstdio>

#include <CommonTypes/CT_PM_Definition.h>
#include <PM_BbValue.h>
#include <PM_GenericApplication.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbCfg.h>
#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_Processor.h>

bool gPM_SetTestValue = false;

static char PM_15MinutePeriodString[] = "15 MINUTES";
static char PM_1DayPeriodString[]     = "1 DAY";

//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3C1FAF860338
PM_ControlPeriod::PM_ControlPeriod (PM_GenericApplication     &theGenericApplication,
                                    CT_PM_Period              thePeriod,
                                    PM_AccumulationPeriod&    theAccPeriod,
                                    uint16                    theIndex,
                                    char*                     theProcessorTypeString,
                                    time_t                    thePstOffset,
                                    bool                      theUpdatePreviousValue):
    myGenericApplication(theGenericApplication),
    myAccPeriod(theAccPeriod),
    myIndex(theIndex),
    myPeriodStartTimeOffset(thePstOffset),
    myDayLightSavingTimeOffset(0),
    myWarning(false),
    myPeriod(thePeriod),
    myProcessorTypeString(theProcessorTypeString),
    myCurrentPeriod(0),
    myUpdatePreviousValue(theUpdatePreviousValue)
{
    Init();

    switch (myPeriod)
    {
    case CT_PM_PERIOD_15_MINUTES:
        myPeriodString = PM_15MinutePeriodString;
        myPeriodInSecond = CT_PM_NUMBER_OF_SEC_IN_15M;
        break;
    case CT_PM_PERIOD_1_DAY:
        myPeriodString = PM_1DayPeriodString;
        myPeriodInSecond = CT_PM_NUMBER_OF_SEC_IN_1DAY;
        break;
    case CT_PM_PERIOD_UNKNOWN:
    default:
        myPeriodString = NULL;
        myPeriodInSecond = 0;
        FC_THROW_ERROR( FC_InvalidArgumentError, "PM: invalid period type" );
        break;
    }

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3C1F6F6D0103
PM_ControlPeriod::~PM_ControlPeriod()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CE703C8
void PM_ControlPeriod::Init()
{
    myFirstTime = true;

}

bool PM_ControlPeriod::IsSameDate(FC_Time theStartPeriod, FC_Time theEndPeriod)
{
    // Here UTC time should be converted to local time and then compare their date
    // because holding current bin solution is based on customer view!!
    
    return theStartPeriod.IsLocalDateSame(theEndPeriod);
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6D010C
void PM_ControlPeriod::ControlPeriod(long theCurrentTimeChanged, FC_Time theCurrentTime,
                                     time_t thePstOffset,        time_t  theDstOffset)
{
    FC_Time currentPeriod;      // the current "current" period.
    long    accDurationChange;  // the accumulation of period duration change for this iteration.
    bool    aIsPmdayChged = false;

    ////////////////////////////////
    //  UPDATE PERIOD INFORMATION.//
    ////////////////////////////////

    // Deduce the current period using the current time and the offset.
    // It takes care of Day Light Saving time and Time zone.
    currentPeriod = PM_GetAccumulationPeriod(myPeriod, theCurrentTime, thePstOffset);

    // Check if the calculated control period start time glitched pack to 12/31/1999.
    // The actual comparison value is 1/7/2000, 05:00 UTC, one week after the
    // typical observed failure time.
    if( currentPeriod.GetUTCTime() < 0x387572d0 )
    {
        // The current time glitched back to 12/31/1999. Just increment the time glitch
        // counter and return without further processing.
        myGenericApplication.GetPmMainApplication().IncTimeGlitchCount();
        return;
    }

    // If first time to execute, make sure period start time is up to date.
    if (myFirstTime)
    {
        // Set the period start time for this period in the region.
        (*GetCurrentValueRegion())[myIndex].SetStartTime(currentPeriod);
        // Initialize current period start time.
        myCurrentPeriod = currentPeriod;
        // Initialize the period start time offset.
        myPeriodStartTimeOffset = thePstOffset;
        // Initialize the day light saving time offset.
        myDayLightSavingTimeOffset = theDstOffset;
        // Reset first time flag.
        myFirstTime = false;
    }

    ////////////////////////////////////////////////////////////
    // VERIFY ALL POTENTIAL SOURCES OF PERIOD DURATION CHANGE.//
    ////////////////////////////////////////////////////////////

    // Keep the accumulation of all time changes for this iteration.
    accDurationChange = theCurrentTimeChanged;

    // Verify if the period start time offset has changed.
    if (myPeriodStartTimeOffset != thePstOffset)
    {
        // Save the new current period start time.
        // It is not considered a period change, but it will change
        // the duration of the accumulation period.
        myCurrentPeriod = currentPeriod;
        // Adjust accumulated duration change.
        accDurationChange += (long)(thePstOffset - myPeriodStartTimeOffset);
        // Set myPeriodStartTimeOffset with the new one.
        myPeriodStartTimeOffset = thePstOffset;

        aIsPmdayChged = true;
    }

    // Verify if the daylight saving time has changed.
    if (myDayLightSavingTimeOffset != theDstOffset)
    {
        // Save the new current period start time.
        // It is not considered a period change, but it will change
        // the duration of the accumulation period.
        myCurrentPeriod = currentPeriod;
        // Adjust accumulated duration change.
        accDurationChange += (long)(theDstOffset - myDayLightSavingTimeOffset);
        // Set myDayLightSavingTimeOffset with the new one.
        myDayLightSavingTimeOffset = theDstOffset;
    }


    ////////////////////////////////////////////////////////////////////////////////////////
    //  CONTROL PERIOD ACCORDING TO CURRENT PERIOD AND ACCUMULATED PERIOD DURATION CHANGE.//
    ////////////////////////////////////////////////////////////////////////////////////////

    // NOTE:
    // If a time of day changed positively (tod set forward) occurs 10 seconds or less before
    // the end of the current period, this current period is valid since, from this period point
    // of view, time of day change is 10 seconds or less even if the time of day change is more
    // than 10 seconds.

    // Also, in the same idea, if a time of day changed occurs 10 seconds or less before
    // the Beginning of the next current period, this next current period is valid since,
    // for this period point of view, time of day change is 10 seconds or less even
    // if the whole change is more than 10 seconds.


    // Check if new accumulation period start time correspond to a
    // different accumulation period.
    if (currentPeriod != myCurrentPeriod)
    {
        // IN DIFFERENT PERIOD OF ACCUMULATION.
        // MR216722, PMDAY issues
        // check if date of start-time in 1-day curr-bin is same as currentPeriod
        // which actually can be treated as end-time.
        // 
        // Note: 
        // Here UTC time should be converted to local time and then compare their date
        // because holding current bin solution is based on customer view!!
        //
        // system time change, DST change, timezone change and PMDAY change can cause
        // period end, but only PMDAY will cause same date for two different bin
        if(aIsPmdayChged == true && myPeriod == CT_PM_PERIOD_1_DAY && IsSameDate((*GetCurrentValueRegion())[myIndex].GetStartTime(), currentPeriod ))
        {
            return;
        }

        // Now, we have to verify the validity of the previous and the new current period.
        // To be valid, the maximum time of day changed accepted is PM_MAX_TIME_CHANGE_SEC
        // for one period. It means that accDurationChange cannot be more than PM_MAX_TIME_CHANGE_SEC,
        // But it could cross periods, so it is shared by the previous and the new current period.

        // VALIDITY VERIFICATION OF THE PREVIOUS PERIOD: Is the duration of the
        // previous period equal to myPeriodInSecond +- PM_MAX_TIME_CHANGE_SEC?
        if ( abs((long) (myPeriodInSecond - ((theCurrentTime.GetUTCTime() - accDurationChange) -
              myCurrentPeriod.GetUTCTime()))) <= PM_MAX_TIME_CHANGE_SEC )
        {
            // The period is VALID for this port.

            // Call UpdatePeriod method in the Period Changed mode in order to reset
            // the internal adjust registers.
            myAccPeriod.UpdateEndPeriod();

            if( myUpdatePreviousValue )
            {
                // Set the current value region to be updated if any TCAs were set during
                // the just completed control period.

                // Maximum TCA.
                if( (*GetCurrentValueRegion())[myIndex].GetMaxTca()->GetAnyTcaDeclared() )
                {
                    // Trigger the updating of the current value region.
                    (*GetCurrentValueRegion()).IncModificationCounter();
                }

                // Minimum TCA.
                if ((*GetCurrentValueRegion())[myIndex].GetMinTca())
                {
                    if( (*GetCurrentValueRegion())[myIndex].GetMinTca()->GetAnyTcaDeclared() )
                    {
                        // Trigger the updating of the current value region.
                        (*GetCurrentValueRegion()).IncModificationCounter();
                    }
                }
            }
        }
        else
        {
            // The period is INVALID.
            // Set the IDF of all parameters in that previous period.
            (*GetCurrentValueRegion())[myIndex].GetIdf()->ForcedSetAllIdf(true);
            // It is not nescessary to update the period since it is invalid.
        }

        // Check if it is a newer accumulation period in time.
        if (currentPeriod > myCurrentPeriod)
        {
            // Copy the content of current to previous accumulation period.
            SwitchOnPeriod(currentPeriod);
        }
        // else: Do not copy the content when time has been set backward.


        // VALIDITY VERIFICATION OF THE NEW CURRENT PERIOD: Is the current
        // accumulation duration greather than the maximum allowed (PM_MAX_TIME_CHANGE_SEC)?
        if ( (theCurrentTime.GetUTCTime() - currentPeriod.GetUTCTime()) > PM_MAX_TIME_CHANGE_SEC )
        {
            // The period is INVALID since it will not be completed.
            // Start a new current period with IDF set to invalid.
            StartNewCurrentPeriod(currentPeriod, true);
        }
        else
        {
            // The period is VALID up to now and can be completed.
            // Start a new current period with IDF set to valid.
            StartNewCurrentPeriod(currentPeriod);
        }

        // Save the new current period start time.
        myCurrentPeriod = currentPeriod;
    }
    else
    {
        // IN THE SAME PERIOD OF ACCUMULATION.

        // Check if the time has been changed for more than the maximum allowed
        // (PM_MAX_TIME_CHANGE_SEC) for THIS period only.
        if ( abs((int)accDurationChange) > PM_MAX_TIME_CHANGE_SEC )
        {
            // The period is INVALID since time changed more than the maximum allowed.
            // Set the IDF of all parameters in that period for all ports.
            (*GetCurrentValueRegion())[myIndex].GetIdf()->ForcedSetAllIdf(true);
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6D0134
void PM_ControlPeriod::SwitchOnPeriod(FC_Time theCurrentPeriod)
{
    if (myWarning)
    {
        fc_cout << "\nPM " << myProcessorTypeString << ": Transfer Switch occurs , index " <<
            myIndex << " for " << myPeriodString << " period\n" << endl;
    }

    // Set the period end time of the current data with current time.
    (*GetCurrentValueRegion())[myIndex].SetEndTime(theCurrentPeriod);

    // Check for need to set test value.
    if( gPM_SetTestValue )
    {
        (*GetCurrentValueRegion())[myIndex].SetTestValue();
    }

    // Copy current data to previous data.
    (*GetPreviousValueRegion())[myIndex] = (*GetCurrentValueRegion())[myIndex];

    // Check to see if the previous value region needs to be updated.
    if(myUpdatePreviousValue)
    {
        // Increment modification counter for previous value region and
        // trigger the start of the Update Notify delay.
        (*GetPreviousValueRegion()).IncModificationCounter();
        myGenericApplication.GetPmProcessor().InitPreviousValueUpdateDelay();
    }
    else
    {
        // Update the previous value region start time in the containing subapplication.
         myGenericApplication.SetControlPeriodTimeStamp( myPeriod, (*GetPreviousValueRegion())[myIndex].GetStartTime() );

         // Set ready status of previous value region in file storage subapp.
         myGenericApplication.SetPreviousRegionReady( myPeriod, true );
    }
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6D013E
void PM_ControlPeriod::StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag)
{
    // Reset all registers (value and TCA) of the new current period for a new accumulation:

    // Value.
    if ((*GetConfigRegion())[myIndex].GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL))
        // If accumulation is not enabled then reset to default values.
        (*GetCurrentValueRegion())[myIndex].ResetAll();
    else
        // If accumulation is enabled then reset with previous values.
        (*GetCurrentValueRegion())[myIndex].ResetAll((*GetPreviousValueRegion())[myIndex]);

    // Maximum TCA.
    (*GetCurrentValueRegion())[myIndex].GetMaxTca()->ResetAllTca();

    // Minimum TCA.
    if ((*GetCurrentValueRegion())[myIndex].GetMinTca())
    {
        (*GetCurrentValueRegion())[myIndex].GetMinTca()->ResetAllTca();
    }

    // Adjust the IDF of all parameters for the current accumulation period.
    myAccPeriod.AdjustCurrentIdf();

    // Set the IDF of all parameters in that period,
    // if this period is started as invalid.
    if (theInvalidFlag)
        (*GetCurrentValueRegion())[myIndex].GetIdf()->ForcedSetAllIdf(true);

    // Reset the adjustment register for the new accumulation period.
    myAccPeriod.RegAdjReset();

    // Set the period start time for the new accumulation period.
    (*GetCurrentValueRegion())[myIndex].SetStartTime(newCurrentPeriod);

    // Reset the period end time for the new accumulation period.
    (*GetCurrentValueRegion())[myIndex].SetEndTime(0);

    // Reset the TCA present flag.
    GetCurrentValueRegion()->SetTcaPresent(false);
}


