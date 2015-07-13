/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     May 21, 2006  Larry M. Wolfrum.
 DESCRIPTION:   Action to populate a PM file image buffer.
--------------------------------------------------------------------------*/

#ifndef PM_FILEPOPULATIONACTION_H
#define PM_FILEPOPULATIONACTION_H

#include <vector>
#include <gdef.h>
#include <ExecutionSupport/FC_Action.h>
#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <CommonTypes/CT_PM_BinaryFileHandler.h>
#include <EPM/PM_SubApplicationRegistration.h>
#include <PM/PM_FileStorageSubApplication.h>

// Forward class declaration.
class FC_Object;
class FC_BbAction;
class PM_BinaryFileHandler;
class PM_FileNameHandle;

const int32 PM_FILE_ACTION_DELAY =        10;    // 10 msec. delay
const int32 PM_FILE_END_OF_PERIOD_DELAY	= 5000;  // 5 second delay
const int32 PM_FILE_INITIALIZATION_DELAY	= 1000;  // 1 second delay
const int32 PM_FILE_ITERATION_DELAY		= 1000;  // 1 second delay


class PM_FilePopulationAction: public FC_Action
{
public:

	typedef vector<PM_BinFileParamData> PM_ParamVector;

	enum PM_FileStorageActionState
	{
		PM_WAITING_FOR_END = 0,
		PM_END_DETECTED,
		PM_START_BUILDING,
		PM_BUILDING_FILE
	};

    //The Action's constructor.
	PM_FilePopulationAction(PM_FileStorageSubApplication& theContext, CT_PM_Period thePeriod, CT_PM_DataType theDataType);

    //The Collector's destructor.
    virtual ~PM_FilePopulationAction();

    // Entry point for doing work when trigger criterion are met.
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                       FC_Object* theInvokerObj,
                                       FC_Object* theParam= NULL);

    //Obsolete method
    virtual void Run(FC_Object* theObject = NULL);

	// Retrieve pointer to BbAction instance.
	FC_BbAction* GetBbAction();

	// Method to obtain the starting time of the current control period.
	FC_Time GetAccumulationPeriod(CT_PM_Period thePeriod);

	// Method to add the PM data for a facility to the file buffer.
	void AddDataToFile();

	// Method to get the parent port signaling type.
	CT_TEL_SignalType GetFacilitySignalType(bbindex_t channel = 0);

	// Method to get HOP mapping whether in SONET or SDH mode.
	void GetHopMapTrueSdh(CT_TEL_HopSpeMapping &stsHopMapping, CT_TEL_HopSpeMapping &vcHopMapping, uint8 &hopOffset) const;


    //For ODU to get the uplayer physical port

    uint16 GetUplayerPhysicalPort(CT_ODU_ServerID theServerID);

    //For ODU to get the uplayer Intermediated ODU id
    void GetUplayerIntermediateOdu(CT_ODU_Layer theOduLayer, CT_ODU_ServerID theServerID, CT_PM_IntermediateOduId &theOduId, CT_PM_IntermediateOduType &theOduType);

    //For ODUT to get the uplayer Intermediated ODU id
    uint16 GetUplayerIntermediateOduId(CT_ODU_Layer theOduLayer, CT_ODU_ServerID theServerID);

    //For ODU to get the Intermediated Level
    bool GetIntermediateLevel(T6100_TelecomIf& theOduApp, CT_ODU_ServerID theServerID);


private:

    //A reference to the generic application.
	PM_FileStorageSubApplication& myContext;

    //Pointer to the file population blackboard action.
    FC_BbAction* myBbAction;

    // State of the file storage action.
	PM_FileStorageActionState myState;

	// My accumulation period type.
	CT_PM_Period myPeriod;

	// Delay in milliseconds to next execution of action.
	int32 myDelay;

	// Iterator to scan the subapplication vector.
	vector<PM_SubApplicationRegistration*>::iterator mySubAppVecIt;

	// My file handler object.
	PM_BinaryFileHandler* myFileHandler;

	// Name of the file currently being created.
	PM_FileNameHandle* myFileNameHandle;
	
	// Count of entities inserted in file buffer.
	uint32 myEntityCount;

	// Vector containing the PM parameter data.
	PM_ParamVector myParamVector;

	char* myBuffer;

	// Count of facilities processed in state iteration.
	uint32 myFacilityCount;

	// Data type being handled by this action
	CT_PM_DataType myDataType;

	// Duplicate file count.
	uint32 myDuplicateFileCount;
};

class PM_PreviousRegionAction: public FC_Action
{
public:

    //The Action's constructor.
	PM_PreviousRegionAction(PM_FileStorageSubApplication& theContext, CT_PM_Period thePeriod, CT_PM_DataType theDataType);

    //The Collector's destructor.
    virtual ~PM_PreviousRegionAction();

    // Entry point for doing work when trigger criterion are met.
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                       FC_Object* theInvokerObj,
                                       FC_Object* theParam= NULL);

    //Obsolete method
    virtual void Run(FC_Object* theObject = NULL);

	// Retrieve pointer to BbAction instance.
	FC_BbAction* GetBbAction();

private:

    //A reference to the generic application.
	PM_FileStorageSubApplication& myContext;

	// My accumulation period type.
	CT_PM_Period myPeriod;

    //Pointer to the file population blackboard action.
    FC_BbAction* myBbAction;

    // My data type of file to be created.
    CT_PM_DataType myDataType;

};

#endif //PM_FILEPOPULATIONACTION_H

