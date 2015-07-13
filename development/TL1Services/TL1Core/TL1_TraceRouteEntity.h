/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2009 - Tom Novak
DESCRIPTION:    Header file for TL1 Trace Route Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TRACEROUTEENTITY_H__
#define __TL1_TRACEROUTEENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_TRACEROUTEDOMAIN_H__
#include "TL1Core/TL1_TraceRouteDomain.h"
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

class TL1_TraceRouteEntity :    public TL1_Entity,          // Base Class
                                public TL1_TraceRouteDomain // Protocol Class
{
public:
    
    TL1_TraceRouteEntity( );

    virtual ~TL1_TraceRouteEntity( );
};

#endif
