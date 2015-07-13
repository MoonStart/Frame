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

#ifndef __TL1_FACILITYENTITY_H__
#define __TL1_FACILITYENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_FACDOMAIN_H__
#include <TL1Core/TL1_FacDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_BERDOMAIN_H__
#include <TL1Core/TL1_BerDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_FACRSPBLK_H__
#include <Response/TL1_FACRspBlk.h>
#endif

#ifndef __TL1_FACILITYEDPARAMETERS_H__
#include <TL1Core/TL1_FacilityEdParameters.h>
#endif

#ifndef __TL1_FACILITYENTPARAMETERS_H__
#include <TL1Core/TL1_FacilityEntParameters.h>
#endif

class TL1_FacilityEntity : public TL1_Entity,         // Base Class
                           public TL1_FacilityDomain, // Protocol Class
                           public TL1_AlarmDomain,    // Protocol Class
                           public TL1_BerDomain,    // Protocol Class
                           public TL1_FacilityValidateEdParameters,
                           public TL1_FacilityValidateEntParameters
{
public:
    
    TL1_FacilityEntity();

    virtual ~TL1_FacilityEntity();
};

#endif
