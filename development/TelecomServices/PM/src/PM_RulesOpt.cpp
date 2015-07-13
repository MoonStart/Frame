/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, February 26, 2003.
 DESCRIPTION:   The class to update Optical parameters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_OptAutoRateLock.h>
#include <Configuration/CFG_OptSubApplication.h>
#include <Configuration/CFG_OptAutomatic.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbStatusOpt.h>
#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_RulesOpt.h>


//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3E6E4CC700FB
PM_RulesOpt::PM_RulesOpt (PM_GenericApplication&    theGenericApplication, 
                          uint16                    theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeOpt::PM_PARAM_NUM),
    myStatusOpt ((*myGenericApplication.GetRegionStatusOpt())[theIndex])

{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3E6E4CC70119
PM_RulesOpt::~PM_RulesOpt ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610C017D
void PM_RulesOpt::Init()
{
    uint32 param;


    for (param = 0; param < PM_TypeOpt::PM_PARAM_NUM; param++)
    {
        myFirstTime[param] = true;
    }

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC70123
void PM_RulesOpt::UpdateRules(bool* theFilteringStateFirstStage, bool* theFilteringStateSecondStage)
{
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeOpt::PM_PARAM_NUM];

    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeOpt::PM_PARAM_NUM];

	// Configuration references
	CFG_OptSubApplication* aOptCfgApp;
	CFG_OptSubApplication* aOppositeOptCfgApp;

    CFG_Opt         *configRefPtr;
    CFG_OptAutomatic *automaticCfgObjectPtr;
	CFG_OptAutoRateLockRegion* aAutoRateLockRegion = (CFG_OptAutoRateLockRegion *) 0;
	CFG_OptCfgRegion* aOppConfigRegion = (CFG_OptCfgRegion *) 0;

	// Determine if we have an OPT configuration application
	if ( (aOptCfgApp = (CFG_OptSubApplication *)myGenericApplication.GetCfgApplicationPtr()) != NULL ) 
	{  
		// Set configuration references.
		CFG_Opt &configRef = (CFG_Opt &)(aOptCfgApp->GetCfgRegion())[0];
		configRefPtr = &configRef;
		CFG_OptAutomatic &automaticCfgObject = (CFG_OptAutomatic &)(aOptCfgApp->GetAutomaticCfgRegion())[0];
		automaticCfgObjectPtr = &automaticCfgObject;
	}

	if ( (aOppositeOptCfgApp = (CFG_OptSubApplication *)myGenericApplication.GetOppositeSideCfgApplication()) != NULL ) 
	{ 
		aAutoRateLockRegion = aOppositeOptCfgApp->GetAutoRateLockRegion();
		aOppConfigRegion = (CFG_OptCfgRegion *) aOppositeOptCfgApp->GetCfgRegion();
	}

    // Alarm reference.
    ALM_FailureBase &almRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmApplication().GetFilteredRegionPtr()))[0];
    // Parameter index.
    uint32          param;
    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator    i;

    //
    // Determine validity state:
    //

    // For all parameters.
    for (param = 0; param < PM_TypeOpt::PM_PARAM_NUM; param++)
    {
        // Verify monitoring state validity change or at first iteration.
        if (myValidityState[param] != myStatusOpt.StatusIsValid(param) || myFirstTime[param])
        {
            // Update my validity.
            myValidityState[param] = myStatusOpt.StatusIsValid(param);

            // Update first time flag.
            myFirstTime[param] = false;

            // Set availability for all Accumulation periods.
            // IDF is available if monitoring status is valid, otherwise it is not available.
            for (i = myVectorOfAccumulationPeriod.begin(); i != myVectorOfAccumulationPeriod.end(); i++)
            {
                (*i)->SetAvailability(param, myValidityState[param]);
            }
        }
    }

    //
    // Determine TCA filtering state:
    //

    // Filter optical TCA when MRTM is attempting to rate lock
    bool aAutoRateLockInProgress = false;
    if (aAutoRateLockRegion && aOppConfigRegion) 
    {
        CFG_Opt& aOppConfigRef = (*aOppConfigRegion)[0];
        CFG_OptAutoRateLock& aOptAutoRateLock = (*aAutoRateLockRegion)[0];
        aAutoRateLockInProgress = (aOppConfigRef.GetAutoRateLockDown()) && (aOptAutoRateLock.GetLockState() == CFG_RATE_NOT_LOCKED);
    }

    // If we have an OPT configuration application, filter laser TCA when
	// laser is off due to either the configuration change or automatic laser
	// shutdown conditions. Also filter TCA when monitoring status is invalid.
	if ( aOptCfgApp != NULL ) 
	{
		filteringStateFirstStage[PM_TypeOpt::PM_OPT] = (!(configRefPtr->GetLaserEnable()) || 
														!myStatusOpt.StatusIsValid(PM_TypeOpt::PM_OPT) ||
														aAutoRateLockInProgress);
		filteringStateFirstStage[PM_TypeOpt::PM_OPT] |= configRefPtr->GetAutomaticLaserShutdown() && automaticCfgObjectPtr->GetAutomaticLaserShutdown();
		filteringStateSecondStage[PM_TypeOpt::PM_OPT] = false;
	}
	else
	{
		// Overwise, filter OPT for OSC
		filteringStateFirstStage[PM_TypeOpt::PM_OPT] = true;
		filteringStateSecondStage[PM_TypeOpt::PM_OPT] = true;
	}

    // Filter optical power received TCA when Upper Layer Service Affecting (2.5s), LOS-OPT (2.5s),
    // Upper Layer None Service Affecting (90s) failure is present or if monitoring
    // status is invalid.
    filteringStateFirstStage[PM_TypeOpt::PM_OPR] = (almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OPT) || 
                                                    almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT) || 
                                                    !myStatusOpt.StatusIsValid(PM_TypeOpt::PM_OPR) ||
                                                    aAutoRateLockInProgress);
    filteringStateSecondStage[PM_TypeOpt::PM_OPR] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OPT);

    filteringStateFirstStage[PM_TypeOpt::PM_DGD] = (almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OPT) ||
                                                    almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT) ||
                                                    !myStatusOpt.StatusIsValid(PM_TypeOpt::PM_DGD) ||
                                                    aAutoRateLockInProgress);
    filteringStateSecondStage[PM_TypeOpt::PM_DGD] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OPT);

    filteringStateFirstStage[PM_TypeOpt::PM_CD] = (almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OPT) ||
                                                    almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT) ||
                                                    !myStatusOpt.StatusIsValid(PM_TypeOpt::PM_CD) ||
                                                    aAutoRateLockInProgress);
    filteringStateSecondStage[PM_TypeOpt::PM_CD] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OPT);

    filteringStateFirstStage[PM_TypeOpt::PM_OSNR] = (almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OPT) ||
                                                    almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT) ||
                                                    !myStatusOpt.StatusIsValid(PM_TypeOpt::PM_OSNR) ||
                                                    aAutoRateLockInProgress);
    filteringStateSecondStage[PM_TypeOpt::PM_OSNR] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OPT);

    //
    // Apply rules:
    //

    // Accumulation of OPT and OPR is masked when status monitoring is invalid.
    if (myStatusOpt.StatusIsValid(PM_TypeOpt::PM_OPT))
    {
        myCurrentValueParam[PM_TypeOpt::PM_OPT].SignedValue = myStatusOpt.GetOPT();
    }
    else
    {
        myCurrentValueParam[PM_TypeOpt::PM_OPT].SignedValue = TRAFFIC_DEFAULT_POWER;
    }

    if (myStatusOpt.StatusIsValid(PM_TypeOpt::PM_OPR))
    {
        myCurrentValueParam[PM_TypeOpt::PM_OPR].SignedValue = myStatusOpt.GetOPR();
    }
    else
    {
        myCurrentValueParam[PM_TypeOpt::PM_OPR].SignedValue = TRAFFIC_DEFAULT_POWER;
    }

    if (myStatusOpt.StatusIsValid(PM_TypeOpt::PM_DGD))
    {
        myCurrentValueParam[PM_TypeOpt::PM_DGD].SignedValue = myStatusOpt.GetDGD();
    }
    else
    {
        myCurrentValueParam[PM_TypeOpt::PM_DGD].SignedValue = 0;
    }

    if (myStatusOpt.StatusIsValid(PM_TypeOpt::PM_CD))
    {
        myCurrentValueParam[PM_TypeOpt::PM_CD].SignedValue = myStatusOpt.GetCD();
    }
    else
    {
        myCurrentValueParam[PM_TypeOpt::PM_CD].SignedValue = 0;
    }

    if (myStatusOpt.StatusIsValid(PM_TypeOpt::PM_OSNR))
    {
        myCurrentValueParam[PM_TypeOpt::PM_OSNR].SignedValue = myStatusOpt.GetOSNR();
    }
    else
    {
        myCurrentValueParam[PM_TypeOpt::PM_OSNR].SignedValue = 0;
    }

    // Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}
