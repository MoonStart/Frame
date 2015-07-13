/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 EXDPATH Response 
TARGET:
AUTHOR:         September 10, 2014 Jing Jin
DESCRIPTION:    Source file for TL1 EXDPATH Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_ExdpathRspBlk.h>

//---------------------------------------------------------------------------------------
TL1_ExdpathRspBlk::TL1_ExdpathRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_ExdpathRspBlk::~TL1_ExdpathRspBlk()
{
}

TL1_ExdpathRspBlk& 
TL1_ExdpathRspBlk::operator=( const TL1_ExdpathRspBlk& t1Blk )
{
    myExdpathName=  t1Blk.myExdpathName;
    myExdpath=      t1Blk.myExdpath;
    myExdpathAddr=  t1Blk.myExdpathAddr;

    return *this;
}

bool 
TL1_ExdpathRspBlk::operator==( const TL1_ExdpathRspBlk& t1Blk ) const
{
    if ( myExdpathName != t1Blk.myExdpathName )
        return false;

    if ( myExdpath != t1Blk.myExdpath )
        return false;

    if ( myExdpathAddr != t1Blk.myExdpathAddr )
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ExdpathRspBlk::GetExdpathAddr( CT_TL1_ExdpathAddr& theExdpathAddr ) const
{
    if( true == myBitSet[ INDEX_ExdpathAddr ] )
    {
        theExdpathAddr = myExdpathAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ExdpathRspBlk::SetExdpathAddr( const CT_TL1_ExdpathAddr& theExdpathAddr )
{
    myBitSet[ INDEX_ExdpathAddr ] = true;
    myExdpathAddr = theExdpathAddr;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_ExdpathRspBlk::GetExdpath( CT_ControlPlane_Hops& theExdpath ) const
{
    if( true == myBitSet[ INDEX_Exdpath ] )
    {
        theExdpath = myExdpath;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_ExdpathRspBlk::SetExdpath( const CT_ControlPlane_Hops& theExdpath )
{
    myBitSet[ INDEX_Exdpath ] = true;
    myExdpath = theExdpath;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ExdpathRspBlk::GetExdpathName( string& theExdpathName ) const
{
    if( true == myBitSet[ INDEX_ExdpathName ] )
    {
        theExdpathName = myExdpathName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ExdpathRspBlk::SetExdpathName( const string& theExdpathName )
{
    myBitSet[ INDEX_ExdpathName ] = true;
    myExdpathName = theExdpathName;
}

