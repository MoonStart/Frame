/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     22 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Process that computes the PM Parameters of ODU.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PII_TickTimer.h>

#include <EPM/src/PM_RulesOdu.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_OduSubApplication.h>
#include <EPM/PM_ProcessorOdu.h>
#include <EPM/src/PM_AccPeriodOdu.h>

//Two seconds in TickTimer format (in milliseconds)
static FC_Milliseconds PM_TWO_SECONDS_MILLISECONDS = 2000;

//-----------------------------------------------------------------
// Class constructor.
PM_ProcessorOdu::PM_ProcessorOdu(PM_GenericApplication& theGenericApplication,
                                 uint16                 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_ODU_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
PM_ProcessorOdu::~PM_ProcessorOdu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_ProcessorOdu::CreateActionsInstances()
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
        // Add to the vector the Parameters HopNearEnd class.
        myRules.push_back(new PM_RulesOdu(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodOdu(myGenericApplication,
                                                               PM_TypeOdu::GetMaxValueTableOdu15M(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_ODU_STRING,
                                                    0,
                                                    false));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodOdu(myGenericApplication,
                                                               PM_TypeOdu::GetMaxValueTableOduDay(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_ODU_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    false));

    }
}
