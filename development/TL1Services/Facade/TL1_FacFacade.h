/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 24, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Facility Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FACFACADE_H__
#define __TL1_FACFACADE_H__

#ifndef __TL1_FACDOMAIN_H__
#include <TL1Core/TL1_FacDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_DltFac( theAddr, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltFac( theAddr, theResponse, theHandle, theCtag ))

#define FACI_EntFacility( theAddr, \
                          theEntParameters, \
                          theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntFac( \
                                    theAddr, \
                                    theEntParameters, \
                                    theResponse  ) )

#define FACI_EdFacility( theAddr, \
                          theEdParameters, \
                          theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdFac( \
                                    theAddr, \
                                    theEdParameters, \
                                    theResponse  ) )

#define FACI_RtrvFac( theAddr, \
                      theAlarmProfile, \
                      thePrimaryState, \
                      theSecondaryState, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFac( theAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theResponse ))

#define FACI_RtrvFacRanging( theFirstAddr, \
                      theAlarmProfile, \
                      thePrimaryState, \
                      theSecondaryState, \
                      theResponse ,\
                      theLastAddr)\
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFac( theFirstAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theResponse,\
                                      theLastAddr ))


#define FACI_RtrvFacWithMembers( theAddr, \
                      theAlarmProfile, \
                      thePrimaryState, \
                      theSecondaryState, \
                      theRtrvMembers, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFac( theAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theRtrvMembers, \
                                      theResponse ))

#define FACI_RtrvFacRangingWithMembers( theFirstAddr, \
                      theAlarmProfile, \
                      thePrimaryState, \
                      theSecondaryState, \
                      theRtrvMembers, \
                      theResponse ,\
                      theLastAddr)\
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFac( theFirstAddr, \
                                      theAlarmProfile, \
                                      thePrimaryState, \
                                      theSecondaryState, \
                                      theRtrvMembers, \
                                      theResponse,\
                                      theLastAddr ))


#define FACI_RmvFac(  theAddr, \
                      isCommandForced, \
                      theResponse, \
                      theHandle, \
                      theCtag  ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RmvFac( theAddr, \
                                     isCommandForced, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ))

#define FACI_RstFac(  theAddr, \
                      isCommandForced, \
                      theResponse, \
                      theHandle, \
                      theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RstFac( theAddr, \
                                     isCommandForced, \
                                     theResponse, \
                                     theHandle, \
                                     theCtag ))

#define FACI_RtrvOptPower( theAddr, \
                           isAutoAdjustOutPowerEnabled, \
                           isAutoAdjustInPowerEnabled, \
                           theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOptPower( theAddr, \
                                           isAutoAdjustOutPowerEnabled, \
                                           isAutoAdjustInPowerEnabled, \
                                           theResponse ))

#define FACI_SetOptPower( theAddr, \
                          outputPowerLevel, \
                          inputPowerLevel, \
                          theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetOptPower( theAddr, \
                                          outputPowerLevel, \
                                          inputPowerLevel, \
                                          theResponse ))

#define FACI_RtrvGain( theAddr, \
                       isAutoAdjustInPowerEnabled, \
                       isAutoAdjustOutPowerEnabled, \
                       theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvGain( theAddr, \
                                       isAutoAdjustInPowerEnabled, \
                                       isAutoAdjustOutPowerEnabled, \
                                       theResponse ))

#define FACI_SetGain( theAddr, \
                      inputGain, \
                      outputGain, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetGain( theAddr, \
                                      inputGain, \
                                      outputGain, \
                                      theResponse ))

#define FACI_RtrvAttn( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAttn( theAddr, theResponse ))

#define FACI_SetAttn( theAddr, powerLevel, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetAttn( theAddr, powerLevel, theResponse ))

#define FACI_RtrvPthTrc( theAddr, powerLevel, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPthTrc( theAddr, powerLevel, theResponse ))

#define FACI_ReleaseLoopback( theAddr, loopbacktype, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ReleaseLoopback( theAddr, loopbacktype, theResponse, theHandle, theCtag ))

#define FACI_OperateLoopback( theAddr, loopbacktype, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateLoopback( theAddr, loopbacktype, theResponse, theHandle, theCtag ))

#define FACI_StartBer( theAddr, theBerType, thePrbsTx, thePrbsRx, thePrbsCompa, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StartBer( theAddr, theBerType, thePrbsTx, thePrbsRx, thePrbsCompa, theResponse ))

#define FACI_StopBer( theAddr, theBerType, thePrbsTx, thePrbsRx, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StopBer( theAddr, theBerType, thePrbsTx, thePrbsRx, theResponse ))

#define FACI_RtrvBer( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvBer( theAddr, theResponse ))

#define FACI_StartDTrace( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StartDTrace( theAddr, theResponse ))

#define FACI_StopDTrace( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StopDTrace( theAddr, theResponse ))

#define FACI_InitLink(theAddr, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, InitLink(theAddr, theResponse))

#define FACI_RtrvDispOch(theAddr, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvDisp(theAddr, theResponse))

#endif
