// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtsConfig.h"
#include <BaseClass/FC_TextStream.h>

MON_OtsConfig::MON_OtsConfig(uint32 theIndex):
    MON_Config(theIndex),
    myTIMMonitoringEnable(false),
    myExpectedTrace()
{
}

MON_OtsConfig::~MON_OtsConfig(void )
{
}

void MON_OtsConfig::Reset()
{
    MON_Config::Reset();
    myExpectedTrace = CT_G709Trace();
    myTIMMonitoringEnable = false;
}

void MON_OtsConfig::SetExpectedTrace(const CT_G709Trace& theExpTrace)
{
    myExpectedTrace = theExpTrace;
}

const CT_G709Trace MON_OtsConfig::GetExpectedTrace() const
{
    return myExpectedTrace;
}

void MON_OtsConfig::SetTIMMonitoringEnable(bool theTIMMonitoringState)
{
    // This setting has effect only in LTE termination type.
    myTIMMonitoringEnable = theTIMMonitoringState;
}

bool MON_OtsConfig::GetTIMMonitoringEnable() const
{
    return myTIMMonitoringEnable;
}


ostream& MON_OtsConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myExpectedTrace);
    theStream << FC_InsertVar(myTIMMonitoringEnable);

    return theStream;
}

istream& MON_OtsConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myExpectedTrace);
    theStream >> FC_ExtractVar(myTIMMonitoringEnable);

    return theStream;
}

FC_Stream& MON_OtsConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myExpectedTrace;
    theStream << myTIMMonitoringEnable;
    return theStream;
}

FC_Stream& MON_OtsConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myExpectedTrace;
    theStream >> myTIMMonitoringEnable;

    return theStream;
}

void MON_OtsConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "OTS     - TIM Monitoring        [tim]       = " << DISPLAY_BOOL(myTIMMonitoringEnable) << endl;
    theStream   << "OTS     - Expected Trace        [trace]     = " ;
    myExpectedTrace.Display(theStream);
}

FC_CmdProcessor::STATUS MON_OtsConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto OTSERROR;

    if (!strcmp(argv[0],"tim"))
    {
        SetTIMMonitoringEnable(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"trace"))
    {
        if (argc != 4) goto OTSERROR;
        string aMessage(argv[1]);
        string aSapi(argv[2]);
        string aDapi(argv[3]);

        CT_G709Trace aTrace(aSapi,aDapi,aMessage);
        SetExpectedTrace(aTrace);
    }
    else
        goto OTSERROR;

    return FC_CmdProcessor::E_SUCCESS;

OTSERROR:
    {
        fc_cout << "ots <tim> <e-nable|d-isable> " << endl;
        fc_cout << "ots <trace> <32-byte message> <15-byte sapi> <15-byte dapi>" << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}