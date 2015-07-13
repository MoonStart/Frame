/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   The class to update TCM PM.
 --------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <T6100/T6100_CardIf.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_TcmCounters.h>
#include <Monitoring/MON_TcmConfig.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Tcm.h>
#include <Configuration/CFG_Odu.h>

#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <EPM/src/PM_AccPeriodTcm.h>
#include <PM/PM_GenericApplication.h>
#include <EPM/PM_BbCountTcm.h>
#include <EPM/PM_BbDefectTcm.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_TcmSubApplication.h>
#include <EPM/src/PM_RulesTcm.h>
#include <CommonTypes/CT_OduDefinitions.h>

#include <TsPii/TSPII_TcmIf.h>
#include <TsPii/TSPII_SubApplication.h>


//-----------------------------------------------------------------
// Class constructor.
PM_RulesTcm::PM_RulesTcm (PM_GenericApplication&  theGenericApplication,
                          uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeTcm::GetMaxNbParamsNoHighOrder64Bits()),
    myDefectTcm( (*myGenericApplication.GetRegionDefectTcm())[theIndex]),
    myCounterTcm( (*myGenericApplication.GetRegionCountTcm())[theIndex]),
    myXYvalue( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] )
{
    Init();
}

//-----------------------------------------------------------------
// Class default destructor.
PM_RulesTcm::~PM_RulesTcm ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_RulesTcm::Init()
{
    myDefect = false;
    myFirstTime = true;
    mySignalType = CT_TEL_SIGNAL_UNKNOWN;
    myTcmMode = CT_TCM_MODE_UNKNOWN;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
void PM_RulesTcm::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage)
{
    // Configuration reference.
    CFG_AppIf* configApp = (CFG_AppIf *)(myGenericApplication.GetCfgApplicationPtr());
    CFG_Tcm & configRef = dynamic_cast<CFG_Tcm&>((*(configApp->GetCfgRegion()))[myIndex]);

    // Monitoring counters registers.
    MON_TcmCounters  &countersObject = (MON_TcmCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[myIndex];

    // Monitoring config .
    MON_TcmConfig  &configObject = (MON_TcmConfig &)(*(myGenericApplication.GetMonApplication().GetConfigRegion()))[myIndex];

    // Parameter index.
    uint32          param;

    // Y value according to signal type.
    uint32          XYvalue;

    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeTcm::PM_PARAM_NUM];

    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeTcm::PM_PARAM_NUM];

    // Group of failures (ored).
    bool            failuresGroup;

    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;

    CT_TEL_SignalType signalType = CT_TEL_SIGNAL_UNKNOWN;

    // Alarm reference.
    ALM_FailureBase &almTcmRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmTcmApplication().GetFilteredRegionPtr()))[myIndex];

    if( configApp )
    {
        // Set signal type based on TCM level and direction.
        CT_ODU_Identifier tcmId = configRef.GetTcmIdentifier();
        switch( tcmId.GetOduKvalueEnum() )
        {
        case CT_ODU_Layer0:
            signalType = (tcmId.GetOduDirection() == CT_ODU_Direction_A) ? CT_TEL_SIGNAL_ODU0TA : CT_TEL_SIGNAL_ODU0TB;
            break;

        case CT_ODU_Layer1:
            signalType = (tcmId.GetOduDirection() == CT_ODU_Direction_A) ? CT_TEL_SIGNAL_ODU1TA : CT_TEL_SIGNAL_ODU1TB;
            break;

        case CT_ODU_Layer2:
            signalType = (tcmId.GetOduDirection() == CT_ODU_Direction_A) ? CT_TEL_SIGNAL_ODU2TA : CT_TEL_SIGNAL_ODU2TB;
            break;

        case CT_ODU_Layer3:
            signalType = (tcmId.GetOduDirection() == CT_ODU_Direction_A) ? CT_TEL_SIGNAL_ODU3TA : CT_TEL_SIGNAL_ODU3TB;
            break;

        case CT_ODU_Layer4:
            signalType = (tcmId.GetOduDirection() == CT_ODU_Direction_A) ? CT_TEL_SIGNAL_ODU4TA : CT_TEL_SIGNAL_ODU4TB;
            break;

        case CT_ODU_LayerF:
            signalType = (tcmId.GetOduDirection() == CT_ODU_Direction_A) ? CT_TEL_SIGNAL_ODUFTA : CT_TEL_SIGNAL_ODUFTB;
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
    }

    // For different flavors of TCM
    switch(signalType)
    {
    case CT_TEL_SIGNAL_ODU0TA:
    case CT_TEL_SIGNAL_ODU0TB:
            XYvalue = myXYvalue.GetXvalueOtuOduLayer0T();
            break;

    case CT_TEL_SIGNAL_ODU1TA:
    case CT_TEL_SIGNAL_ODU1TB:
            XYvalue = myXYvalue.GetXvalueOtuOduLayer1T();
            break;

    case CT_TEL_SIGNAL_ODU2TA:
    case CT_TEL_SIGNAL_ODU2TB:
            XYvalue = myXYvalue.GetXvalueOtuOduLayer2T();
            break;

    case CT_TEL_SIGNAL_ODU3TA:
    case CT_TEL_SIGNAL_ODU3TB:
            XYvalue = myXYvalue.GetXvalueOtuOduLayer3T();
            break;

    case CT_TEL_SIGNAL_ODU4TA:
    case CT_TEL_SIGNAL_ODU4TB:
            XYvalue = myXYvalue.GetXvalueOtuOduLayer4T();
            break;
    
    case CT_TEL_SIGNAL_ODUFTA:
    case CT_TEL_SIGNAL_ODUFTB:
        {
            // Get the ODUF on which ODUFT is created, and then get expected-rate.
            // Note: ODUF is share with ODU0.
            PM_TcmSubApplication & aTcmSubApp = dynamic_cast<PM_TcmSubApplication&>(myGenericApplication);
            T6100_TelecomIf& theOduApp = aTcmSubApp.GetCardContext().GetOduIf();
            CFG_AppIf& aCfgApp = theOduApp.GetCfgPortSideApp((CT_IntfId)CT_PORT_SIDE_30);
            CFG_Odu& aCfgOdu   = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[configRef.GetOduBbIndex()]);
            uint32 expRate     = aCfgOdu.GetExpectedSignalRate();
            
            XYvalue = 0.15*expRate*10/122368;
        }
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
        for (param = 0; param < PM_TypeTcm::GetMaxNbParamsNoHighOrder64Bits(); param++)
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
    myDefect = (myDefectTcm.EverPresentAIS() ||
                myDefectTcm.EverPresentLCK() ||
                myDefectTcm.EverPresentOCI() ||
                myDefectTcm.EverPresentLTC());

    if(configObject.GetLayerFailOnTIM())
    {
        myDefect = myDefect | myDefectTcm.EverPresentTIM();
    }
    
    
    //Bip error will be reported when TCM mode changed
    //Check TSPII to determine whether TCM mode changed
    //Once found changed, force clear any defect and bip error
    //to not allow ES SES increase.
    TSPII_TcmRegion* TcmRegion = NULL;
    TcmRegion = TSPII_SubApplication::GetInstance()->GetTcm();
    if( TcmRegion && (myTcmMode != (*TcmRegion)[myIndex].GetTCMMode()) )
    {
        myDefect = false;
        myCurrentValueParam[PM_TypeTcm::PM_CV].UnsignedValue = 0;
        myTcmMode = (*TcmRegion)[myIndex].GetTCMMode();
    }
    else
    {
        myCurrentValueParam[PM_TypeTcm::PM_CV].UnsignedValue = myCounterTcm.GetBIP();
    }
        myCurrentValueParam[PM_TypeTcm::PM_SES].UnsignedValue = // Bump up by 1 sec?
            myDefect || (myCurrentValueParam[PM_TypeTcm::PM_CV].UnsignedValue >= XYvalue);
        myCurrentValueParam[PM_TypeTcm::PM_ES].UnsignedValue = // Bump up by 1 sec?
            myDefect || (myCurrentValueParam[PM_TypeTcm::PM_CV].UnsignedValue > 0);

    // Prime the UAS FSM.
    myCurrentValueParam[PM_TypeTcm::PM_UAS].UnsignedValue = 1;

    // Accumulation of CV is masked by some defects and SES.
    if ( myCurrentValueParam[PM_TypeTcm::PM_SES].UnsignedValue )
    {
        myCurrentValueParam[PM_TypeTcm::PM_CV].UnsignedValue = 0;
    }

    // Accumulation of CV/EB, ES and SES are suppressed by IAE defect
    if( myDefectTcm.EverPresentIAE() )
    {
        myCurrentValueParam[PM_TypeTcm::PM_CV].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeTcm::PM_ES].UnsignedValue = 0;
        myCurrentValueParam[PM_TypeTcm::PM_SES].UnsignedValue = 0;
    }

    if (myDefect)
    {
        //Refresh all counter of lower level
        myCounterTcm.Update(countersObject);
    }

    //
    // Determine TCA filtering state:
    //

    // Determine failures group state.
    failuresGroup = (almTcmRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_TCM) ||
                     almTcmRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_TCM));

    // Filter parameters TCA,when Upper Layer Service Affecting (2.5s),
    // Upper Layer None Service Affecting (90s), .
    filteringStateFirstStage[PM_TypeTcm::PM_CV] =  failuresGroup;
    filteringStateSecondStage[PM_TypeTcm::PM_CV] = almTcmRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_TCM);

    filteringStateFirstStage[PM_TypeTcm::PM_SES] =  failuresGroup;
    filteringStateSecondStage[PM_TypeTcm::PM_SES] = almTcmRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_TCM);

    filteringStateFirstStage[PM_TypeTcm::PM_ES] =  filteringStateFirstStage[PM_TypeTcm::PM_SES];
    filteringStateSecondStage[PM_TypeTcm::PM_ES] = almTcmRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_TCM);

    filteringStateFirstStage[PM_TypeTcm::PM_UAS] =  failuresGroup;
    filteringStateSecondStage[PM_TypeTcm::PM_UAS] = false;

    //Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}
