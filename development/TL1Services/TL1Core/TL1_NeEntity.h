/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 3, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Ne Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NEENTITY_H__
#define __TL1_NEENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_NEDOMAIN_H__
#include <TL1Core/TL1_NeDomain.h>
#endif

class TL1_NeEntity : public TL1_Entity,     // Base Class
                     public TL1_NeDomain    // Protocol Class

{
public:
    TL1_NeEntity();
    virtual ~TL1_NeEntity();
};

#endif // __TL1_NEENTITY_H__
