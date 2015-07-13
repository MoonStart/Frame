//Copyright(c) Tellabs Transport Group. All rights reserved

#include <BaseClass/FC_TextStream.h>
#include "../CFG_HoldOffTimer.h"
#include "T6100_Dispatcher.h"


CFG_HoldOffTimer::CFG_HoldOffTimer(FC_Action& theCallbackAction):
    myHoldOffTimer(CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO),
    myHoldOffTimerIsActive(false),
    myLastReturnedApplyCondition(false),
    myLastHoldOffCondition(false),
    myHoldOffCounter(0),
    myHoldOffStartCount(0),
    myLast2ndHoldOffCondition(false),
    my2ndHoldOffCounter(0),
    my2ndHoldOffStartCount(0),
    myHoldOffDelay(CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO)
{
    myAutomaticTimedProcessPtr =  new FC_TimedProcess(theCallbackAction, 
                                                      gTimerDispatcher,
                                                      0);

    myAutomaticDelayedActionPtr = new FC_WakeUpProcessAction(*myAutomaticTimedProcessPtr);
}

CFG_HoldOffTimer::~CFG_HoldOffTimer()
{
    if (myAutomaticTimedProcessPtr)  delete myAutomaticTimedProcessPtr;
    if (myAutomaticDelayedActionPtr) delete myAutomaticDelayedActionPtr;
}



bool CFG_HoldOffTimer::ApplyConditionAfterHoldoff(bool   theHoldOffConditionActive,
                                                  bool   &theHoldOffTimerIsActive,
                                                  uint32 theHoldOffDelay,
                                                  bool   the2ndHCA)
{

        // The return variable. Set when the conditions passed in should be applied,
        // which is when the holdoff condition is true and the holdoff vondition
        // did not tolggle for the time of the delay.
        bool aApplyCondition = false;

        // Indicates whether to start (or restart) the timer.
        bool aStartNewHoldOffTimer = false;

        // Flag stores whether either holdoff condition is set
        bool aIsEitherConditionSet = (theHoldOffConditionActive || the2ndHCA);
        // Flag stores whether either condtion has just changed (toggled) to true
        // Used to start a new timer (and holdoff the apply condition)
        bool aConditionChangedToTrue = false;


        // Now, the fun begins
        // Implement Hold Off Timer
        //
        // The basic function is to test the HoldOff conditions,
        // which are in the theHoldOffConditionActive and the2ndHCA input argumenta,
        // against the HoldOff timer, which is in the theHoldOffDelay
        // input argument.
        //
        // The return value of this method is stored in the aApplyCondition
        // local variable, which indicates whether to apply (perform) the action
        // that this condition enables.
        //
        // If either theHoldOffConditionActive or the2ndHCA is set, there are two possibilities:
        // (1)
        // Delay the setting of aApplyCondition (when requested to delay),
        // which is indicated by setting the aStartNewHoldOffTimer local variable, or
        // (2)
        // Set the aApplyCondition local variable
        //

        // There are data member variables that are used in this bit of code
        // which are defined in the header file (if interested,
        // see the header file for descriptions of these variables)



        // First, check if either condition has changed.
        // When either condition changes, increment the appropriate counter.
        // Note: Also check is either condition has just change to true.
        if (theHoldOffConditionActive != myLastHoldOffCondition)
        {
            myHoldOffCounter++;
            myLastHoldOffCondition = theHoldOffConditionActive;
            if (theHoldOffConditionActive)
            {
                aConditionChangedToTrue = true;
            }
        }

        if (the2ndHCA != myLast2ndHoldOffCondition)
        {
            my2ndHoldOffCounter++;
            myLast2ndHoldOffCondition = the2ndHCA;
            if (the2ndHCA)
            {
                aConditionChangedToTrue = true;
            }
        }


        // Second, check if the HoldOff Timer flag has already been set
        // (meaning the Timer was active coming into the method)
        if (myHoldOffTimerIsActive)
        {
            // Check if Timer has expired.
            // If it hasn't expired, nothing to do
            if(myHoldOffTimer.IsExpired())
            {
                // Turn off HoldOff Timer flag and
                // check if either HoldOff condition still exists
                myHoldOffTimerIsActive = false;
                if (aIsEitherConditionSet)
                {
                    // Finally, make sure the conditions did not toggle
                    // before actually setting the Apply Condition Active flag
                    if ((myHoldOffStartCount == myHoldOffCounter)  && (my2ndHoldOffStartCount == my2ndHoldOffCounter))
                    {
                        // Set local variable will be used for return value
                        aApplyCondition = true;
                    }
                    else
                    {
                        // If a toggle did take place, set flag to (re-) start the timer
                        aStartNewHoldOffTimer = true;
                    }
                }  //  if (theHoldOffConditionActive)
            }  //  if (aTimeExpired)
        }  // if (myHoldOffTimerIsActive)
        else
        {
            // If here, the HoldOff Timer was not active
            // If the Either Condition is Active, then either start
            // the timer or apply the condition
            if (aIsEitherConditionSet)
            {
                // Start the Timer if a condition just turned to true
                // or the Last Apply Condition was false (we were holding off)
                if (aConditionChangedToTrue || (!myLastReturnedApplyCondition))
                {
                    // If either Condition changed to true or the Apply Condition
                    // is not already active, set flag to start the timer
                    aStartNewHoldOffTimer = true;

                } //  if (aConditionChangedToTrue || (myLastReturnedApplyCondition = false))
                else
                {
                    // If ApplayCondition is already true, then make sure the aApplyCondition
                    // is true (so that the Apply Condition will remain set when it is returned)
                    // Note: This means nothing has changed, so keep applying the condition
                    aApplyCondition = true;
                } //  else of: if (aConditionChangedToTrue || (myLastReturnedApplyCondition = false))

            }
        }  // else of: if (myHoldOffTimerIsActive)


        // If requested, start a new timer as requested, (just) do it!
        // Note: the only time it won't be set is if the holdoff delay is zero
        if (aStartNewHoldOffTimer)
        {
            // Check if the Delay Timer to see if it is still the same.
            // If it is not, change it before the timer is activated.
            if (theHoldOffDelay != myHoldOffDelay)
            {
                myHoldOffDelay = theHoldOffDelay;
                myHoldOffTimer.SetPeriod(myHoldOffDelay);
                //  set the times process to expire shortly after the timer expires
                myAutomaticTimedProcessPtr->SetDelay(myHoldOffDelay+1);
            }

            // Make sure that the Timer and Timed Process are greater tham zero
            // before starting them up.
            if (myHoldOffDelay > CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO)
            {
                // Record the Timer is Active
                myHoldOffTimerIsActive = true;

                // Record the HoldOff Condition Count when the timer is set
                myHoldOffStartCount = myHoldOffCounter;
                my2ndHoldOffStartCount = my2ndHoldOffCounter;

                // Start the Base Timer
                myHoldOffTimer.Start();

                // Start the Timer (delayed action)
                myAutomaticDelayedActionPtr->RunWithReason(FC_EsReason::EXECUTION_COMPLETE, 0, 0);
            }  // if (myHoldOffDelay > CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO)
            else
            {
                // If the timer is zero just set the Apply Condition
                // based on the condtions pasted in (which is an OR of the conditions)
                aApplyCondition = aIsEitherConditionSet;
            } // if (myHoldOffDelay > CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO)

        } // if (aStartHoldOffTimer)


        // Save the aApplyCondition flag to help determine whether to start
        // the timer later (don't want to start the timer if aApplyCondition is already active.
        myLastReturnedApplyCondition = aApplyCondition;

        // Done at last
        theHoldOffTimerIsActive = myHoldOffTimerIsActive;
        return aApplyCondition;
}


