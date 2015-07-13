/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   Process that computes the PM Parameters Optical Channel.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/src/PM_RulesCop.h>
#include <PM/src/PM_AccPeriodGauge.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbStatusCop.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_CopSubApplication.h>
#include <PM/PM_TypeCop.h>
#include <PM/PM_ProcessorCop.h>
#include <PII_TickTimer.h>
#include <EPM/src/PM_AccPeriodCop.h>

//Two seconds in TickTimer format (in milliseconds)
static FC_Milliseconds PM_TWO_SECONDS_MILLISECONDS = 2000;


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C50162402F1
PM_ProcessorCop::PM_ProcessorCop(PM_GenericApplication& theGenericApplication,
                                 uint32                 theNumberOfPort,
                                 CT_CardFamily          theCardFamily,
                                 CT_PM_Side             theSide):
    PM_Processor(theGenericApplication, (uint16)theNumberOfPort, PM_COP_STRING),
    myCardFamily(theCardFamily),
    mySide(theSide)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C5016240304
PM_ProcessorCop::~PM_ProcessorCop ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC72350304
void PM_ProcessorCop::CreateActionsInstances()
{
    // Create my request action.
    myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
                                                 *myGenericApplication.Get15MCurrentRegionValue(),
                                                 *myGenericApplication.GetDayCurrentRegionValue(),
                                                 *myGenericApplication.Get15MPreviousRegionValue(),
                                                 *myGenericApplication.GetDayPreviousRegionValue(),
                                                 myNumberOfPort);

    for (uint32 portNumber = 0; portNumber < myNumberOfPort; portNumber++)
    {
        // Create a Rules Copical instance.
        myRules.push_back(new PM_RulesCop(myGenericApplication, (uint16)portNumber, myCardFamily, mySide));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodCop(myGenericApplication,
                                                                PM_TypeCop::GetMaxValueTableCop15M(),
                                                                *myRules[portNumber],
                                                                PM_TypeCop::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_COP_STRING));


        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodCop(myGenericApplication,
                                                                PM_TypeCop::GetMaxValueTableCopDay(),
                                                                *myRules[portNumber],
                                                                PM_TypeCop::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_COP_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY) ));
    }

}

//-----------------------------------------------------------------
// The Run() in this derived Processor class is responsible for the following :
//    - harmonize the transmission of regions to ADMIN
//    - detect the change of period and adjust the current/previous regions
//      to transmit to ADMIN and reset the region pointers for the derived
//      class in the next run.
//    - Update the directionless state of the containing subapp.
//    - The Run() should be called at the end of the Run() of the derived Processor.
//##ModelId=3C1F9DEF0239
void PM_ProcessorCop::Run (FC_Object* theObject)
{
    FC_Time         currentTime;
    time_t          dstOffset;
    FC_Milliseconds currentTick;
    time_t            currentTimeChanged;
    uint16          portNumber;

    // Indicate that the processor is finally running
    if( myFirstTime )
    {
        myFirstTime = false;
    }

    // Update the subapp directionless state.
    dynamic_cast<PM_CopSubApplication&>(myGenericApplication).UpdateDirectionlessState();

    for (portNumber = 0 ; portNumber < myNumberOfPort; portNumber++)
    {
        myRules[portNumber]->UpdateRules();
    }

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
    currentTimeChanged = (currentTime.GetUTCTime() - myLastTime.GetUTCTime()) - PM_COLLECT_INTERVAL_SEC;

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


    // Update the accumulation rules and all PM parameters for all active ports only.
    for (portNumber = 0 ; portNumber < myNumberOfPort; portNumber++)
    {
        // Control all periods by checking the end of the accumulation period.

        // 15 minutes:
        myControl15m[portNumber]->ControlPeriod((long)currentTimeChanged, currentTime);

        // 1 day:
        // Especially for 1-day period, gives the period start time offset to the period controller.
        myControlDay[portNumber]->ControlPeriod((long)currentTimeChanged,
                                                currentTime,
                                                GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                dstOffset);
    }

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
