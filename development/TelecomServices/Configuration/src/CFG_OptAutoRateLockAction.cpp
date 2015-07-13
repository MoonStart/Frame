// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_OptAutoRateLockAction.h"
#include "../CFG_AppIf.h"
#include "../CFG_Opt.h"
#include "../CFG_OptAutoRateLock.h"
#include <Monitoring/MON_OptDefects.h>
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_AppIf.h>
#include <Blackboard/FC_BbAction.h>
#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <T6100_Dispatcher.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <TsPii/TSPII_RsIf.h>
#include <Monitoring/MON_OtuDefects.h>


const uint16 CFG_AUTO_LOCK_POLLING     =  500; //Duration between polling of defects (in ms)
const uint16 CFG_AUTO_LOCK_HW_TIMEOUT  = 1500; //Duration for the HW to lock on a new rate
const uint16 CFG_AUTO_LOCK_SW_TIMEOUT  = 4000; //Duration to wait in SW to lock on a new rate (in ms)
const uint16 CFG_AUTO_LOCK_SOAKING     = 1000; //Soaking and clearing duration for defects (in ms)
const uint16 CFG_AUTO_WARM_RESTART     = 1500; //Duration for LOF to soak in a warm restart scenario (in ms)
const uint8  CFG_AUTO_MAX_RETRY_COUNT  = 4;    //Maximum number of retries for lock



CFG_OptAutoRateLockAction::CFG_OptAutoRateLockAction(CFG_AppIf& theCfgIf,
                                                     MON_AppIf& thePortOptMonIf,
                                                     MON_AppIf& theLineOptMonIf,
                                                     MON_AppIf& theOtuMonIf,
                                                     MON_AppIf& thePortRsMonIf,
                                                     MON_AppIf& theLineRsMonIf,
                                                     CFG_OptAutoRateLockRegion& theAutoRateLockRegion):
    CFG_HwRefreshAction(theCfgIf),
    myPortOptMonAppIf(thePortOptMonIf),
    myLineOptMonAppIf(theLineOptMonIf),
    myPortRsMonAppIf(thePortRsMonIf),
    myLineRsMonAppIf(theLineRsMonIf),
    myAutoRateLockRegion(theAutoRateLockRegion),
    myPeriodicProcess(NULL),
    myPortRsLofSoaking(CFG_AUTO_LOCK_SOAKING,CFG_AUTO_LOCK_SOAKING),
    mySwLockTimer(CFG_AUTO_LOCK_SW_TIMEOUT),
    myHwLockTimer(CFG_AUTO_LOCK_HW_TIMEOUT),
	myWarmRestartTimer(CFG_AUTO_WARM_RESTART),
    myPortRsLofSoaked(false),
    myPortOptLossLightCounter(0),
    myPortRsTlabAISCounter(0),
    myPortOptLossClockCounter(0),
	myLineOptLossLightCounter(0),
	myLineRsTlabAISCounter(0),
    myLineOptLossClockCounter(0),
    myPortRsLofCounter(0),
    myOutputRegionChanged(false),
    myHwLockedState(false),
    myOtuLofSoaking( CFG_AUTO_LOCK_SOAKING,CFG_AUTO_LOCK_SOAKING),
    myOtuLofSoaked(false),
    myOtuLofCounter(0),
    myOtuMonAppIf(theOtuMonIf),
	myDoingWarmRestart(false),
	myLockAttemptCount(0)
{
	GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion(),false,false);
	GetBbAction()->AddInputRegion(myLineOptMonAppIf.GetDefectsRegion(),false,false);
	GetBbAction()->AddInputRegion(myPortOptMonAppIf.GetDefectsRegion(),false,false);
	GetBbAction()->AddInputRegion(myOtuMonAppIf.GetDefectsRegion(),false,false);
	GetBbAction()->AddInputRegion(myPortRsMonAppIf.GetDefectsRegion(),false,false);
	GetBbAction()->AddInputRegion(myLineRsMonAppIf.GetDefectsRegion(),false,false);
    GetBbAction()->AddOutputRegion(&myAutoRateLockRegion,false,false);

    myPeriodicProcess = new FC_PeriodicProcess(*GetBbAction(), gTimerDispatcher, CFG_AUTO_LOCK_POLLING);
    myPeriodicProcess->WakeUp();
}

