/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Static Route Response Class
TARGET:
AUTHOR:         July 17, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Retrive Static Route Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_STATRTE_RESPONSE_BLOCK_H__
#define __TL1_STATRTE_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#include <CommonTypes/CT_EON.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>

class TL1_StatRteRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_StatRteRspBlk( );
	#if 0
    TL1_StatRteRspBlk( const uint32*            theDestination,
                       const uint32*            theNetmask,
                       const CT_TL1_LinkAddr*   theTLAid,
                       const CT_IfNumber*       theIfName,
                       const uint32*            theNexthop,
                       const bool*              theAdvertise );
	#endif
    TL1_StatRteRspBlk(const TL1_StatRteRspBlk& );
    
    virtual ~TL1_StatRteRspBlk();

    TL1_StatRteRspBlk& operator=( const TL1_StatRteRspBlk& t1Blk );

    bool operator==( const TL1_StatRteRspBlk& t1Blk ) const;

    bool GetDestination( uint32& theDestination ) const;
    bool GetNetmask( uint32& theNetmask ) const;
    bool GetTLAid( CT_TL1_LinkAddr& theTLAid ) const;
    bool GetIfName( CT_IfNumber& theIfName ) const;
    bool GetNexthop( uint32& theNexthop ) const;
    bool GetAdvertise( bool& theAdvertise ) const;

    void SetDestination( const uint32& theDestination );
    void SetNetmask( const uint32& theNetmask );
    void SetTLAid( const CT_TL1_LinkAddr& theTLAid );
    void SetIfName( const CT_IfNumber& theIfName );
    void SetNexthop( const uint32& theNexthop );
    void SetAdvertise( const bool& theAdvertise );

    bool GetIpv6Destination( string& theDestination ) const;
    bool GetIpv6Nexthop( string& theNexthop ) const;

    void SetDestination( const string& theDestination );
    void SetNexthop( const string& theNexthop );
    

private:
    enum 
    {
        INDEX_Destination = 0,
        INDEX_Netmask,	
        INDEX_TLAid,
        INDEX_IfName,
        INDEX_Nexthop,
        INDEX_Advertise,

        INDEX_IPV6_DESTINATION,
        INDEX_IPV6_NEXTHOP,
        INDEX_END
    };

    vector<bool>    myBitSet;

    uint32          myDestination;
    uint32          myNetmask;
    CT_TL1_LinkAddr myTLAid; 
    CT_IfNumber     myIfName;
    uint32          myNexthop;    
    bool            myAdvertise;

    string          myIpv6Destination;
    string          myIpv6Nexthop;
};

typedef TL1_Rtv_Response< TL1_StatRteRspBlk > TL1_StatRteResponse;

class TL1_RteAllRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_RteAllRspBlk( );
#if 0	
    TL1_RteAllRspBlk( const uint32*             	theDestination,
                      const uint32*             	theNetmask,
                      const uint32*             	theInterface,
                      const uint32*             	theNexthop,
					  const CT_IfNumber*			theIfname,
					  const CT_TL1_LinkAddr*		theTLAid,
					  const CT_TL1_ResourceAddr*	theResource,
					  const CT_RouteType*			theRtype );
#endif	
    TL1_RteAllRspBlk(const TL1_RteAllRspBlk& );
    
    virtual ~TL1_RteAllRspBlk();

    TL1_RteAllRspBlk& operator=( const TL1_RteAllRspBlk& t1Blk );

    bool operator==( const TL1_RteAllRspBlk& t1Blk ) const;

    bool GetDestination( uint32& theDestination ) const;
    bool GetIpv6Destination(string &theDestination) const;
    bool GetNetmask( uint32& theNetmask ) const;
    bool GetInterface( uint32& theInterface ) const;
    bool GetNexthop( uint32& theNexthop ) const;
    bool GetIpv6Nexthop(string &theNexthop) const;
	bool GetIfName( CT_IfNumber& theIfname ) const;
	bool GetTLAid( CT_TL1_LinkAddr& theTLAid ) const;
	bool GetResource( CT_TL1_ResourceAddr& theResource ) const;
	bool GetType( CT_RouteType& theRtype ) const;

    void SetDestination( const uint32& theDestination );
    void SetDestination(const string &theDestination);/*for ipv6*/
    void SetNetmask( const uint32& theNetmask );
    void SetInterface( const uint32& theInterface );
    void SetNexthop( const uint32& theNexthop );
    void SetNexthop(const string &theNexthop );/*for ipv6*/
	void SetIfName( const CT_IfNumber& theIfname );
	void SetTLAid( const CT_TL1_LinkAddr& theTLAid );
	void SetResource( const CT_TL1_ResourceAddr& theResource );
	void SetType( const CT_RouteType& theRtype );

private:
    enum 
    {
        INDEX_Destination = 0,
        INDEX_Netmask,	
        INDEX_Interface,
        INDEX_Nexthop,
        INDEX_Ifname,
        INDEX_TLAid,
        INDEX_Resource,
        INDEX_Rtype,

        INDEX_IPV6_DESTINATION,
        INDEX_IPV6_NEXTHOP,
        INDEX_END
    };

    vector<bool>                 myBitSet;

    uint32                       myDestination;
    uint32                       myNetmask;
    uint32                       myInterface; 
    uint32                       myNexthop;  
    CT_IfNumber                  myIfname;
	CT_TL1_LinkAddr				 myTLAid;
    CT_TL1_ResourceAddr          myResource;
    CT_RouteType                 myRtype; 

    string          myIpv6Destination;
    string          myIpv6Nexthop;
};

typedef TL1_Rtv_Response< TL1_RteAllRspBlk > TL1_RteAllResponse;

#endif  // #ifndef __TL1_STATRTE_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
