/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Slot Response 
TARGET:
AUTHOR:         Lee Gernes
DESCRIPTION:    Source file for TL1 Retrive OSPF Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_OspfRspBlk.h>


//OSPF RC
TL1_OspfRspBlk::TL1_OspfRspBlk(const TL1_SmartParameter<string>&             theEntityName,
                             const TL1_SmartParameter<CT_TL1_ControllerAddr>& theOspfAddr,
                             const TL1_SmartParameter<uint32>&             theRouterId,
                             const TL1_SmartParameter<bool>&               theASBRouterFlag,
                             const TL1_SmartParameter<CT_SM_PST>&          thePst,
                             const TL1_SmartParameter<CT_SM_PSTQ>&         thePstq) :

    itsEntityName(theEntityName),
    itsOspfAddr(theOspfAddr),
    itsRouterId(theRouterId),
    itsASBRouterFlag(theASBRouterFlag),
    itsPst(thePst),
    itsPstq(thePstq)
{
}

TL1_OspfRspBlk::~TL1_OspfRspBlk()
{
}
  
TL1_OspfRspBlk::TL1_OspfRspBlk(const TL1_OspfRspBlk& theBlock) :
    itsEntityName(theBlock.itsEntityName),
    itsOspfAddr(theBlock.itsOspfAddr),
    itsRouterId(theBlock.itsRouterId),
    itsASBRouterFlag(theBlock.itsASBRouterFlag),
    itsPst(theBlock.itsPst),
    itsPstq(theBlock.itsPstq)
{
}

TL1_OspfRspBlk& TL1_OspfRspBlk::operator=( const TL1_OspfRspBlk& theBlock )
{
    itsEntityName=      theBlock.itsEntityName;
    itsOspfAddr=        theBlock.itsOspfAddr;
    itsRouterId=        theBlock.itsRouterId;
    itsASBRouterFlag=    theBlock.itsASBRouterFlag;
    itsPst=             theBlock.itsPst;
    itsPstq=            theBlock.itsPstq;

    return *this;
}

//OSPF ADJ
TL1_OspfAdjRspBlk::TL1_OspfAdjRspBlk(const TL1_SmartParameter<string>& theEntityName,
                             const TL1_SmartParameter<CT_TL1_AdjacencyAddr>& theAdjAddr,
                             const TL1_SmartParameter<CT_TL1_LinkAddr>& theInterfaceAddr,
                             const TL1_SmartParameter<CT_TL1_AreaAddr>& theAreaAddr,
                             const TL1_SmartParameter<CT_InterfaceType>& theInterfaceType,
                             const TL1_SmartParameter<CT_Adj_Status>& theAdjStatus,
							 const TL1_SmartParameter<uint32>&             theNghbrId,
                             const TL1_SmartParameter<uint32>&             theIPAddr,
                             const TL1_SmartParameter<CT_SM_PST>&          thePst,
                             const TL1_SmartParameter<CT_SM_PSTQ>&         thePstq,
                             const TL1_SmartParameter<CT_SM_SST>&          theSst) :

    itsEntityName(theEntityName),
    itsAdjAddr(theAdjAddr),
    itsInterfaceAddr(theInterfaceAddr),
    itsAreaAddr(theAreaAddr),
    itsInterfaceType(theInterfaceType),
    itsAdjStatus(theAdjStatus),
	itsNghbrId(theNghbrId),
    itsIPAddr(theIPAddr),
    itsPst(thePst),
    itsPstq(thePstq),
    itsSst(theSst)
{
}

TL1_OspfAdjRspBlk::~TL1_OspfAdjRspBlk()
{
}
  
TL1_OspfAdjRspBlk::TL1_OspfAdjRspBlk(const TL1_OspfAdjRspBlk& theBlock) :
    itsEntityName(theBlock.itsEntityName),
    itsAdjAddr(theBlock.itsAdjAddr),
    itsInterfaceAddr(theBlock.itsInterfaceAddr),
    itsAreaAddr(theBlock.itsAreaAddr),
    itsInterfaceType(theBlock.itsInterfaceType),
    itsAdjStatus(theBlock.itsAdjStatus),
	itsNghbrId(theBlock.itsNghbrId),
    itsIPAddr(theBlock.itsIPAddr),
    itsPst(theBlock.itsPst),
    itsPstq(theBlock.itsPstq),
    itsSst(theBlock.itsSst)
{
}

