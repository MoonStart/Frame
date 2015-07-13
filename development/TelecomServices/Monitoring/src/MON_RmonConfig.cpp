//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_RmonConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_RmonConfig::MON_RmonConfig(uint32 theIndex):
    MON_Config(theIndex),
    myRmonEnable(false)
{
}

MON_RmonConfig::~MON_RmonConfig()
{
}

void MON_RmonConfig::Reset(void)
{
    MON_Config::Reset();
    myRmonEnable = false;
}


bool MON_RmonConfig::SetRmonEnable(bool theRmonState)
{
    bool hasChanged = (myRmonEnable != theRmonState);
    myRmonEnable = theRmonState;
    return hasChanged;
}

bool MON_RmonConfig::GetRmonEnable() const
{
    return myRmonEnable;
}



ostream& MON_RmonConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myRmonEnable);
    return theStream;
}

istream& MON_RmonConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myRmonEnable);
    return theStream;
}

FC_Stream& MON_RmonConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myRmonEnable;
    return theStream;
}

FC_Stream& MON_RmonConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myRmonEnable;
    return theStream;
}

void MON_RmonConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "RMON    - Rmon Enable          [mon]       = " << DISPLAY_BOOL(myRmonEnable) << endl;
}

FC_CmdProcessor::STATUS MON_RmonConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto RMONERROR;


    if (!strcmp(argv[0],"mon"))
    {
        SetRmonEnable(argv[1][0]=='e');
    }
    else
    {
        goto RMONERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

RMONERROR:
    {
        fc_cout << "rmon <mon> <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}
