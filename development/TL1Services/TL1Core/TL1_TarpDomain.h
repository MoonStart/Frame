/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 23, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 Tarp Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TARPDOMAIN_H__
#define __TL1_TARPDOMAIN_H__

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

class TL1_TarpEdParameters;

class TL1_TarpDomain
{
public:

    virtual void EdFac  ( const CT_TL1_FacAddr&  theAddr,
                          TL1_TarpEdParameters&  theEdParameters, 			
                          TL1_Response&          theResponse ) = 0;

    virtual void RtrvFac( const CT_TL1_FacAddr& theLapdAddr,
                          CT_ProfileTableId*    theAlarmProfile,                        
                          CT_SM_PST*            thePrimaryState,                                    
                          CT_SM_SST*            theSecondaryState,                                    
                          TL1_Response&         theResponse ) const = 0;
};

#endif
