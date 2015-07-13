/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTMs
 AUTHOR   :     23 March 2004   Hemant Thakkar
 DESCRIPTION:   The class to update Near-End SONET/SDH HOP layer parameters. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_HopCounters.h>
#include <Monitoring/MON_HopConfig.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Hop.h>
#include <Configuration/CFG_Rs.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_BbCountHopNearEnd.h>
#include <PM/PM_BbDefectHopNearEnd.h>
#include <PM/PM_BbFailureHopNearEnd.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_HopNearEndSubApplication.h>
#include <PM/src/PM_AccPeriodHopNearEnd.h>
#include <PM/src/PM_RulesHopNearEnd.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_RulesHopNearEnd::PM_RulesHopNearEnd (PM_GenericApplication&  theGenericApplication, 
                        uint16                  theIndex,
                        CT_PM_Sts_Offset		theSts1Offset):
    PM_Rules(theGenericApplication, theIndex, PM_TypeHopNearEnd::PM_PARAM_NUM),
    myDefectHopNearEnd  ( (*myGenericApplication.GetRegionDefectHopNearEnd())[theIndex]),
    myCounterHopNearEnd ( (*myGenericApplication.GetRegionCountHopNearEnd())[theIndex]),
    myFailureHopNearEnd ( (*myGenericApplication.GetRegionFailureHopNearEnd())[theIndex]),
    myXYvalue      ( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] ),
    mySts1Offset   (theSts1Offset)
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesHopNearEnd::~PM_RulesHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesHopNearEnd::Init()
{
    myDefect = false;
    myFirstTime = true;
	mySpeMapping = CT_TEL_HOP_MAPPING_STS1;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesHopNearEnd::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Monitoring counters registers.
    MON_HopCounters  &countersObject = (MON_HopCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[mySts1Offset + myIndex];
    // Configuration reference.
    CFG_Hop          &configRef = (CFG_Hop &)(*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[mySts1Offset + myIndex];
    // Parameter index.
    uint32          param;
    // X value according to signal type.
    uint32          XYvalue;
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeHopNearEnd::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeHopNearEnd::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;
	int32			ptrJustificationCountDiff;
    // Signal type read.
    CT_TEL_HopSpeMapping speMapping = CT_TEL_HOP_MAPPING_STS1;
	// SONET/SDH mode
	bool trueSdhMode = false;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Alarm reference.
    ALM_FailureBase &almHopRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmHopApplication().GetFilteredRegionPtr()))[myIndex];

	PM_HopNearEndSubApplication& aHopApp = dynamic_cast<PM_HopNearEndSubApplication&>(myGenericApplication);
	CFG_Rs& configRsRef	= (CFG_Rs &) (*(aHopApp.GetParentPmSubApp().GetCfgApplication().GetCfgRegion()))[0];

    // Retrieve card signal type configuration.
    speMapping = configRef.GetSpeMapping();
	trueSdhMode = configRsRef.GetSDHTrueMode();

    // Verify signal type change.
    if (speMapping != mySpeMapping)
    {
        // Reset PM data for all Accumulation period
        for (i = myVectorOfAccumulationPeriod.begin(); i != myVectorOfAccumulationPeriod.end(); i++)
        {
            (*i)->ResetAll();
        }
        // Update my signal type.
        mySpeMapping = speMapping;
    }

    
    // Get the X value according to card signal rate configuration.
    switch(mySpeMapping)
    {
		case CT_TEL_HOP_MAPPING_STS1:
		case CT_TEL_HOP_MAPPING_VC3:
			if( trueSdhMode )
			{
				XYvalue = myXYvalue.GetYvalueVc3();
			}
			else
			{
				XYvalue = myXYvalue.GetXvalueSts1();
			}
            break;
        case CT_TEL_HOP_MAPPING_STS3C:
		case CT_TEL_HOP_MAPPING_VC4:
			if( trueSdhMode )
			{
				XYvalue = myXYvalue.GetYvalueVc4();
			}
			else
			{
				XYvalue = myXYvalue.GetXvalueSts3c();
			}
            break;
		case CT_TEL_HOP_MAPPING_STS12C:
		case CT_TEL_HOP_MAPPING_VC4_4:
			if( trueSdhMode )
			{
				XYvalue = myXYvalue.GetYvalueVc4_4c();
			}
			else
			{
				XYvalue = myXYvalue.GetXvalueSts12c();
			} 
            break;
        case CT_TEL_HOP_MAPPING_STS48C:
		case CT_TEL_HOP_MAPPING_VC4_16: 
			if( trueSdhMode )
			{
				XYvalue = myXYvalue.GetYvalueVc4_16c();
			}
			else
			{
				XYvalue = myXYvalue.GetXvalueSts48c();
			}  
            break;
        case CT_TEL_HOP_MAPPING_STS192C:
		case CT_TEL_HOP_MAPPING_VC4_64: 
			if( trueSdhMode )
			{
				XYvalue = myXYvalue.GetYvalueVc4_64c();
			}
			else
			{
				XYvalue = myXYvalue.GetXvalueSts192c();
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
        for (param = 0; param < PM_TypeHopNearEnd::PM_PARAM_NUM; param++)
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
    myDefect = (myDefectHopNearEnd.EverPresentAIS() ||
                myDefectHopNearEnd.EverPresentLOP() ||
                myDefectHopNearEnd.EverPresentPLM() ||
                myDefectHopNearEnd.EverPresentUNEQ());

    myCurrentValueParam[PM_TypeHopNearEnd::PM_CV].UnsignedValue = myCounterHopNearEnd.GetBIP();
    myCurrentValueParam[PM_TypeHopNearEnd::PM_SES].UnsignedValue = myDefect || 
            (myCurrentValueParam[PM_TypeHopNearEnd::PM_CV].UnsignedValue >= XYvalue);
    myCurrentValueParam[PM_TypeHopNearEnd::PM_ES].UnsignedValue = myDefect || 
            (myCurrentValueParam[PM_TypeHopNearEnd::PM_CV].UnsignedValue > 0);
    myCurrentValueParam[PM_TypeHopNearEnd::PM_FC].UnsignedValue = (myFailureHopNearEnd.EverDeclaredAIS()  ||
                                                                   myFailureHopNearEnd.EverDeclaredLOP()  ||
                                                                   myFailureHopNearEnd.EverDeclaredPLM()  ||
                                                                   myFailureHopNearEnd.EverDeclaredUNEQ() ||
																   myFailureHopNearEnd.EverDeclaredUpperSA());
	
	// Prime the UAS FSM.
	myCurrentValueParam[PM_TypeHopNearEnd::PM_UAS].UnsignedValue = 1;

	myCurrentValueParam[PM_TypeHopNearEnd::PM_PJCSGEN].UnsignedValue = ( (myCounterHopNearEnd.GetPPJCGEN() > 0) ||
																	     (myCounterHopNearEnd.GetNPJCGEN() > 0) );

 	myCurrentValueParam[PM_TypeHopNearEnd::PM_PJCSDET].UnsignedValue = ( (myCounterHopNearEnd.GetPPJCDET() > 0) ||
																	     (myCounterHopNearEnd.GetNPJCDET() > 0) );

	ptrJustificationCountDiff = (myCounterHopNearEnd.GetPPJCGEN() - myCounterHopNearEnd.GetNPJCGEN()) -
								(myCounterHopNearEnd.GetPPJCDET() - myCounterHopNearEnd.GetNPJCDET());

	if( ptrJustificationCountDiff >= 0 )
	{
		myCurrentValueParam[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue = ptrJustificationCountDiff;
	}
	else
	{
		myCurrentValueParam[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue = -(ptrJustificationCountDiff);
	}

    // Accumulation of CV is masked by some defects and SES.
    if (myDefect || myCurrentValueParam[PM_TypeHopNearEnd::PM_SES].UnsignedValue)
    {
        myCurrentValueParam[PM_TypeHopNearEnd::PM_CV].UnsignedValue = 0;
    }

    if (myDefect)
    {
        //Refresh all counter of lower level
        myCounterHopNearEnd.Update(countersObject);
    }

    //
    // Determine TCA filtering state:
    //

    // Determine failures group state.
    failuresGroup = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_HOP);

    // Filter parameters TCA,when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s), .
    filteringStateFirstStage[PM_TypeHopNearEnd::PM_CV] =  failuresGroup;
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_CV] = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_HOP);

    filteringStateFirstStage[PM_TypeHopNearEnd::PM_FC] =  failuresGroup;
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_FC] = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_HOP);

    filteringStateFirstStage[PM_TypeHopNearEnd::PM_SES] =  failuresGroup;
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_SES] = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_HOP);

    filteringStateFirstStage[PM_TypeHopNearEnd::PM_ES] =  filteringStateFirstStage[PM_TypeHopNearEnd::PM_SES];
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_ES] = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_HOP);

    filteringStateFirstStage[PM_TypeHopNearEnd::PM_UAS] =  failuresGroup;
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_UAS] = false;

    filteringStateFirstStage[PM_TypeHopNearEnd::PM_PJCSGEN] =  failuresGroup;
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_PJCSGEN] = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_HOP);

    filteringStateFirstStage[PM_TypeHopNearEnd::PM_PJCSDET] =  failuresGroup;
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_PJCSDET] = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_HOP);

    filteringStateFirstStage[PM_TypeHopNearEnd::PM_PJCDIFF] =  failuresGroup;
    filteringStateSecondStage[PM_TypeHopNearEnd::PM_PJCDIFF] = almHopRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_HOP);

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}
