//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Odu.h"
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>
#include <TsPii/TSPII_DwIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <ctype.h>

static const uint16 PROV_ACTIVE_ODU_GENERIC_PROV_MASK       = 0x0001;
static const uint16 IS_ODU_TERM_ODU_GENERIC_PROV_MASK       = 0x0002;
static const uint16 INT_SIG_DISABLED_ODU_GENERIC_PROV_MASK  = 0x0004;
static const uint16 EXT_SIG_DISABLED_ODU_GENERIC_PROV_MASK  = 0x0008;
static const uint16 FORCE_AIS_GENERIC_PROV_MASK             = 0x0010;
static const uint16 FORCE_LCK_GENERIC_PROV_MASK             = 0x0020;
static const uint16 FORCE_OCI_GENERIC_PROV_MASK             = 0x0040;
static const uint16 FORCE_INTERNAL_AIS_GENERIC_PROV_MASK    = 0x0080;
static const uint16 FORCE_INTERNAL_LCK_GENERIC_PROV_MASK    = 0x0100;
static const uint16 FORCE_INTERNAL_OCI_GENERIC_PROV_MASK    = 0x0200;
static const uint16 NULL_SIGNAL_GENERIC_PROV_MASK           = 0x0400;
static const uint16 TX_PRBS_ODU_GENERIC_PROV_MASK           = 0x0800;
static const uint16 TRIB_AUTO_FALLBACK_GENERIC_PROV_MASK    = 0x1000;
static const uint16 PATH_SOURCE_DELAY_PROV_MASK             = 0x2000;
static const uint16 RX_PRBS_ODU_GENERIC_PROV_MASK           = 0x4000;
// Note: Mask 0x8000 is free to use 


CFG_Odu::CFG_Odu(uint32 theIndex):
    CFG_Object(theIndex),
    myOduIdentifier(CT_DEFAULT_ODU_ID),
    myInstanceObjectType(CT_ODU_UNKNOWN_TYPE),
    myPositionList(0),
    myTcmAProcList(0),
    myTcmBProcList(0),
    myServerID(CT_DEFAULT_ODU_SERVER_ID),
    myAltServerID(CT_DEFAULT_ODU_SERVER_ID),
    myBerSdLevel(CT_TEL_INFINITE_BER),
    mySfBerLevel(CT_TEL_INFINITE_BER),
    myTxPayloadType(CT_TEL_PSI_UNAVAILABLE),
    myBurstyBerSdIntervals(0),
    myBurstyBerSdThreshold(0),
    myTraceInUse(false),
    mySentTracePtr(NULL),
    myGenericProvisioning(0),
    myPMProfileId(CT_PM_PT_99),
    myClockType(CT_TEL_CLK_UNKNOWN),
    myTerminatedIndication(CT_ODU_INDICATION_UNKNOWN),
    myTribSize(CT_TEL_TS_UNKNOWN),
    myTribPort(0),
    myChannelIndexInAID(CT_ODU_CHANNEL_INDEX_DEFAULT),
    myPrbsRxSessionCounter(0),
    myExpSigRate(0),
    myGfpTs(0),
    myCrossConnectedOduIdx(CT_ODU_CRS_CONNECTED_ODU_INDEX_DEFAULT)
{
}

CFG_Odu::~CFG_Odu(void)
{
}


bool CFG_Odu::SetOduIdentifier(CT_ODU_Identifier theOduId)
{
    if (myOduIdentifier != theOduId)
    {
        myOduIdentifier = theOduId;
        return true;
    }
    else
    {
        return false;
    }
}

CT_ODU_Identifier CFG_Odu::GetOduIdentifier() const
{
    return myOduIdentifier;
}



bool CFG_Odu::SetOduObjectType(CT_ODU_Object_Type theOduType)
{
    if (myInstanceObjectType != theOduType)
    {
        myInstanceObjectType = theOduType;
        return true;
    }
    else
    {
        return false;
    }
}

CT_ODU_Object_Type CFG_Odu::GetOduObjectType() const
{
    return myInstanceObjectType;
}


bool CFG_Odu::SetOduPositionList(vector<CT_ODU_ServerID>& thePosList)
{
    bool hasChanged = (thePosList != myPositionList);
    myPositionList = thePosList;
    return hasChanged;
}

const vector<CT_ODU_ServerID>& CFG_Odu::GetOduPositionList()
{
    return myPositionList;
}


bool CFG_Odu::SetOduTcmAProcList(vector<CT_NumberOfOdus>& theProcList)
{
    bool hasChanged = (theProcList != myTcmAProcList);
    myTcmAProcList = theProcList;
    return hasChanged;
}

const vector<CT_NumberOfOdus>& CFG_Odu::GetOduTcmAProcList()
{
    return myTcmAProcList;
}


bool CFG_Odu::SetOduTcmBProcList(vector<CT_NumberOfOdus>& theProcList)
{
    bool hasChanged = (theProcList != myTcmBProcList);
    myTcmBProcList = theProcList;
    return hasChanged;
}

const vector<CT_NumberOfOdus>& CFG_Odu::GetOduTcmBProcList()
{
    return myTcmBProcList;
}


bool CFG_Odu::SetServerID(CT_ODU_ServerID theServerId)
{
    if (myServerID != theServerId)
    {
        myServerID = theServerId;
        return true;
    }
    else
    {
        return false;
    }
}

CT_ODU_ServerID CFG_Odu::GetServerID() const 
{
    return myServerID;
}


bool CFG_Odu::SetAltServerID(CT_ODU_ServerID theServerId)
{
    if (myAltServerID != theServerId)
    {
        myAltServerID = theServerId;
        return true;
    }
    else
    {
        return false;
    }
}

CT_ODU_ServerID CFG_Odu::GetAltServerID() const 
{
    return myAltServerID;
}


bool CFG_Odu::SetSentTrace(const CT_G709Trace& theSentTrace)
{
    bool hasChanged = false;
    if (mySentTracePtr == NULL) 
    {
        mySentTracePtr = new CT_G709Trace(CT_TEL_STANDARD_TRACE); 
        hasChanged = true;
    }
    hasChanged = hasChanged || (!(theSentTrace == *mySentTracePtr));

    *mySentTracePtr = theSentTrace;
    myTraceInUse = true;
    return hasChanged;
}

bool CFG_Odu::DeleteSentTrace()
{
    bool hasChanged = false;
    if (mySentTracePtr != NULL) 
    {
        delete mySentTracePtr;
        mySentTracePtr = NULL;
        hasChanged = true;
    }

    myTraceInUse = false;
    return hasChanged;
}

