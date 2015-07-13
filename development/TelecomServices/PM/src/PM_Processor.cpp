/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Base class of PM Processing.
--------------------------------------------------------------------------*/

#include <TimeService/FC_TimeService.h>
#include <PII_TickTimer.h>
#include <CsPii/CSPII_CardIF.h>
#include <PM/PM_Def.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/src/PM_Rules.h>
#include <PM/src/PM_Processor.h>


using namespace std;

//Two seconds in TickTimer format (in milliseconds)
static FC_Milliseconds PM_TWO_SECONDS_MILLISECONDS = 2000;

//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C1F9DEF0210
PM_Processor::PM_Processor (PM_GenericApplication&  theGenericApplication,
                            uint16                  theNumberOfPort,
                            char*                   theProcessorTypeString):
    myWarning(false),
    myControl15m(NULL),
    myControlDay(NULL),
    myNumberOfPort(theNumberOfPort),
    myProcessorTypeString(theProcessorTypeString),
    myGenericApplication(theGenericApplication),
    myAccPeriod15m(NULL),
    myAccPeriodDay(NULL),
    myRegionRequestAction(NULL),
    myRules(NULL),
    myPreviousValueUpdateCount(0),
    myFirstTime( true ),
    myLastTick(0)
{
    char tmp[8];
    string processName ("PM_Processor");
    string slotId,shelfId;

    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetShelfId());
    shelfId = tmp;
    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetSlotId());
    slotId = tmp;

    myInstanceName = processName+":"+shelfId+"."+slotId;
    myLastTime = 0;

    myPreviousValueUpdateDelay =  ((CSPII_CardIF::GetInstance()->GetShelfId()) * PM_NUMBER_OF_TRN_IN_PORT_SHELF) +
                                  (CSPII_CardIF::GetInstance()->GetSlotId());

}

//-----------------------------------------------------------------
// Class default destructor
//##ModelId=3C1F9DEF022E
PM_Processor::~PM_Processor ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F9DEF0230
void PM_Processor::Init()
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
//##ModelId=3CBC723C01F6
void PM_Processor::DeleteActionsInstances()
{
    vector<PM_AccumulationPeriod*>::iterator iterator;
    vector<PM_ControlPeriod*>::iterator iteratorCtl;
    vector<PM_Rules*>::iterator iteratorRules;


    for(iteratorRules = myRules.begin(); iteratorRules != myRules.end(); iteratorRules++)
        delete *iteratorRules;

    // Delete content of vector of accumulation period for 15 minutes.
    for (iterator = myAccPeriod15m.begin(); iterator != myAccPeriod15m.end(); iterator++)
        delete *iterator;

    // Delete content of vector of accumulation period for 1 day.
    for (iterator = myAccPeriodDay.begin(); iterator != myAccPeriodDay.end(); iterator++)
        delete *iterator;

    // Delete content of vector of control period for 15 minutes.
    for (iteratorCtl = myControl15m.begin(); iteratorCtl != myControl15m.end(); iteratorCtl++)
        delete *iteratorCtl;

    // Delete content of vector of control period for 1 day.
    for (iteratorCtl = myControlDay.begin(); iteratorCtl != myControlDay.end(); iteratorCtl++)
        delete *iteratorCtl;

    // Delete content of vector of request action.
    delete myRegionRequestAction;

}

//-----------------------------------------------------------------
// The Run() in this base class Processor is responsible for the following :
//    - harmonize the transmission of regions to ADMIN
//    - detect the change of period and adjust the current/previous regions
//      to transmit to ADMIN and reset the region pointers for the derived
//      Processor class in the next run.
//    - The Run() should be called at the end of the Run() of the derived Processor.
//##ModelId=3C1F9DEF0239
void PM_Processor::Run (FC_Object* theObject)
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

//-----------------------------------------------------------------
//##ModelId=3C1F9DEF0244
void PM_Processor::SetWarning(bool theWarning)
{
    myWarning = theWarning;

    vector<PM_ControlPeriod*>::iterator iterator15m;
    vector<PM_ControlPeriod*>::iterator iteratorDay;

    for (iterator15m = myControl15m.begin(), iteratorDay = myControlDay.begin();
         iterator15m != myControl15m.end();
         iterator15m++, iteratorDay++)
    {
        (*iterator15m)->SetWarning(theWarning);
        (*iteratorDay)->SetWarning(theWarning);
    }

}

//-----------------------------------------------------------------
void PM_Processor::InitPreviousValueUpdateDelay()
{
    myPreviousValueUpdateCount = myPreviousValueUpdateDelay;
}

//-----------------------------------------------------------------
bool PM_Processor::GetRunningState()
{
    return !myFirstTime;
}

