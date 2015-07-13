/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Aug 06, 2010 - Chengsi Shao
DESCRIPTION:    Header file for TL1 ADMREROUTE declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ARRDOMAIN_H__
#define __TL1_ARRDOMAIN_H__

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

#include <LumosTypes/LT_System.h>
#include "CommonTypes/CT_ControlPlane_Definitions.h"


class TL1_OprArrParameters;

class TL1_AdmReRouteDomain
{
public:

    virtual void OprAdmReRoute( TL1_OprArrParameters&     theOprArrParms, 
                                 TL1_Response&     theResponse ) = 0 ;
};
#endif

