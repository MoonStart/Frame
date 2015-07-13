/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 DESCRIPTION:   Base class for all counter parameters for an accumulation
                period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/src/PM_Rules.h>
#include <PM/PM_BbValue.h>
#include <EPM/PM_TypeOdu.h>
#include <PM/PM_TypeOtu.h>
#include <EPM/PM_TypeTcm.h>
#include <PM/src/PM_ResetRequestPeriod.h>
#include <PM/src/PM_AccPeriodCounter.h>
#include <EPM/src/PM_AccPeriodOdu.h>
#include <EPM/src/PM_AccPeriodOtu.h>
#include <EPM/src/PM_AccPeriodTcm.h>

//-----------------------------------------------------------------
//##ModelId=3E6E4CC2034C
PM_AccumulationPeriodCounter::PM_AccumulationPeriodCounter(PM_GenericApplication &theGenericApplication,
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
                           thePeriod),
    myUaDeclared(false),
    myPotentialStateChange(false)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_AccumulationPeriodCounter::PM_AccumulationPeriodCounter(PM_GenericApplication &theGenericApplication,
                                                           CT_PM_64BitValue*     theMaxValueTable,
                                                           PM_Rules&             theRules,
                                                           uint32                theNumberOfParam,
                                                           uint32                thePortNumber,
                                                           CT_PM_Period          thePeriod)
    :PM_AccumulationPeriod(theGenericApplication,
                           theMaxValueTable,
                           theRules,
                           theNumberOfParam,
                           thePortNumber,
                           thePeriod),
    myUaDeclared(false),
    myPotentialStateChange(false)
{
    // Nothing to do for now.
 
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC20388
PM_AccumulationPeriodCounter::~PM_AccumulationPeriodCounter()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------------
//Update the PM Parameters for this period
//##ModelId=3E6E4CC20392
bool PM_AccumulationPeriodCounter::UpdatePeriodOfAll(PM_BbValue& theValue,
                                                     PM_BbCfg&   theConfig,
                                                     bool*       theValidityState,
                                                     bool*       theFilteringStateFirstStage,
                                                     bool*       theFilteringStateSecondStage,
                                                     bool        theEndOfPeriod)
{
    bool someTcaChangedState = false;
    CT_PM_64bit_ull maxThreshold = 0;
    CT_PM_64BitValue newValue;

    for(uint32 i = 0; i < myNumberOfParam; i++)
    {
        CT_PM_64BitValue unionValue;
        CT_PM_64BitValue unionMaxValue;

        unionValue.UnsignedValue = (myRules.GetValueParam(i)).UnsignedValue;
        unionMaxValue = GetMaxValueTable(i);

        // NOTE: If the threshold is zero, accumulate but no TCA declared.
        // Same thing when TCA inhibition is active or if monitoring is
        // invalid.
        newValue.UnsignedValue = (AddValue(theValue, i, unionValue, unionMaxValue,
                                  myUaDeclared, myPotentialStateChange, theEndOfPeriod)).UnsignedValue;

        // Update TCA soaking counters.
        UpdateTcaSoaking(i);

        //
        // VERIFY UNFITERED MAXIMUM TCA:
        //

        // If monitoring is valid.
        if (theValidityState[i])
        {
            maxThreshold = theConfig.GetThreshold(i);

            // Threshold crossing (maximum only) ?
            if ( ( newValue.UnsignedValue >= maxThreshold) && maxThreshold &&
                   !GetCurrentAllTcaInhibit())
            {
                // Verify if not already declared.
                if ( ! theValue.GetMaxTca()->GetTcaUnFilteredState(i) )
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
                        theValue.GetMaxTca()->SetBbTca(i, myMaxTcaOccurTime[i], myMaxTcaCrossedValue[i], GetEntityTypeFor64BitPM());
                        someTcaChangedState = true;
                    }
                }
            }
        }

        //
        // VERIFY FILTERED MAXIMUM TCA:
        //

        // If TCA maximum unfiltered declared.
        if ( theValue.GetMaxTca()->GetTcaUnFilteredState(i))
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
                    theValue.GetMaxTca()->SetBbTca(i, myMaxTcaOccurTime[i], myMaxTcaCrossedValue[i], GetEntityTypeFor64BitPM());

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
                                        
                }
                // Else: for counter TCA unfiltered is not reset (not re-armed).
                // otherwise TCA filter will always pop after soaking
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
                    theValue.GetMaxTca()->SetBbTca(i, myMaxTcaOccurTime[i], myMaxTcaCrossedValue[i], GetEntityTypeFor64BitPM());
                    someTcaChangedState = true;
                }
                // Else: for counter TCA unfiltered is not reset (not re-armed).
                // otherwise TCA filter will always pop after soaking
            }
        }

    }

    return someTcaChangedState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC203B1
