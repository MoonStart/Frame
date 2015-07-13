// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1PROTECTIONACTION_38E49EBD03A0_INCLUDED
#define _INC_SP_1PLUS1PROTECTIONACTION_38E49EBD03A0_INCLUDED

#include "SP_ProtectionAction.h"
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include "SP_1plus1ProtectionGroupConfig.h"
#include <Fsm/FC_Fsm.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <AM/AM_DefectCollector.h>
#include "SP_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include "SP_CallbackTimer.h"


class SP_1plus1Selector;
class SP_1plus1APSController;
class SP_1plus1RequestParser;
class SP_1plus1K1K2Transmitter;
class SP_1plus1ProtectionGroupConfig;
class SP_1plus1FsmLogger;
class SP_OduKSnc;
class SP_Defects;
class FC_Fsm;
class SP_FsmTestParser;
class SP_SwitchingStatistic;
class MON_Region;
class SP_ProtectionGroupStatusRegion;
class CFG_Region;
class SP_DefectProcessorAction;
class ALM_AppIf;
class SP_1plus1ProtectionGroupStatus;




//This class is responsible to executing the 1+1 protection 
//switching coordination. It holds the latest copy of the 
//configuration of the 1+1 protection group. It controls the 
//execution of the following elements: request parser, APS 
//controller, K1K2 transmitter and the selector. There is one 
//protection action per protection group on a port shelf. It 
//always exists, but can be enable or disables. This 
//protection action is part of a protection action vector. 
//This vector is referenced for group operation such has 
//command processing, configuration update or synchronization.


class SP_1plus1ProtectionAction 
: public SP_ProtectionAction
{
    friend class SP_1plus1K1K2Transmitter;
    friend class SP_1plus1RequestParser;
    friend class SP_1plus1Selector;
    friend class SP_1plus1APSController;
    friend class SP_FsmTestParser;

public:

	//Updates the status of the protection group according to 
	//the transmitted K-bytes and traffic selection. Also 
	//notifies switching statistics region (if the were 
	//affected).
  	virtual bool DelayedUpdateStatus(SP_ProtectionGroupStatusRegion& theStatusRegion,
                                     CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*>& theStatRegions);

	//Forwards the execution of a switching command to the 
	//request parser and forces a run of the protection 
	//action. Stores the command ID if the command is 
	//successful. Returns the command result to command 
	//processor.
    virtual CT_SP_CommandResultCode ExecuteSwitchingCommand(CT_SP_CommandType theCommand, CT_SP_CommandID theCommandID);

	//This method actually implements the protection 
	//mechanism. It first validates its configuration 
	//regions. Then it invokes the execution of it base 
	//element in the proper order: request parser, APS 
	//controller (if unlocked), K1K2 transmitter (linear 
	//only), traffic selector. Then it wakes up a status 
	//collection action that will eventually update the 
	//current status report to the admin.
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Removes any references to the facility ports: 
	//unregisters for defects, stop counting switching 
	//statistics, remove port from maps. See Enable() method 
	//about what need to be dismantle.
	virtual void Disable();
    
	//This method prepares the protection action for the new 
	//configuration. It first adds new connection points 
	//(depending on facility rate) into the port map for 
	//eventual bridge and switch operation with 
	//cross-connect. Then it fetches in the port maps 
	//(ingress and egress) reference to all the port involved 
	//in the protection group and passes them to its traffic 
	//selector. Its then fetches reference to MON and CFG 
	//region for defect monitoring and AIS-P/UNEQ-P control. 
	//It registers for notification about facility defects 
	//(MON in linear mode and TEL ports in UPSR mode) and for 
	//equipment defect (CSM and CINV). It resets the 
	//switching statistic of each facility involves in the 
	//protection group. Finally, it resets the basic elements 
	//of the protection action: APS controller, K1K2 
	//transmitter, request parser, traffic selector and mate 
	//synchronization group.
	virtual void Enable();

	//Returns a reference to the protection group 
	//configuration.
    virtual SP_1plus1ProtectionGroupConfig& Get1plus1Config();
    virtual SP_ProtectionGroupConfig& GetConfig();

	//Constructor. Requires the index and the port shelf 
	//context.
	SP_1plus1ProtectionAction(SP_Application& theApplIf);
	//Destructor.
	virtual ~SP_1plus1ProtectionAction();

	//The request parser of the protection group.
	SP_1plus1RequestParser* myRequestParserPtr;

	//The selector of the protection group.
	SP_1plus1Selector* mySelectorPtr;

	//The K1K2 transmitter of the protection group.
    SP_1plus1K1K2Transmitter* myK1K2TransmitterPtr;

	//The APS controller of the protection group.
	SP_1plus1APSController* myAPSControllerPtr;

	//Reference to the APS controller FSM logger (debug).
    SP_1plus1FsmLogger* myLogger;

	//Pointer to the defect processor
	SP_DefectProcessorAction* myDefectProcessor;

	//Pointer to MON defect and status regions
	CT_SP_ProtectionPair<MON_Region*> myMonDefectsRegion;
    CT_SP_ProtectionPair<MON_Region*> myMonStatusRegion;

    //TSPII interfaces
    CT_SP_ProtectionPair<unsigned int> myTspiiInterfaces;

    CT_SP_ProtectionPair<SP_Defects*> mySPDefects;

	//Pointer to ODUk SNC instance
	SP_OduKSnc* myOduSncInstance;

	//The index of the object in mon region
	CT_SP_ProtectionPair<int> myMONObjectIndex;

	//The index of the object in the status region
	int myIndex;

	//Indicates whether hop indications have to be sent
	bool mySendHopIndication;

    CFG_Region* mySyncRegion;
    CT_SP_ProtectionPair<CFG_Region*> myCfgMsRegion;

	//Pair to pointers to the statistics object.
    CT_SP_ProtectionPair<SP_SwitchingStatistic*> mySwitchingStat;

    uint32 myTxApsBytes;

	//Returns the last command ID.
	virtual CT_SP_CommandID GetLastCommandID();

	//Returns the last command completed.
    virtual CT_SP_Request GetLastCommandPriority();

    virtual CT_SP_Protection GetCurrentSelection()=0;
    virtual CT_SP_Protection GetInitialSelection();

	//This method checks if the protection group this action
	//is managing is different from the specified group
	//A group is considered different if the sources are different
	//the protection type is different or the usage status is different
	virtual bool IsProtectionGroupDifferent(SP_ProtectionGroupConfig& theConfig);

	//Copies the configuration data passed in to local copy
	//@returns whether the local copy matches the config data prior to the copy operation
	virtual bool CopyConfiguration(SP_ProtectionGroupConfig& theConfig);

	//Register to be told about defects
	virtual void RegisterToMONDefects();

	//Unregister from defects
	virtual void UnregisterFromMONDefects();

	inline void SetWarmRestart(){myDoingWarmRestart = true;}
	inline void RestartComplete(){myDoingWarmRestart = false;}

	//set up the protection action to correct status region and mon region
	//object indices
	void SetMyIndex();

	//Calculate service affecting status
	//and notify Alarm Management of the result
	//forcedClear is used to force clear the non service
	//affecting condition on the delete of a protection group.
	virtual void CalculateServiceStatus(bool forcedClear);
	virtual void GetAlmAppIf(CT_IntfId thePortId, SP_AlmAppIfCollection& theAlmIfCollection, SP_AlarmReason theReason) = 0;
    virtual int GetAlmIndex(CT_SP_Protection theSide);
	virtual void ConfigureHopBERAlarming(bool theEnable);

	virtual void PreRun();
	virtual void PostRun();

	virtual CT_SP_Protection GetPreferredSide();

	virtual void TransformSources(CT_SP_ProtectionPair<CT_Port> & theOrigSources, CT_SP_ProtectionPair<CT_ChannelId>& theChannels, CT_SP_ProtectionPair<CT_Port> & theNewSources, CT_SP_1plus1Type the1plus1Type);

	virtual void SetupKbyteTransmit();

	virtual bool IsSsmSwitchingAllowed();

	virtual bool IsConfigurationMismatch();

	inline SP_OduKSnc* GetOduKSncInstance() { return myOduSncInstance;}

    virtual void DumpSpecificData();

	FC_Milliseconds GetWTROffset();

    virtual FC_Milliseconds GetHoldOffTimerOffset();

    bool IsLocalDefect(CT_SP_Protection theSide);

    void SetTspiiInterface(CT_SP_Protection theSide, unsigned int theId);

    void SetSPDefects(CT_SP_Protection theSide, SP_Defects* theDefects);

    virtual bool DoSpecificStatusUpdate(SP_1plus1ProtectionGroupStatus& a1plus1Status);

    void RefreshConfiguration();

    uint32 ConvertCurrentReqToTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest);
    uint32 ConvertCurrentReqToTxApsBytes(CT_SP_Request theRequest, bool theRemoteOrLocalRequest);

    void PrepareTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest);
    void DisplayTxApsBytes(uint32 theTxApsBytes);

    // virtual functions for bi-snc, the implmentation should be done in cards
    virtual void RefreshAps(){};
    virtual void DisableAps(){};
    virtual uint32 GetApsBytes() {return 0;} // return 0 for the cards which don't support APS
    virtual void SetTxApsBytes(bool theApsInsert = true){};

