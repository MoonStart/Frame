/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Link Response 
TARGET:
AUTHOR:         June 19, 2007 - Mike Rodgers
DESCRIPTION:    Source file for TL1 Link Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_LinkRspBlk.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>

TL1_LinkRspBlk::TL1_LinkRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_LinkRspBlk::TL1_LinkRspBlk( 
                    const CT_TL1_LinkAddr&        theAddr,
                    const string&                 theEntityName,
                    const string&                 theTLname,
                    const CT_TLNEADDRT&           theNearEndAddrType,
                    const CT_ControlPlane_TL&     theNearEndAddr,
                    const uint32                  theNearEndMask,
                    const CT_TL1_LinkAddr&        theNearEndParentTL,
                    const uint32                  theCost,
                    const CT_TL_DISCOVERY_TYPE&   theNeighborDiscovery,
                    const uint32                  theIfIndex,
                    const uint32                  theNodeId,
                    const CT_ControlPlane_Addr&   theNeighborIfIndex,
                    const CT_ControlPlane_Addr&   theNeighborNodeId,
                    const CT_TL1_LogicalAddr&     theLinkPfAid,
                    const CT_ControlPlane_Addr&   theNeighborSignalingAddr,
                    const CT_ControlPlane_Addr&   theNeighborSignalingId,
                    const CT_TL_ROUTING&          theRouting,
                    const CT_TL_SIGNALING&        theSignaling,
                    const CT_ControlPlane_Addr&   theRouterAreaId,
                    const CT_ControlPlane_Srlg&   theSrlg,
                    const uint32                  theLatency,
                    const string&                 theCarrierId,
                    const CT_ControlPlane_Addr&   theResourceClass,
                    const CT_TL1_ResourceAddr&    theResource,
                    const CT_IfNumber&            theIfName,
                    const string&                 theTLList,
                    const CT_LatencyMode&         theLatencyMode,
                    const uint16                  thePmd,
                    const uint16                  theOsnr,
                    const int                     theFwmp,
                    const int                     thePdl,
                    const int                     theResidualCD,
                    const int                     theSpmNoise,
                    const int                     theXpmNoise,
                    const CT_RESOURCE_LAYER&      theResourceLayer,
                    const CT_SM_PST&              thePST,
                    const CT_SM_PSTQ&             thePSTQ,
                    const CT_SM_SST&              theSST )

    : myBitSet( INDEX_END, false )
{
    myBitSet[ INDEX_Addr ] = true;
    myAddr= theAddr;
    
    myBitSet[ INDEX_EntityName ] = true;
    myEntityName= theEntityName;

    myBitSet[ INDEX_TLname ] = true;
    myTLname= theTLname;

    myBitSet[ INDEX_NearEndAddrType ] = true;
    myNearEndAddrType= theNearEndAddrType;

    myBitSet[ INDEX_NearEndAddr ] = true;
    myNearEndAddr= theNearEndAddr;

    myBitSet[ INDEX_NearEndMask ] = true;
    myNearEndMask= theNearEndMask;

    myBitSet[ INDEX_NearEndParentTL ] = true;
    myNearEndParentTL= theNearEndParentTL;

    myBitSet[ INDEX_Cost ] = true;
    myCost= theCost;

    myBitSet[ INDEX_NeighborDiscovery ] = true;
    myNeighborDiscovery= theNeighborDiscovery;

    myBitSet[ INDEX_IfIndex ] = true;
    myIfIndex= theIfIndex;

    myBitSet[ INDEX_NodeId ] = true;
    myNodeId= theNodeId;

    myBitSet[ INDEX_NeighborIfIndex ] = true;
    myNeighborIfIndex= theNeighborIfIndex;

    myBitSet[ INDEX_NeighborNodeId ] = true;
    myNeighborNodeId= theNeighborNodeId;

    myBitSet[ INDEX_LinkPfAid ] = true;
    myLinkPfAid= theLinkPfAid;

    myBitSet[ INDEX_NeighborSignalingAddr ] = true;
    myNeighborSignalingAddr= theNeighborSignalingAddr;

    myBitSet[ INDEX_NeighborSignalingId ] = true;
    myNeighborSignalingId= theNeighborSignalingId;

    myBitSet[ INDEX_Routing ] = true;
    myRouting= theRouting;

    myBitSet[ INDEX_Signaling ] = true;
    mySignaling= theSignaling;

    myBitSet[ INDEX_RouterAreaId ] = true;
    myRouterAreaId= theRouterAreaId;

    myBitSet[ INDEX_Srlg ] = true;
    mySrlg= theSrlg;

    myBitSet[ INDEX_Latency ] = true;
    myLatency= theLatency;

    myBitSet[ INDEX_CarrierId ] = true;
    myCarrierId= theCarrierId;

    myBitSet[ INDEX_ResourceClass ] = true;
    myResourceClass= theResourceClass;

    myBitSet[ INDEX_Resource ] = true;
    myResource= theResource;

    myBitSet[ INDEX_IfName ] = true;
    myIfName= theIfName;

    myBitSet[ INDEX_TLList ] = true;
    myTLList= theTLList;

    myBitSet[ INDEX_LatencyMode ] = true;
    myLatencyMode= theLatencyMode;

    myBitSet[ INDEX_Pmd ] = true;
    myPmd= thePmd;

    myBitSet[ INDEX_Osnr ] = true;
    myOsnr= theOsnr;

    myBitSet[ INDEX_Fwmp ] = true;
    myFwmp= theFwmp;

    myBitSet[ INDEX_Pdl ] = true;
    myPdl= thePdl;

    myBitSet[ INDEX_ResidualCD ] = true;
    myResidualCD= theResidualCD;

    myBitSet[ INDEX_SpmNoise ] = true;
    mySpmNoise= theSpmNoise;

    myBitSet[ INDEX_XpmNoise ] = true;
    myXpmNoise= theXpmNoise;

    myBitSet[ INDEX_ResourceLayer ] = true;
    myResourceLayer= theResourceLayer;

    myBitSet[ INDEX_PST ] = true;
    myPST= thePST;

    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ= thePSTQ;

    myBitSet[ INDEX_SST ] = true;
    mySST= theSST;
}

TL1_LinkRspBlk::TL1_LinkRspBlk( const TL1_LinkRspBlk& theRspBlk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet = theRspBlk.myBitSet;
    myAddr= theRspBlk.myAddr;
    myEntityName= theRspBlk.myEntityName;
    myTLname= theRspBlk.myTLname;
    myNearEndAddrType= theRspBlk.myNearEndAddrType;
    myNearEndAddr= theRspBlk.myNearEndAddr;
    myNearEndMask= theRspBlk.myNearEndMask;
    myNearEndParentTL= theRspBlk.myNearEndParentTL;
    myCost= theRspBlk.myCost;
    myNeighborDiscovery= theRspBlk.myNeighborDiscovery;
    myIfIndex= theRspBlk.myIfIndex;
    myNodeId= theRspBlk.myNodeId;
    myNeighborIfIndex= theRspBlk.myNeighborIfIndex;
    myNeighborNodeId= theRspBlk.myNeighborNodeId;
    myLinkPfAid= theRspBlk.myLinkPfAid;
    myNeighborSignalingAddr= theRspBlk.myNeighborSignalingAddr;
    myNeighborSignalingId= theRspBlk.myNeighborSignalingId;
    myRouting= theRspBlk.myRouting;
    mySignaling= theRspBlk.mySignaling;
    myRouterAreaId= theRspBlk.myRouterAreaId;
    mySrlg= theRspBlk.mySrlg;
    myLatency= theRspBlk.myLatency;
    myCarrierId= theRspBlk.myCarrierId;
    myResourceClass= theRspBlk.myResourceClass;
    myResource= theRspBlk.myResource;
    myIfName= theRspBlk.myIfName;
    myTLList= theRspBlk.myTLList;
    myLatencyMode= theRspBlk.myLatencyMode;
    myPmd= theRspBlk.myPmd;
    myOsnr= theRspBlk.myOsnr;
    myFwmp= theRspBlk.myFwmp;
    myPdl= theRspBlk.myPdl;
    myResidualCD= theRspBlk.myResidualCD;
    mySpmNoise= theRspBlk.mySpmNoise;
    myXpmNoise= theRspBlk.myXpmNoise;
    myResourceLayer=theRspBlk.myResourceLayer;
    myPST= theRspBlk.myPST;
    myPSTQ= theRspBlk.myPSTQ;
    mySST= theRspBlk.mySST;
}

TL1_LinkRspBlk::~TL1_LinkRspBlk( )
{
}

TL1_LinkRspBlk& 
TL1_LinkRspBlk::operator=( const TL1_LinkRspBlk& theRspBlk )
{
    myBitSet = theRspBlk.myBitSet;
    myAddr= theRspBlk.myAddr;
    myEntityName= theRspBlk.myEntityName;
    myTLname= theRspBlk.myTLname;
    myNearEndAddrType= theRspBlk.myNearEndAddrType;
    myNearEndAddr= theRspBlk.myNearEndAddr;
    myNearEndMask= theRspBlk.myNearEndMask;
    myNearEndParentTL= theRspBlk.myNearEndParentTL;
    myCost= theRspBlk.myCost;
    myNeighborDiscovery= theRspBlk.myNeighborDiscovery;
    myIfIndex= theRspBlk.myIfIndex;
    myNodeId= theRspBlk.myNodeId;
    myNeighborIfIndex= theRspBlk.myNeighborIfIndex;
    myNeighborNodeId= theRspBlk.myNeighborNodeId;
    myLinkPfAid= theRspBlk.myLinkPfAid;
    myNeighborSignalingAddr= theRspBlk.myNeighborSignalingAddr;
    myNeighborSignalingId= theRspBlk.myNeighborSignalingId;
    myRouting= theRspBlk.myRouting;
    mySignaling= theRspBlk.mySignaling;
    myRouterAreaId= theRspBlk.myRouterAreaId;
    mySrlg= theRspBlk.mySrlg;
    myLatency= theRspBlk.myLatency;
    myCarrierId= theRspBlk.myCarrierId;
    myResourceClass= theRspBlk.myResourceClass;
    myResource= theRspBlk.myResource;
    myIfName= theRspBlk.myIfName;
    myTLList= theRspBlk.myTLList;
    myLatencyMode= theRspBlk.myLatencyMode;
    myPmd= theRspBlk.myPmd;
    myOsnr= theRspBlk.myOsnr;
    myFwmp= theRspBlk.myFwmp;
    myPdl= theRspBlk.myPdl;
    myResidualCD= theRspBlk.myResidualCD;
    mySpmNoise= theRspBlk.mySpmNoise;
    myXpmNoise= theRspBlk.myXpmNoise;
    myResourceLayer=theRspBlk.myResourceLayer;
    myPST= theRspBlk.myPST;
    myPSTQ= theRspBlk.myPSTQ;
    mySST= theRspBlk.mySST;

    return *this;
}

