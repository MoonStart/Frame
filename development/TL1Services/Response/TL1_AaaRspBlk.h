/*-----------------------------------------------------------------------------
   Copyright(c) Coriant Group Inc. All rights reserved.

SUBSYSTEM:      TL1 
TARGET:
AUTHOR   :      Apr 2015 - Gang Sun
DESCRIPTION:    Header for Retreive AAA Server Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_AAARSPBLK_H_
#define __TL1_AAARSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_SYSTEM_IDS_H__
    #include <CommonTypes/CT_SystemIds.h>
#endif

#ifdef __cplusplus
#include <ss_gdef.h>
#endif

#include <vector>

using namespace std;

class TL1_AaaRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_AaaRspBlk(){};
    
    TL1_AaaRspBlk(const TL1_AaaRspBlk& theBlock);

    TL1_AaaRspBlk(const TL1_SmartParameter<uint32>&  theIpAddr,
                        const TL1_SmartParameter<string>&  theIpStr,
                        const TL1_SmartParameter<string>&  theSharedSecret,
                        const TL1_SmartParameter<CT_AaaProto>&  theProto,
                        const TL1_SmartParameter<CT_AaaRole>&  theRole,
                        const TL1_SmartParameter<int>&  theTimeout,
                        const TL1_SmartParameter<int>&  theRetry );
                 
    virtual ~TL1_AaaRspBlk(){};

    TL1_AaaRspBlk& operator=( const TL1_AaaRspBlk& theBlock );

    const TL1_SmartParameter<uint32>&
        GetIpAddr() const
    {
        return itsIpAddr;
    }

    const TL1_SmartParameter<string>& 
        GetSharedSecret() const
    {
        return itsSharedSecret;
    }

    const TL1_SmartParameter<string>& 
        GetServerIpStr() const
    {
        return itsIpStr;
    }

    const TL1_SmartParameter<CT_AaaProto>& 
        GetProto() const
    {
        return itsProto;
    }

    const TL1_SmartParameter<CT_AaaRole>& 
        GetRole() const
    {
        return itsRole;
    }

    const TL1_SmartParameter<int>& 
        GetTimeout() const
    {
        return itsTimeout;
    }

    const TL1_SmartParameter<int>& 
        GetRetry() const
    {
        return itsRetry;
    }

    void SetIpAddr(const TL1_SmartParameter<uint32>&  theIpAddr)
    {
        itsIpAddr = theIpAddr;
    }

    void SetSharedSecret(const TL1_SmartParameter<string>&  theSharedSecret)
    {
        itsSharedSecret = theSharedSecret;
    }

    void SetServerIpStr(const TL1_SmartParameter<string>&  theIpStr) 
    {
        itsIpStr = theIpStr;
    }

    void SetProto(const TL1_SmartParameter<CT_AaaProto>&  theProto)
    {
        itsProto = theProto;
    }

    void SetRole(const TL1_SmartParameter<CT_AaaRole>&  theRole)
    {
        itsRole = theRole;
    }

    void SetTimeout(const TL1_SmartParameter<int>&  theTimeout)
    {
        itsTimeout = theTimeout;
    }

    void SetRetry(const TL1_SmartParameter<int>&  theRetry)
    {
        itsRetry = theRetry;
    }

private:
    TL1_SmartParameter<uint32>     itsIpAddr;
    TL1_SmartParameter<string>     itsIpStr;
    TL1_SmartParameter<string>     itsSharedSecret;
    TL1_SmartParameter<CT_AaaProto>     itsProto;
    TL1_SmartParameter<CT_AaaRole>     itsRole;
    TL1_SmartParameter<int>     itsTimeout;
    TL1_SmartParameter<int>     itsRetry;
};

typedef TL1_Rtv_Response< TL1_AaaRspBlk > TL1_AaaResponse;

#endif



