/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2009 - Tom Novak
DESCRIPTION:    Header file for TL1 Ping Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PINGENTITY_H__
#define __TL1_PINGENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_PINGDOMAIN_H__
#include "TL1Core/TL1_PingDomain.h"
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

class TL1_PingEntity :  public TL1_Entity,        // Base Class
                        public TL1_PingDomain     // Protocol Class
{
public:
    
    TL1_PingEntity( );

    virtual ~TL1_PingEntity( );
};

#endif
