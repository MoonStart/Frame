// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Performance Monitoring
//  TARGET   :     SSM and Active Controller
// --------------------------------------------------------------------------*/

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_STATS_ResponseRegion_INCLUDED
#define _INC_STATS_ResponseRegion_INCLUDED

#include <Blackboard/FC_BbRegionVectImp.h>
#include "STATS_Response.h"

class STATS_ResponseRegion: public FC_BbRegionVectImp<STATS_Response>
{
public:
	//Constructor
	STATS_ResponseRegion(const FC_BbKey theKey, size_t theSize = 1);

	//Destructor
	virtual ~STATS_ResponseRegion();

    void ResetData();
};

#endif /* _INC_STATS_ResponseRegion_INCLUDED */