protected:
    CT_SP_Protection GetCurrentYCableSelection(unsigned int tspiiIntf1, unsigned int tspiiIntf2);
    CT_SP_Protection GetInitialYCableSelection(unsigned int tspiiIntf1, unsigned int tspiiIntf2);
    bool IsYCableConfigurationMismatch(TSPII_OpticalRegion* theRxRegion, CT_Status theEqptStatus, bool realPortIsWorking, bool txLaserEnable, TSPII_OpticalRegion* theBkplRegion);
    virtual uint16 GetYCableMateSlotIdx();

private:

	//The state machine implementing the 1+1 switching 
	//protocol.
    static FC_Fsm ourFsm;

	//ID of the last command completed.
	CT_SP_CommandID myLastCommandID;

	//Last command completed.
    CT_SP_Request myLastCommand;
    bool          myDoingWarmRestart;

	SP_1plus1ProtectionGroupConfig myProtectionConfig;

	//Last processed status
	CT_SP_Request myLastStatus;

	bool myBiSwitchingChanged;

	//Timer to soak protection switch notifications
	FC_BaseTimer myNotifSoakTimer;
	bool myNotifSoak;

    //Configuration mismatch holdoff counter
    uint8 myConfigMismatchHoldoffCount;

    void ReportFopIfNeeded();

    bool myFopNrOnRequestedEntity;
    SP_CallbackTimer myFopNrTimerOnRequestedEntity;
    void CheckFopNr();
};

#endif /* _INC_SP_1PLUS1PROTECTIONACTION_38E49EBD03A0_INCLUDED */

