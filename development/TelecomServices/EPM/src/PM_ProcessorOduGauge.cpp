/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Process that computes the PM Parameters for ODU gauges.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <TimeService/FC_TimeService.h>
#include <PII_TickTimer.h>

#include <EPM/src/PM_RulesOduGauge.h>
#include <EPM/src/PM_AccPeriodOduGauge.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_ProcessorOduGauge.h>

//Two seconds in TickTimer format (in milliseconds)
static FC_Milliseconds PM_TWO_SECONDS_MILLISECONDS = 2000;

//-----------------------------------------------------------------
// Class constructor.
PM_ProcessorOduGauge::PM_ProcessorOduGauge(PM_GenericApplication& theGenericApplication,
                                           uint16 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_ODU_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C1F9DED0313
PM_ProcessorOduGauge::~PM_ProcessorOduGauge ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC723803B3
void PM_ProcessorOduGauge::CreateActionsInstances()
{
    // Create request action for long operation.
    myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
                                                 *myGenericApplication.Get15MCurrentRegionValue(),
                                                 *myGenericApplication.GetDayCurrentRegionValue(),
                                                 *myGenericApplication.Get15MPreviousRegionValue(),
                                                 *myGenericApplication.GetDayPreviousRegionValue(),
                                                  myNumberOfPort);

   for (uint portNumber = 0; portNumber < myNumberOfPort; portNumber++)
   {
       // Create a Rules instance.
       myRules.push_back(new PM_RulesOduGauge(myGenericApplication, portNumber));

       // Create an Accumulation Period instance for 15 MINUTE period.
       myAccPeriod15m.push_back(new PM_AccumulationPeriodOduGauge(myGenericApplication,
                                                                  PM_TypeOduGauge::GetMaxValueTableOdu15M(),
                                                                  *myRules[portNumber],                                                                   
                                                                  portNumber,
                                                                  CT_PM_PERIOD_15_MINUTES));

       myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                   CT_PM_PERIOD_15_MINUTES,
                                                   *myAccPeriod15m[portNumber],
                                                   portNumber,
                                                   PM_ODU_STRING,
                                                   0,
                                                   false));

       // Create an Accumulation Period instance for 1 DAY period.
       myAccPeriodDay.push_back(new PM_AccumulationPeriodOduGauge(myGenericApplication,
                                                                  PM_TypeOduGauge::GetMaxValueTableOduDay(),
                                                                  *myRules[portNumber],                                                                   
                                                                  portNumber,
                                                                  CT_PM_PERIOD_1_DAY));

       myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                   CT_PM_PERIOD_1_DAY,
                                                   *myAccPeriodDay[portNumber],
                                                   portNumber,
                                                   PM_ODU_STRING,
                                                   GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                   false));


    }
}

