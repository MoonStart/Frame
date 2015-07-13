/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Conn Response 
TARGET:
AUTHOR:         june 03, 2009 - Tom Novak
DESCRIPTION:    Source file for TL1 Opr Trace Route Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_TraceRouteRspBlk.h>

TL1_TraceRouteRspBlk::TL1_TraceRouteRspBlk( ) :
    myBitSet( INDEX_END, false ) 
{
}

TL1_TraceRouteRspBlk::TL1_TraceRouteRspBlk( const int             theHopCount,
                                            const CT_TraceRoute   theRsp,
                                            const uint32          theIpAddr,
                                            const uint32          theRespTime )
   : myBitSet( INDEX_END, false )
{

    myBitSet[ INDEX_HopCount ] = true;
    myHopCount = theHopCount;

    myBitSet[ INDEX_Rsp ] = true;
    myRsp = theRsp;

    myBitSet[ INDEX_IpAddr ] = true;
    myIpAddr = theIpAddr;

    myBitSet[ INDEX_RespTime ] = true;
    myRespTime = theRespTime;
}

TL1_TraceRouteRspBlk::TL1_TraceRouteRspBlk( const TL1_TraceRouteRspBlk& t1Blk ) :
                        myBitSet( INDEX_END, false )
{
    myBitSet=   t1Blk.myBitSet;
    myHopCount= t1Blk.myHopCount;
    myRsp=      t1Blk.myRsp;
    myIpAddr=   t1Blk.myIpAddr;
    myRespTime= t1Blk.myRespTime;
    myIpv6Addr = t1Blk.myIpv6Addr;
}

TL1_TraceRouteRspBlk::~TL1_TraceRouteRspBlk( )
{
}

TL1_TraceRouteRspBlk& 
TL1_TraceRouteRspBlk::operator=( const TL1_TraceRouteRspBlk& t1Blk )
{
    myHopCount = t1Blk.myHopCount;
    myRsp      = t1Blk.myRsp;
    myIpAddr   = t1Blk.myIpAddr;
    myRespTime = t1Blk.myRespTime;
	myIpv6Addr = t1Blk.myIpv6Addr;

    return *this;
}

bool 
TL1_TraceRouteRspBlk::operator==( const TL1_TraceRouteRspBlk& t1Blk ) const
{
    if ( myHopCount != t1Blk.myHopCount )
        return false;

    if ( myRsp != t1Blk.myRsp )
        return false;

    if ( myIpAddr != t1Blk.myIpAddr )
        return false;

    if ( myRespTime != t1Blk.myRespTime )
        return false;

	if(myIpv6Addr != t1Blk.myIpv6Addr)
	{
		return false;
	}

    return true;
}

//--------------------------------------------------------------
bool 
TL1_TraceRouteRspBlk::GetHopCount( int& theHopCount ) const
{
    if( true == myBitSet[ INDEX_HopCount ] )
    {
        theHopCount = myHopCount;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_TraceRouteRspBlk::SetHopCount( int theHopCount )
{
   myBitSet[ INDEX_HopCount ] = true;
   myHopCount = theHopCount;
}

//--------------------------------------------------------------
bool 
TL1_TraceRouteRspBlk::GetRsp( CT_TraceRoute& theRsp ) const
{
    if( true == myBitSet[ INDEX_Rsp ] )
    {
        theRsp = myRsp;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_TraceRouteRspBlk::SetRsp( CT_TraceRoute theRsp )
{
    myBitSet[ INDEX_Rsp ] = true;
    myRsp = theRsp;
}

//--------------------------------------------------------------
bool 
TL1_TraceRouteRspBlk::GetIpAddr( uint32& theIpAddr ) const
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
TL1_TraceRouteRspBlk::GetIpV6Addr(PingIpv6Addr &vIpv6Addr)  const
{
    if(myBitSet[ INDEX_Ipv6Addr ])
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
TL1_TraceRouteRspBlk::SetIpAddr( uint32 theIpAddr )
{
    myBitSet[ INDEX_IpAddr ] = true;
    myIpAddr = theIpAddr;
}

void TL1_TraceRouteRspBlk::SetIpAddr(const PingIpv6Addr &vIpv6Addr)
{
    myBitSet[ INDEX_Ipv6Addr ] = true;
    myIpv6Addr = vIpv6Addr;
}

//--------------------------------------------------------------
bool 
TL1_TraceRouteRspBlk::GetRespTime( uint32& theRespTime ) const
{
    if( true == myBitSet[ INDEX_RespTime ] )
    {
        theRespTime = myRespTime;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_TraceRouteRspBlk::SetRespTime( uint32 theRespTime )
{
    myBitSet[ INDEX_RespTime ] = true;
    myRespTime = theRespTime;
}


