/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 RSVP Response 
TARGET:
AUTHOR:         August 13, 2007 - Tong Wu
DESCRIPTION:    Source file for TL1 RSVP and RSVPADJ Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_RsvpRspBlk.h>

TL1_RsvpRspBlk::TL1_RsvpRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_RsvpRspBlk::TL1_RsvpRspBlk( const string*                   theEntityName,
                                const CT_TL1_ControllerAddr*    theAddr,
                                const uint32*                   theSignalingControllerId,
                                const CT_TL1_LinkAddr*          theInterfaceAid,
                                const CT_SM_PST*                thePST,
                                const CT_SM_PSTQ*               thePSTQ )
    : myBitSet( INDEX_END, false ), myAddr(*theAddr)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_RsvpAddr ] = true;
        myAddr = *theAddr;
    }

    if( theSignalingControllerId )
    {
        myBitSet[ INDEX_SignalCtlId ] = true;
        mySignalCtlId = *theSignalingControllerId;
    }

    if( theInterfaceAid )
    {
        myBitSet[ INDEX_InterfaceAid ] = true;
        myInterfaceAid = *theInterfaceAid;
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


TL1_RsvpRspBlk::TL1_RsvpRspBlk( const TL1_RsvpRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;    
    mySignalCtlId=      t1Blk.mySignalCtlId;
    myInterfaceAid=     t1Blk.myInterfaceAid;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
}

TL1_RsvpRspBlk::~TL1_RsvpRspBlk( )
{
}

TL1_RsvpRspBlk& 
TL1_RsvpRspBlk::operator=( const TL1_RsvpRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;    
    mySignalCtlId=      t1Blk.mySignalCtlId;
    myInterfaceAid=     t1Blk.myInterfaceAid;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;

    return *this;
}

bool 
TL1_RsvpRspBlk::operator==( const TL1_RsvpRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( mySignalCtlId != t1Blk.mySignalCtlId )
        return false;

    if ( !(myInterfaceAid == t1Blk.myInterfaceAid) )
        return false;

    if ( myPST != t1Blk.myPST )
        return false;

    if ( myPSTQ != t1Blk.myPSTQ )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_RsvpRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_RsvpRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_RsvpRspBlk::GetRsvpAddr( CT_TL1_ControllerAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_RsvpAddr ] )
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
TL1_RsvpRspBlk::SetRsvpAddr( const CT_TL1_ControllerAddr& theAddr )
{
    myBitSet[ INDEX_RsvpAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool 
TL1_RsvpRspBlk::GetSignalCtlId( uint32& theSignalCtlId ) const
{
    if( true == myBitSet[ INDEX_SignalCtlId ] )
    {
        theSignalCtlId = mySignalCtlId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RsvpRspBlk::SetSignalCtlId( const uint32& theSignalCtlId )
{
    myBitSet[ INDEX_SignalCtlId ] = true;
    mySignalCtlId = theSignalCtlId;
}

//--------------------------------------------------------------
bool 
TL1_RsvpRspBlk::GetInterfaceAid( CT_TL1_LinkAddr& theInterfaceAid ) const
{
    if( true == myBitSet[ INDEX_InterfaceAid ] )
    {
        theInterfaceAid = myInterfaceAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RsvpRspBlk::SetInterfaceAid( const CT_TL1_LinkAddr& theInterfaceAid )
{
    myBitSet[ INDEX_InterfaceAid ] = true;
    myInterfaceAid = theInterfaceAid;
}

//--------------------------------------------------------------
bool 
TL1_RsvpRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_RsvpRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_RsvpRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_RsvpRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

//----------------------------------------------------------------------------------------
TL1_RsvpAdjRspBlk::TL1_RsvpAdjRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_RsvpAdjRspBlk::TL1_RsvpAdjRspBlk( const string*                theEntityName,
                                      const CT_TL1_AdjacencyAddr*  theAddr,
                                      const uint32*                theNeighborSignalAddr,
                                      const uint32*                theNeighborSignalId,
                                      const CT_ProfileTableId*     theAlmProfile,
                                      const CT_SM_PST*             thePST,
                                      const CT_SM_PSTQ*            thePSTQ,
                                      const CT_SM_SST*             theSST )
    : myBitSet( INDEX_END, false ), myAddr(*theAddr)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_RsvpAdjAddr ] = true;
        myAddr = *theAddr;
    }

    if( theNeighborSignalAddr )
    {
        myBitSet[ INDEX_NgbrSignalAddr ] = true;
        myNgbrSignalAddr = *theNeighborSignalAddr;
    }

    if( theNeighborSignalId )
    {
        myBitSet[ INDEX_NgbrSignalId ] = true;
        myNgbrSignalId = *theNeighborSignalId;
    }

    if( theAlmProfile )
    {
        myBitSet[ INDEX_AlmProfile ] = true;
        myAlmProfile = *theAlmProfile;
    }
    
    if( thePST )
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }

    if( thePSTQ )
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
    
    if( theSST )
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
}


TL1_RsvpAdjRspBlk::TL1_RsvpAdjRspBlk( const TL1_RsvpAdjRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;    
    myNgbrSignalAddr=   t1Blk.myNgbrSignalAddr;
    myNgbrSignalId=     t1Blk.myNgbrSignalId;
    myAlmProfile=       t1Blk.myAlmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_RsvpAdjRspBlk::~TL1_RsvpAdjRspBlk( )
{
}

TL1_RsvpAdjRspBlk& 
TL1_RsvpAdjRspBlk::operator=( const TL1_RsvpAdjRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;    
    myNgbrSignalAddr=   t1Blk.myNgbrSignalAddr;
    myNgbrSignalId=     t1Blk.myNgbrSignalId;
    myAlmProfile=       t1Blk.myAlmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_RsvpAdjRspBlk::operator==( const TL1_RsvpAdjRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( myNgbrSignalAddr != t1Blk.myNgbrSignalAddr )
        return false;

    if ( myNgbrSignalId != t1Blk.myNgbrSignalId )
        return false;

    if ( myAlmProfile != t1Blk.myAlmProfile )
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
TL1_RsvpAdjRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_RsvpAdjRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_RsvpAdjRspBlk::GetRsvpAdjAddr( CT_TL1_AdjacencyAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_RsvpAdjAddr ] )
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
TL1_RsvpAdjRspBlk::SetRsvpAdjAddr( const CT_TL1_AdjacencyAddr& theAddr )
{
    myBitSet[ INDEX_RsvpAdjAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool 
TL1_RsvpAdjRspBlk::GetNgbrSignalAddr( uint32& theNgbrSignalAddr ) const
{
    if( true == myBitSet[ INDEX_NgbrSignalAddr ] )
    {
        theNgbrSignalAddr = myNgbrSignalAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RsvpAdjRspBlk::SetNgbrSignalAddr( const uint32& theNgbrSignalAddr )
{
    myBitSet[ INDEX_NgbrSignalAddr ] = true;
    myNgbrSignalAddr = theNgbrSignalAddr;
}
//--------------------------------------------------------------
bool 
TL1_RsvpAdjRspBlk::GetNgbrSignalId( uint32& theNgbrSignalId ) const
{
    if( true == myBitSet[ INDEX_NgbrSignalId] )
    {
        theNgbrSignalId = myNgbrSignalId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RsvpAdjRspBlk::SetNgbrSignalId( const uint32& theNgbrSignalId )
{
    myBitSet[ INDEX_NgbrSignalId ] = true;
    myNgbrSignalId = theNgbrSignalId;
}


//--------------------------------------------------------------
bool 
TL1_RsvpAdjRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
{
    if( true == myBitSet[ INDEX_AlmProfile ] )
    {
        theAlarmProfile = myAlmProfile;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RsvpAdjRspBlk::SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile )
{
    myBitSet[ INDEX_AlmProfile] = true;
    myAlmProfile = theAlarmProfile;
}

//--------------------------------------------------------------
bool 
TL1_RsvpAdjRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_RsvpAdjRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_RsvpAdjRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_RsvpAdjRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

//--------------------------------------------------------------
bool 
TL1_RsvpAdjRspBlk::GetSST( CT_SM_SST& theSST ) const
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
TL1_RsvpAdjRspBlk::SetSST( CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST = theSST;
}
