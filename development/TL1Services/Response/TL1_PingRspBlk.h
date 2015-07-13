/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Conn Response Class
TARGET:
AUTHOR:         june 03, 2009 - Tom Novak
DESCRIPTION:    Header file for TL1 Opr Ping Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_PING_RESPONSE_BLOCK_H__
#define __TL1_PING_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_TL1_Base.h>

#include <CommonPlatforms/SoftwareServices/T6100/T7100_Ipv6Addr.h>

class TL1_PingRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_PingRspBlk( );
	
    TL1_PingRspBlk( const string theIpAddr,
                    const string theResult );
 	
    TL1_PingRspBlk( const TL1_PingRspBlk& );
    
    virtual ~TL1_PingRspBlk();

    TL1_PingRspBlk& operator=( const TL1_PingRspBlk& t1Blk );

    bool operator==( const TL1_PingRspBlk& t1Blk ) const;

    bool GetIpAddr( string& theIpAddr ) const;
    bool GetIpV6Addr(PingIpv6Addr &vIpv6Addr) const;
    bool GetResult( string& theResult ) const;

    void SetIpAddr( string &theIpAddr );
    void SetIpAddr(const PingIpv6Addr &vIpv6Addr);
    
    void SetResult( string& theResult );

private:
    enum 
    {
        INDEX_IpAddr = 0,
        INDEX_Ipv6Addr,
        INDEX_Result,
        INDEX_END
    };

    vector<bool>    myBitSet;

    string          myIpAddr;
    PingIpv6Addr    myIpv6Addr;
    string  myResult;
};

typedef TL1_Rtv_Response< TL1_PingRspBlk > TL1_PingResponse;
#endif  // #ifndef __TL1_PING_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