bool 
TL1_LinkRspBlk::operator==( const TL1_LinkRspBlk& theRspBlk ) const
{
    if ( myBitSet != theRspBlk.myBitSet )                               return false;
    if ( myAddr != theRspBlk.myAddr )                                   return false;
    if ( myEntityName != theRspBlk.myEntityName )                       return false;
    if ( myTLname != theRspBlk.myTLname )                               return false;
    if ( myNearEndAddrType != theRspBlk.myNearEndAddrType )             return false;
    if ( myNearEndAddr != theRspBlk.myNearEndAddr )                     return false;
    if ( myNearEndMask != theRspBlk.myNearEndMask )                     return false;
    if ( myNearEndParentTL != theRspBlk.myNearEndParentTL )             return false;
    if ( myCost != theRspBlk.myCost )                                   return false;
    if ( myNeighborDiscovery != theRspBlk.myNeighborDiscovery )         return false;
    if ( myIfIndex != theRspBlk.myIfIndex )                             return false;
    if ( myNodeId != theRspBlk.myNodeId )                               return false;
    if ( myNeighborIfIndex != theRspBlk.myNeighborIfIndex )             return false;
    if ( myNeighborNodeId != theRspBlk.myNeighborNodeId )               return false;
    if ( myLinkPfAid != theRspBlk.myLinkPfAid )                         return false;
    if ( myNeighborSignalingAddr != theRspBlk.myNeighborSignalingAddr ) return false;
    if ( myNeighborSignalingId != theRspBlk.myNeighborSignalingId )     return false;
    if ( myRouting != theRspBlk.myRouting )                             return false;
    if ( mySignaling != theRspBlk.mySignaling )                         return false;
    if ( myRouterAreaId != theRspBlk.myRouterAreaId )                   return false;
    if ( mySrlg != theRspBlk.mySrlg )                                   return false;
    if ( myLatency != theRspBlk.myLatency )                             return false;
    if ( myCarrierId != theRspBlk.myCarrierId )                         return false;
    if ( myResourceClass != theRspBlk.myResourceClass )                 return false;
    if ( myResource != theRspBlk.myResource )                           return false;
    if ( myIfName != theRspBlk.myIfName )                               return false;
    if ( myTLList != theRspBlk.myTLList )                               return false;
    if ( myLatencyMode != theRspBlk.myLatencyMode )                     return false;
    if ( myPmd != theRspBlk.myPmd )                                     return false;
    if ( myOsnr != theRspBlk.myOsnr )                                   return false;
    if ( myFwmp != theRspBlk.myFwmp )                                   return false;
    if ( myPdl != theRspBlk.myPdl )                                     return false;
    if ( myResidualCD != theRspBlk.myResidualCD )                       return false;
    if ( mySpmNoise != theRspBlk.mySpmNoise )                           return false;
    if ( myXpmNoise != theRspBlk.myXpmNoise )                           return false;
    if ( myResourceLayer != theRspBlk.myResourceLayer )                 return false;
    if ( myPST != theRspBlk.myPST )                                     return false;
    if ( myPSTQ != theRspBlk.myPSTQ )                                   return false;
    if ( mySST != theRspBlk.mySST )                                     return false;

    return true;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetAddr( const CT_TL1_LinkAddr& theAddr )
{
    myBitSet[ INDEX_Addr ] = true;
    myAddr= theAddr;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetEntityName( const string& theEntityName )
{
    myBitSet[ INDEX_EntityName ] = true;
    myEntityName= theEntityName;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetTLname( const string& theTLname )
{
    myBitSet[ INDEX_TLname ] = true;
    myTLname= theTLname;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNearEndAddrType( const CT_TLNEADDRT& theNearEndAddrType )
{
    myBitSet[ INDEX_NearEndAddrType ] = true;
    myNearEndAddrType= theNearEndAddrType;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNearEndAddr( const CT_ControlPlane_TL& theNearEndAddr )
{
    myBitSet[ INDEX_NearEndAddr ] = true;
    myNearEndAddr= theNearEndAddr;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNearEndMask( const CT_ControlPlane_Addr& theNearEndMask )
{
    myBitSet[ INDEX_NearEndMask ] = true;
    myNearEndMask= theNearEndMask;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNearEndParentTL( const CT_TL1_LinkAddr& theNearEndParentTL )
{
    myBitSet[ INDEX_NearEndParentTL ] = true;
    myNearEndParentTL= theNearEndParentTL;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetCost( const int& theCost)
{
    myBitSet[ INDEX_Cost ] = true;
    myCost= (uint32)theCost;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNeighborDiscovery( const CT_TL_DISCOVERY_TYPE& theNeighborDiscovery )
{
    myBitSet[ INDEX_NeighborDiscovery ] = true;
    myNeighborDiscovery= theNeighborDiscovery;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetIfIndex( const uint32& theIfIndex )
{
    myBitSet[ INDEX_IfIndex ] = true;
    myIfIndex= theIfIndex;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNodeId( const uint32& theNodeId )
{
    myBitSet[ INDEX_NodeId ] = true;
    myNodeId= theNodeId;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex )
{
    myBitSet[ INDEX_NeighborIfIndex ] = true;
    myNeighborIfIndex= theNeighborIfIndex;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId )
{
    myBitSet[ INDEX_NeighborNodeId ] = true;
    myNeighborNodeId= theNeighborNodeId;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetLinkPfAid( const CT_TL1_LogicalAddr& theLinkPfAid )
{
    myBitSet[ INDEX_LinkPfAid ] = true;
    myLinkPfAid= theLinkPfAid;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNeighborSignalingAddr( const CT_ControlPlane_Addr& theNeighborSignalingAddr )
{
    myBitSet[ INDEX_NeighborSignalingAddr ] = true;
    myNeighborSignalingAddr= theNeighborSignalingAddr;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetNeighborSignalingId( const CT_ControlPlane_Addr& theNeighborSignalingId )
{
    myBitSet[ INDEX_NeighborSignalingId ] = true;
    myNeighborSignalingId= theNeighborSignalingId;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetRouting( const CT_TL_ROUTING& theRouting )
{
    myBitSet[ INDEX_Routing ] = true;
    myRouting= theRouting;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetSignaling( const CT_TL_SIGNALING& theSignaling )
{
    myBitSet[ INDEX_Signaling ] = true;
    mySignaling= theSignaling;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetRouterAreaId( const CT_ControlPlane_Addr& theRouterAreaId )
{
    myBitSet[ INDEX_RouterAreaId ] = true;
    myRouterAreaId= theRouterAreaId;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetSrlg( const CT_ControlPlane_Srlg& theSrlg )
{
    myBitSet[ INDEX_Srlg ] = true;
    mySrlg= theSrlg;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetLatency( const uint32& theLatency )
{
    myBitSet[ INDEX_Latency ] = true;
    myLatency= theLatency;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetLatencyMode( const CT_LatencyMode& theLatencyMode )
{
    myBitSet[ INDEX_LatencyMode ] = true;
    myLatencyMode= theLatencyMode;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetCarrierId( const string& theCarrierId )
{
    myBitSet[ INDEX_CarrierId ] = true;
    myCarrierId= theCarrierId;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetResourceClass( const CT_ControlPlane_Addr& theResourceClass )
{
    myBitSet[ INDEX_ResourceClass ] = true;
    myResourceClass= theResourceClass;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetResource( const CT_TL1_ResourceAddr& theResource )
{
    myBitSet[ INDEX_Resource ] = true;
    myResource= theResource;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetIfName( const CT_IfNumber& theIfName )
{
    myBitSet[ INDEX_IfName ] = true;
    myIfName= theIfName;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetTLList( const string& theTLList )
{
    myBitSet[ INDEX_TLList ] = true;
    myTLList= theTLList;
}


//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetPmd( const uint16& thePmd )
{
    myBitSet[ INDEX_Pmd ] = true;
    myPmd= thePmd;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetOsnr( const uint16& theOsnr )
{
    myBitSet[ INDEX_Osnr ] = true;
    myOsnr= theOsnr;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetFwmp( const int& theFwmp )
{
    myBitSet[ INDEX_Fwmp ] = true;
    myFwmp= theFwmp;

}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetPdl( const int& thePdl )
{
    myBitSet[ INDEX_Pdl ] = true;
    myPdl= thePdl;

}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetResidualCD( const int& theResidualCD )
{
    myBitSet[ INDEX_ResidualCD ] = true;
    myResidualCD= theResidualCD;

}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetSpmNoise( const int& theSpmNoise )
{
    myBitSet[ INDEX_SpmNoise ] = true;
    mySpmNoise= theSpmNoise;

}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetXpmNoise( const int& theXpmNoise )
{
    myBitSet[ INDEX_XpmNoise ] = true;
    myXpmNoise= theXpmNoise;

}

//---------------------------------------------------------------------------------
void 
TL1_LinkRspBlk::SetResourceLayer( const CT_RESOURCE_LAYER& theResourceLayer )
{
    myBitSet[ INDEX_ResourceLayer ] = true;
    myResourceLayer = theResourceLayer;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetPST( const CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST= thePST;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetPSTQ( const CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ= thePSTQ;
}

//--------------------------------------------------------------
void 
TL1_LinkRspBlk::SetSST( const CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST= theSST;
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetAddr( CT_TL1_LinkAddr& theAddr) const
{
    if( true == myBitSet[ INDEX_Addr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetEntityName( string& theEntityName) const
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

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetTLname( string& theTLname) const
{
    if( true == myBitSet[ INDEX_TLname ] )
    {
        theTLname = myTLname;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNearEndAddrType( CT_TLNEADDRT& theNearEndAddrType) const
{
    if( true == myBitSet[ INDEX_NearEndAddrType ] )
    {
        theNearEndAddrType = myNearEndAddrType;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNearEndAddr( CT_ControlPlane_TL& theNearEndAddr) const
{
    if( true == myBitSet[ INDEX_NearEndAddr ] )
    {
        theNearEndAddr = myNearEndAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNearEndMask(CT_ControlPlane_Addr& theNearEndMask) const
{
    if( true == myBitSet[ INDEX_NearEndMask ] )
    {
        theNearEndMask = myNearEndMask;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNearEndParentTL(CT_TL1_LinkAddr& theNearEndParentTL) const
{
    if( true == myBitSet[ INDEX_NearEndParentTL ] )
    {
        theNearEndParentTL = myNearEndParentTL;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetCost(uint32& theCost) const
{
    if( true == myBitSet[ INDEX_Cost ] )
    {
        theCost = myCost;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNeighborDiscovery(CT_TL_DISCOVERY_TYPE& theNeighborDiscovery) const
{
    if( true == myBitSet[ INDEX_NeighborDiscovery ] )
    {
        theNeighborDiscovery = myNeighborDiscovery;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetIfIndex( uint32& theIfIndex ) const
{
    if( true == myBitSet[ INDEX_IfIndex ] )
    {
        theIfIndex = myIfIndex;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNodeId( uint32& theNodeId ) const
{
    if( true == myBitSet[ INDEX_NodeId ] )
    {
        theNodeId = myNodeId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNeighborIfIndex(CT_ControlPlane_Addr& theNeighborIfIndex) const
{
    if( true == myBitSet[ INDEX_NeighborIfIndex ] )
    {
        theNeighborIfIndex = myNeighborIfIndex;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNeighborNodeId(CT_ControlPlane_Addr& theNeighborNodeId) const
{
    if( true == myBitSet[ INDEX_NeighborNodeId ] )
    {
        theNeighborNodeId = myNeighborNodeId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetLinkPfAid(CT_TL1_LogicalAddr& theLinkPfAid) const
{
    if( true == myBitSet[ INDEX_LinkPfAid ] )
    {
        theLinkPfAid = myLinkPfAid;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNeighborSignalingAddr(CT_ControlPlane_Addr& theNeighborSignalingAddr) const
{
    if( true == myBitSet[ INDEX_NeighborSignalingAddr ] )
    {
        theNeighborSignalingAddr = myNeighborSignalingAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetNeighborSignalingId(CT_ControlPlane_Addr& theNeighborSignalingId) const
{
    if( true == myBitSet[ INDEX_NeighborSignalingId ] )
    {
        theNeighborSignalingId = myNeighborSignalingId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetRouting(CT_TL_ROUTING& theRouting) const
{
    if( true == myBitSet[ INDEX_Routing ] )
    {
        theRouting = myRouting;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetSignaling(CT_TL_SIGNALING& theSignaling) const
{
    if( true == myBitSet[ INDEX_Signaling ] )
    {
        theSignaling = mySignaling;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetRouterAreaId(CT_ControlPlane_Addr& theRouterAreaId) const
{
    if( true == myBitSet[ INDEX_RouterAreaId ] )
    {
        theRouterAreaId = myRouterAreaId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetSrlg(CT_ControlPlane_Srlg& theSrlg) const
{
    if( true == myBitSet[ INDEX_Srlg ] )
    {
        theSrlg = mySrlg;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetLatency(uint32& theLatency) const
{
    if( true == myBitSet[ INDEX_Latency ] )
    {
        theLatency = myLatency;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetLatencyMode( CT_LatencyMode& theLatencyMode ) const
{
    if( true == myBitSet[ INDEX_LatencyMode ] )
    {
        theLatencyMode = myLatencyMode;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetCarrierId(string& theCarrierId) const
{
    if( true == myBitSet[ INDEX_CarrierId ] )
    {
        theCarrierId = myCarrierId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetResourceClass(CT_ControlPlane_Addr& theResourceClass) const
{
    if( true == myBitSet[ INDEX_ResourceClass ] )
    {
        theResourceClass = myResourceClass;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetResource(CT_TL1_ResourceAddr& theResource) const
{
    if( true == myBitSet[ INDEX_Resource ] )
    {
        theResource = myResource;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetIfName(CT_IfNumber& theIfName) const
{
    if( true == myBitSet[ INDEX_IfName ] )
    {
        theIfName = myIfName;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetTLList( string& theTLList) const
{
    if( true == myBitSet[ INDEX_TLList ] )
    {
        theTLList = myTLList;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetPmd( uint16& thePmd ) const
{
    if( true == myBitSet[ INDEX_Pmd ] )
    {
        thePmd = myPmd;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetOsnr( uint16& theOsnr ) const
{
    if( true == myBitSet[ INDEX_Osnr ] )
    {
        theOsnr = myOsnr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetFwmp( int& theFwmp ) const
{
    if( true == myBitSet[ INDEX_Fwmp ] )
    {
        theFwmp = myFwmp;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetPdl( int& thePdl ) const
{
    if( true == myBitSet[ INDEX_Pdl ] )
    {
        thePdl = myPdl;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetResidualCD( int& theResidualCD ) const
{
    if( true == myBitSet[ INDEX_ResidualCD ] )
    {
        theResidualCD = myResidualCD;
        return true;
    }
    else
    {
        return false;
    }
}


//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetSpmNoise( int& theSpmNoise ) const
{
    if( true == myBitSet[ INDEX_SpmNoise ] )
    {
        theSpmNoise = mySpmNoise;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetXpmNoise( int& theXpmNoise ) const
{
    if( true == myBitSet[ INDEX_XpmNoise ] )
    {
        theXpmNoise = myXpmNoise;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetResourceLayer( CT_RESOURCE_LAYER& theResourceLayer ) const
{
    if( true == myBitSet[ INDEX_ResourceLayer ] )
    {
        theResourceLayer = myResourceLayer;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetPST(CT_SM_PST& thePST) const
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

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetPSTQ(CT_SM_PSTQ& thePSTQ) const
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

//--------------------------------------------------------------
bool 
TL1_LinkRspBlk::GetSST(CT_SM_SST& theSST) const
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

//-----------------------------------------------------------------------
//
// TNA Link Map Response Block
//

TL1_TnaLnkMapRspBlk::TL1_TnaLnkMapRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_TnaLnkMapRspBlk::TL1_TnaLnkMapRspBlk( const uint32* theTnaValue,
                                          const CT_Call_Tna_Types* theTnaType,
                                          const CT_TL1_LinkAddr*  theLinkAddr)
    : myBitSet( INDEX_END, false )
{
    if( theTnaValue )
    {
        myBitSet[ INDEX_TnaValue ] = true;
        myTnaValue = *theTnaValue;
    }

    if( theTnaType )
    {
        myBitSet[ INDEX_TnaType] = true;
        myTnaType = *theTnaType;
    }

    if ( theLinkAddr )
    {
        myBitSet[ INDEX_LinkAddr ] = true;
        myLinkAddr = *theLinkAddr;
    }
}

TL1_TnaLnkMapRspBlk::TL1_TnaLnkMapRspBlk( const TL1_TnaLnkMapRspBlk& theRspBlk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet     = theRspBlk.myBitSet;
    myTnaValue   = theRspBlk.myTnaValue;
    myTnaType    = theRspBlk.myTnaType;
    myLinkAddr   = theRspBlk.myLinkAddr;

}

TL1_TnaLnkMapRspBlk::~TL1_TnaLnkMapRspBlk( )
{
}

//--------------------------------------------------------------
TL1_TnaLnkMapRspBlk& TL1_TnaLnkMapRspBlk::operator=( const TL1_TnaLnkMapRspBlk& theRspBlk )
{
    myBitSet     = theRspBlk.myBitSet;
    myTnaValue   = theRspBlk.myTnaValue;
    myTnaType    = theRspBlk.myTnaType;
    myLinkAddr   = theRspBlk.myLinkAddr;

    return *this;
}

//--------------------------------------------------------------
bool TL1_TnaLnkMapRspBlk::operator==( const TL1_TnaLnkMapRspBlk& theRspBlk ) const
{
    if ( myBitSet != theRspBlk.myBitSet )
        return false;

    if ( myTnaValue != theRspBlk.myTnaValue )
        return false;

    if ( myTnaType != theRspBlk.myTnaType )
        return false;

    if ( myLinkAddr != theRspBlk.myLinkAddr )
        return false;

    return true;
}

//--------------------------------------------------------------
bool TL1_TnaLnkMapRspBlk::GetTnaValue( uint32& theTnaValue ) const
{
    if( true == myBitSet[ INDEX_TnaValue ] )
    {
        theTnaValue = myTnaValue;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void TL1_TnaLnkMapRspBlk::SetTnaValue( uint32& theTnaValue )
{
   myBitSet[ INDEX_TnaValue ] = true;
   myTnaValue = theTnaValue;
}

//--------------------------------------------------------------
bool TL1_TnaLnkMapRspBlk::GetTnaType( CT_Call_Tna_Types& theTnaType ) const
{
    if( true == myBitSet[ INDEX_TnaType ] )
    {
        theTnaType = myTnaType;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void TL1_TnaLnkMapRspBlk::SetTnaType( CT_Call_Tna_Types& theTnaType )
{
   myBitSet[ INDEX_TnaType ] = true;
   myTnaType = theTnaType;
}

//--------------------------------------------------------------
bool TL1_TnaLnkMapRspBlk::GetLinkAddr( CT_TL1_LinkAddr& theLinkAddr ) const
{
    if( true == myBitSet[ INDEX_LinkAddr ] )
    {
        theLinkAddr = myLinkAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void TL1_TnaLnkMapRspBlk::SetLinkAddr( CT_TL1_LinkAddr& theLinkAddr )
{
   myBitSet[ INDEX_LinkAddr ] = true;
   myLinkAddr = theLinkAddr;
}


//--------------------------------------------------------------
TL1_LinkProfileRspBlk::TL1_LinkProfileRspBlk( ) :
    myBitSet( INDEX_END, false ),
    myAddr( 0 ),
    myEntityName( "" ),
    myProfileName( "" ),
    myNetworkAddressType( CT_LINKPF_NAT_UNKNOWN ),
    myHelloInterval( 0 ),
    myRouterDeadInterval( 0 ),
    myRetransmissionInternal( 0 ),
    myServiceLevelProfile( 99 ),
    myServiceLevelPolicy( 0 ),
    myGMPLSMode( CT_GMPLSMode_UNKNOWN ),
    myARUSupport( false ),
    myG709Mode( CT_G709Mode_UNKNOWN )
{
}

//--------------------------------------------------------------
TL1_LinkProfileRspBlk::TL1_LinkProfileRspBlk( CT_TL1_LogicalAddr  theAddr,
                                              string              theEntityName,
                                              string              theProfileName,
                                              CT_LINKPF_NAT_TYPE  theNetworkAddressType,
                                              uint16              theHelloInterval,
                                              uint16              theRouterDeadInterval,
                                              uint16              theRetransmissionInternal,
                                              CT_TL1_LogicalAddr  theServiceLevelProfile,
                                              CT_TL1_LogicalAddr  theServiceLevelPolicy,
                                              CT_GMPLS_MODE       theGMPLSMode,
                                              bool                theARUSupport,
                                              CT_G709_MODE        theG709Mode ) :
    myBitSet( INDEX_END, false )
{
    myBitSet[ INDEX_Addr ] = true;
    myAddr= theAddr;
    
    myBitSet[ INDEX_EntityName ] = true;
    myEntityName= theEntityName;

    myBitSet[ INDEX_ProfileName ] = true;
    myProfileName = theProfileName;

    myBitSet[ INDEX_NetworkAddressType ] = true;
    myNetworkAddressType = theNetworkAddressType;

    myBitSet[ INDEX_HelloInterval ] = true;
    myHelloInterval = theHelloInterval;

    myBitSet[ INDEX_RouterDeadInterval ] = true;
    myRouterDeadInterval = theRouterDeadInterval;

    myBitSet[ INDEX_RetransmissionInternal ] = true;
    myRetransmissionInternal = theRetransmissionInternal;

    myBitSet[ INDEX_ServiceLevelProfile ] = true;
    myServiceLevelProfile = theServiceLevelProfile;

    myBitSet[ INDEX_ServiceLevelPolicy ] = true;
    myServiceLevelPolicy = theServiceLevelPolicy;

    myBitSet[ INDEX_GMPLSMode ] = true;
    myGMPLSMode = theGMPLSMode;

    myBitSet[ INDEX_ARUSupport ] = true;
    myARUSupport = theARUSupport;

    myBitSet[ INDEX_G709Mode ] = true;
    myG709Mode = theG709Mode;
}

//---------------------------------------------------------------
TL1_LinkProfileRspBlk::TL1_LinkProfileRspBlk(const TL1_LinkProfileRspBlk& theRspBlk )
{
    *this = theRspBlk;
}

//---------------------------------------------------------------
TL1_LinkProfileRspBlk::~TL1_LinkProfileRspBlk()
{

}

//---------------------------------------------------------------
TL1_LinkProfileRspBlk& 
TL1_LinkProfileRspBlk::operator=( const TL1_LinkProfileRspBlk& theRspBlk )
{
    myBitSet                    = theRspBlk.myBitSet;
    myAddr                      = theRspBlk.myAddr;
    myEntityName                = theRspBlk.myEntityName;
    myProfileName               = theRspBlk.myProfileName;
    myNetworkAddressType        = theRspBlk.myNetworkAddressType;
    myHelloInterval             = theRspBlk.myHelloInterval;
    myRouterDeadInterval        = theRspBlk.myRouterDeadInterval;
    myRetransmissionInternal    = theRspBlk.myRetransmissionInternal;
    myServiceLevelProfile       = theRspBlk.myServiceLevelProfile;
    myServiceLevelPolicy        = theRspBlk.myServiceLevelPolicy;
    myGMPLSMode                 = theRspBlk.myGMPLSMode;
    myARUSupport                = theRspBlk.myARUSupport;
    myG709Mode                  = theRspBlk.myG709Mode;

    return *this;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::operator==( const TL1_LinkProfileRspBlk& theRspBlk ) const
{
    if ( myBitSet != theRspBlk.myBitSet )
        return false;

    if ( myAddr != theRspBlk.myAddr )
        return false;

    if ( myEntityName != theRspBlk.myEntityName )
        return false;

    if ( myProfileName != theRspBlk.myProfileName )
        return false;

    if ( myNetworkAddressType != theRspBlk.myNetworkAddressType )
        return false;

    if ( myHelloInterval != theRspBlk.myHelloInterval )
        return false;

    if ( myRouterDeadInterval != theRspBlk.myRouterDeadInterval )
        return false;

    if ( myRetransmissionInternal != theRspBlk.myRetransmissionInternal )
        return false;

    if ( myServiceLevelProfile != theRspBlk.myServiceLevelProfile )
        return false;

    if ( myServiceLevelPolicy != theRspBlk.myServiceLevelPolicy )
        return false;

    if ( myGMPLSMode != theRspBlk.myGMPLSMode )
        return false;

    if ( myARUSupport != theRspBlk.myARUSupport )
        return false;

    if ( myG709Mode != theRspBlk.myG709Mode )
        return false;

    return true;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetAddr( CT_TL1_LogicalAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_Addr ] )
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
TL1_LinkProfileRspBlk::SetAddr( const CT_TL1_LogicalAddr& theAddr )
{
   myBitSet[ INDEX_Addr ] = true;
   myAddr = theAddr;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetEntityName( string& theEntityName ) const
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
TL1_LinkProfileRspBlk::SetEntityName( const string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetProfileName( string& theProfileName ) const
{
    if( true == myBitSet[ INDEX_ProfileName ] )
    {
        theProfileName = myProfileName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetProfileName( const string& theProfileName )
{
   myBitSet[ INDEX_ProfileName ] = true;
   myProfileName = theProfileName;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetNetworkAddressType( CT_LINKPF_NAT_TYPE& theNetworkAddressType ) const
{
    if( true == myBitSet[ INDEX_NetworkAddressType ] )
    {
        theNetworkAddressType = myNetworkAddressType;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetNetworkAddressType( const CT_LINKPF_NAT_TYPE& theNetworkAddressType )
{
   myBitSet[ INDEX_NetworkAddressType ] = true;
   myNetworkAddressType = theNetworkAddressType;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetHelloInterval( uint16& theHelloInterval ) const
{
    if( true == myBitSet[ INDEX_HelloInterval ] )
    {
        theHelloInterval = myHelloInterval;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetHelloInterval( const uint16& theHelloInterval )
{
   myBitSet[ INDEX_HelloInterval ] = true;
   myHelloInterval = theHelloInterval;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetRouterDeadInterval( uint16& theRouterDeadInterval ) const
{
    if( true == myBitSet[ INDEX_RouterDeadInterval ] )
    {
        theRouterDeadInterval = myRouterDeadInterval;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetRouterDeadInterval( const uint16& theRouterDeadInterval )
{
   myBitSet[ INDEX_RouterDeadInterval ] = true;
   myRouterDeadInterval = theRouterDeadInterval;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetRetransmissionInternal( uint16& theRetransmissionInternal ) const
{
    if( true == myBitSet[ INDEX_RetransmissionInternal ] )
    {
        theRetransmissionInternal = myRetransmissionInternal;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetRetransmissionInternal( const uint16& theRetransmissionInternal )
{
   myBitSet[ INDEX_RetransmissionInternal ] = true;
   myRetransmissionInternal = theRetransmissionInternal;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetServiceLevelProfile( CT_TL1_LogicalAddr& theServiceLevelProfile ) const
{
    if( true == myBitSet[ INDEX_ServiceLevelProfile ] )
    {
        theServiceLevelProfile = myServiceLevelProfile;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetServiceLevelProfile( const CT_TL1_LogicalAddr& theServiceLevelProfile )
{
   myBitSet[ INDEX_ServiceLevelProfile ] = true;
   myServiceLevelProfile = theServiceLevelProfile;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetServiceLevelPolicy( CT_TL1_LogicalAddr& theServiceLevelPolicy ) const
{
    if( true == myBitSet[ INDEX_ServiceLevelPolicy ] )
    {
        theServiceLevelPolicy = myServiceLevelPolicy;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetServiceLevelPolicy( const CT_TL1_LogicalAddr& theServiceLevelPolicy )
{
   myBitSet[ INDEX_ServiceLevelPolicy ] = true;
   myServiceLevelPolicy = theServiceLevelPolicy;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetGMPLSMode( CT_GMPLS_MODE& theGMPLSMode ) const
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

void 
TL1_LinkProfileRspBlk::SetGMPLSMode( const CT_GMPLS_MODE& theGMPLSMode )
{
   myBitSet[ INDEX_GMPLSMode ] = true;
   myGMPLSMode = theGMPLSMode;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetARUSupport( bool& theARUSupport ) const
{
    if( true == myBitSet[ INDEX_ARUSupport ] )
    {
        theARUSupport = myARUSupport;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetARUSupport( const bool theARUSupport )
{
   myBitSet[ INDEX_ARUSupport ] = true;
   myARUSupport = theARUSupport;
}

//---------------------------------------------------------------
bool 
TL1_LinkProfileRspBlk::GetG709Mode( CT_G709_MODE& theG709Mode ) const
{
    if( true == myBitSet[ INDEX_G709Mode ] )
    {
        theG709Mode = myG709Mode;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LinkProfileRspBlk::SetG709Mode( const CT_G709_MODE& theG709Mode )
{
   myBitSet[ INDEX_G709Mode ] = true;
   myG709Mode = theG709Mode;
}

//--------------------------------------------------------------
TL1_TrLinkRspBlk::TL1_TrLinkRspBlk( ) :
    myBitSet( INDEX_END, false )
{

}

TL1_TrLinkRspBlk::TL1_TrLinkRspBlk( CT_TL1_LinkAddr       theAddr,
                                    string                theEntityName,
                                    string                theTrlName,
                                    uint32                theCost,
                                    uint32                theIfIndex,
                                    uint32                theNodeId,
                                    CT_ControlPlane_Addr  theNeighborIfIndex,
                                    CT_ControlPlane_Addr  theNeighborNodeId,
                                    CT_TL1_LogicalAddr    theLinkPfAid,
                                    CT_ControlPlane_Addr  theNeighborSignalingAddr,
                                    CT_ControlPlane_Addr  theNeighborSignalingId,
                                    CT_ControlPlane_Addr  theRouterAreaId,
                                    CT_ControlPlane_Addr  theResourceClass,
                                    CT_TL1_ModuleAddr     theModuleAddr,
                                    CT_TL1_Port           thePortNum,
                                    CT_FacilitySubType    theFacSubType,
                                    CT_Adaptation         theAdapt,
                                    uint16                thePmd,
                                    uint16                theOsnr,
                                    int                   thePdl,
                                    CT_TL1_LinkAddr       theParentTL,
                                    CT_SM_PST             thePST,
                                    CT_SM_PSTQ            thePSTQ,
                                    CT_SM_SST             theSST )
{
    myBitSet[ INDEX_Addr ] = true;
    myAddr= theAddr;

    myBitSet[ INDEX_EntityName ] = true;
    myEntityName= theEntityName;

    myBitSet[ INDEX_TrlName ] = true;
    myTrlName= theTrlName;

    myBitSet[ INDEX_Cost ] = true;
    myCost= theCost;

    myBitSet[ INDEX_IfIndex ] = true;
    myIfIndex= theIfIndex;

    myBitSet[ INDEX_NodeId ] = true;
    myNodeId= theNodeId;

    myBitSet[ INDEX_NeighborIfIndex ] = true;
    myNeighborIfIndex= theNeighborIfIndex;

    myBitSet[ INDEX_NeighborNodeId ] = true;
    myNeighborNodeId= theNeighborNodeId;

    myBitSet[ INDEX_LinkPfAid ] = true;
    myLinkPfAid= theLinkPfAid;

    myBitSet[ INDEX_NeighborSignalingAddr ] = true;
    myNeighborSignalingAddr= theNeighborSignalingAddr;

    myBitSet[ INDEX_NeighborSignalingId ] = true;
    myNeighborSignalingId= theNeighborSignalingId;

    myBitSet[ INDEX_RouterAreaId ] = true;
    myRouterAreaId= theRouterAreaId;

    myBitSet[ INDEX_ResourceClass ] = true;
    myResourceClass= theResourceClass;

    myBitSet[ INDEX_ModuleAddr ] = true;
    myModuleAddr= theModuleAddr;

    myBitSet[ INDEX_PortNum ] = true;
    myPortNum= thePortNum;

    myBitSet[ INDEX_FacSubType ] = true;
    myFacSubType= theFacSubType;

    myBitSet[ INDEX_Adaptation ] = true;
    myAdapt= theAdapt;

    myBitSet[ INDEX_Pmd ] = true;
    myPmd= thePmd;

    myBitSet[ INDEX_Osnr ] = true;
    myOsnr= theOsnr;

    myBitSet[ INDEX_Pdl ] = true;
    myPdl= thePdl;

    myBitSet[ INDEX_ParentTL ] = true;
    myParentTL= theParentTL;

    myBitSet[ INDEX_PST ] = true;
    myPST= thePST;

    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ= thePSTQ;

    myBitSet[ INDEX_SST ] = true;
    mySST= theSST;
}

TL1_TrLinkRspBlk::TL1_TrLinkRspBlk(const TL1_TrLinkRspBlk& theRspBlk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=                   theRspBlk.myBitSet;
    myAddr=                     theRspBlk.myAddr;
    myEntityName=               theRspBlk.myEntityName;
    myTrlName=                  theRspBlk.myTrlName;
    myCost=                     theRspBlk.myCost;
    myIfIndex=                  theRspBlk.myIfIndex;
    myNodeId=                   theRspBlk.myNodeId;
    myNeighborIfIndex=          theRspBlk.myNeighborIfIndex;
    myNeighborNodeId=           theRspBlk.myNeighborNodeId;
    myLinkPfAid=                theRspBlk.myLinkPfAid;
    myNeighborSignalingAddr=    theRspBlk.myNeighborSignalingAddr;
    myNeighborSignalingId=      theRspBlk.myNeighborSignalingId;
    myRouterAreaId=             theRspBlk.myRouterAreaId;
    myResourceClass=            theRspBlk.myResourceClass;
    myModuleAddr=               theRspBlk.myModuleAddr;
    myPortNum=                  theRspBlk.myPortNum;
    myFacSubType=               theRspBlk.myFacSubType;
    myAdapt=                    theRspBlk.myAdapt;
    myPmd=                      theRspBlk.myPmd;
    myOsnr=                     theRspBlk.myOsnr;
    myPdl=                      theRspBlk.myPdl;
    myParentTL=                 theRspBlk.myParentTL;
    myPST=                      theRspBlk.myPST;
    myPSTQ=                     theRspBlk.myPSTQ;
    mySST=                      theRspBlk.mySST;
}

TL1_TrLinkRspBlk::~TL1_TrLinkRspBlk()
{

}

TL1_TrLinkRspBlk& 
TL1_TrLinkRspBlk::operator=( const TL1_TrLinkRspBlk& theRspBlk )
{
    myBitSet=                   theRspBlk.myBitSet;
    myAddr=                     theRspBlk.myAddr;
    myEntityName=               theRspBlk.myEntityName;
    myTrlName=                  theRspBlk.myTrlName;
    myCost=                     theRspBlk.myCost;
    myIfIndex=                  theRspBlk.myIfIndex;
    myNodeId=                   theRspBlk.myNodeId;
    myNeighborIfIndex=          theRspBlk.myNeighborIfIndex;
    myNeighborNodeId=           theRspBlk.myNeighborNodeId;
    myLinkPfAid=                theRspBlk.myLinkPfAid;
    myNeighborSignalingAddr=    theRspBlk.myNeighborSignalingAddr;
    myNeighborSignalingId=      theRspBlk.myNeighborSignalingId;
    myRouterAreaId=             theRspBlk.myRouterAreaId;
    myResourceClass=            theRspBlk.myResourceClass;
    myModuleAddr=               theRspBlk.myModuleAddr;
    myPortNum=                  theRspBlk.myPortNum;
    myFacSubType=               theRspBlk.myFacSubType;
    myAdapt=                    theRspBlk.myAdapt;
    myPmd=                      theRspBlk.myPmd;
    myOsnr=                     theRspBlk.myOsnr;
    myPdl=                      theRspBlk.myPdl;
    myParentTL=                 theRspBlk.myParentTL;
    myPST=                      theRspBlk.myPST;
    myPSTQ=                     theRspBlk.myPSTQ;
    mySST=                      theRspBlk.mySST;

    return *this;
}


bool 
TL1_TrLinkRspBlk::operator==( const TL1_TrLinkRspBlk& theRspBlk ) const
{
    if ( myBitSet != theRspBlk.myBitSet )
        return false;

    if ( myAddr != theRspBlk.myAddr )
        return false;

    if ( myEntityName != theRspBlk.myEntityName )
        return false;

    if ( myTrlName != theRspBlk.myTrlName )
        return false;

    if ( myCost != theRspBlk.myCost )
        return false;

    if ( myIfIndex != theRspBlk.myIfIndex )
        return false;

    if ( myNodeId != theRspBlk.myNodeId )
        return false;

    if ( myNeighborIfIndex != theRspBlk.myNeighborIfIndex )
        return false;

    if ( myNeighborNodeId != theRspBlk.myNeighborNodeId )
        return false;

    if ( myLinkPfAid != theRspBlk.myLinkPfAid )
        return false;

    if ( myNeighborSignalingAddr != theRspBlk.myNeighborSignalingAddr )
        return false;

    if ( myNeighborSignalingId != theRspBlk.myNeighborSignalingId )
        return false;

    if ( myRouterAreaId != theRspBlk.myRouterAreaId )
        return false;

    if ( myResourceClass != theRspBlk.myResourceClass )
        return false;

    if ( myModuleAddr != theRspBlk.myModuleAddr )
        return false;

    if ( myPortNum != theRspBlk.myPortNum )
        return false;

    if ( myFacSubType != theRspBlk.myFacSubType )
        return false;

    if ( myAdapt != theRspBlk.myAdapt )
        return false;

    if ( myPmd != theRspBlk.myPmd )
        return false;

    if ( myOsnr != theRspBlk.myOsnr )
        return false;

    if ( myPdl != theRspBlk.myPdl )
        return false;

    if ( myParentTL != theRspBlk.myParentTL )
        return false;

    if ( myPST != theRspBlk.myPST )
        return false;

    if ( myPSTQ != theRspBlk.myPSTQ )
        return false;

    if ( mySST != theRspBlk.mySST )
        return false;

    return true;
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetAddr( const CT_TL1_LinkAddr& theAddr )
{
    myBitSet[ INDEX_Addr ] = true;
    myAddr= theAddr;
}

bool 
TL1_TrLinkRspBlk::GetAddr( CT_TL1_LinkAddr& theAddr) const
{
    if( true == myBitSet[ INDEX_Addr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetEntityName( const string& theEntityName )
{
    myBitSet[ INDEX_EntityName ] = true;
    myEntityName= theEntityName;
}

bool 
TL1_TrLinkRspBlk::GetEntityName( string& theEntityName) const
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

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetTrlName( const string& theTrlName )
{
    myBitSet[ INDEX_TrlName ] = true;
    myTrlName= theTrlName;
}

bool 
TL1_TrLinkRspBlk::GetTrlName( string& theTrlName) const
{
    if( true == myBitSet[ INDEX_TrlName ] )
    {
        theTrlName = myTrlName;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetCost( const int& theCost)
{
    myBitSet[ INDEX_Cost ] = true;
    myCost= (uint32)theCost;
}

bool 
TL1_TrLinkRspBlk::GetCost(uint32& theCost) const
{
    if( true == myBitSet[ INDEX_Cost ] )
    {
        theCost = myCost;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetIfIndex( const uint32& theIfIndex )
{
    myBitSet[ INDEX_IfIndex ] = true;
    myIfIndex= theIfIndex;
}

bool 
TL1_TrLinkRspBlk::GetIfIndex( uint32& theIfIndex ) const
{
    if( true == myBitSet[ INDEX_IfIndex ] )
    {
        theIfIndex = myIfIndex;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetNodeId( const uint32& theNodeId )
{
    myBitSet[ INDEX_NodeId ] = true;
    myNodeId= theNodeId;
}

bool 
TL1_TrLinkRspBlk::GetNodeId( uint32& theNodeId ) const
{
    if( true == myBitSet[ INDEX_NodeId ] )
    {
        theNodeId = myNodeId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex )
{
    myBitSet[ INDEX_NeighborIfIndex ] = true;
    myNeighborIfIndex= theNeighborIfIndex;
}

bool 
TL1_TrLinkRspBlk::GetNeighborIfIndex(CT_ControlPlane_Addr& theNeighborIfIndex) const
{
    if( true == myBitSet[ INDEX_NeighborIfIndex ] )
    {
        theNeighborIfIndex = myNeighborIfIndex;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId )
{
    myBitSet[ INDEX_NeighborNodeId ] = true;
    myNeighborNodeId= theNeighborNodeId;
}

bool 
TL1_TrLinkRspBlk::GetNeighborNodeId(CT_ControlPlane_Addr& theNeighborNodeId) const
{
    if( true == myBitSet[ INDEX_NeighborNodeId ] )
    {
        theNeighborNodeId = myNeighborNodeId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetLinkPfAid( const CT_TL1_LogicalAddr& theLinkPfAid )
{
    myBitSet[ INDEX_LinkPfAid ] = true;
    myLinkPfAid= theLinkPfAid;
}

bool 
TL1_TrLinkRspBlk::GetLinkPfAid(CT_TL1_LogicalAddr& theLinkPfAid) const
{
    if( true == myBitSet[ INDEX_LinkPfAid ] )
    {
        theLinkPfAid = myLinkPfAid;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetNeighborSignalingAddr( const CT_ControlPlane_Addr& theNeighborSignalingAddr )
{
    myBitSet[ INDEX_NeighborSignalingAddr ] = true;
    myNeighborSignalingAddr= theNeighborSignalingAddr;
}

bool 
TL1_TrLinkRspBlk::GetNeighborSignalingAddr(CT_ControlPlane_Addr& theNeighborSignalingAddr) const
{
    if( true == myBitSet[ INDEX_NeighborSignalingAddr ] )
    {
        theNeighborSignalingAddr = myNeighborSignalingAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetNeighborSignalingId( const CT_ControlPlane_Addr& theNeighborSignalingId )
{
    myBitSet[ INDEX_NeighborSignalingId ] = true;
    myNeighborSignalingId= theNeighborSignalingId;
}

bool 
TL1_TrLinkRspBlk::GetNeighborSignalingId(CT_ControlPlane_Addr& theNeighborSignalingId) const
{
    if( true == myBitSet[ INDEX_NeighborSignalingId ] )
    {
        theNeighborSignalingId = myNeighborSignalingId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetRouterAreaId( const CT_ControlPlane_Addr& theRouterAreaId )
{
    myBitSet[ INDEX_RouterAreaId ] = true;
    myRouterAreaId= theRouterAreaId;
}

bool 
TL1_TrLinkRspBlk::GetRouterAreaId(CT_ControlPlane_Addr& theRouterAreaId) const
{
    if( true == myBitSet[ INDEX_RouterAreaId ] )
    {
        theRouterAreaId = myRouterAreaId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetResourceClass( const CT_ControlPlane_Addr& theResourceClass )
{
    myBitSet[ INDEX_ResourceClass ] = true;
    myResourceClass= theResourceClass;
}

bool 
TL1_TrLinkRspBlk::GetResourceClass(CT_ControlPlane_Addr& theResourceClass) const
{
    if( true == myBitSet[ INDEX_ResourceClass ] )
    {
        theResourceClass = myResourceClass;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetModuleAddr( const CT_TL1_ModuleAddr& theModuleAddr ) 
{
    myBitSet[ INDEX_ModuleAddr ] = true;
    myModuleAddr= theModuleAddr;

}

bool 
TL1_TrLinkRspBlk::GetModuleAddr( CT_TL1_ModuleAddr& theModuleAddr ) const
{
    if( true == myBitSet[ INDEX_ModuleAddr ] )
    {
        theModuleAddr = myModuleAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetPortNum( const CT_TL1_Port& thePortNum )
{
    myBitSet[ INDEX_PortNum ] = true;
    myPortNum = thePortNum;
}

bool 
TL1_TrLinkRspBlk::GetPortNum( CT_TL1_Port& thePortNum ) const
{
    if( true == myBitSet[ INDEX_PortNum ] )
    {
        thePortNum = myPortNum;
        return true;
    }
    else
    {
        return false;
    }
}
//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetFacSubType( const CT_FacilitySubType& theFacSubType )
{
    myBitSet[ INDEX_FacSubType ] = true;
    myFacSubType= theFacSubType;
}

bool 
TL1_TrLinkRspBlk::GetFacSubType( CT_FacilitySubType& theFacSubType ) const
{
    if( true == myBitSet[ INDEX_FacSubType ] )
    {
        theFacSubType = myFacSubType;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetAdaptation( const CT_Adaptation& theAdapt ) 
{
    myBitSet[ INDEX_Adaptation ] = true;
    myAdapt= theAdapt;
}

bool 
TL1_TrLinkRspBlk::GetAdaptation( CT_Adaptation& theAdapt ) const
{
    if( true == myBitSet[ INDEX_Adaptation ] )
    {
        theAdapt = myAdapt;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetPmd( const uint16& thePmd )
{
    myBitSet[ INDEX_Pmd ] = true;
    myPmd= thePmd;
}

bool 
TL1_TrLinkRspBlk::GetPmd( uint16& thePmd ) const
{
    if( true == myBitSet[ INDEX_Pmd ] )
    {
        thePmd = myPmd;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetOsnr( const uint16& theOsnr )
{
    myBitSet[ INDEX_Osnr ] = true;
    myOsnr= theOsnr;
}

bool 
TL1_TrLinkRspBlk::GetOsnr( uint16& theOsnr ) const
{
    if( true == myBitSet[ INDEX_Osnr ] )
    {
        theOsnr = myOsnr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetPdl( const int& thePdl )
{
    myBitSet[ INDEX_Pdl ] = true;
    myPdl= thePdl;
}

bool 
TL1_TrLinkRspBlk::GetPdl( int& thePdl ) const
{
    if( true == myBitSet[ INDEX_Pdl ] )
    {
        thePdl = myPdl;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetParentTL( const CT_TL1_LinkAddr& theParentTL )
{
    myBitSet[ INDEX_ParentTL ] = true;
    myParentTL= theParentTL;
}

bool 
TL1_TrLinkRspBlk::GetParentTL( CT_TL1_LinkAddr& theParentTL ) const
{
    if( true == myBitSet[ INDEX_ParentTL ] )
    {
        theParentTL = myParentTL;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetPST( const CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST= thePST;
}

bool 
TL1_TrLinkRspBlk::GetPST(CT_SM_PST& thePST) const
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

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetPSTQ( const CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ= thePSTQ;
}

bool 
TL1_TrLinkRspBlk::GetPSTQ(CT_SM_PSTQ& thePSTQ) const
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

//--------------------------------------------------------------
void 
TL1_TrLinkRspBlk::SetSST( const CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST= theSST;
}

bool 
TL1_TrLinkRspBlk::GetSST(CT_SM_SST& theSST) const
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

//---------------------------------------------------------------

TL1_LadjLinkRspBlk::TL1_LadjLinkRspBlk( ) :
    myLadState(CT_LAD_State_Unknown),
    myBitSet(INDEX_END, false)
{
}

TL1_LadjLinkRspBlk::TL1_LadjLinkRspBlk( CT_TL1_LinkAddr     theAddr,
                                        CT_LadState         theLadState,
                                        string              theTransmitTTI,
                                        string              theReceiveTTI)
{
    myBitSet[INDEX_Addr] = true;
    myAddr = theAddr;

    myBitSet[INDEX_LadState] = true;
    myLadState = theLadState;

    myBitSet[INDEX_TransmitTTI] = true;
    myTransmitTTI = theTransmitTTI;

    myBitSet[INDEX_ReceiveTTI] = true;
    myReceiveTTI = theReceiveTTI;

}

TL1_LadjLinkRspBlk::TL1_LadjLinkRspBlk(const TL1_LadjLinkRspBlk& theRspBlk) :
    myBitSet(INDEX_END, false)
{
    myBitSet =      theRspBlk.myBitSet;
    myAddr =        theRspBlk.myAddr;
    myLadState =    theRspBlk.myLadState;
    myTransmitTTI = theRspBlk.myTransmitTTI;
    myReceiveTTI =  theRspBlk.myReceiveTTI;
}

TL1_LadjLinkRspBlk::~TL1_LadjLinkRspBlk()
{
}

TL1_LadjLinkRspBlk& 
TL1_LadjLinkRspBlk::operator=( const TL1_LadjLinkRspBlk& theRspBlk )
{
    myBitSet =      theRspBlk.myBitSet;
    myAddr =        theRspBlk.myAddr;
    myLadState =    theRspBlk.myLadState;
    myTransmitTTI = theRspBlk.myTransmitTTI;
    myReceiveTTI =  theRspBlk.myReceiveTTI;

    return *this;
}

bool 
TL1_LadjLinkRspBlk::operator==( const TL1_LadjLinkRspBlk& theRspBlk ) const
{
    if( myBitSet != theRspBlk.myBitSet )
        return false;

    if( myAddr != theRspBlk.myAddr )
        return false;

    if( myLadState != theRspBlk.myLadState )
        return false;

    if( myTransmitTTI != theRspBlk.myTransmitTTI )
        return false;

    if( myReceiveTTI != theRspBlk.myReceiveTTI )
        return false;

    return true;
}

//--------------------------------------------------------------------
bool 
TL1_LadjLinkRspBlk::GetAddr( CT_TL1_LinkAddr& theAddr ) const
{
    if( myBitSet[INDEX_Addr] == true )
    {
        theAddr = myAddr;
        return true;
    }
    return false;
}

void 
TL1_LadjLinkRspBlk::SetAddr( const CT_TL1_LinkAddr& theAddr)
{
    myBitSet[INDEX_Addr] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------------
bool 
TL1_LadjLinkRspBlk::GetLadState( CT_LadState& theLadState ) const
{
    if( myBitSet[INDEX_LadState] == true )
    {
        theLadState = myLadState;
        return true;
    }
    return false;
}

void 
TL1_LadjLinkRspBlk::SetLadState( const CT_LadState& theLadState )
{
    myBitSet[INDEX_LadState] = true;
    myLadState = theLadState;
}

//--------------------------------------------------------------------
bool 
TL1_LadjLinkRspBlk::GetTransmitTTI( string& theTransmitTTI ) const
{
    if( myBitSet[INDEX_TransmitTTI] == true )
    {
        theTransmitTTI = myTransmitTTI;
        return true;
    }
    return false;
}

void 
TL1_LadjLinkRspBlk::SetTransmitTTI( const string& theTransmitTTI)
{
    myBitSet[INDEX_TransmitTTI] = true;
    myTransmitTTI = theTransmitTTI;
}

//--------------------------------------------------------------------
bool 
TL1_LadjLinkRspBlk::GetReceiveTTI( string& theReceiveTTI ) const
{
    if( myBitSet[INDEX_ReceiveTTI] == true )
    {
        theReceiveTTI = myReceiveTTI;
        return true;
    }
    return false;
}

void 
TL1_LadjLinkRspBlk::SetReceiveTTI( const string& theReceiveTTI )
{
    myBitSet[INDEX_ReceiveTTI] = true;
    myReceiveTTI = theReceiveTTI;
}

//---------------------------------------------------------------------

TL1_TceLinkRspBlk::TL1_TceLinkRspBlk( ) :
    myCpConfigState(CT_LCP_State_Unknown),
    myCpNameState(CT_LCP_State_Unknown),
    myMpState(CT_LCP_State_Unknown),
    myLcpState(CT_LCP_State_Unknown),
    myRoutingProtocol(CT_GMPLSMode_UNKNOWN),
    mySigProtocol(CT_GMPLSMode_UNKNOWN),
    myBitSet(INDEX_END, false)
{
}

TL1_TceLinkRspBlk::TL1_TceLinkRspBlk( CT_TL1_LinkAddr       theAddr,
                                       CT_LcpState           theLcpState,
                                       CT_LcpState           theMpState,
                                       string                theMgtDomain,
                                       string                theMgtNodeName,
                                       string                theMgtPortName,
                                       CT_LcpState           theCpNameState,
                                       CT_ControlPlane_Addr  theRoutingAreaId,
                                       CT_LcpState           theCpConfigState,
                                       CT_ControlPlane_Addr  theNeighborNodeId,
                                       CT_ControlPlane_Addr  theNeighborIfIndex,
                                       CT_GMPLS_MODE         theSigProtocol,
                                       CT_GMPLS_MODE         theRoutingProtocol,
                                       CT_ControlPlane_Addr  theNeighborSigAddr,
                                       CT_ControlPlane_Addr  theNeighborSigId)
{
    myBitSet[INDEX_Addr] = true;
    myAddr = theAddr;

    myBitSet[INDEX_LcpState] = true;
    myLcpState = theLcpState;

    myBitSet[INDEX_MpState] = true;
    myMpState = theMpState;

    myBitSet[INDEX_MgtDomain] = true;
    myMgtDomain = theMgtDomain;

    myBitSet[INDEX_MgtNodeName] = true;
    myMgtNodeName = theMgtNodeName;

    myBitSet[INDEX_MgtPortName] = true;
    myMgtPortName = theMgtPortName;

    myBitSet[INDEX_CpNameState] = true;
    myCpNameState = theCpNameState;

    myBitSet[INDEX_RoutingAreaId] = true;
    myRoutingAreaId = theRoutingAreaId;

    myBitSet[INDEX_CpConfigState] = true;
    myCpConfigState = theCpConfigState;

    myBitSet[INDEX_NeighborNodeId] = true;
    myNeighborNodeId = theNeighborNodeId;

    myBitSet[INDEX_NeighborIfIndex] = true;
    myNeighborIfIndex = theNeighborIfIndex;

    myBitSet[INDEX_SigProtocol] = true;
    mySigProtocol = theSigProtocol;

    myBitSet[INDEX_RoutingProtocol] = true;
    myRoutingProtocol = theRoutingProtocol;

    myBitSet[INDEX_NeighborSigAddr] = true;
    myNeighborSigAddr = theNeighborSigAddr;

    myBitSet[INDEX_NeighborSigId] = true;
    myNeighborSigId = theNeighborSigId;
}

TL1_TceLinkRspBlk::TL1_TceLinkRspBlk(const TL1_TceLinkRspBlk& theRspBlk) :
    myBitSet(INDEX_END, false)
{
    myBitSet =          theRspBlk.myBitSet;
    myAddr =            theRspBlk.myAddr;
    myLcpState =        theRspBlk.myLcpState;
    myMpState =        theRspBlk.myMpState;
    myMgtDomain =       theRspBlk.myMgtDomain;
    myMgtNodeName =     theRspBlk.myMgtNodeName;
    myMgtPortName =     theRspBlk.myMgtPortName;
    myCpNameState =     theRspBlk.myCpNameState;
    myRoutingAreaId =   theRspBlk.myRoutingAreaId;
    myCpConfigState =   theRspBlk.myCpConfigState;
    myNeighborNodeId =  theRspBlk.myNeighborNodeId;
    myNeighborIfIndex = theRspBlk.myNeighborIfIndex;
    mySigProtocol =     theRspBlk.mySigProtocol;
    myRoutingProtocol = theRspBlk.myRoutingProtocol;
    myNeighborSigAddr = theRspBlk.myNeighborSigAddr;
    myNeighborSigId =   theRspBlk.myNeighborSigId;
}

TL1_TceLinkRspBlk::~TL1_TceLinkRspBlk()
{
}

TL1_TceLinkRspBlk& 
TL1_TceLinkRspBlk::operator=( const TL1_TceLinkRspBlk& theRspBlk )
{
    myBitSet =          theRspBlk.myBitSet;
    myAddr =            theRspBlk.myAddr;
    myLcpState =        theRspBlk.myLcpState;
    myMpState =         theRspBlk.myMpState;
    myMgtDomain =       theRspBlk.myMgtDomain;
    myMgtNodeName =     theRspBlk.myMgtNodeName;
    myMgtPortName =     theRspBlk.myMgtPortName;
    myCpNameState =     theRspBlk.myCpNameState;
    myRoutingAreaId =   theRspBlk.myRoutingAreaId;
    myCpConfigState =   theRspBlk.myCpConfigState;
    myNeighborNodeId =  theRspBlk.myNeighborNodeId;
    myNeighborIfIndex = theRspBlk.myNeighborIfIndex;
    mySigProtocol =     theRspBlk.mySigProtocol;
    myRoutingProtocol = theRspBlk.myRoutingProtocol;
    myNeighborSigAddr = theRspBlk.myNeighborSigAddr;
    myNeighborSigId =   theRspBlk.myNeighborSigId;

    return *this;
}

bool 
TL1_TceLinkRspBlk::operator==( const TL1_TceLinkRspBlk& theRspBlk ) const
{
    if( myBitSet != theRspBlk.myBitSet )
        return false;

    if( myAddr != theRspBlk.myAddr )
        return false;

    if( myLcpState != theRspBlk.myLcpState )
        return false;

    if( myMpState != theRspBlk.myMpState )
        return false;

    if( myMgtDomain != theRspBlk.myMgtDomain )
        return false;

    if( myMgtNodeName != theRspBlk.myMgtNodeName )
        return false;

    if( myMgtPortName != theRspBlk.myMgtPortName )
        return false;

    if( myCpNameState != theRspBlk.myCpNameState )
        return false;

    if( myRoutingAreaId != theRspBlk.myRoutingAreaId )
        return false;

    if( myCpConfigState != theRspBlk.myCpConfigState )
        return false;

    if( myNeighborNodeId != theRspBlk.myNeighborNodeId )
        return false;

    if( myNeighborIfIndex != theRspBlk.myNeighborIfIndex )
        return false;

    if( mySigProtocol != theRspBlk.mySigProtocol )
        return false;

    if( myRoutingProtocol != theRspBlk.myRoutingProtocol )
        return false;

    if( myNeighborSigAddr != theRspBlk.myNeighborSigAddr )
        return false;

    if( myNeighborSigId != theRspBlk.myNeighborSigId )
        return false;

    return true;
}

//---------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetAddr( CT_TL1_LinkAddr& theAddr ) const
{
    if( myBitSet[INDEX_Addr] == true )
    {
        theAddr = myAddr;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetAddr( const CT_TL1_LinkAddr& theAddr )
{
    myAddr = theAddr;
    myBitSet[INDEX_Addr] = true;
}

//----------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetLcpState( CT_LcpState& theLcpState ) const
{
    if( myBitSet[INDEX_LcpState] == true )
    {
        theLcpState = myLcpState;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetLcpState( const CT_LcpState& theLcpState )
{
    if( theLcpState != CT_LCP_State_Unknown )
    {
        myLcpState = theLcpState;
        myBitSet[INDEX_LcpState] = true;
    }
}

//-----------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetMpState( CT_LcpState& theMpState ) const
{
    if( myBitSet[INDEX_MpState] == true )
    {
        theMpState = myMpState;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetMpState( const CT_LcpState& theMpState )
{
    if( theMpState != CT_LCP_State_Unknown )
    {
        myMpState = theMpState;
        myBitSet[INDEX_MpState] = true;
    }
}

//------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetMgtDomain( string& theMgtDomain ) const
{
    if( myBitSet[INDEX_MgtDomain] == true )
    {
        theMgtDomain = myMgtDomain;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetMgtDomain( const string& theMgtDomain )
{
    myMgtDomain = theMgtDomain;
    myBitSet[INDEX_MgtDomain] = true;
}

//------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetMgtNodeName( string& theMgtNodeName ) const
{
    if( myBitSet[INDEX_MgtNodeName] == true )
    {
        theMgtNodeName = myMgtNodeName;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetMgtNodeName( const string& theMgtNodeName )
{
    myMgtNodeName = theMgtNodeName;
    myBitSet[INDEX_MgtNodeName] = true;
}

//--------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetMgtPortName( string& theMgtPortName ) const
{
    if( myBitSet[INDEX_MgtPortName] == true )
    {
        theMgtPortName = myMgtPortName;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetMgtPortName( const string& theMgtPortName )
{
    myMgtPortName = theMgtPortName;
    myBitSet[INDEX_MgtPortName] = true;
}

//--------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetCpNameState( CT_LcpState& theCpNameState ) const
{
    if( myBitSet[INDEX_CpNameState] == true )
    {
        theCpNameState = myCpNameState;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetCpNameState( const CT_LcpState& theCpNameState )
{
    if( theCpNameState != CT_LCP_State_Unknown )
    {
        myCpNameState = theCpNameState;
        myBitSet[INDEX_CpNameState] = true;
    }
}

//--------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetRoutingAreaId( CT_ControlPlane_Addr& theRoutingAreaId ) const
{
    if( myBitSet[INDEX_RoutingAreaId] == true )
    {
        theRoutingAreaId = myRoutingAreaId;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetRoutingAreaId( const CT_ControlPlane_Addr& theRoutingAreaId )
{
    myRoutingAreaId = theRoutingAreaId;
    myBitSet[INDEX_RoutingAreaId] = true;
}

//----------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetCpConfigState( CT_LcpState& theCpConfigState ) const
{
    if( myBitSet[INDEX_CpConfigState] == true )
    {
        theCpConfigState = myCpConfigState;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetCpConfigState( const CT_LcpState& theCpConfigState )
{
    if( theCpConfigState != CT_LCP_State_Unknown )
    {
        myCpConfigState = theCpConfigState;
        myBitSet[INDEX_CpConfigState] = true;
    }
}

//----------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetNeighborNodeId( CT_ControlPlane_Addr& theNeighborNodeId ) const
{
    if( myBitSet[INDEX_NeighborNodeId] == true )
    {
        theNeighborNodeId = myNeighborNodeId;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId )
{
    myNeighborNodeId = theNeighborNodeId;
    myBitSet[INDEX_NeighborNodeId] = true;
}

//------------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetNeighborIfIndex( CT_ControlPlane_Addr& theNeighborIfIndex ) const
{
    if( myBitSet[INDEX_NeighborIfIndex] == true )
    {
        theNeighborIfIndex = myNeighborIfIndex;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex )
{
    myNeighborIfIndex = theNeighborIfIndex;
    myBitSet[INDEX_NeighborIfIndex] = true;
}

//-------------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetSigProtocol( CT_GMPLS_MODE& theSigProtocol ) const
{
    if( myBitSet[INDEX_SigProtocol] == true )
    {
        theSigProtocol = mySigProtocol;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetSigProtocol( const CT_GMPLS_MODE& theSigProtocol )
{
    mySigProtocol = theSigProtocol;
    myBitSet[INDEX_SigProtocol] = true;
}

//--------------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetRoutingProtocol( CT_GMPLS_MODE& theRoutingProtocol ) const
{
    if( myBitSet[INDEX_RoutingProtocol] == true )
    {
        theRoutingProtocol = myRoutingProtocol;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetRoutingProtocol( const CT_GMPLS_MODE& theRoutingProtocol )
{
    myRoutingProtocol = theRoutingProtocol;
    myBitSet[INDEX_RoutingProtocol] = true;
}

//--------------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetNeighborSigAddr( CT_ControlPlane_Addr& theNeighborSigAddr ) const
{
    if( myBitSet[INDEX_NeighborSigAddr] == true )
    {
        theNeighborSigAddr = myNeighborSigAddr;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetNeighborSigAddr( const CT_ControlPlane_Addr& theNeighborSigAddr )
{
    myNeighborSigAddr = theNeighborSigAddr;
    myBitSet[INDEX_NeighborSigAddr] = true;
}

//--------------------------------------------------------------------------------------
bool 
TL1_TceLinkRspBlk::GetNeighborSigId( CT_ControlPlane_Addr& theNeighborSigId ) const
{
    if( myBitSet[INDEX_NeighborSigId] == true )
    {
        theNeighborSigId = myNeighborSigId;
        return true;
    }
    return false;
}

void 
TL1_TceLinkRspBlk::SetNeighborSigId( const CT_ControlPlane_Addr& theNeighborSigId )
{
    myNeighborSigId = theNeighborSigId;
    myBitSet[INDEX_NeighborSigId] = true;
}

TL1_BLinkRspBlk::TL1_BLinkRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_BLinkRspBlk::TL1_BLinkRspBlk( 
                    const CT_TL1_LinkAddr&         theBLAddr,
                    const string&                  theBLName,
                    const CT_BLType&               theBLType,
                    const uint32                   theCost,
                    const uint32&                  theIfIndex,
                    const CT_ControlPlane_Addr&    theNeighborIfIndex,
                    const CT_TL_ROUTING&           theRouting,
                    const CT_ControlPlane_Srlg&    theSrlg,
                    const CT_LatencyMode&          theLatencyMode,
                    const uint32                   theLatency,
                    const CT_ControlPlane_Addr&    theResourceClass,
                    const CT_SM_PST&               thePST,
                    const CT_SM_PSTQ&              thePSTQ,
                    const CT_SM_SST&               theSST,
                    const set< CT_TL1_LinkAddr >&  theTLList,
                    const CT_TL1_LinkAddr&         theTLAddr,
                    const CT_ControlPlane_Addr&    theNeighborNodeId,
                    const CT_ControlPlane_Addr&    theNeighborSignalingAddr,
                    const CT_ControlPlane_Addr&    theNeighborSignalingId,
                    const CT_TL_DISCOVERY_TYPE&    theNeighborDiscovery,
                    const CT_TL1_LogicalAddr&      theLinkPfAid,
                    const CT_ControlPlane_Addr&    theRouterAreaId )

    : myBitSet( INDEX_END, false )
{
    myBitSet[ INDEX_BLAddr ] = true;
    myBLAddr= theBLAddr;

    myBitSet[ INDEX_BLName ] = true;
    myBLName= theBLName;

    myBitSet[ INDEX_BLType ] = true;
    myBLType = theBLType;

    myBitSet[ INDEX_Cost ] = true;
    myCost= theCost;

    myBitSet[ INDEX_IfIndex ] = true;
    myIfIndex= theIfIndex;

    myBitSet[ INDEX_NeighborIfIndex ] = true;
    myNeighborIfIndex= theNeighborIfIndex;

    myBitSet[ INDEX_Routing ] = true;
    myRouting= theRouting;

    myBitSet[ INDEX_Srlg ] = true;
    mySrlg= theSrlg;

    myBitSet[ INDEX_LatencyMode ] = true;
    myLatencyMode= theLatencyMode;

    myBitSet[ INDEX_Latency ] = true;
    myLatency= theLatency;

    myBitSet[ INDEX_ResourceClass ] = true;
    myResourceClass= theResourceClass;

    myBitSet[ INDEX_PST ] = true;
    myPST= thePST;

    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ= thePSTQ;

    myBitSet[ INDEX_SST ] = true;
    mySST= theSST;

    myBitSet[ INDEX_TLList ] = true;
    myTLList= theTLList;

    myBitSet[ INDEX_TLAddr ] = true;
    myTLAddr= theTLAddr;

    myBitSet[ INDEX_NeighborNodeId ] = true;
    myNeighborNodeId= theNeighborNodeId;

    myBitSet[ INDEX_NeighborSignalingAddr ] = true;
    myNeighborSignalingAddr= theNeighborSignalingAddr;

    myBitSet[ INDEX_NeighborSignalingId ] = true;
    myNeighborSignalingId= theNeighborSignalingId;

    myBitSet[ INDEX_NeighborDiscovery ] = true;
    myNeighborDiscovery= theNeighborDiscovery;

    myBitSet[ INDEX_LinkPfAid ] = true;
    myLinkPfAid= theLinkPfAid;

    myBitSet[ INDEX_RouterAreaId ] = true;
    myRouterAreaId= theRouterAreaId;
}

TL1_BLinkRspBlk::TL1_BLinkRspBlk( const TL1_BLinkRspBlk& theRspBlk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet = theRspBlk.myBitSet;
    myBLAddr = theRspBlk.myBLAddr;
    myBLName = theRspBlk.myBLName;
    myBLType = theRspBlk.myBLType;
    myCost = theRspBlk.myCost;
    myIfIndex = theRspBlk.myIfIndex;
    myNeighborIfIndex = theRspBlk.myNeighborIfIndex;
    myRouting = theRspBlk.myRouting;
    mySrlg = theRspBlk.mySrlg;
    myLatencyMode = theRspBlk.myLatencyMode;
    myLatency = theRspBlk.myLatency;
    myResourceClass = theRspBlk.myResourceClass;
    myPST = theRspBlk.myPST;
    myPSTQ = theRspBlk.myPSTQ;
    mySST = theRspBlk.mySST;
    myTLList = theRspBlk.myTLList;
    myTLAddr = theRspBlk.myTLAddr;
    myNeighborNodeId = theRspBlk.myNeighborNodeId;
    myNeighborSignalingAddr = theRspBlk.myNeighborSignalingAddr;
    myNeighborSignalingId = theRspBlk.myNeighborSignalingId;
    myNeighborDiscovery = theRspBlk.myNeighborDiscovery;
    myLinkPfAid = theRspBlk.myLinkPfAid;
    myRouterAreaId = theRspBlk.myRouterAreaId;
}

TL1_BLinkRspBlk::~TL1_BLinkRspBlk( )
{
}

TL1_BLinkRspBlk& 
TL1_BLinkRspBlk::operator=( const TL1_BLinkRspBlk& theRspBlk )
{
    myBitSet = theRspBlk.myBitSet;
    myBLAddr = theRspBlk.myBLAddr;
    myBLName = theRspBlk.myBLName;
    myBLType = theRspBlk.myBLType;
    myCost = theRspBlk.myCost;
    myIfIndex = theRspBlk.myIfIndex;
    myNeighborIfIndex = theRspBlk.myNeighborIfIndex;
    myRouting = theRspBlk.myRouting;
    mySrlg = theRspBlk.mySrlg;
    myLatencyMode = theRspBlk.myLatencyMode;
    myLatency = theRspBlk.myLatency;
    myResourceClass = theRspBlk.myResourceClass;
    myPST = theRspBlk.myPST;
    myPSTQ = theRspBlk.myPSTQ;
    mySST = theRspBlk.mySST;
    myTLList = theRspBlk.myTLList;
    myTLAddr = theRspBlk.myTLAddr;
    myNeighborNodeId = theRspBlk.myNeighborNodeId;
    myNeighborSignalingAddr = theRspBlk.myNeighborSignalingAddr;
    myNeighborSignalingId = theRspBlk.myNeighborSignalingId;
    myNeighborDiscovery = theRspBlk.myNeighborDiscovery;
    myLinkPfAid = theRspBlk.myLinkPfAid;
    myRouterAreaId = theRspBlk.myRouterAreaId;

    return *this;
}

bool 
TL1_BLinkRspBlk::operator==( const TL1_BLinkRspBlk& theRspBlk ) const
{
    if ( myBitSet != theRspBlk.myBitSet )                               return false;
    if ( myBLAddr != theRspBlk.myBLAddr )                               return false;
    if ( myBLName != theRspBlk.myBLName )                               return false;
    if ( myBLType != theRspBlk.myBLType )                               return false;
    if ( myCost != theRspBlk.myCost )                                   return false;
    if ( myIfIndex != theRspBlk.myIfIndex )                             return false;
    if ( myNeighborIfIndex != theRspBlk.myNeighborIfIndex )             return false;
    if ( myRouting != theRspBlk.myRouting )                             return false;
    if ( mySrlg != theRspBlk.mySrlg )                                   return false;
    if ( myLatencyMode != theRspBlk.myLatencyMode )                     return false;
    if ( myLatency != theRspBlk.myLatency )                             return false;
    if ( myResourceClass != theRspBlk.myResourceClass )                 return false;
    if ( myPST != theRspBlk.myPST )                                     return false;
    if ( myPSTQ != theRspBlk.myPSTQ )                                   return false;
    if ( mySST != theRspBlk.mySST )                                     return false;
    if ( myTLList != theRspBlk.myTLList )                               return false;
    if ( myTLAddr != theRspBlk.myTLAddr )                               return false;
    if ( myNeighborNodeId != theRspBlk.myNeighborNodeId )               return false;
    if ( myNeighborSignalingAddr != theRspBlk.myNeighborSignalingAddr ) return false;
    if ( myNeighborSignalingId != theRspBlk.myNeighborSignalingId )     return false;
    if ( myNeighborDiscovery != theRspBlk.myNeighborDiscovery )         return false;
    if ( myLinkPfAid != theRspBlk.myLinkPfAid )                         return false;
    if ( myRouterAreaId != theRspBlk.myRouterAreaId )                   return false;

    return true;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetBLinkAddr( const CT_TL1_LinkAddr& theBLAddr )
{
    myBitSet[ INDEX_BLAddr ] = true;
    myBLAddr= theBLAddr;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetBLinkName( const string& theBLName )
{
    myBitSet[ INDEX_BLName ] = true;
    myBLName= theBLName;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetBLinkType( const CT_BLType& theBLType )
{
    myBitSet[ INDEX_BLType] = true;
    myBLType= theBLType;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetCost( const uint32& theCost)
{
    myBitSet[ INDEX_Cost ] = true;
    myCost= theCost;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetIfIndex( const uint32& theIfIndex )
{
    myBitSet[ INDEX_IfIndex ] = true;
    myIfIndex= theIfIndex;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex )
{
    myBitSet[ INDEX_NeighborIfIndex ] = true;
    myNeighborIfIndex= theNeighborIfIndex;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetRouting( const CT_TL_ROUTING& theRouting )
{
    myBitSet[ INDEX_Routing ] = true;
    myRouting= theRouting;
}
//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetSrlg( const CT_ControlPlane_Srlg& theSrlg )
{
    myBitSet[ INDEX_Srlg ] = true;
    mySrlg= theSrlg;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetLatencyMode( const CT_LatencyMode& theLatencyMode )
{
    myBitSet[ INDEX_LatencyMode ] = true;
    myLatencyMode= theLatencyMode;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetLatency( const uint32& theLatency )
{
    myBitSet[ INDEX_Latency ] = true;
    myLatency= theLatency;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetResourceClass( const CT_ControlPlane_Addr& theResourceClass )
{
    myBitSet[ INDEX_ResourceClass ] = true;
    myResourceClass= theResourceClass;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetPST( const CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST= thePST;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetPSTQ( const CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ= thePSTQ;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetSST( const CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST= theSST;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetTLinkList( const set< CT_TL1_LinkAddr >& theTLList )
{
    myBitSet[ INDEX_TLList ] = true;
    myTLList= theTLList;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetTLinkAddr( const CT_TL1_LinkAddr& theTLAddr )
{
    myBitSet[ INDEX_TLAddr ] = true;
    myTLAddr= theTLAddr;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId )
{
    myBitSet[ INDEX_NeighborNodeId ] = true;
    myNeighborNodeId= theNeighborNodeId;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetNeighborSignalingAddr( const CT_ControlPlane_Addr& theNeighborSignalingAddr )
{
    myBitSet[ INDEX_NeighborSignalingAddr ] = true;
    myNeighborSignalingAddr= theNeighborSignalingAddr;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetNeighborSignalingId( const CT_ControlPlane_Addr& theNeighborSignalingId )
{
    myBitSet[ INDEX_NeighborSignalingId ] = true;
    myNeighborSignalingId= theNeighborSignalingId;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetNeighborDiscovery( const CT_TL_DISCOVERY_TYPE& theNeighborDiscovery )
{
    myBitSet[ INDEX_NeighborDiscovery ] = true;
    myNeighborDiscovery= theNeighborDiscovery;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetLinkPfAid( const CT_TL1_LogicalAddr& theLinkPfAid )
{
    myBitSet[ INDEX_LinkPfAid ] = true;
    myLinkPfAid= theLinkPfAid;
}

//--------------------------------------------------------------
void 
TL1_BLinkRspBlk::SetRouterAreaId( const CT_ControlPlane_Addr& theRouterAreaId )
{
    myBitSet[ INDEX_RouterAreaId ] = true;
    myRouterAreaId= theRouterAreaId;
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetBLinkAddr( CT_TL1_LinkAddr& theBLAddr) const
{
    if( true == myBitSet[ INDEX_BLAddr ] )
    {
        theBLAddr = myBLAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetBLinkName( string& theBLName ) const
{
    if( true == myBitSet[ INDEX_BLName ] )
    {
        theBLName = myBLName;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetBLinkType( CT_BLType& theBLType ) const
{
    if( true == myBitSet[ INDEX_BLType ] )
    {
        theBLType = myBLType;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetCost(uint32& theCost) const
{
    if( true == myBitSet[ INDEX_Cost ] )
    {
        theCost = myCost;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetIfIndex(uint32& theIfIndex) const
{
    if( true == myBitSet[ INDEX_IfIndex ] )
    {
        theIfIndex = myIfIndex;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetNeighborIfIndex(CT_ControlPlane_Addr& theNeighborIfIndex) const
{
    if( true == myBitSet[ INDEX_NeighborIfIndex ] )
    {
        theNeighborIfIndex = myNeighborIfIndex;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetRouting(CT_TL_ROUTING& theRouting) const
{
    if( true == myBitSet[ INDEX_Routing ] )
    {
        theRouting = myRouting;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetSrlg(CT_ControlPlane_Srlg& theSrlg) const
{
    if( true == myBitSet[ INDEX_Srlg ] )
    {
        theSrlg = mySrlg;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetLatencyMode( CT_LatencyMode& theLatencyMode ) const
{
    if( true == myBitSet[ INDEX_LatencyMode ] )
    {
        theLatencyMode = myLatencyMode;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetLatency(uint32& theLatency) const
{
    if( true == myBitSet[ INDEX_Latency ] )
    {
        theLatency = myLatency;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetResourceClass(CT_ControlPlane_Addr& theResourceClass) const
{
    if( true == myBitSet[ INDEX_ResourceClass ] )
    {
        theResourceClass = myResourceClass;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetPST(CT_SM_PST& thePST) const
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

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetPSTQ(CT_SM_PSTQ& thePSTQ) const
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

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetSST(CT_SM_SST& theSST) const
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

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetTLinkList( set< CT_TL1_LinkAddr >& theTLList) const
{
    if( true == myBitSet[ INDEX_TLList ] )
    {
        theTLList = myTLList;
        return true;
    }
    else
    {
        return false;
    }
}


//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetTLinkAddr( CT_TL1_LinkAddr& theTLAddr) const
{
    if( true == myBitSet[ INDEX_TLAddr ] )
    {
        theTLAddr = myTLAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetNeighborNodeId(CT_ControlPlane_Addr& theNeighborNodeId) const
{
    if( true == myBitSet[ INDEX_NeighborNodeId ] )
    {
        theNeighborNodeId = myNeighborNodeId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetNeighborSignalingAddr(CT_ControlPlane_Addr& theNeighborSignalingAddr) const
{
    if( true == myBitSet[ INDEX_NeighborSignalingAddr ] )
    {
        theNeighborSignalingAddr = myNeighborSignalingAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetNeighborSignalingId(CT_ControlPlane_Addr& theNeighborSignalingId) const
{
    if( true == myBitSet[ INDEX_NeighborSignalingId ] )
    {
        theNeighborSignalingId = myNeighborSignalingId;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetNeighborDiscovery(CT_TL_DISCOVERY_TYPE& theNeighborDiscovery) const
{
    if( true == myBitSet[ INDEX_NeighborDiscovery ] )
    {
        theNeighborDiscovery = myNeighborDiscovery;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetLinkPfAid(CT_TL1_LogicalAddr& theLinkPfAid) const
{
    if( true == myBitSet[ INDEX_LinkPfAid ] )
    {
        theLinkPfAid = myLinkPfAid;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_BLinkRspBlk::GetRouterAreaId(CT_ControlPlane_Addr& theRouterAreaId) const
{
    if( true == myBitSet[ INDEX_RouterAreaId ] )
    {
        theRouterAreaId = myRouterAreaId;
        return true;
    }
    else
    {
        return false;
    }
}

