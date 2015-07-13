//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_RmonCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_RmonCounters::MON_RmonCounters(uint32 theIndex):
    MON_Counters(theIndex),
    myEtherStatsDropEvents(0),
    myEtherStatsOctets(0),
    myEtherStatsPkts(0),
    myEtherStatsBroadcastPkts(0),
    myEtherStatsMulticastPkts(0),
    myEtherStatsCRCAlignErrors(0),
    myEtherStatsUndersizePkts(0),
    myEtherStatsOversizePkts(0),
    myEtherStatsFragments(0),
    myEtherStatsJabbers(0),
    myEtherStatsCollisions(0),
    myEtherStatsPkts64Octets(0),
    myEtherStatsPkts65to127Octets(0),
    myEtherStatsPkts128to255Octets(0),
    myEtherStatsPkts256to511Octets(0),
    myEtherStatsPkts512to1023Octets(0),
    myEtherStatsPkts1024to1518Octets(0),
    myEtherStatsDroppedFrames(0),
    myIfOutMulticastPkts(0),
    myIfOutBroadcastPkts(0),
    myIfInUcastPkts(0),
    myIfInDiscards(0),
    myIfInErrors(0),
    myIfOutOctets(0),
    myIfOutUcastPkts(0),
    myIfOutDiscards(0),
    myIfOutErrors(0),
    myEtherStatsHighDropEvents(0),
    myEtherStatsHighOctets(0),
    myEtherStatsHighPkts(0),
    myEtherStatsHighBroadcastPkts(0),
    myEtherStatsHighMulticastPkts(0),
    myEtherStatsHighCRCAlignErrors(0),
    myEtherStatsHighUndersizePkts(0),
    myEtherStatsHighOversizePkts(0),
    myEtherStatsHighFragments(0),
    myEtherStatsHighJabbers(0),
    myEtherStatsHighCollisions(0),
    myEtherStatsHighPkts64Octets(0),
    myEtherStatsHighPkts65to127Octets(0),
    myEtherStatsHighPkts128to255Octets(0),
    myEtherStatsHighPkts256to511Octets(0),
    myEtherStatsHighPkts512to1023Octets(0),
    myEtherStatsHighPkts1024to1518Octets(0),
    myEtherStatsHighDroppedFrames(0),
    myIfHighOutMulticastPkts(0),
    myIfHighOutBroadcastPkts(0),
    myIfHighInUcastPkts(0),
    myIfHighInDiscards(0),
    myIfHighInErrors(0),
    myIfHighOutOctets(0),
    myIfHighOutUcastPkts(0),
    myIfHighOutDiscards(0),
    myIfHighOutErrors(0)
{
}

MON_RmonCounters::~MON_RmonCounters()
{
}


