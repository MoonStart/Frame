// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_PROTECTIONGROUPSTATUSREGIONIMP
#define _INC_SP_PROTECTIONGROUPSTATUSREGIONIMP


#include "SP_ProtectionGroupStatusRegion.h"


//Implementation of the region for the protection group 
//status.
//##ModelId=3937FD2D0372
template <class T>
class SP_ProtectionGroupStatusRegionImp
: public SP_ProtectionGroupStatusRegion
{
public:
	//Constructor. Requires a key.
	//##ModelId=3BBC9AFE03C8
    inline SP_ProtectionGroupStatusRegionImp(const FC_BbKey theKey = "unnamed",
                     size_t theInitialSize = 0):
        SP_ProtectionGroupStatusRegion( theKey )
    {
        Resize(theInitialSize);
    }

	//Destructor.
	//##ModelId=3937FD2D0390
	virtual inline ~SP_ProtectionGroupStatusRegionImp()
    {
        Resize(0);
    }

	//Allocates a new status object of type T.
	//##ModelId=3937FD2D0389
	virtual FC_BbObject* Allocate(bbindex_t theIndex)
    {
        return new T();
    }

	//Frees the given object from memory.
	//##ModelId=3937FD2D0387
    void Deallocate(FC_BbObject* theObject)
    {
        delete theObject;
    }


	//Returns a reference to the object at specified index.
	//##ModelId=3937FD2D037E
    T& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<T&>(*(*myObjVectorPtr)[theIndex]);
    }

};


#endif /* _INC_SP_PROTECTIONGROUPSTATUSREGIONIMP */

