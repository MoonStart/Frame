//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_DrtrConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_DrtrConfig::MON_DrtrConfig(uint32 theIndex):
    MON_Config(theIndex)
{
    Reset();
}

MON_DrtrConfig::~MON_DrtrConfig()
{
}

void MON_DrtrConfig::Reset(void)
{
    MON_Config::Reset();
    myMonitorEnable = false;
}



void MON_DrtrConfig::SetMonitoringEnable(bool theMonitoringEnable)
{
    myMonitorEnable = theMonitoringEnable;
}

bool MON_DrtrConfig::GetMonitoringEnable() const
{
    return myMonitorEnable;
}



ostream& MON_DrtrConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myMonitorEnable);
    return theStream;
}

istream& MON_DrtrConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myMonitorEnable);
    return theStream;
}

FC_Stream& MON_DrtrConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myMonitorEnable;
    return theStream;
}

FC_Stream& MON_DrtrConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myMonitorEnable;
    return theStream;
}

void MON_DrtrConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "DRTR    - Monitoring Enabled    [mon]       = " << DISPLAY_BOOL(myMonitorEnable) << endl;
}

FC_CmdProcessor::STATUS MON_DrtrConfig::Set(int argc, char** argv)
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
