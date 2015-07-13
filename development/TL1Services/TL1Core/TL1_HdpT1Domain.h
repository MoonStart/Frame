/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 22, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 HdpT1 Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_HDPT1DOMAIN_H__
#define __TL1_HDPT1DOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_TELECOM_H__
#include <CommonTypes/CT_Telecom.h>
#endif

#ifndef __CT_AGENTFACILITY_H__
#include <CommonTypes/CT_AgentFacility.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_FACRSPBLK_H__
#include <Response/TL1_FACRspBlk.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

class TL1_HdpT1Domain
{
public:
    
    virtual void DltFac( const CT_TL1_FacAddr& facAddr,
                         TL1_Response& theResponse) = 0;

    virtual void EntFac ( const CT_TL1_FacAddr&         theAddr,
                          CT_ProfileTableId*            theAlarmProfile,
                          CT_SM_PST*                    thePrimaryState,
                          CT_FAC_LineCode*              theLineCode,		  //*******  
                          CT_FAC_FrameFormat*           theSignalFrameFormat, //*******
			  CT_FAC_SaBit*                 theSaBit,
                          CT_FAC_QualityLevelOverride*  theQualityLevelOverride,
                          TL1_Response&                 theResponse   
                          ) = 0;

    virtual void EdFac  ( const CT_TL1_FacAddr&         theAddr,
                          CT_ProfileTableId*            theAlarmProfile,
                          CT_SM_PST*                    thePrimaryState,
                          bool*                         isCommandForced,
                          CT_FAC_LineCode*              theLineCode,			// T1
                          CT_FAC_FrameFormat*           theSignalFrameFormat,	
			  CT_FAC_SaBit*                 theSaBit,			
                          CT_FAC_QualityLevelOverride*  theQualityLevelOverride,
                          TL1_Response& theResponse ) = 0;

    virtual void RtrvFac(const CT_TL1_FacAddr& theFacAddr,
                         CT_ProfileTableId* theAlarmProfile,                        
                         CT_SM_PST* thePrimaryState,                                    
                         CT_SM_SST* theSecondaryState,                                    
                         TL1_Response& theResponse ) const = 0;

    virtual void RmvFac( const CT_TL1_FacAddr& theFacAddr,
		                 bool* isCommandForced,
                         TL1_Response& theResponse ) = 0;

    virtual void RstFac( const CT_TL1_FacAddr& theFacAddr,
		                 bool* isCommandForced,
                         TL1_Response& theResponse ) = 0;

    virtual void RtrvOptPower(const CT_TL1_FacAddr& theFacAddr,
                              bool* isAutoAdjustOutPowerEnabled,
                              bool* isAutoAdjustInPowerEnabled,
                              TL1_Response& theResponse)=0;

    virtual void SetOptPower(const CT_TL1_FacAddr& theFacAddr,
                             CT_TEL_mBm* outputPowerLevel,
                             CT_TEL_mBm* inputPowerLevel,
                             TL1_Response& theResponse)=0;

    virtual void RtrvGain(const CT_TL1_FacAddr& theFacAddr,
                          bool* isAutoAdjustInPowerEnabled,
                          bool* isAutoAdjustOutPowerEnabled,
                          TL1_Response& theResponse)=0;

    virtual void SetGain(const CT_TL1_FacAddr& theFacAddr,
                         CT_TEL_mBm* inputGain,
                         CT_TEL_mBm* outputGain,
                         TL1_Response& theResponse)=0;

    virtual void RtrvAttn(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

    virtual void SetAttn(const CT_TL1_FacAddr& theFacAddr,
                         CT_TEL_mBm* powerLevel,
                         TL1_Response& theResponse)=0;

    virtual void RtrvPthTrc(const CT_TL1_FacAddr& theFacAddr,
                            CT_TL1_PathTrcType* msgType,
                            TL1_Response& theResponse)=0;

    virtual void OperateLoopback( const CT_TL1_FacAddr& theFacAddr,
                            CT_FAC_LoopBackType* loopbackType,
                            TL1_Response& theResponse)=0;

    virtual void ReleaseLoopback( const CT_TL1_FacAddr& theFacAddr,
                            CT_FAC_LoopBackType* loopbackType,
                            TL1_Response& theResponse)=0;

    virtual void StartBer(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

    virtual void StopBer(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

    virtual void StartDTrace(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

    virtual void StopDTrace(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

};

#endif
