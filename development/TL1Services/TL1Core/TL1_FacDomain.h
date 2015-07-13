/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Facility Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FACDOMAIN_H__
#define __TL1_FACDOMAIN_H__

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

#include <LumosTypes/LT_System.h>

class TL1_FacilityEntParameters;
class TL1_FacilityEdParameters;

/**
   CLASS TL1_FacilityDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of facility related TL1 commands, that a TL1 Entities
   for a facility is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_FacilityDomain
{
public:
    
    //
    // There are several groups of Facilities as follows:
    // 1) TRN PORT (GBEP,GOPT,OCn,STMn,TGBEP)
    // 2) OCH
    // 3) OMS
    // 4) OSC
    // 5) OTS
    //
    // The Facility domain will interface to all of the above groups of
    // facilities, although some interface parameters will only pertain
    // to specific groups and can be ommited when used with others.
    //
    virtual void DltFac( const CT_TL1_FacAddr& facAddr,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag) = 0;

    virtual void EntFac( const CT_TL1_FacAddr&         theAddr,
                         TL1_FacilityEntParameters&    theEntParameters,
                         TL1_Response&                 theResponse ) = 0;

    virtual void EdFac( const CT_TL1_FacAddr&         theAddr,
                        TL1_FacilityEdParameters&     theEdParameters,
                        TL1_Response&                 theResponse ) = 0;

    virtual void RtrvFac(const CT_TL1_FacAddr& theFacAddr,
                         CT_ProfileTableId* theAlarmProfile,                        
                         CT_SM_PST* thePrimaryState,                                    
                         CT_SM_SST* theSecondaryState,    
                         TL1_Response& theResponse ) const = 0;

    virtual void RtrvFac(const CT_TL1_FacAddr& theFacAddr,
                         CT_ProfileTableId* theAlarmProfile,                        
                         CT_SM_PST* thePrimaryState,                                    
                         CT_SM_SST* theSecondaryState,    
                         bool theRtrvMembers,                                
                         TL1_Response& theResponse )const {};

    virtual void RtrvFac(int configRegionIndex,
                         const CT_TL1_FacAddr& theFacAddr,
                         CT_ProfileTableId* theAlarmProfile,                        
                         CT_SM_PST* thePrimaryState,                                    
                         CT_SM_SST* theSecondaryState,                                    
                         TL1_Response& theResponse ) const {}

    virtual void RtrvFac(const CT_TL1_FacAddr& theFirstFacAddr,
                         CT_ProfileTableId* theAlarmProfile,                        
                         CT_SM_PST* thePrimaryState,                                    
                         CT_SM_SST* theSecondaryState,                                    
                         TL1_Response& theResponse,
                         const CT_TL1_FacAddr& theLastFacAddr)const 
                         { };

    virtual void RtrvFac(const CT_TL1_FacAddr& theFirstFacAddr,
                         CT_ProfileTableId* theAlarmProfile,                        
                         CT_SM_PST* thePrimaryState,                                    
                         CT_SM_SST* theSecondaryState,   
                         bool theRtrvMembers,
                         TL1_Response& theResponse,
                         const CT_TL1_FacAddr& theLastFacAddr)const 
                         { };
	

    virtual void RmvFac( const CT_TL1_FacAddr& theFacAddr,
                         bool* isCommandForced,
                         TL1_Response& theResponse,
                          LT_Handle                     theHandle,
                          LT_Ctag                       theCtag ) = 0;

    virtual void RstFac( const CT_TL1_FacAddr& theFacAddr,
                       bool* isCommandForced,
                         TL1_Response& theResponse,
                          LT_Handle                     theHandle,
                          LT_Ctag                       theCtag ) = 0;

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
                            TL1_Response& theResponse,
                            LT_Handle                     theHandle,
                            LT_Ctag                       theCtag)=0;

    virtual void ReleaseLoopback( const CT_TL1_FacAddr& theFacAddr,
                            CT_FAC_LoopBackType* loopbackType,
                            TL1_Response& theResponse,
                            LT_Handle                     theHandle,
                            LT_Ctag                       theCtag)=0;

    virtual void StartBer(const CT_TL1_FacAddr& theFacAddr,
                          CT_FAC_BerType* berType,
                          CT_FAC_BerCtrl* prbsTx,
                          CT_FAC_BerCtrl* prbsRx,
                          CT_TEL_PrbsFormat* prbsCompa,
                          TL1_Response& theResponse)=0;

    virtual void StopBer(const CT_TL1_FacAddr& theFacAddr,
                         CT_FAC_BerType* berType,
                         CT_FAC_BerCtrl* prbsTx,
                         CT_FAC_BerCtrl* prbsRx,
                          TL1_Response& theResponse)=0;

    virtual void RtrvBer(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

    virtual void StartDTrace(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

    virtual void StopDTrace(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

    virtual void RtrvDisp(const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse)=0;

};

#endif
