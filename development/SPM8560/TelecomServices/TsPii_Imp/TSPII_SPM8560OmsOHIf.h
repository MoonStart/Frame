/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Anoop Mathew
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/
#ifndef TSPII_SPM8560OMSOHIF_H
#define TSPII_SPM8560OMSOHIF_H

#include "TsPii/TSPII_OmsOHIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"

class TSPII_OscMapperFpgaCtrl;

class TSPII_SPM8560OmsOHIf : public TSPII_OmsOHIf
{
public:
    /* Constructor */ TSPII_SPM8560OmsOHIf(TSPII_OscMapperFpgaChannel theOsc);
    virtual           ~TSPII_SPM8560OmsOHIf();

    // -----------------------------------------------------------------------------------
    // OMS Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32    GetPMI();
    virtual uint32    GetBDIP();
    virtual uint32    GetBDIO();
    virtual uint32    GetFDIP();
    virtual uint32    GetFDIO();

    // -----------------------------------------------------------------------------------
    // OMS Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void      ForcePMI(bool theForcePMI);
    virtual void      ForceBDIP(bool theForceBDIP);
    virtual void      ForceBDIO(bool theForceBDIO);
    virtual void      ForceFDIP(bool theForceFDIP);
    virtual void      ForceFDIO(bool theForceFDIO);
                       
    virtual bool      GetForcePMI() const;
    virtual bool      GetForceBDIP() const;
    virtual bool      GetForceBDIO() const;
    virtual bool      GetForceFDIP() const;
    virtual bool      GetForceFDIO() const;

private:
    TSPII_OscMapperFpgaCtrl &  myOscCtrl;
    TSPII_OscMapperFpgaChannel myOsc;
};

#endif // TSPII_OSC8250OMSOHIF_H
