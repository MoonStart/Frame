/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TelecomServices Performance Management

TARGET:         ActiveController, SMTMU, SSM

AUTHOR:         Michael Sharkey
-----------------------------------------------------------------------------*/ 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef _INC_PM_PROFILE_TABLE_REGION_INCLUDED
#define _INC_PM_PROFILE_TABLE_REGION_INCLUDED

#include <Blackboard/FC_BbKey.h>
#include <PM/PM_ProfileTable.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <TelCommon/TEL_BbRegionBase.h>

#include "../incl/gdef.h"

class PM_ProfileTableRegion : public TEL_BbRegionBase
{
public:

    PM_ProfileTableRegion(FC_BbKey aBbKey, CT_EntityType theEntityType);
    virtual ~PM_ProfileTableRegion();

    virtual FC_BbObject* Allocate(bbindex_t theIndex)
    {
        return new PM_ProfileTable();
    }

    PM_ProfileTable& operator[] ( bbindex_t theIndex ) const
    {
        return static_cast<PM_ProfileTable&>( *(*myObjVectorPtr)[theIndex]);
    }
    
protected:

private:
    CT_EntityType myEntityType;
    
};

#endif /* _INC_PM_PROFILE_TABLE_REGION_INCLUDED */
