/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     January 24, 2006 Larry Wolfrum.
 DESCRIPTION:   OTU Gauge Control period class.
--------------------------------------------------------------------------*/
#if 0
#ifndef PM_CONTROLPERIODOTUGAUGE_H
#define PM_CONTROLPERIODOTUGAUGE_H

#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <PM/PM_BbStatusOtu.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_ControlPeriod.h>


using namespace std;

//This class derives the PM parameters with the data given by 
//PM collector. Then it updates the blackboard regions owned 
//by PM processor with the current PM parameter values.
class PM_ControlPeriodOtuGauge : public  PM_ControlPeriod
{
public:

    //Class default constructor.
    PM_ControlPeriodOtuGauge(PM_GenericApplication		&theGenericApplication,
							  CT_PM_Period				thePeriod,
							  PM_AccumulationPeriod&	theAccPeriod,
							  uint16					theIndex,
							  char*						theProcessorTypeString,
							  time_t thePstOffset = 0);

    //Class default destructor.
    virtual ~PM_ControlPeriodOtuGauge();

protected:

    //Starts a new period by calling the corresponding base class
	//method and then causing the corresponding OTU gauge status
	// object to reset its history state.
    virtual void StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag = false);

private:

    PM_BbStatusOtu&  myStatusOtu;
    
};

#endif //PM_CONTROLPERIODOTUGAUGE_H

#endif
