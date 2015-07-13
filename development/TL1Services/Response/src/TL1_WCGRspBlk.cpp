/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 WCG Response 
TARGET:
DESCRIPTION:    Source file for TL1 WCG Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_WCGRspBlk.h>

//-----------------------------------------------------------------------------
TL1_WCGRspBlk::TL1_WCGRspBlk()
: myBitSet( INDEX_END, false )
{ 
    myEntityName  =     "";
}

//-----------------------------------------------------------------------------
TL1_WCGRspBlk::TL1_WCGRspBlk(
               const string *entityName,
               const CT_TL1_FacAddr* facAddr,
               const CT_FAC_OtsChanMap* theChanAvail)
: myBitSet( INDEX_END, false )
{
    myEntityName = "";
    
    if( entityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *entityName;
    }

    if( facAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
	    myFacAddr = *facAddr;
    }

    if(theChanAvail)
    {
        myBitSet[ INDEX_ChanAvail ] = true;
        myChanAvail = *theChanAvail;
    }
}

//-----------------------------------------------------------------------------
TL1_WCGRspBlk::TL1_WCGRspBlk(const TL1_WCGRspBlk& wcgBlk)
: myBitSet( INDEX_END, false )
{
    myBitSet        = wcgBlk.myBitSet;
    myEntityName    = wcgBlk.myEntityName;
    myFacAddr       = wcgBlk.myFacAddr;
    myChanAvail     = wcgBlk.myChanAvail;
}

//-----------------------------------------------------------------------------
TL1_WCGRspBlk::~TL1_WCGRspBlk()
{
}

//-----------------------------------------------------------------------------
TL1_WCGRspBlk& TL1_WCGRspBlk::operator=( const TL1_WCGRspBlk& theBlock )
{
    myBitSet        = theBlock.myBitSet;
    myEntityName    = theBlock.myEntityName;
    myFacAddr       = theBlock.myFacAddr;
    myChanAvail     = theBlock.myChanAvail;

    return *this;
}

//-----------------------------------------------------------------------------
bool TL1_WCGRspBlk::operator==( const TL1_WCGRspBlk& theBlock ) const
{
    return ( myBitSet        == theBlock.myBitSet &&
             myEntityName    == theBlock.myEntityName &&
             myFacAddr       == theBlock.myFacAddr &&
             myChanAvail     == theBlock.myChanAvail);
}

//-----------------------------------------------------------------------------
bool TL1_WCGRspBlk::GetEntityName(string &EntityName ) const
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

//-----------------------------------------------------------------------------
bool TL1_WCGRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
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

//-----------------------------------------------------------------------------
bool TL1_WCGRspBlk::GetChanAvail(CT_FAC_OtsChanMap& theChanAvail) const
{
    if( true == myBitSet[ INDEX_ChanAvail ] )
    {
        theChanAvail = myChanAvail;
        return true;
    }
    else
    {
        return false;
    }
}
