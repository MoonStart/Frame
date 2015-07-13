// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_GfpProtAction.h"
#include <ErrorService/FC_Error.h>
#include "../CFG_AppIf.h"
#include "../CFG_GfpProt.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>
#include <TsPii/TSPII_GfpIf.h>

CFG_GfpProtAction::CFG_GfpProtAction(CFG_AppIf& theCfgIf,
                                     TSPII_GfpRegion& theGfpPiiRegion) :

    CFG_HwRefreshAction(theCfgIf),
    myWakeUpAction(NULL),
    myProcess(NULL),
    myGfpPiiRegion(theGfpPiiRegion)
{
    // register for changes in GFP protection configuration
    myProcess      = new FC_OneShotProcess(*GetBbAction(), gHighDispatcher);
    myWakeUpAction = new FC_WakeUpProcessAction(*myProcess);

    CFG_Region* theProtCfgRegion = theCfgIf.GetProtCfgRegion();
    if (theProtCfgRegion)
    {
        theProtCfgRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theProtCfgRegion);
    }
}

CFG_GfpProtAction::~CFG_GfpProtAction()
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


FC_Object* CFG_GfpProtAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    /*
    bool aLinkFailTx = false;
    CFG_GfpProt& aProtCfgObject   = static_cast<CFG_GfpProt&>((*GetCfgIf().GetProtCfgRegion())[0]);
    TSPII_GfpIf& aGfpPiiObject = myGfpPiiRegion[0];

    // Hardware Refresh will force Link Fail Tx (CR0) to the router.
    if(aProtCfgObject.GetForceLinkFailTx())
    {
        //Force Link Fail TX (CR0)
        aLinkFailTx = true;
    }
    else
    {
        //No fault to be set.
        aLinkFailTx = false;
    }
    */
    return NULL;
}
