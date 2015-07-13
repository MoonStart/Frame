/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     23 October 2006  Larry M. Wolfrum
 DESCRIPTION:   Class to accumulate OTU layer parameters 
                for one accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_TypeOtu.h>
#include <PM/src/PM_RulesOtu.h>
#include <EPM/src/PM_AccPeriodOtu.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodOtu::PM_AccumulationPeriodOtu( PM_GenericApplication &theGenericApplication,
													CT_PM_64BitValue*     theMaxValueTable,
													PM_Rules&             theRules,
													uint32                thePortNumber,
													CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeOtu::GetMaxNbParamsNoHighOrder64Bits(),
                                  thePortNumber,
                                  thePeriod),
    myUaDeclaredOtu(false),
    myPotentialStateChangeOtu(false),
	myProtectionSchemeInhibit(true)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodOtu::~PM_AccumulationPeriodOtu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodOtu::RegAdjReset()
{
    // This will reset the soaking SES count for the change of UA state.
    myLayerElementOtu.ResetSoakCountforUa();

    ResetAllAdjustRegister();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodOtu::UpdatePeriod(bool* theValidityState, 
											bool* theFilteringStateFirstStage,
											bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex]; 

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Otu rules.
    PM_RulesOtu& otuRules = (PM_RulesOtu&) myRules;

    // In normal accumulation (it is not the end of period) it can have an accumulation 
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myUaDeclaredOtu = 
        myLayerElementOtu.UpdateUA(otuRules.GetValueParam(PM_TypeOtu::PM_SES).UnsignedValue==1);
    myPotentialStateChangeOtu = myLayerElementOtu.IsPotential2ChgState();

    myUaDeclared = myUaDeclaredOtu;
    myPotentialStateChange = myPotentialStateChangeOtu;

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
bool PM_AccumulationPeriodOtu::UpdateEndPeriod()
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
bool PM_AccumulationPeriodOtu::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

		PM_RulesOtu& rulesRef = dynamic_cast<PM_RulesOtu&>(GetRules());

		// Within a period, any change in inhibition sets the invalid flag.
		theValue.GetIdf()->ForcedSetAllIdf( true );

		for (param = 0; param < PM_TypeOtu::PM_PSC; param++)
		{
			theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());
		}

        myLayerElementOtu.ResetSoakCountforUa();

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
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSC, false );
			}

			// Set/clear inhibit IDF bit for PSD montype.
			if( rulesRef.EverPresentRevertiveMode() )
			{
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSD, false );
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
void PM_AccumulationPeriodOtu::AdjustCurrentIdf()
{
	int param;

	PM_RulesOtu& rulesRef = dynamic_cast<PM_RulesOtu&>(GetRules());

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

	// Set the IDF inhibit states based on the configuration inhibit.
	for (param=0; param<PM_TypeOtu::PM_PSC; param++)
	{
		idf.ForcedSetInhibit( param, GetCurrentAllInhibit() );
	}   	

	// Set IDF state of Protection Scheme montypes.
	myProtectionSchemeInhibit = GetCurrentAllInhibit();
	idf.ForcedSetInhibit( PM_TypeOtu::PM_PSC, (!(rulesRef.EverPresentInProtectionScheme()) | myProtectionSchemeInhibit) );
	idf.ForcedSetInhibit( PM_TypeOtu::PM_PSD, (!(rulesRef.EverPresentRevertiveMode()) | myProtectionSchemeInhibit) );
}

