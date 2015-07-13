/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Process that computes the PM Parameters Data.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>

#include <PM/src/PM_RulesData.h>
#include <PM/src/PM_AccPeriodData.h>
#include <PM/src/PM_ControlPeriod.h>
#include <PM/src/PM_RequestAction.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_RegionImpVirtual.h>
#include <PM/PM_BbValue.h>
#include <PM_GenericApplication.h>
#include <PM/PM_ProcessorData.h>


//-----------------------------------------------------------------
// Class constructor.
//##ModelId=3C1F9DED0308
PM_ProcessorData::PM_ProcessorData(PM_GenericApplication& theGenericApplication,
                                   uint16                 theNumberOfPort):
    PM_Processor(theGenericApplication, theNumberOfPort, PM_DATA_STRING)
{
    // Nothing to do for now.

}


//-----------------------------------------------------------------
//##ModelId=3C1F9DED0313
PM_ProcessorData::~PM_ProcessorData ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3CBC723803B3
void PM_ProcessorData::CreateActionsInstances()
{
    // Create request action for long operation.
    myRegionRequestAction = new PM_RequestAction(*myGenericApplication.GetRegionRequest(),
                                                 *myGenericApplication.Get15MCurrentRegionValue(),
                                                 *myGenericApplication.GetDayCurrentRegionValue(),
                                                 *myGenericApplication.Get15MPreviousRegionValue(),
                                                 *myGenericApplication.GetDayPreviousRegionValue(),
                                                 myNumberOfPort);

    bool updatePreviousValue;

    if( !((myGenericApplication.GetSide() >= CT_PM_A_SIDE) &&
          (myGenericApplication.GetSide() <= CT_PM_H_SIDE)) &&
        (CSPII_CardIF::GetInstance()->GetCardType() != CARD_TYPE_TRN_10G) &&
        (CSPII_CardIF::GetInstance()->GetCardType() != CARD_TYPE_TRN_MRTM) )
    {
        updatePreviousValue = false;
    }
    else
    {
        updatePreviousValue = true;
    }

    for (uint32 portNumber = 0; portNumber < myNumberOfPort; portNumber++)
    {
        // Add to the vector the Parameters Data class.
        myRules.push_back(new PM_RulesData(myGenericApplication, (uint16)portNumber));

        // Create an Accumulation Period instance for 15 MINUTE period.
        myAccPeriod15m.push_back(new PM_AccumulationPeriodData(myGenericApplication,
                                                               PM_TypeData::GetMaxValueTableData15M(),
                                                               *myRules[portNumber],
                                                               (uint16)portNumber,
                                                               CT_PM_PERIOD_15_MINUTES));

        myControl15m.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_15_MINUTES,
                                                    *myAccPeriod15m[portNumber],
                                                    (uint16)portNumber,
                                                    PM_DATA_STRING,
                                                    0,
                                                    updatePreviousValue));

        // Create an Accumulation Period instance for 1 DAY period.
        myAccPeriodDay.push_back(new PM_AccumulationPeriodData(myGenericApplication,
                                                               PM_TypeData::GetMaxValueTableDataDay(),
                                                               *myRules[portNumber],
                                                               portNumber,
                                                               CT_PM_PERIOD_1_DAY));

        myControlDay.push_back(new PM_ControlPeriod(myGenericApplication,
                                                    CT_PM_PERIOD_1_DAY,
                                                    *myAccPeriodDay[portNumber],
                                                    (uint16)portNumber,
                                                    PM_DATA_STRING,
                                                    GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY),
                                                    updatePreviousValue));

    }

}
