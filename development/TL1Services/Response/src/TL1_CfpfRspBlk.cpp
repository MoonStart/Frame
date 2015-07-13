/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 CFPF Response 
TARGET:
AUTHOR:         Maggie Zhang
DESCRIPTION:    Source file for TL1 Retrive Control Frame Profile Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_CfpfRspBlk.h>

//
//  RtrvCfpf
//

TL1_CfpfRspBlk::TL1_CfpfRspBlk(
                            const uint32*           theProfileId,
                    const bool*      theLacp,
                    const bool*      theLinkOAM,
                    const bool*      theDot1X,
                    const bool*      theElmi,
                    const bool*      theLldp,
                    const bool*      theGarp)
    : myBitSet( INDEX_END, false)
{
    if( theProfileId )  
    {
        myBitSet[ INDEX_ProfileId ] = true;
        myProfileId = *theProfileId;
    }

    if (theLacp)
    {
        myBitSet[ INDEX_Lacp ] = true;
        myLacp = *theLacp;
    }
    if (theLinkOAM)
    {
        myBitSet[ INDEX_LinkOAM ] = true;
        myLinkOAM = *theLinkOAM;
    }
    if (theDot1X)
    {
        myBitSet[ INDEX_Dot1X ] = true;
        myDot1X = *theDot1X;
    }
    if (theElmi)
    {
        myBitSet[ INDEX_Elmi ] = true;
        myElmi = *theElmi;
    }
    if (theLldp)
    {
        myBitSet[ INDEX_Lldp ] = true;
        myLldp = *theLldp;
    }
    if (theGarp)
    {
        myBitSet[ INDEX_Garp ] = true;
        myGarp = *theGarp;
    }
}

TL1_CfpfRspBlk::~TL1_CfpfRspBlk()
{
}
  
TL1_CfpfRspBlk::TL1_CfpfRspBlk(const TL1_CfpfRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myProfileId(theBlock.myProfileId),
    myLacp(theBlock.myLacp),
    myLinkOAM(theBlock.myLinkOAM),
    myDot1X(theBlock.myDot1X),
    myElmi(theBlock.myElmi),
    myLldp(theBlock.myLldp),
    myGarp(theBlock.myGarp)
{
}

TL1_CfpfRspBlk& TL1_CfpfRspBlk::operator=( const TL1_CfpfRspBlk& theBlock )
{
    myBitSet =          theBlock.myBitSet;
    myProfileId =       theBlock.myProfileId;
    myLacp=             theBlock.myLacp;
    myLinkOAM=          theBlock.myLinkOAM;
    myDot1X=            theBlock.myDot1X;
    myElmi=             theBlock.myElmi;
    myLldp=             theBlock.myLldp;
    myGarp=             theBlock.myGarp;

    return *this;
}

bool TL1_CfpfRspBlk::GetProfileId(uint32& theProfileId) const
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

bool TL1_CfpfRspBlk::GetLacp(bool& theLacp) const
{
    if( true == myBitSet[ INDEX_Lacp ] )
    {
        theLacp = myLacp;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_CfpfRspBlk::GetLinkOAM(bool& theLinkOAM) const
{
    if( true == myBitSet[ INDEX_LinkOAM ] )
    {
        theLinkOAM = myLinkOAM;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_CfpfRspBlk::GetDot1X(bool& theDot1X) const
{
    if( true == myBitSet[ INDEX_Dot1X ] )
    {
        theDot1X = myDot1X;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_CfpfRspBlk::GetElmi(bool& theElmi) const
{
    if( true == myBitSet[ INDEX_Elmi ] )
    {
        theElmi = myElmi;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_CfpfRspBlk::GetLldp(bool& theLldp) const
{
    if( true == myBitSet[ INDEX_Lldp ] )
    {
        theLldp = myLldp;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_CfpfRspBlk::GetGarp(bool& theGarp) const
{
    if( true == myBitSet[ INDEX_Garp ] )
    {
        theGarp = myGarp;
        return true;
    }
    else
    {
        return false;
    }
}

