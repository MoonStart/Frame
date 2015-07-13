/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         Nov. 12, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Security Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SECUENTITY_H__
#define __TL1_SECUENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_SECUDOMAIN_H__
#include <TL1Core/TL1_SecuDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif


class TL1_SecuEntity : public TL1_Entity,     // Base Class
                       public TL1_SecuDomain, // Protocol Class
                       public TL1_AlarmDomain // Protocol Class

{
public:

    TL1_SecuEntity() {};

    virtual ~TL1_SecuEntity() {};
};

#endif
