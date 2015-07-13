/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2003/4/3
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "ErrorService/FC_Error.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_Region.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_BaseRegion::TSPII_BaseRegion(const FC_BbKey & theKey) :
    FC_BbRegionAsVector(theKey)
{
    SetPrivateFlag(true); // TSPII regions are always private, make it the default
}

///////////////////////////////////////////////////////////////////////////////
FC_BbObject * TSPII_BaseRegion::Allocate(bbindex_t theIndex)
{
    FC_THROW_ERROR(FC_RuntimeError, "Not allowed to dynamically allocate in TSPII regions");
    return NULL; // To satisfy the compiler -- never reached.
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseRegion::Deallocate(FC_BbObject* theObject)
{
    delete theObject;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseRegion::AddAt(bbindex_t theIndex, TSPII_BaseIf * theObject)
{
    FC_BbRegionAsVector::AddAt(theIndex, theObject);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseRegion::RemoveAt( bbindex_t theIndex )
{
    FC_BbRegionAsVector::RemoveAt(theIndex);
}

///////////////////////////////////////////////////////////////////////////////
TSPII_BaseIf & TSPII_BaseRegion::operator[] (bbindex_t theIndex) const
{
    return static_cast<TSPII_BaseIf &>(*(*myObjVectorPtr)[theIndex]);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_BaseRegion::AddAt(bbindex_t theIndex, FC_BbObject * theObject)
{
    FC_BbRegionAsVector::AddAt(theIndex, theObject);
}

 

