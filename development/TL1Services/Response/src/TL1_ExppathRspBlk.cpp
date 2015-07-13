/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 EXPPATH Response 
TARGET:
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Source file for TL1 EXPPATH Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_ExppathRspBlk.h>

//---------------------------------------------------------------------------------------
TL1_ExppathRspBlk::TL1_ExppathRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_ExppathRspBlk::~TL1_ExppathRspBlk()
{
}

TL1_ExppathRspBlk& 
TL1_ExppathRspBlk::operator=( const TL1_ExppathRspBlk& t1Blk )
{
    myExppathName=  t1Blk.myExppathName;
    myExppath=      t1Blk.myExppath;
    myExppathAddr=  t1Blk.myExppathAddr;

    return *this;
}

bool 
TL1_ExppathRspBlk::operator==( const TL1_ExppathRspBlk& t1Blk ) const
{
    if ( myExppathName != t1Blk.myExppathName )
        return false;

    if ( myExppath != t1Blk.myExppath )
        return false;

    if ( myExppathAddr != t1Blk.myExppathAddr )
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ExppathRspBlk::GetExppathAddr( CT_TL1_ExppathAddr& theExppathAddr ) const
{
    if( true == myBitSet[ INDEX_ExppathAddr ] )
    {
        theExppathAddr = myExppathAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ExppathRspBlk::SetExppathAddr( const CT_TL1_ExppathAddr& theExppathAddr )
{
    myBitSet[ INDEX_ExppathAddr ] = true;
    myExppathAddr = theExppathAddr;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_ExppathRspBlk::GetExppath( CT_ControlPlane_Hops& theExppath ) const
{
    if( true == myBitSet[ INDEX_Exppath ] )
    {
        theExppath = myExppath;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_ExppathRspBlk::SetExppath( const CT_ControlPlane_Hops& theExppath )
{
    myBitSet[ INDEX_Exppath ] = true;
    myExppath = theExppath;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ExppathRspBlk::GetExppathName( string& theExppathName ) const
{
    if( true == myBitSet[ INDEX_ExppathName ] )
    {
        theExppathName = myExppathName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ExppathRspBlk::SetExppathName( const string& theExppathName )
{
    myBitSet[ INDEX_ExppathName ] = true;
    myExppathName = theExppathName;
}

