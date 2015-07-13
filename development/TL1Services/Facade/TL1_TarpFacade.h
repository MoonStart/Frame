/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 23, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 Tarp Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TARPFACADE_H__
#define __TL1_TARPFACADE_H__

#ifndef __TL1_TARPDOMAIN_H__
#include <TL1Core/TL1_TarpDomain.h>
#endif

#ifndef __TL1_TARPENTITY_H__
#include <TL1Core/TL1_TarpEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define TARP_EdFac( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdFac( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ) )

#define TARP_RtrvFac( \
                        theAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theSecondaryState, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFac( theAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theResponse ) )
#endif
