
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   Base class of SNMP Processing.
--------------------------------------------------------------------------*/

#ifndef SNMP_RMONETHERHISTPROCESSOR_H
#define SNMP_RMONETHERHISTPROCESSOR_H

#include <TimeService/FC_Time.h>
#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Monitoring/MON_AppIf.h>
#include <SNMP/SNMP_RmonRegion.h>
#include <SNMP/SNMP_SystemRegion.h>
#include <ExecutionSupport/FC_Action.h>
#include <vector>

using namespace std;

class SNMP_RmonEtherHistCfgCtrl;
class SNMP_RmonEtherHistIvalController;
class CT_SNMP_Utilization;
class CFG_Region;
class MON_AppIf;
class CFG_AppIf;

class SNMP_ScRmonEtherHistProcessor : public FC_Action
{

public:

    SNMP_ScRmonEtherHistProcessor (SNMP_RmonEtherHistStorageRegion* theStorageRegion,
                                    SNMP_RmonEtherHistDataRegion* theDataRegion,
                                   SNMP_RmonEtherHistCfgRegion* theCfgRegion,
                                   SNMP_RmonEtherCountRegion* theCountRegion,
                                   SNMP_SysUpTimeRegion* theSysUpTimeRegion,
                                   CFG_Region* theOptCfgRegion,
                                   MON_AppIf& theMonApp,
                                   CFG_AppIf& theCfgRsApp,
                                   MON_AppIf* theMacMonApp);
    virtual ~SNMP_ScRmonEtherHistProcessor();
    virtual void Run(FC_Object* theObject = NULL);

private:
    SNMP_RmonEtherHistIvalController* myHistCtrl;
    SNMP_RmonEtherHistCfgCtrl*        myCfgCtrl;
    SNMP_RmonEtherHistStorageRegion*  myStorageRegion;
    SNMP_RmonEtherHistDataRegion*     myDataRegion;
    SNMP_RmonEtherHistCfgRegion*      myCfgRegion;
    SNMP_RmonEtherCountRegion*        myCountRegion;
    MON_AppIf*                        myMacMonApp;
    vector<CT_SNMP_Utilization>       myUtilzationMonitors;
};

#endif //SNMP_RMONETHERHISTPROCESSOR_H
 
