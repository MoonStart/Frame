/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         Feb. 24, 2009- Crystal Guo
DESCRIPTION:    Source file for Retreive Radius Server Response class declaration
-----------------------------------------------------------------------------*/

#include <Response/TL1_RadiusServerRspBlk.h>


TL1_RadServerRspBlk::TL1_RadServerRspBlk(const TL1_SmartParameter<string>&  theRadServer,
                                         const TL1_SmartParameter<uint32>&  theIpAddr,
                                         const TL1_SmartParameter<string>&  theIpStr,
                                         const TL1_SmartParameter<string>&  theSharedSecret) :
    itsRadServer(theRadServer),
    itsIpAddr(theIpAddr),
    itsIpStr(theIpStr),    
    itsSharedSecret(theSharedSecret)
{
}

TL1_RadServerRspBlk::TL1_RadServerRspBlk(const TL1_RadServerRspBlk& theBlock) :
    itsRadServer(theBlock.itsRadServer),
    itsIpAddr(theBlock.itsIpAddr),
    itsIpStr(theBlock.itsIpStr),
    itsSharedSecret(theBlock.itsSharedSecret)
{
}

TL1_RadServerRspBlk& TL1_RadServerRspBlk::operator=( const TL1_RadServerRspBlk& theBlock )
{
    itsRadServer    = theBlock.itsRadServer;
    itsIpAddr       = theBlock.itsIpAddr;
    itsIpStr        = theBlock.itsIpStr;
    itsSharedSecret = theBlock.itsSharedSecret;
    
    return *this;
}