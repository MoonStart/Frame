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
#include <SNMP/SNMP_IntfStatsCollector.h>
#include <T6100/T6100_TelecomIf.h>
#include <SNMP/SNMP_IntfCount.h>

//-----------------------------------------------------------------
SNMP_IntfStatsCollector::SNMP_IntfStatsCollector (T6100_TelecomIf&      theTelecomIf,
                                        MON_AppIf&            theMonApp,
                                        SNMP_IntfCountRegion* theCountRegion,
                                        CT_IntfId             thePortId) :
    SNMP_Collector(theTelecomIf, theMonApp, "INTF", thePortId),
    myIntfCountRegion(theCountRegion)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
SNMP_IntfStatsCollector::~SNMP_IntfStatsCollector ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_IntfStatsCollector::Init()
{
    SNMP_Collector::Init();
}

void SNMP_IntfStatsCollector::ProcessData()
{   
    MON_RmonCounters &countersObject = (MON_RmonCounters &) (*myMonApp.GetCountersRegion())[0];
    MON_RmonStatus& statusObject = (MON_RmonStatus &) (*myMonApp.GetStatusRegion())[0];
    (*myIntfCountRegion)[0].Update(countersObject, statusObject);
    SNMP_Collector::ProcessData();
}
