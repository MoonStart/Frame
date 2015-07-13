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
#include <Monitoring/MON_MsCounters.h>
#include <Monitoring/MON_MsConfig.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_BbCountMsNearEnd.h>
#include <PM/PM_BbDefectMsNearEnd.h>
#include <PM/PM_BbFailureMsNearEnd.h>
#include <PM/PM_BbStatusMsNearEnd.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_MsNearEndSubApplication.h>
#include <PM/src/PM_AccPeriodMsNearEnd.h>
#include <PM/src/PM_RulesMsNearEnd.h>
#include <PM/PM_BbIdf.h>
#include <PM/PM_BbValue.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_RulesMsNearEnd::PM_RulesMsNearEnd (PM_GenericApplication&  theGenericApplication, 
                        uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeMsNearEnd::PM_PARAM_NUM),
    myDefectMsNearEnd  ( (*myGenericApplication.GetRegionDefectMsNearEnd())[theIndex]),
    myCounterMsNearEnd ( (*myGenericApplication.GetRegionCountMsNearEnd())[theIndex]),
    myFailureMsNearEnd ( (*myGenericApplication.GetRegionFailureMsNearEnd())[theIndex]),
    myStatusMsNearEnd ( (*myGenericApplication.GetRegionStatusMsNearEnd())[theIndex]),
    myXYvalue      ( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] ),
    mySignalType(CT_TEL_SIGNAL_UNKNOWN)
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesMsNearEnd::~PM_RulesMsNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesMsNearEnd::Init()
{
    myDefect = false;
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
void PM_RulesMsNearEnd::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Monitoring counters registers.
    MON_MsCounters  &countersObject = (MON_MsCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[myIndex];
    // Configuration reference.
    CFG_Rs          &configRef = (CFG_Rs &)(*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[0];
    // Parameter index.
    uint32          param;
    // X value according to signal type.
    uint32          XYvalue;
    // SONET/SDH mode
    bool trueSdhMode = false;
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeMsNearEnd::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeMsNearEnd::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;
    // Signal type read.
    CT_TEL_SignalType signalType;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Alarm reference.
    ALM_FailureBase &almMsRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmMsApplication().GetFilteredRegionPtr()))[0];
    PM_MsNearEndSubApplication& msNearEndApp = dynamic_cast<PM_MsNearEndSubApplication&>(myGenericApplication);
    MON_OptSubApplication* aMonOptApp = NULL;
    MON_AppIf* aMonAppIf;

    if( (aMonAppIf = msNearEndApp.GetCardContext().GetOptIf().GetMonPortSideAppPtr( myAutoRateLock.ConvertPmSideToCtIfId( msNearEndApp.GetSide() ) )) != NULL )
    {
        aMonOptApp = dynamic_cast<MON_OptSubApplication*>(aMonAppIf);
    }

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

    //-----------------------------------------------------------------
    // If GOPT and Autorate lock is supported, adjust the signal type.
    //-----------------------------------------------------------------
    if( (aMonOptApp != NULL) && (aMonOptApp->GetAutoRateLockSupported()) && (mySignalType == CT_TEL_SIGNAL_GOPT) )
    {
        aLocalSignalType = myAutoRateLock.GetAutoRateLockSignalType(msNearEndApp.GetCardContext(), 
                                                                    aLocalSignalType);
    }

    // Get the X value according to card signal rate configuration.
    // Use local variable to include the case where auto rate lock has locked
    // on to a rate (so we don't want to use GOPT).
    
    switch(aLocalSignalType)
    {
        case CT_TEL_SIGNAL_OC3:
        case CT_TEL_SIGNAL_STM1:
            if( trueSdhMode )
            {
                XYvalue = myXYvalue.GetYvalueStm1Ms();
            }
            else
            {
                XYvalue = myXYvalue.GetXvalueOc3Ms();
            }
            break;
        case CT_TEL_SIGNAL_OC12: 
        case CT_TEL_SIGNAL_STM4:
            if( trueSdhMode )
            {
                XYvalue = myXYvalue.GetYvalueStm4Ms();
            }
            else
            {
                XYvalue = myXYvalue.GetXvalueOc12Ms();
            }
            break;
        case CT_TEL_SIGNAL_OC48: 
        case CT_TEL_SIGNAL_STM16:
            if( trueSdhMode )
            {
                XYvalue = myXYvalue.GetYvalueStm16Ms();
            }
            else
            {
                XYvalue = myXYvalue.GetXvalueOc48Ms();
            }
            break;
        case CT_TEL_SIGNAL_OC192: 
        case CT_TEL_SIGNAL_STM64:
        case CT_TEL_SIGNAL_TGBEP:
            if( trueSdhMode )
            {
                XYvalue = myXYvalue.GetYvalueStm64Ms();
            }
            else
            {
                XYvalue = myXYvalue.GetXvalueOc192Ms();
            }
            break;
        case CT_TEL_SIGNAL_OC768: 
        case CT_TEL_SIGNAL_STM256:
            if( trueSdhMode )
            {
                XYvalue = myXYvalue.GetYvalueStm256Ms();
            }
            else
            {
                XYvalue = myXYvalue.GetXvalueOc768Ms();
            }
            break;
        default:
            // No X value supported.
            XYvalue = PM_NO_TCA_X_VALUE;
            break;
    }

    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeMsNearEnd::PM_PARAM_NUM; param++)
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
    // Apply rules:
    //  
    myCurrentValueParam[PM_TypeMsNearEnd::PM_AISS].UnsignedValue = myDefectMsNearEnd.EverPresentAIS();
    myDefect = (myCurrentValueParam[PM_TypeMsNearEnd::PM_AISS].UnsignedValue != 0) ? true : false;
    myCurrentValueParam[PM_TypeMsNearEnd::PM_CV].UnsignedValue = myCounterMsNearEnd.GetBIP();
    myCurrentValueParam[PM_TypeMsNearEnd::PM_SES].UnsignedValue = myDefect || 
            (myCurrentValueParam[PM_TypeMsNearEnd::PM_CV].UnsignedValue >= XYvalue);
    myCurrentValueParam[PM_TypeMsNearEnd::PM_ES].UnsignedValue = myDefect || 
            (myCurrentValueParam[PM_TypeMsNearEnd::PM_CV].UnsignedValue > 0);
    myCurrentValueParam[PM_TypeMsNearEnd::PM_FC].UnsignedValue = myFailureMsNearEnd.EverDeclaredAIS() || 
            myFailureMsNearEnd.EverDeclaredUpperSA();
    myCurrentValueParam[PM_TypeMsNearEnd::PM_UAS].UnsignedValue = 1;

    // Update the PSC and PSD as a function of the protection state.
    if( myStatusMsNearEnd.EverPresentInProtectionScheme() )
    {
        myCurrentValueParam[PM_TypeMsNearEnd::PM_PSC].UnsignedValue = myStatusMsNearEnd.GetPSC();

        if( myStatusMsNearEnd.EverPresentRevertiveMode() )
        {
            myCurrentValueParam[PM_TypeMsNearEnd::PM_PSD].UnsignedValue = myStatusMsNearEnd.GetPSD();
        }
        else
        {
            myCurrentValueParam[PM_TypeMsNearEnd::PM_PSD].UnsignedValue = 0;
        }
    }
    else
    {
        myCurrentValueParam[PM_TypeMsNearEnd::PM_PSC].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeMsNearEnd::PM_PSD].UnsignedValue = 0;
    }

    // Accumulation of CV is masked by some defects and SES.
    if (myDefect || myCurrentValueParam[PM_TypeMsNearEnd::PM_SES].UnsignedValue)
    {
        myCurrentValueParam[PM_TypeMsNearEnd::PM_CV].UnsignedValue = 0;
    }

    if (myDefect)
    {
        //Refresh all counter of lower level
        myCounterMsNearEnd.Update(countersObject);
    }

    //
    // Determine TCA filtering state:
    //

    // Determine failures group state.
    failuresGroup = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_MS);

    // Filter parameters TCA,when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s), .
    filteringStateFirstStage[PM_TypeMsNearEnd::PM_AISS] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_AISS] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsNearEnd::PM_CV] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_CV] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsNearEnd::PM_FC] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_FC] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsNearEnd::PM_SES] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_SES] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsNearEnd::PM_ES] =  filteringStateFirstStage[PM_TypeMsNearEnd::PM_SES];
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_ES] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsNearEnd::PM_UAS] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_UAS] = false;

    filteringStateFirstStage[PM_TypeMsNearEnd::PM_PSC] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_PSC] = false;

    filteringStateFirstStage[PM_TypeMsNearEnd::PM_PSD] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsNearEnd::PM_PSD] = false;

    //------------------------------------------------------------------
    // Apply Auto Rate Lock rules for GOPT/MRTME AutoRateLock features.
    //------------------------------------------------------------------
    if ( ((aMonOptApp != NULL) && (aMonOptApp->GetAutoRateLockSupported()) && (mySignalType == CT_TEL_SIGNAL_GOPT)) )
    {
        myAutoRateLock.AdjustForAutoRateLock( msNearEndApp.GetCardContext(),
                                              myNumberOfParam,
                                              myCurrentValueParam,
                                              filteringStateFirstStage,
                                              filteringStateSecondStage,
                                              msNearEndApp.GetSide() );
    }
    else
    {
        myAutoRateLock.ResetAutoRateLockStates();
    }

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}

bool* PM_RulesMsNearEnd::GetAutoRateInhibitProfile()
{
    return    myAutoRateLock.GetAutoRateInhibitProfile();
}

bool PM_RulesMsNearEnd::IsAutoRateStateRefreshed()
{
    return   myAutoRateLock.IsAutoRateStateRefreshed();
}

//-----------------------------------------------------------------
bool PM_RulesMsNearEnd::EverPresentRevertiveMode()
{
    return  myStatusMsNearEnd.EverPresentRevertiveMode();
}

//-----------------------------------------------------------------
bool PM_RulesMsNearEnd::EverPresentInProtectionScheme()
{
    return myStatusMsNearEnd.EverPresentInProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesMsNearEnd::EverChangedProtectionScheme()
{
    return myStatusMsNearEnd.EverChangedProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesMsNearEnd::EverChangedRevertiveMode()
{
    return myStatusMsNearEnd.EverChangedRevertiveMode();
}
