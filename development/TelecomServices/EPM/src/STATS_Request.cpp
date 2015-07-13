// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/
#include "../STATS_Request.h"

#include <BaseClass/FC_TextStream.h>
using namespace std;

STATS_Request::STATS_Request()
{
    ResetData();
}

STATS_Request::~STATS_Request()
{
}

void STATS_Request::ResetData()
{
    myRequestCount = 0;
    myRequestEntityId = 0;
    myInitStatsCount = 0;
    myInitStatsEntityId = 0;
    myDuration = 0;
}

FC_Stream& STATS_Request::ReadObjectBinary(FC_Stream& theStream)
{
	theStream >> myRequestCount;
	theStream >> myRequestEntityId;
	theStream >> myInitStatsCount;
	theStream >> myInitStatsEntityId;
	theStream >> myDuration;
    return theStream;
}

FC_Stream& STATS_Request::WriteObjectBinary(FC_Stream& theStream)
{
	theStream << myRequestCount;
	theStream << myRequestEntityId;
	theStream << myInitStatsCount;
	theStream << myInitStatsEntityId;
	theStream << myDuration;
    return theStream;
}

istream& STATS_Request::ReadObject(istream& theStream)
{
	theStream >> FC_ExtractVar(myRequestCount);
	theStream >> FC_ExtractVar(myRequestEntityId);
	theStream >> FC_ExtractVar(myInitStatsCount);
	theStream >> FC_ExtractVar(myInitStatsEntityId);
	theStream >> FC_ExtractVar(myDuration);
    return theStream;
}

ostream& STATS_Request::WriteObject(ostream& theStream)
{
	theStream << FC_InsertVar(myRequestCount);
	theStream << FC_InsertVar(myRequestEntityId);
	theStream << FC_InsertVar(myInitStatsCount);
	theStream << FC_InsertVar(myInitStatsEntityId);
	theStream << FC_InsertVar(myDuration);
    return theStream;
}