CFG_OptAutoRateLockAction::~CFG_OptAutoRateLockAction()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
	GetBbAction()->RemoveInputRegion(myPortOptMonAppIf.GetDefectsRegion());
	GetBbAction()->RemoveInputRegion(myLineOptMonAppIf.GetDefectsRegion());
	GetBbAction()->RemoveInputRegion(myOtuMonAppIf.GetDefectsRegion());
	GetBbAction()->RemoveInputRegion(myPortRsMonAppIf.GetDefectsRegion());
	GetBbAction()->RemoveInputRegion(myLineRsMonAppIf.GetDefectsRegion());
	GetBbAction()->RemoveOutputRegion(&myAutoRateLockRegion);

    if (myPeriodicProcess)	{delete myPeriodicProcess;}
}


FC_Object* CFG_OptAutoRateLockAction::Process(unsigned theRunReason,
                                             FC_Object* theInvokerObj,
                                             FC_Object* theParam)
{
    //Verify region validity
    if(!GetCfgIf().GetCfgRegion()->IsValid() || 
       !myPortOptMonAppIf.GetDefectsRegion()->IsValid() ||
       !myLineOptMonAppIf.GetDefectsRegion()->IsValid() ||
       !myOtuMonAppIf.GetDefectsRegion()->IsValid() ||
       !myPortRsMonAppIf.GetDefectsRegion()->IsValid() ||
       !myLineRsMonAppIf.GetDefectsRegion()->IsValid())
    {
        myAutoRateLockRegion.SetForceInvalidFlag(true);
        return NULL;
    }
    else
    {
        myAutoRateLockRegion.SetForceInvalidFlag(false);
    }

    CFG_Opt& aConfig = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]); 
    CFG_OptAutoRateLock& aAutoRateLock = myAutoRateLockRegion[0];

    myOutputRegionChanged = false; //Reset the flag that indicates if the output region changed

	bool doingWarmRestart = myDoingWarmRestart;
	//Reset my warm restart flag to prevent
	//warm restart special processing from running
	//starting from the next execution of the action.
	myDoingWarmRestart = false;

	

    //Soak the defects
    UpdateDefects();

    //Retrieve the last state
    CFG_RateLockState aNewRateLockState = aAutoRateLock.GetLockState();   

    switch (aAutoRateLock.GetLockState())
    {
        case CFG_RATE_DISABLED:
        {   
            //Check if the Auto Rate Lock was enabled and the map is not empty
            if(aConfig.GetAutoRateLockDown())
            {
				
                //Check if the map is empty
                if(!aConfig.GetClockRateMap().empty())
				{
					// In warm restart scenario,
					// wait 1.5 secs to give the LOF
					// condition time to soak.
					if (doingWarmRestart)
					{
						StartWarmRestartSoak();
						aNewRateLockState = CFG_RATE_WARM_RESTART;
					}
					else
					{
                        if(IsSignalPresent())
						{
                            ExecuteNotLockedTransition(true);
                            aNewRateLockState = CFG_RATE_NOT_LOCKED;
						}
                        else
						{
                            aNewRateLockState = CFG_RATE_NO_SIGNAL;
						}
					}
				}
                else
				{
                    FC_REPORT_ERROR(FC_RuntimeError, "Error: Empty map, cannot enable Auto Rate Lock Down State machine");
				}
            }
        }
        break;
        case CFG_RATE_WARM_RESTART:
		{
			//If the warm restart soak is complete
			//either transition to the "locked" state or
			//"not locked" state depending on the rate lock
			//status.
			if (IsWarmRestartSoakComplete())
			{
				if (IsRateLocked())
				{
					ExecuteLockedTransition();
					aNewRateLockState = CFG_RATE_LOCKED;
				}
				else
				{
					aNewRateLockState = CFG_RATE_NOT_LOCKED;
				}
			}
		}
		break;
        case CFG_RATE_NO_SIGNAL:
        {
            //Check if the Auto Rate Lock is enabled and the map is not empty
            if(aConfig.GetAutoRateLockDown() && !aConfig.GetClockRateMap().empty())
            {
                if(IsSignalPresent())
                {
                    ExecuteNotLockedTransition(true);
                    aNewRateLockState = CFG_RATE_NOT_LOCKED;
                }
            }
            else
            {
                aNewRateLockState = CFG_RATE_DISABLED;
            }
        }
        break;
        case CFG_RATE_NOT_LOCKED:
        {
            //Check if the Auto Rate Lock is enabled and the map is not empty
            if(aConfig.GetAutoRateLockDown() && !aConfig.GetClockRateMap().empty())
            {
                //Check if there is signal to lock to.
                if(IsSignalPresent())
                {
					//Check if the Hw has finished locking
                    if(myHwLockTimer.IsExpired())
					{
                        myHwLockedState = true;
                        ResetDefectsCounters();
					}
                    if(myHwLockedState)
					{
                        //Check the lock state
                        if(IsRateLocked())
						{
						    bool checkSWTimer = true;

							//Check whether relocking is neccesary.
							if (IsRateRetryRequired())
							{
								checkSWTimer = false;
								CT_TEL_daHz retryRate = GetRetryRate(true); //true = starting workaround
						        ExecuteNotLockedTransition(false, retryRate);
                                aNewRateLockState = CFG_RATE_NOT_LOCKED;
							}
							if (checkSWTimer)
							{
                                if(mySwLockTimer.IsExpired())
								{
                                    ExecuteLockedTransition();
                                    aNewRateLockState = CFG_RATE_LOCKED;
								}
							}
						}
                        else
						{
						    CT_TEL_daHz retryRate = GetRetryRate();
							if (retryRate != 0)
							{
								ExecuteNotLockedTransition(false,retryRate);
							}
							else
							{
                                ExecuteNotLockedTransition();
							}

                            aNewRateLockState = CFG_RATE_NOT_LOCKED;
						}
					}
                }
                else
                {
                    aNewRateLockState = CFG_RATE_NO_SIGNAL;
                }
            }
            else
            {
                aNewRateLockState = CFG_RATE_DISABLED;
            }
        }
        break;
        case CFG_RATE_LOCKED:
        {
            //Check if the Auto Rate Lock is enabled and if the map is not empty
            if(aConfig.GetAutoRateLockDown() && !aConfig.GetClockRateMap().empty())
            {
                //Check if there is still a signal 
                if(IsSignalPresent())
                {
                    //Check the lock state
                    if(IsRateUnlocked())
                    {
                        ExecuteNotLockedTransition(true);
                        aNewRateLockState = CFG_RATE_NOT_LOCKED;
                    }
                }
                else
                {
                    aNewRateLockState = CFG_RATE_NO_SIGNAL;
                }
            }
            else
            {
                aNewRateLockState = CFG_RATE_DISABLED;
            }
        }
        break;
        default:
            FC_THROW_ERROR(FC_RuntimeError,"Error: Unexpected state in CFG_AutoRateLockAction");
    }

	//Reset retry counter if we change state from RATE_NOT_LOCKED
	//to another state.
	if (aAutoRateLock.GetLockState() == CFG_RATE_NOT_LOCKED &&
        aNewRateLockState != CFG_RATE_NOT_LOCKED)
	{
		myLockAttemptCount = 0;
	}

    //Save the new states
    myOutputRegionChanged |= aAutoRateLock.SetLockState(aNewRateLockState);

    //Notify and Increment counter only on region change
    if(myOutputRegionChanged)
    {
        myAutoRateLockRegion.IncModificationCounter();
        myAutoRateLockRegion.UpdateNotify();
    }

    return NULL;
}

