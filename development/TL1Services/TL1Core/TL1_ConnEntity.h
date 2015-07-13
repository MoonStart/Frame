/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Control Plane Connection Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONNENTITY_H__
#define __TL1_CONNENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_CONNDOMAIN_H__
#include "TL1Core/TL1_ConnDomain.h"
#endif

class TL1_ConnEntity : public TL1_Entity,        // Base Class
                       public TL1_ConnDomain    // Protocol Class
{
public:
    
    TL1_ConnEntity( );

    virtual ~TL1_ConnEntity( );
};

#endif
