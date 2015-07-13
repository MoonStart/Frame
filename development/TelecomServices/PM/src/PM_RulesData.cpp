/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The class to update Data (RS, FICON, ESCON, GbE, GOPT)
                parameters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_RsCounters.h>
#include <Monitoring/MON_RsConfig.h>
#include <Monitoring/MON_OptSubApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_BbCountData.h>
#include <PM/PM_BbDefectData.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_DataSubApplication.h>
#include <PM/src/PM_AccPeriodData.h>
#include <PM/src/PM_RulesData.h>
#include <EPM/src/PM_AutoRateLock.h>
#include <T6100_MainAppIf.h>
#include <T6100_ControllerStatusRegion.h>

// Default Y values for HDTG, MR145699
#define PMA_YVAL_SES_RS_STM64_BLOCK    2400   //Number of BE-RS to have SES-RS in STM64.
#define PMA_YVAL_SES_RS_STM16_BLOCK    2400
#define PMA_YVAL_SES_RS_STM4_BLOCK    2400
#define PMA_YVAL_SES_RS_STM1_BLOCK    2400
#define PMA_YVAL_SES_RS_STM256_BLOCK    2400
//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3C1F6F5A01EB
PM_RulesData::PM_RulesData (PM_GenericApplication&  theGenericApplication, 
                            uint16                  theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeData::GetMaxNbParamsNoHighOrder64Bits()),
    myDefectData  ( (*myGenericApplication.GetRegionDefectData())[theIndex]),
    myCounterData ( (*myGenericApplication.GetRegionCountData())[theIndex]),
    myXYvalue      ( (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0] ),
    mySignalType(CT_TEL_SIGNAL_UNKNOWN)
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3C1F6F5A01F5
PM_RulesData::~PM_RulesData ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610E015D
void PM_RulesData::Init()
{
    myDefect = false;
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5A01F7
void PM_RulesData::UpdateRules(bool* thefilteringStateFirstStage, bool* thefilteringStateSecondStage) 
{
    // Monitoring counters registers.
    MON_RsCounters* countersObject = NULL;
    // Configuration reference.
    CFG_Rs* configRef = NULL;
    // Alarm reference.
    ALM_FailureBase* almRsRef = NULL;
    // Signal type read.
    CT_TEL_SignalType  signalType = CT_TEL_SIGNAL_UNKNOWN;
    // SONET/SDH mode
    bool trueSdhMode = false;
    // X value according to signal type.
    uint32          XYvalueRs = PM_NO_TCA_X_VALUE;
    // Parameter index.
    uint32          param;
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeData::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeData::PM_PARAM_NUM];
    // Group of failures (ored).
    bool            failuresGroup;
    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;

    PM_DataSubApplication& aDataApp = dynamic_cast<PM_DataSubApplication&>(myGenericApplication);
    MON_OptSubApplication* aMonOptApp = NULL;
    MON_AppIf* aMonAppIf;

    if( (aMonAppIf = aDataApp.GetCardContext().GetOptIf().GetMonPortSideAppPtr( myAutoRateLock.ConvertPmSideToCtIfId( aDataApp.GetSide() ) )) != NULL )
    {
        aMonOptApp = dynamic_cast<MON_OptSubApplication*>(aMonAppIf);
    }

    if ( (CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_OPSM) &&
         (CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_OBM) )
    {
        countersObject = (MON_RsCounters *) &((*(myGenericApplication.GetMonApplication().GetCountersRegion()))[myIndex]);
        configRef      = (CFG_Rs *) &((*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[0]);
        almRsRef       = (ALM_FailureBase *) &((*(myGenericApplication.GetAlmRsApplication().GetFilteredRegionPtr()))[0]);
        if ( configRef )
        {
            signalType = configRef->GetSignalType();
            trueSdhMode = configRef->GetSDHTrueMode();
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

        CT_TEL_SignalType aLocalSignalType = mySignalType;

        //-----------------------------------------------------------------
        // If GOPT and Autorate lock is supported, adjust the signal type.
        //-----------------------------------------------------------------
        if( (aMonOptApp != NULL) && (aMonOptApp->GetAutoRateLockSupported()) && (mySignalType == CT_TEL_SIGNAL_GOPT) )
        {
            aLocalSignalType = myAutoRateLock.GetAutoRateLockSignalType(aDataApp.GetCardContext(), 
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
                    if ((CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_SSM40) &&
                        (CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_OMM))
					{
                        XYvalueRs = myXYvalue.GetYvalueStm1();
					}
					else
					{
                        XYvalueRs = PMA_YVAL_SES_RS_STM1_BLOCK;
					}
                }
                else
                {
                    XYvalueRs = myXYvalue.GetXvalueOc3();
                }
                break;
            case CT_TEL_SIGNAL_OC12: 
            case CT_TEL_SIGNAL_STM4:
                if( trueSdhMode )
                {
                    if ((CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_SSM40) &&
                        (CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_OMM))
					{
                        XYvalueRs = myXYvalue.GetYvalueStm4();
					}
					else
					{
                        XYvalueRs = PMA_YVAL_SES_RS_STM4_BLOCK;
					}
                }
                else
                {
                    XYvalueRs = myXYvalue.GetXvalueOc12();
                }
                break;
            case CT_TEL_SIGNAL_E1:
                XYvalueRs = myXYvalue.GetXvalueE1();
                break;
            case CT_TEL_SIGNAL_OC48: 
            case CT_TEL_SIGNAL_STM16:
                if( trueSdhMode )
                {
                    if ((CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_SSM40) &&
                        (CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_OMM))
					{
                        XYvalueRs = myXYvalue.GetYvalueStm16();
					}
					else
					{
                        XYvalueRs = PMA_YVAL_SES_RS_STM16_BLOCK;
					}
                }
                else
                {
                    XYvalueRs = myXYvalue.GetXvalueOc48();
                }
                break;
            case CT_TEL_SIGNAL_OC192: 
            case CT_TEL_SIGNAL_STM64:
            case CT_TEL_SIGNAL_TGBEP:
                if( trueSdhMode )
                {
                    if (CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_HDTG &&
                        CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_FGTMM &&
                        CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_HGTMM &&
                        CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_HDTG2) 
                    {
                        XYvalueRs = myXYvalue.GetYvalueStm64();
                    }
                    else
                    {
                        XYvalueRs = PMA_YVAL_SES_RS_STM64_BLOCK;
                    }
                }
                else
                {
                    XYvalueRs = myXYvalue.GetXvalueOc192();
                }
                break;
            case CT_TEL_SIGNAL_OC768: 
            case CT_TEL_SIGNAL_STM256:
                if( trueSdhMode )
                {
                    if (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_FGTME)
					{
                        XYvalueRs = PMA_YVAL_SES_RS_STM256_BLOCK;
					}
					else
					{
                        XYvalueRs = myXYvalue.GetYvalueStm256();
					}
                }
                else
                {
                    XYvalueRs = myXYvalue.GetXvalueOc768();
                }
                break;
            case CT_TEL_SIGNAL_10B8B: 
            case CT_TEL_SIGNAL_GOPT:
            case CT_TEL_SIGNAL_GBEP:
            case CT_TEL_SIGNAL_ETH:
            case CT_TEL_SIGNAL_HGE:
            case CT_TEL_SIGNAL_HGE_GFP:    
            case CT_TEL_SIGNAL_FC4G:
            case CT_TEL_SIGNAL_UNKNOWN:
            default:
                // No X value supported.
                XYvalueRs = PM_NO_TCA_X_VALUE;
                break;
        }
    }

    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeData::GetMaxNbParamsNoHighOrder64Bits(); param++)
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

    myCurrentValueParam[PM_TypeData::PM_LOSS].UnsignedValue = myDefectData.EverPresentLOS(); 
    myCurrentValueParam[PM_TypeData::PM_SEFS].UnsignedValue = myDefectData.EverPresentSEF() ||
                                                              myDefectData.EverPresentLOF();
    myDefect = myCurrentValueParam[PM_TypeData::PM_LOSS].UnsignedValue || 
               myCurrentValueParam[PM_TypeData::PM_SEFS].UnsignedValue;

    myCurrentValueParam[PM_TypeData::PM_CV].UnsignedValue = myCounterData.GetBIP();
    myCurrentValueParam[PM_TypeData::PM_SE].UnsignedValue = myCounterData.GetBIP();

    myCurrentValueParam[PM_TypeData::PM_SES].UnsignedValue = myDefect || 
            (myCurrentValueParam[PM_TypeData::PM_CV].UnsignedValue >= XYvalueRs);
    myCurrentValueParam[PM_TypeData::PM_ES].UnsignedValue = myDefect || 
            (myCurrentValueParam[PM_TypeData::PM_CV].UnsignedValue > 0);

    // Accumulation of CV is masked by some defects and SES.
    if (myDefect || myCurrentValueParam[PM_TypeData::PM_SES].UnsignedValue)
    {
        myCurrentValueParam[PM_TypeData::PM_CV].UnsignedValue = 0;
    }

    // Accumulation of Symbol error is masked by LOSS.
    if (myCurrentValueParam[PM_TypeData::PM_LOSS].UnsignedValue)
    {
        myCurrentValueParam[PM_TypeData::PM_SE].UnsignedValue = 0;
    }

    if ( ((CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_OPSM) &&
          (CSPII_CardIF::GetInstance()->GetCardFamily() != CARD_FAM_OBM)) &&
         (myDefect) )
    {
        //Refresh all counter of lower level
        if ( countersObject )
            myCounterData.Update(*countersObject);
    }

    //
    // Determine TCA filtering state:
    //

    // On Transponders or RAMs:
    if ( almRsRef &&
        (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_TRN ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_FGTMM ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_HDTG  ||
        // CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_HDTG2  ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_ENH_TRN ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_SSM ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_SSM40 ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OMM ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OSM ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_FGSM ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OTNM ||
         CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_SMTM) )
    {
        ALM_FailureBase &almOptRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOptApplication().GetFilteredRegionPtr()))[0];

        // Determine failures group state.
        failuresGroup = (almRsRef->GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_RS) ||
                         almRsRef->GetStatus(CT_TelAlarmCondition::ALM_TIM_RS));

        // Filter parameters TCA,when Upper Layer Service Affecting (2.5s),
        // Upper Layer None Service Affecting (90s), LOS-RS (2.5s) or
        // LOF-RS (2.5s) failure is present.
        filteringStateFirstStage[PM_TypeData::PM_LOSS] =  almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT) ||
                                                          almRsRef->GetStatus(CT_TelAlarmCondition::ALM_TIM_RS);
        filteringStateSecondStage[PM_TypeData::PM_LOSS] = almRsRef->GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_RS);

        filteringStateFirstStage[PM_TypeData::PM_CV] =  failuresGroup;
        filteringStateSecondStage[PM_TypeData::PM_CV] = almRsRef->GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_RS);

        filteringStateFirstStage[PM_TypeData::PM_SE] =  failuresGroup ||
                                                        almRsRef->GetStatus(CT_TelAlarmCondition::ALM_LOF_RS);
        filteringStateSecondStage[PM_TypeData::PM_SE] = almRsRef->GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_RS);

        filteringStateFirstStage[PM_TypeData::PM_SEFS] =  filteringStateFirstStage[PM_TypeData::PM_SE];
        filteringStateSecondStage[PM_TypeData::PM_SEFS] = almRsRef->GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_RS);

        filteringStateFirstStage[PM_TypeData::PM_SES] =  failuresGroup ||
                                                         almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT) ||
                                                         almRsRef->GetStatus(CT_TelAlarmCondition::ALM_LOF_RS);
        filteringStateSecondStage[PM_TypeData::PM_SES] = almRsRef->GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_RS);

        filteringStateFirstStage[PM_TypeData::PM_ES] =  filteringStateFirstStage[PM_TypeData::PM_SES];
        filteringStateSecondStage[PM_TypeData::PM_ES] = almRsRef->GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_RS);

        //------------------------------------------------------------------
        // Apply Auto-Rate Lock rules for GOPT/MRTME AutoRateLock feature.
        //------------------------------------------------------------------
        if ( ((aMonOptApp != NULL) && (aMonOptApp->GetAutoRateLockSupported()) && (mySignalType == CT_TEL_SIGNAL_GOPT)) )
        {
            myAutoRateLock.AdjustForAutoRateLock( aDataApp.GetCardContext(),
                                                  myNumberOfParam,
                                                  myCurrentValueParam,
                                                  filteringStateFirstStage,
                                                  filteringStateSecondStage,
                                                  aDataApp.GetSide() );
        }
        else
        {
            myAutoRateLock.ResetAutoRateLockStates();
        }

        //Call the method of the base class.
        PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);
    }
    // On inactive OSCs:
    else if ( almRsRef &&
              (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OSC) &&
              (T6100_MainAppIf::Instance().GetControllerStatusRegion()->IsActiveController() == false) )
    {
        ALM_FailureBase &almOtsRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOtsApplication().GetFilteredRegionPtr()))[0];
        ALM_FailureBase &almOtsOhRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOtsOhApplication().GetFilteredRegionPtr()))[0];
        ALM_FailureBase &almOptRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOptApplication().GetFilteredRegionPtr()))[0];


        // Determine failures group state.
        failuresGroup = (almOtsRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OTS) || 
                         almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_OTS) ||
                         almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT));


        // Filter parameters TCA, when LOS-OTS, TIM-OTS, LOS-OSC, LOF-RS or LOS-RS
        // failure is present.
        filteringStateFirstStage[PM_TypeData::PM_LOSS] = almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT);

        filteringStateFirstStage[PM_TypeData::PM_CV] =  failuresGroup;

        filteringStateFirstStage[PM_TypeData::PM_SE] =  failuresGroup ||
                                                        almRsRef->GetStatus(CT_TelAlarmCondition::ALM_LOF_RS);

        filteringStateFirstStage[PM_TypeData::PM_SEFS] = filteringStateFirstStage[PM_TypeData::PM_SE];

        filteringStateFirstStage[PM_TypeData::PM_SES] =  failuresGroup ||
                                                         almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT) ||
                                                         almRsRef->GetStatus(CT_TelAlarmCondition::ALM_LOF_RS);

        filteringStateFirstStage[PM_TypeData::PM_ES] =  filteringStateFirstStage[PM_TypeData::PM_SES];

        //Call the method of the base class.
        PM_Rules::UpdateRules(filteringStateFirstStage);
    }
    else if ( (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OPSM) ||
              (CSPII_CardIF::GetInstance()->GetCardFamily() == CARD_FAM_OBM) )
    {
        ALM_FailureBase &almOptRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOptApplication().GetFilteredRegionPtr()))[0];

        // Determine failures group state.
        failuresGroup = almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT);

        // Filter LOSS, when OPT loss of light
        // failure is present.
        filteringStateFirstStage[PM_TypeData::PM_LOSS]  = almOptRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OPT);
        filteringStateSecondStage[PM_TypeData::PM_LOSS] = almOptRef.GetStatus(CT_TelAlarmCondition::ALM_UPPER_NSA_OPT);

        // All other RS layer PM parameters are not applicable to OPSM or OBM
        filteringStateFirstStage[PM_TypeData::PM_CV] =  true;
        filteringStateSecondStage[PM_TypeData::PM_CV] = true;

        filteringStateFirstStage[PM_TypeData::PM_SE] =  true;
        filteringStateSecondStage[PM_TypeData::PM_SE] = true;

        filteringStateFirstStage[PM_TypeData::PM_SEFS] =  true;
        filteringStateSecondStage[PM_TypeData::PM_SEFS] = true;

        filteringStateFirstStage[PM_TypeData::PM_SES] =  true;
        filteringStateSecondStage[PM_TypeData::PM_SES] = true;

        filteringStateFirstStage[PM_TypeData::PM_ES] =  true;
        filteringStateSecondStage[PM_TypeData::PM_ES] = true;

        //Call the method of the base class.
        PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);
    }
    else
    {
        // No filtering at all.

        //Call the method of the base class.
        PM_Rules::UpdateRules();
    }

}

bool* PM_RulesData::GetAutoRateInhibitProfile()
{
    return    myAutoRateLock.GetAutoRateInhibitProfile();
}

bool PM_RulesData::IsAutoRateStateRefreshed()
{
    return   myAutoRateLock.IsAutoRateStateRefreshed();
}

