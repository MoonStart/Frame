/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <BaseClass/FC_Stream.h>
#include <PII_TickTimer.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <SNMP/SNMP_Collector.h>
#include <CsPii/CSPII_CardIF.h>
#include <T6100_CardActiveRegion.h>
#include <T6100_TelecomIf.h>

using namespace std;

//-----------------------------------------------------------------
SNMP_Collector::SNMP_Collector (T6100_TelecomIf& theTelecomIf,
                                MON_AppIf&       theMonApp,
                                char* theCollectorTypeString,
                                CT_IntfId theIntfId):
    myCollectorTypeString(theCollectorTypeString),
    myFirstTimeRun(true),
    myWarning(false)    ,
    myCardActiveRegion(theTelecomIf.GetStatusRegion()),
    myIntfId(theIntfId),
    myMonApp(theMonApp)
{
    char tmp[8];
    string processName ("SNMP_Collector");
    string slotId,shelfId,portId;

    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetShelfId());
    shelfId = tmp;
    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetSlotId());
    slotId = tmp;
    sprintf(tmp,"%d", static_cast<int> (myIntfId));
    portId = tmp;

    myInstanceName = processName + ":" + shelfId + "." + slotId + "." + portId;
}

//-----------------------------------------------------------------
SNMP_Collector::~SNMP_Collector()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_Collector::Init()
{
    myFirstTimeRun = true;
    myWarning = false;
}


void SNMP_Collector::AddProcessor(FC_OneShotProcess* theProcess)
{
    myProcessors.push_back(theProcess);
}

//-----------------------------------------------------------------
void SNMP_Collector::Verify(FC_Milliseconds currentTick)
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
void SNMP_Collector::WakeUpProcessors()
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
        // Wake up the processors
        vector<FC_OneShotProcess*>::iterator theProcIter;
        for (theProcIter = myProcessors.begin(); 
             theProcIter != myProcessors.end(); ++theProcIter)
        {
            (*theProcIter)->WakeUp();
        }
    }
}

//-----------------------------------------------------------------
void SNMP_Collector::ProcessData()
{
    FC_Milliseconds currentTick = PII_TickTimer::readTimer();

    // Verify if collector executed in time
    Verify(currentTick);

    // Wake up the processor
    WakeUpProcessors();

}

//-----------------------------------------------------------------
void SNMP_Collector::ResetData()
{
    Init();
}

//-----------------------------------------------------------------
FC_Object*  SNMP_Collector::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    // Verify if card is active.
    if (myCardActiveRegion.GetActive()) 
    {
        ProcessData();
    }
    else
    {
        ResetData();
    }

    return NULL;

}

//-----------------------------------------------------------------
void SNMP_Collector::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_SWError, "Run method is obsoleted!");
}

//-----------------------------------------------------------------
void SNMP_Collector::SetWarning(bool theWarning)
{
    myWarning  = theWarning;
}

//-----------------------------------------------------------------
const char* SNMP_Collector::GetInstanceName( void ) const
{
    return myInstanceName.c_str();
}
