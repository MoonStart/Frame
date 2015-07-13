/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The class to update Far-End SONET/SDH MS layer parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_MsCounters.h>
#include <Monitoring/MON_MsConfig.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_BbCountMsFarEnd.h>
#include <PM/PM_BbDefectMsFarEnd.h>
#include <PM/PM_BbFailureMsFarEnd.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbIdf.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/src/PM_AccPeriodMsFarEnd.h>
#include <PM/src/PM_RulesMsFarEnd.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_RulesMsFarEnd::PM_RulesMsFarEnd (PM_GenericApplication&  theGenericApplication, 
                        uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeMsFarEnd::PM_PARAM_NUM),
    myDefectMsFarEnd  ( (*myGenericApplication.GetRegionDefectMsFarEnd())[theIndex]),
    myCounterMsFarEnd ( (*myGenericApplication.GetRegionCountMsFarEnd())[theIndex]),
    myFailureMsFarEnd ( (*myGenericApplication.GetRegionFailureMsFarEnd())[theIndex]),
    myXvalue      ( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] ),
    mySignalType(CT_TEL_SIGNAL_UNKNOWN)
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesMsFarEnd::~PM_RulesMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesMsFarEnd::Init()
{
    myDefect = false;
    myFirstTime = true;

    // Occurence of a near-end defect causes all far-end parameters to marked 
    // as invalid for the remainder of the collection interval. Thus both
    // 15m and day parameters are flaged as invalid.
    PM_BbValue& curr15MValue = (*myGenericApplication.Get15MCurrentRegionValue())[myIndex];
    my15MIdf = curr15MValue.GetIdf();;
    PM_BbValue& currDayValue = (*myGenericApplication.GetDayCurrentRegionValue())[myIndex];
    myDayIdf = currDayValue.GetIdf();

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesMsFarEnd::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Monitoring counters registers.
    MON_MsCounters  &countersObject = (MON_MsCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[myIndex];
    // Configuration reference.
    CFG_Rs          &configRef = (CFG_Rs &)(*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[0];
    // Parameter index.
    uint32          param;
    // X value according to signal type.
    uint32          Xvalue;
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeMsFarEnd::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeMsFarEnd::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;
    // Signal type read.
    CT_TEL_SignalType signalType = CT_TEL_SIGNAL_OC192;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Alarm reference.
    ALM_FailureBase &almMsRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmMsApplication().GetFilteredRegionPtr()))[0];


    // Retrieve card signal type configuration.
    signalType = configRef.GetSignalType();

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

    
    // Get the X value according to card signal rate configuration.
    switch(mySignalType)
    {
        case CT_TEL_SIGNAL_OC3:
        case CT_TEL_SIGNAL_STM1:
            Xvalue = myXvalue.GetXvalueOc3Ms();
            break;
        case CT_TEL_SIGNAL_OC12: 
        case CT_TEL_SIGNAL_STM4:
            Xvalue = myXvalue.GetXvalueOc12Ms();
            break;
        case CT_TEL_SIGNAL_OC48: 
        case CT_TEL_SIGNAL_STM16:
            Xvalue = myXvalue.GetXvalueOc48Ms();
            break;
        case CT_TEL_SIGNAL_OC192: 
        case CT_TEL_SIGNAL_STM64:
            Xvalue = myXvalue.GetXvalueOc192Ms();
            break;
        default:
            // No X value supported.
            Xvalue = PM_NO_TCA_X_VALUE;
            break;
    }

    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeMsFarEnd::PM_PARAM_NUM; param++)
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
    myDefect = (bool) myDefectMsFarEnd.EverPresentRDI();
    if (myDefectMsFarEnd.EverPresentAIS()) 
    {
        myCurrentValueParam[PM_TypeMsFarEnd::PM_AISS].UnsignedValue = 0; 
        myCurrentValueParam[PM_TypeMsFarEnd::PM_CV].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeMsFarEnd::PM_SES].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeMsFarEnd::PM_ES].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeMsFarEnd::PM_FC].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeMsFarEnd::PM_UAS].UnsignedValue = 0;

        // Mark all current 15m and day parameters as invalid
        for (param = 0; param < PM_TypeMsFarEnd::PM_PARAM_NUM; param++)
        {
            my15MIdf->SetIdf((CT_PM_Parameter) param);
            myDayIdf->SetIdf((CT_PM_Parameter) param);
        }
    }
    else
    {
        myCurrentValueParam[PM_TypeMsFarEnd::PM_AISS].UnsignedValue = myDefectMsFarEnd.EverPresentRDI(); 
        myCurrentValueParam[PM_TypeMsFarEnd::PM_CV].UnsignedValue = myCounterMsFarEnd.GetREI();
        myCurrentValueParam[PM_TypeMsFarEnd::PM_SES].UnsignedValue = myDefect || 
                (myCurrentValueParam[PM_TypeMsFarEnd::PM_CV].UnsignedValue >= Xvalue);
        myCurrentValueParam[PM_TypeMsFarEnd::PM_ES].UnsignedValue = myDefect || 
                (myCurrentValueParam[PM_TypeMsFarEnd::PM_CV].UnsignedValue > 0);
        myCurrentValueParam[PM_TypeMsFarEnd::PM_FC].UnsignedValue = myFailureMsFarEnd.EverDeclaredRDI();
        myCurrentValueParam[PM_TypeMsFarEnd::PM_UAS].UnsignedValue = 1;

        // Accumulation of CV is masked by some defects and SES.
        if (myDefect || myCurrentValueParam[PM_TypeMsFarEnd::PM_SES].UnsignedValue)
        {
            myCurrentValueParam[PM_TypeMsFarEnd::PM_CV].UnsignedValue = 0;
        }
    }

    if (myDefect)
    {
        //Refresh all counter of lower level
        myCounterMsFarEnd.Update(countersObject);
    }

    //
    // Determine TCA filtering state:
    //

    // Determine failures group state.
    failuresGroup = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_MS);

    // Filter parameters TCA,when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s), .
    filteringStateFirstStage[PM_TypeMsFarEnd::PM_AISS] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsFarEnd::PM_AISS] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsFarEnd::PM_CV] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsFarEnd::PM_CV] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsFarEnd::PM_FC] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsFarEnd::PM_FC] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsFarEnd::PM_SES] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsFarEnd::PM_SES] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsFarEnd::PM_ES] =  filteringStateFirstStage[PM_TypeMsFarEnd::PM_SES];
    filteringStateSecondStage[PM_TypeMsFarEnd::PM_ES] = almMsRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_MS);

    filteringStateFirstStage[PM_TypeMsFarEnd::PM_UAS] =  failuresGroup;
    filteringStateSecondStage[PM_TypeMsFarEnd::PM_UAS] = false;

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}
