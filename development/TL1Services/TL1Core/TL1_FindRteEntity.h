#ifndef __TL1_FINDRTEENTITY_H__
#define __TL1_FINDRTEENTITY_H__
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 11, 2011 - TLD
DESCRIPTION:    Header file for TL1 Control Plane FindRte Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#include "TL1Core/TL1_Entity.h"
#include "TL1Core/TL1_FindRteDomain.h"



class TL1_FindRteEntity : public TL1_Entity,        // Base Class
                          public TL1_FindRteDomain  // Protocol Class
{
public:
    
    TL1_FindRteEntity( );

    virtual ~TL1_FindRteEntity( );
};

#endif // __TL1_FINDRTEENTITY_H__
