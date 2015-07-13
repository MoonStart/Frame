/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 22, 2006, Michael Rodgers
DESCRIPTION:    Header file for TL1 Tacc Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TACCFACADE_H__
#define __TL1_TACCFACADE_H__

#ifndef __TL1_TACCDOMAIN_H__
#include <TL1Core/TL1_TaccDomain.h>
#endif

#ifndef __TL1_TACCENTITY_H__
#include <TL1Core/TL1_TaccEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_ConnTacc( ctXcFacData, theTapNumber, theTaMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ConnTacc( ctXcFacData, theTapNumber, theTaMode, theResponse ) )

#define FACI_DiscTacc( theTapNumber, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DiscTacc( theTapNumber, theResponse ) )

#define FACI_ChgAccmd( theTapNumber, theTaMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ChgAccmd( theTapNumber, theTaMode, theResponse ) )

#define FACI_RtrvTap( theTapNumber, theTapStatus, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTap( theTapNumber, theTapStatus, theResponse ) )

#endif
