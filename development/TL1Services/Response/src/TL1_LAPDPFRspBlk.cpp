/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OCH Response 
TARGET:
AUTHOR:         July 10, 2006 - Thomas Novak
DESCRIPTION:    Source file for TL1 LPADPF Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_LAPDPFRspBlk.h>

TL1_LAPDPFRspBlk::TL1_LAPDPFRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_LAPDPFRspBlk::TL1_LAPDPFRspBlk( const TL1_LAPDPFRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet     = t1Blk.myBitSet;
    myEntityName = t1Blk.myEntityName;
    myAddr       = t1Blk.myAddr;
    myTxMode     = t1Blk.myTxMode;
    mySide       = t1Blk.mySide;
    mySeqNum     = t1Blk.mySeqNum;
    myPFname     = t1Blk.myPFname;
    myRtranscnt  = t1Blk.myRtranscnt;
    myAcktmr     = t1Blk.myAcktmr;
    myMxfrm      = t1Blk.myMxfrm;
    myFrmcnt     = t1Blk.myFrmcnt;
    myInacttmr   = t1Blk.myInacttmr;
}

TL1_LAPDPFRspBlk::~TL1_LAPDPFRspBlk( )
{
}

TL1_LAPDPFRspBlk& 
TL1_LAPDPFRspBlk::operator=( const TL1_LAPDPFRspBlk& t1Blk )
{
    myBitSet     = t1Blk.myBitSet;
    myEntityName = t1Blk.myEntityName;
    myAddr       = t1Blk.myAddr;
    myTxMode     = t1Blk.myTxMode;
    mySide       = t1Blk.mySide;
    mySeqNum     = t1Blk.mySeqNum;
    myPFname     = t1Blk.myPFname;
    myRtranscnt  = t1Blk.myRtranscnt;
    myAcktmr     = t1Blk.myAcktmr;
    myMxfrm      = t1Blk.myMxfrm;
    myFrmcnt     = t1Blk.myFrmcnt;
    myInacttmr   = t1Blk.myInacttmr;

    return *this;
}

bool 
TL1_LAPDPFRspBlk::operator==( const TL1_LAPDPFRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet)
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myAddr == t1Blk.myAddr ) )
        return false;

    if ( myTxMode != t1Blk.myTxMode )
        return false;

    if ( mySide != t1Blk.mySide )
        return false;

    if ( mySeqNum != t1Blk.mySeqNum )
        return false;

    if ( !(myPFname == t1Blk.myPFname ) )
        return false;

    if ( myRtranscnt != t1Blk.myRtranscnt )
        return false;

    if ( myAcktmr != t1Blk.myAcktmr )
        return false;

    if ( myMxfrm != t1Blk.myMxfrm )
        return false;

    if ( myFrmcnt != t1Blk.myFrmcnt )
        return false;

    if ( myInacttmr != t1Blk.myInacttmr )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_LAPDPFRspBlk::GetEntityName(string& theEntityName ) const
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
TL1_LAPDPFRspBlk::SetEntityName( const string& theEntityName ) 
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_LAPDPFRspBlk::GetFacAddr( CT_TL1_FacAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
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
TL1_LAPDPFRspBlk::SetFacAddr( const CT_TL1_FacAddr& theAddr ) 
{
    myBitSet[ INDEX_FacAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetTxMode( CT_LPF_TxMode& theTxMode ) const
{
    if ( true == myBitSet[ INDEX_TxMode ] ) 
    {
        theTxMode = myTxMode;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LAPDPFRspBlk::SetTxMode( const CT_LPF_TxMode& theTxMode )
{
    myBitSet[ INDEX_TxMode ] = true;
    myTxMode = theTxMode;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetSide( CT_LPF_Side& theSide ) const
{
    if ( true == myBitSet[ INDEX_Side ] ) 
    {
        theSide = mySide;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LAPDPFRspBlk::SetSide( const CT_LPF_Side& theSide ) 
{
    myBitSet[ INDEX_Side ] = true;
    mySide = theSide;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetSeqNum( CT_LPF_SeqNum& theSeqNum ) const
{
    if ( true == myBitSet[ INDEX_SeqNum ] ) 
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
TL1_LAPDPFRspBlk::SetSeqNum( const CT_LPF_SeqNum& theSeqNum ) 
{
    myBitSet[ INDEX_SeqNum ] = true;
    mySeqNum = theSeqNum;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetPFname( CT_Fac_TraceString& thePFname ) const
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
TL1_LAPDPFRspBlk::SetPFname( const CT_Fac_TraceString& thePFname ) 
{
    myBitSet[ INDEX_PFname] = true;
    myPFname = thePFname;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetRtranscnt( uint16& theRtranscnt ) const
{
    if ( true == myBitSet[ INDEX_Rtranscnt ] ) 
    {
        theRtranscnt = myRtranscnt;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LAPDPFRspBlk::SetRtranscnt( const uint16& theRtranscnt ) 
{
    myBitSet[ INDEX_Rtranscnt ] = true;
    myRtranscnt = theRtranscnt;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetAcktmr( CT_LapdProfile_Timer& theAcktmr ) const
{
    if ( true == myBitSet[ INDEX_Acktmr ] ) 
    {
        theAcktmr = myAcktmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LAPDPFRspBlk::SetAcktmr( const CT_LapdProfile_Timer& theAcktmr ) 
{
    myBitSet[ INDEX_Acktmr ] = true;
    myAcktmr = theAcktmr;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetMxfrm( uint16& theMxfrm ) const
{
    if ( true == myBitSet[ INDEX_Acktmr ] ) 
    {
        theMxfrm = myMxfrm;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LAPDPFRspBlk::SetMxfrm( const uint16& theMxfrm ) 
{
    myBitSet[ INDEX_Mxfrm ] = true;
    myMxfrm = theMxfrm;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetFrmcnt( uint16& theFrmcnt ) const
{
    if ( true == myBitSet[ INDEX_Frmcnt ] ) 
    {
        theFrmcnt = myFrmcnt;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LAPDPFRspBlk::SetFrmcnt( const uint16& theFrmcnt ) 
{
    myBitSet[ INDEX_Frmcnt ] = true;
    myFrmcnt = theFrmcnt;
}

//--------------------------------------------------------------
bool  
TL1_LAPDPFRspBlk::GetInacttmr( uint16& theInacttmr ) const
{
    if ( true == myBitSet[ INDEX_Inacttmr ] ) 
    {
        theInacttmr = myInacttmr;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LAPDPFRspBlk::SetInacttmr( const uint16& theInacttmr ) 
{
    myBitSet[ INDEX_Inacttmr ] = true; 
    myInacttmr = theInacttmr;
}

