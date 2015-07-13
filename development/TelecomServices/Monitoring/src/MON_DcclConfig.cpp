//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_DcclConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_DcclConfig::MON_DcclConfig(uint32 theIndex):
    MON_Config(theIndex)
{
    Reset();
}

MON_DcclConfig::~MON_DcclConfig()
{
}

void MON_DcclConfig::Reset(void)
{
    MON_Config::Reset();
    myMonitoringEnable = false;
}



void MON_DcclConfig::SetMonitoringEnable(bool theMonitoringEnable)
{
    myMonitoringEnable = theMonitoringEnable;
}

bool MON_DcclConfig::GetMonitoringEnable() const
{
    return myMonitoringEnable;
}



ostream& MON_DcclConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myMonitoringEnable);
    return theStream;
}

istream& MON_DcclConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myMonitoringEnable);
    return theStream;
}

FC_Stream& MON_DcclConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myMonitoringEnable;
    return theStream;
}

FC_Stream& MON_DcclConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myMonitoringEnable;
    return theStream;
}

void MON_DcclConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    //For now, this is just a place holder
    //theStream   << "DCCL    - Monitoring Enabled    [mon]       = " << DISPLAY_BOOL(myMonitoringEnable) << endl;
}

FC_CmdProcessor::STATUS MON_DcclConfig::Set(int argc, char** argv)
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
