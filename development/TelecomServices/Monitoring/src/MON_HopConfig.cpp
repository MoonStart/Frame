//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_HopConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_HopConfig::MON_HopConfig(uint32 theIndex):
    MON_Config(theIndex),
    //mySdBerLevel(CT_TEL_INFINITE_BER),
    //mySfBerLevel(CT_TEL_INFINITE_BER),
    //myExpectedC2(0),
    myExpectedTrace(),
    myTIMMonitoringEnable(false),
    myIsConnectedAsSrc(false),
    myIsConnectedAsDst(false)
{
    // ?? Should set Default for Expected Trace ??
    // myExpectedTrace = CT_SONET64ByteTrace();
}

MON_HopConfig::~MON_HopConfig()
{
}

void MON_HopConfig::Reset(void)
{
    MON_Config::Reset();
    //mySdBerLevel = CT_TEL_INFINITE_BER;
    //mySfBerLevel = CT_TEL_INFINITE_BER;
    //myExpectedC2 = 0;
    myExpectedTrace = CT_SONET64ByteTrace();
    myTIMMonitoringEnable = false;
    myIsConnectedAsSrc = false;
    myIsConnectedAsDst = false;
}

/////////////////////////////////////////////////////////////////////
// MON Config parameters (that are written to TSPII) moved to CFG for
// perfomance reasons.
// Calls included BER SF Theshold, BER SD Threhhold, and Expected C2.
#if 0
void MON_HopConfig::SetBerSdThreshold(CT_TEL_BERLevels theSdBerThreshold)
{
    mySdBerLevel = theSdBerThreshold;
}

CT_TEL_BERLevels MON_HopConfig::GetBerSdThreshold() const
{
    return mySdBerLevel;
}

void MON_HopConfig::SetBerSfThreshold(CT_TEL_BERLevels theSfBerThreshold)
{
    mySfBerLevel = theSfBerThreshold;
}

CT_TEL_BERLevels MON_HopConfig::GetBerSfThreshold() const
{
    return mySfBerLevel;
}


void MON_HopConfig::SetExpectedC2(uint8 theC2)
{
    myExpectedC2 = theC2;
}

uint8 MON_HopConfig::GetExpectedC2() const
{
    return myExpectedC2;
}
#endif
/////////////////////////////////////////////////////////////////////



void MON_HopConfig::SetExpectedTrace(const CT_SONET64ByteTrace& theTrace)
{
    myExpectedTrace = theTrace;
}

const CT_SONET64ByteTrace MON_HopConfig::GetExpectedTrace() const
{
    return myExpectedTrace;
}

void MON_HopConfig::SetTIMMonitoringEnable(bool theTIMMonitoringState)
{
    myTIMMonitoringEnable = theTIMMonitoringState;
}

bool MON_HopConfig::GetTIMMonitoringEnable() const
{
    return myTIMMonitoringEnable;
}


bool MON_HopConfig::SetIsConnectedAsSrc(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsSrc != theState)
    {
        myIsConnectedAsSrc = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_HopConfig::GetIsConnectedAsSrc() const
{
    return myIsConnectedAsSrc;
}

bool MON_HopConfig::SetIsConnectedAsDst(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsDst != theState)
    {
        myIsConnectedAsDst = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_HopConfig::GetIsConnectedAsDst() const
{
    return myIsConnectedAsDst;
}


ostream& MON_HopConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    //uint8 aSdBerLevel = (uint32) mySdBerLevel;
    //uint8 aSfBerLevel = (uint32) mySfBerLevel;
    //theStream << FC_InsertVar(aSdBerLevel);
    //theStream << FC_InsertVar(aSfBerLevel);
    //theStream << FC_InsertVar(myExpectedC2);

    //theStream << FC_InsertVar(myExpectedTrace);
    //theStream << FC_InsertVar(myTIMMonitoringEnable);

    theStream << FC_InsertVar(myIsConnectedAsSrc);
    theStream << FC_InsertVar(myIsConnectedAsDst);
    return theStream;
}

istream& MON_HopConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    //uint8 aSdBerLevel;
    //uint8 aSfBerLevel;
    //theStream >> FC_ExtractVar(aSdBerLevel);
    //theStream >> FC_ExtractVar(aSfBerLevel);
    //mySdBerLevel = (CT_TEL_BERLevels) aSdBerLevel;
    //mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    //theStream >> FC_ExtractVar(myExpectedC2);

    //theStream >> FC_ExtractVar(myExpectedTrace);
    //theStream >> FC_ExtractVar(myTIMMonitoringEnable);

    theStream >> FC_ExtractVar(myIsConnectedAsSrc);
    theStream >> FC_ExtractVar(myIsConnectedAsDst);
    return theStream;
}

