/*----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :  Common Types
TARGET      :  Platform Independent
AUTHOR      :  June 19, 2006 - Larry M. Wolfrum
DESCRIPTION :  PM Subapplication registration information.
-----------------------------------------------------------------------*/

#ifndef PM_SUBAPPLICATIONREGISTRATION_H
#define PM_SUBAPPLICATIONREGISTRATION_H

#include <PM/PM_GenericApplication.h>

class PM_SubApplicationRegistration
{

public:

	// Default Constructor
	PM_SubApplicationRegistration( PM_GenericApplication* theSubApplication );   

	// Destructor
	~PM_SubApplicationRegistration();

	// Method to retrieve the subapplication pointer.
	PM_GenericApplication* GetSubApp();

	// Method to retrieve the previous region ready state.
	bool IsPreviousRegionReady( CT_PM_Period thePeriod );

	// Method to set the previous region ready state.
	void SetPreviousRegionReady( CT_PM_Period thePeriod, bool theState );

private:

	// Subapplication pointer.
	PM_GenericApplication* mySubAppPtr;

	// Previous region states.
	bool myPreviousRegionStates[CT_PM_PERIOD_UNKNOWN];

};

//------------------------------------------------------------------
inline
PM_GenericApplication* PM_SubApplicationRegistration::GetSubApp()
{
	return mySubAppPtr;
}

#endif //PM_SUBAPPLICATIONREGISTRATION_H


