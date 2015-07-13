// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_STATS_Request_INCLUDED
#define _INC_STATS_Request_INCLUDED

#include <gdef.h>
#include <Blackboard/FC_BbObject.h>
#include <CsPii/CSPII_CardIF.h>

class STATS_Request : public FC_BbObject
{
public:
	//Constructor
	STATS_Request();

	//Destructor
	virtual ~STATS_Request();

    void ResetData();

	virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);
	virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);
	virtual istream& ReadObject(istream& theStream);
	virtual ostream& WriteObject(ostream& theStream);

    uint32 GetRequestCount(){ return myRequestCount; }
    void   SetRequestCount(uint32 theCount){ myRequestCount = theCount; }

    uint32 GetRequestEntityId(){ return myRequestEntityId; }
    void   SetRequestEntityId(uint32 theEntityId){ myRequestEntityId = theEntityId; }

    uint32 GetInitStatsCount(){ return myInitStatsCount; }
    void   SetInitStatsCount(uint32 theCount){ myInitStatsCount = theCount; }

    uint32 GetInitStatsEntityId(){ return myInitStatsEntityId; }
    void   SetInitStatsEntityId(uint32 theEntityId){ myInitStatsEntityId = theEntityId; }

    uint32 GetDuration(){ return myDuration; }
    void   SetDuration(uint32 theDuration){ myDuration = theDuration; }

private:

    uint32 myRequestCount;
    uint32 myRequestEntityId;
    uint32 myInitStatsCount;
    uint32 myInitStatsEntityId;
    uint32 myDuration;
};

#endif /* _INC_STATS_Request_INCLUDED */
