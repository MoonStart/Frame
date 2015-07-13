/*--------------------------------------------------------------.0---------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 cross-connection Response 
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Retrive cross-connectioLAST REVISION:
   Date    Description
   ----    -----------
 10-15-08  t71mr00076507:Add response block for VCG cross-connect.  Add 'red 
           lined' as a unique attribute.
-----------------------------------------------------------------------------*/

#include <Response/TL1_CrsRspBlk.h>


TL1_CrsRspBlk::TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                             const TL1_SmartParameter<CT_XcType>& theType,
                             const TL1_SmartParameter<string>& theCircuitId,
                             const TL1_SmartParameter<CT_XcPathData>& thePathData, // includes from_cp_aid and to_cp_aid
                             const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theToAddrs,
                             const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theProtToAddrs,
                             const TL1_SmartParameter<string>& theGrpId,
                             const TL1_SmartParameter<bool>& theAutoCfg,
                             const TL1_SmartParameter<int>&  theNpOwner,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST) :
    itsAddr(theAddr),
    itsType(theType),
    itsCircuitId(theCircuitId),
    itsPathData(thePathData),
    itsToAddrs(theToAddrs),
    itsProtToAddrs(theProtToAddrs),
    itsGrpId(theGrpId),
    itsAutoCfg(theAutoCfg),
    itsNpOwner(theNpOwner),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)
{
}

TL1_CrsRspBlk::TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                             const TL1_SmartParameter<CT_XcType>& theType,
                             const TL1_SmartParameter<string>& theCircuitId,
                             const TL1_SmartParameter<CT_XcPathData>& thePathData, // includes from_cp_aid and to_cp_aid
                             const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theToAddrs,
                             const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theProtToAddrs,
                             const TL1_SmartParameter<CT_BRTA_ModeType>& theBrtaMode,
                             const TL1_SmartParameter<CT_TL1_CrsAddr>& theBrPair,
                             const TL1_SmartParameter<CT_TapNumber>& theTapNum,
                             const TL1_SmartParameter<bool>& theAutoCfg,
                             const TL1_SmartParameter<CT_SM_SST>&  theSrcProtStatus,
                             const TL1_SmartParameter<CT_SM_SST>&  theDstProtStatus,
                             const TL1_SmartParameter<CT_ProtGpType>&  theSrcProtType,
                             const TL1_SmartParameter<CT_ProtGpType>&  theDstProtType,
                             const TL1_SmartParameter<int>&  theNpOwner,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST) :
    itsAddr(theAddr),
    itsType(theType),
    itsCircuitId(theCircuitId),
    itsPathData(thePathData),
    itsToAddrs(theToAddrs),
    itsProtToAddrs(theProtToAddrs),
    itsBrtaMode(theBrtaMode),
    itsBrPair(theBrPair),
    itsTapNum(theTapNum),
    itsAutoCfg(theAutoCfg),
    itsSrcProtStatus(theSrcProtStatus),
    itsDstProtStatus(theDstProtStatus),
    itsSrcProtType(theSrcProtType),
    itsDstProtType(theDstProtType),
    itsNpOwner(theNpOwner),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)
{
}

TL1_CrsRspBlk::TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                             const TL1_SmartParameter<CT_SM_PST>&  thePST,
                             const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                             const TL1_SmartParameter<CT_SM_SST>&  theSST) :
    itsAddr(theAddr),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)
{
}

TL1_CrsRspBlk::TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                             const TL1_SmartParameter<CT_XcType>& theType,
                             const TL1_SmartParameter<string>& theCircuitId,
                             const TL1_SmartParameter<CT_XcPathData>& thePathData) :
    itsAddr(theAddr),
    itsType(theType),
    itsCircuitId(theCircuitId),
    itsPathData(thePathData)
{
}


/* Used for: RTRV-CRS-VCG */
TL1_CrsRspBlk::TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                  const TL1_SmartParameter<CT_XcType>& theType,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<bool>& theRedLined ) :
    itsAddr(theAddr),
    itsType(theType),
    itsCircuitId(theCircuitId),
    itsRedLined(theRedLined)
{
}


TL1_CrsRspBlk::~TL1_CrsRspBlk()
{
}
  