void CFG_OptAutoRateLockAction::UpdateDefects()
{
    MON_RsDefects&  aPortRsDefects = static_cast<MON_RsDefects&>((*myPortRsMonAppIf.GetDefectsRegion())[0]); 
	MON_OtuDefects& aOtuDefects    = static_cast<MON_OtuDefects&>((*myOtuMonAppIf.GetDefectsRegion())[0]); 

    uint32 aCount; // Variable to store counters     

    bool aDefectStatus = false;

    // Then check if there is defects that indicates that we are not locked
    aPortRsDefects.GetDefectStatus(CT_TEL_RS_LOF_DEFECT,&aCount,&aDefectStatus);
    myPortRsLofSoaked = myPortRsLofSoaking.DefectUpdated(aDefectStatus,aCount) ;

    // Then check if there is defects that indicates that we are not locked
    aOtuDefects.GetDefectStatus(CT_TEL_OTU_LOF_DEFECT,&aCount,&aDefectStatus);
    myOtuLofSoaked = myOtuLofSoaking.DefectUpdated(aDefectStatus,aCount) ;    
}

bool CFG_OptAutoRateLockAction::IsSignalPresent()
{
    CFG_Opt& aPortOptConfig = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]); 

    
    MON_OptDefects& aPortOptDefects = static_cast<MON_OptDefects&>((*myPortOptMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects&  aPortRsDefects  = static_cast<MON_RsDefects&>((*myPortRsMonAppIf.GetDefectsRegion())[0]); 
    uint32 aCount; // Variable to store counters     
    bool aPortOptLos = false;
    bool aPortRsTlabAIS = false;

    bool aTerminalLoopbackActive = aPortOptConfig.GetTerminalLoopBackEnable();
    aCount = 0; // Variable to store counters     
    aPortOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aCount,&aPortOptLos);
    aCount = 0; // Variable to store counters     
    aPortRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aCount,&aPortRsTlabAIS);

    
    MON_OptDefects& aLineOptDefects = static_cast<MON_OptDefects&>((*myLineOptMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects&  aLineRsDefects  = static_cast<MON_RsDefects&>((*myLineRsMonAppIf.GetDefectsRegion())[0]); 
    bool aLineOptLos = false;
    bool aLineRsTlabAIS = false;
                
    aCount = 0; // Variable to store counters     
    aLineOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aCount,&aLineOptLos);
    aCount = 0; // Variable to store counters     
    aLineRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aCount,&aLineRsTlabAIS);

	//If either side has a valid signal, start the rate lock process.
    // On line side, there should be no terminal loopback.
    return ((!(aPortOptLos || aPortRsTlabAIS || aTerminalLoopbackActive)) || 
            (!(aLineOptLos || aLineRsTlabAIS )));
    
}

