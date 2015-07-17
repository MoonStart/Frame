/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Anoop Mathew
 DESCRIPTION:
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii_Imp/TSPII_LxameUpgrSwitchCntrlAction.h"
#include "TsPii/TSPII_BaseIf.h"
#include <TsPii/TSPII_PipeIf.h>
#include "ErrorService/FC_Error.h"
#include "Blackboard/FC_BbAction.h"
#include "ExecutionSupport/FC_TimedProcess.h"
#include "T6100_MainAppIf.h"
#include "T6100_ShelfIf.h"
#include "T6100_SlotIf.h"
#include "T6100_CardIf.h"
#include "T6100_TelecomIf.h"
#include "SCFG/SCFG_AppIf.h"
#include "TsPii_Imp/TSPII_Spm8560SubApplication.h"
#include "TsPii_Imp/TSPII_OscMapperFpgaCtrl.h"
#include "T6100_Dispatcher.h"
#include <CsPii/CSPII_CardIF.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Oms.h>

#define SWITCH_ARM_TIMEOUT_VAL 120 //120 seconds
#define LXAME_SWITCH_PERIOD 30 * 1000 
#define MAX_ARM_ITERATION 6
#define MAX_AMPS_PER_SHELF 4
const FC_Milliseconds MAX_LOAME_SOAK_TIME = 4 * 1000; //2 secs per avanex, so doubling that value just in case
#define LOAME_CONFIG_POLL_PERIOD 10 * 1000 

TSPII_OlaUpgrLoameFsm::TSPII_OlaUpgrLoameFsm(CT_SlotId theSlotId):
    mySlotId (theSlotId),
    myCurrentState(OLA_UPGRADE_IDLE),
    myLoameConfigInProgress(false),
    myLoameIsConfigured(false),
	myLoameConfigRequested(false)
{
    myTimedProcess = new FC_TimedProcess(*this, gTimerDispatcher, LOAME_CONFIG_POLL_PERIOD);
}

TSPII_OlaUpgrLoameFsm::~TSPII_OlaUpgrLoameFsm()
{
	myTimedProcess->SuspendImmediate();
	delete myTimedProcess;
}

	////////////////////////////////////////////////////////////////////////////////
void TSPII_OlaUpgrLoameFsm::Run(FC_Object* theObject)
{
    // Run() function evaluates the FSM.
    //
    // Note: Run() is called from:
    //              TSPII_LxameUpgrSwitchCntrlAction below


    TSPII_OlaUpgrLoameFsmState nextState;

    // Pilot tone state machine
    switch (myCurrentState)
    {
    case OLA_UPGRADE_IDLE:
        nextState = RunIdle();
        break;
    case DISABLE_AUTO_LOS:
        nextState = RunAutoLosDisable();
        break;
    case AUTO_LOS_DISABLE_SOAK:
        nextState = RunAutoLosSoak();
        break;
    case CHANGE_GAIN:
        nextState = RunChangeGain();
        break;
    case COMPLETED:
        nextState = RunCompleted();
        break;
    default:
        FC_THROW_ERROR(FC_ValueOutOfRangeError, "Invalid controller state"); 
    }

    // Execute state transition if required.
    if (nextState != myCurrentState)
    {
        switch (nextState)
        {
        case OLA_UPGRADE_IDLE:
            EntryIdle(myCurrentState);
            break;
        case DISABLE_AUTO_LOS:
            EntryAutoLosDisable(myCurrentState);
            break;
        case AUTO_LOS_DISABLE_SOAK:
            EntryAutoLosSoak(myCurrentState);
            break;
        case CHANGE_GAIN:
            EntryChangeGain(myCurrentState);
            break;
        case COMPLETED:
            EntryCompleted(myCurrentState);
            break;
        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "Invalid controller state");
        }
        myCurrentState = nextState;
    }
}

