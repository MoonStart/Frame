/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         Nov. 12, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Security Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SECUDOMAIN_H__
#define __TL1_SECUDOMAIN_H__

#ifndef __TL1_RESPONSE_H__
    #include <Response/TL1_Response.h>
#endif

#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Ftp.h>

/**
   CLASS TL1_SecuDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_SecuDomain
{
public:

    virtual void RtrvSecuSys(TL1_Response& theResponse )const = 0;

    virtual void EdSecuSys(int*  theLoginTries,
    int*  theSuspensionDuration,
    int*  thePasswordCount,
    bool* thePwdCompl,
    int*  theInactivityTimeout,
    int*  theWarningPeriod,
    CT_SecureMode* theSecureMode,
    TL1_Response& theResponse ) = 0;

    virtual void EdWarning(string* theWarnMesg,
    TL1_Response& theResponse ) = 0;

    virtual void RtrvWarning(TL1_Response& theResponse ) const = 0;

    virtual void RtrvPwdExpireMesg(TL1_Response& theResponse ) const = 0;

    virtual void IsLockedOut( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void ValidateActUser( const string  theUserId,
                                  TL1_Response& theResponse ) const= 0;

    virtual bool ValidateLoginCaseInsensitive( const string theUserId,
                                               const string thePassword,
                                               TL1_Response& theResponse ) const= 0;

    virtual void GetUserStatus( const string  theUserId,
    TL1_Response& theResponse) const= 0; 

    virtual void GetLoginMsg( const string theUserId,
    TL1_Response& theResponse) const = 0;

    virtual void GetUserSessionMax( const string theUserId,
    TL1_Response& theResponse) const = 0;

    virtual void GetUserPwdConstrained( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void GetUserPasswordExpireLoginNum( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void GetUserMsgFilters( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void GetSnmpPrivProtocol( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void GetSnmpUserSecLevel( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void GetSnmpAuthProtocol( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual unsigned int GetUserSessionMask( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void GetSshKeyUrl( const string  theUserId,
    TL1_Response& theResponse) const= 0;

    virtual void IncrementUnknownUIDLoginAttempt(
    const unsigned long theIPAddress,
    const string  theIPv6Address,
    TL1_Response& theResponse)= 0;

    virtual void SecuIncrementWrongPassword(
    const string  theUserId,
    const unsigned long theIPAddress,
    const string  theIPv6Address,
    TL1_Response& theResponse)= 0;

    virtual void SuccessfullLogin(
    const string  theUserId,
    TL1_Response& theResponse)= 0;

    virtual void LogoutUser(
    const string  theUserId,
    TL1_Response& theResponse)= 0;

    virtual bool  ValidateAddUser(     const string  theUserId,
    const string  thePassword,
    const string  theRole,
    const string  theCLIRole,
    const string  theSNMPRole,
    const string  theEncryptPwd,
    const uint16* theSessionTimeout,
    const uint16* theSessionMax,
    const uint16* thePasswordAging,
    const uint16* thePasswordUpdateWaiting,
    const uint8*  thePasswordExpireLoginNum,
    const int*    theStatus,
    bool&         theExistStatus,
    const int*    theSnmpUserSecLevel,
    const int*    theSnmpAuthProtocol,
    const string* theSnmpAuthPassphrase,
    const int*    theSnmpPrivProtocol,
    const string* theSnmpPrivPassphrase,
    TL1_Response& theResponse)= 0;

    virtual bool AddUser(     const string          theUserId,
    const string          thePassword,
    const string          theEncryptPassword,
    const string          theRole,
    const string          theCLIRole,
    const string          theSNMPRole,
    const int             theEncryptPasswordType,
    const uint16          theSessionTimeout,
    const uint16          theSessionMax,
    const uint16          thePasswordAging,
    const uint16          thePasswordUpdateWaiting,
    const uint8           thePasswordExpireLoginNum,
    const int             theStatus,
    const unsigned int    theAlmMsg, 
    const unsigned int    theDbchgMsg, 
    const unsigned int    theEvtMsg, 
    const unsigned int    thePmMsg,
    const int     theSnmpUserSecLevel,
    const int     theSnmpAuthProtocol,
    const string  theSnmpAuthPassphrase,
    const int     theSnmpPrivProtocol,
    const string  theSnmpPrivPassphrase,

    const string  theEncryptSnmpAuthPassphrase,
    const string  theEncryptSnmpPrivPassphrase,
    const int     theEncryptSnmpAuthPassphraseType,
    const int     theEncryptSnmpPrivPassphraseType,
    const CT_FtpUrl*      theSshKeySrcUrl,
    const string*         theSshKeySrcUrlAsString,

    TL1_Response& theResponse)= 0;

    virtual bool ValidateEditUser(    const string   theUserId,
    const bool     isUserAdmin,
    const string*  thePassword,
    const string*  theEncryptPassword,
    const string*  theRole,
    const string*  theCLIRole,
    const string*  theSNMPRole,
    const uint16*  theSessionTimeout,
    const uint16*  theSessionMax,
    const uint16*  thePasswordAging,
    const uint16*  thePasswordUpdateWaiting,
    const uint8*   thePasswordExpireLoginNum,
    const int*     theStatus,
    const unsigned int* theAllowAlm,
    const  unsigned int* theAllowDbchg,
    const  unsigned int* theAllowEvt,
    const  unsigned int* theAllowPm,
    const int*     theSnmpUserSecLevel,
    const int*     theSnmpAuthProtocol,
    const string*  theSnmpAuthPassphrase,
    const int*     theSnmpPrivProtocol,
    const string*  theSnmpPrivPassphrase,    
    const CT_FtpUrl*      theSshKeySrcUrl,
    const string*         theSshKeyToDelete,
    TL1_Response& theResponse)= 0;


    virtual bool EditUser(    const string          theUserId,
    const bool            isUserAdmin,
    const string*         thePassword,
    const string*         theEncryptPassword,
    const string*         theRole,
    const string*         theCLIRole,
    const string*         theSNMPRole,
    const int*            theEncryptPasswordType,
    const uint16*         theSessionTimeout,
    const uint16*         theSessionMax,
    const uint16*         thePasswordAging,
    const uint16*         thePasswordUpdateWaiting,
    const uint8*          thePasswordExpireLoginNum,
    const int*            theStatus,
    const unsigned int*   theAlmMsg, 
    const unsigned int*   theDbchgMsg, 
    const unsigned int*   theEvtMsg, 
    const unsigned int*   thePmMsgconst,
    const int*            theSnmpUserSecLevel,
    const int*            theSnmpAuthProtocol,
    const string*         theSnmpAuthPassphrase,
    const int*            theSnmpPrivProtocol,
    const string*         theSnmpPrivPassphrase,
    const string*         theEncryptSnmpAuthPassphrase,
    const string*         theEncryptSnmpPrivPassphrase,
    const int*            theEncryptSnmpAuthPassphraseType,
    const int*            theEncryptSnmpPrivPassphraseType,
    const CT_FtpUrl*      theSshKeySrcUrl,
    const string*         theSshKeySrcUrlAsString,
    const string*         theSshKeyToDelete,
    TL1_Response&         theResponse)= 0;

    virtual bool ValidateDeleteUser(  const string  theUserId,
    TL1_Response& theResponse)= 0;

    virtual void DeleteUser(  const string  theUserId,
    TL1_Response& theResponse)= 0;

    virtual void RetrieveSshKeys( const string theUserId,
                                  const int theFormat,
                                  TL1_Response& theResponse)= 0;

    virtual void EntRadServer(const CT_TL1_LogicalAddr&  theAddr,
    uint32*             theRadServerIp,
    const string*       theSharedSecret,
    TL1_Response& theResponse )= 0;

    virtual void EdRadServer(const CT_TL1_LogicalAddr&  theAddr,
    uint32*             theRadServerIp,
    const string*       theSharedSecret,
    TL1_Response& theResponse )= 0;

    virtual void DltRadServer(const CT_TL1_LogicalAddr&  theAddr,
    TL1_Response& theResponse )= 0;

    virtual void RtrvRadServer(const string theAidStr,
    const CT_TL1_LogicalAddr&  theAddr,
    TL1_Response& theResponse )=0;

    virtual void RadiusUserSuccessfullLogin(TL1_Response& theResponse)=0;
    
    virtual void EntAaa(uint32*             theIp,
    const string*       theSharedSecret,
    CT_AaaProto*   theProto,
    CT_AaaRole*    theRole,
    int*         theTimeout,
    int*         theRetry,
    TL1_Response& theResponse )= 0;

    virtual void EdAaa(uint32*             theIp,
    const string*       theSharedSecret,
    CT_AaaProto*   theProto,
    CT_AaaRole*    theRole,
    int*         theTimeout,
    int*         theRetry,
    TL1_Response& theResponse )= 0;

    virtual void DltAaa(uint32*             theIp,
    CT_AaaProto   theProto,
    CT_AaaRole    theRole,
    TL1_Response& theResponse )= 0;

    virtual void RtrvAaa(uint32*             theIp,
    CT_AaaProto*   theProto,
    CT_AaaRole*    theRole,
    TL1_Response& theResponse )=0;

};

#endif
