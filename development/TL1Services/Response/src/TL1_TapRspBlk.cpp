/*--------------------------------------------------------------.0---------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 cross-connection Response 
TARGET:
AUTHOR:         October 2006- Brian Clever
DESCRIPTION:    Source file for TL1 TAP Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_TapRspBlk.h>
#include <Response/TL1_SmartParameter.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_XcTypes.h>

TL1_TapRspBlk::TL1_TapRspBlk(const TL1_SmartParameter<CT_TL1_FacAddr>& theEQAddr,
                             const TL1_SmartParameter<CT_XcFacType>& theEQType,
                             const TL1_SmartParameter<CT_TL1_FacAddr>& theFAAddr,
                             const TL1_SmartParameter<CT_XcFacType>& theFAType,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST) :
    itsEQTapAddr(theEQAddr),
    itsEQType(theEQType),
    itsFATapAddr(theFAAddr),
    itsFAType(theFAType),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)
{
}


/*

TL1_TapRspBlk::~TL1_TapRspBlk()
{
}
  
TL1_TapRspBlk::TL1_TapRspBlk(const TL1_TapRspBlk& theBlock) :
    itsEQTapAddr(theBlock.itsEQTapAddr),
    itsEQType(theBlock.itsEQType),
    itsFATapAddr(theBlock.itsFATapAddr),
    itsFAType(theBlock.itsFAType),
    itsPST(theBlock.itsPST),
    itsPSTQ(theBlock.itsPSTQ),
    itsSST(theBlock.itsSST)
{
}

TL1_CrsRspBlk& TL1_CrsRspBlk::operator=( const TL1_TapRspBlk& theBlock )
{
    itsEQTapAddr=       theBlock.itsEQTapAddr;
    itsEQType=            theBlock.itsEQType;
    itsFATapAddr=       theBlock.itsFATapAddr;
    itsFAType=            theBlock.itsType;
    itsPST=             theBlock.itsPST;
    itsPSTQ=            theBlock.itsPSTQ;
    itsSST=             theBlock.itsSST;
    return *this;
}

bool TL1_CrsRspBlk::operator==( const TL1_TapRspBlk& theBlock ) const
{
    return ( itsEQTapAddr       == theBlock.itsEQTapAddr &&
             itsEQType          == theBlock.itsEQType &&
             itsFATapAddr       == theBlock.itsFATapAddr &&
             itsFAType          == theBlock.itsFAType &&
             itsPST             == theBlock.itsPST &&
             itsPSTQ            == theBlock.itsPSTQ &&
             itsSST             == theBlock.itsSST );
}

*/