
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:
 TARGET   :
 AUTHOR   :
 DESCRIPTION:
--------------------------------------------------------------------------*/

#include <TimeService/FC_TimeService.h>
#include <CsPii/CSPII_CardIF.h>
#include <SNMP/SNMP_ScRmonEtherStatsProcessor.h>
#include <SNMP/SNMP_RmonConfigController.h>
#include <SNMP/SNMP_RmonRegion.h>
#include <SNMP/SNMP_RmonEtherStatsData.h>
#include <SNMP/SNMP_RmonConfig.h>
#include <SNMP/SNMP_RmonEtherCount.h>
#include <SNMP/SNMP_SystemData.h>

//-----------------------------------------------------------------
SNMP_ScRmonEtherStatsProcessor::SNMP_ScRmonEtherStatsProcessor (SNMP_RmonEtherStatsDataRegion* theDataRegion,
                                                                SNMP_RmonEtherStatsCfgRegion* theCfgRegion,
                                                                SNMP_RmonEtherCountRegion* theCountRegion,
                                                                SNMP_SysUpTimeRegion* theSysUpTimeRegion) :
myDataRegion(theDataRegion),
myCfgRegion(theCfgRegion),
myCountRegion(theCountRegion),
mySysUpTimeRegion(theSysUpTimeRegion)
{
    myCfgCtrl = new SNMP_RmonEtherStatsCfgCtrl(myCfgRegion, myDataRegion, theSysUpTimeRegion);
}

//-----------------------------------------------------------------
SNMP_ScRmonEtherStatsProcessor::~SNMP_ScRmonEtherStatsProcessor ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_ScRmonEtherStatsProcessor::Run (FC_Object* theObject)
{
    size_t loopIndex;
    SNMP_BbRmonEtherCount& etherCount = (*myCountRegion)[0];

    myCfgCtrl->UpdateEtherStatsConfig();
    for (loopIndex = 0; loopIndex < myCfgRegion->Size(); loopIndex++)
    {
        SNMP_BbRmonEtherStatsData& statsEntry = (*myDataRegion)[loopIndex];
        if (statsEntry.IsCollectionEnabled())
        {
            statsEntry.IncDropEvents(etherCount.GetDropEvents());
            statsEntry.IncOctets(etherCount.GetOctets());
            statsEntry.IncPkts(etherCount.GetPkts());
            statsEntry.IncBroadcastPkts(etherCount.GetBroadcastPkts());
            statsEntry.IncMulticastPkts(etherCount.GetMulticastPkts());
            statsEntry.IncCRCAlignErrors(etherCount.GetCRCAlignErrors());
            statsEntry.IncUndersizePkts(etherCount.GetUndersizePkts());
            statsEntry.IncOversizePkts(etherCount.GetOversizePkts());
            statsEntry.IncFragments(etherCount.GetFragments());
            statsEntry.IncJabbers(etherCount.GetJabbers());
            statsEntry.IncCollisions(etherCount.GetCollisions());
            statsEntry.IncPkts64(etherCount.GetPkts64());
            statsEntry.IncPkts65to127(etherCount.GetPkts65to127());
            statsEntry.IncPkts128to255(etherCount.GetPkts128to255());
            statsEntry.IncPkts256to511(etherCount.GetPkts256to511());
            statsEntry.IncPkts512to1023(etherCount.GetPkts512to1023());
            statsEntry.IncPkts1024to1518(etherCount.GetPkts1024to1518());
            statsEntry.IncDroppedFrames(etherCount.GetDroppedFrames());
        }
    }
}
