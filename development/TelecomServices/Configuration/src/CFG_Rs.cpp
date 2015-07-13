//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Rs.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>

static const uint16 AUTO_AISL_RS_GENERIC_PROV_MASK          = 0x0001;
static const uint16 AUTO_TLABAIS_RS_GENERIC_PROV_MASK       = 0x0002;
static const uint16 FORCE_AISL_RS_GENERIC_PROV_MASK         = 0x0004;
static const uint16 FORCE_TLABAIS_RS_GENERIC_PROV_MASK      = 0x0008;
static const uint16 INT_SIG_DISABLED_RS_GENERIC_PROV_MASK   = 0x0010;
static const uint16 EXT_SIG_DISABLED_RS_GENERIC_PROV_MASK   = 0x0020;
static const uint16 MESS_ENABLED_RS_GENERIC_PROV_MASK       = 0x0040;
static const uint16 SENT_TRACE_TRANS_RS_GENERIC_PROV_MASK   = 0x0080;
static const uint16 SDH_TRUE_RS_GENERIC_PROV_MASK           = 0x0100;
static const uint16 IGNORE_CSFLOS_CSFLOSYNC_RS_GENERIC_PROV_MASK    = 0x0200;


CFG_Rs::CFG_Rs(uint32 theIndex):
    CFG_Object(theIndex),
    myIndicationType(CT_RS_INDICATION_UNKNOWN),
    myInternalIndType(CT_RS_INDICATION_UNKNOWN),
    mySignalType (CT_TEL_SIGNAL_UNKNOWN),
    myClockType(CT_TEL_CLK_UNKNOWN),
    myCrossover(CT_TEL_DEVICENONE),
    myDevice(CT_TEL_DEVICENONE),
    mySentTrace(),
    myGenericProvisioning(0x00C1),  // Auto_AISL, Mess_Enabled, and Sent_Trace_Trans are defaulted to true
    myCBRMappingMode(NULL_MAPPING),
    myInterPacketGap(CT_TEL_DEFAULT_INTERPACKET_GAP)
{
}

CFG_Rs::~CFG_Rs(void)
{
}

bool CFG_Rs::SetSignalType(CT_TEL_SignalType theSignalType)
{
    bool hasChanged = (mySignalType != theSignalType);
    mySignalType = theSignalType;
    return hasChanged;
}


CT_TEL_SignalType CFG_Rs::GetSignalType() const
{
    return mySignalType;
}


bool CFG_Rs::SetClockType(CT_TEL_ClkType theType)
{
    bool hasChanged = (myClockType != theType);
    myClockType = theType;
    return hasChanged;
}


CT_TEL_ClkType CFG_Rs::GetClockType() const
{
    return myClockType;
}


bool CFG_Rs::SetSfpRouteAndSignalType(CT_TEL_FrontEndDevice theDevice, CT_TEL_FrontEndDevice theCrossover, CT_TEL_SignalType theSignalType, CT_TEL_ClkType theType)
{
    bool hasChanged = ((myDevice != theDevice) ||
                       (myCrossover != theCrossover) ||
                       (mySignalType != theSignalType) ||
                       (myClockType != theType) );
    myDevice     = theDevice;
    myCrossover  = theCrossover;
    mySignalType = theSignalType;
    myClockType  = theType;
    return hasChanged;
}

CT_TEL_FrontEndDevice CFG_Rs::GetCrossoverInSfpRoute() const
{
    return myCrossover;
}

CT_TEL_FrontEndDevice CFG_Rs::GetDeviceInSfpRoute() const
{
    return myDevice;
}


