/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Telecom Services
 TARGET   :     ALL
 AUTHOR   :     M. Vendette - April 05th ,2000
 DESCRIPTION:   Base class region used by Telecom Services
--------------------------------------------------------------------------*/

#include "../TEL_BbRegionBase.h"

//------------------------------------------------------------------
// Constructor of Telecom Services config region.
//##ModelId=3C20B0B2016A
TEL_BbRegionBase::TEL_BbRegionBase(const FC_BbKey& theKey):
    FC_BbRegionAsVector(theKey, 0)
{
}


//------------------------------------------------------------------
// Class Destructor 
//##ModelId=3C20B0B20174
TEL_BbRegionBase::~TEL_BbRegionBase() 
{

}

//##ModelId=3C20B0B20187
void TEL_BbRegionBase::Deallocate(FC_BbObject* theObject)
{
    delete theObject;
}

