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

#ifndef __TL1_HDPT1FACADE_H__
#define __TL1_HDPT1FACADE_H__

#ifndef __TL1_HDPT1DOMAIN_H__
#include <TL1Core/TL1_HdpT1Domain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACHDPT1_DltFac( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltFac( theAddr, theResponse ))

#define FACHDPT1_EntFac(theAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        theLineCode, \
                        theSignalFrameFormat, \
                        theSaBit, \
                        theQualityLevelOverride, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntFac( \
                    theAddr, \
                    theAlarmProfile, \
                    thePrimaryState, \
                    theLineCode, \
                    theSignalFrameFormat, \
                    theSaBit, \
                    theQualityLevelOverride, \
                    theResponse  ))

#define FACHDPT1_EdFac( theAddr, \
                        theAlarmProfile, \
                        thePrimaryState, \
                        isCommandForced, \
                        theLineCode, \
                        theSignalFrameFormat, \
                        theSaBit, \
                        theQualityLevelOverride, \
                        theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdFac( \
                    theAddr, \
                    theAlarmProfile, \
                    thePrimaryState, \
                    isCommandForced, \
                    theLineCode, \
                    theSignalFrameFormat, \
                    theSaBit, \
                    theQualityLevelOverride, \
                    theResponse ))

#define FACHDPT1_RtrvFac( theAddr, \
                      theAlarmProfile, \
                      thePrimaryState, \
                      theSecondaryState, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFac( theAddr, \
                                                          theAlarmProfile, \
                                                          thePrimaryState, \
                                                          theSecondaryState, \
                                                          theResponse ))
#define FACHDPT1_RmvFac(  theAddr, \
                      isCommandForced, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RmvFac( theAddr, \
                                                         isCommandForced, \
                                                         theResponse ))

#define FACHDPT1_RstFac(  theAddr, \
                      isCommandForced, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RstFac( theAddr, \
                                                         isCommandForced, \
                                                         theResponse ))

#define FACIHDPT1_RtrvAlm( theAddr, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAlm( theAddr, theNotifCode, theCondType, theServAffectingFlag, theLocation, theDirection, theResponse, true ))

#define FACIHDPT1_RtrvCond( theAddr, theCondType, theLocation, theDirection, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCond( theAddr, theCondType, theLocation, theDirection, theResponse ))

#define FACIHDPT1_RtrvArc( theAddr, theArcMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvArc( theAddr, theArcMode, theResponse ))

#define FACIHDPT1_OprArc( theAddr, theArcMode, theArcHour, theArcMinutes, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprArc( theAddr, theArcMode, theArcHour, theArcMinutes, theResponse ))

#define FACIHDPT1_RlsArc( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RlsArc( theAddr, theResponse ))

#define FACHDPT1_RtrvOptPower( theAddr, \
                           isAutoAdjustOutPowerEnabled, \
                           isAutoAdjustInPowerEnabled, \
                           theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOptPower( theAddr, \
                                                               isAutoAdjustOutPowerEnabled, \
                                                               isAutoAdjustInPowerEnabled, \
                                                               theResponse ))

#define FACHDPT1_SetOptPower( theAddr, \
                          outputPowerLevel, \
                          inputPowerLevel, \
                          theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetOptPower( theAddr, \
                                                               outputPowerLevel, \
                                                               inputPowerLevel, \
                                                               theResponse ))

#define FACHDPT1_RtrvGain( theAddr, \
                       isAutoAdjustInPowerEnabled, \
                       isAutoAdjustOutPowerEnabled, \
                       theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvGain( theAddr, \
                                                           isAutoAdjustInPowerEnabled, \
                                                           isAutoAdjustOutPowerEnabled, \
                                                           theResponse ))

#define FACHDPT1_SetGain( theAddr, \
                      inputGain, \
                      outputGain, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetGain( theAddr, \
                                                          inputGain, \
                                                          outputGain, \
                                                          theResponse ))

#define FACHDPT1_RtrvAttn( theAddr, \
                       theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAttn( theAddr, \
                                                           theResponse ))

#define FACHDPT1_SetAttn( theAddr, \
                      powerLevel, \
                      theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetAttn( theAddr, \
                                                          powerLevel, \
                                                          theResponse ))

#define FACHDPT1_RtrvPthTrc( theAddr, \
                         powerLevel, \
                         theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvPthTrc( theAddr, \
                                                             powerLevel, \
                                                             theResponse ))

#define FACHDPT1_ReleaseLoopback( theAddr, \
                         loopbacktype, \
                         theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, ReleaseLoopback( theAddr, \
                                                             loopbacktype, \
                                                             theResponse ))

#define FACHDPT1_OperateLoopback( theAddr, \
                         loopbacktype, \
                         theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateLoopback( theAddr, \
                                                             loopbacktype, \
                                                             theResponse ))

#define FACHDPT1_StartBer( theAddr, \
                       theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StartBer( theAddr, \
                                                           theResponse ))

#define FACHDPT1_StopBer( theAddr, \
                       theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StopBer( theAddr, \
                                                           theResponse ))

#define FACHDPT1_StartDTrace( theAddr, \
                       theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StartDTrace( theAddr, \
                                                           theResponse ))

#define FACHDPT1_StopDTrace( theAddr, \
                       theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, StopDTrace( theAddr, \
                                                           theResponse ))

#endif
