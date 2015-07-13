// Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef TEL_REGIONBASEIMPWITHINDEX_H
#define TEL_REGIONBASEIMPWITHINDEX_H

#include <Blackboard/FC_BbRegion.h>
 
/* 
This region is the base class region used by Telecom Services.
*/
//##ModelId=3C20B0B0015C
template <class REGION, class OBJECT>
class TEL_RegionBaseImpWithIndex:    public REGION
{

public:

    //Constructor of Telecom Services region base.
	//##ModelId=3C20B0B0030A
    TEL_RegionBaseImpWithIndex(const FC_BbKey theKey = "unnamed",
                     size_t theInitialSize = 0):
        REGION(  theKey )
    {
        this->Resize(theInitialSize);
    }

    // Region destructor.
	//##ModelId=3C20B0B00314
    virtual ~TEL_RegionBaseImpWithIndex()
    {
        this->Resize(0);
    }

	//##ModelId=3C20B0B00316
	virtual FC_BbObject* Allocate(bbindex_t theIndex)
    {
        return new OBJECT(theIndex);
    }

	//##ModelId=3C20B0B00320
    void Deallocate(FC_BbObject* theObject)
    {
        delete theObject;
    }

	//##ModelId=3C20B0B00329
    OBJECT& operator[] ( bbindex_t theIndex ) const
    {
#ifdef LINUX
        return static_cast< OBJECT & > (*(*this->myObjVectorPtr)[theIndex]);
#else
        return static_cast< OBJECT & > (*(*myObjVectorPtr)[theIndex]);
#endif
    }

};

#endif //TEL_REGIONBASEIMPWITHINDEX_H


