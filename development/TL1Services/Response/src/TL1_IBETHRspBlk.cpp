/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/

#include <Response/TL1_IBETHRspBlk.h>

TL1_IBETHRspBlk::TL1_IBETHRspBlk( ) :
myBitSet( INDEX_END, false ),
myLkType(CT_lktype_broadcast),
myBridge(CT_TEL_BridgeNone),
myPST(0),
myPSTQ(0),
mySST(0)
{
}

TL1_IBETHRspBlk::TL1_IBETHRspBlk( const TL1_IBETHRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myIBETHAddr=        t1Blk.myIBETHAddr;
    myLkType=           t1Blk.myLkType;
    myBridge=           t1Blk.myBridge;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_IBETHRspBlk::~TL1_IBETHRspBlk( )
{
}

TL1_IBETHRspBlk& 
TL1_IBETHRspBlk::operator=( const TL1_IBETHRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myIBETHAddr=        t1Blk.myIBETHAddr;
    myLkType=           t1Blk.myLkType;
    myBridge=           t1Blk.myBridge;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_IBETHRspBlk::operator==( const TL1_IBETHRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myIBETHAddr == t1Blk.myIBETHAddr ) )
        return false;

    if ( myLkType != t1Blk.myLkType )
        return false;

    if ( myBridge != t1Blk.myBridge )
        return false;

    if ( myPST != t1Blk.myPST )
        return false;

    if ( myPSTQ != t1Blk.myPSTQ )
        return false;

    if ( mySST != t1Blk.mySST )
        return false;

    return true;
}


bool 
TL1_IBETHRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_IBETHRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}


bool 
TL1_IBETHRspBlk::GetIBETHAddr( CT_TL1_FacAddr& theIBETHAddr ) const
{
    if( true == myBitSet[ INDEX_IBETHAddr ] )
    {
        theIBETHAddr = myIBETHAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_IBETHRspBlk::SetIBETHAddr(  CT_TL1_FacAddr& theIBETHAddr )
{
    myBitSet[ INDEX_IBETHAddr ] = true;
    myIBETHAddr = theIBETHAddr;
}


bool 
TL1_IBETHRspBlk::GetLkType( CT_LkType& theLkType ) const
{
    if( true == myBitSet[ INDEX_LkType] )
    {
        theLkType = myLkType;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_IBETHRspBlk::SetLkType( CT_LkType& theLkType )
{
    myBitSet[ INDEX_LkType ] = true;
    myLkType = theLkType;
}


bool 
TL1_IBETHRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_IBETHRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}


bool 
TL1_IBETHRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_IBETHRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}


bool 
TL1_IBETHRspBlk::GetSST( CT_SM_SST& theSST ) const
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
TL1_IBETHRspBlk::SetSST( CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST = theSST;
}


bool 
TL1_IBETHRspBlk::GetBridge( CT_Bridge& theBridge ) const
{
    if( true == myBitSet[ INDEX_Bridge] )
    {
        theBridge = myBridge;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_IBETHRspBlk::SetBridge( CT_Bridge& theBridge )  
{
    myBitSet[ INDEX_Bridge ]  = true;
    myBridge = theBridge;
}


