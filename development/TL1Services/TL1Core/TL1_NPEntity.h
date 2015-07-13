/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 NP Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NPENTITY_H__
#define __TL1_NPENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_NPDOMAIN_H__
#include "TL1Core/TL1_NPDomain.h"
#endif

class TL1_NPEntity : public TL1_Entity,        // Base Class
                      public TL1_NPDomain    // Protocol Class
{
public:
    
    TL1_NPEntity( );

    virtual ~TL1_NPEntity( );
};

#endif
