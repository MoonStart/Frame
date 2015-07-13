/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004  Hemant Thakkar
 DESCRIPTION:   Class to accumulate Near-End SONET/SDH HOP layer parameters
                for one accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_TypeHopNearEnd.h>
#include <PM/src/PM_RulesHopNearEnd.h>
#include <PM/src/PM_AccPeriodHopNearEnd.h>
#include <PM/PM_HopNearEndSubApplication.h>


//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodHopNearEnd::PM_AccumulationPeriodHopNearEnd( PM_GenericApplication &theGenericApplication,
                                                                CT_PM_Value*          theMaxValueTable,
                                                                PM_Rules&             theRules,
                                                                uint32                thePortNumber,
                                                                CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeHopNearEnd::PM_PARAM_NUM,
                                  thePortNumber,
                                  thePeriod),
    // Regenerator Section stuff.
    myUaDeclaredHopNearEnd(false),
    myPotentialStateChangeHopNearEnd(false),
    myDisableSts1Inhibit(true)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodHopNearEnd::~PM_AccumulationPeriodHopNearEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_AccumulationPeriodHopNearEnd::RegAdjReset()
{
    // This will reset the soaking SES count for the change of UA state.
    myLayerElementHopNearEnd.ResetSoakCountforUa();

    ResetAllAdjustRegister();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodHopNearEnd::UpdatePeriod(bool* theValidityState,
                                                  bool* theFilteringStateFirstStage,
                                                  bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Regenerator section rules.
    PM_RulesHopNearEnd& hopRules = (PM_RulesHopNearEnd&) myRules;


    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myUaDeclaredHopNearEnd =
        myLayerElementHopNearEnd.UpdateUA(hopRules.GetValueParam(PM_TypeHopNearEnd::PM_SES).UnsignedValue==1);
    myPotentialStateChangeHopNearEnd = myLayerElementHopNearEnd.IsPotential2ChgState();

    myUaDeclared = myUaDeclaredHopNearEnd;
    myPotentialStateChange = myPotentialStateChangeHopNearEnd;

    // Apply STS-1 selection adjustments to current value data.
    SetSomeTcaChangedState( AdjustForStst1Selection() );

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
bool PM_AccumulationPeriodHopNearEnd::UpdateEndPeriod()
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
bool PM_AccumulationPeriodHopNearEnd::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        PM_HopNearEndSubApplication &hopApp = dynamic_cast<PM_HopNearEndSubApplication&>(myGenericApplication);

        if( hopApp.GetSide() != CT_PM_LINE_SIDE_0 )
        {
            // This is a port side facility.
            for (param = 0; param < myNumberOfParam; param++)
            {
                theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());

                ResetAdjustRegister(param);
            }
        }
        else
        {
            // Within a period, any change in inhibition sets the
            // invalid flag.
            theValue.GetIdf()->ForcedSetAllIdf( true );

            if( myDisableSts1Inhibit && !(GetCurrentAllInhibit()) )
            {
                // This is the first time PM collection has been enabled
                // during this period.
                myDisableSts1Inhibit = false;
            }

            if( !myDisableSts1Inhibit )
            {
                // Set the non-pointer justication parameters.
                for (param = 0; param < PM_TypeHopNearEnd::PM_PJSTART; param++)
                {
                    theValue.GetIdf()->ForcedSetInhibit( param, false );
                    ResetAdjustRegister(param);
                }
            }
        }

        myLayerElementHopNearEnd.ResetSoakCountforUa();
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
bool PM_AccumulationPeriodHopNearEnd::AdjustForStst1Selection()
{
    bool stsSelectionChanged = false;
    PM_HopNearEndSubApplication &hopApp = dynamic_cast<PM_HopNearEndSubApplication&>(myGenericApplication);

    if( (hopApp.GetSide() == CT_PM_LINE_SIDE_0) && (!myDisableSts1Inhibit) )
    {
        // Determine if an STS selection has changed.
        if( (stsSelectionChanged = hopApp.GetSts1ConfigChanged()) )
        {
            // Get a reference to the IDF object.
            PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

            // Determine if my STS is selected for pointer justification collection
            bool stsSelected = (myIndex == hopApp.GetSelectedSts1()) ? true : false;

            // Now set the pointer justification parameters inhibit based on the STS selection.
            for (uint32 param = PM_TypeHopNearEnd::PM_PJSTART; param < myNumberOfParam; param++)
            {
                if( stsSelected )
                {
                    // This STS is the selected STS.
                    // Set or reaffirm the inhibit setting.
                    idf.ForcedSetInhibit( param, false );

                    // Set or reaffirm the invalid flag to
                    // force a PARTIAL state.
                    idf.ForcedSetIdf( param, true );
                }
                else
                {
                    // If the current state is PARTIAL, leave it as PARTIAL.
                    // If the current state is COMPLETE, change it to PARTIAL.
                    if( (idf.GetIdf( param ) == CT_PM_IDF_COMPLETE) )
                    {
                        idf.ForcedSetIdf( param, true );
                    }
                }
            }
        }
    }
    return stsSelectionChanged;
}

//------------------------------------------------------------------
void PM_AccumulationPeriodHopNearEnd::AdjustCurrentIdf()
{
    uint32 param;

    PM_HopNearEndSubApplication &hopApp = dynamic_cast<PM_HopNearEndSubApplication&>(myGenericApplication);

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

    // Determine if this is the Line or Port side.
    if( hopApp.GetSide() == CT_PM_LINE_SIDE_0 )
    {
        // This is the Line side.

        // Set initial rules for applying STS inhibit.
        myDisableSts1Inhibit =  GetCurrentAllInhibit();

        // Set the IDF inhibit states for the non-pointer justifiction
        // parameters.
        for (param = 0; param < PM_TypeHopNearEnd::PM_PJSTART; param++)
        {
            idf.ForcedSetInhibit( param, myDisableSts1Inhibit );
        }

        // Determine if my STS-1 is selected for pointer justification collection
        bool sts1NotSelected = (myIndex != hopApp.GetSelectedSts1()) ? true : false;

        // Set the IDF inhibit states for the pointer justification parameters
        // based on the selected STS-1.
        for (param=PM_TypeHopNearEnd::PM_PJSTART; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, (sts1NotSelected | myDisableSts1Inhibit) );
        }
    }
    else
    {
        // This is the Port side.

        // Set the IDF inhibit states based on the configuration inhibit.
        for (param=0; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, GetCurrentAllInhibit() );
        }
    }
}
