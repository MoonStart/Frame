/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Keith Halsall - August 7, 2012
DESCRIPTION:    Header file for TL1 DA Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DAFACADE_H__
#define __TL1_DAFACADE_H__

#ifndef __TL1_DAENTITY_H__
#include <TL1Core/TL1_DaEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


// DA
#define FACI_EntDa( theAddr, theDcnAddr, theMgtDomain, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntDa( theAddr, theDcnAddr, theMgtDomain, thePst, theResponse ))

#define FACI_EdDa( theId, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdDa( theId, thePst, theResponse ))

#define FACI_DltDa( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltDa( theId, theResponse ))

#define FACI_RtrvDa( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvDa( theId, theResponse ))  
                       
#endif                       
