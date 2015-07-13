//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Opt.h"
#include "BaseClass/FC_TextStream.h"
#include "Configuration/CFG_AppIf.h"
#include "CFG_Definitions.h"
#include "CommonTypes/CT_FacilityIds.h"
#include <string.h>  // for strcmp
#include <cstring>   // for strncpy
 
    // bool myLaserEnable;
    // bool myProvisionningActive;
    // bool myFacilityLoopBackEnable;
    // bool myTerminalLoopBackEnable;
    // bool myAutomaticLaserShutdown;
    // bool myNearEndAutomaticLaserShutdown;
    // bool myPrbsTxEnable;
    // bool myPrbsRxEnable;
    // bool myIdAutoNegEnable;
    // bool myDebugTraceEnable;
    // bool myAutoRateLockDown;
    // bool myPropFefi;
static const uint16 LASER_ENABLE_OPT_GENERIC_PROV_MASK     = 0x0001;
static const uint16 PROV_ACTIVE_OPT_GENERIC_PROV_MASK      = 0x0002;
static const uint16 FAC_LOOP_OPT_GENERIC_PROV_MASK         = 0x0004;
static const uint16 TER_LOOP_OPT_GENERIC_PROV_MASK         = 0x0008;
static const uint16 ALS_OPT_GENERIC_PROV_MASK              = 0x0010;
static const uint16 NEAR_END_ALS_OPT_GENERIC_PROV_MASK     = 0x0020;
static const uint16 TX_PRBS_OPT_GENERIC_PROV_MASK          = 0x0040;
static const uint16 RX_PRBS_OPT_GENERIC_PROV_MASK          = 0x0080;
static const uint16 ID_AUTO_NEG_OPT_GENERIC_PROV_MASK      = 0x0100;
static const uint16 DEBUG_TRACE_OPT_GENERIC_PROV_MASK      = 0x0200;
static const uint16 AUTO_RATE_LOCK_OPT_GENERIC_PROV_MASK   = 0x0400;
static const uint16 PROP_FEFI_OPT_GENERIC_PROV_MASK        = 0x0800;
static const uint16 IGNORE_CSFLOSYNC_OPT_GENERIC_PROV_MASK = 0x1000;


CFG_Opt::CFG_Opt(uint32 theIndex):
    CFG_Object(theIndex),
    myAlsHoldOffDelay(0),
    myMaintSigDelay(0),
    myLosThreshold(TRAFFIC_DEFAULT_POWER),
    mySignalRate(0),
    myDigitalWrapperEnable(CT_OTN_MODE_NONE),
    myWavelength(UNKNOWN_WAVELENGHT),
    myFrequency(0),
    myBand(CT_TEL_UNKNOWN_BAND),
    myPlan(CT_TEL_UNKNOWN_PLAN),
    myPrbsRxSessionCounter(0),
    myOEORegenMode(CT_TEL_OEO_REGEN_UNKNOWN),
    myClockType(CT_TEL_CLK_UNKNOWN),
    myOTIDStatus(CT_TEL_OTID_DISABLED),
    myMaintPropMode(CT_TEL_MAINT_PROP_OFF),
    myPrbsFormat(CT_TEL_PRBS_G709),
    myGenericProvisioning(0x0100)         // myIdAutoNegEnable is defaulted to true
{
}

CFG_Opt::~CFG_Opt()
{
}

