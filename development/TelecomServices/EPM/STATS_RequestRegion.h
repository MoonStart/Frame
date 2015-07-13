// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_STATS_RequestRegion_INCLUDED
#define _INC_STATS_RequestRegion_INCLUDED

#include <Blackboard/FC_BbRegionVectImp.h>
#include "STATS_Request.h"

class STATS_RequestRegion: public FC_BbRegionVectImp<STATS_Request>
{
public:
	//Constructor
	STATS_RequestRegion(const FC_BbKey theKey, size_t theSize = 1);

	//Destructor
	virtual ~STATS_RequestRegion();

    void ResetData();
};

#endif /* _INC_STATS_RequestRegion_INCLUDED */
