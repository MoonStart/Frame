/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_ETHERHISTCONTROLLER_H
#define SNMP_ETHERHISTCONTROLLER_H

#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <SNMP/SNMP_RmonRegion.h>
#include <SNMP/SNMP_SystemRegion.h>
#include <vector>

using namespace std;

class CT_SNMP_Utilization;

class SNMP_RmonEtherHistIvalController
{
public:
    SNMP_RmonEtherHistIvalController();
    SNMP_RmonEtherHistIvalController(SNMP_RmonEtherHistStorageRegion* theStorageRegion,
                                     SNMP_SysUpTimeRegion*            theSysUpTimeRegion);
    virtual ~SNMP_RmonEtherHistIvalController();

    void UpdateSampleStart(vector<CT_SNMP_Utilization>& theUtilizationMonitors);

private:
    SNMP_RmonEtherHistStorageRegion* myStorageRegion;
    SNMP_SysUpTimeRegion*            mySysUpTimeRegion;
};

#endif //SNMP_ETHERHISTCONTROLLER_H
