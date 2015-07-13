#ifndef _TSPII_PILOTTONEIF_H
#define _TSPII_PILOTTONEIF_H
/*-----------------------------------------------------------------------------
 *Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:         TSPII 
AUTHOR:         M. Piotte, 2002/12/17
DESCRIPTION:    Pilot tone collection class
-----------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"

class TSPII_PilotToneAction;
class FC_TimerDispatcher;

const int TSPII_MAX_PT_SIM = CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY;

class TSPII_PilotToneIf : public TSPII_BaseIf
{
public:
    /* CTOR */   TSPII_PilotToneIf(FC_TimerDispatcher * theDispatcher = NULL, 
                                   bool theDefault = false,
                                   bool theDCPowerSupported = false);
    virtual      ~TSPII_PilotToneIf();
    virtual void Reset();

    // -----------------------------------------------------------------------------------
    // Configuration Interfaces
    // -----------------------------------------------------------------------------------

    // -----------------------------------------------------------------------------------
    // Monitoring Interfaces
    // -----------------------------------------------------------------------------------
    virtual void GetPTRawData(TSPII_PilotToneAction * theAction);

    // -----------------------------------------------------------------------------------
    // Availability Interfaces
    // -----------------------------------------------------------------------------------
    virtual bool IsDCPowerSupported() const;

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   & WriteObject(ostream & theStream);
    virtual istream   & ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    void                 RefreshGet();
    void                 RefreshSet();

    FC_TimerDispatcher * myDispatcher;
    bool                 myFailure;
    float                myNoiseLevel;
    float                myGain;
    bool                 myDCPowerSupported;
    float                myPTFreq[TSPII_MAX_PT_SIM];
    float                myPTAmpl[TSPII_MAX_PT_SIM];
};

#endif // _TSPII_PILOTTONEIF_H 
