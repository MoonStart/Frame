/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         MAy 6, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Slot Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLOTDOMAIN_H__
#define __TL1_SLOTDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_RTRVALLPARAMETERS_H__
#include <TL1Core/TL1_RtrvAllParameters.h>
#endif

/**
   CLASS TL1_SlotDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of facility related TL1 commands, that a TL1 Entities
   for a slot is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_SlotDomain
{
public:
    virtual void EdSlot( const CT_TL1_SlotAddr& theAddr,
                         bool* theCommandMode,
				         CT_ProfileTableId* theAlarmProfile,
                         CT_SM_PST* thePrimaryState,
                         TL1_Response& theResponse )=0;
    
    virtual void RtrvSlot( const CT_TL1_SlotAddr& theAddr,
                           CT_ProfileTableId* theAlmProfile,
                           CT_SM_PST* thePrimaryState,
                           CT_SM_SST* theSecondaryState,
                           TL1_Response& theResponse,
                           TL1_RtrvAllParameters* theRtrvParams = 0 ) = 0;

    virtual void RtrvIntIpSlot( const CT_TL1_SlotAddr& theSlot,
                                TL1_Response& theResponse ) = 0;
};

#endif
