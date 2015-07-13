// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_OPTAUTORATELOCKACTION_
#define _CFG_OPTAUTORATELOCKACTION_

#include "CFG_Definitions.h"
#include "CFG_HwRefreshAction.h"
#include "CommonTypes/CT_Telecom.h"
#include "Alarm/ALM_SoakingFailure.h"


// Forward declaration of class.
class FC_PeriodicProcess;
class CFG_AppIf;
class MON_AppIf;
class MON_OtuIf;

//This class is an action that implements the adaptative facility
//(Automatic rate lock down) on port side of OPT layer.
class CFG_OptAutoRateLockAction
: public CFG_HwRefreshAction
{
public:
    //Constructor.
    CFG_OptAutoRateLockAction(CFG_AppIf& theCfgIf,
                              MON_AppIf& thePortOptMonIf,
                              MON_AppIf& theLineOptMonIf,
                              MON_AppIf& theOtuMonIf,
                              MON_AppIf& thePortRsMonIf,
                              MON_AppIf& theLineRsMonIf,
                              CFG_OptAutoRateLockRegion& theAutoRateLockRegion);

    //Virtual destructor of the class.
    virtual ~CFG_OptAutoRateLockAction();

    //Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);


    //Set warm restart indication
#if defined (LINUX) || defined (WIN32)
    inline void SetWarmRestart(){myDoingWarmRestart = true;}
#else
    inline void SetWarmRestart(){myDoingWarmRestart = true;}
#endif


private:

    void UpdateDefects();
    bool IsSignalPresent();
    bool IsRateLocked();
    bool IsRateUnlocked();
    void ResetDefectsCounters();
    void ExecuteLockedTransition();
    void ExecuteNotLockedTransition(bool theFirstTime = false, CT_TEL_daHz theStartRate = 0);
    void StartWarmRestartSoak();
    bool IsWarmRestartSoakComplete();
    bool IsRateRetryRequired();
    CT_TEL_daHz GetRetryRate(bool startRetry = false);


    FC_PeriodicProcess* myPeriodicProcess;
    FC_BaseTimer mySwLockTimer;
    FC_BaseTimer myHwLockTimer;
    FC_BaseTimer myWarmRestartTimer;

    MON_AppIf& myPortOptMonAppIf;
    MON_AppIf& myLineOptMonAppIf;
    MON_AppIf& myPortRsMonAppIf;
    MON_AppIf& myLineRsMonAppIf;
    MON_AppIf& myOtuMonAppIf;

    CFG_OptAutoRateLockRegion& myAutoRateLockRegion;

    //Soaked alarms
    ALM_SoakingFailure myPortRsLofSoaking;
    ALM_SoakingFailure myOtuLofSoaking;

    bool myPortRsLofSoaked;
    bool myOtuLofSoaked;

    uint32 myPortOptLossLightCounter;
    uint32 myPortRsTlabAISCounter;
    uint32 myPortOptLossClockCounter;
    uint32 myLineOptLossLightCounter;
    uint32 myLineRsTlabAISCounter;
    uint32 myLineOptLossClockCounter;

    uint32 myOtuLofCounter;
    uint32 myPortRsLofCounter;

    bool myOutputRegionChanged;
    bool myHwLockedState;
    bool myDoingWarmRestart;

    uint32 myLockAttemptCount;

};


#endif /* _CFG_OPTAUTORATELOCKACTION_ */
