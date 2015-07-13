// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_SyncProtAction.h"
#include <ErrorService/FC_Error.h>
#include "../CFG_AppIf.h"
#include "../CFG_SyncProt.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>
#include <TsPii/TSPII_ClkSelIf.h>

CFG_SyncProtAction::CFG_SyncProtAction(CFG_AppIf& theCfgIf,
                                      TSPII_ClkSelRegion& theSyncPiiRegion) : 
                                            
    CFG_HwRefreshAction(theCfgIf),
	myWakeUpAction(NULL),
	myProcess(NULL),
    mySyncPiiRegion(theSyncPiiRegion)
{
    // register for changes in SYNC protection configuration
	myProcess      = new FC_OneShotProcess(*GetBbAction(), gHighDispatcher);
	myWakeUpAction = new FC_WakeUpProcessAction(*myProcess);
    
    CFG_Region* theProtCfgRegion = theCfgIf.GetProtCfgRegion();
    if (theProtCfgRegion) 
    {
        theProtCfgRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theProtCfgRegion);  
    }
}

CFG_SyncProtAction::~CFG_SyncProtAction()
{
    // Remove my action from the protection configuration observers list
	
    CFG_Region* theProtCfgRegion = GetCfgIf().GetProtCfgRegion();
    if (theProtCfgRegion) 
	{
        theProtCfgRegion->RemoveObserver(myWakeUpAction);
		delete myWakeUpAction;
		delete myProcess;
	}
}


FC_Object* CFG_SyncProtAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_SyncProt& aProtCfgObject   = static_cast<CFG_SyncProt&>((*GetCfgIf().GetProtCfgRegion())[0]); 
    TSPII_ClkSelIf& aSyncPiiObject = mySyncPiiRegion[0];

    // Configure timing reference selection
    aSyncPiiObject.SetSelectedRef(aProtCfgObject.GetTimingReference());

    return NULL;
}
