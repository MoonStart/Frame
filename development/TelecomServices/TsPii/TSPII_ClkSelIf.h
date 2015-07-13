#ifndef _TSPII_CLKSELIF_H
#define _TSPII_CLKSELIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - March 2004
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for SONET/SDH Clock Selection hardware.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"

class TSPII_ClkSelIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_ClkSelIf(bool theDefault = false);
    virtual                           ~TSPII_ClkSelIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Mon Interfaces
    // -----------------------------------------------------------------------------------
    virtual CT_TEL_ClkSelState        GetTimingState();
    virtual CT_FAC_RxSsm              GetFreerunSsm();
	virtual CT_TEL_ClkMode            GetMateClockMode();

    // -----------------------------------------------------------------------------------
    // SONET/SDH Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetTimingMode(const CT_TEL_ClkSelMode theMode);
    virtual CT_TEL_ClkSelMode         GetTimingMode() const;

    virtual void                      SetSelectedRef(const CT_TEL_ClkSelRef theRef);
    virtual CT_TEL_ClkSelRef          GetSelectedRef() const;

	virtual void                      SetClockMode(const CT_TEL_ClkMode theClkMode);
	virtual CT_TEL_ClkMode            GetClockMode() const;

    virtual void SetFramedTimingInputsEnable(bool theFramedEnable);
    virtual bool GetFramedTimingInputsEnable();

    virtual void SetClockBandwidth(CT_TEL_ClockBandwidth theBandwidth);
    virtual CT_TEL_ClockBandwidth GetClockBandwidth();

    // -----------------------------------------------------------------------------------
    // Clock output control interfaces 
    // -----------------------------------------------------------------------------------
    virtual void SetClkOutEnable(bool theClkOutEnable);
    virtual bool GetClkOutEnable();

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:
    void                      RefreshGet();
    void                      RefreshSet();

    // Monitoring attributes
    CT_TEL_ClkSelState        itsTimingState;
    CT_FAC_RxSsm              itsFreerunSsm;
	CT_TEL_ClkMode            itsMateClockMode;

    // Configuration attributes
    CT_TEL_ClkSelMode         itsTimingMode;
    CT_TEL_ClkSelRef          itsSelectedRef;
    CT_TEL_ClkMode            itsClockMode;
    bool                      itsFramedTimingInputsEnable;
    CT_TEL_ClockBandwidth     itsClockBandwidth;
    bool                      itsClkOutEnable;
};

#endif // _TSPII_CLKSELIF_H
