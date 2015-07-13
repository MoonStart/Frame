// Copyright(c) Tellabs Transport Group. All rights reserved

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_HOLDOFFTIMER_INCLUDED
#define _INC_CFG_HOLDOFFTIMER_INCLUDED

#include "CFG_AppIf.h"
#include "CFG_Definitions.h"
#include "Blackboard/FC_BbAction.h"
#include <ExecutionSupport/FC_BaseTimer.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include "ExecutionSupport/FC_TimerDispatcher.h"
#include "ExecutionSupport/FC_WakeUpProcessAction.h"
#include "CommonTypes/CT_Telecom.h"
#include <cstring>

class FC_Stream;

class CFG_HoldOffTimer
{
public:
    //Constructor. Requires a callback action.
    CFG_HoldOffTimer(FC_Action& theCallbackAction);

    //Destructor.
    virtual  ~CFG_HoldOffTimer();

    virtual bool ApplyConditionAfterHoldoff(bool   theHoldOffConditionActive,
                                            bool   &theHoldOffTimerIsActive,
                                            uint32 theHoldOffDelay = CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO, 
                                            bool   the2ndHCA = false);

private:

    //The pointer to the action that will be wokem up 
    FC_WakeUpProcessAction* myAutomaticDelayedActionPtr;

	//Process used to holdoff the turning off of a laser (for ALS).
    FC_TimedProcess* myAutomaticTimedProcessPtr;



    // Base Timer that is used to determine when the timed process has fired
    // (needed because this process could be running due to a change to an input region)
    FC_BaseTimer myHoldOffTimer;
    // Indicates that the HoldOff Timer is active (timed process is running)
    bool   myHoldOffTimerIsActive;
    // Saves the HoldOff Delay time to determine when to reset the timed process 
    // and the base timer (want to reset only when necessary because they are expensive operations)
    uint32 myHoldOffDelay;

    // Saves the last Set of Apply Condition (used to determine whether to start
    // a timer or just keep the Condition active)
    bool   myLastReturnedApplyCondition;

    // Saves the last HoldOff Condition (used to increment the HoldOff Counter)
    bool   myLastHoldOffCondition;
    // The number of changes to the HoldOff Condition (used to detect toggles during the HoldOff Delay)
    uint8  myHoldOffCounter;
    // The HoldOff Counter when the HoldOff Timer is started (used to detect toggles during the HoldOff Delay)
    uint8  myHoldOffStartCount;

    // Saves the last 2nd HoldOff Condition (used to increment the HoldOff Counter)
    bool   myLast2ndHoldOffCondition;
    // The number of changes to the 2nd HoldOff Condition (used to detect toggles during the HoldOff Delay)
    uint8  my2ndHoldOffCounter;
    // The 2nd HoldOff Counter when the HoldOff Timer is started (used to detect toggles during the HoldOff Delay)
    uint8  my2ndHoldOffStartCount;
};


#endif // _INC_CFG_HOLDOFFTIMER_INCLUDED 

