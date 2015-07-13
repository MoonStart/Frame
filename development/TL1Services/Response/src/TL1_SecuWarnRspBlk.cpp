/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         Feb. 7, 2005- Maggie Zhang 
DESCRIPTION:    Source file for TL1 Retrive Warning Message Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SecuWarnRspBlk.h>


TL1_SecuWarnRspBlk::TL1_SecuWarnRspBlk(const TL1_SmartParameter<string>& theWarnMesg):                             

    itsWarningMesg(theWarnMesg)
{
}

TL1_SecuWarnRspBlk::~TL1_SecuWarnRspBlk()
{
}
  
TL1_SecuWarnRspBlk::TL1_SecuWarnRspBlk(const TL1_SecuWarnRspBlk& theBlock) :
    itsWarningMesg(theBlock.itsWarningMesg)
{
}

TL1_SecuWarnRspBlk& TL1_SecuWarnRspBlk::operator=( const TL1_SecuWarnRspBlk& theBlock )
{
    itsWarningMesg= theBlock.itsWarningMesg;
    return *this;
}