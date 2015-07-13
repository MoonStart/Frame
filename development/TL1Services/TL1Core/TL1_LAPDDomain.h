/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 25, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 LAPD Profile Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDDOMAIN_H__
#define __TL1_LAPDDOMAIN_H__

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

class TL1_LAPDEdParameters;
class TL1_LAPDEntParameters;

class TL1_LAPDDomain
{
public:

    virtual void EntLapd( const CT_TL1_FacAddr&  theLapdAddr,
                          TL1_LAPDEntParameters& theEntParameters,
                          TL1_Response&          theResponse ) = 0;

    virtual void EdLapd(  const CT_TL1_FacAddr& theLapdAddr,
                          TL1_LAPDEdParameters& theEdParameters, 			
                          TL1_Response&         theResponse ) = 0;

    virtual void RtrvLapd( const CT_TL1_FacAddr& theLapdAddr,
                           CT_ProfileTableId*    theAlarmProfile,                        
                           CT_SM_PST*            thePrimaryState,                                    
                           CT_SM_SST*            theSecondaryState,                                    
                           TL1_Response&         theResponse ) const = 0;

    virtual void DltLapd( const CT_TL1_FacAddr&  theLapdAddr,
                          TL1_Response&          theResponse,
                          LT_Handle              theHandle,
                          LT_Ctag                theCtag ) = 0;
};

#endif
