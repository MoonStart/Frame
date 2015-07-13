//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Hop.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_Hop::CFG_Hop(uint32 theIndex):
    CFG_Object(theIndex),
    myForceAISP(false),
    myForceUNEQ(false),
    mySpeMapping(CT_TEL_HOP_MAPPING_UNKNOWN),
    myPMProfileId(CT_PM_PT_99),
    mySendTraceFlag(false),
    mySdBerLevel(CT_TEL_INFINITE_BER),
    mySfBerLevel(CT_TEL_INFINITE_BER),
    myExpectedC2(0),
    myPointerJustEnabled(false)
{
    mySentTrace = CT_SONET64ByteTrace();
}

CFG_Hop::~CFG_Hop(void)
{
}

void CFG_Hop::SetSpeMapping(CT_TEL_HopSpeMapping theMapping)
{
    mySpeMapping = theMapping;
}

CT_TEL_HopSpeMapping CFG_Hop::GetSpeMapping() const
{
    return mySpeMapping;
}

void CFG_Hop::SetPMProfileId(CT_PMProfileTableId thePMPFId)
{
    myPMProfileId = thePMPFId;
}

CT_PMProfileTableId CFG_Hop::GetPMProfileId() const
{
    return myPMProfileId;
}

void CFG_Hop::SetSentTrace(const CT_SONET64ByteTrace& theSentTrace)
{
    mySentTrace = theSentTrace;
}

const CT_SONET64ByteTrace& CFG_Hop::GetSentTrace() const
{
    return mySentTrace;
}

void CFG_Hop::SetSendTraceFlag(bool theSendTraceFlag)
{
    mySendTraceFlag = theSendTraceFlag;
}

bool CFG_Hop::GetSendTraceFlag() const
{
    return mySendTraceFlag;
}

void CFG_Hop::SetForceAISP(bool theForceAISP)
{
    myForceAISP = theForceAISP;
}

bool CFG_Hop::GetForceAISP() const
{
    return myForceAISP;
}

void CFG_Hop::SetForceUNEQ(bool theForceUNEQ)
{
    myForceUNEQ = theForceUNEQ;
}

bool CFG_Hop::GetForceUNEQ() const
{
    return myForceUNEQ;
}

// Add in Monitoring Configurations also
void CFG_Hop::SetBerSdThreshold(CT_TEL_BERLevels theSdBerThreshold)
{
    mySdBerLevel = theSdBerThreshold;
}

CT_TEL_BERLevels CFG_Hop::GetBerSdThreshold() const
{
    return mySdBerLevel;
}

void CFG_Hop::SetBerSfThreshold(CT_TEL_BERLevels theSfBerThreshold)
{
    mySfBerLevel = theSfBerThreshold;
}

CT_TEL_BERLevels CFG_Hop::GetBerSfThreshold() const
{
    return mySfBerLevel;
}


void CFG_Hop::SetExpectedC2(uint8 theC2)
{
    myExpectedC2 = theC2;
}

uint8 CFG_Hop::GetExpectedC2() const
{
    return myExpectedC2;
}


void CFG_Hop::SetPointerJustEnabled(bool thePointerJustEnabled)
{
    myPointerJustEnabled = thePointerJustEnabled;
}

bool CFG_Hop::GetPointerJustEnabled() const
{
    return myPointerJustEnabled;
}


void CFG_Hop::Reset(void)
{
    // Initialize all attributes to default values.
    mySpeMapping = CT_TEL_HOP_MAPPING_UNKNOWN;
    myPMProfileId = CT_PM_PT_99;
    myForceAISP = false;
    myForceUNEQ = false;
    mySentTrace = CT_SONET64ByteTrace();
    mySendTraceFlag = false;
    mySdBerLevel = CT_TEL_INFINITE_BER;
    mySfBerLevel = CT_TEL_INFINITE_BER;
    myExpectedC2 = 0;
    myPointerJustEnabled = false;
}

ostream& CFG_Hop::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    uint8 aSpeMapping = (uint8) mySpeMapping;
    uint8 aPMProfileId = (uint8) myPMProfileId;

    theStream   << FC_InsertVar(aSpeMapping);
    theStream   << FC_InsertVar(aPMProfileId);
    theStream   << FC_InsertVar(myForceAISP);
    theStream   << FC_InsertVar(myForceUNEQ);
    theStream   << FC_InsertVar(mySendTraceFlag);
    //theStream   << FC_InsertVar(mySentTrace);

    uint8 aSdBerLevel = (uint8) mySdBerLevel;
    uint8 aSfBerLevel = (uint8) mySfBerLevel;
    theStream << FC_InsertVar(aSdBerLevel);
    theStream << FC_InsertVar(aSfBerLevel);
    theStream << FC_InsertVar(myExpectedC2);

    return theStream;
}

