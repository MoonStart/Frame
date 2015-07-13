/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         September 10, 2014 Jing Jin
DESCRIPTION:    Header file for TL1 EXDPATH Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXDPATHDOMAIN_H__
#define __TL1_EXDPATHDOMAIN_H__

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

class TL1_ExdpathParameters;
class CT_TL1_ExdpathAddr;

class TL1_ExdpathDomain
{
public:

    virtual void EntExdpath( CT_TL1_ExdpathAddr&        theExdpathAddr,
                             TL1_ExdpathParameters&     theEntParameters,
                             TL1_Response&              theResponse ) = 0;

    virtual void EdExdpath( CT_TL1_ExdpathAddr&         theExdpathAddr,
                            TL1_ExdpathParameters&      theEntParameters,
                            TL1_Response&               theResponse ) = 0;

    virtual void DltExdpath( CT_TL1_ExdpathAddr&        theExdpathAddr,
                             TL1_ExdpathParameters&     theEntParameters,
                             TL1_Response&              theResponse ) = 0;

    virtual void RtrvExdpath( CT_TL1_ExdpathAddr&       theExdpathAddr,
                              TL1_ExdpathParameters&    theEntParameters,
                              TL1_Response&             theResponse ) = 0;
};

#endif

