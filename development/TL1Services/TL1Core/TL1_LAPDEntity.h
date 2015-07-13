/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 22, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 LAPD Profile Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDENTITY_H__
#define __TL1_LAPDENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_LAPDDOMAIN_H__
#include "TL1Core/TL1_LAPDDomain.h"
#endif

class TL1_LAPDEntity : public TL1_Entity,        // Base Class
                       public TL1_LAPDDomain,    // Protocol Class
                       public TL1_AlarmDomain    // Protocol Class
{
public:
    
    TL1_LAPDEntity( );

    virtual ~TL1_LAPDEntity( );
};

#endif
