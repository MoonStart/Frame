/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     January 24, 2006 Larry Wolfrum.
 DESCRIPTION:   RMON Gauge Control period class.
--------------------------------------------------------------------------*/

#ifndef PM_CONTROLPERIODRMONGAUGE_H
#define PM_CONTROLPERIODRMONGAUGE_H

#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <EPM/PM_BbStatusRmon.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_ControlPeriod.h>


using namespace std;

//This class derives the PM parameters with the data given by 
//PM collector. Then it updates the blackboard regions owned 
//by PM processor with the current PM parameter values.
class PM_ControlPeriodRmonGauge : public  PM_ControlPeriod
{
public:

    //Class default constructor.
    PM_ControlPeriodRmonGauge(PM_GenericApplication		&theGenericApplication,
							  CT_PM_Period				thePeriod,
							  PM_AccumulationPeriod&	theAccPeriod,
							  uint16					theIndex,
							  char*						theProcessorTypeString,
                              CT_PM_Value*              theMaxValueTable,
							  time_t thePstOffset = 0);

    //Class default destructor.
    virtual ~PM_ControlPeriodRmonGauge();

protected:

    //Starts a new period by calling the corresponding base class
	//method and then causing the corresponding RMON gauge status
	// object to reset its history state.
    virtual void StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag = false);

private:

    PM_BbStatusRmon&  myStatusRmon;

    //A pointer to a table that holds maximum values of all PM parameters.
    CT_PM_Value* myMaxValueTable;
};

#endif //PM_CONTROLPERIODRMONGAUGE_H
