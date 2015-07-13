/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <Monitoring/MON_RmonCounters.h>
#include <SNMP/SNMP_RmonEtherCount.h>


//-----------------------------------------------------------------
SNMP_BbRmonEtherCount::SNMP_BbRmonEtherCount ()
{
}

//-----------------------------------------------------------------
SNMP_BbRmonEtherCount::~SNMP_BbRmonEtherCount ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_BbRmonEtherCount::Update(MON_RmonCounters& theCounter) 
{
    uint32 count = 0;

    theCounter.GetErrorCount(CT_TEL_RMON_DROP_EVENTS, &count);
    myDropEvents.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_OCTETS, &count);
    myOctets.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_PKTS, &count);
    myPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_BROADCAST_PKTS, &count);
    myBroadcastPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_MULTICAST_PKTS, &count);
    myMulticastPkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_CRC_ALIGN_ERRORS, &count);
    myCRCAlignErrors.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_UNDERSIZE_PKTS, &count);
    myUndersizePkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_OVERSIZE_PKTS, &count);
    myOversizePkts.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_FRAGMENTS, &count);
    myFragments.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_JABBERS, &count);
    myJabbers.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_COLLISIONS, &count);
    myCollisions.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_PKTS_64_OCTETS, &count);
    myPkts64.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_PKTS_65_TO_127_OCTETS, &count);
    myPkts65to127.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_PKTS_128_TO_255_OCTETS, &count);
    myPkts128to255.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_PKTS_256_TO_511_OCTETS, &count);
    myPkts256to511.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_PKTS_512_TO_1023_OCTETS, &count);
    myPkts512to1023.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_PKTS_1024_TO_1518_OCTETS, &count);
    myPkts1024to1518.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_DROPPED_FRAMES, &count);
    myDroppedFrames.Update(count);

    theCounter.GetErrorCount(CT_TEL_RMON_HIGH_OCTETS, &count);
    myHighOctets.Update(count);
    theCounter.GetErrorCount(CT_TEL_RMON_HIGH_PKTS, &count);
    myHighPkts.Update(count);
}

//-----------------------------------------------------------------
ostream& SNMP_BbRmonEtherCount::WriteObject( ostream& theStream )
{
    theStream <<  myDropEvents;
    theStream <<  myOctets;
    theStream <<  myPkts;
    theStream <<  myBroadcastPkts;
    theStream <<  myMulticastPkts;
    theStream <<  myCRCAlignErrors;
    theStream <<  myUndersizePkts;
    theStream <<  myOversizePkts;
    theStream <<  myFragments;
    theStream <<  myJabbers;
    theStream <<  myCollisions;
    theStream <<  myPkts64;
    theStream <<  myPkts65to127;
    theStream <<  myPkts128to255;
    theStream <<  myPkts256to511;
    theStream <<  myPkts512to1023;
    theStream <<  myPkts1024to1518;
    theStream <<  myDroppedFrames;

    theStream <<  myHighOctets;
    theStream <<  myHighPkts;
    return theStream;
}

//-----------------------------------------------------------------
istream& SNMP_BbRmonEtherCount::ReadObject( istream& theStream )
{
    theStream >>  myDropEvents;
    theStream >>  myOctets;
    theStream >>  myPkts;
    theStream >>  myBroadcastPkts;
    theStream >>  myMulticastPkts;
    theStream >>  myCRCAlignErrors;
    theStream >>  myUndersizePkts;
    theStream >>  myOversizePkts;
    theStream >>  myFragments;
    theStream >>  myJabbers;
    theStream >>  myCollisions;
    theStream >>  myPkts64;
    theStream >>  myPkts65to127;
    theStream >>  myPkts128to255;
    theStream >>  myPkts256to511;
    theStream >>  myPkts512to1023;
    theStream >>  myPkts1024to1518;
    theStream >>  myDroppedFrames;

    theStream >>  myHighOctets;
    theStream >>  myHighPkts;
    return theStream;
}

//-----------------------------------------------------------------
void SNMP_BbRmonEtherCount::Init(restart_type theRestart)
{
    // Nothing to do for now.
}
