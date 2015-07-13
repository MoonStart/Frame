/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         Oct 1, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 External Control Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONTDOMAIN_H__
#define __TL1_CONTDOMAIN_H__

#ifndef CT_EQUIPMENT
#include <CommonTypes/CT_Equipment.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

/**
   CLASS TL1_ContDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_ContDomain
{
public:

    virtual void OprExtCont(  const CT_TL1_LogicalAddr& theAddr,
                              CT_ContType* theContType,
                              CT_ContDuration* theContDuration,
                              TL1_Response& theResponse ) = 0;

    virtual void RlsExtCont(  const CT_TL1_LogicalAddr& theAddr,
                              CT_ContType* theContType,
                              CT_ContDuration* theContDuration,
                              TL1_Response& theResponse) = 0;

    virtual void RtrvAttrCont(const CT_TL1_LogicalAddr& theAddr,
                              CT_ContType* theContType,
                              TL1_Response& theResponse )const = 0;

    virtual void RtrvExtCont( const CT_TL1_LogicalAddr& theAddr,
                              CT_ContType* theContType,
                              TL1_Response& theResponse)const = 0;

    virtual void SetAttrCont( const CT_TL1_LogicalAddr& theAddr,
                              CT_ContType* theContType,
                              TL1_Response& theResponse) = 0;

    virtual void OprAco(      TL1_Response& theResponse) = 0;

};

#endif
