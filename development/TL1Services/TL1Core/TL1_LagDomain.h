/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 25, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 LAG Profile Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAGDOMAIN_H__
#define __TL1_LAGDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include "CommonTypes/CT_TL1_Base.h"
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


class TL1_LagDomain
{
public:

    virtual void EntLag( const CT_TL1_FacAddr&  theLagAddr,
                         CT_TL1_FacAddr*    theAddEthAddr,
                         CT_FacilitySubType theAddEthType,
                         CT_TEL_VlanTag*    theVlanTag,
                         bool*              theTagMode,
                         CT_TEL_Tpid*       theTpid,
                         int*               theCFProfile,
                         bool*              theLacpEnabled,
                         int*               theSystemPriority,
                         char*              theSystemIdentifier,
                         CT_TEL_LacpTimeoutMode* theTimeoutMode,
                         CT_ProfileTableId* theAlarmProfile,
                         CT_SM_PST*         thePrimaryState,
                         TL1_Response&          theResponse ) = 0;

    virtual void EdLag(  const CT_TL1_FacAddr& theLagAddr,
                         CT_TL1_FacAddr*    theAddEthAddr,
                         CT_FacilitySubType theAddEthType,
                         CT_TL1_FacAddr*    theRmvEthAddr,
                         CT_FacilitySubType theRmvEthType,
                         CT_TEL_VlanTag*    theVlanTag,
                         bool*              theTagMode,
                         CT_TEL_Tpid*       theTpid,
                         int*               theCFProfile,
                         bool*              theLacpEnabled,
                         int*               theSystemPriority,
                         char*              theSystemIdentifier,
                         CT_TEL_LacpTimeoutMode* theTimeoutMode,
                         CT_ProfileTableId* theAlarmProfile,
                         bool*              theCommandMode,
                         CT_SM_PST*         thePrimaryState,
                         TL1_Response&         theResponse ) = 0;

    virtual void RtrvLag( const CT_TL1_FacAddr& theLagAddr,
                           CT_ProfileTableId*    theAlarmProfile,
                           bool*                 theMember,
                           CT_SM_PST*            thePrimaryState,                                    
                           CT_SM_SST*            theSecondaryState,                                    
                           TL1_Response&         theResponse ) const = 0;

    virtual void RtrvLagMembers( const CT_TL1_FacAddr& theLagAddr,
                           TL1_Response&         theResponse ) const = 0;

    virtual void DltLag( const CT_TL1_FacAddr&  theLagAddr,
                         TL1_Response&          theResponse,
                         LT_Handle              theHandle,
                         LT_Ctag                theCtag,
                         bool*                  theRmvMembers ) = 0;
};

#endif
