/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Martin Piotte, 2002/12/17
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_FecIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"

///////////////////////////////////////////////////////////////////////////////
TSPII_FecIf::TSPII_FecIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_FecIf::~TSPII_FecIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::RefreshGet()
{
    // Monitoring attributes
    itsErrorCountOnZeros           = GetBitErrorCountOnZeros();
    itsHighErrorCountOnZeros       = GetHighBitErrorCountOnZeros();
    itsErrorCountOnOnes            = GetBitErrorCountOnOnes();
    itsHighErrorCountOnOnes        = GetHighBitErrorCountOnOnes();
    itsCorrectedBytesCount         = GetFECCorrectedBytesCount();
    itsHighCorrectedBytesCount     = GetHighFECCorrectedBytesCount();
    itsNonCorrectableRSFrameCount  = GetNonCorrectableRSFrameCount();
    itsHighNonCorrectableRSFrameCount = GetHighNonCorrectableRSFrameCount();
    itsBip8Count                   = GetBip8Count();
    itsHighBip8Count               = GetHighBip8Count();
    itsBeiCount                    = GetBeiCount();
    itsHighBeiCount                = GetHighBeiCount();
    itsLOF                         = GetLOF();
    itsLOMF                        = GetLOMF();
    itsFECM                        = GetFECM();
    itsAIS                         = GetAIS();
    itsBDI                         = GetBDI();
    itsBerSf                       = GetBerSf();
    itsBerSd                       = GetBerSd();
    itsMateDefect                  = GetMateDefect();
    itsRxTrace                     = GetRxTrace();
    itsBER                         = GetBER();
    itsIAE                         = GetIAE();
    itsDispCompState               = GetDispCompState();
    itsTIM                         = GetTIM();
    
    // Configuration attributes
    itsFECEnabled                  = GetCorrectionEnable();
    itsSuperFecEnabled             = GetSuperFecEnable();
    itsForcedAIS                   = GetForcedAIS();
    itsForcedBDI                   = GetForcedBDI();
    itsErrorGeneration             = GetErrorGeneration();
    itsBerSfThreshold              = GetBerSfThreshold();
    itsBerSdThreshold              = GetBerSdThreshold();
    itsTxTrace                     = GetTxTrace();
    itsExpectedTrace               = GetExpectedTrace();
    itsAllowBDIBEI                 = GetBDIAndBEIAllowed();
    itsBurstySdBerIntervals        = GetBurstyBerSdIntervals();
    itsBurstySdBerThreshold        = GetBurstyBerSdThreshold();
    itsFECType                     = GetFECType();
    itsSendDefectToMate            = GetSendDefectToMate();
    itsTIMCriteraMode              = GetTimCriteria();
    itsLayerFailOnTIM              = GetLayerFailOnTIM();
    itsTIMMonitoringEnable         = GetTIMMonitoringEnable();
    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::RefreshSet()
{
    // Configuration attributes
    SetCorrectionEnable(itsFECEnabled);
    SetSuperFecEnable(itsSuperFecEnabled);
    ForceAIS(itsForcedAIS);
    ForceBDI(itsForcedBDI);
    SetErrorGeneration(itsErrorGeneration);
    SetBerSfThreshold(itsBerSfThreshold);
    SetBerSdThreshold(itsBerSdThreshold);
    SetTxTrace(itsTxTrace);
    SetExpectedTrace(itsExpectedTrace);
    SetBDIAndBEIAllowed(itsAllowBDIBEI);
    SetBurstyBerSdThreshold(itsBurstySdBerIntervals, itsBurstySdBerThreshold);
    SetFECType(itsFECType);
    SetSendDefectToMate(itsSendDefectToMate);
    SetTimCriteria(itsTIMCriteraMode);
    SetLayerFailOnTIM(itsLayerFailOnTIM);
    SetTIMMonitoringEnable(itsTIMMonitoringEnable);    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsErrorCountOnZeros           = 0;
    itsHighErrorCountOnZeros       = 0;
    itsErrorCountOnOnes            = 0;
    itsHighErrorCountOnOnes        = 0;
    itsCorrectedBytesCount         = 0;
    itsHighCorrectedBytesCount     = 0;
    itsNonCorrectableRSFrameCount  = 0;
    itsHighNonCorrectableRSFrameCount = 0;
    itsBip8Count                   = 0;
    itsHighBip8Count               = 0;
    itsBeiCount                    = 0;
    itsHighBeiCount                = 0;
    itsLOF                         = 0;
    itsLOMF                        = 0;
    itsFECM                        = 0;
    itsAIS                         = 0;
    itsBDI                         = 0;
    itsBerSf                       = 0;
    itsBerSd                       = 0;
    itsMateDefect                  = 0;
    itsTIM                         = 0;
    itsRxTrace                     = CT_G709Trace();
    itsBER                         = CT_Float32();
    itsIAE                         = 0;
    itsDispCompState               = CT_TEL_DISP_COMP_UNKNOWN;

    // Configuration attributes
    itsFECEnabled                 = false;
    itsSuperFecEnabled            = false;
    itsForcedAIS                  = false;
    itsForcedBDI                  = false;
    itsErrorGeneration            = false;
    itsBerSfThreshold             = CT_TEL_NO_BER;
    itsBerSdThreshold             = CT_TEL_NO_BER;
    itsTxTrace                    = CT_G709Trace();
    itsExpectedTrace              = CT_G709Trace();
    itsAllowBDIBEI                = true;
    itsBurstySdBerIntervals       = 0;
    itsBurstySdBerThreshold       = 0;
    // Keep the default Super, since that was used on the OSM40
    itsFECType                    = CT_TEL_FEC_TYPE_SUPER;
    itsSendDefectToMate           = false;
    itsTIMCriteraMode             = CT_TEL_TIM_SAPI_DAPI;
    itsLayerFailOnTIM             = false;
    itsTIMMonitoringEnable        = false;  
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetFECCorrectedBytesCount()
{
    return itsCorrectedBytesCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBitErrorCountOnOnes()
{
    return itsErrorCountOnOnes;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBitErrorCountOnZeros()
{
    return itsErrorCountOnZeros;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetNonCorrectableRSFrameCount()
{
    return itsNonCorrectableRSFrameCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBip8Count()
{
    return itsBip8Count;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBeiCount()
{
    return itsBeiCount;
}


///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetHighFECCorrectedBytesCount()
{
    return itsHighCorrectedBytesCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetHighBitErrorCountOnOnes()
{
    return itsHighErrorCountOnOnes;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetHighBitErrorCountOnZeros()
{
    return itsHighErrorCountOnZeros;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetHighNonCorrectableRSFrameCount()
{
    return itsHighNonCorrectableRSFrameCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetHighBip8Count()
{
    return itsHighBip8Count;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetHighBeiCount()
{
    return itsHighBeiCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetLOF()
{
    return itsLOF;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetLOMF()
{
    return itsLOMF;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetAIS()
{
    return itsAIS;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetFECM()
{
    return itsFECM;
}


///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBDI()
{
    return itsBDI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBerSf()
{
    return itsBerSf;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBerSd()
{
    return itsBerSd;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetTIM()
{
    return itsTIM;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetMateDefect()
{
    return itsMateDefect;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_FecIf::GetRxTrace()
{
    return itsRxTrace;
}

///////////////////////////////////////////////////////////////////////////////
const CT_Float32 & TSPII_FecIf::GetBER()
{
    return itsBER;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetIAE()
{
    return itsIAE;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetCorrectionEnable(bool theEnable)
{
    itsFECEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetTxTrace(const CT_G709Trace & theTrace)
{
    itsTxTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetExpectedTrace(const CT_G709Trace & theTrace)
{
    itsExpectedTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetTimCriteria(CT_TEL_TimCriteriaMode theTimCriteria)
{
    itsTIMCriteraMode = theTimCriteria;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::ForceAIS(bool theEnable)
{
    itsForcedAIS = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::ForceBDI(bool theEnable)
{
    itsForcedBDI = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetErrorGeneration(bool theEnable)
{
    itsErrorGeneration = theEnable;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetSuperFecEnable(bool theEnable)
{
    itsSuperFecEnabled = theEnable;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetBerSfThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSfThreshold = theThreshold;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetBerSdThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSdThreshold = theThreshold;
}

/*********************************BEGIN**********************************/
/**                                                                    **/
/**  Function:  SetBDIAndBEIAllowed                                    **/
/**                                                                    **/
/**  Description:                                                      **/
/**      Enable or disable BDI and BEI insertion                       **/
/**      When BDI/BEI is allowed BDI can be forced or automatically    **/
/**      generated, and BEI can be automatically generated.            **/
/**      When BDI/BEI is not allowed then BDI cannot be forced, and    **/
/**      neither BEI nor BDI will be inserted automatically.           **/
/**                                                                    **/
/**  Inputs:                                                           **/
/**      allowed - true to allow BDI and BEI insertion, false to       **/
/**                prevent it                                          **/
/**                                                                    **/
/**  Outputs:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**  Returns:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**********************************END***********************************/
void TSPII_FecIf::SetBDIAndBEIAllowed(bool allowed)
{
    itsAllowBDIBEI = allowed;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetBurstyBerSdThreshold(uint intervals, uint32 threshold)
{
  itsBurstySdBerIntervals = intervals;
  itsBurstySdBerThreshold = threshold;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetFECType(CT_TEL_FecType theFECType)
{
    itsFECType = theFECType;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetSendDefectToMate(bool theEnable)
{
    itsSendDefectToMate = theEnable;
}



//////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetSuperFecEnable() const
{
    return itsSuperFecEnabled;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetCorrectionEnable() const
{
    return itsFECEnabled;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_FecIf::GetTxTrace() const
{
    return itsTxTrace;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_FecIf::GetExpectedTrace() const
{
    return itsExpectedTrace;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_TimCriteriaMode TSPII_FecIf::GetTimCriteria() const
{
    return itsTIMCriteraMode;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetForcedAIS() const
{
    return itsForcedAIS;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetForcedBDI() const
{
    return itsForcedBDI;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetErrorGeneration() const
{
    return itsErrorGeneration;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_FecIf::GetBerSfThreshold() const
{
    return itsBerSfThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_FecIf::GetBerSdThreshold() const
{
    return itsBerSdThreshold;
}

/*********************************BEGIN**********************************/
/**                                                                    **/
/**  Function:  GetBDIAndBEIAllowed                                    **/
/**                                                                    **/
/**  Description:                                                      **/
/**      Determine if BDI and/or BEI can be inserted                   **/
/**      When BDI/BEI is allowed BDI can be forced or automatically    **/
/**      generated, and BEI can be automatically generated.            **/
/**      When BDI/BEI is not allowed then BDI cannot be forced, and    **/
/**      neither BEI nor BDI will be inserted automatically.           **/
/**                                                                    **/
/**  Inputs:                                                           **/
/**      None.                                                         **/
/**                                                                    **/
/**  Outputs:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**  Returns:                                                          **/
/**      true if BDI and BEI can be inserted, false if they cannot     **/
/**                                                                    **/
/**********************************END***********************************/
bool TSPII_FecIf::GetBDIAndBEIAllowed() const
{
    return itsAllowBDIBEI;
}

///////////////////////////////////////////////////////////////////////////////
uint TSPII_FecIf::GetBurstyBerSdIntervals() const
{
  return itsBurstySdBerIntervals;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_FecIf::GetBurstyBerSdThreshold() const
{
  return itsBurstySdBerThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_FecType TSPII_FecIf::GetFECType() const
{
    return itsFECType;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_DispCompState TSPII_FecIf::GetDispCompState()
{
    return itsDispCompState;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetSendDefectToMate() const
{
    return itsSendDefectToMate;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetTIMMonitoringEnable(bool theEnable)
{
    itsTIMMonitoringEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetTIMMonitoringEnable() const
{
    return itsTIMMonitoringEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::SetLayerFailOnTIM(bool theEnable)
{
    itsLayerFailOnTIM = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::GetLayerFailOnTIM() const
{
    return itsLayerFailOnTIM;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_FecIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aBerSfThreshold = itsBerSfThreshold;
    int aBerSdThreshold = itsBerSdThreshold;
    int aFECType = itsFECType;
    int aDispCompState = itsDispCompState;
    int aTIMCriteraMode = itsTIMCriteraMode;

    // Monitoring
    theStream << itsErrorCountOnZeros;
    theStream << itsErrorCountOnOnes;
    theStream << itsCorrectedBytesCount;
    theStream << itsNonCorrectableRSFrameCount;
    theStream << itsBip8Count;
    theStream << itsBeiCount;
    theStream << itsHighErrorCountOnZeros;
    theStream << itsHighErrorCountOnOnes;
    theStream << itsHighCorrectedBytesCount;
    theStream << itsHighNonCorrectableRSFrameCount;
    theStream << itsHighBip8Count;
    theStream << itsHighBeiCount;
    theStream << itsLOF;
    theStream << itsLOMF;
    theStream << itsFECM;
    theStream << itsAIS;
    theStream << itsBDI;
    theStream << itsBerSf;
    theStream << itsBerSd;
    theStream << itsIAE;
    theStream << itsRxTrace;
    theStream << itsBER;
    theStream << aDispCompState;
    theStream << itsMateDefect;
    theStream << itsTIM;
    
    // Configuration
    theStream << itsFECEnabled;
    theStream << itsSuperFecEnabled;
    theStream << itsForcedAIS;
    theStream << itsForcedBDI;
    theStream << itsErrorGeneration;
    theStream << aBerSfThreshold;
    theStream << aBerSdThreshold;
    theStream << itsTxTrace;
    theStream << itsExpectedTrace;
    theStream << itsAllowBDIBEI;
    theStream << itsBurstySdBerIntervals;
    theStream << itsBurstySdBerThreshold;
    theStream << aFECType;
    theStream << itsSendDefectToMate;
    theStream << aTIMCriteraMode;
    theStream << itsLayerFailOnTIM;
    theStream << itsTIMMonitoringEnable;
    
    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_FecIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aBerSfThreshold;
    int aBerSdThreshold;
    int aFECType;
    int aDispCompState;
    int aTIMCriteraMode;
    
    // Monitoring
    theStream >> itsErrorCountOnZeros;
    theStream >> itsErrorCountOnOnes;
    theStream >> itsCorrectedBytesCount;
    theStream >> itsNonCorrectableRSFrameCount;
    theStream >> itsBip8Count;
    theStream >> itsBeiCount;
    theStream >> itsHighErrorCountOnZeros;
    theStream >> itsHighErrorCountOnOnes;
    theStream >> itsHighCorrectedBytesCount;
    theStream >> itsHighNonCorrectableRSFrameCount;
    theStream >> itsHighBip8Count;
    theStream >> itsHighBeiCount;
    theStream >> itsLOF;
    theStream >> itsLOMF;
    theStream >> itsFECM;
    theStream >> itsAIS;
    theStream >> itsBDI;
    theStream >> itsBerSf;
    theStream >> itsBerSd;
    theStream >> itsIAE;
    theStream >> itsRxTrace;
    theStream >> itsBER;
    theStream >> aDispCompState;
    theStream >> itsMateDefect;
    theStream >> itsTIM;

    // Configuration
    theStream >> itsFECEnabled;
    theStream >> itsSuperFecEnabled;
    theStream >> itsForcedAIS;
    theStream >> itsForcedBDI;
    theStream >> itsErrorGeneration;
    theStream >> aBerSfThreshold;
    theStream >> aBerSdThreshold;
    theStream >> itsTxTrace;
    theStream >> itsExpectedTrace;
    theStream >> itsAllowBDIBEI;
    theStream >> itsBurstySdBerIntervals;
    theStream >> itsBurstySdBerThreshold;
    theStream >> aFECType;
    theStream >> itsSendDefectToMate;
    theStream >> aTIMCriteraMode;
    theStream >> itsLayerFailOnTIM;
    theStream >> itsTIMMonitoringEnable;
    
    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsFECType = (CT_TEL_FecType) aFECType;
    itsDispCompState = (CT_TEL_DispCompState) aDispCompState;
    itsTIMCriteraMode = (CT_TEL_TimCriteriaMode) aTIMCriteraMode;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_FecIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aBerSfThreshold = itsBerSfThreshold;
    int aBerSdThreshold = itsBerSdThreshold;
    int aFECType = itsFECType;
    int aDispCompState = itsDispCompState;
    int aTIMCriteraMode = itsTIMCriteraMode;

    // Monitoring
    theStream << FC_InsertVar(itsErrorCountOnZeros);
    theStream << FC_InsertVar(itsErrorCountOnOnes);
    theStream << FC_InsertVar(itsCorrectedBytesCount);
    theStream << FC_InsertVar(itsNonCorrectableRSFrameCount);
    theStream << FC_InsertVar(itsBip8Count);
    theStream << FC_InsertVar(itsBeiCount);
    theStream << FC_InsertVar(itsHighErrorCountOnZeros);
    theStream << FC_InsertVar(itsHighErrorCountOnOnes);
    theStream << FC_InsertVar(itsHighCorrectedBytesCount);
    theStream << FC_InsertVar(itsHighNonCorrectableRSFrameCount);
    theStream << FC_InsertVar(itsHighBip8Count);
    theStream << FC_InsertVar(itsHighBeiCount);
    theStream << FC_InsertVar(itsLOF);
    theStream << FC_InsertVar(itsLOMF);
    theStream << FC_InsertVar(itsFECM);
    theStream << FC_InsertVar(itsAIS);
    theStream << FC_InsertVar(itsBDI);
    theStream << FC_InsertVar(itsBerSf);
    theStream << FC_InsertVar(itsBerSd);
    theStream << FC_InsertVar(itsIAE);
    theStream << FC_InsertVar(itsTIM);
    theStream << itsRxTrace;
    theStream << itsBER;
    theStream << FC_InsertVar(aDispCompState);
    theStream << FC_InsertVar(itsMateDefect);

    // Configuration
    theStream << FC_InsertVar(itsFECEnabled);
    theStream << FC_InsertVar(itsSuperFecEnabled);
    theStream << FC_InsertVar(itsForcedAIS);
    theStream << FC_InsertVar(itsForcedBDI);
    theStream << FC_InsertVar(itsErrorGeneration);
    theStream << FC_InsertVar(aBerSfThreshold);
    theStream << FC_InsertVar(aBerSdThreshold);
    theStream << itsTxTrace;
    theStream << itsExpectedTrace;
    theStream << FC_InsertVar(itsAllowBDIBEI);
    theStream << FC_InsertVar(itsBurstySdBerIntervals);
    theStream << FC_InsertVar(itsBurstySdBerThreshold);
    theStream << FC_InsertVar(aFECType);
    theStream << FC_InsertVar(itsSendDefectToMate);
    theStream << FC_InsertVar(aTIMCriteraMode);
    theStream << FC_InsertVar(itsLayerFailOnTIM);
    theStream << FC_InsertVar(itsTIMMonitoringEnable);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_FecIf::ReadObject(istream & theStream)
{
    int aBerSfThreshold;
    int aBerSdThreshold;
    int aFECType;
    int aDispCompState;
    int aTIMCriteraMode;

    // Monitoring
    theStream >> FC_ExtractVar(itsErrorCountOnZeros);
    theStream >> FC_ExtractVar(itsErrorCountOnOnes);
    theStream >> FC_ExtractVar(itsCorrectedBytesCount);
    theStream >> FC_ExtractVar(itsNonCorrectableRSFrameCount);
    theStream >> FC_ExtractVar(itsBip8Count);
    theStream >> FC_ExtractVar(itsBeiCount);
    theStream >> FC_ExtractVar(itsHighErrorCountOnZeros);
    theStream >> FC_ExtractVar(itsHighErrorCountOnOnes);
    theStream >> FC_ExtractVar(itsHighCorrectedBytesCount);
    theStream >> FC_ExtractVar(itsHighNonCorrectableRSFrameCount);
    theStream >> FC_ExtractVar(itsHighBip8Count);
    theStream >> FC_ExtractVar(itsHighBeiCount);
    theStream >> FC_ExtractVar(itsLOF);
    theStream >> FC_ExtractVar(itsLOMF);
    theStream >> FC_ExtractVar(itsFECM);
    theStream >> FC_ExtractVar(itsAIS);
    theStream >> FC_ExtractVar(itsBDI);
    theStream >> FC_ExtractVar(itsBerSf);
    theStream >> FC_ExtractVar(itsBerSd);
    theStream >> FC_ExtractVar(itsIAE);
    theStream >> FC_ExtractVar(itsTIM);
    theStream >> itsRxTrace;
    theStream >> itsBER;
    theStream >> FC_ExtractVar(aDispCompState);
    theStream >> FC_ExtractVar(itsMateDefect);

    // Configuration
    theStream >> FC_ExtractVar(itsFECEnabled);
    theStream >> FC_ExtractVar(itsSuperFecEnabled);
    theStream >> FC_ExtractVar(itsForcedAIS);
    theStream >> FC_ExtractVar(itsForcedBDI);
    theStream >> FC_ExtractVar(itsErrorGeneration);
    theStream >> FC_ExtractVar(aBerSfThreshold);
    theStream >> FC_ExtractVar(aBerSdThreshold);
    theStream >> itsTxTrace;
    theStream >> itsExpectedTrace;
    theStream >> FC_ExtractVar(itsAllowBDIBEI);
    theStream >> FC_ExtractVar(itsBurstySdBerIntervals);
    theStream >> FC_ExtractVar(itsBurstySdBerThreshold);
    theStream >> FC_ExtractVar(aFECType);
    theStream >> FC_ExtractVar(itsSendDefectToMate);
    theStream >> FC_ExtractVar(aTIMCriteraMode);
    theStream >> FC_ExtractVar(itsLayerFailOnTIM);
    theStream >> FC_ExtractVar(itsTIMMonitoringEnable);
    
    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsFECType = (CT_TEL_FecType) aFECType;
    itsDispCompState = (CT_TEL_DispCompState) aDispCompState;
    itsTIMCriteraMode = (CT_TEL_TimCriteriaMode) itsTIMCriteraMode;
    
    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  Forward Error Correction (OTU) Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Error correction      = " << TEXT_ON_OFF(itsFECEnabled)                 << "\n";
    theStream << "      FEC Type              = " << DISPLAY_FEC_TYPE(GetFECType())        << "\n";
    theStream << "      Super FEC             = " << TEXT_ON_OFF(itsSuperFecEnabled)            << "\n";
    theStream << "      Forced AIS            = " << TEXT_ON_OFF(itsForcedAIS)                  << "\n";
    theStream << "      Forced BDI            = " << TEXT_ON_OFF(itsForcedBDI)                  << "\n";
    theStream << "      BDI & BEI allowed     = " << TEXT_ON_OFF(itsAllowBDIBEI)                << "\n";
    theStream << "      Error Generation      = " << TEXT_ON_OFF(itsErrorGeneration)            << "\n";
    theStream << "      BerSfThreshold        = " << DISPLAY_BER(itsBerSfThreshold)             << "\n";
    theStream << "      BerSdThreshold        = " << DISPLAY_BER(itsBerSdThreshold)             << "\n";
    theStream << "      Bursty BER Threshold  = DEGM(" << itsBurstySdBerIntervals << ") DEGTHR(" << itsBurstySdBerThreshold << ")\n";
    theStream << "      Send Defect To Mate   = " << TEXT_ON_OFF(itsSendDefectToMate)                  << "\n";
    theStream << "      TIM CRITERA           = " << DISPLAY_TIMCRITERIAMODE(itsTIMCriteraMode)        << "\n";
    theStream << "      Fec TX Trace  = Sapi  = " << itsTxTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                      Dapi  = " << itsTxTrace.GetDapiPrintable(false)         << "\n";
    theStream << "                   Operator = " << itsTxTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                   Trace ID = " << itsTxTrace.GetTraceID()                    << "\n";
    theStream << "                       CRC7 = " << (uint32)itsTxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsTxTrace.IsValid())          << "\n";
    theStream << "      Fec EXP Trace = Sapi  = " << itsExpectedTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                      Dapi  = " << itsExpectedTrace.GetDapiPrintable(false)         << "\n";
    theStream << "                   Operator = " << itsExpectedTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                   Trace ID = " << itsExpectedTrace.GetTraceID()                    << "\n";
    theStream << "                       CRC7 = " << (uint32)itsExpectedTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsExpectedTrace.IsValid())          << "\n";
    theStream << "      Fec TIM Mon enable    = " << TEXT_ON_OFF(itsTIMMonitoringEnable)        << "\n";
    theStream << "      Fec Layer Fail on TIM = " << TEXT_ON_OFF(itsLayerFailOnTIM)             << "\n";
    theStream << "    MONITORING\n";
    theStream << "      FEC Corrected Bytes   = " << itsCorrectedBytesCount                     << "\n";
    theStream << "      High FEC Correct Bytes= " << itsHighCorrectedBytesCount                     << "\n";
    theStream << "      Bit Error on Ones     = " << itsErrorCountOnOnes                        << "\n";
    theStream << "      High Bit Err on Ones  = " << itsHighErrorCountOnOnes                        << "\n";
    theStream << "      Bit Error on Zeros    = " << itsErrorCountOnZeros                       << "\n";
    theStream << "      High Bit Err on Zeros = " << itsHighErrorCountOnZeros                       << "\n";
    theStream << "      Non Correctable Frame = " << itsNonCorrectableRSFrameCount              << "\n";
    theStream << "      High Non Correct Frame= " << itsHighNonCorrectableRSFrameCount              << "\n";
    theStream << "      BIP8                  = " << itsBip8Count                               << "\n";
    theStream << "      High BIP8             = " << itsHighBip8Count                               << "\n";
    theStream << "      BEI                   = " << itsBeiCount                                << "\n";
    theStream << "      High BEI              = " << itsHighBeiCount                                << "\n";
    theStream << "      Dispersion Comp State = " << DISPLAY_DISP_COMP_STATE(itsDispCompState)  << "\n";
    theStream << "      FEC LOF defect        = " << TEXT_DEFECT(itsLOF)                        << "\n";
    theStream << "      FEC LOMF defect       = " << TEXT_DEFECT(itsLOMF)                        << "\n";
    theStream << "      FEC FECM defect       = " << TEXT_DEFECT(itsFECM)                       << "\n";
    theStream << "      FEC AIS defect        = " << TEXT_DEFECT(itsAIS)                        << "\n";
    theStream << "      FEC BDI defect        = " << TEXT_DEFECT(itsBDI)                        << "\n";
    theStream << "      FEC BerSf defect      = " << TEXT_DEFECT(itsBerSf)                      << "\n";
    theStream << "      FEC BerSd defect      = " << TEXT_DEFECT(itsBerSd)                      << "\n";
    theStream << "      FEC IAE defect        = " << TEXT_DEFECT(itsIAE)                        << "\n";
    theStream << "      FEC TIM defect        = " << TEXT_DEFECT(itsTIM)                        << "\n";
    theStream << "      FEC Mate defect       = " << TEXT_DEFECT(itsMateDefect)                        << "\n";
    theStream << "      FEC BER               = " << itsBER.DisplayFloat() << "  Man[" << dec << itsBER.GetMantissa()     << "] Exp[" << static_cast<int>(itsBER.GetExponent())      << "] Val[" << dec << itsBER.GetValue()      << "] \n";
    theStream << "      FEC RX Trace  = Sapi  = " << itsRxTrace.GetSapiPrintable(false)         << "\n";
    theStream << "                      Dapi  = " << itsRxTrace.GetDapiPrintable(false)         << "\n";
    theStream << "                   Operator = " << itsRxTrace.GetOperatorSpecificPrintable(false)  << "\n";
    theStream << "                   Trace ID = " << itsRxTrace.GetTraceID()                    << "\n";
    theStream << "                       CRC7 = " << (uint32)itsRxTrace.GetCRC7()               << "\n";
    theStream << "                   Is Valid = " << TEXT_ON_OFF(itsRxTrace.IsValid())          << "\n";
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::Set(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "fecenable") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetCorrectionEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetCorrectionEnable(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "sfecenable") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetSuperFecEnable(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetSuperFecEnable(false);
        }
        else
        {
            printUsage = true;
        }
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
    else if(argc == 2 && strcmp(argv[0], "allowbdibei") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            SetBDIAndBEIAllowed(true);
        }
        else if(strcmp(argv[1], "off") == 0)
        {
            SetBDIAndBEIAllowed(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "errorgen") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetErrorGeneration(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetErrorGeneration(false);
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
    else if (argc == 5 && strcmp(argv[0], "txtrace") == 0)
    {
        CT_G709Trace trace(argv[1], argv[2], argv[3], atoi(argv[4]));
        SetTxTrace(trace);
    }
    else if (argc == 5 && strcmp(argv[0], "expectedtrace") == 0)
    {
        CT_G709Trace trace(argv[1], argv[2], argv[3], atoi(argv[4]));
        SetExpectedTrace(trace);
    }    
    else if((argc == 3) && (strcmp(argv[0], "berburst") == 0))
    {
      SetBurstyBerSdThreshold(strtoul(argv[1], NULL, 0), strtoul(argv[2], NULL, 0));
      printUsage = false;
    }
    else if (argc == 2 && strcmp(argv[0], "fectype") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_FEC_TYPE_LAST; i++) if (strcmp(argv[1], DISPLAY_FEC_TYPE(i)) == 0)
        {
            SetFECType((CT_TEL_FecType)i);
            printUsage = false;
            break;
        }
    }
    else if (argc == 2 && strncmp(argv[0], "senddef", 7) == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetSendDefectToMate(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetSendDefectToMate(false);
        }
        else
        {
            printUsage = true;
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
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    fecenable        <on|off>\n"
                   "    sfecenable       <on|off>\n"
                   "    forceais         <on|off>\n"
                   "    forcebdi         <on|off>\n"
                   "    allowbdibei      <on|off>\n"
                   "    errorgen         <on|off>\n"
                   "    timcritera       <sapi|dapi|sapi_dapi|oper|sapi_oper|dapi_oper|sapi_dapi_oper|unknown>\n"
                   "    bersfthres       <Error free|10-12|10-11| ... |10-3>\n"
                   "    bersdthres       <Error free|10-12|10-11| ... |10-3>\n"
                   "    berburst         <intervals(DEGM)> <threshold(DEGTHR)>\n"
                   "    fectype          <Regular | Super | Super-Legacy | SuperI7 | SuperI9 | SoftDecision | None | Unknown)>\n"
                   "    senddefecttomate <on|off>\n"
                   "    timmon           <on|off>\n"
                   "    layerfailontim   <on|off>\n"
                   "    txtrace          <sapi(15 char max)> <dapi(15 char max)> <trace(28 char max)> <trace ID>\n"
                   "    expectedtrace    <sapi(15 char max)> <dapi(15 char max)> <trace(28 char max)> <trace ID>" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_FecIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;
    if (argc == 2 && strcmp(argv[0], "correctbyte") == 0)
    {
        itsCorrectedBytesCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "inccorrectbyte") == 0)
    {
        itsCorrectedBytesCount += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "errones") == 0)
    {
        itsErrorCountOnOnes = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "errzeros") == 0)
    {
        itsErrorCountOnZeros = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "uncorframe") == 0)
    {
        itsNonCorrectableRSFrameCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "incuncorframe") == 0)
    {
        itsNonCorrectableRSFrameCount += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "bip8") == 0)
    {
        itsBip8Count = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "incbip8") == 0)
    {
        itsBip8Count += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "bei") == 0)
    {
        itsBeiCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "incbei") == 0)
    {
        itsBeiCount += strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "highcorrectbyte") == 0)
    {
        itsHighCorrectedBytesCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "higherrones") == 0)
    {
        itsHighErrorCountOnOnes = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "higherrzeros") == 0)
    {
        itsHighErrorCountOnZeros = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "highuncorframe") == 0)
    {
        itsHighNonCorrectableRSFrameCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "highbip8") == 0)
    {
        itsHighBip8Count = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "highbei") == 0)
    {
        itsHighBeiCount = strtoul(argv[1], NULL, 0);
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
    else if (argc == 2 && strcmp(argv[0], "lomf") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLOMF)) itsLOMF++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLOMF)) itsLOMF++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "iae") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsIAE)) itsIAE++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsIAE)) itsIAE++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "fecm") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsFECM)) itsFECM++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsFECM)) itsFECM++;
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
    else if (argc == 5 && strcmp(argv[0], "rxtrace") == 0)
    {
        itsRxTrace = CT_G709Trace(argv[1], argv[2], argv[3], atoi(argv[4]));
    }
    else if (argc == 2 && strcmp(argv[0], "BER") == 0)
    {
        double aBER= atof(argv[1]);
        itsBER.SetFloat(aBER);
    }
    else if (argc == 2 && strcmp(argv[0], "dcstate") == 0)
    {
        if (strcmp(argv[1], "tdcinit") == 0)
        {
            itsDispCompState = CT_TEL_DISP_COMP_TDC_INIT;
        }
        else if (strcmp(argv[1], "dliinit") == 0)
        {
            itsDispCompState = CT_TEL_DISP_COMP_DLI_INIT;
        }
        else if (strcmp(argv[1], "demuxinit") == 0)
        {
            itsDispCompState = CT_TEL_DISP_COMP_DEMUX_INIT;
        }
        else if (strcmp(argv[1], "optimizing") == 0)
        {
            itsDispCompState = CT_TEL_DISP_COMP_OPTIMIZING;
        }
        else if (strcmp(argv[1], "unknown") == 0)
        {
            itsDispCompState = CT_TEL_DISP_COMP_UNKNOWN;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "matedefect") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsMateDefect)) itsMateDefect++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsMateDefect)) itsMateDefect++;
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
        fc_cout << "    inccorrectbyte  <increment>\n"
                   "    correctbyte     <count>\n"
                   "    errones         <count>\n"
                   "    errzeros        <count>\n"
                   "    uncorframe      <count>\n"
                   "    incuncorframe   <increment>\n"
                   "    bip8            <count>\n"
                   "    incbip8         <increment>\n"
                   "    bei             <count>\n"
                   "    incbei          <increment>\n"
                   "    highcorrectbyte <count>\n"
                   "    higherrones     <count>\n"
                   "    higherrzeros    <count>\n"
                   "    highuncorframe  <count>\n"
                   "    highbip8        <count>\n"
                   "    highbei         <count>\n"
                   "    lof             <on|off>\n"
                   "    lomf            <on|off>\n"
                   "    fecm            <on|off>\n"
                   "    ais             <on|off>\n"
                   "    bdi             <on|off>\n"
                   "    bersf           <on|off>\n"
                   "    bersd           <on|off>\n"
                   "    iae             <on|off>\n"
                   "    matedefect      <on|off>\n"
                   "    tim             <on|off>\n"
                   "    BER             <floating point number(i.e., 0.0001025)>\n"
                   "    dcstate         <tdcinit | dliinit | demuxinit | optimizing | unknown>\n"
                   "    rxtrace         <sapi(15 char max)> <dapi(15 char max)> <operator(28 char max)> <trace ID>" << endl;
    }
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_FecIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
