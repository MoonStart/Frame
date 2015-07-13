/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 08, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Service Level Profile and Service Level Policy
                Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLPFFACADE_H__
#define __TL1_SLPFFACADE_H__

#ifndef __TL1_SLPFDOMAIN_H__
#include <TL1Core/TL1_SlpfDomain.h>
#endif

#ifndef __TL1_SLPFENTITY_H__
#include <TL1Core/TL1_SlpfEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EdSlpf( \
                        theAddr, \
                        theEdParameters, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSlpf( \
                                    theAddr, \
                                    theEdParameters, \
                                    theResponse  ) )
                                      

#define FACI_RtrvSlpf( \
                        theAddr, \
                        ctProfileName, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSlpf( theAddr, \
                                       ctProfileName, \
                                       theResponse ) )

#define FACI_EdSlpolicy( \
                            theAddr, \
                            theEdParameters, \
                            theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSlpolicy( \
                                       theAddr, \
                                       theEdParameters, \
                                       theResponse  ) )
                                      

#define FACI_RtrvSlpolicy( \
                                theAddr, \
                                theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSlpolicy( theAddr, \
                                           theResponse ) )
                                      
#endif
