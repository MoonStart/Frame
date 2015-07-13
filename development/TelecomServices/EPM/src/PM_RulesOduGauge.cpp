/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   The class to update ODU layer gauge parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_BbStatusOduGauge.h>
#include <EPM/PM_BbDefectOdu.h>
#include <EPM/PM_BbCountOdu.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_OduGaugeSubApplication.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AccPeriodOduGauge.h>
#include <EPM/src/PM_RulesOduGauge.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Monitoring/MON_OduConfig.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Odu.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_RulesOduGauge::PM_RulesOduGauge (PM_GenericApplication&  theGenericApplication,                                    
                                    uint16 theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeOduGauge::PM_PARAM_NUM),
    myStatusOduGauge  ( (*myGenericApplication.GetRegionStatusOduGauge())[theIndex])
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesOduGauge::~PM_RulesOduGauge ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_RulesOduGauge::Init()
{
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();
}

//-----------------------------------------------------------------
void PM_RulesOduGauge::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeOduGauge::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeOduGauge::PM_PARAM_NUM];
    // Parameter index.
    uint32          param;
    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator i;
    // Bool for presence of defects
    bool myDefect = false;
    // Group of failures (ored).
    bool failuresGroup;
	
    if( myIndex >= (myGenericApplication.GetCfgApplicationPtr()->GetCfgRegion()->Size()) ) 
        return;

	CFG_Odu & CFG_OduConfRef = dynamic_cast<CFG_Odu&>((*(myGenericApplication.GetCfgApplicationPtr()->GetCfgRegion()))[myIndex]);
	MON_OduConfig & MON_OduConfRef = (MON_OduConfig &)(*(myGenericApplication.GetMonApplication().GetConfigRegion()))[myIndex];

    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeOduGauge::PM_PARAM_NUM; param++)
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

    filteringStateFirstStage[PM_TypeOduGauge::PM_DELAY]  = false; 
    filteringStateSecondStage[PM_TypeOduGauge::PM_DELAY] = false;

    //
    // Apply rules:
    // MR211698, workround solution:
    // For non-OTN, if no XC exist, return 0 directlly
    if( CFG_OduConfRef.GetOduObjectType() == CT_ODU_POOL_CLIENT_INSIDE_ODU &&
		CFG_OduConfRef.GetIsOduTerm() &&
		!MON_OduConfRef.GetIsConnectedAsSrc() &&
		!MON_OduConfRef.GetIsConnectedAsDst())
    {
        myCurrentValueParam[PM_TypeOduGauge::PM_DELAY].SignedValue = 0;
    }
	else
	{
	    myCurrentValueParam[PM_TypeOduGauge::PM_DELAY].SignedValue = myStatusOduGauge.GetDelay();
	}

    

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}

