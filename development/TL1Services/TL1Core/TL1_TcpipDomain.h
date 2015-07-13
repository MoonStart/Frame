#ifndef __TL1_TCPIPDOMAIN_H__
#define __TL1_TCPIPDOMAIN_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
DESCRIPTION:    Header file for TL1 TCPIP Domain declaration
LAST REVISION:
   Date    Description
   ----    -----------
 11-02-10  t71mr00135122:Initial entry.
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 strings gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_IPSEC_H__
#include <CommonTypes/CT_IpSec.h>
#endif

#include <Agent/DBManagement/DBM_DbReqRegion.h>

#include <CT_TL1_LogicalAddr.h> // Do we need this?

/**
   CLASS TL1_TcpipDomain 

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_TcpipDomain
{
public:
    
    virtual void EdTcpipReq( const string& theTcpipAid,
                             CT_DupAddrDetCnt* theDupAddrDetCnt,
                             CT_DupAddrDetTmr* theDupAddrDetTmr,
                             CT_SecurityEnable* theTelnetEnable,
                             CT_SecurityEnable* theFtpEnable,
                             CT_SecurityEnable* theHttpEnable,
                             CT_SshAuthentication* theSshAuthentication,
                             CT_SshKeyStrength* theSshKeyStrength,
                             bool* theCommandMode,
                             TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvTcpipReq( const string& theTcpipAid,
                               CT_ShowFP* theShowFP,
                               CT_Yes_No* theShowKey,
                               TL1_Response& tl1RspBlk ) = 0;
};
#endif
