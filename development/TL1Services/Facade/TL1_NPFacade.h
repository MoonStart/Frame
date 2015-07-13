/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 NP Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NPFACADE_H__
#define __TL1_NPFACADE_H__

#ifndef __TL1_NPENTITY_H__
#include <TL1Core/TL1_NPEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EntNp( theAddr, theEntParameters, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntNp( theAddr, theEntParameters, theResponse  ) )

#define FACI_EdNp( theAddr, theEdParameters, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdNp( theAddr, theEdParameters, theResponse  ) )
                                    
#define FACI_RtrvNp( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvNp( theAddr, theResponse ) )
                                      
#define FACI_DltNp( theAddr, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltNp( theAddr, theResponse, theHandle, theCtag ) )
                                    
#define FACI_RtrvNpStats( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvNpStats( theAddr, theResponse ) )
                                    
#endif
