/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 02, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 CALL Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CALLDOMAIN_H__
#define __TL1_CALLDOMAIN_H__


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
#include "CommonTypes/CT_ControlPlane_Convert.h"
#include <CommonTypes/CT_ControlPlane_Requests.h>

class TL1_CallEntParameters;
class TL1_CallRtrvParameters;
class CT_ControlPlane_CallId;
class CT_TL1_NodeAddr;

class TL1_CallDomain
{
public:

    virtual void EntCall( TL1_CallEntParameters&        theEntParameters,
                          TL1_Response&                 theResponse ) = 0;

    virtual void EdCall( TL1_CallEntParameters&         theEntParameters,
                          TL1_Response&                 theResponse ) = 0;

    virtual void RtrvCall( TL1_CallRtrvParameters&      theRtrvParameters,
                           TL1_Response&                theResponse ) const = 0;

    virtual void DltCall( CT_ControlPlane_CallId*       theCallId,
                          CT_TL1_NodeAddr*              theNodeId,
                          TL1_Response&                 theResponse,
                          LT_Handle                     theHandle,
                          LT_Ctag                       theCtag,
                          const CALL_DELETE*            theFalData ) = 0;

    virtual void RtrvCallDetail( CT_ControlPlane_CallId*       theCallId,
                                 CT_TL1_ResourceAddr*          theCtp,
                                 TL1_Response&                 theResponse ) const = 0;
};

#endif
