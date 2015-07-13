/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         July, 15 2010- Kevin, Wang
DESCRIPTION:    Source file for TL1 Retrieve IF Config Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_IfConfigRspBlk.h>


TL1_IfConfigRspBlk::TL1_IfConfigRspBlk( const TL1_SmartParameter<string>  theAidStr,
                        const TL1_SmartParameter<string>     theIfName,
                        const TL1_SmartParameter<string>     theIfType,
                        const TL1_SmartParameter<string>     theIpv6Addr,
                        const TL1_SmartParameter<int>        theIfStatus,
                        const TL1_SmartParameter<string>     theIfVldTmr,
                        const TL1_SmartParameter<int>        theIfRouterAddr ) :
        myAidStr(theAidStr),
        myIfName(theIfName),
        myIfType(theIfType),
        myIpv6Addr(theIpv6Addr),
        myIfStatus(theIfStatus),
        myIfVldTmr(theIfVldTmr),
        myIfRouterAddr(theIfRouterAddr)
{
}

TL1_IfConfigRspBlk::~TL1_IfConfigRspBlk()
{
}
  
TL1_IfConfigRspBlk::TL1_IfConfigRspBlk( const TL1_IfConfigRspBlk& theBlock ) :
        myAidStr(theBlock.myAidStr),
        myIfName(theBlock.myIfName),
        myIfType(theBlock.myIfType),
        myIpv6Addr(theBlock.myIpv6Addr),
        myIfStatus(theBlock.myIfStatus),
        myIfVldTmr(theBlock.myIfVldTmr),
        myIfRouterAddr(theBlock.myIfRouterAddr)
{
}

TL1_IfConfigRspBlk& TL1_IfConfigRspBlk::operator=( const TL1_IfConfigRspBlk& theBlock )
{
    myAidStr = theBlock.myAidStr;
    myIfName = theBlock.myIfName;
    myIfType = theBlock.myIfType;
    myIpv6Addr = theBlock.myIpv6Addr;
    myIfStatus = theBlock.myIfStatus;
    myIfVldTmr = theBlock.myIfVldTmr;
    myIfRouterAddr = theBlock.myIfRouterAddr;

    return *this;
}

const TL1_SmartParameter<string>& TL1_IfConfigRspBlk::GetIfAid() const
{
    return myAidStr;
}

const TL1_SmartParameter<string>& TL1_IfConfigRspBlk::GetIfName() const
{
    return myIfName;
}

const TL1_SmartParameter<string>& TL1_IfConfigRspBlk::GetIfType() const
{
    return myIfType;
}

const TL1_SmartParameter<string>& TL1_IfConfigRspBlk::GetIpv6Addr() const
{
    return myIpv6Addr;
}

const TL1_SmartParameter<int>& TL1_IfConfigRspBlk::GetIfStatus() const
{
    return myIfStatus;
}

const TL1_SmartParameter<string>& TL1_IfConfigRspBlk::GetIfVldTmr() const
{
    return myIfVldTmr;
}

const TL1_SmartParameter<int>& TL1_IfConfigRspBlk::GetIfRouterAddr() const
{
    return myIfRouterAddr;
}
