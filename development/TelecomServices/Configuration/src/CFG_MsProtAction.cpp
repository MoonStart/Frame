// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_MsProtAction.h"
#include <ErrorService/FC_Error.h>
#include "../CFG_AppIf.h"
#include "../CFG_MsProt.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>
#include <TsPii/TSPII_MsIf.h>

CFG_MsProtAction::CFG_MsProtAction(CFG_AppIf& theCfgIf,
                                   TSPII_MsRegion& theMsPiiRegion) : 
                                            
    CFG_HwRefreshAction(theCfgIf),
	myWakeUpAction(NULL),
	myProcess(NULL),
    myMsPiiRegion(theMsPiiRegion)
{
    // register for changes in MS protection configuration
	myProcess      = new FC_OneShotProcess(*GetBbAction(), gHighDispatcher);
	myWakeUpAction = new FC_WakeUpProcessAction(*myProcess);
    
    CFG_Region* theProtCfgRegion = theCfgIf.GetProtCfgRegion();
    if (theProtCfgRegion) 
    {
        theProtCfgRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theProtCfgRegion);  
    }
}

CFG_MsProtAction::~CFG_MsProtAction()
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


FC_Object* CFG_MsProtAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_MsProt& aProtCfgObject   = static_cast<CFG_MsProt&>((*GetCfgIf().GetProtCfgRegion())[0]); 
    TSPII_MsIf& aMsPiiObject = myMsPiiRegion[0];

    // Configure K1 and K2 bytes
    aMsPiiObject.SetK1TxByte(aProtCfgObject.GetEgressK1Value());
    aMsPiiObject.SetK2TxByte(aProtCfgObject.GetEgressK2Value());

    aMsPiiObject.SetTxCsi(aProtCfgObject.GetEgressCsi());

    return NULL;
}
