// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_PROTECTIONACTION_38E49D7601C9_INCLUDED
#define _INC_SP_PROTECTIONACTION_38E49D7601C9_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include <CommonTypes/CT_SP_CommandType.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include "SP_ProtectionGroupStatusRegionImp.h"
#include "SP_SwitchingStatistic.h"
#include <strstream>

const int SP_MAX_SNAPSHOT = 10;

class SP_StatusCollectionAction;
class T6700_PortShelfIf;
class SP_ProtectionGroupStatus;
class SP_ProtectionGroupStatusRegion;
class SP_ProtectionGroupConfig;
class SP_Selector;
class SP_RequestParser;
class FC_WakeUpProcessAction;
class CT_SP_CommandType;
class FC_OneShotProcess;
class FC_TimedProcess;
class FC_BbAction;
class SP_Application;
class SP_DefectProcessorAction;


//This class is the base class for signal protection action. 
//It holds protection configuration common to both type of 
//protection.
//##ModelId=38E49D7601C9
class SP_ProtectionAction 
: public FC_Action
{
public:

	//Returns true if the protection action is enabled and 
	//running.
	//##ModelId=39071D8B00A6
	virtual bool IsEnabled() const;

	//Returns true if the protection action is allowed to operate
	virtual bool IsAllowedToOperate() const;

	//Allow the protection action to operate
	virtual void AllowOperation();

	//This method enables the protection action to protect 
	//the facilities. This should be specialized by derived 
	//class.
	//##ModelId=39071D8B016E
	virtual void Enable();

	//This method disables a protection action from running. 
	//It should be specialized by derived class. This method 
	//suspend the status collection process and changes the 
	//enable status for false.
	//##ModelId=38F21CBF0223
	virtual void Disable();

    //This method disables a protection action from running. 
	virtual void DisableBase();

    virtual void UpdateUsage();

	//This method requests the execution of a switching 
	//command on a protection group. The execution fails if 
	//conditions are such that a higher priority command is 
	//being executed. It returns true if command fails. The 
	//command ID received is stored for eventual 
	//verification. This method is abstract.
	//##ModelId=38EDE8CE023C
	virtual CT_SP_CommandResultCode ExecuteSwitchingCommand(CT_SP_CommandType theCommand, CT_SP_CommandID theCommandID) = 0;

	//Constructor. Requires index and port shelf context.
	//##ModelId=38FB0962028D
	SP_ProtectionAction(SP_Application& theApplIf);

	//Destructor.
	//##ModelId=38FB096202DE
	virtual ~SP_ProtectionAction();

	//Updates the status of each protection unit by reading 
	//the status of the request parsers (abstract).
	//##ModelId=3911CCBF00CF
  	virtual bool DelayedUpdateStatus(SP_ProtectionGroupStatusRegion& theStatusRegion,
                                     CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*>& theStatRegions) = 0;

	//Returns a reference to the protection action 
	//configuration copy.
	//##ModelId=3B8BC9BF0192
	virtual SP_ProtectionGroupConfig& GetConfig() = 0;

	//Starts the protection action if stopped (debug).
	//##ModelId=39ACEFA00047
    inline void Start();
	//Stop the protection action from running (debug).
	//##ModelId=39ACEFA00033
    inline void Stop();

	//Returns a reference to the low priority wake up action.
	//##ModelId=39ACEFA0000B
    inline FC_WakeUpProcessAction& GetLowPriorityWakeUpAction();
	//Returns a reference to the high priority wake up action.
	//##ModelId=3B8BC9BF0156
    inline FC_WakeUpProcessAction& GetHighPriorityWakeUpAction();

	//Not supported.
	//##ModelId=3B8BC9BF007A
    virtual void Run( FC_Object* theObject = NULL );

	//This method returns the last command ID executed with 
	//or without success.
	//##ModelId=38EDEC4F037D
	virtual CT_SP_CommandID GetLastCommandID() = 0;

	//This method returns the priority of the last switching 
	//command (abstract).
	//##ModelId=3B8BC9BE0231
    virtual CT_SP_Request GetLastCommandPriority() = 0;

	//This method checks if the protection group this action
	//is managing is different from the specified group
	//A group is considered different if the sources are different
	//the protection type is different or the usage status is different
	virtual bool IsProtectionGroupDifferent(SP_ProtectionGroupConfig& theConfig) = 0;

    //This method checks if all the relevent resources that are required
    //for this protection group to operate are present.
	virtual bool IsResourceReady(SP_ProtectionGroupConfig& theConfig);

    //This method checks if this protection group is allowed to be configured
    //on this card
	virtual bool IsConfigurationAllowed(SP_ProtectionGroupConfig& theConfig);

	//Copies the configuration data passed in to local copy
	//@returns whether the local copy matches the config data prior to the copy operation
	virtual bool CopyConfiguration(SP_ProtectionGroupConfig& theConfig) = 0;

	//Run the protection action to apply new configuration
	void ApplyConfiguration();

	//Register to be told about defects
	virtual void RegisterToMONDefects() = 0;

	//Unregister from defects
	virtual void UnregisterFromMONDefects() = 0;

	//This method should be specialized by derived class. It 
	//does nothing by default.
	//##ModelId=3B8BC9BE01CD
	virtual FC_Stream&   SnapshotWrite(FC_Stream& theStream);
	//This method force the protection action to send all it 
	//its attributes into a selected stream.
	//##ModelId=3B8BC9BE0173
	unsigned int         SnapshotTake(const char * theHeader);
	//This mehotd dumps the specified snapshot to the console 
	//(debug).
	//##ModelId=3B8BC9BE0119
	void                 SnapshotDisplay(unsigned int theIndex);
	//This method delete the specified snapshot (debug).
	//##ModelId=3B8BC9BE00C9
	void                 SnapshotClear(unsigned int theIndex);
	//This method lists all the snapshot currently taken 
	//(debug).
	//##ModelId=3B8BC9BE00B4
	void                 SnapshotList();

    FC_BbAction* GetBbAction() { return myBbAction; }

    SP_Application& GetAppIf() const { return myApplIf;}

    //Method for performance improvements
	virtual void RegisterSpecificObservers(SP_DefectProcessorAction* theDefectProcessor);

    virtual void UnregisterSpecificObservers(SP_DefectProcessorAction* theDefectProcessor);

	/*Return value indicates whether glitches should be ignored */
    virtual bool GetSpecificSFDefects(CT_SP_Protection theSide, CT_IntfId theIntfId, uint32* theCount, bool* theState);
	virtual bool GetSpecificSFLowDefects(CT_SP_Protection theSide, CT_IntfId theIntfId, uint32* theCount, bool* theState);
	virtual bool GetSpecificSDDefects(CT_SP_Protection theSide, CT_IntfId theIntfId, uint32* theCount, bool* theState);

	virtual bool IsSsmSwitchingAllowed();

protected:


	//True if protection action is stop from running (debug).
	//##ModelId=39ACEF9F0316
    bool stopped;

	//Pointer to the low priority wake up action usually 
	//execute for low priority event (configuration or 
	//command update).
	//##ModelId=39ACEF9F02E5
    FC_WakeUpProcessAction* myLowPriorityCallbackAction;
	//Pointer to the high priority wake up action usually 
	//execute for high priority event (failures, APS 
	//messages).
	//##ModelId=3B8BC9BD0208
    FC_WakeUpProcessAction* myHighPriorityCallbackAction;
	//Low priority process running low priority action.
	//##ModelId=3B8BC9BD01FE
    FC_OneShotProcess* myLowPriorityProcess;
	//High priority process running high priority action.
	//##ModelId=39ACEF9F029E
    FC_OneShotProcess* myHighPriorityProcess;

	//This class is a FC_WakeUpProcessAction with a define static 
    //instance name specific for signal protection.
	//##ModelId=3BBC9B040131
    class SP_WakeUpProcessAction : public FC_WakeUpProcessAction
    {
    public:
	//Constructor. Requires a one shot process.
		//##ModelId=3BBC9B040150
        SP_WakeUpProcessAction(FC_OneShotProcess& theProcess) : FC_WakeUpProcessAction(theProcess) {}
	//Returns a reference to the instance name.
		//##ModelId=3BBC9B04015A
        virtual const char*  GetInstanceName(void) const;
	//Their instance name.
		//##ModelId=3BBC9B040164
        static const char*   ourInstanceName;
    };

	//Prints to the cosole the reason why action if executed.
	//##ModelId=3B8BC9BD0276
    void Log(const string& theGroupType, unsigned theReason, FC_Object* theInvoker, FC_Object* theParam);



private:

	bool myEnabledStatus;
	bool myOperationStatus;

    FC_BbAction* myBbAction;

	//Array for stream use to store snapshots (debug).
	//##ModelId=3B8BC9BD0153
	static FC_Stream*  mySnapshotFCStream[SP_MAX_SNAPSHOT];
	//Array for stream use to store snapshots (debug).
	//##ModelId=3B8BC9BD013F
	static ostrstream* mySnapshotStrstream[SP_MAX_SNAPSHOT];

    SP_Application& myApplIf;

};

