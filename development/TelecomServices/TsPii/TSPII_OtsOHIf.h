#ifndef _TSPII_OTSOHIF_H
#define _TSPII_OTSOHIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/12
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_G709Trace.h"

class TSPII_OtsOHIf : public TSPII_BaseIf
{
public:
    /* Constructor */           TSPII_OtsOHIf(bool theDefault = false);
    virtual                     ~TSPII_OtsOHIf();
    virtual void                Reset();

    // -----------------------------------------------------------------------------------
    // OTS Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32              GetPMI();
    virtual uint32              GetBDIP();
    virtual uint32              GetBDIO();
    virtual const CT_G709Trace& GetRxTTI();

    // -----------------------------------------------------------------------------------
    // OTS Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                ForcePMI(bool theForcePMI);
    virtual void                ForceBDIP(bool theForceBDIP);
    virtual void                ForceBDIO(bool theForceBDIO);
    virtual void                SetTxTTI(const CT_G709Trace & theTrace);

    virtual bool                GetForcePMI() const;
    virtual bool                GetForceBDIP() const;
    virtual bool                GetForceBDIO() const;
    virtual const CT_G709Trace& GetTxTTI() const;

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &          WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &          ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   &          WriteObject(ostream & theStream);
    virtual istream   &          ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    void         RefreshSet();
    void         RefreshGet();

    // Monitoring
    uint32       itsPMI;
    uint32       itsBDIP;
    uint32       itsBDIO;
    CT_G709Trace itsRxTrace;

    // Configuration attributes
    bool         itsForcePMI;
    bool         itsForceBDIP;
    bool         itsForceBDIO;
    CT_G709Trace itsTxTrace;
};

#endif // _TSPII_OTSOHIF_H
