/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 18, 2011 - Shawn He
DESCRIPTION:    Header file for TL1 GCC Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_GCCDOMAIN_H__
#define __TL1_GCCDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include "CommonTypes/CT_TL1_Base.h"
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

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#include <LumosTypes/LT_System.h>

#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <CommonTypes/CT_TL1_EqptAddr.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>

class TL1_GCCEdParameters;
class TL1_GCCEntParameters;

class TL1_GCCDomain
{
public:

    virtual void EntGCC( const CT_TL1_FacAddr&  theGCCAddr,
                          TL1_GCCEntParameters& theEntParameters,
                          TL1_Response&          theResponse ) = 0;

    virtual void EdGCC(  const CT_TL1_FacAddr& theGCCAddr,
                          TL1_GCCEdParameters& theEdParameters, 			
                          TL1_Response&         theResponse ) = 0;

    virtual void RtrvGCC( const CT_TL1_FacAddr& theGCCAddr,
                           CT_GCC_Type*          theType,
                           CT_PPPProfAddr*       theProfileAddr,                        
                           CT_ProfileTableId*    theAlarmProfile,                        
                           CT_SM_PST*            thePrimaryState,                                    
                           TL1_Response&         theResponse ) const = 0;

    virtual void DltGCC( const CT_TL1_FacAddr&  theGCCAddr,
                          CT_GCC_Type*           theType,
                          TL1_Response&          theResponse,
                          LT_Handle              theHandle,
                          LT_Ctag                theCtag ) = 0;
};


#endif