void MON_RmonCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_RMON_DROP_EVENTS:
        *theCount = myEtherStatsDropEvents;
        break;
    case CT_TEL_RMON_OCTETS:
        *theCount = myEtherStatsOctets;
        break;
    case CT_TEL_RMON_PKTS:
        *theCount = myEtherStatsPkts;
        break;
    case CT_TEL_RMON_BROADCAST_PKTS:
        *theCount = myEtherStatsBroadcastPkts;
        break;
    case CT_TEL_RMON_MULTICAST_PKTS:
        *theCount = myEtherStatsMulticastPkts;
        break;
    case CT_TEL_RMON_CRC_ALIGN_ERRORS:
        *theCount = myEtherStatsCRCAlignErrors;
        break;
    case CT_TEL_RMON_UNDERSIZE_PKTS:
        *theCount = myEtherStatsUndersizePkts;
        break;
    case CT_TEL_RMON_OVERSIZE_PKTS:
        *theCount = myEtherStatsOversizePkts;
        break;
    case CT_TEL_RMON_FRAGMENTS:
        *theCount = myEtherStatsFragments;
        break;
    case CT_TEL_RMON_JABBERS:
        *theCount = myEtherStatsJabbers;
        break;
    case CT_TEL_RMON_COLLISIONS:
        *theCount = myEtherStatsCollisions;
        break;
    case CT_TEL_RMON_PKTS_64_OCTETS:
        *theCount = myEtherStatsPkts64Octets;
        break;
    case CT_TEL_RMON_PKTS_65_TO_127_OCTETS:
        *theCount = myEtherStatsPkts65to127Octets;
        break;
    case CT_TEL_RMON_PKTS_128_TO_255_OCTETS:
        *theCount = myEtherStatsPkts128to255Octets;
        break;
    case CT_TEL_RMON_PKTS_256_TO_511_OCTETS:
        *theCount = myEtherStatsPkts256to511Octets;
        break;
    case CT_TEL_RMON_PKTS_512_TO_1023_OCTETS:
        *theCount = myEtherStatsPkts512to1023Octets;
        break;
    case CT_TEL_RMON_PKTS_1024_TO_1518_OCTETS:
        *theCount = myEtherStatsPkts1024to1518Octets;
        break;
    case CT_TEL_RMON_DROPPED_FRAMES:
        *theCount = myEtherStatsDroppedFrames;
        break;
    case CT_TEL_RMON_IF_OUT_MULTICAST_PKTS:
        *theCount = myIfOutMulticastPkts;
        break;
    case CT_TEL_RMON_IF_OUT_BROADCAST_PKTS:
        *theCount = myIfOutBroadcastPkts;
        break;
    case CT_TEL_RMON_IF_IN_UCAST_PKTS:
        *theCount = myIfInUcastPkts;
        break;
    case CT_TEL_RMON_IF_IN_DISCARDS:
        *theCount = myIfInDiscards;
        break;
    case CT_TEL_RMON_IF_IN_ERRORS:
        *theCount = myIfInErrors;
        break;
    case CT_TEL_RMON_IF_OUT_OCTETS:
        *theCount = myIfOutOctets;
        break;
    case CT_TEL_RMON_IF_OUT_UCAST_PKTS:
        *theCount = myIfOutUcastPkts;
        break;
    case CT_TEL_RMON_IF_OUT_DISCARDS:
        *theCount = myIfOutDiscards;
        break;
    case CT_TEL_RMON_IF_OUT_ERRORS:
        *theCount = myIfOutErrors;
        break;
    // For 64 bits
    case CT_TEL_RMON_HIGH_DROP_EVENTS:
        *theCount = myEtherStatsHighDropEvents;
        break;
    case CT_TEL_RMON_HIGH_OCTETS:
        *theCount = myEtherStatsHighOctets;
        break;
    case CT_TEL_RMON_HIGH_PKTS:
        *theCount = myEtherStatsHighPkts;
        break;
    case CT_TEL_RMON_HIGH_BROADCAST_PKTS:
        *theCount = myEtherStatsHighBroadcastPkts;
        break;
    case CT_TEL_RMON_HIGH_MULTICAST_PKTS:
        *theCount = myEtherStatsHighMulticastPkts;
        break;
    case CT_TEL_RMON_HIGH_CRC_ALIGN_ERRORS:
        *theCount = myEtherStatsHighCRCAlignErrors;
        break;
    case CT_TEL_RMON_HIGH_UNDERSIZE_PKTS:
        *theCount = myEtherStatsHighUndersizePkts;
        break;
    case CT_TEL_RMON_HIGH_OVERSIZE_PKTS:
        *theCount = myEtherStatsHighOversizePkts;
        break;
    case CT_TEL_RMON_HIGH_FRAGMENTS:
        *theCount = myEtherStatsHighFragments;
        break;
    case CT_TEL_RMON_HIGH_JABBERS:
        *theCount = myEtherStatsHighJabbers;
        break;
    case CT_TEL_RMON_HIGH_COLLISIONS:
        *theCount = myEtherStatsHighCollisions;
        break;
    case CT_TEL_RMON_HIGH_PKTS_64_OCTETS:
        *theCount = myEtherStatsHighPkts64Octets;
        break;
    case CT_TEL_RMON_HIGH_PKTS_65_TO_127_OCTETS:
        *theCount = myEtherStatsHighPkts65to127Octets;
        break;
    case CT_TEL_RMON_HIGH_PKTS_128_TO_255_OCTETS:
        *theCount = myEtherStatsHighPkts128to255Octets;
        break;
    case CT_TEL_RMON_HIGH_PKTS_256_TO_511_OCTETS:
        *theCount = myEtherStatsHighPkts256to511Octets;
        break;
    case CT_TEL_RMON_HIGH_PKTS_512_TO_1023_OCTETS:
        *theCount = myEtherStatsHighPkts512to1023Octets;
        break;
    case CT_TEL_RMON_HIGH_PKTS_1024_TO_1518_OCTETS:
        *theCount = myEtherStatsHighPkts1024to1518Octets;
        break;
    case CT_TEL_RMON_HIGH_DROPPED_FRAMES:
        *theCount = myEtherStatsHighDroppedFrames;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_MULTICAST_PKTS:
        *theCount = myIfHighOutMulticastPkts;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_BROADCAST_PKTS:
        *theCount = myIfHighOutBroadcastPkts;
        break;
    case CT_TEL_RMON_HIGH_IF_IN_UCAST_PKTS:
        *theCount = myIfHighInUcastPkts;
        break;
    case CT_TEL_RMON_HIGH_IF_IN_DISCARDS:
        *theCount = myIfHighInDiscards;
        break;
    case CT_TEL_RMON_HIGH_IF_IN_ERRORS:
        *theCount = myIfHighInErrors;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_OCTETS:
        *theCount = myIfHighOutOctets;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_UCAST_PKTS:
        *theCount = myIfHighOutUcastPkts;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_DISCARDS:
        *theCount = myIfHighOutDiscards;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_ERRORS:
        *theCount = myIfHighOutErrors;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_RmonCounters: Unsupported register");
        break;
    }
}

