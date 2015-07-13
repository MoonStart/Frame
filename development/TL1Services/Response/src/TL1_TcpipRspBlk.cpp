/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Networking - TCPIP Response 
TARGET:
AUTHOR: 
DESCRIPTION:    Class implementation for TL1 'RTRV-TCPIP' response
-----------------------------------------------------------------------------*/

#include <Response/TL1_TcpipRspBlk.h>



//-----------------------------------------------------------------------------
// Constructor  -  RTRV-TCPIP
//
TL1_TcpipRspBlk::TL1_TcpipRspBlk(
    const string*                theTcpipAid,
    const CT_DupAddrDetCnt*      theDupAddrDetCnt,
    const CT_DupAddrDetTmr*      theDupAddrDetTmr,
    const CT_SecurityEnable*     theTelnetEnable,
    const CT_SecurityEnable*     theFtpEnable,
    const CT_SecurityEnable*     theHttpEnable,
    const CT_SshAuthentication*  theSshAuthentication,
    const CT_SshKeyStrength*     theSshKeyStrength,
    const string*                thePublicKeyFingerprint,
    const string*                thePublicKey )

    :myBitSet( INDEX_END, false)              // sets the vector size
{

    if ( theTcpipAid )
    {
        myBitSet[INDEX_TcpipAid] = true;
        myTcpipAid = *theTcpipAid;
    }

    if ( theDupAddrDetCnt )
    {
        myBitSet[INDEX_DupAddrDetCnt] = true;
        myDupAddrDetCnt = *theDupAddrDetCnt;
    }

    if ( theDupAddrDetTmr )
    {
        myBitSet[INDEX_DupAddrDetTmr] = true;
        myDupAddrDetTmr = *theDupAddrDetTmr;
    }

    if ( theTelnetEnable )
    {
        myBitSet[INDEX_TelnetEnable] = true;
        myTelnetEnable = *theTelnetEnable;
    }

    if ( theFtpEnable )
    {
        myBitSet[INDEX_FtpEnable] = true;
        myFtpEnable = *theFtpEnable;
    }

    if ( theHttpEnable )
    {
        myBitSet[INDEX_HttpEnable] = true;
        myHttpEnable = *theHttpEnable;
    }

    if ( theSshAuthentication )
    {
        myBitSet[INDEX_SshAuthentication] = true;
        mySshAuthentication = *theSshAuthentication;
    }

    if ( theSshKeyStrength )
    {
        myBitSet[INDEX_SshKeyStrength] = true;
        mySshKeyStrength = *theSshKeyStrength;
    }

    if ( thePublicKeyFingerprint )
    {
        myBitSet[INDEX_PublicKeyFingerprint] = true;
        myPublicKeyFingerprint = *thePublicKeyFingerprint;
    }

    if ( thePublicKey )
    {
        myBitSet[INDEX_PublicKey] = true;
        myPublicKey = *thePublicKey;
    }
}



//-----------------------------------------------------------------------------
// Copy Constructor  -  RTRV-TCPIP
//
TL1_TcpipRspBlk::TL1_TcpipRspBlk( const TL1_TcpipRspBlk& theBlock )
{

    myBitSet               = theBlock.myBitSet;

    myTcpipAid             = theBlock.myTcpipAid;
    myDupAddrDetCnt        = theBlock.myDupAddrDetCnt;
    myDupAddrDetTmr        = theBlock.myDupAddrDetTmr;
    myTelnetEnable         = theBlock.myTelnetEnable;
    myFtpEnable            = theBlock.myFtpEnable;
    myHttpEnable           = theBlock.myHttpEnable;
    mySshAuthentication    = theBlock.mySshAuthentication;
    mySshKeyStrength       = theBlock.mySshKeyStrength;
    myPublicKeyFingerprint = theBlock.myPublicKeyFingerprint;
    myPublicKey            = theBlock.myPublicKey;
}



//-----------------------------------------------------------------------------
// Assignment Operator  -  RTRV-TCPIP
//
TL1_TcpipRspBlk& 
TL1_TcpipRspBlk::operator=( const TL1_TcpipRspBlk& theBlock )
{

    myBitSet               = theBlock.myBitSet;

    myTcpipAid             = theBlock.myTcpipAid;
    myDupAddrDetCnt        = theBlock.myDupAddrDetCnt;
    myDupAddrDetTmr        = theBlock.myDupAddrDetTmr;
    myTelnetEnable         = theBlock.myTelnetEnable;
    myFtpEnable            = theBlock.myFtpEnable;
    myHttpEnable           = theBlock.myHttpEnable;
    mySshAuthentication    = theBlock.mySshAuthentication;
    mySshKeyStrength       = theBlock.mySshKeyStrength;
    myPublicKeyFingerprint = theBlock.myPublicKeyFingerprint;
    myPublicKey            = theBlock.myPublicKey;

    return *this;
}



