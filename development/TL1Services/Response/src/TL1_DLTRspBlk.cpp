/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_DLTRspBlk.h>

TL1_DLTRspBlk:: TL1_DLTRspBlk(const string* entityName)
    : myEntityName( *entityName)
{
}

TL1_DLTRspBlk::TL1_DLTRspBlk(const TL1_DLTRspBlk& blk)
    : myEntityName( blk.myEntityName)
{
}

TL1_DLTRspBlk::~TL1_DLTRspBlk()
{
}

TL1_DLTRspBlk& TL1_DLTRspBlk::operator=( const TL1_DLTRspBlk& theBlock )
{
    myEntityName = theBlock.myEntityName;

    return *this;
}

// Definition for GetEntityName()
bool TL1_DLTRspBlk::GetEntityName( string& entityName) const
{
    entityName = myEntityName;
    return true;
}

