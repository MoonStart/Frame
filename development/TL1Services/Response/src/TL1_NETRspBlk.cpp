/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 NET Response 
TARGET:
AUTHOR:         Jun 5, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Retrive NET Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_NETRspBlk.h>


TL1_NETRspBlk::TL1_NETRspBlk( const TL1_SmartParameter<CT_EONType>& theEONType,
                              const TL1_SmartParameter<CT_EONState>& theEONState,
                              const TL1_SmartParameter<uint32>& theLocalIf,
                              const TL1_SmartParameter<uint32>& theLocalIfMask,
                              const TL1_SmartParameter<uint32>& theManageIf,
                              const TL1_SmartParameter<uint32>& theManageIfMask,
                              const TL1_SmartParameter<uint32>& theRouterIf,
                              const TL1_SmartParameter<uint32>& theRouterIfMask,
                              const TL1_SmartParameter<uint32>& theDCNIf,
                              const TL1_SmartParameter<uint32>& theDCNIfMask,
                              const TL1_SmartParameter<CT_IfSpeed>&  theDcnIfSpeed,
                              const TL1_SmartParameter<CT_IfDuplex>& theDcnIfDuplex,
                              const TL1_SmartParameter<uint32>& theGNEIf,
                              const TL1_SmartParameter<uint32>& theGNEIfMask,
                              const TL1_SmartParameter<uint32>& theGateway,
                              const TL1_SmartParameter<bool>&   theDhcpClient,
                              const TL1_SmartParameter<string>& theIpSubnet, 
                              const TL1_SmartParameter<string>& theNESubnet, 
                              const TL1_SmartParameter<bool>&   theRadClient,
                              const TL1_SmartParameter<uint32>& theRadIter,
                              const TL1_SmartParameter<uint32>& theRadTmout,
                              const TL1_SmartParameter<bool>&   theNatDcn,
                              const TL1_SmartParameter<uint32>& thePrimaryGNE,
                              const TL1_SmartParameter<uint32>& theSecondaryGNE,
                              const TL1_SmartParameter<CT_NM_ROUTING_CONFIG>& theDcnRoutingConfig) : 
    itsEONType(theEONType),
    itsEONState(theEONState),
    itsLocalIf(theLocalIf),
    itsLocalIfMask(theLocalIfMask),
    itsManageIf(theManageIf),
    itsManageIfMask(theManageIfMask),
    itsRouterIf(theRouterIf),
    itsRouterIfMask(theRouterIfMask),
    itsDCNIf(theDCNIf),
    itsDCNIfMask(theDCNIfMask),
    itsDCNIfSpeed(theDcnIfSpeed),
    itsDCNIfDuplex(theDcnIfDuplex),
    itsGNEIf(theGNEIf),
    itsGNEIfMask(theGNEIfMask),
    itsGateway(theGateway),
    itsDhcpClient(theDhcpClient),
    itsIpSubnet(theIpSubnet),
    itsNESubnet(theNESubnet),
    itsRadClient(theRadClient),
    itsRadIter(theRadIter),
    itsRadTmout(theRadTmout),
    itsDcnNat(theNatDcn),
    itsPriGneAddr(thePrimaryGNE),
    itsSecGneAddr(theSecondaryGNE),
    itsDcnRoutingConfig(theDcnRoutingConfig)
{
}

TL1_NETRspBlk::~TL1_NETRspBlk()
{
}
  
TL1_NETRspBlk::TL1_NETRspBlk(const TL1_NETRspBlk& theBlock) :
    itsEONType(theBlock.itsEONType),
    itsEONState(theBlock.itsEONState),
    itsLocalIf(theBlock.itsLocalIf),
    itsLocalIfMask(theBlock.itsLocalIfMask),
    itsManageIf(theBlock.itsManageIf),
    itsManageIfMask(theBlock.itsManageIfMask),
    itsRouterIf(theBlock.itsRouterIf),
    itsRouterIfMask(theBlock.itsRouterIfMask),
    itsDCNIf(theBlock.itsDCNIf),
    itsDCNIfMask(theBlock.itsDCNIfMask),
    itsDCNIfSpeed(theBlock.itsDCNIfSpeed),
    itsDCNIfDuplex(theBlock.itsDCNIfDuplex),
    itsGNEIf(theBlock.itsGNEIf),
    itsGNEIfMask(theBlock.itsGNEIfMask),
    itsGateway(theBlock.itsGateway),
    itsDhcpClient(theBlock.itsDhcpClient),
    itsIpSubnet(theBlock.itsIpSubnet),
    itsNESubnet(theBlock.itsNESubnet),
    itsRadClient(theBlock.itsRadClient),
    itsRadIter(theBlock.itsRadIter),
    itsRadTmout(theBlock.itsRadTmout),
    itsDcnNat(theBlock.itsDcnNat),
    itsPriGneAddr(theBlock.itsPriGneAddr),
    itsSecGneAddr(theBlock.itsSecGneAddr),
    itsDcnRoutingConfig(theBlock.itsDcnRoutingConfig)
{
}

TL1_NETRspBlk& TL1_NETRspBlk::operator=( const TL1_NETRspBlk& theBlock )
{
    itsEONType = theBlock.itsEONType;
    itsEONState = theBlock.itsEONState;
    itsLocalIf = theBlock.itsLocalIf;
    itsLocalIfMask = theBlock.itsLocalIfMask;
    itsManageIf = theBlock.itsManageIf;
    itsManageIfMask = theBlock.itsManageIfMask;
    itsRouterIf = theBlock.itsRouterIf;
    itsRouterIfMask = theBlock.itsRouterIfMask;
    itsDCNIf = theBlock.itsDCNIf;
    itsDCNIfMask = theBlock.itsDCNIfMask;
    itsDCNIfSpeed = theBlock.itsDCNIfSpeed;
    itsDCNIfDuplex = theBlock.itsDCNIfDuplex;
    itsGNEIf = theBlock.itsGNEIf;
    itsGNEIfMask = theBlock.itsGNEIfMask;
    itsGateway = theBlock.itsGateway;
    itsDhcpClient = theBlock.itsDhcpClient;
    itsIpSubnet = theBlock.itsIpSubnet;
    itsNESubnet = theBlock.itsNESubnet;
    itsRadClient = theBlock.itsRadClient;
    itsRadIter = theBlock.itsRadIter;
    itsRadTmout = theBlock.itsRadTmout;
    itsDcnNat = theBlock.itsDcnNat;
    itsPriGneAddr = theBlock.itsPriGneAddr;
    itsSecGneAddr = theBlock.itsSecGneAddr;
    itsDcnRoutingConfig = theBlock.itsDcnRoutingConfig;

    return *this;
}
