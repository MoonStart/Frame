
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         March 27, 2012 - Leo LU
DESCRIPTION:    Header file for TL1 Switch Domain facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_BERFACADE_H__
#define __TL1_BERFACADE_H__

#ifndef __TL1_SWITCHDOMAINENTITY_H__
#include <TL1Core/TL1_BerDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvBer( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvBer( theAddr, theResponse ))

#define FACI_StartBer( theAddr, theBerType, thePrbsTx, thePrbsRx, thePrbsCompa, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StartBer( theAddr, theBerType, thePrbsTx, thePrbsRx, thePrbsCompa, theResponse ))

#define FACI_StopBer( theAddr, theBerType, thePrbsTx, thePrbsRx, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StopBer( theAddr, theBerType, thePrbsTx, thePrbsRx, theResponse ))

#endif //__TL1_BERFACADE_H__
