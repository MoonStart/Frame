/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   The class to update Tcm layer gauge parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_BbStatusTcmGauge.h>
#include <EPM/PM_BbDefectTcm.h>
#include <EPM/PM_BbCountTcm.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_TcmGaugeSubApplication.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AccPeriodTcmGauge.h>
#include <EPM/src/PM_RulesTcmGauge.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_RulesTcmGauge::PM_RulesTcmGauge (PM_GenericApplication&  theGenericApplication,                                    
                                    uint16 theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeTcmGauge::PM_PARAM_NUM),
    myStatusTcmGauge  ( (*myGenericApplication.GetRegionStatusTcmGauge())[theIndex])
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesTcmGauge::~PM_RulesTcmGauge ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_RulesTcmGauge::Init()
{
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();
}

//-----------------------------------------------------------------
void PM_RulesTcmGauge::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeTcmGauge::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeTcmGauge::PM_PARAM_NUM];
    // Parameter index.
    uint32          param;
    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator i;
    // Bool for presence of defects
    bool myDefect = false;

    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeTcmGauge::PM_PARAM_NUM; param++)
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

    filteringStateFirstStage[PM_TypeTcmGauge::PM_DELAY]  = false; 
    filteringStateSecondStage[PM_TypeTcmGauge::PM_DELAY] = false;

    //
    // Apply rules:
    //

    myCurrentValueParam[PM_TypeTcmGauge::PM_DELAY].SignedValue = myStatusTcmGauge.GetDelay();

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}

