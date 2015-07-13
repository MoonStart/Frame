// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_RmonIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_RmonUpdateStatusAction.h"
#include "../MON_RmonCounters.h"
#include "../MON_RmonConfig.h"
#include "../MON_RmonStatus.h"
#include "../MON_Region.h"

MON_RmonUpdateStatusAction::MON_RmonUpdateStatusAction(MON_AppIf& theMonIf,
                                                       TSPII_RmonRegion& theRmonPiiRegion,
                                                       MON_AppIf* theUpstreamLayerIf):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myRmonPiiRegion(theRmonPiiRegion)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myRmonPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);   
}

MON_RmonUpdateStatusAction::~MON_RmonUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myRmonPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_RmonUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}


FC_Object* MON_RmonUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{

    MON_RmonStatus& aStatus     = static_cast<MON_RmonStatus&>((*GetMonIf().GetStatusRegion())[0]);
    MON_RmonCounters& aCounters = static_cast<MON_RmonCounters&>((*GetMonIf().GetCountersRegion())[0]);
    MON_RmonConfig& aConfig     = static_cast<MON_RmonConfig&>((*GetMonIf().GetConfigRegion())[0]);
    TSPII_RmonIf& aRmonPII      = myRmonPiiRegion[0];
    // bool hasDefectsChanged = false;


    //--------------------------------------------------------------
    // CONFIG
    // 
    aRmonPII.SetEnabled(aConfig.GetRmonEnable());

    //--------------------------------------------------------------
    // COUNTERS
    // 64 bit counters use two fields, normal and High 
    // Call the High Counter field second.
    aCounters.SetErrorCount(CT_TEL_RMON_DROP_EVENTS,                  aRmonPII.GetEtherStatsDropEvents());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_DROP_EVENTS,             aRmonPII.GetEtherStatsHighDropEvents());
    aCounters.SetErrorCount(CT_TEL_RMON_OCTETS,                       aRmonPII.GetEtherStatsOctets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_OCTETS,                  aRmonPII.GetEtherStatsHighOctets());
    aCounters.SetErrorCount(CT_TEL_RMON_PKTS,                         aRmonPII.GetEtherStatsPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_PKTS,                    aRmonPII.GetEtherStatsHighPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_BROADCAST_PKTS,               aRmonPII.GetEtherStatsBroadcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_BROADCAST_PKTS,          aRmonPII.GetEtherStatsHighBroadcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_MULTICAST_PKTS,               aRmonPII.GetEtherStatsMulticastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_MULTICAST_PKTS,          aRmonPII.GetEtherStatsHighMulticastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_CRC_ALIGN_ERRORS,             aRmonPII.GetEtherStatsCRCAlignErrors());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_CRC_ALIGN_ERRORS,        aRmonPII.GetEtherStatsHighCRCAlignErrors());
    aCounters.SetErrorCount(CT_TEL_RMON_UNDERSIZE_PKTS,               aRmonPII.GetEtherStatsUndersizePkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_UNDERSIZE_PKTS,          aRmonPII.GetEtherStatsHighUndersizePkts());
    aCounters.SetErrorCount(CT_TEL_RMON_OVERSIZE_PKTS,                aRmonPII.GetEtherStatsOversizePkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_OVERSIZE_PKTS,           aRmonPII.GetEtherStatsHighOversizePkts());
    aCounters.SetErrorCount(CT_TEL_RMON_FRAGMENTS,                    aRmonPII.GetEtherStatsFragments());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_FRAGMENTS,               aRmonPII.GetEtherStatsHighFragments());
    aCounters.SetErrorCount(CT_TEL_RMON_JABBERS,                      aRmonPII.GetEtherStatsJabbers());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_JABBERS,                 aRmonPII.GetEtherStatsHighJabbers());
    aCounters.SetErrorCount(CT_TEL_RMON_COLLISIONS,                   aRmonPII.GetEtherStatsCollisions());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_COLLISIONS,              aRmonPII.GetEtherStatsHighCollisions());
    aCounters.SetErrorCount(CT_TEL_RMON_PKTS_64_OCTETS,               aRmonPII.GetEtherStatsPkts64Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_PKTS_64_OCTETS,          aRmonPII.GetEtherStatsHighPkts64Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_PKTS_65_TO_127_OCTETS,        aRmonPII.GetEtherStatsPkts65to127Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_PKTS_65_TO_127_OCTETS,   aRmonPII.GetEtherStatsHighPkts65to127Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_PKTS_128_TO_255_OCTETS,       aRmonPII.GetEtherStatsPkts128to255Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_PKTS_128_TO_255_OCTETS,  aRmonPII.GetEtherStatsHighPkts128to255Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_PKTS_256_TO_511_OCTETS,       aRmonPII.GetEtherStatsPkts256to511Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_PKTS_256_TO_511_OCTETS,  aRmonPII.GetEtherStatsHighPkts256to511Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_PKTS_512_TO_1023_OCTETS,      aRmonPII.GetEtherStatsPkts512to1023Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_PKTS_512_TO_1023_OCTETS, aRmonPII.GetEtherStatsHighPkts512to1023Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_PKTS_1024_TO_1518_OCTETS,     aRmonPII.GetEtherStatsPkts1024to1518Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_PKTS_1024_TO_1518_OCTETS,aRmonPII.GetEtherStatsHighPkts1024to1518Octets());
    aCounters.SetErrorCount(CT_TEL_RMON_DROPPED_FRAMES,               aRmonPII.GetEtherStatsDroppedFrames());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_DROPPED_FRAMES,          aRmonPII.GetEtherStatsHighDroppedFrames());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_OUT_MULTICAST_PKTS,        aRmonPII.GetIfOutMulticastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_OUT_MULTICAST_PKTS,   aRmonPII.GetIfHighOutMulticastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_OUT_BROADCAST_PKTS,        aRmonPII.GetIfOutBroadcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_OUT_BROADCAST_PKTS,   aRmonPII.GetIfHighOutBroadcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_IN_UCAST_PKTS,             aRmonPII.GetIfInUcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_IN_UCAST_PKTS,        aRmonPII.GetIfHighInUcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_IN_DISCARDS,               aRmonPII.GetIfInDiscards());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_IN_DISCARDS,          aRmonPII.GetIfHighInDiscards());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_IN_ERRORS,                 aRmonPII.GetIfInErrors());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_IN_ERRORS,            aRmonPII.GetIfHighInErrors());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_OUT_OCTETS,                aRmonPII.GetIfOutOctets());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_OUT_OCTETS,           aRmonPII.GetIfHighOutOctets());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_OUT_UCAST_PKTS,            aRmonPII.GetIfOutUcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_OUT_UCAST_PKTS,       aRmonPII.GetIfHighOutUcastPkts());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_OUT_DISCARDS,              aRmonPII.GetIfOutDiscards());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_OUT_DISCARDS,         aRmonPII.GetIfHighOutDiscards());
    aCounters.SetErrorCount(CT_TEL_RMON_IF_OUT_ERRORS,                aRmonPII.GetIfOutErrors());
    aCounters.SetErrorCount(CT_TEL_RMON_HIGH_IF_OUT_ERRORS,           aRmonPII.GetIfHighOutErrors());

    // Validate Counter region
    aCounters.Validate();

    //--------------------------------------------------------------
    // DEFECTS
    // 
    // No Defects at this time

    //--------------------------------------------------------------
    // STATUS
    // 
    bool hasStatusChanged = false;

    //The MAC address of the interface.
    uint32 aIfPhysAddressHigh;
    uint32 aIfPhysAddressLow;
    bool   aSuccess;

    //MTU Size
    uint32 aIfMtu;

    aSuccess = aRmonPII.GetIfPhysAddress(aIfPhysAddressHigh, aIfPhysAddressLow);
    if (aSuccess) 
    {
        hasStatusChanged |= aStatus.SetIfPhysAddressHigh(aIfPhysAddressHigh);
        hasStatusChanged |= aStatus.SetIfPhysAddressLow(aIfPhysAddressLow);
    }

    aIfMtu = aRmonPII.GetIfMtu();
    hasStatusChanged |= aStatus.SetIfMtu(aIfMtu);  

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();

    return NULL;
}
