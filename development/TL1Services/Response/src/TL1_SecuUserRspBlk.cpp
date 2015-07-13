/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_SecuUserRspBlk.h>

TL1_SecuUserRspBlk::TL1_SecuUserRspBlk(const string* userId, const string* role, const string* clirole, const string* snmprole, const long sessionTimeout, 
                                       const long passwordAging, const long passwordUpdateWaiting, const int status,const uint32 maxSession ,  
                                       const uint32 almMsgAlw, const uint32 dbchgMsgAlw, const uint32 evtMsgAlw,
                                       const uint32 pMMsgAlw, const uint32 pwdConstrained, const uint32 passwordExpireLoginNum,
                                       const uint32 snmpUserSecLevel,const uint32 snmpAuthProtocol,const uint32 snmpPrivProtocol, const string* sshUrl)
: myUserID( "" ), myRole( "" ), myCLIRole( ""), mySNMPRole(""),mySessionTimeout( sessionTimeout ), mySessionMax( maxSession ),myPasswordAging( passwordAging ),
myPasswordUpdateWaiting( passwordUpdateWaiting ), myStatus(status), myAlmMsgAlw(almMsgAlw),
myDbchgMsgAlw(dbchgMsgAlw), myEvtMsgAlw(evtMsgAlw), myPMMsgAlw(pMMsgAlw), myPwdConstrained(pwdConstrained),
myPwdExpireLoginNum(passwordExpireLoginNum),
mySnmpUserSecLevel(snmpUserSecLevel),mySnmpAuthProtocol(snmpAuthProtocol),mySnmpPrivProtocol(snmpPrivProtocol),mySshKeyUrl("")
{
    if( userId )
    {
        myUserID = *userId;
    }
    if( role )
    {
        myRole = *role;
    }
    if(clirole)
    {
        myCLIRole = *clirole;
    }
    if(snmprole)
    {
        mySNMPRole = *snmprole;
    }
    if (sshUrl)
    {
        mySshKeyUrl = *sshUrl;
    }
}

TL1_SecuUserRspBlk::TL1_SecuUserRspBlk(const char* userId, const char* role, const char* clirole, const char* snmprole, const long sessionTimeout, 
                                       const long passwordAging, const long passwordUpdateWaiting, const int status, const uint32 maxSession ,  
                                       const uint32 almMsgAlw, const uint32 dbchgMsgAlw, const uint32 evtMsgAlw,
                                       const uint32 pMMsgAlw, const uint32 pwdConstrained, const uint32 passwordExpireLoginNum,
                                       const uint32 snmpUserSecLevel,const uint32 snmpAuthProtocol,const uint32 snmpPrivProtocol, const char* sshUrl)
: myUserID( "" ), myRole( "" ), myCLIRole(""), mySNMPRole(""),mySessionMax( maxSession ), mySessionTimeout( sessionTimeout ), myPasswordAging( passwordAging ),
myPasswordUpdateWaiting( passwordUpdateWaiting ), myStatus(status), myAlmMsgAlw(almMsgAlw),
myDbchgMsgAlw(dbchgMsgAlw), myEvtMsgAlw(evtMsgAlw), myPMMsgAlw(pMMsgAlw), myPwdConstrained(pwdConstrained),
myPwdExpireLoginNum(passwordExpireLoginNum),
mySnmpUserSecLevel(snmpUserSecLevel),mySnmpAuthProtocol(snmpAuthProtocol),mySnmpPrivProtocol(snmpPrivProtocol),mySshKeyUrl("")
{
    if( userId )
    {
        myUserID = *userId;
    }
    if( role )
    {
        myRole = *role;
    }
    if(clirole)
    {
        myCLIRole = *clirole;
    }
    if(snmprole)
    {
        mySNMPRole = *snmprole;
    }
    if (sshUrl)
    {
        mySshKeyUrl = sshUrl;
    }
}

