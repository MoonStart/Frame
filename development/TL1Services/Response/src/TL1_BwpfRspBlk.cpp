/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 SNMP Response 
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Source file for TL1 Retrive Bandwidth Profile Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_BwpfRspBlk.h>

//
//  RtrvBwpf
//

TL1_BwpfRspBlk::TL1_BwpfRspBlk(
                            const uint32*           theProfileId,
                            const int*              theCir,
                            const int*              theCbs)
    : myBitSet( INDEX_END, false)
{
    if( theProfileId )  
    {
        myBitSet[ INDEX_ProfileId ] = true;
        myProfileId = *theProfileId;
    }

    if( theCir )  
    {
        myBitSet[ INDEX_Cir ] = true;
        myCir = *theCir;
    }

    if( theCbs )  
    {
        myBitSet[ INDEX_Cbs ] = true;
        myCbs = *theCbs;
    }
}

TL1_BwpfRspBlk::~TL1_BwpfRspBlk()
{
}
  
TL1_BwpfRspBlk::TL1_BwpfRspBlk(const TL1_BwpfRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myProfileId(theBlock.myProfileId),
    myCir(theBlock.myCir),
    myCbs(theBlock.myCbs)
{
}

TL1_BwpfRspBlk& TL1_BwpfRspBlk::operator=( const TL1_BwpfRspBlk& theBlock )
{
    myBitSet =          theBlock.myBitSet;
    myProfileId =       theBlock.myProfileId;
    myCir =             theBlock.myCir;
    myCbs =             theBlock.myCbs;

    return *this;
}

bool TL1_BwpfRspBlk::GetProfileId(uint32& theProfileId) const
{
    if( true == myBitSet[ INDEX_ProfileId ] )
    {
        theProfileId = myProfileId;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_BwpfRspBlk::GetCir(int& theCir) const
{
    if( true == myBitSet[ INDEX_Cir ] )
    {
        theCir = myCir;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_BwpfRspBlk::GetCbs(int& theCbs) const
{
    if( true == myBitSet[ INDEX_Cbs ] )
    {
        theCbs = myCbs;
        return true;
    }
    else
    {
        return false;
    }
}
