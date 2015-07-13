/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     December 21, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that computes the PM Parameters for RMON counters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <EPM/src/PM_RulesRmonCounter.h>
#include <EPM/src/PM_AccPeriodRmonCounter.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_ProcessorRmonCounter.h>


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C1F9DED0308
PM_ProcessorRmonCounter::PM_ProcessorRmonCounter(PM_GenericApplication& theGenericApplication,
                                   uint16                 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_RMON_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C1F9DED0313
PM_ProcessorRmonCounter::~PM_ProcessorRmonCounter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC723803B3
void PM_ProcessorRmonCounter::CreateActionsInstances()
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
        // Add to the vector the Parameters Data class.
        myRules.push_back(new PM_RulesRmonCounter(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodRmonCounter(myGenericApplication,
                                                               PM_TypeRmonCounter::GetMaxValueTableRmon15M(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_RMON_STRING,
                                                    0,
                                                    false));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodRmonCounter(myGenericApplication,
                                                               PM_TypeRmonCounter::GetMaxValueTableRmonDay(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_RMON_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    false));

    }

}
