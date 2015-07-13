/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         June 6, 2003- Jean-Francois Emond
DESCRIPTION:    Implementation file for TL1 Arc response block
-----------------------------------------------------------------------------*/ 

#include <Response/TL1_ArcRspBlk.h>

TL1_ArcRspBlk::TL1_ArcRspBlk( const TL1_SmartParameter< string >& theEntityName,
                              const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                              const TL1_SmartParameter< CT_ARC_Config >& theArcMode,
                              const TL1_SmartParameter< CT_ARCInterval >& theArcHour,
                              const TL1_SmartParameter< CT_ARCInterval >& theArcMinutes,
                              const TL1_SmartParameter< CT_ARC_Timer >& theRemainingTime) :
    itsEntityName( theEntityName ),
    itsSlotAddr( theSlotAddr ),
    itsArcMode( theArcMode ),
    itsArcHour( theArcHour ),
    itsArcMinutes( theArcMinutes ),
    itsRemainingTime( theRemainingTime )
{
}

TL1_ArcRspBlk::TL1_ArcRspBlk( const TL1_SmartParameter< string >& theEntityName,
                              const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                              const TL1_SmartParameter< CT_ARC_Config >& theArcMode,
                              const TL1_SmartParameter< CT_ARCInterval >& theArcHour,
                              const TL1_SmartParameter< CT_ARCInterval >& theArcMinutes,
                              const TL1_SmartParameter< CT_ARC_Timer >& theRemainingTime) :
    itsEntityName( theEntityName ),
    itsFacAddr( theFacAddr ),
    itsArcMode( theArcMode ),
    itsArcHour( theArcHour ),
    itsArcMinutes( theArcMinutes ),
    itsRemainingTime( theRemainingTime )
{
}

TL1_ArcRspBlk::~TL1_ArcRspBlk()
{
}

TL1_ArcRspBlk::TL1_ArcRspBlk( const TL1_ArcRspBlk& theBlock ) :
    itsEntityName( theBlock.itsEntityName ),
    itsSlotAddr( theBlock.itsSlotAddr ),
    itsFacAddr( theBlock.itsFacAddr ),
    itsArcMode( theBlock.itsArcMode ),
    itsArcHour( theBlock.itsArcHour ),
    itsArcMinutes( theBlock.itsArcMinutes ),
    itsRemainingTime( theBlock.itsRemainingTime )
{
}

TL1_ArcRspBlk& TL1_ArcRspBlk::operator=( const TL1_ArcRspBlk& theBlock )
{
    itsEntityName = theBlock.itsEntityName;
    itsSlotAddr = theBlock.itsSlotAddr;
    itsFacAddr = theBlock.itsFacAddr;
    itsArcMode = theBlock.itsArcMode;
    itsArcHour = theBlock.itsArcHour;
    itsArcMinutes = theBlock.itsArcMinutes;
    itsRemainingTime = theBlock.itsRemainingTime;

    return *this;
}
