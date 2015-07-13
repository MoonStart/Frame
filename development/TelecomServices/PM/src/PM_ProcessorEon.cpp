/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   Process that computes the PM Parameters EON.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/src/PM_RulesEon.h>
#include <PM/src/PM_AccPeriodCounter.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM_GenericApplication.h>
#include <PM/PM_ProcessorEon.h>


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3FA1610A0047
PM_ProcessorEon::PM_ProcessorEon(PM_GenericApplication& theGenericApplication,
                                 uint16                 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_EON_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3FA1610A0058
PM_ProcessorEon::~PM_ProcessorEon ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610A005A
void PM_ProcessorEon::CreateActionsInstances()
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
        // Add to the vector the Parameters EON class.
        myRules.push_back(new PM_RulesEon(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodCounter(myGenericApplication,
                                                                  PM_TypeEon::GetMaxValueTableEon15M(),
                                                                  *myRules[portNumber],
                                                                  PM_TypeEon::PM_PARAM_NUM,
                                                                  portNumber,
                                                                  CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_EON_STRING));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodCounter(myGenericApplication,
                                                                  PM_TypeEon::GetMaxValueTableEonDay(),
                                                                  *myRules[portNumber],
                                                                  PM_TypeEon::PM_PARAM_NUM,
                                                                  portNumber,
                                                                  CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_EON_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY) ));

    }

}
