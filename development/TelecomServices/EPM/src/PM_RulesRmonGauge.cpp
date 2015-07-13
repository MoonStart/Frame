/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     TRN.
 AUTHOR   :     December 21, 2005  Larry Wolfrum.
 DESCRIPTION:   The class to update RMON layer gauge parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_BbStatusRmon.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_RmonGaugeSubApplication.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AccPeriodRmonGauge.h>
#include <EPM/src/PM_RulesRmonGauge.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_RulesRmonGauge::PM_RulesRmonGauge (PM_GenericApplication&  theGenericApplication,
									  CT_PM_Period thePeriod,
									  uint16 theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeRmonGauge::PM_PARAM_NUM),
    myStatusRmon ( (*myGenericApplication.GetRegionStatusRmon())[thePeriod])
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesRmonGauge::~PM_RulesRmonGauge ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesRmonGauge::Init()
{
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesRmonGauge::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Parameter index.
    uint32          param;

    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeRmonGauge::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeRmonGauge::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;

	PM_RmonGaugeSubApplication& rmonApp = dynamic_cast<PM_RmonGaugeSubApplication&>(myGenericApplication);
	MON_OptSubApplication* aMonOptApp = NULL;
	MON_AppIf* aMonAppIf;

	if( (aMonAppIf = rmonApp.GetCardContext().GetOptIf().GetMonPortSideAppPtr( myAutoRateLock.ConvertPmSideToCtIfId( rmonApp.GetSide() ) )) != NULL )
	{
		aMonOptApp = dynamic_cast<MON_OptSubApplication*>(aMonAppIf);
	}

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeRmonGauge::PM_PARAM_NUM; param++)
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
    // Apply rules and determine TCA filtering state:
	// 
	
    // Filter parameters and TCA when LOS is detected on the OPT layer.

	ALM_FailureBase &almOptRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOptApplication().GetFilteredRegionPtr()))[0];
	failuresGroup = almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT);

	if( !failuresGroup )
	{
		// No LOS detected

		// Get the utilization value from the status object. The utilization value is a percentage
		// with a range of values of 0 to 100. It is calculated and maintained as an unsigned
		// integer within the status object. It is copied to the SignedValue portion of the
		// myCurrentValueParam union to be properly processed as a gauge value. The assumption
		// here is that the compiler will correctly perform the unsigned to signed type conversion.
		myCurrentValueParam[PM_TypeRmonGauge::PM_UTIL].SignedValue = myStatusRmon.GetUtilization(); 

		for (param = 0; param < PM_TypeRmonGauge::PM_PARAM_NUM; param++)
		{
			filteringStateFirstStage[param] = failuresGroup;
			filteringStateSecondStage[param] = failuresGroup;
		}
	}
	else
	{
 		for (param = 0; param < PM_TypeRmonGauge::PM_PARAM_NUM; param++)
		{
			filteringStateFirstStage[param] = failuresGroup;
			filteringStateSecondStage[param] = failuresGroup;
			myCurrentValueParam[param].SignedValue = 0;
		}
	}

    //------------------------------------------------------------------
	// Apply Auto Rate Lock rules GOPT/MRTME AutoRateLock features.
    //------------------------------------------------------------------
    CFG_Rs& aCfgRsObj = (CFG_Rs &)(*(rmonApp.GetCardContext().GetRsIf().GetCfgPortSideApp(myAutoRateLock.ConvertPmSideToCtIfId(rmonApp.GetSide())).GetCfgRegion()))[0];

	if ( ((aMonOptApp != NULL) && (aMonOptApp->GetAutoRateLockSupported()) && (aCfgRsObj.GetSignalType() == CT_TEL_SIGNAL_GOPT)) )
	{
        myAutoRateLock.AdjustForAutoRateLock( rmonApp.GetCardContext(),
											  myNumberOfParam,
											  myCurrentValueParam,
											  filteringStateFirstStage,
											  filteringStateSecondStage,
                                              rmonApp.GetSide() );
	}
	else
	{
		myAutoRateLock.ResetAutoRateLockStates();
	}

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}

bool* PM_RulesRmonGauge::GetAutoRateInhibitProfile()
{
	return	myAutoRateLock.GetAutoRateInhibitProfile();
}

bool PM_RulesRmonGauge::IsAutoRateStateRefreshed()
{
	return   myAutoRateLock.IsAutoRateStateRefreshed();
}

//-----------------------------------------------------------------
void PM_RulesRmonGauge::ResetParams()
{
    myCurrentValueParam[PM_TypeRmonGauge::PM_UTIL].SignedValue = myStatusRmon.GetLastUtilization();

    // Propagate the reset back toward the source
    myStatusRmon.EndOfPeriod();
}
