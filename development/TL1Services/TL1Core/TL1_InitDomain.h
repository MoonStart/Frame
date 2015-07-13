#ifndef __TL1_INITDOMAIN_H__
#define __TL1_INITDOMAIN_H__
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 27, 2007, Mike Rodgers
DESCRIPTION:    Header file for TL1 INIT declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#ifndef __CT_TL1_ENTITYADDR_H__
#include <CommonTypes/CT_TL1_EntityAddr.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

/**
   CLASS TL1_InitDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of facility related TL1 commands, that a TL1 Entities
   for a slot is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_InitDomain
{
public:

    virtual void InitLink( const CT_TL1_FacAddr& theAddr,
                           TL1_Response& theResponse) =0;

};

#endif
