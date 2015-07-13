/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         February 19, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Equipment Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EQPTFACADE_H__
#define __TL1_EQPTFACADE_H__

#ifndef __TL1_EQPTDOMAIN_H__
#include <TL1Core/TL1_EqptDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_DltEqpt( theAddr, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltEqpt( theAddr, theResponse, theHandle, theCtag ))


#define FACI_EdEqpt( theAddr, \
                     theCommandMode, \
                     theEqptParameters, \
                     theResponse, \
                     theHandle, \
                     theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdEqpt( \
                     theAddr, \
                     theCommandMode, \
                     theEqptParameters, \
                     theResponse, \
                     theHandle, \
                     theCtag ))

#define FACI_EntEqpt(theAddr, \
                        theEqptParameters, \
                        theResponse , \
                        theHandle, \
                        theCtag) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntEqpt( \
                        theAddr, \
                        theEqptParameters, \
                        theResponse, \
                        theHandle, \
                        theCtag ))

#define FACI_RmvEqpt( theAddr, theCommandMode, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RmvEqpt( theAddr, theCommandMode, theResponse, theHandle, theCtag ))

#define FACI_RstEqpt( theAddr, theCommandMode, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RstEqpt( theAddr, theCommandMode, theResponse, theHandle, theCtag ))

#define FACI_MeasureOutputPower( theAddr, theSignal, thePath, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, MeasureOutputPower( theAddr, theSignal, thePath, theResponse ))

#define FACI_OperateEqptLed( theAddr, thePeriod, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateEqptLed( theAddr, thePeriod, theResponse ))

#define FACI_RtrvEqpt( theAddr, theAlmProfileFilter, thePstFilter, theSstFilter, theResponse, theRtrvParameters ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvEqpt(theAddr, theAlmProfileFilter, thePstFilter, theSstFilter, theResponse, \
theRtrvParameters ))

#define FACI_RtrvLed( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLed( theAddr, theResponse ))

#define FACI_RtrvFpgaVer( theAddr, theFWStatus, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFpgaVer( theAddr, theFWStatus, theResponse ))

#define FACI_RtrvSwVer( theAddr, theSWStatus, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSwVer( theAddr, theSWStatus, theResponse ))

#define FACI_InitSys( theAddr, theInitPhase, theCommandMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, InitSys( theAddr, theInitPhase, theCommandMode,theResponse ))

#define FACI_SwDxEqpt( theAddr, theCommandMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SwDxEqpt( theAddr, theCommandMode, theResponse ))
#endif
