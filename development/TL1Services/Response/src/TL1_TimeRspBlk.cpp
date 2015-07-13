/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 TOD Response 
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Retrive TOD Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_TimeRspBlk.h>


TL1_TodRspBlk::TL1_TodRspBlk(const TL1_SmartParameter<CT_TimeTm>&   theUTCDateAndTime,
                             const TL1_SmartParameter<int>&         theTimeSubSeconds,
                             const TL1_SmartParameter<string>&      theTimeSource,
                             const TL1_SmartParameter<string>&      theAlternalteTimeSource,
                             const TL1_SmartParameter<CT_SM_State>& theState ) :

    itsUTCDateAndTime(theUTCDateAndTime),
    itsTimeSubSeconds(theTimeSubSeconds),
    itsTimeSource(theTimeSource),
    itsAlternalteTimeSource(theAlternalteTimeSource),
    itsState(theState)
{
}

TL1_TodRspBlk::~TL1_TodRspBlk()
{
}
  
TL1_TodRspBlk::TL1_TodRspBlk(const TL1_TodRspBlk& theBlock) :
    itsUTCDateAndTime(theBlock.itsUTCDateAndTime),
    itsTimeSubSeconds(theBlock.itsTimeSubSeconds),
    itsTimeSource(theBlock.itsTimeSource),
    itsAlternalteTimeSource(theBlock.itsAlternalteTimeSource),
    itsState(theBlock.itsState)
{
}

TL1_TodRspBlk& TL1_TodRspBlk::operator=( const TL1_TodRspBlk& theBlock )
{
    itsUTCDateAndTime=       theBlock.itsUTCDateAndTime;
    itsTimeSubSeconds=       theBlock.itsTimeSubSeconds;
    itsTimeSource=           theBlock.itsTimeSource;
    itsAlternalteTimeSource= theBlock.itsAlternalteTimeSource;
    itsState=                theBlock.itsState;

    return *this;
}