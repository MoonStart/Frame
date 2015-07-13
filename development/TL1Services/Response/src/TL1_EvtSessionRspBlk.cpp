/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Report event session Response 
TARGET:
AUTHOR:         July 8, 2003- Christian Halle 
DESCRIPTION:    Source file for TL1 report event session Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_EvtSessionRspBlk.h>


TL1_EvtSessionRspBlk::TL1_EvtSessionRspBlk( const TL1_SmartParameter<string>& theTid,
                          const TL1_SmartParameter<string>& theUserId,
                          const TL1_SmartParameter<CT_TL1_LoginStatus>& theLoginStatus,	
#if defined VXWORKS67 || defined LINUX
                          const TL1_SmartParameter<string>& theSessionIPAddress,
#else
						  const TL1_SmartParameter<uint32>& theSessionIPAddress,
#endif
                          const TL1_SmartParameter<time_t>& theTime) :
	itsTid(theTid),
	itsUserId(theUserId),
	itsLoginStatus(theLoginStatus),
	itsSessionIPAddress(theSessionIPAddress),
	itsTime(theTime)
{
}

TL1_EvtSessionRspBlk::~TL1_EvtSessionRspBlk()
{
}
  
TL1_EvtSessionRspBlk::TL1_EvtSessionRspBlk(const TL1_EvtSessionRspBlk& theBlock) :
	itsTid(theBlock.itsTid),
	itsUserId(theBlock.itsUserId),
	itsLoginStatus(theBlock.itsLoginStatus),
	itsSessionIPAddress(theBlock.itsSessionIPAddress),
	itsTime(theBlock.itsTime)
{
}

TL1_EvtSessionRspBlk& TL1_EvtSessionRspBlk::operator=( const TL1_EvtSessionRspBlk& theBlock )
{
	itsTid = theBlock.itsTid;
	itsUserId = theBlock.itsUserId;
	itsLoginStatus = theBlock.itsLoginStatus;  
	itsSessionIPAddress = theBlock.itsSessionIPAddress;
	itsTime = theBlock.itsTime;

    return *this;
}
