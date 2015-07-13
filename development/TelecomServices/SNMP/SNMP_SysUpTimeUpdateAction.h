/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   Base class of SNMP Processing.
--------------------------------------------------------------------------*/

#ifndef SNMP_SYSUPTIMEUPDATEACTION_H
#define SNMP_SYSUPTIMEUPDATEACTION_H

#include <gdef.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ExecutionSupport/FC_Action.h>
#include <SNMP/SNMP_SystemRegion.h>

class SNMP_SysUpTimeUpdateAction : public FC_Action 
{
public:
    SNMP_SysUpTimeUpdateAction(SNMP_SysUpTimeRegion* theSysUpTimeRegion);
    virtual ~SNMP_SysUpTimeUpdateAction();
    virtual void Run(FC_Object* theObject = NULL);
protected:
    SNMP_SysUpTimeRegion*  mySysUpTimeRegion;
    uint32 myCurrLocalTickTimerValue;
    uint32 myLastLocalTickTimerValue;
    CT_SNMP_TimeTicks myCurrTimeTicksValue;
};

class SNMP_CtrlSysUpTimeUpdateAction : public SNMP_SysUpTimeUpdateAction
{
public:
    SNMP_CtrlSysUpTimeUpdateAction(SNMP_SysUpTimeRegion* theScSysTimeRegion,
                                   SNMP_SysInfoRegion* theSysInfoRegion);
    virtual ~SNMP_CtrlSysUpTimeUpdateAction();
    virtual void Run(FC_Object* theObject = NULL);
private:
    SNMP_SysInfoRegion* mySysInfoRegion;
    uint32 myLastAgentEnableTimestamp;
    uint32 myIterationCounter;
};

class SNMP_ScSysUpTimeUpdateAction : public SNMP_SysUpTimeUpdateAction
{
public:
    SNMP_ScSysUpTimeUpdateAction (SNMP_SysUpTimeRegion* theScSysTimeRegion,
                                  SNMP_SysUpTimeRegion* theCtrlSysTimeRegion);
    virtual ~SNMP_ScSysUpTimeUpdateAction();
    virtual void Run(FC_Object* theObject = NULL);

private:
    SNMP_SysUpTimeRegion*  myCtrlSysUpTimeRegion;
    CT_SNMP_TimeTicks myLastUpdateFromCtrl;
};

#endif //SNMP_SYSUPTIMEUPDATEACTION_H
 
