/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 11, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 OSI Profile Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSIENTITY_H__
#define __TL1_OSIENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_OSIDOMAIN_H__
#include "TL1Core/TL1_OSIDomain.h"
#endif

class TL1_OSIRTREntity : public TL1_Entity,        // Base Class
                         public TL1_OSIRTRDomain,  // Protocol Class
                         public TL1_AlarmDomain    // Protocol Class
{
public:
    
    TL1_OSIRTREntity( );

    virtual ~TL1_OSIRTREntity( );
};

#endif
