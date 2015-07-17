/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : SPM8560
 AUTHOR      : Anoop Mathew
 DESCRIPTION : SPM8560 specific class for TSPII interface.  
--------------------------------------------------------------------------*/
#ifndef TSPII_SPM8560RSIF_H
#define TSPII_SPM8560RSIF_H

#include "TsPii/TSPII_RsIf.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaDrv.h"

class TSPII_OscMapperFpgaCtrl;

class TSPII_SPM8560RsIf : public TSPII_RsIf
{
public:
    /* Constructor */         TSPII_SPM8560RsIf(TSPII_OscMapperFpgaChannel theOsc);
    virtual                   ~TSPII_SPM8560RsIf();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32            GetCVCount();
    virtual uint32            GetLOF();
    virtual uint32            GetOOF();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void              SetSignalType(CT_TEL_SignalType theSignalType);
    virtual CT_TEL_SignalType GetSignalType() const;

    virtual void              SetEnableMessaging(bool enable);
    virtual bool              GetMessagingEnabled() const;

private:
    TSPII_OscMapperFpgaCtrl &   myOscCtrl;
    TSPII_OscMapperFpgaChannel  myOsc;
};

#endif // TSPII_SPM8560RSIF_H