void MON_RmonCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_RMON_DROP_EVENTS:
        myEtherStatsDropEvents = theCount;
        break;
    case CT_TEL_RMON_OCTETS:
        myEtherStatsOctets = theCount;
        break;
    case CT_TEL_RMON_PKTS:
        myEtherStatsPkts = theCount;
        break;
    case CT_TEL_RMON_BROADCAST_PKTS:
        myEtherStatsBroadcastPkts = theCount;
        break;
    case CT_TEL_RMON_MULTICAST_PKTS:
        myEtherStatsMulticastPkts = theCount;
        break;
    case CT_TEL_RMON_CRC_ALIGN_ERRORS:
        myEtherStatsCRCAlignErrors = theCount;
        break;
    case CT_TEL_RMON_UNDERSIZE_PKTS:
        myEtherStatsUndersizePkts = theCount;
        break;
    case CT_TEL_RMON_OVERSIZE_PKTS:
        myEtherStatsOversizePkts = theCount;
        break;
    case CT_TEL_RMON_FRAGMENTS:
        myEtherStatsFragments = theCount;
        break;
    case CT_TEL_RMON_JABBERS:
        myEtherStatsJabbers = theCount;
        break;
    case CT_TEL_RMON_COLLISIONS:
        myEtherStatsCollisions = theCount;
        break;
    case CT_TEL_RMON_PKTS_64_OCTETS:
        myEtherStatsPkts64Octets = theCount;
        break;
    case CT_TEL_RMON_PKTS_65_TO_127_OCTETS:
        myEtherStatsPkts65to127Octets = theCount;
        break;
    case CT_TEL_RMON_PKTS_128_TO_255_OCTETS:
        myEtherStatsPkts128to255Octets = theCount;
        break;
    case CT_TEL_RMON_PKTS_256_TO_511_OCTETS:
        myEtherStatsPkts256to511Octets = theCount;
        break;
    case CT_TEL_RMON_PKTS_512_TO_1023_OCTETS:
        myEtherStatsPkts512to1023Octets = theCount;
        break;
    case CT_TEL_RMON_PKTS_1024_TO_1518_OCTETS:
        myEtherStatsPkts1024to1518Octets = theCount;
        break;
    case CT_TEL_RMON_DROPPED_FRAMES:
        myEtherStatsDroppedFrames = theCount;
        break;
    case CT_TEL_RMON_IF_OUT_MULTICAST_PKTS:
        myIfOutMulticastPkts = theCount;
        break;
    case CT_TEL_RMON_IF_OUT_BROADCAST_PKTS:
        myIfOutBroadcastPkts = theCount;
        break;
    case CT_TEL_RMON_IF_IN_UCAST_PKTS:
        myIfInUcastPkts = theCount;
        break;
    case CT_TEL_RMON_IF_IN_DISCARDS:
        myIfInDiscards = theCount;
        break;
    case CT_TEL_RMON_IF_IN_ERRORS:
        myIfInErrors = theCount;
        break;
    case CT_TEL_RMON_IF_OUT_OCTETS:
        myIfOutOctets = theCount;
        break;
    case CT_TEL_RMON_IF_OUT_UCAST_PKTS:
        myIfOutUcastPkts = theCount;
        break;
    case CT_TEL_RMON_IF_OUT_DISCARDS:
        myIfOutDiscards = theCount;
        break;
    case CT_TEL_RMON_IF_OUT_ERRORS:
        myIfOutErrors = theCount;
        break;
    // For 64 bits
    case CT_TEL_RMON_HIGH_DROP_EVENTS:
        myEtherStatsHighDropEvents = theCount;
        break;
    case CT_TEL_RMON_HIGH_OCTETS:
        myEtherStatsHighOctets = theCount;
        break;
    case CT_TEL_RMON_HIGH_PKTS:
        myEtherStatsHighPkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_BROADCAST_PKTS:
        myEtherStatsHighBroadcastPkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_MULTICAST_PKTS:
        myEtherStatsHighMulticastPkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_CRC_ALIGN_ERRORS:
        myEtherStatsHighCRCAlignErrors = theCount;
        break;
    case CT_TEL_RMON_HIGH_UNDERSIZE_PKTS:
        myEtherStatsHighUndersizePkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_OVERSIZE_PKTS:
        myEtherStatsHighOversizePkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_FRAGMENTS:
        myEtherStatsHighFragments = theCount;
        break;
    case CT_TEL_RMON_HIGH_JABBERS:
        myEtherStatsHighJabbers = theCount;
        break;
    case CT_TEL_RMON_HIGH_COLLISIONS:
        myEtherStatsHighCollisions = theCount;
        break;
    case CT_TEL_RMON_HIGH_PKTS_64_OCTETS:
        myEtherStatsHighPkts64Octets = theCount;
        break;
    case CT_TEL_RMON_HIGH_PKTS_65_TO_127_OCTETS:
        myEtherStatsHighPkts65to127Octets = theCount;
        break;
    case CT_TEL_RMON_HIGH_PKTS_128_TO_255_OCTETS:
        myEtherStatsHighPkts128to255Octets = theCount;
        break;
    case CT_TEL_RMON_HIGH_PKTS_256_TO_511_OCTETS:
        myEtherStatsHighPkts256to511Octets = theCount;
        break;
    case CT_TEL_RMON_HIGH_PKTS_512_TO_1023_OCTETS:
        myEtherStatsHighPkts512to1023Octets = theCount;
        break;
    case CT_TEL_RMON_HIGH_PKTS_1024_TO_1518_OCTETS:
        myEtherStatsHighPkts1024to1518Octets = theCount;
        break;
    case CT_TEL_RMON_HIGH_DROPPED_FRAMES:
        myEtherStatsHighDroppedFrames = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_MULTICAST_PKTS:
        myIfHighOutMulticastPkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_BROADCAST_PKTS:
        myIfHighOutBroadcastPkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_IN_UCAST_PKTS:
        myIfHighInUcastPkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_IN_DISCARDS:
        myIfHighInDiscards = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_IN_ERRORS:
        myIfHighInErrors = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_OCTETS:
        myIfHighOutOctets = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_UCAST_PKTS:
        myIfHighOutUcastPkts = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_DISCARDS:
        myIfHighOutDiscards = theCount;
        break;
    case CT_TEL_RMON_HIGH_IF_OUT_ERRORS:
        myIfHighOutErrors = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_RmonCounters: Unsupported register");
        break;
    }
}


