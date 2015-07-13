/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 22, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 HdpT1 Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_HDPT1ENTITY_H__
#define __TL1_HDPT1ENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_HDPT1DOMAIN_H__
#include <TL1Core/TL1_HdpT1Domain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_FACRSPBLK_H__
#include <Response/TL1_FACRspBlk.h>
#endif


class TL1_HdpT1Entity : public TL1_Entity,         // Base Class
                        public TL1_HdpT1Domain,    // Protocol Class
                        public TL1_AlarmDomain     // Protocol Class
{
public:
    
    TL1_HdpT1Entity();

    virtual ~TL1_HdpT1Entity();
};

#endif
