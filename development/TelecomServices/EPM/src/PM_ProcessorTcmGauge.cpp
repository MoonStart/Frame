/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Process that computes the PM Parameters for Tcm gauges.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <TimeService/FC_TimeService.h>
#include <PII_TickTimer.h>

#include <EPM/src/PM_RulesTcmGauge.h>
#include <EPM/src/PM_AccPeriodTcmGauge.h>
#include <EPM/src/PM_ControlPeriodTcmGauge.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_ProcessorTcmGauge.h>
#include <T6100/T6100_ObjectAllocManager.h>

//Two seconds in TickTimer format (in milliseconds)
static FC_Milliseconds PM_TWO_SECONDS_MILLISECONDS = 2000;

//-----------------------------------------------------------------
// Class constructor.
PM_ProcessorTcmGauge::PM_ProcessorTcmGauge(PM_GenericApplication& theGenericApplication,
                                           uint16 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_TCM_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C1F9DED0313
PM_ProcessorTcmGauge::~PM_ProcessorTcmGauge ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC723803B3
void PM_ProcessorTcmGauge::CreateActionsInstances()
{
    // Create request action for long operation.
    myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
                                                 *myGenericApplication.Get15MCurrentRegionValue(),
                                                 *myGenericApplication.GetDayCurrentRegionValue(),
                                                 *myGenericApplication.Get15MPreviousRegionValue(),
                                                 *myGenericApplication.GetDayPreviousRegionValue(),
                                                  myNumberOfPort);

   for (uint portNumber = 0; portNumber < myNumberOfPort; portNumber++)
   {
       // Create a Rules instance.
       myRules.push_back(new PM_RulesTcmGauge(myGenericApplication, portNumber));

       // Create an Accumulation Period instance for 15 MINUTE period.
       myAccPeriod15m.push_back(new PM_AccumulationPeriodTcmGauge(myGenericApplication,
                                                                  PM_TypeTcmGauge::GetMaxValueTableTcm15M(),
                                                                  *myRules[portNumber],                                                                   
                                                                  portNumber,
                                                                  CT_PM_PERIOD_15_MINUTES));

       myControl15m.push_back(new PM_ControlPeriodTcmGauge(myGenericApplication,
                                                   CT_PM_PERIOD_15_MINUTES,
                                                   *myAccPeriod15m[portNumber],
                                                   portNumber,
                                                   PM_TCM_STRING,
                                                   0));

       // Create an Accumulation Period instance for 1 DAY period.
       myAccPeriodDay.push_back(new PM_AccumulationPeriodTcmGauge(myGenericApplication,
                                                                  PM_TypeTcmGauge::GetMaxValueTableTcmDay(),
                                                                  *myRules[portNumber],                                                                   
                                                                  portNumber,
                                                                  CT_PM_PERIOD_1_DAY));

       myControlDay.push_back(new PM_ControlPeriodTcmGauge(myGenericApplication,
                                                   CT_PM_PERIOD_1_DAY,
                                                   *myAccPeriodDay[portNumber],
                                                   portNumber,
                                                   PM_TCM_STRING,
                                                   GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY)));


    }
}

//-----------------------------------------------------------------
void PM_ProcessorTcmGauge::Run (FC_Object* theObject)
{
    FC_Time         currentTime;
    time_t          dstOffset;
    FC_Milliseconds currentTick;
    time_t          currentTimeChanged;
    T6100_ObjectAllocManager& objectAllocMgr = myGenericApplication.GetObjectAllocMgr();

    // Indicate that the processor is finally running
    if( myFirstTime )
    {
        myFirstTime = false;
    }

    // Reset pending the observation of at least one object.
    myObjectsAllocated = false;

    for (objectAllocMgr.InitMapIterator(); !(objectAllocMgr.IsIteratorAtEnd()); objectAllocMgr.IncrementMapIterator())
    {
        myRules[objectAllocMgr.GetStaticIndexFromIterator()]->UpdateRules();
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
    for (objectAllocMgr.InitMapIterator(); !(objectAllocMgr.IsIteratorAtEnd()); objectAllocMgr.IncrementMapIterator())
    {
        // We are inside the loop, therefore we found at least one object.
        myObjectsAllocated = true;

        // Control all periods by checking the end of the accumulation period.

        // 15 minutes:
        myControl15m[objectAllocMgr.GetStaticIndexFromIterator()]->ControlPeriod((long)currentTimeChanged, currentTime);

        // 1 day:
        // Especially for 1-day period, gives the period start time offset to the period controller.
        myControlDay[objectAllocMgr.GetStaticIndexFromIterator()]->ControlPeriod((long)currentTimeChanged,
                                                currentTime,
                                                GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                dstOffset);
    }

    // UpdateNotify the current register.
    myGenericApplication.GetCurrentRegionValue(CT_PM_PERIOD_15_MINUTES)->UpdateNotify();
    myGenericApplication.GetCurrentRegionValue(CT_PM_PERIOD_1_DAY)->UpdateNotify();
}

//-----------------------------------------------------------------
void PM_ProcessorTcmGauge::Init()
{
    for (uint32 portNumber = 0; portNumber < myNumberOfPort; portNumber++)
    {
        myAccPeriod15m[portNumber]->Init((uint16)portNumber);

        myAccPeriodDay[portNumber]->Init((uint16)portNumber);

        myControl15m[portNumber]->Init();

        myControlDay[portNumber]->Init();

        myRules[portNumber]->Init();
    }
}

//-----------------------------------------------------------------
void PM_ProcessorTcmGauge::Init( uint16 thePortNumber )
{
    myAccPeriod15m[thePortNumber]->Init(thePortNumber);

    myAccPeriodDay[thePortNumber]->Init(thePortNumber);

    myControl15m[thePortNumber]->Init();

    myControlDay[thePortNumber]->Init();

    myRules[thePortNumber]->Init();
}