istream& CFG_Hop::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    uint8 aSpeMapping = 0;
    uint8 aPMProfileId = 0;

    theStream   >> FC_ExtractVar(aSpeMapping);
    mySpeMapping = (CT_TEL_HopSpeMapping) aSpeMapping;
    theStream   >> FC_ExtractVar(aPMProfileId);
    myPMProfileId = (CT_PMProfileTableId) aPMProfileId;
    theStream   >> FC_ExtractVar(myForceAISP);
    theStream   >> FC_ExtractVar(myForceUNEQ);
    theStream   >> FC_ExtractVar(mySendTraceFlag);
    //theStream   >> FC_ExtractVar(mySentTrace);

    uint8 aSdBerLevel;
    uint8 aSfBerLevel;
    theStream >> FC_ExtractVar(aSdBerLevel);
    theStream >> FC_ExtractVar(aSfBerLevel);
    mySdBerLevel = (CT_TEL_BERLevels) aSdBerLevel;
    mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    theStream >> FC_ExtractVar(myExpectedC2);

    return theStream;
}

FC_Stream& CFG_Hop::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    uint8 aSpeMapping = (uint8) mySpeMapping;
    uint8 aPMProfileId = (uint8) myPMProfileId;

    theStream   << aSpeMapping;
    theStream   << aPMProfileId;
    theStream   << myForceAISP;
    theStream   << myForceUNEQ;
    theStream   << mySendTraceFlag;
    //theStream   << mySentTrace;

    uint8 aSdBerLevel = (uint8) mySdBerLevel;
    uint8 aSfBerLevel = (uint8) mySfBerLevel;
    theStream << aSdBerLevel;
    theStream << aSfBerLevel;
    theStream << myExpectedC2;

    return theStream;
}

FC_Stream& CFG_Hop::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    uint8 aSpeMapping = 0;
    uint8 aPMProfileId = 0;

    theStream   >> aSpeMapping;
    mySpeMapping = (CT_TEL_HopSpeMapping)aSpeMapping;
    theStream   >> aPMProfileId;
    myPMProfileId = (CT_PMProfileTableId)aPMProfileId;

    theStream   >> myForceAISP;
    theStream   >> myForceUNEQ;
    theStream   >> mySendTraceFlag;
    //theStream   >> mySentTrace;

    uint8 aSdBerLevel;
    uint8 aSfBerLevel;
    theStream >> aSdBerLevel;
    theStream >> aSfBerLevel;
    mySdBerLevel = (CT_TEL_BERLevels) aSdBerLevel;
    mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    theStream >> myExpectedC2;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Hop::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto HOPERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"aisgen"))
    {
        SetForceAISP(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"uneqgen"))
    {
        SetForceUNEQ(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"tracegen"))
    {
        SetSendTraceFlag(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"trace"))
    {
        string aMessage(argv[1]);
        CT_SONET64ByteTrace aTrace(aMessage);
        SetSentTrace(aTrace);
    }
    else if (!strcmp(aParam,"spemap"))
    {
        SetSpeMapping(CFG_STRING_TO_HOP_SPE_MAPPING(argv[1]));
    }
    else if (!strcmp(argv[0],"sdber"))
    {
        SetBerSdThreshold(CFG_STRING_TO_BER(argv[1]));
    }
    else if (!strcmp(argv[0],"sfber"))
    {
        SetBerSfThreshold(CFG_STRING_TO_BER(argv[1]));
    }
    else if (!strcmp(argv[0],"expC2"))
    {
        SetExpectedC2(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"ptr",3))
    {
        SetPointerJustEnabled(argv[1][0]=='e');
    }
    else
    {
        goto HOPERROR;
    }


    return FC_CmdProcessor::E_SUCCESS;

HOPERROR:
    {
        fc_cout << "hop <aisgen|uneqgen|tracegen|ptrjust> <e-nable|d-isable> " << endl;
        fc_cout << "hop <trace> <62-byte message>" << endl;
        fc_cout << "hop <spemap> <sts1|sts3c|sts12c|sts48c|sts192c|sts3t|sts12t|sts48t|sts1c22v|concat>" << endl;
        fc_cout << "hop <sdber> <Numeric value range 3 .. 12 inclusive> " << endl;
        fc_cout << "hop <sfber> <Numeric value range 3 .. 12 inclusive> " << endl;
        fc_cout << "hop <expC2> <1 byte integer>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Hop::Display( FC_Stream& theStream )
{
    theStream   << "HOP      - SPE Mapping          [spemap]    = " << DISPLAY_HOP_SPE_MAPPING(mySpeMapping) << endl;
    theStream   << "HOP      - Force AIS-P          [aisgen]    = " << DISPLAY_BOOL(myForceAISP) << endl;
    theStream   << "HOP      - Force UNEQ-P         [uneqgen]   = " << DISPLAY_BOOL(myForceUNEQ) << endl;
    theStream   << "HOP      - SD BER Threshold     [sdber]     = " << DISPLAY_BER(mySdBerLevel) << endl;
    theStream   << "HOP      - SF BER Threshold     [sfber]     = " << DISPLAY_BER(mySfBerLevel) << endl;
    theStream   << "HOP      - Expected C2          [expC2]     = " << uint(myExpectedC2) << endl;
    theStream   << "HOP      - Pointer Just Enabled [ptrjust]   = " << DISPLAY_BOOL(myPointerJustEnabled) << endl;
    theStream   << "HOP      - Send Trace           [tracegen]  = " << DISPLAY_BOOL(mySendTraceFlag) << endl;
    theStream   << "HOP      - Transmitted Trace    [trace]     = " ;
    mySentTrace.Display(theStream);
}