void TSPII_OlaUpgrLoameFsm::EntryIdle(TSPII_OlaUpgrLoameFsmState thePreviousState)
{
	//
}
void TSPII_OlaUpgrLoameFsm::EntryAutoLosDisable(TSPII_OlaUpgrLoameFsmState thePreviousState)
{
	myLoameConfigInProgress = true;
	myLoameIsConfigured = false;
	//Disable the auto los feature on the LOAME
	TSPII_CntrlLxameOsaCtrlAction* theOutputAmpAction = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(mySlotId);
	fc_cout << "Disabling LOS for slot " << (uint32)mySlotId << endl;
    theOutputAmpAction->SetAutoLOSEnable(false);
	myTimedProcess->WakeUp();
}
void TSPII_OlaUpgrLoameFsm::EntryAutoLosSoak(TSPII_OlaUpgrLoameFsmState thePreviousState)
{
	myStateStopwatch.Start();
	myTimedProcess->WakeUp();
}
void TSPII_OlaUpgrLoameFsm::EntryChangeGain(TSPII_OlaUpgrLoameFsmState thePreviousState)
{
	//Change the gain
	CT_ShelfId theCurrentShelfId = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();
	TSPII_PipeRegion* aPipeRegion = TSPII_SubApplication::GetInstance()->GetPipe(TSPII_DONT_CARE, mySlotId);
	TSPII_PipeIf& aPipePii = (*aPipeRegion)[0];
	T6100_CardIf* theCard = (T6100_MainAppIf::Instance().GetShelfPtr(theCurrentShelfId)->GetSlotPtr(mySlotId)->GetCardPtr(OAM_FAM));
	if (theCard)
	{
		//Check for validity of OMS region before using data within it to make decisions
		if (theCard->GetOmsIf().GetCfgPortApp().GetCfgRegion()->IsValid())
		{
	        CFG_Oms& aOmsConfig  = static_cast<CFG_Oms&>((*theCard->GetOmsIf().GetCfgPortApp().GetCfgRegion())[0]);
	 
            CT_TEL_mBm configuredGain = aOmsConfig.GetGain();
	        CT_TEL_mBm configuredGainInHw = aPipePii.GetGain();
	        //Toggle gain by 0.1dB to active VOA on amplifier
		    if (!aOmsConfig.GetPowerControlEnable())
			{
	            if (configuredGain != configuredGainInHw)
		             aPipePii.SetGain(configuredGain);
	            else if (configuredGainInHw >= 2100)
                    aPipePii.SetGain(configuredGainInHw-10);
	            else if (configuredGainInHw <= 1700)
                    aPipePii.SetGain(configuredGainInHw+10);
	            else
                    aPipePii.SetGain(configuredGainInHw+10);
			}
		}
		else
		{
			//Data not valid. Assume power mgmt is in automatic mode.
			fc_cout << "TSPII_OlaUpgrLoameFsm::OMS CFG region not valid for slot " << mySlotId << endl;
		}
	}

	//Start stopwatch
	myTimedProcess->WakeUp();
	myStateStopwatch.Start();
}
void TSPII_OlaUpgrLoameFsm::EntryCompleted(TSPII_OlaUpgrLoameFsmState thePreviousState)
{
	myLoameConfigInProgress = false;
	myLoameIsConfigured = true;
	myLoameConfigRequested = false;
}

TSPII_OlaUpgrLoameFsm::TSPII_OlaUpgrLoameFsmState TSPII_OlaUpgrLoameFsm::RunIdle()
{
	//Check for a config request and transition appropriately
	if (myLoameConfigRequested)
	{
		return DISABLE_AUTO_LOS;
	}

	return OLA_UPGRADE_IDLE;
}
TSPII_OlaUpgrLoameFsm::TSPII_OlaUpgrLoameFsmState TSPII_OlaUpgrLoameFsm::RunAutoLosDisable()
{
	//Check whether the hardware has taken the auto los configuration
	//If it has then start the soak timer
	bool stage1State = true; //Assume auto LOS is enabled
    bool stage2State = true; //Assume auto LOS is enabled
	TSPII_CntrlLxameOsaCtrlAction* theOutputAmpAction = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(mySlotId);
	theOutputAmpAction->GetAutoLOSEnableState(stage1State, stage2State);

	if (!stage1State && !stage2State) /*auto los config has been accepted by hardware */
	{
		return AUTO_LOS_DISABLE_SOAK;
	}

	myTimedProcess->WakeUp();
	return DISABLE_AUTO_LOS;

}
TSPII_OlaUpgrLoameFsm::TSPII_OlaUpgrLoameFsmState TSPII_OlaUpgrLoameFsm::RunAutoLosSoak()
{
	if (myStateStopwatch.GetElapsedTime() > MAX_LOAME_SOAK_TIME)
		return CHANGE_GAIN;

	myTimedProcess->WakeUp();
	return AUTO_LOS_DISABLE_SOAK;
}
TSPII_OlaUpgrLoameFsm::TSPII_OlaUpgrLoameFsmState TSPII_OlaUpgrLoameFsm::RunChangeGain()
{
	if (myStateStopwatch.GetElapsedTime() > (MAX_LOAME_SOAK_TIME*2))
		return COMPLETED;

	myTimedProcess->WakeUp();
	return CHANGE_GAIN;
}

