/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004  Hemant Thakkar
 DESCRIPTION:   Class to accumulate Near-End SONET/SDH MS layer parameters
                for one accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_TypeMsNearEnd.h>
#include <PM/src/PM_RulesMsNearEnd.h>
#include <PM/src/PM_AccPeriodMsNearEnd.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodMsNearEnd::PM_AccumulationPeriodMsNearEnd( PM_GenericApplication &theGenericApplication,
                                                                CT_PM_Value*          theMaxValueTable,
                                                                PM_Rules&             theRules,
                                                                uint32                thePortNumber,
                                                                CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeMsNearEnd::PM_PARAM_NUM,
                                  thePortNumber,
                                  thePeriod),
    // Regenerator Section stuff.
    myUaDeclaredMsNearEnd(false),
    myPotentialStateChangeMsNearEnd(false),
    myDisableAutoRateInhibit(true),
    myProtectionSchemeInhibit(true)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodMsNearEnd::~PM_AccumulationPeriodMsNearEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodMsNearEnd::RegAdjReset()
{
    // This will reset the soaking SES count for the change of UA state.
    myLayerElementMsNearEnd.ResetSoakCountforUa();

    ResetAllAdjustRegister();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodMsNearEnd::UpdatePeriod(bool* theValidityState,
                                                  bool* theFilteringStateFirstStage,
                                                  bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Regenerator section rules.
    PM_RulesMsNearEnd& dataRules = (PM_RulesMsNearEnd&) myRules;


    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myUaDeclaredMsNearEnd =
        myLayerElementMsNearEnd.UpdateUA(dataRules.GetValueParam(PM_TypeMsNearEnd::PM_SES).UnsignedValue==1);
    myPotentialStateChangeMsNearEnd = myLayerElementMsNearEnd.IsPotential2ChgState();

    myUaDeclared = myUaDeclaredMsNearEnd;
    myPotentialStateChange = myPotentialStateChangeMsNearEnd;

    // Apply Auto-Rate Lock adjustments to current value data.
    SetSomeTcaChangedState( AdjustForAutoRateLock( value ) );

    // Apply protection scheme adjustments to current value data.
    SetSomeTcaChangedState( AdjustForProtectionScheme( value ) );

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
bool PM_AccumulationPeriodMsNearEnd::UpdateEndPeriod()
{
    bool    validityState[PM_MAX_NUMBER_OF_PARAMETERS];             // Computed validity state.
    bool    filteringStateFirstStage[PM_MAX_NUMBER_OF_PARAMETERS];  // Computed filtering state first stage.
    bool    filteringStateSecondStage[PM_MAX_NUMBER_OF_PARAMETERS]; // Computed filtering state second stage.
    uint32  param;                                                  // Parameter index.


    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

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
bool PM_AccumulationPeriodMsNearEnd::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        // Get pointer to Auto-Rate Lock inhibit profile
        PM_RulesMsNearEnd& rulesRef = dynamic_cast<PM_RulesMsNearEnd&>(GetRules());
        bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();

        // Within a period, any change in inhibition sets the invalid flag.
        theValue.GetIdf()->ForcedSetAllIdf( true );

        // Validate pointer to see if this facility is configured for
        // Auto-Rate Lock
        if( aAutoRateInhibitProfile == NULL )
        {
            // This is a fixed rate facility.
            for (param = 0; param < PM_TypeMsNearEnd::PM_PSC; param++)
            {
                theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());

                ResetAdjustRegister(param);
            }
        }
        else
        {
            // This is an Auto-Rate Lock facility
            if( myDisableAutoRateInhibit && !(GetCurrentAllInhibit()) )
            {
                // This is the first time PM collection has been enabled
                // during this period.
                 myDisableAutoRateInhibit = false;
            }

            if( !myDisableAutoRateInhibit )
            {
                for (param = 0; param < PM_TypeMsNearEnd::PM_PSC; param++)
                {

                    theValue.GetIdf()->ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                    aAutoRateInhibitProfile++;

                    ResetAdjustRegister(param);
                }
            }
        }

        myLayerElementMsNearEnd.ResetSoakCountforUa();

        // Set flag for protection state montypes.
        if( myProtectionSchemeInhibit && !(GetCurrentAllInhibit()) )
        {
            // This is the first time Protection Scheme has been enabled
            // during this period.
            myProtectionSchemeInhibit = false;
        }

        if( !myProtectionSchemeInhibit )
        {
            // Set/clear inhibit IDF bit for PSC montype.
            if( rulesRef.EverPresentInProtectionScheme() )
            {
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSC, false );
            }

            // Set/clear inhibit IDF bit for PSD montype.
            if( rulesRef.EverPresentRevertiveMode() )
            {
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSD, false );
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

//------------------------------------------------------------------
bool PM_AccumulationPeriodMsNearEnd::AdjustForAutoRateLock( PM_BbValue& theValue )
{
    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesMsNearEnd& rulesRef = dynamic_cast<PM_RulesMsNearEnd&>(GetRules());
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

            // Adjust the IDF inhibit states per the Auto-Rate
            // inhibit profile.
            for (int param=0; param<PM_TypeMsNearEnd::PM_PSC; param++)
            {
                theValue.GetIdf()->ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                aAutoRateInhibitProfile++;
            }

            retVal = true;
        }
    }
    return retVal;
}

