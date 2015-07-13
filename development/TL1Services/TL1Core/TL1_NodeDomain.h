#ifndef __TL1_NODEDOMAIN_H__
#define __TL1_NODEDOMAIN_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         October 19, 2005- Mike Rodgers
DESCRIPTION:    Header file for TL1 NODE Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_TL1_CONTROLPLANEADDR_H_
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#include <CommonTypes/CT_TL1_Base.h>

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

/**
   CLASS TL1_NodeDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_NodeDomain
{
public:

    virtual void DltNode( const CT_TL1_NodeAddr& nodeAddr,
                          TL1_Response& tl1RspBlk ) = 0;

    virtual void EdNode( const CT_TL1_NodeAddr& nodeAddr,
                         string* nodeName,
                         CT_TL1_AreaAddr* areaAddr,
                         CT_SM_PST* ctPst,
                         TL1_Response& tl1RspBlk ) = 0;

    virtual void EntNode( const CT_TL1_NodeAddr& nodeAddr,
                          string* nodeName,
                          uint32 nodeIp,
                          CT_TL1_AreaAddr areaAddr,
                          CT_SM_PST* ctPst,
                          TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvNode( const CT_TL1_NodeAddr& nodeAddr,
                           TL1_Response& tl1RspBlk )const = 0;
};

#endif
