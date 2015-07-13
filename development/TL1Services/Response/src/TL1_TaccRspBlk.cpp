/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 TACC Response 
TARGET:
AUTHOR:         December 7, 2006 - Mike Rodgers
DESCRIPTION:    Source file for TL1 Retrive TAP Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_TaccRspBlk.h>


TL1_TaccRspBlk::TL1_TaccRspBlk(
                   const string* theTapAid,
                   const CT_XcFacData* theTapTermAid1,
                   const CT_XcFacData* theTapTermAid2,
                   const CT_XcFacData* theEquipAid,
                   const CT_XcFacData* theFacAid,
                   const CT_BRTA_ModeType* theTapMode,
                   const string* theTapStatus)
    : myBitSet( INDEX_END, false)
{
    if( theTapAid )  
    {
		myBitSet[ INDEX_TapAid ] = true;
        myTapAid = *theTapAid;
    }

    if( theTapTermAid1 )  
    {
		myBitSet[ INDEX_TapTermAid1 ] = true;
        myTapTermAid1 = *theTapTermAid1;
    }

    if( theTapTermAid2 )  
    {
		myBitSet[ INDEX_TapTermAid2 ] = true;
        myTapTermAid2 = *theTapTermAid2;
    }

    if( theEquipAid )  
    {
		myBitSet[ INDEX_EquipAid ] = true;
        myEquipAid = *theEquipAid;
    }

    if( theFacAid )  
    {
		myBitSet[ INDEX_FacAid ] = true;
        myFacAid = *theFacAid;
    }

    if( theTapMode )  
    {
		myBitSet[ INDEX_TapMode ] = true;
        myTapMode = *theTapMode;
    }

    if( theTapStatus )  
    {
		myBitSet[ INDEX_TapStatus ] = true;
        myTapStatus = *theTapStatus;
    }

}


TL1_TaccRspBlk::~TL1_TaccRspBlk()
{
}
  
TL1_TaccRspBlk::TL1_TaccRspBlk(const TL1_TaccRspBlk& theBlock) :
    myBitSet(theBlock.myBitSet),
    myTapAid(theBlock.myTapAid),
    myTapTermAid1(theBlock.myTapTermAid1),
    myTapTermAid2(theBlock.myTapTermAid2),
    myEquipAid(theBlock.myEquipAid),
    myFacAid(theBlock.myFacAid),
    myTapMode(theBlock.myTapMode),
    myTapStatus(theBlock.myTapStatus)
{
}

TL1_TaccRspBlk& TL1_TaccRspBlk::operator=( const TL1_TaccRspBlk& theBlock )
{
    myBitSet      =  theBlock.myBitSet;
    myTapAid      =  theBlock.myTapAid;
    myTapTermAid1 =  theBlock.myTapTermAid1;
    myTapTermAid2 =  theBlock.myTapTermAid2;
    myEquipAid    =  theBlock.myEquipAid;
    myFacAid      =  theBlock.myFacAid;
    myTapMode     =  theBlock.myTapMode;
    myTapStatus   =  theBlock.myTapStatus;

    return *this;
}

bool TL1_TaccRspBlk::GetTapAid(string& Aid) const
{
   if( true == myBitSet[ INDEX_TapAid ] )
	{
    	Aid = myTapAid;
		return true;
	}
   else
   {
      return false;
   }
}

bool TL1_TaccRspBlk::GetTapTermAid1(CT_XcFacData& Aid) const
{
   if( true == myBitSet[ INDEX_TapTermAid1 ] )
	{
    	Aid = myTapTermAid1;
		return true;
	}
   else
   {
      return false;
   }
}

bool TL1_TaccRspBlk::GetTapTermAid2(CT_XcFacData& Aid) const
{
   if( true == myBitSet[ INDEX_TapTermAid2 ] )
	{
    	Aid = myTapTermAid2;
		return true;
	}
   else
   {
      return false;
   }
}

bool TL1_TaccRspBlk::GetEquipAid(CT_XcFacData& Aid) const
{
   if( true == myBitSet[ INDEX_EquipAid ] )
	{
    	Aid = myEquipAid;
		return true;
	}
   else
   {
      return false;
   }
}

bool TL1_TaccRspBlk::GetFacAid(CT_XcFacData& Aid) const
{
   if( true == myBitSet[ INDEX_FacAid ] )
	{
    	Aid = myFacAid;
		return true;
	}
   else
   {
      return false;
   }
}

bool TL1_TaccRspBlk::GetTapMode(CT_BRTA_ModeType& TapMode) const
{
   if( true == myBitSet[ INDEX_TapMode ] )
	{
    	TapMode = myTapMode;
		return true;
	}
   else
   {
      return false;
   }
}

bool TL1_TaccRspBlk::GetTapStatus(string& TapStatus) const
{
   if( true == myBitSet[ INDEX_TapStatus ] )
	{
    	TapStatus = myTapStatus;
		return true;
	}
   else
   {
      return false;
   }
}


