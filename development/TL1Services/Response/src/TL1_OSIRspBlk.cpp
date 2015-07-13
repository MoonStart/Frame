/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OSI Response 
TARGET:
AUTHOR:         August 11, 2006 - Thomas Novak
DESCRIPTION:    Source file for TL1 OSI Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_OSIRspBlk.h>

TL1_OSIRTRRspBlk::TL1_OSIRTRRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_OSIRTRRspBlk::TL1_OSIRTRRspBlk( const TL1_OSIRTRRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myOsiRtrAddr=       t1Blk.myOsiRtrAddr;

    myPrimaryAddr=      t1Blk.myPrimaryAddr;
    myAuxAddr1=         t1Blk.myAuxAddr1;
    myAuxAddr2=         t1Blk.myAuxAddr2;
    myRSysId=           t1Blk.myRSysId;
    myMaxLifetime=      t1Blk.myMaxLifetime;
    myLevel=            t1Blk.myLevel;
    myNumMaxArea=       t1Blk.myNumMaxArea;
    myLevel1State=      t1Blk.myLevel1State;
    myLevel2State=      t1Blk.myLevel2State;
    myNSAP=             t1Blk.myNSAP;
    myEonGre=           t1Blk.myEonGre;

    myAlarmProfile=     t1Blk.myAlarmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_OSIRTRRspBlk::~TL1_OSIRTRRspBlk( )
{
}

TL1_OSIRTRRspBlk& 
TL1_OSIRTRRspBlk::operator=( const TL1_OSIRTRRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myOsiRtrAddr=       t1Blk.myOsiRtrAddr;

    myPrimaryAddr=      t1Blk.myPrimaryAddr;
    myAuxAddr1=         t1Blk.myAuxAddr1;
    myAuxAddr2=         t1Blk.myAuxAddr2;
    myRSysId=           t1Blk.myRSysId;
    myMaxLifetime=      t1Blk.myMaxLifetime;
    myLevel=            t1Blk.myLevel;
    myNumMaxArea=       t1Blk.myNumMaxArea;
    myLevel1State=      t1Blk.myLevel1State;
    myLevel2State=      t1Blk.myLevel2State;
    myNSAP=             t1Blk.myNSAP;
    myEonGre=           t1Blk.myEonGre;

    myAlarmProfile=     t1Blk.myAlarmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_OSIRTRRspBlk::operator==( const TL1_OSIRTRRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myOsiRtrAddr == t1Blk.myOsiRtrAddr ) )
        return false;

    if ( myPrimaryAddr != t1Blk.myPrimaryAddr )
        return false;

    if ( myAuxAddr1 != t1Blk.myAuxAddr1 )
        return false;

    if ( myAuxAddr2 != t1Blk.myAuxAddr2 )
        return false;

    if ( myRSysId != t1Blk.myRSysId )
        return false;

    if ( myMaxLifetime != t1Blk.myMaxLifetime )
        return false;

    if ( myLevel != t1Blk.myLevel )
        return false;

    if ( myNumMaxArea != t1Blk.myNumMaxArea )
        return false;

    if ( myLevel1State != t1Blk.myLevel1State )
        return false;

    if ( myLevel2State != t1Blk.myLevel2State )
        return false;

    if ( myNSAP != t1Blk.myNSAP )
        return false;

    if ( myEonGre != t1Blk.myEonGre )
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
TL1_OSIRTRRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_OSIRTRRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetOsiRtrAddr( CT_TL1_FacAddr& theOsiRtrAddr ) const
{
    if( true == myBitSet[ INDEX_OsiRtrAddr ] )
    {
        theOsiRtrAddr = myOsiRtrAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetOsiRtrAddr( const CT_TL1_FacAddr& theOsiRtrAddr )
{
    myBitSet[ INDEX_OsiRtrAddr ] = true;
    myOsiRtrAddr = theOsiRtrAddr;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetPrimaryAddress( string& thePrimaryAddr ) const
{
    if( true == myBitSet[ INDEX_PrimaryAddr ] )
    {
        thePrimaryAddr = myPrimaryAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetPrimaryAddress( const string& thePrimaryAddr )
{
    myBitSet[ INDEX_PrimaryAddr ] = true;
    myPrimaryAddr = thePrimaryAddr;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetAuxillaryAddress1(  string& theAuxAddr1 ) const
{
    if( true == myBitSet[ INDEX_AuxAddr1 ] )
    {
        theAuxAddr1 = myAuxAddr1;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetAuxillaryAddress1( const string& theAuxAddr1 )
{
    myBitSet[ INDEX_AuxAddr1 ] = true;
    myAuxAddr1 = theAuxAddr1;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetAuxillaryAddress2(  string& theAuxAddr2 ) const
{
    if( true == myBitSet[ INDEX_AuxAddr2 ] )
    {
        theAuxAddr2 = myAuxAddr2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetAuxillaryAddress2 ( const string& theAuxAddr2 )
{
    myBitSet[ INDEX_AuxAddr2 ] = true;
    myAuxAddr2 = theAuxAddr2;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetRoutingSysId( string& theRSysId ) const
{
    if( true == myBitSet[ INDEX_RSysId ] )
    {
        theRSysId = myRSysId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetRoutingSysId( const string& theRSysId )
{
    myBitSet[ INDEX_RSysId ] = true;
    myRSysId = theRSysId;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetMaxLifetimeControl( uint16& theMaxLifetime ) const
{
    if( true == myBitSet[ INDEX_MaxLifetime ] )
    {
        theMaxLifetime = myMaxLifetime;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetMaxLifetimeControl( const uint16& theMaxLifetime )
{
    myBitSet[ INDEX_MaxLifetime ] = true;
    myMaxLifetime = theMaxLifetime;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetRoutingLevel( uint16& theLevel ) const
{
    if( true == myBitSet[ INDEX_Level ] )
    {
        theLevel = myLevel;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetRoutingLevel( const uint16& theLevel )
{
    myBitSet[ INDEX_Level ] = true;
    myLevel = theLevel;
}

//--------------------------------------------------------------
bool  
TL1_OSIRTRRspBlk::GetNSAP( string& theNSAP ) const
{
    if( true == myBitSet[ INDEX_NSAP ] )
    {
        theNSAP = myNSAP;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_OSIRTRRspBlk::SetNSAP( const string& theNSAP )
{
    myBitSet[ INDEX_NSAP ] = true;
    myNSAP = theNSAP;
}

//--------------------------------------------------------------
bool  
TL1_OSIRTRRspBlk::GetEonGre( bool& theEonGre ) const
{
    if( true == myBitSet[ INDEX_EONGRE ] )
    {
        theEonGre = myEonGre;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_OSIRTRRspBlk::SetEonGre( const bool& theEonGre )
{
    myBitSet[ INDEX_EONGRE ] = true;
    myEonGre = theEonGre;
}


//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetMaxAreaAddress( uint16& theNumMaxArea ) const
{
    if( true == myBitSet[ INDEX_NumMaxArea ] )
    {
        theNumMaxArea = myNumMaxArea;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetMaxAreaAddress( const uint16& theNumMaxArea )
{
    myBitSet[ INDEX_NumMaxArea ] = true;
    myNumMaxArea = theNumMaxArea;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_OSIRTRRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_OSIRTRRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetSST( CT_SM_SST& theSST ) const
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
TL1_OSIRTRRspBlk::SetSST( CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST = theSST;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
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
TL1_OSIRTRRspBlk::SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile )  
{
    myBitSet[ INDEX_AlarmProfile ]  = true;
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetLevel1State( uint16& theLevel1State ) const
{
    if( true == myBitSet[ INDEX_Level1State ] )
    {
        theLevel1State = myLevel1State;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetLevel1State( const uint16& theLevel1State ) 
{
    myBitSet[ INDEX_Level1State ]  = true;
    myLevel1State = theLevel1State;
}

//--------------------------------------------------------------
bool 
TL1_OSIRTRRspBlk::GetLevel2State( uint16& theLevel2State ) const
{
    if( true == myBitSet[ INDEX_Level2State ] )
    {
        theLevel2State = myLevel2State;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OSIRTRRspBlk::SetLevel2State( const uint16& theLevel2State ) 
{
    myBitSet[ INDEX_Level2State ]  = true;
    myLevel2State = theLevel2State;
}

//--------------------------------------------------------------
TL1_OsiRtrMapNeighborRspBlk::TL1_OsiRtrMapNeighborRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_OsiRtrMapNeighborRspBlk::TL1_OsiRtrMapNeighborRspBlk(const TL1_OsiRtrMapNeighborRspBlk& theBlk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=       theBlk.myBitSet;

    myEntityName=   theBlk.myEntityName;
    myOsiRtrAddr=   theBlk.myOsiRtrAddr;

    myLapdName=     theBlk.myLapdName; 
    myLapdAddr=     theBlk.myLapdAddr;

    myNsapAddress=  theBlk.myNsapAddress; 
    myRouterLevel=  theBlk.myRouterLevel;

    myTid=          theBlk.myTid;
}

TL1_OsiRtrMapNeighborRspBlk::~TL1_OsiRtrMapNeighborRspBlk( )
{

}

TL1_OsiRtrMapNeighborRspBlk& 
TL1_OsiRtrMapNeighborRspBlk::operator=( const TL1_OsiRtrMapNeighborRspBlk& theBlk )
{
    myBitSet=       theBlk.myBitSet;

    myEntityName=   theBlk.myEntityName;
    myOsiRtrAddr=   theBlk.myOsiRtrAddr;

    myLapdName=     theBlk.myLapdName; 
    myLapdAddr=     theBlk.myLapdAddr;

    myNsapAddress=  theBlk.myNsapAddress; 
    myRouterLevel=  theBlk.myRouterLevel;

    myTid=          theBlk.myTid;

    return *this;
}

bool 
TL1_OsiRtrMapNeighborRspBlk::operator==( const TL1_OsiRtrMapNeighborRspBlk& theBlk ) const
{
    if ( myBitSet != theBlk.myBitSet )
        return false;

    if ( myEntityName != theBlk.myEntityName )
        return false;

    if ( !( myOsiRtrAddr == theBlk.myOsiRtrAddr ) )
        return false;

    if ( !( myLapdName == theBlk.myLapdName ) )
        return false;

    if ( !( myLapdAddr == theBlk.myLapdAddr ) )
        return false;

    if ( !( myNsapAddress == theBlk.myNsapAddress ) )
        return false;

    if ( myRouterLevel != theBlk.myRouterLevel )
       return false;

    if ( !( myTid == theBlk.myTid ) )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNeighborRspBlk::GetRouterLevel( uint8& theLevel ) const
{
    if( true == myBitSet[ INDEX_RouterLevel ] )
    {
        theLevel = myRouterLevel;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNeighborRspBlk::SetRouterLevel( const uint8& theLevel )
{
    myBitSet[ INDEX_RouterLevel ] = true;
    myRouterLevel = theLevel;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNeighborRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_OsiRtrMapNeighborRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNeighborRspBlk::GetOsiRtrAddr( CT_TL1_FacAddr& theOsiRtrAddr ) const
{
    if( true == myBitSet[ INDEX_OsiRtrAddr ] )
    {
        theOsiRtrAddr = myOsiRtrAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNeighborRspBlk::SetOsiRtrAddr( const CT_TL1_FacAddr& theOsiRtrAddr )
{
    myBitSet[ INDEX_OsiRtrAddr ] = true;
    myOsiRtrAddr = theOsiRtrAddr;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNeighborRspBlk::GetLapdName( string& theLapdName ) const
{
    if( true == myBitSet[ INDEX_LapdName ] )
    {
        theLapdName = myLapdName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNeighborRspBlk::SetLapdName( const string& theLapdName )
{
   myBitSet[ INDEX_LapdName ] = true;
   myLapdName = theLapdName;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNeighborRspBlk::GetLapdAddr( CT_TL1_FacAddr& theLapdAddr ) const
{
    if( true == myBitSet[ INDEX_LapdAddr ] )
    {
        theLapdAddr = myLapdAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNeighborRspBlk::SetLapdAddr( const CT_TL1_FacAddr& theLapdAddr )
{
   myBitSet[ INDEX_LapdAddr ] = true;
   myLapdAddr = theLapdAddr;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNeighborRspBlk::GetNsapAddress( string& theNsapAddr ) const
{
    if( true == myBitSet[ INDEX_NsapAddress ] )
    {
        theNsapAddr = myNsapAddress;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNeighborRspBlk::SetNsapAddress( const string& theNsapAddr )
{
    myBitSet[ INDEX_NsapAddress ] = true;
    myNsapAddress = theNsapAddr;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNeighborRspBlk::GetTid( string& theTid ) const
{
    if( true == myBitSet[ INDEX_Tid ] )
    {
        theTid = myTid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNeighborRspBlk::SetTid( const string& theTid )
{
    myBitSet[ INDEX_Tid ] = true;
    myTid = theTid;
}

//--------------------------------------------------------------
TL1_OsiRtrMapNetworkRspBlk::TL1_OsiRtrMapNetworkRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_OsiRtrMapNetworkRspBlk::TL1_OsiRtrMapNetworkRspBlk(const TL1_OsiRtrMapNetworkRspBlk& theBlk ) :
    myBitSet( INDEX_END, false )
{
	myBitSet=       theBlk.myBitSet;

    myEntityName=   theBlk.myEntityName;
    myOsiRtrAddr=   theBlk.myOsiRtrAddr;

    myLapdName=     theBlk.myLapdName; 
    myLapdAddr=     theBlk.myLapdAddr;

    myNsapAddress=  theBlk.myNsapAddress; 
    myTid=          theBlk.myTid;

}

TL1_OsiRtrMapNetworkRspBlk::~TL1_OsiRtrMapNetworkRspBlk( )
{

}

TL1_OsiRtrMapNetworkRspBlk& 
TL1_OsiRtrMapNetworkRspBlk::operator=( const TL1_OsiRtrMapNetworkRspBlk& theBlk )
{
    myBitSet=       theBlk.myBitSet;

    myEntityName=   theBlk.myEntityName;
    myOsiRtrAddr=   theBlk.myOsiRtrAddr;

    myLapdName=     theBlk.myLapdName; 
    myLapdAddr=     theBlk.myLapdAddr;

    myNsapAddress=  theBlk.myNsapAddress; 
    myTid=          theBlk.myTid;

    return *this;
}

bool 
TL1_OsiRtrMapNetworkRspBlk::operator==( const TL1_OsiRtrMapNetworkRspBlk& theBlk ) const
{
    if ( myBitSet != theBlk.myBitSet )
        return false;

    if ( myEntityName != theBlk.myEntityName )
        return false;

    if ( !( myOsiRtrAddr == theBlk.myOsiRtrAddr ) )
        return false;

    if ( !( myLapdName == theBlk.myLapdName ) )
        return false;

    if ( !( myLapdAddr == theBlk.myLapdAddr ) )
        return false;

    if ( !( myNsapAddress == theBlk.myNsapAddress ) )
        return false;

    if (  !( myTid == theBlk.myTid ) )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNetworkRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_OsiRtrMapNetworkRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNetworkRspBlk::GetOsiRtrAddr( CT_TL1_FacAddr& theOsiRtrAddr ) const
{
    if( true == myBitSet[ INDEX_OsiRtrAddr ] )
    {
        theOsiRtrAddr = myOsiRtrAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNetworkRspBlk::SetOsiRtrAddr( const CT_TL1_FacAddr& theOsiRtrAddr )
{
    myBitSet[ INDEX_OsiRtrAddr ] = true;
    myOsiRtrAddr = theOsiRtrAddr;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNetworkRspBlk::GetLapdName( string& theLapdName ) const
{
    if( true == myBitSet[ INDEX_LapdName ] )
    {
        theLapdName = myLapdName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNetworkRspBlk::SetLapdName( const string& theLapdName )
{
   myBitSet[ INDEX_LapdName ] = true;
   myLapdName = theLapdName;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNetworkRspBlk::GetLapdAddr( CT_TL1_FacAddr& theLapdAddr ) const
{
    if( true == myBitSet[ INDEX_LapdAddr ] )
    {
        theLapdAddr = myLapdAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNetworkRspBlk::SetLapdAddr( const CT_TL1_FacAddr& theLapdAddr )
{
   myBitSet[ INDEX_LapdAddr ] = true;
   myLapdAddr = theLapdAddr;
}

//--------------------------------------------------------------
bool 
TL1_OsiRtrMapNetworkRspBlk::GetNsapAddress( string& theNsapAddr ) const
{
    if( true == myBitSet[ INDEX_NsapAddress ] )
    {
        theNsapAddr = myNsapAddress;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNetworkRspBlk::SetNsapAddress( const string& theNsapAddr )
{
    myBitSet[ INDEX_NsapAddress ] = true;
    myNsapAddress = theNsapAddr;
}

///--------------------------------------------------------------
bool 
TL1_OsiRtrMapNetworkRspBlk::GetTid( string& theTid ) const
{
    if( true == myBitSet[ INDEX_Tid ] )
    {
        theTid = myTid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OsiRtrMapNetworkRspBlk::SetTid( const string& theTid )
{
    myBitSet[ INDEX_Tid ] = true;
    myTid = theTid;
}
