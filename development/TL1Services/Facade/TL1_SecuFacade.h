/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         Nov. 13, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Security Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SECUFACADE_H__
#define __TL1_SECUFACADE_H__

#ifndef __TL1_SECUENTITY_H__
#include <TL1Core/TL1_SecuEntity.h>
#endif

#ifndef __TL1_IPSECENTITY_H__
#include <TL1Core/TL1_IpSecEntity.h>
#endif

#ifndef __FC_BBOBJECT_H__
#include <Blackboard/FC_BbObject.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvSecuSys( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSecuSys( theResponse ))

#define FACI_EdSecuSys( theLoginTries, theSuspensionDuration, thePasswordCount, thePwdCompl, theInactivityTimeout, theWarningPeriod, theSecureMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSecuSys( theLoginTries, theSuspensionDuration, thePasswordCount, thePwdCompl, theInactivityTimeout, theWarningPeriod, theSecureMode, theResponse ))

#define FACI_RtrvWarning( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvWarning( theResponse ))

#define FACI_RtrvPwdExpireMesg( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPwdExpireMesg( theResponse ))

#define FACI_RtrvLoginMsg(theUserId, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetLoginMsg( theUserId, theResponse ))

#define FACI_EdWarning( theWarnMesg, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdWarning( theWarnMesg, theResponse ))

#define FACI_EdPwdExpireMesg( theWarnMesg, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdPwdExpireMesg( theWarnMesg, theResponse ))

#define FACI_IsLockedOut( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, IsLockedOut( theUserId, theResponse ))

#define FACI_ValidateActUser( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ValidateActUser( theUserId, theResponse ))

#define FACI_GetUserStatus( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetUserStatus( theUserId, theResponse ))

#define FACI_GetUserPwdConstrained( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetUserPwdConstrained( theUserId, theResponse ))

#define FACI_GetUserMsgFilters( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetUserMsgFilters( theUserId, theResponse ))

#define FACI_GetUserSessionMask( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetUserSessionMask( theUserId, theResponse ))

#define FACI_GetUserSshKeys( theUserId, theFormat, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RetrieveSshKeys( theUserId, theFormat, theResponse ))

#define FACI_GetUserSessionMax( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetUserSessionMax( theUserId, theResponse ))

#define FACI_GetUserPasswordExpireLoginNum( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetUserPasswordExpireLoginNum( theUserId, theResponse ))

#define FACI_GetUserSessionMax( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetUserSessionMax( theUserId, theResponse ))

#define FACI_GetSnmpUserSecLevel( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetSnmpUserSecLevel( theUserId, theResponse ))

#define FACI_GetSnmpAuthProtocol( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetSnmpAuthProtocol( theUserId, theResponse ))

#define FACI_GetSnmpPrivProtocol( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetSnmpPrivProtocol( theUserId, theResponse ))

#define FACI_GetSshKeyUrl( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetSshKeyUrl( theUserId, theResponse ))

#define FACI_IncrementUnknownUIDLoginAttempt(theIPAddress, theIPv6Address, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, IncrementUnknownUIDLoginAttempt(theIPAddress, theIPv6Address, theResponse ))

#define FACI_IncrementWrongPassword( theUserId, theIPAddress, theIPv6Address, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SecuIncrementWrongPassword( theUserId, theIPAddress, theIPv6Address, theResponse ))

#define FACI_SuccessfullLogin( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SuccessfullLogin( theUserId, theResponse ))

#define FACI_RadiusUserSuccessfullLogin( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RadiusUserSuccessfullLogin( theResponse ))

#define FACI_LogoutUser( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, LogoutUser( theUserId, theResponse ))

#define FACI_ValidateLoginCaseInsensitive( theUserId, thePassword, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ValidateLoginCaseInsensitive( theUserId, thePassword, theResponse ))

#define FACI_ValidateAddUser( theUserId, thePassword, theRole, theCLIRole, theSNMPRole, theEncryptPwd, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum, theStatus, theExistStatus,theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ValidateAddUser( theUserId, thePassword, theRole, theCLIRole, theSNMPRole, theEncryptPwd, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum, theStatus, theExistStatus,theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse, theResponse ))

#define FACI_AddUser( theUserId, thePassword, theEncryptPassword,theRole, theCLIRole, theSNMPRole, theEncryptPasswordType, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum, theStatus, theAlmMsg, theDbchgMsg, theEvtMsg, thePmMsg,theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse, theEncryptSnmpAuthPasspharse,theEncryptSnmpPrivPasspharse, theEncryptSnmpAuthPasspharseType,theEncryptSnmpPrivPasspharseType, theSshKeySrcUrl, theSshKeySrcUrlAsString, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, AddUser( theUserId, thePassword, theEncryptPassword, theRole, theCLIRole, theSNMPRole, theEncryptPasswordType, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum, theStatus, theAlmMsg, theDbchgMsg, theEvtMsg, thePmMsg,theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse, theEncryptSnmpAuthPasspharse,theEncryptSnmpPrivPasspharse, theEncryptSnmpAuthPasspharseType,theEncryptSnmpPrivPasspharseType, theSshKeySrcUrl, theSshKeySrcUrlAsString, theResponse ))

#define FACI_ValidateEditUser( theUserId, isUserAdmin, thePassword,theEncryptPassword, theRole, theCLIRole, theSNMPRole, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum,theStatus, theAllowAlm,theAllowDbchg,theAllowEvt,theAllowPm, theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse, theSshKeySrcUrl, theSshKeyToDelete, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ValidateEditUser( theUserId, isUserAdmin, thePassword, theEncryptPassword, theRole, theCLIRole, theSNMPRole, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum,theStatus,theAllowAlm,theAllowDbchg,theAllowEvt,theAllowPm, theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse,theSshKeySrcUrl,theSshKeyToDelete,theResponse ))

