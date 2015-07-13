/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Conn Response Class
TARGET:
AUTHOR:         june 03, 2009 - Tom Novak
DESCRIPTION:    Header file for TL1 Opr Trace Route Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_TRACEROUTE_RESPONSE_BLOCK_H__
#define __TL1_TRACEROUTE_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_EON.h>

#include <CommonPlatforms/SoftwareServices/T6100/T7100_Ipv6Addr.h>

class TL1_TraceRouteRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_TraceRouteRspBlk( );
	
    TL1_TraceRouteRspBlk( const int             theHopCount,
                          const CT_TraceRoute   theRsp,
                          const uint32          theIpAddr,
                          const uint32             theRespTime );
 	
    TL1_TraceRouteRspBlk( const TL1_TraceRouteRspBlk& );
    
    virtual ~TL1_TraceRouteRspBlk();

    TL1_TraceRouteRspBlk& operator=( const TL1_TraceRouteRspBlk& t1Blk );

    bool operator==( const TL1_TraceRouteRspBlk& t1Blk ) const;

    bool GetHopCount( int& theHopCount ) const;
    bool GetRsp( CT_TraceRoute& theRsp ) const;
    bool GetIpAddr( uint32& theIpAddr ) const;
    bool GetIpV6Addr(PingIpv6Addr &vIpv6Addr) const ;
    
    bool GetRespTime( uint32& theRespTime ) const;

    void SetHopCount( int theHopCount );
    void SetRsp( CT_TraceRoute theRsp );
    void SetIpAddr( uint32 theIpAddr );
    void SetIpAddr(const PingIpv6Addr &vIpv6Addr);
    void SetRespTime( uint32 theRespTime );

private:
    enum 
    {
        INDEX_HopCount = 0,
        INDEX_Rsp,
        INDEX_IpAddr,
        INDEX_Ipv6Addr,
        INDEX_RespTime,
        INDEX_END
    };

    vector<bool>    myBitSet;

    int             myHopCount;
    CT_TraceRoute   myRsp;
    uint32          myIpAddr;
    PingIpv6Addr    myIpv6Addr;
    uint32          myRespTime;
};

typedef TL1_Rtv_Response< TL1_TraceRouteRspBlk > TL1_TraceRouteResponse;
#endif  // #ifndef __TL1_TRACEROUTE_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