//------------------------------------------------------------------
void PM_AccumulationPeriodMsNearEnd::AdjustCurrentIdf()
{
    int param;

    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesMsNearEnd& rulesRef = dynamic_cast<PM_RulesMsNearEnd&>(GetRules());
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
        for (param=0; param<PM_TypeMsNearEnd::PM_PSC; param++)
        {
            idf.ForcedSetInhibit( param, (*aAutoRateInhibitProfile | myDisableAutoRateInhibit) );
            aAutoRateInhibitProfile++;
        }
    }
    else
    {
        // Set the IDF inhibit states based on the configuration inhibit.
        for (param=0; param<PM_TypeMsNearEnd::PM_PSC; param++)
        {
            idf.ForcedSetInhibit( param, GetCurrentAllInhibit() );
        }
    }

    // Set IDF state of Protection Scheme montypes.
    myProtectionSchemeInhibit = GetCurrentAllInhibit();
    idf.ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSC, (!(rulesRef.EverPresentInProtectionScheme()) | myProtectionSchemeInhibit) );
    idf.ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSD, (!(rulesRef.EverPresentRevertiveMode()) | myProtectionSchemeInhibit) );
}

//------------------------------------------------------------------
bool PM_AccumulationPeriodMsNearEnd::AdjustForProtectionScheme( PM_BbValue& theValue )
{
    PM_RulesMsNearEnd& rulesRef = dynamic_cast<PM_RulesMsNearEnd&>(GetRules());
    bool retVal = false;
    CT_PM_64BitValue unionValue;

    unionValue.UnsignedValue = 0;

    // Check to see if PM is enabled for Protection Scheme montypes.
    if( !myProtectionSchemeInhibit )
    {
        // Determine if Protection Scheme state change has occured.
        if( rulesRef.EverChangedProtectionScheme() )
        {
            theValue.GetIdf()->SetIdf( PM_TypeMsNearEnd::PM_PSC );
            theValue.GetIdf()->SetIdf( PM_TypeMsNearEnd::PM_PSD );

            if( rulesRef.EverPresentInProtectionScheme() )
            {
                // We have transitioned into a protection scheme.
                //
                // Reset PSC and PSD counts.
                theValue.SetValue(PM_TypeMsNearEnd::PM_PSC, unionValue);
                theValue.SetValue(PM_TypeMsNearEnd::PM_PSD, unionValue);

                // If the protection scheme has transitioned to the "on" state,
                // clear the inhibit bit for PSC.
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSC, false );

                // If the revertive mode is on, clear the inhibit bit for PSD.
                if( rulesRef.EverPresentRevertiveMode() )
                {
                    theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSD, false );
                }
                else
                {
                    theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSD, true );
                }
            }
            else
            {
                // We have transitioned out of a protection scheme.
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSC, true );
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSD, true );
            }

            retVal = true;
        }

        // Determine if Revertive mode change has occured.
        if( (!(rulesRef.EverChangedProtectionScheme())) &&
            (rulesRef.EverPresentInProtectionScheme()) &&
            (rulesRef.EverChangedRevertiveMode()) )
        {
            theValue.GetIdf()->SetIdf( PM_TypeMsNearEnd::PM_PSD );

            if( rulesRef.EverPresentRevertiveMode() )
            {
                // Reset PSD count.
                theValue.SetValue(PM_TypeMsNearEnd::PM_PSD, unionValue);

                // If the revertive mode has transitioned to the "on" state,
                // clear the inhibit bit for PSD.
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSD, false );
            }
            else
            {
                // If the revertive mode has transitioned to the "off" state,
                // set the inhibit bit for PSD.
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeMsNearEnd::PM_PSD, true );
            }

            retVal = true;
        }
    }
    return retVal;
}