TL1_OspfAdjRspBlk& TL1_OspfAdjRspBlk::operator=( const TL1_OspfAdjRspBlk& theBlock )
{
    itsEntityName=      theBlock.itsEntityName;
    itsAdjAddr=         theBlock.itsAdjAddr;
    itsInterfaceAddr=   theBlock.itsInterfaceAddr;
    itsAreaAddr=        theBlock.itsAreaAddr;
    itsInterfaceType=   theBlock.itsInterfaceType;
    itsAdjStatus=		theBlock.itsAdjStatus;
	itsNghbrId=         theBlock.itsNghbrId;
    itsIPAddr=          theBlock.itsIPAddr;
    itsPst=             theBlock.itsPst;
    itsPstq=            theBlock.itsPstq;
    itsSst=             theBlock.itsSst;

    return *this;
}

//OSPF AREA
TL1_OspfAreaRspBlk::TL1_OspfAreaRspBlk(const TL1_SmartParameter<string>&        theEntityName,
                             const TL1_SmartParameter<CT_TL1_AreaAddr>&         theAreaAddr,
                             const TL1_SmartParameter<uint32>&                  theRouterAreaId,
                             const TL1_SmartParameter<CT_TL1_LogicalId>&        theProfileId,
                             const TL1_SmartParameter<bool>&                    theHub,
                             const TL1_SmartParameter<CT_RROVisibilityType>&    theRroVisibility,
                             const TL1_SmartParameter<CT_SM_PST>&               thePst,
                             const TL1_SmartParameter<CT_SM_PSTQ>&              thePstq,
                             const TL1_SmartParameter<CT_SM_SST>&               theSst) :

    itsEntityName(theEntityName),
    itsAreaAddr(theAreaAddr),
    itsRouterAreaId(theRouterAreaId),
    itsProfileId(theProfileId),
    itsHub(theHub),
    itsRroVisibility(theRroVisibility),
    itsPst(thePst),
    itsPstq(thePstq),
    itsSst(theSst)
{
}

TL1_OspfAreaRspBlk::~TL1_OspfAreaRspBlk()
{
}
  
TL1_OspfAreaRspBlk::TL1_OspfAreaRspBlk(const TL1_OspfAreaRspBlk& theBlock) :
    itsEntityName(theBlock.itsEntityName),
    itsAreaAddr(theBlock.itsAreaAddr),
    itsRouterAreaId(theBlock.itsRouterAreaId),
    itsProfileId(theBlock.itsProfileId),
    itsHub(theBlock.itsHub),
    itsRroVisibility(theBlock.itsRroVisibility),
    itsPst(theBlock.itsPst),
    itsPstq(theBlock.itsPstq),
    itsSst(theBlock.itsSst)
{
}

TL1_OspfAreaRspBlk& TL1_OspfAreaRspBlk::operator=( const TL1_OspfAreaRspBlk& theBlock )
{
    itsEntityName=      theBlock.itsEntityName;
    itsAreaAddr=        theBlock.itsAreaAddr;
    itsRouterAreaId=    theBlock.itsRouterAreaId;
    itsProfileId=       theBlock.itsProfileId;
    itsHub=             theBlock.itsHub;
    itsRroVisibility=   theBlock.itsRroVisibility;
    itsPst=             theBlock.itsPst;
    itsPstq=            theBlock.itsPstq;
    itsSst=             theBlock.itsSst;

    return *this;
}


//---------------------------------------------------------------------------------------
//   Ospfrpmap
//---------------------------------------------------------------------------------------
TL1_OspfrpmapRspBlk::TL1_OspfrpmapRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_OspfrpmapRspBlk::TL1_OspfrpmapRspBlk( const string*            theEntityName,
                                          const CT_TL1_RpMapAddr*  theAddr )
    : myBitSet( INDEX_END, false ), myAddr(*theAddr)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_OspfrpmapAddr ] = true;
        myAddr = *theAddr;
    }
}


TL1_OspfrpmapRspBlk::TL1_OspfrpmapRspBlk( const TL1_OspfrpmapRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;    
}

TL1_OspfrpmapRspBlk::~TL1_OspfrpmapRspBlk( )
{
}

TL1_OspfrpmapRspBlk& 
TL1_OspfrpmapRspBlk::operator=( const TL1_OspfrpmapRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myAddr=             t1Blk.myAddr;

    return *this;
}

bool 
TL1_OspfrpmapRspBlk::operator==( const TL1_OspfrpmapRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpmapRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_OspfrpmapRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpmapRspBlk::GetOspfrpmapAddr( CT_TL1_RpMapAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_OspfrpmapAddr ] )
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
TL1_OspfrpmapRspBlk::SetOspfrpmapAddr( const CT_TL1_RpMapAddr& theAddr )
{
    myBitSet[ INDEX_OspfrpmapAddr ] = true;
    myAddr = theAddr;
}

