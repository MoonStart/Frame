//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_IBETHConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_IBETHConfig::MON_IBETHConfig(uint32 theIndex):
    MON_Config(theIndex)
{
    Reset();
}

MON_IBETHConfig::~MON_IBETHConfig()
{
}

void MON_IBETHConfig::Reset(void)
{
    MON_Config::Reset();
    myMonitoringEnable = false;
}



void MON_IBETHConfig::SetMonitoringEnable(bool theMonitoringEnable)
{
    myMonitoringEnable = theMonitoringEnable;
}

bool MON_IBETHConfig::GetMonitoringEnable() const
{
    return myMonitoringEnable;
}



ostream& MON_IBETHConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myMonitoringEnable);
    return theStream;
}

istream& MON_IBETHConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myMonitoringEnable);
    return theStream;
}

FC_Stream& MON_IBETHConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myMonitoringEnable;
    return theStream;
}

FC_Stream& MON_IBETHConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myMonitoringEnable;
    return theStream;
}

void MON_IBETHConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    //For now, this is just a place holder
    //theStream   << "GCC    - Monitoring Enabled    [mon]       = " << DISPLAY_BOOL(myMonitoringEnable) << endl;
}

FC_CmdProcessor::STATUS MON_IBETHConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto HOPERROR;
    else if (!strcmp(argv[0],"tim"))
    {
        SetMonitoringEnable(argv[1][0]=='e');
    }
    else
    {
        goto HOPERROR;
    }
    return FC_CmdProcessor::E_SUCCESS;

HOPERROR:
    {
        fc_cout << "hop <mon> <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}
