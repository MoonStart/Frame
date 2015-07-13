/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 5, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to manage Data Layer AutoRate Lock processing.
--------------------------------------------------------------------------*/

#include <EPM/src/PM_AutoRateLockRmon.h>

// Table of Auto-Rate Lock Parameter Inhibit Profiles
// Since the Auto Rate Lock inhibit algorithm is the same
// for all RMON parameters, the same table is used for both
// RMON counters and gauges. Since the number of RMON counter
// parameters is larger than the number of RMON gauge parameters,
// the larger number determines the size of the profile array elements.
// There is an implied union or overlay of the counter vs. the gauge
// parameters in each of the array elements.
bool PM_AutoRateLockRmon::AutoRateLockProfiles[PM_AutoRateLockProfile_MAX][PM_TypeRmonCounter::PM_PARAM_NUM-9] = 
{
	//  PM_AutoRateLockProfile_INHIBIT_ALL
	{
		true,	// DROP OR UTIL
		true,	// PKT
		true,	// BCPKT
		true,	// MCPKT
		true,	// CRCAE
		true,	// USPKT
		true,	// OSPKT
		true,	// FRAG
		true	// JABR
	},

	//  PM_AutoRateLockProfile_1
	{
		false,	// DROP OR UTIL
		false,	// PKT
		false,	// BCPKT
		false,	// MCPKT
		false,	// CRCAE
		false,	// USPKT
		false,	// OSPKT
		false,	// FRAG
		false	// JABR
	}
};

PM_AutoRateLockRmon::PM_AutoRateLockRmon()
{
	// Nothing to do for now.
}

PM_AutoRateLockRmon::~PM_AutoRateLockRmon()
{
	// Nothing to do for now.
}

bool* PM_AutoRateLockRmon::MapAutoRateToProfile( CT_TEL_daHz theAutoBitRate )
{
	bool* profile;

	switch( theAutoBitRate )
	{
	case 0:
		 profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_INHIBIT_ALL][0];
		 break;

	case BIT_RATE_100BFX:
	case BIT_RATE_GBE:
    case BIT_RATE_TGLAN:
		profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_1][0];
		break;

	default:
		 profile = &AutoRateLockProfiles[PM_AutoRateLockProfile_INHIBIT_ALL][0];
		 break;
	}

	return profile;
}
