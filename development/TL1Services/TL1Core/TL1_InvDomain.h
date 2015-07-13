/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         MAy 6, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 INV declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_INVDOMAIN_H__
#define __TL1_INVDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif


#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_RTRVALLPARAMETERS_H__
#include <TL1Core/TL1_RtrvAllParameters.h>
#endif

/**
   CLASS TL1_InvDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of facility related TL1 commands, that a TL1 Entities
   for a slot is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_InvDomain
{
public:

    virtual void RtrvInv(  const CT_TL1_SlotAddr& theAddr,
                            CT_FirmwareStatus* theFirmwareStatus,
                            CT_SoftwareStatus* theSoftwareStatus,
                           TL1_Response& theResponse,
                           TL1_RtrvAllParameters* theRtrvParams = 0 ) = 0;

};

#endif
