// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_ARRDEFECTCOLLECTORACTION_38E35B0900D0_INCLUDED
#define _INC_SP_ARRDEFECTCOLLECTORACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include "SP_Definitions.h"
#include "SP_CallbackTimer.h"
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <vector>

#ifdef PSOSP
#include <map>
#include <multimap>
#else
#include <map>
#endif

class FC_BbAction;
class T6100_CardIf;
class MON_Region;
class SP_ArrDefectCollectorConfigAction;
class SP_ReRouteConfigRegion;
class SP_ReRouteDefectRegion;
class CFG_Region;
class CSM_CardConfigStatusRegion;
class SP_ArrOduDefectCollectorData;

typedef enum SP_ArrTimerState_Enum
{
    TIMER_NOT_STARTED,
    TIMER_STARTED_RUNNING,
    TIMER_STARTED_EXPIRED
} SP_ArrTimerState;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class implements an instance of a port data container for the defect collector action
class SP_ArrPortDefectCollectorData
{
public:
    SP_ArrPortDefectCollectorData(CT_IntfId thePortId, 
		                      uint8 theDefectObjIndex, 
							  MON_Region* theMonOptDefectRegion, 
							  MON_Region* theMonOtuDefectRegion, 
							  MON_Region* theMonOduDefectRegion,
							  MON_Region* theMonRsDefectRegion,
							  MON_Region* theMonMsDefectRegion,
                              MON_Region* theMonRsConfigRegion,
							  MON_Region* theMonOtuConfigRegion,
							  FC_Action&  theCallbackAction);
    virtual ~SP_ArrPortDefectCollectorData();

	//Get defect region pointer for a defect layer.
	MON_Region* GetDefectRegion(SP_ArrDefectLayer theDefectLayer);
    MON_Region* GetConfigRegion(SP_ArrDefectLayer theDefectLayer);
	SP_ArrTimerState GetClearSoakTimerState();
	void StartClearSoakTimer();
	void StopClearSoakTimer();
    SP_ArrTimerState GetPhySoakTimerState();
	void StartPhySoakTimer();
	void StopPhySoakTimer();
    bool SetPhyDefectActive(bool isActive);
    inline bool GetPhyDefectActive();
    bool SetInternalSystemDefect(bool theIntSysDefect);
    inline bool GetInternalSystemDefect();
	inline uint8 GetDefectObjIndex(SP_ArrDefectLayer theDefectLayer);
	inline CT_IntfId GetPortId();
	inline bool IsCurrentlyMonitoringDefects();
	inline void SetDefectMonitoring(bool theEnable);

private:
    //MON defect regions that this action is collecting defects from
	MON_Region* myMonOduDefectRegion;
	MON_Region* myMonOtuDefectRegion;
	MON_Region* myMonOptDefectRegion;
    MON_Region* myMonRsDefectRegion;
	MON_Region* myMonMsDefectRegion;

    //MON config regions that this action is looking up configuration params
    MON_Region* myMonOtuConfigRegion;
	MON_Region* myMonRsConfigRegion;

	uint8 myDefectObjIndex;
	CT_IntfId myPortId;
	bool myIsDefectsMonitored;
	SP_CallbackTimer myClearHoldoffTimer;
    SP_CallbackTimer myPhyHoldoffTimer;
    bool myPhyDefectActive;
    bool myInternalSystemDefect;
};

inline bool SP_ArrPortDefectCollectorData::GetPhyDefectActive()                                 { return  myPhyDefectActive; }
inline bool SP_ArrPortDefectCollectorData::GetInternalSystemDefect()                            { return  myInternalSystemDefect; }
inline uint8 SP_ArrPortDefectCollectorData::GetDefectObjIndex(SP_ArrDefectLayer theDefectLayer) { return  myDefectObjIndex; }
inline CT_IntfId SP_ArrPortDefectCollectorData::GetPortId()                                     { return  myPortId; }
inline bool SP_ArrPortDefectCollectorData::IsCurrentlyMonitoringDefects()                       { return  myIsDefectsMonitored; }
inline void SP_ArrPortDefectCollectorData::SetDefectMonitoring(bool theEnable)                  { myIsDefectsMonitored = theEnable; }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class implements an instance of a odu data container for the defect collector action
class SP_ArrOduDefectCollectorData
{
public:
    SP_ArrOduDefectCollectorData(CT_ODU_Identifier theOduId, 
		                      uint8 theDefectObjIndex,
							  MON_Region* theMonOduDefectRegion,
							  FC_Action&  theCallbackAction);
    virtual ~SP_ArrOduDefectCollectorData();

	//Get defect region pointer for a defect layer.
	SP_ArrTimerState GetClearSoakTimerState();
	void StartClearSoakTimer();
	void StopClearSoakTimer();
    inline MON_Region* GetDefectRegion();
	inline uint8 GetDefectObjIndex();
	inline CT_ODU_Identifier GetOduId();
	inline bool IsCurrentlyMonitoringDefects();
	inline void SetDefectMonitoring(bool theEnable);

private:
    //MON defect regions that this action is collecting defects from
	MON_Region* myMonOduDefectRegion;

