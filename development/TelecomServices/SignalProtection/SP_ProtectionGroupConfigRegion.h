// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_PROTECTIONGROUPCONFIGREGION_38DB811701D7_INCLUDED
#define _INC_SP_PROTECTIONGROUPCONFIGREGION_38DB811701D7_INCLUDED


#include <TelCommon/TEL_BbRegionBase.h>
#include <CommonTypes/CT_SignalProtection.h>
#include "SP_Definitions.h"
#include "SP_ProtectionGroupConfig.h"

//This is the base class of the protection group 
//configuration region.
class SP_ProtectionGroupConfig;

//This is the base class of the protection group 
//configuration region. This region holds all the protection 
//group of the same type for a given port shelf. There are as 
//many regions that there are port shelves. This class 
//handles the request and freeing of available protection 
//groups for a port shelf.
//##ModelId=38DB811701D7
class SP_ProtectionGroupConfigRegion
: public TEL_BbRegionBase
{
public:
	//Constructor. Requires a key.
	//##ModelId=3B8BC9D40084
    SP_ProtectionGroupConfigRegion(const FC_BbKey theKey);
	//Destructor.
	//##ModelId=38E201F101C3
	virtual ~SP_ProtectionGroupConfigRegion();

	//Returns a reference to the object at specified index.
	//##ModelId=3937FD380024
    inline SP_ProtectionGroupConfig& operator[] ( bbindex_t theIndex ) const
    {
    	return static_cast<SP_ProtectionGroupConfig&>(*(*myObjVectorPtr)[theIndex]);
    }

};


#endif /* _INC_SP_PROTECTIONGROUPCONFIGREGION_38DB811701D7_INCLUDED */

