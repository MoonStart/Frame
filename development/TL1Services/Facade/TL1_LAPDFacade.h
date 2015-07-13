/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 25, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 LAPD Profile Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDFACADE_H__
#define __TL1_LAPDFACADE_H__

#ifndef __TL1_LAPDDOMAIN_H__
#include <TL1Core/TL1_LAPDDomain.h>
#endif

#ifndef __TL1_LAPDENTITY_H__
#include <TL1Core/TL1_LAPDEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define LAPD_EntLapd( \
                        theAddr, \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntLapd( \
                                    theAddr, \
                                    theEntParameters, \
                                    theResponse  ) )
                                    
#define LAPD_EdLapd( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdLapd( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ) )

#define LAPD_RtrvLapd( \
                        theAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theSecondaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLapd( theAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theResponse ) )
                                      
#define LAPD_DltLapd( \
                        theAddr, \
                        theResponse, \
                        theHandle, \
                        theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltLapd( theAddr, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ) )

#endif
