/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#include <SNMP/SNMP_SystemRegion.h>
#include <SNMP/SNMP_SystemData.h>
#include <SNMP/SNMP_SysUpTimeUpdateAction.h>
#include <SNMP/SNMP_Defs.h>
#include <PII_TickTimer.h>

//-----------------------------------------------------------------
SNMP_SysUpTimeUpdateAction::SNMP_SysUpTimeUpdateAction (SNMP_SysUpTimeRegion* theSysTimeRegion) :
mySysUpTimeRegion(theSysTimeRegion),
myCurrLocalTickTimerValue(0),
myLastLocalTickTimerValue(0),
myCurrTimeTicksValue(0)
{
}

//-----------------------------------------------------------------
SNMP_SysUpTimeUpdateAction::~SNMP_SysUpTimeUpdateAction ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_SysUpTimeUpdateAction::Run (FC_Object* theObject) 
{
    uint32 diffTickValue = 0;
    myLastLocalTickTimerValue = myCurrLocalTickTimerValue;
    myCurrLocalTickTimerValue = (static_cast<uint32> (PII_TickTimer::readTimer()));
    if (myCurrLocalTickTimerValue < myLastLocalTickTimerValue) 
    {
        diffTickValue += SNMP_MAX_COUNTER32 - myLastLocalTickTimerValue;
        diffTickValue += myCurrLocalTickTimerValue;
        diffTickValue = diffTickValue / 10;
    }
    else
    {
        diffTickValue = ((myCurrLocalTickTimerValue - myLastLocalTickTimerValue) / 10);
    }
    myCurrTimeTicksValue += (static_cast<CT_SNMP_TimeTicks> (diffTickValue));
    //cout << "sysUpTime Calculated: " << dec << myCurrTimeTicksValue << endl;
    SNMP_BbSystemUpTime& sysUpTimeObj = (*mySysUpTimeRegion)[0];
    sysUpTimeObj.SetSysUpTime(myCurrTimeTicksValue);
}

//-----------------------------------------------------------------
SNMP_ScSysUpTimeUpdateAction::SNMP_ScSysUpTimeUpdateAction (SNMP_SysUpTimeRegion* theScSysTimeRegion,
                                  SNMP_SysUpTimeRegion* theCtrlSysTimeRegion) :
SNMP_SysUpTimeUpdateAction(theScSysTimeRegion),
myCtrlSysUpTimeRegion(theCtrlSysTimeRegion),
myLastUpdateFromCtrl(0)
{
}

//-----------------------------------------------------------------
SNMP_ScSysUpTimeUpdateAction::~SNMP_ScSysUpTimeUpdateAction ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_ScSysUpTimeUpdateAction::Run (FC_Object* theObject) 
{
    SNMP_BbSystemUpTime& ctrlSysUpTimeObj = (*myCtrlSysUpTimeRegion)[0];
    if (myLastUpdateFromCtrl != ctrlSysUpTimeObj.GetSysUpTime()) 
    {
        SNMP_BbSystemUpTime& scSysUpTimeObj = (*mySysUpTimeRegion)[0];
        myCurrTimeTicksValue = ctrlSysUpTimeObj.GetSysUpTime();
        myLastUpdateFromCtrl = myCurrTimeTicksValue;
        scSysUpTimeObj.SetSysUpTime(myCurrTimeTicksValue);
       //cout << "sysUpTime Update from Ctrl: " << dec << myCurrTimeTicksValue << endl;
    }
    else
    {
        SNMP_SysUpTimeUpdateAction::Run(theObject);
    }
    mySysUpTimeRegion->IncModificationCounter();
}

//-----------------------------------------------------------------
SNMP_CtrlSysUpTimeUpdateAction::SNMP_CtrlSysUpTimeUpdateAction (SNMP_SysUpTimeRegion* theCtrlSysTimeRegion,
                                   SNMP_SysInfoRegion* theSysInfoRegion) :
SNMP_SysUpTimeUpdateAction(theCtrlSysTimeRegion),
mySysInfoRegion(theSysInfoRegion),
myLastAgentEnableTimestamp(0),
myIterationCounter(0)
{
}

//-----------------------------------------------------------------
SNMP_CtrlSysUpTimeUpdateAction::~SNMP_CtrlSysUpTimeUpdateAction ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_CtrlSysUpTimeUpdateAction::Run (FC_Object* theObject) 
{
    SNMP_BbSystemInfo& sysInfoObj = (*mySysInfoRegion)[0];
    if (myLastAgentEnableTimestamp != sysInfoObj.GetSnmpEnableTimestamp()) 
    {
        myLastAgentEnableTimestamp = sysInfoObj.GetSnmpEnableTimestamp();
        myCurrLocalTickTimerValue = (static_cast<uint32> (PII_TickTimer::readTimer()));
        myLastLocalTickTimerValue = myCurrLocalTickTimerValue;
        SNMP_BbSystemUpTime& ctrlSysUpTimeObj = (*mySysUpTimeRegion)[0];
        myCurrTimeTicksValue = 0;
        ctrlSysUpTimeObj.SetSysUpTime(myCurrTimeTicksValue);
       // cout << "sysUpTime Update from Agent: " << dec << myCurrTimeTicksValue << endl;
    }
    else
    {
        SNMP_SysUpTimeUpdateAction::Run(theObject);
    }
    if (++myIterationCounter > 30) 
    {
        myIterationCounter = 0;
        mySysUpTimeRegion->IncModificationCounter();
    }
}
