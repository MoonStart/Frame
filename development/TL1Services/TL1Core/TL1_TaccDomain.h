/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 22, 2006 - Michael Rodgers
DESCRIPTION:    Header file for TL1 TACC Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TACCDOMAIN_H__
#define __TL1_TACCDOMAIN_H__


#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_TL1_BASE_H_
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef CT_TESTACCESSTYPES_H
#include <CommonTypes/CT_TestAccessTypes.h>
#endif

/**
   CLASS TL1_TaccDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_TaccDomain
{
public:

    virtual void ConnTacc( CT_XcFacData& ctXcFacData,
                           CT_TapNumber ctTapNumber,
                           CT_BRTA_ModeType ctTaMode,
                           TL1_Response& tl1RspBlk) = 0;

    virtual void DiscTacc( CT_TapNumber ctTapNumber,
                           TL1_Response& tl1RspBlk) = 0;

    virtual void ChgAccmd( CT_TapNumber ctTapNumber,
                           CT_BRTA_ModeType ctTaMode,
                           TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvTap( CT_TapNumber ctTapNumber,
                          CT_TapStatus* ctTapStatus,
                          TL1_Response& tl1RspBlk)const = 0;

};

#endif
