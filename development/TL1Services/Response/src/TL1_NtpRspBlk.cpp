/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Slot Response 
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Retrive NTP Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_NtpRspBlk.h>


TL1_NtpRspBlk::TL1_NtpRspBlk(const TL1_SmartParameter<string>&             theEntityName,
                             const TL1_SmartParameter<CT_TL1_LogicalAddr>& theNtpAddr,
                             const TL1_SmartParameter<string>&             thePeerIP,
                             const TL1_SmartParameter<string>&             thePeerDescription,
                             const TL1_SmartParameter<int>&                theVersion,
                             const TL1_SmartParameter<int>&                thePort,
                             const TL1_SmartParameter<CT_NtpMode>&         theHostMode,
                             const TL1_SmartParameter<uint16>&             thePollingInterval,
                             const TL1_SmartParameter<uint8>&              theStratum,
                             const TL1_SmartParameter<float>&              thePrecision,
                             const TL1_SmartParameter<bool>&               theReachability,
                             const TL1_SmartParameter<float>&              theDelay,
                             const TL1_SmartParameter<float>&              theDispersion,
                             const TL1_SmartParameter<float>&              theRootDelay,
                             const TL1_SmartParameter<float>&              theRootDispersion,
                             const TL1_SmartParameter<CT_SM_PST>&          thePst,
                             const TL1_SmartParameter<CT_SM_PSTQ>&         thePstq,
                             const TL1_SmartParameter<CT_SM_SST>&          theSst,
                             const TL1_SmartParameter<CT_NtpPeerConfigType>& thePeerConfigMode ) :

    itsEntityName(theEntityName),
    itsNtpAddr(theNtpAddr),
    itsPeerIP(thePeerIP),
    itsPeerDescription(thePeerDescription),
    itsVersion(theVersion),
    itsPort(thePort),
    itsHostMode(theHostMode),
    itsPollingInterval(thePollingInterval),
    itsStratum(theStratum),
    itsPrecision(thePrecision),
    itsReachability(theReachability),
    itsDelay(theDelay),
    itsDispersion(theDispersion),
    itsRootDelay(theRootDelay),
    itsRootDispersion(theRootDispersion),
    itsPst(thePst),
    itsPstq(thePstq),
    itsSst(theSst),
    itsPeerConfigMode(thePeerConfigMode)
{
}

TL1_NtpRspBlk::~TL1_NtpRspBlk()
{
}
  
TL1_NtpRspBlk::TL1_NtpRspBlk(const TL1_NtpRspBlk& theBlock) :
    itsEntityName(theBlock.itsEntityName),
    itsNtpAddr(theBlock.itsNtpAddr),
    itsPeerIP(theBlock.itsPeerIP),
    itsPeerDescription(theBlock.itsPeerDescription),
    itsVersion(theBlock.itsVersion),
    itsPort(theBlock.itsPort),
    itsHostMode(theBlock.itsHostMode),
    itsPollingInterval(theBlock.itsPollingInterval),
    itsStratum(theBlock.itsStratum),
    itsPrecision(theBlock.itsPrecision),
    itsReachability(theBlock.itsReachability),
    itsDelay(theBlock.itsDelay),
    itsDispersion(theBlock.itsDispersion),
    itsRootDelay(theBlock.itsRootDelay),
    itsRootDispersion(theBlock.itsRootDispersion),
    itsPst(theBlock.itsPst),
    itsPstq(theBlock.itsPstq),
    itsSst(theBlock.itsSst),
    itsPeerConfigMode(theBlock.itsPeerConfigMode)
{
}

TL1_NtpRspBlk::TL1_NtpRspBlk() :
    itsEntityName(""),
    itsNtpAddr(0),
    itsPeerIP(""),
    itsPeerDescription(""),
    itsVersion(0),
    itsPort(0),
    itsHostMode((CT_NtpMode) 0),
    itsPollingInterval((uint16) 0),
    itsStratum((uint8) 0),
    itsPrecision((float) 0),
    itsReachability(false),
    itsDelay((float) 0),
    itsDispersion((float) 0),
    itsRootDelay((float) 0),
    itsRootDispersion((float) 0),
    itsPst(CT_SM_PST_NCRT),
    itsPstq(CT_SM_PSTQ_DNE),
    itsSst(CT_SM_SST_UAS),
    itsPeerConfigMode(NTP_PEER_CONFIG_MANUAL)
{
}

TL1_NtpRspBlk& TL1_NtpRspBlk::operator=( const TL1_NtpRspBlk& theBlock )
{
    itsEntityName=      theBlock.itsEntityName;
    itsNtpAddr=         theBlock.itsNtpAddr;
    itsPeerIP=          theBlock.itsPeerIP;
    itsPeerDescription= theBlock.itsPeerDescription;
    itsVersion=         theBlock.itsVersion;
    itsPort=            theBlock.itsPort;
    itsHostMode=        theBlock.itsHostMode;
    itsPollingInterval= theBlock.itsPollingInterval;
    itsStratum=         theBlock.itsStratum;
    itsPrecision=       theBlock.itsPrecision;
    itsReachability=    theBlock.itsReachability;
    itsDelay=           theBlock.itsDelay;
    itsDispersion=      theBlock.itsDispersion;
    itsRootDelay=       theBlock.itsRootDelay;
    itsRootDispersion=  theBlock.itsRootDispersion;
    itsPst=             theBlock.itsPst;
    itsPstq=            theBlock.itsPstq;
    itsSst=             theBlock.itsSst;
    itsPeerConfigMode = theBlock.itsPeerConfigMode;

    return *this;
}

bool TL1_NtpRspBlk::operator==( const TL1_NtpRspBlk& theBlock )
{
    return (itsEntityName       == theBlock.itsEntityName &&
            itsNtpAddr          == theBlock.itsNtpAddr &&
            itsPeerIP           == theBlock.itsPeerIP &&
            itsPeerDescription  == theBlock.itsPeerDescription &&
            itsVersion          == theBlock.itsVersion &&
            itsPort             == theBlock.itsPort &&
            itsHostMode         == theBlock.itsHostMode &&
            itsStratum          == theBlock.itsStratum &&
            itsReachability     == theBlock.itsReachability &&
            itsPst              == theBlock.itsPst &&
            itsPstq             == theBlock.itsPstq &&
            itsSst              == theBlock.itsSst &&
            itsPeerConfigMode   == theBlock.itsPeerConfigMode); 
}

bool TL1_NtpRspBlk::operator!=( const TL1_NtpRspBlk& theBlock )
{
    return (!(*this == theBlock)); 
}
