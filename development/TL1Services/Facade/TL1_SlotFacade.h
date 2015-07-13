/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 16, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Slot Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLOTFACADE_H__
#define __TL1_SLOTFACADE_H__

#ifndef __TL1_SLOTENTITY_H__
#include <TL1Core/TL1_SlotEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EdSlot( theAddr, theCommandMode, theAlarmProfile, thePrimaryState, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSlot( theAddr, theCommandMode, theAlarmProfile, thePrimaryState, theResponse ))

#define FACI_RtrvSlot( theAddr, theAlmProfileFilter, thePstFilter, theSstFilter, theResponse, rtrvParameters ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSlot( theAddr, theAlmProfileFilter, thePstFilter, theSstFilter, theResponse, \
	rtrvParameters ))

#define FACI_RtrvIntIpSlot( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIntIpSlot( theAddr, theResponse ))

#endif //__TL1_NEFACADE_H__
