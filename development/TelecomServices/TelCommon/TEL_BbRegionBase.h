// Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef TEL_BBREGIONBASE_H
#define TEL_BBREGIONBASE_H

#include "Blackboard/FC_BbRegionAsVector.h"
#include "TelCommon/TEL_BbObjectBase.h"

/* 
This region is the base class region used by Telecom Services.
*/
//##ModelId=3C20B0B1033E
class TEL_BbRegionBase:    public FC_BbRegionAsVector
{

public:

    //Constructor of Telecom Services region base.
	//##ModelId=3C20B0B2016A
    TEL_BbRegionBase(const FC_BbKey& theKey);

    // Region destructor.
	//##ModelId=3C20B0B20174
    virtual ~TEL_BbRegionBase();

	//##ModelId=3C20B0B2017D
    virtual FC_BbObject* Allocate(bbindex_t theIndex) = 0; 
	//##ModelId=3C20B0B20187
    virtual void Deallocate(FC_BbObject* theObject);

	//##ModelId=3C20B0B20191
    TEL_BbObjectBase& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<TEL_BbObjectBase&>( *(*myObjVectorPtr)[theIndex]);
    }

};

#endif //TEL_BBREGIONBASE_H



