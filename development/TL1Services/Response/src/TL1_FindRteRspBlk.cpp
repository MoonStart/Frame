/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OPR-FINDRTE Response Class 
TARGET:
AUTHOR:         July 07, 2011 - TLD
DESCRIPTION:    TL1 OPR-FINDRTE response, class implementation 
-----------------------------------------------------------------------------*/

#include <Response/TL1_FindRteRspBlk.h>



TL1_FindRteRspBlk::TL1_FindRteRspBlk( )

    :myBitSet( INDEX_END, false ) 
{
}


//-----------------------------------------------------------------------------
//  TL1_FindRteRspBlk constructors
TL1_FindRteRspBlk::TL1_FindRteRspBlk( 
    const CT_CallPathType        theCallPathType,
    const CT_FindRte_Status      theFindRteStatus,
    const CT_ControlPlane_Hops&  theRouteElements )
                                
    :myBitSet( INDEX_END, false )
{

    myBitSet[ INDEX_CallPathType ] = true;
    myCallPathType = theCallPathType;

    myBitSet[ INDEX_FindRteStatus ] = true;
    myFindRteStatus = theFindRteStatus;

    myBitSet[ INDEX_RouteElements ] = true;
    myRouteElements = theRouteElements;
}


//-----------------------------------------------------------------------------
// Copy Constructor
TL1_FindRteRspBlk::TL1_FindRteRspBlk( const TL1_FindRteRspBlk& theObject )

    :myBitSet( INDEX_END, false )
{

    *this = theObject;
}


//-----------------------------------------------------------------------------
// Destructor
TL1_FindRteRspBlk::~TL1_FindRteRspBlk( )
{
}


//-----------------------------------------------------------------------------
// Overloaded assignment operator
TL1_FindRteRspBlk& 
TL1_FindRteRspBlk::operator=( const TL1_FindRteRspBlk& theObject )
{
    myBitSet =           theObject.myBitSet;
    myCallPathType =     theObject.myCallPathType;
    myFindRteStatus =    theObject.myFindRteStatus;
    myRouteElements =    theObject.myRouteElements;

    return *this;
}


//-----------------------------------------------------------------------------
// Overloaded equality operator
bool 
TL1_FindRteRspBlk::operator==( const TL1_FindRteRspBlk& theObject ) const
{
    if ( myBitSet != theObject.myBitSet )
        return false;

    if ( myCallPathType != theObject.myCallPathType )
        return false;

    if ( myFindRteStatus != theObject.myFindRteStatus )
        return false;

    if ( myRouteElements != theObject.myRouteElements )
        return false;

    return true;
}


//-----------------------------------------------------------------------------
// Overloaded inequality operator
bool 
TL1_FindRteRspBlk::operator!=( const TL1_FindRteRspBlk& theObject ) const
{

    return ( !(*this == theObject ));
}


//--------------------------------------------------------------
bool 
TL1_FindRteRspBlk::GetCallPathType( CT_CallPathType& theCallPathType ) const
{
    if ( true == myBitSet[ INDEX_CallPathType ] )
    {
        theCallPathType = myCallPathType;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_FindRteRspBlk::SetCallPathType( const CT_CallPathType& theCallPathType ) 
{
   myBitSet[ INDEX_CallPathType ] = true;
   myCallPathType = theCallPathType;
}


//--------------------------------------------------------------
bool 
TL1_FindRteRspBlk::GetFindRteStatus( CT_FindRte_Status& theFindRteStatus ) const
{
    if ( true == myBitSet[ INDEX_FindRteStatus ] )
    {
        theFindRteStatus = myFindRteStatus;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_FindRteRspBlk::SetFindRteStatus( const CT_FindRte_Status& theFindRteStatus ) 
{
   myBitSet[ INDEX_FindRteStatus ] = true;
   myFindRteStatus = theFindRteStatus;
}


//--------------------------------------------------------------
bool 
TL1_FindRteRspBlk::GetRouteElements( CT_ControlPlane_Hops& theRouteElements ) const
{
    if ( true == myBitSet[ INDEX_RouteElements ] )
    {
        theRouteElements = myRouteElements;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_FindRteRspBlk::SetRouteElements( const CT_ControlPlane_Hops& theRouteElements ) 
{
   myBitSet[ INDEX_RouteElements ] = true;
   myRouteElements = theRouteElements;
}
