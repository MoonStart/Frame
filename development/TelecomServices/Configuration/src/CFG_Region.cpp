//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Region.h"

//##ModelId=3C0FE62F015F
CFG_Region::CFG_Region(const FC_BbKey theKey):
    TEL_BbRegionBase(theKey)
{
}

//##ModelId=3C0FE62F016A
CFG_Region::~CFG_Region()
{
}

//This method resets all objects within the region to 
//their default values.
//##ModelId=3C0FE62F0175
void CFG_Region::Reset()
{
    FC_BbRegion::Iterator it=Begin();
    for(; it!=End(); ++it)
        static_cast<CFG_Object&>(*it).Reset();

}
