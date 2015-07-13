/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TelecomServices Performance Monitoring

TARGET:         ActiveController, SMTMU, SSM

AUTHOR:         Michael Sharkey
-----------------------------------------------------------------------------*/ 

#include "PM_ProfileTableRegion.h"

#include <CommonTypes/CT_PM_Definition.h>
 
//-----------------------------------------------------------------------
PM_ProfileTableRegion::PM_ProfileTableRegion(FC_BbKey aBbKey, CT_EntityType theEntityType)
:TEL_BbRegionBase(aBbKey)
,myEntityType(theEntityType)
{
    Resize((size_t)CT_PM_NUMBER_OF_PT );
    for ( bbindex_t i=0; i < (bbindex_t)CT_PM_NUMBER_OF_PT; i++) 
    {
        (*this)[ i ].SetEntityType( myEntityType );
    }
}

//-----------------------------------------------------------------------
PM_ProfileTableRegion::~PM_ProfileTableRegion()
{
}
