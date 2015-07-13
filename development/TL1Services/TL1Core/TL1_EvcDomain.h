/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 15, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 cross-connection Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EVCDOMAIN_H__
#define __TL1_EVCDOMAIN_H__

#ifndef __CT_XCTYPES_H__
#include <CommonTypes/CT_XcTypes.h>
#endif

#ifndef __CT_TELECOM_H__
#include <CommonTypes/CT_Telecom.h>
#endif

#ifndef __CT_EVCDATA_H__
#include <CommonTypes/CT_EvcData.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef CT_TESTACCESSTYPES_H
#include <CommonTypes/CT_TestAccessTypes.h>
#endif

#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_AM_Definitions.h>

#include <LumosTypes/LT_System.h>
#include <list>
class CT_TL1_EvcAddr;
class TL1_Response;

/**
   CLASS TL1_EvcDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of Evc related TL1 commands, that a TL1 Entities
   for a Evc is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_EvcDomain
{
public:

    virtual void RtrvEvc(const CT_EvcData& theEvcId,
                         const CT_TL1_EvcAddr& theAddr,
                         TL1_Response& theResponse) = 0;

    virtual void EntEvc( const CT_EvcData& theEvcId,
                         const CT_TL1_EvcAddr& theAddr,
                         string* theCircuitId,
                         bool* theRdld,
                         CT_TEL_VlanTag* theSVid,
                         list<CT_TEL_VlanTag>* theAddCVid,
                         list<CT_TEL_VlanTag>* theAddSVid,
                         int* theBwpfCOS0,
                         bool* theIsAllFrame,
                         bool* theDiscPause,
                         CT_TEL_PbitRegen* thePbitRegen,
                         bool* theAisState,
                         int*  theAisInterval,
                         int*  theAisMegLevel,
                         CT_TEL_MacMode* theDestMacModeLevel,
                         CT_ProfileTableId* theAlarmProfile,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;
    
    virtual void EdEvc(  const CT_EvcData& theEvcId,
                         string* theCircuitId,
                         bool* theRdld,
                         bool* theIncl,
                         bool* theQua, 
                         CT_TEL_VlanTag* theSVid,
                         list<CT_TEL_VlanTag>* theAddCVid,
                         list<CT_TEL_VlanTag>* theAddSVid,
                         list<CT_TEL_VlanTag>* theRmvCVid,
                         list<CT_TEL_VlanTag>* theRmvSVid,
                         int* theBwpfCOS0,
                          bool* theDiscPause,
                         CT_TEL_PbitRegen* thePbitRegen,
                         bool* theAisState,
                         int*  theAisInterval,
                         int*  theAisMegLevel,
                         CT_TEL_MacMode* theDestMacModeLevel,
                         bool* theLoopbackState,
                         CT_FAC_LoopBackType* theLoopbackType,
                         CT_ProfileTableId* theAlarmProfile,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;
    
    virtual void DltEvc( const CT_EvcData& theEvcId,
                         bool* theIncl,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;

};

#endif
