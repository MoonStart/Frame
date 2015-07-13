/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     8 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Class to accumulate TCM layer parameters
                for one accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbCfgLayer.h>
#include <EPM/PM_TypeTcm.h>
#include <EPM/src/PM_RulesTcm.h>
#include <EPM/src/PM_AccPeriodTcm.h>
#include <PM/PM_TcmSubApplication.h>
#include <T6100/T6100_ObjectAllocManager.h>


//-----------------------------------------------------------------
// Class constructor.
PM_AccumulationPeriodTcm::PM_AccumulationPeriodTcm( PM_GenericApplication &theGenericApplication,
                                                    CT_PM_64BitValue*     theMaxValueTable,
                                                    PM_Rules&             theRules,
                                                    uint32                thePortNumber,
                                                    CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeTcm::GetMaxNbParamsNoHighOrder64Bits(),
                                  thePortNumber,
                                  thePeriod),
    // Regenerator Section stuff.
    myUaDeclaredTcm(false),
    myPotentialStateChangeTcm(false),
    myDynamicIndex(0)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodTcm::~PM_AccumulationPeriodTcm()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodTcm::RegAdjReset()
{
    // This will reset the soaking SES count for the change of UA state.
    myLayerElementTcm.ResetSoakCountforUa();

    ResetAllAdjustRegister();

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodTcm::Init(uint16 thePortNumber)
{
    // myIndex is not initialized yet.
    myIndex = thePortNumber;

    // Default accumulation is disabled.
    myCurrentAllInhibit = true;

    // Ensure that the inhibition status is refreshed in the first run of PM Processor.
    CheckInhibitionChange( (*GetConfigRegion())[myIndex] );

    // To be sure it is reset.
    ResetSomeTcaChangedState();

    // Reset adjustment register values.
    ResetAllAdjustRegister();
}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodTcm::UpdatePeriod(bool* theValidityState,
                                            bool* theFilteringStateFirstStage,
                                            bool* theFilteringStateSecondStage)
{
    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myDynamicIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // TCM rules.
    PM_RulesTcm& tcmRules = (PM_RulesTcm&) myRules;


    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myUaDeclaredTcm =
        myLayerElementTcm.UpdateUA(tcmRules.GetValueParam(PM_TypeTcm::PM_SES).UnsignedValue==1);
    myPotentialStateChangeTcm = myLayerElementTcm.IsPotential2ChgState();

    myUaDeclared = myUaDeclaredTcm;
    myPotentialStateChange = myPotentialStateChangeTcm;

    // Check if All parameters accumulation is enabled.
    if (!GetCurrentAllInhibit())
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, theValidityState,
                                                  theFilteringStateFirstStage,
                                                  theFilteringStateSecondStage,
                                                  false) );
    }

    return GetSomeTcaChangedState();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodTcm::UpdateEndPeriod()
{
    bool    validityState[PM_MAX_NUMBER_OF_PARAMETERS];             // Computed validity state.
    bool    filteringStateFirstStage[PM_MAX_NUMBER_OF_PARAMETERS];  // Computed filtering state first stage.
    bool    filteringStateSecondStage[PM_MAX_NUMBER_OF_PARAMETERS]; // Computed filtering state second stage.
    uint32  param;                                                  // Parameter index.

    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myDynamicIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Set validity state to valid and filtering state to no filtering.
    for (param = 0; param < myNumberOfParam; param++)
    {
        filteringStateFirstStage[param] = false;
        filteringStateSecondStage[param] = false;
        validityState[param] = true;
    }

    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.



    // Check if All parameters accumulation is enabled.
    if (!GetCurrentAllInhibit())
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, validityState,
                                                  filteringStateFirstStage,
                                                  filteringStateSecondStage,
                                                  true) );
    }

    return GetSomeTcaChangedState();

}

