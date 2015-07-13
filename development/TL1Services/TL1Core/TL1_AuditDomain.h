/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Audit Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_AUDITDOMAIN_H__
#define __TL1_AUDITDOMAIN_H__


//#ifndef __CT_TL1_AUDIT_H__
//#include <CommonTypes/CT_TL1_Audit.h>
//#endif

/**
   CLASS TL1_AuditDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of audit related TL1 commands, that a TL1 Entities
   for an audit is expected to implement. This class contains no
   data member nor any default implementation.
 */

// Not completetely defined for AP100, to be updated later.

class TL1_AuditDomain
{
public:

    virtual void AlwAudData( ) = 0;    //AP300

    virtual void AudData( ) = 0;       //AP300

    virtual void AudEqpt( ) = 0;       //AP300

    virtual void InhAudData( ) = 0;    //AP300
};

#endif