TL1_SecuUserRspBlk::TL1_SecuUserRspBlk(const TL1_SecuUserRspBlk& blk)
: myUserID( blk.myUserID), myRole( blk.myRole), myCLIRole( blk.myCLIRole), mySNMPRole(blk.mySNMPRole),mySessionTimeout( blk.mySessionTimeout ), myPasswordAging( blk.myPasswordAging ),
mySessionMax(blk.mySessionMax),myPasswordUpdateWaiting( blk.myPasswordUpdateWaiting ), myStatus(blk.myStatus), myAlmMsgAlw(blk.myAlmMsgAlw),
myDbchgMsgAlw(blk.myDbchgMsgAlw), myEvtMsgAlw(blk.myEvtMsgAlw), myPMMsgAlw(blk.myPMMsgAlw), myPwdConstrained(blk.myPwdConstrained),
myPwdExpireLoginNum(blk.myPwdExpireLoginNum),
mySnmpUserSecLevel(blk.mySnmpUserSecLevel),mySnmpAuthProtocol(blk.mySnmpAuthProtocol),mySnmpPrivProtocol(blk.mySnmpPrivProtocol),
mySshKeyUrl(blk.mySshKeyUrl)
{
}

TL1_SecuUserRspBlk::~TL1_SecuUserRspBlk()
{
}

TL1_SecuUserRspBlk& TL1_SecuUserRspBlk::operator=( const TL1_SecuUserRspBlk& theBlock )
{
    myUserID = theBlock.myUserID;
    myRole = theBlock.myRole;
    myCLIRole = theBlock.myCLIRole;
    mySNMPRole = theBlock.mySNMPRole;
    mySessionTimeout = theBlock.mySessionTimeout;
    mySessionMax  = theBlock.mySessionMax;
    myPasswordAging = theBlock.myPasswordAging;
    myPasswordUpdateWaiting = theBlock.myPasswordUpdateWaiting;
    myStatus = theBlock.myStatus;
    myAlmMsgAlw = theBlock.myAlmMsgAlw;
    myDbchgMsgAlw = theBlock.myDbchgMsgAlw;
    myEvtMsgAlw = theBlock.myEvtMsgAlw;
    myPMMsgAlw = theBlock.myPMMsgAlw;
    myPwdConstrained = theBlock.myPwdConstrained;
    myPwdExpireLoginNum = theBlock.myPwdExpireLoginNum;\
    mySnmpUserSecLevel = theBlock.mySnmpUserSecLevel;
    mySnmpAuthProtocol = theBlock.mySnmpAuthProtocol;
    mySnmpPrivProtocol = theBlock.mySnmpPrivProtocol;
    mySshKeyUrl        = theBlock.mySshKeyUrl;
    return *this;
}

bool TL1_SecuUserRspBlk::GetUserID( string& userID) const
{
    userID = myUserID;
    return true;
}

bool TL1_SecuUserRspBlk::GetRole( string& Role ) const
{
    Role = myRole;
    return true;
}

bool TL1_SecuUserRspBlk::GetCLIRole( string& CliRole ) const
{
    CliRole = myCLIRole;
    return true;
}

bool TL1_SecuUserRspBlk::GetSNMPRole( string& SnmpRole ) const
{
    SnmpRole = mySNMPRole;
    return true;
}

bool TL1_SecuUserRspBlk::GetSessionTimeout( long& sessionTimeout ) const
{
    sessionTimeout = mySessionTimeout;
    return true;
}

bool TL1_SecuUserRspBlk::GetSessionMax( long& sessionMax ) const
{
    sessionMax = mySessionMax;
    return true;
}

bool TL1_SecuUserRspBlk::OnlyHasSnmpPrivilege() const
{
    if(myCLIRole == "A0" && myRole == "A0" && mySNMPRole != "A0" )
        return true;

    return false;
}

bool TL1_SecuUserRspBlk::HasSnmpPrivilege() const
{
    if(mySNMPRole != "A0" )
        return true;

    return false;
}

bool TL1_SecuUserRspBlk::GetSshKeyUrl(string &sshKeyUrl) const
{
    sshKeyUrl = mySshKeyUrl;
    return true;
}

bool TL1_SecuUserRspBlk::GetPasswordAging( long& passwordAging ) const
{

    passwordAging = myPasswordAging;
    return true;
}

bool TL1_SecuUserRspBlk::GetPasswordUpdateWaiting( long& passwordUpdateWaiting ) const
{

    passwordUpdateWaiting = myPasswordUpdateWaiting;
    return true;
}

bool TL1_SecuUserRspBlk::GetPasswordExpireLoginNum( int& passwordExpireLoginNum ) const
{

    passwordExpireLoginNum = myPwdExpireLoginNum;
    return true;
}

