/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Gain Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Gain Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_GainRspBlk.h>

TL1_GainRspBlk::TL1_GainRspBlk(){;}

TL1_GainRspBlk::TL1_GainRspBlk(const string* EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const bool* Apai,
                  const CT_TEL_mBm* IGain,
                  const bool* Apao,
                  const CT_TEL_mBm* OGain)
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

    if( Apao )
    {
        myBitSet[ INDEX_Apao ] = true;
        myApao = *Apao;
    }

    if( OGain )
    {
        myBitSet[ INDEX_OGain ] = true;
        myOGain = *OGain;
    }

    if( Apai)
    {
        myBitSet[ INDEX_Apai ] = true;
        myApai = *Apai;
    }

    if( IGain )
    {
        myBitSet[ INDEX_IGain ] = true;
        myIGain = *IGain;
    }
}

TL1_GainRspBlk::TL1_GainRspBlk(const TL1_GainRspBlk& otsBlk)
    : myBitSet( otsBlk.myBitSet ), myEntityName(otsBlk.myEntityName), myFacAddr(otsBlk.myFacAddr), 
      myApai( otsBlk.myApai), myIGain( otsBlk.myIGain), myApao( otsBlk.myApao), myOGain( otsBlk.myOGain)
{
}

TL1_GainRspBlk::~TL1_GainRspBlk()
{
}

TL1_GainRspBlk& TL1_GainRspBlk::operator=( const TL1_GainRspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;
    myEntityName = theBlock.myEntityName;
    myFacAddr = theBlock.myFacAddr;
    myApai =  theBlock.myApai;
    myIGain =  theBlock.myIGain;
    myApao =  theBlock.myApao;
    myOGain =  theBlock.myOGain;

    return *this;
}

bool TL1_GainRspBlk::GetEntityName(string &EntityName ) const
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

bool TL1_GainRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
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

bool TL1_GainRspBlk::GetIGain(CT_TEL_mBm& IGain ) const
{
    if( true == myBitSet[ INDEX_IGain ] )
    {
        IGain = myIGain;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_GainRspBlk::GetOGain(CT_TEL_mBm& OGain ) const
{
    if( true == myBitSet[ INDEX_OGain ] )
    {
        OGain = myOGain;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_GainRspBlk::GetApao(bool& Apao ) const
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

bool TL1_GainRspBlk::GetApai(bool& Apai ) const
{
    if( true == myBitSet[ INDEX_Apai ] )
    {
        Apai = myApai;
        return true;
    }
    else
    {
        return false;
    }
}

