/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 NEType Response 
TARGET:
AUTHOR:         Aug 11, 2003- Christian Halle 
DESCRIPTION:    Source file for TL1 Retrive SW Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_NETypeRespBlk.h>


TL1_RtrvNETypeRspBlk::TL1_RtrvNETypeRspBlk(const TL1_SmartParameter<string>&             theVendor,
                           const TL1_SmartParameter<string>&             theSwType,
                           const TL1_SmartParameter<string>&             theSwVersion,
                           const CT_NodeConfiguration             theNodeCfg):

    itsVendor(theVendor),
    itsSwType(theSwType),
    itsSwVersion(theSwVersion),
    itsNodeCfg(theNodeCfg)
{
}

TL1_RtrvNETypeRspBlk::~TL1_RtrvNETypeRspBlk()
{
}
  
TL1_RtrvNETypeRspBlk::TL1_RtrvNETypeRspBlk(const TL1_RtrvNETypeRspBlk& theBlock) :
    itsVendor(theBlock.itsVendor),
    itsSwType(theBlock.itsSwType),
    itsSwVersion(theBlock.itsSwVersion),
    itsNodeCfg(theBlock.itsNodeCfg)
{
}

TL1_RtrvNETypeRspBlk& TL1_RtrvNETypeRspBlk::operator=( const TL1_RtrvNETypeRspBlk& theBlock )
{
    itsVendor=     theBlock.itsVendor;
    itsSwType=     theBlock.itsSwType;
    itsSwVersion=  theBlock.itsSwVersion;
    itsNodeCfg=    theBlock.itsNodeCfg;

    return *this;
}
