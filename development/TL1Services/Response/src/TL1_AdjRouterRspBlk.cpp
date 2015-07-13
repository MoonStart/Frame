/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 4, 2003- Jean-Francois Tremblay
DESCRIPTION:    Source file for TL1 Retrieve Adj Router Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_AdjRouterRspBlk.h>


TL1_AdjRouterRspBlk::TL1_AdjRouterRspBlk( const TL1_SmartParameter<uint32>& theNeighborIp,
                                          const TL1_SmartParameter<CT_Adj_Status>& theAdjacencyStatus,
                                          const TL1_SmartParameter<CT_IfNumber>& theIfName ) :
    itsNeighborIp(theNeighborIp),
    itsAdjacencyStatus(theAdjacencyStatus),
    itsIfName(theIfName)
{
}

TL1_AdjRouterRspBlk::~TL1_AdjRouterRspBlk()
{
}
  
TL1_AdjRouterRspBlk::TL1_AdjRouterRspBlk( const TL1_AdjRouterRspBlk& theBlock ) :
    itsNeighborIp(theBlock.itsNeighborIp),
    itsAdjacencyStatus(theBlock.itsAdjacencyStatus),
    itsIfName(theBlock.itsIfName)
{
}

TL1_AdjRouterRspBlk& TL1_AdjRouterRspBlk::operator=( const TL1_AdjRouterRspBlk& theBlock )
{
    itsNeighborIp = theBlock.itsNeighborIp;
    itsAdjacencyStatus = theBlock.itsAdjacencyStatus;
    itsIfName = theBlock.itsIfName;

    return *this;
}

const TL1_SmartParameter<uint32>& TL1_AdjRouterRspBlk::GetNeighborIp() const
{
    return itsNeighborIp;
}

const TL1_SmartParameter<CT_Adj_Status>& TL1_AdjRouterRspBlk::GetAdjacencyStatus() const
{
    return itsAdjacencyStatus;
}

const TL1_SmartParameter<CT_IfNumber>& TL1_AdjRouterRspBlk::GetIfName() const
{
    return itsIfName;
}

