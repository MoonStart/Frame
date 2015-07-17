/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Anoop Mathew
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/
#ifndef TSPII_SPM8560OPTICALIF_H
#define TSPII_SPM8560OPTICALIF_H

#include "TsPii/TSPII_OpticalIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"

class TSPII_OscMapperFpgaCtrl;

class TSPII_SPM8560OpticalIf : public TSPII_OpticalIf
{
public:
    /* Constructor */ TSPII_SPM8560OpticalIf(TSPII_OscMapperFpgaChannel theOsc);
    virtual           ~TSPII_SPM8560OpticalIf();

    // -----------------------------------------------------------------------------------
    // Optical Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual bool      GetLaserState();
    virtual uint32    GetOptLOS();
    virtual uint32    GetLossOfClock();

    virtual CT_TEL_mBm     GetOpticalPowerTransmittedByPeer();
    virtual CT_TEL_mBm     GetOpticalPowerTransmittedToPeer();
	virtual CT_TEL_mBm     GetOpticalPowerReceived();
    virtual CT_TEL_mBm     GetOpticalPowerTransmitted();

    virtual CT_TEL_mBm     GetOmsPowerTransmittedByPeer();
    virtual CT_TEL_mBm     GetOmsPowerTransmittedToPeer();
    virtual CT_TEL_mBm     GetOmsPowerTransmitted();

    // -----------------------------------------------------------------------------------
    // Optical Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void      SetLaserEnable(bool theEnable);
    virtual void      SetFacilityLoopbackEnable(bool theEnable);
    virtual void      SetTerminalLoopbackEnable(bool theEnable);

    virtual bool      GetLaserEnable() const;
    virtual bool      GetFacilityLoopbackEnable() const;
    virtual bool      GetTerminalLoopbackEnable() const;

    virtual void      SetOpticalPowerTransmittedToPeer();

    virtual void      SetOmsPowerTransmittedToPeer();

private:
    TSPII_OscMapperFpgaCtrl &  myOscCtrl;
    TSPII_OscMapperFpgaChannel myOsc;
};

#endif // TSPII_SPM8560OPTICALIF_H
