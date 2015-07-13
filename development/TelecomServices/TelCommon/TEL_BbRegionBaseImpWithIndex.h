// Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef TEL_BBREGIONBASEIMPWITHINDEX_H
#define TEL_BBREGIONBASEIMPWITHINDEX_H

#include "TelCommon/TEL_BbRegionBase.h"

/* 
This region is the base class region used by Telecom Services.
*/
//##ModelId=3C20B0B00346
template <class T>
class TEL_BbRegionBaseImpWithIndex:    public TEL_BbRegionBase
{

public:

    //Constructor of Telecom Services region base.
	//##ModelId=3C20B0B10104
    TEL_BbRegionBaseImpWithIndex(const FC_BbKey theKey = "unnamed",
                     size_t theInitialSize = 0):
        TEL_BbRegionBase( theKey )
    {
        Resize(theInitialSize);
    }

    // Region destructor.
	//##ModelId=3C20B0B10117
    virtual ~TEL_BbRegionBaseImpWithIndex()
    {
        Resize(0);
    }

	//##ModelId=3C20B0B10119
	virtual FC_BbObject* Allocate(bbindex_t theIndex)
    {
        return new T(theIndex);
    }

	//##ModelId=3C20B0B10122
    void Deallocate(FC_BbObject* theObject)
    {
        delete theObject;
    }

	//##ModelId=3C20B0B1012C
    T& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<T&>( *(*myObjVectorPtr)[theIndex]);
    }

};

#endif //TEL_BBREGIONBASEIMPWITHINDEX_H


