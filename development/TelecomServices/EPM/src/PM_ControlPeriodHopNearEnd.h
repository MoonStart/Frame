/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     July 7, 2008 Larry Wolfrum.
 DESCRIPTION:   HOP Near End Control Period class.
--------------------------------------------------------------------------*/

#ifndef PM_CONTROLPERIODHOPNEAREND_H
#define PM_CONTROLPERIODHOPNEAREND_H

#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_ControlPeriod.h>


using namespace std;

//This class derives the PM parameters with the data given by 
//PM collector. Then it updates the blackboard regions owned 
//by PM processor with the current PM parameter values.
class PM_ControlPeriodHopNearEnd : public  PM_ControlPeriod
{
public:

    //Class default constructor.
    PM_ControlPeriodHopNearEnd(PM_GenericApplication		&theGenericApplication,
							   CT_PM_Period					thePeriod,
							   PM_AccumulationPeriod&		theAccPeriod,
							   uint16						theIndex,
							   char*						theProcessorTypeString,
							   time_t						thePstOffset = 0);

    //Class default destructor.
    virtual ~PM_ControlPeriodHopNearEnd();

protected:

    //This method switches the content of the current and 
    //previous register.
    virtual void SwitchOnPeriod(FC_Time theCurrentTime);

};

#endif //PM_CONTROLPERIODHOPNEAREND_H
