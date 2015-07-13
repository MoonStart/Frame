/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Class to handle a reset request of any signal.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OchSubApplication.h>

#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbThreshold.h>
#include <PM/PM_BbValue.h>
#include <PM_Def.h>
#include <PM/PM_BbValue.h>
#include <EPM/PM_BbValueOdu.h>
#include <EPM/PM_BbValueTcm.h>
#include <EPM/PM_TypeOdu.h>
#include <EPM/PM_TypeTcm.h>
#include <Configuration/CFG_Odu.h>
#include <Configuration/CFG_Tcm.h>
#include <Configuration/CFG_AppIf.h>

#include <PM/src/PM_ResetRequestPeriod.h>

//-----------------------------------------------------------------
//##ModelId=3C1F6F6200CA
PM_ResetRequestPeriod::PM_ResetRequestPeriod(uint8                  theNumberOfIndex, 
                                             PM_GenericApplication& theGenericApplication,
                                             uint32                 thePortNumber):
    myNumberOfParam(theNumberOfIndex),
    myGenericApplication(theGenericApplication),
    myPortNumber(thePortNumber)
{    
    int counter = 0;


    myResetCurCount = new uint8[myNumberOfParam];
    myResetMinCount = new uint8[myNumberOfParam];
    myResetMaxCount = new uint8[myNumberOfParam];

    for (counter = 0 ; counter < myNumberOfParam ; counter++)
    {
        myResetCurCount[counter] = 0;
        myResetMinCount[counter] = 0;
        myResetMaxCount[counter] = 0;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6200D5
PM_ResetRequestPeriod::~PM_ResetRequestPeriod()
{
    delete [] myResetCurCount;
    delete [] myResetMinCount;
    delete [] myResetMaxCount;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CE20398
bool PM_ResetRequestPeriod::CheckResetCounterReqChange(PM_BbCfg&    theControl, 
                                                       PM_BbValue&  theValue)
{
    bool isRegionChanged = false;
    uint8 counter=0;


    // For all parameters.
    for (counter=0 ; counter < myNumberOfParam ; counter++)
    {
        if (theControl.GetResetCurRegisterCounter(counter) == 0)
        {
            myResetCurCount[counter] = theControl.GetResetCurRegisterCounter(counter);
        }
        else
        {
            // Check if a reset current value is requested.
            if (myResetCurCount[counter] != theControl.GetResetCurRegisterCounter(counter))
            {
                // Reset requested.
                // Update the count stored to acknowledge that the request was processed.
                myResetCurCount[counter] = theControl.GetResetCurRegisterCounter(counter);

                // Perform the reset of the values and the TCA. Set the IDF to invalid.
                theValue.ResetCurParam(counter);
                isRegionChanged = true;
            }
        }
    }

    return isRegionChanged;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CE30029
bool PM_ResetRequestPeriod::CheckResetGaugeReqChange(PM_BbCfg&      theControl, 
                                                     PM_BbValue&    theValue,
                                                     bool           theOduEntity,
                                                     bool           theTcmEntity,
                                                     bbindex_t      theOduTcmIndex)
{
    bool isRegionChanged = false;
    uint8 counter=0;

    // For all parameters.
    for (counter=0 ; counter < myNumberOfParam ; counter++)
    {
        // Current value for accumulation period.
        if (theControl.GetResetCurRegisterCounter(counter) == 0)
        {
            myResetCurCount[counter] = theControl.GetResetCurRegisterCounter(counter);
        }
        else
        {
            // Check if a reset current value is requested.
            if (myResetCurCount[counter] != theControl.GetResetCurRegisterCounter(counter))
            {
                // Reset requested.
                // Update the count stored to acknowledge that the request was processed.
                myResetCurCount[counter] = theControl.GetResetCurRegisterCounter(counter);

                // Perform the reset of the current values.
                theValue.ResetCurParam(counter);
                isRegionChanged = true;
            }
        }

        // Minimum value for accumulation period.
        if (theControl.GetResetMinRegisterCounter(counter) == 0)
        {
            myResetMinCount[counter] = theControl.GetResetMinRegisterCounter(counter);
        }
        else
        {
            // Check if a reset minimum value is requested.
            if (myResetMinCount[counter] != theControl.GetResetMinRegisterCounter(counter))
            {
                // Reset requested.
                isRegionChanged = true;

                // Update the count stored to acknowledge that the request was processed.
                myResetMinCount[counter] = theControl.GetResetMinRegisterCounter(counter);

                bool callDefaultResetMinParamMethod = true;

                //====================================================================================
                // Perform the reset of the minimum values.
                //====================================================================================

                if ( (theOduEntity && (counter == (uint8)PM_TypeOduGauge::PM_DELAY)) ||
                     (theTcmEntity && (counter == (uint8)PM_TypeTcmGauge::PM_DELAY)) )
                {
                    //========================================================================
                    // Special processing is needed for ODU/TCM DELAY value w/ DMSOURCE=En/Disabled.
                    // If DMSOURCE is ENABLED,  then we will set the MinValue/LowValue to MAX!
                    // Now the next iteration of the collector will set gauge LOW value correctly.
                    // If DMSOURCE is DISABLED, then we will set the MinValue/LowValue to zero.
                    //========================================================================
                    if ( theOduEntity )
                    {
                        CFG_Odu& config = dynamic_cast<CFG_Odu&>((*(myGenericApplication.GetCfgApplicationPtr()->GetCfgRegion()))[theOduTcmIndex]);

                        // MR185621:
                        // If pm-mode is disabled, reset min to zero even if DMSOURCE is enabled!
                        if (theControl.GetInhibitParam(counter))
                        {
                            callDefaultResetMinParamMethod = true;
                        }
                        else if ( config.GetPathDelayEnabled() )
                        {
                            PM_BbValueOduGauge* theOduGaugeValue = (dynamic_cast<PM_BbValueOduGauge*>(&theValue));
                            if ( theOduGaugeValue )
                            {
                                callDefaultResetMinParamMethod = false; ///////////////
                                theOduGaugeValue->ResetMinParamDMSourceEnabled(counter);
                            }
                        }
                    }
                    else // theTcmEntity...
                    {
                        CFG_Tcm& config = dynamic_cast<CFG_Tcm&>((*(myGenericApplication.GetCfgApplicationPtr()->GetCfgRegion()))[theOduTcmIndex]);
                        if (theControl.GetInhibitParam(counter))
                        {
                            callDefaultResetMinParamMethod = true;
                        }
                        if ( config.GetTcmDelayEnabled() )
                        {
                            PM_BbValueTcmGauge* theTcmGaugeValue = (dynamic_cast<PM_BbValueTcmGauge*>(&theValue));
                            if ( theTcmGaugeValue )
                            {
                                callDefaultResetMinParamMethod = false; ///////////////
                                theTcmGaugeValue->ResetMinParamDMSourceEnabled(counter);
                            }
                        }
                    }
                }

                if ( callDefaultResetMinParamMethod )
                {
                    theValue.ResetMinParam(counter);
                }
            }
        }

        // Maximum value for accumulation period.
        if (theControl.GetResetMaxRegisterCounter(counter) == 0)
        {
            myResetMaxCount[counter] = theControl.GetResetMaxRegisterCounter(counter);
        }
        else
        {
            // Check if a reset maximum value is requested.
            if (myResetMaxCount[counter] != theControl.GetResetMaxRegisterCounter(counter))
            {
                // Reset requested.
                // Update the count stored to acknowledge that the request was processed.
                myResetMaxCount[counter] = theControl.GetResetMaxRegisterCounter(counter);

                // Perform the reset of the maximum values.
                theValue.ResetMaxParam(counter);
                isRegionChanged = true;
            }
        }
    }

    return isRegionChanged;

}

//-----------------------------------------------------------------
bool PM_ResetRequestPeriod::CheckResetRmonGaugeReqChange( PM_BbCfg&          theControl, 
                                                          PM_BbValue&        theValue,
                                                          PM_RulesRmonGauge& theRules )
{
    bool isRegionChanged = false;
    uint8 counter=0;


    // For all parameters.
    for (counter=0 ; counter < myNumberOfParam ; counter++)
    {
        // Current value for accumulation period.
        if (theControl.GetResetCurRegisterCounter(counter) == 0)
        {
            myResetCurCount[counter] = theControl.GetResetCurRegisterCounter(counter);
        }
        else
        {
            // Check if a reset current value is requested.
            if (myResetCurCount[counter] != theControl.GetResetCurRegisterCounter(counter))
            {
                // Reset requested.
                // Update the count stored to acknowledge that the request was processed.
                myResetCurCount[counter] = theControl.GetResetCurRegisterCounter(counter);

                // Reset the history state in the appropriate RMON status object.
                theRules.ResetParams();

                // Perform the reset of the current values.
                theValue.ResetCurParam(counter);
                isRegionChanged = true;
            }
        }

        // Minimum value for accumulation period.
        if (theControl.GetResetMinRegisterCounter(counter) == 0)
        {
            myResetMinCount[counter] = theControl.GetResetMinRegisterCounter(counter);
        }
        else
        {
            // Check if a reset minimum value is requested.
            if (myResetMinCount[counter] != theControl.GetResetMinRegisterCounter(counter))
            {
                // Reset requested.
                // Update the count stored to acknowledge that the request was processed.
                myResetMinCount[counter] = theControl.GetResetMinRegisterCounter(counter);

                // Perform the reset of the minimum values.
                theValue.ResetMinParam(counter);
                isRegionChanged = true;
            }
        }

        // Maximum value for accumulation period.
        if (theControl.GetResetMaxRegisterCounter(counter) == 0)
        {
            myResetMaxCount[counter] = theControl.GetResetMaxRegisterCounter(counter);
        }
        else
        {
            // Check if a reset maximum value is requested.
            if (myResetMaxCount[counter] != theControl.GetResetMaxRegisterCounter(counter))
            {
                // Reset requested.
                // Update the count stored to acknowledge that the request was processed.
                myResetMaxCount[counter] = theControl.GetResetMaxRegisterCounter(counter);

                // Perform the reset of the maximum values.
                theValue.ResetMaxParam(counter);
                isRegionChanged = true;
            }
        }
    }

    return isRegionChanged;

}
