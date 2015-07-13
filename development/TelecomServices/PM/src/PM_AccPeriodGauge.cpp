/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 15, 2002 Sebastien Cossette.
 DESCRIPTION:   Base class for all gauge parameters for an accumulation period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/src/PM_Rules.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_BbValueOpt.h>
#include <PM/PM_TypeOpt.h>
#include <PM/src/PM_ResetRequestPeriod.h>
#include <PM/src/PM_AccPeriodGauge.h>
#include <EPM/src/PM_AccPeriodOduGauge.h>
#include <EPM/src/PM_AccPeriodTcmGauge.h>
#include <EPM/src/PM_AccPeriodRmonGauge.h>

//-----------------------------------------------------------------
//##ModelId=3E6E4CBC034E
PM_AccumulationPeriodGauge::PM_AccumulationPeriodGauge(PM_GenericApplication &theGenericApplication,
                                                       CT_PM_Value*          theMaxValueTable,
                                                       PM_Rules&             theRules,
                                                       uint32                theNumberOfParam,
                                                       uint32                thePortNumber,
                                                       CT_PM_Period          thePeriod)
    :PM_AccumulationPeriod(theGenericApplication,
                           theMaxValueTable,
                           theRules,
                           theNumberOfParam,
                           thePortNumber,
                           thePeriod)
{
    // Create minimum TCA soaking counter and enable flag.
    myMinTcaFirstStageSoakingCounter = new uint8 [theNumberOfParam];
    myMinTcaSecondStageSoakingCounter = new uint8 [theNumberOfParam];
    myMinTcaFirstStageSoakingEnable = new bool [theNumberOfParam];
    myMinTcaSecondStageSoakingEnable = new bool [theNumberOfParam];
    myPrevFilteringStateFirstStage = new bool[theNumberOfParam];
    myPrevFilteringStateSecondStage = new bool[theNumberOfParam];

    // Create maximum TCA occuring time and crossed value arrays.
    myMinTcaOccurTime = new FC_Time [theNumberOfParam];
    myMinTcaCrossedValue = new CT_PM_Value [theNumberOfParam];

    // Reset minimum TCA soaking.
    for(uint32 i = 0; i < myNumberOfParam; i++)
    {
        StopMinTcaFirstStageSoaking(i);
        StopMinTcaSecondStageSoaking(i);
        myPrevFilteringStateFirstStage[i] = false;
        myPrevFilteringStateSecondStage[i] = false;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBC036D
PM_AccumulationPeriodGauge::~PM_AccumulationPeriodGauge()
{
    delete [] myMinTcaFirstStageSoakingCounter;
    delete [] myMinTcaSecondStageSoakingCounter;
    delete [] myMinTcaFirstStageSoakingEnable;
    delete [] myMinTcaSecondStageSoakingEnable;
    delete [] myMinTcaOccurTime;
    delete [] myMinTcaCrossedValue;
    delete [] myPrevFilteringStateFirstStage;
    delete [] myPrevFilteringStateSecondStage;

}

//-----------------------------------------------------------------------
//Update the PM Parameters for this period
//##ModelId=3E6E4CBC0376
bool PM_AccumulationPeriodGauge::UpdatePeriodOfAll(PM_BbValue& theValue,
                                                   PM_BbCfg&   theConfig,
                                                   bool*       theValidityState,
                                                   bool*       theFilteringStateFirstStage,
                                                   bool*       theFilteringStateSecondStage,
                                                   bool        theEndOfPeriod)
{
    bool        someTcaChangedState = false;
    int32       minThreshold = 0;
    int32       maxThreshold = 0;
    CT_PM_64BitValue newValue;
    bool        continueMinTcaProcessing;
    bool        continueMaxTcaProcessing;

    //-------------------------------------------------------------------
    // PM_AccumulationPeriod(Odu/Tcm)Gauge DELAY should NOT issue TCA at zero!
    // NOTE: "ZeroValue" here is the value of the newValue!
    //-------------------------------------------------------------------
    bool allowTCAonZeroValue = true;
    if ( dynamic_cast<PM_AccumulationPeriodOduGauge*>(this) ||
         dynamic_cast<PM_AccumulationPeriodTcmGauge*>(this) )
    {
        allowTCAonZeroValue = false;
    }

    //-------------------------------------------------------------------
    // PM_AccumulationPeriod(RMON)Gauge UTIL-HT should NOT issue TCA at zero!
    // NOTE: "ZeroValue" here is the value of the maxThreshold!
    //-------------------------------------------------------------------
    bool allow_HT_TCAonZeroValue = true;
    if ( dynamic_cast<PM_AccumulationPeriodRmonGauge*>(this) ||
         dynamic_cast<PM_AccumulationPeriodOduGauge*>(this) )
    {
        allow_HT_TCAonZeroValue = false;
    }

    for(uint32 i = 0; i < myNumberOfParam; i++)
    {
        CT_PM_64BitValue unionValue;
        CT_PM_Value unionMaxValue;

        unionValue.SignedValue = (myRules.GetValueParam(i)).SignedValue;
        unionMaxValue = myMaxValueTable[i];

        // NOTE: When TCA inhibition is active, accumulate but no TCA declared.
        // Same thing if monitoring is invalid.
        newValue.SignedValue = (AddValue(theValue, i, unionValue, unionMaxValue,
                                false, false, theEndOfPeriod)).SignedValue;

        // Update TCA soaking counters.
        UpdateTcaSoaking(i);

        //
        // VERIFY UNFITERED TCAS:
        //

        // If monitoring is valid.
        if (theValidityState[i])
        {
            if (!GetCurrentAllTcaInhibit())
            {
                theConfig.GetThreshold(i, minThreshold, maxThreshold);

                if( dynamic_cast<PM_BbValueOpt*>(&theValue) && (i == PM_TypeOpt::PM_OSNR) )
                {
                    allowTCAonZeroValue = false;
                }
                // Minimum threshold?
                if ( (newValue.SignedValue <= minThreshold) && 
                     ((newValue.SignedValue!=0) || allowTCAonZeroValue) &&
                     (!theValue.GetMinTca()->GetTcaUnFilteredState(i)) )
                {
                    // A TCA minimum unfiltered has occured.
                    theValue.GetMinTca()->SetTcaUnFiltered(i);
                    // Keep a snapshot of crossed value and occuring time.
                    myMinTcaOccurTime[i].GetCurrentTime();
                    myMinTcaCrossedValue[i].SignedValue = (int32)newValue.SignedValue;

                    // If first stage filtering required.
                    if (theFilteringStateFirstStage)
                    {
                        // Start TCA minimum soaking of first stage.
                        StartMinTcaFirstStageSoaking(i);
                        // If second stage filtering required.
                        if (theFilteringStateSecondStage)
                        {
                            // Start TCA minimum soaking of second stage.
                            StartMinTcaSecondStageSoaking(i);
                        }
                    }
                    // If TCA minimum not already declared.
                    else if (!(theValue.GetMinTca()->GetTcaState(i)))
                    {
                        // A TCA minimum has occured.
                        CT_PM_64BitValue temp64BitValue;
                        temp64BitValue.SignedValue = myMinTcaCrossedValue[i].SignedValue;
                        theValue.GetMinTca()->SetBbTca(i, myMinTcaOccurTime[i], temp64BitValue);
                        someTcaChangedState = true;
                    }
                }

                // Maximum threshold?
                if ( (newValue.SignedValue >= maxThreshold) && 
                     ((maxThreshold!=0) || allow_HT_TCAonZeroValue) &&
                     (!theValue.GetMaxTca()->GetTcaUnFilteredState(i)) )
                {
                    // A TCA maximum unfiltered has occured.
                    theValue.GetMaxTca()->SetTcaUnFiltered(i);
                    // Keep a snapshot of crossed value and occuring time.
                    myMaxTcaOccurTime[i].GetCurrentTime();
                    myMaxTcaCrossedValue[i] = newValue;

                    // If first stage filtering required.
                    if (theFilteringStateFirstStage)
                    {
                        // Start TCA maximum soaking of first stage.
                        StartMaxTcaFirstStageSoaking(i);
                        // If second stage filtering required.
                        if (theFilteringStateSecondStage)
                            // Start TCA maximum soaking of second stage.
                            StartMaxTcaSecondStageSoaking(i);
                    }
                    // If TCA maximum not already declared.
                    else if (!(theValue.GetMaxTca()->GetTcaState(i)))
                    {
                        // A TCA maximum has occured.
                        theValue.GetMaxTca()->SetBbTca(i, myMaxTcaOccurTime[i], myMaxTcaCrossedValue[i]);
                        someTcaChangedState = true;
                    }
                }
            }
        }

        //
        // VERIFY FILTERED TCAS:
        //

        // If TCA minimum unfiltered declared.
        if ( theValue.GetMinTca()->GetTcaUnFilteredState(i))
        {
            // If either the first stage or second stage filter state
            // changed to false from the previous state, clear the
            // unfiltered TCA and skip the remaining processing.
            continueMinTcaProcessing = true;
            if (theFilteringStateFirstStage)
            {
                if ((!theFilteringStateFirstStage[i]) && myPrevFilteringStateFirstStage[i])
                {
                    continueMinTcaProcessing = false;
                    StopMinTcaFirstStageSoaking(i);
                    theValue.GetMinTca()->ResetTcaUnFiltered(i);
                    if (theFilteringStateSecondStage)
                    {
                        StopMinTcaSecondStageSoaking(i);
                    }
                }
            }
            if (theFilteringStateSecondStage)
            {
                if ((!theFilteringStateSecondStage[i]) && myPrevFilteringStateSecondStage[i])
                {
                    continueMinTcaProcessing = false;
                    StopMinTcaSecondStageSoaking(i);
                    theValue.GetMinTca()->ResetTcaUnFiltered(i);
                }
            }
            if (continueMinTcaProcessing)
            {
                // If first stage soaking is completed.
                if (IsMinTcaFirstStageSoakingCompleted(i))
                {
                    // Stop soaking or first stage.
                    StopMinTcaFirstStageSoaking(i);
                    // Verify if not already declared and no first stage filtering condition on and
                    // second filtering stage is not required.
                    if ( !((theValue.GetMinTca()->GetTcaState(i)) || 
                           (theFilteringStateFirstStage && theFilteringStateFirstStage[i]) ||
                           (theFilteringStateSecondStage)) )
                    {
                        // A TCA minimum has occured.
                        CT_PM_64BitValue temp64BitValue;
                        temp64BitValue.SignedValue = myMinTcaCrossedValue[i].SignedValue;
                        theValue.GetMinTca()->SetBbTca(i, myMinTcaOccurTime[i], temp64BitValue);
                        // Stop soaking of second stage. It is not necessary to wait second stage.
                        StopMinTcaSecondStageSoaking(i);
                        someTcaChangedState = true;
                    }
                    // If filtering condition on and second filtering required.
                    else if ( (theFilteringStateFirstStage && theFilteringStateFirstStage[i]) && 
                              (theFilteringStateSecondStage) )
                    {
                        // Stop soaking of second stage. It is not necessary to wait second stage.
                        StopMinTcaSecondStageSoaking(i);
                        // Reset TCA minimum unfiltered.
                        theValue.GetMinTca()->ResetTcaUnFiltered(i);
                    }
                    // If filtering of second stage is not required.
                    else if (!theFilteringStateSecondStage)
                    {
                        // Reset TCA minimum unfiltered.
                        theValue.GetMinTca()->ResetTcaUnFiltered(i);
                    }
                }
                // If second stage soaking is completed.
                else if (IsMinTcaSecondStageSoakingCompleted(i))
                {
                    // Stop soaking of second stage.
                    StopMinTcaSecondStageSoaking(i);
                    // Verify if not already declared and no second stage filtering condition on.
                    if ( !((theValue.GetMinTca()->GetTcaState(i)) || 
                           (theFilteringStateSecondStage && theFilteringStateSecondStage[i])) )
                    {
                        // A TCA minimum has occured.
                        CT_PM_64BitValue temp64BitValue;
                        temp64BitValue.SignedValue = myMinTcaCrossedValue[i].SignedValue;
                        theValue.GetMinTca()->SetBbTca(i, myMinTcaOccurTime[i], temp64BitValue);
                        someTcaChangedState = true;
                    }
                    else
                    {
                        // Reset TCA minimum unfiltered.
                        theValue.GetMinTca()->ResetTcaUnFiltered(i);
                    }
                }
            }
        }

        // If TCA maximum unfiltered declared.
        if ( theValue.GetMaxTca()->GetTcaUnFilteredState(i))
        {
            // If either the first stage or second stage filter state
            // changed to false from the previous state, clear the
            // unfiltered TCA and skip the remaining processing.
            // If either the first stage or second stage filter state
            // changed to false from the previous state, clear the
            // unfiltered TCA and skip the remaining processing.
            continueMaxTcaProcessing = true;
            if (theFilteringStateFirstStage)
            {
                if ((!theFilteringStateFirstStage[i]) && myPrevFilteringStateFirstStage[i])
                {
                    continueMaxTcaProcessing = false;
                    StopMaxTcaFirstStageSoaking(i);
                    theValue.GetMaxTca()->ResetTcaUnFiltered(i);
                    if (theFilteringStateSecondStage)
                    {
                        StopMaxTcaSecondStageSoaking(i);
                    }
                }
            }
            if (theFilteringStateSecondStage)
            {
                if ((!theFilteringStateSecondStage[i]) && myPrevFilteringStateSecondStage[i])
                {
                    continueMaxTcaProcessing = false;
                    StopMaxTcaSecondStageSoaking(i);
                    theValue.GetMaxTca()->ResetTcaUnFiltered(i);
                }
            }
            if (continueMaxTcaProcessing)
            {
                // If first stage soaking is completed.
                if (IsMaxTcaFirstStageSoakingCompleted(i))
                {
                    // Stop soaking or first stage.
                    StopMaxTcaFirstStageSoaking(i);
                    // Verify if not already declared and no first stage filtering condition on and
                    // second filtering stage is not required.
                    if ( !((theValue.GetMaxTca()->GetTcaState(i)) || 
                           (theFilteringStateFirstStage && theFilteringStateFirstStage[i]) ||
                           (theFilteringStateSecondStage)) )
                    {
                        // A TCA maximum has occured.
                        theValue.GetMaxTca()->SetBbTca(i, myMaxTcaOccurTime[i], myMaxTcaCrossedValue[i]);
                        // Stop soaking of second stage. It is not necessary to wait second stage.
                        StopMaxTcaSecondStageSoaking(i);
                        someTcaChangedState = true;
                    }
                    // If filtering condition on and second filtering required.
                    else if ( (theFilteringStateFirstStage && theFilteringStateFirstStage[i]) && 
                              (theFilteringStateSecondStage) )
                    {
                        // Stop soaking of second stage. It is not necessary to wait second stage.
                        StopMaxTcaSecondStageSoaking(i);
                        // Reset TCA maximum unfiltered.
                        theValue.GetMaxTca()->ResetTcaUnFiltered(i);
                    }
                    // If filtering of second stage is not required.
                    else if (!theFilteringStateSecondStage)
                    {
                        // Reset TCA maximum unfiltered.
                        theValue.GetMaxTca()->ResetTcaUnFiltered(i);
                    }
                }
                // If second stage soaking is completed.
                else if (IsMaxTcaSecondStageSoakingCompleted(i))
                {
                    // Stop soaking of second stage.
                    StopMaxTcaSecondStageSoaking(i);
                    // Verify if not already declared and no second stage filtering condition on.
                    if ( !((theValue.GetMaxTca()->GetTcaState(i)) || 
                           (theFilteringStateSecondStage && theFilteringStateSecondStage[i])) )
                    {
                        // A TCA maximum has occured.
                        theValue.GetMaxTca()->SetBbTca(i, myMaxTcaOccurTime[i], myMaxTcaCrossedValue[i]);
                        someTcaChangedState = true;
                    }
                    else
                    {
                        // Reset TCA maximum unfiltered.
                        theValue.GetMaxTca()->ResetTcaUnFiltered(i);
                    }
                }
            }
        }

        if (theFilteringStateFirstStage)
        {
            myPrevFilteringStateFirstStage[i] = theFilteringStateFirstStage[i];
        }
        if (theFilteringStateSecondStage)
        {
            myPrevFilteringStateSecondStage[i] = theFilteringStateSecondStage[i];
        }
    }

    return someTcaChangedState;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBC039F
CT_PM_64BitValue PM_AccumulationPeriodGauge::AddValue(
                                                 PM_BbValue&        theValue,
                                                 CT_PM_Parameter    theParam,
                                                 CT_PM_64BitValue   theNumber,
                                                 CT_PM_Value        theMaxValue,
                                                 bool               theUaState,
                                                 bool               thePotential2ChgState,
                                                 bool               theEndOfPeriod)
{
    CT_PM_64BitValue tempValue;
    CT_PM_64BitValue unionValue;
    CT_PM_64BitValue unionMinValue;
    CT_PM_64BitValue unionMaxValue;

    tempValue = theNumber;
    theValue.GetValues(theParam, unionValue, unionMinValue, unionMaxValue);

    // Accumulation of parameter.

    // Verify maximum and minimum values.
    if (tempValue.SignedValue > theMaxValue.SignedValue)
    {
        CT_PM_64BitValue a64BitValue;
        a64BitValue.SignedValue = theMaxValue.SignedValue;
        tempValue = a64BitValue;
    }
    else if (tempValue.SignedValue < -(theMaxValue.SignedValue))
    {
        tempValue.SignedValue = -theMaxValue.SignedValue;
    }

    // Set the new values.
    unionValue = tempValue;
    if (unionValue.SignedValue >= unionMaxValue.SignedValue)
        unionMaxValue = unionValue;
    if (unionValue.SignedValue <= unionMinValue.SignedValue)
        unionMinValue = unionValue;

    theValue.SetValues(theParam, unionValue, unionMinValue, unionMaxValue);


    return tempValue;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBC03D0
bool PM_AccumulationPeriodGauge::CheckThresholdChange(PM_BbCfg&     theThreshold,
                                                      PM_BbValue&   theValue)
{
    uint32         param;
    bool        someTcaChangedState = false;
    bool        minThresholdChanged;
    bool        maxThresholdChanged;
    int32       minThreshold;
    int32       maxThreshold;
    CT_PM_64BitValue unionValue;
    CT_PM_64BitValue unionMinValue;
    CT_PM_64BitValue unionMaxValue;


    // For all PM parameters for this layer, verify if the new configured
    // minimum threshold value is lower than the current value and if the
    // new maximum threshold value is higher than the current value. If so
    // and a TCA is set, reset the TCA.
    for (param = 0; param < myNumberOfParam; param++)
    {
        // Get current threshold values.
        theThreshold.GetThreshold(param, minThreshold, maxThreshold);

        // Get current threshold flag of change.
        theThreshold.HasThresholdChanged(param, minThresholdChanged, maxThresholdChanged);

        // Get current values.
        theValue.GetValues(param, unionValue, unionMinValue, unionMaxValue);

        // Check if the minimum TCA is set before verifying if
        // it needs resetting and if threshold value has really
        // changed.
        if ( theValue.GetMinTca()->GetTcaState(param) && minThresholdChanged )
        {
            // Check if the new threshold values are higher and
            // lower than the current value read.
            // Minimum threshold. Verification of unfiltered TCA
            // is not necessary since it is re-armed after soaking.
            if ( unionValue.SignedValue > minThreshold )
            {
                // New minimum threshold value doesn't cause a TCA:
                // reset the maximum TCA.
                theValue.GetMinTca()->ResetTca(param);
                someTcaChangedState = true;
            }
        }

        // Check if the maximum TCA is set before verifying if
        // it needs resetting and if threshold value has really
        // changed.
        if ( theValue.GetMaxTca()->GetTcaState(param) && maxThresholdChanged )
        {
            // Check if the new threshold values are higher and
            // lower than the current value read.
            // Maximum threshold. Verification of unfiltered TCA
            // is not necessary since it is re-armed after soaking.
            if ( unionValue.SignedValue < maxThreshold )
            {
                // New maximum threshold value doesn't cause a TCA:
                // reset the maximum TCA.
                theValue.GetMaxTca()->ResetTca(param);
                someTcaChangedState = true;
            }
        }
    }

    return someTcaChangedState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBC03E6
bool PM_AccumulationPeriodGauge::CheckResetReqChange(PM_BbCfg    &theConfig,
                                                     PM_BbValue& theCurrentValue)
{

    return myCurrentResetPtr->CheckResetGaugeReqChange(theConfig, theCurrentValue);

}

//-----------------------------------------------------------------
//##ModelId=3FA161070393
bool PM_AccumulationPeriodGauge::IsMinTcaFirstStageSoakingCompleted(CT_PM_Parameter theParameter)
{
    return (myMinTcaFirstStageSoakingCounter[theParameter] >= PM_TCA_SOAKING_FIRST_STAGE_TIME_SEC);

}

//-----------------------------------------------------------------
//##ModelId=3FA1610703D1
bool PM_AccumulationPeriodGauge::IsMinTcaSecondStageSoakingCompleted(CT_PM_Parameter theParameter)
{
    return (myMinTcaSecondStageSoakingCounter[theParameter] >= PM_TCA_SOAKING_SECOND_STAGE_TIME_SEC);

}

//-----------------------------------------------------------------
//##ModelId=3FA1610703E1
void PM_AccumulationPeriodGauge::UpdateTcaSoaking(CT_PM_Parameter theParameter)
{
    if (myMinTcaFirstStageSoakingEnable[theParameter])
        myMinTcaFirstStageSoakingCounter[theParameter]++;

    if (myMinTcaSecondStageSoakingEnable[theParameter])
        myMinTcaSecondStageSoakingCounter[theParameter]++;

    // Call base class for maximum TCA.
    PM_AccumulationPeriod::UpdateTcaSoaking(theParameter);

}
