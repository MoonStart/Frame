/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 5, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Control Plane CPPF Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CPPFENTITY_H__
#define __TL1_CPPFENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_CPPFDOMAIN_H__
#include "TL1Core/TL1_CppfDomain.h"
#endif

class TL1_CppfEntity : public TL1_Entity,        // Base Class
                       public TL1_CppfDomain    // Protocol Class
{
public:
    
    TL1_CppfEntity() {};
    virtual ~TL1_CppfEntity() {};
};

#endif
