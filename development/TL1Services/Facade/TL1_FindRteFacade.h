#ifndef __TL1_FINDRTEFACADE_H__
#define __TL1_FINDRTEFACADE_H__
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 11, 2011 - TLD
DESCRIPTION:    Header file for TL1 Find Route Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#include <TL1Core/TL1_FindRteDomain.h>
#include <TL1Core/TL1_FindRteEntity.h>

#include <Facade/FC_FacadeOperationIf.h>


#define FACI_OprFindRte( \
                        theOprParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprFindRte( \
                                    theOprParameters, \
                                    theResponse  ) )

#endif // __TL1_FINDRTEFACADE_H__
