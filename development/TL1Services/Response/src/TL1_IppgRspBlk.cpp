/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Mtera Response 
TARGET:
AUTHOR:        2013.11.8- Gang zhu
DESCRIPTION:    Source file for TL1 Retrive mtera Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_IppgRspBlk.h>


TL1_IppgRspBlk::TL1_IppgRspBlk(const TL1_SmartParameter<string>& theIfAid,
                   const TL1_SmartParameter<string>& theIfName,
                   const TL1_SmartParameter<string>& theIppgMems,
                   const TL1_SmartParameter<string>& theActiveMem,
                   const TL1_SmartParameter<LT_PrimaryState>& thePrimaryState) : 
    myIfAid(theIfAid),
    myIfName(theIfName),
    myIppgMems(theIppgMems),
    myActiveMem(theActiveMem),
    myPrimaryState(thePrimaryState)
{
}
  
TL1_IppgRspBlk::TL1_IppgRspBlk(const TL1_IppgRspBlk& theBlock) :
    myIfAid(theBlock.myIfAid),
    myIfName(theBlock.myIfName),
    myIppgMems(theBlock.myIppgMems),
    myActiveMem(theBlock.myActiveMem),
    myPrimaryState(theBlock.myPrimaryState)      
{
}

TL1_IppgRspBlk::~TL1_IppgRspBlk()
{
}

TL1_IppgRspBlk& TL1_IppgRspBlk::operator=( const TL1_IppgRspBlk& theBlock )
{
    myIfAid = theBlock.myIfAid;
    myIfName = theBlock.myIfName;
    myIppgMems = theBlock.myIppgMems;
    myActiveMem = theBlock.myActiveMem;
    myPrimaryState = theBlock.myPrimaryState;
   
    return *this;
}


const TL1_SmartParameter<string>& TL1_IppgRspBlk::GetIfAid() const
{
    return myIfAid;
}

const TL1_SmartParameter<string>& TL1_IppgRspBlk::GetIfName() const
{
    return myIfName;
}

const TL1_SmartParameter<string>& TL1_IppgRspBlk::GetIfIppgMems() const
{
    return myIppgMems;
}

const TL1_SmartParameter<string>& TL1_IppgRspBlk::GetIfActiveMem() const
{
    return myActiveMem;
}

const TL1_SmartParameter<LT_PrimaryState>& TL1_IppgRspBlk::GetPrimaryState() const
{
    return myPrimaryState;
}
