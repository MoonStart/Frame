/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 22, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 LAPD Profile Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDPROFILEDOMAIN_H__
#define __TL1_LAPDPROFILEDOMAIN_H__

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

class TL1_LAPDProfileEdParameters;

class TL1_LAPDProfileDomain
{
public:

    virtual void EdLapdPf( const CT_TL1_FacAddr&         theAddr,
                           TL1_LAPDProfileEdParameters&  theEdParameters, 			
                           TL1_Response&                 theResponse ) = 0;

    virtual void RtrvLapdPf(const CT_TL1_FacAddr&  theFacAddr,                                   
                            TL1_Response&          theResponse ) = 0;
};

#endif