//---------------------------------------------------------------------------------------
//   Ospfrp
//---------------------------------------------------------------------------------------
TL1_OspfrpRspBlk::TL1_OspfrpRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_OspfrpRspBlk::TL1_OspfrpRspBlk( const string*               theEntityName,
                                    const CT_TL1_RpAddr*        theAddr,
                                    const uint32*               theChildRtAreaId,
                                    const uint32*               theParentRtAreaId,
                                    const CT_Ospfrp_Entry_Type* theEntryType,
                                    const uint32*               theParentNodeId,
                                    const uint32*               theParentTgtAddr,
                                    const uint32*               theParentTgtAddrMask,
                                    const uint32*               theChildTgtAddr,
                                    const uint32*               theChildTgtAddrMask,
                                    const uint32*               theParentLinkAddr,
                                    const uint32*               theParentLinkIfIdx,
                                    const uint32*               theChildLinkAddr,
                                    const uint32*               theChildLinkIfIdx,
                                    const uint8*                thePrecedence )
    : myBitSet( INDEX_END, false ), myAddr(*theAddr)
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_OspfrpAddr ] = true;
        myAddr = *theAddr;
    }

    if( theChildRtAreaId )
    {
        myBitSet[ INDEX_ChildRtAreaId ] = true;
        myChildRoutingAreaId = *theChildRtAreaId;
    }

    if( theParentRtAreaId )
    {
        myBitSet[ INDEX_ParentRtAreaId ] = true;
        myParentRoutingAreaId = *theParentRtAreaId;
    }

    if( theEntryType )
    {
        myBitSet[ INDEX_EntryType ] = true;
        myEntryType = *theEntryType;
    }

    if( theParentNodeId )
    {
        myBitSet[ INDEX_ParentNodeId ] = true;
        myParentNodeId = *theParentNodeId;
    }

    if( theParentTgtAddr )
    {
        myBitSet[ INDEX_ParentTgtAddr ] = true;
        myParentTgtAddr = *theParentTgtAddr;
    }

    if( theParentTgtAddrMask )
    {
        myBitSet[ INDEX_ParentTgtAddrMask ] = true;
        myParentTgtAddrMask = *theParentTgtAddrMask;
    }

    if( theChildTgtAddr )
    {
        myBitSet[ INDEX_ChildTgtAddr ] = true;
        myChildTgtAddr = *theChildTgtAddr;
    }

    if( theChildTgtAddrMask )
    {
        myBitSet[ INDEX_ChildTgtAddrMask ] = true;
        myChildTgtAddrMask = *theChildTgtAddrMask;
    }

    if( theParentLinkAddr )
    {
        myBitSet[ INDEX_ParentLinkAddr ] = true;
        myParentLinkAddr = *theParentLinkAddr;
    }

    if( theParentLinkIfIdx )
    {
        myBitSet[ INDEX_ParentLinkIfIdx ] = true;
        myParentLinkIfIdx = *theParentLinkIfIdx;
    }

    if( theChildLinkAddr )
    {
        myBitSet[ INDEX_ChildLinkAddr ] = true;
        myChildLinkAddr = *theChildLinkAddr;
    }

    if( theChildLinkIfIdx )
    {
        myBitSet[ INDEX_ChildLinkIfIdx ] = true;
        myChildLinkIfIdx = *theChildLinkIfIdx;
    }

    if( thePrecedence )
    {
        myBitSet[ INDEX_Precedence ] = true;
        myPrecedence = *thePrecedence;
    }
}


TL1_OspfrpRspBlk::TL1_OspfrpRspBlk( const TL1_OspfrpRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=              t1Blk.myBitSet;
    myEntityName=          t1Blk.myEntityName;
    myAddr=                t1Blk.myAddr; 
    myChildRoutingAreaId=  t1Blk.myChildRoutingAreaId;   
    myParentRoutingAreaId= t1Blk.myParentRoutingAreaId;
    myEntryType=           t1Blk.myEntryType;
    myParentNodeId=        t1Blk.myParentNodeId;
    myParentTgtAddr=       t1Blk.myParentTgtAddr;
    myParentTgtAddrMask=   t1Blk.myParentTgtAddrMask;
    myChildTgtAddr=        t1Blk.myChildTgtAddr;
    myChildTgtAddrMask=    t1Blk.myChildTgtAddrMask;
    myParentLinkAddr=      t1Blk.myParentLinkAddr;
    myParentLinkIfIdx=     t1Blk.myParentLinkIfIdx;
    myChildLinkAddr=       t1Blk.myChildLinkAddr;
    myChildLinkIfIdx=      t1Blk.myChildLinkIfIdx;
    myPrecedence=          t1Blk.myPrecedence;
}

