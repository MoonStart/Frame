#ifndef __TL1_IPSECDOMAIN_H__
#define __TL1_IPSECDOMAIN_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         October 19, 2005- Mike Rodgers
DESCRIPTION:    Header file for TL1 IPSEC Domain declaration
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

#include <CT_TL1_LogicalAddr.h>

/**
   CLASS TL1_IpSecDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_IpSecDomain
{
public:
    
    virtual void SetIpSecRequest(bool theIsEnabled,
                             string* theIpAddress,
                             TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvIpSecRequest( TL1_Response& tl1RspBlk ) = 0;
    
    virtual void EntSpdRequest(const CT_TL1_LogicalAddr16& theAddr,
                               string* theName,
                               string* theLocalAddress,
                               string* theRemoteAddress,
                               string* theLocalPort,
                               string* theRemotePort,
                               string* theProtocol,
                               CT_SecuSpdPolicyType* theAction,
                               CT_SecuSpdModeType* theConnectionType,
                               CT_SecuSpdSuite* theAlgorithmSuite,
                               CT_SecuIkeVersion* theIkeVersion,
                               string* theIkeAuthorization,
                               TL1_Response& tl1RspBlk) = 0;

    virtual void EdSpdRequest(const CT_TL1_LogicalAddr16& theAddr,
                               string* theName,
                               string* theLocalAddress,
                               string* theRemoteAddress,
                               string* theLocalPort,
                               string* theRemotePort,
                               string* theProtocol,
                               CT_SecuSpdPolicyType* theAction,
                               CT_SecuSpdModeType* theConnectionType,
                               CT_SecuSpdSuite* theAlgorithmSuite,
                               CT_SecuIkeVersion* theIkeVersion,
                               string* theIkeAuthorization,
                              TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvSpdRequest(const string theAidStr,
                                const CT_TL1_LogicalAddr16& theAddr,
                                TL1_Response& tl1RspBlk) = 0;

    virtual void DltSpdRequest( const CT_TL1_LogicalAddr16& theAddr,
                                TL1_Response& tl1RspBlk) = 0;


    virtual void EntCert( string& theCertAid,
                          string* theEncryptionPwd,
                          string* theIntegrityPwd,
                          CT_FtpUrl* theSrcUrl,
                          TL1_Response& tl1RspBlk ) = 0;

    virtual void EdCert( string& theCertAid, 
                         CT_Yes_No* theCertActive,
                         CT_MinorExpThreshold* theCertMinExpThreshold,
                         CT_MajorExpThreshold* theCertMajExpThreshold,
                         CT_AlarmProfile* theCertAlarmProfile,
                         CT_EditablePST* theCertPrimaryState,
                         TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvCert( string& theCertAid, TL1_Response& tl1RspBlk ) = 0;

    virtual void DltCert( string& theCertAid, TL1_Response& tl1RspBlk ) = 0;


    virtual void EntPskRequest( const CT_TL1_LogicalAddr16& theAddr,
                                string* theKey,
                                string* theIdentifier,
                                TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvPskRequest( const string theAidStr,
                                 const CT_TL1_LogicalAddr16& theAddr,
                                 TL1_Response& tl1RspBlk) = 0;

    virtual void DltPskRequest( const CT_TL1_LogicalAddr16& theAddr,
                                TL1_Response& tl1RspBlk) = 0;
};

#endif