bool CFG_Opt::SetLaserEnable(bool theLaserEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (theLaserEnable) 
    {
        myGenericProvisioning  |= LASER_ENABLE_OPT_GENERIC_PROV_MASK;
        
    }
    else
    {
        myGenericProvisioning  &= ~(LASER_ENABLE_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetLaserEnable() const
{
    bool aSet = ((myGenericProvisioning & LASER_ENABLE_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetAutomaticLaserShutdown(bool theAutomaticLaserShutdown)
{
    uint16 prevProv = myGenericProvisioning;

    if (theAutomaticLaserShutdown) 
    {
        myGenericProvisioning  |= ALS_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(ALS_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetAutomaticLaserShutdown() const
{
    bool aSet = ((myGenericProvisioning & ALS_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetNearEndAutomaticLaserShutdown(bool theNearEndAutomaticLaserShutdown)
{
    uint16 prevProv = myGenericProvisioning;

    if (theNearEndAutomaticLaserShutdown) 
    {
        myGenericProvisioning  |= NEAR_END_ALS_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(NEAR_END_ALS_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetNearEndAutomaticLaserShutdown() const
{
    bool aSet = ((myGenericProvisioning & NEAR_END_ALS_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetAlsHoldOffDelay(uint32 theAlsHoldOffDelay)
{
    bool hasChanged = (myAlsHoldOffDelay != theAlsHoldOffDelay);
    myAlsHoldOffDelay = theAlsHoldOffDelay;
    return hasChanged;
}

uint32 CFG_Opt::GetAlsHoldOffDelay() const
{
    return myAlsHoldOffDelay;
}

bool CFG_Opt::SetMaintSigDelay(uint32 theMaintSigDelay)
{
    bool hasChanged = (myMaintSigDelay != theMaintSigDelay);
    myMaintSigDelay = theMaintSigDelay;
    return hasChanged;
}

uint32 CFG_Opt::GetMaintSigDelay() const
{
    return myMaintSigDelay;
}

bool CFG_Opt::SetProvisionningActive(bool theProvisionningActive)
{
    uint16 prevProv = myGenericProvisioning;

    if (theProvisionningActive) 
    {
        myGenericProvisioning |= PROV_ACTIVE_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(PROV_ACTIVE_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetProvisionningActive() const
{
    bool aSet = ((myGenericProvisioning & PROV_ACTIVE_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetFacilityLoopBackEnable(bool theFacilityLoopBackEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (theFacilityLoopBackEnable) 
    {
        myGenericProvisioning |= FAC_LOOP_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(FAC_LOOP_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetFacilityLoopBackEnable() const
{
    bool aSet = ((myGenericProvisioning & FAC_LOOP_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetTerminalLoopBackEnable(bool theTerminalLoopBackEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (theTerminalLoopBackEnable) 
    {
        myGenericProvisioning |= TER_LOOP_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(TER_LOOP_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetTerminalLoopBackEnable() const
{
    bool aSet = ((myGenericProvisioning & TER_LOOP_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetLosThreshold(CT_TEL_mBm theLosThreshold)
{
    if (myLosThreshold != theLosThreshold)
    {
        myLosThreshold = theLosThreshold;
        return true;
    }
    else
    {
        return false;
    }
}

CT_TEL_mBm CFG_Opt::GetLosThreshold() const
{
    return myLosThreshold;
}

bool CFG_Opt::SetAutoRateLockDown(bool theAutoRateLockDown)
{
    uint16 prevProv = myGenericProvisioning;

    if (theAutoRateLockDown) 
    {
        myGenericProvisioning  |= AUTO_RATE_LOCK_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(AUTO_RATE_LOCK_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetAutoRateLockDown() const
{
    bool aSet = ((myGenericProvisioning & AUTO_RATE_LOCK_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetSignalRate(CT_TEL_daHz theSignalRate)
{
    bool hasChanged = false;
    if(mySignalRate != theSignalRate)
    {
        mySignalRate = theSignalRate;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_daHz CFG_Opt::GetSignalRate() const
{
    return mySignalRate;
}

bool CFG_Opt::SetClockRateMap(CFG_ClockRateMap& theMap)
{
    if (!(myClockRateMap == theMap))
    {
        myClockRateMap = theMap;
        return true;
    }
    else
    {
        return false;
    }
}

const CFG_ClockRateMap& CFG_Opt::GetClockRateMap() const
{
    return myClockRateMap;
}


bool CFG_Opt::SetDigitalWrapperEnable(CT_TEL_OTNMode theDigitalWrapperEnable)
{
    bool hasChanged = (myDigitalWrapperEnable != theDigitalWrapperEnable);
    myDigitalWrapperEnable = theDigitalWrapperEnable;
    return hasChanged;
}

CT_TEL_OTNMode CFG_Opt::GetDigitalWrapperEnable() const
{
    return myDigitalWrapperEnable;
}

bool CFG_Opt::SetWavelength(const CT_Wavelength& theWavelength)
{
    bool hasChanged = false;

    if (theWavelength != myWavelength)
    {
        hasChanged |= true;
        myWavelength = theWavelength;
    }

    return hasChanged;
}

const CT_Wavelength& CFG_Opt::GetWavelength() const
{
    return myWavelength;
}

bool CFG_Opt::SetFrequency(const uint32 theFrequency)
{
    bool hasChanged = false;

    if (theFrequency != myFrequency)
    {
        hasChanged |= true;
        myFrequency = theFrequency;
    }

    return hasChanged;
}

uint32 CFG_Opt::GetFrequency() const
{
    return myFrequency;
}

bool CFG_Opt::SetBand(const CT_TEL_OpticalWaveLength& theBand)
{
    bool hasChanged = false;

    if (theBand != myBand)
    {
        hasChanged |= true;
        myBand = theBand;
    }

    return hasChanged;
}

const CT_TEL_OpticalWaveLength& CFG_Opt::GetBand() const
{
    return myBand;
}


bool CFG_Opt::SetFreqPlan(const CT_TEL_FreqencyPlan& thePlan)
{
    bool hasChanged = false;

    if (thePlan != myPlan)
    {
        hasChanged |= true;
        myPlan = thePlan;
    }

    return hasChanged;
}

const CT_TEL_FreqencyPlan& CFG_Opt::GetFreqPlan() const
{
    return myPlan;
}


void CFG_Opt::SetDebugTraceEnable(bool theDebugTrace)
{
    if (theDebugTrace) 
    {
        myGenericProvisioning  |= DEBUG_TRACE_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(DEBUG_TRACE_OPT_GENERIC_PROV_MASK);
    }
    return;
}

bool CFG_Opt::GetDebugTraceEnable() const
{
    bool aSet = ((myGenericProvisioning & DEBUG_TRACE_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetIdAutoNegEnable(bool theIdAutoNeg)
{
    uint16 prevProv = myGenericProvisioning;

    if (theIdAutoNeg) 
    {
        myGenericProvisioning  |= ID_AUTO_NEG_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(ID_AUTO_NEG_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetIdAutoNegEnable() const
{
    bool aSet = ((myGenericProvisioning & ID_AUTO_NEG_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetPrbsTxEnable(bool thePrbsTxEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (thePrbsTxEnable) 
    {
        myGenericProvisioning  |= TX_PRBS_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(TX_PRBS_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetPrbsTxEnable() const
{
    bool aSet = ((myGenericProvisioning & TX_PRBS_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetPrbsRxEnable(bool thePrbsRxEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (thePrbsRxEnable) 
    {
        myGenericProvisioning  |= RX_PRBS_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(RX_PRBS_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CFG_Opt::GetPrbsRxEnable() const
{
    bool aSet = ((myGenericProvisioning & RX_PRBS_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Opt::SetPrbsRxSessionCounter(uint32 thePrbsRxSessionCounter)
{
    bool hasChanged = (myPrbsRxSessionCounter != thePrbsRxSessionCounter);
    myPrbsRxSessionCounter = thePrbsRxSessionCounter;
    return hasChanged;
}

uint32 CFG_Opt::GetPrbsRxSessionCounter() const
{
    return myPrbsRxSessionCounter;
}



bool CFG_Opt::SetOEORegenMode(CT_TEL_OEO_REGEN_MODE theMode)
{
    bool hasChanged = (myOEORegenMode != theMode);
    myOEORegenMode = theMode;
    return hasChanged;
}


CT_TEL_OEO_REGEN_MODE CFG_Opt::GetOEORegenMode() const
{
    return myOEORegenMode;
}

bool CFG_Opt::SetClockType(CT_TEL_ClkType theType)
{
    bool hasChanged = (myClockType != theType);
    myClockType = theType;
    return hasChanged;
}


CT_TEL_ClkType CFG_Opt::GetClockType() const
{
    return myClockType;
}

bool CFG_Opt::SetOTIDStatus(CT_TEL_OTIDStatus theOTIDStatus)
{
    bool hasChanged = (myOTIDStatus != theOTIDStatus);
    myOTIDStatus = theOTIDStatus;
    return hasChanged;
}

CT_TEL_OTIDStatus CFG_Opt::GetOTIDStatus() const
{
    return myOTIDStatus;
}

bool CFG_Opt::SetMaintPropMode(CT_TEL_MAINT_PROP_MODE theMode)
{
    bool hasChanged = (myMaintPropMode != theMode);
    myMaintPropMode = theMode;
    return hasChanged;
}


CT_TEL_MAINT_PROP_MODE CFG_Opt::GetMaintPropMode() const
{
    return myMaintPropMode;
}


bool CFG_Opt::SetPropFefiEnabled(bool thePropFefiEnabled)
{
    uint16 prevProv = myGenericProvisioning;

    if (thePropFefiEnabled) 
    {
        myGenericProvisioning  |= PROP_FEFI_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(PROP_FEFI_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool CFG_Opt::GetPropFefiEnabled() const
{
    bool aSet = ((myGenericProvisioning & PROP_FEFI_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Opt::SetIgnoreCsfLOSyncFlag(bool theIgnoreFlag)
{
    uint16 prevProv = myGenericProvisioning;

    if (theIgnoreFlag) 
    {
        myGenericProvisioning  |= IGNORE_CSFLOSYNC_OPT_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(IGNORE_CSFLOSYNC_OPT_GENERIC_PROV_MASK);
    }

    if (prevProv != myGenericProvisioning)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool CFG_Opt::GetIgnoreCsfLOSyncFlag() const
{
    bool aSet = ((myGenericProvisioning & IGNORE_CSFLOSYNC_OPT_GENERIC_PROV_MASK) != 0);
    return aSet;
}


//This method set the PRBS format: G709(no fixed stuff) or FixedStuff
bool CFG_Opt::SetPrbsFormat(CT_TEL_PrbsFormat thePrbsFormat)
{
    bool hasChanged = false;

    if (thePrbsFormat != myPrbsFormat)
    {
        hasChanged |= true;
        myPrbsFormat = thePrbsFormat;
    }

    return hasChanged;
}


//This method returns the PRBS format: G709(no fixed stuff) or FixedStuff
CT_TEL_PrbsFormat CFG_Opt::GetPrbsFormat() const
{
    return myPrbsFormat;
}


ostream& CFG_Opt::WriteObject( ostream& theStream )
{
    CFG_ClockRateMap::iterator iter;

    CFG_Object::WriteObject(theStream);

    //Serialize the size of the map
    uint32 aClockRateMapSize = myClockRateMap.size();
    theStream   << FC_InsertVar(aClockRateMapSize);

    //Serialize the clock rate map
    for (iter = myClockRateMap.begin(); iter != myClockRateMap.end(); iter++)
    {
        uint32 aSignalRate = (*iter).first;
        uint8  aSignalType = (*iter).second;

        theStream   << FC_InsertVar(aSignalRate);
        theStream   << FC_InsertVar(aSignalType);
    }

    uint8 aDigitalWrapperEnable = myDigitalWrapperEnable;
    theStream   << FC_InsertVar(aDigitalWrapperEnable);

    theStream   << FC_InsertVar(myAlsHoldOffDelay);
    theStream   << FC_InsertVar(myMaintSigDelay);
    theStream   << FC_InsertVar(myLosThreshold);

    uint8 aWavelength = myWavelength.WavelengthIndex();
    theStream   << FC_InsertLabelAndVar("aWavelength", aWavelength);

    theStream   << FC_InsertVar(myFrequency);

    uint32 aBand = (uint32) myBand;
    theStream   << FC_InsertVar(aBand);

    uint32 aPlan = (uint32) myPlan;
    theStream   << FC_InsertVar(aPlan);

    theStream   << FC_InsertVar(myPrbsRxSessionCounter);
    theStream   << FC_InsertVar(mySignalRate);

    uint8 aOEORegenMode = (uint8) myOEORegenMode;
    theStream   << FC_InsertVar(aOEORegenMode);

    uint8 aClockType = (uint8) myClockType;
    theStream   << FC_InsertVar(aClockType);

    uint8 aOTIDStatus = (uint8) myOTIDStatus;
    theStream   << FC_InsertVar(aOTIDStatus);

    uint8 aMaintPropMode = (uint8) myMaintPropMode;
    theStream   << FC_InsertVar(aMaintPropMode);

    theStream   << FC_InsertVar(myGenericProvisioning);

    uint32 aPrbsFormat = (uint32) myPrbsFormat;
    theStream   << FC_InsertVar(aPrbsFormat);

    return theStream;
}


istream& CFG_Opt::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    //Deserialize the size of the map
    uint32 aClockRateMapSize = 0;
    theStream   >> FC_ExtractVar(aClockRateMapSize);

    //Deserialize the map
    myClockRateMap.erase(myClockRateMap.begin(), myClockRateMap.end());
    for (uint8 i=0; i<aClockRateMapSize; i++)
    {
        uint32 aSignalRate;
        uint8 aSignalType;
        theStream   >> FC_ExtractVar(aSignalRate);
        theStream   >> FC_ExtractVar(aSignalType);
        myClockRateMap[(CT_TEL_daHz)aSignalRate] = (CT_TEL_SignalType)aSignalType;
    }

    uint8 aDigitalWrapperEnable = 0;
    theStream   >> FC_ExtractVar(aDigitalWrapperEnable);
    myDigitalWrapperEnable = (CT_TEL_OTNMode) aDigitalWrapperEnable;

    theStream   >> FC_ExtractVar(myAlsHoldOffDelay);
    theStream   >> FC_ExtractVar(myMaintSigDelay);
    theStream   >> FC_ExtractVar(myLosThreshold);

    uint8 aWavelength;  // for conversion
    theStream   >>  FC_ExtractVar(aWavelength);
    // Convert and store the expected channel
    CT_Wavelength bWavelength(aWavelength);
    myWavelength = bWavelength;

    theStream   >> FC_ExtractVar(myFrequency);

    uint32 aBand = 0;
    theStream   >> FC_ExtractVar(aBand);
    myBand = (CT_TEL_OpticalWaveLength) aBand;

    uint32 aPlan = 0;
    theStream   >> FC_ExtractVar(aPlan);
    myPlan = (CT_TEL_FreqencyPlan) aPlan;

    theStream   >> FC_ExtractVar(myPrbsRxSessionCounter);
    theStream   >> FC_ExtractVar(mySignalRate);

    uint8 aOEORegenMode = 0;
    theStream   >> FC_ExtractVar(aOEORegenMode);
    myOEORegenMode = (CT_TEL_OEO_REGEN_MODE) aOEORegenMode;

    uint8 aClockType = 0;
    theStream   >> FC_ExtractVar(aClockType);
    myClockType = (CT_TEL_ClkType) aClockType;

    uint8 aOTIDStatus = 0;
    theStream   >> FC_ExtractVar(aOTIDStatus);
    myOTIDStatus = (CT_TEL_OTIDStatus) aOTIDStatus;

    uint8 aMaintPropMode = 0;
    theStream   >> FC_ExtractVar(aMaintPropMode);
    myMaintPropMode = (CT_TEL_MAINT_PROP_MODE) aMaintPropMode;

    theStream   >> FC_ExtractVar(myGenericProvisioning);

    uint32 aPrbsFormat = 0;
    theStream   >> FC_ExtractVar(aPrbsFormat);
    myPrbsFormat = (CT_TEL_PrbsFormat) aPrbsFormat;

    return theStream;

}

FC_Stream& CFG_Opt::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_ClockRateMap::iterator iter;

    CFG_Object::WriteObjectBinary(theStream);

    //Serialize the size of the map
    theStream   << myClockRateMap.size();

    //Serialize the clock rate map
    for (iter = myClockRateMap.begin(); iter != myClockRateMap.end(); iter++)
    {
        theStream   << (*iter).first;
        theStream   << (uint8)(*iter).second;
    }

    theStream   << (uint8)myDigitalWrapperEnable;

    theStream   << myAlsHoldOffDelay;
    theStream   << myMaintSigDelay;
    theStream   << myLosThreshold;
    theStream   << myWavelength;
    theStream   << (uint32) myFrequency;

    theStream   << (uint32) myBand;
    theStream   << (uint32) myPlan;

    theStream   << myPrbsRxSessionCounter;
    theStream   << mySignalRate;

    theStream   << (uint8) myOEORegenMode;
    theStream   << (uint8) myClockType;
    theStream   << (uint8) myOTIDStatus;
    theStream   << (uint8) myMaintPropMode;

    theStream   << myGenericProvisioning;
    
    theStream   << (uint32) myPrbsFormat;

    return theStream;

}

FC_Stream& CFG_Opt::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    //Deserialize the size of the map
    uint32 aClockRateMapSize = 0;
    theStream   >> aClockRateMapSize;

    //Deserialize the map
    myClockRateMap.erase(myClockRateMap.begin(), myClockRateMap.end());
    for (uint8 i=0;i<aClockRateMapSize; i++)
    {
        uint32 aSignalRate;
        uint8  aSignalType;
        theStream   >> aSignalRate;
        theStream   >> aSignalType;
        myClockRateMap[(CT_TEL_daHz)aSignalRate] = (CT_TEL_SignalType)aSignalType;

    }

    uint8 aDigitalWrapperEnable = 0;
    theStream   >> aDigitalWrapperEnable;
    myDigitalWrapperEnable = (CT_TEL_OTNMode) aDigitalWrapperEnable;

    theStream   >> myAlsHoldOffDelay;
    theStream   >> myMaintSigDelay;
    theStream   >> myLosThreshold;
    theStream   >> myWavelength;
    theStream   >> myFrequency;

    uint32 aBand = 0;
    theStream   >> aBand;
    myBand = (CT_TEL_OpticalWaveLength) aBand;

    uint32 aPlan = 0;
    theStream   >> aPlan;
    myPlan = (CT_TEL_FreqencyPlan) aPlan;

    theStream   >> myPrbsRxSessionCounter;
    theStream   >> mySignalRate;

    uint8 aOEORegenMode = 0;
    theStream   >> aOEORegenMode;
    myOEORegenMode = (CT_TEL_OEO_REGEN_MODE) aOEORegenMode;

    uint8 aClockType = 0;
    theStream   >> aClockType;
    myClockType = (CT_TEL_ClkType) aClockType;

    uint8 aOTIDStatus = 0;
    theStream   >> aOTIDStatus;
    myOTIDStatus = (CT_TEL_OTIDStatus) aOTIDStatus;

    uint8 aMaintPropMode = 0;
    theStream   >> aMaintPropMode;
    myMaintPropMode = (CT_TEL_MAINT_PROP_MODE) aMaintPropMode;

    theStream   >> myGenericProvisioning;

    uint32 aPrbsFormat = 0;
    theStream   >> aPrbsFormat;
    myPrbsFormat = (CT_TEL_PrbsFormat) aPrbsFormat;

    return theStream;

}

FC_CmdProcessor::STATUS CFG_Opt::Set(int argc, char **argv)
{
    char aParam[32];
    char aParamState[16];

    //We need at least 2 arguments
    if (argc < 2)
        goto OPTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);
    strcpy(aParamState, argv[1]);

    if (!strncmp(aParam,"prbsformat",10))
    {
        if(!strcmp(aParamState,"g709"))
        {
            SetPrbsFormat(CT_TEL_PRBS_G709);
        }
        else if(!strcmp(aParamState,"fixedstuff"))
        {
            SetPrbsFormat(CT_TEL_PRBS_FIXEDSTUFF);
        }
        else
        {
            goto OPTERROR;
        }
    }
    else if (!strncmp(aParam,"autosh",6))
    {
        SetAutomaticLaserShutdown(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"near",4))
    {
        SetNearEndAutomaticLaserShutdown(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"del",3))
    {
        SetAlsHoldOffDelay(static_cast<uint32>(strtoul(aParamState, NULL, 0)));
    }
    else if (!strncmp(aParam,"msdel",5))
    {
        SetMaintSigDelay(static_cast<uint32>(strtoul(aParamState, NULL, 0)));
    }
    else if (!strcmp(aParam,"laser"))
    {
        SetLaserEnable(aParamState[0]=='e');
    }
    else if (!strcmp(aParam,"facloop"))
    {
        SetFacilityLoopBackEnable(aParamState[0]=='e');
    }
    else if (!strcmp(aParam,"termloop"))
    {
        SetTerminalLoopBackEnable(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"los",3))
    {
        SetLosThreshold(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"autolo",6))
    {
        SetAutoRateLockDown(aParamState[0]=='e');
    }
    else if (!strcmp(aParam,"wavelength"))
    {
        SetWavelength(CT_Wavelength(atoi(aParamState)));
    }
    else if (!strcmp(aParam,"frequency"))
    {
        SetFrequency(uint32(atoi(aParamState)));
    }
    else if (!strcmp(aParam,"band"))
    {
        SetBand(CFG_STRING_TO_BAND(argv[1]));
    }
    else if (!strcmp(aParam,"plan"))
    {
        SetFreqPlan(CFG_STRING_TO_FREQ_PLAN(argv[1]));
    }
    else if (!strcmp(aParam,"provision"))
    {
        SetProvisionningActive(aParamState[0]=='e');
    }
    else if (!strcmp(aParam,"digwrap"))
    {
        if(!strcmp(aParamState,"none"))
        {
            SetDigitalWrapperEnable(CT_OTN_MODE_NONE);
        }
        else if(!strcmp(aParamState,"g709"))
        {
            SetDigitalWrapperEnable(CT_OTN_MODE_G709);
        }
        else
        {
            goto OPTERROR;
        }
    }
    else if (!strcmp(aParam,"dbgtrace"))
    {
        SetDebugTraceEnable(aParamState[0]=='e');
    }
    else if (!strcmp(aParam,"idautonego"))
    {
        SetIdAutoNegEnable(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"txpr",4))
    {
        SetPrbsTxEnable(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"rxpr",4))
    {
        SetPrbsRxEnable(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"rxses",5))
    {
        SetPrbsRxSessionCounter(static_cast<uint32>(strtoul(aParamState, NULL, 0)));
    }
    else if (!strcmp(aParam,"sigrate"))
    {
        SetSignalRate(atoi(aParamState));
    }
    else if (!strcmp(aParam,"ratemap"))
    {
        if(argc >= 4)
        {
            if(argv[1][0] == 'i')
            {
                for(uint8 i= 3; i<argc;  i+=2)
                {
                    //Insert element in map
                    myClockRateMap[atoi(argv[i-1])] = CFG_STRING_TO_SIGNAL_TYPE(argv[i]);
                }
            }
            else if(argv[1][0] == 'r')
            {
                for(uint8 i= 3; i<argc;  i+=2)
                {
                    //Remove element from map
                    myClockRateMap.erase(atoi(argv[i-1]));
                }
            }
        }
    }
    else if (!strncmp(aParam,"oeo",3))
    {
        if(!strcmp(aParamState,"off"))
        {
            SetOEORegenMode(CT_TEL_OEO_REGEN_OFF);
        }
        else if(!strcmp(aParamState,"on"))
        {
            SetOEORegenMode(CT_TEL_OEO_REGEN_ON);
        }
        else if(!strcmp(aParamState,"non"))
        {
            SetOEORegenMode(CT_TEL_OEO_REGEN_ON_NANO);
        }
        else if(!strcmp(aParamState,"mate"))
        {
            SetOEORegenMode(CT_TEL_OEO_REGEN_LINE_MATE);
        }
        else if(!strcmp(aParamState,"loop"))
        {
            SetOEORegenMode(CT_TEL_OEO_REGEN_LINE_LOOPBACK);
        }
        else if(!strncmp(aParamState,"unkn",4))
        {
            SetOEORegenMode(CT_TEL_OEO_REGEN_UNKNOWN);
        }
        else
        {
            goto OPTERROR;
        }
    }
    else if (!strncmp(aParam,"clk",3))
    {
        if(!strcmp(aParamState,"g709"))
        {
            SetClockType(CT_TEL_CLK_G709);
        }
        else if(!strcmp(aParamState,"ovrfs"))
        {
            SetClockType(CT_TEL_CLK_OVRCLKFS);
        }
        else if(!strncmp(aParamState,"unkn",4))
        {
            SetClockType(CT_TEL_CLK_UNKNOWN);
        }
        else
        {
            goto OPTERROR;
        }
    }

    else if (!strncmp(aParam,"OTID",4))
    {
        if(!strcmp(aParamState,"Disabled"))
        {
            SetOTIDStatus(CT_TEL_OTID_DISABLED);
        }
        else if(!strcmp(aParamState,"Enabled"))
        {
            SetOTIDStatus(CT_TEL_OTID_ENABLED);
        }
        else
        {
            goto OPTERROR;
        }
    }
    else if (!strncmp(aParam,"maint",5))
    {
        if(!strcmp(aParamState,"off"))
        {
            SetMaintPropMode(CT_TEL_MAINT_PROP_OFF);
        }
        else if(!strcmp(aParamState,"on"))
        {
            SetMaintPropMode(CT_TEL_MAINT_PROP_ON);
        }
        else if(!strcmp(aParamState,"als"))
        {
            SetMaintPropMode(CT_TEL_MAINT_PROP_ALS);
        }
        else
        {
            goto OPTERROR;
        }
    }
    else if (!strncmp(aParam,"propf",5))
    {
        SetPropFefiEnabled(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"ign",3))
    {
        SetIgnoreCsfLOSyncFlag(aParamState[0]=='e');
    }
    else
    {
        goto OPTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OPTERROR:
    {
        fc_cout << "opt autoshut        <e-nable|d-isable> " << endl;
        fc_cout << "opt delay (for ALS) <long integer (time in msecs)> " << endl;
        fc_cout << "opt msdelay (for MaintSig) <long integer (time in msecs)> " << endl;
        fc_cout << "opt maintprop       <off|on|als>"  << endl;
        fc_cout << "opt nearendals      <e-nable|d-isable> " << endl;
        fc_cout << "opt facloop         <e-nable|d-isable> " << endl;
        fc_cout << "opt termloop        <e-nable|d-isable> " << endl;
        fc_cout << "opt laser           <e-nable|d-isable> " << endl;
        fc_cout << "opt autolock        <e-nable|d-isable> " << endl;
        fc_cout << "opt idautonego      <e-nable|d-isable> " << endl;
        fc_cout << "opt dbgtrace        <e-nable|d-isable> " << endl;
        fc_cout << "opt provision       <e-nable|d-isable> " << endl;
        fc_cout << "opt propfefi        <e-nable|d-isable> " << endl;
        fc_cout << "opt ignorecsf       <e-nable|d-isable> " << endl;
        fc_cout << "opt los             <Loss of Signal threshold (in mBm)> " << endl;
        fc_cout << "opt digwrap         <none|g709> "        << endl;
        fc_cout << "opt wavelength      <lambda# (255 for none)> " << endl;
        fc_cout << "opt frequency       <frequency (0 for none)> " << endl;
        fc_cout << "opt band            <1310|15xx> (nm) "   << endl;
        fc_cout << "opt plan            <44bst-chan|44-chan|32-chan|88-chan) "  << endl;
        fc_cout << "opt txprbs          <e-nable|d-isable> " << endl;
        fc_cout << "opt rxprbs          <e-nable|d-isable> " << endl;
        fc_cout << "opt rxsession       <long integer (counter)> " << endl;
        fc_cout << "opt sigrate         <rate (daHz)> "      << endl;
        fc_cout << "opt ratemap         <i-nsert|r-emove> <rate (daHz)> <oc3|oc12|oc48|10b8b|e1|stm1|stm4|stm16|gopt|gbep|tgbep>" << endl;
        fc_cout << "opt oeoregen        <off|on|non|mate|loop|unknown>"  << endl;
        fc_cout << "opt clktype         <g709|ovrfs|unknown>"  << endl;
        fc_cout << "opt OPIDStatus      <Disabled|Enabled|unknown>"  << endl;
        fc_cout << "opt prbsformat      <g709|fixedstuff>"  << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_FAILURE;
}

void CFG_Opt::Reset()
{
    // Initialize all attributes to default values.
    myAlsHoldOffDelay           = 0;
    myMaintSigDelay             = 0;
    myLosThreshold              = TRAFFIC_DEFAULT_POWER,
    myClockRateMap.erase(myClockRateMap.begin(), myClockRateMap.end());
    myDigitalWrapperEnable      = CT_OTN_MODE_NONE;
    myWavelength                = UNKNOWN_WAVELENGHT;
    myFrequency                 = 0;
    myBand                      = CT_TEL_UNKNOWN_BAND;
    myPlan                      = CT_TEL_UNKNOWN_PLAN;
    myPrbsRxSessionCounter      = 0;
    myOEORegenMode              = CT_TEL_OEO_REGEN_UNKNOWN;
    myClockType                 = CT_TEL_CLK_UNKNOWN;
    myOTIDStatus                = CT_TEL_OTID_DISABLED;
    myMaintPropMode             = CT_TEL_MAINT_PROP_OFF;
    myGenericProvisioning       = 0x0100;  // myIdAutoNegEnable is defaulted to true
    myPrbsFormat                = CT_TEL_PRBS_G709;
}

void CFG_Opt::Display( FC_Stream& theStream )
{
    CFG_ClockRateMap::iterator iter;
    uint32 index = 1;

    theStream   << "OPT      - Laser Enable        [laser]      = " << DISPLAY_BOOL(GetLaserEnable()) << endl;
    theStream   << "OPT      - Auto Laser Shutdown [autoshut]   = " << DISPLAY_BOOL(GetAutomaticLaserShutdown()) << endl;
    theStream   << "OPT      - ALS Delay (ms)      [delay]      = " << myAlsHoldOffDelay << endl;
    theStream   << "OPT      - MaintSig Delay (ms) [msdelay]    = " << myMaintSigDelay << endl;
    theStream   << "OPT      - Facility Loopback   [facloop]    = " << DISPLAY_BOOL(GetFacilityLoopBackEnable()) << endl;
    theStream   << "OPT      - Terminal Loopback   [termloop]   = " << DISPLAY_BOOL(GetTerminalLoopBackEnable()) << endl;
    theStream   << "OPT      - Provisionning       [provision]  = " << DISPLAY_BOOL(GetProvisionningActive()) << endl;
    theStream   << "OPT      - Maintenance Prop    [maintprop]  = " << DISPLAY_MAINT_PROP_MODE(myMaintPropMode) << endl;
    theStream   << "OPT      - Near End ALS        [nearendals] = " << DISPLAY_BOOL(GetNearEndAutomaticLaserShutdown()) << endl;
    theStream   << "OPT      - LOS Threshold (mBm) [los]        = " << myLosThreshold << endl;
    theStream   << "OPT      - Digital Wrapper     [digwrap]    = " << DISPLAY_BOOL(myDigitalWrapperEnable) << endl;
    theStream   << "OPT      - Wavelength          [wavelength] = " << (uint32)myWavelength.WavelengthIndex() << endl;
    theStream   << "OPT      - Frequency           [frequency]  = " << myFrequency << endl;
    theStream   << "OPT      - Band (nm)           [band]       = " << DISPLAY_BAND(myBand) << endl;
    theStream   << "OPT      - Freq Plan           [plan]       = " << DISPLAY_FREQ_PLAN(myPlan) << endl;
    theStream   << "OPT      - Id Auto Negotiation [idautonego] = " << DISPLAY_BOOL(GetIdAutoNegEnable()) << endl;
    theStream   << "OPT      - Debug Trace Enable  [dbgtrace]   = " << DISPLAY_BOOL(GetDebugTraceEnable()) << endl;
    theStream   << "OPT      - Propagate Fefi      [propfefi]   = " << DISPLAY_BOOL(GetPropFefiEnabled()) << endl;
    theStream   << "OPT      - Ignore CsfLOSync    [ignorecsf]  = " << DISPLAY_BOOL(GetIgnoreCsfLOSyncFlag()) << endl;
    theStream   << "OPT      - Tx PRBS Enable      [txprbs]     = " << DISPLAY_BOOL(GetPrbsTxEnable()) << endl;
    theStream   << "OPT      - Rx PRBS Enable      [rxprbs]     = " << DISPLAY_BOOL(GetPrbsRxEnable()) << endl;
    theStream   << "OPT      - Rx PRBS Session Cnt [rxsession]  = " << myPrbsRxSessionCounter << endl;
    theStream   << "OPT      - Default Signal Rate [sigrate]    = " << mySignalRate << endl;
    theStream   << "OPT      - OEO Regen           [oeoregen]   = " << DISPLAY_OEO_REGEN_MODE(myOEORegenMode) << endl;
    theStream   << "OPT      - Clock Type          [clocktype]  = " << DISPLAY_CLOCK_TYPE(myClockType) << endl;
    theStream   << "OPT      - OTID Status         [OTIDStatus] = " << DISPLAY_OTID_STATUS(myOTIDStatus) << endl;
    theStream   << "OPT      - Auto Rate Lock Down [autolock]   = " << DISPLAY_BOOL(GetAutoRateLockDown()) << endl;
    theStream   << "OPT      - Clock Rate Map      [ratemap]    = " << " Size : " << myClockRateMap.size() << endl;
    theStream   << "OPT      - Prbs Format         [prbsformat] = " << DISPLAY_PRBS_FORMAT(myPrbsFormat) << endl;
    for (iter = myClockRateMap.begin(); iter != myClockRateMap.end(); iter++)
    {
        theStream   << "                                              " << index << "-"
                    << "Rate: " << (*iter).first << " Type: " << DISPLAY_SIGNAL_TYPE((*iter).second) << endl;
        index++;
    }

}