void CFG_OptAutoRateLockAction::ResetDefectsCounters()
{
    MON_OptDefects& aPortOptDefects = static_cast<MON_OptDefects&>((*myPortOptMonAppIf.GetDefectsRegion())[0]); 
    MON_OptDefects& aLineOptDefects = static_cast<MON_OptDefects&>((*myLineOptMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects&  aPortRsDefects  = static_cast<MON_RsDefects&>((*myPortRsMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects&  aLineRsDefects  = static_cast<MON_RsDefects&>((*myLineRsMonAppIf.GetDefectsRegion())[0]); 
    MON_OtuDefects& aOtuDefects     = static_cast<MON_OtuDefects&>((*myOtuMonAppIf.GetDefectsRegion())[0]); 

    uint32 aOptLossLightCounter = 0;
    uint32 aRsTlabAISCounter = 0;
    uint32 aOptLossClockCounter = 0;
    uint32 aRsLofCounter = 0;
    uint32 aOtuLofCounter = 0;

    bool aDefects = false;

	//reset port side
    aPortOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aOptLossLightCounter,&aDefects);
    myPortOptLossLightCounter = aOptLossLightCounter;
    aPortRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aRsTlabAISCounter,&aDefects);
    myPortRsTlabAISCounter = aRsTlabAISCounter;
	aPortOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_CLK_DEFECT,&aOptLossClockCounter,&aDefects);
    myPortOptLossClockCounter = aOptLossClockCounter;
	aPortRsDefects.GetDefectStatus(CT_TEL_RS_LOF_DEFECT,&aRsLofCounter,&aDefects);
    myPortRsLofCounter = aRsLofCounter;

	//reset line side
	aLineOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aOptLossLightCounter,&aDefects);
    myLineOptLossLightCounter = aOptLossLightCounter;
    aLineRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aRsTlabAISCounter,&aDefects);
    myLineRsTlabAISCounter = aRsTlabAISCounter;
    aLineOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_CLK_DEFECT,&aOptLossClockCounter,&aDefects);
    myLineOptLossClockCounter = aOptLossClockCounter;
    aOtuDefects.GetDefectStatus(CT_TEL_OTU_LOF_DEFECT,&aOtuLofCounter,&aDefects);
    myOtuLofCounter = aOtuLofCounter;
}