void MON_RmonCounters::Reset(void)
{
    MON_Counters::Reset();
    myEtherStatsDropEvents = 0;
    myEtherStatsOctets = 0;
    myEtherStatsPkts = 0;
    myEtherStatsBroadcastPkts = 0;
    myEtherStatsMulticastPkts = 0;
    myEtherStatsCRCAlignErrors = 0;
    myEtherStatsUndersizePkts = 0;
    myEtherStatsOversizePkts = 0;
    myEtherStatsFragments = 0;
    myEtherStatsJabbers = 0;
    myEtherStatsCollisions = 0;
    myEtherStatsPkts64Octets = 0;
    myEtherStatsPkts65to127Octets = 0;
    myEtherStatsPkts128to255Octets = 0;
    myEtherStatsPkts256to511Octets = 0;
    myEtherStatsPkts512to1023Octets = 0;
    myEtherStatsPkts1024to1518Octets = 0;
    myEtherStatsDroppedFrames = 0;
    myIfOutMulticastPkts = 0;
    myIfOutBroadcastPkts = 0;
    myIfInUcastPkts = 0;
    myIfInDiscards = 0;
    myIfInErrors = 0;
    myIfOutOctets = 0;
    myIfOutUcastPkts = 0;
    myIfOutDiscards = 0;
    myIfOutErrors = 0;
    // For 64 bits
    myEtherStatsHighDropEvents = 0;
    myEtherStatsHighOctets = 0;
    myEtherStatsHighPkts = 0;
    myEtherStatsHighBroadcastPkts = 0;
    myEtherStatsHighMulticastPkts = 0;
    myEtherStatsHighCRCAlignErrors = 0;
    myEtherStatsHighUndersizePkts = 0;
    myEtherStatsHighOversizePkts = 0;
    myEtherStatsHighFragments = 0;
    myEtherStatsHighJabbers = 0;
    myEtherStatsHighCollisions = 0;
    myEtherStatsHighPkts64Octets = 0;
    myEtherStatsHighPkts65to127Octets = 0;
    myEtherStatsHighPkts128to255Octets = 0;
    myEtherStatsHighPkts256to511Octets = 0;
    myEtherStatsHighPkts512to1023Octets = 0;
    myEtherStatsHighPkts1024to1518Octets = 0;
    myEtherStatsHighDroppedFrames = 0;
    myIfHighOutMulticastPkts = 0;
    myIfHighOutBroadcastPkts = 0;
    myIfHighInUcastPkts = 0;
    myIfHighInDiscards = 0;
    myIfHighInErrors = 0;
    myIfHighOutOctets = 0;
    myIfHighOutUcastPkts = 0;
    myIfHighOutDiscards = 0;
    myIfHighOutErrors = 0;
}

