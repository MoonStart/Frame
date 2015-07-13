/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 4, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to accumulate Rmon Counter parameters for one accumulation
                period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <EPM/PM_TypeRmon.h>
#include <EPM/src/PM_RulesRmonGauge.h>
#include <EPM/src/PM_AccPeriodRmonGauge.h>
#include <PM/src/PM_ResetRequestPeriod.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodRmonGauge::PM_AccumulationPeriodRmonGauge( PM_GenericApplication &theGenericApplication,
                                                      CT_PM_Value*          theMaxValueTable,
                                                      PM_Rules&             theRules,
                                                      uint32                thePortNumber,
                                                      CT_PM_Period          thePeriod):

    PM_AccumulationPeriodGauge( theGenericApplication,
                                theMaxValueTable,
                                theRules,
                                PM_TypeRmonGauge::PM_PARAM_NUM,
                                thePortNumber,
                                thePeriod),

    // RMON layer stuff.
    myDisableAutoRateInhibit(true)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodRmonGauge::~PM_AccumulationPeriodRmonGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodRmonGauge::UpdatePeriod(bool* theValidityState,
                                                  bool* theFilteringStateFirstStage,
                                                  bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Apply Auto-Rate Lock adjustments to current value data.
    SetSomeTcaChangedState( AdjustForAutoRateLock() );

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
bool PM_AccumulationPeriodRmonGauge::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        // Check to see if the transition was into the "enabled" state
        PM_RulesRmonGauge& rulesRef = dynamic_cast<PM_RulesRmonGauge&>(GetRules());

        if( !(GetCurrentAllInhibit()) )
        {
            // Reset the history state in the appropriate RMON status object.
            rulesRef.ResetParams();
        }

        // Get pointer to Auto-Rate Lock inhibit profile
        bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();

        // Validate pointer to see if this facility is configured for
        // Auto-Rate Lock
        if( aAutoRateInhibitProfile == NULL )
        {
            // This is a fixed rate facility.
            for (param = 0; param < myNumberOfParam; param++)
            {
                theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());
            }
        }
        else
        {
            // This is an Auto-Rate Lock facility

            // Within a period, any change in inhibition sets the
            // invalid flag.
            theValue.GetIdf()->ForcedSetAllIdf( true );

            if( myDisableAutoRateInhibit && !(GetCurrentAllInhibit()) )
            {
                // This is the first time PM collection has been enabled
                // during this period.
                 myDisableAutoRateInhibit = false;
            }

            if( !myDisableAutoRateInhibit )
            {
                for (param = 0; param < myNumberOfParam; param++)
                {

                    theValue.GetIdf()->ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                    aAutoRateInhibitProfile++;
                }
            }
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

bool PM_AccumulationPeriodRmonGauge::AdjustForAutoRateLock()
{
    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesRmonGauge& rulesRef = dynamic_cast<PM_RulesRmonGauge&>(GetRules());
    bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();
    bool retVal = false;

    // Validate pointer to see if this facility is configured for
    // Auto-Rate Lock
    if( (aAutoRateInhibitProfile != NULL) && (!myDisableAutoRateInhibit) )
    {
        // Determine if an Auto-Rate Lock update has occured.
        if( rulesRef.IsAutoRateStateRefreshed() )
        {
            // An Auto-Rate update has occured.
            // Reset all of the current data.
            ResetAll();

            // Get a reference to the IDF object.
            PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

            // Adjust the IDF inhibit states per the Auto-Rate
            // inhibit profile.
            for (uint32 param=0; param<myNumberOfParam; param++)
            {
                idf.ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                aAutoRateInhibitProfile++;
            }

            retVal = true;
        }
    }
    return retVal;
}

//------------------------------------------------------------------
void PM_AccumulationPeriodRmonGauge::AdjustCurrentIdf()
{
    uint32 param;

    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesRmonGauge& rulesRef = dynamic_cast<PM_RulesRmonGauge&>(GetRules());
    bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

    // Validate pointer to see if this facility is configured for
    // Auto-Rate Lock
    if( aAutoRateInhibitProfile != NULL )
    {
        // Set initial rules for applying Auto-Rate Lock inhibit.
        myDisableAutoRateInhibit =  GetCurrentAllInhibit();

        // Adjust the IDF inhibit states per the Auto-Rate
        // inhibit profile combined with the configuration inhibit.
        for (param=0; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, (*aAutoRateInhibitProfile | myDisableAutoRateInhibit) );
            aAutoRateInhibitProfile++;
        }
    }
    else
    {
        // Set the IDF inhibit states based on the configuration inhibit.
        for (param=0; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, GetCurrentAllInhibit() );
        }
    }
}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodRmonGauge::CheckResetReqChange(PM_BbCfg    &theConfig,
                                                         PM_BbValue& theCurrentValue)
{
    return myCurrentResetPtr->CheckResetRmonGaugeReqChange( theConfig, theCurrentValue, dynamic_cast<PM_RulesRmonGauge&>(GetRules()) );
}
