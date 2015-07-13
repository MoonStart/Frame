/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 02, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Call Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CALLFACADE_H__
#define __TL1_CALLFACADE_H__

#ifndef __TL1_CALLDOMAIN_H__
#include <TL1Core/TL1_CallDomain.h>
#endif

#ifndef __TL1_CALLENTITY_H__
#include <TL1Core/TL1_CallEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EntCall( \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntCall( \
                                    theEntParameters, \
                                    theResponse  ) )
                                     
#define FACI_EdCall( \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdCall( \
                                    theEntParameters, \
                                    theResponse  ) )

#define FACI_RtrvCall( \
                        theRtrvParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCall( theRtrvParameters, \
                                       theResponse ) )

#define FACI_RtrvCallDetail( \
                              theCallId, \
                              theCtp, \
                              theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCallDetail( theCallId, \
                                             theCtp, \
                                             theResponse ) )
                                     
#define FACI_DltCall( \
                        theCallId, \
                        theNodeId, \
                        theResponse, \
                        theHandle, \
                        theCtag,    \
                        theFalData ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltCall( theCallId, \
                                      theNodeId, \
                                      theResponse, \
                                      theHandle, \
                                      theCtag,  \
                                      theFalData ) )

#endif
