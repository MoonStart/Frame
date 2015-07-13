/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Static Route Response 
TARGET:
AUTHOR:         July 17, 2007 - Tong Wu
DESCRIPTION:    Source file for TL1 Static Route Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_StatRteRspBlk.h>

TL1_StatRteRspBlk::TL1_StatRteRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

#if 0
TL1_StatRteRspBlk::TL1_StatRteRspBlk( const uint32*             theDestination,
                                      const uint32*             theNetmask,
                                      const CT_TL1_LinkAddr*    theTLAid,
                                      const CT_IfNumber*        theIfName,
                                      const uint32*             theNexthop,
                                      const bool*               theAdvertise)
    : myBitSet( INDEX_END, false )
{
    if( theDestination )
    {
        myBitSet[ INDEX_Destination ] = true;
        myDestination = *theDestination;
    }

    if( theNetmask )
    {
        myBitSet[ INDEX_Netmask ] = true;
        myNetmask = *theNetmask;
    }

    if( theTLAid )
    {
        myBitSet[ INDEX_TLAid ] = true;
        myTLAid = *theTLAid;
    }

    if( theIfName )
    {
        myBitSet[ INDEX_IfName ] = true;
        myIfName = *theIfName;
    }

    if( theNexthop )
    {
        myBitSet[ INDEX_Nexthop ] = true;
        myNexthop = *theNexthop;
    }

    if( theAdvertise )
    {
        myBitSet[ INDEX_Advertise ] = true;
        myAdvertise = *theAdvertise;
    }
}
#endif

TL1_StatRteRspBlk::TL1_StatRteRspBlk( const TL1_StatRteRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=       t1Blk.myBitSet;
    myDestination=  t1Blk.myDestination;
    myNetmask=      t1Blk.myNetmask;    
    myTLAid=        t1Blk.myTLAid;
    myIfName=       t1Blk.myIfName;
    myNexthop=      t1Blk.myNexthop;
    myAdvertise=    t1Blk.myAdvertise;

    myIpv6Destination = t1Blk.myIpv6Destination;
    myIpv6Nexthop     = t1Blk.myIpv6Nexthop;
    
}

TL1_StatRteRspBlk::~TL1_StatRteRspBlk( )
{
}

TL1_StatRteRspBlk& 
TL1_StatRteRspBlk::operator=( const TL1_StatRteRspBlk& t1Blk )
{
    myBitSet=       t1Blk.myBitSet;
    myDestination=  t1Blk.myDestination;
    myNetmask=      t1Blk.myNetmask;    
    myTLAid=        t1Blk.myTLAid;
    myIfName=       t1Blk.myIfName;
    myNexthop=      t1Blk.myNexthop;
    myAdvertise=    t1Blk.myAdvertise;

    myIpv6Destination = t1Blk.myIpv6Destination;
    myIpv6Nexthop     = t1Blk.myIpv6Nexthop;

    return *this;
}

