/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Networking - TCPIP Response
TARGET:
AUTHOR:
DESCRIPTION:    Class interface for TL1 'RTRV-TCPIP' response 
-----------------------------------------------------------------------------*/
#ifndef __TL1_TCPIPRSPBLK_H_
#define __TL1_TCPIPRSPBLK_H_

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_SYSTEM_IDS_H_
#include <CommonTypes/CT_IpSec.h>
#endif

#include <vector>



//-----------------------------------------------------------------------------
// RTRV-TCPIP TL1 Response Block
//
class TL1_TcpipRspBlk : public TL1_GeneralRspBlk
{
public:

    /* Constructors & Destructors */
    TL1_TcpipRspBlk() {}
    
    virtual ~TL1_TcpipRspBlk() {}

    TL1_TcpipRspBlk( 
        const string*               theTcpipAid,
        const CT_DupAddrDetCnt*     theDupAddrDetCnt,
        const CT_DupAddrDetTmr*     theDupAddrDetTmr,
        const CT_SecurityEnable*    theTelnetEnable,
        const CT_SecurityEnable*    theFtpEnable,
        const CT_SecurityEnable*    theHttpEnable,
        const CT_SshAuthentication* theSshAuthentication,
        const CT_SshKeyStrength*    theSshKeyStrength,
        const string*               thePublicKeyFingerprint,
        const string*               thePublicKey );
                 
    TL1_TcpipRspBlk( const TL1_TcpipRspBlk& );

    /* Assignment operator */
    TL1_TcpipRspBlk& operator=( const TL1_TcpipRspBlk& theBlock );

    /* Equality operator */
    bool operator==( const TL1_TcpipRspBlk& theBlock ) const;

    /* Member 'get' methods */
    bool GetTcpipAid( string& theTcpipAid ) const ;
    bool GetDupAddrDetCnt( CT_DupAddrDetCnt& theDupAddrDetCnt ) const;
    bool GetDupAddrDetTmr( CT_DupAddrDetTmr& theDupAddrDetTmr ) const;
    bool GetTelnetEnable( CT_SecurityEnable& theTelnetEnable ) const;
    bool GetFtpEnable( CT_SecurityEnable& theFtpEnable ) const;
    bool GetHttpEnable( CT_SecurityEnable& theHttpEnable ) const;
    bool GetSshAuthentication( CT_SshAuthentication& theSshAuthentication) const;
    bool GetSshKeyStrength( CT_SshKeyStrength& theSshKeyStrength) const;
    bool GetPublicKeyFingerprint( string& thePublicKeyFingerprint ) const;
    bool GetPublicKey( string& thePublicKey ) const;


private:

    enum 
    {
        INDEX_TcpipAid = 0,
        INDEX_DupAddrDetCnt,
        INDEX_DupAddrDetTmr,
        INDEX_TelnetEnable,
        INDEX_FtpEnable,
        INDEX_HttpEnable,
        INDEX_SshAuthentication,
        INDEX_SshKeyStrength,
        INDEX_PublicKeyFingerprint,
        INDEX_PublicKey,
        INDEX_END
	};

    vector<bool>         myBitSet;  // Identifies which attributes are valid

    string		         myTcpipAid;
    CT_DupAddrDetCnt     myDupAddrDetCnt;
    CT_DupAddrDetTmr     myDupAddrDetTmr;
    CT_SecurityEnable    myTelnetEnable;
    CT_SecurityEnable    myFtpEnable;
    CT_SecurityEnable    myHttpEnable;
    CT_SshAuthentication mySshAuthentication;
    CT_SshKeyStrength    mySshKeyStrength;
    string               myPublicKeyFingerprint;
    string               myPublicKey;
};

typedef TL1_Rtv_Response< TL1_TcpipRspBlk > TL1_TcpipResponse;

#endif // __TL1_TCPIPRSPBLK_H_