bool CFG_Rs::SetInternalSignalingDisabled(bool theDisable)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theDisable) 
    {
        myGenericProvisioning |= INT_SIG_DISABLED_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(INT_SIG_DISABLED_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetInternalSignalingDisabled() const
{
    bool aSet = ((myGenericProvisioning & INT_SIG_DISABLED_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}

bool CFG_Rs::SetExternalSignalingDisabled(bool theDisable)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theDisable) 
    {
        myGenericProvisioning |= EXT_SIG_DISABLED_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(EXT_SIG_DISABLED_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetExternalSignalingDisabled() const
{
    bool aSet = ((myGenericProvisioning & EXT_SIG_DISABLED_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Rs::SetForceAISL(bool theForceAISL)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceAISL) 
    {
        myGenericProvisioning |= FORCE_AISL_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(FORCE_AISL_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetForceAISL() const
{
    bool aSet = ((myGenericProvisioning & FORCE_AISL_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Rs::SetForceTlabAIS(bool theForceTlabAIS)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theForceTlabAIS) 
    {
        myGenericProvisioning |= FORCE_TLABAIS_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(FORCE_TLABAIS_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetForceTlabAIS() const
{
    bool aSet = ((myGenericProvisioning & FORCE_TLABAIS_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Rs::SetSentTrace(const CT_SDH16ByteTrace& theSentTrace)
{
    bool hasChanged = (!(mySentTrace == theSentTrace));
    mySentTrace = theSentTrace;
    return hasChanged;
}

 CT_SDH16ByteTrace CFG_Rs::GetSentTrace() const
{
    return mySentTrace;
}


bool CFG_Rs::SetAutomaticAISL(bool theAutomaticAISL)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theAutomaticAISL) 
    {
        myGenericProvisioning |= AUTO_AISL_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(AUTO_AISL_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetAutomaticAISL() const
{
    bool aSet = ((myGenericProvisioning & AUTO_AISL_RS_GENERIC_PROV_MASK) != 0);
    return aSet;

}


bool CFG_Rs::SetAutoTlabAIS(bool theAutoTlabAIS)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theAutoTlabAIS) 
    {
        myGenericProvisioning |= AUTO_TLABAIS_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(AUTO_TLABAIS_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetAutoTlabAIS() const
{
    bool aSet = ((myGenericProvisioning & AUTO_TLABAIS_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Rs::SetIndicationType(CT_RS_IndicationType theIndicationType)
{
    bool hasChanged = (myIndicationType != theIndicationType);
    myIndicationType = theIndicationType;
    return hasChanged;
}

CT_RS_IndicationType CFG_Rs::GetIndicationType() const
{
    return myIndicationType;

}

bool CFG_Rs::SetInternalIndType(CT_RS_IndicationType theIndicationType)
{
    bool hasChanged = (myInternalIndType != theIndicationType);
    myInternalIndType = theIndicationType;
    return hasChanged;
}

CT_RS_IndicationType CFG_Rs::GetInternalIndType() const
{
    return myInternalIndType;

}


bool CFG_Rs::SetSentTraceTransparent(bool theTraceTransparent)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theTraceTransparent) 
    {
        myGenericProvisioning |= SENT_TRACE_TRANS_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(SENT_TRACE_TRANS_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetSentTraceTransparent() const
{
    bool aSet = ((myGenericProvisioning & SENT_TRACE_TRANS_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Rs::SetMessagingEnabled(bool theMessagingEnabled)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theMessagingEnabled) 
    {
        myGenericProvisioning |= MESS_ENABLED_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(MESS_ENABLED_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetMessagingEnabled() const
{
    bool aSet = ((myGenericProvisioning & MESS_ENABLED_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}


bool CFG_Rs::SetSDHTrueMode(bool theSDHTrueMode)
{
    uint16 thePrevProv = myGenericProvisioning;
    if (theSDHTrueMode) 
    {
        myGenericProvisioning |= SDH_TRUE_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning &= ~(SDH_TRUE_RS_GENERIC_PROV_MASK);
    }
    return (thePrevProv != myGenericProvisioning);
}

bool CFG_Rs::GetSDHTrueMode() const
{
    bool aSet = ((myGenericProvisioning & SDH_TRUE_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}

CT_TEL_PayloadType CFG_Rs::GetCBRMappingMode() const
{
    return myCBRMappingMode;
}


bool CFG_Rs::SetCBRMappingMode(CT_TEL_PayloadType theCBRMappingMode)
{   
    bool hasChanged = (myCBRMappingMode != theCBRMappingMode);
    myCBRMappingMode = theCBRMappingMode;
    return hasChanged;
}

uint8 CFG_Rs::GetInterPacketGap() const
{
    return myInterPacketGap;
}


bool CFG_Rs::SetInterPacketGap(uint8 theInterPacketGap)
{   
    bool hasChanged = (myInterPacketGap != theInterPacketGap);
    myInterPacketGap = theInterPacketGap;
    return hasChanged;
}

bool CFG_Rs::SetIgnoreCsfLosCsfLosyncFlag(bool theIgnoreFlag)
{
    uint16 prevProv = myGenericProvisioning;

    if (theIgnoreFlag) 
    {
        myGenericProvisioning  |= IGNORE_CSFLOS_CSFLOSYNC_RS_GENERIC_PROV_MASK;
    }
    else
    {
        myGenericProvisioning  &= ~(IGNORE_CSFLOS_CSFLOSYNC_RS_GENERIC_PROV_MASK);
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

bool CFG_Rs::GetIgnoreCsfLosCsfLosyncFlag() const
{
    bool aSet = ((myGenericProvisioning & IGNORE_CSFLOS_CSFLOSYNC_RS_GENERIC_PROV_MASK) != 0);
    return aSet;
}


void CFG_Rs::Reset(void)
{
    // Initialize all attributes to default values.
    mySentTrace     = CT_SDH16ByteTrace();
    myIndicationType= CT_RS_INDICATION_UNKNOWN;
    myInternalIndType= CT_RS_INDICATION_UNKNOWN;
    mySignalType    = CT_TEL_SIGNAL_UNKNOWN;
    myClockType     = CT_TEL_CLK_UNKNOWN;
    myCrossover     = CT_TEL_DEVICENONE;
    myDevice        = CT_TEL_DEVICENONE;
    myGenericProvisioning  = 0x00C1;
    myCBRMappingMode       = NULL_MAPPING;
    myInterPacketGap = CT_TEL_DEFAULT_INTERPACKET_GAP;
}

ostream& CFG_Rs::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    uint32 aSignalType = mySignalType;
    theStream   << FC_InsertVar(aSignalType);
    theStream   << FC_InsertVar(mySentTrace);
    theStream   << FC_InsertVar(myGenericProvisioning);

    uint32 aCBRMappingMode = myCBRMappingMode;
    theStream   << FC_InsertVar(aCBRMappingMode);

    uint8  aCrossover = (uint8) myCrossover;
    theStream   << FC_InsertVar(aCrossover);
    uint8  aDev = (uint8) myDevice;
    theStream   << FC_InsertVar(aDev);
    uint8 aClockType = (uint8) myClockType;
    theStream   << FC_InsertVar(aClockType);
    uint8 aIndicationType = (uint8) myIndicationType;
    theStream   << FC_InsertVar(aIndicationType);
    uint8 aInternalIndType = (uint8) myInternalIndType;
    theStream   << FC_InsertVar(aInternalIndType);
    theStream   << FC_InsertVar(myInterPacketGap);

    return theStream;

}

istream& CFG_Rs::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint32 aSignalType = 0;
    theStream   >> FC_ExtractVar(aSignalType);
    mySignalType = (CT_TEL_SignalType) aSignalType;
    theStream   >> FC_ExtractVar(mySentTrace);
    theStream   >> FC_ExtractVar(myGenericProvisioning);

    uint32 aCBRMappingMode = 0;
    theStream   >> FC_ExtractVar(aCBRMappingMode);
    myCBRMappingMode = (CT_TEL_PayloadType) aCBRMappingMode;

    uint8  aCrossover = 0;
    theStream   >> FC_ExtractVar(aCrossover);
    myCrossover = (CT_TEL_FrontEndDevice) aCrossover;
    uint8  aDev = 0;
    theStream   >> FC_ExtractVar(aDev);
    myDevice = (CT_TEL_FrontEndDevice) aDev;

    uint8 aClockType = 0;
    theStream   >> FC_ExtractVar(aClockType);
    myClockType = (CT_TEL_ClkType) aClockType;
    uint8 aIndicationType = 0;
    theStream   >> FC_ExtractVar(aIndicationType);
    myIndicationType = (CT_RS_IndicationType) aIndicationType;
    uint8 aInternalIndType = 0;
    theStream   >> FC_ExtractVar(aInternalIndType);
    myInternalIndType = (CT_RS_IndicationType) aInternalIndType;
    theStream   >> FC_ExtractVar(myInterPacketGap);

    return theStream;

}

FC_Stream& CFG_Rs::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << (uint32)mySignalType;

    theStream   << mySentTrace;;
    theStream   << myGenericProvisioning;
    theStream   << (uint32)myCBRMappingMode;

    theStream   << (uint8) myCrossover;
    theStream   << (uint8) myDevice;
    theStream   << (uint8) myClockType;
    theStream   << (uint8) myIndicationType;
    theStream   << (uint8) myInternalIndType;
    theStream   << myInterPacketGap;

    return theStream;

}

FC_Stream& CFG_Rs::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint32 aSignalType = 0;
    theStream   >> aSignalType;
    mySignalType = (CT_TEL_SignalType)aSignalType;

    theStream   >> mySentTrace;
    theStream   >> myGenericProvisioning;

    uint32 aCBRMappingMode = 0;
    theStream   >> aCBRMappingMode;
    myCBRMappingMode = (CT_TEL_PayloadType)aCBRMappingMode;

    uint8 aCrossover = 0;
    theStream >> aCrossover;
    myCrossover = (CT_TEL_FrontEndDevice)aCrossover;
    uint8 aDev = 0;
    theStream >> aDev;
    myDevice = (CT_TEL_FrontEndDevice)aDev;

    uint8 aClockType = 0;
    theStream   >> aClockType;
    myClockType = (CT_TEL_ClkType) aClockType;
    uint8 aIndicationType = 0;
    theStream   >> aIndicationType;
    myIndicationType = (CT_RS_IndicationType) aIndicationType;
    uint8 aInternalIndType = 0;
    theStream   >> aInternalIndType;
    myInternalIndType = (CT_RS_IndicationType) aInternalIndType;
    theStream   >> myInterPacketGap;


    return theStream;

}

FC_CmdProcessor::STATUS CFG_Rs::Set(int argc, char **argv)
{
    int  aMaxBufLen = 31;
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto RSERROR;

    //Copy arguments
    int aArgLen;
    aArgLen = strlen(argv[0]);
    if (aArgLen > aMaxBufLen)
    {
        aArgLen = aMaxBufLen;
        fc_cout << "WARNING: argument length exceeds buffer size, only " << aMaxBufLen << " chars will be used." << endl;
    }
    strncpy(aParam, argv[0], aArgLen);
    aParam[aArgLen] = '\0';

    if (!strncmp(aParam,"disin",5))
    {
        SetInternalSignalingDisabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"disex",5))
    {
        SetExternalSignalingDisabled(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"aisgen"))
    {
        SetForceAISL(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"tlabai",6))
    {
        SetForceTlabAIS(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"autoais"))
    {
        SetAutomaticAISL(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"autotl",6))
    {
        SetAutoTlabAIS(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"tracetrans"))
    {
        SetSentTraceTransparent(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"mess",4))
    {
        SetMessagingEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"truesdh",7))
    {
        SetSDHTrueMode(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"trace"))
    {
        string aMessage(argv[1]);
        CT_SDH16ByteTrace aTrace(aMessage);
        SetSentTrace(aTrace);
    }
    else if (!strcmp(aParam,"sigtype"))
    {
        SetSignalType(CFG_STRING_TO_SIGNAL_TYPE(argv[1]));
    }
    else if (!strncmp(aParam,"clk",3))
    {
        SetClockType(CFG_STRING_TO_CLOCK_TYPE(argv[1]));
    }
    else if (!strncmp(aParam,"indi",4))
    {
        int i;
        CT_RS_IndicationType anIndi;
        bool printUsage = true;
        for (i = 0; i < CT_RS_INDICATION_NONE; i++)
        {
            if (strcmp(argv[1], DISPLAY_RS_INDICATION(i)) == 0)
            {
                anIndi     = (CT_RS_IndicationType)i;
                printUsage = false;
                break;
            }
        }
        // Check to make sure each argument is valid
        if (printUsage)
        {
            goto RSERROR;
        }
        else
        {
            SetIndicationType(CT_RS_IndicationType(anIndi));
        }
    }
    else if (!strncmp(aParam,"inter",5))
    {
        int i;
        CT_RS_IndicationType anIndi;
        bool printUsage = true;
        for (i = 0; i < CT_RS_INDICATION_NONE; i++)
        {
            if (strcmp(argv[1], DISPLAY_RS_INDICATION(i)) == 0)
            {
                anIndi     = (CT_RS_IndicationType)i;
                printUsage = false;
                break;
            }
        }
        // Check to make sure each argument is valid
        if (printUsage)
        {
            goto RSERROR;
        }
        else
        {
            SetInternalIndType(CT_RS_IndicationType(anIndi));
        }
    }
    else if (!strncmp(aParam,"sfp",3))
    {
        if(argc == 4)
        {
            CT_TEL_FrontEndDevice aDevice, aCrossover;
            aDevice    = CFG_STRING_TO_DEV(argv[1]);
            aCrossover = CFG_STRING_TO_DEV(argv[2]);

            // Check to make sure each argument is valid
            if ((aDevice    == CT_TEL_END_DEVICES) ||
                (aCrossover == CT_TEL_END_DEVICES))
            {
                goto RSERROR;
            }
            else
            {
                SetSfpRouteAndSignalType(aDevice, aCrossover, CFG_STRING_TO_SIGNAL_TYPE(argv[3]));
            }
        }
    }
    else if (!strncmp(aParam,"ssmsfp",6))
    {
        if(argc == 3)
        {
            CT_TEL_SsmFrontEndDevice aDevice;
            aDevice    = CFG_STRING_TO_SSM_DEV(argv[1]);

            // Check to make sure each argument is valid
            if (aDevice == CT_TEL_SSM_END_DEVICES)
            {
                goto RSERROR;
            }
            else
            {
                SetSfpRouteAndSignalType(CT_TEL_FrontEndDevice(aDevice), CT_TEL_DEVICENONE, CFG_STRING_TO_SIGNAL_TYPE(argv[2]));
            }
        }
    }
    else if (!strncmp(aParam,"ssm40",5)) 
    {
        if (argc == 3) 
        {
            int i;
            CT_TEL_Ssm40FrontEndDevice aDevice;
            bool printUsage = true;
            for (i = 0; i < CT_TEL_SSM40_END_DEV; i++)
            {
                if (strcmp(argv[1], DISPLAY_SSM40_DEV(i)) == 0)
                {
                    aDevice    = (CT_TEL_Ssm40FrontEndDevice)i;
                    printUsage = false;
                    break;
                }
            }
            // Check to make sure each argument is valid
            if (printUsage)
            {
                goto RSERROR;
            }
            else
            {
                SetSfpRouteAndSignalType(CT_TEL_FrontEndDevice(aDevice), CT_TEL_DEVICENONE, CFG_STRING_TO_SIGNAL_TYPE(argv[2]),myClockType);
            }

        }
        
    }
    else if (!strcmp(aParam,"cbrmapping"))
    {
        SetCBRMappingMode(CFG_STRING_TO_CBRMAP(argv[1]));
    }
    else if (!strncmp(aParam,"ipg",3))
    {
        SetInterPacketGap(uint8(atoi(argv[1])));
    }
    else
    {
        goto RSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

RSERROR:
    {
        fc_cout << "rs <aisgen | autoais | tlabaisgen | autotlabais> <e-nable|d-isable> " << endl;
        fc_cout << "rs <tracetrans | messaging | truesdh>            <e-nable|d-isable> " << endl;
        fc_cout << "rs <trace>        <15-byte message>" << endl;
        fc_cout << "rs <cbrmapping>   <sync|async> " << endl;
        fc_cout << "rs <ipg>   <8-12> " << endl;
        fc_cout << "rs <sigtype>  <oc3|oc12|oc48|oc192|oc768|10b8b|e1|stm1|stm4|stm16|stm64|stm256|" << endl;
        fc_cout << "               gbep|tgbep|tglan|tglf|tglp|tglwfs|tglfstd|escon|ficon|ficon2g|" << endl;
        fc_cout << "               fc|fc1g|fc2g|fc4g|fc10g|fc266m|fc531m|fc133m|100bfx|d1v" << endl;
        fc_cout << "               dvbasi|isc|isc2g|vcg|dv6000|sdi|hdsdi|3gsdi|vs411|vs811| >" << endl;
        fc_cout << "               odu0|odu1|odu2|odu3|otu1|otu2|otu3|otu3e2|otu4|fge|hge| >" << endl;
        fc_cout << "               otu_tglwfs|otu_tglwofs|eth|eth10|eth100|eth1000|gopt|ochp >" << endl;
        fc_cout << "rs <clk-type> <g709 | ovr_fs | ovr_nofs | ovr_fc | odu3 | odu3e2 | unknown>"  << endl;
        fc_cout << "rs <sfpandsigtype> (Note: Enter all three fields on single line) " << endl;
        fc_cout << "                   <device: dev0-dev10|4gdev1|4gdev2> " << endl;
        fc_cout << "                   <crossover: dev0|crossa1|crossa2|crossb1|crossb2>"  << endl;
        fc_cout << "                   <sigtype: see possible entries above> " << endl;
        fc_cout << "rs <ssmsfpsig>     (Note: Enter both fields on single line & only on SSM) " << endl;
        fc_cout << "                   <device: dev0-dev12|10gdev13|sdev1-sdev10|s10gdev11>" << endl;
        fc_cout << "                   <sigtype: see possible entries above> " << endl;
        fc_cout << "rs <ssm40-sfpsig>  (Note: Enter both fields on single line & only on SSM40) " << endl;
        DisplayDevices();
        fc_cout << "                   <sigtype: see possible entries above> " << endl;
        fc_cout << "rs <disex-ternal | disin-ternal>      <e-nable|d-isable> " << endl;
        fc_cout << "rs <indi-cation>  ";
        DisplayIndications();
        fc_cout << endl;
        fc_cout << "rs <inter-nalind> <indication: see possible entries above>";
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Rs::Display( FC_Stream& theStream )
{
    theStream   << "RS       - Signal Type          [sigtype]     = " << DISPLAY_SIGNAL_TYPE(mySignalType) << endl;
    theStream   << "RS       - Clock Type           [clocktype]   = " << DISPLAY_CLOCK_TYPE(myClockType) << endl;
    theStream   << "RS       - Crossover            [crossover]   = " << DISPLAY_DEV(myCrossover) << endl;
    theStream   << "RS       - SFP Device           [sfpdev]      = " << DISPLAY_DEV(myDevice) << endl;
    theStream   << "RS       - SFP Device (SSM)     [sfpdev]      = " << DISPLAY_SSM_DEV(myDevice) << endl;
    theStream   << "RS       - SFP Device (SSM40)   [sfpdev]      = " << DISPLAY_SSM40_DEV(myDevice) << endl;
    theStream   << "RS       - SFP Device (OSM20)   [sfpdev]      = " << DISPLAY_HYPHYFLEX_DEV(myDevice) << endl;
    theStream   << "RS       - Disable External Sig [disexternal] = " << DISPLAY_BOOL(GetExternalSignalingDisabled())  << endl;
    theStream   << "RS       - Disable Internal Sig [disinternal] = " << DISPLAY_BOOL(GetInternalSignalingDisabled())  << endl;
    theStream   << "RS       - Indication Type      [indication]  = " << DISPLAY_RS_INDICATION(myIndicationType) << endl;
    theStream   << "RS       - Internal Indication  [internalind] = " << DISPLAY_RS_INDICATION(myInternalIndType) << endl;
    theStream   << "RS       - Force AIS-L          [aisgen]      = " << DISPLAY_BOOL(GetForceAISL()) << endl;
    theStream   << "RS       - Force TLAB AIS       [tlabaisgen]  = " << DISPLAY_BOOL(GetForceTlabAIS()) << endl;
    theStream   << "RS       - Automatic AIS-L      [autoais]     = " << DISPLAY_BOOL(GetAutomaticAISL()) << endl;
    theStream   << "RS       - Automatic TLAB AIS   [autotlabais] = " << DISPLAY_BOOL(GetAutoTlabAIS()) << endl;
    theStream   << "RS       - Tx Trace Transparent [tracetrans]  = " << DISPLAY_BOOL(GetSentTraceTransparent()) << endl;
    theStream   << "RS       - Messaging Enabled    [messaging]   = " << DISPLAY_BOOL(GetMessagingEnabled()) << endl;
    theStream   << "RS       - True SDH Enabled     [truesdh]     = " << DISPLAY_BOOL(GetSDHTrueMode()) << endl;
    theStream   << "RS       - Ignore CsfLos&Losync [igncsf]      = " << DISPLAY_BOOL(GetIgnoreCsfLosCsfLosyncFlag()) << endl;
    theStream   << "RS       - CBR Mapping Mode     [cbrmapping]  = " << DISPLAY_PAYLOAD_TYPE(myCBRMappingMode) << endl;
    theStream   << "RS       - InterPacket Gap      [ipg]         = " << dec << (uint32)myInterPacketGap << dec << endl;
    theStream   << "RS       - Transmitted Trace    [trace]       = " ;
    mySentTrace.Display(theStream);
}


bool CFG_Rs::IsPayloadTypeSONETSDH(CT_TEL_SignalType theSignalType)
{
    switch (theSignalType)
    {
    case CT_TEL_SIGNAL_OC3:
    case CT_TEL_SIGNAL_OC12:
    case CT_TEL_SIGNAL_OC48:
    case CT_TEL_SIGNAL_OC192:
    case CT_TEL_SIGNAL_OC768:
    case CT_TEL_SIGNAL_STM1:
    case CT_TEL_SIGNAL_STM4:
    case CT_TEL_SIGNAL_STM16:
    case CT_TEL_SIGNAL_STM64:
    case CT_TEL_SIGNAL_STM256:
    case CT_TEL_SIGNAL_TGBEP:
        return true;
    default:
        return false;
    }
}

bool CFG_Rs::IsSignalTypeOTN(CT_TEL_SignalType theSignalType)
{
    switch (theSignalType)
    {
    case CT_TEL_SIGNAL_ODU1:
    case CT_TEL_SIGNAL_ODU2:
    case CT_TEL_SIGNAL_ODU3:
    case CT_TEL_SIGNAL_OTU1:
    case CT_TEL_SIGNAL_OTU2:
    case CT_TEL_SIGNAL_OTU3:
    case CT_TEL_SIGNAL_OTU_TGLAN_WFS:
    case CT_TEL_SIGNAL_OTU_TGLAN_WOFS:
    case CT_TEL_SIGNAL_OTU_TGFC_WOFS:
    case CT_TEL_SIGNAL_OTU3e2:
    case CT_TEL_SIGNAL_OCH_P:
    case CT_TEL_SIGNAL_OTU4:
        return true;
    default:
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
void CFG_Rs::DisplayDevices()
{
    int devType;

    fc_cout << "                   <device: ";
    for(devType = (int) CT_TEL_SSM40_DEVNONE; devType < (int) CT_TEL_SSM40_END_DEV; devType++)
    {
        fc_cout << DISPLAY_SSM40_DEV((CT_TEL_Ssm40FrontEndDevice)devType) << "|";
    }

    fc_cout << ">\n";
}

///////////////////////////////////////////////////////////////////////////////
void CFG_Rs::DisplayIndications()
{
    int indType;

    fc_cout << "<";
    for(indType = (int) CT_RS_INDICATION_AIS; indType < (int) CT_RS_INDICATION_NONE; indType++)
    {
        fc_cout << DISPLAY_RS_INDICATION((CT_RS_IndicationType)indType) << "|";
    }

    fc_cout << ">";
}