// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_PROTECTIONGROUPSTATUSREGION_38E0B0C70260_INCLUDED
#define _INC_SP_PROTECTIONGROUPSTATUSREGION_38E0B0C70260_INCLUDED

#include <TelCommon/TEL_BbRegionBase.h>
#include <CommonTypes/CT_SignalProtection.h>
#include "SP_ProtectionGroupStatus.h"

//This is the base class of the protection group status 
//region.
class SP_ProtectionGroupStatus;

//This is the base class of the protection group status 
//region.  This region holds all the protection group status 
//of the same type for a given port shelf. There are as many 
//regions that there are port shelves.
//##ModelId=38E0B0C70260
class SP_ProtectionGroupStatusRegion 
: public TEL_BbRegionBase
{
public:
	//Constructor. Requires a key.
	//##ModelId=3B8BC9D40124
	SP_ProtectionGroupStatusRegion(const FC_BbKey theKey);

	//Destructor.
	//##ModelId=38E201ED02EA
	virtual ~SP_ProtectionGroupStatusRegion();

	//Returns a reference to the object at specified index.
	//##ModelId=3937FD3802E1
    inline SP_ProtectionGroupStatus& operator[] ( bbindex_t theIndex ) const
    {
    	return static_cast<SP_ProtectionGroupStatus&>(*(*myObjVectorPtr)[theIndex]);
    }

};

#endif /* _INC_SP_PROTECTIONGROUPSTATUSREGION_38E0B0C70260_INCLUDED */

