/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004   Hemant Thakkar
 DESCRIPTION:   Process that computes the PM Parameters of GFP.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/src/PM_RulesGfp.h>
#include <PM/src/PM_AccPeriodGfp.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM_GenericApplication.h>
#include <PM/PM_ProcessorGfp.h>


//-----------------------------------------------------------------
// Class constructor.
PM_ProcessorGfp::PM_ProcessorGfp(PM_GenericApplication& theGenericApplication,
                                 uint16                 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_GFP_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
PM_ProcessorGfp::~PM_ProcessorGfp ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_ProcessorGfp::CreateActionsInstances()
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
        // Add to the vector the Parameters Gfp class.
        myRules.push_back(new PM_RulesGfp(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodGfp(myGenericApplication,
                                                              PM_TypeGfp::GetMaxValueTableGfp15M(),
                                                              *myRules[portNumber],
                                                              portNumber,
                                                              CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_MS_NE_STRING));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodGfp(myGenericApplication,
                                                              PM_TypeGfp::GetMaxValueTableGfpDay(),
                                                              *myRules[portNumber],
                                                              portNumber,
                                                              CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_MS_NE_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY) ));

    }

}
