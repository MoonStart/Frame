/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Base class for all parameters for an accumulation period.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <PM_RegionImp.h>
#include <PM_BbValue.h>
#include <PM/PM_BbCfg.h>
#include <PM/src/PM_ResetRequestPeriod.h>
#include <PM/src/PM_Rules.h>
#include "PM_AccPeriod.h"


//-----------------------------------------------------------------
//##ModelId=3C1F6F780035
PM_AccumulationPeriod::PM_AccumulationPeriod (PM_GenericApplication &theGenericApplication,
                                              CT_PM_Value*          theMaxValueTable,
                                              PM_Rules&             theRules,
                                              uint32                theNumberOfParam,
                                              uint32                thePortNumber,
                                              CT_PM_Period          thePeriod):
    myGenericApplication(theGenericApplication),
    myMaxValueTable(theMaxValueTable),
    myMaxValueTable64Bit(NULL),
    myNumberOfParam(theNumberOfParam),

    myConfigUpdateAction(),
    myPeriod(thePeriod),
    myPreviousUaState(theNumberOfParam),
    myCurrentResetPtr(NULL),
    // Reference to the Rules used to get the rules.
    myRules(theRules),
    // Accumulation inhibited by default.
    myCurrentAllInhibit (true),
    myIndex(thePortNumber)
{
    InitializeData();
}
 
//-----------------------------------------------------------------
PM_AccumulationPeriod::PM_AccumulationPeriod (PM_GenericApplication &theGenericApplication,
                                              CT_PM_64BitValue*     theMaxValueTable,
                                              PM_Rules&             theRules,
                                              uint32                theNumberOfParam,
                                              uint32                thePortNumber,
                                              CT_PM_Period          thePeriod):
    myGenericApplication(theGenericApplication),
    myMaxValueTable(NULL),
    myMaxValueTable64Bit(theMaxValueTable),
    myNumberOfParam(theNumberOfParam),
 
    myConfigUpdateAction(),
    myPeriod(thePeriod),
    myPreviousUaState(theNumberOfParam),
    myCurrentResetPtr(NULL),
    // Reference to the Rules used to get the rules.
    myRules(theRules),
    // Accumulation inhibited by default.
    myCurrentAllInhibit (true),
    myIndex(thePortNumber)
{
    InitializeData();
}

