/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 6, 2003- Stephen Wu
DESCRIPTION:    Header file for TL1 EON Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EONENTITY_H__
#define __TL1_EONENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_EONDOMAIN_H__
#include <TL1Core/TL1_EONDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

class TL1_EONEntity : public TL1_Entity,     // Base Class
                     public TL1_EONDomain,    // Protocol Class
					 public TL1_AlarmDomain  // Alarm


{
public:
    TL1_EONEntity();

    virtual ~TL1_EONEntity();

};

#endif // __TL1_NEENTITY_H__
