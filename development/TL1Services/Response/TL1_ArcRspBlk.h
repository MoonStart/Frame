/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         June 6, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Arc response block
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ARCRSPBLK_H__
#define __TL1_ARCRSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef _INC_CT_ARC_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_ARC_Definitions.h>
#endif

#include <vector>

using namespace std;

class TL1_ArcRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_ArcRspBlk(){}

    TL1_ArcRspBlk( const TL1_ArcRspBlk& theBlock );

	TL1_ArcRspBlk( const TL1_SmartParameter< string >& theEntityName,
                   const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                   const TL1_SmartParameter< CT_ARC_Config >& theArcMode,
                   const TL1_SmartParameter< CT_ARCInterval >& theArcHour,
                   const TL1_SmartParameter< CT_ARCInterval >& theArcMinutes,
                   const TL1_SmartParameter< CT_ARC_Timer >& theRemainingTime );

    TL1_ArcRspBlk( const TL1_SmartParameter< string >& theEntityName,
                   const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                   const TL1_SmartParameter< CT_ARC_Config >& theArcMode,
                   const TL1_SmartParameter< CT_ARCInterval >& theArcHour,
                   const TL1_SmartParameter< CT_ARCInterval >& theArcMinutes,
                   const TL1_SmartParameter< CT_ARC_Timer >& theRemainingTime );

	virtual ~TL1_ArcRspBlk();

    TL1_ArcRspBlk& operator=( const TL1_ArcRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< CT_TL1_SlotAddr >&
        GetSlotAddr() const
    {
        return itsSlotAddr;
    }

    const TL1_SmartParameter< CT_TL1_FacAddr >&
        GetFacAddr() const
    {
        return itsFacAddr;
    }

    const TL1_SmartParameter< CT_ARC_Config >&
        GetArcMode() const
    {
        return itsArcMode;
    }

    const TL1_SmartParameter< CT_ARCInterval >&
        GetArcHour() const
    {
        return itsArcHour;
    }

    const TL1_SmartParameter< CT_ARCInterval >&
        GetArcMinutes() const
    {
        return itsArcMinutes;
    }

    const TL1_SmartParameter< CT_ARC_Timer >&
        GetRemainingTime() const
    {
        return itsRemainingTime;
    }

private:
	TL1_SmartParameter< string >              itsEntityName;
    TL1_SmartParameter< CT_TL1_SlotAddr >     itsSlotAddr;
    TL1_SmartParameter< CT_TL1_FacAddr >      itsFacAddr;
	TL1_SmartParameter< CT_ARC_Config >       itsArcMode;
	TL1_SmartParameter< CT_ARCInterval >      itsArcHour;
	TL1_SmartParameter< CT_ARCInterval >      itsArcMinutes;
    TL1_SmartParameter< CT_ARC_Timer >        itsRemainingTime;
};


typedef TL1_Rtv_Response< TL1_ArcRspBlk > TL1_ArcResponse;


#endif