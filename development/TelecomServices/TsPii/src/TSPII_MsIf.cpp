/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds - July 2003
 DESCRIPTION:Definition of the class TSPII_MsIf. This provides abstract
             interface for SONET/SDH Line/MS termination hardware.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_MsIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <iostream>
#include <iomanip>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_MsIf::TSPII_MsIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_MsIf::~TSPII_MsIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::RefreshGet()
{
    // Monitoring attributes
    itsAis                  = GetAis();
    itsInternalAis          = GetInternalAis();
    itsProprietaryInternalAis = GetProprietaryInternalAis();
    itsRdi                  = GetRdi();
    itsBerSf                = GetBerSf();
    itsBerSd                = GetBerSd();
    itsCvCount              = GetCvCount();
    itsReiCount             = GetReiCount();
    itsK1RxByte             = GetK1RxByte();
    itsK2RxByte             = GetK2RxByte();
    itsRxSsm                = GetRxSsm();
    itsRxCsi                = GetRxCsi();
    itsIsTimingRefValid     = GetIsTimingRefValid();

    // Configuration attributes
    itsBerSdThreshold       = GetBerSdThreshold();
    itsBerSfThreshold       = GetBerSfThreshold();
    itsK1TxByte             = GetK1TxByte();
    itsK2TxByte             = GetK2TxByte();
    itsTxSsm                = GetTxSsm();
    itsTimingRef            = GetAsTimingRef();
    itsFirstTimeslot        = GetFirstTimeslot();
    itsTxCsi                = GetTxCsi();
    itsDerivedSourceMode    = GetDerivedTimingSourceMode();
	itsMappedInputReference = GetInputReferenceMapping();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::RefreshSet()
{
    // Configuration attributes
    SetBerSdThreshold(itsBerSdThreshold);
    SetBerSfThreshold(itsBerSfThreshold);
    SetK1TxByte(itsK1TxByte);
    SetK2TxByte(itsK2TxByte);
    SetTxSsm(itsTxSsm);
    SetAsTimingRef(itsTimingRef);
    SetFirstTimeslot(itsFirstTimeslot);
    SetTxCsi(itsTxCsi);
    SetDerivedTimingSourceMode(itsDerivedSourceMode);
	SetInputReferenceMapping(itsMappedInputReference);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::Reset()
{
    TSPII_BaseIf::Reset();
    
    // Monitoring attributes
    itsAis                   = 0;
    itsInternalAis           = 0;
    itsProprietaryInternalAis  = 0;
    itsRdi                   = 0;
    itsBerSf                 = 0;
    itsBerSd                 = 0;
    itsCvCount               = 0;
    itsReiCount              = 0;
    itsK1RxByte              = 0;
    itsK2RxByte              = 0;
    itsRxSsm                 = CT_RxSsm_DUS;
    itsRxCsi                 = 0;
    itsIsTimingRefValid      = false;

    // Configuration attributes
    itsBerSdThreshold        = CT_TEL_NO_BER;
    itsBerSfThreshold        = CT_TEL_NO_BER;
    itsK1TxByte              = 0;
    itsK2TxByte              = 0;
    itsTxSsm                 = CT_RxSsm_DUS;
    itsTimingRef             = CT_TEL_MS_TREF_NONE;
    itsFirstTimeslot         = 0;
    itsTxCsi                 = 0;
    itsDerivedSourceMode     = CT_DT_SOURCE_NONE;
	itsMappedInputReference  = 0;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetAis() 
{
    return itsAis;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetInternalAis() 
{
    return itsInternalAis;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetProprietaryInternalAis() 
{
    return itsProprietaryInternalAis;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetRdi() 
{
    return itsRdi;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_MsIf::GetK1RxByte()
{
    return itsK1RxByte;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_MsIf::GetK2RxByte()
{
    return itsK2RxByte;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetBerSf()
{
    return itsBerSf;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetBerSd()
{
    return itsBerSd;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetCvCount()
{
    return itsCvCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MsIf::GetReiCount()
{
    return itsReiCount;
}

///////////////////////////////////////////////////////////////////////////////
CT_FAC_RxSsm  TSPII_MsIf::GetRxSsm()
{
    return itsRxSsm;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_MsIf::GetRxCsi()
{
    return itsRxCsi;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MsIf::GetIsTimingRefValid()
{
    return itsIsTimingRefValid;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetBerSdThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSdThreshold = theThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_MsIf::GetBerSdThreshold() const
{
    return itsBerSdThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetBerSfThreshold(CT_TEL_BERLevels theThreshold)
{
    itsBerSfThreshold = theThreshold;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_BERLevels TSPII_MsIf::GetBerSfThreshold() const
{
    return itsBerSfThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetK1TxByte(uint8 theValue)
{
    itsK1TxByte = theValue;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_MsIf::GetK1TxByte() const
{
    return itsK1TxByte;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetK2TxByte(uint8 theValue)
{
    itsK2TxByte = theValue;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_MsIf::GetK2TxByte() const
{
    return itsK2TxByte;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetTxSsm(CT_FAC_RxSsm theSsm)
{
    itsTxSsm = theSsm;
}

///////////////////////////////////////////////////////////////////////////////
CT_FAC_RxSsm TSPII_MsIf::GetTxSsm() const
{
    return itsTxSsm;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetAsTimingRef(CT_TEL_MsTref theRef)
{
    itsTimingRef = theRef;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MsTref TSPII_MsIf::GetAsTimingRef() const
{
    return itsTimingRef;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetFirstTimeslot(uint16 theTslot)
{
    itsFirstTimeslot = theTslot;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MsIf::GetFirstTimeslot() const
{
    return itsFirstTimeslot;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetTxCsi(uint8 theValue)
{
    itsTxCsi = theValue;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_MsIf::GetTxCsi() const
{
    return itsTxCsi;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetDerivedTimingSourceMode(CT_TEL_DT_Source_Mode theDTSourceMode)
{
    itsDerivedSourceMode = theDTSourceMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_DT_Source_Mode TSPII_MsIf::GetDerivedTimingSourceMode() const
{
    return itsDerivedSourceMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::SetInputReferenceMapping(uint16 theInputRef)
{
    itsMappedInputReference = theInputRef;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MsIf::GetInputReferenceMapping() const
{
    return itsMappedInputReference;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_MsIf::WriteObjectBinary(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    int aBerSdThreshold = itsBerSdThreshold;
    int aBerSfThreshold = itsBerSfThreshold;
    int aRxSsm = itsRxSsm;
    int aTxSsm = itsTxSsm;
    int aTimingRef = itsTimingRef;
	int aDTSource = itsDerivedSourceMode;

    // Monitoring attributes
    theStream << itsAis;
    theStream << itsInternalAis;
    theStream << itsProprietaryInternalAis;
    theStream << itsRdi;
    theStream << itsBerSf;
    theStream << itsBerSd;
    theStream << itsCvCount;
    theStream << itsReiCount;
    theStream << itsK1RxByte;
    theStream << itsK2RxByte;
    theStream << aRxSsm;
    theStream << itsRxCsi;
    theStream << itsIsTimingRefValid;

    // Configuration attributes
    theStream << aBerSdThreshold;
    theStream << aBerSfThreshold;
    theStream << itsK1TxByte;
    theStream << itsK2TxByte;
    theStream << aTxSsm;
    theStream << aTimingRef;
    theStream << itsFirstTimeslot;
    theStream << itsTxCsi;
    theStream << aDTSource;
	theStream << itsMappedInputReference;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_MsIf::ReadObjectBinary(FC_Stream & theStream)
{
    int aBerSdThreshold;
    int aBerSfThreshold;
    int aRxSsm;
    int aTxSsm;
    int aTimingRef;
	int aDTSource;

    // Monitoring attributes
    theStream >> itsAis;
    theStream >> itsInternalAis;
    theStream >> itsProprietaryInternalAis;
    theStream >> itsRdi;
    theStream >> itsBerSf;
    theStream >> itsBerSd;
    theStream >> itsCvCount;
    theStream >> itsReiCount;
    theStream >> itsK1RxByte;
    theStream >> itsK2RxByte;
    theStream >> aRxSsm;
    theStream >> itsRxCsi;
    theStream >> itsIsTimingRefValid;

    itsRxSsm = (CT_FAC_RxSsm) aRxSsm;

    // Configuration attributes
    theStream >> aBerSdThreshold;
    theStream >> aBerSfThreshold;
    theStream >> itsK1TxByte;
    theStream >> itsK2TxByte;
    theStream >> aTxSsm;
    theStream >> aTimingRef;
    theStream >> itsFirstTimeslot;
    theStream >> itsTxCsi;
    theStream >> aDTSource;
	theStream >> itsMappedInputReference;

    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    itsTxSsm = (CT_FAC_RxSsm) aTxSsm;
    itsTimingRef = (CT_TEL_MsTref) aTimingRef;
	itsDerivedSourceMode = (CT_TEL_DT_Source_Mode)aDTSource;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_MsIf::WriteObject(ostream & theStream)
{      
    // Update H/W
    UpdateValues();
    RefreshGet();
    
    int aBerSdThreshold = itsBerSdThreshold;
    int aBerSfThreshold = itsBerSfThreshold;
    int aRxSsm = itsRxSsm;
    int aTxSsm = itsTxSsm;
    int aTimingRef = itsTimingRef;
	int aDTSource = itsDerivedSourceMode;

    // Monitoring attributes
    theStream << FC_InsertVar(itsAis);
    theStream << FC_InsertVar(itsInternalAis);
    theStream << FC_InsertVar(itsProprietaryInternalAis);
    theStream << FC_InsertVar(itsRdi);
    theStream << FC_InsertVar(itsBerSf);
    theStream << FC_InsertVar(itsBerSd);
    theStream << FC_InsertVar(itsCvCount);
    theStream << FC_InsertVar(itsReiCount);
    theStream << FC_InsertVar(itsK1RxByte);
    theStream << FC_InsertVar(itsK2RxByte);
    theStream << FC_InsertVar(aRxSsm);
    theStream << FC_InsertVar(itsRxCsi);
    theStream << FC_InsertVar(itsIsTimingRefValid);

    // Configuration attributes
    theStream << FC_InsertVar(aBerSdThreshold);
    theStream << FC_InsertVar(aBerSfThreshold);
    theStream << FC_InsertVar(itsK1TxByte);
    theStream << FC_InsertVar(itsK2TxByte);
    theStream << FC_InsertVar(aTxSsm);
    theStream << FC_InsertVar(aTimingRef);
    theStream << FC_InsertVar(itsFirstTimeslot);
    theStream << FC_InsertVar(itsTxCsi);
    theStream << FC_InsertVar(aDTSource);
	theStream << FC_InsertVar(itsMappedInputReference);
    
    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_MsIf::ReadObject(istream & theStream)
{
    int aBerSdThreshold;
    int aBerSfThreshold;
    int aRxSsm;
    int aTxSsm;
    int aTimingRef;
	int aDTSource;

    // Monitoring attributes
    theStream >> FC_ExtractVar(itsAis);
    theStream >> FC_ExtractVar(itsInternalAis);
    theStream >> FC_ExtractVar(itsProprietaryInternalAis);
    theStream >> FC_ExtractVar(itsRdi);
    theStream >> FC_ExtractVar(itsBerSf);
    theStream >> FC_ExtractVar(itsBerSd);
    theStream >> FC_ExtractVar(itsCvCount);
    theStream >> FC_ExtractVar(itsReiCount);
    theStream >> FC_ExtractVar(itsK1RxByte);
    theStream >> FC_ExtractVar(itsK2RxByte);
    theStream >> FC_ExtractVar(aRxSsm);
    theStream >> FC_ExtractVar(itsRxCsi);
    theStream >> FC_ExtractVar(itsIsTimingRefValid);

    itsRxSsm = (CT_FAC_RxSsm) aRxSsm;

    // Configuration attributes
    theStream >> FC_ExtractVar(aBerSdThreshold);
    theStream >> FC_ExtractVar(aBerSfThreshold);
    theStream >> FC_ExtractVar(itsK1TxByte);
    theStream >> FC_ExtractVar(itsK2TxByte);
    theStream >> FC_ExtractVar(aTxSsm);
    theStream >> FC_ExtractVar(aTimingRef);
    theStream >> FC_ExtractVar(itsFirstTimeslot);
    theStream >> FC_ExtractVar(itsTxCsi);
    theStream >> FC_ExtractVar(aDTSource);
	theStream >> FC_ExtractVar(itsMappedInputReference);
    
    itsBerSdThreshold = (CT_TEL_BERLevels) aBerSdThreshold;
    itsBerSfThreshold = (CT_TEL_BERLevels) aBerSfThreshold;
    itsTxSsm = (CT_FAC_RxSsm) aTxSsm;
    itsTimingRef = (CT_TEL_MsTref) aTimingRef;
	itsDerivedSourceMode = (CT_TEL_DT_Source_Mode)aDTSource;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::Display(FC_Stream & theStream)
{
    char buf[10];

    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  MS Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      SD-BER Threshold      = " << DISPLAY_BER(itsBerSdThreshold)               << "\n";
    theStream << "      SF-BER Threshold      = " << DISPLAY_BER(itsBerSfThreshold)               << "\n";
    sprintf(buf, "0x%2.2X", itsK1TxByte);
    theStream << "      K1 Tx Byte            = " << buf                                          << "\n";
    sprintf(buf, "0x%2.2X", itsK2TxByte);
    theStream << "      K2 Tx Byte            = " << buf                                          << "\n";
    theStream << "      Tx SSM                = " << display_RXSSM(itsTxSsm)                      << "\n";
    sprintf(buf, "0x%2.2X", itsTxCsi);
    theStream << "      Tx CSI                = " << buf                                          << "\n";
    theStream << "      Timing Ref            = " << DISPLAY_MS_TREF(itsTimingRef)                << "\n";
    theStream << "      First Timeslot        = " << itsFirstTimeslot + 1                         << "\n";
    theStream << "      Derived Timing Source = " << DISPLAY_DT_SOURCE_MODE(itsDerivedSourceMode) << "\n";
	theStream << "      Mapped Input Ref      = " << itsMappedInputReference                      << "\n";
    theStream << "    MONITORING\n";
    theStream << "      AIS Defect            = " << TEXT_DEFECT(itsAis)                          << "\n";
    theStream << "      Internal AIS Defect   = " << TEXT_DEFECT(itsInternalAis)                  << "\n";
    theStream << "      Propri Internal AIS   = " << TEXT_DEFECT(itsProprietaryInternalAis)                  << "\n";
    theStream << "      RDI Defect            = " << TEXT_DEFECT(itsRdi)                          << "\n";
    theStream << "      SD-BER Defect         = " << TEXT_DEFECT(itsBerSd)                        << "\n";
    theStream << "      SF-BER Defect         = " << TEXT_DEFECT(itsBerSf)                        << "\n";    
    theStream << "      CV Count              = " << itsCvCount                                   << "\n";    
    theStream << "      REI Count             = " << itsReiCount                                  << "\n";
    sprintf(buf, "0x%2.2X", itsK1RxByte);
    theStream << "      K1 Rx Byte            = " << buf                                          << "\n";
    sprintf(buf, "0x%2.2X", itsK2RxByte);
    theStream << "      K2 Rx Byte            = " << buf                                          << "\n";
    theStream << "      Rx SSM                = " << display_RXSSM(itsRxSsm)                      << "\n";
    sprintf(buf, "0x%2.2X", itsRxCsi);
    theStream << "      Rx CSI                = " << buf                                          << "\n";
    theStream << "      Is Timing Ref Valid   = " << DISPLAY_BOOL(itsIsTimingRefValid)            << "\n";
    theStream << endl;

    TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MsIf::Set(int argc, char ** argv)
{

    bool printUsage = false;

    if ((argc == 2) && strcmp(argv[0], "bersdthres") == 0)
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
    else if (argc == 2 && strcmp(argv[0], "k1txbyte") == 0)
    {
        long k1byte;

        k1byte = strtol(argv[1], NULL, 0);
        if((k1byte >= 0) || (k1byte <= 0xFF))
        {
            SetK1TxByte((uint8)k1byte);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "k2txbyte") == 0)
    {
        long k2byte;

        k2byte = strtol(argv[1], NULL, 0);
        if((k2byte >= 0) || (k2byte <= 0xFF))
        {
            SetK2TxByte((uint8)k2byte);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "txcsi") == 0)
    {
        long csi;

        csi = strtol(argv[1], NULL, 0);
        if((csi >= 0) || (csi <= 0xFF))
        {
            SetTxCsi((uint8)csi);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "txssm") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_RxSsm_ALL; i++) if (strcmp(argv[1], display_RXSSM(i)) == 0)
        {
            SetTxSsm((CT_FAC_RxSsm)i);
            printUsage = false;
            break;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "timingref") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_RxSsm_ALL; i++) if (strcmp(argv[1], DISPLAY_MS_TREF(i)) == 0)
        {
            SetAsTimingRef((CT_TEL_MsTref)i);
            printUsage = false;
            break;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "firsttimeslot") == 0)
    {
        long timeslot;

        timeslot = strtol(argv[1], NULL, 0);
        if((timeslot >= 1) || (timeslot <= 192))
        {
            SetFirstTimeslot((uint16)timeslot - 1);
        }
        else
        {
            printUsage = true;
        }
    }
	else if (argc == 2 && strcmp(argv[0], "derivedtmgsrc") == 0)
    {
        printUsage = true;
        for (int i = 0; i < CT_DT_SOURCE_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_DT_SOURCE_MODE(i)) == 0)
        {
            SetDerivedTimingSourceMode((CT_TEL_DT_Source_Mode)i);
            printUsage = false;
            break;
        }
    }
	else if (argc == 2 && strcmp(argv[0], "mapinputref") == 0)
    {
        long inputRef;

        inputRef = strtol(argv[1], NULL, 0);
        SetInputReferenceMapping((uint16)inputRef);
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    bersdthres      <Error free|10-12|10-11| ... |10-3>\n"
                   "    bersfthres      <Error free|10-12|10-11| ... |10-3>\n"
                   "    k1txbyte        <0 ... 0xFF>\n"
                   "    k2txbyte        <0 ... 0xFF>\n" 
                   "    txcsi           <0 ... 0xFF>\n" 
                   "    txssm           <PRS|STU|ST2|TNC|ST3E|ST3|SMC|ST4|PNO|DUS>\n"
                   "                    <SEC|PRC|SSUA|SSUB|DNU>\n"
                   "    timingref       <Primary|Secondary|None>\n" 
                   "    firsttimeslot   <1 ... 192>\n" 
                   "    derivedtmgsrc   <SourceA|SourceB|SourceA_B|None>\n" 
				   "    mapinputref     <0 ... 0xFFFF>\n"<< endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MsIf::Simul(int argc, char ** argv)
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
    else if ((argc == 2) && (strcmp(argv[0], "internalais") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsInternalAis)) itsInternalAis++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsInternalAis)) itsInternalAis++;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "propinternalais") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if (!TSPII_DEFECT(itsProprietaryInternalAis)) itsProprietaryInternalAis++;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if (TSPII_DEFECT(itsProprietaryInternalAis)) itsProprietaryInternalAis++;
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
    else if ((argc == 2) && (strcmp(argv[0], "cvcount") == 0))
    {
        itsCvCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "inccvcount") == 0)
    {
        itsCvCount += strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "reicount") == 0))
    {
        itsReiCount = strtoul(argv[1], NULL, 0);
    }
    else if (argc == 2 && strcmp(argv[0], "increicount") == 0)
    {
        itsReiCount += strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "k1rxbyte") == 0))
    {
        long k1byte;

        k1byte = strtol(argv[1], NULL, 0);
        if((k1byte >= 0) && (k1byte <= 255))
        {
            itsK1RxByte = (uint8)k1byte;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "k2rxbyte") == 0))
    {
        long k2byte;

        k2byte = strtol(argv[1], NULL, 0);
        if((k2byte >= 0) && (k2byte <= 255))
        {
            itsK2RxByte = (uint8)k2byte;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "rxcsi") == 0))
    {
        long csi;

        csi = strtol(argv[1], NULL, 0);
        if((csi >= 0) && (csi <= 255))
        {
            itsRxCsi = (uint8)csi;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "rxssm") == 0)
    {
        printUsage = true;
        for (int i = 0; i <= CT_RxSsm_ALL; i++) if (strcmp(argv[1], display_RXSSM(i)) == 0)
        {
            itsRxSsm = (CT_FAC_RxSsm)i;
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "trefvalid") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsIsTimingRefValid = true;;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsIsTimingRefValid = false;
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
                   "    internalais     <on|off>\n"   
                   "    propinternalais <on|off>\n"   
                   "    rdi             <on|off>\n"   
                   "    bersf           <on|off>\n"
                   "    bersd           <on|off>\n"
                   "    cvcount         <0 ... 0xFFFFFFFF>\n"
                   "    reicount        <0 ... 0xFFFFFFFF>\n"
                   "    inccvcount      <0 ... 0xFFFFFFFF>\n"
                   "    increicount     <0 ... 0xFFFFFFFF>\n"
                   "    k1rxbyte        <0 ... 0xFF>\n"
                   "    k2rxbyte        <0 ... 0xFF>\n" 
                   "    rxcsi           <0 ... 0xFF>\n" 
                   "    rxssm           <PRS|STU|ST2|TNC|ST3E|ST3|SMC|ST4|PNO|DUS>\n"
                   "    trefvalid       <on|off>\n" << endl;
    }
    
    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MsIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}
