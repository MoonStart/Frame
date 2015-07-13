/*-----------------------------------------------------------------------------
Copyright(c) Tellabs, Inc. All rights reserved.

SUBSYSTEM:      Telecom Services
TARGET:         TSPII 
AUTHOR:         David A. Marcinkiewicz
DESCRIPTION:    OSA base class for LIAME/LRAME
-----------------------------------------------------------------------------*/

#include "TsPii/TSPII_OsaIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
TSPII_OsaIf::TSPII_OsaIf(bool theDefault, bool theOsaPowerSupported) :
    TSPII_BaseIf(theDefault),
    myOsaPowerSupported(theOsaPowerSupported)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_OsaIf::~TSPII_OsaIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::RefreshGet()
{
    int i;

    myChanPowerOffset = GetChanPowerOffset();
    myChanPowerResolution = GetChanPowerResolution();
    myItuSpacing = GetItuSpacing();
    myItuFrequency = GetStartItuFrequency();
    myMaxNumChannels = GetMaxNumChannels();

    myOpmStatus = GetOpmStatus();
    UpdateOpmStatusBits();
    myLOSHysteresis = GetLOSHysteresis();

    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) myOsnrValid[i] = IsOsnrValid(i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) myOsaChanPower[i] = GetPower(i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) myOsaInputChanPower[i] = GetInputPower(i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) myOsaChanOSNR[i]  = GetOsnr(i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) 
    {
        myOsaOutputChanPower[i] = GetOutputPower(i);
    }

    for (i=0; i < TSPII_MAX_OSA_CHANELS; i++)
        myLOS[i] = GetLOS(i);

    for (i=0; i < TSPII_MAX_OSA_CHANELS; i++)
        myLOSThreshold[i] = GetLOSThreshold(i);

    for (i=0; i < TSPII_MAX_OSA_CHANELS; i++)
        myChType40G[i] = IsOch40G(i);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::RefreshSet()
{
    int i;

    SetItuSpacing(myItuSpacing);
    SetStartItuFrequency(myItuFrequency);
    SetMaxNumChannels(myMaxNumChannels);
    SetChanPowerOffset(myChanPowerOffset);
    SetChanPowerResolution(myChanPowerResolution);
    for (i=0; i < TSPII_MAX_OSA_CHANELS; i++)
        SetLOSThreshold(myLOSThreshold[i], i);
    SetLOSHysteresis(myLOSHysteresis);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::Reset()
{
    int i;

    TSPII_BaseIf::Reset();
    myOpmStatus = 0;
    UpdateOpmStatusBits();

    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++)
    {
        myOsnrValid[i] = true;
        myOsaChanPower[i] = TRAFFIC_DEFAULT_POWER;
        myOsaInputChanPower[i] = TRAFFIC_DEFAULT_POWER;
        myOsaChanOSNR[i]  = TRAFFIC_DEFAULT_POWER;
        myLOS[i] = 0;
        myLOSThreshold[i] = 0;
        myOsaOutputChanPower[i] = TRAFFIC_DEFAULT_POWER;
        myChType40G[i] = false;
    }
    myLOSHysteresis = TSPII_OSA_DEFAULT_HYSTERESIS;

    // default to zero for simulation
    SetItuSpacing(0);
    SetStartItuFrequency(0);
    SetMaxNumChannels(TSPII_MAX_OSA_CHANELS);
    SetChanPowerOffset(0);
    SetChanPowerResolution(0);
    myOchHist.ClearHistoryForAllCh();
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OsaIf::IsOsnrValid(uint32 theIndex) const
{
    return myOsnrValid[theIndex];
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OsaIf::IsOch10G(uint32 theIndex) const
{
    bool rc = false;

    if (theIndex < TSPII_MAX_OSA_CHANELS)
    {
        if (myChType40G[theIndex] == false)
            rc = true;
    }

    return rc;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OsaIf::IsOch40G(uint32 theIndex) const
{
    if (theIndex < TSPII_MAX_OSA_CHANELS)
        return myChType40G[theIndex];
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OsaIf::IsOsaPowerSupported()
{
    return myOsaPowerSupported;
}
///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetItuSpacing(uint32 theItuSpacing)
{    
    myItuSpacing = theItuSpacing;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetStartItuFrequency(uint32 theItuFrequency)
{
    myItuFrequency = theItuFrequency;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OsaIf::GetItuSpacing()
{    
    return myItuSpacing;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OsaIf::GetStartItuFrequency()
{
   return myItuFrequency;
} 

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetMaxNumChannels(uint32 theMaxNumChannels)
{
    myMaxNumChannels = theMaxNumChannels;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OsaIf::GetMaxNumChannels()
{
    return myMaxNumChannels;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetChanPowerOffset(uint32 theChanPowerOffset)
{
    myChanPowerOffset = theChanPowerOffset;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OsaIf::GetChanPowerOffset()
{
    return myChanPowerOffset;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetChanPowerResolution(uint32 theChanPowerResolution)
{
    myChanPowerResolution = theChanPowerResolution;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OsaIf::GetChanPowerResolution()
{
    return myChanPowerResolution;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OsaIf::GetPower(uint32 theIndex)
{
    if (theIndex < TSPII_MAX_OSA_CHANELS)
        return myOsaChanPower[theIndex];
    else
        return TRAFFIC_DEFAULT_POWER;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetLOSThreshold(CT_TEL_mBm theLOSThreshold, uint32 theIndex)
{
    myLOSThreshold[theIndex] = theLOSThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetLOSThreshold(CT_TEL_mBm theLOSThreshold)
{
    uint32 i;
    for (i=0; i < TSPII_MAX_OSA_CHANELS; i++)
        SetLOSThreshold(theLOSThreshold, i);
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OsaIf::GetLOSThreshold(uint32 theIndex)
{
    if (theIndex < TSPII_MAX_OSA_CHANELS)
        return myLOSThreshold[theIndex];
    else
        return TRAFFIC_DEFAULT_POWER;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OsaIf::GetInputPower(uint32 theIndex)
{
    if (theIndex < TSPII_MAX_OSA_CHANELS)
        return myOsaInputChanPower[theIndex];
    else
        return TRAFFIC_DEFAULT_POWER;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OsaIf::GetOsnr(uint32 theIndex)
{
    if (theIndex < TSPII_MAX_OSA_CHANELS)
        return myOsaChanOSNR[theIndex];
    else
        return TRAFFIC_DEFAULT_POWER;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OsaIf::GetOutputPower(uint32 theIndex)
{
    CT_TEL_mBm ret = TRAFFIC_DEFAULT_POWER;
    if (theIndex < TSPII_MAX_OSA_CHANELS)
    {
        ret = myOsaOutputChanPower[theIndex];
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OsaIf::GetLOS(uint32 theIndex)
{
    if (theIndex < TSPII_MAX_OSA_CHANELS)
        return myLOS[theIndex];
    else
        return myLOS[0];
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OsaIf::GetLOSHysteresis(void) const
{
    return myLOSHysteresis;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::SetLOSHysteresis(CT_TEL_mBm theValue)
{
    if ( theValue > 0 )
    {
        myLOSHysteresis = theValue;
    }
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_OsaIf::GetOpmStatus(void)
{
    return myOpmStatus;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::UpdateOpmStatusBits(void)
{
    uint32 opmStat = GetOpmStatus();

    if (opmStat & TSPII_OPM_STATUS_MASK_WAVELENGTH_RANGE)
        myWavelengthRangeInvalid = true;
    else 
        myWavelengthRangeInvalid = false;

    if (opmStat & TSPII_OPM_STATUS_MASK_UNDERFLOW)
        myUnderflowActive = true;
    else 
        myUnderflowActive = false;

    if (opmStat & TSPII_OPM_STATUS_MASK_OVERFLOW)
        myOverflowActive = true;
    else 
        myOverflowActive = false;

    if (opmStat & TSPII_OPM_STATUS_MASK_CH_SPACING)
        myCH_SpacingInvalid = true;
    else 
        myCH_SpacingInvalid = false;

    if (opmStat & TSPII_OPM_STATUS_MASK_CH_NUMBER)
        myCH_NumberInvalid = true;
    else 
        myCH_NumberInvalid = false;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OsaIf::WriteObjectBinary(FC_Stream & theStream)
{
    int i;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Availability
    theStream << myOsaPowerSupported;
    theStream << myOpmStatus;

    // Monitoring (simulation only).
    theStream << myOpmStatus;
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << myOsaChanPower[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << myOsaInputChanPower[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << myOsaChanOSNR[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << myLOS[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << myLOSThreshold[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++)
    { 
        theStream << myOsaOutputChanPower[i];
    }
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << myOsnrValid[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << myChType40G[i];

    // Configuration                                
    theStream << myItuSpacing;                            
    theStream << myItuFrequency;
    theStream << myMaxNumChannels;
    theStream << myChanPowerOffset;
    theStream << myChanPowerResolution;
    theStream << myLOSHysteresis;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_OsaIf::ReadObjectBinary(FC_Stream & theStream)
{
    int i;

    // Availability
    theStream >> myOsaPowerSupported;

    // Monitoring (simulation only).
    theStream >> myOpmStatus;
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> myOsaChanPower[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> myOsaInputChanPower[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> myOsaChanOSNR[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> myLOS[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> myLOSThreshold[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++)
    { 
        theStream >> myOsaOutputChanPower[i];
    }
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> myOsnrValid[i];
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> myChType40G[i];

    // Configuration
    theStream >> myItuSpacing;                               
    theStream >> myItuFrequency;
    theStream >> myChanPowerOffset;
    theStream >> myMaxNumChannels;
    theStream >> myChanPowerResolution;
    theStream >> myLOSHysteresis;

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_OsaIf::WriteObject(ostream & theStream)
{
    int i;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Availability
    theStream << FC_InsertVar(myOsaPowerSupported);

    // Monitoring (simulation only).
    theStream << FC_InsertVar(myOpmStatus);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << FC_InsertArrayVar(myOsaChanPower, i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << FC_InsertArrayVar(myOsaInputChanPower, i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << FC_InsertArrayVar(myOsaChanOSNR, i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << FC_InsertArrayVar(myLOS, i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << FC_InsertArrayVar(myLOSThreshold, i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++)
    { 
        theStream << FC_InsertArrayVar(myOsaOutputChanPower, i);
    }
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << FC_InsertArrayVar(myOsnrValid, i);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream << FC_InsertArrayVar(myChType40G, i);

    // Configuration                                      
    theStream << FC_InsertVar(myItuSpacing);
    theStream << FC_InsertVar(myItuFrequency);           
    theStream << FC_InsertVar(myMaxNumChannels);
    theStream << FC_InsertVar(myChanPowerOffset);
    theStream << FC_InsertVar(myChanPowerResolution);
    theStream << FC_InsertVar(myLOSHysteresis);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_OsaIf::ReadObject(istream & theStream)
{
    int i;

    // Availability
    theStream >> FC_ExtractVar(myOsaPowerSupported);

    // Monitoring (simulation only).
    theStream >> FC_ExtractVar(myOpmStatus);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> FC_ExtractVar(myOsaChanPower[i]);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> FC_ExtractVar(myOsaInputChanPower[i]);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> FC_ExtractVar(myOsaChanOSNR[i]);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> FC_ExtractVar(myLOS[i]);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> FC_ExtractVar(myLOSThreshold[i]);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++)
    { 
        theStream >> FC_ExtractVar(myOsaOutputChanPower[i]);
    }
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> FC_ExtractVar(myOsnrValid[i]);
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++) theStream >> FC_ExtractVar(myChType40G[i]);

    // Configuration
    theStream >> FC_ExtractVar(myItuSpacing);             
    theStream >> FC_ExtractVar(myItuFrequency);
    theStream >> FC_ExtractVar(myMaxNumChannels);
    theStream >> FC_ExtractVar(myChanPowerOffset);
    theStream >> FC_ExtractVar(myChanPowerResolution);
    theStream >> FC_ExtractVar(myLOSHysteresis);

    // Update H/W
    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::Display(FC_Stream & theStream)
{
    int i;
    char OutBuf[256];

    // Update H/W
    UpdateValues();
    RefreshGet();
    UpdateOpmStatusBits();

    theStream << "  OSA Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      ITU Frequency               = " << myItuFrequency << "\n";
    theStream << "      ITU Spacing                 = " << myItuSpacing << "\n";
    theStream << "      Max Number of Channels      = " << myMaxNumChannels << "\n";
    theStream << "      Channel Power Offset        = " << myChanPowerOffset << "\n";
    theStream << "      Channel Power Resolution    = " << myChanPowerResolution << "\n";
    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++)
    {
        sprintf(OutBuf, "      Chan %2d LOS Threshold       = %-5d\n", (i + 1), myLOSThreshold[i]);

        theStream << OutBuf;
    }
    theStream << "      LOS Hysteresis              = " << myLOSHysteresis << "\n";
    theStream << "    MONITORING\n";
    theStream << "      OSA Power Supported                = " << TEXT_ON_OFF(myOsaPowerSupported)   << "\n";
    theStream << "      OPM Integrity Status Byte          = ";
    sprintf(OutBuf, "0x%02x", myOpmStatus);
    theStream << OutBuf << endl;

    theStream << "        (0x10) Wavelength Range Invalid  = " << TEXT_ON_OFF(myWavelengthRangeInvalid) << "\n";
    theStream << "        (0x08) Underflow Active          = " << TEXT_ON_OFF(myUnderflowActive)   << "\n";
    theStream << "        (0x04) Overflow Active           = " << TEXT_ON_OFF(myOverflowActive)    << "\n";
    theStream << "        (0x02) Channel Spacing Invalid   = " << TEXT_ON_OFF(myCH_SpacingInvalid) << "\n";
    theStream << "        (0x01) Channel Number Invalid    = " << TEXT_ON_OFF(myCH_NumberInvalid)  << "\n\n";

    if (myOpmStatus)
    {
        theStream << "    INVALID CHANNEL POWER & OSNR\n\n";
    }

    theStream << "      Chan  Meas. Pwr  OSNR   InPower  OutPower  OSNR  40G   LOS" << endl;
    theStream << "              (mBm)    (mBm)  (mBm)     (mBm)    valid          " << endl;
    theStream << "      ----------------------------------------------------------" << endl;
              // "       xx    12345     12345  12345    12345     off   off   off" 

    for (i = 0; i < TSPII_MAX_OSA_CHANELS; i++)
    {
        sprintf(OutBuf, "       %2d    %-5d     %-5d  %-5d    %-5d     %-3.3s   %-3.3s   ",
            (i + 1), myOsaChanPower[i], myOsaChanOSNR[i], myOsaInputChanPower[i],
            myOsaOutputChanPower[i], TEXT_ON_OFF(myOsnrValid[i]), TEXT_ON_OFF(myChType40G[i]));

        theStream << OutBuf << TEXT_DEFECT(myLOS[i]) << endl; 
    }

    theStream << endl;

    TSPII_BaseIf::Display(theStream);                 
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OsaIf::Set(int argc, char ** argv)
{
    // Configuration 
    // tspii setosa <1|2|osa1|osa2> itufreq>         <0x00-0xff>
    // tspii setosa <1|2|osa1|osa2> ituspacing       <0x00-0xff>
    // tspii setosa <1|2|osa1|osa2> maxchannels      <0x00 = 0 CH>\n" 
    // tspii setosa <1|2|osa1|osa2> chpwrsoffset     <0x00 = -50dB>\n"
    // tspii setosa <1|2|osa1|osa2> xhpwrresolution  <0x00 = 0dB\n" << endl;
    // tspii setosa <1|2|osa1|osa2> sigtype <10|40|0|1>

    bool printUsage = false;
    uint32 anIndex;

    if (argc == 2 && strcmp(argv[0], "itufreq") == 0)
    {   
        uint32 ituFreq = strtoul(argv[1], NULL, 0);

        if (ituFreq <= 0xFF)
        {
            SetStartItuFrequency(ituFreq);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "ituspacing") == 0)
    {   
        uint32 ituSpacing = strtoul(argv[1], NULL, 0);

        if (ituSpacing <= 0xFF)
        {
            SetItuSpacing(ituSpacing);
        }
        else
        {
            printUsage = true;
        }
    }
        else if (argc == 2 && strcmp(argv[0], "maxchannels") == 0)
    {   
        uint32 maxchan = strtoul(argv[1], NULL, 0);

        if (maxchan <= 0xFF)
        {
            SetMaxNumChannels(maxchan);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "chpwrsoffset") == 0)
    {   
        uint32 chPowerOffset = strtoul(argv[1], NULL, 0);

        if (chPowerOffset <= 0xFF)
        {
            SetChanPowerOffset(chPowerOffset);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "chpwrresolution") == 0)
    {   
        uint32 chPowerRes = strtoul(argv[1], NULL, 0);

        if (chPowerRes <= 0xFF)
        {
            SetChanPowerResolution(chPowerRes);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "losthreshold") == 0)
    {   
        anIndex = strtoul(argv[2], NULL, 0) - 1;

        if (anIndex < TSPII_MAX_OSA_CHANELS)
        {
            SetLOSThreshold(strtoul(argv[1], NULL, 0), anIndex);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && strcmp(argv[0], "loshysteresis") == 0)
    {   
        unsigned long theValue = strtoul(argv[1], NULL, 0);
        if ( (theValue == ULONG_MAX)
        ||   (theValue == 0)
        ||   (theValue > TSPII_OSA_DEFAULT_HYSTERESIS) )
        {
            printUsage = true;
        }
        else
        {
            SetLOSHysteresis( theValue );
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Set(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    itufreq          <0x00 =   191700 GHz>\n"
                   "    ituspacing       <0x00 =   0 GHz >\n"
                   "    maxchannels      <0x00 =   0 CH  >\n" 
                   "    chpwrsoffset     <0x00 = -50 dB  >\n"
                   "    chpwrresolution  <0x00 =   0 dB  > \n"
                   "    losthreshold     <mBm> <1-" << TSPII_MAX_OSA_CHANELS <<  ">\n"
                   "    loshysteresis    <mBm> (1 <= mBm <= " << TSPII_OSA_DEFAULT_HYSTERESIS << ")\n";
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_OsaIf::Simul(int argc, char ** argv)
{
    // Monitoring 
    // tspii simosa <1|2|osa1|osa2> osapwravail      <on|off>
    // tspii simosa <1|2|osa1|osa2> wavelengthrange  <on|off>
    // tspii simosa <1|2|osa1|osa2> underflowactive  <on|off>
    // tspii simosa <1|2|osa1|osa2> overflowactive   <on|off>
    // tspii simosa <1|2|osa1|osa2> chspacinginvalid <on|off>
    // tspii simosa <1|2|osa1|osa2> chnumberinvalid  <on|off>
    // tspii simosa <1|2|osa1|osa2> opmstatus        <0x00-0x1f>
    // tspii simosa <1|2|osa1|osa2> power            <1-88 | all> <mBm>
    // tspii simosa <1|2|osa1|osa2> osnr             <1-88 | all> <dB>
    // tspii simosa <1|2|osa1|osa2> sigtype          <1-88 | all> <0=10G 1=40G>

    bool printUsage = false;
    uint32 anIndex = 1;

    if (argc == 2 && strcmp(argv[0], "osapwravail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myOsaPowerSupported = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myOsaPowerSupported = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "opmstatus") == 0)
    {   
        uint32 opmStat = strtoul(argv[1], NULL, 0);

        if (opmStat <= TSPII_OPM_STATUS_MASK)
        {
            myOpmStatus = opmStat;
            UpdateOpmStatusBits();
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "wavelengthrange") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myWavelengthRangeInvalid = true;
            myOpmStatus |= TSPII_OPM_STATUS_MASK_WAVELENGTH_RANGE;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myWavelengthRangeInvalid = false;
            myOpmStatus &= !(TSPII_OPM_STATUS_MASK_WAVELENGTH_RANGE);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "underflowactive") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myUnderflowActive = true;
            myOpmStatus |= TSPII_OPM_STATUS_MASK_UNDERFLOW;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myUnderflowActive = false;
            myOpmStatus &= !(TSPII_OPM_STATUS_MASK_UNDERFLOW);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "overflowactive") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myOverflowActive = true;
            myOpmStatus |= TSPII_OPM_STATUS_MASK_OVERFLOW;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myOverflowActive = false;
            myOpmStatus &= !(TSPII_OPM_STATUS_MASK_OVERFLOW);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 2 && strcmp(argv[0], "chspacinginvalid") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myCH_SpacingInvalid = true;
            myOpmStatus |= TSPII_OPM_STATUS_MASK_CH_SPACING;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myCH_SpacingInvalid = false;
            myOpmStatus &= !(TSPII_OPM_STATUS_MASK_CH_SPACING);
        }
        else
        {
            printUsage = true;
        }
    }    
    else if (argc == 2 && strcmp(argv[0], "chnumberinvalid") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            myCH_NumberInvalid = true;
            myOpmStatus |= TSPII_OPM_STATUS_MASK_CH_NUMBER;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            myCH_NumberInvalid = false;
            myOpmStatus &= !(TSPII_OPM_STATUS_MASK_CH_NUMBER);
        }
        else
        {
            printUsage = true;
        }
    }
    else if (argc == 3 && strcmp(argv[0], "power") == 0)
    {
        unsigned int id, endid;
        if(strcmp(argv[1], "all") == 0)
        {
            id = 0;
            endid = TSPII_MAX_OSA_CHANELS;
        }
        else
        {
            id = strtoul(argv[1], NULL, 0) - 1;
            endid = id + 1;
        }

        for( ; id < endid ; id++)
        {
            if (id < TSPII_MAX_OSA_CHANELS)
            {
                myOsaChanPower[id] = strtoul(argv[2], NULL, 0);
            }
            else
            {
                printUsage = true;
            }
        }
    }
    else if (argc == 3 && strcmp(argv[0], "inpower") == 0)
    {
        unsigned int id, endid;
        if(strcmp(argv[1], "all") == 0)
        {
            id = 0;
            endid = TSPII_MAX_OSA_CHANELS;
        }
        else
        {
            id = strtoul(argv[1], NULL, 0) - 1;
            endid = id + 1;
        }

        for( ; id < endid ; id++)
        {
            if (id < TSPII_MAX_OSA_CHANELS)
            {
                myOsaInputChanPower[id] = strtoul(argv[2], NULL, 0);
            }
            else
            {
                printUsage = true;
            }
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "los") == 0)
    {
        unsigned int endid;
        if(strcmp(argv[2], "all") == 0)
        {
            anIndex = 0;
            endid = TSPII_MAX_OSA_CHANELS;
        }
        else
        {
            anIndex = strtoul(argv[2], NULL, 0) - 1;
            endid = anIndex + 1;
        }

        for( ; anIndex < endid ; anIndex++)
        {
            if (anIndex < TSPII_MAX_OSA_CHANELS)
            {
                if (strcmp(argv[1], "on") == 0)
                {
                    if (!TSPII_DEFECT(myLOS[anIndex])) myLOS[anIndex]++;
                }
                else if (strcmp(argv[1], "off") == 0)
                {
                    if (TSPII_DEFECT(myLOS[anIndex])) myLOS[anIndex]++;
                }
                else
                {
                    printUsage = true;
                }
            }
            else
            {
                printUsage = true;
            }
        }
    }
    else if ((argc == 3) && strcmp(argv[0], "osnr") == 0)
    {
        unsigned int id, endid;
        if(strcmp(argv[1], "all") == 0)
        {
            id = 0;
            endid = TSPII_MAX_OSA_CHANELS;
        }
        else
        {
            id = strtoul(argv[1], NULL, 0) - 1;
            endid = id + 1;
        }

        for( ; id < endid ; id++)
        {
            if (id < TSPII_MAX_OSA_CHANELS)
            {
                myOsaChanOSNR[id] = strtoul(argv[2], NULL, 0);
            }
            else
            {
                printUsage = true;
            }
        }
    }
    else if (argc == 3 && strcmp(argv[0], "outpower") == 0)
    {
        unsigned int id, endid;
        if(strcmp(argv[1], "all") == 0)
        {
            id = 0;
            endid = TSPII_MAX_OSA_CHANELS;
        }
        else
        {
            id = strtoul(argv[1], NULL, 0) - 1;
            endid = id + 1;
        }

        for( ; id < endid ; id++)
        {
            if (id < TSPII_MAX_OSA_CHANELS)
            {
                myOsaOutputChanPower[id] = strtoul(argv[2], NULL, 0);
            }
            else
            {
                printUsage = true;
            }
        }
    }
    else if (argc == 3 && strcmp(argv[0], "osnrvalid") == 0)
    {
        unsigned int id, endid;
        if(strcmp(argv[1], "all") == 0)
        {
            id = 0;
            endid = TSPII_MAX_OSA_CHANELS;
        }
        else
        {
            id = strtoul(argv[1], NULL, 0) - 1;
            endid = id + 1;
        }

        for( ; id < endid ; id++)
        {
            if (id < TSPII_MAX_OSA_CHANELS)
            {
                if (strcmp(argv[2], "on") == 0)
                {
                    myOsnrValid[id] = true;
                }
                else if (strcmp(argv[2], "off") == 0)
                {
                    myOsnrValid[id] = false;
                }
                else
                {
                    printUsage = true;
                }
            }
            else
            {
                printUsage = true;
            }
        }
    }
    else if ((argc == 3) && (strcmp(argv[0], "sigtype") == 0))
    {
        unsigned int type = strtoul(argv[2], NULL, 0);
        unsigned int id, endid;
        if(strcmp(argv[1], "all") == 0)
        {
            id = 0;
            endid = TSPII_MAX_OSA_CHANELS;
        }
        else
        {
            id = strtoul(argv[1], NULL, 0) - 1;
            endid = id + 1;
        }

        for( ; id < endid ; id++)
        {
            if (id < TSPII_MAX_OSA_CHANELS)
            {
                if ( (type == 1) || (type == 40) )
                {
                    myChType40G[id] = true;
                }
                else
                {
                    myChType40G[id] = false;
                }
            }
            else
            {
                printUsage = true;
            }
        }
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }

    if (printUsage)
    {
        fc_cout << "    osapwravail      <on|off>\n"
                   "    wavelengthrange  <on|off>\n"
                   "    underflowactive  <on|off>\n"
                   "    overflowactive   <on|off>\n"
                   "    chspacinginvalid <on|off>\n"
                   "    chnumberinvalid  <on|off>\n"
                   "    osnrvalid        <1-" << TSPII_MAX_OSA_CHANELS <<  " | all> <on|off>\n"
                   "    opmstatus        <0x00-0x1f>\n" 
                   "    power            <1-" << TSPII_MAX_OSA_CHANELS <<  " | all> <mBm>\n" 
                   "    inpower          <1-" << TSPII_MAX_OSA_CHANELS <<  " | all> <mBm>\n"
                   "    outpower         <1-" << TSPII_MAX_OSA_CHANELS <<  " | all> <mBm>\n"
                   "    los              <on|off> <1-" << TSPII_MAX_OSA_CHANELS <<  " | all>\n"
                   "    osnr             <1-" << TSPII_MAX_OSA_CHANELS <<  " | all> <mBm>\n"
                   "    sigtype          <1-" << TSPII_MAX_OSA_CHANELS <<  " | all> <0=10G | 1=40G>" << endl;
    }
    return printUsage;
}                            

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    TSPII_BaseIf::Display(theStream, argc, argv);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_OsaIf::OchHistMenu(int argc, char **argv)
{
    myOchHist.Menu( argc, argv );
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm TSPII_OsaIf::Debounce(uint32 theIndex, CT_TEL_mBm thePower, CT_TEL_mBm theOsnr)
{
    myOchHist.Update( theIndex, thePower, theOsnr );
    return myOchHist.GetPower( theIndex );
}

// eof