bool 
TL1_StatRteRspBlk::operator==( const TL1_StatRteRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myDestination != t1Blk.myDestination )
        return false;

    if ( myNetmask != t1Blk.myNetmask )
        return false;

    if ( !( myTLAid == t1Blk.myTLAid ) )
        return false;

    if ( myIfName != t1Blk.myIfName)
        return false;

    if ( myNexthop != t1Blk.myNexthop )
        return false;

    if ( myAdvertise != t1Blk.myAdvertise )
        return false;

    if(myIpv6Destination != t1Blk.myIpv6Destination)
        return false;

    if(myIpv6Nexthop != t1Blk.myIpv6Nexthop)
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_StatRteRspBlk::GetDestination( uint32& theDestination ) const
{
    if( true == myBitSet[ INDEX_Destination ] )
    {
        theDestination = myDestination;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_StatRteRspBlk::SetDestination( const uint32& theDestination )
{
   myBitSet[ INDEX_Destination ] = true;
   myDestination = theDestination;
}

//--------------------------------------------------------------
bool 
TL1_StatRteRspBlk::GetNetmask( uint32& theNetmask ) const
{
    if( true == myBitSet[ INDEX_Netmask ] )
    {
        theNetmask = myNetmask;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_StatRteRspBlk::SetNetmask( const uint32& theNetmask )
{
    myBitSet[ INDEX_Netmask ] = true;
    myNetmask = theNetmask;
}

//--------------------------------------------------------------
bool 
TL1_StatRteRspBlk::GetTLAid( CT_TL1_LinkAddr& theTLAid ) const
{
    if( true == myBitSet[ INDEX_TLAid ] )
    {
        theTLAid = myTLAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_StatRteRspBlk::SetTLAid( const CT_TL1_LinkAddr& theTLAid )
{
    myBitSet[ INDEX_TLAid ] = true;
    myTLAid = theTLAid;
}

//--------------------------------------------------------------
bool 
TL1_StatRteRspBlk::GetIfName( CT_IfNumber& theIfName ) const
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

void 
TL1_StatRteRspBlk::SetIfName( const CT_IfNumber& theIfName )
{
    myBitSet[ INDEX_IfName ] = true;
    myIfName = theIfName;
}

//--------------------------------------------------------------
bool 
TL1_StatRteRspBlk::GetNexthop( uint32& theNexthop ) const
{
    if( true == myBitSet[ INDEX_Nexthop ] )
    {
        theNexthop = myNexthop;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_StatRteRspBlk::SetNexthop( const uint32& theNexthop )
{
    myBitSet[ INDEX_Nexthop ] = true;
    myNexthop = theNexthop;
}


//--------------------------------------------------------------
bool 
TL1_StatRteRspBlk::GetAdvertise( bool& theAdvertise ) const
{
    if( true == myBitSet[ INDEX_Advertise ] )
    {
        theAdvertise = myAdvertise;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_StatRteRspBlk::SetAdvertise( const bool& theAdvertise )
{
    myBitSet[ INDEX_Advertise ] = true;
    myAdvertise = theAdvertise;
}



bool TL1_StatRteRspBlk::GetIpv6Destination( string &theDestination ) const
{
    if( true == myBitSet[ INDEX_IPV6_DESTINATION ] )
    {
        theDestination = myIpv6Destination;
        return true;
    }
    else
    {
        return false;
    }

}

bool TL1_StatRteRspBlk::GetIpv6Nexthop( string &theNexthop ) const
{
    if( true == myBitSet[ INDEX_IPV6_NEXTHOP ] )
    {
        theNexthop = myIpv6Nexthop;
        return true;
    }
    else
    {
        return false;
    }
}



void TL1_StatRteRspBlk::SetDestination( const string& theDestination )
{
    myBitSet[ INDEX_IPV6_DESTINATION ] = true;
    myIpv6Destination = theDestination;
}


void TL1_StatRteRspBlk::SetNexthop( const string& theNexthop )
{
    myBitSet[ INDEX_IPV6_NEXTHOP ] = true;
    myIpv6Nexthop = theNexthop;
}
    



//------------------------------------------------------------------------
TL1_RteAllRspBlk::TL1_RteAllRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}


#if 0
TL1_RteAllRspBlk::TL1_RteAllRspBlk( const uint32*           	theDestination,
                                    const uint32*           	theNetmask,
                                    const uint32*           	theInterface,
                                    const uint32*           	theNexthop,
									const CT_IfNumber*			theIfname,
									const CT_TL1_LinkAddr*		theTLAid,
									const CT_TL1_ResourceAddr*	theResource,
									const CT_RouteType*			theRtype )
    : myBitSet( INDEX_END, false )
{
    if( theDestination )
    {
        myBitSet[ INDEX_Destination ] = true;
        myDestination = *theDestination;
    }

    if( theNetmask )
    {
        myBitSet[ INDEX_Netmask ] = true;
        myNetmask = *theNetmask;
    }

    if( theInterface )
    {
        myBitSet[ INDEX_Interface ] = true;
        myInterface = *theInterface;
    }

    if( theNexthop )
    {
        myBitSet[ INDEX_Nexthop ] = true;
        myNexthop = *theNexthop;
    }

    if( theIfname )
    {
        myBitSet[ INDEX_Ifname ] = true;
        myIfname = *theIfname;
    }

    if( theTLAid )
    {
        myBitSet[ INDEX_TLAid ] = true;
        myTLAid = *theTLAid;
    }

    if( theResource )
    {
        myBitSet[ INDEX_Resource ] = true;
        myResource = *theResource;
    }

    if( theRtype )
    {
        myBitSet[ INDEX_Rtype ] = true;
        myRtype = *theRtype;
    }
}
#endif

TL1_RteAllRspBlk::TL1_RteAllRspBlk( const TL1_RteAllRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=       t1Blk.myBitSet;
    myDestination=      t1Blk.myDestination;
    myNetmask=          t1Blk.myNetmask;    
    myInterface=        t1Blk.myInterface;
    myNexthop=          t1Blk.myNexthop;
    myIfname=           t1Blk.myIfname;
    myTLAid=            t1Blk.myTLAid;
    myResource=         t1Blk.myResource;
    myRtype=            t1Blk.myRtype;

    myIpv6Destination = t1Blk.myIpv6Destination;
    myIpv6Nexthop =     t1Blk.myIpv6Nexthop;
}

TL1_RteAllRspBlk::~TL1_RteAllRspBlk( )
{
}

TL1_RteAllRspBlk& 
TL1_RteAllRspBlk::operator=( const TL1_RteAllRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myDestination=      t1Blk.myDestination;
    myNetmask=          t1Blk.myNetmask;    
    myInterface=        t1Blk.myInterface;
    myNexthop=          t1Blk.myNexthop;
    myIfname=           t1Blk.myIfname;
    myTLAid=            t1Blk.myTLAid;
    myResource=         t1Blk.myResource;
    myRtype=            t1Blk.myRtype;

    myIpv6Destination = t1Blk.myIpv6Destination;
    myIpv6Nexthop =     t1Blk.myIpv6Nexthop;
 
    return *this;
}

bool 
TL1_RteAllRspBlk::operator==( const TL1_RteAllRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myDestination != t1Blk.myDestination )
        return false;

    if ( myNetmask != t1Blk.myNetmask  )
        return false;

    if ( myInterface != t1Blk.myInterface  )
        return false;

    if ( myNexthop != t1Blk.myNexthop )
        return false;

	if ( myIfname != t1Blk.myIfname )
		return false;

	if ( myTLAid != t1Blk.myTLAid )
		return false;

	if ( myResource != t1Blk.myResource )
		return false;

	if ( myRtype != t1Blk.myRtype )
		return false;

    if(myIpv6Destination != t1Blk.myIpv6Destination)
    {
        return false;
    }

    if(myIpv6Nexthop != t1Blk.myIpv6Nexthop)
    {
        return false;
    }

    return true;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetDestination( uint32& theDestination ) const
{
    if( true == myBitSet[ INDEX_Destination ] )
    {
        theDestination = myDestination;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_RteAllRspBlk::GetIpv6Destination(string &theDestination) const
{
    if( true == myBitSet[ INDEX_IPV6_DESTINATION ] )
    {
        theDestination = myIpv6Destination;
        return true;
    }
    else
    {
        return false;
    }
}


void 
TL1_RteAllRspBlk::SetDestination( const uint32& theDestination )
{
   myBitSet[ INDEX_Destination ] = true;
   myDestination = theDestination;
}

void TL1_RteAllRspBlk::SetDestination(const string &theDestination)
{
    myBitSet[ INDEX_IPV6_DESTINATION ] = true;
    myIpv6Destination = theDestination;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetNetmask( uint32& theNetmask ) const
{
    if( true == myBitSet[ INDEX_Netmask ] )
    {
        theNetmask = myNetmask;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RteAllRspBlk::SetNetmask( const uint32& theNetmask )
{
    myBitSet[ INDEX_Netmask ] = true;
    myNetmask = theNetmask;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetInterface( uint32& theInterface ) const
{
    if( true == myBitSet[ INDEX_Interface ] )
    {
        theInterface = myInterface;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RteAllRspBlk::SetInterface( const uint32& theInterface )
{
    myBitSet[ INDEX_Interface ] = true;
    myInterface = theInterface;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetNexthop( uint32& theNexthop ) const
{
    if( true == myBitSet[ INDEX_Nexthop ] )
    {
        theNexthop = myNexthop;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_RteAllRspBlk::GetIpv6Nexthop(string &theNexthop) const
{
    if( true == myBitSet[ INDEX_IPV6_DESTINATION ] )
    {
        theNexthop = myIpv6Nexthop;
        return true;
    }
    else
    {
        return false;
    }
}


void 
TL1_RteAllRspBlk::SetNexthop( const uint32& theNexthop )
{
    myBitSet[ INDEX_Nexthop ] = true;
    myNexthop = theNexthop;
}

void TL1_RteAllRspBlk::SetNexthop(const string &theNexthop )
{
    myBitSet[ INDEX_IPV6_NEXTHOP ] = true;
    myIpv6Nexthop = theNexthop;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetIfName( CT_IfNumber& theIfname ) const
{
    if( true == myBitSet[ INDEX_Ifname ] )
    {
        theIfname = myIfname;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RteAllRspBlk::SetIfName( const CT_IfNumber& theIfname )
{
    myBitSet[ INDEX_Ifname ] = true;
    myIfname = theIfname;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetTLAid( CT_TL1_LinkAddr& theTLAid ) const
{
    if( true == myBitSet[ INDEX_TLAid ] )
    {
        theTLAid = myTLAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RteAllRspBlk::SetTLAid( const CT_TL1_LinkAddr& theTLAid )
{
    myBitSet[ INDEX_TLAid ] = true;
    myTLAid = theTLAid;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetResource( CT_TL1_ResourceAddr& theResource ) const
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

void 
TL1_RteAllRspBlk::SetResource( const CT_TL1_ResourceAddr& theResource )
{
    myBitSet[ INDEX_Resource ] = true;
    myResource = theResource;
}

//--------------------------------------------------------------
bool 
TL1_RteAllRspBlk::GetType( CT_RouteType& theRtype ) const
{
    if( true == myBitSet[ INDEX_Rtype ] )
    {
        theRtype = myRtype;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_RteAllRspBlk::SetType( const CT_RouteType& theRtype )
{
    myBitSet[ INDEX_Rtype ] = true;
    myRtype = theRtype;
}



