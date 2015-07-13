/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 6, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to manage RMON Counter Layer AutoRate Lock processing.
--------------------------------------------------------------------------*/

#ifndef PM_AUTORATELOCKRMON_H
#define PM_AUTORATELOCKRMON_H

#include <EPM/src/PM_AutoRateLock.h>
#include <EPM/PM_TypeRmon.h>

class PM_AutoRateLockRmon : public PM_AutoRateLock
{
public:

	enum PM_AutoRateLockProfiles
	{
		PM_AutoRateLockProfile_INHIBIT_ALL,
		PM_AutoRateLockProfile_1,
		PM_AutoRateLockProfile_MAX
	};
	
	// Class default constructor
	 PM_AutoRateLockRmon();

	// Class default destructor
	virtual ~PM_AutoRateLockRmon();

	// Returns a pointer to an Auto-Rate Lock inhibit profile.
	virtual bool* MapAutoRateToProfile( CT_TEL_daHz theAutoBitRate );

private:

	// Table of Auto-Rate Lock Parameter Inhibit Profiles.
	// Since the Auto Rate Lock inhibit algorithm is the same
	// for all RMON parameters, the same table is used for both
	// RMON counters and gauges. Given that the number of RMON counter
	// parameters is larger than the number of RMON gauge parameters,
	// the larger number determines the size of the profile array elements.
	// There is an implied union or overlay of the counter vs. the gauge
	// parameters in each of the array elements.
	static bool AutoRateLockProfiles[PM_AutoRateLockProfile_MAX][PM_TypeRmonCounter::PM_PARAM_NUM-9];

};

#endif //PM_AUTORATELOCKRMON_H