TSPII_OlaUpgrLoameFsm::TSPII_OlaUpgrLoameFsmState TSPII_OlaUpgrLoameFsm::RunCompleted()
{
	return OLA_UPGRADE_IDLE;
}

void TSPII_OlaUpgrLoameFsm::RestartFsm()
{
	//Reset all param
	myCurrentState = OLA_UPGRADE_IDLE;
    myLoameConfigInProgress = false;
	myLoameIsConfigured = false;
	myLoameConfigRequested = false;
}

void TSPII_OlaUpgrLoameFsm::ConfigureLoame()
{
	myLoameConfigRequested = true;
}

TSPII_LxameUpgrSwitchCntrlAction::TSPII_LxameUpgrSwitchCntrlAction():
myLoameFSMs(MAX_AMPS_PER_SHELF)
{
	int i;
	mySwitchArmingCounts = new uint32[MAX_AMPS_PER_SHELF];
    for (i = 0 ; i < MAX_AMPS_PER_SHELF; i++)
    {
        mySwitchArmingCounts[i] = 0;
    }
	//Create the Loame upgrade FSMs
    myLoameFSMs[0] = new TSPII_OlaUpgrLoameFsm(LOAM_2);
    myLoameFSMs[1] = new TSPII_OlaUpgrLoameFsm(LOAM_16);
	myLoameFSMs[2] = new TSPII_OlaUpgrLoameFsm(LOAM_6);
	myLoameFSMs[3] = new TSPII_OlaUpgrLoameFsm(LOAM_12);

    myBbAction = new FC_BbAction(this);
	//Add the SCFG region as an input region
	mySCFGRegion = &(T6100_MainAppIf::Instance().GetSCFGApp().GetParamRegion());
	myBbAction->AddInputRegion(mySCFGRegion);
	myTimedProcess = new FC_TimedProcess(*this, gTimerDispatcher, LXAME_SWITCH_PERIOD);
}

TSPII_LxameUpgrSwitchCntrlAction::~TSPII_LxameUpgrSwitchCntrlAction()
{
	int i;
	delete [] mySwitchArmingCounts;

	for (i = 0 ; i < MAX_AMPS_PER_SHELF; i++)
    {
        delete myLoameFSMs[i];
		myLoameFSMs[i]= NULL;
    }

	myTimedProcess->SuspendImmediate();
	myBbAction->RemoveInputRegion(mySCFGRegion);
	delete myBbAction;
	delete myTimedProcess;
}

void TSPII_LxameUpgrSwitchCntrlAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run method should not be called");
}

