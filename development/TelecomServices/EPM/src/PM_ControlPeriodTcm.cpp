
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     December 6, 2010, Larry Wolfrum.
 DESCRIPTION:   TCM Control period class.
--------------------------------------------------------------------------*/

#include <cstdio>

#include <CommonTypes/CT_PM_Definition.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_RegionImp.h>
#include <EPM/PM_BbValueTcm.h>
#include <PM/PM_BbCfg.h>
#include <EPM/src/PM_AccPeriodTcm.h>
#include <EPM/src/PM_ControlPeriodTcm.h>
#include <EPM/PM_ProcessorTcm.h>
#include <T6100/T6100_ObjectAllocManager.h>


static char PM_15MinutePeriodString[] = "15 MINUTES";
static char PM_1DayPeriodString[]     = "1 DAY";

//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3C1FAF860338
PM_ControlPeriodTcm::PM_ControlPeriodTcm (PM_GenericApplication     &theGenericApplication,
                                          CT_PM_Period              thePeriod,
                                          PM_AccumulationPeriod&    theAccPeriod,
                                          uint16                    theIndex,
                                          char*                     theProcessorTypeString,
                                          time_t                    thePstOffset):
	PM_ControlPeriod( theGenericApplication,
					  thePeriod,
					  theAccPeriod,
					  theIndex,
					  theProcessorTypeString,
					  thePstOffset,
					  false ),
    myDynamicIndex(0)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
// Class default destructor.
PM_ControlPeriodTcm::~PM_ControlPeriodTcm()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_ControlPeriodTcm::ControlPeriod(long theCurrentTimeChanged, FC_Time theCurrentTime,
                                        time_t thePstOffset,        time_t  theDstOffset)
{
    FC_Time currentPeriod;      // the current "current" period.
    long    accDurationChange;  // the accumulation of period duration change for this iteration.
    bool    aIsPmdayChged = false;

    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

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
        (*GetCurrentValueRegion())[myDynamicIndex].SetStartTime(currentPeriod);
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
        // check if date of is same day
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
        }
        else
        {
            // The period is INVALID.
            // Set the IDF of all parameters in that previous period.
            (*GetCurrentValueRegion())[myDynamicIndex].GetIdf()->ForcedSetAllIdf(true);
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
            (*GetCurrentValueRegion())[myDynamicIndex].GetIdf()->ForcedSetAllIdf(true);
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6D0134
void PM_ControlPeriodTcm::SwitchOnPeriod(FC_Time theCurrentPeriod)
{
    if (myWarning)
    {
        fc_cout << "\nPM " << myProcessorTypeString << ": Transfer Switch occurs , index " <<
            myIndex << " for " << myPeriodString << " period\n" << endl;
    }

    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    PM_BbValueTcm& currentValue = dynamic_cast<PM_BbValueTcm&>((*GetCurrentValueRegion())[myDynamicIndex]);

    // Set the period end time of the current data with current time.
    currentValue.SetEndTime(theCurrentPeriod);

    // Copy current data to previous data.
    PM_BbValueTcm& previousValue = dynamic_cast<PM_BbValueTcm&>((*GetPreviousValueRegion())[myIndex]);
    previousValue = currentValue;

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
         myGenericApplication.SetControlPeriodTimeStamp( myPeriod, previousValue.GetStartTime() );

         // Set ready status of previous value region in file storage subapp.
         myGenericApplication.SetPreviousRegionReady( myPeriod, true );
    }
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6D013E
void PM_ControlPeriodTcm::StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag)
{
    // Reset all registers (value and TCA) of the new current period for a new accumulation:

    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    // Value.
    if ((*GetConfigRegion())[myIndex].GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL))
        // If accumulation is not enabled then reset to default values.
        (*GetCurrentValueRegion())[myDynamicIndex].ResetAll();
    else
        // If accumulation is enabled then reset with previous values.
        (*GetCurrentValueRegion())[myDynamicIndex].ResetAll((*GetPreviousValueRegion())[myIndex]);

    // Maximum TCA.
    (*GetCurrentValueRegion())[myDynamicIndex].GetMaxTca()->ResetAllTca();

    // Adjust the IDF of all parameters for the current accumulation period.
    myAccPeriod.AdjustCurrentIdf();

    // Set the IDF of all parameters in that period,
    // if this period is started as invalid.
    if (theInvalidFlag)
        (*GetCurrentValueRegion())[myDynamicIndex].GetIdf()->ForcedSetAllIdf(true);

    // Reset the adjustment register for the new accumulation period.
    myAccPeriod.RegAdjReset();

    // Set the period start time for the new accumulation period.
    (*GetCurrentValueRegion())[myDynamicIndex].SetStartTime(newCurrentPeriod);

    // Reset the period end time for the new accumulation period.
    (*GetCurrentValueRegion())[myDynamicIndex].SetEndTime(0);

    // Reset the TCA present flag.
    GetCurrentValueRegion()->SetTcaPresent(false);
}


