/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Aug 06, 2010 - Chengsi Shao
DESCRIPTION:    Header file for TL1 ADMREROUTE Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ARRFACADE_H__
#define __TL1_ARRFACADE_H__

#ifndef __TL1_ARRDOMAIN_H__
#include <TL1Core/TL1_ArrDomain.h>
#endif

#ifndef __TL1_ARRENTITY_H__
#include <TL1Core/TL1_ArrEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_OprAdmReRoute( \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprAdmReRoute( \
                                     theParameters, \
                                     theResponse ) )
                         

#endif

