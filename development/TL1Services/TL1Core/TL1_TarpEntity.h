/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 23, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 Tarp Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TARPENTITY_H__
#define __TL1_TARPENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_TARPDOMAIN_H__
#include "TL1Core/TL1_TarpDomain.h"
#endif

class TL1_TarpEntity : public TL1_Entity,              // Base Class
                       public TL1_TarpDomain    // Protocol Class
{
public:
    
    TL1_TarpEntity( );

    virtual ~TL1_TarpEntity( );
};

#endif