bool TL1_SecuUserRspBlk::GetAlmMsgAlw( unsigned int& almMsgAlw ) const
{
    almMsgAlw = myAlmMsgAlw;
    return true;
}

bool TL1_SecuUserRspBlk::GetAlmMsgAlwText( string& almMsgAlwText ) const
{

    almMsgAlwText = GetMsgAlwText( myAlmMsgAlw );
    return true;
}

bool TL1_SecuUserRspBlk::GetDbchgMsgAlw( unsigned int& dbchgMsgAlw ) const
{

    dbchgMsgAlw = myDbchgMsgAlw;
    return true;
}

bool TL1_SecuUserRspBlk::GetDbchgMsgAlwText( string& dbchgMsgAlwText ) const
{

    dbchgMsgAlwText = GetMsgAlwText( myDbchgMsgAlw );
    return true;
}

bool TL1_SecuUserRspBlk::GetEvtMsgAlw( unsigned int& evtMsgAlw ) const
{
    evtMsgAlw = myEvtMsgAlw;
    return true;
}

bool TL1_SecuUserRspBlk::GetEvtMsgAlwText( string& evtMsgAlwText ) const
{

    evtMsgAlwText = GetMsgAlwText( myEvtMsgAlw );
    return true;
}

bool TL1_SecuUserRspBlk::GetPMMsgAlw( unsigned int& pMMsgAlw ) const
{
    pMMsgAlw = myPMMsgAlw;
    return true;
}

bool TL1_SecuUserRspBlk::GetPMMsgAlwText( string& pMMsgAlwText ) const
{

    pMMsgAlwText = GetMsgAlwText( myPMMsgAlw );
    return true;
}

string TL1_SecuUserRspBlk::GetMsgAlwText( unsigned int msgAlwInh ) const
{
    string retMsgAlwText;

    switch(msgAlwInh)
    {
    case MSG_INH:
        retMsgAlwText = "INH";
        break;
    case MSG_ALW:
        retMsgAlwText = "ALW";
        break;
    case MSG_INH_OWN:
        retMsgAlwText = "INH-OWN";
        break;
    default :
        retMsgAlwText = "INH";
        break;
    }

    return retMsgAlwText;
}

bool TL1_SecuUserRspBlk::GetStatus( int& status) const
{
    status = myStatus;
    return true;
}

bool TL1_SecuUserRspBlk::GetStatusText( string& statusText ) const
{

    switch(myStatus)
    {
    case USER_DISABLED:
        statusText = "DISABLED";
        break;
    case USER_ENABLED:
        statusText = "ENABLED";
        break;
    case USER_PASSWORD_EXPIRED:
        statusText = "PASSWORD AGED";
        break;
    case USER_LOCKED_OUT:
        statusText = "LOCK-OUT";
        break;
    default :
        statusText = "";
        break;
    }

    return true;
}

bool TL1_SecuUserRspBlk::GetPwdConstrained( unsigned int& pwdConstrained ) const
{
    pwdConstrained = myPwdConstrained;
    return true;
}


bool TL1_SecuUserRspBlk::GetSnmpUserSecLevel( int& SnmpUserSecLevel ) const
{
    SnmpUserSecLevel= mySnmpUserSecLevel ;
    return true;
}

bool TL1_SecuUserRspBlk::GetSnmpAuthProtocol(int& SnmpAuthProtocol ) const
{
    SnmpAuthProtocol = mySnmpAuthProtocol ;
    return true;
}

bool TL1_SecuUserRspBlk::GetSnmpPrivProtocol( int& SnmpPrivProtocol ) const
{
    SnmpPrivProtocol = mySnmpPrivProtocol ;
    return true;
}

bool TL1_SecuUserRspBlk::GetSnmpUserSecLevelText( string& secLevelText ) const
{
    switch(mySnmpUserSecLevel)
    {
    case LEVEL_NOAUTH_NOPRIV :
        secLevelText="noAuthnoPriv";
        break;
    case LEVEL_AUTH_NOPRIV  :
        secLevelText="authNoPriv";
        break;
    case LEVEL_AUTH_PRIV:
        secLevelText="authPriv";
        break;
    default   :
        secLevelText="";
        break;
    }

    return true;
}  

