/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Aug 06, 2010 - Chengsi Shao
DESCRIPTION:    Header file for TL1 Control Plane ADMREROUTE Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ARRENTITY_H__
#define __TL1_ARRENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_ARRDOMAIN_H__
#include "TL1Core/TL1_ArrDomain.h"
#endif

class TL1_AdmReRouteEntity : public TL1_Entity,
                          public TL1_AdmReRouteDomain
{
public:
    TL1_AdmReRouteEntity( );
    virtual ~TL1_AdmReRouteEntity( );
};
#endif

