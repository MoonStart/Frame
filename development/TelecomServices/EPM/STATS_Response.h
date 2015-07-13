// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_STATS_Response_INCLUDED
#define _INC_STATS_Response_INCLUDED

#include <gdef.h>
#include <list>
#include <CommonTypes/CT_PMA_General.h>
#include <Blackboard/FC_BbObject.h>
#include <CsPii/CSPII_CardIF.h>

class STATS_Response : public FC_BbObject
{
public:
    //Constructor
    STATS_Response();

    //Destructor
    virtual ~STATS_Response();

    void ResetData();

    virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);
    virtual istream& ReadObject(istream& theStream);
    virtual ostream& WriteObject(ostream& theStream);

    void SetRequestCount(uint32 theCount){ myRequestCount = theCount; }
    uint32 GetRequestCount(){ return myRequestCount; }

    CT_PMA_StatsDataMap GetStatsDataMap(){ return myStatsDataMap; }
    void UpdateStatsDataMap(CT_PMA_StatId theStatId, uint32 theCount)
    {
        myStatsDataMap.insert(CT_PMA_StatsDataMap::value_type(theStatId, theCount));
    }

    list<string> GetStatsDataList(){ return myStatsDataList; }
    void UpdateStatsDataList(list<string> theList){ myStatsDataList = theList; }

private:

    uint32 myRequestCount;

    CT_PMA_StatsDataMap myStatsDataMap;

    list<string> myStatsDataList;
};

#endif /* _INC_STATS_Response_INCLUDED */