//-----------------------------------------------------------------------------
// Equality Operator  -  RTRV-TCPIP
//
bool
TL1_TcpipRspBlk::operator==( const TL1_TcpipRspBlk& theBlock ) const
{

    return( myBitSet               == theBlock.myBitSet               &&
            myTcpipAid             == theBlock.myTcpipAid             &&
            myDupAddrDetCnt        == theBlock.myDupAddrDetCnt        &&
            myDupAddrDetTmr        == theBlock.myDupAddrDetTmr        &&
            myTelnetEnable         == theBlock.myTelnetEnable         &&
            myFtpEnable            == theBlock.myFtpEnable            &&
            myHttpEnable           == theBlock.myHttpEnable           &&
            mySshAuthentication    == theBlock.mySshAuthentication    &&
            mySshKeyStrength       == theBlock.mySshKeyStrength       &&
            myPublicKeyFingerprint == theBlock.myPublicKeyFingerprint &&
            myPublicKey            == theBlock.myPublicKey );
}



/*
  =============================================================================
  =                           Member 'Get' Methods                            =
  =============================================================================
*/

//-----------------------------------------------------------------------------
// Get TCPIP Aid
//
bool 
TL1_TcpipRspBlk::GetTcpipAid( string& theTcpipAid ) const
{
    if ( myBitSet[INDEX_TcpipAid] == true )
	{
    	theTcpipAid = myTcpipAid;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get Duplicate Address Detect Count
//
bool 
TL1_TcpipRspBlk::GetDupAddrDetCnt( CT_DupAddrDetCnt& theDupAddrDetCnt ) const
{
    if ( myBitSet[INDEX_DupAddrDetCnt] == true )
	{
    	theDupAddrDetCnt = myDupAddrDetCnt;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get Duplicate Address Detect Timer
//
bool 
TL1_TcpipRspBlk::GetDupAddrDetTmr( CT_DupAddrDetTmr& theDupAddrDetTmr ) const
{
    if ( myBitSet[INDEX_DupAddrDetTmr] == true )
	{
    	theDupAddrDetTmr = myDupAddrDetTmr;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get Telnet Security Enable
//
bool 
TL1_TcpipRspBlk::GetTelnetEnable( CT_SecurityEnable& theTelnetEnable ) const
{
    if ( myBitSet[INDEX_TelnetEnable] == true )
	{
    	theTelnetEnable = myTelnetEnable;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get FTP Security Enable
//
bool 
TL1_TcpipRspBlk::GetFtpEnable( CT_SecurityEnable& theFtpEnable ) const
{
    if ( myBitSet[INDEX_FtpEnable] == true )
	{
    	theFtpEnable = myFtpEnable;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get HTTP Security Enable
//
bool 
TL1_TcpipRspBlk::GetHttpEnable( CT_SecurityEnable& theHttpEnable ) const
{
    if ( myBitSet[INDEX_HttpEnable] == true )
	{
    	theHttpEnable = myHttpEnable;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get SSH Authentication
//
bool 
TL1_TcpipRspBlk::GetSshAuthentication( CT_SshAuthentication& theSshAuthentication ) const
{
    if ( myBitSet[INDEX_SshAuthentication] == true )
	{
    	theSshAuthentication = mySshAuthentication;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get SSH Key Strength
//
bool 
TL1_TcpipRspBlk::GetSshKeyStrength( CT_SshKeyStrength& theSshKeyStrength ) const
{
    if ( myBitSet[INDEX_SshKeyStrength] == true )
	{
    	theSshKeyStrength = mySshKeyStrength;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get Public Key Fingerprint
//
bool 
TL1_TcpipRspBlk::GetPublicKeyFingerprint( string& thePublicKeyFingerprint ) const
{
    if ( myBitSet[INDEX_PublicKeyFingerprint] == true )
	{
    	thePublicKeyFingerprint = myPublicKeyFingerprint;
		return true;
	}

    return false;
}


//-----------------------------------------------------------------------------
// Get Public Key
//
bool 
TL1_TcpipRspBlk::GetPublicKey( string& thePublicKey ) const
{
    if ( myBitSet[INDEX_PublicKey] == true )
	{
    	thePublicKey = myPublicKey;
		return true;
	}

    return false;
}
