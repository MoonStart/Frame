// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_OmsAutomaticShutdownAction.h"
#include <Blackboard/FC_BbAction.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OmsDefects.h>
#include <Monitoring/MON_OmsStatus.h>
#include "CFG_AppIf.h"
#include "CFG_OmsAutomaticShutdown.h"
#include <ExecutionSupport/FC_TimedProcess.h>
#include <T6100_Dispatcher.h>


const FC_Milliseconds MON_SOAKING_FOR_SHUTDOWN = 1000;

CFG_OmsAutomaticShutdownAction::CFG_OmsAutomaticShutdownAction(CFG_AppIf& theCfgIf,
                                                               MON_AppIf& theMonIf,
                                                               CFG_OmsAutomaticShutdownRegion& theRegion):
    CFG_HwRefreshAction(theCfgIf),
    myUpStreamMonAppIf(theMonIf),
    myAutomaticShutdownRegion(theRegion),
    myTimedProcess(NULL),
    myOmsLossSoaking(MON_SOAKING_FOR_SHUTDOWN,MON_SOAKING_FOR_SHUTDOWN)
{
    GetBbAction()->AddInputRegion(myUpStreamMonAppIf.GetStatusRegion()); // for oms power and actual gain
    GetBbAction()->AddInputRegion(myUpStreamMonAppIf.GetDefectsRegion());
    GetBbAction()->AddOutputRegion(&myAutomaticShutdownRegion);

    myTimedProcess = new FC_TimedProcess(*GetBbAction(), gTimerDispatcher, MON_SOAKING_FOR_SHUTDOWN+1);
}

CFG_OmsAutomaticShutdownAction::~CFG_OmsAutomaticShutdownAction()
{
    GetBbAction()->RemoveInputRegion(myUpStreamMonAppIf.GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(&myAutomaticShutdownRegion);
}


FC_Object* CFG_OmsAutomaticShutdownAction::Process(unsigned theRunReason,
                                                   FC_Object* theInvokerObj,
                                                   FC_Object* theParam)
{
    bool hasChanged = false;
    MON_OmsDefects& aDefects = static_cast<MON_OmsDefects&>((*myUpStreamMonAppIf.GetDefectsRegion())[0]);
    CFG_OmsAutomaticShutdown& aAutomaticShutdown  = myAutomaticShutdownRegion[0];

    // Get OMS-LOS defect and soak it for 1s in order to avoid glitch on control of amps
    bool aLOSState = false;
    uint32 aOmsLosCount = 0;
    aDefects.GetDefectStatus(CT_TEL_OMS_LOS_DEFECT,&aOmsLosCount,&aLOSState);
    bool aOMSLossSoakedState = myOmsLossSoaking.DefectUpdated(aLOSState, aOmsLosCount);

    // Wake up timer process so that we get called back when a soaking is done
    myTimedProcess->WakeUp();

    // Shutdown on OMS-LOS
    hasChanged |= aAutomaticShutdown.SetAmplifierShutdown(aOMSLossSoakedState);

    if (hasChanged)
    {
        myAutomaticShutdownRegion.IncModificationCounter();
    }


    return NULL;
}



