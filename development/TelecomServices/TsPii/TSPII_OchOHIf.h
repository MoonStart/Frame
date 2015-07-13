#ifndef _TSPII_OCHOHIF_H
#define _TSPII_OCHOHIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/12
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#include "ss_gdef.h"
#include "TsPii/TSPII_BaseIf.h"

class TSPII_OchOHIf : public TSPII_BaseIf
{
public:
    /* Constructor */           TSPII_OchOHIf(bool theDefault = false);
    virtual                     ~TSPII_OchOHIf();
    virtual void                Reset();

    // -----------------------------------------------------------------------------------
    // Och Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32              GetOCI();
    virtual uint32              GetFDIP();
    virtual uint32              GetFDIO();

    // -----------------------------------------------------------------------------------
    // Och Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                ForceOCI(bool theForceOCI);
    virtual void                ForceFDIP(bool theForceFDIP);
    virtual void                ForceFDIO(bool theForceFDIO);
    virtual void                IgnoreTheForce(bool theEnable);

    virtual bool                GetForceOCI() const;
    virtual bool                GetForceFDIP() const;
    virtual bool                GetForceFDIO() const;
    virtual bool                GetIgnoreForce() const;

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
    virtual void DisplayVerbose(FC_Stream & theStream);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    void        RefreshGet();
    void        RefreshSet();

    // Monitoring
    uint32      itsOCI;
    uint32      itsFDIP;
    uint32      itsFDIO;

    // Configuration attributes
    bool        itsForceOCI;
    bool        itsForceFDIP;
    bool        itsForceFDIO;
    bool        itsIgnoreForce;
};

#endif // _TSPII_OCHOHIF_H
