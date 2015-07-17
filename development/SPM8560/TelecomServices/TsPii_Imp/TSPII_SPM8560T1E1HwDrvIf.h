#ifndef TSPII_SPM8560T1E1HWDRVIF_H
#define TSPII_SPM8560T1E1HWDRVIF_H

/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SPM8560T1E1HwDrvIf.h 
* Type:    C++ include
* Description:
*    Provides the platform independant interface for the T1/E1 
*    Transceiver/Framer & BITS clock source hardware.
*
*************************************END***************************************
*/

#include "TsPii/TSPII_T1E1If.h"
#include "Devices/HdpTimingCard.h"
#include <HdpSpecializedDevice.h>


using namespace Devices;

class TSPII_SPM8560T1E1HwDrvIf : public TSPII_T1E1If
{

public:

    /*************************************************************************/
	/** Costructor                                                          **/
    /*************************************************************************/	
	TSPII_SPM8560T1E1HwDrvIf(uint theClkOutSize, uint theUnit);
    
    /*************************************************************************/
	/** Destructor                                                          **/
    /*************************************************************************/
	virtual ~TSPII_SPM8560T1E1HwDrvIf();

    virtual void UpdateValues();
    /*************************************************************************/
	/** T1E1 & Clock Entity configuration methods                           **/
    /*************************************************************************/
    virtual void SetLineCoding(CT_FAC_LineCode LineCode);
    virtual void SetFramingType(CT_FAC_FrameFormat FrameFormat);
    virtual void SetClkDisqualifyRef(bool);
    virtual void SetTimingSource(CT_ShelfId theShelf, CT_SlotId theSlot);
    virtual void SetSSMSaBit(CT_FAC_SaBit theSaBit);

    /*************************************************************************/
    /** T1E1 & Clock Entity monitor methods                                 **/
    /*************************************************************************/
    virtual CT_FAC_LineCode GetLineCoding(void);
    virtual CT_FAC_FrameFormat GetFramingType(void);
    virtual bool GetTimingSource(CT_ShelfId& theShelf, CT_SlotId& theSlot) const;
    virtual CT_FAC_SaBit GetSSMSaBit(void);
    virtual CT_FAC_RxSsm GetRxSsm(void);
    virtual uint32 GetAis(void);
    virtual uint32 GetLof(void);
    virtual uint32 GetLos(void);
    virtual bool GetClkDisqualifyRef(void);

protected:
                                                                                           
    /*************************************************************************/
    /** utility methods                                                     **/
    /*************************************************************************/

private:

    HdpTimingCard & itsTimingCtrl;
	HdpGenericDevice& itsHdpDev;

};

#endif // TSPII_SPM8560T1E1HWDRVIF_H