//This is true is the protection action is enabled and 
//running.
//##ModelId=39071D8B00A6
inline bool SP_ProtectionAction::IsEnabled() const
{
    return myEnabledStatus;
}

//This is true is the protection action is allowed to run
//##ModelId=39071D8B00A6
inline bool SP_ProtectionAction::IsAllowedToOperate() const
{
    return myOperationStatus;
}

//Allow the protection action to operate
//##ModelId=39071D8B00A6
inline void SP_ProtectionAction::AllowOperation() {myOperationStatus = true;}

//This method enables the protection action to protect 
//the facilities. This assumes that the facilities have 
//been configured as well as the other properties of the 
//protection group.
//##ModelId=39071D8B016E
inline void SP_ProtectionAction::Enable() 
{
	// wake up this action's process
	//myLowPriorityProcess->WakeUp();
	//myHighPriorityProcess->WakeUp();
    myEnabledStatus = true;
}

//This method disables a protection action from running. 
//It un-registers any callbacks from port monitoring. It 
//also specifies in the switching statistic objects that 
//each port is not involved in protection anymore.
//##ModelId=38F21CBF0223
inline void SP_ProtectionAction::Disable()
{
    //myStatusCollectionProcessPtr->SuspendImmediate();
	myLowPriorityProcess->SuspendImmediate();
	myHighPriorityProcess->SuspendImmediate();
    myEnabledStatus = false;
	myOperationStatus = false;
}

//##ModelId=39ACEFA00047
inline void SP_ProtectionAction::Start() { stopped = false; }
//##ModelId=39ACEFA00033
inline void SP_ProtectionAction::Stop() { stopped = true; }

//##ModelId=39ACEFA0000B
inline FC_WakeUpProcessAction& SP_ProtectionAction::GetLowPriorityWakeUpAction()
{
    return *myLowPriorityCallbackAction;
}

//##ModelId=3B8BC9BF0156
inline FC_WakeUpProcessAction& SP_ProtectionAction::GetHighPriorityWakeUpAction()
{
    return *myHighPriorityCallbackAction;
}


#endif /* _INC_SP_PROTECTIONACTION_38E49D7601C9_INCLUDED */

