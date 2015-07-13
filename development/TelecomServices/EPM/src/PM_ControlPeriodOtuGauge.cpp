/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June, 2009 Rick Huang.
 DESCRIPTION:   OTU Gauge Control period class.
--------------------------------------------------------------------------*/
#if 0
#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/PM_ControlPeriodOtuGauge.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValueOtu.h>
#include <PM/PM_BbCfg.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_ControlPeriodOtuGauge::PM_ControlPeriodOtuGauge (PM_GenericApplication     &theGenericApplication,
													  CT_PM_Period              thePeriod,
													  PM_AccumulationPeriod&    theAccPeriod,
													  uint16                    theIndex,
													  char*                     theProcessorTypeString,
													  time_t                    thePstOffset):
	PM_ControlPeriod( theGenericApplication,
					  thePeriod,
					  theAccPeriod,
					  theIndex,
					  theProcessorTypeString,
					  thePstOffset,
					  false ),
	myStatusOtu( (*myGenericApplication.GetRegionStatusOtu())[thePeriod] )
{
	// Nothing else to do for now.
}

//-----------------------------------------------------------------
// Class default destructor.
PM_ControlPeriodOtuGauge::~PM_ControlPeriodOtuGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_ControlPeriodOtuGauge::StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag)
{
	// Call corresponding method in base class
	PM_ControlPeriod::StartNewCurrentPeriod( newCurrentPeriod, theInvalidFlag );

	// Reset value registers of the new current period for a new accumulation value.
	if( !((*GetConfigRegion())[myIndex].GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL)) )
	{
		// If accumulation is enabled then override the values set by the base class
		// with the last utilization value.
		(*GetCurrentValueRegion())[myIndex].ResetAll();
	}
 
	// Reset the history state in the appropriate OTU status object.
	myStatusOtu.EndOfPeriod();
}

#endif
