/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   Process that computes the PM Parameters of Near-End SONET/SDH
                HOP.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PII_TickTimer.h>

#include <PM/src/PM_RulesHopNearEnd.h>
#include <PM/src/PM_AccPeriodHopNearEnd.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM_GenericApplication.h>
#include <PM/PM_HopNearEndSubApplication.h>
#include <PM/PM_ProcessorHopNearEnd.h>
#include <EPM/src/PM_ControlPeriodHopNearEnd.h>

//Two seconds in TickTimer format (in milliseconds)
static FC_Milliseconds PM_TWO_SECONDS_MILLISECONDS = 2000;

//-----------------------------------------------------------------
// Class constructor.
PM_ProcessorHopNearEnd::PM_ProcessorHopNearEnd(PM_GenericApplication& theGenericApplication,
                                               uint16                 theNumberOfPort,
                                               CT_PM_Sts_Offset		 theSts1Offset):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_HOP_NE_STRING),
    mySts1Offset(theSts1Offset)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
PM_ProcessorHopNearEnd::~PM_ProcessorHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_ProcessorHopNearEnd::CreateActionsInstances()
{
    // Create request action for long operation.
    myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
                                                 *myGenericApplication.Get15MCurrentRegionValue(),
                                                 *myGenericApplication.GetDayCurrentRegionValue(),
                                                 *myGenericApplication.Get15MPreviousRegionValue(),
                                                 *myGenericApplication.GetDayPreviousRegionValue(),
                                                 myNumberOfPort);

    for (uint32 portNumber = 0; portNumber < myNumberOfPort; portNumber++)
    {
        // Add to the vector the Parameters HopNearEnd class.
        myRules.push_back(new PM_RulesHopNearEnd(myGenericApplication, (uint16)portNumber, mySts1Offset));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodHopNearEnd(myGenericApplication,
                                                               PM_TypeHopNearEnd::GetMaxValueTableHopNearEnd15M(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_HOP_NE_STRING,
                                                    0,
                                                    false));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodHopNearEnd(myGenericApplication,
                                                               PM_TypeHopNearEnd::GetMaxValueTableHopNearEndDay(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_HOP_NE_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    false));

    }

}

//-----------------------------------------------------------------
void PM_ProcessorHopNearEnd::Run (FC_Object* theObject)
{
    FC_Time         currentTime;
    time_t          dstOffset;
    FC_Milliseconds currentTick;
    time_t            currentTimeChanged;
    uint16          portNumber;
    PM_HopNearEndSubApplication &hopApp = dynamic_cast<PM_HopNearEndSubApplication&>(myGenericApplication);

    // Indicate that the processor is finally running
    if( myFirstTime )
    {
        myFirstTime = false;
    }

    for (portNumber = 0 ; portNumber < myNumberOfPort; portNumber++)
    {
        myRules[portNumber]->UpdateRules();
    }

    // "Consume", or reset, the flag set by the collector indicating
    // whether or not the line side STS selection has changed.
    hopApp.SetSts1ConfigChanged( false );

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

    // UpdateNotify current value registers.
    myGenericApplication.GetCurrentRegionValue(CT_PM_PERIOD_15_MINUTES)->UpdateNotify();
    myGenericApplication.GetCurrentRegionValue(CT_PM_PERIOD_1_DAY)->UpdateNotify();

}


