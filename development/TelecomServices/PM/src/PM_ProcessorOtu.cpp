/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     Sebastien Cossette, January 9, 2002.
 DESCRIPTION:   Process that computes the PM Parameters for OTU.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/src/PM_RulesOtu.h>
#include <EPM/src/PM_AccPeriodOtu.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbCountOtu.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_TypeOtu.h>
#include <PM/PM_ProcessorOtu.h>


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C9255A90359
PM_ProcessorOtu::PM_ProcessorOtu(PM_GenericApplication& theGenericApplication,
                                 uint32                 theNumberOfPort):
    PM_Processor(theGenericApplication, (uint16)theNumberOfPort, PM_OTU_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C9255A90377
PM_ProcessorOtu::~PM_ProcessorOtu()
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3CBC72330081
void PM_ProcessorOtu::CreateActionsInstances()
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
        myRules.push_back(new PM_RulesOtu(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodOtu(myGenericApplication,
                                                              PM_TypeOtu::GetMaxValueTableOtu15M(),
                                                              *myRules[portNumber],
                                                              portNumber,
                                                              CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OTU_STRING,
                                                    0,
                                                    false));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodOtu(myGenericApplication,
                                                              PM_TypeOtu::GetMaxValueTableOtuDay(),
                                                              *myRules[portNumber],
                                                              portNumber,
                                                              CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_OTU_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    false));
    }

}
