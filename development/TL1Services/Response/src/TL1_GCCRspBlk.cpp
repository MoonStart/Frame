/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 GCC Response 
TARGET:
AUTHOR:         Shawn He
DESCRIPTION:    Source file for TL1 GCC Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_GCCRspBlk.h>

TL1_GCCRspBlk::TL1_GCCRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_GCCRspBlk::TL1_GCCRspBlk( const TL1_GCCRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myGCCAddr=          t1Blk.myGCCAddr;
    myProfileAddr=      t1Blk.myProfileAddr;
    myAlarmProfile=     t1Blk.myAlarmProfile;
    myNpOwner=          t1Blk.myNpOwner;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_GCCRspBlk::~TL1_GCCRspBlk( )
{
}

TL1_GCCRspBlk& 
TL1_GCCRspBlk::operator=( const TL1_GCCRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myGCCAddr=          t1Blk.myGCCAddr;
    myProfileAddr=      t1Blk.myProfileAddr;
    myAlarmProfile=     t1Blk.myAlarmProfile;
    myNpOwner=          t1Blk.myNpOwner;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_GCCRspBlk::operator==( const TL1_GCCRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myGCCAddr == t1Blk.myGCCAddr ) )
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
TL1_GCCRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_GCCRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_GCCRspBlk::GetGCCAddr( CT_TL1_FacAddr& theGCCAddr ) const
{
    if( true == myBitSet[ INDEX_GCCAddr ] )
    {
        theGCCAddr = myGCCAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_GCCRspBlk::SetGCCAddr( const CT_TL1_FacAddr& theGCCAddr )
{
    myBitSet[ INDEX_GCCAddr ] = true;
    myGCCAddr = theGCCAddr;
}


//--------------------------------------------------------------
bool 
TL1_GCCRspBlk::GetProfileAddr( CT_PPPProfAddr& theProfileAddr ) const
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
TL1_GCCRspBlk::SetProfileAddr( const CT_PPPProfAddr& theProfileAddr )
{
    myBitSet[ INDEX_ProfileAddr ] = true;
    myProfileAddr = theProfileAddr;
}

//--------------------------------------------------------------
bool 
TL1_GCCRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_GCCRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_GCCRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_GCCRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

//--------------------------------------------------------------
bool 
TL1_GCCRspBlk::GetSST( CT_SM_SST& theSST ) const
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
TL1_GCCRspBlk::SetSST( CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST = theSST;
}



//--------------------------------------------------------------
bool 
TL1_GCCRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
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
TL1_GCCRspBlk::SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile )  
{
    myBitSet[ INDEX_AlarmProfile ]  = true;
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------
bool 
TL1_GCCRspBlk::GetNpOwner( uint8& theNpOwner ) const
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
TL1_GCCRspBlk::SetNpOwner( const uint8& theNpOwner )  
{
    myBitSet[ INDEX_NpOwner ]  = true;
    myNpOwner = theNpOwner;
}
