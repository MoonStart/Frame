/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 13, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 RSVP and RSVPADJ Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RSVPDOMAIN_H__
#define __TL1_RSVPDOMAIN_H__

#ifndef __CT_TL1_CONTROLPLANEADDR_H__
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#ifndef __CT_TELECOM_H__
#include <CommonTypes/CT_Telecom.h>
#endif

#ifndef __CT_AGENTFACILITY_H__
#include <CommonTypes/CT_AgentFacility.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#include <LumosTypes/LT_System.h>
#include <LumosTypes/LT_Rsvp.h>
#include <CommonTypes/CT_AM_Definitions.h>


class TL1_RsvpDomain
{
public:

    virtual void EntRsvp( const CT_TL1_ControllerAddr&  theAddr,
                          uint32*               theSignalCtlId,
                          CT_TL1_LinkAddr*     theInterfaceAid,
                          TL1_Response&          theResponse ) = 0;

    virtual void RtrvRsvp( const CT_TL1_ControllerAddr&   theAddr,                 
                           TL1_Response&         theResponse ) const = 0;

    virtual void DltRsvp( const CT_TL1_ControllerAddr&  theAddr,
                          TL1_Response&          theResponse,
                          LT_Handle              theHandle,
                          LT_Ctag                theCtag ) = 0;

};

class TL1_RsvpAdjDomain
{
public:

    virtual void EntRsvpAdj( const CT_TL1_AdjacencyAddr&  theAddr,
                             uint32*            theNgbrSignalAddr,
                             uint32*            theNgbrSignalId,
                             const LT_AlmSetClr& theSetClrAlarm,
                             CT_SM_PST*         thePst,
                             TL1_Response&      theResponse ) = 0;

    virtual void RtrvRsvpAdj( const CT_TL1_AdjacencyAddr&   theAddr, 
                              CT_TL1_NetworkPartitionAddr*  theNetPart,
                              CT_SM_PST*                    thePst,
                              CT_SM_SST*                    theSst,                
                              TL1_Response&         theResponse ) const = 0;

    virtual void EdRsvpAdj( const CT_TL1_AdjacencyAddr& theAddr,
                            CT_ProfileTableId*          theAlmProfile,
                            const LT_AlmSetClr&         theSetClrAlarm,
                            CT_SM_PST*                  thePst,
                            TL1_Response&               theResponse,
                            LT_Handle                   theHandle ) = 0;

    virtual void DltRsvpAdj( const CT_TL1_AdjacencyAddr&  theAddr,
                             TL1_Response&          theResponse,
                             LT_Handle              theHandle,
                             LT_Ctag                theCtag ) = 0;


};

#endif
