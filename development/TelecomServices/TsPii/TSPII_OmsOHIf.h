#ifndef _TSPII_OMSOHIF_H
#define _TSPII_OMSOHIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/12
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "ss_gdef.h"
#include "TsPii/TSPII_BaseIf.h"

class TSPII_OmsOHIf : public TSPII_BaseIf
{
public:
    /* Constructor */           TSPII_OmsOHIf(bool theDefault = false);
    virtual                     ~TSPII_OmsOHIf();
    virtual void                Reset();

    // -----------------------------------------------------------------------------------
    // OMS Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32              GetPMI();
    virtual uint32              GetBDIP();
    virtual uint32              GetBDIO();
    virtual uint32              GetFDIP();
    virtual uint32              GetFDIO();

    // -----------------------------------------------------------------------------------
    // OMS Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                ForcePMI(bool theForcePMI);
    virtual void                ForceBDIP(bool theForceBDIP);
    virtual void                ForceBDIO(bool theForceBDIO);
    virtual void                ForceFDIP(bool theForceFDIP);
    virtual void                ForceFDIO(bool theForceFDIO);
                                
    virtual bool                GetForcePMI() const;
    virtual bool                GetForceBDIP() const;
    virtual bool                GetForceBDIO() const;
    virtual bool                GetForceFDIP() const;
    virtual bool                GetForceFDIO() const;

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

    void        RefreshGet();
    void        RefreshSet();

    // Monitoring
    uint32      itsPMI;
    uint32      itsBDIP;
    uint32      itsBDIO;
    uint32      itsFDIP;
    uint32      itsFDIO;

    // Configuration attributes
    bool        itsForcePMI;
    bool        itsForceBDIP;
    bool        itsForceBDIO;
    bool        itsForceFDIP;
    bool        itsForceFDIO;
};

#endif // _TSPII_OMSOHIF_H
