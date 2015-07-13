/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Alarm Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_BWPFFACADE_H__
#define __TL1_BWPFFACADE_H__

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#ifndef __TL1_BWPFDOMAIN_H__
#include <TL1Core/TL1_BwpfDomain.h>
#endif

#define FACI_EdBwpf( theProfileId, theCir, theCbs, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdBwpf( theProfileId, theCir, theCbs, theResponse ))

#define FACI_EntBwpf( theProfileId, theCir, theCbs, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntBwpf( theProfileId, theCir, theCbs, theResponse ))

#define FACI_DltBwpf( theProfileId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltBwpf( theProfileId, theResponse ))

#define FACI_RtrvBwpf( theProfileId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvBwpf( theProfileId, theResponse ))

#endif
