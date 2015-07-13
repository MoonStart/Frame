/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         September 10, 2014 Jing Jin
DESCRIPTION:    Header file for TL1 Control Plane Exdpath Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXDPATHENTITY_H__
#define __TL1_EXDPATHENTITY_H__

#include "TL1Core/TL1_Entity.h"
#include "TL1Core/TL1_ExdpathDomain.h"

class TL1_ExdpathEntity : public TL1_Entity,        // Base Class
                          public TL1_ExdpathDomain  // Protocol Class
{
public:
    
    TL1_ExdpathEntity( );

    virtual ~TL1_ExdpathEntity( );
};

#endif

