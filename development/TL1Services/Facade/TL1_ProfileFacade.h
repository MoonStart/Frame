/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Tong Wu
DESCRIPTION:    Header file for TL1 CPPF, LINKPF Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PROFILEFACADE_H__
#define __TL1_PROFILEFACADE_H__

#ifndef __TL1_PROFILEDOMAIN_H__
#include <TL1Core/TL1_ProfileDomain.h>
#endif

#ifndef __TL1_PROFILEENTITY_H__
#include <TL1Core/TL1_ProfileEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif
