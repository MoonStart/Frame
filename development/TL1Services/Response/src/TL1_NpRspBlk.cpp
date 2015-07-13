/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 NP Response 
TARGET:
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Source file for TL1 NP Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_NpRspBlk.h>

TL1_NPRspBlk::TL1_NPRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_NPRspBlk::TL1_NPRspBlk( const string*                      theEntityName,
                            const CT_TL1_NetworkPartitionAddr* theAddr,
                            const string*                      theNpName,
                            const uint16*                      theTimeout,
                            const CT_SM_PST*                   thePST,
                            const CT_SM_PSTQ*                  thePSTQ)
    : myBitSet( INDEX_END, false ), myAddr(*theAddr)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_NpAddr ] = true;
        myAddr = *theAddr;
    }

    if( theNpName )
    {
        myBitSet[ INDEX_NpName ] = true;
        myNpName = *theNpName;
    }

    if( theTimeout )
    {
        myBitSet[ INDEX_Timeout ] = true;
        myTimeout = *theTimeout;
    }

    if(thePST)
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }

    if(thePSTQ)
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
}


TL1_NPRspBlk::TL1_NPRspBlk( const TL1_NPRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;    
    myNpName=           t1Blk.myNpName;
    myTimeout=          t1Blk.myTimeout;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
}

TL1_NPRspBlk::~TL1_NPRspBlk( )
{
}

TL1_NPRspBlk& 
TL1_NPRspBlk::operator=( const TL1_NPRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;
    myNpName=           t1Blk.myNpName;
    myTimeout=          t1Blk.myTimeout;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;

    return *this;
}

