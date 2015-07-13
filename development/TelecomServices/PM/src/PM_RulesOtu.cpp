/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, MRTM and 10G.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The class to update OTU parameters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OtuConfig.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>

#include <PM/src/PM_AccPeriod.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM_GenericApplication.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_BbCountOtu.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbDefectOtu.h>
#include <PM/PM_BbStatusOtu.h>
#include <PM/PM_BbIdf.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_TypeOtu.h>
#include <PM/src/PM_RulesOtu.h>
#include <CsPii/CSPII_CardIF.h>

// HGTMM OTU1e special SES threshold
#define PMA_YVAL_SES_OTU1e    12695
#define PMA_YVAL_SES_OTU1f    12949
#define PMA_YVAL_SES_OTU2e    12748

//
#define PM_BEFEC_SCALE_INVALID   0
#define PM_BEFEC_SCALE_OTU1   8000 
#define PM_BEFEC_SCALE_OTU2   8000 
#define PM_BEFEC_SCALE_OTU3   1000

#define PM_BEFEC_SCALE_CONVERT_BIT_TO_BYTE 8

//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3C9255A90092
PM_RulesOtu::PM_RulesOtu (PM_GenericApplication& theGenericApplication, 
                          uint16                 theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeOtu::GetMaxNbParamsNoHighOrder64Bits()),
    myCounterOtu ( (*myGenericApplication.GetRegionCountOtu())[theIndex]),
    myDefectOtu  ( (*myGenericApplication.GetRegionDefectOtu())[theIndex]),
    myStatusOtu  ( (*myGenericApplication.GetRegionStatusOtu())[theIndex]),
    myYvalue ( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] ),  //????????
    mySignalType(CT_TEL_SIGNAL_UNKNOWN)
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3C9255A900BA
PM_RulesOtu::~PM_RulesOtu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610C03BF
void PM_RulesOtu::Init()
{
    myFirstTime = true;

    // If the signal protection scheme involving the observed OCH facility
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
//##ModelId=3C9255A900BC
void PM_RulesOtu::UpdateRules(bool* theFilteringStateFirstStage, bool* theFilteringStateSecondStage)
{

    CFG_Rs* configRef = (CFG_Rs *) 0;
    configRef         = (CFG_Rs *) &(*(myGenericApplication.GetCfgApplicationPtr()));
    CT_PM_Side aPMSide = myGenericApplication.GetSide();
    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();


    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeOtu::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeOtu::PM_PARAM_NUM];
    // Parameter index.
    uint32          param;
    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Bool for presence of defects
    bool myDefect = false;
	// Group of failures (ored).
    bool            failuresGroup;
    // Number of CV/EBs acceptable based on signal type OTU1,OTU2, or OTU3 
    uint32 YvalueOtu;
    // OTU1, OTU2, OTU3, OTU4
    CT_TEL_SignalType signalType;
	CT_TEL_SignalType aLocalSignalType;

	if ( configRef == 0 )
		aLocalSignalType = CT_TEL_SIGNAL_OTU1;
	else 
	{
		configRef = (CFG_Rs *) &((*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[0]);
		//Get signal type
	    signalType = configRef->GetSignalType();

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

		aLocalSignalType = mySignalType;
	}
    
    // YvalueOtu = myYvalue.GetYvalueOtu1();

    //
    // For different flavors of OTU
    //
    uint32 aBeFECScaler = PM_BEFEC_SCALE_INVALID;

    switch( aLocalSignalType )
    {
        case CT_TEL_SIGNAL_OTU1:
			aBeFECScaler = PM_BEFEC_SCALE_OTU1;
            if( CSPII_CardIF::GetInstance()->GetCardType() == OSM20
             || CSPII_CardIF::GetInstance()->GetCardType() == OMMX 
             || CSPII_CardIF::GetInstance()->GetCardType() == OSM1S)
            {
                YvalueOtu = myYvalue.GetXvalueOtuOduLayer1();
            }
            else
            {
                YvalueOtu = myYvalue.GetYvalueOtu1();
            }
            break;

        case CT_TEL_SIGNAL_OTU2:
	    case CT_TEL_SIGNAL_OTU_TGLAN_WFS://for HDTG OTU2 OVRCLK_FS
	    case CT_TEL_SIGNAL_OTU_TGLAN_WOFS://for HDTG OTU2 OVRCLK_NOFS
	    case CT_TEL_SIGNAL_OTU_TGFC_WOFS://for HDTG OTU2 OVRCLK_FC
            aBeFECScaler = PM_BEFEC_SCALE_OTU2;
            YvalueOtu = myYvalue.GetYvalueOtu2();
            if ( (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_HGTMM) || 
				 (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_HDTG2))
			{
                if(aLocalSignalType == CT_TEL_SIGNAL_OTU_TGLAN_WOFS) // OTU1e
                {
                    YvalueOtu = PMA_YVAL_SES_OTU1e;
                }
                else if(aLocalSignalType == CT_TEL_SIGNAL_OTU_TGFC_WOFS) // OTU1f
                {
                    YvalueOtu = PMA_YVAL_SES_OTU1f;
                }
                else if(aLocalSignalType == CT_TEL_SIGNAL_OTU_TGLAN_WFS) // OTU2e
                {
                    YvalueOtu = PMA_YVAL_SES_OTU2e;
                }
			}
            break;

        case CT_TEL_SIGNAL_OTU3:
            aBeFECScaler = PM_BEFEC_SCALE_OTU3;
            if(CSPII_CardIF::GetInstance()->GetCardFamily() == FGSM_FAM
              || CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_FGTME)
            {
                YvalueOtu = myYvalue.GetXvalueOtuOduLayer3();
            }
            else
            {
                YvalueOtu = myYvalue.GetYvalueOtu3();
            }
            break;

        case CT_TEL_SIGNAL_OTU3e2:
            aBeFECScaler = PM_BEFEC_SCALE_OTU3;
            if(CSPII_CardIF::GetInstance()->GetCardFamily() == FGSM_FAM)
            {
                YvalueOtu = myYvalue.GetXvalueOtuOduLayer3e2();
            }
            else
            {
                YvalueOtu = myYvalue.GetYvalueOtu3();
            }
            break;

        case CT_TEL_SIGNAL_OTU4:
            aBeFECScaler = PM_BEFEC_SCALE_INVALID; // No longer scaled (64bit)!
            YvalueOtu = myYvalue.GetYvalueOtu4();
            break;

        case CT_TEL_SIGNAL_OCH_P:
            aBeFECScaler = PM_BEFEC_SCALE_OTU2;
            YvalueOtu = myYvalue.GetYvalueOtu2();
            if ( ((aCardType == CARD_TYPE_HGTMM || aCardType == CARD_TYPE_HGTMMS) && (aPMSide == CT_PM_PORT_SIDE_12)) ||
                 (aCardType == CARD_TYPE_HGTM) || (aCardType == CARD_TYPE_HGTMS) )
            {
                aBeFECScaler = PM_BEFEC_SCALE_INVALID; // No longer scaled (64bit)!
                YvalueOtu = myYvalue.GetYvalueOtu4();
            }
            break;

        case CT_TEL_SIGNAL_UNKNOWN:
        default:
            // No Y value supported.
            YvalueOtu = PM_NO_TCA_Y_VALUE;
            break;
    }

    // Determine validity state:
    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeOtu::GetMaxNbParamsNoHighOrder64Bits(); param++)
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
    // Determine TCA filtering state:
    //

    // If ALM applications on OTU layer is present ...
    // Filter BE corrected/uncorrected TCA when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s) or if LOF-OTU or TIM-OTU failure is
    // present.
	//
	// Filter CV TCA when Upper Layer Service Affecting (2.5s),
	// Upper Layer None Service Affecting (90s), or TIM-OTU failure is
    // present.
    ALM_AppIf* almApp = myGenericApplication.GetAlmOtuApplicationPtr();
    if (almApp) 
    {
        // Alarm reference.
        ALM_FailureBase &almRef = (ALM_FailureBase &)(*(almApp->GetFilteredRegionPtr()))[0];

		failuresGroup = (almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OTU) ||
						 almRef.GetStatus(CT_TelAlarmCondition::ALM_LOF_OTU) ||
						 almRef.GetStatus(CT_TelAlarmCondition::ALM_LOM_OTU) ||
						 almRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_OTU));

        filteringStateFirstStage[PM_TypeOtu::PM_BE] = failuresGroup; 
        filteringStateSecondStage[PM_TypeOtu::PM_BE] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OTU);

        filteringStateFirstStage[PM_TypeOtu::PM_UBE] = filteringStateFirstStage[PM_TypeOtu::PM_BE];
        filteringStateSecondStage[PM_TypeOtu::PM_UBE] = filteringStateSecondStage[PM_TypeOtu::PM_BE];

		filteringStateFirstStage[PM_TypeOtu::PM_CV] = (almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_OTU) || 
                                                       almRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_OTU));
        filteringStateSecondStage[PM_TypeOtu::PM_CV] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OTU);

		filteringStateFirstStage[PM_TypeOtu::PM_ES] = failuresGroup; 
        filteringStateSecondStage[PM_TypeOtu::PM_ES] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OTU);

		filteringStateFirstStage[PM_TypeOtu::PM_SES] = failuresGroup; 
        filteringStateSecondStage[PM_TypeOtu::PM_SES] = almRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OTU);

		filteringStateFirstStage[PM_TypeOtu::PM_UAS] = failuresGroup; 
        filteringStateSecondStage[PM_TypeOtu::PM_UAS] = false;
    }
    else
    {
        filteringStateFirstStage[PM_TypeOtu::PM_BE] = false;
        filteringStateSecondStage[PM_TypeOtu::PM_BE] = false;

        filteringStateFirstStage[PM_TypeOtu::PM_UBE] = false;
        filteringStateSecondStage[PM_TypeOtu::PM_UBE] = false;

		filteringStateFirstStage[PM_TypeOtu::PM_CV] = false;
        filteringStateSecondStage[PM_TypeOtu::PM_CV] = false;

		filteringStateFirstStage[PM_TypeOtu::PM_ES] = false; 
        filteringStateSecondStage[PM_TypeOtu::PM_ES] = false;

		filteringStateFirstStage[PM_TypeOtu::PM_SES] = false; 
        filteringStateSecondStage[PM_TypeOtu::PM_SES] = false;

		filteringStateFirstStage[PM_TypeOtu::PM_UAS] = false; 
        filteringStateSecondStage[PM_TypeOtu::PM_UAS] = false;
    }

    //
    // Apply rules:
    //
    // Monitoring config .
    myDefect = (myDefectOtu.EverPresentLOS()) || (myDefectOtu.EverPresentLOF());

    MON_AppIf* theMonAppPtr = myGenericApplication.GetMonApplicationPtr();
    // For OTNMD, the MonAppPtr is NULL for LINE 2&3 interface.
    if (theMonAppPtr != NULL)
    {
        MON_OtuConfig& configObject = (MON_OtuConfig &)(*(theMonAppPtr->GetConfigRegion()))[0];
        if (configObject.GetLayerFailOnTIM())
        {
            myDefect = myDefect | myDefectOtu.EverPresentTIM();
        }
    } 

    myCurrentValueParam[PM_TypeOtu::PM_PSC].UnsignedValue = myStatusOtu.GetPSC();
    myCurrentValueParam[PM_TypeOtu::PM_PSD].UnsignedValue = myStatusOtu.GetPSD();

    // Code Violations (actually based on BIP8, or block errors, for OTU)
    myCurrentValueParam[PM_TypeOtu::PM_CV].UnsignedValue = myCounterOtu.GetBIP();

    // Errored second
    myCurrentValueParam[PM_TypeOtu::PM_ES].UnsignedValue = myDefect || (myCurrentValueParam[PM_TypeOtu::PM_CV].UnsignedValue > 0);

    // Severely errored second
    myCurrentValueParam[PM_TypeOtu::PM_SES].UnsignedValue = myDefect || (myCurrentValueParam[PM_TypeOtu::PM_CV].UnsignedValue >= YvalueOtu);

    // Unavailable second
    myCurrentValueParam[PM_TypeOtu::PM_UAS].UnsignedValue = 1;

    // Accumulation of BE corrected/uncorrected is masked by some defects.
    if (myDefectOtu.EverPresentLOF())
    {
        myCurrentValueParam[PM_TypeOtu::PM_BE].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeOtu::PM_UBE].UnsignedValue = 0;
    }
    else if ( aBeFECScaler != PM_BEFEC_SCALE_INVALID )
    {
        if(CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_OSM20 ||
           CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_OMMX)  //Only OSM20 and OMMX count on Zeros and Ones
        {
            // Scale the raw correctable block error count by special value according to signal type
            myCurrentValueParam[PM_TypeOtu::PM_BE].UnsignedValue = myCounterOtu.GetBE() / aBeFECScaler;
            if( (myCounterOtu.GetBE() % aBeFECScaler) > 0 )
            {
                // Round up for any fraction thereof.
                myCurrentValueParam[PM_TypeOtu::PM_BE].UnsignedValue += 1;
            }
        }
        else  //Except for OSM20 and OMMX 
        {
            myCurrentValueParam[PM_TypeOtu::PM_BE].UnsignedValue = myCounterOtu.GetBEByte() / aBeFECScaler;
            if( (myCounterOtu.GetBEByte() % aBeFECScaler) > 0 )
            {
                // Round up for any fraction thereof.
                myCurrentValueParam[PM_TypeOtu::PM_BE].UnsignedValue += 1;
            }
        }

        myCurrentValueParam[PM_TypeOtu::PM_UBE].UnsignedValue = myCounterOtu.GetUBE();
    }
    else // Normal Processing...
    {
        myCurrentValueParam[PM_TypeOtu::PM_BE].UnsignedValue = myCounterOtu.GetBEByte();
        myCurrentValueParam[PM_TypeOtu::PM_UBE].UnsignedValue = myCounterOtu.GetUBE();
    }

	// Accumulate CV only if there is no LOS condition.  CV is actually based on BIP8, or block errors, for OTU.
	if ((myDefectOtu.EverPresentLOS())|| myCurrentValueParam[PM_TypeOtu::PM_SES].UnsignedValue)
	{
		myCurrentValueParam[PM_TypeOtu::PM_CV].UnsignedValue = 0;
	}

    // Accumulation of CV/EB, ES and SES are suppressed by IAE defect
    if( myDefectOtu.EverPresentIAE() && !(myDefectOtu.EverPresentLOF()) && !(myDefectOtu.EverPresentLOS()))
    {
        myCurrentValueParam[PM_TypeOtu::PM_CV].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeOtu::PM_ES].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeOtu::PM_SES].UnsignedValue = 0;
    }

	// Update the PSC and PSD as a function of the protection state.
	if( myStatusOtu.EverPresentInProtectionScheme() )
	{
		myCurrentValueParam[PM_TypeOtu::PM_PSC].UnsignedValue = myStatusOtu.GetPSC();

		if( myStatusOtu.EverPresentRevertiveMode() )
		{
			myCurrentValueParam[PM_TypeOtu::PM_PSD].UnsignedValue = myStatusOtu.GetPSD();
		}
		else
		{
			myCurrentValueParam[PM_TypeOtu::PM_PSD].UnsignedValue = 0;
		}
	}
	else
	{
		myCurrentValueParam[PM_TypeOtu::PM_PSC].UnsignedValue = 0;
		myCurrentValueParam[PM_TypeOtu::PM_PSD].UnsignedValue = 0;
	}

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}

//-----------------------------------------------------------------
bool PM_RulesOtu::EverPresentRevertiveMode()
{
	return  myStatusOtu.EverPresentRevertiveMode();
}

//-----------------------------------------------------------------
bool PM_RulesOtu::EverPresentInProtectionScheme()
{
    return myStatusOtu.EverPresentInProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesOtu::EverChangedProtectionScheme()
{
    return myStatusOtu.EverChangedProtectionScheme();
}

//-----------------------------------------------------------------
bool PM_RulesOtu::EverChangedRevertiveMode()
{
    return myStatusOtu.EverChangedRevertiveMode();
}
