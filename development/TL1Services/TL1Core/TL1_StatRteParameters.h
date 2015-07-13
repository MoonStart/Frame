/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 17, 2007 - Tong Wu
DESCRIPTION:    Header file for Static Route TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_STATRTEPARAMETERS_H__
#define __TL1_STATRTEPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_STATRTERSPBLK_H__
#include <Response/TL1_StatRteRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>

#include <T6100/T7100_Ipv6Addr.h>

class TL1_StatRteParameters  
{
public:

    enum PARAM
    {
        INDEX_DESTINATION = 0,
        INDEX_PREFIXLEN,
        INDEX_NEXTHOP,
        INDEX_TLAID,
        INDEX_IFNAME,
        INDEX_ADVERTISE,
        INDEX_END
    };

    TL1_StatRteParameters();

    virtual ~TL1_StatRteParameters();

    TL1_StatRteParameters(const TL1_StatRteParameters& theInst );

    TL1_StatRteParameters& operator=( const TL1_StatRteParameters& theInst );

    bool operator==( const TL1_StatRteParameters& theInst ) const;

    static string RemoveQuotesFromParameter(const char *vpIpAddr);

    uint32                    GetDestination( ) const;
    string                    GetIpv6Destination( ) const;
    void                      SetDestination(string &theDestination );

    uint32                     GetPrefixLen() const;
    void                       SetPrefixLen(uint32 thePrefixLen);

    uint32                     GetNetmask( ) const;

    CT_TL1_LinkAddr           GetTLAid( ) const;
    void                       SetTLAid( CT_TL1_LinkAddr &theTLAid );

    CT_IfNumber           	  GetIfName( ) const;
    void                       SetIfName( CT_IfNumber theIfName );

    string                     GetIpv6Nexthop( ) const;
    uint32                     GetNexthop( ) const;
    void                       SetNexthop(const string &theNexthop );

    bool                       GetAdvertise( ) const;
    void                       SetAdvertise(bool theAdvertise);

    IpAddrType                GetAdrdrType( ) const;
    void                      SetAddrType(IpAddrType theType);

    bool                      GetParamValid(TL1_StatRteParameters::PARAM theParam);

private:
    
    vector<bool>    myBitSet;

    string          myDestination;
    uint32          myPrefixLen;/*netmask only can be used for ipv4,here if mask used it will convert to prefixlen*/
    string          myNexthop;
    CT_TL1_LinkAddr myTLAid;
    CT_IfNumber     myIfName;
    bool            myAdvertise;
    IpAddrType      myAddrType;
};




#endif