	uint8 myDefectObjIndex;
	CT_ODU_Identifier myOduId;
	bool myIsDefectsMonitored;
	SP_CallbackTimer myClearHoldoffTimer;
};

inline MON_Region* SP_ArrOduDefectCollectorData::GetDefectRegion()                             { return  myMonOduDefectRegion; }
inline uint8 SP_ArrOduDefectCollectorData::GetDefectObjIndex()                                 { return  myDefectObjIndex; }
inline CT_ODU_Identifier SP_ArrOduDefectCollectorData::GetOduId()                              { return  myOduId; }
inline bool SP_ArrOduDefectCollectorData::IsCurrentlyMonitoringDefects()                       { return  myIsDefectsMonitored; }
inline void SP_ArrOduDefectCollectorData::SetDefectMonitoring(bool theEnable)                  { myIsDefectsMonitored = theEnable; }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef vector<SP_ArrPortDefectCollectorData*> SP_ArrPortDefectCollectorDataCollection;
typedef map<uint32, SP_ArrOduDefectCollectorData*, greater<uint32> > SP_ArrOduDefectCollectorDataCollection;
typedef multimap<SP_ArrDefectLayer, CT_TEL_Defect, greater<SP_ArrDefectLayer> > SP_ArrDefectList;
typedef map< unsigned int, unsigned int, greater<unsigned int> > SP_ArrRegionObserveMap;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class handles defect collection on a remote card for the 
//automatic re-route purposes.
//##ModelId=38E35B0900D0
class SP_ArrDefectCollectorAction 
: public FC_Action
{
public:
	//Constructor.
    SP_ArrDefectCollectorAction(  
        SP_ReRouteConfigRegion& theConfigRegion,
		SP_ReRouteDefectRegion& theDefectRegion,
		T6100_CardIf& theCardContext);

    //Destructor.
    virtual ~SP_ArrDefectCollectorAction();

	//Not implemented.
    virtual void Run( FC_Object* theObject = NULL );

	//This method processes defects and fills in defect region
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Forces the defect collecting to start if it was 
	//stopped(debug).
    inline void Start();
	//Forces the defect collecting processing to stop (debug).
    inline void Stop();

    FC_BbAction* GetBbAction() { return myBbAction; }
	SP_ArrPortDefectCollectorDataCollection& GetPortDefectCollectorData() {return myPortDataCollectionSet;}

	void AddToPortDefectCollector(CT_IntfId thePortId);
    void UpdateOduDefectCollector(CT_IntfId thePortId, bool theAdd);
	void ConfigureBbActionInputs(bool addRegions);
	void MonitorDefects();
	void MonitorDefectsOnPort(SP_ArrPortDefectCollectorData* thePortData, bool theMonitor);

	//inline void SetConfigAction(SP_ArrDefectCollectorConfigAction* theConfigAction);

protected:
	//Reference to the config and defects regions.
    SP_ReRouteConfigRegion& myConfigRegion;
    SP_ReRouteDefectRegion& myDefectsRegion;


	//The card context I am running in
	T6100_CardIf& myCardContext;

	//True if processing is stop (debug).
    bool stopped;

private:
	SP_ArrPortDefectCollectorDataCollection myPortDataCollectionSet;
    SP_ArrOduDefectCollectorDataCollection myOduDataCollectionSet;
    FC_BbAction* myBbAction;
	SP_ArrDefectCollectorConfigAction* myConfigAction;
	SP_ArrDefectList myDefectList;
	//CSM region
    CSM_CardConfigStatusRegion* myCsmRegion;
    vector<uint32>* myOdukIdentifierList;
    SP_ArrRegionObserveMap myRegionObserveMap;
    bool myPendingUpdate;

    //Helper functions
    bool ProcessPortDefects();
    bool ProcessOduDefects();
    MON_Region* FindOduk(uint32 theOduIdentifier, int* theLayerIdx);
    CT_IntfId GetOduKPort(uint32 theOduIdentifier);
    void MonitorDefectsOnOdu();
    void ManageOduInputRegions(uint32 theOduIdentifier, bool addInput, bool removeInput);
    bool InternalSystemDefectPresent(SP_ArrPortDefectCollectorData* theDataCollectorData);
};

inline void SP_ArrDefectCollectorAction::Start() { stopped = false; }
inline void SP_ArrDefectCollectorAction::Stop() { stopped = true; }
//inline void SP_ArrDefectCollectorAction::SetConfigAction(SP_ArrDefectCollectorConfigAction* theConfigAction) { myConfigAction = theConfigAction; }

/////////////////////////////////////////////////////////////////////////////////////////////////
//This helper action is responsible for configuring the defect collector
class SP_ArrDefectCollectorConfigAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_ArrDefectCollectorConfigAction( SP_ArrDefectCollectorAction* theDefectCollector,
		                               SP_ReRouteConfigRegion& theConfigRegion);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_ArrDefectCollectorConfigAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles config request coming from the 
	//admin. 
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

	SP_ArrDefectCollectorAction* myDefectCollector;
	FC_BbAction* myBbAction;
	SP_ReRouteConfigRegion& myConfigRegion;
};




#endif /* _INC_SP_ARRDEFECTCOLLECTORACTION_38E35B0900D0_INCLUDED */
