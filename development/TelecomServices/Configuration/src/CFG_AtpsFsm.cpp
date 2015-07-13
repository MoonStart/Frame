// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_AtpsFsm.h"
#include "../CFG_OtsAutomaticTxPwrShutAction.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <ITS/ITS_AppIfBase.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>

const uint32 ATPS_FSM_MAX_ITERATION = 5;
const FC_Milliseconds APTS_FSM_WTR_PERIOD = 10000; // 10s

CFG_AtpsFsm::CFG_AtpsFsm(CFG_OtsAutomaticTxPwrShutAction& anAction):
    myAction(anAction),
    myState(INIT),
    myTimer(*anAction.GetBbAction())
{
}
CFG_AtpsFsm::~CFG_AtpsFsm()
{
}

void CFG_AtpsFsm::Enable()
{
    // read every condition of the system
    ReadConditions();

    // run state machine until state is stable
    State previousState = INIT;
    uint32 i=0;

    do
    {
        // remember previous state
        previousState = myState;

        // Run state machine
        RunFsm();


        if (i++>ATPS_FSM_MAX_ITERATION)
        {
            FC_REPORT_ERROR(FC_RuntimeError, "ATPS state machine unstable");
            break;
        }
    }
    while (previousState != myState);
}

void CFG_AtpsFsm::ReadConditions()
{
    myBdiCondition = GetBdiCondition();
    myLosCondition = GetLosCondition();
}

void CFG_AtpsFsm::RunFsm()
{
    switch(myState)
    {
    case INIT:
    case OFF:
        myState = STANDBY;
        break;
    case STANDBY:
        if (myBdiCondition || myLosCondition)
            myState = SHUTDOWN;
        break;
    case SHUTDOWN:
        if ( !(myBdiCondition || myLosCondition) )
        {
            myTimer.Start(APTS_FSM_WTR_PERIOD);
            myState = WTR;
        }
        break;
    case WTR:
        if (myBdiCondition || myLosCondition)
        {
            myTimer.Stop();
            myState = SHUTDOWN;
        }
        else if (myTimer.IsExpired())
        {
            myTimer.Stop();
            myState = STANDBY;
        }
        break;
    }
}

bool CFG_AtpsFsm::IsShutdownActive()
{
    switch (myState)
    {
    case SHUTDOWN:
    case WTR:
        return true;
    default:
        return false;
    }

}

void CFG_AtpsFsm::Disable()
{
    myState = OFF;
    myTimer.Stop();
}


bool CFG_AtpsFsm::GetBdiCondition()
{
    //--------------------------------------------------------------------
    //check if condition OTS-BDI is detected at the input
    //--------------------------------------------------------------------
    bool aOtsBdiFailure = false;

    //OTS-BDI
    // now check on this side if we have a BDI failure
    ALM_FailureBase& aFailure   = (*myAction.myOtsOHAlmIf.GetFilteredRegionPtr())[0];
    aOtsBdiFailure = aFailure.GetStatus(CT_TelAlarmCondition::ALM_BDI_OTS);

    return aOtsBdiFailure;
}

bool CFG_AtpsFsm::GetLosCondition()
{
    //--------------------------------------------------------------------
    //check if condition OTS-OTS is detected at the input
    //--------------------------------------------------------------------
    bool aOtsLosFailure = false;

    // now check if we have an OTS-LOS failure
    ALM_FailureBase& aFailure   = (*myAction.myOtsAlmIf.GetFilteredRegionPtr())[0];
    aOtsLosFailure = aFailure.GetStatus(CT_TelAlarmCondition::ALM_LOS_OTS);

    return aOtsLosFailure;
}


void CFG_AtpsFsm::Display(FC_Stream& theStream)
{
    theStream << "OTS CATPS FSM State   :" << DISPLAY_CATPS_STATE(myState) << endl;
    if (myState==WTR)
       theStream << "OTS CATPS FSM Timer   :" << myTimer.GetTimeRemaining() << "ms" << endl;
    theStream << "OTS CATPS FSM BDI     :" << DISPLAY_BOOL(myBdiCondition) << endl;
    theStream << "OTS CATPS FSM LOS     :" << DISPLAY_BOOL(myLosCondition) << endl;
}
