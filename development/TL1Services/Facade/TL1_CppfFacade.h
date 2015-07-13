/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 07, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 CP Profile Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CPPFFACADE_H__
#define __TL1_CPPFFACADE_H__

#ifndef __TL1_CPPFDOMAIN_H__
#include <TL1Core/TL1_CppfDomain.h>
#endif

#ifndef __TL1_CPPFENTITY_H__
#include <TL1Core/TL1_CppfEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EdCppf(theAddr, cppfName, gmplsMode, refreshSecs, advertisement, theResponse) \
FAC_OP_CONST(NO_SUB_RGN_ID, EdCppf( theAddr, cppfName, gmplsMode, refreshSecs, advertisement, theResponse ))

#define FACI_RtrvCppf(theAddr, theResponse) \
FAC_OP_CONST(NO_SUB_RGN_ID, RtrvCppf(theAddr, theResponse))

#endif
