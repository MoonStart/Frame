/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Shawn He
DESCRIPTION:    Header file for TL1 GCC Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_GCCFACADE_H__
#define __TL1_GCCFACADE_H__

#ifndef __TL1_GCCDOMAIN_H__
#include <TL1Core/TL1_GCCDomain.h>
#endif

#ifndef __TL1_GCCENTITY_H__
#include <TL1Core/TL1_GCCEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

//GCC
#define FACI_EntGCC( \
                        theAddr, \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntGCC( \
                                    theAddr, \
                                    theEntParameters, \
                                    theResponse  ) )
                                    
#define FACI_EdGCC( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdGCC( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ) )

#define FACI_RtrvGCC( \
                        theAddr, \
                        theType, \
                        theProfileAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvGCC( theAddr, \
                                      theType, \
                                      theProfileAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theResponse ) )
                                      
#define FACI_DltGCC( \
                        theAddr, \
                        theType, \
                        theResponse, \
                        theHandle, \
                        theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltGCC( theAddr, \
                                     theType, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ) )

#endif
