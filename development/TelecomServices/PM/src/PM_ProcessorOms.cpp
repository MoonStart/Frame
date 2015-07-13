/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Process that computes the PM Parameters Oms.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/src/PM_AccPeriodGauge.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/src/PM_RulesOms.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbStatusOms.h>
#include <PM/PM_TypeOms.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_ProcessorOms.h>


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3E6E4C9703AF
PM_ProcessorOms::PM_ProcessorOms(PM_GenericApplication& theGenericApplication,
                                 uint32                 theNumberOfPort):
    PM_Processor(theGenericApplication, (uint16)theNumberOfPort, PM_OMS_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3E6E4C9703BA
PM_ProcessorOms::~PM_ProcessorOms ()
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3E6E4C9703C3
void PM_ProcessorOms::CreateActionsInstances()
{
    // Create request action for long operation.
    myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
                                                 *myGenericApplication.Get15MCurrentRegionValue(),
                                                 *myGenericApplication.GetDayCurrentRegionValue(),
                                                 *myGenericApplication.Get15MPreviousRegionValue(),
                                                 *myGenericApplication.GetDayPreviousRegionValue(),
                                                 myNumberOfPort);

    for (uint32 portNumber = 0; portNumber < myNumberOfPort; portNumber++)
    {
        // Create a Rules instance.
        myRules.push_back(new PM_RulesOms(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodGauge(myGenericApplication,
                                                                PM_TypeOms::GetMaxValueTableOms15M(),
                                                                *myRules[portNumber],
                                                                PM_TypeOms::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OMS_STRING));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodGauge(myGenericApplication,
                                                                PM_TypeOms::GetMaxValueTableOmsDay(),
                                                                *myRules[portNumber],
                                                                PM_TypeOms::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OMS_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY) ));

    }

}
