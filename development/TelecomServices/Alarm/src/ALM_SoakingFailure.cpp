/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm  
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class set the failure status according to the defect
                condition (status and counter) for a soaking failure.
--------------------------------------------------------------------------*/

#include "../ALM_SoakingFailure.h"

static const FC_Milliseconds ALM_DONT_CARE_TIME(10);

//-----------------------------------------------------------------
//##ModelId=3C506C3203BE
ALM_SoakingFailure::ALM_SoakingFailure (FC_Milliseconds theSoakingTime, 
                                        FC_Milliseconds theRecoveryTime):

    // Call the constructor of the FC_TimerBase with passing it any value
    itsTimer (ALM_DONT_CARE_TIME),

    // Initialize Soaking timer, Recovery timer
    itsSoakingTime (theSoakingTime),
    itsRecoveryTime (theRecoveryTime)
{
    // reset itsFailureStatus previous transition counter and itsState
    Reset();
}

//-----------------------------------------------------------------
//##ModelId=3C506C3203C9
ALM_SoakingFailure::~ALM_SoakingFailure ()
{
}

//-----------------------------------------------------------------
//##ModelId=3DBFFAE601AF
void ALM_SoakingFailure::Reset()
{
    itsFailureStatus = false;
    itsPreviousTCount = 0;
    itsState = ALM_NORMAL_S;
}

//-----------------------------------------------------------------
//##ModelId=3C506C3203CB
bool ALM_SoakingFailure::DefectUpdated (bool theStatus, ALM_TCount theTCount, bool theRecoveryOverride)
{
    switch (itsState)
    {
    case ALM_NORMAL_S:
        if ( theStatus )
        {
            if (itsSoakingTime)
            {
                // Defect Status is true, go in DEFECT state
                // and start soaking timer
                itsTimer.SetPeriod (itsSoakingTime);
                itsTimer.Start();
                itsState = ALM_DEFECT_S;
            }
            else
            {
                itsState = ALM_FAILURE_S;
                itsFailureStatus = true;
            }           
        }

        break;

    case ALM_DEFECT_S:
        if ( !theStatus )
        {
            // Defect Status is false, go back to NORMAL state
            itsState = ALM_NORMAL_S;
        }
        else if (itsPreviousTCount != theTCount)
        {
            // The previous TCount differs from the current TCount,
            // that means Defect Status goes to false and go back to true.
            // So restart timer because Defect Status was not true for at
            // least "itsSoakingTime" msec.
            itsTimer.Start();
        }
        else if (itsTimer.IsExpired())
        {
            // In DEFECT for "itsSoakingTime" msec., go to FAILURE state
            // and returns failure status to true
            itsState = ALM_FAILURE_S;
            itsFailureStatus = true;
        }
        break;

    case ALM_FAILURE_S:
        if ( !theStatus )
        {
            if(itsRecoveryTime)
            {
                // Defect Status is false, go in RECOVERY state and start recovery timer
                itsTimer.SetPeriod (itsRecoveryTime);
                itsTimer.Start();
                itsState = ALM_RECOVERY_S;
            }
            else
            {
                //Go right to Normal state
                itsState = ALM_NORMAL_S;
                itsFailureStatus = false;
            }

        }
        break;

    case ALM_RECOVERY_S:
        if ( theStatus )
        {
            // Defect Status is true, go back to FAILURE state
            itsState = ALM_FAILURE_S;
        }
        else if (itsPreviousTCount != theTCount)
        {
            // The previous TCount differs from the current TCount,
            // that means Defect Status goes to true and goes back to false.
            // So restart timer because Defect Status was not false for at
            // least "itsRecoveryTime" msec.
            itsTimer.Start();
        }
        else if (itsTimer.IsExpired() || theRecoveryOverride)
        {
            // In RECOVERY for "itsRecoveryTime" msec., go to NORMAL state
            // and returns failure status to false
            itsState = ALM_NORMAL_S;
            itsFailureStatus = false;
        }
        break;
    }

    // Keep previous TCount for next iteration
    itsPreviousTCount = theTCount;

    return itsFailureStatus;
}
