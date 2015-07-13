/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     26 Oct 2009   Larry Wolfrum
 DESCRIPTION:   The class to update ODU PM. 
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OduCounters.h>
#include <Monitoring/MON_OduConfig.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Odu.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <EPM/src/PM_AccPeriodOdu.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_BbCountOdu.h>
#include <EPM/PM_BbDefectOdu.h>
#include <EPM/PM_BbStatusOdu.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_OduSubApplication.h>
#include <EPM/src/PM_RulesOdu.h>
#include <CommonTypes/CT_OduDefinitions.h>


//-----------------------------------------------------------------
// Class constructor.
PM_RulesOdu::PM_RulesOdu (PM_GenericApplication&  theGenericApplication, 
                          uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeOdu::GetMaxNbParamsNoHighOrder64Bits()),
    myDefectOdu( (*myGenericApplication.GetRegionDefectOdu())[theIndex]),
    myCounterOdu( (*myGenericApplication.GetRegionCountOdu())[theIndex]),
    myStatusOdu ( (*myGenericApplication.GetRegionStatusOdu())[theIndex]),
    myXYvalue( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] )
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesOdu::~PM_RulesOdu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesOdu::Init()
{
    myDefect = false;
    myFirstTime = true;
	mySignalType = CT_TEL_SIGNAL_UNKNOWN;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesOdu::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    if (myIndex >= myGenericApplication.GetCfgApplicationPtr()->GetCfgRegion()->Size())
    {
        return;
    }
    // Configuration reference.
    CFG_Odu& configRef = dynamic_cast<CFG_Odu&>((*(myGenericApplication.GetCfgApplicationPtr()->GetCfgRegion()))[myIndex]);

    // Monitoring counters registers.
    MON_OduCounters  &countersObject = (MON_OduCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[myIndex];

    // Monitoring config .
    MON_OduConfig  &configObject = (MON_OduConfig &)(*(myGenericApplication.GetMonApplication().GetConfigRegion()))[myIndex];

    // Parameter index.
    uint32          param;

    // Y value according to signal type.
    uint32          XYvalue;

    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeOdu::PM_PARAM_NUM];

    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeOdu::PM_PARAM_NUM];

    // Group of failures (ored).
    bool            failuresGroup;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;

	// ODU1, ODU2
	CT_TEL_SignalType signalType = CT_TEL_SIGNAL_UNKNOWN;

    //ODUF
    uint32 expRate = configRef.GetExpectedSignalRate();

    // Alarm reference.
    ALM_FailureBase &almOduRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOduApplication().GetFilteredRegionPtr()))[myIndex];

	// Set signal type based on "K" value
	switch( configRef.GetOduIdentifier().GetOduKvalue() )
	{
	case 0:
		signalType = CT_TEL_SIGNAL_ODU0;
		break;

	case CT_ODU_Layer1:
		signalType = CT_TEL_SIGNAL_ODU1;
		break;

	case CT_ODU_Layer2:
		signalType = CT_TEL_SIGNAL_ODU2;
		break;

	case CT_ODU_Layer3:
		signalType = CT_TEL_SIGNAL_ODU3;
		break;

    case CT_ODU_Layer4:
        signalType = CT_TEL_SIGNAL_ODU4;
        break;

    case CT_ODU_LayerF:
        signalType = CT_TEL_SIGNAL_ODUF;
        break;

	default:
		signalType = CT_TEL_SIGNAL_UNKNOWN;
		break;
	}

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

    // For different flavors of ODU
    switch(signalType)
	{
		case CT_TEL_SIGNAL_ODU0:
			XYvalue = myXYvalue.GetXvalueOtuOduLayer0();
			break;

		case CT_TEL_SIGNAL_ODU1:
			XYvalue = myXYvalue.GetXvalueOtuOduLayer1();
			break;

        case CT_TEL_SIGNAL_ODU2:
            if(configRef.GetClockType() == CT_TEL_CLK_G709)
            {
    			XYvalue = myXYvalue.GetXvalueOtuOduLayer2();
            }
            else
            {
    			XYvalue = myXYvalue.GetXvalueOtuOduLayer2e();
            }
			break;

        case CT_TEL_SIGNAL_ODU3:
            if(configRef.GetClockType() == CT_TEL_CLK_ODU3)
            {
                XYvalue = myXYvalue.GetXvalueOtuOduLayer3();
            }
            else
            {
                XYvalue = myXYvalue.GetXvalueOtuOduLayer3e2();
            }
			break;

        case CT_TEL_SIGNAL_ODU4:
            XYvalue = myXYvalue.GetXvalueOtuOduLayer4();
			break;

        case CT_TEL_SIGNAL_ODUF:
            int32 multiplier;
            multiplier = 10;
            if (CSPII_CardIF::GetInstance()->GetCardFamily() == OSM_FAM)
            {
                multiplier = 1000;
            }
            XYvalue = (0.15*expRate/122368)*multiplier;
			break;

		case CT_TEL_SIGNAL_UNKNOWN:
		default:
			// No Y value supported.
			XYvalue = PM_NO_TCA_Y_VALUE;
			break;
	}

    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeOdu::GetMaxNbParamsNoHighOrder64Bits(); param++)
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
    myDefect = (myDefectOdu.EverPresentAIS() ||
                myDefectOdu.EverPresentLCK() ||
                myDefectOdu.EverPresentOCI());

    if(configObject.GetLayerFailOnTIM())
    {
        myDefect = myDefect | myDefectOdu.EverPresentTIM();
    }

    myCurrentValueParam[PM_TypeOdu::PM_CV].UnsignedValue = myCounterOdu.GetBIP();
    myCurrentValueParam[PM_TypeOdu::PM_SES].UnsignedValue = // Bump up by 1 sec?
        myDefect || (myCurrentValueParam[PM_TypeOdu::PM_CV].UnsignedValue >= XYvalue);
    myCurrentValueParam[PM_TypeOdu::PM_ES].UnsignedValue = // Bump up by 1 sec?
        myDefect || (myCurrentValueParam[PM_TypeOdu::PM_CV].UnsignedValue > 0);

    // Prime the UAS FSM.
    myCurrentValueParam[PM_TypeOdu::PM_UAS].UnsignedValue = 1;

    // Update the PSC and PSD as a function of the protection state.
    if( myStatusOdu.EverPresentInProtectionScheme() )
    {
	    myCurrentValueParam[PM_TypeOdu::PM_PSC].UnsignedValue = myStatusOdu.GetPSC();

	    if( myStatusOdu.EverPresentRevertiveMode() )
	    {
		    myCurrentValueParam[PM_TypeOdu::PM_PSD].UnsignedValue = myStatusOdu.GetPSD();
	    }
	    else
	    {
		    myCurrentValueParam[PM_TypeOdu::PM_PSD].UnsignedValue = 0;
	    }
    }
    else
    {
	    myCurrentValueParam[PM_TypeOdu::PM_PSC].UnsignedValue = 0;
	    myCurrentValueParam[PM_TypeOdu::PM_PSD].UnsignedValue = 0;
    }

    // Accumulation of CV is masked by some defects and SES.
    if (myDefect || myCurrentValueParam[PM_TypeOdu::PM_SES].UnsignedValue)
    {
        myCurrentValueParam[PM_TypeOdu::PM_CV].UnsignedValue = 0;
    }

    if (myDefect)
    {
        //Refresh all counter of lower level
        myCounterOdu.Update(countersObject);
    }

    //
    // Determine TCA filtering state:
    //

    // Determine failures group state.
    failuresGroup = (almOduRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_ODU) ||
                     almOduRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_ODU));

    // Filter parameters TCA,when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s), .
    filteringStateFirstStage[PM_TypeOdu::PM_CV] =  failuresGroup;
    filteringStateSecondStage[PM_TypeOdu::PM_CV] = almOduRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_ODU);

    filteringStateFirstStage[PM_TypeOdu::PM_SES] =  failuresGroup;
    filteringStateSecondStage[PM_TypeOdu::PM_SES] = almOduRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_ODU);

    filteringStateFirstStage[PM_TypeOdu::PM_ES] =  filteringStateFirstStage[PM_TypeOdu::PM_SES];
    filteringStateSecondStage[PM_TypeOdu::PM_ES] = almOduRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_ODU);

    filteringStateFirstStage[PM_TypeOdu::PM_UAS] =  failuresGroup;
    filteringStateSecondStage[PM_TypeOdu::PM_UAS] = false;

    filteringStateFirstStage[PM_TypeOdu::PM_PSC] =  failuresGroup;
    filteringStateSecondStage[PM_TypeOdu::PM_PSC] = false;

    filteringStateFirstStage[PM_TypeOdu::PM_PSD] =  failuresGroup;
    filteringStateSecondStage[PM_TypeOdu::PM_PSD] = false;

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);
}

//-----------------------------------------------------------------
bool PM_RulesOdu::EverPresentRevertiveMode()
{
	return  myStatusOdu.EverPresentRevertiveMode();
}

//-----------------------------------------------------------------
bool PM_RulesOdu::EverPresentInProtectionScheme()
{
    return myStatusOdu.EverPresentInProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesOdu::EverChangedProtectionScheme()
{
    return myStatusOdu.EverChangedProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesOdu::EverChangedRevertiveMode()
{
    return myStatusOdu.EverChangedRevertiveMode();
}
