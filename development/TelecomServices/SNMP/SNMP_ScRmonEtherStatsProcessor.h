

/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   Base class of SNMP Processing.
--------------------------------------------------------------------------*/

#ifndef SNMP_RMONETHERSTATSPROCESSOR_H
#define SNMP_RMONETHERSTATSPROCESSOR_H

#include <TimeService/FC_Time.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ExecutionSupport/FC_Action.h>
#include <SNMP/SNMP_RmonRegion.h>
#include <SNMP/SNMP_SystemRegion.h>

class SNMP_RmonEtherStatsCfgCtrl;

class SNMP_ScRmonEtherStatsProcessor : public FC_Action
{
public:
    SNMP_ScRmonEtherStatsProcessor (SNMP_RmonEtherStatsDataRegion* theDataRegion,
                                   SNMP_RmonEtherStatsCfgRegion* theCfgRegion,
                                   SNMP_RmonEtherCountRegion* theCountRegion,
                                   SNMP_SysUpTimeRegion* theSysUpTimeRegion);
    virtual ~SNMP_ScRmonEtherStatsProcessor();
    virtual void Run(FC_Object* theObject = NULL);

private:
    SNMP_RmonEtherStatsDataRegion*  myDataRegion;
    SNMP_RmonEtherStatsCfgRegion*   myCfgRegion;
    SNMP_RmonEtherCountRegion*      myCountRegion;
    SNMP_SysUpTimeRegion*           mySysUpTimeRegion;
    SNMP_RmonEtherStatsCfgCtrl*     myCfgCtrl;

};

#endif //SNMP_RMONETHERSTATSPROCESSOR_H
 
