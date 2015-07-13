/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Equipment Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Equipment Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_SECUUSERRESPONSE_BLOCK_H_
#define __TL1_SECUUSERRESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#ifndef __CT_SYSTEM_IDS_H__
#include <CommonTypes/CT_SystemIds.h>
#endif


class TL1_SecuUserRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_SecuUserRspBlk(){}

    TL1_SecuUserRspBlk(const string* userId, const string* role, const string* clirole, const string* snmprole, const long sessionTimeout, const long passwordAging,
        const long passwordUpdateWaiting, const int status, const uint32 maxSession = 0, const uint32 almMsgAlw = 0, const uint32 dbchgMsgAlw = 0,
        const uint32 evtMsgAlw = 0, const uint32 pmMsgAlw = 0, const uint32 pwdConstrained = 0, const uint32 passwordExpireLoginNum = 0,
        const uint32 snmpUserSecLevel=0,const uint32 snmpAuthProtocol=0,const uint32 privProtocol=0, const string* sshUrl = 0);

    TL1_SecuUserRspBlk(const char* userId, const char* role, const char* clirole, const char* snmprole, const long sessionTimeout, const long passwordAging,
        const long passwordUpdateWaiting, const int status, const uint32 maxSession = 0,const uint32 almMsgAlw = 0, const uint32 dbchgMsgAlw = 0,
        const uint32 evtMsgAlw = 0, const uint32 pmMsgAlw = 0, const uint32 pwdConstrained = 0, const uint32 passwordExpireLoginNum = 0,
        const uint32 snmpUserSecLevel=0,const uint32 snmpAuthProtocol=0,const uint32 privProtocol=0, const char* sshUrl = 0);
                 
    TL1_SecuUserRspBlk(const TL1_SecuUserRspBlk& );
    
    virtual ~TL1_SecuUserRspBlk();

    TL1_SecuUserRspBlk& operator=( const TL1_SecuUserRspBlk& theBlock );

    bool GetUserID( string&) const ;

    bool GetRole( string& ) const;

    bool GetCLIRole( string& ) const;

    bool GetSNMPRole( string& ) const;

    bool GetSessionTimeout( long& ) const;

    bool GetSessionMax( long& ) const;

    bool GetPasswordAging( long& ) const;

    bool GetPasswordUpdateWaiting( long& ) const;

    bool GetPasswordExpireLoginNum( int& ) const;
    
    bool GetAlmMsgAlw( unsigned int& ) const;

    bool GetAlmMsgAlwText( string& ) const;
    
    bool GetDbchgMsgAlw( unsigned int& ) const;

    bool GetDbchgMsgAlwText( string& ) const;
    
    bool GetEvtMsgAlw( unsigned int& ) const;

    bool GetEvtMsgAlwText( string& ) const;
    
    bool GetPMMsgAlw( unsigned int& ) const;

    bool GetPMMsgAlwText( string& ) const;

    bool GetStatus( int& ) const;

    bool GetStatusText( string& ) const;

    bool GetPwdConstrained( unsigned int& ) const;

    bool GetSnmpUserSecLevel( int& ) const;

    bool GetSnmpAuthProtocol( int& ) const;

    bool GetSnmpPrivProtocol( int& ) const;	

    bool GetSnmpUserSecLevelText( string& secLevelText ) const;

    bool GetSnmpAuthProtocolText( string& authProtocolText) const;
  
    bool GetSnmpPrivProtocolText( string& privProtocolText) const;
    bool HasSnmpPrivilege() const ;
    bool GetSshKeyUrl(string& sshKeyUrl) const;

private:
    bool OnlyHasSnmpPrivilege() const ;

private:
    string          myUserID; 
    string          myRole;
    string          myCLIRole;
    string          mySNMPRole;
    long            mySessionTimeout;
    long            mySessionMax;
    long            myPasswordAging;
    long            myPasswordUpdateWaiting;
    int             myStatus;
    unsigned int    myAlmMsgAlw;
    unsigned int    myDbchgMsgAlw;
    unsigned int    myEvtMsgAlw;
    unsigned int    myPMMsgAlw;
    unsigned int    myPwdConstrained;
    int             myPwdExpireLoginNum;
    int             mySnmpUserSecLevel ;
    int             mySnmpAuthProtocol ;
    int             mySnmpPrivProtocol ;
    string          mySshKeyUrl;

    string GetMsgAlwText( unsigned int ) const;
};

typedef TL1_Rtv_Response< TL1_SecuUserRspBlk > TL1_SecuUserResponse;

class TL1_SecuUserSshRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_SecuUserSshRspBlk(){}

    TL1_SecuUserSshRspBlk(const string& userId, const string& key1, const string& key2, const string& key3, 
                          const string& key4, const string& key5, const string& key6);

    TL1_SecuUserSshRspBlk(const char* userId, const char* key1 = 0, const char* key2 = 0, const char* key3 = 0, 
                          const char* key4 = 0, const char* key5 = 0, const char* key6 = 0);
                 
    TL1_SecuUserSshRspBlk(const TL1_SecuUserSshRspBlk& );
    
    virtual ~TL1_SecuUserSshRspBlk();

    TL1_SecuUserSshRspBlk& operator=( const TL1_SecuUserSshRspBlk& theBlock );

    bool GetUserID( string&) const ;

    bool GetSshKey1Text( string& ) const;

    bool GetSshKey2Text( string& ) const;

    bool GetSshKey3Text( string& ) const;

    bool GetSshKey4Text( string& ) const;

    bool GetSshKey5Text( string& ) const;

    bool GetSshKey6Text( string& ) const;

private:
    string          myUserID; 
    string          mySshKey1;
    string          mySshKey2;
    string          mySshKey3;
    string          mySshKey4;
    string          mySshKey5;
    string          mySshKey6;
};

typedef TL1_Rtv_Response< TL1_SecuUserSshRspBlk > TL1_SecuUserSshResponse;

#endif  // #ifndef __TL1_SECUUSERRESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
