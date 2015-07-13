#ifndef __TL1_LINKDOMAIN_H__
#define __TL1_LINKDOMAIN_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         October 19, 2005- Mike Rodgers
DESCRIPTION:    Header file for TL1 Topological and Bundled LINK Domain declaration
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

#ifndef _CT_CONTROLPLANEDEFS_H_
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __TL1_LINKPARAMETERS_H__
#include <TL1Core/TL1_LinkParameters.h>
#endif

/**
   CLASS TL1_LinkDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_LinkDomain
{
public:

    virtual void DltLink( const LT_Handle& aHandle,
                          const CT_TL1_LinkAddr& aAddr,
                          TL1_Response& tl1RspBlk ) = 0;

    virtual void EdLink( const CT_TL1_LinkAddr& aAddr,
                         TL1_LinkParameters& linkParms,
                         TL1_Response& tl1RspBlk ) = 0;

    virtual void EntLink( const CT_TL1_LinkAddr& aAddr,
                          TL1_LinkParameters& linkParms,
                          TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvLink( const CT_TL1_LinkAddr& aAddr,
                           const CT_ControlPlane_Addr* theIfIndex,
                           const CT_TL1_ResourceAddr* theResource,
                           const CT_TL1_NodeAddr* theNodeAddr,
                           const CT_TL1_NetworkPartitionAddr* theNpAddr,
                           TL1_Response& tl1RspBlk )const = 0;

    virtual void EdLinkProfile( const CT_TL1_LogicalAddr& aAddr,
                                TL1_LinkParameters& linkParms,
                                TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvLinkProfile( const CT_TL1_LogicalAddr& aAddr,
                                  TL1_Response& tl1RspBlk )const = 0;

    virtual void RtrvLadjLink(const CT_TL1_LinkAddr& addr,
                              TL1_Response&         theResponse) = 0;

    virtual void RtrvTceLink(const CT_TL1_LinkAddr& addr,
                             TL1_Response&         theResponse) = 0;


};

class TL1_TnaLinkDomain
{
public:

    virtual void DltTnaLnkMap( uint32* theTnaValue,
                               CT_Call_Tna_Types* theTnaType,
                               CT_TL1_LinkAddr* linkAddr,
                               TL1_Response& tl1RspBlk ) = 0;

    virtual void EntTnaLnkMap( uint32& theTnaValue,
                               CT_Call_Tna_Types& theTnaType,
                               CT_TL1_LinkAddr& linkAddr,
                               TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvTnaLnkMap( const uint32* theTnaValue,
                                const CT_Call_Tna_Types* theTnaType,
                                const CT_TL1_LinkAddr* linkAddr,
                                TL1_Response& tl1RspBlk )const = 0;

};

class TL1_TrLinkDomain
{
public:

    virtual void DltTrLink( const LT_Handle& aHandle,
                            const CT_TL1_LinkAddr& aAddr,
                            TL1_Response& tl1RspBlk ) = 0;

    virtual void EdTrLink( const CT_TL1_LinkAddr& aAddr,
                           TL1_TrLinkParameters& linkParms,
                           TL1_Response& tl1RspBlk ) = 0;

    virtual void EntTrLink( const CT_TL1_LinkAddr& aAddr,
                            TL1_TrLinkParameters& linkParms,
                            TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvTrLink( const CT_TL1_LinkAddr& aAddr,
                             const CT_TL1_ModuleAddr* theModuleAddr,
                             const CT_FacilitySubType* theFacSubType,
                             const CT_Adaptation* theAdaptation,
                             const CT_ControlPlane_Addr* theIfIndex,
                             TL1_Response& tl1RspBlk )const = 0;
};

class TL1_BLinkDomain
{
public:

    virtual void DltBLink( const LT_Handle& aHandle,
                          const CT_TL1_LinkAddr& aAddr,
                          TL1_Response& tl1RspBlk ) = 0;

    virtual void EdBLink( const CT_TL1_LinkAddr& aAddr,
                         TL1_BLinkParameters& theBLinkParms,
                         TL1_Response& tl1RspBlk ) = 0;

    virtual void EntBLink( const CT_TL1_LinkAddr& aAddr,
                          TL1_BLinkParameters& theBLinkParms,
                          TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvBLink( const CT_TL1_LinkAddr& aAddr,
                           TL1_Response& tl1RspBlk )const = 0;

    virtual void EdBLinkMember( const CT_TL1_LinkAddr& aAddr,
                                TL1_BLinkParameters& theBLinkParms,
                                TL1_Response& tl1RspBlk ) = 0;

    virtual void RtrvBLinkMember( const CT_TL1_LinkAddr& aAddr,
                                  TL1_Response& tl1RspBlk )const = 0;
};

#endif
