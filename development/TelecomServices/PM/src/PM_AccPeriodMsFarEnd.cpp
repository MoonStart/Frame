/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004  Hemant Thakkar
 DESCRIPTION:   Class to accumulate Far-End SONET/SDH MS layer parameters
                for one accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_TypeMsFarEnd.h>
#include <PM/src/PM_RulesMsFarEnd.h>
#include <PM/src/PM_AccPeriodMsFarEnd.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodMsFarEnd::PM_AccumulationPeriodMsFarEnd( PM_GenericApplication &theGenericApplication,
                                                                CT_PM_Value*          theMaxValueTable,
                                                                PM_Rules&             theRules,
                                                                uint32                thePortNumber,
                                                                CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeMsFarEnd::PM_PARAM_NUM,
                                  thePortNumber,
                                  thePeriod),
    // Regenerator Section stuff.
    myUaDeclaredMsFarEnd(false),
    myPotentialStateChangeMsFarEnd(false)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodMsFarEnd::~PM_AccumulationPeriodMsFarEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodMsFarEnd::RegAdjReset()
{
    // This will reset the soaking SES count for the change of UA state.
    myLayerElementMsFarEnd.ResetSoakCountforUa();

    ResetAllAdjustRegister();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodMsFarEnd::UpdatePeriod(bool* theValidityState,
                                                  bool* theFilteringStateFirstStage,
                                                  bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Regenerator section rules.
    PM_RulesMsFarEnd& dataRules = (PM_RulesMsFarEnd&) myRules;


    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myUaDeclaredMsFarEnd =
        myLayerElementMsFarEnd.UpdateUA(dataRules.GetValueParam(PM_TypeMsFarEnd::PM_SES).UnsignedValue==1);
    myPotentialStateChangeMsFarEnd = myLayerElementMsFarEnd.IsPotential2ChgState();

    myUaDeclared = myUaDeclaredMsFarEnd;
    myPotentialStateChange = myPotentialStateChangeMsFarEnd;

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
bool PM_AccumulationPeriodMsFarEnd::UpdateEndPeriod()
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
bool PM_AccumulationPeriodMsFarEnd::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.


    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));
        for (param = 0; param < myNumberOfParam; param++)
        {
            theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());
            ResetAdjustRegister(param);
        }
        myLayerElementMsFarEnd.ResetSoakCountforUa();
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
