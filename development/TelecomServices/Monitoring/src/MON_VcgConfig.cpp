//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_VcgConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <cstring>

MON_VcgConfig::MON_VcgConfig(uint32 theIndex):
    MON_Config(theIndex),
    myDebugFlag(false),
    myLastTime(0),
    myShortestTime(0),  
    myLongestTime(0),
    myGroupEnable(false)
{
    myHopIdList = CT_FAC_StsMap();
    Reset();
}

MON_VcgConfig::~MON_VcgConfig()
{
}

void MON_VcgConfig::Reset(void)
{
    MON_Config::Reset();
    myGroupEnable = false;
    myDebugFlag = false;
    myLastTime = 0;
    myShortestTime = 0;  
    myLongestTime = 0;
}

void MON_VcgConfig::SetHopIdList(CT_FAC_StsMap& theHopIdList)
{
    myHopIdList = theHopIdList;
}

CT_FAC_StsMap& MON_VcgConfig::GetHopIdList()
{
    return myHopIdList;
}


void MON_VcgConfig::SetGroupOfHopsEnable(bool theGroupEnable)
{
    myGroupEnable = theGroupEnable;
}

bool MON_VcgConfig::GetGroupOfHopsEnable() const
{
    return myGroupEnable;
}



void MON_VcgConfig::SetDebugFlagSet(bool theDebugEnable) 
{
    myDebugFlag = theDebugEnable;
}

bool MON_VcgConfig::IsDebugFlagSet() const 
{
    return myDebugFlag;
}


void MON_VcgConfig::SetProcessTime(const FC_Milliseconds& theTime)
{
    myLastTime = theTime;

    if (myLastTime > myLongestTime)
        myLongestTime = myLastTime;

    if (myShortestTime == 0)
    {
        myShortestTime = myLastTime;
    }
    else if ((myLastTime != 0) && (myLastTime < myShortestTime))
    {
        myShortestTime = myLastTime;
    }
}


// For Display
ostream& MON_VcgConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myHopIdList);
    theStream << FC_InsertVar(myGroupEnable);
    theStream << FC_InsertVar(myDebugFlag);
    theStream << FC_InsertVar(myLastTime);
    theStream << FC_InsertVar(myShortestTime);
    theStream << FC_InsertVar(myLongestTime);
    return theStream;
}

istream& MON_VcgConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myHopIdList);
    theStream >> FC_ExtractVar(myGroupEnable);
    theStream >> FC_ExtractVar(myDebugFlag);
    theStream >> FC_ExtractVar(myLastTime);
    theStream >> FC_ExtractVar(myShortestTime);
    theStream >> FC_ExtractVar(myLongestTime);
    return theStream;
}


// For persitance and region transfer
FC_Stream& MON_VcgConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myHopIdList;
    theStream << myGroupEnable;
    return theStream;
}

FC_Stream& MON_VcgConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myHopIdList;
    theStream >> myGroupEnable;
    return theStream;
}



FC_CmdProcessor::STATUS MON_VcgConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto VCGERROR;

    if (!strncmp(argv[0],"st",2))
    {
        //uint16 tempChannel = atoi(argv[1]);
        //SetGroupOfHopsStartChannel(tempChannel);
    }
    else if (!strncmp(argv[0],"gr",2))
    {
        SetGroupOfHopsEnable(argv[1][0]=='e');
    }
    else if (!strncmp(argv[0],"deb",3))
    {
        SetDebugFlagSet(argv[1][0]=='e');
    }
    else
    {
        goto VCGERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

VCGERROR:
    {
        //fc_cout << "vcg <startchannel>  <0|24|48|72|96|120|144|168 | 65535>" << endl;
        fc_cout << "vcg <groupenable>   <e-nable|d-isable> " << endl;
        fc_cout << "vcg <debug>         <e-nable|d-isable> (for index 0 only)" << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}



void MON_VcgConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    //theStream   << "VCG   - Start Channel    [startchannel]   = " << uint32(myGroupStartChannel) << endl;
    theStream   << "VCG   - Group Enable     [groupenable]    = " << DISPLAY_BOOL(myGroupEnable) << endl;
    theStream   << "VCG   - Debug (index 0)  [debug]          = " << DISPLAY_BOOL(myDebugFlag) << endl;
    if (myDebugFlag)
    {
        theStream   << "VCG   - Last Time ms                      = " << myLastTime << endl;
        theStream   << "VCG   - Shortest Time ms                  = " << myShortestTime << endl;
        theStream   << "VCG   - Longest Time ms                   = " << myLongestTime << endl;
    }
}
