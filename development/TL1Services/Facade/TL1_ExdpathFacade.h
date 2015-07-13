/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         September 10, 2014 Jing Jin
DESCRIPTION:    Header file for TL1 EXDPATH Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXDPATHFACADE_H__
#define __TL1_EXDPATHFACADE_H__

#ifndef __TL1_EXDPATHDOMAIN_H__
#include <TL1Core/TL1_ExdpathDomain.h>
#endif

#ifndef __TL1_EXDPATHENTITY_H__
#include <TL1Core/TL1_ExdpathEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EntExdpath( \
                        theExdAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntExdpath( \
                                    theExdAddr, \
                                    theParameters, \
                                    theResponse  ) )

#define FACI_EdExdpath( \
                        theExdAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdExdpath( \
                                    theExdAddr, \
                                    theParameters, \
                                    theResponse  ) )

#define FACI_DltExdpath( \
                        theExdAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltExdpath( \
                                    theExdAddr, \
                                    theParameters, \
                                    theResponse  ) )


#define FACI_RtrvExdpath( \
                        theExdAddr, \
                        theParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvExdpath( \
                                    theExdAddr, \
                                    theParameters, \
                                    theResponse  ) )

#endif

