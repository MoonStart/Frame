/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 12, 2011 - Tom Novak
DESCRIPTION:    Header file for TL1 Control Plane CpSw Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CPSWITCHENTITY_H__
#define __TL1_CPSWITCHENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_CPSWITCHDOMAIN_H__
#include "TL1Core/TL1_CpSwDomain.h"
#endif

class TL1_CpSwEntity : public TL1_Entity,        // Base Class
                       public TL1_CpSwDomain     // Protocol Class
{
public:
    
    TL1_CpSwEntity( );

    virtual ~TL1_CpSwEntity( );
};


#endif
