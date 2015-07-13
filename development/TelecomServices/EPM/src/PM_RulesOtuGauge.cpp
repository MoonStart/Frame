/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     TRN.
 AUTHOR   :     June, 2009  Rick Huang.
 DESCRIPTION:   The class to update OTU layer gauge parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_BbStatusOtuGauge.h>
#include <PM/PM_BbDefectOtu.h>
#include <PM/PM_BbCountOtu.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_OtuGaugeSubApplication.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AccPeriodOtuGauge.h>
#include <EPM/src/PM_RulesOtuGauge.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_RulesOtuGauge::PM_RulesOtuGauge (PM_GenericApplication&  theGenericApplication,                                    
                                    uint16 theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeOtuGauge::PM_PARAM_NUM),
    myStatusOtuGauge  ( (*myGenericApplication.GetRegionStatusOtuGauge())[theIndex])
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesOtuGauge::~PM_RulesOtuGauge ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesOtuGauge::Init()
{
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();

}

void PM_RulesOtuGauge::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeOtuGauge::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeOtuGauge::PM_PARAM_NUM];
    // Parameter index.
    uint32          param;
    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Bool for presence of defects
    bool myDefect = false;
    // Group of failures (ored).
    bool            failuresGroup;

    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeOtuGauge::PM_PARAM_NUM; param++)
        {
            // Set availability for all Accumulation periods.
            // IDF is available if monitoring status is valid, otherwise it is not available.
            for (i = myVectorOfAccumulationPeriod.begin(); i != myVectorOfAccumulationPeriod.end(); i++)
            {
                (*i)->SetAvailability(param, myValidityState[param]);
            }
        }
        // Update first time flag.
        myFirstTime = false;
    }

    //
    // Determine TCA filtering state:
    //

    // If ALM applications on OTU layer is present ...
    // Filter BE corrected/uncorrected TCA when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s) or if LOF-OTU or TIM-OTU failure is
    // present.
    //
    //Filter CV TCA when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s), or TIM-OTU failure is
    // present.
    ALM_AppIf* almApp = myGenericApplication.GetAlmOtuApplicationPtr();
    if (almApp)
    {
        // Alarm reference.
        ALM_FailureBase &almRef = (ALM_FailureBase &)(*(almApp->GetFilteredRegionPtr()))[0];

        failuresGroup = (almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OTU) ||
                         almRef.GetStatus(CT_TelAlarmCondition::ALM_LOF_OTU) ||
                         almRef.GetStatus(CT_TelAlarmCondition::ALM_LOM_OTU) ||
                         almRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_OTU));

        filteringStateFirstStage[PM_TypeOtuGauge::PM_BER]  = failuresGroup; 
        filteringStateSecondStage[PM_TypeOtuGauge::PM_BER] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OTU);
    }
    else
    {
        filteringStateFirstStage[PM_TypeOtuGauge::PM_BER]  = false; 
        filteringStateSecondStage[PM_TypeOtuGauge::PM_BER] = false;
    }

    //
    // Apply rules:
    //

    myCurrentValueParam[PM_TypeOtuGauge::PM_BER].SignedValue = myStatusOtuGauge.GetBER();

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}

