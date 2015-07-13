/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 12, 2011 - Tom Novak
DESCRIPTION:    Header file for TL1 CpSwitch Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CPSWITCHDOMAIN_H__
#define __TL1_CPSWITCHDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include "CommonTypes/CT_TL1_Base.h"
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#include "CommonTypes/CT_ControlPlane_Definitions.h"
#include "CommonTypes/CT_ControlPlane_Convert.h"


class TL1_CpSwDomain
{
public:

    virtual void OprCpSw( const CT_CpSw_Cmd&              theSwCmd,
                          const bool&                     theAllCalls,
                          const CT_ControlPlane_CallId&   theCallId,
                          const CT_CallPathType*          thePathType,
                          TL1_Response&                   theResponse ) = 0;

    virtual void RlsCpSw( const bool&                     theAllCalls,
                          const CT_ControlPlane_CallId&   theCallId,
                          TL1_Response&                   theResponse ) = 0;

};

#endif
