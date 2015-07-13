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
#include <PM/PM_TypeOpt.h>
#include <PM/src/PM_RulesOptCounter.h>
#include <PM/src/PM_AccPeriodOptCounter.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodOptCounter::PM_AccumulationPeriodOptCounter( PM_GenericApplication &theGenericApplication,
                                                                CT_PM_Value*          theMaxValueTable,
                                                                PM_Rules&             theRules,
                                                                uint32                thePortNumber,
                                                                CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeOptCounter::PM_PARAM_NUM,
                                  thePortNumber,
                                  thePeriod),
    // Regenerator Section stuff.
    myUaDeclaredOpt(false),
    myPotentialStateChangeOpt(false),
    myProtectionSchemeInhibit(true)

{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodOptCounter::~PM_AccumulationPeriodOptCounter()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodOptCounter::UpdatePeriod(bool* theValidityState,
                                                  bool* theFilteringStateFirstStage,
                                                  bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Regenerator section rules.
    PM_RulesOptCounter& dataRules = (PM_RulesOptCounter&) myRules;


    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myPotentialStateChangeOpt = myLayerElementOpt.IsPotential2ChgState();

    myUaDeclared = myUaDeclaredOpt;
    myPotentialStateChange = myPotentialStateChangeOpt;

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
bool PM_AccumulationPeriodOptCounter::UpdateEndPeriod()
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
bool PM_AccumulationPeriodOptCounter::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));
        PM_RulesOptCounter& rulesRef = dynamic_cast<PM_RulesOptCounter&>(GetRules());

        // Within a period, any change in inhibition sets the invalid flag.
        theValue.GetIdf()->ForcedSetAllIdf( true );

        myLayerElementOpt.ResetSoakCountforUa();

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
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSC, false );
            }

            // Set/clear inhibit IDF bit for PSD montype.
            if( rulesRef.EverPresentRevertiveMode() )
            {
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSD, false );
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
void PM_AccumulationPeriodOptCounter::AdjustCurrentIdf()
{
	int param;

	PM_RulesOptCounter& rulesRef = dynamic_cast<PM_RulesOptCounter&>(GetRules());

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

	// Set IDF state of Protection Scheme montypes.
	myProtectionSchemeInhibit = GetCurrentAllInhibit();
	idf.ForcedSetInhibit( PM_TypeOptCounter::PM_PSC, (!(rulesRef.EverPresentInProtectionScheme()) | myProtectionSchemeInhibit) );
	idf.ForcedSetInhibit( PM_TypeOptCounter::PM_PSD, (!(rulesRef.EverPresentRevertiveMode()) | myProtectionSchemeInhibit) );
}

//------------------------------------------------------------------
bool PM_AccumulationPeriodOptCounter::AdjustForProtectionScheme( PM_BbValue& theValue )
{
	PM_RulesOptCounter& rulesRef = dynamic_cast<PM_RulesOptCounter&>(GetRules());
	bool retVal = false;
	CT_PM_64BitValue unionValue;

	unionValue.UnsignedValue = 0;

	// Check to see if PM is enabled for Protection Scheme montypes.
	if( !myProtectionSchemeInhibit )
	{
		// Determine if Protection Scheme state change has occured.
		if( rulesRef.EverChangedProtectionScheme() )
		{
			theValue.GetIdf()->SetIdf( PM_TypeOptCounter::PM_PSC );
			theValue.GetIdf()->SetIdf( PM_TypeOptCounter::PM_PSD );

			if( rulesRef.EverPresentInProtectionScheme() )
			{
				// We have transitioned into a protection scheme.
				// 
				// Reset PSC and PSD counts.
				theValue.SetValue(PM_TypeOptCounter::PM_PSC, unionValue);
				theValue.SetValue(PM_TypeOptCounter::PM_PSD, unionValue);

				// If the protection scheme has transitioned to the "on" state,
				// clear the inhibit bit for PSC.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSC, false );

				// If the revertive mode is on, clear the inhibit bit for PSD.
				if( rulesRef.EverPresentRevertiveMode() )
				{
					theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSD, false );
				}
				else
				{
					theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSD, true );
				}
			}
			else
			{
				// We have transitioned out of a protection scheme.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSC, true );
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSD, true );
			}

			retVal = true;
		}

		// Determine if Revertive mode change has occured.
		if( (rulesRef.EverChangedRevertiveMode()) &&
			(!(rulesRef.EverChangedProtectionScheme())) &&
			(rulesRef.EverPresentInProtectionScheme()) )
		{
			theValue.GetIdf()->SetIdf( PM_TypeOptCounter::PM_PSD );

			if( rulesRef.EverPresentRevertiveMode() )
			{
				// Reset PSD count.
				theValue.SetValue(PM_TypeOptCounter::PM_PSD, unionValue);

				// If the revertive mode has transitioned to the "on" state,
				// clear the inhibit bit for PSD.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSD, false );
			}
			else
			{
				// If the revertive mode has transitioned to the "off" state,
				// set the inhibit bit for PSD.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOptCounter::PM_PSD, true );
			}

			retVal = true;
		}
	}
	return retVal;
}
