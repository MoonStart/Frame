/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for TL1 Control Plane Exppath Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXPPATHENTITY_H__
#define __TL1_EXPPATHENTITY_H__

#include "TL1Core/TL1_Entity.h"
#include "TL1Core/TL1_ExppathDomain.h"

class TL1_ExppathEntity : public TL1_Entity,        // Base Class
                          public TL1_ExppathDomain  // Protocol Class
{
public:
    
    TL1_ExppathEntity( );

    virtual ~TL1_ExppathEntity( );
};

#endif
