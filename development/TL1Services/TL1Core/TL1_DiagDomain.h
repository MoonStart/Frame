/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 21, 2003- Stephen Wu
DESCRIPTION:    Header file for TL1 OnDemand Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DIAGDOMAIN_H__
#define __TL1_DIAGDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_CARDSTATUSMONITORING_H__
#include <CommonTypes/CT_CardStatusMonitoring.h>
#endif

#ifndef CT_ITS_DEFINITIONS_H
#include <CommonTypes/CT_ITS_Definitions.h>
#endif

#ifndef CT_TIME_H
#include <CommonTypes/CT_Time.h>
#endif


class TL1_Response;

/**
   CLASS TL1_DiagDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of equipment related TL1 command a TL1 Entity
   for an equipment is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_DiagDomain
{
public:
    virtual void MeasureOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                     const CT_Wavelength* theChannel,
                                     const CT_TL1_Port* thePort,
                                     const CT_SignalDirection* theDirection,
                                     const CT_Wavelength* theLane,
                                     TL1_Response& theResponse ) = 0;

    virtual void EditOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                    const CT_MeasOptChanNum* theChannel,
                                    const CT_TL1_Port* thePort,
                                    const CT_MeasOptChanNum *theLane,
                                    const CT_TEL_mBm* theAttn,
                                    const CT_TEL_mBm* theIgain,
                                    const CT_TEL_mBm* theOgain,
                                    const CT_TEL_mBm* theLsrOptPwr,
                                    const CT_TEL_mBm* theLstOptPwr,
                                    const CT_TEL_mBm* thePsrOptPwr,
                                    const CT_TEL_mBm* thePstOptPwr,
                                    const CT_TEL_mBm* thePsrLaneLowOptPwr,
                                    const CT_TEL_mBm* thePsrLaneHighOptPwr,
                                    const CT_TEL_mBm* thePstLaneLowOptPwr,
                                    const CT_TEL_mBm* thePstLaneHighOptPwr,								    
                                    const CT_TEL_mBm* thePsrLaneNumOptPwr,
                                    const CT_TEL_mBm* thePstLaneNumOptPwr,								    
                                    const CT_TimeTm theDateTime,
                                    const bool bDateSet,
                                    const bool bTimeSet,
                                    TL1_Response& theResponse ) = 0;

    virtual void RetrieveOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                        const CT_MeasOptChanNum* theChannel,
                                        const CT_TL1_Port* thePort,
                                        const CT_MeasOptChanNum* theLane,
                                        TL1_Response& theResponse ) = 0;

};

#endif
