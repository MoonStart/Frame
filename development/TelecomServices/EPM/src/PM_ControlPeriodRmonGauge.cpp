/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     January 24, 2006 Larry Wolfrum.
 DESCRIPTION:   RMON Gauge Control period class.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <EPM/src/PM_ControlPeriodRmonGauge.h>
#include <PM/PM_RegionImp.h>
#include <EPM/PM_BbValueRmon.h>
#include <EPM/PM_TypeRmon.h>
#include <PM/PM_BbCfg.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_ControlPeriodRmonGauge::PM_ControlPeriodRmonGauge (PM_GenericApplication     &theGenericApplication,
													  CT_PM_Period              thePeriod,
													  PM_AccumulationPeriod&    theAccPeriod,
													  uint16                    theIndex,
													  char*                     theProcessorTypeString,
													  CT_PM_Value*              theMaxValueTable,
													  time_t                    thePstOffset):
	PM_ControlPeriod( theGenericApplication,
					  thePeriod,
					  theAccPeriod,
					  theIndex,
					  theProcessorTypeString,
					  thePstOffset,
					  false ),
	myStatusRmon( (*myGenericApplication.GetRegionStatusRmon())[thePeriod] ),
	myMaxValueTable(theMaxValueTable)
{
	// Nothing else to do for now.
}

//-----------------------------------------------------------------
// Class default destructor.
PM_ControlPeriodRmonGauge::~PM_ControlPeriodRmonGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_ControlPeriodRmonGauge::StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag)
{
	// Call corresponding method in base class
	PM_ControlPeriod::StartNewCurrentPeriod( newCurrentPeriod, theInvalidFlag );

	// Reset value registers of the new current period for a new accumulation value.
	if( !((*GetConfigRegion())[myIndex].GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL)) )
	{
		// If accumulation is enabled then override the values set by the base class
		// with the last utilization value.
		uint32 lastUtilization = myStatusRmon.GetLastUtilization();
		if( lastUtilization > myMaxValueTable[PM_TypeRmonGauge::PM_UTIL].UnsignedValue)
		{
			lastUtilization = myMaxValueTable[PM_TypeRmonGauge::PM_UTIL].UnsignedValue;
		}
		(*GetCurrentValueRegion())[myIndex].ResetAll( lastUtilization );
	}
 
	// Reset the history state in the appropriate RMON status object.
	myStatusRmon.EndOfPeriod();
}