CT_PM_64BitValue PM_AccumulationPeriodCounter::AddValue(
                                                   PM_BbValue&      theValue,
                                                   CT_PM_Parameter  theParam,
                                                   CT_PM_64BitValue theNumber,
                                                   CT_PM_64BitValue theMaxValue,
                                                   bool             theUaState,
                                                   bool             thePotential2ChgState,
                                                   bool             theEndOfPeriod)
{
    CT_PM_64BitValue tempValue;
    CT_PM_64BitValue unionValue;

    FC_Time currentTime;
    CT_PM_64bit_ull regSpaceLeft;
    bool uasParameter = theValue.IsUasParameter(theParam);
    bool uasAdjParameter = theValue.IsUasAdjustedParameter(theParam);

    //Retreive current time;
    currentTime.GetCurrentTime();

    theValue.GetValue(theParam, unionValue);

    tempValue.UnsignedValue = unionValue.UnsignedValue;

    // If end of period, return the value (for TCA purposes) since it might have not previously been
    // reported due to the potential to change availability.
    if (theEndOfPeriod)
    {
        return tempValue;
    }

    // Not end of period.
    else
    {
        if ((uasAdjParameter) || (uasParameter))
        {
            // If a change of UA state has occured, perform register adjustement.
            if ( (myPreviousUaState.GetTcaState(theParam) == 0 && theUaState ) ||
                 (myPreviousUaState.GetTcaState(theParam) != 0 && !theUaState))
            {
                // If the transition is from Available to Unavailable.
                if (theUaState)
                {
                    // If this is Unavailability Seconds parameter, add the adjustment register
                    // otherwise subtract the adjumstment register.
                    if (uasParameter)
                    {
                        tempValue.UnsignedValue += myAdjustRegister[theParam];
                    }
                    else
                    {
                        // Check if substraction possible to prevent 0 crossing.
                        if (tempValue.UnsignedValue < myAdjustRegister[theParam])
                        {
                            tempValue.UnsignedValue = 0;
                        }
                        else
                        {
                            // Substract adjustement register to current value.
                            tempValue.UnsignedValue -= myAdjustRegister[theParam];
                        }
                    }
                }
                // If the transition is from Unavailable to Available.
                else
                {
                    // If this is Unavailability Seconds parameter, subtract the adjustment register
                    // otherwise add the adjumstment register.
                    if (uasParameter)
                    {
                        // Check if substraction possible to prevent 0 crossing.
                        if (tempValue.UnsignedValue < myAdjustRegister[theParam])
                        {
                            tempValue.UnsignedValue = 0;
                        }
                        else
                        {
                            // Substract adjustement register to current value.
                            tempValue.UnsignedValue -= myAdjustRegister[theParam];
                        }
                    }
                    else
                    {
                        // Add adjustement register to current value.
                        tempValue.UnsignedValue += myAdjustRegister[theParam];
                    }
                }

                // Put the current state in the previous state for next iteration.
                theUaState ? myPreviousUaState.SetBbTca(theParam, currentTime, tempValue, GetEntityTypeFor64BitPM()) : 
                             myPreviousUaState.ResetTca(theParam) ;
                theUaState ? myPreviousUaState.SetTcaUnFiltered(theParam) : myPreviousUaState.ResetTca(theParam) ;

                // Reset adjustement register.
                myAdjustRegister[theParam] = 0;

            } // End of if UA state change.

            // Else if there was no change in the UA state.
            else
            {
                // If there is a potential change of state coming, increment adjustement register.
                if (thePotential2ChgState)
                {
                    regSpaceLeft = (theMaxValue.UnsignedValue - tempValue.UnsignedValue);

                    // Check if the number to add in AdjReg will cross the Max value.
                    if (regSpaceLeft <= theNumber.UnsignedValue)
                    {
                        myAdjustRegister[theParam] += regSpaceLeft;
                    }
                    else
                    {
                        myAdjustRegister[theParam] += theNumber.UnsignedValue;
                    }

                }
                // If no potential, reset it.
                else
                {
                    myAdjustRegister[theParam] = 0;
                }
            }

            // Accumulation of parameter.

            // Accumulate parameter of this second if not in UA state.
            if( (theUaState && uasParameter) || ((!theUaState) && (!uasParameter)) )
            {
                regSpaceLeft = (theMaxValue.UnsignedValue - tempValue.UnsignedValue);

                // Check if the number to add in tempValue will cross the Max value.
                if (regSpaceLeft <= theNumber.UnsignedValue)
                {
                    tempValue.UnsignedValue += regSpaceLeft;
                }
                else
                {
                    tempValue.UnsignedValue += theNumber.UnsignedValue;
                }
            }
        }
        else
        {
            regSpaceLeft = (theMaxValue.UnsignedValue - tempValue.UnsignedValue);

            // Check if the number to add in tempValue will cross the Max value.
            if (regSpaceLeft <= theNumber.UnsignedValue)
            {
                tempValue.UnsignedValue += regSpaceLeft;
            }
            else
            {
                tempValue.UnsignedValue += theNumber.UnsignedValue;
            }
        }

        unionValue = tempValue;

        theValue.SetValue(theParam, unionValue);

        // If in potential to change state, return 0 to prevent an early TCA trig.
        // Else, return the current count.
        if (thePotential2ChgState)
        {
            tempValue.UnsignedValue = 0;
        }
        return tempValue;

    }  // End of else not end of period.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC203E3
bool PM_AccumulationPeriodCounter::CheckThresholdChange(PM_BbCfg&   theConfig,
                                                        PM_BbValue& theValue)
{
    uint32 param;
    bool someTcaChangedState = false;
    CT_PM_64BitValue value;
    CT_PM_64bit_ull maxThreshold;

    // For all PM parameters, verify if the new configured threshold
    // value is higher than the actual value. If so and a TCA is set, reset the TCA.
    for (param = 0; param < myNumberOfParam; param++)
    {
        // Get current threshold value.
        maxThreshold = theConfig.GetThreshold(param);

        // Get current value.
        theValue.GetValue(param, value);

        // Check if the TCA is set before verifying if it needs resetting and
        // if threshold has really changed.
        if ( theValue.GetMaxTca()->GetTcaState(param) && theConfig.HasThresholdChanged(param) )
        {
            // Check if the new threshold is higher than the
            // current value read.
            if ( value.UnsignedValue < maxThreshold)
            {
                // New threshold is higher than accumulation count:
                // reset the TCA.
                theValue.GetMaxTca()->ResetTca(param);
                someTcaChangedState = true;
            }
        }
        // Check if the TCA unfiltered is set before verifying if it needs resetting and
        // if threshold has really changed.
        if ( theValue.GetMaxTca()->GetTcaUnFilteredState(param) && theConfig.HasThresholdChanged(param) )
        {
            // Check if the new threshold is higher than the
            // current value read.
            if ( value.UnsignedValue < maxThreshold)
            {
                // New threshold is higher than accumulation count:
                // reset the TCA unfiltered.
                theValue.GetMaxTca()->ResetTcaUnFiltered(param);
                someTcaChangedState = true;
            }
        }
    }

    return someTcaChangedState;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC3006A
bool PM_AccumulationPeriodCounter::CheckResetReqChange(PM_BbCfg&   theConfig,
                                                       PM_BbValue& theCurrentValue)
{

    return myCurrentResetPtr->CheckResetCounterReqChange(theConfig, theCurrentValue);

}

//-----------------------------------------------------------------
CT_PM_64BitValue PM_AccumulationPeriodCounter::GetMaxValueTable(CT_PM_Parameter theParameter)
{
    if ( myMaxValueTable ) // Normal Processing!
    {
        CT_PM_64BitValue a64BitValue;
        a64BitValue.UnsignedValue = myMaxValueTable[theParameter].UnsignedValue;
        return a64BitValue;
    }
    else // use 64Bit Table!
    {
        return GetMaxValueTable64Bit(theParameter);
    }
}
 
//-----------------------------------------------------------------
// See virtual function from inheriting class(es).
//-----------------------------------------------------------------
CT_PM_64BitValue PM_AccumulationPeriodCounter::GetMaxValueTable64Bit(CT_PM_Parameter theParameter)
{
    return myMaxValueTable64Bit[theParameter];
}

//-----------------------------------------------------------------
// See virtual function from inheriting class(es).
//-----------------------------------------------------------------
CT_EntityType PM_AccumulationPeriodCounter::GetEntityTypeFor64BitPM()
{
    return CT_UNKNOWN_ENTITY_TYPE;
}