CT_G709Trace & CFG_Odu::GetSentTrace() const
{
    if (mySentTracePtr != NULL) 
    {
        return(*mySentTracePtr);
    }
    else
    {
        return(CT_G709StandardDefaultTrace::GetInstance());
    }
}


bool CFG_Odu::SetIsOduTerm(bool theIsOduTerm)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theIsOduTerm) 
    {
        myGenericProvisioning |= IS_ODU_TERM_ODU_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(IS_ODU_TERM_ODU_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetIsOduTerm() const
{
    bool aSet = ((myGenericProvisioning & IS_ODU_TERM_ODU_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Odu::SetInternalSignalingDisabled(bool theDisable)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theDisable) 
    {
        myGenericProvisioning  |= INT_SIG_DISABLED_ODU_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(INT_SIG_DISABLED_ODU_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetInternalSignalingDisabled() const
{
    bool aSet = ((myGenericProvisioning & INT_SIG_DISABLED_ODU_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetExternalSignalingDisabled(bool theDisable)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theDisable) 
    {
        myGenericProvisioning  |= EXT_SIG_DISABLED_ODU_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(EXT_SIG_DISABLED_ODU_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetExternalSignalingDisabled() const
{
    bool aSet = ((myGenericProvisioning & EXT_SIG_DISABLED_ODU_GENERIC_PROV_MASK) != 0);
    return aSet;
}



bool CFG_Odu::SetForceAIS(bool theForceAIS)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceAIS) 
    {
        myGenericProvisioning  |= FORCE_AIS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(FORCE_AIS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetForceAIS() const
{
    bool aSet = ((myGenericProvisioning & FORCE_AIS_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetForceLCK(bool theForceLCK)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceLCK) 
    {
        myGenericProvisioning  |= FORCE_LCK_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(FORCE_LCK_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetForceLCK() const
{
    bool aSet = ((myGenericProvisioning & FORCE_LCK_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetForceOCI(bool theForceOCI)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceOCI) 
    {
        myGenericProvisioning  |= FORCE_OCI_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(FORCE_OCI_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetForceOCI() const
{
    bool aSet = ((myGenericProvisioning & FORCE_OCI_GENERIC_PROV_MASK) != 0);
    return aSet;
}

// Add in Monitoring Configurations also
bool CFG_Odu::SetBerSdThreshold(CT_TEL_BERLevels theBerSdThreshold)
{
    bool hasChanged = (theBerSdThreshold != myBerSdLevel);
    myBerSdLevel = theBerSdThreshold;
    return hasChanged;
}

CT_TEL_BERLevels CFG_Odu::GetBerSdThreshold() const
{
    return myBerSdLevel;
}

bool CFG_Odu::SetBerSfThreshold(CT_TEL_BERLevels theSfBerThreshold)
{
    bool hasChanged = (theSfBerThreshold != mySfBerLevel);
    mySfBerLevel = theSfBerThreshold;
    return hasChanged;
}

CT_TEL_BERLevels CFG_Odu::GetBerSfThreshold() const
{
    return mySfBerLevel;
}

bool CFG_Odu::SetTxPayloadType(CT_TEL_PayloadSignalId theTxPayloadType)
{
    bool hasChanged = (theTxPayloadType != myTxPayloadType);
    myTxPayloadType = theTxPayloadType;
    return hasChanged;
}

CT_TEL_PayloadSignalId CFG_Odu::GetTxPayloadType() const
{
    return myTxPayloadType;
}


bool CFG_Odu::SetForceInternalAIS(bool theForceInternalAIS)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceInternalAIS) 
    {
        myGenericProvisioning  |= FORCE_INTERNAL_AIS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(FORCE_INTERNAL_AIS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetForceInternalAIS() const
{
    bool aSet = ((myGenericProvisioning & FORCE_INTERNAL_AIS_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetForceInternalLCK(bool theForceInternalLCK)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceInternalLCK) 
    {
        myGenericProvisioning  |= FORCE_INTERNAL_LCK_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(FORCE_INTERNAL_LCK_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetForceInternalLCK() const
{
    bool aSet = ((myGenericProvisioning & FORCE_INTERNAL_LCK_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Odu::SetForceInternalOCI(bool theForceInternalOCI)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceInternalOCI) 
    {
        myGenericProvisioning  |= FORCE_INTERNAL_OCI_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(FORCE_INTERNAL_OCI_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Odu::GetForceInternalOCI() const
{
    bool aSet = ((myGenericProvisioning & FORCE_INTERNAL_OCI_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetBurstyBerSdIntervals(uint16 theIntervals)
{
    bool hasChanged = (theIntervals != myBurstyBerSdIntervals);
    myBurstyBerSdIntervals = theIntervals;
    return hasChanged;
}

uint16 CFG_Odu::GetBurstyBerSdIntervals() const
{
    return myBurstyBerSdIntervals;
}

bool CFG_Odu::SetBurstyBerSdThreshold(uint32 theThreshold)
{
    bool hasChanged = (theThreshold != myBurstyBerSdThreshold);
    myBurstyBerSdThreshold = theThreshold;
    return hasChanged;
}

uint32 CFG_Odu::GetBurstyBerSdThreshold() const
{
    return myBurstyBerSdThreshold;
}

bool CFG_Odu::SetProvisionningActive(bool theProvisionningActive)
{
    uint16 prevProv = myGenericProvisioning;

    if (theProvisionningActive) 
    {
        myGenericProvisioning |= PROV_ACTIVE_ODU_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(PROV_ACTIVE_ODU_GENERIC_PROV_MASK);
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

bool CFG_Odu::GetProvisionningActive() const
{
    bool aSet = ((myGenericProvisioning & PROV_ACTIVE_ODU_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Odu::SetPMProfileId(CT_PMProfileTableId thePMPFId)
{
    bool hasChanged = (myPMProfileId != thePMPFId);
    myPMProfileId = thePMPFId;
    return hasChanged;
}

CT_PMProfileTableId CFG_Odu::GetPMProfileId() const
{
    return myPMProfileId;
}

bool CFG_Odu::SetClockType(CT_TEL_ClkType theClockType)
{
    bool hasChanged = (theClockType != myClockType);
    myClockType = theClockType;
    return hasChanged;
}

CT_TEL_ClkType CFG_Odu::GetClockType() const
{
    return myClockType;
}

bool CFG_Odu::SetTerminatedIndication(CT_ODU_IndicationType theTerminatedIndication)
{
    bool hasChanged = (theTerminatedIndication != myTerminatedIndication);
    myTerminatedIndication = theTerminatedIndication;
    return hasChanged;
}

CT_ODU_IndicationType CFG_Odu::GetTerminatedIndication() const
{
    return myTerminatedIndication;
}

bool CFG_Odu::SetTribSize(CT_TEL_TS_SIZE theTribSize)
{
    bool hasChanged = (theTribSize != myTribSize);
    myTribSize = theTribSize;
    return hasChanged;
}

CT_TEL_TS_SIZE CFG_Odu::GetTribSize() const
{
    return (CT_TEL_TS_SIZE)myTribSize;
}

bool CFG_Odu::SetTribPort(uint8 theTribPort)
{
    bool hasChanged = (theTribPort != myTribPort);
    myTribPort = theTribPort;
    return hasChanged;
}

uint8 CFG_Odu::GetTribPort() const
{
    return myTribPort;
}

bool CFG_Odu::SetTribAutoFallBack(bool theTribAutoFallBack)
{
    uint16 prevProv = myGenericProvisioning;
    if (theTribAutoFallBack) 
    {
        myGenericProvisioning |= TRIB_AUTO_FALLBACK_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(TRIB_AUTO_FALLBACK_GENERIC_PROV_MASK);
    }
    return (prevProv != myGenericProvisioning);
}

bool CFG_Odu::GetTribAutoFallBack() const
{
    bool aSet = ((myGenericProvisioning & TRIB_AUTO_FALLBACK_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetChannelIndexInAID(uint8 theChannelIndexInAID)
{
    bool hasChanged = (theChannelIndexInAID != myChannelIndexInAID);
    myChannelIndexInAID = theChannelIndexInAID;
    return hasChanged;
}

uint8 CFG_Odu::GetChannelIndexInAID() const
{
    return myChannelIndexInAID;
}

bool CFG_Odu::SetPathDelayEnabled(bool theEnabled)
{
    uint16 prevProv = myGenericProvisioning;

    if (theEnabled) 
    {
        myGenericProvisioning |= PATH_SOURCE_DELAY_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(PATH_SOURCE_DELAY_PROV_MASK);
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

bool CFG_Odu::GetPathDelayEnabled() const
{
    bool aSet = ((myGenericProvisioning & PATH_SOURCE_DELAY_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetPrbsTxEnable(bool thePrbsTxEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (thePrbsTxEnable) 
    {
        myGenericProvisioning  |= TX_PRBS_ODU_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(TX_PRBS_ODU_GENERIC_PROV_MASK);
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

bool CFG_Odu::GetPrbsTxEnable() const
{
    bool aSet = ((myGenericProvisioning & TX_PRBS_ODU_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetPrbsRxEnable(bool thePrbsRxEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (thePrbsRxEnable) 
    {
        myGenericProvisioning  |= RX_PRBS_ODU_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(RX_PRBS_ODU_GENERIC_PROV_MASK);
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

bool CFG_Odu::GetPrbsRxEnable() const
{
    bool aSet = ((myGenericProvisioning & RX_PRBS_ODU_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetPrbsRxSessionCounter(uint32 thePrbsRxSessionCounter)
{
    bool hasChanged = (myPrbsRxSessionCounter != thePrbsRxSessionCounter);
    myPrbsRxSessionCounter = thePrbsRxSessionCounter;
    return hasChanged;
}

uint32 CFG_Odu::GetPrbsRxSessionCounter() const
{
    return myPrbsRxSessionCounter;
}

bool CFG_Odu::GetNULLSignalEnable() const
{
    bool aSet = ((myGenericProvisioning & NULL_SIGNAL_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Odu::SetNULLSignalEnable(bool theEnable)
{
    uint16 prevProv = myGenericProvisioning;

    if (theEnable) 
    {
        myGenericProvisioning  |= NULL_SIGNAL_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(NULL_SIGNAL_GENERIC_PROV_MASK);
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

bool CFG_Odu::SetExpectedSignalRate(uint32 theExpSigRate)
{
    bool hasChanged = (myExpSigRate != theExpSigRate);
    myExpSigRate = theExpSigRate;
    return hasChanged;
}

uint32 CFG_Odu::GetExpectedSignalRate() const
{
    return myExpSigRate;
}

bool CFG_Odu::SetGfpTs(uint8 theGfpTs)
{
    bool hasChanged = (myGfpTs != theGfpTs);
    myGfpTs = theGfpTs;
    return hasChanged;
}

uint8 CFG_Odu::GetGfpTs() const
{
    return myGfpTs;
}

bool CFG_Odu::SetCrossConnectedOduIdx(uint8 theOduIdx)
{
    bool hasChanged = (myCrossConnectedOduIdx != theOduIdx);
    myCrossConnectedOduIdx = theOduIdx;
    return hasChanged;
}

uint8 CFG_Odu::GetCrossConnectedOduIdx() const
{
    return myCrossConnectedOduIdx;
}

void CFG_Odu::Reset(void)
{
    myOduIdentifier = CT_DEFAULT_ODU_ID;
    myInstanceObjectType = CT_ODU_UNKNOWN_TYPE;
    myPositionList.erase(myPositionList.begin(), myPositionList.end()); 
    myTcmAProcList.erase(myTcmAProcList.begin(), myTcmAProcList.end());
    myTcmBProcList.erase(myTcmBProcList.begin(), myTcmBProcList.end());
    myServerID = CT_DEFAULT_ODU_SERVER_ID;
    myAltServerID = CT_DEFAULT_ODU_SERVER_ID;
    myBerSdLevel = CT_TEL_INFINITE_BER;
    mySfBerLevel = CT_TEL_INFINITE_BER;
    myTxPayloadType = CT_TEL_PSI_UNAVAILABLE;
    myBurstyBerSdIntervals = 0;
    myBurstyBerSdThreshold = 0;
    // Note: DeleteSentTrace() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //mySentTracePtr   = NULL;
    DeleteSentTrace();
    myGenericProvisioning = 0;
    myPMProfileId = CT_PM_PT_99;
    myClockType = CT_TEL_CLK_UNKNOWN;
    myTerminatedIndication = CT_ODU_INDICATION_UNKNOWN;
    myTribSize = CT_TEL_TS_UNKNOWN;
    myTribPort = 0;
    myChannelIndexInAID = CT_ODU_CHANNEL_INDEX_DEFAULT;
    myPrbsRxSessionCounter = 0;
    myExpSigRate = 0;
    myGfpTs = 0;
    myCrossConnectedOduIdx = CT_ODU_CRS_CONNECTED_ODU_INDEX_DEFAULT;
}


// For Display
ostream& CFG_Odu::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        theStream    << FC_InsertVar(aTrace);
    }
    theStream   << FC_InsertVar(myTxPayloadType);

    uint8 aBerSdLevel = (uint8) myBerSdLevel;
    uint8 aSfBerLevel = (uint8) mySfBerLevel;
    theStream   << FC_InsertVar(aBerSdLevel);
    theStream   << FC_InsertVar(aSfBerLevel);
    theStream   << FC_InsertVar(myBurstyBerSdIntervals);
    theStream   << FC_InsertVar(myBurstyBerSdThreshold);

    uint32 anOduIdentifier = myOduIdentifier.GetIdValue(); 
    theStream   << FC_InsertVar(anOduIdentifier);
    uint32 anIdentifier = myServerID.GetIdValue(); 
    theStream   << FC_InsertVar(anIdentifier);
    anIdentifier = myAltServerID.GetIdValue(); 
    theStream   << FC_InsertVar(anIdentifier);

    uint8 aInstanceObjectType = (uint8) myInstanceObjectType;
    theStream   << FC_InsertVar(aInstanceObjectType);

    uint32  numberOfMbrs;
    numberOfMbrs   = myPositionList.size();
    theStream << FC_InsertVar(numberOfMbrs);

    string aList;
    char aPos[12];
    for (uint32 anIndex = 0; anIndex < (uint32) numberOfMbrs; anIndex++)
    {
        uint32 aPosInt = myPositionList[anIndex].GetIdValue();
        sprintf(aPos, "%10d,", aPosInt);
        aPos[11] = 0;
        aList += aPos;
    }
    theStream << FC_InsertVar(aList);


    numberOfMbrs   = myTcmAProcList.size();
    theStream << FC_InsertVar(numberOfMbrs);

    string aProcList;
    char aProc[6];
    for (uint32 anIndex = 0; anIndex < (uint32) numberOfMbrs; anIndex++)
    {
        sprintf(aProc, "%4d,", myTcmAProcList[anIndex]);
        aProc[5] = 0;
        aProcList += aProc;
    }
    theStream << FC_InsertVar(aProcList);


    numberOfMbrs   = myTcmBProcList.size();
    theStream << FC_InsertVar(numberOfMbrs);

    string bProcList;
    for (uint32 anIndex = 0; anIndex < (uint32) numberOfMbrs; anIndex++)
    {
        sprintf(aProc, "%4d,", myTcmBProcList[anIndex]);
        aProc[5] = 0;
        bProcList += aProc;
    }
    theStream << FC_InsertVar(bProcList);


    theStream   << FC_InsertVar(myGenericProvisioning);
    uint8 aPMProfileId = (uint8) myPMProfileId;
    theStream   << FC_InsertVar(aPMProfileId);

    uint8 aClockType = (uint8) myClockType;
    theStream   << FC_InsertVar(aClockType);

    uint8 aTerminatedIndication = (uint8) myTerminatedIndication;
    theStream   << FC_InsertVar(aTerminatedIndication);

    uint8 aTribSize = (uint8)myTribSize;
    theStream   << FC_InsertVar(aTribSize);

    theStream   << FC_InsertVar(myTribPort);
    theStream   << FC_InsertVar(myChannelIndexInAID);
    theStream   << FC_InsertVar(myPrbsRxSessionCounter);
    theStream   << FC_InsertVar(myExpSigRate);
    theStream   << FC_InsertVar(myGfpTs);
    theStream   << FC_InsertVar(myCrossConnectedOduIdx);

    return theStream;
}

// For Display
istream& CFG_Odu::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream   >> FC_ExtractVar(aTrace);
        SetSentTrace(aTrace);
    }
    else
    {
        DeleteSentTrace();
    }
    theStream   >> FC_ExtractVar(myTxPayloadType);

    uint8 aBerSdLevel;
    uint8 aSfBerLevel;
    theStream   >> FC_ExtractVar(aBerSdLevel);
    theStream   >> FC_ExtractVar(aSfBerLevel);
    myBerSdLevel = (CT_TEL_BERLevels) aBerSdLevel;
    mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    theStream   >> FC_ExtractVar(myBurstyBerSdIntervals);
    theStream   >> FC_ExtractVar(myBurstyBerSdThreshold);

    uint32 anOduIdentifier;
    theStream   >> FC_ExtractVar(anOduIdentifier);
    myOduIdentifier = (CT_ODU_Identifier) anOduIdentifier;
    uint32 anIdentifier;
    theStream   >> FC_ExtractVar(anIdentifier);
    myServerID = (CT_ODU_ServerID) anIdentifier;
    theStream   >> FC_ExtractVar(anIdentifier);
    myAltServerID = (CT_ODU_ServerID) anIdentifier;
    
    uint8 aInstanceObjectType;
    theStream   >> FC_ExtractVar(aInstanceObjectType);
    myInstanceObjectType = (CT_ODU_Object_Type) aInstanceObjectType;

    uint32 numberOfMbrs;
    uint32 anIndex;

    theStream   >> FC_ExtractVar(numberOfMbrs);
    myPositionList.erase(myPositionList.begin(), myPositionList.end());

    if (numberOfMbrs != 0)
    {
        for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
        {
            myPositionList.push_back((uint32) 0);
        }
        char* aPosList = new char[numberOfMbrs * 12 + 10];
        theStream >> FC_ExtractVar(aPosList);

        char* aPosId = strtok(aPosList, ",");
        anIndex = 0;
        while ((anIndex < numberOfMbrs) && (aPosId != NULL))
        {
            myPositionList[anIndex] = ((CT_ODU_ServerID) atol(aPosId));
            anIndex++;
            aPosId = strtok(NULL, ",");
        }

        delete [] aPosList;

    }
    else
    {
        string aPosList;
        theStream >> FC_ExtractVar(aPosList);
    }


    theStream   >> FC_ExtractVar(numberOfMbrs);
    myTcmAProcList.erase(myTcmAProcList.begin(), myTcmAProcList.end());

    if (numberOfMbrs != 0)
    {
        for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
        {
            myTcmAProcList.push_back((uint16) 0);
        }
        char* aProcList = new char[numberOfMbrs * 6 + 10];
        theStream >> FC_ExtractVar(aProcList);

        char* aProcId = strtok(aProcList, ",");
        anIndex = 0;
        while ((anIndex < numberOfMbrs) && (aProcId != NULL))
        {
            myTcmAProcList[anIndex] = ((uint16) atoi(aProcId));
            anIndex++;
            aProcId = strtok(NULL, ",");
        }

        delete [] aProcList;

    }
    else
    {
        string aProcList;
        theStream >> FC_ExtractVar(aProcList);
    }


    theStream   >> FC_ExtractVar(numberOfMbrs);
    myTcmBProcList.erase(myTcmBProcList.begin(), myTcmBProcList.end());

    if (numberOfMbrs != 0)
    {
        for (anIndex = 0; anIndex < numberOfMbrs; anIndex++)
        {
            myTcmBProcList.push_back((uint16) 0);
        }
        char* bProcList = new char[numberOfMbrs * 6 + 10];
        theStream >> FC_ExtractVar(bProcList);

        char* bProcId = strtok(bProcList, ",");
        anIndex = 0;
        while ((anIndex < numberOfMbrs) && (bProcId != NULL))
        {
            myTcmBProcList[anIndex] = ((uint16) atoi(bProcId));
            anIndex++;
            bProcId = strtok(NULL, ",");
        }

        delete [] bProcList;

    }
    else
    {
        string bProcList;
        theStream >> FC_ExtractVar(bProcList);
    }


    theStream   >> FC_ExtractVar(myGenericProvisioning);
    uint8 aPMProfileId = 0;
    theStream   >> FC_ExtractVar(aPMProfileId);
    myPMProfileId = (CT_PMProfileTableId) aPMProfileId;

    uint8 aClockType;
    theStream   >> FC_ExtractVar(aClockType);
    myClockType = (CT_TEL_ClkType) aClockType;

    uint8 aTerminatedIndication;
    theStream   >> FC_ExtractVar(aTerminatedIndication);
    myTerminatedIndication = (CT_ODU_IndicationType) aTerminatedIndication;

    uint8 aTribSize;
    theStream   >> FC_ExtractVar(aTribSize);
    myTribSize = (CT_TEL_TS_SIZE)aTribSize;

    theStream   >> FC_ExtractVar(myTribPort);
    theStream   >> FC_ExtractVar(myChannelIndexInAID);
    theStream   >> FC_ExtractVar(myPrbsRxSessionCounter);
    theStream   >> FC_ExtractVar(myExpSigRate);
    theStream   >> FC_ExtractVar(myGfpTs);
    theStream   >> FC_ExtractVar(myCrossConnectedOduIdx);

    return theStream;
}


// For persitance and region transfer
FC_Stream& CFG_Odu::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myTraceInUse;
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        theStream    << aTrace;
    }

    theStream   << myTxPayloadType;

    uint8 aBerSdLevel = (uint8) myBerSdLevel;
    uint8 aSfBerLevel = (uint8) mySfBerLevel;
    theStream   << aBerSdLevel;
    theStream   << aSfBerLevel;
    theStream   << myBurstyBerSdIntervals;
    theStream   << myBurstyBerSdThreshold;

    uint32 anOduIdentifier = myOduIdentifier.GetIdValue(); 
    theStream   << anOduIdentifier;
    uint32 anIdentifier = myServerID.GetIdValue(); 
    theStream   << anIdentifier;
    anIdentifier = myAltServerID.GetIdValue(); 
    theStream   << anIdentifier;


    uint8 aInstanceObjectType = (uint8) myInstanceObjectType;
    theStream   << aInstanceObjectType;

    uint32  numberOfMbrs;
    numberOfMbrs = myPositionList.size();
    theStream << numberOfMbrs;
    for (uint32 anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        uint32 aPosInt = myPositionList[anIndex].GetIdValue();
        theStream << aPosInt;
    }

    numberOfMbrs = myTcmAProcList.size();
    theStream << numberOfMbrs;
    for (uint32 anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        theStream << myTcmAProcList[anIndex];
    }

    numberOfMbrs = myTcmBProcList.size();
    theStream << numberOfMbrs;
    for (uint32 anIndex = 0; anIndex < numberOfMbrs; anIndex++)
    {
        theStream << myTcmBProcList[anIndex];
    }

    theStream   << myGenericProvisioning;
    uint8 aPMProfileId = (uint8) myPMProfileId;
    theStream   << aPMProfileId;

    uint8 aClockType = (uint8) myClockType;
    theStream   << aClockType;

    uint8 aTerminatedIndication = (uint8) myTerminatedIndication;
    theStream   << aTerminatedIndication;

    uint8 aTribSize = (uint8) myTribSize;
    theStream   << aTribSize;

    theStream   << myTribPort;
    theStream   << myChannelIndexInAID;
    theStream   << myPrbsRxSessionCounter;
    theStream   << myExpSigRate;
    theStream   << myGfpTs;
    theStream   << myCrossConnectedOduIdx;
    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Odu::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myTraceInUse;
    if (myTraceInUse) 
    {
        // CT_G709Trace aTrace();
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream    >> aTrace;
        SetSentTrace(aTrace);
    }
    else
    {
        DeleteSentTrace();
    }

    theStream   >> myTxPayloadType;

    uint8 aBerSdLevel;
    uint8 aSfBerLevel;
    theStream >> aBerSdLevel;
    theStream >> aSfBerLevel;
    myBerSdLevel = (CT_TEL_BERLevels) aBerSdLevel;
    mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    theStream   >> myBurstyBerSdIntervals;
    theStream   >> myBurstyBerSdThreshold;

    uint32 anOduIdentifier;
    theStream   >> anOduIdentifier;
    myOduIdentifier = (CT_ODU_Identifier) anOduIdentifier;
    uint32 anIdentifier;
    theStream   >> anIdentifier;
    myServerID = (CT_ODU_ServerID) anIdentifier;
    theStream   >> anIdentifier;
    myAltServerID = (CT_ODU_ServerID) anIdentifier;

    uint8 aInstanceObjectType;
    theStream   >> aInstanceObjectType;
    myInstanceObjectType = (CT_ODU_Object_Type) aInstanceObjectType;

    myPositionList.erase(myPositionList.begin(), myPositionList.end());
    uint32  numberOfMbrs;
    uint32 i = 0;
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint32 aPos;
        theStream >> aPos;
        myPositionList.push_back((CT_ODU_ServerID) aPos);
    }

    myTcmAProcList.erase(myTcmAProcList.begin(), myTcmAProcList.end());
    i = 0;
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 aProc;
        theStream >> aProc;
        myTcmAProcList.push_back(aProc);
    }

    myTcmBProcList.erase(myTcmBProcList.begin(), myTcmBProcList.end());
    i = 0;
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        uint16 bProc;
        theStream >> bProc;
        myTcmBProcList.push_back(bProc);
    }

    theStream   >> myGenericProvisioning;
    uint8 aPMProfileId = 0;
    theStream   >> aPMProfileId;
    myPMProfileId = (CT_PMProfileTableId)aPMProfileId;

    uint8 aClockType;
    theStream   >> aClockType;
    myClockType = (CT_TEL_ClkType) aClockType;

    uint8 aTerminatedIndication;
    theStream   >> aTerminatedIndication;
    myTerminatedIndication = (CT_ODU_IndicationType) aTerminatedIndication;

    uint8 aTribSize;
    theStream   >> aTribSize;
    myTribSize = (CT_TEL_TS_SIZE) aTribSize;

    theStream   >> myTribPort;
    theStream   >> myChannelIndexInAID;
    theStream   >> myPrbsRxSessionCounter;
    theStream   >> myExpSigRate;
    theStream   >> myGfpTs;
    theStream   >> myCrossConnectedOduIdx;
    return theStream;
}

FC_CmdProcessor::STATUS CFG_Odu::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto ODUERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"oduterm"))
    {
        SetIsOduTerm(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"disin",5))
    {
        SetInternalSignalingDisabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"disex",5))
    {
        SetExternalSignalingDisabled(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"aisgen"))
    {
        SetForceAIS(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"ocigen"))
    {
        SetForceOCI(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"lckgen"))
    {
        SetForceLCK(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"intaisgen"))
    {
        SetForceInternalAIS(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"intocigen"))
    {
        SetForceInternalOCI(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"intlckgen"))
    {
        SetForceInternalLCK(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"trace"))
    {
        if (argc != 4) goto ODUERROR;
        string aSapi(argv[1]);
        string aDapi(argv[2]);
        string aMessage(argv[3]);

        CT_G709Trace aTrace(aSapi,aDapi,aMessage);
        SetSentTrace(aTrace);
    }
    else if (!strncmp(aParam,"rmtr",4))
    {
        if(argv[1][0]=='e')
        {
            DeleteSentTrace();
        }
    }
    else if (!strcmp(argv[0],"BerSd"))
    {
        SetBerSdThreshold(CFG_STRING_TO_BER(argv[1]));
    }
    else if (!strcmp(argv[0],"sfber"))
    {
        SetBerSfThreshold(CFG_STRING_TO_BER(argv[1]));
    }
    else if(!strncmp(aParam,"psi",3))
    {
        SetTxPayloadType(uint8(atoi(argv[1])));
    }
    else if(!strncmp(aParam,"inter",5))
    {
        SetBurstyBerSdIntervals(uint16(atoi(argv[1])));
    }
    else if(!strncmp(aParam,"thres",5))
    {
        SetBurstyBerSdThreshold(uint32(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"prov",4))
    {
        SetProvisionningActive(argv[1][0]=='e');
    }
    else if(!strcmp(aParam,"oduid"))
    {
        if (!isdigit(argv[1][0]))
        {
            fc_cout << "Error: odu id must be a numeric number" << endl;
            goto ODUERROR;
        }
        char * num = argv[1];
        SetOduIdentifier(CT_ODU_Identifier(strtoul(num, &num, 10)));
    }
    else if(!strncmp(aParam,"hexodu",6))
    {
        if (!isxdigit(argv[1][0]))
        {
            fc_cout << "Error: odu id must be a hex number" << endl;
            goto ODUERROR;
        }
        uint32 numlong = uint32(strtoul(argv[1], NULL, 0));
        SetOduIdentifier(CT_ODU_Identifier(numlong));
    }
    else if(!strncmp(aParam,"serv",4))
    {  
        if (!isdigit(argv[1][0]))
        {
            fc_cout << "Error: server id must be a numeric number" << endl;
            goto ODUERROR;
        }
        SetServerID(CT_ODU_ServerID(atol(argv[1])));
    }
    else if(!strncmp(aParam,"hexser",6))
    {
        if (!isxdigit(argv[1][0]))
        {
            fc_cout << "Error: server id must be a hex number" << endl;
            goto ODUERROR;
        }
        SetServerID(CT_ODU_ServerID(strtoul(argv[1], NULL, 0)));
    }
    else if(!strncmp(aParam,"alts",4))
    {
        if (!isdigit(argv[1][0]))
        {
            fc_cout << "Error: server id must be a numeric number" << endl;
            goto ODUERROR;
        }
        SetAltServerID(CT_ODU_ServerID(atol(argv[1])));
    }
    else if(!strncmp(aParam,"hexalt",6))
    {
        if (!isxdigit(argv[1][0]))
        {
            fc_cout << "Error: server id must be a hex number" << endl;
            goto ODUERROR;
        }
        SetAltServerID(CT_ODU_ServerID(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(argv[0],"type"))
    {
        SetOduObjectType(CFG_STRING_TO_ODU_TYPE(argv[1]));
    }
    else if (!strcmp(aParam,"pos"))
    {
        myPositionList.erase(myPositionList.begin(), myPositionList.end());
        if(strcmp(argv[1],"NULL"))
        {
            char* aPosStr;
            aPosStr = strtok(argv[1], ",");
            while (aPosStr != 0)
            {
                if (!isdigit(aPosStr[0]))
                {  
                    fc_cout << "Error: position must be a numeric number" << endl;
                    goto ODUERROR;
                }
                myPositionList.push_back(((CT_ODU_ServerID) atol(aPosStr)));
                aPosStr = strtok(0, ",");
            }
        }
    }
    else if (!strcmp(aParam,"hexpos"))
    {
        myPositionList.erase(myPositionList.begin(), myPositionList.end());
        if(strcmp(argv[1],"NULL"))
        {
            char* aPosStr;
            aPosStr = strtok(argv[1], ",");
            while (aPosStr != 0)
            {
                if (!isxdigit(aPosStr[0]))
                {  
                    fc_cout << "Error: position must be a hex number" << endl;
                    goto ODUERROR;
                }
                myPositionList.push_back(CT_ODU_ServerID(strtoul(aPosStr, NULL, 0)));
                aPosStr = strtok(0, ",");
            }
        }
    }
    else if (!strncmp(aParam,"clk", 3))
    {
        SetClockType(CFG_STRING_TO_CLOCK_TYPE(argv[1]));
    }
    else if (!strncmp(aParam,"term", 4))
    {
        CT_ODU_IndicationType aType = CT_ODU_INDICATION_UNKNOWN;
        if (!strcmp(argv[1],"ais")) 
        {
            aType = CT_ODU_INDICATION_AIS;        
        }
        else if (!strcmp(argv[1],"lck")) 
        {
            aType = CT_ODU_INDICATION_LCK;        
        }
        else if (!strcmp(argv[1],"oci")) 
        {
            aType = CT_ODU_INDICATION_OCI;        
        }
        else if (!strcmp(argv[1],"none")) 
        {
            aType = CT_ODU_INDICATION_NONE;        
        }
        SetTerminatedIndication(aType);
    }
    else if(!strncmp(aParam,"ts-s", 4))
    {
        SetTribSize(CFG_STRING_TO_TS_SIZE(argv[1]));
    }
    else if(!strncmp(aParam,"ts-p", 4))
    {
        SetTribPort(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"auto", 4))
    {
        SetTribAutoFallBack(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"tcmap",5))
    {
        myTcmAProcList.erase(myTcmAProcList.begin(), myTcmAProcList.end());
        if(strcmp(argv[1],"NULL"))
        {
            char* aProcStr;
            aProcStr = strtok(argv[1], ",");
            while (aProcStr != 0)
            {
                myTcmAProcList.push_back(((CT_NumberOfOdus) atol(aProcStr)));
                aProcStr = strtok(0, ",");
            }
        }
    }
    else if (!strncmp(aParam,"tcmbp",5))
    {
        myTcmBProcList.erase(myTcmBProcList.begin(), myTcmBProcList.end());
        if(strcmp(argv[1],"NULL"))
        {
            char* aProcStr;
            aProcStr = strtok(argv[1], ",");
            while (aProcStr != 0)
            {
                myTcmBProcList.push_back(((CT_NumberOfOdus) atol(aProcStr)));
                aProcStr = strtok(0, ",");
            }
        }
    }
    else if(!strncmp(aParam,"chan", 4))
    {
        SetChannelIndexInAID(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"del",3))
    {
        SetPathDelayEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"txpr",4))
    {
        SetPrbsTxEnable(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"rxpr",4))
    {
        SetPrbsRxEnable(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"rxses",5))
    {
        SetPrbsRxSessionCounter(static_cast<uint32>(strtoul(aParam, NULL, 0)));
    }
    else if(!strncmp(aParam,"null",4))
    {
        SetNULLSignalEnable(argv[1][0]=='e');
    }
    else if(!strncmp(aParam,"exprate",7))
    {
        SetExpectedSignalRate(uint32(atoi(argv[1])));
    }
    else if(!strncmp(aParam,"gfpts",5))
    {
        SetGfpTs(uint8(atoi(argv[1])));
    }
    else if(!strncmp(aParam,"crsoduidx",9))
    {
        SetCrossConnectedOduIdx(uint8(atoi(argv[1])));
    }    
    else
    {
        goto ODUERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

ODUERROR:
    {
        fc_cout << "odu <aisgen|ocigen|lckgen> <e-nable|d-isable> " << endl;
        fc_cout << "odu <intaisgen|intocigen|intlckgen> <e-nable|d-isable>  [Note: for internal] " << endl;
        fc_cout << "odu <oduid>  <uint32 ID definition> " << endl;
        fc_cout << "odu <hexodu> <hex 0x Odu ID definition> " << endl;
        fc_cout << "odu <type> <mux-pool | reg-ular | not-assignedpool | " << endl;
        fc_cout << "            wi-thin (pool Odu within client) | " << endl;
        fc_cout << "            in-side (pool client inside Odu)> " << endl;
        fc_cout << "odu <pos>    <list of ServerIDs on one line of string> " << endl;
        fc_cout << "             <note: lists are separated by a comma or NULL for blank list> " << endl;
        fc_cout << "odu <hexpos> <hex 0x list of ServerIDs> " << endl;
        fc_cout << "odu <tcmap-roclist>  <list for TCM Dir A processing (order of instances)> " << endl;
        fc_cout << "odu <tcmbp-roclist>  <list for TCM Dir B processing (order of instances)> " << endl;
        fc_cout << "odu <serv-erid>      <uint16 Server ID definition> " << endl;
        fc_cout << "odu <alts-erverid>   <uint16 Alternate Server ID definition> " << endl;
        fc_cout << "odu <hexserv>        <hex 0x Server ID> " << endl;
        fc_cout << "odu <hexalts>        <hex 0x Alternate Server ID> " << endl;
        fc_cout << "odu <oduterm> <e-nable|d-isable> " << endl;
        fc_cout << "odu <disex-ternal>   <e-nable|d-isable> " << endl;
        fc_cout << "odu <disin-ternal>   <e-nable|d-isable> " << endl;
        fc_cout << "odu <prov-ision>     <e-nable|d-isable> " << endl;
        fc_cout << "odu <del-ay source>  <e-nable|d-isable> " << endl;
        fc_cout << "odu <inter-vals> < int number of intervas for SD calculation > " << endl;
        fc_cout << "odu <thres-hold> < int thresold of block errors > " << endl;
        fc_cout << "odu <BerSd> <Numeric value range 5 .. 12 inclusive | 0 for NO_BER> " << endl;
        fc_cout << "odu <sfber> <Numeric value range 3 .. 12 inclusive | 0 for NO_BER> " << endl;
        fc_cout << "odu <rmtr-ace> <e-nable|d-isable> " << endl;
        fc_cout << "odu trace <15-byte sapi> <15-byte dapi> <28-byte message> " << endl;
        fc_cout << "odu <psi> < Value between 0 and 255 > " << endl;
        fc_cout << "odu <clk-type> <g709 | ovr_fs | ovr_nofs | ovr_fc | odu3 | odu3e2 | unknown>"  << endl;
        fc_cout << "odu <term-inatedIndication> <ais | lck | oci| none | unknown>"  << endl;
        fc_cout << "odu <ts-size> <2G5 | 1G25 | unknown  > " << endl;
        fc_cout << "odu <ts-port> < Value between 0 and 255 > " << endl;
        fc_cout << "odu <autofallback> <e-nable|d-isable> " << endl;
        fc_cout << "odu <chan-idx> < Value between 0 and 32 > " << endl;
        fc_cout << "Odu txprbs          <e-nable|d-isable> " << endl;
        fc_cout << "Odu rxprbs          <e-nable|d-isable> " << endl;
        fc_cout << "Odu nullsignal      <e-nable|d-isable> " << endl;
        fc_cout << "Odu rxsession       <long integer (counter)> " << endl;
        fc_cout << "odu exprate         <uint32 expected signal rate> " << endl;
        fc_cout << "odu gfpts           <uint8 gfp ts> " << endl;
        fc_cout << "odu crsoduidx       <uint8 cross connected odu index> " << endl;
        fc_cout << endl;

        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Odu::Display( FC_Stream& theStream )
{
    uint32 aOduIdentifier = myOduIdentifier.GetIdValue();
    theStream   << "ODU      - Odu ID               [oduid]     = 0x " << hex << aOduIdentifier << myOduIdentifier.DisplayOduIdentifier() << endl;
    if (myOduIdentifier != CT_DEFAULT_ODU_ID) 
    {  
        // Note: add one because TSPII is one based
        uint16 aTspiiDwInstance = TSPII_SubApplication::GetInstance()->GetOduPoolIndex(aOduIdentifier) + 1;
        theStream   << "    -----> tspii instance       (1-based)   = " << dec << aTspiiDwInstance << endl;
    }
    
    theStream   << "ODU      - Odu Object Type      [type]      = " << DISPLAY_ODU_OBJECT_TYPE(myInstanceObjectType)  << endl;
    theStream   << "ODU      - Position List        [pos]       = ";
    vector<CT_ODU_ServerID>::iterator j;
    for (j = myPositionList.begin(); j != myPositionList.end(); j++)
    {
        CT_ODU_ServerID aTmpPos = (*j); 
        theStream << "0x " << hex << aTmpPos.GetIdValue() << aTmpPos.DisplayServerID() << ", ";
    }
    theStream   << endl;

    theStream   << "ODU      - Server ID            [serv]      = 0x " << hex << myServerID.GetIdValue() << myServerID.DisplayServerID() << endl;
    theStream   << "ODU      - Alt Server ID        [alts]      = 0x " << hex << myAltServerID.GetIdValue() << myAltServerID.DisplayServerID() << endl;
    theStream   << "ODU      - TCM A Processing List[tcmap]     = ";
    uint16 aProc;
    vector<uint16>::iterator i;
    for (i = myTcmAProcList.begin(); i != myTcmAProcList.end(); i++)
    {
        aProc = uint16(*i);
        theStream << dec << aProc << ",";
    }
    theStream   << endl;

    theStream   << "ODU      - TCM B Processing List[tcmap]     = ";
    for (i = myTcmBProcList.begin(); i != myTcmBProcList.end(); i++)
    {
        aProc = uint16(*i);
        theStream << dec << aProc << ",";
    }
    theStream   << endl;

    theStream   << "ODU      - Odu Terminating      [oduterm]   = " << DISPLAY_BOOL(GetIsOduTerm())  << endl;
    theStream   << "ODU      - Disable External Sig [disext]    = " << DISPLAY_BOOL(GetExternalSignalingDisabled())  << endl;
    theStream   << "ODU      - Disable Internal Sig [disint]    = " << DISPLAY_BOOL(GetInternalSignalingDisabled())  << endl;
    theStream   << "ODU      - Provisioning Active  [prov]      = " << DISPLAY_BOOL(GetProvisionningActive()) << endl;
    theStream   << "ODU      - Path Delay Source    [delay]     = " << DISPLAY_BOOL(GetPathDelayEnabled()) << endl;
    theStream   << "ODU      - AIS Forced           [aisgen]    = " << DISPLAY_BOOL(GetForceAIS())  << endl;
    theStream   << "ODU      - OCI Forced           [ocigen]    = " << DISPLAY_BOOL(GetForceOCI())  << endl;
    theStream   << "ODU      - LCK Forced           [lckgen]    = " << DISPLAY_BOOL(GetForceLCK())  << endl;
    theStream   << "ODU      - Bursty SD Intervals  [intervals] = " << dec << myBurstyBerSdIntervals << dec << endl;
    theStream   << "ODU      - Bursty SD Threshold  [threshold] = " << dec << myBurstyBerSdThreshold << dec << endl;
    theStream   << "ODU      - SD BER Threshold     [BerSd]     = " << DISPLAY_BER(myBerSdLevel) << endl;
    theStream   << "ODU      - SF BER Threshold     [sfber]     = " << DISPLAY_BER(mySfBerLevel) << endl;
    theStream   << "ODU      - TXPayload Load Type  [psi]       = 0x " << hex << (uint32)myTxPayloadType << dec << endl;
    theStream   << "ODU      - Clock Type           [clocktype] = " << DISPLAY_CLOCK_TYPE(myClockType) << endl;
    theStream   << "ODU      - Terminated Indication[termindi]  = " << DISPLAY_ODU_INDICATION(myTerminatedIndication) << endl;
    theStream   << "ODU      - Trib Slot Size       [tribsize]  = " << DISPLAY_TS_SIZE(myTribSize) << endl;
    theStream   << "ODU      - Trib Port            [tribport]  = 0x " << hex << (uint32)myTribPort << dec << endl;
    theStream   << "ODU      - Trib AutoFallback    [autofallback]  = " << DISPLAY_BOOL(GetTribAutoFallBack())  << endl;
    theStream   << "ODU      - Internal AIS Forced  [intaisgen] = " << DISPLAY_BOOL(GetForceInternalAIS())  << endl;
    theStream   << "ODU      - Internal OCI Forced  [intocigen] = " << DISPLAY_BOOL(GetForceInternalOCI())  << endl;
    theStream   << "ODU      - Internal LCK Forced  [intlckgen] = " << DISPLAY_BOOL(GetForceInternalLCK())  << endl;
    theStream   << "ODU      - Channel Index        [chanidx]   = " << dec << (uint32)myChannelIndexInAID << dec << endl;
    theStream   << "ODU      - Tx PRBS Enable       [txprbs]    = " << DISPLAY_BOOL(GetPrbsTxEnable()) << endl;
    theStream   << "ODU      - Rx PRBS Enable       [rxprbs]    = " << DISPLAY_BOOL(GetPrbsRxEnable()) << endl;
    theStream   << "ODU      - Rx PRBS Session Cnt  [rxsession] = " << myPrbsRxSessionCounter << endl;
    theStream   << "ODU      - NULL Signal Enable   [nullsignal]= " << DISPLAY_BOOL(GetNULLSignalEnable()) << endl;
    theStream   << "ODU      - Expected SignalRate  [exprate]   = " << dec << myExpSigRate << dec << endl;
    theStream   << "ODU      - GFP TS               [gfpts]     = " << dec << (uint32)myGfpTs << dec << endl;
    theStream   << "ODU      - Crs Conn ODU idx     [oduIndex]  = " << dec << (uint32)myCrossConnectedOduIdx << dec << endl;
    theStream   << "ODU      - Trace In Use                     = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "ODU      - Transmitted Trace    [trace]     = " ;

    if (mySentTracePtr != NULL) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        aTrace.Display(theStream);
    }
    else
    {
        theStream   << endl;
    }
}
