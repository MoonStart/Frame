/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 10, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 NTP Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NTPENTITY_H__
#define __TL1_NTPENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_NTPDOMAIN_H__
#include <TL1Core/TL1_NTPDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif


class TL1_NtpEntity : public TL1_Entity,     // Base Class
                      public TL1_NtpDomain,  // Protocol Class                         
                      public TL1_AlarmDomain // Protocol Class                         

{
public:

    TL1_NtpEntity() {};

    virtual ~TL1_NtpEntity() {};
};

#endif