bool CFG_OptAutoRateLockAction::IsRateLocked()
{
    MON_OptDefects& aPortOptDefects = static_cast<MON_OptDefects&>((*myPortOptMonAppIf.GetDefectsRegion())[0]); 
    MON_OptDefects& aLineOptDefects = static_cast<MON_OptDefects&>((*myLineOptMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects& aPortRsDefects = static_cast<MON_RsDefects&>((*myPortRsMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects& aLineRsDefects = static_cast<MON_RsDefects&>((*myLineRsMonAppIf.GetDefectsRegion())[0]); 
    MON_OtuDefects& aOtuDefects = static_cast<MON_OtuDefects&>((*myOtuMonAppIf.GetDefectsRegion())[0]); 
    CFG_Opt& aConfig = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]); 
    CFG_OptAutoRateLock& aAutoRateLock = myAutoRateLockRegion[0];

    bool aOptLossLight = false;
    bool aRsTlabAIS = false;
    bool aOptLossClock = false;
    bool aRsLof = false;
    bool aOtuLof = false;

    uint32 aOptLossLightCounter = 0;
    uint32 aRsTlabAISCounter = 0;
    uint32 aOptLossClockCounter = 0;
    uint32 aRsLofCounter = 0;
    uint32 aOtuLofCounter = 0;

    bool aRateLockedOnPort = false;
    bool aRateLockedOnLine = false;
    
    //First, check if the rate is still in the map
    const CFG_ClockRateMap& aClockRateMap = aConfig.GetClockRateMap();
    CFG_ClockRateMap::const_iterator aIter = aClockRateMap.find(aAutoRateLock.GetSignalRate());

    if(aIter != aClockRateMap.end() &&
      (*aIter).second == aAutoRateLock.GetSignalType())
    {
        // Then check if there is defects that indicates that we are not locked
        
        aPortOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aOptLossLightCounter,&aOptLossLight);
        aPortRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aRsTlabAISCounter,&aRsTlabAIS);
        aPortOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_CLK_DEFECT,&aOptLossClockCounter,&aOptLossClock);
        aPortRsDefects.GetDefectStatus(CT_TEL_RS_LOF_DEFECT,&aRsLofCounter,&aRsLof);
        if((myPortOptLossLightCounter == aOptLossLightCounter) && (myPortOptLossClockCounter == aOptLossClockCounter) && 
           (myPortRsTlabAISCounter == aRsTlabAISCounter)       && (myPortRsLofCounter == aRsLofCounter) &&
           !aOptLossLight && !aOptLossClock && !aRsTlabAIS && !aRsLof)
        {
            aRateLockedOnPort = true;
        }
        
        aLineOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aOptLossLightCounter,&aOptLossLight);
        aLineRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aRsTlabAISCounter,&aRsTlabAIS);
        aLineOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_CLK_DEFECT,&aOptLossClockCounter,&aOptLossClock);
        aOtuDefects.GetDefectStatus(CT_TEL_OTU_LOF_DEFECT,&aOtuLofCounter,&aOtuLof);
        if((myLineOptLossLightCounter == aOptLossLightCounter) && (myLineOptLossClockCounter == aOptLossClockCounter) && 
           (myLineRsTlabAISCounter == aRsTlabAISCounter)       && (myOtuLofCounter == aOtuLofCounter) &&
           !aOptLossLight && !aOptLossClock && !aRsTlabAIS && !aOtuLof)
        {
            aRateLockedOnLine = true;
        }
        
    }

    return (aRateLockedOnPort || aRateLockedOnLine);
}

