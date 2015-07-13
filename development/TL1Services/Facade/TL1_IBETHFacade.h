/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IBETHFACADE_H__
#define __TL1_IBETHFACADE_H__

#ifndef __TL1_IBETHDOMAIN_H__
#include <TL1Core/TL1_IBETHDomain.h>
#endif

#ifndef __TL1_IBETHENTITY_H__
#include <TL1Core/TL1_IBETHEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EntIBETH( \
                        theAddr, \
                        theEntParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntIBETH( \
                                    theAddr, \
                                    theEntParameters, \
                                    theResponse  ) )
                                    
#define FACI_EdIBETH( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdIBETH( \
                    theAddr, \
                    theEdParameters, \
                    theResponse ) )

#define FACI_RtrvIBETH( \
                        theAddr, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIBETH( theAddr, \
                                      theResponse ) )
                                      
#define FACI_DltIBETH( \
                        theAddr, \
                        theResponse, \
                        theHandle, \
                        theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltIBETH( theAddr, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ) )

#endif
