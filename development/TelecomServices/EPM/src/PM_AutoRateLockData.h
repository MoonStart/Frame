/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 5, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to manage Data Layer AutoRate Lock processing.
--------------------------------------------------------------------------*/

#ifndef PM_AUTORATELOCKDATA_H
#define PM_AUTORATELOCKDATA_H

#include <EPM/src/PM_AutoRateLock.h>
#include <PM/PM_TypeData.h>

class PM_AutoRateLockData : public PM_AutoRateLock
{
public:

	enum PM_AutoRateLockProfiles
	{
		PM_AutoRateLockProfile_INHIBIT_ALL,
		PM_AutoRateLockProfile_1,
		PM_AutoRateLockProfile_2,
		PM_AutoRateLockProfile_3,
		PM_AutoRateLockProfile_MAX
	};
	
	// Class default constructor
	 PM_AutoRateLockData();

	// Class default destructor
	virtual ~PM_AutoRateLockData();

	// Returns a pointer to an Auto-Rate Lock inhibit profile.
	virtual bool* MapAutoRateToProfile( CT_TEL_daHz theAutoBitRate );

private:

	// Table of Auto-Rate Lock profiles
	static bool AutoRateLockProfiles[PM_AutoRateLockProfile_MAX][PM_TypeData::PM_PARAM_NUM-1];

};

#endif //PM_AUTORATELOCKDATA_H

