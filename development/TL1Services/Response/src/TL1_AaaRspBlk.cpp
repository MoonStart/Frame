/*-----------------------------------------------------------------------------
   Copyright(c) Coriant Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 
TARGET:
AUTHOR   :      Apr 2015 - Gang Sun
DESCRIPTION:    Source file for Retreive AAA Server Response class declaration
-----------------------------------------------------------------------------*/

#include <Response/TL1_AaaRspBlk.h>


TL1_AaaRspBlk::TL1_AaaRspBlk(const TL1_SmartParameter<uint32>&  theIpAddr,
                                         const TL1_SmartParameter<string>&  theIpStr,
                                         const TL1_SmartParameter<string>&  theSharedSecret,
                                         const TL1_SmartParameter<CT_AaaProto>&  theProto,
                                         const TL1_SmartParameter<CT_AaaRole>&  theRole,
                                         const TL1_SmartParameter<int>&  theTimeout,
                                         const TL1_SmartParameter<int>&  theRetry) :
    itsIpAddr(theIpAddr),
    itsIpStr(theIpStr),    
    itsSharedSecret(theSharedSecret),
    itsProto(theProto),
    itsRole(theRole),
    itsTimeout(theTimeout),
    itsRetry(theRetry)
{
}

TL1_AaaRspBlk::TL1_AaaRspBlk(const TL1_AaaRspBlk& theBlock) :
    itsIpAddr(theBlock.itsIpAddr),
    itsIpStr(theBlock.itsIpStr),
    itsSharedSecret(theBlock.itsSharedSecret),
    itsProto(theBlock.itsProto),
    itsRole(theBlock.itsRole),
    itsTimeout(theBlock.itsTimeout),
    itsRetry(theBlock.itsRetry)
{
}

TL1_AaaRspBlk& TL1_AaaRspBlk::operator=( const TL1_AaaRspBlk& theBlock )
{
    itsIpAddr       = theBlock.itsIpAddr;
    itsIpStr        = theBlock.itsIpStr;
    itsSharedSecret = theBlock.itsSharedSecret;
    itsProto        = theBlock.itsProto;
    itsRole         = theBlock.itsRole;
    itsTimeout      = theBlock.itsTimeout;
    itsRetry        = theBlock.itsRetry;
    
    return *this;
}