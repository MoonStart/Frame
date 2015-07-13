// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_MacAutomaticAction.h"
#include <CommonTypes/CT_Port.h>
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_Mac.h"
#include "../CFG_Evc.h"
#include "../CFG_Opt.h"
#include "../CFG_EvcAutomatic.h"
#include "../CFG_MacAutomatic.h"
#include <Monitoring/MON_GfpDefects.h>
#include <Monitoring/MON_MacDefects.h>
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>

CFG_MacAutomaticAction::CFG_MacAutomaticAction(CFG_AppIf& theCfgIf,
                                               //MON_AppIf* theMacMonApp,
                                               MON_AppIf* theGfpMonApp,
                                               CFG_AppIf* theOptCfgApp,
                                               CFG_AppIf* theEvcCfgApp,
                                               CT_IntfId  theIntfId) :
    CFG_HwRefreshAction(theCfgIf),
    //myMacMonApp(theMacMonApp),
    myGfpMonApp(theGfpMonApp),
    myOptCfgApp(theOptCfgApp),
    myEvcCfgApp(theEvcCfgApp),
	myIntfId(theIntfId),
	myWakeUpAction(NULL),
	myProcess(NULL)
{	 
        	
    GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());

    // register about config changes or defect changes
    if (myOptCfgApp)
	{
        GetBbAction()->AddInputRegion(myOptCfgApp->GetCfgRegion());
	}

    /*if (myMacMonApp) 
    {
        GetBbAction()->AddInputRegion(myMacMonApp->GetDefectsRegion());
    } */ 
  	
    if (myEvcCfgApp)
    {   
        GetBbAction()->AddInputRegion(myEvcCfgApp->GetAutomaticCfgRegion());
    }
    
    if (myGfpMonApp) 
    {
        GetBbAction()->AddInputRegion(myGfpMonApp->GetDefectsRegion());
    }

    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());

}

CFG_MacAutomaticAction::~CFG_MacAutomaticAction()
{

	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());

	/*if (myMacMonApp)
	{
		GetBbAction()->RemoveInputRegion(myMacMonApp->GetDefectsRegion());
	}*/
    if (myGfpMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myGfpMonApp->GetDefectsRegion());
    }        
    if (myEvcCfgApp)
    {                    
        GetBbAction()->RemoveInputRegion(myEvcCfgApp->GetAutomaticCfgRegion());
    }
    
    if (myOptCfgApp)
	{
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetCfgRegion());
	}

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_MacAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{
        
    bool aForceRemoteFault    = false;
    bool aForceFefi           = false;
    uint8 aGfpIdx             = CT_TEL_INVALID_VCG_IDX;
    uint32 aDefectCount       = 0L;
    bool aDefectState         = false;
    //MON_Region* aMacMonRegion = NULL;
    MON_Region* aGfpMonRegion = NULL;
    CFG_Region* aOptCfgRegion = NULL;   
    
    CFG_MacAutomatic& aAutomaticCfgObject   = static_cast<CFG_MacAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]); 
    CFG_Mac& aCfgObject = static_cast<CFG_Mac&>((*GetCfgIf().GetCfgRegion())[0]);

    /*
    if (myEvcCfgApp)
    {
        CFG_EvcAutomatic& aEvcAutoConfig = static_cast<CFG_EvcAutomatic&>((*myEvcCfgApp->GetAutomaticCfgRegion())[0]);
        aGfpIdx = aEvcAutoConfig.GetGfpIdx(myIntfId);     
    
        //if (myMacMonApp) 
        //{
        //    aMacMonRegion = myMacMonApp->GetDefectsRegion();
        //}
    
        if (myGfpMonApp)
        {
            aGfpMonRegion = myGfpMonApp->GetDefectsRegion();
        }       
        
        if (myOptCfgApp)
        {
            aOptCfgRegion = myOptCfgApp->GetCfgRegion();
        }
        
        CFG_Opt& aOptCfgObject = static_cast<CFG_Opt&>((*aOptCfgRegion)[0]);
        
        bool aPrbsEnabled = false;
        if (aOptCfgObject.GetPrbsRxEnable() || aOptCfgObject.GetPrbsTxEnable())
        {
            aPrbsEnabled = true;
        }

        
        if ((aGfpMonRegion) && (aGfpIdx != CT_TEL_INVALID_VCG_IDX) && (!aOptCfgObject.GetFacilityLoopBackEnable()) && (!aPrbsEnabled))
        {
            if (aGfpMonRegion->IsValid()) 
            {
                                    
                MON_Defects& aGfpMonObject = static_cast<MON_Defects&>((*aGfpMonRegion)[aGfpIdx]);
                
                if (aCfgObject.GetPropFefiEnabled())
                {
                    // Check CSF FEFI to force FEFI
                    //aGfpMonObject.GetDefectStatus(CT_TEL_GFP_CSF_FEFI_DEFECT, &aDefectCount, &aDefectState);
                    //aForceFefi = aDefectState;
                    //aAutomaticCfgObject.SetFefiEnabled(aForceFefi); 
                    //aAutomaticCfgObject.SetRemoteFaultForced(false);
                }
                else
                {
                   // aAutomaticCfgObject.SetFefiEnabled(false);
                   // if (aCfgObject.GetAutoNeg())
                   // {
                   //     aGfpMonObject.GetDefectStatus(CT_TEL_GFP_CSF_LOS_DEFECT, &aDefectCount, &aDefectState);
                   //     aForceRemoteFault = aDefectState;
                   //     aAutomaticCfgObject.SetRemoteFaultForced(aForceRemoteFault);
                   // }
                   // else
                   //     aAutomaticCfgObject.SetRemoteFaultForced(false);
                }

            }
        }
        else
            //aAutomaticCfgObject.SetFefiEnabled(false);
    }
    else
    {
        //aAutomaticCfgObject.SetRemoteFaultForced(false);
        //aAutomaticCfgObject.SetFefiEnabled(false);
    }            
    //GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    */

    return NULL;
}
