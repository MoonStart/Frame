#ifndef _TSPII_OSAIF_H
#define _TSPII_OSAIF_H
/*-----------------------------------------------------------------------------
Copyright(c) Tellabs, Inc. All rights reserved.

SUBSYSTEM:      Telecom Services
TARGET:         TSPII 
AUTHOR:         David A. Marcinkiewicz
DESCRIPTION:    OSA base class
-----------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_OchOsaDebounce.h"
#include "CommonTypes/CT_Telecom.h"

const int TSPII_MAX_OSA_CHANELS = CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY;  // fixme 44?

#define TSPII_OPM_STATUS_MASK                  0x1F
#define TSPII_OPM_STATUS_MASK_WAVELENGTH_RANGE 0x10
#define TSPII_OPM_STATUS_MASK_UNDERFLOW        0x08
#define TSPII_OPM_STATUS_MASK_OVERFLOW         0x04
#define TSPII_OPM_STATUS_MASK_CH_SPACING       0x02
#define TSPII_OPM_STATUS_MASK_CH_NUMBER        0x01
const CT_TEL_mBm TSPII_OSA_DEFAULT_HYSTERESIS = 300;

class TSPII_OsaIf : public TSPII_BaseIf
{
public:
    /* ctor */   TSPII_OsaIf(bool theDefault = false, bool IsOsaPowerSupported = false);
    virtual      ~TSPII_OsaIf();
    virtual void Reset();

    // -----------------------------------------------------------------------------------
    // Configuration Interfaces
    // -----------------------------------------------------------------------------------
    virtual void        SetItuSpacing(uint32 theItuSpacing); 
    virtual void        SetStartItuFrequency(uint32 theItuFrequency);
    virtual void        SetMaxNumChannels(uint32 theMaxNumChannels);
    virtual void        SetChanPowerOffset(uint32 theChanPowerOffset); 
    virtual void        SetChanPowerResolution(uint32 theChanPowerResolution);
    virtual void        SetLOSThreshold(CT_TEL_mBm theLOSThreshold, uint32 theIndex);
    virtual void        SetLOSThreshold(CT_TEL_mBm theLOSThreshold);
    virtual void        SetLOSHysteresis(CT_TEL_mBm theValue);

    // -----------------------------------------------------------------------------------
    // Monitoring Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32      GetItuSpacing(); 
    virtual uint32      GetStartItuFrequency();
    virtual uint32      GetChanPowerOffset(); 
    virtual uint32      GetMaxNumChannels();
    virtual uint32      GetChanPowerResolution();
    virtual CT_TEL_mBm  GetPower(uint32 theIndex = 0);
    virtual CT_TEL_mBm  GetInsertionLoss() { return 0; }
    virtual CT_TEL_mBm  GetInputPower(uint32 theIndex = 0);
    virtual CT_TEL_mBm  GetOutputPower(uint32 theIndex = 0);
    virtual CT_TEL_mBm  GetOsnr(uint32 theIndex = 0);
    virtual uint32      GetOpmStatus(void);   
    virtual void        UpdateOpmStatusBits(void);
    virtual uint32      GetLOS(uint32 theIndex = 0);
    CT_TEL_mBm          GetLOSThreshold(uint32 theIndex = 0);
    CT_TEL_mBm          GetLOSHysteresis(void) const;
    virtual bool        IsOsnrValid(uint32 theIndex = 0) const;
    virtual bool        IsOch10G(uint32 theIndex = 0) const;
    virtual bool        IsOch40G(uint32 theIndex = 0) const;

    // -----------------------------------------------------------------------------------
    // Availability Interfaces
    // -----------------------------------------------------------------------------------
    virtual bool IsOsaPowerSupported();

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

    virtual void OchHistMenu(int argc, char ** argv);

protected:

    // OCH power debouncing - only available to derived classes
    virtual CT_TEL_mBm Debounce(uint32 theIndex, CT_TEL_mBm thePower, CT_TEL_mBm theOsnr);

    void                 RefreshGet();
    void                 RefreshSet();

    // Monitoring attributes
    bool                 myWavelengthRangeInvalid;
    bool                 myUnderflowActive;
    bool                 myOverflowActive;
    bool                 myCH_SpacingInvalid;
    bool                 myCH_NumberInvalid;
    uint32               myOpmStatus; // Integrity Check register
    uint32               myLOS[TSPII_MAX_OSA_CHANELS];
    CT_TEL_mBm           myLOSThreshold[TSPII_MAX_OSA_CHANELS];
    CT_TEL_mBm           myLOSHysteresis;
    bool                 myOsnrValid[TSPII_MAX_OSA_CHANELS];
    bool                 myChType40G[TSPII_MAX_OSA_CHANELS]; // true means 40G, false means 10G

    // Configuration attributes
    uint32               myItuSpacing;
    uint32               myItuFrequency;
    uint32               myMaxNumChannels;
    uint32               myChanPowerOffset;
    uint32               myChanPowerResolution;
    CT_TEL_mBm           myOsaChanPower[TSPII_MAX_OSA_CHANELS];
    CT_TEL_mBm           myOsaInputChanPower[TSPII_MAX_OSA_CHANELS];
    CT_TEL_mBm           myOsaOutputChanPower[TSPII_MAX_OSA_CHANELS];
    CT_TEL_mBm           myOsaChanOSNR[TSPII_MAX_OSA_CHANELS];

    // Availability attributes. 
    bool                 myOsaPowerSupported;
    
    // Debounce class
    TSPII_OchOsaDebounce myOchHist;
};

#endif // _TSPII_OSAIF_H 
