/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 DcnEthPort Response 
TARGET:
AUTHOR:        2014.12.29 - Gang zhu
DESCRIPTION:    Source file for TL1 Retrive DcnEthPort Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_DcnEthPortRspBlk.h>


TL1_DcnEthPortRspBlk::TL1_DcnEthPortRspBlk(const TL1_SmartParameter<CT_DCNETHPORTType>& theIfname,
                   const TL1_SmartParameter<bool>& theIfstate,const TL1_SmartParameter<bool>& theZtcstate) : 
    itsIfname(theIfname),
    itsIfstate(theIfstate),
    itsZtcstate(theZtcstate)
{
}

TL1_DcnEthPortRspBlk::~TL1_DcnEthPortRspBlk()
{
}
  
TL1_DcnEthPortRspBlk::TL1_DcnEthPortRspBlk(const TL1_DcnEthPortRspBlk& theBlock) :
    itsIfname(theBlock.itsIfname),
    itsIfstate(theBlock.itsIfstate),
    itsZtcstate(theBlock.itsZtcstate)
{
}

TL1_DcnEthPortRspBlk& TL1_DcnEthPortRspBlk::operator=( const TL1_DcnEthPortRspBlk& theBlock )
{
    itsIfname = theBlock.itsIfname;
    itsIfstate = theBlock.itsIfstate;
    itsZtcstate = theBlock.itsZtcstate;
   
    return *this;
}

