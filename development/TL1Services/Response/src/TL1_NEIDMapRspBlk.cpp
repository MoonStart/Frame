/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 NEIDMap Response 
TARGET:
AUTHOR:         Jun 22, 2009- Lei Cao
DESCRIPTION:    Source file for TL1 Retrive NEIDMap Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_NEIDMapRspBlk.h>


TL1_NEIDMapRspBlk::TL1_NEIDMapRspBlk(const TL1_SmartParameter<CT_ShelfId>& theShelfNumber,
                            const TL1_SmartParameter<uint32> theIPAddress,
                            const TL1_SmartParameter<string> theTid,
                            const TL1_SmartParameter<string> theEngineid,
                            const TL1_SmartParameter<CT_ProdType> theProdType,
                            const TL1_SmartParameter<CT_LinkInfo> theLink,
                            const TL1_SmartParameter<bool> theMode):
	itsTid(theTid),
	itsIPAddress(theIPAddress),
	itsMode(theMode),
	itsEngineid(theEngineid),
	itsProdType(theProdType),
	itsLink(theLink),
	itsShelfNumber(theShelfNumber)

{
}

TL1_NEIDMapRspBlk::~TL1_NEIDMapRspBlk()
{
}
  
TL1_NEIDMapRspBlk::TL1_NEIDMapRspBlk(const TL1_NEIDMapRspBlk& theBlock) :
	itsTid(theBlock.itsTid),
	itsIPAddress(theBlock.itsIPAddress),
	itsMode(theBlock.itsMode),
	itsEngineid(theBlock.itsEngineid),
	itsShelfNumber(theBlock.itsShelfNumber),
	itsLink(theBlock.itsLink),
	itsProdType(theBlock.itsProdType)
{
}

TL1_NEIDMapRspBlk& TL1_NEIDMapRspBlk::operator=( const TL1_NEIDMapRspBlk& theBlock )
{
	itsTid = theBlock.itsTid;
	itsIPAddress = theBlock.itsIPAddress;
	itsMode = theBlock.itsMode;
	itsEngineid = theBlock.itsEngineid;
	itsShelfNumber = theBlock.itsShelfNumber;
	itsProdType = theBlock.itsProdType;
	itsLink= theBlock.itsLink;

    return *this;
}