ostream& MON_RmonCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myEtherStatsDropEvents);
    theStream   << FC_InsertVar(myEtherStatsOctets);
    theStream   << FC_InsertVar(myEtherStatsPkts);
    theStream   << FC_InsertVar(myEtherStatsBroadcastPkts);
    theStream   << FC_InsertVar(myEtherStatsMulticastPkts);
    theStream   << FC_InsertVar(myEtherStatsCRCAlignErrors);
    theStream   << FC_InsertVar(myEtherStatsUndersizePkts);
    theStream   << FC_InsertVar(myEtherStatsOversizePkts);
    theStream   << FC_InsertVar(myEtherStatsFragments);
    theStream   << FC_InsertVar(myEtherStatsJabbers);
    theStream   << FC_InsertVar(myEtherStatsCollisions);
    theStream   << FC_InsertVar(myEtherStatsPkts64Octets);
    theStream   << FC_InsertVar(myEtherStatsPkts65to127Octets);
    theStream   << FC_InsertVar(myEtherStatsPkts128to255Octets);
    theStream   << FC_InsertVar(myEtherStatsPkts256to511Octets);
    theStream   << FC_InsertVar(myEtherStatsPkts512to1023Octets);
    theStream   << FC_InsertVar(myEtherStatsPkts1024to1518Octets);
    theStream   << FC_InsertVar(myEtherStatsDroppedFrames);
    theStream   << FC_InsertVar(myIfOutMulticastPkts);
    theStream   << FC_InsertVar(myIfOutBroadcastPkts);
    theStream   << FC_InsertVar(myIfInUcastPkts);
    theStream   << FC_InsertVar(myIfInDiscards);
    theStream   << FC_InsertVar(myIfInErrors);
    theStream   << FC_InsertVar(myIfOutOctets);
    theStream   << FC_InsertVar(myIfOutUcastPkts);
    theStream   << FC_InsertVar(myIfOutDiscards);
    theStream   << FC_InsertVar(myIfOutErrors);
    // For 64 bits
    theStream   << FC_InsertVar(myEtherStatsHighDropEvents);
    theStream   << FC_InsertVar(myEtherStatsHighOctets);
    theStream   << FC_InsertVar(myEtherStatsHighPkts);
    theStream   << FC_InsertVar(myEtherStatsHighBroadcastPkts);
    theStream   << FC_InsertVar(myEtherStatsHighMulticastPkts);
    theStream   << FC_InsertVar(myEtherStatsHighCRCAlignErrors);
    theStream   << FC_InsertVar(myEtherStatsHighUndersizePkts);
    theStream   << FC_InsertVar(myEtherStatsHighOversizePkts);
    theStream   << FC_InsertVar(myEtherStatsHighFragments);
    theStream   << FC_InsertVar(myEtherStatsHighJabbers);
    theStream   << FC_InsertVar(myEtherStatsHighCollisions);
    theStream   << FC_InsertVar(myEtherStatsHighPkts64Octets);
    theStream   << FC_InsertVar(myEtherStatsHighPkts65to127Octets);
    theStream   << FC_InsertVar(myEtherStatsHighPkts128to255Octets);
    theStream   << FC_InsertVar(myEtherStatsHighPkts256to511Octets);
    theStream   << FC_InsertVar(myEtherStatsHighPkts512to1023Octets);
    theStream   << FC_InsertVar(myEtherStatsHighPkts1024to1518Octets);
    theStream   << FC_InsertVar(myEtherStatsHighDroppedFrames);
    theStream   << FC_InsertVar(myIfHighOutMulticastPkts);
    theStream   << FC_InsertVar(myIfHighOutBroadcastPkts);
    theStream   << FC_InsertVar(myIfHighInUcastPkts);
    theStream   << FC_InsertVar(myIfHighInDiscards);
    theStream   << FC_InsertVar(myIfHighInErrors);
    theStream   << FC_InsertVar(myIfHighOutOctets);
    theStream   << FC_InsertVar(myIfHighOutUcastPkts);
    theStream   << FC_InsertVar(myIfHighOutDiscards);
    theStream   << FC_InsertVar(myIfHighOutErrors);
    return theStream;
}

