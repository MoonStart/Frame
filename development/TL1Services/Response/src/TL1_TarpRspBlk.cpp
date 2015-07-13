/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Tarp Response 
TARGET:
AUTHOR:         July 25, 2006 - Thomas Novak
DESCRIPTION:    Source file for TL1 LPAD Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_TarpRspBlk.h>

TL1_TarpRspBlk::TL1_TarpRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_TarpRspBlk::TL1_TarpRspBlk( const TL1_TarpRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myTarpAddr=         t1Blk.myTarpAddr;

    myFlushTmr=         t1Blk.myFlushTmr;
    myEntryTmr=         t1Blk.myEntryTmr;
    myT1Tmr=            t1Blk.myT1Tmr;
    myT2Tmr=            t1Blk.myT2Tmr;
    myT3Tmr=            t1Blk.myT3Tmr;
    myT4Tmr=            t1Blk.myT4Tmr;
    myProtAddr=         t1Blk.myProtAddr;
    mySeqNum=           t1Blk.mySeqNum;
    myLFTarpMsg=        t1Blk.myLFTarpMsg;
    myNSEL=             t1Blk.myNSEL;
    myTarpReset=        t1Blk.myTarpReset;

    myAlarmProfile=     t1Blk.myAlarmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_TarpRspBlk::~TL1_TarpRspBlk( )
{
}

TL1_TarpRspBlk& 
TL1_TarpRspBlk::operator=( const TL1_TarpRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myTarpAddr=         t1Blk.myTarpAddr;

    myFlushTmr=         t1Blk.myFlushTmr;
    myEntryTmr=         t1Blk.myEntryTmr;
    myT1Tmr=            t1Blk.myT1Tmr;
    myT2Tmr=            t1Blk.myT2Tmr;
    myT3Tmr=            t1Blk.myT3Tmr;
    myT4Tmr=            t1Blk.myT4Tmr;
    myProtAddr=         t1Blk.myProtAddr;
    mySeqNum=           t1Blk.mySeqNum;
    myLFTarpMsg=        t1Blk.myLFTarpMsg;
    myNSEL=             t1Blk.myNSEL;
    myTarpReset=        t1Blk.myTarpReset;

    myAlarmProfile=     t1Blk.myAlarmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_TarpRspBlk::operator==( const TL1_TarpRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myTarpAddr == t1Blk.myTarpAddr ) )
        return false;

    if ( myFlushTmr != t1Blk.myFlushTmr )
        return false;

    if ( myEntryTmr != t1Blk.myEntryTmr )
        return false;

    if ( myT1Tmr != t1Blk.myT1Tmr )
        return false;

    if ( myT2Tmr != t1Blk.myT2Tmr )
        return false;

    if ( myT3Tmr != t1Blk.myT3Tmr )
        return false;

    if ( myT4Tmr != t1Blk.myT4Tmr )
        return false;

    if ( myProtAddr != t1Blk.myProtAddr )
        return false;

    if ( mySeqNum != t1Blk.mySeqNum )
        return false;

    if ( myLFTarpMsg != t1Blk.myLFTarpMsg )
        return false;

    if ( myNSEL != t1Blk.myNSEL )
        return false;

    if ( myTarpReset != t1Blk.myTarpReset )
        return false;
    
    if ( myAlarmProfile != t1Blk.myAlarmProfile )
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
TL1_TarpRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_TarpRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_TarpRspBlk::GetTarpAddr( CT_TL1_FacAddr& theTarpAddr ) const
{
    if( true == myBitSet[ INDEX_TarpAddr ] )
    {
        theTarpAddr = myTarpAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_TarpRspBlk::SetTarpAddr( const CT_TL1_FacAddr& theTarpAddr )
{
    myBitSet[ INDEX_TarpAddr ] = true;
    myTarpAddr = theTarpAddr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetFlushTmr( uint16& theFlushTmr ) const
{
    if( true == myBitSet[ INDEX_FlushTmr ] )
    {
        theFlushTmr = myFlushTmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetFlushTmr( const uint16& theFlushTmr )
{
    myBitSet[ INDEX_FlushTmr ] = true;
    myFlushTmr = theFlushTmr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetEntryTmr( uint16& theEntryTmr ) const
{
    if( true == myBitSet[ INDEX_EntryTmr ] )
    {
        theEntryTmr = myEntryTmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetEntryTmr( const uint16& theEntryTmr )
{
    myBitSet[ INDEX_EntryTmr ] = true;
    myEntryTmr = theEntryTmr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetT1Tmr( uint16& theT1Tmr ) const
{
    if( true == myBitSet[ INDEX_T1Tmr ] )
    {
        theT1Tmr = myT1Tmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetT1Tmr( const uint16& theT1Tmr )
{
    myBitSet[ INDEX_T1Tmr ] = true;
    myT1Tmr = theT1Tmr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetT2Tmr( uint16& theT2Tmr ) const
{
    if( true == myBitSet[ INDEX_T2Tmr ] )
    {
        theT2Tmr = myT2Tmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetT2Tmr( const uint16& theT2Tmr )
{
    myBitSet[ INDEX_T2Tmr ] = true;
    myT2Tmr = theT2Tmr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetT3Tmr( uint16& theT3Tmr ) const
{
    if( true == myBitSet[ INDEX_T3Tmr ] )
    {
        theT3Tmr = myT3Tmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetT3Tmr( const uint16& theT3Tmr )
{
    myBitSet[ INDEX_T3Tmr ] = true;
    myT3Tmr = theT3Tmr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetT4Tmr( uint16& theT4Tmr ) const
{
    if( true == myBitSet[ INDEX_T4Tmr ] )
    {
        theT4Tmr = myT4Tmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetT4Tmr( const uint16& theT4Tmr )
{
    myBitSet[ INDEX_T4Tmr ] = true;
    myT4Tmr = theT4Tmr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetProtAddr( uint16& theProtAddr ) const
{
    if( true == myBitSet[ INDEX_ProtAddr ] )
    {
        theProtAddr = myProtAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetProtAddr( const uint16& theProtAddr )
{
    myBitSet[ INDEX_ProtAddr ] = true;
    myProtAddr = theProtAddr;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetSeqNum( uint16& theSeqNum ) const
{
    if( true == myBitSet[ INDEX_SeqNum ] )
    {
        theSeqNum = mySeqNum;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetSeqNum( const uint16& theSeqNum )
{
    myBitSet[ INDEX_SeqNum ] = true;
    mySeqNum = theSeqNum;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetLFTarpMsg( uint32& theLFTarpMsg ) const
{
    if( true == myBitSet[ INDEX_LFTarpMsg ] )
    {
        theLFTarpMsg = myLFTarpMsg;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetLFTarpMsg( const uint32& theLFTarpMsg )
{
    myBitSet[ INDEX_LFTarpMsg ] = true;
    myLFTarpMsg = theLFTarpMsg;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetNSEL( string& theNSEL ) const
{
    if( true == myBitSet[ INDEX_NSEL ] )
    {
        theNSEL = myNSEL;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetNSEL( const string& theNSEL )
{
    myBitSet[ INDEX_NSEL ] = true;
    myNSEL = theNSEL;
}

//--------------------------------------------------------------
bool  
TL1_TarpRspBlk::GetTarpReset( CT_TarpResetType&  theTarpReset ) const
{
    if( true == myBitSet[ INDEX_TarpReset ] )
    {
        theTarpReset = myTarpReset;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_TarpRspBlk::SetTarpReset( CT_TarpResetType&  theTarpReset )
{
    myBitSet[ INDEX_TarpReset ] = true;
    myTarpReset = theTarpReset;
}

//--------------------------------------------------------------
bool 
TL1_TarpRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_TarpRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_TarpRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_TarpRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

//--------------------------------------------------------------
bool 
TL1_TarpRspBlk::GetSST( CT_SM_SST& theSST ) const
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
TL1_TarpRspBlk::SetSST( CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST = theSST;
}



//--------------------------------------------------------------
bool 
TL1_TarpRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
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
TL1_TarpRspBlk::SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile )  
{
    myBitSet[ INDEX_AlarmProfile ]  = true;
    myAlarmProfile = theAlarmProfile;
}

