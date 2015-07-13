/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds - July 2003
 DESCRIPTION:Definition of the class TSPII_HopIf. This models the High
             Order Path termination entity.
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_HopIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_HopIf::TSPII_HopIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_HopIf::~TSPII_HopIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::RefreshGet()
{
    // Monitoring attributes
    itsDefectsChanged      = GetDefectsChanged();  // Must be done first
    itsAis                 = GetAis();
    itsUneq                = GetUneq();
    itsLop                 = GetLop();
    itsRdi                 = GetRdi();
    itsPlm                 = GetPlm();
    itsBerSd               = GetBerSd();
    itsBerSf               = GetBerSf();
    itsSFHigh              = GetSFHigh();
    itsSFLow               = GetSFLow();
    itsSD                  = GetSD();
    itsReiCount            = GetReiCount();
    itsCvCount             = GetCvCount();
    itsPpjgCount           = GetPpjgCount();
    itsNpjgCount           = GetNpjgCount();
    itsPpjdCount           = GetPpjdCount();
    itsNpjdCount           = GetNpjdCount();
    itsRxPQM               = GetRxPQM();
    itsRxTrace             = GetRxTrace();
    itsRxHwPQWSquelch      = GetRxHwPQWSquelch();
    itsTxHwPQWSquelch      = GetTxHwPQWSquelch();


    // Configuration attributes
    itsSpeMapping          = GetSpeMapping();
    itsTxTrace             = GetTxTrace();
    itsForceUneqEnabled    = GetForceUneqEnabled();
    itsForceAisEnabled     = GetForceAisEnabled();
    itsForceIntAisEnabled  = GetForceInternalAisEnabled();
    itsForceRdiEnabled     = GetForceRdiEnabled();
    itsBerSdThreshold      = GetBerSdThreshold();
    itsBerSfThreshold      = GetBerSfThreshold();
    itsExpectedC2          = GetExpectedC2();
    itsPointerJustEnabled  = GetPointerJustEnabled();
    itsSrcTrafficEnabled   = GetSrcTrafficEnabled();
    itsTxPQM               = GetTxPQM();
    itsFppEnabled          = GetFppEnabled();
    itsFppSquelchEnabled   = GetFppSquelchEnabled();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::RefreshSet()
{
    // Configuration attributes
    SetSpeMapping(itsSpeMapping);
    SetTxTrace(itsTxTrace);
    SetForceUneqEnabled(itsForceUneqEnabled);
    SetForceAisEnabled(itsForceAisEnabled);
    SetForceInternalAisEnabled(itsForceIntAisEnabled);
    SetForceRdiEnabled(itsForceRdiEnabled);
    SetBerSdThreshold(itsBerSdThreshold);
    SetBerSfThreshold(itsBerSfThreshold);
    SetExpectedC2(itsExpectedC2);
    SetPointerJustEnabled(itsPointerJustEnabled);
    SetSrcTrafficEnabled(itsSrcTrafficEnabled);
    SetTxPQM(itsTxPQM);
    SetFppEnabled(itsFppEnabled);
    SetFppSquelchEnabled(itsFppSquelchEnabled);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsAis                 = 0;
    itsUneq                = 0;
    itsLop                 = 0;
    itsRdi                 = 0;
    itsPlm                 = 0;
    itsBerSd               = 0;
    itsBerSf               = 0;
    itsSFHigh              = 0;
    itsSFLow               = 0;
    itsSD                  = 0;
    itsReiCount            = 0;
    itsCvCount             = 0;
    itsPpjgCount           = 0;
    itsNpjgCount           = 0;
    itsPpjdCount           = 0;
    itsNpjdCount           = 0;
    itsRxPQM               = 0;
    itsRxTrace             = CT_SONET64ByteTrace();
    itsDefectsChanged      = false;
    itsRxHwPQWSquelch      = false;
    itsTxHwPQWSquelch      = false;

    // Configuration attributes
    itsSpeMapping          = CT_TEL_HOP_MAPPING_STS1;
    itsTxTrace             = CT_SONET64ByteTrace();
    itsForceUneqEnabled    = false;
    itsForceAisEnabled     = false;
    itsForceIntAisEnabled  = false;
    itsForceRdiEnabled     = false;
    itsBerSdThreshold      = CT_TEL_NO_BER;
    itsBerSfThreshold      = CT_TEL_NO_BER;
    itsExpectedC2          = 0x00;
    itsPointerJustEnabled  = false;
    itsSrcTrafficEnabled   = false;
    itsTxPQM               = 0;
    itsFppEnabled          = false;
    itsFppSquelchEnabled   = true;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetAis()
{
    return itsAis;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetUneq()
{
    return itsUneq;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetLop()
{
    return itsLop;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetRdi()
{
    return itsRdi;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetPlm()
{
    return itsPlm;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetBerSf()
{
    return itsBerSf;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetBerSd()
{
    return itsBerSd;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetSFHigh()
{
    return itsSFHigh;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetSFLow()
{
    return itsSFLow;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetSD()
{
    return itsSD;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetCvCount()
{
    return itsCvCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetReiCount()
{
    return itsReiCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetPpjgCount()
{
    return itsPpjgCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetNpjgCount()
{
    return itsNpjgCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetPpjdCount()
{
    return itsPpjdCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HopIf::GetNpjdCount()
{
    return itsNpjdCount;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_HopIf::GetRxPQM()
{
    return itsRxPQM;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetDefectsChanged()
{
    return itsDefectsChanged;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetRxHwPQWSquelch()
{
    return itsRxHwPQWSquelch;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetTxHwPQWSquelch()
{
    return itsTxHwPQWSquelch;
}

///////////////////////////////////////////////////////////////////////////////
const CT_SONET64ByteTrace & TSPII_HopIf::GetRxTrace()
{
    return itsRxTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetSpeMapping(CT_TEL_HopSpeMapping theMapping)
{
    itsSpeMapping = theMapping;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_HopSpeMapping TSPII_HopIf::GetSpeMapping() const
{
    return itsSpeMapping;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetTxTrace(const CT_SONET64ByteTrace & theTrace)
{
    itsTxTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
const CT_SONET64ByteTrace & TSPII_HopIf::GetTxTrace() const
{
    return itsTxTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetForceUneqEnabled(bool theEnable)
{
    itsForceUneqEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetForceUneqEnabled() const
{
    return itsForceUneqEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetForceAisEnabled(bool theEnable)
{
    itsForceAisEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetForceAisEnabled() const
{
    return itsForceAisEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetForceInternalAisEnabled(bool theEnable)
{
    itsForceIntAisEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetForceInternalAisEnabled() const
{
    return itsForceIntAisEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetForceRdiEnabled(bool theEnable)
{
    itsForceRdiEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetForceRdiEnabled() const
{
    return itsForceRdiEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetBerSdThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSdThreshold = theThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_HopIf::GetBerSdThreshold() const
{
    return itsBerSdThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetBerSfThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSfThreshold = theThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_HopIf::GetBerSfThreshold() const
{
    return itsBerSfThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetExpectedC2(uint8 theC2)
{
    itsExpectedC2 = theC2;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_HopIf::GetExpectedC2() const
{
    return itsExpectedC2;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetPointerJustEnabled(bool theEnable)
{
    itsPointerJustEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetPointerJustEnabled() const
{
    return itsPointerJustEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetSrcTrafficEnabled(bool theEnable)
{
    itsSrcTrafficEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetSrcTrafficEnabled() const
{
    return itsSrcTrafficEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetTxPQM(uint16 thePQM, uint16 theMask)
{
    uint16 TxPQM;

    // Get current Tx value
    TxPQM = itsTxPQM;

    // Clear out current bits based on mask
    TxPQM &= ~(theMask);

    // Set new bits based on mask
    TxPQM |= (thePQM & theMask);

    // Set the new Tx value
    itsTxPQM = TxPQM;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_HopIf::GetTxPQM() const
{
    return itsTxPQM;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetFppEnabled(bool theEnabled)
{
    itsFppEnabled = theEnabled;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetFppEnabled() const
{
    return itsFppEnabled;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::SetFppSquelchEnabled(bool theEnabled)
{
    itsFppSquelchEnabled = theEnabled;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::GetFppSquelchEnabled() const
{
    return itsFppSquelchEnabled;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_HopIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aSpeMapping = itsSpeMapping;
    int aBerSdThreshold = itsBerSdThreshold;
    int aBerSfThreshold = itsBerSfThreshold;

    // Monitoring
    theStream << itsAis;
    theStream << itsUneq;
    theStream << itsLop;
    theStream << itsRdi;
    theStream << itsPlm;
    theStream << itsBerSd;
    theStream << itsBerSf;
    theStream << itsSFHigh;
    theStream << itsSFLow;
    theStream << itsSD;
    theStream << itsReiCount;
    theStream << itsCvCount;
    theStream << itsPpjgCount;
    theStream << itsNpjgCount;
    theStream << itsPpjdCount;
    theStream << itsNpjdCount;
    theStream << itsRxTrace;
    theStream << itsRxPQM;
    theStream << itsDefectsChanged;
    theStream << itsRxHwPQWSquelch;
    theStream << itsTxHwPQWSquelch;

    // Configuration
    theStream << aSpeMapping;
    theStream << itsTxTrace;
    theStream << itsForceUneqEnabled;
    theStream << itsForceAisEnabled;
    theStream << itsForceIntAisEnabled;
    theStream << itsForceRdiEnabled;
    theStream << aBerSdThreshold;
    theStream << aBerSfThreshold;
    theStream << itsExpectedC2;
    theStream << itsPointerJustEnabled;
    theStream << itsSrcTrafficEnabled;
    theStream << itsTxPQM;
    theStream << itsFppEnabled;
    theStream << itsFppSquelchEnabled;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_HopIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aSpeMapping;
    int aBerSdThreshold;
    int aBerSfThreshold;

    // Monitoring
    theStream >> itsAis;
    theStream >> itsUneq;
    theStream >> itsLop;
    theStream >> itsRdi;
    theStream >> itsPlm;
    theStream >> itsBerSd;
    theStream >> itsBerSf;
    theStream >> itsSFHigh;
    theStream >> itsSFLow;
    theStream >> itsSD;
    theStream >> itsReiCount;
    theStream >> itsCvCount;
    theStream >> itsPpjgCount;
    theStream >> itsNpjgCount;
    theStream >> itsPpjdCount;
    theStream >> itsNpjdCount;
    theStream >> itsRxTrace;
    theStream >> itsRxPQM;
    theStream >> itsDefectsChanged;
    theStream >> itsRxHwPQWSquelch;
    theStream >> itsTxHwPQWSquelch;

    // Configuration
    theStream >> aSpeMapping;
    theStream >> itsTxTrace;
    theStream >> itsForceUneqEnabled;
    theStream >> itsForceAisEnabled;
    theStream >> itsForceIntAisEnabled;
    theStream >> itsForceRdiEnabled;
    theStream >> aBerSdThreshold;
    theStream >> aBerSfThreshold;
    theStream >> itsExpectedC2;
    theStream >> itsPointerJustEnabled;
    theStream >> itsSrcTrafficEnabled;
    theStream >> itsTxPQM;
    theStream >> itsFppEnabled;
    theStream >> itsFppSquelchEnabled;

    // Update H/W
    itsSpeMapping = (CT_TEL_HopSpeMapping) aSpeMapping;
    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_HopIf::WriteObject(ostream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aSpeMapping = itsSpeMapping;
    int aBerSdThreshold = itsBerSdThreshold;
    int aBerSfThreshold = itsBerSfThreshold;

    // Monitoring
    theStream << FC_InsertVar(itsAis);
    theStream << FC_InsertVar(itsUneq);
    theStream << FC_InsertVar(itsLop);
    theStream << FC_InsertVar(itsRdi);
    theStream << FC_InsertVar(itsPlm);
    theStream << FC_InsertVar(itsBerSd);
    theStream << FC_InsertVar(itsBerSf);
    theStream << FC_InsertVar(itsSFHigh);
    theStream << FC_InsertVar(itsSFLow);
    theStream << FC_InsertVar(itsSD);
    theStream << FC_InsertVar(itsReiCount);
    theStream << FC_InsertVar(itsCvCount);
    theStream << FC_InsertVar(itsPpjgCount);
    theStream << FC_InsertVar(itsNpjgCount);
    theStream << FC_InsertVar(itsPpjdCount);
    theStream << FC_InsertVar(itsNpjdCount);
    theStream << FC_InsertVar(itsRxTrace);
    theStream << FC_InsertVar(itsRxPQM);
    theStream << FC_InsertVar(itsDefectsChanged);
    theStream << FC_InsertVar(itsRxHwPQWSquelch);
    theStream << FC_InsertVar(itsTxHwPQWSquelch);

    // Configuration
    theStream << FC_InsertVar(aSpeMapping);
    theStream << FC_InsertVar(itsTxTrace);
    theStream << FC_InsertVar(itsForceUneqEnabled);
    theStream << FC_InsertVar(itsForceAisEnabled);
    theStream << FC_InsertVar(itsForceIntAisEnabled);
    theStream << FC_InsertVar(itsForceRdiEnabled);
    theStream << FC_InsertVar(aBerSdThreshold);
    theStream << FC_InsertVar(aBerSfThreshold);
    theStream << FC_InsertVar(itsExpectedC2);
    theStream << FC_InsertVar(itsPointerJustEnabled);
    theStream << FC_InsertVar(itsSrcTrafficEnabled);
    theStream << FC_InsertVar(itsTxPQM);
    theStream << FC_InsertVar(itsFppEnabled);
    theStream << FC_InsertVar(itsFppSquelchEnabled);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_HopIf::ReadObject(istream & theStream)
{
    int aSpeMapping;
    int aBerSdThreshold;
    int aBerSfThreshold;

    // Monitoring
    theStream >> FC_ExtractVar(itsAis);
    theStream >> FC_ExtractVar(itsUneq);
    theStream >> FC_ExtractVar(itsLop);
    theStream >> FC_ExtractVar(itsRdi);
    theStream >> FC_ExtractVar(itsPlm);
    theStream >> FC_ExtractVar(itsBerSd);
    theStream >> FC_ExtractVar(itsBerSf);
    theStream >> FC_ExtractVar(itsSFHigh);
    theStream >> FC_ExtractVar(itsSFLow);
    theStream >> FC_ExtractVar(itsSD);
    theStream >> FC_ExtractVar(itsReiCount);
    theStream >> FC_ExtractVar(itsCvCount);
    theStream >> FC_ExtractVar(itsPpjgCount);
    theStream >> FC_ExtractVar(itsNpjgCount);
    theStream >> FC_ExtractVar(itsPpjdCount);
    theStream >> FC_ExtractVar(itsNpjdCount);
    theStream >> FC_ExtractVar(itsRxTrace);
    theStream >> FC_ExtractVar(itsRxPQM);
    theStream >> FC_ExtractVar(itsDefectsChanged);
    theStream >> FC_ExtractVar(itsRxHwPQWSquelch);
    theStream >> FC_ExtractVar(itsTxHwPQWSquelch);

    // Configuration
    theStream >> FC_ExtractVar(aSpeMapping);
    theStream >> FC_ExtractVar(itsTxTrace);
    theStream >> FC_ExtractVar(itsForceUneqEnabled);
    theStream >> FC_ExtractVar(itsForceAisEnabled);
    theStream >> FC_ExtractVar(itsForceIntAisEnabled);
    theStream >> FC_ExtractVar(itsForceRdiEnabled);
    theStream >> FC_ExtractVar(aBerSdThreshold);
    theStream >> FC_ExtractVar(aBerSfThreshold);
    theStream >> FC_ExtractVar(itsExpectedC2);
    theStream >> FC_ExtractVar(itsPointerJustEnabled);
    theStream >> FC_ExtractVar(itsSrcTrafficEnabled);
    theStream >> FC_ExtractVar(itsTxPQM);
    theStream >> FC_ExtractVar(itsFppEnabled);
    theStream >> FC_ExtractVar(itsFppSquelchEnabled);

    // Update H/W
    itsSpeMapping = (CT_TEL_HopSpeMapping) aSpeMapping;
    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::Display(FC_Stream & theStream)
{
    char buf[10];

    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  HOP Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Spe Mapping           = " << DISPLAY_HOP_SPE_MAPPING(itsSpeMapping) << "\n";
    theStream << "      Tx Trace              = \"" << itsTxTrace.GetTracePrintable()       << "\"\n";
    theStream << "      Force UNEQ enabled    = " << DISPLAY_BOOL(itsForceUneqEnabled)      << "\n";
    theStream << "      Force AIS enabled     = " << DISPLAY_BOOL(itsForceAisEnabled)       << "\n";
    theStream << "      Force Internal AIS    = " << DISPLAY_BOOL(itsForceIntAisEnabled)    << "\n";
    theStream << "      Force RDI enabled     = " << DISPLAY_BOOL(itsForceRdiEnabled)       << "\n";
    theStream << "      SD-BER Threshold      = " << DISPLAY_BER(itsBerSdThreshold)         << "\n";
    theStream << "      SF-BER Threshold      = " << DISPLAY_BER(itsBerSfThreshold)         << "\n";
    theStream << "      Pointer Just enabled  = " << DISPLAY_BOOL(itsPointerJustEnabled)    << "\n";
    theStream << "      Src traffic enabled   = " << DISPLAY_BOOL(itsSrcTrafficEnabled)     << "\n";
    sprintf(buf, "0x%04X", itsTxPQM);
    theStream << "      Tx PQM                = " << buf                                    << "\n";
    theStream << "      Fpp Enabled           = " << DISPLAY_BOOL(itsFppEnabled)            << "\n";
    theStream << "      Fpp Squelch Enabled   = " << DISPLAY_BOOL(itsFppSquelchEnabled)     << "\n";
    sprintf(buf, "0x%02X", itsExpectedC2);
    theStream << "      Expected C2           = " << buf                                    << "\n";
    theStream << "    MONITORING\n";
    theStream << "      AIS Defect            = " << TEXT_DEFECT(itsAis)                    << "\n";
    theStream << "      UNEQ Defect           = " << TEXT_DEFECT(itsUneq)                   << "\n";
    theStream << "      LOP Defect            = " << TEXT_DEFECT(itsLop)                    << "\n";
    theStream << "      RDI Defect            = " << TEXT_DEFECT(itsRdi)                    << "\n";
    theStream << "      PLM Defect            = " << TEXT_DEFECT(itsPlm)                    << "\n";
    theStream << "      SD-BER Defect         = " << TEXT_DEFECT(itsBerSd)                  << "\n";
    theStream << "      SF-BER Defect         = " << TEXT_DEFECT(itsBerSf)                  << "\n";
    theStream << "      SF-High PQM Defect    = " << TEXT_DEFECT(itsSFHigh)                 << "\n";
    theStream << "      SF-Low PQM Defect     = " << TEXT_DEFECT(itsSFLow)                  << "\n";
    theStream << "      SD PQM Defect         = " << TEXT_DEFECT(itsSD)                     << "\n";
    theStream << "      CV Count              = " << itsCvCount                             << "\n";
    theStream << "      REI Count             = " << itsReiCount                            << "\n";
    theStream << "      PPJG Count            = " << itsPpjgCount                           << "\n";
    theStream << "      NPJG Count            = " << itsNpjgCount                           << "\n";
    theStream << "      PPJD Count            = " << itsPpjdCount                           << "\n";
    theStream << "      NPJD Count            = " << itsNpjdCount                           << "\n";
    sprintf(buf, "0x%04X", itsRxPQM);
    theStream << "      Rx PQM                = " << buf                                    << "\n";
    theStream << "      Rx Trace              = \"" << itsRxTrace.GetTracePrintable()       << "\"\n";
    theStream << "      Defects Changed       = " << DISPLAY_BOOL(itsDefectsChanged)        << "\n";
    theStream << "      Rx PQW HW Squelch     = " << DISPLAY_BOOL(itsRxHwPQWSquelch)        << "\n";
    theStream << "      Tx PQW HW Squelch     = " << DISPLAY_BOOL(itsTxHwPQWSquelch)        << endl;

    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::Set(int argc, char ** argv)
{

    bool printUsage = false;

    if (argc == 2 && (strcmp(argv[0], "txtrace") == 0))
    {
        CT_SONET64ByteTrace trace(argv[1]);
        SetTxTrace(trace);
    }
    else if ((argc == 2) && (strcmp(argv[0], "txpqm") == 0))
    {
        SetTxPQM(static_cast<uint16>(strtoul(argv[1], NULL, 0)));
    }
    else if ((argc == 2) && (strcmp(argv[0], "fppenabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetFppEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetFppEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "fppsqfenabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetFppSquelchEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetFppSquelchEnabled(false);
        }
        else
        {
            printUsage = true;
        }
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
    else if ((argc == 2) && (strcmp(argv[0], "uneqenabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceUneqEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceUneqEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "aisenabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceAisEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceAisEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "intaisenabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceInternalAisEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceInternalAisEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "rdienabled") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetForceRdiEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetForceRdiEnabled(false);
        }
        else
        {
            printUsage = true;
        }
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
    else if (argc == 2 && strcmp(argv[0], "expectedc2") == 0)
    {
        long c2;

        c2 = strtol(argv[1], NULL, 0);
        if((c2 >= 0) || (c2 <= 0xFF))
        {
            SetExpectedC2((uint8)c2);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "pointerjust") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetPointerJustEnabled(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetPointerJustEnabled(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "spemapping") == 0))
    {
        printUsage = true;
        for (int i = 0; i < CT_TEL_HOP_MAPPING_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_HOP_SPE_MAPPING(i)) == 0)
        {
            SetSpeMapping((CT_TEL_HopSpeMapping)i);
            printUsage = false;
            break;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    txtrace         <62 bytes trace>\n"
                   "    txpqm           <0 ... 0xFFFF>\n"
                   "    fppenabled      <on|off>\n"
                   "    fppsqfenabled   <on|off>\n"
                   "    trafenabled     <on|off>\n"
                   "    uneqenabled     <on|off>\n"
                   "    aisenabled      <on|off>\n"
                   "    intaisenabled   <on|off>\n"
                   "    rdienabled      <on|off>\n"
                   "    bersdthres      <Error free|10-12|10-11| ... |10-3>\n"
                   "    bersfthres      <Error free|10-12|10-11| ... |10-3>\n"
                   "    expectedc2      <0 ... 0xFF>\n"
                   "    pointerjust     <on|off>\n"
                   "    spemapping      <STS1|STS3C|STS12C|STS48C|STS192C|STS1C22V|STS3T|STS12T|STS48T|STS192T|CONCAT>" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HopIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "ais") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsAis)) itsAis++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsAis)) itsAis++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "uneq") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsUneq)) itsUneq++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsUneq)) itsUneq++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "lop") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsLop)) itsLop++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsLop)) itsLop++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "rdi") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsRdi)) itsRdi++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsRdi)) itsRdi++;
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
            if (!TSPII_DEFECT(itsPlm)) itsPlm++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsPlm)) itsPlm++;
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
    else if ((argc == 2) && (strcmp(argv[0], "sfhpqm") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsSFHigh)) itsSFHigh++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsSFHigh)) itsSFHigh++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "sflpqm") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsSFLow)) itsSFLow++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsSFLow)) itsSFLow++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "sdpqm") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsSD)) itsSD++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsSD)) itsSD++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "reicount") == 0))
    {
        itsReiCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "increicount") == 0)
    {
        itsReiCount += strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "cvcount") == 0))
    {
        itsCvCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "inccvcount") == 0)
    {
        itsCvCount += strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "ppjgcount") == 0))
    {
        itsPpjgCount = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "npjgcount") == 0))
    {
        itsNpjgCount = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "ppjdcount") == 0))
    {
        itsPpjdCount = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "npjdcount") == 0))
    {
        itsNpjdCount = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxpqm") == 0))
    {
        itsRxPQM = static_cast<uint16>(strtoul(argv[1], NULL, 0));
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxtrace") == 0))
    {
        itsRxTrace = CT_SONET64ByteTrace(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "defectschanged") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsDefectsChanged = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsDefectsChanged = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxhwpqwsquelch") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsRxHwPQWSquelch = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsRxHwPQWSquelch = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "txhwpqwsquelch") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsTxHwPQWSquelch = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsTxHwPQWSquelch = false;
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
        fc_cout << "    ais             <on|off>\n"
                   "    uneq            <on|off>\n"
                   "    lop             <on|off>\n"
                   "    rdi             <on|off>\n"
                   "    plm             <on|off>\n"
                   "    bersf           <on|off>\n"
                   "    bersd           <on|off>\n"
                   "    sfhpqm          <on|off>\n"
                   "    sflpqm          <on|off>\n"
                   "    sdpqm           <on|off>\n"
                   "    reicount        <0 ... 0xFFFFFFFF>\n"
                   "    cvcount         <0 ... 0xFFFFFFFF>\n"
                   "    increicount     <0 ... 0xFFFFFFFF>\n"
                   "    inccvcount      <0 ... 0xFFFFFFFF>\n"
                   "    ppjgcount       <0 ... 0xFFFFFFFF>\n"
                   "    npjgcount       <0 ... 0xFFFFFFFF>\n"
                   "    ppjgcount       <0 ... 0xFFFFFFFF>\n"
                   "    npjdcount       <0 ... 0xFFFFFFFF>\n"
                   "    rxpqm           <0 ... 0xFFFFFFFF>\n"
                   "    rxtrace         <62 bytes trace>\n"
                   "    defectschanged  <on|off>\n"
                   "    rxhwpqwsquelch  <on|off>\n"
                   "    txhwpqwsquelch  <on|off>" << endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HopIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}

