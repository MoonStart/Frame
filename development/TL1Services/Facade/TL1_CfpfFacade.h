/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         June 25, 2009- Maggie Zhang
DESCRIPTION:    Header file for TL1 Control Frame Profile Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CFPFFACADE_H__
#define __TL1_CFPFFACADE_H__

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#ifndef __TL1_CFPFDOMAIN_H__
#include <TL1Core/TL1_CfpfDomain.h>
#endif

#define FACI_EdCfpf( theProfileId, theLacp, theLinkOAM, theDot1X, theElmi, theLldp, theGarp, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdCfpf( theProfileId, theLacp, theLinkOAM, theDot1X, theElmi, theLldp, theGarp, theResponse ))

#define FACI_RtrvCfpf( theProfileId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCfpf( theProfileId, theResponse ))

#endif
