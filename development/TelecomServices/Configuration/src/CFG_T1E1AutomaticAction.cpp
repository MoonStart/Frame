// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_T1E1AutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_T1E1.h"
#include "../CFG_T1E1Automatic.h"
#include "../CFG_Opt.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>

CFG_T1E1AutomaticAction::CFG_T1E1AutomaticAction(CFG_AppIf& theCfgIf,
                                                 MON_AppIf* theT1E1MonApp):
    CFG_HwRefreshAction(theCfgIf),
    myT1E1MonApp(theT1E1MonApp)
{
    // register about config changes or defect changes
    if (myT1E1MonApp) 
    {
        GetBbAction()->AddInputRegion(myT1E1MonApp->GetDefectsRegion());
    }
    
  	GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_T1E1AutomaticAction::~CFG_T1E1AutomaticAction()
{
    if (myT1E1MonApp) 
    {
        GetBbAction()->RemoveInputRegion(myT1E1MonApp->GetDefectsRegion());
    }

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_T1E1AutomaticAction::Process(unsigned theRunReason,
                                            FC_Object* theInvokerObj,
                                            FC_Object* theParam)
{
    bool aDisqualifyRef = false;

    CFG_T1E1Automatic& aAutomaticCfgObject  = static_cast<CFG_T1E1Automatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]); 

    if (myT1E1MonApp) 
    {   
        MON_Defects& aT1E1Defects = static_cast<MON_Defects&>((*myT1E1MonApp->GetDefectsRegion())[0]);

        // For now, disqualify reference if the layer is locked.
        // Later, if defects should be considered, then use:
        //         aT1E1Defects.IsLayerInDefects();
        aDisqualifyRef = aT1E1Defects.IsLayerLocked(); 
    }

    // Update automatic config object
    aAutomaticCfgObject.SetDisqualifyRef(aDisqualifyRef);

    GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();

    return NULL;
}