FC_Object* TSPII_LxameUpgrSwitchCntrlAction::DoRunWithReason(unsigned theRunReason,
                                                  FC_Object* theInvokerObj,
                                                  FC_Object* theParam)
{
	//For subnode config changes from subnode OLA->SBOADM 2d or
	//SBOADM 2d to OLA, set the amplifier switches appropriately.
	//Steps to setting the upgrade switches:
	//0. If switches are set the way we want them, don't do anything
	//1. First set the arm timeout value to 20 secs (to give us ample time to switch)
	//2. Arm the switches
	//3. Make sure the switches are armed
	//4. Hit the switches simultaneously
	bool continueProcessing = false;
	SCFG_ParamObject& aSCFGParam = (*mySCFGRegion)[0];
	uint8 theSubNodeIndex = aSCFGParam.GetSubNodeCfg().GetSubNodeIndex();
	TSPII_UpgradeSwitchStatus theSwitchPos = SW_POSITION_ERROR;
	bool theSboadmSwitchPos = false;
	bool is2dNode = true;
	int i;

	if (theSubNodeIndex == SBOADM_FP3_CH44_RCMM2_AMP_INDEX ||
		theSubNodeIndex == SBOADM_FP3_CH44_RCMM4_AMP_INDEX ||
        theSubNodeIndex == SBOADM_FP3_CH44_RCMM8_AMP_INDEX ||
		theSubNodeIndex == OLA_FP3_7100_CH44_AMP_INDEX ||
		theSubNodeIndex == SBOADM_FP3_CH32PLUS_RCMM4_AMP_INDEX ||
		theSubNodeIndex == SBOADM_FP3_CH32PLUS_RCMM2_AMP_INDEX ||
		theSubNodeIndex == OLA_FP3_7100_CH32PLUS_AMP_INDEX ||
        theSubNodeIndex == SBOADM_FP3_CH44_RCMM8_HCSS_AMP_INDEX)
	{
		theSwitchPos = ((theSubNodeIndex == OLA_FP3_7100_CH44_AMP_INDEX || theSubNodeIndex == OLA_FP3_7100_CH32PLUS_AMP_INDEX) ? SW_POSITION_OLA : SW_POSITION_SBOADM);
		theSboadmSwitchPos = ((theSubNodeIndex == OLA_FP3_7100_CH44_AMP_INDEX || theSubNodeIndex == OLA_FP3_7100_CH32PLUS_AMP_INDEX) ? false : true);
		continueProcessing = true;
		if (theSubNodeIndex == SBOADM_FP3_CH44_RCMM4_AMP_INDEX || theSubNodeIndex == SBOADM_FP3_CH32PLUS_RCMM4_AMP_INDEX || 
            theSubNodeIndex == SBOADM_FP3_CH44_RCMM8_AMP_INDEX || theSubNodeIndex == SBOADM_FP3_CH44_RCMM8_HCSS_AMP_INDEX)
			is2dNode = false;
	}
	if (continueProcessing)
	{
		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLiam1 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LIAM_1);
		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLiam19 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LIAM_19);
		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLiam5 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LIAM_5);
		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLiam13 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LIAM_13);

		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLoam2 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LOAM_2);
		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLoam16 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LOAM_16);
		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLoam6 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LOAM_6);
		TSPII_CntrlLxameOsaCtrlAction* theCtrlActLoam12 = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(LOAM_12);

		bool switchRequired = false;
		bool pendCond = false;

		Process(0, LIAM_1, LOAM_2, pendCond, switchRequired, theSwitchPos);
        Process(1, LIAM_19, LOAM_16, pendCond, switchRequired, theSwitchPos);

		if (!is2dNode) //C and D sides only exist on 4d node
		{
		    Process(2, LIAM_5, LOAM_6, pendCond, switchRequired, theSwitchPos);
		    Process(3, LIAM_13, LOAM_12, pendCond, switchRequired, theSwitchPos);
		}
		
		if (pendCond == false && switchRequired == true)
		{
			//Assert mastership, just in case
		    //Assert/Negate the OLA switch
			TSPII_OscMapperFpgaCtrl::GetInstance().OptSetSwitchMastershipControl(true);
		    TSPII_OscMapperFpgaCtrl::GetInstance().OptSetOpticalSwitchControl(theSboadmSwitchPos);
            fc_cout << "Switching LIAME/LRAME upgrade switch to : "; 
            if (theSboadmSwitchPos)
                fc_cout << "SBOADM (position A)" << endl;
            else
                fc_cout << "OLA    (position B)" << endl;

			//Disarm the switches
			if (theCtrlActLiam1)
		        theCtrlActLiam1->DisarmUpgradeSwitch();
			if (theCtrlActLiam19)
                theCtrlActLiam19->DisarmUpgradeSwitch();

			if (!is2dNode)
			{
			    if (theCtrlActLiam5)
                    theCtrlActLiam5->DisarmUpgradeSwitch();
			    if (theCtrlActLiam13)
                    theCtrlActLiam13->DisarmUpgradeSwitch();
			}

			//Enable AUTO LOS feature
			if (theCtrlActLoam2)
		        theCtrlActLoam2->SetAutoLOSEnable(true);
			if (theCtrlActLoam16)
                theCtrlActLoam16->SetAutoLOSEnable(true);

			if (!is2dNode)
			{
			    if (theCtrlActLoam6)
                    theCtrlActLoam6->SetAutoLOSEnable(true);
			    if (theCtrlActLoam12)
                    theCtrlActLoam12->SetAutoLOSEnable(true);
			}

			//Reset all output AMP state machines
			for (i = 0 ; i < MAX_AMPS_PER_SHELF; i++)
			{
                myLoameFSMs[i]->RestartFsm();
			}
		}

		if (pendCond)
			myTimedProcess->WakeUp();

		//If there is an error condition let the amps disarm by themselves
	}
	
    return NULL;
}

FC_TimedProcess* TSPII_LxameUpgrSwitchCntrlAction::GetSwitchTimedProcess()
{
	return myTimedProcess;
}

void TSPII_LxameUpgrSwitchCntrlAction::ResetArmingCount(CT_SlotId theSlot)
{
	switch (theSlot)
	{
	case LIAM_1:
	case LOAM_2:
        mySwitchArmingCounts[0] =0;
		myLoameFSMs[0]->RestartFsm();
		break;
	case LIAM_19:
	case LOAM_16:
		mySwitchArmingCounts[1] = 0;
		myLoameFSMs[1]->RestartFsm();
		break;
	case LIAM_5:
	case LOAM_6:
		mySwitchArmingCounts[2] = 0;
		myLoameFSMs[2]->RestartFsm();
		break;
	case LIAM_13:
	case LOAM_12:
		mySwitchArmingCounts[3] = 0;
		myLoameFSMs[3]->RestartFsm();
		break;
	default:
		break;
	}
}

