// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_MsAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_Ms.h"
#include "../CFG_MsAutomatic.h"
#include "../CFG_SyncProt.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>

CFG_MsAutomaticAction::CFG_MsAutomaticAction(CFG_AppIf& theCfgIf,
                                             CFG_AppIf* theSyncCfgApp,
                                             CT_IntfId  theIntfId):
    CFG_HwRefreshAction(theCfgIf),
    mySyncCfgApp(theSyncCfgApp),
    myIntfId(theIntfId)
{
    // register about config changes or defect changes
    if (mySyncCfgApp) 
    {
        GetBbAction()->AddInputRegion(mySyncCfgApp->GetProtCfgRegion());
    }
    
  	GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_MsAutomaticAction::~CFG_MsAutomaticAction()
{
    if (mySyncCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(mySyncCfgApp->GetProtCfgRegion());
    }

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_MsAutomaticAction::Process(unsigned theRunReason,
                                          FC_Object* theInvokerObj,
                                          FC_Object* theParam)
{
    bool         aIsActiveRef    = false;
    CT_FAC_RxSsm aSelectedRefSSM = CT_TEL_SUPPORTED_DEFAULT_SSM;

    CFG_MsAutomatic& aAutomaticCfgObject  = static_cast<CFG_MsAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]); 

    if (mySyncCfgApp) 
    {   
        CFG_SyncProt& aSyncProtConfig = static_cast<CFG_SyncProt&>((*mySyncCfgApp->GetProtCfgRegion())[0]);
 
        aIsActiveRef    = (aSyncProtConfig.GetActiveRefId() == myIntfId); 
        aSelectedRefSSM = aSyncProtConfig.GetSelectedRefSSM();
    }

    // Update automatic config object
    aAutomaticCfgObject.SetIsActiveRef(aIsActiveRef);
    aAutomaticCfgObject.SetSelectedRefSSM(aSelectedRefSSM);

    GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();

    return NULL;
}
