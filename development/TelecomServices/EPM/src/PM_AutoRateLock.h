/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 5, 2006, Larry Wolfrum.
 DESCRIPTION:   Base class to manage AutoRate Lock processing.
--------------------------------------------------------------------------*/

#ifndef PM_AUTORATELOCK_H
#define PM_AUTORATELOCK_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <T6100/T6100_CardIf.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_Opt.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_MacStatus.h>

class PM_AutoRateLock
{
public:
	
	// Class default constructor
	 PM_AutoRateLock();

	// Class default destructor
	virtual ~PM_AutoRateLock();

	// Resets internal Auto-Rate lock state variables
	void ResetAutoRateLockStates();

	// Returns Auto-Rate Lock inhibit profile array
	bool* GetAutoRateInhibitProfile();

	// Returns an indication that the Auto-Rate state has changed
	bool IsAutoRateStateRefreshed();

	// Method to adjust Auto-Rate Lock state information and TCA filtering
	void AdjustForAutoRateLock( T6100_CardIf& theCardContext,
								uint32 theNumberOfParam,
								CT_PM_64BitValue* theCurrentValueParam,
								bool* theFilteringStateFirstStage,
								bool* theFilteringStateSecondStage,
                                CT_PM_Side thePMSide = CT_PM_PORT_SIDE_0 );

	// Returns a pointer to an Auto-Rate Lock inhibit profile.
	// Must be over-ridden by a derived class.
	virtual bool* MapAutoRateToProfile( CT_TEL_daHz theAutoBitRate ) = 0;

	// Returns a pointer to the CFG_Opt region.
	static CFG_Opt* GetCfgOptRegion( T6100_CardIf& theCardContext, CT_PM_Side theSide );

	// Returns a pointer to the MON_Opt region.
	static MON_OptStatus* GetMonOptStatusRegion( T6100_CardIf& theCardContext );

	static MON_MacStatus* GetMonMacStatusRegion( T6100_CardIf& theCardContext, CT_PM_Side thePMSide );

	// Returns massaged signal type as a function of locker bit rate.
	virtual CT_TEL_SignalType GetAutoRateLockSignalType(T6100_CardIf& theCardContext,
														CT_TEL_SignalType origSignalTyperetSignalType);

	// Maps CT_PM_Side to CT_If_Id of entity which contains the MonOptApp defining
	// the AutoRate Lock characteristics.
	CT_IntfId ConvertPmSideToCtIfId( const CT_PM_Side theSide );


protected:

	//Pointer to selected Auto-Rate Lock inhibit profile
	bool* myAutoRateLockProfile;

private:

	//Flag indicating that the current values
	//must be reset.
	bool myAutoRateLockRefresh;

	//Current Auto-Rate Lock bit rate. A rate of 0
	// indicates that the facility is not locked.
	CT_TEL_daHz	myCurrentAutoBitRate;

	//Auto-Rate Lock bit rate when last locked.
	//A rate of 0 indicates that this facility, as
	//an Auto-Rate Lock facility, has never been locked.
	CT_TEL_daHz	myLastLockedAutoBitRate;
};

#endif //PM_AUTORATELOCK_H
