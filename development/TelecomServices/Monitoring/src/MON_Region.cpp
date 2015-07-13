//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_Region.h"


//##ModelId=3C0FE66E03C2
MON_Region::MON_Region(const FC_BbKey theKey):
    TEL_BbRegionBase(theKey)
{
}

//##ModelId=3C0FE66E03CD
MON_Region::~MON_Region()
{
}

//This method invokes hardware refresh method of all
//objects within the region.
//##ModelId=3C0FE66E03E0
void MON_Region::Reset()
{
    // Refresh each object within the region that need to be refreshed.
    FC_BbRegion::Iterator it=Begin();
    for(; it!=End(); ++it)
    {
        static_cast<MON_Object&>(*it).Reset();
    }
}
