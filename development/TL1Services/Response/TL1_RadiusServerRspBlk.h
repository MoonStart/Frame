/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         Feb. 24, 2009- Crystal Guo
DESCRIPTION:    Header for Retreive Radius Server Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RADSERVERRSPBLK_H_
#define __TL1_RADSERVERRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifdef __cplusplus
#include <ss_gdef.h>
#endif

#include <vector>

using namespace std;

class TL1_RadServerRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RadServerRspBlk(){};
    
    TL1_RadServerRspBlk(const TL1_RadServerRspBlk& theBlock);

    TL1_RadServerRspBlk(const TL1_SmartParameter<string>&  theRadServer,
                        const TL1_SmartParameter<uint32>&  theIpAddr,
                        const TL1_SmartParameter<string>&  theIpStr,
                        const TL1_SmartParameter<string>&  theSharedSecret );
                 
    virtual ~TL1_RadServerRspBlk(){};

    TL1_RadServerRspBlk& operator=( const TL1_RadServerRspBlk& theBlock );

    const TL1_SmartParameter<string>&
        GetRadServer() const
    {
        return itsRadServer;
    }

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

    void SetRadServer(const TL1_SmartParameter<string>&  theRadServer)
    {
        itsRadServer = theRadServer;
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

private:
    TL1_SmartParameter<string>     itsRadServer;
    TL1_SmartParameter<uint32>     itsIpAddr;
    TL1_SmartParameter<string>     itsIpStr;
    TL1_SmartParameter<string>     itsSharedSecret;
};

typedef TL1_Rtv_Response< TL1_RadServerRspBlk > TL1_RadServerResponse;

#endif



