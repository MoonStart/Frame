/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 CPPF
TARGET:
AUTHOR:         November 07, 2007 - Mike Rodgers
DESCRIPTION:    Source file for TL1 CP Profile Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_CppfRspBlk.h>

TL1_CppfRspBlk::TL1_CppfRspBlk( ) :
    myBitSet( INDEX_END, false ) 
{
}

TL1_CppfRspBlk::TL1_CppfRspBlk( const string*                  theEntityName,
                                const CT_TL1_LogicalAddr*      theAddr,
                                const string*                  theProfName,
                                const CT_GMPLS_MODE*           theGMPLSMode,
                                const uint32*                  theRefreshSecs,
                                const CT_Advertisement*        theAdvertisement )
   : myBitSet( INDEX_END, false )
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_CppfAddr ] = true;
        myAddr = *theAddr;
    }

    if( theProfName )
    {
        myBitSet[ INDEX_ProfileName ] = true;
        myProfileName = *theProfName;
    }

    if( theGMPLSMode )
    {
        myBitSet[ INDEX_GMPLSMode] = true;
        myGMPLSMode = *theGMPLSMode;
    }

    if( theRefreshSecs )
    {
        myBitSet[ INDEX_RefreshSecs] = true;
        myRefreshSecs = *theRefreshSecs;
    }

    if( theAdvertisement )
    {
        myBitSet[ INDEX_Advertisement] = true;
        myAdvertisement = *theAdvertisement;
    }
}


TL1_CppfRspBlk::TL1_CppfRspBlk( const TL1_CppfRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=                  t1Blk.myBitSet;
    myEntityName=              t1Blk.myEntityName;
    myAddr=                    t1Blk.myAddr;    
    myProfileName=             t1Blk.myProfileName;
    myGMPLSMode=               t1Blk.myGMPLSMode;
    myRefreshSecs=             t1Blk.myRefreshSecs;
    myAdvertisement=           t1Blk.myAdvertisement;
}

TL1_CppfRspBlk::~TL1_CppfRspBlk( )
{
}

TL1_CppfRspBlk& TL1_CppfRspBlk::operator=( const TL1_CppfRspBlk& t1Blk )
{
    myBitSet=                  t1Blk.myBitSet;
    myEntityName=              t1Blk.myEntityName;
    myAddr=                    t1Blk.myAddr;    
    myProfileName=             t1Blk.myProfileName;
    myGMPLSMode=               t1Blk.myGMPLSMode;
    myRefreshSecs=             t1Blk.myRefreshSecs;
    myAdvertisement=           t1Blk.myAdvertisement;

    return *this;
}

bool TL1_CppfRspBlk::operator==( const TL1_CppfRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( !( myProfileName == t1Blk.myProfileName ) )
        return false;

    if ( myGMPLSMode != t1Blk.myGMPLSMode )
        return false;

    if ( myRefreshSecs != t1Blk.myRefreshSecs )
        return false;

    if ( myAdvertisement != t1Blk.myAdvertisement )
        return false;


    return true;
}

//--------------------------------------------------------------
bool TL1_CppfRspBlk::GetEntityName( string& theEntityName ) const
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

void TL1_CppfRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool TL1_CppfRspBlk::GetCppfAddr( CT_TL1_LogicalAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_CppfAddr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_CppfRspBlk::SetCppfAddr( const CT_TL1_LogicalAddr& theAddr )
{
    myBitSet[ INDEX_CppfAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool TL1_CppfRspBlk::GetProfileName( string& theProfName) const
{
    if( true == myBitSet[ INDEX_ProfileName ] )
    {
        theProfName = myProfileName;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_CppfRspBlk::SetProfileName( const string& theProfName )
{
   myBitSet[ INDEX_ProfileName ] = true;
   myProfileName = theProfName;
}

//--------------------------------------------------------------
bool TL1_CppfRspBlk::GetGMPLSMode( CT_GMPLS_MODE& theGMPLSMode ) const
{
    if( true == myBitSet[ INDEX_GMPLSMode ] )
    {
        theGMPLSMode = myGMPLSMode;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_CppfRspBlk::SetGMPLSMode( const CT_GMPLS_MODE& theGMPLSMode )
{
    myBitSet[ INDEX_GMPLSMode ] = true;
    myGMPLSMode = theGMPLSMode;
}

//--------------------------------------------------------------
bool TL1_CppfRspBlk::GetRefreshSeconds( uint32& theRefreshSecs ) const
{
    if( true == myBitSet[ INDEX_RefreshSecs ] )
    {
        theRefreshSecs = myRefreshSecs;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_CppfRspBlk::SetRefreshSeconds( const uint32& theRefreshSecs )
{
    myBitSet[ INDEX_RefreshSecs ] = true;
    myRefreshSecs = theRefreshSecs;
}

//--------------------------------------------------------------
bool TL1_CppfRspBlk::GetAdvertisement( CT_Advertisement& theAdvertisement ) const
{
    if( true == myBitSet[ INDEX_Advertisement ] )
    {
        theAdvertisement = myAdvertisement;
        return true;
    }
    else
    {
        return false;
    }
}

void TL1_CppfRspBlk::SetAdvertisement( const CT_Advertisement& theAdvertisement )
{
    myBitSet[ INDEX_Advertisement ] = true;
    myAdvertisement = theAdvertisement;
}

