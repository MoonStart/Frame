/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 LPBK Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 LPBK Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_LPBKRspBlk.h>

TL1_LPBKRspBlk:: TL1_LPBKRspBlk(const string *EntityName,
                  const CT_TL1_LoopbackType* type)
    : myEntityName(*EntityName), myType( *type)
{
}

TL1_LPBKRspBlk::TL1_LPBKRspBlk(const TL1_LPBKRspBlk& Blk)
    : myEntityName( Blk.myEntityName), myType( Blk.myType)
{
}

TL1_LPBKRspBlk::~TL1_LPBKRspBlk()
{
}

TL1_LPBKRspBlk& TL1_LPBKRspBlk::operator=( const TL1_LPBKRspBlk& theBlock )
{
    myEntityName = theBlock.myEntityName;
    return *this;
}

bool TL1_LPBKRspBlk::GetEntityName(string &EntityName ) const
{
        EntityName = myEntityName;
        return true;
}

bool TL1_LPBKRspBlk::GetLoopbackType(CT_TL1_LoopbackType& type ) const
{
        type = myType;
        return true;
}
