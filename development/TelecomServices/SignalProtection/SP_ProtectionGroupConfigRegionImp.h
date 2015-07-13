// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_PROTECTIONGROUPCONFIGREGIONIMP
#define _INC_SP_PROTECTIONGROUPCONFIGREGIONIMP


#include "SP_ProtectionGroupConfigRegion.h"


//Implementation of the region for the protection group 
//configuration.
//##ModelId=3937FD4803DF
template <class T>
class SP_ProtectionGroupConfigRegionImp
: public SP_ProtectionGroupConfigRegion
{
public:
	//Constructor. Requires the key of the region.
	//##ModelId=3BBC9AFF00B2
    inline SP_ProtectionGroupConfigRegionImp(const FC_BbKey theKey = "unnamed",
                     size_t theInitialSize = 0):
        SP_ProtectionGroupConfigRegion( theKey )
    {
        Resize(theInitialSize);
    }

	//Destructor.
	//##ModelId=3937FD490016
	virtual inline ~SP_ProtectionGroupConfigRegionImp()
    {
        Resize(0);
    }

	//Allocates a new status object of type T.
	//##ModelId=3937FD49000F
	virtual FC_BbObject* Allocate(bbindex_t theIndex)
    {
        return new T();
    }

	//Frees the given object from memory.
	//##ModelId=3937FD49000D
    void Deallocate(FC_BbObject* theObject)
    {
        delete theObject;
    }


	//Returns a reference to the object at specified index.
	//##ModelId=3937FD49000B
    T& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<T&>(*(*myObjVectorPtr)[theIndex]);
    }

};


#endif /* _INC_SP_PROTECTIONGROUPCONFIGREGIONIMP */

