/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Martin Piotte, 2002/12/17
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_DwIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_DwIf::TSPII_DwIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_DwIf::~TSPII_DwIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::RefreshGet()
{
    // Monitoring attributes
    itsAIS       = GetAIS();
    itsLCK       = GetLCK();
    itsOCI       = GetOCI();
    itsBDI       = GetBDI();
    itsBerSf     = GetBerSf();
    itsBerSd     = GetBerSd();
    itsPLM       = GetPLM();
    itsMSIM      = GetMSIM();
    itsGenAIS    = GetGenAIS();
    itsLOFLOM    = GetLOFLOM();
    itsLOOMFI    = GetLOOMFI();
    itsTIM       = GetTIM(); 
    itsBip8Count = GetBip8Count();
    itsHighBip8Count = GetHighBip8Count();
    itsRxTrace       = GetRxTrace();
    itsRxPayloadType = GetRxPayloadType();
    itsInternalAIS   = GetInternalAIS();
    itsInternalLCK   = GetInternalLCK();
    itsInternalOCI   = GetInternalOCI();
    itsSSF           = GetSSF();
    itsSSFforSGEO    = GetSSFforSGEO();
    itsPathDelay = GetPathDelay();
    itsPrbsRxLosync = GetPrbsRxLosync();
    GetPrbsRxErrors(itsPrbsRxErrorCountHigh, itsPrbsRxErrorCountLow, itsPrbsRxErrorTime);
    //itsRxAps    = GetRxAps();
    
    // Configuration attributes
    itsForcedODUIndication  = GetForcedODUIndication();
    itsForcedInternalODUIndication  = GetForcedInternalODUIndication();
    itsForcedInternalAIS    = GetForcedInternalAIS();
    itsForcedBDI            = GetForcedBDI();
    itsBerSfThreshold       = GetBerSfThreshold();
    itsBerSdThreshold       = GetBerSdThreshold();
    itsTxTrace              = GetTxTrace();
    itsExpectedTrace        = GetExpectedTrace();
    itsTxPayloadType        = GetTxPayloadType();
    itsExpectedPayloadType  = GetExpectedPayloadType();
    itsIsOduTerm            = GetIsOduTerm();
    itsSrcTrafficEnabled    = GetSrcTrafficEnabled();
    itsBurstySdBerIntervals = GetBurstyBerSdIntervals();
    itsBurstySdBerThreshold = GetBurstyBerSdThreshold();
    itsODUTsSize            = GetODUTsSize();
    itsClockType            = GetClockType();
    itsTribPort             = GetTribPort();
    itsPathDelayEnabled     = GetPathDelayEnabled();
    itsExpRate              = GetExpRate();
    itsNULLSignalEnable     = GetNULLSignalEnable();
    itsPRBSRXEnable         = GetPRBSRXEnable();
    itsPRBSTXEnable         = GetPRBSTXEnable();
    itsPRBSRXSessionCounter = GetPRBSRXSessionCounter();
    itsGfpTsNum             = GetGfpTsNum();
    itsServer               = GetServer();
    itsXcOtherSideIndex     = GetXcOtherSideIndex();
    itsTIMCriteraMode       = GetTimCriteria();
    itsLayerFailOnTIM       = GetLayerFailOnTIM();
    itsTIMMonitoringEnable  = GetTIMMonitoringEnable();
    itsProvisioned          = GetIsProvisioned();
    itsCrossConnected       = GetIsCrossConnected();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::RefreshSet()
{
    // Configuration attributes
    ForceODUIndication(itsForcedODUIndication);
    ForceInternalODUIndication(itsForcedInternalODUIndication);
    ForceInternalAIS(itsForcedInternalAIS);
    ForceBDI(itsForcedBDI);
    SetBerSfThreshold(itsBerSfThreshold);
    SetBerSdThreshold(itsBerSdThreshold);
    SetTxTrace(itsTxTrace);
    SetExpectedTrace(itsExpectedTrace);
    SetTxPayloadType(itsTxPayloadType);
    SetExpectedPayloadType(itsExpectedPayloadType);
    SetIsOduTerm(itsIsOduTerm);
    SetSrcTrafficEnabled(itsSrcTrafficEnabled);
    SetBurstyBerSdThreshold(itsBurstySdBerIntervals, itsBurstySdBerThreshold);
    SetODUTsSize(itsODUTsSize);
    SetClockType(itsClockType);
    SetTribPort(itsTribPort);
    SetPathDelayEnabled(itsPathDelayEnabled);
    SetExpRate(itsExpRate);
    SetNULLSignalEnable(itsNULLSignalEnable);
    SetPRBSRXEnable(itsPRBSRXEnable);
    SetPRBSRXSessionCounter(itsPRBSRXSessionCounter);
    SetPRBSTXEnable(itsPRBSTXEnable);
    SetGfpTsNum(itsGfpTsNum);
    SetServer(itsServer);
    SetXcOtherSideIndex(itsXcOtherSideIndex);
    SetTimCriteria(itsTIMCriteraMode);
    SetLayerFailOnTIM(itsLayerFailOnTIM);
    SetTIMMonitoringEnable(itsTIMMonitoringEnable);
    SetIsProvisioned(itsProvisioned);
    SetTxApsBytes(itsTxAps.channel, itsTxAps.bytes, itsTxAps.apsInsert);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsAIS       = 0;
    itsLCK       = 0;
    itsOCI       = 0;
    itsBDI       = 0;
    itsBerSf     = 0;
    itsBerSd     = 0;
    itsPLM       = 0;
    itsMSIM      = 0;
    itsGenAIS    = 0;
    itsLOFLOM    = 0;
    itsLOOMFI    = 0;
    itsBip8Count = 0;
    itsHighBip8Count = 0;
    itsRxTrace   = CT_G709Trace();
    itsRxPayloadType     = 0;
    itsInternalAIS       = 0;
    itsInternalLCK       = 0;
    itsInternalOCI       = 0;
    itsSSF               = 0;
    itsSSFforSGEO        = 0;
    itsPathDelay = 0;
    itsPrbsRxLosync = 0;
    itsPrbsRxErrorCountHigh          = 0;
    itsPrbsRxErrorCountLow           = 0;
    itsPrbsRxErrorTime               = 0;
    itsTIM                           = 0;
    itsRxAps                         = 0;

    // Configuration attributes
    itsForcedODUIndication	= CT_ODU_INDICATION_UNKNOWN;
    itsForcedInternalODUIndication= CT_ODU_INDICATION_UNKNOWN;
    itsForcedInternalAIS    = false;
    itsForcedBDI            = false;
    itsBerSfThreshold       = CT_TEL_NO_BER;
    itsBerSdThreshold       = CT_TEL_NO_BER;
    itsTxTrace              = CT_G709Trace();
    itsExpectedTrace        = CT_G709Trace();
    itsTxPayloadType        = 0;
    itsExpectedPayloadType  = 0;
    itsIsOduTerm            = false;
    itsSrcTrafficEnabled    = false;
    itsBurstySdBerIntervals = 0;
    itsBurstySdBerThreshold = 0;
    itsODUTsSize            = CT_TEL_TS_UNKNOWN;
    itsClockType            = CT_TEL_CLK_UNKNOWN;
    itsTribPort             = 0;
    itsPathDelayEnabled     = false;
    itsExpRate              = 0;
    itsNULLSignalEnable     = false;
    itsPRBSRXEnable         = false;
    itsPRBSTXEnable         = false;
    itsPRBSRXSessionCounter = 0;
    itsGfpTsNum             = 0;
    itsServer               = CT_ODU_ServerID::SERVER_DEFAULT;
    itsXcOtherSideIndex     = CT_ODU_CRS_CONNECTED_ODU_INDEX_DEFAULT;
    itsTIMCriteraMode       = CT_TEL_TIM_SAPI_DAPI;
    itsLayerFailOnTIM       = false;
    itsTIMMonitoringEnable  = false; 
    itsProvisioned          = false;
    itsCrossConnected       = false;
}

///////////////////////////////////////////;////////////////////////////////////
const CT_G709Trace & TSPII_DwIf::GetRxTrace()
{
    return itsRxTrace;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetAIS()
{
    return itsAIS;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetLCK()
{
    return itsLCK;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetOCI()
{
    return itsOCI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetBDI()
{
    return itsBDI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetBerSf()
{
    return itsBerSf;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetBerSd()
{
    return itsBerSd;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetPLM()
{
    return itsPLM;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetMSIM()
{
    return itsMSIM;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetGenAIS()
{
    return itsGenAIS;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetLOFLOM()
{
    return itsLOFLOM;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetLOOMFI()
{
    return itsLOOMFI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetTIM()
{
    return itsTIM;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetRxAps(uint8 apsChannel)
{
    return itsRxAps;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetBip8Count()
{
    return itsBip8Count;
}
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetHighBip8Count()
{
    return itsHighBip8Count;
}
///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DwIf::GetRxPayloadType()
{
    return itsRxPayloadType;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetInternalAIS()
{
    return itsInternalAIS;
}

///////////////////////////////////////////////////////////////////////////////
int32 TSPII_DwIf::GetPathDelay()
{
    return itsPathDelay;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetTxTrace(const CT_G709Trace & theTraceToTransmit)
{
    itsTxTrace = theTraceToTransmit;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetTimCriteria(CT_TEL_TimCriteriaMode theTimCriteria)
{
    itsTIMCriteraMode = theTimCriteria;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::ForceODUIndication(CT_ODU_IndicationType theIndication)
{
    itsForcedODUIndication = theIndication;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::ForceInternalODUIndication(CT_ODU_IndicationType theInternalIndication)
{
    itsForcedInternalODUIndication = theInternalIndication;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::ForceInternalAIS(bool theEnable)
{
    itsForcedInternalAIS = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::ForceBDI(bool theEnable)
{
    itsForcedBDI = theEnable;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetBerSfThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSfThreshold = theThreshold;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetBerSdThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSdThreshold = theThreshold;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetTxPayloadType(uint8 pt)
{
    itsTxPayloadType = pt;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetExpectedPayloadType(uint8 pt)
{
    itsExpectedPayloadType = pt;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetIsOduTerm(bool theIsOduTerm)
{
    itsIsOduTerm = theIsOduTerm;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetSrcTrafficEnabled(bool theEnable)
{
    itsSrcTrafficEnabled = theEnable;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetBurstyBerSdThreshold(uint intervals, uint32 threshold)
{
  itsBurstySdBerIntervals = intervals;
  itsBurstySdBerThreshold = threshold;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetODUTsSize(CT_TEL_TS_SIZE theODUTsSize, bool theIsAutoFallback)
{
    itsODUTsSize = theODUTsSize;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetClockType(CT_TEL_ClkType theClockType)
{
    itsClockType = theClockType;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetTribPort(uint16 theTribPort)
{
    itsTribPort = theTribPort;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetPathDelayEnabled(bool theEnable)
{
    itsPathDelayEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetExpRate(uint32 theRate)
{
    itsExpRate = theRate;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetNULLSignalEnable(bool theEnable)
{
    itsNULLSignalEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetPRBSTXEnable(bool theEnable)
{
    itsPRBSTXEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetPRBSRXSessionCounter(uint32 thePRBSRXSessionCounter)
{
    itsPRBSRXSessionCounter = thePRBSRXSessionCounter;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetPRBSRXEnable(bool theEnable)
{
    if((theEnable != itsPRBSRXEnable) && (theEnable == true))
    {
        // Reset the error counts and time when we transition to enabled
        itsPrbsRxErrorCountHigh = 0;
        itsPrbsRxErrorCountLow = 0;
        itsPrbsRxErrorTime = 0;
    }
    itsPRBSRXEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetGfpTsNum(uint8 theTsNum)
{
    itsGfpTsNum = theTsNum;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetDiagSigTxEnable(CT_TEL_DiagSignal theSig, bool theEnable)
{
    switch(theSig)
    {
        case CT_TEL_DiagSig_ODUNULL:
            SetNULLSignalEnable(theEnable);
            break;
            
        case CT_TEL_DiagSig_ODUPRBS:
            SetPRBSTXEnable(theEnable);
            break;

        case CT_TEL_DiagSig_ODUNONE:
            SetNULLSignalEnable(false);
            SetPRBSTXEnable(false);
        
        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetServer(CT_ODU_ServerID theServer)
{
    itsServer = theServer;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetXcOtherSideIndex(uint8 theOduIndex)
{
    itsXcOtherSideIndex = theOduIndex;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetExpectedTrace(const CT_G709Trace & theTrace)
{
    itsExpectedTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_DwIf::GetTxTrace() const 
{
    return itsTxTrace;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_DwIf::GetExpectedTrace() const
{
    return itsExpectedTrace;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_TimCriteriaMode TSPII_DwIf::GetTimCriteria() const
{
    return itsTIMCriteraMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_ODU_IndicationType TSPII_DwIf::GetForcedODUIndication() const
{
    return itsForcedODUIndication;
}

///////////////////////////////////////////////////////////////////////////////
CT_ODU_IndicationType TSPII_DwIf::GetForcedInternalODUIndication() const
{
    return itsForcedInternalODUIndication;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetForcedInternalAIS() const
{
    return itsForcedInternalAIS;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetForcedBDI() const 
{
    return itsForcedBDI;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_DwIf::GetBerSfThreshold() const
{
    return itsBerSfThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_DwIf::GetBerSdThreshold() const
{
    return itsBerSdThreshold;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DwIf::GetTxPayloadType() const
{
    return itsTxPayloadType;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DwIf::GetExpectedPayloadType() const
{
    return itsExpectedPayloadType;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetIsOduTerm() const
{
    return itsIsOduTerm;
}

//////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetSrcTrafficEnabled() const
{
    return itsSrcTrafficEnabled;
}

//////////////////////////////////////////////////////////////////////////////
uint TSPII_DwIf::GetBurstyBerSdIntervals() const
{
  return itsBurstySdBerIntervals;
}

//////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetBurstyBerSdThreshold() const
{
  return itsBurstySdBerThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_TS_SIZE TSPII_DwIf::GetODUTsSize() const
{
    return itsODUTsSize;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClkType TSPII_DwIf::GetClockType() const
{
    return itsClockType;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_DwIf::GetTribPort() const
{
    return itsTribPort;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetPathDelayEnabled() const
{
    return itsPathDelayEnabled;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetExpRate() const
{
    return itsExpRate;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetNULLSignalEnable() const
{
    return itsNULLSignalEnable;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetPrbsRxLosync() 
{
    return itsPrbsRxLosync;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetPrbsRxErrors(uint32 & theCountHigh, uint32 & theCountLow, uint32 & theTime) 
{
    bool foundIt = true;   // Can be set to false with debugger to simulate failure

    theCountHigh = itsPrbsRxErrorCountHigh;
    theCountLow = itsPrbsRxErrorCountLow;
    theTime = itsPrbsRxErrorTime;
    return foundIt;
}
    
    

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetPRBSRXEnable() const
{
    return itsPRBSRXEnable;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetPRBSRXSessionCounter() const
{
    return itsPRBSRXSessionCounter;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetPRBSTXEnable() const
{
    return itsPRBSTXEnable;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DwIf::GetGfpTsNum() const
{
    return itsGfpTsNum;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetInternalLCK() 
{
    return itsInternalLCK;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetInternalOCI() 
{
    return itsInternalOCI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetSSF() 
{
    return itsSSF;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_DwIf::GetSSFforSGEO() 
{
    return itsSSFforSGEO;
}

///////////////////////////////////////////////////////////////////////////////
CT_ODU_ServerID TSPII_DwIf::GetServer() const
{
    return itsServer;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_DwIf::GetXcOtherSideIndex() const
{
    return itsXcOtherSideIndex;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetTIMMonitoringEnable(bool theEnable)
{
    itsTIMMonitoringEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetTIMMonitoringEnable() const
{
    return itsTIMMonitoringEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetLayerFailOnTIM(bool theEnable)
{
    itsLayerFailOnTIM = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetLayerFailOnTIM() const
{
    return itsLayerFailOnTIM;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetIsProvisioned(bool theEnable)
{
    itsProvisioned = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::SetTxApsBytes(CT_SP_APS_Channel theApsChannel, uint32 theApsBytes ,bool theApsInsert)
{
    itsTxAps.channel = theApsChannel;
    itsTxAps.bytes   = theApsBytes;
    itsTxAps.apsInsert =theApsInsert;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetIsProvisioned() const
{
    return itsProvisioned;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::GetIsCrossConnected()
{
    return itsCrossConnected;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DwIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aBerSfThreshold = itsBerSfThreshold;
    int aBerSdThreshold = itsBerSdThreshold;
    int aODUTsSize = itsODUTsSize;
    int aClkType = itsClockType;
    uint32 aServer = itsServer.GetIdValue();
    int aTIMCriteraMode = itsTIMCriteraMode;

    // Monitoring
    theStream << itsRxTrace;
    theStream << itsAIS;
    theStream << itsLCK;
    theStream << itsOCI;
    theStream << itsBDI;
    theStream << itsBerSf;
    theStream << itsBerSd;
    theStream << itsPLM;
    theStream << itsMSIM;
    theStream << itsGenAIS;
    theStream << itsLOFLOM;
    theStream << itsLOOMFI;
    theStream << itsBip8Count;
    theStream << itsHighBip8Count;
    theStream << static_cast<int>(itsRxPayloadType);
    theStream << itsInternalAIS;
    theStream << itsInternalLCK;
    theStream << itsInternalOCI;
    theStream << itsSSF;
    theStream << itsSSFforSGEO;
    theStream << itsPathDelay; 
    theStream << itsPrbsRxLosync;
    theStream << itsPrbsRxErrorCountHigh;
    theStream << itsPrbsRxErrorCountLow;
    theStream << itsPrbsRxErrorTime;
    theStream << itsTIM;

    // Configuration
    theStream << itsTxTrace;
    theStream << itsExpectedTrace;
    theStream << itsForcedODUIndication;
    theStream << itsForcedInternalODUIndication;
    theStream << itsForcedInternalAIS;
    theStream << itsForcedBDI;
    theStream << aBerSfThreshold;
    theStream << aBerSdThreshold;
    theStream << static_cast<int>(itsTxPayloadType);
    theStream << itsIsOduTerm;
    theStream << itsSrcTrafficEnabled;
    theStream << itsBurstySdBerIntervals;
    theStream << itsBurstySdBerThreshold;
    theStream << aODUTsSize;
    theStream << (uint32)itsClockType;
    theStream << itsTribPort;
    theStream << itsPathDelayEnabled;
    theStream << itsExpRate;
    theStream << itsNULLSignalEnable;
    theStream << itsPRBSRXEnable;
    theStream << itsPRBSTXEnable;
    theStream << itsPRBSRXSessionCounter;
    theStream << itsGfpTsNum;
    theStream << aServer;
    theStream << itsXcOtherSideIndex;
    theStream << aTIMCriteraMode;
    theStream << static_cast<int>(itsExpectedPayloadType);
    theStream << itsLayerFailOnTIM;
    theStream << itsTIMMonitoringEnable;
    theStream << itsProvisioned;
    theStream << itsCrossConnected;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_DwIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aBerSfThreshold;
    int aBerSdThreshold;
    int aODUTsSize;
    int aClockType;
    int aRxPti;
    int aTxPti;
    int aExpectPti;
    uint32 aServer;
    int aTIMCriteraMode;

    // Monitoring
    theStream >> itsRxTrace;
    theStream >> itsAIS;
    theStream >> itsLCK;
    theStream >> itsOCI;
    theStream >> itsBDI;
    theStream >> itsBerSf;
    theStream >> itsBerSd;
    theStream >> itsPLM;
    theStream >> itsMSIM;
    theStream >> itsGenAIS;
    theStream >> itsLOFLOM;
    theStream >> itsLOOMFI;
    theStream >> itsBip8Count;
    theStream >> itsHighBip8Count;
    theStream >> aRxPti;
    itsRxPayloadType = static_cast<uint8>(aRxPti);
    theStream >> itsInternalAIS;
    theStream >> itsInternalLCK;
    theStream >> itsInternalOCI;
    theStream >> itsSSF; 
    theStream >> itsSSFforSGEO; 
    theStream >> itsPathDelay; 
    theStream >> itsPrbsRxLosync;
    theStream >> itsPrbsRxErrorCountHigh;
    theStream >> itsPrbsRxErrorCountLow;
    theStream >> itsPrbsRxErrorTime;
    theStream >> itsTIM;

    // Configuration
    theStream >> itsTxTrace;
    theStream >> itsExpectedTrace;
    theStream >> ((int&)itsForcedODUIndication);
    theStream >> ((int&)itsForcedInternalODUIndication);
    theStream >> itsForcedInternalAIS;
    theStream >> itsForcedBDI;
    theStream >> aBerSfThreshold;
    theStream >> aBerSdThreshold;
    theStream >> aTxPti;
    itsTxPayloadType = static_cast<uint8>(aTxPti);
    theStream >> itsIsOduTerm;
    theStream >> itsSrcTrafficEnabled;
    theStream >> itsBurstySdBerIntervals;
    theStream >> itsBurstySdBerThreshold;
    theStream >> aODUTsSize;
    theStream >> aClockType;
    theStream >> itsTribPort;
    theStream >> itsPathDelayEnabled;
    theStream >> itsExpRate;
    theStream >> itsNULLSignalEnable;
    theStream >> itsPRBSRXEnable;
    theStream >> itsPRBSRXSessionCounter; 
    theStream >> itsPRBSTXEnable; 
    theStream >> itsGfpTsNum;
    theStream >> aServer;
    theStream >> itsXcOtherSideIndex;
    theStream >> aTIMCriteraMode;
    theStream >> aExpectPti;
    theStream >> itsLayerFailOnTIM;
    theStream >> itsTIMMonitoringEnable;
    theStream >> itsProvisioned;
    theStream >> itsCrossConnected;
    itsExpectedPayloadType = static_cast<uint8>(aExpectPti);

    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsODUTsSize = (CT_TEL_TS_SIZE) aODUTsSize;
    itsClockType = (CT_TEL_ClkType) aClockType;
    itsServer    = (CT_ODU_ServerID)aServer;
    itsTIMCriteraMode = (CT_TEL_TimCriteriaMode) aTIMCriteraMode;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_DwIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aBerSfThreshold = itsBerSfThreshold;
    int aBerSdThreshold = itsBerSdThreshold;
    int aODUTsSize = itsODUTsSize;
    int aClockType = itsClockType;
    uint32 aServer = itsServer.GetIdValue();
    int aTIMCriteraMode = itsTIMCriteraMode;

    // Monitoring
    theStream << itsRxTrace;
    theStream << FC_InsertVar(itsAIS);
    theStream << FC_InsertVar(itsLCK);
    theStream << FC_InsertVar(itsOCI);
    theStream << FC_InsertVar(itsBDI);
    theStream << FC_InsertVar(itsBerSf);
    theStream << FC_InsertVar(itsBerSd);
    theStream << FC_InsertVar(itsPLM);
    theStream << FC_InsertVar(itsMSIM);
    theStream << FC_InsertVar(itsGenAIS);
    theStream << FC_InsertVar(itsLOFLOM);
    theStream << FC_InsertVar(itsLOOMFI);
    theStream << FC_InsertVar(itsBip8Count);
    theStream << FC_InsertVar(itsHighBip8Count);
    theStream << FC_InsertVar(itsRxPayloadType);
    theStream << FC_InsertVar(itsInternalAIS);
    theStream << FC_InsertVar(itsInternalLCK);
    theStream << FC_InsertVar(itsInternalOCI);
    theStream << FC_InsertVar(itsSSF);
    theStream << FC_InsertVar(itsSSFforSGEO);
    theStream << FC_InsertVar(itsPathDelay);
    theStream << FC_InsertVar(itsPrbsRxLosync);
    theStream << FC_InsertVar(itsPrbsRxErrorCountHigh);
    theStream << FC_InsertVar(itsPrbsRxErrorCountLow);
    theStream << FC_InsertVar(itsPrbsRxErrorTime);
    theStream << FC_InsertVar(itsTIM);

    // Configuration
    theStream << itsTxTrace;
    theStream << itsExpectedTrace;
    theStream << FC_InsertVar((int&)itsForcedODUIndication);
    theStream << FC_InsertVar((int&)itsForcedInternalODUIndication);
    theStream << FC_InsertVar(itsForcedInternalAIS);
    theStream << FC_InsertVar(itsForcedBDI);
    theStream << FC_InsertVar(aBerSfThreshold);
    theStream << FC_InsertVar(aBerSdThreshold);
    theStream << FC_InsertVar(itsTxPayloadType);
    theStream << FC_InsertVar(itsIsOduTerm);
    theStream << FC_InsertVar(itsSrcTrafficEnabled);
    theStream << FC_InsertVar(itsBurstySdBerIntervals);
    theStream << FC_InsertVar(itsBurstySdBerThreshold);
    theStream << FC_InsertVar(aODUTsSize);
    theStream << FC_InsertVar(aClockType);
    theStream << FC_InsertVar(itsTribPort);
    theStream << FC_InsertVar(itsPathDelayEnabled);
    theStream << FC_InsertVar(itsExpRate);
    theStream << FC_InsertVar(itsNULLSignalEnable);
    theStream << FC_InsertVar(itsPRBSRXEnable);
    theStream << FC_InsertVar(itsPRBSTXEnable);
    theStream << FC_InsertVar(itsPRBSRXSessionCounter);
    theStream << FC_InsertVar(itsGfpTsNum);
    theStream << FC_InsertVar(aServer);
    theStream << FC_InsertVar(itsXcOtherSideIndex);
    theStream << FC_InsertVar(aTIMCriteraMode);
    theStream << FC_InsertVar(itsExpectedPayloadType);
    theStream << FC_InsertVar(itsLayerFailOnTIM);
    theStream << FC_InsertVar(itsTIMMonitoringEnable);
    theStream << FC_InsertVar(itsProvisioned);
    theStream << FC_InsertVar(itsCrossConnected);
    
    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_DwIf::ReadObject(istream & theStream)
{
    int aBerSfThreshold;
    int aBerSdThreshold;
    int aODUTsSize;
    int aClockType;
    uint32 aServer;
    int aTIMCriteraMode;

    // Monitoring
    theStream >> itsRxTrace;
    theStream >> FC_ExtractVar(itsAIS);
    theStream >> FC_ExtractVar(itsLCK);
    theStream >> FC_ExtractVar(itsOCI);
    theStream >> FC_ExtractVar(itsBDI);
    theStream >> FC_ExtractVar(itsBerSf);
    theStream >> FC_ExtractVar(itsBerSd);
    theStream >> FC_ExtractVar(itsPLM);
    theStream >> FC_ExtractVar(itsMSIM);
    theStream >> FC_ExtractVar(itsGenAIS);
    theStream >> FC_ExtractVar(itsLOFLOM);
    theStream >> FC_ExtractVar(itsLOOMFI);
    theStream >> FC_ExtractVar(itsBip8Count);
    theStream >> FC_ExtractVar(itsHighBip8Count);
    theStream >> FC_ExtractVar(itsRxPayloadType);
    theStream >> FC_ExtractVar(itsInternalAIS);
    theStream >> FC_ExtractVar(itsInternalLCK);
    theStream >> FC_ExtractVar(itsInternalOCI);
    theStream >> FC_ExtractVar(itsSSF);
    theStream >> FC_ExtractVar(itsSSFforSGEO);
    theStream >> FC_ExtractVar(itsPathDelay);
    theStream >> FC_ExtractVar(itsPrbsRxLosync);
    theStream >> FC_ExtractVar(itsPrbsRxErrorCountHigh);
    theStream >> FC_ExtractVar(itsPrbsRxErrorCountLow);
    theStream >> FC_ExtractVar(itsPrbsRxErrorTime);
    theStream >> FC_ExtractVar(itsTIM);

    // Configuration
    theStream >> itsTxTrace;
    theStream >> itsExpectedTrace;
    theStream >> FC_ExtractVar((int&)itsForcedODUIndication);
    theStream >> FC_ExtractVar((int&)itsForcedInternalODUIndication);
    theStream >> FC_ExtractVar(itsForcedInternalAIS);
    theStream >> FC_ExtractVar(itsForcedBDI);
    theStream >> FC_ExtractVar(aBerSfThreshold);
    theStream >> FC_ExtractVar(aBerSdThreshold);
    theStream >> FC_ExtractVar(itsTxPayloadType);
    theStream >> FC_ExtractVar(itsIsOduTerm);
    theStream >> FC_ExtractVar(itsSrcTrafficEnabled);
    theStream >> FC_ExtractVar(itsBurstySdBerIntervals);
    theStream >> FC_ExtractVar(itsBurstySdBerThreshold);
    theStream >> FC_ExtractVar(aODUTsSize);
    theStream >> FC_ExtractVar(aClockType);
    theStream >> FC_ExtractVar(itsTribPort);
    theStream >> FC_ExtractVar(itsPathDelayEnabled);
    theStream >> FC_ExtractVar(itsExpRate);
    theStream >> FC_ExtractVar(itsNULLSignalEnable);
    theStream >> FC_ExtractVar(itsPRBSRXEnable);
    theStream >> FC_ExtractVar(itsPRBSTXEnable);
    theStream >> FC_ExtractVar(itsPRBSRXSessionCounter);
    theStream >> FC_ExtractVar(itsGfpTsNum);
    theStream >> FC_ExtractVar(aServer);
    theStream >> FC_ExtractVar(itsXcOtherSideIndex);
    theStream >> FC_ExtractVar(aTIMCriteraMode); 
    theStream >> FC_ExtractVar(itsExpectedPayloadType);
    theStream >> FC_ExtractVar(itsLayerFailOnTIM);
    theStream >> FC_ExtractVar(itsTIMMonitoringEnable);
    theStream >> FC_ExtractVar(itsProvisioned);
    theStream >> FC_ExtractVar(itsCrossConnected);
    
    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsODUTsSize = (CT_TEL_TS_SIZE) aODUTsSize;
    itsClockType = (CT_TEL_ClkType) aClockType;
    itsServer    = (CT_ODU_ServerID) aServer;
    itsTIMCriteraMode = (CT_TEL_TimCriteriaMode) aTIMCriteraMode;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  Digital Wrapper (ODU) Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      DW TX Trace  = Sapi   = " << itsTxTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                     Dapi   = " << itsTxTrace.GetDapiPrintable(false)         << "\n";
    theStream << "          OperatorSpecific  = " << itsTxTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                      CRC7  = " << (uint32)itsTxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsTxTrace.IsValid())          << "\n";
    theStream << "      DW TIM CRITERA        = " << DISPLAY_TIMCRITERIAMODE(itsTIMCriteraMode) << "\n";
    theStream << "      DW EXP Trace = Sapi   = " << itsExpectedTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                      Dapi  = " << itsExpectedTrace.GetDapiPrintable(false)         << "\n";
    theStream << "                   Operator = " << itsExpectedTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                   Trace ID = " << itsExpectedTrace.GetTraceID()                    << "\n";
    theStream << "                       CRC7 = " << (uint32)itsExpectedTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsExpectedTrace.IsValid())          << "\n";
    theStream << "      DW TIM Mon enable     = " << TEXT_ON_OFF(itsTIMMonitoringEnable)        << "\n";
    theStream << "      DW Layer Fail on TIM  = " << TEXT_ON_OFF(itsLayerFailOnTIM)             << "\n";
    theStream << "      DW if provisioned     = " << TEXT_ON_OFF(itsProvisioned)                << "\n";
    theStream << "      DW if cross connected = " << TEXT_ON_OFF(itsCrossConnected)             << "\n";
    theStream << "      DW ind forced         = " << DISPLAY_ODU_INDICATION(itsForcedODUIndication) << "\n";
    theStream << "      DW internal ind forced= " << DISPLAY_ODU_INDICATION(itsForcedInternalODUIndication) << "\n";
    theStream << "      DW BDI forced         = " << TEXT_ON_OFF(itsForcedBDI)                  << "\n";
    theStream << "      DW internal AIS forced= " << TEXT_ON_OFF(itsForcedInternalAIS)          << "\n";
    theStream << "      DW BerSfThreshold     = " << DISPLAY_BER(itsBerSfThreshold)             << "\n";
    theStream << "      DW BerSdThreshold     = " << DISPLAY_BER(itsBerSdThreshold)             << "\n";
    theStream << "      DW Bursty BER Thresh  = DEGM(" << itsBurstySdBerIntervals << ") DEGTHR(" << itsBurstySdBerThreshold << ")\n";
    theStream << "      DW TX PayloadType     = 0x" << hex << static_cast<uint32>(itsTxPayloadType) << dec << " " << DISPLAY_OPU_PSI(itsTxPayloadType) << "\n";
    theStream << "      DW Expct PayloadType  = 0x" << hex << static_cast<uint32>(itsExpectedPayloadType) << dec << " " << DISPLAY_OPU_PSI(itsExpectedPayloadType) << "\n";
    theStream << "      DW Odu Terminating    = " << TEXT_ON_OFF(itsIsOduTerm)                  << "\n";
    theStream << "      DW Src Traffic Enable = " << TEXT_ON_OFF(itsSrcTrafficEnabled)          << "\n";
    theStream << "      DW ODU PT Mode        = " << DISPLAY_TS_SIZE(itsODUTsSize)           << "\n";
    theStream << "      Clock Type            = " << DISPLAY_CLOCK_TYPE(itsClockType)           << "\n";
    theStream << "      DW Trib Port          = 0x" << hex << itsTribPort << dec << " " << itsTribPort << "\n";
    theStream << "      DW Path Delay Enable  = " << TEXT_ON_OFF(itsPathDelayEnabled)           << "\n";
    theStream << "      ExpRate(Rate/10)      = " << (uint32)itsExpRate                   << "\n";
    theStream << "      DW NULL Signal Enable = " << TEXT_ON_OFF(itsNULLSignalEnable)           << "\n";
    theStream << "      DW PRBS RX Enable     = " << TEXT_ON_OFF(itsPRBSRXEnable)           << "\n";
    theStream << "      DW PRBS TX Enable     = " << TEXT_ON_OFF(itsPRBSTXEnable)           << "\n";
    theStream << "      DW PRBS RX Session Cnt= " << itsPRBSRXSessionCounter       << "\n";
    theStream << "      DW TribSlot Num       = " << (uint32)itsGfpTsNum          << "\n";
    theStream << "      DW Server ID          = 0x" << hex << itsServer.GetIdValue() << dec << itsServer.DisplayServerID() << "\n";
    theStream << "      DW Xc OtherSide Index = " << itsXcOtherSideIndex << "\n";
    theStream << "      DW APS Channel        = " << itsTxAps.channel << "\n";
    theStream << "      DW APS Bytes          = 0x" << hex << itsTxAps.bytes << dec << " " << itsTxAps.bytes << "\n";
	theStream << "      DW APS insertion      = " << TEXT_ON_OFF(itsTxAps.apsInsert) << "\n";
    theStream << "    MONITORING\n";
    theStream << "      DW RX Trace  = Sapi   = " << itsRxTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                     Dapi   = " << itsRxTrace.GetDapiPrintable(false)         << "\n";
    theStream << "          OperatorSpecific  = " << itsRxTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                      CRC7  = " << (uint32)itsRxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsRxTrace.IsValid())          << "\n";
    theStream << "      DW AIS defect         = " << TEXT_DEFECT(itsAIS)                        << "\n";
    theStream << "      DW LCK defect         = " << TEXT_DEFECT(itsLCK)                        << "\n";
    theStream << "      DW OCI defect         = " << TEXT_DEFECT(itsOCI)                        << "\n";
    theStream << "      DW BDI defect         = " << TEXT_DEFECT(itsBDI)                        << "\n";
    theStream << "      DW BerSf defect       = " << TEXT_DEFECT(itsBerSf)                      << "\n";
    theStream << "      DW BerSd defect       = " << TEXT_DEFECT(itsBerSd)                      << "\n";
    theStream << "      DW PLM defect         = " << TEXT_DEFECT(itsPLM)                        << "\n";
    theStream << "      DW TIM defect         = " << TEXT_DEFECT(itsTIM)                        << "\n";
    theStream << "      DW MSIM defect        = " << TEXT_DEFECT(itsMSIM)                        << "\n";
    theStream << "      DW LOFLOM defect      = " << TEXT_DEFECT(itsLOFLOM)                        << "\n";
    theStream << "      DW LOOMFI defect      = " << TEXT_DEFECT(itsLOOMFI)                        << "\n";
    theStream << "      DW GenAIS defect      = " << TEXT_DEFECT(itsGenAIS)                        << "\n";
    theStream << "      BIP8                  = " << itsBip8Count                                  << "\n";
    theStream << "      High BIP8             = " << itsHighBip8Count                               << "\n";
    theStream << "      DW RX PayloadType     = 0x" << hex << static_cast<uint32>(itsRxPayloadType) << dec << " " << DISPLAY_OPU_PSI(itsRxPayloadType) << "\n";
    theStream << "      DW Internal AIS defect= " << TEXT_DEFECT(itsInternalAIS)                        << "\n";
    theStream << "      DW Internal LCK defect= " << TEXT_DEFECT(itsInternalLCK)                        << "\n";
    theStream << "      DW Internal OCI defect= " << TEXT_DEFECT(itsInternalOCI)                        << "\n";
    theStream << "      DW SSF defect         = " << TEXT_DEFECT(itsSSF)                        << "\n";
    theStream << "      DW SSF for SGEO defect= " << TEXT_DEFECT(itsSSFforSGEO)                 << "\n";
    theStream << "      Path Delay            = " << itsPathDelay                                << "\n";
    theStream << "      PRBS RX Losync        = " << TEXT_DEFECT(itsPrbsRxLosync)                                << "\n";
    theStream << "      PRBS Rx Errors        = " << itsPrbsRxErrorCountHigh << ", " << itsPrbsRxErrorCountLow << " \n";
    theStream << "      PRBS Rx Time          = " << itsPrbsRxErrorTime                             << " milliSeconds\n";
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::Set(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 4 && strcmp(argv[0], "txtrace") == 0)
    {
        CT_G709Trace trace(argv[1], argv[2], argv[3]);
        SetTxTrace(trace);
    }
    else if (argc == 4 && strcmp(argv[0], "expectedtrace") == 0)
    {
        CT_G709Trace trace(argv[1], argv[2], argv[3]);
        SetExpectedTrace(trace);
    }    
    else if (argc == 2 && strcmp(argv[0], "forceind") == 0)
    {
        if (strcmp(argv[1], "ais") == 0)
        {
            ForceODUIndication(CT_ODU_INDICATION_AIS);
        }
        else if (strcmp(argv[1], "oci") == 0)
        {
            ForceODUIndication(CT_ODU_INDICATION_OCI);
        }
        else if (strcmp(argv[1], "lck") == 0)
        {
            ForceODUIndication(CT_ODU_INDICATION_LCK);
        }
        else if (strcmp(argv[1], "unknown") == 0)
        {
            ForceODUIndication(CT_ODU_INDICATION_UNKNOWN);
        }
        else if (strcmp(argv[1], "none") == 0)
        {
            ForceODUIndication(CT_ODU_INDICATION_NONE);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "forceintind") == 0)
    {
        if (strcmp(argv[1], "ais") == 0)
        {
            ForceInternalODUIndication(CT_ODU_INDICATION_AIS);
        }
        else if (strcmp(argv[1], "oci") == 0)
        {
            ForceInternalODUIndication(CT_ODU_INDICATION_OCI);
        }
        else if (strcmp(argv[1], "lck") == 0)
        {
            ForceInternalODUIndication(CT_ODU_INDICATION_LCK);
        }
        else if (strcmp(argv[1], "unknown") == 0)
        {
            ForceInternalODUIndication(CT_ODU_INDICATION_UNKNOWN);
        }
        else if (strcmp(argv[1], "none") == 0)
        {
            ForceInternalODUIndication(CT_ODU_INDICATION_NONE);
        }
        else
        {
            printUsage = true;
        }

    }
    else if (argc == 2 && strcmp(argv[0], "forcebdi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            ForceBDI(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            ForceBDI(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "forceintais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            ForceInternalAIS(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            ForceInternalAIS(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "bersfthres") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_INFINITE_BER; i++) if (strcmp(argv[1], DISPLAY_BER(i)) == 0)
        {
            SetBerSfThreshold((CT_TEL_BERLevels)i);
            printUsage = false;
            break;
        }
    }
    else if((argc == 2) && strcmp(argv[0], "gfptsnum") == 0)
    {
        SetGfpTsNum(static_cast<uint8>(strtoul(argv[1], NULL, 0)));
        printUsage = false;
    }
    else if((argc == 2) && strcmp(argv[0], "tssize") == 0)
    {
        if (strcmp(argv[1], "2.5G") == 0)
        {
            SetODUTsSize(CT_TEL_TS_2G5);
        }
        else if (strcmp(argv[1], "1.25G") == 0)
        {
            SetODUTsSize(CT_TEL_TS_1G25);
        }
        else if (strcmp(argv[1], "unknown") == 0)
        {
            SetODUTsSize(CT_TEL_TS_UNKNOWN);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "clocktype") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i < CT_TEL_CLK_UNKNOWN; i++)
        {
            if (strcmp(argv[1], DISPLAY_CLOCK_TYPE(i)) == 0)
            {
                SetClockType((CT_TEL_ClkType)i);
                printUsage = false;
                break;
            }
        }
    }
    else if((argc == 2) && strcmp(argv[0], "txpayloadtype") == 0)
    {
        uint8 txpt = static_cast<uint8>(strtoul(argv[1], NULL, 0));
        SetTxPayloadType(txpt);
        printUsage = false;
    }
    else if((argc == 2) && strcmp(argv[0], "expectpayloadtype") == 0)
    {
        uint8 txpt = static_cast<uint8>(strtoul(argv[1], NULL, 0));
        SetExpectedPayloadType(txpt);
        printUsage = false;
    }
    else if((argc == 2) && strcmp(argv[0], "oduterm") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIsOduTerm(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIsOduTerm(false);
        }
        else
        {
            printUsage = true;
        }
    }
    // Must parse "Error free" as two arguments since FC parser doesn't do it if quoted.
    else if ((argc == 3) && (strcmp(argv[0], "bersfthres") == 0) &&
             (strcmp(argv[1], "Error") == 0) &&
             (strcmp(argv[2], "free") == 0))
    {
        SetBerSfThreshold(CT_TEL_NO_BER);
        printUsage = false;
    }
    else if ((argc == 2) && strcmp(argv[0], "bersdthres") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_INFINITE_BER; i++) if (strcmp(argv[1], DISPLAY_BER(i)) == 0)
        {
            SetBerSdThreshold((CT_TEL_BERLevels)i);
            printUsage = false;
            break;
        }
    }
    // Must parse "Error free" as two arguments since FC parser doesn't do it if quoted.
    else if ((argc == 3) && (strcmp(argv[0], "bersdthres") == 0) &&
             (strcmp(argv[1], "Error") == 0) &&
             (strcmp(argv[2], "free") == 0))
    {
        SetBerSdThreshold(CT_TEL_NO_BER);
        printUsage = false;
    }
    else if ((argc == 2) && (strcmp(argv[0], "trafenabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetSrcTrafficEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetSrcTrafficEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "pdenabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetPathDelayEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetPathDelayEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if((argc == 3) && (strcmp(argv[0], "berburst") == 0))
    {
      SetBurstyBerSdThreshold(strtoul(argv[1], NULL, 0), strtoul(argv[2], NULL, 0));
      printUsage = false;
    }
    else if((argc == 2) && (strcmp(argv[0], "tribport") == 0))
    {
        SetTribPort(static_cast<uint16>(strtoul(argv[1], NULL, 0)));
        printUsage = false;
    }
    else if((argc == 2) && (strcmp(argv[0], "nullsig") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetNULLSignalEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetNULLSignalEnable(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if((argc == 2) && (strcmp(argv[0], "prbstx") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetPRBSTXEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetPRBSTXEnable(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if((argc == 2) && (strcmp(argv[0], "prbsrx") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetPRBSRXEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetPRBSRXEnable(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if((argc == 2) && (strcmp(argv[0], "exprate") == 0))
    {
        SetExpRate( strtoul(argv[1], NULL, 0));
    }
    else if (argc == 2 && strcmp(argv[0], "server") == 0 )
    {
        if (!isxdigit(argv[1][0]))
        {
            fc_cout << "Error: Server ID must be a hex number" << endl;
            printUsage = true;
        }
        else
        {
            SetServer(CT_ODU_ServerID(strtoul(argv[1], NULL, 0)));
            printUsage = false;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "timcritera") == 0)
    {
        if (strcmp(argv[1], "sapi") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_SAPI);
        }
        else if (strcmp(argv[1], "dapi") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_DAPI);
        }
        else if (strcmp(argv[1], "sapi_dapi") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_SAPI_DAPI);
        }
        else if (strcmp(argv[1], "oper") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_OPER);
        }
        else if (strcmp(argv[1], "sapi_oper") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_SAPI_OPER);
        }
        else if (strcmp(argv[1], "dapi_oper") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_DAPI_OPER);
        }
        else if (strcmp(argv[1], "sapi_dapi_oper") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_SAPI_DAPI_OPER);
        }
        else if (strcmp(argv[1], "unknown") == 0)
        {
            SetTimCriteria(CT_TEL_TIM_UNKNOWN);
        }        
        else
        {
            printUsage = true;
        }
    }    
    else if((argc == 2) && (strcmp(argv[0], "timmon") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetTIMMonitoringEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetTIMMonitoringEnable(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if((argc == 2) && (strcmp(argv[0], "layerfailontim") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetLayerFailOnTIM(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetLayerFailOnTIM(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if((argc == 2) && (strcmp(argv[0], "isprovisioned") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetIsProvisioned(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetIsProvisioned(false);
        }
        else
        {
            printUsage = true;
        }
    }    
    else if((argc == 4) && (strcmp(argv[0], "txapsbytes") == 0) && ((strcmp(argv[3], "on") == 0) || (strcmp(argv[3], "off") == 0)) )
    {
        CT_SP_APS_Channel apsChannel = static_cast<CT_SP_APS_Channel>(strtoul(argv[1], NULL, 0));
        uint32 apsBytes = static_cast<uint32>(strtoul(argv[2], NULL, 0));
		bool apsInsert = (strcmp(argv[3], "on") == 0) ? true:false;
        SetTxApsBytes(apsChannel, apsBytes,apsInsert);
        printUsage = false;
    }
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    txtrace         <sapi(15 char max)> <dapi(15 char max)> <operator(28 char max)>\n"
                   "    expectedtrace   <sapi(15 char max)> <dapi(15 char max)> <operator(28 char max)>\n"
                   "    timcritera      <sapi|dapi|sapi_dapi|oper|sapi_oper|dapi_oper|sapi_dapi_oper|unknown>\n"
                   "    timmon          <on|off>\n"
                   "    isprovisioned   <on|off>\n"
                   "    layerfailontim  <on|off>\n"
                   "    forceind        <ais|oci|lck|unknown|none>\n"	
                   "    forceintind     <ais|oci|lck|unknown|none>\n"	
                   "    forceintais     <on|off>\n"
                   "    forcebdi        <on|off>\n"
                   "    bersfthres      <Error free|10-12|10-11| ... |10-3>\n"
                   "    bersdthres      <Error free|10-12|10-11| ... |10-3>\n"
                   "    berburst        <intervals(DEGM)> <threshold(DEGTHR)>\n"
                   "    oduterm         <on|off>\n"
                   "    pdenabled       <on|off>\n"
                   "    txpayloadtype   <pt (0-255)>\n" 
                   "    tssize          <2.5G|1.25G|unknown>\n"
                   "    gfptsnum        <num (0-255)>\n"
                   "    trafenabled     <on|off>\n"
                   "    tribport        <1-32>\n"
                   "    nullsig         <on|off>\n"
                   "    prbstx          <on|off>\n"
                   "    prbsrx          <on|off>\n"
                   "    exprate         <rate/10>\n"
                   "    server          <32 bit hex 0x Server>\n"
				   "    txapsbytes      <apschannel> <apsbytes> <on|off>\n" << endl;
        DisplayClockTypes();
        fc_cout << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_DwIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 4 && strcmp(argv[0], "rxtrace") == 0)
    {
        itsRxTrace = CT_G709Trace(argv[1], argv[2], argv[3]); 
    }
    else if (argc == 2 && strcmp(argv[0], "bdi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBDI)) itsBDI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBDI)) itsBDI++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsAIS)) itsAIS++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsAIS)) itsAIS++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "oci") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsOCI)) itsOCI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsOCI)) itsOCI++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "lck") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLCK)) itsLCK++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLCK)) itsLCK++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "bersf") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBerSf)) itsBerSf++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBerSf)) itsBerSf++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "bersd") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsBerSd)) itsBerSd++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsBerSd)) itsBerSd++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "plm") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsPLM)) itsPLM++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsPLM)) itsPLM++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "msim") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsMSIM)) itsMSIM++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsMSIM)) itsMSIM++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "genais") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsGenAIS)) itsGenAIS++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsGenAIS)) itsGenAIS++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "loflom") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLOFLOM)) itsLOFLOM++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLOFLOM)) itsLOFLOM++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "loomfi") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLOOMFI)) itsLOOMFI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLOOMFI)) itsLOOMFI++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "tim") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsTIM)) itsTIM++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsTIM)) itsTIM++;
        }
        else
        {
            printUsage = true;
        }
    }    
    else if (argc == 2 && strcmp(argv[0], "bip8") == 0)
    {
        itsBip8Count = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "incbip8") == 0)
    {
        itsBip8Count += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "highbip8") == 0)
    {
        itsHighBip8Count = strtoul(argv[1], NULL, 0);
    }
    else if((argc == 2) && (strcmp(argv[0], "rxpayloadtype") == 0))
    {
        itsRxPayloadType = static_cast<uint8>(strtoul(argv[1], NULL, 0));
        printUsage = false;
    }
    else if (argc == 2 && strcmp(argv[0], "internalais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsInternalAIS)) itsInternalAIS++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsInternalAIS)) itsInternalAIS++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "internallck") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsInternalLCK)) itsInternalLCK++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsInternalLCK)) itsInternalLCK++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "internaloci") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsInternalOCI)) itsInternalOCI++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsInternalOCI)) itsInternalOCI++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ssf") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsSSF)) itsSSF++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsSSF)) itsSSF++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ssf4sgeo") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsSSFforSGEO)) itsSSFforSGEO++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsSSFforSGEO)) itsSSFforSGEO++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "prbsrxlosync") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsPrbsRxLosync)) itsPrbsRxLosync++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsPrbsRxLosync)) itsPrbsRxLosync++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 3 && strcmp(argv[0], "prbsrxerrs") == 0)
    {
        itsPrbsRxErrorCountHigh = strtoul(argv[1], NULL, 0);
        itsPrbsRxErrorCountLow = strtoul(argv[2], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "prbsrxtime") == 0)
    {
        itsPrbsRxErrorTime = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "delay") == 0)
    {
        itsPathDelay = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "exprate") == 0)
    {
        itsExpRate =  strtoul(argv[1], NULL, 0);
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    rxtrace         <sapi(15 char max)> <dapi(15 char max)> <operator(28 char max)>\n"
                   "    ais             <on|off>\n"
                   "    lck             <on|off>\n"
                   "    oci             <on|off>\n"
                   "    bdi             <on|off>\n" 
                   "    bersf           <on|off>\n"
                   "    bersd           <on|off>\n" 
                   "    plm             <on|off>\n" 
                   "    msim            <on|off>\n" 
                   "    loflom          <on|off>\n" 
                   "    loomfi          <on|off>\n" 
                   "    genais          <on|off>\n" 
                   "    bip8            <count>\n"
                   "    incbip8         <increment>\n"
                   "    highbip8        <count>\n"
                   "    rxpayloadtype   <pt (0-255)>\n" 
                   "    internalais     <on|off>\n"
                   "    internallck     <on|off>\n"
                   "    internaloci     <on|off>\n"
                   "    ssf             <on|off>\n"
                   "    tim             <on|off>\n"
                   "    ssf4sgeo        <on|off>\n"
                   "    prbsrxlosync    <on|off>\n"
                   "    prbsrxerrs      <counth countl>\n"
                   "    prbsrxtime      <time>\n"
                   "    exprate         <rate/10>\n"
                   "    delay           <0-2147483647>\n" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_DwIf::DisplayClockTypes()
{
    int clkType;

    fc_cout << "    clocktype         <";
    for(clkType = (int) CT_TEL_CLK_G709; clkType < (int) CT_TEL_CLK_UNKNOWN; clkType++)
    {
        fc_cout << DISPLAY_CLOCK_TYPE((CT_TEL_ClkType)clkType) << "|";
    }
    fc_cout << ">\n";
}

