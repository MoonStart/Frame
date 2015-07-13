/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004  Hemant Thakkar.
 DESCRIPTION:   The class to update GFP layer parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <Monitoring/MON_AppIf.h>
//#include <Monitoring/MON_GfpCounters.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Gfp.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <PM_GenericApplication.h>
#include <PM/PM_BbCountGfp.h>
#include <PM/PM_BbDefectGfp.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/src/PM_AccPeriodGfp.h>
#include <PM/src/PM_RulesGfp.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_RulesGfp::PM_RulesGfp (PM_GenericApplication&  theGenericApplication, 
                          uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeGfp::PM_PARAM_NUM),
    myDefectGfp ( (*myGenericApplication.GetRegionDefectGfp())[theIndex]),
    myCounterGfp ( (*myGenericApplication.GetRegionCountGfp())[theIndex]),
    myXvalue      ( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] ),
    mySignalType(CT_TEL_SIGNAL_UNKNOWN)
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesGfp::~PM_RulesGfp ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesGfp::Init()
{
    myDefect = false;
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesGfp::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Monitoring counters registers.
//    MON_GfpCounters  &countersObject = (MON_GfpCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[myIndex];
    // Monitoring configuration object.
    // Parameter index.
    uint32          param;

    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeGfp::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeGfp::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Alarm reference.
    ALM_FailureBase &almGfpRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmGfpApplication().GetFilteredRegionPtr()))[0];
    
    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeGfp::PM_PARAM_NUM; param++)
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
    myDefect = myDefectGfp.EverPresentLOFD();
    myCurrentValueParam[PM_TypeGfp::PM_10B_ERR].UnsignedValue = myCounterGfp.Get10BErr(); 

    // Accumulation of 10B_ERR is masked by LOFD.
    if (myDefect)
    {
        myCurrentValueParam[PM_TypeGfp::PM_10B_ERR].UnsignedValue = 0;
        //myCounterGfp.Update(countersObject);
    }

    //
    // Determine TCA filtering state:
    //

    // Determine failures group state.
    failuresGroup = almGfpRef.GetStatus(CT_TelAlarmCondition::ALM_LOFD_GFP);

    // Filter parameters TCA,when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s), .
    filteringStateFirstStage[PM_TypeGfp::PM_10B_ERR] = failuresGroup;
    filteringStateSecondStage[PM_TypeGfp::PM_10B_ERR] = false;

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}
