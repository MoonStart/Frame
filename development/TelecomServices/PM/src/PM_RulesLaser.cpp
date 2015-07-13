/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, February 26, 2003.
 DESCRIPTION:   The class to update Laser parameters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_OptAutomatic.h>
#include <Configuration/CFG_OptAutoRateLock.h>
#include <Configuration/CFG_OptSubApplication.h>

#include <PM_GenericApplication.h>
#include <PM/PM_TypeLaser.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbStatusLaser.h>
#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_RulesLaser.h>


//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3E6E4CD30012
PM_RulesLaser::PM_RulesLaser (PM_GenericApplication&    theGenericApplication, 
                              uint16                    theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeLaser::PM_PARAM_NUM),
    myStatusLaser ((*myGenericApplication.GetRegionStatusLaser())[theIndex])
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3E6E4CD30030
PM_RulesLaser::~PM_RulesLaser ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610D015E
void PM_RulesLaser::Init()
{
    uint32 param;


    for (param = 0; param < PM_TypeLaser::PM_PARAM_NUM; param++)
    {
        myFirstTime[param] = true;
    }

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CD3003A
void PM_RulesLaser::UpdateRules(bool* theFilteringStateFirstStage, bool* theFilteringStageSecondStage)
{
    // Computed state for first stage filtering (2.5 seconds failures).
    bool    filteringStateFirstStage[PM_TypeLaser::PM_PARAM_NUM];
    // Parameter index.
    uint32  param;
    // Configuration reference.
    CFG_Opt &configRef = (CFG_Opt &)(*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[0];    
    CFG_OptAutomatic &automaticCfgObject = (CFG_OptAutomatic &) (*(myGenericApplication.GetCfgApplication().GetAutomaticCfgRegion()))[0];

    CFG_OptAutoRateLockRegion* aAutoRateLockRegion = (CFG_OptAutoRateLockRegion *) 0;
    CFG_OptCfgRegion* aOppConfigRegion = (CFG_OptCfgRegion *) 0;
    CFG_OptSubApplication* aOppositeOptCfgApp = (CFG_OptSubApplication *) myGenericApplication.GetOppositeSideCfgApplication();
    if (aOppositeOptCfgApp) 
    {
        aAutoRateLockRegion = aOppositeOptCfgApp->GetAutoRateLockRegion();
        aOppConfigRegion = (CFG_OptCfgRegion *) aOppositeOptCfgApp->GetCfgRegion();
    }

    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator    i;


    //
    // Determine validity state:
    //

    // For all parameters.
    for (param = 0; param < PM_TypeLaser::PM_PARAM_NUM; param++)
    {
        // Verify monitoring state validity change or at first iteration.
        if (myValidityState[param] != myStatusLaser.StatusIsValid(param) || myFirstTime[param])
        {
            // Update my validity.
            myValidityState[param] = myStatusLaser.StatusIsValid(param);

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
    // Filter laser TCA when laser is off due to either the configuration
    // change or automatic laser shutdown conditions. 

    bool aAutoRateLockInProgress = false;
    if (aAutoRateLockRegion && aOppConfigRegion) 
    {
        CFG_Opt& aOppConfigRef = (*aOppConfigRegion)[0];
        CFG_OptAutoRateLock& aOptAutoRateLock = (*aAutoRateLockRegion)[0];
        aAutoRateLockInProgress = (aOppConfigRef.GetAutoRateLockDown()) && (aOptAutoRateLock.GetLockState() == CFG_RATE_NOT_LOCKED);
    }

    for (param = 0; param < PM_TypeLaser::PM_PARAM_NUM; param++)
    {
       filteringStateFirstStage[param] = configRef.GetAutomaticLaserShutdown() && automaticCfgObject.GetAutomaticLaserShutdown();
       filteringStateFirstStage[param] |= (!(configRef.GetLaserEnable()));
       filteringStateFirstStage[param] |= aAutoRateLockInProgress;
    }

    //
    // Apply rules.
    //
    
    myCurrentValueParam[PM_TypeLaser::PM_LT].SignedValue = myStatusLaser.GetLT();
    myCurrentValueParam[PM_TypeLaser::PM_LBC].SignedValue = myStatusLaser.GetLBC();
    
    // Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage);

}
