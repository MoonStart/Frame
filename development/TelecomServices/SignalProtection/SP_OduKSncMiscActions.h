// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef __SP_ODUKSNCMISCACTIONS_H__
#define __SP_ODUKSNCMISCACTIONS_H__

#include <SignalProtection/SP_1plus1ProtectionAction.h>
#include <SignalProtection/SP_CallbackTimer.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <SignalProtection/SP_ProtectionGroupConfigRegion.h>
#include <Configuration/CFG_Definitions.h>


class FC_PeriodicProcess;
class FC_Action;
class FC_TimedProcess;
class FC_BoolRegion;
class SP_ApplicationStatus;


class SP_PQWPollData
{
public:
    SP_PQWPollData(uint8 thePQWChannel);
    virtual ~SP_PQWPollData();

	//All these functions are defined inline for performance reasons as they are used during protection switching
    bool SetPollData(uint16 theRxPqw, bool theHwSquelch, bool theRxSFHigh, bool theRxSFLow, bool theRxSD, bool theTxSFHigh, bool theTxSFLow, bool theTxSD);
	inline uint8 GetPQWChannel();
	inline bool IsConfigured();
	inline void SetIsConfigured(bool theConfigure);

private:
    uint8 myPQWChannel;
	bool myIsConfigured;
	uint16 myRxPQW;
    bool myHWSquelch;
    bool myRxSFHigh;
    bool myRxSFLow;
    bool myRxSD;
	bool myTxSFHigh;
    bool myTxSFLow;
    bool myTxSD;

};

inline uint8 SP_PQWPollData::GetPQWChannel()              { return myPQWChannel; }
inline bool SP_PQWPollData::IsConfigured()                { return myIsConfigured; }
void SP_PQWPollData::SetIsConfigured(bool theConfigure)   { myIsConfigured = theConfigure; }


/////////////////////////////////////////////////////////////////////////
//This action is responsible for polling for PQW and associated status
class SP_OduKSncPQWPollingAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_OduKSncPQWPollingAction (FC_BoolRegion& theIsrMonRegion, int theNumOfPqwChannels);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_OduKSncPQWPollingAction();

	static SP_OduKSncPQWPollingAction* GetInstance();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//Run method
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    FC_PeriodicProcess* GetProcessPtr();

    void SetConfiguration(bool isConfigured, uint8 thePQWChannel, CT_ShelfId theShelf, CT_SlotId theSlot /*0-based*/);

protected:
	
private:

	//
    FC_PeriodicProcess* myProcess;
    FC_BoolRegion& myIsrMonRegion;
	static SP_OduKSncPQWPollingAction       *itsInstance;    // Instance pointers

	typedef vector<SP_PQWPollData*> SP_PQWPollDataCollection;
	SP_PQWPollDataCollection myDataCollectionSet;

    bool myPQWTimeout[NUMBER_OF_SHELF+1][NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF+1];
    int myPQWTimeoutRefCount[NUMBER_OF_SHELF+1][NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF+1];
};

//////////////////////////////////////////////////////////////////////////////
//This class enables/disables PQW timeout interrupts for remote
//slots based on configuration
class SP_OduKSncPQWTimeoutIntrCtrl
{
public:
	//Constructor. 
    //##ModelId=3BBC9B0F02A0
    SP_OduKSncPQWTimeoutIntrCtrl ();

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_OduKSncPQWTimeoutIntrCtrl();

	static SP_OduKSncPQWTimeoutIntrCtrl & GetInstance();

	void SetConfiguration(bool interruptEnable, CT_ShelfId theShelf, CT_SlotId theSlot);

protected:
	
private:
    static SP_OduKSncPQWTimeoutIntrCtrl       *itsInstance;    // Instance pointers
    int myPQWIntRefCount[NUMBER_OF_SHELF+1][NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF+1];
};

//////////////////////////////////////////////////////////////////////////////////////
//This class configures the defect priority table for SNC.
class SP_OduKSncPriorityTable
{
public:
	//Constructor. 
    //##ModelId=3BBC9B0F02A0
    SP_OduKSncPriorityTable ();

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_OduKSncPriorityTable();

	static SP_OduKSncPriorityTable & GetInstance();

	void Configure();

protected:
	
private:
    static SP_OduKSncPriorityTable       *itsInstance;    // Instance pointers
	bool myIsConfigured;
};

//////////////////////////////////////////////////////////////////////////////////////
//This class determines general switch fab configuration parameters like logical shelf id etc...
class SP_OduKSncSwitchFabConfig
{
public:
	//Constructor. 
    //##ModelId=3BBC9B0F02A0
    SP_OduKSncSwitchFabConfig ();

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_OduKSncSwitchFabConfig();

	static SP_OduKSncSwitchFabConfig & GetInstance();

	void GetLogicalShelfId(CFG_Misc& aMiscCfgObject, CT_ShelfId phyShelfId1, CT_ShelfId phyShelfId2, CT_ShelfId* theShelfId1, CT_ShelfId* theShelfId2);

protected:
	
private:
    static SP_OduKSncSwitchFabConfig       *itsInstance;    // Instance pointers
};

/////////////////////////////////////////////////////////////////////////////////////
//This class implements an action that control the tranmission of pqw from a module
//during initialization
class SP_OduKSncPQWTxControlAction
: public FC_Action
{
public:
	//Constructor. 
    //##ModelId=3BBC9B0F02A0
    SP_OduKSncPQWTxControlAction (TEL_BbRegionBaseImp<SP_ApplicationStatus>* theAppStatus,
                                  FC_BoolRegion* theControlRegion);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_OduKSncPQWTxControlAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

protected:
	
private:
    FC_BbAction* myBbAction;
    TEL_BbRegionBaseImp<SP_ApplicationStatus>* myAppStatus;
    FC_BoolRegion* myControlRegion;
};

/////////////////////////////////////////////////////////////////////////////////////
//This class implements an action that sets up global snc configuration
//prior to protection schemes being configured.
//In then updates the control region so that protection scheme configuration may occur
//////////////////////////////////////////////////////////////////////////////////////
class SP_OduKSncGlobalControlConfigAction
: public FC_Action
{
public:
	//Constructor. 
    //##ModelId=3BBC9B0F02A0
    SP_OduKSncGlobalControlConfigAction (CFG_MiscCfgRegion* theCfgMiscRegion,
                                         FC_BoolRegion* theControlRegion);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_OduKSncGlobalControlConfigAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void SetOverride(bool theOverride);
    FC_TimedProcess* GetProcessPtr();

protected:
	
private:
	CT_ShelfId myLogicalShelfId;
    CT_ShelfId myPhyShelfId;
    CT_SlotId mySlotId;
    FC_BbAction* myBbAction;
    CFG_MiscCfgRegion* myCfgSwitchModeRegion;
    FC_TimedProcess* myProcess;
	CT_TEL_SwitchMode myPrevSwitchMode;
    FC_BoolRegion* myControlRegion;
    bool myGeneralControlInitComplete;
    SP_CallbackTimer* myHoldoffTimer;
    bool myOverride;
};

#endif /* __SP_ODUKSNCMISCACTIONS_H__ */

