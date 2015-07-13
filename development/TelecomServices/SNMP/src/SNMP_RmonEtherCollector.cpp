/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_RmonCounters.h>
#include <Monitoring/MON_AppIf.h>
#include <SNMP/SNMP_RmonEtherCollector.h>
#include <T6100/T6100_TelecomIf.h>
#include <SNMP/SNMP_RmonEtherCount.h>

//-----------------------------------------------------------------
SNMP_RmonEtherCollector::SNMP_RmonEtherCollector (T6100_TelecomIf&   theTelecomIf,
                                                  MON_AppIf&         theMonApp,
                                                  SNMP_RmonEtherCountRegion* theCountRegion,
                                                  CT_IntfId          thePortId) :
    SNMP_Collector(theTelecomIf, theMonApp, "RMON", thePortId),
    myRmonEtherCountRegion(theCountRegion)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
SNMP_RmonEtherCollector::~SNMP_RmonEtherCollector ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_RmonEtherCollector::Init()
{
    SNMP_Collector::Init();
}

void SNMP_RmonEtherCollector::ProcessData()
{   
    MON_RmonCounters &countersObject = (MON_RmonCounters &) (*myMonApp.GetCountersRegion())[0];
    (*myRmonEtherCountRegion)[0].Update(countersObject);
    SNMP_Collector::ProcessData();
}
