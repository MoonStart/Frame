/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 25, 2009 - Ed Bandyk
DESCRIPTION:    Header file for TL1 Switch Domian entity declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWITCH_DOMAIN_ENTITY_H__
#define __TL1_SWITCH_DOMAIN_ENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_SWITCHDOMAINDOMAIN_H__
#include <TL1Core/TL1_SwitchDomainDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

class TL1_Response;


/**
   CLASS TL1_SwitchDomainEntity

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of SW Management related TL1 commands, that a TL1 Entities
   for a SW is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_SwitchDomainEntity: public TL1_Entity,
                              public TL1_SwitchDomainDomain,    // Protocol Class
                              public TL1_AlarmDomain            // Protocol Class
{
public:

    TL1_SwitchDomainEntity();

    virtual ~TL1_SwitchDomainEntity();
};

#endif // __TL1_SWITCH_DOMAIN_ENTITY_H__
