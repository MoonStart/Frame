// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
//
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/
#include "../STATS_ResponseRegion.h"

using namespace std;

STATS_ResponseRegion::STATS_ResponseRegion(const FC_BbKey theKey, size_t theSize): FC_BbRegionVectImp<STATS_Response>( theKey, theSize)
{
}

STATS_ResponseRegion::~STATS_ResponseRegion()
{
}

void STATS_ResponseRegion::ResetData()
{
    // Reset each object within the region that need to be reset.
    FC_BbRegion::Iterator it=Begin();
    for(; it!=End(); ++it)
    {
        static_cast<STATS_Response&>(*it).ResetData();
    }
}
