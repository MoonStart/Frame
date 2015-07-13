/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   The class to update Oms parameters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbStatusOms.h>
#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_RulesOms.h>


//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3E6E4C9600A0
PM_RulesOms::PM_RulesOms (PM_GenericApplication&    theGenericApplication, 
                          uint16                    theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeOms::PM_PARAM_NUM),
    myStatusOms ((*myGenericApplication.GetRegionStatusOms())[theIndex])
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3E6E4C9600B5
PM_RulesOms::~PM_RulesOms ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610B02C6
void PM_RulesOms::Init()
{
    uint32 param;


    for (param = 0; param < PM_TypeOms::PM_PARAM_NUM; param++)
    {
        myFirstTime[param] = true;
    }

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9600DC
void PM_RulesOms::UpdateRules(bool* theFilteringStateFirstStage, bool* theFilteringStateSecondStage)
{
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeOms::PM_PARAM_NUM];
    // Parameter index.
    uint32          param;
    // Alarm reference.
    ALM_FailureBase &almRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmApplication().GetFilteredRegionPtr()))[0];
    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator    i;


    //
    // Determine validity state:
    //

    // For all parameters.
    for (param = 0; param < PM_TypeOms::PM_PARAM_NUM; param++)
    {
        // Verify monitoring state validity change or at first iteration.
        if (myValidityState[param] != myStatusOms.StatusIsValid(param) || myFirstTime[param])
        {
            // Update my validity.
            myValidityState[param] = myStatusOms.StatusIsValid(param);

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

    for (param = 0; param < PM_TypeOms::PM_PARAM_NUM; param++)
    {
        // Filter all parameter TCA when LOS failure is present or 
        // if monitoring is invalid.
        filteringStateFirstStage[param] = (almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OMS) ||
                                           !myStatusOms.StatusIsValid(param));
    }

    //
    // Apply rules:
    //

    // Accumulation of OPT and OPR is masked when status monitoring is invalid.
    if (myStatusOms.StatusIsValid(PM_TypeOms::PM_OPT))
    {
        myCurrentValueParam[PM_TypeOms::PM_OPT].SignedValue = myStatusOms.GetOPT();
    }
    else
    {
        myCurrentValueParam[PM_TypeOms::PM_OPT].SignedValue = TRAFFIC_DEFAULT_POWER;
    }

    if (myStatusOms.StatusIsValid(PM_TypeOms::PM_OPR))
    {
        myCurrentValueParam[PM_TypeOms::PM_OPR].SignedValue = myStatusOms.GetOPR();
    }
    else
    {
        myCurrentValueParam[PM_TypeOms::PM_OPR].SignedValue = TRAFFIC_DEFAULT_POWER;
    }

    // Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage);

}
