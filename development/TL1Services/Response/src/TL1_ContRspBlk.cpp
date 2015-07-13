/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         Oct 5, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Environment Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_ContRspBlk.h>


TL1_ContRspBlk::TL1_ContRspBlk( const TL1_SmartParameter<CT_TL1_LogicalAddr>& theAddr,
                                    const TL1_SmartParameter<CT_ContType>& theType,
                                    const TL1_SmartParameter<CT_ContDuration>& theDuration,
                                    const TL1_SmartParameter<CT_ContState>& theState  ) :
    itsAddr(theAddr),
    itsType(theType),
    itsDuration(theDuration),    
    itsState(theState)
{
}

TL1_ContRspBlk::~TL1_ContRspBlk()
{
}
  
TL1_ContRspBlk::TL1_ContRspBlk( const TL1_ContRspBlk& theBlock ) :
    itsAddr(theBlock.itsAddr),
    itsType(theBlock.itsType),
    itsDuration(theBlock.itsDuration),    
    itsState(theBlock.itsState)
{
}

TL1_ContRspBlk& TL1_ContRspBlk::operator=( const TL1_ContRspBlk& theBlock )
{
    itsAddr = theBlock.itsAddr;
    itsType = theBlock.itsType;
    itsDuration = theBlock.itsDuration;  
    itsState = theBlock.itsState;

    return *this;
}

const TL1_SmartParameter<CT_TL1_LogicalAddr>& TL1_ContRspBlk::GetAddr() const
{
    return itsAddr;
}

const TL1_SmartParameter<CT_ContType>& TL1_ContRspBlk::GetType() const
{
    return itsType;
}

const TL1_SmartParameter<CT_ContDuration>& TL1_ContRspBlk::GetDuration() const
{
    return itsDuration;
}

const TL1_SmartParameter<CT_ContState>& TL1_ContRspBlk::GetState() const
{
    return itsState;
}

