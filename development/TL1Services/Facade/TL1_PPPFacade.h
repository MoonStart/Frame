/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Header file for TL1 PPP, PPPPF Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PPPFACADE_H__
#define __TL1_PPPFACADE_H__

#ifndef __TL1_PPPDOMAIN_H__
#include <TL1Core/TL1_PPPDomain.h>
#endif

#ifndef __TL1_PPPENTITY_H__
#include <TL1Core/TL1_PPPEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EntPPP( \
                        theAddr, \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntPPP( \
                                    theAddr, \
                                    theEntParameters, \
                                    theResponse  ) )
                                    
#define FACI_EdPPP( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdPPP( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ) )

#define FACI_RtrvPPP( \
                        theAddr, \
                        theProfileAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPPP( theAddr, \
                                      theProfileAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theResponse ) )
                                      
#define FACI_DltPPP( \
                        theAddr, \
                        theResponse, \
                        theHandle, \
                        theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltPPP( theAddr, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ) )


#define FACI_EdPPPPF( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdPPPPF( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ))

#define FACI_RtrvPPPPF( \
                        theAddr, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPPPPF( \
                        theAddr, \
                        theResponse ) )

#endif
