//Copyright(c) Tellabs Transport Group. All rights reserved


#ifndef MON_REGION_H
#define MON_REGION_H

#include <TelCommon/TEL_BbRegionBase.h>
#include "MON_Object.h"


//This class is a MON_Object container. This is a 
//generic region.
//##ModelId=3C0FE66E03B7
class MON_Region : public TEL_BbRegionBase
{
public:
	//Constructor.
	//##ModelId=3C0FE66E03C2
    MON_Region(const FC_BbKey theKey);

	//Virtual destructor.
	//##ModelId=3C0FE66E03CD
    virtual ~MON_Region(void);

	//##ModelId=3C0FE66E03E0
    virtual void Reset(void);

	//##ModelId=3C7170D9033F
    MON_Object& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<MON_Object&>( ElementAt(theIndex));
    }

};

#endif /* MON_REGION_H */

