/*-----------------------------------------------------------------------------
 *Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Telecom Services
TARGET:         SPM8560
AUTHOR:         Anoop Mathew
DESCRIPTION:    Action that controls the Lxame upgrade switch
-----------------------------------------------------------------------------*/

#ifndef TSPII_LxameUpgrSwitchCntrlAction_H
#define TSPII_LxameUpgrSwitchCntrlAction_H

#include <vector>

#include <ExecutionSupport/FC_Milliseconds.h>
#include <ExecutionSupport/FC_BaseTimer.h>
#include <ExecutionSupport/FC_Action.h>
#include "ExecutionSupport/FC_BaseStopwatch.h"
#include <gdef.h>
#include "CommonTypes/CT_SystemIds.h"
#include "TsPii_Imp/TSPII_CntrlLxameOsaCtrlAction.h"

class FC_BbAction;
class SCFG_ParamRegion;
class FC_TimedProcess;



class TSPII_OlaUpgrLoameFsm : public FC_Action
{
	enum TSPII_OlaUpgrLoameFsmState
    {
        OLA_UPGRADE_IDLE,
        DISABLE_AUTO_LOS,
        AUTO_LOS_DISABLE_SOAK,
        CHANGE_GAIN,
        COMPLETED
    };
public:
	TSPII_OlaUpgrLoameFsm(CT_SlotId theSlotId);
	virtual ~TSPII_OlaUpgrLoameFsm();
	virtual void        Run(FC_Object* theObject = NULL);
	void RestartFsm();
	void ConfigureLoame();
	bool IsConfigInProgress() {return myLoameConfigInProgress;}
	bool IsConfigCompleted() {return myLoameIsConfigured;}

private:
	// FSM methods
	void                        EntryIdle           (TSPII_OlaUpgrLoameFsmState thePreviousState);
    void                        EntryAutoLosDisable (TSPII_OlaUpgrLoameFsmState thePreviousState);
    void                        EntryAutoLosSoak    (TSPII_OlaUpgrLoameFsmState thePreviousState);
    void                        EntryChangeGain     (TSPII_OlaUpgrLoameFsmState thePreviousState);
    void                        EntryCompleted      (TSPII_OlaUpgrLoameFsmState thePreviousState);
   
    TSPII_OlaUpgrLoameFsmState         RunIdle           ();
    TSPII_OlaUpgrLoameFsmState         RunAutoLosDisable ();
    TSPII_OlaUpgrLoameFsmState         RunAutoLosSoak    ();
    TSPII_OlaUpgrLoameFsmState         RunChangeGain     ();
    TSPII_OlaUpgrLoameFsmState         RunCompleted      ();
    
	TSPII_OlaUpgrLoameFsmState         myCurrentState;
	bool                               myLoameConfigInProgress;
	bool                               myLoameIsConfigured;
	bool                               myLoameConfigRequested;
	FC_BaseStopwatch                   myStateStopwatch;
	CT_SlotId                          mySlotId;
	FC_TimedProcess*                   myTimedProcess;
};


typedef vector< TSPII_OlaUpgrLoameFsm* >  OlaUpgFsmList;

class TSPII_LxameUpgrSwitchCntrlAction : public FC_Action
{
public:

    /* CONSTRUCTOR */   TSPII_LxameUpgrSwitchCntrlAction();
    virtual             ~TSPII_LxameUpgrSwitchCntrlAction();
    virtual void        Run(FC_Object* theObject = NULL);
    virtual FC_Object * DoRunWithReason(unsigned theRunReason, FC_Object * theInvokerObj, FC_Object * theParam = NULL);
	FC_TimedProcess*    GetSwitchTimedProcess();
	void ResetArmingCount(CT_SlotId theSlot);
	void Process(int index, CT_SlotId theInputAmpSlot, CT_SlotId theOutputAmpSlot, bool& pending, bool& performSwitch, TSPII_UpgradeSwitchStatus newSwitchPosition);
private:
    FC_BbAction *          myBbAction;
	SCFG_ParamRegion*      mySCFGRegion;
	FC_TimedProcess*       myTimedProcess;
	uint32*                mySwitchArmingCounts;
	OlaUpgFsmList          myLoameFSMs;
	
};

#endif  //  TSPII_LxameUpgrSwitchCntrlAction_H 