#define FACI_EditUser( theUserId, isUserAdmin, thePassword,  theEncryptPassword, theRole, theCLIRole, theSNMPRole, theEncryptPasswordType, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum, theStatus, theAlmMsg, theDbchgMsg, theEvtMsg, thePmMsg,theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse, theEncryptSnmpAuthPasspharse,theEncryptSnmpPrivPasspharse,theEncryptSnmpAuthPasspharseType, theEncryptSnmpPrivPasspharseType, theSshKeySrcUrl, theSshKeySrcUrlAsString, theSshKeyToDelete, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EditUser( theUserId, isUserAdmin, thePassword, theEncryptPassword, theRole, theCLIRole, theSNMPRole, theEncryptPasswordType, theSessionTimeout, theSessionMax, thePasswordAging, thePasswordUpdateWaiting, thePasswordExpireLoginNum, theStatus, theAlmMsg, theDbchgMsg, theEvtMsg, thePmMsg,theSnmpUserSecLevel,theSnmpAuthProtocol,theSnmpAuthPasspharse,theSnmpPrivProtocol,theSnmpPrivPasspharse,  theEncryptSnmpAuthPasspharse,theEncryptSnmpPrivPasspharse,theEncryptSnmpAuthPasspharseType, theEncryptSnmpPrivPasspharseType, theSshKeySrcUrl, theSshKeySrcUrlAsString, theSshKeyToDelete, theResponse ))

#define FACI_ValidateDeleteUser( theUserId,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ValidateDeleteUser( theUserId, theResponse ))

#define FACI_DeleteUser( theUserId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DeleteUser( theUserId, theResponse ))

#define FACI_SetIpSecReq( theIsEnabled, theIpAddress, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetIpSecRequest( theIsEnabled, theIpAddress, theResponse ))

#define FACI_RtrvIpSecReq( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIpSecRequest( theResponse ))

#define FACI_EntPskReq( theAddr, theKey, theIdentifier, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntPskRequest( theAddr, theKey, theIdentifier, theResponse ) )

#define FACI_RtrvPskReq( theAidStr, theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPskRequest( theAidStr, theAddr, theResponse ))

#define FACI_DltPskReq( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltPskRequest( theAddr, theResponse ))

#define FACI_EntSpdReq( theAddr, theName, theLocalAddr, theRemoteAddr, theLocalPort, theRemotePort, theTransProt, theSpdAction, theSpdMode, theSpdSuite, theIkeVersion, theIkeAuth, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntSpdRequest( theAddr, theName, theLocalAddr, theRemoteAddr, theLocalPort, theRemotePort, theTransProt, theSpdAction, theSpdMode, theSpdSuite, theIkeVersion, theIkeAuth, theResponse ) )

#define FACI_EdSpdReq( theAddr, theName, theLocalAddr, theRemoteAddr, theLocalPort, theRemotePort, theTransProt, theSpdAction, theSpdMode, theSpdSuite, theIkeVersion, theIkeAuth, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSpdRequest( theAddr, theName, theLocalAddr, theRemoteAddr, theLocalPort, theRemotePort, theTransProt, theSpdAction, theSpdMode, theSpdSuite, theIkeVersion, theIkeAuth, theResponse ) )

#define FACI_RtrvSpdReq( theAidStr, theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSpdRequest( theAidStr, theAddr, theResponse ))

#define FACI_DltSpdReq( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltSpdRequest( theAddr, theResponse ))

#define FACI_EntCert( theCertAid, theEncryptionPwd, theIntegrityPwd, theUrl, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntCert( theCertAid,  theEncryptionPwd, theIntegrityPwd, theUrl,theResponse))

#define FACI_EdCert( theCertAid, theCertActive, theCertMinExpThreshold, theCertMajExpThreshold, theCertAlarmProfile, theCertPrimaryState, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdCert( theCertAid,  theCertActive, theCertMinExpThreshold, theCertMajExpThreshold, theCertAlarmProfile,theCertPrimaryState, theResponse))

#define FACI_RtrvCert( theCertAid, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCert( theCertAid, theResponse))

#define FACI_DltCert( theCertAid, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltCert( theCertAid, theResponse))

#define FACI_EntRadServer( theAddr, theRadServerIp, theSharedSecret, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntRadServer( theAddr, theRadServerIp, theSharedSecret, theResponse ))

#define FACI_EdRadServer( theAddr, theRadServerIp, theSharedSecret, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdRadServer( theAddr, theRadServerIp, theSharedSecret, theResponse ))

#define FACI_DltRadServer( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltRadServer( theAddr, theResponse ))

#define FACI_RtrvRadServer( theAidStr, theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvRadServer( theAidStr, theAddr, theResponse ))

#define FACI_EntAaa( theIp, theSharedSecret, theProto, theRole, theTimeout, theRetry, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntAaa( theIp, theSharedSecret, theProto, theRole, theTimeout, theRetry, theResponse ))

#define FACI_EdAaa( theIp, theSharedSecret, theProto, theRole, theTimeout, theRetry, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdAaa( theIp, theSharedSecret, theProto, theRole, theTimeout, theRetry, theResponse ))

#define FACI_DltAaa( theIp, theProto, theRole, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltAaa( theIp, theProto, theRole, theResponse ))

#define FACI_RtrvAaa( theIp, theProto, theRole, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAaa( theIp, theProto, theRole, theResponse ))

#endif