TL1_OspfrpRspBlk::~TL1_OspfrpRspBlk( )
{
}

TL1_OspfrpRspBlk& 
TL1_OspfrpRspBlk::operator=( const TL1_OspfrpRspBlk& t1Blk )
{
    myBitSet=              t1Blk.myBitSet;
    myEntityName=          t1Blk.myEntityName;
    myAddr=                t1Blk.myAddr;
    myChildRoutingAreaId=  t1Blk.myChildRoutingAreaId;   
    myParentRoutingAreaId= t1Blk.myParentRoutingAreaId;
    myEntryType=           t1Blk.myEntryType;
    myParentNodeId=        t1Blk.myParentNodeId;
    myParentTgtAddr=       t1Blk.myParentTgtAddr;
    myParentTgtAddrMask=   t1Blk.myParentTgtAddrMask;
    myChildTgtAddr=        t1Blk.myChildTgtAddr;
    myChildTgtAddrMask=    t1Blk.myChildTgtAddrMask;
    myParentLinkAddr=      t1Blk.myParentLinkAddr;
    myParentLinkIfIdx=     t1Blk.myParentLinkIfIdx;
    myChildLinkAddr=       t1Blk.myChildLinkAddr;
    myChildLinkIfIdx=      t1Blk.myChildLinkIfIdx;
    myPrecedence=          t1Blk.myPrecedence;

    return *this;
}

bool 
TL1_OspfrpRspBlk::operator==( const TL1_OspfrpRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( myChildRoutingAreaId != t1Blk.myChildRoutingAreaId )
        return false;

    if ( myParentRoutingAreaId != t1Blk.myParentRoutingAreaId )
        return false;

    if ( myEntryType != t1Blk.myEntryType )
        return false;

    if ( myParentNodeId != t1Blk.myParentNodeId )
        return false;

    if ( myParentTgtAddr != t1Blk.myParentTgtAddr )
        return false;

    if ( myParentTgtAddrMask != t1Blk.myParentTgtAddrMask )
        return false;

    if ( myChildTgtAddr != t1Blk.myChildTgtAddr )
        return false;

    if ( myChildTgtAddrMask != t1Blk.myChildTgtAddrMask )
        return false;

    if ( myParentLinkAddr != t1Blk.myParentLinkAddr )
        return false;

    if ( myParentLinkIfIdx != t1Blk.myParentLinkIfIdx )
        return false;

    if ( myChildLinkAddr != t1Blk.myChildLinkAddr )
        return false;

    if ( myChildLinkIfIdx != t1Blk.myChildLinkIfIdx )
        return false;

    if ( myPrecedence != t1Blk.myPrecedence )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_OspfrpRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetOspfrpAddr( CT_TL1_RpAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_OspfrpAddr ] )
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
TL1_OspfrpRspBlk::SetOspfrpAddr( const CT_TL1_RpAddr& theAddr )
{
    myBitSet[ INDEX_OspfrpAddr ] = true;
    myAddr = theAddr;
}


