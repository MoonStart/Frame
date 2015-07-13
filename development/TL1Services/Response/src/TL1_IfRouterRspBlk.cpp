/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Source file for TL1 Retrieve IF Router Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_IfRouterRspBlk.h>


TL1_IfRouterRspBlk::TL1_IfRouterRspBlk( const TL1_SmartParameter<CT_IfNumber>& theIfName,
                                        const TL1_SmartParameter<CT_InterfaceType>& theIfType,
                                        const TL1_SmartParameter<CT_InterfaceMode>& theIfMode,
                                        const TL1_SmartParameter<CT_InterfaceState>& theIfState,
                                        const TL1_SmartParameter<uint32>& theHelloInt,
                                        const TL1_SmartParameter<uint32>& theRouterDeadInterval,
                                        const TL1_SmartParameter<uint32>& theLinkCost,
                                        const TL1_SmartParameter<bool>& theSWstatus,
                                        const TL1_SmartParameter<bool>& thePSstatus) :
    itsIfName(theIfName),
    itsIfType(theIfType),
    itsIfMode(theIfMode),
    itsIfState(theIfState),
    itsHelloInt(theHelloInt),
    itsRouterDeadInterval(theRouterDeadInterval),
    itsLinkCost(theLinkCost),
    itsSWstatus(theSWstatus),
    itsPSstatus(thePSstatus)
{
}

TL1_IfRouterRspBlk::~TL1_IfRouterRspBlk()
{
}
  
TL1_IfRouterRspBlk::TL1_IfRouterRspBlk( const TL1_IfRouterRspBlk& theBlock ) :
    itsIfName(theBlock.itsIfName),
    itsIfType(theBlock.itsIfType),
    itsIfMode(theBlock.itsIfMode),
    itsIfState(theBlock.itsIfState),
    itsHelloInt(theBlock.itsHelloInt),
    itsRouterDeadInterval(theBlock.itsRouterDeadInterval),
    itsLinkCost(theBlock.itsLinkCost),
    itsSWstatus(theBlock.itsSWstatus),
    itsPSstatus(theBlock.itsPSstatus)
{
}

TL1_IfRouterRspBlk& TL1_IfRouterRspBlk::operator=( const TL1_IfRouterRspBlk& theBlock )
{
    itsIfName = theBlock.itsIfName;
    itsIfType = theBlock.itsIfType;
    itsIfMode = theBlock.itsIfMode;
    itsIfState = theBlock.itsIfState;
    itsHelloInt = theBlock.itsHelloInt;
    itsRouterDeadInterval = theBlock.itsRouterDeadInterval;
    itsLinkCost = theBlock.itsLinkCost;
    itsSWstatus = theBlock.itsSWstatus;
    itsPSstatus = theBlock.itsPSstatus;

    return *this;
}

const TL1_SmartParameter<CT_IfNumber>& TL1_IfRouterRspBlk::GetIfName() const
{
    return itsIfName;
}

const TL1_SmartParameter<CT_InterfaceType>& TL1_IfRouterRspBlk::GetIfType() const
{
    return itsIfType;
}

const TL1_SmartParameter<CT_InterfaceMode>& TL1_IfRouterRspBlk::GetIfMode() const
{
    return itsIfMode;
}

const TL1_SmartParameter<CT_InterfaceState>& TL1_IfRouterRspBlk::GetIfState() const
{
    return itsIfState;
}



const TL1_SmartParameter<uint32>& TL1_IfRouterRspBlk::GetHelloInt() const
{
    return itsHelloInt;
}



const TL1_SmartParameter<uint32>& TL1_IfRouterRspBlk::GetRouterDeadInterval() const
{
    return itsRouterDeadInterval;
}

const TL1_SmartParameter<uint32>& TL1_IfRouterRspBlk::GetLinkCost() const
{
    return itsLinkCost;
}

const TL1_SmartParameter<bool>& TL1_IfRouterRspBlk::GetSWstatus() const
{
    return itsSWstatus;
}


const TL1_SmartParameter<bool>& TL1_IfRouterRspBlk::GetPSstatus() const
{
    return itsPSstatus;
}