bool CFG_OptAutoRateLockAction::IsRateUnlocked()
{
    MON_OptDefects& aPortOptDefects = static_cast<MON_OptDefects&>((*myPortOptMonAppIf.GetDefectsRegion())[0]); 
    MON_OptDefects& aLineOptDefects = static_cast<MON_OptDefects&>((*myLineOptMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects& aPortRsDefects = static_cast<MON_RsDefects&>((*myPortRsMonAppIf.GetDefectsRegion())[0]); 
    MON_RsDefects& aLineRsDefects = static_cast<MON_RsDefects&>((*myLineRsMonAppIf.GetDefectsRegion())[0]); 
    MON_OtuDefects& aOtuDefects = static_cast<MON_OtuDefects&>((*myOtuMonAppIf.GetDefectsRegion())[0]); 
    CFG_Opt& aConfig = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]); 
    CFG_OptAutoRateLock& aAutoRateLock = myAutoRateLockRegion[0];


    bool aOptLossLight = false;
    bool aRsTlabAIS = false;
    bool aOptLossClock = false;

    uint32 aOptLossLightCounter = 0;
    uint32 aRsTlabAISCounter = 0;
    uint32 aOptLossClockCounter = 0;

    bool aRateUnlocked = false;
	bool aRateUnlockedPort = false;
	bool aRateUnlockedLine = false;
    
    //First, check if the rate is still in the map
    const CFG_ClockRateMap& aClockRateMap = aConfig.GetClockRateMap();
    CFG_ClockRateMap::const_iterator aIter = aClockRateMap.find(aAutoRateLock.GetSignalRate());

    if(aIter != aClockRateMap.end() && 
      (*aIter).second == aAutoRateLock.GetSignalType())
    {
        
        // Then check if there is defects that indicates that we are not locked
        aPortOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aOptLossLightCounter,&aOptLossLight);
        aPortRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aRsTlabAISCounter,&aRsTlabAIS);
        aPortOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_CLK_DEFECT,&aOptLossClockCounter,&aOptLossClock);

        if((myPortOptLossLightCounter != aOptLossLightCounter) || (myPortOptLossClockCounter != aOptLossClockCounter) ||
           (myPortRsTlabAISCounter != aRsTlabAISCounter)       ||
           aOptLossLight || aOptLossClock || aRsTlabAIS || myPortRsLofSoaked)
        {
            aRateUnlockedPort = true;
        }
        
        // Then check if there is defects that indicates that we are not locked
        aLineOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT,&aOptLossLightCounter,&aOptLossLight);
        aLineRsDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,&aRsTlabAISCounter,&aRsTlabAIS);
        aLineOptDefects.GetDefectStatus(CT_TEL_OPT_LOSS_CLK_DEFECT,&aOptLossClockCounter,&aOptLossClock);

        if((myLineOptLossLightCounter != aOptLossLightCounter) || (myLineOptLossClockCounter != aOptLossClockCounter) ||
           (myLineRsTlabAISCounter != aRsTlabAISCounter)       ||
           aOptLossLight || aOptLossClock || aRsTlabAIS || myOtuLofSoaked)
        {
            aRateUnlockedLine = true;
        }
        

		//rate is considered unlocked only if both line and port
		//are unlocked
		aRateUnlocked = aRateUnlockedPort && aRateUnlockedLine;
    }
    else
    {
        aRateUnlocked = true;
    }

    return aRateUnlocked;
}


void CFG_OptAutoRateLockAction::ExecuteLockedTransition()
{
    //Reset the defect counters
    ResetDefectsCounters();
	
}

void CFG_OptAutoRateLockAction::ExecuteNotLockedTransition(bool theResetMapIter, CT_TEL_daHz theStartRate)
{
    CFG_Opt& aConfig = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]); 
    CFG_OptAutoRateLock& aAutoRateLock = myAutoRateLockRegion[0];
    const CFG_ClockRateMap& aClockRateMap = aConfig.GetClockRateMap();
#ifdef WIN32    
    CFG_ClockRateMap::const_iterator aIter;
#else
  #ifdef WRLINUX
    CFG_ClockRateMap::const_iterator aIter;
  #else
    CFG_ClockRateMap::const_iterator aIter=NULL;
  #endif
#endif
    //The HW is not locked
    myHwLockedState = false;

    // Check if we have to take the first element in the map
    if(theResetMapIter)
    {
        aIter = aClockRateMap.begin();    
    }
	else if (theStartRate != 0)
	{
		//check if we have to start at a specific rate
       aIter = aClockRateMap.find(theStartRate);

	   //If the specified rate is not in the map
	   //take the first element in the map
	   if(aIter == aClockRateMap.end())
       {
           aIter = aClockRateMap.begin();
       }
	}
    else
    {  
        // First, try to find the last tried rate in the map
        aIter = aClockRateMap.find(aAutoRateLock.GetSignalRate());
        if(aIter != aClockRateMap.end())
        {
            // Second, increment iterator to get the next item in the map. (Handle wrap aroud)
            aIter++;
            if(aIter == aClockRateMap.end())
            {
                aIter = aClockRateMap.begin();
            }
        }
        else
        {
            aIter = aClockRateMap.begin();
        }
    }    

    //Set the new rate and type of signal that we try to lock at
    myOutputRegionChanged |= aAutoRateLock.SetSignalRate((*aIter).first);
    myOutputRegionChanged |= aAutoRateLock.SetSignalType((*aIter).second);

    //Start the timers
    mySwLockTimer.Start();
    myHwLockTimer.Start();
}