//-----------------------------------------------------------------
void PM_AccumulationPeriod::InitializeData()
{
    myAdjustRegister = new CT_PM_64bit_ull [myNumberOfParam];

    // Create maximum TCA soaking counter and enable flag.
    myMaxTcaFirstStageSoakingCounter = new uint8 [myNumberOfParam];
    myMaxTcaSecondStageSoakingCounter = new uint8 [myNumberOfParam];
    myMaxTcaFirstStageSoakingEnable = new bool [myNumberOfParam];
    myMaxTcaSecondStageSoakingEnable = new bool [myNumberOfParam];

    // Create maximum TCA occuring time and crossed value arrays.
    myMaxTcaOccurTime = new FC_Time [myNumberOfParam];
    myMaxTcaCrossedValue = new CT_PM_64BitValue [myNumberOfParam];

    // Reset maximum TCA soaking.
    for(uint32 i = 0; i < myNumberOfParam; i++)
    {
        StopMaxTcaFirstStageSoaking(i);
        StopMaxTcaSecondStageSoaking(i);
    }

    // Add itself in to the accumulation period vector owned by Rules class.
    myRules.AddAccumulationPeriod(this);

    // Create reset request handler.
    myCurrentResetPtr = new PM_ResetRequestPeriod((uint8)myNumberOfParam, myGenericApplication, myIndex);

    // Note: These registry are done for each port in the region. So
    // there will have more that one action on the same region.
    GetConfigRegion()->AddObserver(&myConfigUpdateAction);
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780054
PM_AccumulationPeriod::~PM_AccumulationPeriod()
{
    delete [] myAdjustRegister;
    delete [] myMaxTcaFirstStageSoakingCounter;
    delete [] myMaxTcaSecondStageSoakingCounter;
    delete [] myMaxTcaFirstStageSoakingEnable;
    delete [] myMaxTcaSecondStageSoakingEnable;
    delete [] myMaxTcaOccurTime;
    delete [] myMaxTcaCrossedValue;
    delete myCurrentResetPtr;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780056
void PM_AccumulationPeriod::Init(uint16 thePortNumber)
{
    // myIndex is not initialized yet.
    myIndex = thePortNumber;

    // Default accumulation is disabled.
    myCurrentAllInhibit = true;

    // Reset all IDF, inhibit and availability.
    (*GetCurrentValueRegion())[myIndex].GetIdf()->Reset();

    // Ensure that the inhibition status is refreshed in the first run of PM Processor.
    CheckInhibitionChange( (*GetConfigRegion())[myIndex],
                           (*GetCurrentValueRegion())[myIndex]);

    // To be sure it is reset.
    ResetSomeTcaChangedState();

    // Reset current register values.
    ResetAll((*GetCurrentValueRegion())[myIndex]);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780060
bool PM_AccumulationPeriod::AccumulateParameter(bool* theValidityState,
                                                bool* theFilteringStateFirstStage,
                                                bool* theFilteringStateSecondStage)
{
    bool flag = false;
    bool tcaChangedState = false;

    // Verify if any of the following request is pending. If any of these
    // pending request changed the status of at leat one TCA, a notification
    // has to be send to the ADMIN complex, so increment the modification counter.
    flag |= VerifyConfigChange();

    // Reset the control to no TCA.
    ResetSomeTcaChangedState();

    // Update all parameters for a given port. This method returns true if a TCA
    // occurred on at least one parameter.
    tcaChangedState |= UpdatePeriod(theValidityState, theFilteringStateFirstStage, theFilteringStateSecondStage);

    if( tcaChangedState )
    {
        // Mark the current value region as having had a TCA occur
        // on at least one parameter.
        GetCurrentValueRegion()->SetTcaPresent( true );
    }

    flag |= tcaChangedState;

    if (flag)
    {
        // IncModificationCounter current register region,
        // in order to force a blackboard transfer.
        GetCurrentValueRegion()->IncModificationCounter();
    }

    return flag;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7800A4
bool PM_AccumulationPeriod::VerifyConfigChange()
{
    bool changedFlag = false;


    // Check if region is worth investigating for a modification.
    if ( GetConfigVerifyRequest() )
    {
        changedFlag |= CheckResetReqChange((*GetConfigRegion())[myIndex],
                                           (*GetCurrentValueRegion())[myIndex]);

        changedFlag |= CheckInhibitionChange((*GetConfigRegion())[myIndex],
                                             (*GetCurrentValueRegion())[myIndex]);

        changedFlag |= CheckThresholdChange((*GetConfigRegion())[myIndex],
                                            (*GetCurrentValueRegion())[myIndex]);


        SetConfigVerifyRequest(false);
    }

    return changedFlag;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F78018A
void PM_AccumulationPeriod::ResetAll(PM_BbValue& theValue)
{
    ResetAllAdjustRegister();

    theValue.ResetAll();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB500B9
void PM_AccumulationPeriod::ResetAll()
{
    // Reset all parameter value.
    (*GetCurrentValueRegion())[myIndex].ResetAll();

    // Reset all TCA statues.
    (*GetCurrentValueRegion())[myIndex].GetMaxTca()->ResetAllTca();
    if ((*GetCurrentValueRegion())[myIndex].GetMinTca())
        (*GetCurrentValueRegion())[myIndex].GetMinTca()->ResetAllTca();

    // Set all IDF status to invalid.
    (*GetCurrentValueRegion())[myIndex].GetIdf()->ForcedSetAllIdf(true);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F78016E
void PM_AccumulationPeriod::ResetAllAdjustRegister()
{
    uint32 i;

    for (i=0; i<myNumberOfParam; i++)
    {
        myAdjustRegister[i] = 0;
    }

    myPreviousUaState.ResetAllTca();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780176
void PM_AccumulationPeriod::ResetAdjustRegister(CT_PM_Parameter theParam)
{
    myAdjustRegister[theParam] = 0;

    myPreviousUaState.ResetTca(theParam);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780086
void PM_AccumulationPeriod::RegAdjReset()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780072
bool PM_AccumulationPeriod::UpdatePeriod(bool* theValidityState,
                                         bool* theFilteringStateFirstStage,
                                         bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

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
//##ModelId=3E6E4CB4016B
bool PM_AccumulationPeriod::UpdateEndPeriod()
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
//##ModelId=3C1F6F78007C
void PM_AccumulationPeriod::AdjustCurrentIdf()  //Used in Switch
{
    uint32 j;


    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

    // Set inhibition flag in IDF as its per PM_AccumulationPeriod object.

    // For all parameters.
    for (j = 0; j < myNumberOfParam; j++)
    {
        idf.ForcedSetInhibit(j, GetCurrentAllInhibit());
    }

}

//------------------------------------------------------------------
//##ModelId=3FA1610601FD
void PM_AccumulationPeriod::SetAvailability(CT_PM_Parameter theParameter,
                                            bool            theAvailability)
                                            //Used when Monitoring validity changes..
{
    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // Set the availability of the parameter.
    idf.ForcedSetAvailability(theParameter, theAvailability);

}

//------------------------------------------------------------------
//##ModelId=3C1F6F7800E0
bool PM_AccumulationPeriod::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
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
//##ModelId=3FA1610602F7
bool PM_AccumulationPeriod::IsMaxTcaFirstStageSoakingCompleted(CT_PM_Parameter theParameter)
{
    return (myMaxTcaFirstStageSoakingCounter[theParameter] >= PM_TCA_SOAKING_FIRST_STAGE_TIME_SEC);

}

//-----------------------------------------------------------------
//##ModelId=3FA161060326
bool PM_AccumulationPeriod::IsMaxTcaSecondStageSoakingCompleted(CT_PM_Parameter theParameter)
{
    return (myMaxTcaSecondStageSoakingCounter[theParameter] >= PM_TCA_SOAKING_SECOND_STAGE_TIME_SEC);

}

//-----------------------------------------------------------------
//##ModelId=3FA161060355
void PM_AccumulationPeriod::UpdateTcaSoaking(CT_PM_Parameter theParameter)
{
    if (myMaxTcaFirstStageSoakingEnable[theParameter])
        myMaxTcaFirstStageSoakingCounter[theParameter]++;

    if (myMaxTcaSecondStageSoakingEnable[theParameter])
        myMaxTcaSecondStageSoakingCounter[theParameter]++;

}

PM_Rules& PM_AccumulationPeriod::GetRules()
{
    return myRules;
}

