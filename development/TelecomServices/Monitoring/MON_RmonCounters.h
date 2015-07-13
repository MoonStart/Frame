//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_RMONCOUNTERS_H
#define MON_RMONCOUNTERS_H

#include "MON_Object.h"
#include "MON_Counters.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the counters for the 
//RMON layer.
class MON_RmonCounters :public MON_Counters
{
public:

    //Constructor.
    MON_RmonCounters(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_RmonCounters(void);

    void Reset();

    virtual void Display(FC_Stream& theStream);

    void GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const;

    void SetErrorCount(CT_TEL_Register theRegister, uint32 theCount);

protected:

    virtual ostream& WriteObject( ostream& theStream );

    virtual istream& ReadObject( istream& theStream );

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // The current Rmon Counts
    uint32 myEtherStatsDropEvents;
    uint32 myEtherStatsOctets;
    uint32 myEtherStatsPkts;
    uint32 myEtherStatsBroadcastPkts;
    uint32 myEtherStatsMulticastPkts;
    uint32 myEtherStatsCRCAlignErrors;
    uint32 myEtherStatsUndersizePkts;
    uint32 myEtherStatsOversizePkts;
    uint32 myEtherStatsFragments;
    uint32 myEtherStatsJabbers;
    uint32 myEtherStatsCollisions;
    uint32 myEtherStatsPkts64Octets;
    uint32 myEtherStatsPkts65to127Octets;
    uint32 myEtherStatsPkts128to255Octets;
    uint32 myEtherStatsPkts256to511Octets;
    uint32 myEtherStatsPkts512to1023Octets;
    uint32 myEtherStatsPkts1024to1518Octets;
    uint32 myEtherStatsDroppedFrames;
    uint32 myIfOutMulticastPkts;
    uint32 myIfOutBroadcastPkts;
    uint32 myIfInUcastPkts;
    uint32 myIfInDiscards;
    uint32 myIfInErrors;
    uint32 myIfOutOctets;
    uint32 myIfOutUcastPkts;
    uint32 myIfOutDiscards;
    uint32 myIfOutErrors;

    // For 64 bit Rmon Counts
    uint32 myEtherStatsHighDropEvents;
    uint32 myEtherStatsHighOctets;
    uint32 myEtherStatsHighPkts;
    uint32 myEtherStatsHighBroadcastPkts;
    uint32 myEtherStatsHighMulticastPkts;
    uint32 myEtherStatsHighCRCAlignErrors;
    uint32 myEtherStatsHighUndersizePkts;
    uint32 myEtherStatsHighOversizePkts;
    uint32 myEtherStatsHighFragments;
    uint32 myEtherStatsHighJabbers;
    uint32 myEtherStatsHighCollisions;
    uint32 myEtherStatsHighPkts64Octets;
    uint32 myEtherStatsHighPkts65to127Octets;
    uint32 myEtherStatsHighPkts128to255Octets;
    uint32 myEtherStatsHighPkts256to511Octets;
    uint32 myEtherStatsHighPkts512to1023Octets;
    uint32 myEtherStatsHighPkts1024to1518Octets;
    uint32 myEtherStatsHighDroppedFrames;
    uint32 myIfHighOutMulticastPkts;
    uint32 myIfHighOutBroadcastPkts;
    uint32 myIfHighInUcastPkts;
    uint32 myIfHighInDiscards;
    uint32 myIfHighInErrors;
    uint32 myIfHighOutOctets;
    uint32 myIfHighOutUcastPkts;
    uint32 myIfHighOutDiscards;
    uint32 myIfHighOutErrors;

};

#endif /* MON_RMONCOUNTERS_H */
