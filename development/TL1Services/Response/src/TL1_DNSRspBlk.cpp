/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 NET Response 
TARGET:
AUTHOR:         Jun 5, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Retrive DNS Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_DNSRspBlk.h>


TL1_DNSRspBlk::TL1_DNSRspBlk( const TL1_SmartParameter<string>& theTid,
						      const TL1_SmartParameter<uint32>& theIPAddress,
                        const TL1_SmartParameter<bool>& theRneMode) :
	itsTid(theTid),
	itsIPAddress(theIPAddress),
	itsRneMode(theRneMode)
{
}

TL1_DNSRspBlk::~TL1_DNSRspBlk()
{
}
  
TL1_DNSRspBlk::TL1_DNSRspBlk(const TL1_DNSRspBlk& theBlock) :
	itsTid(theBlock.itsTid),
	itsIPAddress(theBlock.itsIPAddress),
	itsRneMode(theBlock.itsRneMode)
{
}

TL1_DNSRspBlk& TL1_DNSRspBlk::operator=( const TL1_DNSRspBlk& theBlock )
{
	itsTid = theBlock.itsTid;
	itsIPAddress = theBlock.itsIPAddress;
	itsRneMode = theBlock.itsRneMode;

    return *this;
}
