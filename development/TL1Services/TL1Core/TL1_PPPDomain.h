/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 25, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 PPP, PPPF Profile Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PPPDOMAIN_H__
#define __TL1_PPPDOMAIN_H__

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

class TL1_PPPEdParameters;
class TL1_PPPEntParameters;

class TL1_PPPDomain
{
public:

    virtual void EntPPP( const CT_TL1_FacAddr&  thePPPAddr,
                          TL1_PPPEntParameters& theEntParameters,
                          TL1_Response&          theResponse ) = 0;

    virtual void EdPPP(  const CT_TL1_FacAddr& thePPPAddr,
                          TL1_PPPEdParameters& theEdParameters, 			
                          TL1_Response&         theResponse ) = 0;

    virtual void RtrvPPP( const CT_TL1_FacAddr& thePPPAddr,
                           CT_PPPProfAddr*       theProfileAddr,                        
                           CT_ProfileTableId*    theAlarmProfile,                        
                           CT_SM_PST*            thePrimaryState,                                    
                           TL1_Response&         theResponse ) const = 0;

    virtual void DltPPP( const CT_TL1_FacAddr&  thePPPAddr,
                          TL1_Response&          theResponse,
                          LT_Handle              theHandle,
                          LT_Ctag                theCtag ) = 0;
};


class TL1_PPPProfileEdParameters;

class TL1_PPPProfileDomain
{
public:

    virtual void EdPPPPF( const CT_TL1_LogicalAddr&         theAddr,
                           TL1_PPPProfileEdParameters&  theEdParameters, 			
                           TL1_Response&                 theResponse ) = 0;

    virtual void RtrvPPPPF(const CT_TL1_LogicalAddr&  theAddr,                                   
                            TL1_Response&          theResponse ) = 0;
};

#endif
