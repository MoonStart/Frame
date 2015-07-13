/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   Process that computes the PM Parameters of Near-End SONET/SDH
                Multiplex Section.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/src/PM_RulesOptCounter.h>
#include <PM/src/PM_AccPeriodOptCounter.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM_GenericApplication.h>
#include <PM/PM_ProcessorOptCounter.h>

//-----------------------------------------------------------------
// Class constructor.
PM_ProcessorOptCounter::PM_ProcessorOptCounter(PM_GenericApplication& theGenericApplication,
                                             uint16                 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_OPT_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
PM_ProcessorOptCounter::~PM_ProcessorOptCounter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_ProcessorOptCounter::CreateActionsInstances()
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
        // Add to the vector the Parameters MsNearEnd class.
        myRules.push_back(new PM_RulesOptCounter(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        // wait for AccPeriodOpt.cpp Created 
        myAccPeriod15m.push_back(new PM_AccumulationPeriodOptCounter(myGenericApplication,
                                                               PM_TypeOptCounter::GetMaxValueTableOpt15M(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OPT_STRING,
                                                    0,
                                                    false));

        // Create an Accumulation Period instance for 1 DAY period.
        // wait for AccPeriodOpt.cpp Created
        myAccPeriodDay.push_back(new PM_AccumulationPeriodOptCounter(myGenericApplication,
                                                               PM_TypeOptCounter::GetMaxValueTableOptDay(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OPT_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    false));

    }

}
