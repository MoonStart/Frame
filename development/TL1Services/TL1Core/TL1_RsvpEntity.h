/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 13, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 RSVP and RSVPADJ Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RSVPENTITY_H__
#define __TL1_RSVPENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_RSVPDOMAIN_H__
#include "TL1Core/TL1_RsvpDomain.h"
#endif

class TL1_RsvpEntity : public TL1_Entity,        // Base Class
                       public TL1_RsvpDomain     // Protocol Class
{
public:
    
    TL1_RsvpEntity( );

    virtual ~TL1_RsvpEntity( );
};


class TL1_RsvpAdjEntity : public TL1_Entity,           // Base Class
                          public TL1_RsvpAdjDomain,    // Protocol Class
                          public TL1_AlarmDomain       // Protocol Class
{
public:
    
    TL1_RsvpAdjEntity( );

    virtual ~TL1_RsvpAdjEntity( );
};

#endif
