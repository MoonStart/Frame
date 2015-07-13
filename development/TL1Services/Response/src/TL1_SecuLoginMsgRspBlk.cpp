/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         April 11, 2006 - Michael Kreger 
DESCRIPTION:    Source file for TL1 Retrive Warning Message Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SecuLoginMsgRspBlk.h>


TL1_SecuLoginMsgRspBlk::TL1_SecuLoginMsgRspBlk(const TL1_SmartParameter<string>& theLoginMesg):                             

    itsLoginMesg(theLoginMesg)
{
}

TL1_SecuLoginMsgRspBlk::~TL1_SecuLoginMsgRspBlk()
{
}
  
TL1_SecuLoginMsgRspBlk::TL1_SecuLoginMsgRspBlk(const TL1_SecuLoginMsgRspBlk& theBlock) :
    itsLoginMesg(theBlock.itsLoginMesg)
{
}

TL1_SecuLoginMsgRspBlk& TL1_SecuLoginMsgRspBlk::operator=( const TL1_SecuLoginMsgRspBlk& theBlock )
{
    itsLoginMesg= theBlock.itsLoginMesg;
    return *this;
}