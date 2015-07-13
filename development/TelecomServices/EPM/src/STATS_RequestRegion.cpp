// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
//
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/
#include "../STATS_RequestRegion.h"

using namespace std;

STATS_RequestRegion::STATS_RequestRegion(const FC_BbKey theKey, size_t theSize): FC_BbRegionVectImp<STATS_Request>( theKey, theSize)
{
}

STATS_RequestRegion::~STATS_RequestRegion()
{
}

void STATS_RequestRegion::ResetData()
{
    // Reset each object within the region that need to be reset.
    FC_BbRegion::Iterator it=Begin();
    for(; it!=End(); ++it)
    {
        static_cast<STATS_Request&>(*it).ResetData();
    }
}