bool 
TL1_NPRspBlk::operator==( const TL1_NPRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( !( myNpName == t1Blk.myNpName ) )
        return false;

    if ( myTimeout == t1Blk.myTimeout )
        return false;

    if ( myPST != t1Blk.myPST )
        return false;

    if ( myPSTQ != t1Blk.myPSTQ )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_NPRspBlk::GetEntityName( string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_NPRspBlk::GetNpAddr( CT_TL1_NetworkPartitionAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_NpAddr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPRspBlk::SetNpAddr( const CT_TL1_NetworkPartitionAddr& theAddr )
{
    myBitSet[ INDEX_NpAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool 
TL1_NPRspBlk::GetNpName( string& theNpName ) const
{
    if( true == myBitSet[ INDEX_NpName ] )
    {
        theNpName = myNpName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPRspBlk::SetNpName( const string& theNpName )
{
    myBitSet[ INDEX_NpName ] = true;
    myNpName = theNpName;
}

//--------------------------------------------------------------
bool 
TL1_NPRspBlk::GetTimeout( uint16& theTimeout ) const
{
    if( true == myBitSet[ INDEX_Timeout ] )
    {
        theTimeout = myTimeout;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPRspBlk::SetTimeout( const uint16& theTimeout )
{
    myBitSet[ INDEX_Timeout ] = true;
    myTimeout = theTimeout;
}

//--------------------------------------------------------------
bool 
TL1_NPRspBlk::GetPST( CT_SM_PST& thePST ) const
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        thePST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_NPRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        thePSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_NPRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}


//-------------------------------------------------------------------------------------------------------
// NP-STATS response
TL1_NPSTATSRspBlk::TL1_NPSTATSRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_NPSTATSRspBlk::TL1_NPSTATSRspBlk( const string*                      theEntityName,
                                      const CT_TL1_NetworkPartitionAddr* theAddr,
                                      const string*                      theNpName,
                                      const uint32*                      theCurrActiveCalls,
                                      const uint32*                      theCurrCallAttempts,
                                      const uint32*                      theCurrFailCallAttempts,
                                      const uint32*                      theCurrFailCallAttemptsRoute,
                                      const uint32*                      thePrevCallAttempts,
                                      const uint32*                      thePrevFailCallAttempts,
                                      const uint32*                      thePrevFailCallAttemptsRoute )
     : myBitSet( INDEX_END, false ), myAddr(*theAddr)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_NpAddr ] = true;
        myAddr = *theAddr;
    }

    if( theNpName )
    {
        myBitSet[ INDEX_NpName ] = true;
        myNpName = *theNpName;
    }

    if( theCurrActiveCalls )
    {
        myBitSet[ INDEX_CurrActiveCalls ] = true;
        myCurrActiveCalls = *theCurrActiveCalls;
    }

    if( theCurrCallAttempts )
    {
        myBitSet[ INDEX_CurrCallAttempts ] = true;
        myCurrCallAttempts = *theCurrCallAttempts;
    }

    if( theCurrFailCallAttempts )
    {
        myBitSet[ INDEX_CurrFailCallAttempts ] = true;
        myCurrFailCallAttempts = *theCurrFailCallAttempts;
    }

    if( theCurrFailCallAttemptsRoute )
    {
        myBitSet[ INDEX_CurrFailCallAttemptsRoute ] = true;
        myCurrFailCallAttemptsRoute = *theCurrFailCallAttemptsRoute;
    }

    if( thePrevCallAttempts )
    {
        myBitSet[ INDEX_PrevCallAttempts ] = true;
        myPrevCallAttempts = *thePrevCallAttempts;
    }

    if( thePrevFailCallAttempts )
    {
        myBitSet[ INDEX_PrevFailCallAttempts ] = true;
        myPrevFailCallAttempts = *thePrevFailCallAttempts;
    }

    if( thePrevFailCallAttemptsRoute )
    {
        myBitSet[ INDEX_PrevFailCallAttemptsRoute ] = true;
        myPrevFailCallAttemptsRoute = *thePrevFailCallAttemptsRoute;
    }
}


TL1_NPSTATSRspBlk::TL1_NPSTATSRspBlk( const TL1_NPSTATSRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=                       t1Blk.myBitSet;
    myEntityName=                   t1Blk.myEntityName;
    myAddr=                         t1Blk.myAddr;    
    myNpName=                       t1Blk.myNpName;
    myCurrActiveCalls=              t1Blk.myCurrActiveCalls;
    myCurrCallAttempts=             t1Blk.myCurrCallAttempts;
    myCurrFailCallAttempts=         t1Blk.myCurrFailCallAttempts;
    myCurrFailCallAttemptsRoute=    t1Blk.myCurrFailCallAttemptsRoute;
    myPrevCallAttempts=             t1Blk.myPrevCallAttempts;
    myPrevFailCallAttempts=         t1Blk.myPrevFailCallAttempts;
    myPrevFailCallAttemptsRoute=    t1Blk.myPrevFailCallAttemptsRoute;
}

TL1_NPSTATSRspBlk::~TL1_NPSTATSRspBlk( )
{
}

TL1_NPSTATSRspBlk& 
TL1_NPSTATSRspBlk::operator=( const TL1_NPSTATSRspBlk& t1Blk )
{
    myBitSet=                       t1Blk.myBitSet;
    myEntityName=                   t1Blk.myEntityName;
    myAddr=                         t1Blk.myAddr;    
    myNpName=                       t1Blk.myNpName;
    myCurrActiveCalls=              t1Blk.myCurrActiveCalls;
    myCurrCallAttempts=             t1Blk.myCurrCallAttempts;
    myCurrFailCallAttempts=         t1Blk.myCurrFailCallAttempts;
    myCurrFailCallAttemptsRoute=    t1Blk.myCurrFailCallAttemptsRoute;
    myPrevCallAttempts=             t1Blk.myPrevCallAttempts;
    myPrevFailCallAttempts=         t1Blk.myPrevFailCallAttempts;
    myPrevFailCallAttemptsRoute=    t1Blk.myPrevFailCallAttemptsRoute;

    return *this;
}

bool 
TL1_NPSTATSRspBlk::operator==( const TL1_NPSTATSRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( !( myNpName == t1Blk.myNpName ) )
        return false;

    if ( myCurrActiveCalls == t1Blk.myCurrActiveCalls )
        return false;

    if ( myCurrCallAttempts == t1Blk.myCurrCallAttempts )
        return false;

    if ( myCurrFailCallAttempts == t1Blk.myCurrFailCallAttempts )
        return false;

    if ( myCurrFailCallAttemptsRoute == t1Blk.myCurrFailCallAttemptsRoute )
        return false;

    if ( myPrevCallAttempts == t1Blk.myPrevCallAttempts )
        return false;

    if ( myPrevFailCallAttempts == t1Blk.myPrevFailCallAttempts )
        return false;

    if ( myPrevFailCallAttemptsRoute == t1Blk.myPrevFailCallAttemptsRoute )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetEntityName( string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPSTATSRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetNpAddr( CT_TL1_NetworkPartitionAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_NpAddr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPSTATSRspBlk::SetNpAddr( const CT_TL1_NetworkPartitionAddr& theAddr )
{
    myBitSet[ INDEX_NpAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetNpName( string& theNpName ) const
{
    if( true == myBitSet[ INDEX_NpName ] )
    {
        theNpName = myNpName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPSTATSRspBlk::SetNpName( const string& theNpName )
{
    myBitSet[ INDEX_NpName ] = true;
    myNpName = theNpName;
}
//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetCurrActiveCalls( uint32& theCurrActiveCalls ) const
{
    if( true == myBitSet[ INDEX_CurrActiveCalls ] )
    {
        theCurrActiveCalls = myCurrActiveCalls;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPSTATSRspBlk::SetCurrActiveCalls( const uint32& theCurrActiveCalls )
{
    myBitSet[ INDEX_CurrActiveCalls] = true;
    myCurrActiveCalls = theCurrActiveCalls;
}


//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetCurrCallAttempts( uint32& theCurrCallAttempts  ) const
{
    if( true == myBitSet[ INDEX_CurrCallAttempts ] )
    {
        theCurrCallAttempts = myCurrCallAttempts;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPSTATSRspBlk::SetCurrCallAttempts( const uint32& theCurrCallAttempts )
{
    myBitSet[ INDEX_CurrCallAttempts ] = true;
    myCurrCallAttempts = theCurrCallAttempts;
}

//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetCurrFailCallAttempts( uint32& theCurrFailCallAttempts ) const
{
    if( true == myBitSet[ INDEX_CurrFailCallAttempts ] )
    {
        theCurrFailCallAttempts = myCurrFailCallAttempts;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_NPSTATSRspBlk::SetCurrFailCallAttempts( const uint32& theCurrFailCallAttempts )
{
    myBitSet[ INDEX_CurrFailCallAttempts ] = true;
    myCurrFailCallAttempts = theCurrFailCallAttempts;
}

//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetCurrFailCallAttemptsRoute( uint32& theCurrFailCallAttemptsRoute ) const
{
    if( true == myBitSet[ INDEX_CurrFailCallAttemptsRoute ] )
    {
        theCurrFailCallAttemptsRoute = myCurrFailCallAttemptsRoute;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPSTATSRspBlk::SetCurrFailCallAttemptsRoute( const uint32& theCurrFailCallAttemptsRoute )
{
    myBitSet[ INDEX_CurrFailCallAttemptsRoute] = true;
    myCurrFailCallAttemptsRoute = theCurrFailCallAttemptsRoute;
}


//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetPrevCallAttempts( uint32& thePrevCallAttempts  ) const
{
    if( true == myBitSet[ INDEX_PrevCallAttempts ] )
    {
        thePrevCallAttempts = myPrevCallAttempts;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_NPSTATSRspBlk::SetPrevCallAttempts( const uint32& thePrevCallAttempts )
{
    myBitSet[ INDEX_PrevCallAttempts ] = true;
    myPrevCallAttempts = thePrevCallAttempts;
}

//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetPrevFailCallAttempts( uint32& thePrevFailCallAttempts ) const
{
    if( true == myBitSet[ INDEX_PrevFailCallAttempts ] )
    {
        thePrevFailCallAttempts = myPrevFailCallAttempts;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_NPSTATSRspBlk::SetPrevFailCallAttempts( const uint32& thePrevFailCallAttempts )
{
    myBitSet[ INDEX_PrevFailCallAttempts ] = true;
    myPrevFailCallAttempts = thePrevFailCallAttempts;
}

//--------------------------------------------------------------
bool 
TL1_NPSTATSRspBlk::GetPrevFailCallAttemptsRoute( uint32& thePrevFailCallAttemptsRoute ) const
{
    if( true == myBitSet[ INDEX_PrevFailCallAttemptsRoute ] )
    {
        thePrevFailCallAttemptsRoute = myPrevFailCallAttemptsRoute;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_NPSTATSRspBlk::SetPrevFailCallAttemptsRoute( const uint32& thePrevFailCallAttemptsRoute )
{
    myBitSet[ INDEX_PrevFailCallAttemptsRoute ] = true;
    myPrevFailCallAttemptsRoute = thePrevFailCallAttemptsRoute;
}

