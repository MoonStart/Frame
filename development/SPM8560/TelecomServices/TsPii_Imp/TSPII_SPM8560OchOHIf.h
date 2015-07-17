/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Anoop Mathew
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/
#ifndef TSPII_SPM8560OCHOHIF_H
#define TSPII_SPM8560OCHOHIF_H

#include "TsPii/TSPII_OchOHIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"

class TSPII_OscMapperFpgaCtrl;

class TSPII_SPM8560OchOHIf : public TSPII_OchOHIf
{
public:
    /* Constructor */ TSPII_SPM8560OchOHIf(TSPII_OscMapperFpgaChannel theOsc, uint32 theOch);
    virtual           ~TSPII_SPM8560OchOHIf();

    // -----------------------------------------------------------------------------------
    // Och Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32    GetOCI();
    virtual uint32    GetFDIP();
    virtual uint32    GetFDIO();

    // -----------------------------------------------------------------------------------
    // Och Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void      ForceOCI(bool theForceOCI);
    virtual void      ForceFDIP(bool theForceFDIP);
    virtual void      ForceFDIO(bool theForceFDIO);

    virtual bool      GetForceOCI() const;
    virtual bool      GetForceFDIP() const;
    virtual bool      GetForceFDIO() const;

private:
    TSPII_OscMapperFpgaCtrl &  myOscCtrl;
    TSPII_OscMapperFpgaChannel myOsc;
    uint32                     myOch;
};

#endif // TSPII_OSC8250OCHOHIF_H
