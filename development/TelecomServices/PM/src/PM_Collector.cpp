/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     February 15, 1999 Marc-Andre Ledoux.
 DESCRIPTION:   Process that collects the data needed by the PM Processor.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_Stream.h>
#include <PII_TickTimer.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include "PM_Collector.h"
#include <CsPii/CSPII_CardIF.h>
#include <T6100/T6100_CardActiveRegion.h>
#include <T6100/T6100_MainAppIf.h>
#include <T6100/T6100_ControllerStatusRegion.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_Processor.h>

#ifndef FC_TimeMgmtApp_h
#include <TimeService/FC_TimeMgmtApp.h>
#endif

#ifndef FC_TimeRefBbRegion_h
#include <TimeService/FC_TimeRefBbRegion.h>
#endif

#ifndef FC_TimeService_h
#include <TimeService/FC_TimeService.h>
#endif

using namespace std;


//-----------------------------------------------------------------
//##ModelId=3C1F6F8503A5
PM_Collector::PM_Collector (PM_GenericApplication& theGenericApplication,
                            FC_OneShotProcess &theProcessorProcess,
                            char* theCollectorTypeString,
                            uint32 theNumberOfPort):
    myGenericApplication(theGenericApplication),
    myProcessorProcess(theProcessorProcess),
    myCollectorTypeString(theCollectorTypeString),
    myNumberOfPort(theNumberOfPort),
    myFirstTimeRun(true),
    myWarning(false),
    myIsTimeSyncedWithController(false),
    myLastTick(0)
{
    char tmp[8];
    string processName ("PM_Collector");
    string slotId,shelfId;

    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetShelfId());
    shelfId = tmp;
    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetSlotId());
    slotId = tmp;

    myInstanceName = processName+":"+shelfId+"."+slotId;

    if( T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() )
    {
        // If this PM collector is executing on the active controller, then
        // by definition its time base is synchronized to the controller.
        myIsTimeSyncedWithController = true;
    }   
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8503B9
PM_Collector::~PM_Collector()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8503BB
void PM_Collector::Init()
{
    myFirstTimeRun = true;
    myWarning = false;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F86000E
void PM_Collector::Verify(FC_Milliseconds currentTick)
{
    FC_Milliseconds diffTick;


    if (myWarning)
    {
        if (myLastTick != 0)
        {
            diffTick = currentTick - myLastTick;

            if (diffTick >= 2000)
            {
                fc_cout << "\nWarning: " << myInstanceName << " " << myCollectorTypeString << 
                    " has missed a second\n" << endl; 
            }

            else if (diffTick >= 1050)
            {
                fc_cout << "\nWarning: " << myInstanceName << " " << myCollectorTypeString << 
                    " executed " << (diffTick - 1000) << " ms too late.\n" << endl;
            }

            else if (diffTick <= 950)
            {
                fc_cout << "\nWarning: " << myInstanceName << " " << myCollectorTypeString << 
                    " executed " << (diffTick - 1000) << " ms too early.\n" << endl;
            }
        }  
    }

    myLastTick = currentTick;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F860019
void PM_Collector::WakeUpProcessor()
{
    // Let the collector run 1 time before waking-up the processor, 
    // in order to have a 1 second interval right after the system startup. 
    if (myFirstTimeRun)
    {
        myFirstTimeRun = false;
    }
    // Run the processor.
    else
    {
        // Wake up the PM processor.
        myProcessorProcess.WakeUp();
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D2C03DB
void PM_Collector::ProcessData()
{
    FC_Milliseconds currentTick = PII_TickTimer::readTimer();


    // Verify if PM collector executed in time
    Verify(currentTick);

    // Wake up the processor
    WakeUpProcessor();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D2D00B1
void PM_Collector::ResetData()
{
    Init();
    myGenericApplication.GetPmProcessor().Init();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D2B03B1
FC_Object*  PM_Collector::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    if( !myIsTimeSyncedWithController )
    {
        // check the system time is synchronized with controller to run
        FC_TimeRefBbRegion* timeRefRegion = &FC_TimeService::Instance()->GetTimeRefRegion();
        if( (*timeRefRegion)[0].IsSystemTimeUpdate() )
        {
            myIsTimeSyncedWithController = true;
        }
    }
    else
    {
        // Verify if card is active.
        if(myGenericApplication.GetCardActiveRegionRef().GetActive())
        {
            ProcessData();
        }
        else
        {
            ResetData();
        }
    }

    return NULL;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8503C4
void PM_Collector::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_SWError, "Run method is obsoleted!");

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F8503D0
void PM_Collector::SetWarning(bool theWarning)
{
    myWarning  = theWarning;

}

//-----------------------------------------------------------------
//##ModelId=3C9255C8005A
const char* PM_Collector::GetInstanceName( void ) const
{
    return myInstanceName.c_str();

}
