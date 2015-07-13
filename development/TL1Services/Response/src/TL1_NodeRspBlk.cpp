/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Node Response 
TARGET:
AUTHOR:         June 19, 2007 - Mike Rodgers
DESCRIPTION:    Source file for TL1 Node Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_NodeRspBlk.h>

TL1_NodeRspBlk::TL1_NodeRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_NodeRspBlk::TL1_NodeRspBlk( const string*           theEntityName,
                                const CT_TL1_NodeAddr*  theAddr,
                                const string*           theNodeName,
                                const uint32*           theNodeId,
                                const string*           theAreaName,
                                const CT_SM_PST*        thePST,
                                const CT_SM_PSTQ*       thePSTQ)
    : myBitSet( INDEX_END, false ), myAddr(*theAddr)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_NodeAddr ] = true;
        myAddr = *theAddr;
    }

    if( theNodeName )
    {
        myBitSet[ INDEX_NodeName ] = true;
        myNodeName = *theNodeName;
    }

    if( theNodeId )
    {
        myBitSet[ INDEX_NodeId ] = true;
        myNodeId = *theNodeId;
    }

    if( theAreaName )
    {
        myBitSet[ INDEX_AreaName ] = true;
        myAreaName = *theAreaName;
    }

    if(thePST)
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }

    if(thePSTQ)
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
}


TL1_NodeRspBlk::TL1_NodeRspBlk( const TL1_NodeRspBlk& theRspBlk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet       = theRspBlk.myBitSet;
    myEntityName   = theRspBlk.myEntityName;
    myAddr         = theRspBlk.myAddr;    
    myNodeName     = theRspBlk.myNodeName;
    myNodeId       = theRspBlk.myNodeId;
    myAreaName     = theRspBlk.myAreaName;
    myPST          = theRspBlk.myPST;
    myPSTQ         = theRspBlk.myPSTQ;
}

TL1_NodeRspBlk::~TL1_NodeRspBlk( )
{
}

TL1_NodeRspBlk& TL1_NodeRspBlk::operator=( const TL1_NodeRspBlk& theRspBlk )
{
    myBitSet       = theRspBlk.myBitSet;
    myEntityName   = theRspBlk.myEntityName;
    myAddr         = theRspBlk.myAddr;
    myNodeName     = theRspBlk.myNodeName;
    myNodeId       = theRspBlk.myNodeId;
    myAreaName     = theRspBlk.myAreaName;
    myPST          = theRspBlk.myPST;
    myPSTQ         = theRspBlk.myPSTQ;

    return *this;
}

bool TL1_NodeRspBlk::operator==( const TL1_NodeRspBlk& theRspBlk ) const
{
    if ( myBitSet != theRspBlk.myBitSet )
        return false;

    if ( myEntityName != theRspBlk.myEntityName )
        return false;

    if ( !( myAddr == theRspBlk.myAddr ) )
        return false;

    if ( !( myNodeName == theRspBlk.myNodeName ) )
        return false;

    if ( !( myNodeId == theRspBlk.myNodeId ) )
        return false;

    if ( !( myAreaName == theRspBlk.myAreaName ) )
        return false;

    if ( myPST != theRspBlk.myPST )
        return false;

    if ( myPSTQ != theRspBlk.myPSTQ )
        return false;

    return true;
}

//--------------------------------------------------------------
bool TL1_NodeRspBlk::GetEntityName( string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_NodeRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool TL1_NodeRspBlk::GetNodeAddr( CT_TL1_NodeAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_NodeAddr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_NodeRspBlk::SetNodeAddr( const CT_TL1_NodeAddr& theAddr )
{
    myBitSet[ INDEX_NodeAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool TL1_NodeRspBlk::GetNodeName( string& theNodeName ) const
{
    if( true == myBitSet[ INDEX_NodeName ] )
    {
        theNodeName = myNodeName;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_NodeRspBlk::SetNodeName( const string& theNodeName )
{
    myBitSet[ INDEX_NodeName ] = true;
    myNodeName = theNodeName;
}

//--------------------------------------------------------------
bool TL1_NodeRspBlk::GetNodeId( uint32& theNodeId ) const
{
    if( true == myBitSet[ INDEX_NodeId ] )
    {
        theNodeId = myNodeId;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_NodeRspBlk::SetNodeId( const uint32& theNodeId )
{
    myBitSet[ INDEX_NodeId ] = true;
    myNodeId = theNodeId;
}

//--------------------------------------------------------------
bool TL1_NodeRspBlk::GetAreaName( string& theAreaName ) const
{
    if( true == myBitSet[ INDEX_AreaName ] )
    {
        theAreaName = myAreaName;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_NodeRspBlk::SetAreaName( const string& theAreaName )
{
    myBitSet[ INDEX_AreaName ] = true;
    myAreaName = theAreaName;
}

//--------------------------------------------------------------
bool TL1_NodeRspBlk::GetPST( CT_SM_PST& thePST ) const
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        thePST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_NodeRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool TL1_NodeRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        thePSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_NodeRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

