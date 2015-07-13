/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Eric Bernier November 30th 1999
 DESCRIPTION:Definition of the class TSPII_RsIf
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_RsIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>
#include "CommonTypes/CT_Telecom.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_RsIf::TSPII_RsIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_RsIf::~TSPII_RsIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::RefreshGet()
{
    bool isSet;

    // Monitoring attributes
    itsRxTrace            = GetRxTrace();
    itsCVCount            = GetCVCount();
    itsHighCVCount        = GetHighCVCount();
    itsLOS                = GetLOS();
    itsLOF                = GetLOF();
    itsGENAIS             = GetGENAIS();
    itsOOF                = GetOOF();
    itsTIM                = GetTIM();
    itsTlabAISRx          = GetTlabAISRx();
    itsTlabAISTx          = GetTlabAISTx();
    itsInternalLOF        = GetInternalLOF();
    itsInternalGENAIS     = GetInternalGENAIS();
    itsInternalCSFOPU     = GetInternalCSFOPU();
    itsOrderedSetLocalFault   = GetLocalFault();
    itsOrderedSetRemoteFault  = GetRemoteFault();


    // Configuration attributes
    itsTxTrace            = GetTxTrace();
    itsExpectedTrace      = GetExpectedTrace();
    itsForceAIS           = GetForceAIS();
    itsTxTraceTransparent = GetTxTraceTransparent();
    itsSignalType         = GetSignalType();
    itsClockType          = GetClockType();
    isSet                 = GetSfpRouteAndSignalType(itsSfpRouteEnd, itsSfpRouteMiddle, itsSignalType);
    itsForceInternalAIS   = GetForceInternalAIS();
    itsForceRDI           = GetForceRDI();
    itsRdiReiAutomatic    = GetRdiReiAutomatic();
    itsMessagingEnabled   = GetMessagingEnabled();
    itsForceInternalCSFOPU= GetForceInternalCSFOPU();
    itsForceTlabAIS       = GetForceTlabAIS();
    itsAutoTlabAIS        = GetAutoTlabAIS();
    itsAutoRateLockActive = GetAutoRateLockActive();
    itsUseSDHMode         = GetTrueSDHMode();
    itsAddEnable          = GetAddonly();
    itsDropEnable         = GetDroponly();
    itsOduMappingMode     = GetCBRMappingMode();
    itsForcedRsIndication   = GetForceRsIndication();
    itsForcedInternalRsIndication   = GetForceInternalRsIndication();
    itsReplaceSig         = GetReplaceSig();
    itsInterPacketGap     = GetInterPacketGap();
    itsLayerFailOnTIM      = GetLayerFailOnTIM();
    itsTIMMonitoringEnable = GetTIMMonitoringEnable();    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::RefreshSet()
{
    // Configuration attributes
    SetTxTrace(itsTxTrace);
    SetExpectedTrace(itsExpectedTrace);
    ForceAIS(itsForceAIS);
    SetTxTraceTransparent(itsTxTraceTransparent);
    SetSignalType(itsSignalType);
    SetClockType(itsClockType);
    SetSfpRouteAndSignalType(itsSfpRouteEnd, itsSfpRouteMiddle, itsSignalType, itsClockType);
    SetForceInternalAIS(itsForceInternalAIS);
    SetForceRDI(itsForceRDI);
    SetRdiReiAutomatic(itsRdiReiAutomatic);
    SetEnableMessaging(itsMessagingEnabled);
    SetForceInternalCSFOPU(itsForceInternalCSFOPU);
    SetForceTlabAIS(itsForceTlabAIS);
    SetAutoTlabAIS(itsAutoTlabAIS);
    SetAutoRateLockActive(itsAutoRateLockActive);
    SetTrueSDHMode(itsUseSDHMode);
    SetAddonly(itsAddEnable);
    SetDroponly(itsDropEnable);
    SetCBRMappingMode(itsOduMappingMode);
    ForceRsIndication(itsForcedRsIndication);
    ForceInternalRsIndication(itsForcedInternalRsIndication);
    SetReplaceSig(itsReplaceSig);
    SetInterPacketGap(itsInterPacketGap);
    SetLayerFailOnTIM(itsLayerFailOnTIM);
    SetTIMMonitoringEnable(itsTIMMonitoringEnable);    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsRxTrace            = CT_SDH16ByteTrace("NULL           ");
    itsCVCount            = 0;
    itsHighCVCount        = 0;
    itsLOS                = 0;
    itsLOF                = 0;
    itsGENAIS             = 0;
    itsOOF                = 0;
    itsTIM                = 0;
    itsTlabAISRx          = 0;
    itsTlabAISTx          = false;
    itsInternalLOF        = 0;
    itsInternalGENAIS     = 0;
    itsInternalCSFOPU     = 0;
    itsOrderedSetLocalFault     = 0;
    itsOrderedSetRemoteFault    = 0;


    // Configuration attributes
    itsTxTrace            = CT_SDH16ByteTrace("NULL           ");
    itsExpectedTrace      = CT_SDH16ByteTrace("NULL           ");
    itsForceAIS           = false;
    itsTxTraceTransparent = true;
    itsSignalType         = CT_TEL_SIGNAL_UNKNOWN;
    itsClockType          = CT_TEL_CLK_UNKNOWN;
    itsSfpRouteEnd        = 0;
    itsSfpRouteMiddle     = 0;
    itsForceInternalAIS   = false;
    itsForceRDI           = false;
    itsRdiReiAutomatic    = true;
    itsMessagingEnabled   = false;
    itsForceInternalCSFOPU= false;
    itsForceTlabAIS       = false;
    itsAutoTlabAIS        = false;
    itsAutoRateLockActive = false;
    itsUseSDHMode         = false;
    itsAddEnable          = false;
    itsDropEnable         = false;    
    itsOduMappingMode     = NULL_MAPPING;

    itsSonetTerminated    = false;
    itsForcedRsIndication   = CT_RS_INDICATION_UNKNOWN;
    itsForcedInternalRsIndication = CT_RS_INDICATION_UNKNOWN;    
    itsReplaceSig = CT_RS_INDICATION_UNKNOWN;
    itsInterPacketGap = CT_TEL_DEFAULT_INTERPACKET_GAP;
    itsLayerFailOnTIM       = false;
    itsTIMMonitoringEnable  = false;   
}

///////////////////////////////////////////////////////////////////////////////
const CT_SDH16ByteTrace & TSPII_RsIf::GetRxTrace()
{
    return itsRxTrace;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetCVCount()
{
    return itsCVCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetHighCVCount()
{
    return itsHighCVCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetLOS()
{
    return itsLOS;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetLOF()
{
    return itsLOF;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetGENAIS()
{
    return itsGENAIS;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetOOF()
{
    return itsOOF;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetTIM()
{
    return itsTIM;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetTxTrace(const CT_SDH16ByteTrace & theTrace)
{
    itsTxTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::ForceAIS(bool theEnable)
{
    itsForceAIS = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::ForceRsIndication(CT_RS_IndicationType theIndication)
{
    itsForcedRsIndication = theIndication;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetReplaceSig(CT_RS_ReplaceSigType theType)
{
    itsReplaceSig = theType;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::ForceInternalRsIndication(CT_RS_IndicationType theIndication)
{
    itsForcedInternalRsIndication = theIndication;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetTxTraceTransparent(bool theTransparent)
{
    itsTxTraceTransparent = theTransparent;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetSignalType(CT_TEL_SignalType theSignalType)
{
    itsSignalType = theSignalType;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetClockType(CT_TEL_ClkType theClockType)
{
    itsClockType = theClockType;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetSfpRouteAndSignalType(uint32 theSfpRouteEnd, 
                                          uint32 theSfpRouteMiddle, 
                                          CT_TEL_SignalType theSignalType, 
                                          CT_TEL_ClkType theClockType)
{
    bool foundIt = true;   // Can force false with debugger to simulate failure
                           // 
    itsSfpRouteEnd = theSfpRouteEnd;
    itsSfpRouteMiddle = theSfpRouteMiddle;
    itsSignalType = theSignalType;
    itsClockType = theClockType;

}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetForceInternalAIS(bool theEnable)
{
    itsForceInternalAIS = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetForceRDI(bool theEnable)
{
    itsForceRDI = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetRdiReiAutomatic(bool theEnable)
{
    itsRdiReiAutomatic = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetEnableMessaging(bool theEnable)
{
    itsMessagingEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetInterPacketGap(uint8 theInterPacketGap)
{
    itsInterPacketGap = theInterPacketGap;
}

///////////////////////////////////////////////////////////////////////////////
const CT_SDH16ByteTrace & TSPII_RsIf::GetTxTrace() const
{
    return itsTxTrace;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetForceAIS() const
{
    return itsForceAIS;
}

///////////////////////////////////////////////////////////////////////////////
CT_RS_ReplaceSigType TSPII_RsIf::GetReplaceSig() const
{
    return itsReplaceSig;
}

///////////////////////////////////////////////////////////////////////////////
CT_RS_IndicationType  TSPII_RsIf::GetForceRsIndication() const
{
    return itsForcedRsIndication;
}

///////////////////////////////////////////////////////////////////////////////
CT_RS_IndicationType  TSPII_RsIf::GetForceInternalRsIndication() const
{
    return itsForcedInternalRsIndication;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetTxTraceTransparent() const
{
    return itsTxTraceTransparent;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_SignalType TSPII_RsIf::GetSignalType() const
{
    return itsSignalType;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_ClkType TSPII_RsIf::GetClockType() const
{
    return itsClockType;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetSfpRouteAndSignalType(uint32 & theSfpRouteEnd, uint32 & theSfpRouteMiddle, CT_TEL_SignalType & theSignalType) const
{
    bool foundIt = true;   // Can force false with debugger to simulate failure

    theSfpRouteEnd = itsSfpRouteEnd;
    theSfpRouteMiddle = itsSfpRouteMiddle;
    theSignalType = itsSignalType;
    return foundIt;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetForceInternalAIS() const
{
    return itsForceInternalAIS;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetForceRDI() const
{
    return itsForceRDI;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetRdiReiAutomatic() const
{
    return itsRdiReiAutomatic;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetMessagingEnabled() const
{
    return itsMessagingEnabled;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_RsIf::GetInterPacketGap() const
{
    return itsInterPacketGap; 
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::ForceFrmOduXconn(uint32 theCurSfpRouteEnd, uint32 thePrevSfpRouteEnd)
{
    // Do nothing in simulation
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_RsIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aSignalType = itsSignalType;
    int aClkType = itsClockType;
    int aOduMappingMode = itsOduMappingMode;
    int aForcedRsIndication = itsForcedRsIndication;
    int aForcedInternalRsIndication = itsForcedInternalRsIndication;
    int aReplaceSig     = itsReplaceSig;

    // Monitoring
    theStream << itsRxTrace;
    theStream << itsCVCount;
    theStream << itsHighCVCount;
    theStream << itsLOS;
    theStream << itsLOF;
    theStream << itsGENAIS;
    theStream << itsOOF;
    theStream << itsTIM;
    theStream << itsTlabAISRx;
    theStream << itsTlabAISTx;
    theStream << itsInternalLOF;
    theStream << itsInternalGENAIS;
    theStream << itsInternalCSFOPU;
    theStream << itsOrderedSetLocalFault;
    theStream << itsOrderedSetRemoteFault;


    // Configuration
    theStream << itsTxTrace;
    theStream << itsExpectedTrace;
    theStream << itsForceAIS;
    theStream << itsTxTraceTransparent;
    theStream << aSignalType;
    theStream << (uint32)itsClockType;
    theStream << itsForceInternalAIS;
    theStream << itsForceRDI;
    theStream << itsRdiReiAutomatic;
    theStream << itsSfpRouteEnd;
    theStream << itsSfpRouteMiddle;
    theStream << itsMessagingEnabled;
    theStream << itsForceInternalCSFOPU;
    theStream << itsForceTlabAIS;
    theStream << itsAutoTlabAIS;
    theStream << itsAutoRateLockActive;
    theStream << itsUseSDHMode;
    theStream << itsAddEnable;
    theStream << itsDropEnable;
    theStream << aOduMappingMode;
    theStream << aForcedRsIndication;
    theStream << aForcedInternalRsIndication;
    theStream << aReplaceSig;
    theStream << itsLayerFailOnTIM;
    theStream << itsTIMMonitoringEnable;
    
    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_RsIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aSignalType;
    int aClockType;
    int aOduMappingMode;
    int aForcedRsIndication;
    int aForcedInternalRsIndication;
    int aReplaceSig;


    // Monitoring
    theStream >> itsRxTrace;
    theStream >> itsCVCount;
    theStream >> itsHighCVCount;
    theStream >> itsLOS;
    theStream >> itsLOF;
    theStream >> itsGENAIS;
    theStream >> itsOOF;
    theStream >> itsTIM;
    theStream >> itsTlabAISRx;
    theStream >> itsTlabAISTx;
    theStream >> itsInternalLOF;
    theStream >> itsInternalGENAIS;
    theStream >> itsInternalCSFOPU;
    theStream >> itsOrderedSetLocalFault;
    theStream >> itsOrderedSetRemoteFault;


    // Configuration
    theStream >> itsTxTrace;
    theStream >> itsExpectedTrace;
    theStream >> itsForceAIS;
    theStream >> itsTxTraceTransparent;
    theStream >> aSignalType;
    theStream >> aClockType;
    theStream >> itsForceInternalAIS;
    theStream >> itsForceRDI;
    theStream >> itsRdiReiAutomatic;
    theStream >> itsSfpRouteEnd;
    theStream >> itsSfpRouteMiddle;
    theStream >> itsMessagingEnabled;
    theStream >> itsForceInternalCSFOPU;
    theStream >> itsForceTlabAIS;
    theStream >> itsAutoTlabAIS;
    theStream >> itsAutoRateLockActive;
    theStream >> itsUseSDHMode;
    theStream >> itsAddEnable;
    theStream >> itsDropEnable;
    theStream >> aOduMappingMode;
    theStream >> aForcedRsIndication;
    theStream >> aForcedInternalRsIndication;
    theStream >> aReplaceSig;
    theStream >> itsLayerFailOnTIM;
    theStream >> itsTIMMonitoringEnable;
    
    // Update H/W
    itsSignalType = (CT_TEL_SignalType) aSignalType;
    itsClockType = (CT_TEL_ClkType) aClockType;
    itsOduMappingMode = (CT_TEL_PayloadType) aOduMappingMode;
    itsForcedRsIndication = (CT_RS_IndicationType) aForcedRsIndication;
    itsForcedInternalRsIndication = (CT_RS_IndicationType) aForcedInternalRsIndication;
    itsReplaceSig  = (CT_RS_ReplaceSigType) aReplaceSig;

    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_RsIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aSignalType = itsSignalType;
    int aClockType = itsClockType;
    int aOduMappingMode = itsOduMappingMode;
    int aForcedRsIndication = itsForcedRsIndication;
    int aForcedInternalRsIndication = itsForcedInternalRsIndication;
    int aReplaceSig = itsReplaceSig;

    // Monitoring
    theStream << FC_InsertVar(itsRxTrace);
    theStream << FC_InsertVar(itsCVCount);
    theStream << FC_InsertVar(itsHighCVCount);
    theStream << FC_InsertVar(itsLOS);
    theStream << FC_InsertVar(itsLOF);
    theStream << FC_InsertVar(itsGENAIS);
    theStream << FC_InsertVar(itsOOF);
    theStream << FC_InsertVar(itsTIM);
    theStream << FC_InsertVar(itsTlabAISRx);
    theStream << FC_InsertVar(itsTlabAISTx);
    theStream << FC_InsertVar(itsInternalLOF);
    theStream << FC_InsertVar(itsInternalGENAIS);
    theStream << FC_InsertVar(itsInternalCSFOPU);
    theStream << FC_InsertVar(itsOrderedSetLocalFault);
    theStream << FC_InsertVar(itsOrderedSetRemoteFault);


    // Configuration
    theStream << FC_InsertVar(itsTxTrace);
    theStream << FC_InsertVar(itsExpectedTrace);
    theStream << FC_InsertVar(itsForceAIS);
    theStream << FC_InsertVar(itsTxTraceTransparent);
    theStream << FC_InsertVar(aSignalType);
    theStream << FC_InsertVar(aClockType);
    theStream << FC_InsertVar(itsForceInternalAIS);
    theStream << FC_InsertVar(itsForceRDI);
    theStream << FC_InsertVar(itsRdiReiAutomatic);
    theStream << FC_InsertVar(itsSfpRouteEnd);
    theStream << FC_InsertVar(itsSfpRouteMiddle);
    theStream << FC_InsertVar(itsMessagingEnabled);
    theStream << FC_InsertVar(itsForceInternalCSFOPU);
    theStream << FC_InsertVar(itsForceTlabAIS);
    theStream << FC_InsertVar(itsAutoTlabAIS);
    theStream << FC_InsertVar(itsAutoRateLockActive);
    theStream << FC_InsertVar(itsUseSDHMode);
    theStream << FC_InsertVar(itsAddEnable);
    theStream << FC_InsertVar(itsDropEnable);
    theStream << FC_InsertVar(aOduMappingMode);
    theStream << FC_InsertVar(aForcedRsIndication);
    theStream << FC_InsertVar(aForcedInternalRsIndication);
    theStream << FC_InsertVar(aReplaceSig);
    theStream << FC_InsertVar(itsLayerFailOnTIM);
    theStream << FC_InsertVar(itsTIMMonitoringEnable);
    
    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_RsIf::ReadObject(istream & theStream)
{
    int aSignalType;
    int aClockType;
    int aOduMappingMode;
    int aForcedRsIndication;
    int aForcedInternalRsIndication;
    int aReplaceSig;

    // Monitoring
    theStream >> FC_ExtractVar(itsRxTrace);
    theStream >> FC_ExtractVar(itsCVCount);
    theStream >> FC_ExtractVar(itsHighCVCount);
    theStream >> FC_ExtractVar(itsLOS);
    theStream >> FC_ExtractVar(itsLOF);
    theStream >> FC_ExtractVar(itsGENAIS);
    theStream >> FC_ExtractVar(itsOOF);
    theStream >> FC_ExtractVar(itsTIM);
    theStream >> FC_ExtractVar(itsTlabAISRx);
    theStream >> FC_ExtractVar(itsTlabAISTx);
    theStream >> FC_ExtractVar(itsInternalLOF);
    theStream >> FC_ExtractVar(itsInternalGENAIS);
    theStream >> FC_ExtractVar(itsInternalCSFOPU);
    theStream >> FC_ExtractVar(itsOrderedSetLocalFault);
    theStream >> FC_ExtractVar(itsOrderedSetRemoteFault);


    // Configuration
    theStream >> FC_ExtractVar(itsTxTrace);
    theStream >> FC_ExtractVar(itsExpectedTrace);
    theStream >> FC_ExtractVar(itsForceAIS);
    theStream >> FC_ExtractVar(itsTxTraceTransparent);
    theStream >> FC_ExtractVar(aSignalType);
    theStream >> FC_ExtractVar(aClockType);
    theStream >> FC_ExtractVar(itsForceInternalAIS);
    theStream >> FC_ExtractVar(itsForceRDI);
    theStream >> FC_ExtractVar(itsRdiReiAutomatic);
    theStream >> FC_ExtractVar(itsSfpRouteEnd);
    theStream >> FC_ExtractVar(itsSfpRouteMiddle);
    theStream >> FC_ExtractVar(itsMessagingEnabled);
    theStream >> FC_ExtractVar(itsForceInternalCSFOPU);
    theStream >> FC_ExtractVar(itsForceTlabAIS);
    theStream >> FC_ExtractVar(itsAutoTlabAIS);
    theStream >> FC_ExtractVar(itsAutoRateLockActive);
    theStream >> FC_ExtractVar(itsUseSDHMode);
    theStream >> FC_ExtractVar(itsAddEnable);
    theStream >> FC_ExtractVar(itsDropEnable);
    theStream >> FC_ExtractVar(aOduMappingMode);
    theStream >> FC_ExtractVar(aForcedRsIndication);
    theStream >> FC_ExtractVar(aForcedInternalRsIndication);
    theStream >> FC_ExtractVar(aReplaceSig);
    theStream >> FC_ExtractVar(itsLayerFailOnTIM);
    theStream >> FC_ExtractVar(itsTIMMonitoringEnable);
    
    // Update H/W
    itsSignalType     = (CT_TEL_SignalType) aSignalType;
    itsClockType      = (CT_TEL_ClkType) aClockType;
    itsOduMappingMode = (CT_TEL_PayloadType) aOduMappingMode;
    itsForcedRsIndication = (CT_RS_IndicationType) aForcedRsIndication;
    itsForcedInternalRsIndication = (CT_RS_IndicationType) aForcedInternalRsIndication;
    itsReplaceSig = (CT_RS_ReplaceSigType)aReplaceSig;

    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  RS Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Transmitted trace     = " << itsTxTrace.GetTracePrintable(false)   << "\n";
    theStream << "      Expected trace        = " << itsExpectedTrace.GetTracePrintable(false)   << "\n";
    theStream << "      TIM Mon enable        = " << TEXT_ON_OFF(itsTIMMonitoringEnable)        << "\n";
    theStream << "      Layer Fail on TIM     = " << TEXT_ON_OFF(itsLayerFailOnTIM)             << "\n";
    theStream << "      Force AIS             = " << TEXT_ON_OFF(itsForceAIS)           << "\n";
    theStream << "      Force Indication      = " << DISPLAY_RS_INDICATION(itsForcedRsIndication) << "\n";
    theStream << "      Replacement Signal    = " << DISPLAY_RS_INDICATION(itsReplaceSig) << "\n";
    theStream << "      TX trace transparent  = " << TEXT_ON_OFF(itsTxTraceTransparent) << "\n";
    theStream << "      Signal Type           = " << DISPLAY_SIGNAL_TYPE(itsSignalType) << "\n";
    theStream << "      Clock Type            = " << DISPLAY_CLOCK_TYPE(itsClockType)     << "\n";
    theStream << "      SFP Routing           = " << itsSfpRouteEnd << ", " << itsSfpRouteMiddle    << "\n";
    theStream << "      Force Internal AIS    = " << TEXT_ON_OFF(itsForceInternalAIS)   << "\n";
    theStream << "      Force Internal Indi   = " << DISPLAY_RS_INDICATION(itsForcedInternalRsIndication) << "\n";
    theStream << "      Force RDI             = " << TEXT_ON_OFF(itsForceRDI)           << "\n";
    theStream << "      Automatic RDI/REI     = " << TEXT_ON_OFF(itsRdiReiAutomatic)    << "\n";
    theStream << "      Messaging Enabled     = " << TEXT_ON_OFF(itsMessagingEnabled)           << "\n";
    theStream << "      Force CSF-OPU         = " << TEXT_ON_OFF(itsForceInternalCSFOPU)       << "\n";
    theStream << "      Force TLAB AIS        = " << TEXT_ON_OFF(itsForceTlabAIS)       << "\n";
    theStream << "      Auto TLAB AIS         = " << TEXT_ON_OFF(itsAutoTlabAIS)        << "\n";
    theStream << "      Auto Rate Lock Active = " << TEXT_ON_OFF(itsAutoRateLockActive)        << "\n";
    theStream << "      Mode                  = " << (itsUseSDHMode?"SDH":"SONET")      << "\n";
    theStream << "      Add                   = " << (itsAddEnable?"Enable":"Disable")  << "\n";
    theStream << "      Drop                  = " << (itsDropEnable?"Enable":"Disable") << "\n";
    theStream << "      CBRMappingMode        = " << DISPLAY_PAYLOAD_TYPE(itsOduMappingMode) << "\n"; 
    theStream << "      InterPacketGap        = " << (int)itsInterPacketGap                  << "\n";
    theStream << "    MONITORING\n";
    theStream << "      B1 Count              = " << itsCVCount                         << "\n";
    theStream << "      High B1 Count         = " << itsHighCVCount                     << "\n";
    theStream << "      LOS Defect            = " << TEXT_DEFECT(itsLOS)                << "\n";
    theStream << "      LOF Defect            = " << TEXT_DEFECT(itsLOF)                << "\n";
    theStream << "      GENAIS Defect         = " << TEXT_DEFECT(itsGENAIS)                << "\n";
    theStream << "      OOF Defect            = " << TEXT_DEFECT(itsOOF)                << "\n";
    theStream << "      TIM Defect            = " << TEXT_DEFECT(itsTIM)                << "\n";
    theStream << "      Received trace        = " << itsRxTrace.GetTracePrintable(false)   << "" << endl;
    theStream << "      TLAB AIS Rx           = " << TEXT_DEFECT(itsTlabAISRx)          << "\n";
    theStream << "      TLAB AIS Tx           = " << TEXT_ON_OFF(itsTlabAISTx)          << "\n";    
    theStream << "      Internal LOF          = " << TEXT_DEFECT(itsInternalLOF)        << "\n";
    theStream << "      Internal GENAIS       = " << TEXT_DEFECT(itsInternalGENAIS)     << "\n";
    theStream << "      Internal CSF-OPU      = " << TEXT_DEFECT(itsInternalCSFOPU)     << "\n";
    theStream << "      OrderedSet Local Fault= " << TEXT_DEFECT(itsOrderedSetLocalFault)<< "\n";
    theStream << "      OrderedSet Remot Fault= "<< TEXT_DEFECT(itsOrderedSetRemoteFault)<< "\n";
    

    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::Set(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "txtrace") == 0)
    {
        CT_SDH16ByteTrace trace(argv[1]);
        SetTxTrace(trace);
    }
    else if (argc == 2 && strcmp(argv[0], "expectedtrace") == 0)
    {
        CT_SDH16ByteTrace trace(argv[1]);
        SetExpectedTrace(trace);
    }
    else if (argc == 2 && strcmp(argv[0], "forceais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            ForceAIS(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            ForceAIS(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "forceind") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_RS_INDICATION_NONE; i++)
        {
            if (strcmp(argv[1], DISPLAY_RS_INDICATION(i)) == 0)
            {
                ForceRsIndication((CT_RS_IndicationType)i);
                printUsage = false;
                break;
            }
        }
    }
    else if (argc == 2 && strcmp(argv[0], "replacesig") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_RS_INDICATION_NONE; i++)
        {
            if (strcmp(argv[1], DISPLAY_RS_INDICATION(i)) == 0)
            {
                SetReplaceSig((CT_RS_ReplaceSigType)i);
                printUsage = false;
                break;
            }
        }
    }
    else if (argc == 2 && strcmp(argv[0], "forceintind") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i <= CT_RS_INDICATION_NONE; i++)
        {
            if (strcmp(argv[1], DISPLAY_RS_INDICATION(i)) == 0)
            {
                ForceInternalRsIndication((CT_RS_IndicationType)i);
                printUsage = false;
                break;
            }
        }
    }
    else if (argc == 2 && strcmp(argv[0], "transparent") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetTxTraceTransparent(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetTxTraceTransparent(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "signaltype") == 0)
    {
        int i;
        printUsage = true;
        for (i = 0; i < CT_TEL_SIGNAL_END; i++)
        {
            if (strcmp(argv[1], DISPLAY_SIGNAL_TYPE(i)) == 0)
            {
                SetSignalType((CT_TEL_SignalType)i);
                printUsage = false;
                break;
            }
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
    else if ((argc == 4 || argc == 5) && strcmp(argv[0], "routeandsignaltype") == 0)
    {
        int i;
        printUsage = true;
        CT_TEL_ClkType aClockType = GetClockType();

        if (argc == 5) 
        {
            for (i = 0; i < CT_TEL_CLK_UNKNOWN; i++)
            {
                if (strcmp(argv[4], DISPLAY_CLOCK_TYPE(i)) == 0)
                {
                    aClockType = (CT_TEL_ClkType)i;
                    printUsage = false;
                    break;
                }
            }

        }  
        for (i = 0; i < CT_TEL_SIGNAL_END; i++)
        {
            if (strcmp(argv[3], DISPLAY_SIGNAL_TYPE(i)) == 0)
            {
                uint32 aEndDevice = strtoul(argv[1], NULL, 0);
                uint32 aMiddleDevice = strtoul(argv[2], NULL, 0);

                SetSfpRouteAndSignalType(aEndDevice, aMiddleDevice, (CT_TEL_SignalType)i, aClockType);
                printUsage = false;
                break;
            }
        }
    }
    else if (argc == 2 && strcmp(argv[0], "forceinternalais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceInternalAIS(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceInternalAIS(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "forcerdi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceRDI(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceRDI(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "autordirei") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetRdiReiAutomatic(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetRdiReiAutomatic(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "messaging") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetEnableMessaging(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetEnableMessaging(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "forcecsfopu") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetForceInternalCSFOPU(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceInternalCSFOPU(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "forcetlabais") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetForceTlabAIS(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceTlabAIS(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "autotlabais") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetAutoTlabAIS(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAutoTlabAIS(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "autoratelock") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetAutoRateLockActive(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAutoRateLockActive(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "mode") == 0)
    {
        if(strcmp(argv[1], "SDH") == 0)
        {
            SetTrueSDHMode(true);
        }
        else if (strcmp(argv[1], "SONET") == 0)
        {
            SetTrueSDHMode(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if  (argc == 2 && strcmp(argv[0], "add") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetAddonly(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
             SetAddonly(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if  (argc == 2 && strcmp(argv[0], "drop") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetDroponly(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
             SetDroponly(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "odumappingmode") == 0)
    {
        
        if( strcmp(argv[1], "sync") == 0)
        {
            SetCBRMappingMode(BIT_SYNC_CBR_MAPPING);
            printUsage = false;
        }
        else if( strcmp(argv[1],"async") == 0)
        {
            SetCBRMappingMode(ASYNC_CBR_MAPPING);
            printUsage = false;        
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
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    txtrace            <15 bytes trace>\n"
                   "    expectedtrace      <15 bytes trace>\n"
                   "    forceais           <on|off>\n"
                   "    forceind           <RS-AIS|RS-TLABAIS|RS-LF|RS-RF|RS-PN11AIS|UNKNOWN|NONE>\n"
                   "    replacesig         <RS-AIS|RS-TLABAIS|RS-LF|RS-RF|RS-PN11AIS|UNKNOWN|NONE>\n"
                   "    forceintind        <RS-AIS|RS-TLABAIS|RS-LF|RS-RF|RS-PN11AIS|UNKNOWN|NONE>\n"
                   "    transparent        <on|off>\n"
                   "    timmon             <on|off>\n"
                   "    layerfailontim     <on|off>\n";
        DisplayClockTypes();
        DisplaySignalTypes();
        DisplayRouteAndSignalTypes();

        fc_cout << "    forceinternalais   <on|off>\n"
                << "    forcerdi           <on|off>\n"
                << "    autordirei         <on|off>\n"
                << "    messaging          <on|off>\n"
                << "    forcecsfopu        <on|off>\n"
                << "    forcetlabais       <on|off>\n"
                << "    autotlabais        <on|off>\n"
                << "    autoratelock       <on|off>\n"
                << "    mode               <SDH|SONET>\n"
                << "    add                <on|off>\n"
                << "    drop               <on|off>\n" 
                << "    odumappingmode     <sync|async>\n" << endl;
 

    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "los") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLOS)) itsLOS++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLOS)) itsLOS++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "lof") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLOF)) itsLOF++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLOF)) itsLOF++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "genais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsGENAIS)) itsGENAIS++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsGENAIS)) itsGENAIS++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "oof") == 0)
    {
        // When OOF is activated for simulation purposes,
        // the event bit is set but the defect value stays low
        if (strcmp(argv[1], "on") == 0)
        {
            itsOOF += 2;
        }
        else if (strcmp(argv[1], "off") != 0)
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "tim") == 0)
    {
        // When TIM is activated for simulation purposes,
        // the event bit is set but the defect value stays low
        if (strcmp(argv[1], "on") == 0)
        {
            itsTIM++;
        }
        else if (strcmp(argv[1], "off") != 0)
        {
            printUsage = true;
        }
    }    
    else if (argc ==2 && strcmp(argv[0], "tais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsTlabAISRx)) itsTlabAISRx++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsTlabAISRx)) itsTlabAISRx++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "rxtrace") == 0)
    {
        itsRxTrace = CT_SDH16ByteTrace(argv[1]);
    }
    else if (argc == 2 && strcmp(argv[0], "b1count") == 0)
    {
        itsCVCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "incb1count") == 0)
    {
        itsCVCount += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "highb1count") == 0)
    {
        itsHighCVCount = strtoul(argv[1], NULL, 0);
    }
    else if(argc == 2 && strcmp(argv[0], "internallof") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsInternalLOF))
            {
                itsInternalLOF++;
            }
            else
            {
                itsInternalLOF+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsInternalLOF))
            {
                itsInternalLOF++;
            }
            else
            {
                itsInternalLOF+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "internalgenais") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsInternalGENAIS))
            {
                itsInternalGENAIS++;
            }
            else
            {
                itsInternalGENAIS+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsInternalGENAIS))
            {
                itsInternalGENAIS++;
            }
            else
            {
                itsInternalGENAIS+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strncmp(argv[0], "internalcs", 10) == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsInternalCSFOPU))
            {
                itsInternalCSFOPU++;
            }
            else
            {
                itsInternalCSFOPU+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsInternalCSFOPU))
            {
                itsInternalCSFOPU++;
            }
            else
            {
                itsInternalCSFOPU+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "orderedsetlocalfault") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsOrderedSetLocalFault))
            {
                itsOrderedSetLocalFault++;
            }
            else
            {
                itsOrderedSetLocalFault+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsOrderedSetLocalFault))
            {
                itsOrderedSetLocalFault++;
            }
            else
            {
                itsOrderedSetLocalFault+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "orderedsetremotefault") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsOrderedSetRemoteFault))
            {
                itsOrderedSetRemoteFault++;
            }
            else
            {
                itsOrderedSetRemoteFault+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsOrderedSetRemoteFault))
            {
                itsOrderedSetRemoteFault++;
            }
            else
            {
                itsOrderedSetRemoteFault+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    los                       <on|off>\n"
                   "    lof                       <on|off>\n"
                   "    genais                    <on|off>\n"
                   "    oof                       on\n"
                   "    tim                       <on|off>\n"
                   "    tais                      <on|off>\n"
                   "    rxtrace                   <15 bytes trace>\n"
                   "    b1count                   <count>\n"
                   "    incb1count                <increment>\n" 
                   "    highb1count               <count>\n"
                   "    internallof               <on|off>\n"
                   "    internalgenais            <on|off>\n"
                   "    internalcsfopu            <on|off>\n"
                   "    orderedsetlocalfault      <on|off>\n"
                   "    orderedsetremotefault     <on|off>\n"<< endl;

    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::DisplaySignalTypes()
{
    int sigType;

    fc_cout << "    signaltype        <";
    for(sigType = (int) CT_TEL_SIGNAL_E1; sigType < (int) CT_TEL_SIGNAL_END; sigType++)
    {
        fc_cout << DISPLAY_SIGNAL_TYPE((CT_TEL_SignalType)sigType) << "|";
    }
    fc_cout << ">\n";
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::DisplayClockTypes()
{
    int clkType;

    fc_cout << "    clocktype         <";
    for(clkType = (int) CT_TEL_CLK_G709; clkType < (int) CT_TEL_CLK_UNKNOWN; clkType++)
    {
        fc_cout << DISPLAY_CLOCK_TYPE((CT_TEL_ClkType)clkType) << "|";
    }
    fc_cout << ">\n";
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::DisplayRouteAndSignalTypes()
{
    int sigType;
    int clkType;

    fc_cout << "    routeandsignaltype <0-255>, <0-255>, <";
    for(sigType = (int) CT_TEL_SIGNAL_E1; sigType < (int) CT_TEL_SIGNAL_END; sigType++)
    {
        fc_cout << DISPLAY_SIGNAL_TYPE((CT_TEL_SignalType)sigType) << "|";
    }
    fc_cout << ">, <optional: ";
    for(clkType = (int) CT_TEL_CLK_G709; clkType <= (int) CT_TEL_CLK_UNKNOWN; clkType++)
    {
        fc_cout << DISPLAY_CLOCK_TYPE((CT_TEL_ClkType)clkType) << "|";
    }
    fc_cout << ">\n";
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetForceInternalCSFOPU(bool theEnable)
{
    itsForceInternalCSFOPU = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetForceTlabAIS(bool theEnable)
{
    itsForceTlabAIS = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetAutoTlabAIS(bool theEnable)
{
    itsAutoTlabAIS = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetAutoRateLockActive(bool theEnable)
{
    itsAutoRateLockActive = theEnable;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetForceInternalCSFOPU() const
{
    return itsForceInternalCSFOPU;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetForceTlabAIS() const
{
    return itsForceTlabAIS;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetAutoTlabAIS() const
{
    return itsAutoTlabAIS;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetAutoRateLockActive() const
{
    return itsAutoRateLockActive;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetTlabAISTx() const
{
    return itsTlabAISTx;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_RsIf::GetTlabAISRx()
{
    return itsTlabAISRx;
}
///////////////////////////////////////////////////////////////////////////////
uint32  TSPII_RsIf::GetInternalLOF()
{
    return itsInternalLOF;
}
///////////////////////////////////////////////////////////////////////////////
uint32  TSPII_RsIf::GetInternalGENAIS()
{
    return itsInternalGENAIS;
}
///////////////////////////////////////////////////////////////////////////////
uint32  TSPII_RsIf::GetInternalCSFOPU()
{
    return itsInternalCSFOPU;
}
///////////////////////////////////////////////////////////////////////////////
uint32  TSPII_RsIf::GetLocalFault()
{
    return itsOrderedSetLocalFault;
}
///////////////////////////////////////////////////////////////////////////////
uint32  TSPII_RsIf::GetRemoteFault()
{
    return itsOrderedSetRemoteFault;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetTrueSDHMode(bool useSDHMode)
{
    itsUseSDHMode = useSDHMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetTrueSDHMode() const
{
    return itsUseSDHMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetAddonly(bool theEnable)
{
     itsAddEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetAddonly() const
{
    return  itsAddEnable;
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetDroponly(bool theEnable)
{
    itsDropEnable = theEnable;
}
//////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetCBRMappingMode(CT_TEL_PayloadType theMappingMode)
{
    itsOduMappingMode = theMappingMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetDroponly() const
{
    return  itsDropEnable;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_PayloadType  TSPII_RsIf::GetCBRMappingMode() const
{
    return itsOduMappingMode;
}

///////////////////////////////////////////////////////////////////////////////
bool  TSPII_RsIf::IsSonetTerminated()
{
    return itsSonetTerminated;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetExpectedTrace(const CT_SDH16ByteTrace& theTrace)
{
    itsExpectedTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
const CT_SDH16ByteTrace & TSPII_RsIf::GetExpectedTrace() const
{
    return itsExpectedTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetTIMMonitoringEnable(bool theEnable)
{
    itsTIMMonitoringEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetTIMMonitoringEnable() const
{
    return itsTIMMonitoringEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::SetLayerFailOnTIM(bool theEnable)
{
    itsLayerFailOnTIM = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_RsIf::GetLayerFailOnTIM() const
{
    return itsLayerFailOnTIM;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_RsIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
