/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The class to update Near-End SONET/SDH MS layer parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_BbStatusOptCounter.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/src/PM_AccPeriodOptCounter.h>
#include <PM/src/PM_RulesOptCounter.h>
#include <PM/PM_BbIdf.h>
#include <PM/PM_BbValue.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_RulesOptCounter::PM_RulesOptCounter (PM_GenericApplication&  theGenericApplication, 
                        uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeOptCounter::PM_PARAM_NUM),
    myStatusOpt ( (*myGenericApplication.GetRegionStatusOptCounter())[theIndex]),
    mySignalType(CT_TEL_SIGNAL_UNKNOWN)
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesOptCounter::~PM_RulesOptCounter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesOptCounter::Init()
{
    myFirstTime = true;    
    // If the signal protection scheme involving the observed MS facility
    // becoms invalid due to creation/deletion, the PM_PSC and PM_PSD 
    // parameters are to be marked invalid. If there is only a revertive mode
    // change, only the PM_PSD parameter is made invalid. To mark one or both
    // of these parameters invalid, we need the IDF objects.
    PM_BbValue& curr15MValue = (*myGenericApplication.Get15MCurrentRegionValue())[myIndex];
    my15MIdf = curr15MValue.GetIdf();;
    PM_BbValue& currDayValue = (*myGenericApplication.GetDayCurrentRegionValue())[myIndex];
    myDayIdf = currDayValue.GetIdf();

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesOptCounter::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Configuration reference.
    CFG_Rs          &configRef = (CFG_Rs &)(*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[0];
    // Parameter index.
    uint32          param;
    // SONET/SDH mode
    bool trueSdhMode = false;
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeOptCounter::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeOptCounter::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;
    // Signal type read.
    CT_TEL_SignalType signalType;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Alarm reference.
    ALM_FailureBase &almOptRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOptApplication().GetFilteredRegionPtr()))[0];
    
    // Retrieve card signal type configuration.
    signalType = configRef.GetSignalType();
    trueSdhMode = configRef.GetSDHTrueMode();

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

    CT_TEL_SignalType aLocalSignalType = mySignalType;

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeOptCounter::PM_PARAM_NUM; param++)
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

    // Update the PSC and PSD as a function of the protection state.
    if( myStatusOpt.EverPresentInProtectionScheme() )
    {
        myCurrentValueParam[PM_TypeOptCounter::PM_PSC].UnsignedValue = myStatusOpt.GetPSC();

        if( myStatusOpt.EverPresentRevertiveMode() )
        {
        myCurrentValueParam[PM_TypeOptCounter::PM_PSD].UnsignedValue = myStatusOpt.GetPSD();
        }
        else
        {
            myCurrentValueParam[PM_TypeOptCounter::PM_PSD].UnsignedValue = 0;
        }
    }
    else
    {
        myCurrentValueParam[PM_TypeOptCounter::PM_PSC].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeOptCounter::PM_PSD].UnsignedValue = 0;
    }
    
    failuresGroup = almOptRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OPT);

    filteringStateFirstStage[PM_TypeOptCounter::PM_PSC] =  failuresGroup;
    filteringStateSecondStage[PM_TypeOptCounter::PM_PSC] = false;

    filteringStateFirstStage[PM_TypeOptCounter::PM_PSD] =  failuresGroup;
    filteringStateSecondStage[PM_TypeOptCounter::PM_PSD] = false;


    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}

//-----------------------------------------------------------------
bool PM_RulesOptCounter::EverPresentRevertiveMode()
{
    return  myStatusOpt.EverPresentRevertiveMode();
}

//-----------------------------------------------------------------
bool PM_RulesOptCounter::EverPresentInProtectionScheme()
{
    return myStatusOpt.EverPresentInProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesOptCounter::EverChangedProtectionScheme()
{
    return myStatusOpt.EverChangedProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesOptCounter::EverChangedRevertiveMode()
{
    return myStatusOpt.EverChangedRevertiveMode();
}
