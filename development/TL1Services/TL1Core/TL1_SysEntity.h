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

#ifndef __TL1_FACENTITY_H__
#define __TL1_FACENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_SYSDOMAIN_H__
#include <TL1Core/TL1_SysDomain.h>
#endif

#ifndef __TL1_AUDITDOMAIN_H__
#include <TL1Core/TL1_AuditDomain.h>
#endif

#ifndef __TL1_SWMGTDOMAIN_H__
#include <TL1Core/TL1_SwMgtDomain.h>
#endif

#ifndef __TL1_PMSYSTEMDOMAIN_H__
#include <TL1Core/TL1_PmSysDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif


class TL1_SystemEntity : public TL1_Entity,       // Base Class
                         public TL1_SystemDomain, // Protocol Class
                         public TL1_AuditDomain,  // Protocol Class
                         public TL1_SwMgtDomain,  // Protocol Class                         
                         public TL1_PmSystemDomain   // Protocol Class                         
{
public:

    TL1_SystemEntity();

    virtual ~TL1_SystemEntity();

};

#endif
