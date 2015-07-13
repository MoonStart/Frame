/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_INTFCONFIGCONTROLLER_H
#define SNMP_INTFCONFIGCONTROLLER_H

#include <vector>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <SNMP/SNMP_IntfRegion.h>
#include <SNMP/SNMP_IntfStatsConfig.h>
#include <SNMP/SNMP_IntfStatsData.h>
#include <SNMP/SNMP_SystemRegion.h>

using namespace std;

class SNMP_IntfConfigController
{
public:
    SNMP_IntfConfigController(SNMP_IntfStatsDataRegion* theDataRegion,
                              SNMP_IntfStatsCfgRegion*  theCfgRegion,
                              SNMP_SysUpTimeRegion*     theSysUpTimeRegion) :
        myCfgRegion(theCfgRegion),
        myDataRegion(theDataRegion),
        mySysUpTimeRegion(theSysUpTimeRegion) { }
    ~SNMP_IntfConfigController() { }

    void UpdateConfig();
protected:

    SNMP_IntfStatsCfgRegion*  myCfgRegion;
    SNMP_IntfStatsDataRegion* myDataRegion;
    SNMP_SysUpTimeRegion*     mySysUpTimeRegion;

private:
    SNMP_IntfConfigController();

};

#endif //SNMP_INTFCONFIGCONTROLLER_H
