/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     April 17, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to manage MS Near End Layer AutoRate Lock processing.
--------------------------------------------------------------------------*/

#ifndef PM_AUTORATELOCKMSNEAREND_H
#define PM_AUTORATELOCKMSNEAREND_H

#include <EPM/src/PM_AutoRateLock.h>
#include <PM/PM_TypeMsNearEnd.h>

class PM_AutoRateLockMsNearEnd : public PM_AutoRateLock
{
public:

	enum PM_AutoRateLockProfiles
	{
		PM_AutoRateLockProfile_INHIBIT_ALL,
		PM_AutoRateLockProfile_1,
		PM_AutoRateLockProfile_MAX
	};
	
	// Class default constructor
	 PM_AutoRateLockMsNearEnd();

	// Class default destructor
	virtual ~PM_AutoRateLockMsNearEnd();

	// Returns a pointer to an Auto-Rate Lock inhibit profile.
	virtual bool* MapAutoRateToProfile( CT_TEL_daHz theAutoBitRate );

private:

	// Two dimensional array of autorate lock profiles. The least significant
	// dimension is the parameter index within the layer. The most significant
	// dimension profile index.
	static bool AutoRateLockProfiles[PM_AutoRateLockProfile_MAX][PM_TypeMsNearEnd::PM_PARAM_NUM];

};

#endif //PM_AUTORATELOCKMSNEAREND_H

