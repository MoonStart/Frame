
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 3, 2010 Larry Wolfrum.
 DESCRIPTION:   Class for all COP parameters for an accumulation
                period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/src/PM_Rules.h>
#include <PM/PM_BbValue.h>
#include <PM/src/PM_ResetRequestPeriod.h>
#include <EPM/src/PM_AccPeriodCop.h>
#include <PM/PM_CopSubApplication.h>


//-----------------------------------------------------------------
PM_AccumulationPeriodCop::PM_AccumulationPeriodCop(PM_GenericApplication &theGenericApplication,
                                                       CT_PM_Value*          theMaxValueTable,
                                                       PM_Rules&             theRules,
                                                       uint32                theNumberOfParam,
                                                       uint32                thePortNumber,
                                                       CT_PM_Period          thePeriod)
    :PM_AccumulationPeriodGauge(theGenericApplication,
                           theMaxValueTable,
                           theRules,
                           theNumberOfParam,
                           thePortNumber,
                           thePeriod),

    myDisableCopInhibit(true),
    myPrevDirectionlessState(false)
{
}

//-----------------------------------------------------------------
PM_AccumulationPeriodCop::~PM_AccumulationPeriodCop()
{
}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodCop::UpdatePeriod(bool* theValidityState,
                                         bool* theFilteringStateFirstStage,
                                         bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    SetSomeTcaChangedState( AdjustForDirectionless( value ) );

    // Check if All parameters accumulation is enabled.
    if ( !GetCurrentAllInhibit() && !(dynamic_cast<PM_CopSubApplication&>(myGenericApplication).IsDirectionless()) )
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, theValidityState,
                                                  theFilteringStateFirstStage,
                                                  theFilteringStateSecondStage,
                                                  false) );
    }

    return GetSomeTcaChangedState();

}

//-----------------------------------------------------------------
bool PM_AccumulationPeriodCop::UpdateEndPeriod()
{
    bool    validityState[PM_MAX_NUMBER_OF_PARAMETERS];               // Computed validity state.
    bool    filteringStateFirstStage[PM_MAX_NUMBER_OF_PARAMETERS];    // Computed filtering state first stage.
    bool    filteringStateSecondStage[PM_MAX_NUMBER_OF_PARAMETERS];   // Computed filtering state second stage.
    uint32  param;                                                    // Parameter index.


    // Set validity state to valid and filtering state to no filtering.
    for (param = 0; param < myNumberOfParam; param++)
    {
        filteringStateFirstStage[param] = false;
        filteringStateSecondStage[param] = false;
        validityState[param] = false;
    }

    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];


    // Check if All parameters accumulation is enabled.
    if ( !GetCurrentAllInhibit() && !(dynamic_cast<PM_CopSubApplication&>(myGenericApplication).IsDirectionless()) )
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, validityState,
                                                  filteringStateFirstStage,
                                                  filteringStateSecondStage,
                                                  true) );
    }

    return GetSomeTcaChangedState();

}

//------------------------------------------------------------------
bool PM_AccumulationPeriodCop::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        // Within a period, any change in inhibition sets the invalid flag.
        theValue.GetIdf()->ForcedSetAllIdf( true );

        if( myDisableCopInhibit && !(GetCurrentAllInhibit()) )
        {
            // This is the first time PM collection has been enabled
            // during this period.
             myDisableCopInhibit = false;
        }

        if( !myDisableCopInhibit )
        {
            bool isDirectionless = dynamic_cast<PM_CopSubApplication&>(myGenericApplication).IsDirectionless();

            for (param = 0; param < myNumberOfParam; param++)
            {
                theValue.GetIdf()->ForcedSetInhibit( param, isDirectionless );
                ResetAdjustRegister(param);
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

bool PM_AccumulationPeriodCop::AdjustForDirectionless( PM_BbValue& theValue )
{
    bool retVal = false;

    if( !myDisableCopInhibit )
    {
        // Determine if the directionless state has changed.
        bool isDirectionless = dynamic_cast<PM_CopSubApplication&>(myGenericApplication).IsDirectionless();

        if( isDirectionless != myPrevDirectionlessState )
        {
            // The directionless state has changed.
            // Reset all of the current data.
            ResetAll();

            // Adjust the IDF inhibit states per the directionless state
            for (uint32 param=0; param<myNumberOfParam; param++)
            {
                theValue.GetIdf()->ForcedSetInhibit( param, isDirectionless );
            }

            myPrevDirectionlessState = isDirectionless;
            retVal = true;
        }
    }
    return retVal;
}

//------------------------------------------------------------------
void PM_AccumulationPeriodCop::AdjustCurrentIdf()
{
    uint32 param;

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

    // Set initial rules for applying directionless inhibit.
    myDisableCopInhibit =  GetCurrentAllInhibit();

    // Adjust the IDF inhibit states per the directionless and configuration inhibit.
    for (param=0; param<myNumberOfParam; param++)
    {
        idf.ForcedSetInhibit( param, myDisableCopInhibit );
    }
}
