/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Connection Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONNDOMAIN_H__
#define __TL1_CONNDOMAIN_H__

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
#include <CommonTypes/CT_ControlPlane_Requests.h>

class TL1_ConnEntParameters;
class TL1_ConnEdParameters;
class TL1_ConnRtrvParameters;
class CT_ControlPlane_CallId;
class CT_TL1_NodeAddr;
class CT_ControlPlane_ConnectionId;
class TL1_ConnRouteParameters;

class TL1_ConnDomain
{
public:

    virtual void EntConn( TL1_ConnEntParameters& theEntParameters,
                          TL1_Response&          theResponse ) = 0;

    virtual void RtrvConn( TL1_ConnRtrvParameters& theRtrvParameters,
                           TL1_Response&           theResponse ) const = 0;

    virtual void DltConn( CT_TL1_NodeAddr*              theNodeId,
                          CT_ControlPlane_ConnectionId* theConnId,
                          bool*                         theForced,
                          TL1_Response&                 theResponse,
                          LT_Handle                     theHandle,
                          LT_Ctag                       theCtag,
                          const CONN_DELETE*            theFalData ) = 0;

    virtual void EdConn( TL1_ConnEdParameters& theEdParameters,
                         TL1_Response&         theResponse ) = 0;

    virtual void RtrvConnInfo( CT_ControlPlane_CallId* theCallId,
                               CT_TL1_NodeAddr*             theNodeId,
                               uint8                        theMultiplier,
                               TL1_Response&                theResponse ) const = 0;

    virtual void RtrvConnRoute( TL1_ConnRouteParameters& theParameters,
                                TL1_Response&                   theResponse ) = 0;


};

#endif
