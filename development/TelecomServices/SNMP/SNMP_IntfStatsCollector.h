/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_INTFCOLLECTOR_H
#define SNMP_INTFCOLLECTOR_H

#include <SNMP/SNMP_Collector.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <SNMP/SNMP_IntfRegion.h>

// Forward class declaration

class SNMP_IntfStatsCollector: public SNMP_Collector
{
public:

    //The constructor of collector Data.
    SNMP_IntfStatsCollector(T6100_TelecomIf&      theTelecomIf,
                       MON_AppIf&            theMonApp,
                       SNMP_IntfCountRegion* theCountRegion,
                       CT_IntfId thePortId);
    
    //The default destructor of collector Data.
    virtual ~SNMP_IntfStatsCollector();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    virtual void Init();

    virtual void ProcessData();

protected:

    //Pointer to the region that contains Data counters for the current second.
    SNMP_IntfCountRegion* myIntfCountRegion;
};

#endif //SNMP_INTFCOLLECTOR_H