istream& MON_RmonCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myEtherStatsDropEvents);
    theStream   >> FC_ExtractVar(myEtherStatsOctets);
    theStream   >> FC_ExtractVar(myEtherStatsPkts);
    theStream   >> FC_ExtractVar(myEtherStatsBroadcastPkts);
    theStream   >> FC_ExtractVar(myEtherStatsMulticastPkts);
    theStream   >> FC_ExtractVar(myEtherStatsCRCAlignErrors);
    theStream   >> FC_ExtractVar(myEtherStatsUndersizePkts);
    theStream   >> FC_ExtractVar(myEtherStatsOversizePkts);
    theStream   >> FC_ExtractVar(myEtherStatsFragments);
    theStream   >> FC_ExtractVar(myEtherStatsJabbers);
    theStream   >> FC_ExtractVar(myEtherStatsCollisions);
    theStream   >> FC_ExtractVar(myEtherStatsPkts64Octets);
    theStream   >> FC_ExtractVar(myEtherStatsPkts65to127Octets);
    theStream   >> FC_ExtractVar(myEtherStatsPkts128to255Octets);
    theStream   >> FC_ExtractVar(myEtherStatsPkts256to511Octets);
    theStream   >> FC_ExtractVar(myEtherStatsPkts512to1023Octets);
    theStream   >> FC_ExtractVar(myEtherStatsPkts1024to1518Octets);
    theStream   >> FC_ExtractVar(myEtherStatsDroppedFrames);
    theStream   >> FC_ExtractVar(myIfOutMulticastPkts);
    theStream   >> FC_ExtractVar(myIfOutBroadcastPkts);
    theStream   >> FC_ExtractVar(myIfInUcastPkts);
    theStream   >> FC_ExtractVar(myIfInDiscards);
    theStream   >> FC_ExtractVar(myIfInErrors);
    theStream   >> FC_ExtractVar(myIfOutOctets);
    theStream   >> FC_ExtractVar(myIfOutUcastPkts);
    theStream   >> FC_ExtractVar(myIfOutDiscards);
    theStream   >> FC_ExtractVar(myIfOutErrors);
    // For 64 bits
    theStream   >> FC_ExtractVar(myEtherStatsHighDropEvents);
    theStream   >> FC_ExtractVar(myEtherStatsHighOctets);
    theStream   >> FC_ExtractVar(myEtherStatsHighPkts);
    theStream   >> FC_ExtractVar(myEtherStatsHighBroadcastPkts);
    theStream   >> FC_ExtractVar(myEtherStatsHighMulticastPkts);
    theStream   >> FC_ExtractVar(myEtherStatsHighCRCAlignErrors);
    theStream   >> FC_ExtractVar(myEtherStatsHighUndersizePkts);
    theStream   >> FC_ExtractVar(myEtherStatsHighOversizePkts);
    theStream   >> FC_ExtractVar(myEtherStatsHighFragments);
    theStream   >> FC_ExtractVar(myEtherStatsHighJabbers);
    theStream   >> FC_ExtractVar(myEtherStatsHighCollisions);
    theStream   >> FC_ExtractVar(myEtherStatsHighPkts64Octets);
    theStream   >> FC_ExtractVar(myEtherStatsHighPkts65to127Octets);
    theStream   >> FC_ExtractVar(myEtherStatsHighPkts128to255Octets);
    theStream   >> FC_ExtractVar(myEtherStatsHighPkts256to511Octets);
    theStream   >> FC_ExtractVar(myEtherStatsHighPkts512to1023Octets);
    theStream   >> FC_ExtractVar(myEtherStatsHighPkts1024to1518Octets);
    theStream   >> FC_ExtractVar(myEtherStatsHighDroppedFrames);
    theStream   >> FC_ExtractVar(myIfHighOutMulticastPkts);
    theStream   >> FC_ExtractVar(myIfHighOutBroadcastPkts);
    theStream   >> FC_ExtractVar(myIfHighInUcastPkts);
    theStream   >> FC_ExtractVar(myIfHighInDiscards);
    theStream   >> FC_ExtractVar(myIfHighInErrors);
    theStream   >> FC_ExtractVar(myIfHighOutOctets);
    theStream   >> FC_ExtractVar(myIfHighOutUcastPkts);
    theStream   >> FC_ExtractVar(myIfHighOutDiscards);
    theStream   >> FC_ExtractVar(myIfHighOutErrors);
    return theStream;
}

FC_Stream& MON_RmonCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myEtherStatsDropEvents;
    theStream   << myEtherStatsOctets;
    theStream   << myEtherStatsPkts;
    theStream   << myEtherStatsBroadcastPkts;
    theStream   << myEtherStatsMulticastPkts;
    theStream   << myEtherStatsCRCAlignErrors;
    theStream   << myEtherStatsUndersizePkts;
    theStream   << myEtherStatsOversizePkts;
    theStream   << myEtherStatsFragments;
    theStream   << myEtherStatsJabbers;
    theStream   << myEtherStatsCollisions;
    theStream   << myEtherStatsPkts64Octets;
    theStream   << myEtherStatsPkts65to127Octets;
    theStream   << myEtherStatsPkts128to255Octets;
    theStream   << myEtherStatsPkts256to511Octets;
    theStream   << myEtherStatsPkts512to1023Octets;
    theStream   << myEtherStatsPkts1024to1518Octets;
    theStream   << myEtherStatsDroppedFrames;
    theStream   << myIfOutMulticastPkts;
    theStream   << myIfOutBroadcastPkts;
    theStream   << myIfInUcastPkts;
    theStream   << myIfInDiscards;
    theStream   << myIfInErrors;
    theStream   << myIfOutOctets;
    theStream   << myIfOutUcastPkts;
    theStream   << myIfOutDiscards;
    theStream   << myIfOutErrors;
    // For 64 bits
    theStream   << myEtherStatsHighDropEvents;
    theStream   << myEtherStatsHighOctets;
    theStream   << myEtherStatsHighPkts;
    theStream   << myEtherStatsHighBroadcastPkts;
    theStream   << myEtherStatsHighMulticastPkts;
    theStream   << myEtherStatsHighCRCAlignErrors;
    theStream   << myEtherStatsHighUndersizePkts;
    theStream   << myEtherStatsHighOversizePkts;
    theStream   << myEtherStatsHighFragments;
    theStream   << myEtherStatsHighJabbers;
    theStream   << myEtherStatsHighCollisions;
    theStream   << myEtherStatsHighPkts64Octets;
    theStream   << myEtherStatsHighPkts65to127Octets;
    theStream   << myEtherStatsHighPkts128to255Octets;
    theStream   << myEtherStatsHighPkts256to511Octets;
    theStream   << myEtherStatsHighPkts512to1023Octets;
    theStream   << myEtherStatsHighPkts1024to1518Octets;
    theStream   << myEtherStatsHighDroppedFrames;
    theStream   << myIfHighOutMulticastPkts;
    theStream   << myIfHighOutBroadcastPkts;
    theStream   << myIfHighInUcastPkts;
    theStream   << myIfHighInDiscards;
    theStream   << myIfHighInErrors;
    theStream   << myIfHighOutOctets;
    theStream   << myIfHighOutUcastPkts;
    theStream   << myIfHighOutDiscards;
    theStream   << myIfHighOutErrors;
    return theStream;
}

