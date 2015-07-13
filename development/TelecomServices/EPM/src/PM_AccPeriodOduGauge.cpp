/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Class to accumulate Odu Counter parameters for one accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <EPM/PM_TypeOdu.h>
#include <EPM/src/PM_RulesOdu.h>
#include <EPM/src/PM_RulesOduGauge.h>
#include <EPM/src/PM_AccPeriodOduGauge.h>
#include <PM/src/PM_ResetRequestPeriod.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodOduGauge::PM_AccumulationPeriodOduGauge( PM_GenericApplication &theGenericApplication,
                                                      CT_PM_Value*          theMaxValueTable,
                                                      PM_Rules&             theRules,
                                                      uint32                thePortNumber,
                                                      CT_PM_Period          thePeriod):

    PM_AccumulationPeriodGauge( theGenericApplication,
                                theMaxValueTable,
                                theRules,
                                PM_TypeOduGauge::PM_PARAM_NUM,
                                thePortNumber,
                                thePeriod)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodOduGauge::~PM_AccumulationPeriodOduGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodOduGauge::UpdatePeriod(bool* theValidityState,
                                                 bool* theFilteringStateFirstStage,
                                                 bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    //SetSomeTcaChangedState( AdjustForAutoRateLock() );

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

//------------------------------------------------------------------
bool PM_AccumulationPeriodOduGauge::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        // Check to see if the transition was into the "enabled" state
        if( !(GetCurrentAllInhibit()) )
        {
            // Reset the history state in the appropriate Odu status object.
            //PM_RulesOduGauge& rulesRef = dynamic_cast<PM_RulesOduGauge&>(GetRules());
            //rulesRef.ResetParams();
        }

        // This is a fixed rate facility.
        for (param = 0; param < myNumberOfParam; param++)
        {
            theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());
        }
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
bool PM_AccumulationPeriodOduGauge::VerifyConfigChange()
{
    bool changedFlag = false;

    // Check if region is worth investigating for a modification.
    if ( GetConfigVerifyRequest() )
    {
        changedFlag |= myCurrentResetPtr->CheckResetGaugeReqChange((*GetConfigRegion())[myIndex],
                                                                   (*GetCurrentValueRegion())[myIndex],
                                                                   true, false, myIndex);

        changedFlag |= CheckInhibitionChange((*GetConfigRegion())[myIndex],
                                             (*GetCurrentValueRegion())[myIndex]);

        changedFlag |= CheckThresholdChange((*GetConfigRegion())[myIndex],
                                            (*GetCurrentValueRegion())[myIndex]);


        SetConfigVerifyRequest(false);
    }

    return changedFlag;
}

