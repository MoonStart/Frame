#ifndef __TL1_OSPFDOMAIN_H__
#define __TL1_OSPFDOMAIN_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 30, 2007- Lee Gernes
DESCRIPTION:    Header file for TL1 OSPF Domain declaration
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

#ifndef __CT_OSPF_H_
#include <CommonTypes/CT_EON.h>
#endif

/**
   CLASS TL1_OspfDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_OspfParameters;
class TL1_OspfrpEntParameters;
class TL1_OspfrpEdParameters;

class TL1_OspfDomain
{
public:

    virtual void EntOspf( const CT_TL1_ControllerAddr&  theAddr,
                          uint32*                       theRouterId,
                          bool*                         theOspfAsbr,
                          CT_SM_PST*                    thePst,
                          TL1_Response&                 theResponse ) = 0;

    virtual void EdOspf(  const CT_TL1_ControllerAddr&  theAddr,
                          uint32*                       theRouterId,
                          bool*                         theCommandMode,
                          CT_SM_PST*                    thePst,
                          TL1_Response&                 theResponse ) = 0;

    virtual void DltOspf( const CT_TL1_ControllerAddr& theAddr,
                             TL1_Response& theResponse ) = 0;

    virtual void RtrvOspf(const CT_TL1_ControllerAddr& theAddr,
                             CT_SM_PST* thePst,
                             TL1_Response& theResponse )const = 0;
};

// OSPFADJ
class TL1_OspfAdjDomain
{
public:

    virtual void EntOspfAdj( const CT_TL1_AdjacencyAddr& theAddr,
                             TL1_OspfParameters& theParameters,
                             TL1_Response& theResponse ) = 0;

    virtual void EdOspfAdj(  const CT_TL1_AdjacencyAddr& theAddr,
                             TL1_OspfParameters& theParameters,
                             TL1_Response& theResponse ) = 0;

    virtual void DltOspfAdj( const CT_TL1_AdjacencyAddr& theAddr,
                             TL1_Response& theResponse ) = 0;

    virtual void RtrvOspfAdj(const CT_TL1_AdjacencyAddr& theAddr,
                             CT_TL1_LinkAddr* theInterfaceAddr,
                             CT_TL1_AreaAddr* theAreaAddr,
                             CT_Adj_Status* theAdjStatus,
                             CT_SM_PST* thePst,
                             TL1_Response& theResponse )const = 0;
};

// OSPFAREA
class TL1_OspfAreaDomain
{
public:

    virtual void EntOspfArea( const CT_TL1_AreaAddr&    theAddr,
                              uint32*                   theRouterAreaId,
                              CT_TL1_LogicalAddr*       thePrtPfAddr,
                              bool*                     theHub,
                              CT_RROVisibilityType*     theRroVisibility,
                              CT_SM_PST*                thePst,
                              TL1_Response&             theResponse ) = 0;

    virtual void EdOspfArea( const CT_TL1_AreaAddr& theAddr,
                             CT_TL1_LogicalAddr*       thePrtPfAddr,
                             bool*                  theCommandMode,
                             bool*                  theHub,
                             CT_RROVisibilityType*  theRroVisibility,
                             CT_SM_PST*             thePst,
                             TL1_Response&          theResponse ) = 0;

    virtual void DltOspfArea( const CT_TL1_AreaAddr& theAddr,
                             TL1_Response& theResponse ) = 0;

    virtual void RtrvOspfArea(const CT_TL1_AreaAddr& theAreaAddr,
                             CT_SM_PST* thePst,
                             TL1_Response& theResponse )const = 0;
};

// OSPFRPMAP
class TL1_OspfrpmapDomain
{
public:

    virtual void EntOspfrpmap( const CT_TL1_RpMapAddr& theAddr,
                               TL1_Response& theResponse ) = 0;

    virtual void DltOspfrpmap( const CT_TL1_RpMapAddr& theAddr,
                               TL1_Response& theResponse ) = 0;

    virtual void RtrvOspfrpmap(const CT_TL1_RpMapAddr& theAddr,
                               TL1_Response& theResponse )const = 0;
};

// OSPFRP
class TL1_OspfrpDomain
{
public:

    virtual void EntOspfrp( const CT_TL1_RpAddr& theAddr,
                            TL1_OspfrpEntParameters& theParameters,
                            TL1_Response& theResponse ) = 0;

    virtual void EdOspfrp(  const CT_TL1_RpAddr& theAddr,
                            TL1_OspfrpEdParameters& theParameters,
                            TL1_Response& theResponse ) = 0;

    virtual void DltOspfrp( const CT_TL1_RpAddr& theAddr,
                             TL1_Response& theResponse ) = 0;

    virtual void RtrvOspfrp(const CT_TL1_RpAddr& theAddr,
                            uint32* theChildRoutingAreaId,
                            uint32* theParentRoutingAreaId,
                            CT_Ospfrp_Entry_Type* theEntryType,
                            TL1_Response& theResponse )const = 0;
};

#endif
