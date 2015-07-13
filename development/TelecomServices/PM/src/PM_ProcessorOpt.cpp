/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, December 4, 2001.
 DESCRIPTION:   Process that computes the PM Parameters Optical.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/src/PM_AccPeriodGauge.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/src/PM_RulesOpt.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbStatusOpt.h>
#include <PM/PM_TypeOpt.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_ProcessorOpt.h>


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C1F9DEC01EE
PM_ProcessorOpt::PM_ProcessorOpt(PM_GenericApplication& theGenericApplication,
                                 uint32                 theNumberOfPort):
    PM_Processor(theGenericApplication, (uint16)theNumberOfPort, PM_OPT_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C1F9DEC01F8
PM_ProcessorOpt::~PM_ProcessorOpt ()
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3CBC723603CE
void PM_ProcessorOpt::CreateActionsInstances()
{
    // Create request action for long operation.
    myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
                                                 *myGenericApplication.Get15MCurrentRegionValue(),
                                                 *myGenericApplication.GetDayCurrentRegionValue(),
                                                 *myGenericApplication.Get15MPreviousRegionValue(),
                                                 *myGenericApplication.GetDayPreviousRegionValue(),
                                                 myNumberOfPort);

    bool updatePreviousValue;

    if( myGenericApplication.GetSide() >= CT_PM_A_SIDE &&
        myGenericApplication.GetSide() <= CT_PM_H_SIDE )
    {
        updatePreviousValue = true;
    }
    else
    {
        updatePreviousValue = false;
    }

    for (uint32 portNumber = 0; portNumber < myNumberOfPort; portNumber++)
    {
        // Create a Rules instance.
        myRules.push_back(new PM_RulesOpt(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodGauge(myGenericApplication,
                                                                PM_TypeOpt::GetMaxValueTableOpt15M(),
                                                                *myRules[portNumber],
                                                                PM_TypeOpt::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OPT_STRING,
                                                    0,
                                                    updatePreviousValue));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodGauge(myGenericApplication,
                                                                PM_TypeOpt::GetMaxValueTableOptDay(),
                                                                *myRules[portNumber],
                                                                PM_TypeOpt::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OPT_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    updatePreviousValue));

    }

}
