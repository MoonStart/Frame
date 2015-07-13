/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Class to accumulate ODU layer parameters
                for one accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <EPM/PM_TypeOdu.h>
#include <EPM/src/PM_RulesOdu.h>
#include <EPM/src/PM_AccPeriodOdu.h>
#include <PM/PM_OduSubApplication.h>


//-----------------------------------------------------------------
// Class constructor.
PM_AccumulationPeriodOdu::PM_AccumulationPeriodOdu( PM_GenericApplication &theGenericApplication,
                                                    CT_PM_64BitValue*     theMaxValueTable,
                                                    PM_Rules&             theRules,
                                                    uint32                thePortNumber,
                                                    CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeOdu::GetMaxNbParamsNoHighOrder64Bits(),
                                  thePortNumber,
                                  thePeriod),
    // Regenerator Section stuff.
    myUaDeclaredOdu(false),
    myPotentialStateChangeOdu(false),
    myProtectionSchemeInhibit(true)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodOdu::~PM_AccumulationPeriodOdu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodOdu::RegAdjReset()
{
    // This will reset the soaking SES count for the change of UA state.
    myLayerElementOdu.ResetSoakCountforUa();

    ResetAllAdjustRegister();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodOdu::UpdatePeriod(bool* theValidityState,
                                            bool* theFilteringStateFirstStage,
                                            bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Regenerator section rules.
    PM_RulesOdu& oduRules = (PM_RulesOdu&) myRules;


    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myUaDeclaredOdu =
        myLayerElementOdu.UpdateUA(oduRules.GetValueParam(PM_TypeOdu::PM_SES).UnsignedValue==1);
    myPotentialStateChangeOdu = myLayerElementOdu.IsPotential2ChgState();

    myUaDeclared = myUaDeclaredOdu;
    myPotentialStateChange = myPotentialStateChangeOdu;

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
bool PM_AccumulationPeriodOdu::UpdateEndPeriod()
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

// add the methods back for ODU MAP to OTU PM collection


//------------------------------------------------------------------
bool PM_AccumulationPeriodOdu::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        PM_RulesOdu& rulesRef = dynamic_cast<PM_RulesOdu&>(GetRules());

        // Within a period, any change in inhibition sets the invalid flag.
        theValue.GetIdf()->ForcedSetAllIdf( true );

        for (param = 0; param < PM_TypeOdu::PM_PSC; param++)
        {
            theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());
        }

        myLayerElementOdu.ResetSoakCountforUa();

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
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSC, false );
            }

            // Set/clear inhibit IDF bit for PSD montype.
            if( rulesRef.EverPresentRevertiveMode() )
            {
                theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSD, false );
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
void PM_AccumulationPeriodOdu::AdjustCurrentIdf()
{
	int param;

	PM_RulesOdu& rulesRef = dynamic_cast<PM_RulesOdu&>(GetRules());

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

	// Set the IDF inhibit states based on the configuration inhibit.
	for (param=0; param<PM_TypeOdu::PM_PSC; param++)
	{
		idf.ForcedSetInhibit( param, GetCurrentAllInhibit() );
	}   	

	// Set IDF state of Protection Scheme montypes.
	myProtectionSchemeInhibit = GetCurrentAllInhibit();
	idf.ForcedSetInhibit( PM_TypeOdu::PM_PSC, (!(rulesRef.EverPresentInProtectionScheme()) | myProtectionSchemeInhibit) );
	idf.ForcedSetInhibit( PM_TypeOdu::PM_PSD, (!(rulesRef.EverPresentRevertiveMode()) | myProtectionSchemeInhibit) );
}

//------------------------------------------------------------------
bool PM_AccumulationPeriodOdu::AdjustForProtectionScheme( PM_BbValue& theValue )
{
	PM_RulesOdu& rulesRef = dynamic_cast<PM_RulesOdu&>(GetRules());
	bool retVal = false;
	CT_PM_64BitValue unionValue;

	unionValue.UnsignedValue = 0;

	// Check to see if PM is enabled for Protection Scheme montypes.
	if( !myProtectionSchemeInhibit )
	{
		// Determine if Protection Scheme state change has occured.
		if( rulesRef.EverChangedProtectionScheme() )
		{
			theValue.GetIdf()->SetIdf( PM_TypeOdu::PM_PSC );
			theValue.GetIdf()->SetIdf( PM_TypeOdu::PM_PSD );

			if( rulesRef.EverPresentInProtectionScheme() )
			{
				// We have transitioned into a protection scheme.
				// 
				// Reset PSC and PSD counts.
				theValue.SetValue(PM_TypeOdu::PM_PSC, unionValue);
				theValue.SetValue(PM_TypeOdu::PM_PSD, unionValue);

				// If the protection scheme has transitioned to the "on" state,
				// clear the inhibit bit for PSC.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSC, false );

				// If the revertive mode is on, clear the inhibit bit for PSD.
				if( rulesRef.EverPresentRevertiveMode() )
				{
					theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSD, false );
				}
				else
				{
					theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSD, true );
				}
			}
			else
			{
				// We have transitioned out of a protection scheme.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSC, true );
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSD, true );
			}

			retVal = true;
		}

		// Determine if Revertive mode change has occured.
		if( (rulesRef.EverChangedRevertiveMode()) &&
			(!(rulesRef.EverChangedProtectionScheme())) &&
			(rulesRef.EverPresentInProtectionScheme()) )
		{
			theValue.GetIdf()->SetIdf( PM_TypeOdu::PM_PSD );

			if( rulesRef.EverPresentRevertiveMode() )
			{
				// Reset PSD count.
				theValue.SetValue(PM_TypeOdu::PM_PSD, unionValue);

				// If the revertive mode has transitioned to the "on" state,
				// clear the inhibit bit for PSD.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSD, false );
			}
			else
			{
				// If the revertive mode has transitioned to the "off" state,
				// set the inhibit bit for PSD.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOdu::PM_PSD, true );
			}

			retVal = true;
		}
	}
	return retVal;
}

//------------------------------------------------------------------------------------
CT_PM_64BitValue PM_AccumulationPeriodOdu::GetMaxValueTable64Bit(CT_PM_Parameter theParameter)
{
    if ( (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_34) )
    {
        if ( theParameter == PM_TypeOdu::PM_CV )
        {
            return myMaxValueTable64Bit[PM_TypeOdu::PM_CV_HIGH];
        }
    }
 
    return myMaxValueTable64Bit[theParameter];
}

//------------------------------------------------------------------------------------
CT_EntityType PM_AccumulationPeriodOdu::GetEntityTypeFor64BitPM()
{
    CT_EntityType a64BitEntityType = CT_UNKNOWN_ENTITY_TYPE;
 
    if ( (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_34) )
    {
        a64BitEntityType = CT_ODU4;
    }
 
    return a64BitEntityType;
}

