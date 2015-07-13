/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Shawn He
DESCRIPTION:    Header file for TL1 GCC Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_GCCENTITY_H__
#define __TL1_GCCENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_GCCDOMAIN_H__
#include "TL1Core/TL1_GCCDomain.h"
#endif

class TL1_GCCEntity :  public TL1_Entity,        // Base Class
                       public TL1_GCCDomain,     // Protocol Class
                       public TL1_AlarmDomain    // Protocol Class
{
public:
    
    TL1_GCCEntity( );

    virtual ~TL1_GCCEntity( );
};

#endif
