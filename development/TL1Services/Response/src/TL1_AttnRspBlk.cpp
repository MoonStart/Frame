/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Attenuation Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Attenuation Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_AttnRspBlk.h>

#ifndef CT_AGENTFACILITY_H
#include <CommonTypes/CT_AgentFacility.h>
#endif

TL1_AttnRspBlk::TL1_AttnRspBlk() :
myBitSet( INDEX_END, false ),
myFacAddr(CT_TL1_FacAddr()),
myEntityName(""),
myApao(false),
myAttn(INVALID_GAIN),
myAttnIngress(INVALID_GAIN),
myAttnEgress(INVALID_GAIN){ }

TL1_AttnRspBlk:: TL1_AttnRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const bool* Apao,
                  const CT_TEL_mBm *Attn,
                  const CT_TEL_mBm *AttnIngress,
                  const CT_TEL_mBm *AttnEgress)
    : myBitSet( INDEX_END, false )
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

    if(Apao)
    {
        myBitSet[ INDEX_Apao ] = true;
        myApao = *Apao;
    }

    if(Attn)
    {
        myBitSet[ INDEX_Attn ] = true;
        myAttn = *Attn;
    }

    if(AttnIngress)
    {
        myBitSet[ INDEX_AttnIngress ] = true;
        myAttnIngress = *AttnIngress;
    }

     if(AttnEgress)
    {
        myBitSet[ INDEX_AttnEgress ] = true;
        myAttnEgress = *AttnEgress;
    }

}

TL1_AttnRspBlk::TL1_AttnRspBlk(const TL1_AttnRspBlk& attnBlk)
    : myBitSet( attnBlk.myBitSet), myEntityName( attnBlk.myEntityName), 
      myFacAddr( attnBlk.myFacAddr), myApao( attnBlk.myApao), myAttn( attnBlk.myAttn), myAttnIngress( attnBlk.myAttnIngress), myAttnEgress( attnBlk.myAttnEgress)
{
}

TL1_AttnRspBlk::~TL1_AttnRspBlk()
{
}

TL1_AttnRspBlk& TL1_AttnRspBlk::operator=( const TL1_AttnRspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;

    myEntityName = theBlock.myEntityName;
    myFacAddr = theBlock.myFacAddr;
    myApao = theBlock.myApao;
    myAttn = theBlock.myAttn;

    return *this;
}

bool TL1_AttnRspBlk::operator==( const TL1_AttnRspBlk& theBlock ) const
{
    return ( myBitSet     == theBlock.myBitSet     &&
             myEntityName == theBlock.myEntityName &&
             myFacAddr    == theBlock.myFacAddr    &&
             myApao       == theBlock.myApao       &&
             myAttn       == theBlock.myAttn    &&
             myAttnIngress       == theBlock.myAttnIngress    &&
             myAttnEgress       == theBlock.myAttnEgress      );

}

bool TL1_AttnRspBlk::operator!=( const TL1_AttnRspBlk& theBlock ) const
{
    return ( !( myBitSet     == theBlock.myBitSet     &&
                myEntityName == theBlock.myEntityName &&
                myFacAddr    == theBlock.myFacAddr    &&
                myApao       == theBlock.myApao       &&
                myAttn       == theBlock.myAttn   &&
                myAttnIngress       == theBlock.myAttnIngress    &&
                myAttnEgress       == theBlock.myAttnEgress) );

}

bool TL1_AttnRspBlk::GetEntityName(string &EntityName ) const
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

bool TL1_AttnRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
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

bool TL1_AttnRspBlk::GetApao(bool &Apao ) const
{
    if( true == myBitSet[ INDEX_Apao ] )
    {
        Apao = myApao;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_AttnRspBlk::GetAttn( CT_TEL_mBm &Attn) const
{
    if( true == myBitSet[ INDEX_Attn ] )
    {
        Attn = myAttn;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_AttnRspBlk::GetAttnIngress( CT_TEL_mBm &AttnIngress) const
{
    if( true == myBitSet[ INDEX_AttnIngress ] )
    {
        AttnIngress = myAttnIngress;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_AttnRspBlk::GetAttnEgress( CT_TEL_mBm &AttnEgress) const
{
    if( true == myBitSet[ INDEX_AttnEgress ] )
    {
        AttnEgress = myAttnEgress;
        return true;
    }
    else
    {
        return false;
    }
}


