/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for TL1 EXPPATH Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXPPATHFACADE_H__
#define __TL1_EXPPATHFACADE_H__

#ifndef __TL1_EXPPATHDOMAIN_H__
#include <TL1Core/TL1_ExppathDomain.h>
#endif

#ifndef __TL1_EXPPATHENTITY_H__
#include <TL1Core/TL1_ExppathEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EntExppath( \
                        theExpAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntExppath( \
                                    theExpAddr, \
                                    theParameters, \
                                    theResponse  ) )

#define FACI_EdExppath( \
                        theExpAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdExppath( \
                                    theExpAddr, \
                                    theParameters, \
                                    theResponse  ) )

#define FACI_DltExppath( \
                        theExpAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltExppath( \
                                    theExpAddr, \
                                    theParameters, \
                                    theResponse  ) )


#define FACI_RtrvExppath( \
                        theExpAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvExppath( \
                                    theExpAddr, \
                                    theParameters, \
                                    theResponse  ) )

#endif
