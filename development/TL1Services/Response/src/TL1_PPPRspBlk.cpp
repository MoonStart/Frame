/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 PPP, PPPPF Response 
TARGET:
AUTHOR:         Lee Gernes
DESCRIPTION:    Source file for TL1 PPP, PPPPF Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_PPPRspBlk.h>

TL1_PPPRspBlk::TL1_PPPRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_PPPRspBlk::TL1_PPPRspBlk( const TL1_PPPRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myPPPAddr=          t1Blk.myPPPAddr;
    myProfileAddr=      t1Blk.myProfileAddr;
    myAlarmProfile=     t1Blk.myAlarmProfile;
    myNpOwner=          t1Blk.myNpOwner;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_PPPRspBlk::~TL1_PPPRspBlk( )
{
}

TL1_PPPRspBlk& 
TL1_PPPRspBlk::operator=( const TL1_PPPRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myPPPAddr=          t1Blk.myPPPAddr;
    myProfileAddr=      t1Blk.myProfileAddr;
    myAlarmProfile=     t1Blk.myAlarmProfile;
    myNpOwner=          t1Blk.myNpOwner;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_PPPRspBlk::operator==( const TL1_PPPRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myPPPAddr == t1Blk.myPPPAddr ) )
        return false;

    if ( myProfileAddr != t1Blk.myProfileAddr )
        return false;
   
    if ( myAlarmProfile != t1Blk.myAlarmProfile )
        return false;

    if ( myNpOwner != t1Blk.myNpOwner )
        return false;

    if ( myPST != t1Blk.myPST )
        return false;

    if ( myPSTQ != t1Blk.myPSTQ )
        return false;

    if ( mySST != t1Blk.mySST )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_PPPRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetPPPAddr( CT_TL1_FacAddr& thePPPAddr ) const
{
    if( true == myBitSet[ INDEX_PPPAddr ] )
    {
        thePPPAddr = myPPPAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_PPPRspBlk::SetPPPAddr( const CT_TL1_FacAddr& thePPPAddr )
{
    myBitSet[ INDEX_PPPAddr ] = true;
    myPPPAddr = thePPPAddr;
}

//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetProfileAddr( CT_PPPProfAddr& theProfileAddr ) const
{
    if( true == myBitSet[ INDEX_ProfileAddr ] )
    {
        theProfileAddr = myProfileAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_PPPRspBlk::SetProfileAddr( const CT_PPPProfAddr& theProfileAddr )
{
    myBitSet[ INDEX_ProfileAddr ] = true;
    myProfileAddr = theProfileAddr;
}

//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_PPPRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_PPPRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetSST( CT_SM_SST& theSST ) const
{
    if( true == myBitSet[ INDEX_SST ] )
    {
        theSST = mySST;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_PPPRspBlk::SetSST( CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST = theSST;
}



//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
{
    if( true == myBitSet[ INDEX_AlarmProfile ] )
    {
        theAlarmProfile = myAlarmProfile;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_PPPRspBlk::SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile )  
{
    myBitSet[ INDEX_AlarmProfile ]  = true;
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------
bool 
TL1_PPPRspBlk::GetNpOwner( uint8& theNpOwner ) const
{
    if( true == myBitSet[ INDEX_NpOwner ] )
    {
        theNpOwner = myNpOwner;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_PPPRspBlk::SetNpOwner( const uint8& theNpOwner )  
{
    myBitSet[ INDEX_NpOwner ]  = true;
    myNpOwner = theNpOwner;
}


TL1_PPPPFRspBlk::TL1_PPPPFRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_PPPPFRspBlk::TL1_PPPPFRspBlk( const TL1_PPPPFRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet     = t1Blk.myBitSet;
    myEntityName = t1Blk.myEntityName;
    myPFAddr     = t1Blk.myPFAddr;
    myPFname	 = t1Blk.myPFname;
    myMaxRcvUnits= t1Blk.myMaxRcvUnits;
    myFCS        = t1Blk.myFCS;
    myRestartTimer    = t1Blk.myRestartTimer;
    myMaxFailureCount = t1Blk.myMaxFailureCount;
}

TL1_PPPPFRspBlk::~TL1_PPPPFRspBlk( )
{
}

TL1_PPPPFRspBlk& 
TL1_PPPPFRspBlk::operator=( const TL1_PPPPFRspBlk& t1Blk )
{
    myBitSet     = t1Blk.myBitSet;
    myEntityName = t1Blk.myEntityName;
    myPFAddr     = t1Blk.myPFAddr;
    myPFname	 = t1Blk.myPFname;
    myMaxRcvUnits = t1Blk.myMaxRcvUnits;
    myFCS        = t1Blk.myFCS;
    myRestartTimer    = t1Blk.myRestartTimer;
    myMaxFailureCount = t1Blk.myMaxFailureCount;

    return *this;
}

bool 
TL1_PPPPFRspBlk::operator==( const TL1_PPPPFRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet)
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myPFAddr == t1Blk.myPFAddr ) )
        return false;

    if ( !(myPFname == t1Blk.myPFname ) )
        return false;

    if ( !(myMaxRcvUnits == t1Blk.myMaxRcvUnits ) )
        return false;

    if ( !(myFCS == t1Blk.myFCS ) )
        return false;

    if ( !(myRestartTimer == t1Blk.myRestartTimer ) ) 
        return false;

    if ( !(myMaxFailureCount == t1Blk.myMaxFailureCount ) ) 
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_PPPPFRspBlk::GetEntityName(string& theEntityName ) const
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
TL1_PPPPFRspBlk::SetEntityName( const string& theEntityName ) 
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_PPPPFRspBlk::GetPFAddr( CT_TL1_LogicalAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_PFAddr ] )
    {
        theAddr = myPFAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_PPPPFRspBlk::SetPFAddr( const CT_TL1_LogicalAddr& theAddr ) 
{
    myBitSet[ INDEX_PFAddr ] = true;
    myPFAddr = theAddr;
}
  
//--------------------------------------------------------------
bool  
TL1_PPPPFRspBlk::GetPFname( string& thePFname ) const
{
    if ( true == myBitSet[ INDEX_PFname] ) 
    {
        thePFname = myPFname;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_PPPPFRspBlk::SetPFname( const string& thePFname ) 
{
    myBitSet[ INDEX_PFname] = true;
    myPFname = thePFname;
}


//--------------------------------------------------------------
bool  
TL1_PPPPFRspBlk::GetMaxRcvUnits( uint16& theMaxRcvUnits ) const
{
    if ( true == myBitSet[ INDEX_MaxRcvUnits ] ) 
    {
        theMaxRcvUnits = myMaxRcvUnits;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_PPPPFRspBlk::SetMaxRcvUnits( const uint16& theMaxRcvUnits ) 
{
    myBitSet[ INDEX_MaxRcvUnits ] = true;
    myMaxRcvUnits = theMaxRcvUnits;
}


//--------------------------------------------------------------
bool  
TL1_PPPPFRspBlk::GetFCS( CT_FCS& theFCS ) const
{
    if ( true == myBitSet[ INDEX_FCS ] ) 
    {
        theFCS = myFCS;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_PPPPFRspBlk::SetFCS( const CT_FCS& theFCS ) 
{
    myBitSet[ INDEX_FCS ] = true;
    myFCS = theFCS;
}


//--------------------------------------------------------------
bool  
TL1_PPPPFRspBlk::GetRestartTimer( uint16& theRestartTimer ) const
{
    if ( true == myBitSet[ INDEX_RestartTimer ] ) 
    {
        theRestartTimer = myRestartTimer;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_PPPPFRspBlk::SetRestartTimer( const uint16& theRestartTimer ) 
{
    myBitSet[ INDEX_RestartTimer ] = true;
    myRestartTimer = theRestartTimer;
}


//--------------------------------------------------------------
bool  
TL1_PPPPFRspBlk::GetMaxFailureCount( uint16& theMaxFailureCount ) const
{
    if ( true == myBitSet[ INDEX_MaxFailureCount ] ) 
    {
        theMaxFailureCount = myMaxFailureCount;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_PPPPFRspBlk::SetMaxFailureCount( const uint16& theMaxFailureCount ) 
{
    myBitSet[ INDEX_MaxFailureCount ] = true;
    myMaxFailureCount = theMaxFailureCount;
}
