/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Connection Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONNFACADE_H__
#define __TL1_CONNFACADE_H__

#ifndef __TL1_CONNDOMAIN_H__
#include <TL1Core/TL1_ConnDomain.h>
#endif

#ifndef __TL1_CONNENTITY_H__
#include <TL1Core/TL1_ConnEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EntConn( \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntConn( \
                                    theEntParameters, \
                                    theResponse  ) )
                                     

#define FACI_RtrvConn( \
                        theRtrvParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvConn( theRtrvParameters, \
                                       theResponse ) )
                                      
#define FACI_DltConn( \
                        theNodeId, \
                        theConnId, \
                        theForced, \
                        theResponse, \
                        theHandle, \
                        theCtag, \
                        theFalData ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltConn( theNodeId, \
                                      theConnId, \
                                      theForced, \
                                      theResponse, \
                                      theHandle, \
                                      theCtag, \
                                      theFalData ) )

#define FACI_EdConn( \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdConn( \
                                    theEdParameters, \
                                    theResponse  ) )

#define FACI_RtrvConnInfo( \
                        theCallId, \
                        theNodeId, \
                        theMultiplier, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvConnInfo( theCallId, \
                                           theNodeId, \
                                           theMultiplier, \
                                           theResponse ) )

#define FACI_RtrvConnRoute( \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvConnRoute( \
                                    theParameters, \
                                    theResponse  ) )
                                     
#endif
