/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 22, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 LAG Profile Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAGENTITY_H__
#define __TL1_LAGENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_LAGDOMAIN_H__
#include "TL1Core/TL1_LagDomain.h"
#endif

class TL1_LagEntity : public TL1_Entity,        // Base Class
                       public TL1_LagDomain,    // Protocol Class
                       public TL1_AlarmDomain    // Protocol Class
{
public:
    
    TL1_LagEntity( );

    virtual ~TL1_LagEntity( );
};

#endif
