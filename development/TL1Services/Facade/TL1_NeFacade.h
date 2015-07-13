/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 3, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Ne Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NEFACADE_H__
#define __TL1_NEFACADE_H__

#ifndef __TL1_NE_ENTITY_H__
#include <TL1Core/TL1_NeEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EdNe( theName, theNodeConfiguration, theSubNodeConfiguration, theHardwareVersion, theSpanA,theSpanB, theNeLocation, theSID, theSite, theTimeZone, theDSP, \
                   theStsVcMode, theStsVcArcIntvHr, theStsVcArcIntvMn, theSyncOsc, theDefInterPacketGap, isCommandForced, theIntValueIntA, theFiberTypeIntA, theLowLatencyIntA, theIntValueIntB, theFiberTypeIntB, theLowLatencyIntB, \
                   theIntValueIntC, theFiberTypeIntC, theLowLatencyIntC, theIntValueIntD, theFiberTypeIntD, theLowLatencyIntD, theIntValueIntE, theFiberTypeIntE, theLowLatencyIntE, \
                   theIntValueIntF, theFiberTypeIntF, theLowLatencyIntF, theIntValueIntG, theFiberTypeIntG, theLowLatencyIntG, theIntValueIntH, theFiberTypeIntH, theLowLatencyIntH, \
                   theIntValueExtA, theFiberTypeExtA, theLowLatencyExtA, theIntValueExtB, theFiberTypeExtB, theLowLatencyExtB, theIntValueExtC, theFiberTypeExtC, theLowLatencyExtC, \
                   theIntValueExtD, theFiberTypeExtD, theLowLatencyExtD, theIntValueExtE, theFiberTypeExtE, theLowLatencyExtE, theIntValueExtF, theFiberTypeExtF, theLowLatencyExtF, \
                   theIntValueExtG, theFiberTypeExtG, theLowLatencyExtG, theIntValueExtH, theFiberTypeExtH, theLowLatencyExtH, theSysAlmPf, theCpInit, theMfgCtr, thePrimaryState, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdNe( theName, theNodeConfiguration, theSubNodeConfiguration, theHardwareVersion, theSpanA, theSpanB, theNeLocation, theSID, theSite, \
              theTimeZone, theDSP, theStsVcMode, theStsVcArcIntvHr, theStsVcArcIntvMn, theSyncOsc, theDefInterPacketGap, isCommandForced, theIntValueIntA, theFiberTypeIntA, theLowLatencyIntA, theIntValueIntB, theFiberTypeIntB, theLowLatencyIntB, \
                   theIntValueIntC, theFiberTypeIntC, theLowLatencyIntC, theIntValueIntD, theFiberTypeIntD, theLowLatencyIntD, theIntValueIntE, theFiberTypeIntE, theLowLatencyIntE, \
                   theIntValueIntF, theFiberTypeIntF, theLowLatencyIntF, theIntValueIntG, theFiberTypeIntG, theLowLatencyIntG, theIntValueIntH, theFiberTypeIntH, theLowLatencyIntH, \
                   theIntValueExtA, theFiberTypeExtA, theLowLatencyExtA, theIntValueExtB, theFiberTypeExtB, theLowLatencyExtB, theIntValueExtC, theFiberTypeExtC, theLowLatencyExtC, \
                   theIntValueExtD, theFiberTypeExtD, theLowLatencyExtD, theIntValueExtE, theFiberTypeExtE, theLowLatencyExtE, theIntValueExtF, theFiberTypeExtF, theLowLatencyExtF, \
                   theIntValueExtG, theFiberTypeExtG, theLowLatencyExtG, theIntValueExtH, theFiberTypeExtH, theLowLatencyExtH, theSysAlmPf, theCpInit, theMfgCtr, thePrimaryState, theResponse ))

#define FACI_RtrvNe( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvNe( theResponse ))

#define FACI_SetSID( theSID, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetSid( theSID,theResponse ))

#endif //__TL1_NEFACADE_H__
