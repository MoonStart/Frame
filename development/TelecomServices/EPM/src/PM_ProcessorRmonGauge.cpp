/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     December 21, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that computes the PM Parameters for RMON gauges.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <TimeService/FC_TimeService.h>
#include <PII_TickTimer.h>

#include <EPM/src/PM_RulesRmonGauge.h>
#include <EPM/src/PM_AccPeriodRmonGauge.h>
#include <EPM/src/PM_ControlPeriodRmonGauge.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_ProcessorRmonGauge.h>

//Two seconds in TickTimer format (in milliseconds)
static FC_Milliseconds PM_TWO_SECONDS_MILLISECONDS = 2000;

//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C1F9DED0308
PM_ProcessorRmonGauge::PM_ProcessorRmonGauge(PM_GenericApplication& theGenericApplication,
											 uint16 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_RMON_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C1F9DED0313
PM_ProcessorRmonGauge::~PM_ProcessorRmonGauge ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC723803B3
void PM_ProcessorRmonGauge::CreateActionsInstances()
{
    // Create request action for long operation.
	myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
												 *myGenericApplication.Get15MCurrentRegionValue(),
												 *myGenericApplication.GetDayCurrentRegionValue(),
												 *myGenericApplication.Get15MPreviousRegionValue(),
												 *myGenericApplication.GetDayPreviousRegionValue(),
												 myNumberOfPort);

	// This next set of code is a bit of an abomination of the PM architecture.
	// Two rules objects are created, one for 15 minute data, the other for one day data.
	// The assumption is for the RMON gauge data, there will only be one port monitored
	// per subapplication, etc. Therefore, the port number in the following constructor
	// invocations is forced to 0. Also, the myRules vector is loaded with a 15 minute
	// instance and a 1 day instance. These vector positions were originally intended
	// to be populated with per port instances. 
	myRules.push_back(new PM_RulesRmonGauge(myGenericApplication, CT_PM_PERIOD_15_MINUTES, 0));
	myRules.push_back(new PM_RulesRmonGauge(myGenericApplication, CT_PM_PERIOD_1_DAY, 0));

	// Create an Accumulation Period instance for 15 MINUTE period.
	myAccPeriod15m.push_back(new PM_AccumulationPeriodRmonGauge(myGenericApplication,
																PM_TypeRmonGauge::GetMaxValueTableRmon15M(),
																*myRules[CT_PM_PERIOD_15_MINUTES],
																0,
																CT_PM_PERIOD_15_MINUTES));

	myControl15m.push_back(new PM_ControlPeriodRmonGauge(myGenericApplication,
														 CT_PM_PERIOD_15_MINUTES,
														 *myAccPeriod15m[0],
														 0,
														 PM_RMON_STRING,
														 PM_TypeRmonGauge::GetMaxValueTableRmon15M()));

	// Create an Accumulation Period instance for 1 DAY period.
	myAccPeriodDay.push_back(new PM_AccumulationPeriodRmonGauge(myGenericApplication,
																PM_TypeRmonGauge::GetMaxValueTableRmonDay(),
																*myRules[CT_PM_PERIOD_1_DAY],
																0,
																CT_PM_PERIOD_1_DAY));

	myControlDay.push_back(new PM_ControlPeriodRmonGauge(myGenericApplication,
														 CT_PM_PERIOD_1_DAY,
														 *myAccPeriodDay[0],
														 0,
														 PM_RMON_STRING,
														 PM_TypeRmonGauge::GetMaxValueTableRmonDay(),
														 GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY)));
}

//-----------------------------------------------------------------
// The Run() in this class Processor is responsible for the following :
//    - harmonize the transmission of regions to ADMIN
//    - detect the change of period and adjust the current/previous regions
//      to transmit to ADMIN and reset the region pointers for the derived
//      Processor class in the next run.
//    - The Run() should be called at the end of the Run() of the derived Processor.
//##ModelId=3C1F9DEF0239
void PM_ProcessorRmonGauge::Run (FC_Object* theObject) 
{
    FC_Time         currentTime;
    time_t          dstOffset;
    FC_Milliseconds currentTick;
    long            currentTimeChanged;

    // Indicate that the processor is finally running
    if( myFirstTime )
    {
        myFirstTime = false;
    }

	// Cause each of the rules objects to update their respective current values.
	myRules[CT_PM_PERIOD_15_MINUTES]->UpdateRules();
	myRules[CT_PM_PERIOD_1_DAY]->UpdateRules();

    // This block is what the common PM Processor does on every second.
    // This is executed only at the end of the last thread of PM Processor.
    // Here we basically do the following 
    // - check the Time Of Day change 
    // - the end of period

    // Get the actual time.
    currentTime.GetCurrentTime();

    // Get the daylight saving time offset from Time Services.
    dstOffset= FC_TimeService::Instance()->GetDstOffset();

    // Get the tick timer (in milliseconds).
    currentTick = PII_TickTimer::readTimer();

    // Calculate the current time changing. The result is 0 if the time doesn't changed.
    // The result is positive if the time is forward, otherwize, the result is negative.
    currentTimeChanged = (long)((currentTime.GetUTCTime() - myLastTime.GetUTCTime()) - PM_COLLECT_INTERVAL_SEC);

    // Verify if the processor missed a second.
    if (myWarning)
    {
        if (currentTick - myLastTick >= PM_TWO_SECONDS_MILLISECONDS)
        {
            fc_cout << "\nWarning: " << myInstanceName << " " << myProcessorTypeString 
                 << " has missed a second\n" << endl;
        }
    }

    // Set my last time and tick for the next run.
    myLastTime = currentTime;
    myLastTick = currentTick;

    // The control of period is divided in some stages:
    // 1- Verification of the end of the period, using the ControlPeriod method.
    //    Region counter is incremented if TCAs occur.
    // 2- Update notify the region. If TCA occur, region is send.
    // 3- Copy content of current to previous period of accumulation if new period.


	// Control all periods by checking the end of the accumulation period.

	// 15 minutes: 
	myControl15m[0]->ControlPeriod(currentTimeChanged, currentTime);

	// 1 day: 
	// Especially for 1-day period, gives the period start time offset to the period controller.
	myControlDay[0]->ControlPeriod(currentTimeChanged, 
											currentTime, 
											GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
											dstOffset);

    // UpdateNotify the current register.
	myGenericApplication.GetCurrentRegionValue(CT_PM_PERIOD_15_MINUTES)->UpdateNotify();
	myGenericApplication.GetCurrentRegionValue(CT_PM_PERIOD_1_DAY)->UpdateNotify();

	// UpdateNotify the previous value regions after the appropriate delay.
	if( myPreviousValueUpdateCount > 0 )
	{
		myPreviousValueUpdateCount--;

		if( myPreviousValueUpdateCount == 0 )
		{
			myGenericApplication.GetPreviousRegionValue(CT_PM_PERIOD_15_MINUTES)->UpdateNotify();
			myGenericApplication.GetPreviousRegionValue(CT_PM_PERIOD_1_DAY)->UpdateNotify();
		}
	}
}
