// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/
#include "../STATS_Response.h"

#include <BaseClass/FC_TextStream.h>
using namespace std;

STATS_Response::STATS_Response()
{
    ResetData();
}

STATS_Response::~STATS_Response()
{
}

void STATS_Response::ResetData()
{
    myRequestCount = 0;
    myStatsDataMap.clear();
    myStatsDataList.erase(myStatsDataList.begin(), myStatsDataList.end());
}

FC_Stream& STATS_Response::ReadObjectBinary(FC_Stream& theStream)
{
    theStream >> myRequestCount;

    //-----------------------------
    // Handle myStatsDataMap now...
    //-----------------------------
    myStatsDataMap.clear(); 

    uint32 aNumberOfStatsData;

    theStream >> aNumberOfStatsData;

    if ( aNumberOfStatsData )
    {
        uint8     StatId;
        uint32 StatCount;

        for ( uint32 aStatsIter=0; aStatsIter < aNumberOfStatsData; aStatsIter++ )
        {
            theStream >> StatId;
            theStream >> StatCount;
            myStatsDataMap.insert(CT_PMA_StatsDataMap::value_type(StatId, StatCount));
        }
    }

    //-----------------------------
    // Handle myStatsDataList now...
    //-----------------------------
    myStatsDataList.erase(myStatsDataList.begin(), myStatsDataList.end());
 
    uint32 aNumberOfStatsDataList;
 
    theStream >> aNumberOfStatsDataList;
 
    if ( aNumberOfStatsDataList )
    {
        string aStatListString;
 
        for ( uint32 aStatsIter=0; aStatsIter < aNumberOfStatsDataList; aStatsIter++ )
        {
            theStream >> aStatListString;
            myStatsDataList.push_back(aStatListString);
        }
    }

    return theStream;
}

FC_Stream& STATS_Response::WriteObjectBinary(FC_Stream& theStream)
{
    theStream << myRequestCount;

    //-----------------------------
    // Handle myStatsDataMap now...
    //-----------------------------
    uint32 aNumberOfStatsData = myStatsDataMap.size();

    theStream << aNumberOfStatsData;

    if ( aNumberOfStatsData )
    {
        CT_PMA_StatsDataMap::iterator aStatsIter;
        for ( aStatsIter = myStatsDataMap.begin(); aStatsIter != myStatsDataMap.end(); aStatsIter++ )
        {
            uint8     StatId = (*aStatsIter).first;
            uint32 StatCount = (*aStatsIter).second;
            theStream << StatId;
            theStream << StatCount;
        }
    }

    //-----------------------------
    // Handle myStatsDataList now...
    //-----------------------------
    uint32 aNumberOfStatsDataList = myStatsDataList.size();
 
    theStream << aNumberOfStatsDataList;
 
    if ( aNumberOfStatsDataList )
    {
        list<string>::iterator aStatsIter;
        for ( aStatsIter = myStatsDataList.begin(); aStatsIter != myStatsDataList.end(); aStatsIter++ )
        {
            string aStatListString = (*aStatsIter);
            theStream << aStatListString;
        }
    }

    return theStream;
}

istream& STATS_Response::ReadObject(istream& theStream)
{
    theStream >> FC_ExtractVar(myRequestCount);

    //-----------------------------
    // Handle myStatsDataMap now...
    //-----------------------------
    fc_cout << "" << endl;
    fc_cout << "DEFAULT set of data provided for testing!" << endl;
    fc_cout << "" << endl;

    uint8 StatId = 0; uint32 StatCount = 0;
    for ( uint32 aStatsIter=0; aStatsIter < 6; aStatsIter++ )
    {
        myStatsDataMap.insert(CT_PMA_StatsDataMap::value_type(StatId, StatCount));
        StatId++;
        StatCount++;
    }

    //-----------------------------
    // Handle myStatsDataList now...
    //-----------------------------
    myStatsDataList.push_back("mac=00:00:00:00:00:00 vlan=000 modid=00 port=0");
    myStatsDataList.push_back("mac=00:00:00:00:00:01 vlan=001 modid=01 port=1");
    myStatsDataList.push_back("mac=00:00:00:00:00:02 vlan=002 modid=02 port=2");

    return theStream;
}

ostream& STATS_Response::WriteObject(ostream& theStream)
{
    theStream << FC_InsertVar(myRequestCount);

    //-----------------------------
    // Handle myStatsDataMap now...
    //-----------------------------
    if ( myStatsDataMap.size() )
    {
        CT_PMA_StatsDataMap::iterator aStatsIter;
        for ( aStatsIter = myStatsDataMap.begin(); aStatsIter != myStatsDataMap.end(); aStatsIter++ )
        {
            uint8     StatId = (*aStatsIter).first;
            uint32 StatCount = (*aStatsIter).second;
            theStream << FC_InsertVar(StatId);
            theStream << FC_InsertVar(StatCount);
        }
    }

    //-----------------------------
    // Handle myStatsDataList now...
    //-----------------------------
    if ( myStatsDataList.size() )
    {
        list<string>::iterator aStatsIter;
        for ( aStatsIter = myStatsDataList.begin(); aStatsIter != myStatsDataList.end(); aStatsIter++ )
        {
            string aStatListString = (*aStatsIter);
            theStream << FC_InsertVar(aStatListString);
        }
    }

    return theStream;
}