void CFG_OptAutoRateLockAction::StartWarmRestartSoak()
{
	//Get current bit rate and signal type on the port side from PII
	//and save in autolock region.
	CFG_OptAutoRateLock& aAutoRateLock = myAutoRateLockRegion[0];
	TSPII_OpticalRegion* theOptPiiRegion = TSPII_SubApplication::GetInstance()->GetOptical(TSPII_PORT_SIDE, GetCfgIf().GetSlotId());
	TSPII_RsRegion* theRsPiiRegion = TSPII_SubApplication::GetInstance()->GetRs(TSPII_PORT_SIDE, GetCfgIf().GetSlotId());
	TSPII_RsIf& aRsPII        = (*theRsPiiRegion)[0];
	TSPII_OpticalIf& aOptPII        = (*theOptPiiRegion)[0];
	aAutoRateLock.SetSignalRate(aOptPII.GetBitRate());
    aAutoRateLock.SetSignalType(aRsPII.GetSignalType());

	//Start warm restart soak timer
	myWarmRestartTimer.Start();
}

bool CFG_OptAutoRateLockAction::IsWarmRestartSoakComplete()
{
	return myWarmRestartTimer.IsExpired();

}

bool CFG_OptAutoRateLockAction::IsRateRetryRequired()
{
    CFG_Opt& aConfig = static_cast<CFG_Opt&>((*GetCfgIf().GetCfgRegion())[0]); 
    CFG_OptAutoRateLock& aAutoRateLock = myAutoRateLockRegion[0];
    const CFG_ClockRateMap& aClockRateMap = aConfig.GetClockRateMap();
#ifdef WIN32
    CFG_ClockRateMap::const_iterator aIter;
#else
  #ifdef WRLINUX
    CFG_ClockRateMap::const_iterator aIter;
  #else
    CFG_ClockRateMap::const_iterator aIter=NULL;
  #endif
#endif    

	//If GbE rate is in the ratemap and we have locked on 100BFX
	//rate, then try again to lock. This is done to get around
	//a hardware limitation on the MRTM that causes false lock
	//of GbE on 100BFX.
	if (aAutoRateLock.GetSignalRate() == BIT_RATE_100BFX &&
		myLockAttemptCount == 0)
	{
		aIter = aClockRateMap.find(BIT_RATE_GBE);
		if (aIter != aClockRateMap.end())
			return true;
	}
	return false;
}

CT_TEL_daHz CFG_OptAutoRateLockAction::GetRetryRate(bool startRetry)
{
	CT_TEL_daHz returnRate = 0;
	//Check whether retrying the alternate rate is necessary or go back to the original 
	//rate and retry it again

	if (startRetry)
	{
		//Find first non Gbe rate after Gbe and try that rate
		//DEBUG
		//fc_cout << "Trying non Gbe " <<  myLockAttemptCount  << endl;
        returnRate = BIT_RATE_OC12;
		
		myLockAttemptCount++;
		return returnRate;
	}
	if (myLockAttemptCount > 0 && myLockAttemptCount <= CFG_AUTO_MAX_RETRY_COUNT)
	{
	    					
		if (myLockAttemptCount == 1 || myLockAttemptCount == 3)
		{
			//DEBUG
		    //fc_cout << "Trying Gbe " <<  myLockAttemptCount  << endl;
		    returnRate =  BIT_RATE_GBE;
		}
		else if (myLockAttemptCount == 2)
		{
		    //Find first SONET rate after Gbe and try that rate
		    //DEBUG
		    //fc_cout << "Trying OC12 " <<  myLockAttemptCount  << endl;
		    returnRate = BIT_RATE_OC12;
		}
		else //Give up
		{
			//DEBUG
		    //fc_cout << "Giving up on Gbe " <<  myLockAttemptCount  << endl;
	        returnRate =  BIT_RATE_100BFX;
		}
		//Set the lock attempt count appropriately	
		myLockAttemptCount++;	
	}

	return returnRate;
}


