/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Source file for TL1 Retrieve IP Routing Table Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_IPRoutTblRspBlk.h>


TL1_IPRoutTblRspBlk::TL1_IPRoutTblRspBlk( const TL1_SmartParameter<uint32>& theDestAddress,
                                          const TL1_SmartParameter<uint32>& theNetMask,
                                          const TL1_SmartParameter<uint32>& theNextHopAddr,
                                          const TL1_SmartParameter<CT_LinkStatus>& theLinkStatus,
                                          const TL1_SmartParameter<CT_RouteType>& theRouteType,
                                          const TL1_SmartParameter<CT_IfNumber>& theIfName ) :
    itsDestAddress(theDestAddress),
    itsNetMask(theNetMask),
    itsNextHopAddr(theNextHopAddr),
    itsLinkStatus(theLinkStatus),
    itsRouteType(theRouteType),
    itsIfName(theIfName)
{
}

TL1_IPRoutTblRspBlk::~TL1_IPRoutTblRspBlk()
{
}
  
TL1_IPRoutTblRspBlk::TL1_IPRoutTblRspBlk( const TL1_IPRoutTblRspBlk& theBlock ) :
    itsDestAddress(theBlock.itsDestAddress),
    itsNetMask(theBlock.itsNetMask),
    itsNextHopAddr(theBlock.itsNextHopAddr),
    itsLinkStatus(theBlock.itsLinkStatus),
    itsRouteType(theBlock.itsRouteType),
    itsIfName(theBlock.itsIfName)
{
}

TL1_IPRoutTblRspBlk& TL1_IPRoutTblRspBlk::operator=( const TL1_IPRoutTblRspBlk& theBlock )
{
    itsDestAddress = theBlock.itsDestAddress;
    itsNetMask     = theBlock.itsNetMask;
    itsNextHopAddr = theBlock.itsNextHopAddr;
    itsLinkStatus  = theBlock.itsLinkStatus;
    itsRouteType   = theBlock.itsRouteType;
    itsIfName      = theBlock.itsIfName;

    return *this;
}

const TL1_SmartParameter<uint32>& TL1_IPRoutTblRspBlk::GetDestAddress() const
{
    return itsDestAddress;
}

const TL1_SmartParameter<uint32>& TL1_IPRoutTblRspBlk::GetNetMask() const
{
    return itsNetMask;
}

const TL1_SmartParameter<uint32>& TL1_IPRoutTblRspBlk::GetNextHopAddr() const
{
    return itsNextHopAddr;
}

const TL1_SmartParameter<CT_LinkStatus>& TL1_IPRoutTblRspBlk::GetLinkStatus() const
{
    return itsLinkStatus;
}

const TL1_SmartParameter<CT_RouteType>& TL1_IPRoutTblRspBlk::GetRouteType() const
{
    return itsRouteType;
}

const TL1_SmartParameter<CT_IfNumber>& TL1_IPRoutTblRspBlk::GetIfName() const
{
    return itsIfName;
}

