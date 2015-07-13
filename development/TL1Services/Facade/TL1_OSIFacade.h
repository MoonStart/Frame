/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 11, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 OSI Profile Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSIFACADE_H__
#define __TL1_OSIFACADE_H__

#ifndef __TL1_OSIDOMAIN_H__
#include <TL1Core/TL1_OSIDomain.h>
#endif

#ifndef __TL1_OSIENTITY_H__
#include <TL1Core/TL1_OSIEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define OsiRtr_Ent( \
                        theAddr, \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntOsiRtr( \
                                    theAddr, \
                                    theEntParameters, \
                                    theResponse  ) )
                                    
#define OsiRtr_Ed( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdOsiRtr( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ) )

#define OsiRtr_Rtrv( \
                        theAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theSecondaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOsiRtr( theAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theResponse ) )

#define OsiRtr_RtrvMapNeighbor( \
                        theAddr, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOsiRtrMapNeighbor( theAddr, \
                                                    theResponse ) )

#define OsiRtr_RtrvMapNetwork( \
                        theAddr, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOsiRtrMapNetwork( theAddr, \
                                                   theResponse ) )

                                      
#define OsiRtr_Dlt( \
                        theAddr, \
                        theResponse, \
                        theHandle, \
                        theCtag, \
                        theForced ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltOsiRtr( theAddr, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag, \
                                     theForced ) )

#endif
