/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 4, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to accumulate Otu Counter parameters for one accumulation 
                period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>

#include <PM/PM_TypeOtu.h>
#include <EPM/src/PM_RulesOtuGauge.h>
#include <EPM/src/PM_AccPeriodOtuGauge.h>

#include <PM/src/PM_ResetRequestPeriod.h>
#include <CommonTypes/CT_Float32.h>

//-----------------------------------------------------------------
// Class default constructor.
PM_AccumulationPeriodOtuGauge::PM_AccumulationPeriodOtuGauge( PM_GenericApplication &theGenericApplication,
                                                      CT_PM_Value*          theMaxValueTable,
                                                      PM_Rules&             theRules,
                                                      uint32                thePortNumber,
                                                      CT_PM_Period          thePeriod):

    PM_AccumulationPeriodGauge( theGenericApplication,
								theMaxValueTable,
								theRules,
								PM_TypeOtuGauge::PM_PARAM_NUM,
								thePortNumber,
								thePeriod)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
PM_AccumulationPeriodOtuGauge::~PM_AccumulationPeriodOtuGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------------
//Update the PM Parameters for this period 
bool PM_AccumulationPeriodOtuGauge::UpdatePeriodOfAll(PM_BbValue& theValue,
                                                   PM_BbCfg&   theConfig,
                                                   bool*       theValidityState, 
                                                   bool*       theFilteringStateFirstStage,
                                                   bool*       theFilteringStateSecondStage,
                                                   bool        theEndOfPeriod)
{
    bool        someTcaChangedState = false;
    int32       minThreshold = 0;
    int32       maxThreshold = 0;
    CT_PM_Value newValue;    
    bool        continueMaxTcaProcessing;


    for(uint32 i = 0; i < myNumberOfParam; i++)
    {
        CT_PM_Value unionValue;
        CT_PM_Value unionMaxValue;
        CT_PM_64BitValue a64BitValue;

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

                // Maximum threshold?
                CT_Float32  newVal(newValue.SignedValue);
                CT_Float32  maxThr(maxThreshold);
                if ( (newVal >= maxThr) && !theValue.GetMaxTca()->GetTcaUnFilteredState(i) )
                {
                    // A TCA maximum unfiltered has occured.
                    theValue.GetMaxTca()->SetTcaUnFiltered(i);
                    // Keep a snapshot of crossed value and occuring time.
                    myMaxTcaOccurTime[i].GetCurrentTime();
                    a64BitValue.SignedValue = newValue.SignedValue;
                    myMaxTcaCrossedValue[i] = a64BitValue;

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
                    if ( !(theValue.GetMaxTca()->GetTcaState(i) || theFilteringStateFirstStage[i] ||
                           theFilteringStateSecondStage))
                    {
                        // A TCA maximum has occured.
                        theValue.GetMaxTca()->SetBbTca(i, myMaxTcaOccurTime[i], myMaxTcaCrossedValue[i]);
                        // Stop soaking of second stage. It is not necessary to wait second stage.
                        StopMaxTcaSecondStageSoaking(i);
                        someTcaChangedState = true;
                    }
                    // If filtering condition on and second filtering required.
                    else if (theFilteringStateFirstStage[i] && theFilteringStateSecondStage)
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
                    if ( !(theValue.GetMaxTca()->GetTcaState(i) || theFilteringStateSecondStage[i]) )
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
CT_PM_Value PM_AccumulationPeriodOtuGauge::AddValue(PM_BbValue&        theValue, 
                                                 CT_PM_Parameter    theParam, 
                                                 CT_PM_Value        theNumber, 
                                                 CT_PM_Value        theMaxValue, 
                                                 bool               theUaState, 
                                                 bool               thePotential2ChgState, 
                                                 bool               theEndOfPeriod)
{
    CT_PM_Value tempValue;
    CT_PM_Value unionValue;
    CT_PM_Value unionMinValue;
    CT_PM_Value unionMaxValue;   

    CT_PM_64BitValue a64BitUnionValue;
    CT_PM_64BitValue a64BitUnionMinValue;
    CT_PM_64BitValue a64BitUnionMaxValue;   

    tempValue = theNumber;
    theValue.GetValues(theParam, a64BitUnionValue, a64BitUnionMinValue, a64BitUnionMaxValue);

    unionValue.SignedValue    = (int32)a64BitUnionValue.SignedValue;
    unionMinValue.SignedValue = (int32)a64BitUnionMinValue.SignedValue;
    unionMaxValue.SignedValue = (int32)a64BitUnionMaxValue.SignedValue;

    // Accumulation of parameter.    

    // Verify maximum and minimum values.
    CT_Float32  tempVal(tempValue.SignedValue);
    CT_Float32  theMaxVal(theMaxValue.SignedValue);
    
    if ( tempVal > theMaxVal )
    {
        tempValue = theMaxValue;
    }

    // Set the new values.
    unionValue = tempValue;
    CT_Float32  unionVal(unionValue.SignedValue);
    CT_Float32  unionMaxVal(unionMaxValue.SignedValue);
    CT_Float32  unionMinVal(unionMinValue.SignedValue);

    if (unionVal > unionMaxVal)
        unionMaxValue = unionValue;
    if (unionVal < unionMinVal)
        unionMinValue = unionValue;

    a64BitUnionValue.SignedValue    = unionValue.SignedValue;
    a64BitUnionMinValue.SignedValue = unionMinValue.SignedValue;
    a64BitUnionMaxValue.SignedValue = unionMaxValue.SignedValue;

    theValue.SetValues(theParam, a64BitUnionValue, a64BitUnionMinValue, a64BitUnionMaxValue);

    return tempValue;
}
