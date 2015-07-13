
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   Base class of SNMP Processing.
--------------------------------------------------------------------------*/

#ifndef SNMP_INTFSTATSPROCESSOR_H
#define SNMP_INTFSTATSPROCESSOR_H

#include <TimeService/FC_Time.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ExecutionSupport/FC_Action.h>
#include <SNMP/SNMP_IntfRegion.h>
#include <SNMP/SNMP_SystemRegion.h>
#include <Alarm/ALM_FailureRegionImp.h>

class ALM_FailureBase;
class SNMP_IntfConfigController;
class CFG_Region;
class MON_Region;

class SNMP_ScIntfStatsProcessor : public FC_Action
{
public:
    SNMP_ScIntfStatsProcessor (SNMP_IntfStatsDataRegion* theDataRegion,
                               SNMP_IntfStatsCfgRegion*  theCfgRegion,
                               SNMP_IntfCountRegion*     theCountRegion,
                               SNMP_SysUpTimeRegion*     theSysUpTimeRegion,
                               MON_Region*      theMonOptCfgRegion,
                               CFG_Region*         theCfgOptRegion,
                               ALM_FailureRegionImp<ALM_FailureBase>* theRsAlmRegion);
    virtual ~SNMP_ScIntfStatsProcessor();
    virtual void Run(FC_Object* theObject = NULL);

private:
    SNMP_IntfStatsDataRegion*  myDataRegion;
    SNMP_IntfStatsCfgRegion*   myCfgRegion;
    SNMP_IntfCountRegion*      myCountRegion;
    SNMP_SysUpTimeRegion*      mySysUpTimeRegion;
    SNMP_IntfConfigController* myCfgCtrl;
    MON_Region*                myMonOptCfgRegion;
    CFG_Region*                myCfgOptRegion;
    ALM_FailureRegionImp<ALM_FailureBase>* myAlmRsRegion;
    CT_SNMP_OperStatus         myLastOperStatus;

};

#endif //SNMP_INTFSTATSPROCESSOR_H
 
