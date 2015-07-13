/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         2013.9.16 - Gang Zhu
DESCRIPTION:    Header file for TL1 MGTETH Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MGTETHENTITY_H__
#define __TL1_MGTETHENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_MGTETHDOMAIN_H__
#include "TL1Core/TL1_MgtETHDomain.h"
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

class TL1_MgtETHEntity : public TL1_Entity,        // Base Class
                            public TL1_MgtETHDomain,    // Protocol Class
                            public TL1_AlarmDomain
{
public:
    
    TL1_MgtETHEntity( );

    virtual ~TL1_MgtETHEntity( );
};

#endif

