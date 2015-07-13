#ifndef __TL1_DAENTITY_H__
#define __TL1_DAENTITY_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Keith Halsall - August 7, 2012
DESCRIPTION:    Header file for TL1 DA Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_DADOMAIN_H__
#include "TL1Core/TL1_DaDomain.h"
#endif


class TL1_DaEntity :   public TL1_Entity,       // Base Class
                       public TL1_DaDomain      // Protocol Class
{
public:
    
    TL1_DaEntity() {};

    virtual ~TL1_DaEntity() {};
};
#endif
