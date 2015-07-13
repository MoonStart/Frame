//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_GccConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_GccConfig::MON_GccConfig(uint32 theIndex):
    MON_Config(theIndex)
{
    Reset();
}

MON_GccConfig::~MON_GccConfig()
{
}

void MON_GccConfig::Reset(void)
{
    MON_Config::Reset();
    myMonitoringEnable = false;
}



void MON_GccConfig::SetMonitoringEnable(bool theMonitoringEnable)
{
    myMonitoringEnable = theMonitoringEnable;
}

bool MON_GccConfig::GetMonitoringEnable() const
{
    return myMonitoringEnable;
}



ostream& MON_GccConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myMonitoringEnable);
    return theStream;
}

istream& MON_GccConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myMonitoringEnable);
    return theStream;
}

FC_Stream& MON_GccConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myMonitoringEnable;
    return theStream;
}

FC_Stream& MON_GccConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myMonitoringEnable;
    return theStream;
}

void MON_GccConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    //For now, this is just a place holder
    //theStream   << "GCC    - Monitoring Enabled    [mon]       = " << DISPLAY_BOOL(myMonitoringEnable) << endl;
}

FC_CmdProcessor::STATUS MON_GccConfig::Set(int argc, char** argv)
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
