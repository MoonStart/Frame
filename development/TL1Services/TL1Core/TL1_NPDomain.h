/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 26, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Network Partition Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NPDOMAIN_H__
#define __TL1_NPDOMAIN_H__

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

#include <LumosTypes/LT_System.h>

class TL1_NPEntParameters;
class TL1_NPEdParameters;

class TL1_NPDomain
{
public:

    virtual void EntNp( const CT_TL1_NetworkPartitionAddr&  theAddr,
                          TL1_NPEntParameters& theEntParameters,
                          TL1_Response&          theResponse ) = 0;

    virtual void EdNp( const CT_TL1_NetworkPartitionAddr&  theAddr,
                       TL1_NPEdParameters& theEdParameters,
                       TL1_Response&       theResponse ) = 0;

    virtual void RtrvNp( const CT_TL1_NetworkPartitionAddr& theAddr,                 
                           TL1_Response&         theResponse ) const = 0;

    virtual void DltNp( const CT_TL1_NetworkPartitionAddr&  theAddr,
                          TL1_Response&          theResponse,
                          LT_Handle              theHandle,
                          LT_Ctag                theCtag ) = 0;

    virtual void RtrvNpStats( const CT_TL1_NetworkPartitionAddr& theAddr,                 
                              TL1_Response&         theResponse ) const = 0;


};

#endif