TL1_CrsRspBlk::TL1_CrsRspBlk(const TL1_CrsRspBlk& theBlock) :
    itsAddr(theBlock.itsAddr),
    itsType(theBlock.itsType),
    itsCircuitId(theBlock.itsCircuitId),
    itsPathData(theBlock.itsPathData),
    itsToAddrs(theBlock.itsToAddrs),
    itsProtToAddrs(theBlock.itsProtToAddrs),
    itsBrtaMode(theBlock.itsBrtaMode),
    itsBrPair(theBlock.itsBrPair),
    itsTapNum(theBlock.itsTapNum),
    itsGrpId(theBlock.itsGrpId),
    itsAutoCfg(theBlock.itsAutoCfg),
    itsSrcProtStatus(theBlock.itsSrcProtStatus),
    itsDstProtStatus(theBlock.itsDstProtStatus),
    itsSrcProtType(theBlock.itsSrcProtType),
    itsDstProtType(theBlock.itsDstProtType),
    itsNpOwner(theBlock.itsNpOwner),
    itsRedLined(theBlock.itsRedLined),
    itsPST(theBlock.itsPST),
    itsPSTQ(theBlock.itsPSTQ),
    itsSST(theBlock.itsSST)
{
}

TL1_CrsRspBlk& TL1_CrsRspBlk::operator=( const TL1_CrsRspBlk& theBlock )
{
    itsAddr=            theBlock.itsAddr;
    itsType=            theBlock.itsType;
    itsCircuitId=       theBlock.itsCircuitId;
    itsPathData=        theBlock.itsPathData;
    itsToAddrs=         theBlock.itsToAddrs;
    itsProtToAddrs=     theBlock.itsProtToAddrs;
    itsBrtaMode=        theBlock.itsBrtaMode;
    itsBrPair=          theBlock.itsBrPair;
    itsTapNum=          theBlock.itsTapNum;
    itsGrpId=           theBlock.itsGrpId;
    itsAutoCfg=         theBlock.itsAutoCfg;
    itsSrcProtStatus=   theBlock.itsSrcProtStatus;
    itsDstProtStatus=   theBlock.itsDstProtStatus;
    itsSrcProtType=     theBlock.itsSrcProtType;
    itsDstProtType=     theBlock.itsDstProtType;
    itsNpOwner=         theBlock.itsNpOwner;
    itsRedLined=        theBlock.itsRedLined;
    itsPST=             theBlock.itsPST;
    itsPSTQ=            theBlock.itsPSTQ;
    itsSST=             theBlock.itsSST;
    return *this;
}

bool TL1_CrsRspBlk::operator==( const TL1_CrsRspBlk& theBlock ) const
{
    return ( itsAddr            == theBlock.itsAddr &&
             itsType            == theBlock.itsType &&
             itsCircuitId       == theBlock.itsCircuitId &&
             itsPathData        == theBlock.itsPathData &&
             itsToAddrs         == theBlock.itsToAddrs &&
             itsProtToAddrs     == theBlock.itsProtToAddrs &&
             itsBrtaMode        == theBlock.itsBrtaMode &&
             itsBrPair          == theBlock.itsBrPair &&
             itsTapNum          == theBlock.itsTapNum &&
             itsGrpId           == theBlock.itsGrpId &&
             itsAutoCfg         == theBlock.itsAutoCfg &&
             itsSrcProtStatus   == theBlock.itsSrcProtStatus &&
             itsDstProtStatus   == theBlock.itsDstProtStatus &&
             itsSrcProtType     == theBlock.itsSrcProtType &&
             itsDstProtType     == theBlock.itsDstProtType &&
             itsNpOwner         == theBlock.itsNpOwner &&
             itsRedLined        == theBlock.itsRedLined &&
             itsPST             == theBlock.itsPST &&
             itsPSTQ            == theBlock.itsPSTQ &&
             itsSST             == theBlock.itsSST );
}

bool TL1_CrsRspBlk::operator<( const TL1_CrsRspBlk& theBlock ) const
{
    if (GetAddr().GetValue().GetFromAddr() < theBlock.GetAddr().GetValue().GetFromAddr())
    {
        return true;
    }
    else if (GetAddr().GetValue().GetFromAddr() == theBlock.GetAddr().GetValue().GetFromAddr())
    {
        if (GetAddr().GetValue().GetToAddr() < theBlock.GetAddr().GetValue().GetToAddr())
        {
            return true;
        }
    }
    return false;
}
