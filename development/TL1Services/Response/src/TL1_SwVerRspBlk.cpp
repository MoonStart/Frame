/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive SWV VERSION Response
TARGET:
AUTHOR:         Ed Bandyk
DESCRIPTION:    Source file for TL1 Retrive SW VERSION Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SwVerRspBlk.h>


TL1_SWVERRspBlk::TL1_SWVERRspBlk()
{
}

TL1_SWVERRspBlk::TL1_SWVERRspBlk(const string* entityName,
                                  const CT_TL1_SlotAddr*    slotAddr,
                                  const string              theVersion,
                                  const uint8               thePatchLevel,
                                  const CT_SoftwareStatus   theStatus
                                  )
    : myBitSet( INDEX_END, false),mySlotAddr(*slotAddr)
{
    if( entityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *entityName;
    }

    if( slotAddr )
    {
        myBitSet[ INDEX_SlotAddr ] = true;
        mySlotAddr = *slotAddr;
    }

    // not optional
    myBitSet[ INDEX_Version ] = true;
    myVersion = theVersion;

    myBitSet[ INDEX_PatchLevel ] = true;
    myPatchLevel = thePatchLevel;

    myBitSet[ INDEX_Status ] = true;
    myStatus = theStatus;
}


TL1_SWVERRspBlk::~TL1_SWVERRspBlk()
{
}

 TL1_SWVERRspBlk::TL1_SWVERRspBlk(const TL1_SWVERRspBlk& theBlk) : mySlotAddr(0,0)
{
    myBitSet        = theBlk.myBitSet;
    myEntityName    = theBlk.myEntityName;
    mySlotAddr      = theBlk.mySlotAddr;
    myVersion       = theBlk.myVersion;
    myPatchLevel    = theBlk.myPatchLevel;
    myStatus        = theBlk.myStatus;
}

TL1_SWVERRspBlk&  TL1_SWVERRspBlk::operator=( const TL1_SWVERRspBlk& theBlock )
{
    myBitSet        = theBlock.myBitSet;
    myEntityName    = theBlock.myEntityName;
    mySlotAddr      = theBlock.mySlotAddr;
    myVersion       = theBlock.myVersion;
    myPatchLevel    = theBlock.myPatchLevel;
    myStatus        = theBlock.myStatus;

    return *this;
}

bool TL1_SWVERRspBlk::operator==( const TL1_SWVERRspBlk& theBlock ) const
{
    return ( myBitSet       == theBlock.myBitSet &&
             myEntityName   == theBlock.myEntityName &&
             mySlotAddr     == theBlock.mySlotAddr &&
             myVersion      == theBlock.myVersion  &&
             myPatchLevel   == theBlock.myPatchLevel &&
             myStatus       == theBlock.myStatus);
}

bool TL1_SWVERRspBlk::GetEntityName( string& entityName) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        entityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SWVERRspBlk::GetSlotAddr( CT_TL1_SlotAddr& slotAddr ) const
{
    if( true == myBitSet[ INDEX_SlotAddr ] )
    {
        slotAddr = mySlotAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SWVERRspBlk::GetVersion( string& theVersion) const
{
    if( true == myBitSet[ INDEX_Version ] )
    {
        theVersion = myVersion;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SWVERRspBlk::GetPatchLevel( uint8& thePatchLevel) const
{
    if( true == myBitSet[ INDEX_PatchLevel ] )
    {
        thePatchLevel = myPatchLevel;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_SWVERRspBlk::GetStatus( CT_SoftwareStatus& theStatus) const
{
    if( true == myBitSet[ INDEX_Status ] )
    {
        theStatus = myStatus;
        return true;
    }
    else
    {
        return false;
    }
}
