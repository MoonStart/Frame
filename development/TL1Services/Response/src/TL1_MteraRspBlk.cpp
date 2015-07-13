/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Mtera Response 
TARGET:
AUTHOR:        2013.11.8- Gang zhu
DESCRIPTION:    Source file for TL1 Retrive mtera Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_MteraRspBlk.h>


TL1_MTERARspBlk::TL1_MTERARspBlk(const TL1_SmartParameter<uint32>& theLocalIf,
                   const TL1_SmartParameter<uint32>& theLocalIfMask,
                   const TL1_SmartParameter<uint32>& theLocalIfGtw
                   ) : 
    itsLocalIf(theLocalIf),
    itsLocalIfMask(theLocalIfMask),
    itsLocalIfGtw(theLocalIfGtw)
{
}

TL1_MTERARspBlk::~TL1_MTERARspBlk()
{
}
  
TL1_MTERARspBlk::TL1_MTERARspBlk(const TL1_MTERARspBlk& theBlock) :
    itsLocalIf(theBlock.itsLocalIf),
    itsLocalIfMask(theBlock.itsLocalIfMask),
    itsLocalIfGtw(theBlock.itsLocalIfGtw)   
{
}

TL1_MTERARspBlk& TL1_MTERARspBlk::operator=( const TL1_MTERARspBlk& theBlock )
{
    itsLocalIf = theBlock.itsLocalIf;
    itsLocalIfMask = theBlock.itsLocalIfMask;
    itsLocalIfGtw = theBlock.itsLocalIfGtw;
   
    return *this;
}

