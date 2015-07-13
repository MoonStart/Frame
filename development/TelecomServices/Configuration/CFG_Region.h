//Copyright(c) Tellabs Transport Group. All rights reserved


#ifndef CFG_REGION_H
#define CFG_REGION_H

#include <TelCommon/TEL_BbRegionBase.h>
#include "CFG_Object.h"


//This class is a CFG_Object container. This is a 
//generic region.
//##ModelId=3C0FE62F0154
class CFG_Region : public TEL_BbRegionBase
{
public:
	//Constructor.
	//##ModelId=3C0FE62F015F
    CFG_Region(const FC_BbKey theKey);

	//Virtual destructor.
	//##ModelId=3C0FE62F016A
    virtual ~CFG_Region();

	//This method resets all objects within the region to 
	//their default values.
	//##ModelId=3C0FE62F0175
    virtual void Reset();

	//##ModelId=3C716FEB00E4
    CFG_Object& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<CFG_Object&>( ElementAt(theIndex));
    }

};

#endif /* CFG_REGION_H */