FC_Stream& MON_HopConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    //uint8 aSdBerLevel = (uint32) mySdBerLevel;
    //uint8 aSfBerLevel = (uint32) mySfBerLevel;
    //theStream << aSdBerLevel;
    //theStream << aSfBerLevel;
    //theStream << myExpectedC2;

    //theStream << myExpectedTrace;
    //theStream << myTIMMonitoringEnable;

    theStream << myIsConnectedAsSrc;
    theStream << myIsConnectedAsDst;
    return theStream;
}

FC_Stream& MON_HopConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    //uint8 aSdBerLevel;
    //uint8 aSfBerLevel;
    //theStream >> aSdBerLevel;
    //theStream >> aSfBerLevel;
    //mySdBerLevel = (CT_TEL_BERLevels) aSdBerLevel;
    //mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    //theStream >> myExpectedC2;

    //theStream >> myExpectedTrace;
    //theStream >> myTIMMonitoringEnable;
    //
    theStream >> myIsConnectedAsSrc;
    theStream >> myIsConnectedAsDst;
    return theStream;
}

void MON_HopConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    //theStream   << "HOP     - SD BER Threshold      [sdber]     = " << DISPLAY_BER(mySdBerLevel) << endl;
    //theStream   << "HOP     - SF BER Threshold      [sfber]     = " << DISPLAY_BER(mySfBerLevel) << endl;
    //theStream   << "HOP     - Expected C2           [expC2]     = " << uint(myExpectedC2) << endl;
    theStream   << "HOP     - Is Connected As Src   [src]       = " << DISPLAY_BOOL(myIsConnectedAsSrc) << endl;
    theStream   << "HOP     - Is Connected As Dst   [dst]       = " << DISPLAY_BOOL(myIsConnectedAsDst) << endl;
    // Path Trace Monitoring is not supported at this time
    //theStream   << "HOP     - TIM Monitoring        [tim]       = " << DISPLAY_BOOL(myTIMMonitoringEnable) << endl;
    //theStream   << "HOP     - Expected Trace        [trace]     = " ;
    //myExpectedTrace.Display(theStream);
}

FC_CmdProcessor::STATUS MON_HopConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto HOPERROR;

// NOTE: Calls to BER SF Theshold, BER SD Threhhold, and Expected C2
// were moved to CFG for perfomance reasons.


    if (!strcmp(argv[0],"src"))
    {
        SetIsConnectedAsSrc(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"dst"))
    {
        SetIsConnectedAsDst(argv[1][0]=='e');
    }
    // Trace monitoring is not supported
    //else if (!strcmp(argv[0],"tim"))
    //{
    //    SetTIMMonitoringEnable(argv[1][0]=='e');
    //}
    //else if (!strcmp(argv[0],"trace"))
    //{
    //    string aMessage(argv[1]); aMessage.resize(62,' ');
    //    CT_SONET64ByteTrace aTrace(aMessage);
    //    SetExpectedTrace(aTrace);
    //}
    else
    {
        goto HOPERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

HOPERROR:
    {
        fc_cout << "hop <src|dst> <e-nable|d-isable> " << endl;
        // NOTE: Calls to BER SF Theshold, BER SD Threhhold, and Expected C2
        // were moved to CFG for perfomance reasons.
        // fc_cout << "hop <sfber> <Numeric value range 3 .. 12 inclusive> " << endl;
        // fc_cout << "hop <expC2> <1 byte integer>" << endl;
        fc_cout << "hop <sdber>, <sfber>, and <expC2> moved to CFG " << endl;
        fc_cout << "hop <trace> NOT SUPPORTED" << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}
