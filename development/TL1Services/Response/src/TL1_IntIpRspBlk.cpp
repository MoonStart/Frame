/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Source file for TL1 Retrieve Internal IP Address Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_IntIpRspBlk.h>


TL1_IntIpRspBlk::TL1_IntIpRspBlk( const TL1_SmartParameter<CT_TL1_SlotAddr>& theSlotAddr,
                                  const TL1_SmartParameter<uint32>& theIpAddress ) :
    itsSlotAddr(theSlotAddr),
    itsIpAddress(theIpAddress)
{
}

TL1_IntIpRspBlk::~TL1_IntIpRspBlk()
{
}
  
TL1_IntIpRspBlk::TL1_IntIpRspBlk( const TL1_IntIpRspBlk& theBlock ) :
    itsSlotAddr(theBlock.itsSlotAddr),
    itsIpAddress(theBlock.itsIpAddress)
{
}

TL1_IntIpRspBlk& TL1_IntIpRspBlk::operator=( const TL1_IntIpRspBlk& theBlock )
{
    itsSlotAddr  = theBlock.itsSlotAddr;
    itsIpAddress = theBlock.itsIpAddress;

    return *this;
}

const TL1_SmartParameter<uint32>& TL1_IntIpRspBlk::GetIPAddress() const
{
    return itsIpAddress;
}

const TL1_SmartParameter<CT_TL1_SlotAddr>& TL1_IntIpRspBlk::GetSlotAddr() const
{
    return itsSlotAddr;
}

