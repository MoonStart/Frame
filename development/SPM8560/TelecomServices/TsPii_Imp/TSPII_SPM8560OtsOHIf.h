/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Anoop Mathew
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/
#ifndef TSPII_SPM8560OTSOHIF_H
#define TSPII_SPM8560OTSOHIF_H

#include "TsPii/TSPII_OtsOHIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"

class TSPII_OscMapperFpgaCtrl;

class TSPII_SPM8560OtsOHIf : public TSPII_OtsOHIf
{
public:
    /* Constructor */            TSPII_SPM8560OtsOHIf(TSPII_OscMapperFpgaChannel theOsc);
    virtual                      ~TSPII_SPM8560OtsOHIf();

    // -----------------------------------------------------------------------------------
    // OTS Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32               GetPMI();
    virtual uint32               GetBDIP();
    virtual uint32               GetBDIO();
    virtual const CT_G709Trace & GetRxTTI();

    // -----------------------------------------------------------------------------------
    // OTS Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                 ForcePMI(bool theForcePMI);
    virtual void                 ForceBDIP(bool theForceBDIP);
    virtual void                 ForceBDIO(bool theForceBDIO);
    virtual void                 SetTxTTI(const CT_G709Trace & theTrace);

    virtual bool                 GetForcePMI() const;
    virtual bool                 GetForceBDIP() const;
    virtual bool                 GetForceBDIO() const;
    virtual const CT_G709Trace & GetTxTTI() const;

private:
    TSPII_OscMapperFpgaCtrl &   myOscCtrl;
    TSPII_OscMapperFpgaChannel  myOsc;
};

#endif // TSPII_SPM8560OTSOHIF_H
