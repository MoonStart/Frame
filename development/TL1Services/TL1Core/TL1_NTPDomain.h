/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 10, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 NTP Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NTPDOMAIN_H__
#define __TL1_NTPDOMAIN_H__

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_NTPTYPES_H__
#include <CommonTypes/CT_NtpTypes.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_TL1_BASE_H_
#include <CommonTypes/CT_TL1_Base.h>
#endif

/**
   CLASS TL1_NtpDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_NtpDomain
{
public:

    virtual void RtrvNtpPeer(const CT_TL1_LogicalAddr& theId,
                             TL1_Response& theResponse )const = 0;

    virtual void EntNtpPeer( const CT_TL1_LogicalAddr& theId,
                             string* theIpAddress,
                             string* theName,
                             CT_SM_PST* thePst,
                             TL1_Response& theResponse ) = 0;

    virtual void EdNtpPeer(  const CT_TL1_LogicalAddr& theId,
                             string* theName,
                             CT_SM_PST* thePst,
                             TL1_Response& theResponse ) = 0;

    virtual void DltNtpPeer( const CT_TL1_LogicalAddr& theId,
                             TL1_Response& theResponse ) = 0;
};

#endif
