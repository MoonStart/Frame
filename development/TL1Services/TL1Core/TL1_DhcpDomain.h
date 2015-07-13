
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         October 19, 2005- Mike Rodgers
DESCRIPTION:    Header file for TL1 DHCP Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DHCPDOMAIN_H__
#define __TL1_DHCPDOMAIN_H__

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_TL1_BASE_H_
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

/**
   CLASS TL1_DhcpDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */

class TL1_DhcpDomain
{
public:

    virtual void EdDhcp(	const CT_TL1_LogicalAddr& aAddr,
									CT_ProfileTableId* ctAlarmProfile,
									bool* ctOption82,
                                    uint32* ctSrvrIp,
									bool* ctDhcpStatus,
									uint32* ctMinIp,
									uint32* ctMaxIp,
                                    bool* ctCmdMode,
									CT_SM_PST* ctPst,
									TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvDhcp(	const CT_TL1_LogicalAddr& aAddr,
                             TL1_Response& tl1RspBlk)const = 0;
    
    virtual void DltDhcpIpaddr(	const CT_TL1_LogicalAddr& aAddr,
         uint32* ctRneIp,
         bool* ctCmdMode,
         TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvDhcpIpaddr(	const CT_TL1_LogicalAddr& aAddr,
                             TL1_Response& tl1RspBlk)const = 0;
};

#endif
