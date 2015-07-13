/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:
 TARGET   :
 AUTHOR   :
 DESCRIPTION:
--------------------------------------------------------------------------*/

#include <TimeService/FC_TimeService.h>
#include <PII_TickTimer.h>
#include <CsPii/CSPII_CardIF.h>
#include <SNMP/SNMP_Processor.h>

using namespace std;


//-----------------------------------------------------------------
// Class constructor.
SNMP_Processor::SNMP_Processor (char*  theProcessorTypeString):
    myWarning(false),
    myProcessorTypeString(theProcessorTypeString)
{
    char tmp[8];
    string processName ("SNMP_Processor");
    string slotId,shelfId;

    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetShelfId());
    shelfId = tmp;
    sprintf(tmp,"%d",CSPII_CardIF::GetInstance()->GetSlotId());
    slotId = tmp;

    myInstanceName = processName+":"+shelfId+"."+slotId;
    myLastTime = 0;
}

//-----------------------------------------------------------------
// Class default destructor
SNMP_Processor::~SNMP_Processor ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void SNMP_Processor::Init()
{
}

//-----------------------------------------------------------------
void SNMP_Processor::CreateActionsInstances()
{
}

//-----------------------------------------------------------------
void SNMP_Processor::DeleteActionsInstances()
{
}

//-----------------------------------------------------------------
void SNMP_Processor::Run (FC_Object* theObject)
{
}

//-----------------------------------------------------------------
void SNMP_Processor::SetWarning(bool theWarning)
{
}
