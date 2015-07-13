/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Attenuation Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Attenuation Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_PWRRspBlk.h>

TL1_PWRRspBlk:: TL1_PWRRspBlk(){;}

TL1_PWRRspBlk:: TL1_PWRRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const bool* Apao,
                  const CT_TEL_mBm *Output ,
                  const bool* Apai,
                  const CT_TEL_mBm *Input )
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

    if(Output)
    {
        myBitSet[ INDEX_Output ] = true;
        myOutput = *Output;
    }

    if(Apai)
    {
        myBitSet[ INDEX_Apai ] = true;
        myApai = *Apai;
    }

    if(Input)
    {
        myBitSet[ INDEX_Input ] = true;
        myInput = *Input;
    }

}

TL1_PWRRspBlk::TL1_PWRRspBlk(const TL1_PWRRspBlk& pwrBlk)
    : myBitSet( pwrBlk.myBitSet ), myEntityName( pwrBlk.myEntityName), 
      myFacAddr(pwrBlk.myFacAddr), myApao( pwrBlk.myApao), myOutput( pwrBlk.myOutput),
      myApai( pwrBlk.myApai), myInput( pwrBlk.myInput)
{
}

TL1_PWRRspBlk::~TL1_PWRRspBlk()
{
}

TL1_PWRRspBlk& TL1_PWRRspBlk::operator=( const TL1_PWRRspBlk& theBlock )
{
    myBitSet = theBlock.myBitSet;
    myEntityName = theBlock.myEntityName;
    myFacAddr = theBlock.myFacAddr;
    myApao = theBlock.myApao;
    myOutput = theBlock.myOutput;
    myApai = theBlock.myApai;
    myInput = theBlock.myInput;

    return *this;
}

bool TL1_PWRRspBlk::GetEntityName(string &EntityName ) const
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

bool TL1_PWRRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
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

bool TL1_PWRRspBlk::GetApao(bool &Apao ) const
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

bool TL1_PWRRspBlk::GetInput( CT_TEL_mBm &Input) const
{
    if( true == myBitSet[ INDEX_Input ] )
    {
        Input = myInput;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_PWRRspBlk::GetApai(bool &Apai ) const
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

bool TL1_PWRRspBlk::GetOutput( CT_TEL_mBm &Output) const
{
    if( true == myBitSet[ INDEX_Output ] )
    {
        Output = myOutput;
        return true;
    }
    else
    {
        return false;
    }
}
