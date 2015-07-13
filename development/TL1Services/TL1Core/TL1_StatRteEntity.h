/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 17, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Control Plane Static Route Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_STATRTEENTITY_H__
#define __TL1_STATRTEENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_STATRTEDOMAIN_H__
#include "TL1Core/TL1_StatRteDomain.h"
#endif

class TL1_StatRteEntity : public TL1_Entity,          // Base Class
                          public TL1_StatRteDomain    // Protocol Class
{
public:
    
    TL1_StatRteEntity( );

    virtual ~TL1_StatRteEntity( );
};

#endif
