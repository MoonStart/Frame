// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_Dispatcher.h>
#include "../SP_ProtectionAction.h"
#include "../SP_ProtectionGroupStatus.h"
#include "../SP_ProtectionGroupStatusRegion.h"
#include "../SP_Definitions.h"
#include "../SP_StatusCollectionAction.h"
#include "SP_Application.h"
#include "../SP_ProtectionGroupConfig.h"



//##ModelId=3B8BC9BD0153
FC_Stream*  SP_ProtectionAction::mySnapshotFCStream[SP_MAX_SNAPSHOT]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//##ModelId=3B8BC9BD013F
ostrstream* SP_ProtectionAction::mySnapshotStrstream[SP_MAX_SNAPSHOT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//##ModelId=38FB0962028D
SP_ProtectionAction::SP_ProtectionAction(SP_Application& theApplIf) :
    myLowPriorityProcess(NULL),
    myHighPriorityProcess(NULL),
    myLowPriorityCallbackAction(NULL),
    myHighPriorityCallbackAction(NULL),
    stopped(false),
	myEnabledStatus(false),
	myOperationStatus(false),
    myBbAction(NULL),
    myApplIf(theApplIf)
{
    myBbAction = new FC_BbAction(this);

    myLowPriorityProcess = new FC_OneShotProcess(*myBbAction, gLowDispatcher);
    myLowPriorityCallbackAction = new SP_WakeUpProcessAction(*myLowPriorityProcess);
    myHighPriorityProcess = new FC_OneShotProcess(*myBbAction, gHighDispatcher);
    myHighPriorityCallbackAction = new SP_WakeUpProcessAction(*myHighPriorityProcess);
}

//##ModelId=38FB096202DE
SP_ProtectionAction::~SP_ProtectionAction()
{
    delete myLowPriorityProcess;
    delete myLowPriorityCallbackAction;
    delete myHighPriorityProcess;
    delete myHighPriorityCallbackAction;
    delete myBbAction;
}

//##ModelId=3B8BC9BF007A
void SP_ProtectionAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3B8BC9BE01CD
FC_Stream& SP_ProtectionAction::SnapshotWrite(FC_Stream& theStream)
{
	return theStream;
}

//##ModelId=3B8BC9BD0276
void SP_ProtectionAction::Log(const string& theGroupType, 
                              unsigned theReason, 
                              FC_Object* theInvoker, 
                              FC_Object* theParam)
{

    switch (theReason)
    {
    case SP_SWITCHING_COMMAND_REASON:           fc_cout << "Switching command"; break;
    case SP_SWITCHING_COMMAND_REASON_IMMEDIAT:  fc_cout << "Immediat switching command"; break;
    case SP_DEFECT_GLITCH_REASON:               fc_cout << "Defect glitch"; break;
    case SP_CONFIG_REFRESH_REASON:              fc_cout << "Config refresh"; break;
    case SP_CONFIG_REFRESH_REASON_IMMEDIAT:     fc_cout << "Immediat config refresh"; break;
    case SP_SYNCHRONIZATION_REASON:             fc_cout << "Synchronization"; break;
    default: fc_cout << "reason 0x" << hex << theReason; 
    }
    fc_cout << " from 0x" << hex << (int)theInvoker;
    fc_cout << " with param 0x" << hex << (int) theParam;

    fc_cout << endl;

}


void SP_ProtectionAction::UpdateUsage()
{

}

void SP_ProtectionAction::ApplyConfiguration()
{
	//run the protection action to apply changes to configuration
    GetLowPriorityWakeUpAction().RunWithReason(SP_CONFIG_REFRESH_REASON, this);
}

void SP_ProtectionAction::RegisterSpecificObservers(SP_DefectProcessorAction* theDefectProcessor)
{
	//Default no implementation
}

void SP_ProtectionAction::UnregisterSpecificObservers(SP_DefectProcessorAction* theDefectProcessor)
{
	//Default no implementation
}

bool SP_ProtectionAction::GetSpecificSFDefects(CT_SP_Protection theSide, CT_IntfId theIntfId, uint32* theCount, bool* theState)
{
	//Default no implementation
	return true;
}

bool SP_ProtectionAction::GetSpecificSFLowDefects(CT_SP_Protection theSide, CT_IntfId theIntfId, uint32* theCount, bool* theState)
{
	//Default no implementation
	return true;
}

bool SP_ProtectionAction::GetSpecificSDDefects(CT_SP_Protection theSide, CT_IntfId theIntfId, uint32* theCount, bool* theState)
{
	//Default no implementation
	return true;
}

bool SP_ProtectionAction::IsResourceReady(SP_ProtectionGroupConfig& theConfig)
{
	//Default: Always ready
	return true;
}

bool SP_ProtectionAction::IsSsmSwitchingAllowed()
{
	//Default: Always allowed
	return true;
}

bool SP_ProtectionAction::IsConfigurationAllowed(SP_ProtectionGroupConfig& theConfig)
{
    return true;
}

void SP_ProtectionAction::DisableBase()
{
    //Default no implementation
}

//##ModelId=3BBC9B040164
const char* SP_ProtectionAction::SP_WakeUpProcessAction::ourInstanceName = "SP_ProtectionAction";
//##ModelId=3BBC9B04015A
const char* SP_ProtectionAction::SP_WakeUpProcessAction::GetInstanceName(void ) const 
	{ return ourInstanceName; }