bool TL1_SecuUserRspBlk::GetSnmpAuthProtocolText( string& authProtocolText) const
{

    switch(mySnmpAuthProtocol)
    {
    case AUTH_PROTOCOL_MD5:
        authProtocolText="MD5";
        break;
    case AUTH_PROTOCOL_SHA:
        authProtocolText="SHA";
        break;
    default:
        authProtocolText="";
        break;
    }

    return true;
}

bool TL1_SecuUserRspBlk::GetSnmpPrivProtocolText( string& privProtocolText) const
{

    switch(mySnmpPrivProtocol)
    {
    case PRIV_PROTOCOL_DES:
        privProtocolText="DES";
        break;
    default:
        privProtocolText="";
        break;
    }
    return true;
}



TL1_SecuUserSshRspBlk::TL1_SecuUserSshRspBlk(const string& userId, const string& key1, const string& key2, const string& key3, 
                                       const string& key4, const string& key5, const string& key6)
: myUserID( userId ), mySshKey1( key1 ), mySshKey2( key2 ),mySshKey3( key3 ), mySshKey4( key4 ),mySshKey5( key5 ), mySshKey6( key6 )
{
}

TL1_SecuUserSshRspBlk::TL1_SecuUserSshRspBlk(const char* userId, const char* key1, const char* key2, const char* key3, 
                                       const char* key4, const char* key5, const char* key6)
: myUserID( "" ), mySshKey1(""),mySshKey2( "" ), mySshKey3( "" ), mySshKey4( "" ), mySshKey5( "" ), mySshKey6("")
{
    if( userId )
    {
        myUserID = *userId;
    }
    if (key1)
    {
        mySshKey1 = *key1;
    }
    if (key2)
    {
        mySshKey2 = *key2;
    }
    if (key3)
    {
        mySshKey3 = *key3;
    }
    if (key4)
    {
        mySshKey4 = *key4;
    }
    if (key5)
    {
        mySshKey5= *key5;
    }
    if (key6)
    {
        mySshKey6 = *key6;
    }
}

TL1_SecuUserSshRspBlk::TL1_SecuUserSshRspBlk(const TL1_SecuUserSshRspBlk& blk)
: myUserID( blk.myUserID), mySshKey1( blk.mySshKey1), mySshKey2(blk.mySshKey2),mySshKey3( blk.mySshKey3 ), mySshKey4( blk.mySshKey4 ),
mySshKey5(blk.mySshKey5),mySshKey6( blk.mySshKey6 )
{
}

TL1_SecuUserSshRspBlk::~TL1_SecuUserSshRspBlk()
{
}

TL1_SecuUserSshRspBlk& TL1_SecuUserSshRspBlk::operator=( const TL1_SecuUserSshRspBlk& theBlock )
{
    myUserID = theBlock.myUserID;
    mySshKey1 = theBlock.mySshKey1;
    mySshKey2 = theBlock.mySshKey2;
    mySshKey3 = theBlock.mySshKey3;
    mySshKey4 = theBlock.mySshKey4;
    mySshKey5 = theBlock.mySshKey5;
    mySshKey6 = theBlock.mySshKey6;
    return *this;
}

bool TL1_SecuUserSshRspBlk::GetUserID( string& userID) const
{
    userID = myUserID;
    return true;
}

bool TL1_SecuUserSshRspBlk::GetSshKey1Text( string& sshKeyText) const
{
    sshKeyText = mySshKey1;
    return true;
}

bool TL1_SecuUserSshRspBlk::GetSshKey2Text( string& sshKeyText) const
{
    sshKeyText = mySshKey2;
    return true;
}

bool TL1_SecuUserSshRspBlk::GetSshKey3Text( string& sshKeyText) const
{
    sshKeyText = mySshKey3;
    return true;
}

bool TL1_SecuUserSshRspBlk::GetSshKey4Text( string& sshKeyText) const
{
    sshKeyText = mySshKey4;
    return true;
}

bool TL1_SecuUserSshRspBlk::GetSshKey5Text( string& sshKeyText) const
{
    sshKeyText = mySshKey5;
    return true;
}

bool TL1_SecuUserSshRspBlk::GetSshKey6Text( string& sshKeyText) const
{
    sshKeyText = mySshKey6;
    return true;
}

