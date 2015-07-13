/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 9, 2002.
 DESCRIPTION:   Process that computes the PM Parameters OTS Layer.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/src/PM_RulesLaser.h>
#include <PM/src/PM_AccPeriodGauge.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbStatusLaser.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_TypeLaser.h>
#include <PM/PM_ProcessorLaser.h>


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C1F9DEB0098
PM_ProcessorLaser::PM_ProcessorLaser(PM_GenericApplication& theGenericApplication,
                                     uint32 theNumberOfPort):
    PM_Processor(theGenericApplication, (uint16)theNumberOfPort, PM_LASER_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C1F9DEB00A4
PM_ProcessorLaser::~PM_ProcessorLaser ()
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3CBC723400A0
void PM_ProcessorLaser::CreateActionsInstances()
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
        myRules.push_back(new PM_RulesLaser(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodGauge(myGenericApplication,
                                                                PM_TypeLaser::GetMaxValueTableLaser15M(),
                                                                *myRules[portNumber],
                                                                PM_TypeLaser::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_LASER_STRING,
                                                    0,
                                                    false));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodGauge(myGenericApplication,
                                                                PM_TypeLaser::GetMaxValueTableLaserDay(),
                                                                *myRules[portNumber],
                                                                PM_TypeLaser::PM_PARAM_NUM,
                                                                portNumber,
                                                                CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_LASER_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    false));


    }

}
