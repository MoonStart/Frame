/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     TRN.
 AUTHOR   :     December 21, 2005  Larry Wolfrum.
 DESCRIPTION:   The class to update RMON layer counter parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_BbCountRmon.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_RmonCounterSubApplication.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AccPeriodRmonCounter.h>
#include <EPM/src/PM_RulesRmonCounter.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_RulesRmonCounter::PM_RulesRmonCounter (PM_GenericApplication&  theGenericApplication, 
                                          uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeRmonCounter::GetMaxNbParamsNoHighOrder64Bits()),
    myCounterRmon ( (*myGenericApplication.GetRegionCountRmon())[theIndex]),
    mySignalType ( CT_TEL_SIGNAL_UNKNOWN )
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesRmonCounter::~PM_RulesRmonCounter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesRmonCounter::Init()
{
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesRmonCounter::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Parameter index.
    uint32          param;

    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeRmonCounter::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeRmonCounter::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;

	PM_RmonCounterSubApplication& rmonApp = dynamic_cast<PM_RmonCounterSubApplication&>(myGenericApplication);
	MON_OptSubApplication* aMonOptApp = NULL;
	MON_AppIf* aMonAppIf;

	if( (aMonAppIf = rmonApp.GetCardContext().GetOptIf().GetMonPortSideAppPtr( myAutoRateLock.ConvertPmSideToCtIfId( rmonApp.GetSide() ) )) != NULL )
	{
		aMonOptApp = dynamic_cast<MON_OptSubApplication*>(aMonAppIf);
	}

	CT_TEL_SignalType  signalType = CT_TEL_SIGNAL_UNKNOWN;

    CFG_Rs& aCfgRsObj = (CFG_Rs &)(*(rmonApp.GetCardContext().GetRsIf().GetCfgPortSideApp(myAutoRateLock.ConvertPmSideToCtIfId(rmonApp.GetSide())).GetCfgRegion()))[0];

    // Retrieve card signal type configuration.
    signalType = aCfgRsObj.GetSignalType();

    // Verify signal type change.
    if (signalType != mySignalType)
    {
        // Reset PM data for all Accumulation period
        for (i = myVectorOfAccumulationPeriod.begin(); i != myVectorOfAccumulationPeriod.end(); i++)
        {
            (*i)->ResetAll();
        }
        // Update my signal type.
        mySignalType = signalType;
    }

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeRmonCounter::GetMaxNbParamsNoHighOrder64Bits(); param++)
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
		
		myCurrentValueParam[PM_TypeRmonCounter::PM_DROP].UnsignedValue = myCounterRmon.GetDroppedEvents(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_PKT].UnsignedValue = myCounterRmon.GetPackets(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue = myCounterRmon.GetBroadcastPackets(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue = myCounterRmon.GetMulticastPackets(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue = myCounterRmon.GetCrcAlignErrors(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_USPKT].UnsignedValue = myCounterRmon.GetUndersizePackets(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue = myCounterRmon.GetOversizePackets(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_FRAG].UnsignedValue = myCounterRmon.GetFragmentedPackets(); 
		myCurrentValueParam[PM_TypeRmonCounter::PM_JABR].UnsignedValue = myCounterRmon.GetJabbers();

		for (param = 0; param < PM_TypeRmonCounter::PM_PARAM_NUM; param++)
		{
			filteringStateFirstStage[param] = failuresGroup;
			filteringStateSecondStage[param] = failuresGroup;
		}
	}
	else
	{
 		for (param = 0; param < PM_TypeRmonCounter::PM_PARAM_NUM; param++)
		{
			filteringStateFirstStage[param] = failuresGroup;
			filteringStateSecondStage[param] = failuresGroup;
		}

 		for (param = 0; param < PM_TypeRmonCounter::GetMaxNbParamsNoHighOrder64Bits(); param++)
		{
			myCurrentValueParam[param].UnsignedValue = 0;
		}
	}


    //------------------------------------------------------------------
	// Apply Auto Rate Lock rules GOPT/MRTME AutoRateLock features.
    //------------------------------------------------------------------
    //CFG_Rs& aCfgRsObj = (CFG_Rs &)(*(rmonApp.GetCardContext().GetRsIf().GetCfgPortSideApp(myAutoRateLock.ConvertPmSideToCtIfId(rmonApp.GetSide())).GetCfgRegion()))[0];

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
    PM_Rules::UpdateRules( filteringStateFirstStage, filteringStateSecondStage );

}

bool* PM_RulesRmonCounter::GetAutoRateInhibitProfile()
{
	return	myAutoRateLock.GetAutoRateInhibitProfile();
}

bool PM_RulesRmonCounter::IsAutoRateStateRefreshed()
{
	return   myAutoRateLock.IsAutoRateStateRefreshed();
}