FC_Stream& MON_RmonCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myEtherStatsDropEvents;
    theStream   >> myEtherStatsOctets;
    theStream   >> myEtherStatsPkts;
    theStream   >> myEtherStatsBroadcastPkts;
    theStream   >> myEtherStatsMulticastPkts;
    theStream   >> myEtherStatsCRCAlignErrors;
    theStream   >> myEtherStatsUndersizePkts;
    theStream   >> myEtherStatsOversizePkts;
    theStream   >> myEtherStatsFragments;
    theStream   >> myEtherStatsJabbers;
    theStream   >> myEtherStatsCollisions;
    theStream   >> myEtherStatsPkts64Octets;
    theStream   >> myEtherStatsPkts65to127Octets;
    theStream   >> myEtherStatsPkts128to255Octets;
    theStream   >> myEtherStatsPkts256to511Octets;
    theStream   >> myEtherStatsPkts512to1023Octets;
    theStream   >> myEtherStatsPkts1024to1518Octets;
    theStream   >> myEtherStatsDroppedFrames;
    theStream   >> myIfOutMulticastPkts;
    theStream   >> myIfOutBroadcastPkts;
    theStream   >> myIfInUcastPkts;
    theStream   >> myIfInDiscards;
    theStream   >> myIfInErrors;
    theStream   >> myIfOutOctets;
    theStream   >> myIfOutUcastPkts;
    theStream   >> myIfOutDiscards;
    theStream   >> myIfOutErrors;
    // For 64 bits
    theStream   >> myEtherStatsHighDropEvents;
    theStream   >> myEtherStatsHighOctets;
    theStream   >> myEtherStatsHighPkts;
    theStream   >> myEtherStatsHighBroadcastPkts;
    theStream   >> myEtherStatsHighMulticastPkts;
    theStream   >> myEtherStatsHighCRCAlignErrors;
    theStream   >> myEtherStatsHighUndersizePkts;
    theStream   >> myEtherStatsHighOversizePkts;
    theStream   >> myEtherStatsHighFragments;
    theStream   >> myEtherStatsHighJabbers;
    theStream   >> myEtherStatsHighCollisions;
    theStream   >> myEtherStatsHighPkts64Octets;
    theStream   >> myEtherStatsHighPkts65to127Octets;
    theStream   >> myEtherStatsHighPkts128to255Octets;
    theStream   >> myEtherStatsHighPkts256to511Octets;
    theStream   >> myEtherStatsHighPkts512to1023Octets;
    theStream   >> myEtherStatsHighPkts1024to1518Octets;
    theStream   >> myEtherStatsHighDroppedFrames;
    theStream   >> myIfHighOutMulticastPkts;
    theStream   >> myIfHighOutBroadcastPkts;
    theStream   >> myIfHighInUcastPkts;
    theStream   >> myIfHighInDiscards;
    theStream   >> myIfHighInErrors;
    theStream   >> myIfHighOutOctets;
    theStream   >> myIfHighOutUcastPkts;
    theStream   >> myIfHighOutDiscards;
    theStream   >> myIfHighOutErrors;

    return theStream;

}

