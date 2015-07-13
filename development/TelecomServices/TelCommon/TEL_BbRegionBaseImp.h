// Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef TEL_BBREGIONBASEIMP_H
#define TEL_BBREGIONBASEIMP_H

#include "TelCommon/TEL_BbRegionBase.h"

/* 
This region is the base class region used by Telecom Services.
*/
//##ModelId=3C20B0B1013F
template <class T>
class TEL_BbRegionBaseImp:    public TEL_BbRegionBase
{

public:

    //Constructor of Telecom Services region base.
	//##ModelId=3C20B0B10303
    TEL_BbRegionBaseImp(const FC_BbKey theKey = "unnamed",
                     size_t theInitialSize = 0):
        TEL_BbRegionBase(  theKey )
    {
        Resize(theInitialSize);
    }

    // Region destructor.
	//##ModelId=3C20B0B1030D
    virtual ~TEL_BbRegionBaseImp()
    {
        Resize(0);
    }

	//##ModelId=3C20B0B10316
	virtual FC_BbObject* Allocate(bbindex_t theIndex)
    {
        return new T();
    }

	//##ModelId=3C20B0B10320
    void Deallocate(FC_BbObject* theObject)
    {
        delete theObject;
    }


	//##ModelId=3C20B0B1032A
    T& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<T&>(*(*myObjVectorPtr)[theIndex]);
    }
};

#endif //TEL_BBREGIONBASEIMP_H


