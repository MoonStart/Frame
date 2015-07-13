/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 17, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Static Route Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_STATRTEDOMAIN_H__
#define __TL1_STATRTEDOMAIN_H__

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
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#include <CommonTypes/CT_EON.h>

class TL1_StatRteParameters;

class TL1_StatRteDomain
{
public:

    virtual void EntStatRte( TL1_StatRteParameters& theEntParameters,
                             TL1_Response&          theResponse ) = 0;

    virtual void EntStatRteIpv6( TL1_StatRteParameters& theEntParameters,
                            TL1_Response&          theResponse ) = 0;

    virtual void EdStatRte( TL1_StatRteParameters& theEdParameters,
                             TL1_Response&         theResponse ) = 0;

    virtual void RtrvStatRte(string       *theDestination,                 
                              TL1_Response&    theResponse ) const = 0;

    virtual void DltStatRte( TL1_StatRteParameters& theDltParameters,
                             TL1_Response&          theResponse ) = 0;


    virtual void DltStatRteIpv6( TL1_StatRteParameters& theDltParameters,
                                TL1_Response&          theResponse ) = 0;

    virtual void RtrvRteAll( TL1_Response&    theResponse ) const = 0;


};

#endif
