/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <PII_TickTimer.h>
#include <SNMP/SNMP_RmonEtherStatsReqAction.h>
#include <SNMP/SNMP_RmonEtherStatsData.h>
#include <SNMP/SNMP_RmonRequest.h>
#include <SNMP/SNMP_ScRmonSubApplication.h>
#include <CommonTypes/CT_SNMP_RmonEtherFileBuffers.h>


PMD_SnmpEtherStatsBuffer  PmdEtherStatsBuffer;    

//-----------------------------------------------------------------
// Class constructor.
SNMP_ScRmonEtherStatsReqAction::SNMP_ScRmonEtherStatsReqAction (SNMP_RmonEtherStatsDataRegion*  theDataRegion,
                                 SNMP_RmonEtherStatsReqRegion*  theReqRegion,
                                 SNMP_ScRmonSubApplication * theScSubApp) :
myReqRegion(theReqRegion),
myDataRegion(theDataRegion),
myScSubApp(theScSubApp)
{
}

//-----------------------------------------------------------------
SNMP_ScRmonEtherStatsReqAction::~SNMP_ScRmonEtherStatsReqAction ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_ScRmonEtherStatsReqAction::Run (FC_Object* theObject) 
{
    //Get all the stats data for each active port
    int port;
    int numactiveIndex =0;

    SNMP_EtherFileBuffer * myPMDFileBuffer = myScSubApp->GetFileBufferPtr();
    for (port =0; port < CT_SNMP_MAX_RMON_STATS_INDEX; port++)
    { 
        try
        {
            SNMP_BbRmonEtherStatsData * statsData = reinterpret_cast<SNMP_BbRmonEtherStatsData*>(&(*myDataRegion)[port]);
            //if the index is defined then get data members
            if (statsData->GetIndex())
            {
                numactiveIndex++;
                PmdEtherStatsBuffer.index = statsData->GetIndex();
                PmdEtherStatsBuffer.dropEvents = statsData->GetDropEvents();
                PmdEtherStatsBuffer.octets = statsData->GetOctets();
                PmdEtherStatsBuffer.pkts = statsData->GetPkts();
                PmdEtherStatsBuffer.broadcastPkts = statsData->GetBroadcastPkts();
                PmdEtherStatsBuffer.multicastPkts = statsData->GetMulticastPkts();
                PmdEtherStatsBuffer.CRCalignErrors = statsData->GetCRCAlignErrors();
                PmdEtherStatsBuffer.undersizePkts = statsData->GetUndersizePkts();
                PmdEtherStatsBuffer.oversizePkts = statsData->GetOversizePkts();
                PmdEtherStatsBuffer.fragments = statsData->GetFragments();
                PmdEtherStatsBuffer.jabbers = statsData->GetJabbers();
                PmdEtherStatsBuffer.collisions = statsData->GetCollisions();
                PmdEtherStatsBuffer.pkts64 = statsData->GetPkts64();
                PmdEtherStatsBuffer.pkts65to127 = statsData->GetPkts65to127();
                PmdEtherStatsBuffer.pkts128to255 = statsData->GetPkts128to255();
                PmdEtherStatsBuffer.pkts256to511 = statsData->GetPkts256to511();
                PmdEtherStatsBuffer.pkts512to1023 = statsData->GetPkts512to1023();
                PmdEtherStatsBuffer.pkts1024to1518 = statsData->GetPkts1024to1518();
                PmdEtherStatsBuffer.droppedFrames = statsData->GetDroppedFrames();
                PmdEtherStatsBuffer.createTime = statsData->GetCreateTime();
                //copy the row to the file
                myPMDFileBuffer->CopyStatsData(&PmdEtherStatsBuffer.index,20*sizeof(int),port);
            }
        }
        catch(...)
        {
        }
    
    }
    myPMDFileBuffer->WriteStatsIndex(numactiveIndex);
}
