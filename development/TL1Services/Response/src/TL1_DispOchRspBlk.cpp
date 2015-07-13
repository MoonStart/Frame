
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Dispersion Response 
TARGET:
AUTHOR:         February 5, 2008
DESCRIPTION:    Source file for TL1 Dispersion Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_DispOchRspBlk.h>

#ifndef CT_AGENTFACILITY_H
#include <CommonTypes/CT_AgentFacility.h>
#endif

TL1_DispOchRspBlk::TL1_DispOchRspBlk() :
myBitSet( INDEX_END, false ),
myFacAddr(CT_TL1_FacAddr()),
myEntityName(""),
myChromDisp(CHROMATIC_DISP_NA),
myDiffGroupDelay(DIFF_GRP_DELAY_NA) { }

TL1_DispOchRspBlk:: TL1_DispOchRspBlk(const string *EntityName,
                                      const CT_TL1_FacAddr* FacAddr,
                                      const int16* ChromDisp,
                                      const int16 * theDiffGroupDelay )
: myBitSet( INDEX_END, false )
 ,myFacAddr(CT_TL1_FacAddr())
 ,myEntityName("")
 ,myChromDisp(CHROMATIC_DISP_NA)
 ,myDiffGroupDelay(DIFF_GRP_DELAY_NA)
{
    if( EntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *EntityName;
    }

    if( FacAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *FacAddr;
    }

    if(ChromDisp)
    {
        myBitSet[ INDEX_ChromDisp ] = true;
        myChromDisp = *ChromDisp;
    }

    if(theDiffGroupDelay)
    {
        myBitSet[ INDEX_DiffGroupDelay ] = true;
        myDiffGroupDelay = *theDiffGroupDelay;
    }

}

TL1_DispOchRspBlk::TL1_DispOchRspBlk(const TL1_DispOchRspBlk& ochDispRspBlk)
: myBitSet(ochDispRspBlk.myBitSet), 
  myEntityName(ochDispRspBlk.myEntityName),
  myFacAddr(ochDispRspBlk.myFacAddr),
  myChromDisp(ochDispRspBlk.myChromDisp),
  myDiffGroupDelay(ochDispRspBlk.myDiffGroupDelay)
{
}

TL1_DispOchRspBlk::~TL1_DispOchRspBlk()
{
}

TL1_DispOchRspBlk& TL1_DispOchRspBlk::operator=( const TL1_DispOchRspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;

    myEntityName = theBlock.myEntityName;
    myFacAddr = theBlock.myFacAddr;
    myChromDisp = theBlock.myChromDisp;
    myDiffGroupDelay = theBlock.myDiffGroupDelay;
    return *this;
}

bool TL1_DispOchRspBlk::operator==( const TL1_DispOchRspBlk& theBlock ) const
{
    return ( myBitSet     == theBlock.myBitSet     &&
             myEntityName == theBlock.myEntityName &&
             myFacAddr    == theBlock.myFacAddr    &&
             myChromDisp  == theBlock.myChromDisp    &&
             myDiffGroupDelay  == theBlock.myDiffGroupDelay );

}

bool TL1_DispOchRspBlk::operator!=( const TL1_DispOchRspBlk& theBlock ) const
{
    return ( !( myBitSet     == theBlock.myBitSet     &&
                myEntityName == theBlock.myEntityName &&
                myFacAddr    == theBlock.myFacAddr    &&
                myChromDisp  == theBlock.myChromDisp    &&
                myDiffGroupDelay  == theBlock.myDiffGroupDelay ) );

}

bool TL1_DispOchRspBlk::GetEntityName(string &EntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        EntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_DispOchRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        FacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_DispOchRspBlk::GetChromDisp(int16 &ChromDisp ) const
{
    if( true == myBitSet[ INDEX_ChromDisp ] )
    {
        ChromDisp = myChromDisp;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_DispOchRspBlk::GetDiffGroupDelay(int16 &theDGD ) const
{
    if( true == myBitSet[ INDEX_DiffGroupDelay ] )
    {
        theDGD = myDiffGroupDelay;
        return true;
    }
    else
    {
        return false;
    }
}
