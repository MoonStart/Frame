#ifndef __TL1_DADOMAIN_H__
#define __TL1_DADOMAIN_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Keith Halsall - August 7, 2012
DESCRIPTION:    Header file for TL1 DA Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_TL1_CONTROLPLANEADDR_H__
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#ifndef __CT_CONTROLPLANE_DEFINITIONS_H__
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

/**
   CLASS TL1_DaDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_DaDomain
{
public:

    virtual void EntDa( const CT_TL1_DiscoveryAgentAddr&    theAddr,
                        CT_TL1_LinkAddr*                    theDcnAddr,
                        string*                             theMgtDomain,
                        CT_SM_PST*                          thePst,
                        TL1_Response&                       theResponse ) = 0;

    virtual void EdDa(  const CT_TL1_DiscoveryAgentAddr&    theAddr,
                        CT_SM_PST*                          thePst,
                        TL1_Response&                       theResponse ) = 0;

    virtual void DltDa( const CT_TL1_DiscoveryAgentAddr&    theAddr,
                        TL1_Response&                       theResponse ) = 0;

    virtual void RtrvDa(const CT_TL1_DiscoveryAgentAddr&    theAddr,
                        TL1_Response&                       theResponse )const = 0;
};
#endif
