/*----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :  Common Types
TARGET      :  Platform Independent
AUTHOR      :  June 19, 2006 - Larry M. Wolfrum
DESCRIPTION :  PM Subapplication registration information.
-----------------------------------------------------------------------*/

#include <EPM/PM_SubApplicationRegistration.h>

//-----------------------------------------------------------------
PM_SubApplicationRegistration::PM_SubApplicationRegistration( PM_GenericApplication* theSubApplication ):
	mySubAppPtr( theSubApplication )
{
	for( uint32 period = 0; period < (uint32)CT_PM_PERIOD_UNKNOWN; period++ )
	{
	   myPreviousRegionStates[period] = false;
	}
}

//-----------------------------------------------------------------
PM_SubApplicationRegistration::~PM_SubApplicationRegistration()
{
	// Nothing to do for now.
}

//------------------------------------------------------------------
bool PM_SubApplicationRegistration::IsPreviousRegionReady( CT_PM_Period thePeriod )
{
	if( (thePeriod >= 0) && (thePeriod < CT_PM_PERIOD_UNKNOWN) )
	{
		return myPreviousRegionStates[thePeriod];
	}
	else
	{
		FC_THROW_ERROR(FC_RuntimeError, "PM_SubApplicationRegistration::IsPreviousRegionReady(): bad parameter");
		return false;
	}
}

//------------------------------------------------------------------
void PM_SubApplicationRegistration::SetPreviousRegionReady( CT_PM_Period thePeriod, bool theState )
{
	if( (thePeriod >= 0) && (thePeriod < CT_PM_PERIOD_UNKNOWN) )
	{
		myPreviousRegionStates[thePeriod] = theState;;
	}
	else
	{
		FC_THROW_ERROR(FC_RuntimeError, "PM_SubApplicationRegistration::SetPreviousRegionReady(): bad parameter");
	}
}


