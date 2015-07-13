/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 19, 2007 - Ed Bandyk
DESCRIPTION:    Header file for TL1 SNMP Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SNMPENTITY_H__
#define __TL1_SNMPENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_SNMPDOMAIN_H__
#include <TL1Core/TL1_SnmpDomain.h>
#endif

class TL1_SnmpEntity : public TL1_Entity,     // Base Class
                     public TL1_SnmpDomain    // Protocol Class


{
public:
    TL1_SnmpEntity();

    virtual ~TL1_SnmpEntity();

};

#endif // __TL1_SNMPENTITY_H__
