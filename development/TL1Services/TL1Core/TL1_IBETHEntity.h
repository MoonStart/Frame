/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:        
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IBETHENTITY_H__
#define __TL1_IBETHENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_IBETHDOMAIN_H__
#include "TL1Core/TL1_IBETHDomain.h"
#endif

class TL1_IBETHEntity :  public TL1_Entity,
                       public TL1_IBETHDomain,
                       public TL1_AlarmDomain
{
public:
    
    TL1_IBETHEntity( );

    virtual ~TL1_IBETHEntity( );
};

#endif
