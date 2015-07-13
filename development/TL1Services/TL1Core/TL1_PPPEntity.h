/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Header file for TL1 PPP, PPPPF Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PPPENTITY_H__
#define __TL1_PPPENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_PPPDOMAIN_H__
#include "TL1Core/TL1_PPPDomain.h"
#endif

class TL1_PPPEntity :  public TL1_Entity,        // Base Class
                       public TL1_PPPDomain,     // Protocol Class
                       public TL1_AlarmDomain    // Protocol Class
{
public:
    
    TL1_PPPEntity( );

    virtual ~TL1_PPPEntity( );
};

class TL1_PPPProfileEntity : public TL1_Entity,              // Base Class
                              public TL1_PPPProfileDomain    // Protocol Class
{
public:
    
    TL1_PPPProfileEntity( );

    virtual ~TL1_PPPProfileEntity( );
};

#endif
