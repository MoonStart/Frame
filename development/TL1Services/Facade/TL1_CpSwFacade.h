/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 12, 2011, 2011 - Tom Novak
DESCRIPTION:    Header file for Opr Switch Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CPSWITCHFACADE_H__
#define __TL1_CPSWITCHFACADE_H__

#ifndef __TL1_CPSWITCHDOMAIN_H__
#include <TL1Core/TL1_CpSwDomain.h>
#endif

#ifndef __TL1_CPSWITCHENTITY_H__
#include <TL1Core/TL1_CpSwEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_OprCpSw( \
                        theCommand, \
                        theAllCalls, \
                        theCallId, \
                        thePathType, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprCpSw( \
                                theCommand, \
                                theAllCalls, \
                                theCallId, \
                                thePathType, \
                                theResponse  ) )
                                     

#define FACI_RlsCpSw( \
                        theAllCalls, \
                        theCallId, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RlsCpSw( \
                               theAllCalls, \
                               theCallId, \
                               theResponse  ) )

#endif
