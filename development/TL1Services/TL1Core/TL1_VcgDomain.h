/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:
AUTHOR:         July 25, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 VCG Profile Domain declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_VCGDOMAIN_H__
#define __TL1_VCGDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include "CommonTypes/CT_TL1_Base.h"
#endif

#ifndef __CT_TELECOM_H__
#include <CommonTypes/CT_Telecom.h>
#endif


#ifndef CT_CROSSCONNECT_H
#include <CommonTypes/CT_CrossConnect.h>
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
#include <CommonTypes/CT_ControlPlane_Definitions.h>

class TL1_VcgDomain
{
public:

    virtual void EntVcg( const CT_TL1_FacAddr&  theVcgAddr,
                         bool*                  theIsAutoMode,
                         CT_TEL_TermSize*       theVcatType,
                         CT_ProfileTableId*     theAlarmProfile,
                         CT_XcPath*             theCCPath,
                         uint32*                thePlcThr,
                         uint32*                theTlcThr,
                         bool*                  theHoTmr,
                         bool*                  theWtrTmr,
                         CT_FAC_NValue*         theNValue,
                         CT_TEL_VlanTag*        thePVid,
                         bool*                  theTagMode,
                         CT_TEL_Tpid*           theTPid,
                         bool*                  theProt,
                         bool*                  theLcas,
                         CT_SM_PST*             thePrimaryState,
                         LT_Handle*             myHandle,
                         LT_Ctag                myCtag,
                         TL1_Response&          theResponse ) = 0;

    virtual void EdVcg(  const CT_TL1_FacAddr& theVcgAddr,
                         CT_ProfileTableId*     theAlarmProfile,
                         uint32*                thePlcThr,
                         uint32*                theTlcThr,
                         bool*                  theHoTmr,
                         bool*                  theWtrTmr,
                         CT_FAC_NValue*         theNValue,
                         const CT_TL1_FacAddr*  theAddTtp,
                         const CT_TL1_FacAddr*  theRmvTtp,
                         CT_XcFacType           theTtpFacType,
                         const CT_TL1_FacAddr*  theAddCrs,
                         const CT_TL1_FacAddr*  theRmvCrs,
                         CT_XcFacType           theCrsFacType,
                         CT_XcType*             theCCType,
                         CT_TEL_VlanTag*        thePVid,
                         bool*                  theTagMode,
                         CT_TEL_Tpid*           theTPid,
                         bool*                  theProt,
                         bool*                  theLcas,
                         CT_VcgMapIdxRangeList* theAddTtpMapBuff,
                         CT_VcgMapIdxRangeList* theRmvTtpMapBuff,
                         CT_SM_PST*             thePrimaryState,
                         bool*                  theIsCommandForced,
                         LT_Handle*             myHandle,
                         LT_Ctag                myCtag,
                         TL1_Response&         theResponse ) = 0;

    virtual void RtrvVcg( const CT_TL1_FacAddr& theVcgAddr,
                           CT_ProfileTableId*    theAlarmProfile,
                           bool*                 theMember,
                           CT_SM_PST*            thePrimaryState,
                           CT_SM_SST*            theSecondaryState,
                           TL1_Response&         theResponse ) const = 0;

    virtual void RtrvVcgMembers( const CT_TL1_FacAddr& theVcgAddr,
                                TL1_Response&         theResponse ) const = 0;

    virtual void DltVcg( const CT_TL1_FacAddr&  theVcgAddr,
                         bool*                  theRmvMembers,
                          TL1_Response&          theResponse,
                          LT_Handle              theHandle,
                          LT_Ctag                theCtag ) = 0;
};

#endif