//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetChildRtAreaId( uint32& theChildRtAreaId ) const
{
    if( true == myBitSet[ INDEX_ChildRtAreaId ] )
    {
        theChildRtAreaId = myChildRoutingAreaId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetChildRtAreaId( const uint32& theChildRtAreaId )
{
    myBitSet[ INDEX_ChildRtAreaId ] = true;
    myChildRoutingAreaId = theChildRtAreaId;
}
//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetParentRtAreaId( uint32& theParentRtAreaId ) const
{
    if( true == myBitSet[ INDEX_ParentRtAreaId ] )
    {
        theParentRtAreaId = myParentRoutingAreaId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetParentRtAreaId( const uint32& theParentRtAreaId )
{
    myBitSet[ INDEX_ParentRtAreaId ] = true;
    myParentRoutingAreaId = theParentRtAreaId;
}


//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetEntryType( CT_Ospfrp_Entry_Type& theEntryType ) const
{
    if( true == myBitSet[ INDEX_EntryType ] )
    {
        theEntryType = myEntryType;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetEntryType( const CT_Ospfrp_Entry_Type& theEntryType  )
{
    myBitSet[ INDEX_EntryType ] = true;
    myEntryType = theEntryType;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetParentNodeId( uint32& theParentNodeId ) const
{
    if( true == myBitSet[ INDEX_ParentNodeId ] )
    {
        theParentNodeId = myParentNodeId;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_OspfrpRspBlk::SetParentNodeId( const uint32& theParentNodeId )
{
    myBitSet[ INDEX_ParentNodeId ] = true;
    myParentNodeId = theParentNodeId;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetParentTgtAddr( uint32& theParentTgtAddr ) const
{
    if( true == myBitSet[ INDEX_ParentTgtAddr ] )
    {
        theParentTgtAddr = myParentTgtAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetParentTgtAddr( const uint32& theParentTgtAddr )
{
    myBitSet[ INDEX_ParentTgtAddr ] = true;
    myParentTgtAddr = theParentTgtAddr;
}
//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetParentTgtAddrMask( uint32& theParentTgtAddrMask ) const
{
    if( true == myBitSet[ INDEX_ParentTgtAddrMask ] )
    {
        theParentTgtAddrMask = myParentTgtAddrMask;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetParentTgtAddrMask( const uint32& theParentTgtAddrMask )
{
    myBitSet[ INDEX_ParentTgtAddrMask ] = true;
    myParentTgtAddrMask = theParentTgtAddrMask;
}


//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetChildTgtAddr( uint32& theChildTgtAddr ) const
{
    if( true == myBitSet[ INDEX_ChildTgtAddr ] )
    {
        theChildTgtAddr = myChildTgtAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetChildTgtAddr( const uint32& theChildTgtAddr  )
{
    myBitSet[ INDEX_ChildTgtAddr ] = true;
    myChildTgtAddr = theChildTgtAddr;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetChildTgtAddrMask( uint32& theChildTgtAddrMask ) const
{
    if( true == myBitSet[ INDEX_ChildTgtAddrMask ] )
    {
        theChildTgtAddrMask = myChildTgtAddrMask;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_OspfrpRspBlk::SetChildTgtAddrMask( const uint32& theChildTgtAddrMask )
{
    myBitSet[ INDEX_ChildTgtAddrMask ] = true;
    myChildTgtAddrMask = theChildTgtAddrMask;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetParentLinkAddr( uint32& theParentLinkAddr ) const
{
    if( true == myBitSet[ INDEX_ParentLinkAddr ] )
    {
        theParentLinkAddr = myParentLinkAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetParentLinkAddr( const uint32& theParentLinkAddr )
{
    myBitSet[ INDEX_ParentLinkAddr ] = true;
    myParentLinkAddr = theParentLinkAddr;
}
//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetParentLinkIfIdx( uint32& theParentLinkIfIdx ) const
{
    if( true == myBitSet[ INDEX_ParentLinkIfIdx ] )
    {
        theParentLinkIfIdx = myParentLinkIfIdx;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetParentLinkIfIdx( const uint32& theParentLinkIfIdx )
{
    myBitSet[ INDEX_ParentLinkIfIdx ] = true;
    myParentLinkIfIdx = theParentLinkIfIdx;
}


//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetChildLinkAddr( uint32& theChildLinkAddr ) const
{
    if( true == myBitSet[ INDEX_ChildLinkAddr ] )
    {
        theChildLinkAddr = myChildLinkAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_OspfrpRspBlk::SetChildLinkAddr( const uint32& theChildLinkAddr  )
{
    myBitSet[ INDEX_ChildLinkAddr ] = true;
    myChildLinkAddr = theChildLinkAddr;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetChildLinkIfIdx( uint32& theChildLinkIfIdx ) const
{
    if( true == myBitSet[ INDEX_ChildLinkIfIdx ] )
    {
        theChildLinkIfIdx = myChildLinkIfIdx;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_OspfrpRspBlk::SetChildLinkIfIdx( const uint32& theChildLinkIfIdx )
{
    myBitSet[ INDEX_ChildLinkIfIdx ] = true;
    myChildLinkIfIdx = theChildLinkIfIdx;
}

//--------------------------------------------------------------
bool 
TL1_OspfrpRspBlk::GetPrecedence( uint8& thePrecedence ) const
{
    if( true == myBitSet[ INDEX_Precedence ] )
    {
        thePrecedence = myPrecedence;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_OspfrpRspBlk::SetPrecedence( const uint8& thePrecedence )
{
    myBitSet[ INDEX_Precedence ] = true;
    myPrecedence = thePrecedence;
}



