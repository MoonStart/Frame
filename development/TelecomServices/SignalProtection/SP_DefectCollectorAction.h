// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_DEFECTCOLLECTORACTION_38E35B0900D0_INCLUDED
#define _INC_SP_DEFECTCOLLECTORACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include "SP_Definitions.h"
#include <CommonTypes/CT_FacilityIds.h>
#include <vector>


class SP_Defect;
class FC_BbAction;
class T6100_CardIf;
class MON_Region;
class SP_DefectCollectorConfigAction;
class CFG_Region;

#define SP_INVALID_ODU_POOL_IDX -1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class implements an instance of a data container for the defect collector action
class SP_DefectCollectorData
{
public:
    SP_DefectCollectorData(CT_IntfId thePortId, uint8 theDefectObjIndex, MON_Region* theMonOptRegion, MON_Region* theMonOtuRegion, MON_Region* theMonOduRegion);
    virtual ~SP_DefectCollectorData();

	//All these functions are defined inline for performance reasons as they are used during protection switching
    inline void SetOptLosCount(uint32 theOptLosCount);
	inline uint32 GetOptLosCount();
	inline MON_Region* GetOduRegion();
	inline MON_Region* GetOtuRegion();
	inline MON_Region* GetOptRegion();
	inline MON_Region* GetOduPoolRegion();
	inline void SetOduPoolRegion (MON_Region* theOduPoolRegion);
	inline uint8 GetDefectObjIndex();
	inline CT_IntfId GetPortId();
	inline void SetOduPoolIndex(int theOduPoolIndex);
	inline int GetOduPoolIndex();

private:
    //MON regions that this action is collecting defects from
	MON_Region* myMonOduRegion;
	MON_Region* myMonOtuRegion;
	MON_Region* myMonOptRegion;
	MON_Region* myMonOduPoolRegion;
	uint32 myOptLosCount;
	uint8 myDefectObjIndex;
	int myOduPoolIndex;
	CT_IntfId myPortId;
};

inline void SP_DefectCollectorData::SetOptLosCount(uint32 theOptLosCount)       { myOptLosCount = theOptLosCount; }
inline uint32 SP_DefectCollectorData::GetOptLosCount()                          { return  myOptLosCount; }
inline MON_Region* SP_DefectCollectorData::GetOduRegion()                       { return myMonOduRegion; }
inline MON_Region* SP_DefectCollectorData::GetOtuRegion()                       { return myMonOtuRegion; }
inline MON_Region* SP_DefectCollectorData::GetOptRegion()                       { return myMonOptRegion; }
inline MON_Region* SP_DefectCollectorData::GetOduPoolRegion()                   { return myMonOduPoolRegion; }
inline void SP_DefectCollectorData::SetOduPoolRegion (MON_Region* theOduPoolRegion) { myMonOduPoolRegion = theOduPoolRegion; }
inline uint8 SP_DefectCollectorData::GetDefectObjIndex()                        { return  myDefectObjIndex; }
inline CT_IntfId SP_DefectCollectorData::GetPortId()                            { return  myPortId; }
inline void SP_DefectCollectorData::SetOduPoolIndex(int theOduPoolIndex)        { myOduPoolIndex = theOduPoolIndex; }
inline int SP_DefectCollectorData::GetOduPoolIndex()                            { return myOduPoolIndex;}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class handles defect collection on a remote card for the 
//protection actions.
//##ModelId=38E35B0900D0
class SP_DefectCollectorAction 
: public FC_Action
{
public:
	//Constructor. Requires defects region.
    //##ModelId=3BBC9B0F02A0
    SP_DefectCollectorAction(  
        TEL_BbRegionBaseImp<SP_Defects>& theDefectsRegion,
		T6100_CardIf& theCardContext);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_DefectCollectorAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles switching request coming from the 
	//admin. It also updates the command results once the 
	//command is completed.
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Forces the defect collecting to start if it was 
	//stopped(debug).
    //##ModelId=39ACEFB00072
    inline void Start();
	//Forces the defect collecting processing to stop (debug).
    //##ModelId=39ACEFB0005E
    inline void Stop();

    FC_BbAction* GetBbAction() { return myBbAction; }

	void AddToDefectCollector(CT_IntfId thePortId, bool oduIsPooled);
	void AddOduPoolToDefectCollector(CT_IntfId thePortId, uint8 numOfPooledOdu);
	void ConfigureOduPoolData();
	inline void SetConfigAction(SP_DefectCollectorConfigAction* theConfigAction);

protected:
	//Reference to the defects region.
    //##ModelId=394102B8010F
    TEL_BbRegionBaseImp<SP_Defects>& myDefectsRegion;

	//The card context I am running in
	T6100_CardIf& myCardContext;

	//True if processing is stop (debug).
    //##ModelId=39ACEFB0002C
    bool stopped;

private:
	typedef vector<SP_DefectCollectorData*> SP_DefectCollectorDataCollection;
	SP_DefectCollectorDataCollection myDataCollectionSet;
    FC_BbAction* myBbAction;
	CFG_Region* myCfgPoolOduRegion;
	uint8 myNumPooledOdu;
	SP_DefectCollectorConfigAction* myConfigAction;
};

inline void SP_DefectCollectorAction::Start() { stopped = false; }
inline void SP_DefectCollectorAction::Stop() { stopped = true; }
inline void SP_DefectCollectorAction::SetConfigAction(SP_DefectCollectorConfigAction* theConfigAction) { myConfigAction = theConfigAction; }

/////////////////////////////////////////////////////////////////////////////////////////////////
//This helper action is responsible for configuring the defect collector
class SP_DefectCollectorConfigAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_DefectCollectorConfigAction( SP_DefectCollectorAction* theDefectCollector);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_DefectCollectorConfigAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles config request coming from the 
	//admin. 
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	void ConfigureBbActionInputs(bool addRegions, CFG_Region* theCfgPoolOduRegion);

private:

	SP_DefectCollectorAction* myDefectCollector;
	FC_BbAction* myBbAction;
};




#endif /* _INC_SP_DEFECTCOLLECTORACTION_38E35B0900D0_INCLUDED */