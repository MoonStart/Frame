/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 02, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Control Plane CALL Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CALLENTITY_H__
#define __TL1_CALLENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_CALLDOMAIN_H__
#include "TL1Core/TL1_CallDomain.h"
#endif

class TL1_CallEntity : public TL1_Entity,        // Base Class
                       public TL1_CallDomain     // Protocol Class
{
public:
    
    TL1_CallEntity( );

    virtual ~TL1_CallEntity( );
};

#endif
