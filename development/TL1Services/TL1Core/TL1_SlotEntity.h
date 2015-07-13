/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Facility Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLOTENTITY_H__
#define __TL1_SLOTENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_SLOTDOMAIN_H__
#include <TL1Core/TL1_SlotDomain.h>
#endif

#ifndef __TL1_INVDOMAIN_H__
#include <TL1Core/TL1_InvDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif


class TL1_SlotEntity : public TL1_Entity,     // Base Class
                       public TL1_SlotDomain, // Protocol Class
                       public TL1_InvDomain,  // Protocol Class
                       public TL1_AlarmDomain // Protocol Class
{
public:
    
    TL1_SlotEntity() {}

    virtual ~TL1_SlotEntity() {}
};

#endif