/*
FC_CmdProcessor::STATUS CFG_HwRefreshAction::Debug(int argc, char **argv)
{
    char aParam[32];
    char aParamState[16];

    //We need at least 2 arguments
    if (argc < 2)
        goto OPTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);
    strcpy(aParamState, argv[1]);

    if (!strncmp(aParam,"hold",4))
    {
        fc_cout   << "HOLD OFF - Last Returned Apply Condition     = " << DISPLAY_BOOL(myLastReturnedApplyCondition) << endl;
        fc_cout   << "HOLD OFF - HoldOff Timer Is Active           = " << DISPLAY_BOOL(myHoldOffTimerIsActive) << endl;
        fc_cout   << "HOLD OFF - Last 1st Holdoff Condition            = " << DISPLAY_BOOL(myLastHoldOffCondition) << endl;
        fc_cout   << "HOLD OFF - 1st Holdoff Start Count               = " << (uint32)myHoldOffStartCount << endl;
        fc_cout   << "HOLD OFF - 1st Holdoff Counter                   = " << (uint32)myHoldOffCounter << endl;
        fc_cout   << "HOLD OFF - Last 2nd Holdoff Condition        = " << DISPLAY_BOOL(myLast2ndHoldOffCondition) << endl;
        fc_cout   << "HOLD OFF - 2nd Holdoff Start Count           = " << (uint32)my2ndHoldOffStartCount << endl;
        fc_cout   << "HOLD OFF - 2nd Holdoff Counter               = " << (uint32)my2ndHoldOffCounter << endl;
        fc_cout   << "HOLD OFF - Last ALS HoldOff Delay (time)         = " << myHoldOffDelay << endl;
    }
    else
    {
        goto OPTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OPTERROR:
    {
        fc_cout << "opt hold-off x   " << endl;
        fc_cout << "odu hold-off x   " << endl;
        fc_cout << "rs hold-off x    " << endl;
        fc_cout << "gfp hold-off x   " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_FAILURE;
}
*/
