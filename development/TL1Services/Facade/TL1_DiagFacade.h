/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 21, 2003- Stephen Wu
DESCRIPTION:    Header file for TL1 On Demand Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DIAGFACADE_H__
#define __TL1_DIAGFACADE_H__

#ifndef __TL1_DIAGDOMAIN_H__
#include <TL1Core/TL1_DiagDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#ifndef T6700_LONGOPERIMP_H
#include <Facade/FC_FacadeOper.h>
#endif

#ifndef __T7100_TL1DIAGIF_H__
#include <TL1Core/T7100_TL1DiagIf.h>
#endif

class FACA_MeasurePowerCommand
{
public:
	// Information Only, Never used.
    virtual void MeasureOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                     const CT_MeasOptChanNum* theChannel,
                                     const CT_TL1_Port* thePort,
                                     const CT_SignalDirection* theDirection,
                                     const CT_MeasOptChanNum* theLane,
                                     TL1_Response& theResponse ) = 0;

    virtual void EditOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                    const CT_MeasOptChanNum* theChannel,
                                    const CT_TL1_Port* thePort,
                                    const CT_MeasOptChanNum *theLane,
                                    const CT_TEL_mBm* theAttn,
							        const CT_TEL_mBm* theIgain,
								    const CT_TEL_mBm* theOgain,
                                    const CT_TEL_mBm* theEstOptPwr,
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
                                    const CT_TEL_mBm* theDsrOptPwr,
                                    const CT_TEL_mBm* theDstOptPwr,
                                    const CT_TimeTm theDateTime,
                                    const bool bDateSet,
                                    const bool bTimeSet,
                                    TL1_Response& theResponse ) = 0;

    virtual void RetrieveOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                        const CT_MeasOptChanNum* theChannel,
                                        const CT_TL1_Port* thePort,
                                        const CT_MeasOptChanNum* theLane,
                                        TL1_Response& theResponse ) = 0;
    virtual bool CheckIfExtConnected(const CT_TL1_SlotAddr& theAddr) = 0;

}; 

#if defined(LINUX) || defined(WIN32)
template <> class GetFacadeOperObj<FACA_MeasurePowerCommand> : 
        public FC_FacadeOper<FACA_MeasurePowerCommand>
#else
class GetFacadeOperObj<FACA_MeasurePowerCommand> : 
        public FC_FacadeOper<FACA_MeasurePowerCommand>
#endif
{
public:
    GetFacadeOperObj();
    virtual ~GetFacadeOperObj();

    virtual void MeasureOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                     const CT_MeasOptChanNum* theChannel,
                                     const CT_TL1_Port* thePort,
                                     const CT_SignalDirection* theDirection,
                                     const CT_MeasOptChanNum* theLane,
                                     TL1_Response& theResponse );
    
    virtual void EditOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                    const CT_MeasOptChanNum* theChannel,
                                    const CT_TL1_Port* thePort,
                                    const CT_MeasOptChanNum *theLane,
                                    const CT_TEL_mBm* theAttn,
							        const CT_TEL_mBm* theIgain,
								    const CT_TEL_mBm* theOgain,
                                    const CT_TEL_mBm* theEstOptPwr,
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
                                    const CT_TEL_mBm* theDsrOptPwr,
                                    const CT_TEL_mBm* theDstOptPwr,
                                    const CT_TimeTm theDateTime,
                                    const bool bDateSet,
                                    const bool bTimeSet,
                                    TL1_Response& theResponse );

    virtual void RetrieveOpticalPower( const CT_TL1_SlotAddr& theAddr,
                                        const CT_MeasOptChanNum* theChannel,
                                        const CT_TL1_Port* thePort,
                                        const CT_MeasOptChanNum* theLane,
                                        TL1_Response& theResponse );

    virtual bool CheckIfExtConnected(const CT_TL1_SlotAddr& theAddr);

private:

    virtual void GetMinMaxWavelength(T7100_TL1DiagIf* tl1DiagIfPtr, CT_TL1_SlotAddr theAddr,
                         CT_Wavelength& theMinWavelength, CT_Wavelength& theMaxWavelength);

    virtual CT_SM_PST GetOchPst(CT_SlotId slotId, CT_MeasOptChanNum itsChannel);

};

#define FACI_MeasureOpticalPower( theAddr, theChannel, thePort, theDirection, theLane, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, MeasureOpticalPower( theAddr, theChannel, thePort, theDirection, theLane, theResponse ))

#define FACI_EditOpticalPower( theAddr, theChannel, thePort, theLane, theAttn, theIgain, theOgain, theEstOptPwr, theLsrOptPwr, theLstOptPwr, thePsrOptPwr, thePstOptPwr, thePsrLaneLowOptPwr, thePsrLaneHighOptPwr, thePstLaneLowOptPwr, thePstLaneHighOptPwr, thePsrLaneOptPwr, thePstLaneOptPwr, theDsrOptPwr, theDstOptPwr, theDateTime, bDateSet, bTimeSet, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EditOpticalPower( theAddr, theChannel, thePort, theLane, theAttn, theIgain, theOgain, theEstOptPwr, theLsrOptPwr, theLstOptPwr, thePsrOptPwr, thePstOptPwr, thePsrLaneLowOptPwr, thePsrLaneHighOptPwr, thePstLaneLowOptPwr, thePstLaneHighOptPwr, thePsrLaneOptPwr, thePstLaneOptPwr, theDsrOptPwr, theDstOptPwr, theDateTime, bDateSet, bTimeSet, theResponse ))

#define FACI_RetrieveOpticalPower( theAddr, theChannel, thePort, theLane, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RetrieveOpticalPower( theAddr, theChannel, thePort,theLane, theResponse ))

#define FACI_CheckIfExtConnected(theAddr) \
FAC_OP_CONST( NO_SUB_RGN_ID, CheckIfExtConnected(theAddr))

#endif
