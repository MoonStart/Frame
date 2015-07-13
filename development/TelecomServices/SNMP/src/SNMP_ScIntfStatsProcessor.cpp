/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <TimeService/FC_TimeService.h>
#include <CsPii/CSPII_CardIF.h>
#include <SNMP/SNMP_ScIntfStatsProcessor.h>
#include <SNMP/SNMP_IntfStatsConfigController.h>
#include <SNMP/SNMP_IntfRegion.h>
#include <SNMP/SNMP_IntfStatsData.h>
#include <SNMP/SNMP_IntfStatsConfig.h>
#include <SNMP/SNMP_IntfCount.h>
#include <SNMP/SNMP_SystemData.h>
#include <Configuration/CFG_Region.h>
#include <Monitoring/MON_Region.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <Configuration/CFG_Opt.h>
#include <Monitoring/MON_OptConfig.h>

//-----------------------------------------------------------------
SNMP_ScIntfStatsProcessor::SNMP_ScIntfStatsProcessor (SNMP_IntfStatsDataRegion* theDataRegion,
                                                      SNMP_IntfStatsCfgRegion* theCfgRegion,
                                                      SNMP_IntfCountRegion* theCountRegion,
                                                      SNMP_SysUpTimeRegion* theSysUpTimeRegion,
                                                      MON_Region*  theMonOptCfgRegion,
                                                      CFG_Region* theOptCfgRegion,
                                                      ALM_FailureRegionImp<ALM_FailureBase>* theRsAlmRegion) :
myDataRegion(theDataRegion),
myCfgRegion(theCfgRegion),
myCountRegion(theCountRegion),
mySysUpTimeRegion(theSysUpTimeRegion),
myMonOptCfgRegion(theMonOptCfgRegion),
myCfgOptRegion(theOptCfgRegion),
myAlmRsRegion(theRsAlmRegion),
myLastOperStatus(CT_SNMP_OperStatusNotPresent)
{
    myCfgCtrl = new SNMP_IntfConfigController(myDataRegion, myCfgRegion, theSysUpTimeRegion);
}

//-----------------------------------------------------------------
SNMP_ScIntfStatsProcessor::~SNMP_ScIntfStatsProcessor ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_ScIntfStatsProcessor::Run (FC_Object* theObject) 
{
    SNMP_BbIntfCount& intfCount = (*myCountRegion)[0];
    ALM_FailureBase&  almRs = static_cast<ALM_FailureBase&> ((*myAlmRsRegion)[0]);
    MON_OptConfig& monOptCfg = static_cast<MON_OptConfig&> ((*myMonOptCfgRegion)[0]);
    CFG_Opt& optCfg = static_cast<CFG_Opt&> ((*myCfgOptRegion)[0]);
    CT_SNMP_OperStatus currOperStatus;
    CT_SNMP_AdminStatus currAdminStatus;

    myCfgCtrl->UpdateConfig();
    SNMP_BbIntfStatsData& intfEntry = (*myDataRegion)[0];
    if (intfEntry.IsCollectionEnabled()) 
    {
        intfEntry.IncInOctets(intfCount.GetInOctets());
        intfEntry.IncInUCastPkts(intfCount.GetInUCastPkts());
        intfEntry.IncInDiscards(intfCount.GetInDiscards());
        intfEntry.IncInErrors(intfCount.GetInErrors());
        intfEntry.IncInUnknownProtos(intfCount.GetInUnknownProtos());
        intfEntry.IncOutOctets(intfCount.GetOutOctets());
        intfEntry.IncOutUCastPkts(intfCount.GetOutUCastPkts());
        intfEntry.IncOutDiscards(intfCount.GetOutDiscards());
        intfEntry.IncOutErrors(intfCount.GetOutErrors());
        intfEntry.IncInMulticastPkts(intfCount.GetInMulticastPkts());
        intfEntry.IncInBroadcastPkts(intfCount.GetInBroadcastPkts());
        intfEntry.IncOutMulticastPkts(intfCount.GetOutMulticastPkts());
        intfEntry.IncOutBroadcastPkts(intfCount.GetOutBroadcastPkts());
        intfEntry.IncHCInOctets(intfCount.GetHCInOctets());
        intfEntry.IncHCInUCastPkts(intfCount.GetHCInUCastPkts());
        intfEntry.IncHCInMulticastPkts(intfCount.GetHCInMulticastPkts());
        intfEntry.IncHCInBroadcastPkts(intfCount.GetHCInBroadcastPkts());
        intfEntry.IncHCOutOctets(intfCount.GetHCOutOctets());
        intfEntry.IncHCOutUCastPkts(intfCount.GetHCOutUCastPkts());
        intfEntry.IncHCOutMulticastPkts(intfCount.GetHCOutMulticastPkts());
        intfEntry.IncHCOutBroadcastPkts(intfCount.GetHCOutBroadcastPkts());
        if (monOptCfg.GetLayerLocked())
        {
            currAdminStatus = CT_SNMP_AdminStatusDown;
            currOperStatus = CT_SNMP_OperStatusDown;
        }
        else
        {
            currAdminStatus = CT_SNMP_AdminStatusUp;
            currOperStatus = CT_SNMP_OperStatusUp;
            if ((almRs.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_RS)) ||
                (almRs.GetStatus(CT_TelAlarmCondition::ALM_LOF_RS)))
            {
                currOperStatus = CT_SNMP_OperStatusDown;
            }
        }
        if ((optCfg.GetFacilityLoopBackEnable()) ||
            (optCfg.GetTerminalLoopBackEnable()))

        {
            currAdminStatus = CT_SNMP_AdminStatusTesting;
            currOperStatus = CT_SNMP_OperStatusTesting;
        }
        if ((!intfEntry.IsFirstSample()) &&
            (currOperStatus != myLastOperStatus))
        {
            SNMP_BbSystemUpTime& sysUpTimeObj = (*mySysUpTimeRegion)[0];
            CT_SNMP_TimeTicks currSysUpTime = sysUpTimeObj.GetSysUpTime();
            intfEntry.SetLastChange(currSysUpTime);
            intfEntry.DisableFirstSampleFlag();
        }
        intfEntry.SetAdminStatus(currAdminStatus);
        intfEntry.SetOperStatus(currOperStatus);
        myLastOperStatus = currOperStatus;
    }
}
