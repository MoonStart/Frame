/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive FPGAV VERSION Response
TARGET:
AUTHOR:         Xinlun Fang
DESCRIPTION:    Source file for TL1 Retrive FPGAV VERSION Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_FpgaVerRspBlk.h>



TL1_FPGAVERRspBlk::TL1_FPGAVERRspBlk()
{
}

TL1_FPGAVERRspBlk::TL1_FPGAVERRspBlk(const string*   entityName,
                      const CT_TL1_SlotAddr*         slotAddr,
                      const string                   theFpgaName,
                      const string                   theVersion,
                      const TL1_SmartParameter<CT_FirmwareStatus>        theStatus
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

    //----------------------------------------------
    // not optional
    //----------------------------------------------
    myBitSet[ INDEX_FpgaName ] = true;
    myFpgaName = theFpgaName;

    myBitSet[ INDEX_Version ] = true;
    myVersion = theVersion;

    myBitSet[ INDEX_Status ] = true;
    myStatus = theStatus;

}


TL1_FPGAVERRspBlk::~TL1_FPGAVERRspBlk()
{
}

 TL1_FPGAVERRspBlk::TL1_FPGAVERRspBlk(const TL1_FPGAVERRspBlk& theBlk) : mySlotAddr(0,0)
{
    myBitSet      = theBlk.myBitSet;
    myEntityName  = theBlk.myEntityName;
    mySlotAddr    = theBlk.mySlotAddr;
    myFpgaName      = theBlk.myFpgaName;
    myVersion       = theBlk.myVersion;
    myStatus        = theBlk.myStatus;
}

TL1_FPGAVERRspBlk&  TL1_FPGAVERRspBlk::operator=( const TL1_FPGAVERRspBlk& theBlock )
{
    myBitSet      = theBlock.myBitSet;
    myEntityName  = theBlock.myEntityName;
    mySlotAddr    = theBlock.mySlotAddr;
    myFpgaName      = theBlock.myFpgaName;
    myVersion       = theBlock.myVersion;
    myStatus        = theBlock.myStatus;

    return *this;
}

bool TL1_FPGAVERRspBlk::operator==( const TL1_FPGAVERRspBlk& theBlock ) const
{
    return ( myBitSet      == theBlock.myBitSet &&
             myEntityName  == theBlock.myEntityName &&
             mySlotAddr    == theBlock.mySlotAddr &&
             myFpgaName      == theBlock.myFpgaName &&
             myVersion       == theBlock.myVersion  &&
             myStatus        == theBlock.myStatus);
}

bool TL1_FPGAVERRspBlk::GetEntityName( string& entityName) const
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

bool TL1_FPGAVERRspBlk::GetSlotAddr( CT_TL1_SlotAddr& slotAddr ) const
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

bool TL1_FPGAVERRspBlk::GetFpgaName( string& theFpgaName) const
{
    if( true == myBitSet[ INDEX_FpgaName ] )
    {
        theFpgaName = myFpgaName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_FPGAVERRspBlk::GetVersion( string& theVersion) const
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

bool TL1_FPGAVERRspBlk::GetStatus( TL1_SmartParameter<CT_FirmwareStatus>& theStatus) const
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
