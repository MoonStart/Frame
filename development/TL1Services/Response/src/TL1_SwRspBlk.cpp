/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 SW Response 
TARGET:
AUTHOR:         Aug 11, 2003- Christian Halle 
DESCRIPTION:    Source file for TL1 Retrive SW Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SwRspBlk.h>


TL1_RtrvSwRspBlk::TL1_RtrvSwRspBlk(const TL1_SmartParameter<string>&             theVendor,
                           const TL1_SmartParameter<string>&             theSwType,
                           const TL1_SmartParameter<string>&             theSwVersion,
                           const TL1_SmartParameter<string>&             thePatchLevel,
                           const TL1_SmartParameter<string>&             theSwContext,
                           const TL1_SmartParameter<int>&                theSize,
                           const TL1_SmartParameter<string>&             theLocation,
                           const TL1_SmartParameter<string>&             theLastUpdate,
                           const TL1_SmartParameter<string>&             thePath,
                           const TL1_SmartParameter<CT_SM_PST>&          thePst,
                           const TL1_SmartParameter<CT_SM_PSTQ>&         thePstq,
                           const TL1_SmartParameter<CT_SM_SST>&          theSst ) :

    itsVendor(theVendor),
    itsSwType(theSwType),
    itsSwVersion(theSwVersion),
    itsPatchLevel(thePatchLevel),
    itsSwContext(theSwContext),
    itsSize(theSize),
    itsLocation(theLocation),
    itsLastUpdate(theLastUpdate),
    itsPath(thePath),
    itsPst(thePst),
    itsPstq(thePstq),
    itsSst(theSst)
{
}

TL1_RtrvSwRspBlk::~TL1_RtrvSwRspBlk()
{
}
  
TL1_RtrvSwRspBlk::TL1_RtrvSwRspBlk(const TL1_RtrvSwRspBlk& theBlock) :
    itsVendor(theBlock.itsVendor),
    itsSwType(theBlock.itsSwType),
    itsSwVersion(theBlock.itsSwVersion),
    itsPatchLevel(theBlock.itsPatchLevel),
    itsSwContext(theBlock.itsSwContext),
    itsSize(theBlock.itsSize),
    itsLocation(theBlock.itsLocation),
    itsLastUpdate(theBlock.itsLastUpdate),
    itsPath(theBlock.itsPath),
    itsPst(theBlock.itsPst),
    itsPstq(theBlock.itsPstq),
    itsSst(theBlock.itsSst)
{
}

TL1_RtrvSwRspBlk& TL1_RtrvSwRspBlk::operator=( const TL1_RtrvSwRspBlk& theBlock )
{
    itsVendor=     theBlock.itsVendor;
    itsSwType=     theBlock.itsSwType;
    itsSwVersion=  theBlock.itsSwVersion;
    itsPatchLevel= theBlock.itsPatchLevel;
    itsSwContext=  theBlock.itsSwContext;
    itsSize=       theBlock.itsSize;
    itsLocation=   theBlock.itsLocation;
    itsLastUpdate= theBlock.itsLastUpdate;
    itsPath=       theBlock.itsPath;
    itsPst=        theBlock.itsPst;
    itsPstq=       theBlock.itsPstq;
    itsSst=        theBlock.itsSst;

    return *this;
}
