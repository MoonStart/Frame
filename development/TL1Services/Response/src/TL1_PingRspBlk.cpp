/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Conn Response 
TARGET:
AUTHOR:         june 03, 2009 - Tom Novak
DESCRIPTION:    Source file for TL1 Opr Ping Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_PingRspBlk.h>

TL1_PingRspBlk::TL1_PingRspBlk( ) :
    myBitSet( INDEX_END, false ) 
{
}

TL1_PingRspBlk::TL1_PingRspBlk( const string   theIpAddr,
                                const string   theResult ) 
   : myBitSet( INDEX_END, false )
{

    myBitSet[ INDEX_IpAddr ] = true;
    myIpAddr = theIpAddr;

    myBitSet[ INDEX_Result ] = true;
    myResult = theResult;
}

TL1_PingRspBlk::TL1_PingRspBlk( const TL1_PingRspBlk& t1Blk ) :
                    myBitSet( INDEX_END, false )
{
    myBitSet	= t1Blk.myBitSet;
    myIpAddr	= t1Blk.myIpAddr;
    myResult	= t1Blk.myResult;
    myIpv6Addr 	= t1Blk.myIpv6Addr;
}

TL1_PingRspBlk::~TL1_PingRspBlk( )
{
}

TL1_PingRspBlk& 
TL1_PingRspBlk::operator=( const TL1_PingRspBlk& t1Blk )
{
    myIpAddr	=	t1Blk.myIpAddr;
    myResult	=	t1Blk.myResult;
	myIpv6Addr 	= 	t1Blk.myIpv6Addr;
    return *this;
}

bool 
TL1_PingRspBlk::operator==( const TL1_PingRspBlk& t1Blk ) const
{
    if ( myIpAddr != t1Blk.myIpAddr )
        return false;

    if ( myResult != t1Blk.myResult )
        return false;

	if(myIpv6Addr != t1Blk.myIpv6Addr)
	{
		return false;
	}

    return true;
}

//--------------------------------------------------------------
bool 
TL1_PingRspBlk::GetIpAddr( string& theIpAddr ) const
{
    if( true == myBitSet[ INDEX_IpAddr ] )
    {
        theIpAddr = myIpAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_PingRspBlk::GetIpV6Addr(PingIpv6Addr &vIpv6Addr) const
{
    if( true == myBitSet[ INDEX_Ipv6Addr ] )
    {
        vIpv6Addr = myIpv6Addr;
        return true;
    }
    else
    {
        return false;
    }
}


void 
TL1_PingRspBlk::SetIpAddr( string& theIpAddr )
{
   myBitSet[ INDEX_IpAddr ] = true;
   myIpAddr = theIpAddr;
}


void 
TL1_PingRspBlk::SetIpAddr(const PingIpv6Addr &vIpv6Addr)
{
   myBitSet[ INDEX_Ipv6Addr ] = true;
   myIpv6Addr = vIpv6Addr;
}


//--------------------------------------------------------------
bool 
TL1_PingRspBlk::GetResult( string& theResult ) const
{
    if( true == myBitSet[ INDEX_Result ] )
    {
        theResult = myResult;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_PingRspBlk::SetResult( string& theResult )
{
    myBitSet[ INDEX_Result ] = true;
    myResult= theResult;
}