void TSPII_LxameUpgrSwitchCntrlAction::Process(int index, CT_SlotId theInputAmpSlot, CT_SlotId theOutputAmpSlot, bool& pending, bool& performSwitch, TSPII_UpgradeSwitchStatus newSwitchPosition)
{

	TSPII_CntrlLxameOsaCtrlAction* theInputAmpAction = TSPII_Spm8560SubApplication::GetSpecificInstance().GetLxameOsaCtrlAction(theInputAmpSlot);
	TSPII_OlaUpgrLoameFsm* theOutputAmpFsm = myLoameFSMs[index];

    bool considerOutputAmp = false;
	bool ignoreOutputAmp = true;

	//If switching to SBOADM position, we have to control the output AMP LOS shutdown as well
    if (newSwitchPosition == SW_POSITION_SBOADM)
	{
		if (TSPII_Spm8560SubApplication::GetSpecificInstance().IsCardInitialized(theOutputAmpSlot))
		{
            considerOutputAmp = true;
			ignoreOutputAmp = false;
		}
	}


	if (theInputAmpAction)
	{
		if (theInputAmpAction->IsAmpPresent())
		{
			if (theInputAmpAction->GetUpgradeSwitchStatus() != newSwitchPosition)
			{
				if (mySwitchArmingCounts[index] != 0)
				{
				    if (considerOutputAmp)
					{
						//Run the loame state machine
						theOutputAmpFsm->Run(this);
                        //theOutputAmpAction->GetAutoLOSEnableState(stage1State, stage2State);
					}

					if ((theInputAmpAction->IsUpgradeSwitchArmed()) &&
						((considerOutputAmp && theOutputAmpFsm->IsConfigCompleted()) || ignoreOutputAmp))
					{
						//Reset the FSM now that we are done
						//theOutputAmpFsm->RestartFsm();
						performSwitch = true;
					    mySwitchArmingCounts[index] = 0; //reset counter for next switch
					}
					else 
					{
						pending = true;
						theOutputAmpFsm->Run(this);
						fc_cout << "Slot " << (uint32)theInputAmpSlot << " - Waiting for LIAME/LRAME switch arming ..." << endl;
					    (mySwitchArmingCounts[index])++; // keep waiting for switch to arm
					}
					if (((mySwitchArmingCounts[index] % MAX_ARM_ITERATION) == 0) && !performSwitch)
					{
						theOutputAmpFsm->RestartFsm();
                        mySwitchArmingCounts[index] = 0; //start over
						fc_cout << "Slot " << (uint32)theInputAmpSlot << " - Unable to arm LIAME/LRAME switch..Starting over" << endl;
					}
				}
				else
				{
					//Check whether we are already armed. If so just proceed.
					//This covers the situation where we timed out on the arming
					//and the switch became armed immeaditely after that
				    if (considerOutputAmp)
					{
						//Run the state machine
						theOutputAmpFsm->Run(this);
                        //theOutputAmpAction->GetAutoLOSEnableState(stage1State, stage2State);
					}
					if (theInputAmpAction->IsUpgradeSwitchArmed() &&
						((considerOutputAmp && theOutputAmpFsm->IsConfigCompleted()) || ignoreOutputAmp))
					{
						//theOutputAmpFsm->RestartFsm();
						performSwitch = true;
					    mySwitchArmingCounts[index] = 0; //reset counter for next switch
					}
					else
					{
					    theInputAmpAction->SetUpgradeSwitchArmingTimeout(SWITCH_ARM_TIMEOUT_VAL);
					    //theCtrlActLiam1->DisarmUpgradeSwitch();
			            theInputAmpAction->ArmUpgradeSwitch(this);
						if (considerOutputAmp)
						{
                            theOutputAmpFsm->ConfigureLoame();
							//fc_cout << "Disabling LOS for slot " << theOutputAmpSlot << endl;
                            //theOutputAmpAction->SetAutoLOSEnable(false);	
						}

					    mySwitchArmingCounts[index] =1; //indicate that we are starting the arming wait
				        pending = true;
					}
				}		
			}
		}
		else
		{
            mySwitchArmingCounts[index] = 0;
		}
	}

}