//------------------------------------------------------------------
bool PM_AccumulationPeriodTcm::CheckInhibitionChange(PM_BbCfg& theConfig)
{
    bool isRegionChanged = false;

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));
        isRegionChanged = true;
    }

    // Verify TCA inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ALL) != GetCurrentAllTcaInhibit() )
    {
        SetCurrentAllTcaInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ALL));
        isRegionChanged = true;
    }

    return isRegionChanged;
}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodTcm::VerifyConfigChange()
{
    bool changedFlag = false;

    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    // Check if region is worth investigating for a modification.
    if ( GetConfigVerifyRequest() )
    {
        changedFlag |= CheckResetReqChange((*GetConfigRegion())[myIndex],
                                           (*GetCurrentValueRegion())[myDynamicIndex]);

        changedFlag |= PM_AccumulationPeriod::CheckInhibitionChange((*GetConfigRegion())[myIndex],
                                             (*GetCurrentValueRegion())[myDynamicIndex]);

        changedFlag |= CheckThresholdChange((*GetConfigRegion())[myIndex],
                                            (*GetCurrentValueRegion())[myDynamicIndex]);


        SetConfigVerifyRequest(false);

        // MR188464
        // if pm-mode is enabled, check tcm-mode and set IDF to different status 
        // based on tcm-mode
        if(!GetCurrentAllInhibit())
        {
            PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*GetConfigRegion())[myIndex]);
            if(aPM_NE_CONFIG_OBJ)
            {
                uint16 param = 0;
                PM_BbCfgTcm * pmTcmConf = dynamic_cast<PM_BbCfgTcm *> (aPM_NE_CONFIG_OBJ);
                PM_BbValue& aValue = (*GetCurrentValueRegion())[myDynamicIndex];
                
                if(pmTcmConf && pmTcmConf->GetTcmModeChgedFlag())
                {
                    // 1) -- provision TCM with SRC mode
                    if(pmTcmConf->GetPrevTcmMode() == CT_TCM_MODE_UNKNOWN && 
                       pmTcmConf->GetCurrTcmMode() == CT_TCM_MODE_SOURCE)
                    {
                        for (param = 0; param < myNumberOfParam; param++)
                        {
                            aValue.GetIdf()->SetIdf(param, CT_PM_IDF_NA);
                        }
                    }
                    // 2) -- from SRC --> SRC_SNK/SRC_SNK_NIM/SNK/SNK_NIM or
                    //       from SRC_SNK/SRC_SNK_NIM/SNK/SNK_NIM --> SRC
                    //       set to PRTL
                    else if(( pmTcmConf->GetPrevTcmMode() == CT_TCM_MODE_SOURCE &&
                              pmTcmConf->GetCurrTcmMode() != CT_TCM_MODE_SOURCE &&
                              pmTcmConf->GetCurrTcmMode() != CT_TCM_MODE_UNKNOWN) ||
                            ( pmTcmConf->GetPrevTcmMode() != CT_TCM_MODE_SOURCE &&
                              pmTcmConf->GetPrevTcmMode() != CT_TCM_MODE_UNKNOWN &&
                              pmTcmConf->GetCurrTcmMode() == CT_TCM_MODE_SOURCE))
                    {
                        for (param = 0; param < myNumberOfParam; param++)
                        {
                            aValue.GetIdf()->SetIdf(param, CT_PM_IDF_PARTIAL);
                        }
                    }
                }
            }
        }
    }

    return changedFlag;

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodTcm::ResetAll()
{
    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    // Reset all parameter value.
    (*GetCurrentValueRegion())[myDynamicIndex].ResetAll();

    // Reset all TCA statues.
    (*GetCurrentValueRegion())[myDynamicIndex].GetMaxTca()->ResetAllTca();
    if ((*GetCurrentValueRegion())[myDynamicIndex].GetMinTca())
        (*GetCurrentValueRegion())[myDynamicIndex].GetMinTca()->ResetAllTca();

    // Set all IDF status to invalid.
    (*GetCurrentValueRegion())[myDynamicIndex].GetIdf()->ForcedSetAllIdf(true);

}

//------------------------------------------------------------------
void PM_AccumulationPeriodTcm::AdjustCurrentIdf()  //Used in Switch
{
    uint32 j;

    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myDynamicIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

    // Set inhibition flag in IDF as its per PM_AccumulationPeriod object.

    // For all parameters.
    for (j = 0; j < myNumberOfParam; j++)
    {
        idf.ForcedSetInhibit(j, GetCurrentAllInhibit());
    }

    // MR188464
    if(!GetCurrentAllInhibit())
    {
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*GetConfigRegion())[myIndex]);
        if(aPM_NE_CONFIG_OBJ)
        {
            PM_BbCfgTcm * pmTcmConf = dynamic_cast<PM_BbCfgTcm *> (aPM_NE_CONFIG_OBJ);
            if(pmTcmConf)
            {
                // reset tcm-mode change flag when starting a new bin
                pmTcmConf->SetModeChgedFlag(false);

                if(pmTcmConf->GetCurrTcmMode() == CT_TCM_MODE_SOURCE)
                {
                    for (j = 0; j < myNumberOfParam; j++)
                    {
                        idf.SetIdf(j, CT_PM_IDF_NA);
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------
void PM_AccumulationPeriodTcm::SetAvailability(CT_PM_Parameter theParameter,
                                            bool            theAvailability)
                                            //Used when Monitoring validity changes..
{
    // Set the dynamic index
    myDynamicIndex = myGenericApplication.GetObjectAllocMgr().GetDynamicIndexFromIterator();

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myDynamicIndex].GetIdf());

    // Set the availability of the parameter.
    idf.ForcedSetAvailability(theParameter, theAvailability);

}

//-----------------------------------------------------------------
CT_PM_64BitValue PM_AccumulationPeriodTcm::GetMaxValueTable64Bit(CT_PM_Parameter theParameter)
{
    if ( ((myGenericApplication.GetSide() == CT_PM_PORT_SIDE_80) ||
          (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_81)) )
    {
        if ( theParameter == PM_TypeTcm::PM_CV )
        {
            return myMaxValueTable64Bit[PM_TypeTcm::PM_CV_HIGH];
        }
    }
 
    return myMaxValueTable64Bit[theParameter];
}
 
//-----------------------------------------------------------------
CT_EntityType PM_AccumulationPeriodTcm::GetEntityTypeFor64BitPM()
{
    CT_EntityType a64BitEntityType = CT_UNKNOWN_ENTITY_TYPE;
 
    if ( ((myGenericApplication.GetSide() == CT_PM_PORT_SIDE_80) ||
          (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_81)) )
    {
        a64BitEntityType = CT_ODU4T;
    }
 
    return a64BitEntityType;
}

