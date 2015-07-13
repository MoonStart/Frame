/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Slot Response 
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Retrive Slot Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SlotRspBlk.h>


TL1_SlotRspBlk::TL1_SlotRspBlk(const TL1_SmartParameter<string>& theEntityName,
                               const TL1_SmartParameter<CT_TL1_SlotAddr>& theSlotAddr,
                               const TL1_SmartParameter<CT_AcceptableCpList>& thePartNumberList,
                               const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile,
                               const TL1_SmartParameter<CT_SM_PST>&  thePST,
                               const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                               const TL1_SmartParameter<CT_SM_SST>&  theSST) :
    itsEntityName(theEntityName),
    itsSlotAddr(theSlotAddr),
    itsPartNumberList(thePartNumberList),
    itsAlarmProfile(theAlarmProfile),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)

{
}

TL1_SlotRspBlk::~TL1_SlotRspBlk()
{
}
  
TL1_SlotRspBlk::TL1_SlotRspBlk(const TL1_SlotRspBlk& theBlock) :
    itsEntityName(theBlock.itsEntityName),
    itsSlotAddr(theBlock.itsSlotAddr),
    itsPartNumberList(theBlock.itsPartNumberList),
    itsAlarmProfile(theBlock.itsAlarmProfile),
    itsPST(theBlock.itsPST),
    itsPSTQ(theBlock.itsPSTQ),
    itsSST(theBlock.itsSST)
{
}

TL1_SlotRspBlk& TL1_SlotRspBlk::operator=( const TL1_SlotRspBlk& theBlock )
{
    itsEntityName=     theBlock.itsEntityName;
    itsSlotAddr=       theBlock.itsSlotAddr;
    itsPartNumberList= theBlock.itsPartNumberList;
    itsAlarmProfile=   theBlock.itsAlarmProfile;
    itsPST=            theBlock.itsPST;
    itsPSTQ=           theBlock.itsPSTQ;
    itsSST=            theBlock.itsSST;

    return *this;
}

bool TL1_SlotRspBlk::operator==( const TL1_SlotRspBlk& theBlock ) const
{
    return ( itsEntityName==     theBlock.itsEntityName &&
             itsSlotAddr==       theBlock.itsSlotAddr &&
             itsPartNumberList== theBlock.itsPartNumberList &&
             itsAlarmProfile==   theBlock.itsAlarmProfile &&
             itsPST==            theBlock.itsPST &&
             itsPSTQ==           theBlock.itsPSTQ &&
             itsSST==            theBlock.itsSST );
}