//------------------------------------------------------------------
bool PM_AccumulationPeriodOtu::AdjustForProtectionScheme( PM_BbValue& theValue )
{
	PM_RulesOtu& rulesRef = dynamic_cast<PM_RulesOtu&>(GetRules());
	bool retVal = false;
	CT_PM_64BitValue unionValue;

	unionValue.UnsignedValue = 0;

	// Check to see if PM is enabled for Protection Scheme montypes.
	if( !myProtectionSchemeInhibit )
	{
		// Determine if Protection Scheme state change has occured.
		if( rulesRef.EverChangedProtectionScheme() )
		{
			theValue.GetIdf()->SetIdf( PM_TypeOtu::PM_PSC );
			theValue.GetIdf()->SetIdf( PM_TypeOtu::PM_PSD );

			if( rulesRef.EverPresentInProtectionScheme() )
			{
				// We have transitioned into a protection scheme.
				// 
				// Reset PSC and PSD counts.
				theValue.SetValue(PM_TypeOtu::PM_PSC, unionValue);
				theValue.SetValue(PM_TypeOtu::PM_PSD, unionValue);

				// If the protection scheme has transitioned to the "on" state,
				// clear the inhibit bit for PSC.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSC, false );

				// If the revertive mode is on, clear the inhibit bit for PSD.
				if( rulesRef.EverPresentRevertiveMode() )
				{
					theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSD, false );
				}
				else
				{
					theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSD, true );
				}
			}
			else
			{
				// We have transitioned out of a protection scheme.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSC, true );
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSD, true );
			}

			retVal = true;
		}

		// Determine if Revertive mode change has occured.
		if( (rulesRef.EverChangedRevertiveMode()) &&
			(!(rulesRef.EverChangedProtectionScheme())) &&
			(rulesRef.EverPresentInProtectionScheme()) )
		{
			theValue.GetIdf()->SetIdf( PM_TypeOtu::PM_PSD );

			if( rulesRef.EverPresentRevertiveMode() )
			{
				// Reset PSD count.
				theValue.SetValue(PM_TypeOtu::PM_PSD, unionValue);

				// If the revertive mode has transitioned to the "on" state,
				// clear the inhibit bit for PSD.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSD, false );
			}
			else
			{
				// If the revertive mode has transitioned to the "off" state,
				// set the inhibit bit for PSD.
				theValue.GetIdf()->ForcedSetInhibit( PM_TypeOtu::PM_PSD, true );
			}

			retVal = true;
		}
	}
	return retVal;
}

//-----------------------------------------------------------------
CT_PM_64BitValue PM_AccumulationPeriodOtu::GetMaxValueTable64Bit(CT_PM_Parameter theParameter)
{
    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
    CT_PM_Side  aPMSide = myGenericApplication.GetSide();
    if ( ((aCardType == CARD_TYPE_HGTM || aCardType == CARD_TYPE_HGTMS) &&
           ((aPMSide == CT_PM_PORT_SIDE_0 || aPMSide == CT_PM_PORT_SIDE_1))) ||
          ((aCardType == CARD_TYPE_HGTMM || aCardType == CARD_TYPE_HGTMMS) &&
            (aPMSide == CT_PM_PORT_SIDE_12)) )
    {
        if ( theParameter == PM_TypeOtu::PM_CV )
        {
            return myMaxValueTable64Bit[PM_TypeOtu::PM_CV_HIGH];
        }
        else if ( theParameter == PM_TypeOtu::PM_BE )
        {
            return myMaxValueTable64Bit[PM_TypeOtu::PM_BE_HIGH];
        }
    }
 
    return myMaxValueTable64Bit[theParameter];
}

//-----------------------------------------------------------------
CT_EntityType PM_AccumulationPeriodOtu::GetEntityTypeFor64BitPM()
{
    CT_EntityType a64BitEntityType = CT_UNKNOWN_ENTITY_TYPE;
    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
    CT_PM_Side  aPMSide = myGenericApplication.GetSide();
 
    if ( ((aCardType == CARD_TYPE_HGTM || aCardType == CARD_TYPE_HGTMS) &&
           ((aPMSide == CT_PM_PORT_SIDE_0 || aPMSide == CT_PM_PORT_SIDE_1))) ||
          ((aCardType == CARD_TYPE_HGTMM || aCardType == CARD_TYPE_HGTMMS) &&
            (aPMSide == CT_PM_PORT_SIDE_12)) )
    {
        a64BitEntityType = CT_OTU4;
    }
 
    return a64BitEntityType;
}

