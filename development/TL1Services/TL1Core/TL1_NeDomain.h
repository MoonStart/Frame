/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 3, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Ne Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NEDOMAIN_H__
#define __TL1_NEDOMAIN_H__

#ifndef __CT_TL1_EQUIPMENT_H__
#include <CommonTypes/CT_TL1_Equipment.h>
#endif

#ifndef __CT_Equipment_H__
#include <CommonTypes/CT_Equipment.h>
#endif

#ifndef __CT_CARDSTATUSMONITORING_H__
#include <CommonTypes/CT_CardStatusMonitoring.h>
#endif

#ifndef __CT_CARD_INVENTORY_H__
#include <CommonTypes/CT_CardInventory.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_TIMEZONE_H_
#include <CommonTypes/CT_TimeZone.h>
#endif

#ifndef _CT_CONTROLPLANEDEFS_H_
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#endif

#include <CommonTypes/CT_ARC_Definitions.h>
class TL1_Response;


/**
   CLASS TL1_NeDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of equipment related TL1 command a TL1 Entity
   for an Ne is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_NeDomain
{
public:
    virtual void EdNe( CT_EqName* theName,
                       CT_NodeConfiguration* theNodeConfiguration,
                       CT_NodeSubTypeConfiguration* theSubNodeConfiguration,
                       CT_NodeReleaseConfiguration* theHWVersion,
                       CT_NodeSpanConfiguration* theSpanA,
                       CT_NodeSpanConfiguration* theSpanB,
                       string* theNeLocation,
                       string* theSID,
                       string* theSite,
                       CT_TimeZone* theTimeZone,
                       bool* theDSP,
                       CT_NodeStsVcMode* theStsVcMode,
                       CT_ARCInterval* theStsVcArcIntvHr,
                       CT_ARCInterval* theStsVcArcIntvMn,
                       CT_SyncOsc* theSyncOsc,
                       uint8* theDefInterPacketGap,
                       bool* isCommandForced,
                       int* theIntValueIntA,
                       CT_DCM_FiberType* theFiberTypeIntA,
                       bool* theLowLatencyIntA,
                       int* theIntValueIntB,
                       CT_DCM_FiberType* theFiberTypeIntB,
                       bool* theLowLatencyIntB,
                       int* theIntValueIntC,
                       CT_DCM_FiberType* theFiberTypeIntC,
                       bool* theLowLatencyIntC,
                       int* theIntValueIntD,
                       CT_DCM_FiberType* theFiberTypeIntD,
                       bool* theLowLatencyIntD,
                       int* theIntValueIntE,
                       CT_DCM_FiberType* theFiberTypeIntE,
                       bool* theLowLatencyIntE,
                       int* theIntValueIntF,
                       CT_DCM_FiberType* theFiberTypeIntF,
                       bool* theLowLatencyIntF,
                       int* theIntValueIntG,
                       CT_DCM_FiberType* theFiberTypeIntG,
                       bool* theLowLatencyIntG,
                       int* theIntValueIntH,
                       CT_DCM_FiberType* theFiberTypeIntH,
                       bool* theLowLatencyIntH,
                       int* theIntValueExtA,
                       CT_DCM_FiberType* theFiberTypeExtA,
                       bool* theLowLatencyExtA,
                       int* theIntValueExtB,
                       CT_DCM_FiberType* theFiberTypeExtB,
                       bool* theLowLatencyExtB,
                       int* theIntValueExtC,
                       CT_DCM_FiberType* theFiberTypeExtC,
                       bool* theLowLatencyExtC,
                       int* theIntValueExtD,
                       CT_DCM_FiberType* theFiberTypeExtD,
                       bool* theLowLatencyExtD,
                       int* theIntValueExtE,
                       CT_DCM_FiberType* theFiberTypeExtE,
                       bool* theLowLatencyExtE,
                       int* theIntValueExtF,
                       CT_DCM_FiberType* theFiberTypeExtF,
                       bool* theLowLatencyExtF,
                       int* theIntValueExtG,
                       CT_DCM_FiberType* theFiberTypeExtG,
                       bool* theLowLatencyExtG,
                       int* theIntValueExtH,
                       CT_DCM_FiberType* theFiberTypeExtH,
                       bool* theLowLatencyExtH,
                       CT_ProfileTableId* theSysAlmPf,
                       CT_CPInit* theCpInit,
					   CT_MfgCtrl* theMfgCtrl,
                       CT_SM_PST* thePrimaryState,
                       TL1_Response& theResponse ) = 0;

    virtual void RtrvNe( TL1_Response& theResponse ) = 0;

	virtual void SetSid( string* theSID, TL1_Response& theResponse) = 0;
};

#endif //__TL1_NEDOMAIN_H__