void MON_RmonCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "RMON    - DROP_EVENTS Count                 = " << myEtherStatsDropEvents << endl;
    theStream   << "RMON    - HIGH DROP_EVENTS Count            = " << myEtherStatsHighDropEvents << endl;
    theStream   << "RMON    - OCTETS Count                      = " << myEtherStatsOctets << endl;
    theStream   << "RMON    - HIGH OCTETS Count                 = " << myEtherStatsHighOctets << endl;
    theStream   << "RMON    - PKTS Count                        = " << myEtherStatsPkts << endl;
    theStream   << "RMON    - HIGH PKTS Count                   = " << myEtherStatsHighPkts << endl;
    theStream   << "RMON    - BROADCAST_PKTS Count              = " << myEtherStatsBroadcastPkts << endl;
    theStream   << "RMON    - HIGH BROADCAST_PKTS Count         = " << myEtherStatsHighBroadcastPkts << endl;
    theStream   << "RMON    - MULTICAST_PKTS Count              = " << myEtherStatsMulticastPkts << endl;
    theStream   << "RMON    - HIGH MULTICAST_PKTS Count         = " << myEtherStatsHighMulticastPkts << endl;
    theStream   << "RMON    - CRC_ALIGN_ERRORS Count            = " << myEtherStatsCRCAlignErrors << endl;
    theStream   << "RMON    - HIGH CRC_ALIGN_ERRORS Count       = " << myEtherStatsHighCRCAlignErrors << endl;
    theStream   << "RMON    - UNDERSIZE_PKTS Count              = " << myEtherStatsUndersizePkts << endl;
    theStream   << "RMON    - HIGH UNDERSIZE_PKTS Count         = " << myEtherStatsHighUndersizePkts << endl;
    theStream   << "RMON    - OVERSIZE_PKTS Count               = " << myEtherStatsOversizePkts << endl;
    theStream   << "RMON    - HIGH OVERSIZE_PKTS Count          = " << myEtherStatsHighOversizePkts << endl;
    theStream   << "RMON    - FRAGMENTS Count                   = " << myEtherStatsFragments << endl;
    theStream   << "RMON    - HIGH FRAGMENTS Count              = " << myEtherStatsHighFragments << endl;
    theStream   << "RMON    - JABBERS Count                     = " << myEtherStatsJabbers << endl;
    theStream   << "RMON    - HIGH JABBERS Count                = " << myEtherStatsHighJabbers << endl;
    theStream   << "RMON    - COLLISIONS Count                  = " << myEtherStatsCollisions << endl;
    theStream   << "RMON    - HIGH COLLISIONS Count             = " << myEtherStatsHighCollisions << endl;
    theStream   << "RMON    - PKTS_64_OCTETS Count              = " << myEtherStatsPkts64Octets << endl;
    theStream   << "RMON    - HIGH PKTS_64_OCTETS Count         = " << myEtherStatsHighPkts64Octets << endl;
    theStream   << "RMON    - PKTS_65_TO_127_OCTETS Count       = " << myEtherStatsPkts65to127Octets << endl;
    theStream   << "RMON    - HIGH PKTS_65_TO_127_OCTETS Count  = " << myEtherStatsHighPkts65to127Octets << endl;
    theStream   << "RMON    - PKTS_128_TO_255_OCTETS Count      = " << myEtherStatsPkts128to255Octets << endl;
    theStream   << "RMON    - HIGH PKTS_128_TO_255_OCTETS Count = " << myEtherStatsHighPkts128to255Octets << endl;
    theStream   << "RMON    - PKTS_256_TO_511_OCTETS Count      = " << myEtherStatsPkts256to511Octets << endl;
    theStream   << "RMON    - HIGH PKTS_256_TO_511_OCTETS Count = " << myEtherStatsHighPkts256to511Octets << endl;
    theStream   << "RMON    - PKTS_512_TO_1023_OCTETS Count     = " << myEtherStatsPkts512to1023Octets << endl;
    theStream   << "RMON    - HIGH PKTS_512_TO_1023_OCTETS Count= " << myEtherStatsHighPkts512to1023Octets << endl;
    theStream   << "RMON    - PKTS_1024_TO_1518_OCTETS Count    = " << myEtherStatsPkts1024to1518Octets << endl;
    theStream   << "RMON    - HIGH PKTS_1024_TO_1518_OCTETS Cnt = " << myEtherStatsHighPkts1024to1518Octets << endl;
    theStream   << "RMON    - DROPPED_FRAMES Count              = " << myEtherStatsDroppedFrames << endl;
    theStream   << "RMON    - HIGH DROPPED_FRAMES Count         = " << myEtherStatsHighDroppedFrames << endl;
    theStream   << "RMON    - IF_OUT_MULTICAST_PKTS Count       = " << myIfOutMulticastPkts << endl;
    theStream   << "RMON    - HIGH IF_OUT_MULTICAST_PKTS Count  = " << myIfHighOutMulticastPkts << endl;
    theStream   << "RMON    - IF_OUT_BROADCAST_PKTS Count       = " << myIfOutBroadcastPkts << endl;
    theStream   << "RMON    - HIGH IF_OUT_BROADCAST_PKTS Count  = " << myIfHighOutBroadcastPkts << endl;
    theStream   << "RMON    - IF_IN_UCAST_PKTS Count            = " << myIfInUcastPkts << endl;
    theStream   << "RMON    - HIGH IF_IN_UCAST_PKTS Count       = " << myIfHighInUcastPkts << endl;
    theStream   << "RMON    - IF_IN_DISCARDS Count              = " << myIfInDiscards << endl;
    theStream   << "RMON    - HIGH IF_IN_DISCARDS Count         = " << myIfHighInDiscards << endl;
    theStream   << "RMON    - IF_IN_ERRORS Count                = " << myIfInErrors << endl;
    theStream   << "RMON    - HIGH IF_IN_ERRORS Count           = " << myIfHighInErrors << endl;
    theStream   << "RMON    - IF_OUT_OCTETS Count               = " << myIfOutOctets << endl;
    theStream   << "RMON    - HIGH IF_OUT_OCTETS Count          = " << myIfHighOutOctets << endl;
    theStream   << "RMON    - IF_OUT_UCAST_PKTS Count           = " << myIfOutUcastPkts << endl;
    theStream   << "RMON    - HIGH IF_OUT_UCAST_PKTS Count      = " << myIfHighOutUcastPkts << endl;
    theStream   << "RMON    - IF_OUT_DISCARDS Count             = " << myIfOutDiscards << endl;
    theStream   << "RMON    - HIGH IF_OUT_DISCARDS Count        = " << myIfHighOutDiscards << endl;
    theStream   << "RMON    - IF_OUT_ERRORS Count               = " << myIfOutErrors << endl;
    theStream   << "RMON    - HIGH IF_OUT_ERRORS Count          = " << myIfHighOutErrors << endl;

}
