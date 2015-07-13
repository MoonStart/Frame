/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Equipment Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EQPTDOMAIN_H__
#define __TL1_EQPTDOMAIN_H__

#ifndef __CT_TL1_EQUIPMENT_H__
#include <CommonTypes/CT_TL1_Equipment.h>
#endif

#ifndef __CT_Equipment_H__
#include <CommonTypes/CT_Equipment.h>
#endif

#ifndef _INC_CT_AM_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef _CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_SMA_H__
#include <CommonTypes/CT_SMA.h>
#endif

#ifndef __CT_CARDSTATUSMONITORING_H__
#include <CommonTypes/CT_CardStatusMonitoring.h>
#endif

#ifndef __CT_TELECOM_H__
#include <CommonTypes/CT_Telecom.h>
#endif

#include <LumosTypes/LT_System.h>

class TL1_Response;
class TL1_EqptParameters;
class TL1_RtrvAllParameters;

/**
   CLASS TL1_EqptDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of equipment related TL1 command a TL1 Entity
   for an equipment is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_EqptDomain
{
public:
    virtual void DltEqpt( const CT_TL1_SlotAddr& theAddr,
                          TL1_Response& theResponse,
                          LT_Handle theHandle,
                          LT_Ctag   theCtag ) = 0;

/*
  Still Required?!?! Not visible in AP3 of the CRM...

    virtual void DiagEqpt( const CT_TL1_SlotAddr& theAddr ) = 0;
*/

    virtual void EdEqpt( const CT_TL1_SlotAddr& theAddr,
                         bool*                  theCommandMode,
                         TL1_EqptParameters&    theEqptParameters,
                         TL1_Response&          theResponse,
                         LT_Handle              theHandle,
                         LT_Ctag                theCtag) = 0;

    virtual void EntEqpt(const CT_TL1_SlotAddr& theAddr,
                            TL1_EqptParameters&     theEqptParameters,
                            TL1_Response&           theResponse,
                            LT_Handle               theHandle,
                            LT_Ctag                 theCtag) = 0;

    virtual void RmvEqpt( const CT_TL1_SlotAddr& theAddr,
                          bool* theCommandMode,
                          TL1_Response& theResponse,
                          LT_Handle theHandle,
                          LT_Ctag   theCtag  ) = 0;

    virtual void RstEqpt( const CT_TL1_SlotAddr& theAddr,
                          bool* theCommandMode,
                          TL1_Response& theResponse,
                          LT_Handle theHandle,
                          LT_Ctag   theCtag  ) = 0;


	// Not implemented in AP100
    /*virtual void MeasureOutputPower( const CT_TL1_SlotAddr& theAddr,
                                     CT_TL1_OpticalSignal* theSignal,
                                     CT_TL1_OpticalPathId* thePath,
                                     TL1_Response& theResponse ) = 0;
	*/

    virtual void RtrvEqpt( const CT_TL1_SlotAddr& theAddr,
                           CT_ProfileTableId * theAlmProfile,
                           CT_SM_PST* thePrimaryState,
                           CT_SM_SST* theSecondaryState,
                           TL1_Response& theResponse,
                           TL1_RtrvAllParameters* theRtrvParams = 0) = 0;

	// Not implemented in AP100
    /*virtual void OperateEqptLed( const CT_TL1_SlotAddr& theAddr,
                                 CT_TL1_PeriodSec* thePeriod,
                                 TL1_Response& theResponse ) = 0;

	*/


    virtual void InitSys(const CT_TL1_SlotAddr& theAddr,
                        CT_SMA_RestartType* theRestartType,
                        bool* theCommandMode,
                        TL1_Response& theResponse ) = 0;  
    
    virtual void SwDxEqpt(const CT_TL1_SlotAddr& theAddr,
                          bool* theCmdMde,
                        TL1_Response& theResponse ) = 0;  

    virtual void RtrvLed ( const CT_TL1_SlotAddr& theAddr,
                           TL1_Response& theResponse ) const = 0;

    virtual void RtrvFpgaVer(  const CT_TL1_SlotAddr& theAddr,
                        CT_FirmwareStatus* theFirmwareStatus,
                        TL1_Response& theResponse  )const =0;

    virtual void RtrvSwVer(  const CT_TL1_SlotAddr& theAddr,
                        CT_SoftwareStatus* theSoftwareStatus,
                        TL1_Response& theResponse  )const =0;
};

#endif


