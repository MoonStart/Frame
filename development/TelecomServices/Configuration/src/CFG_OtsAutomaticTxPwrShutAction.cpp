// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_OtsAutomaticTxPwrShutAction.h"
#include "../CFG_AtpsFsm.h"
#include "../CFG_AppIf.h"
#include "../CFG_Ots.h"
#include "../CFG_OtsAutomaticTxPwrShut.h"
#include <ErrorService/FC_Error.h>
#include <T6100_Dispatcher.h>
#include <Blackboard/FC_BbAction.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>


CFG_OtsAutomaticTxPwrShutAction::CFG_OtsAutomaticTxPwrShutAction(CFG_AppIf& theCfgIf,
                                                                 CFG_OtsAutomaticTxPwrShutRegion& theAutomaticTxPwrShutRegion,
                                                                 ALM_AppIf& theOtsOHAlmIf,
                                                                 ALM_AppIf& theOtsAlmIf):
    CFG_HwRefreshAction(theCfgIf),
    myAutomaticTxPwrShutRegion(theAutomaticTxPwrShutRegion),
    myOtsOHAlmIf(theOtsOHAlmIf),
    myOtsAlmIf(theOtsAlmIf),
    myAtpsFsm(NULL)
{
    //Create Atps state machine
    myAtpsFsm = new CFG_AtpsFsm(*this);

    //Register config region as output
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());

    // Register for OSC failure
    GetBbAction()->AddInputRegion(myOtsOHAlmIf.GetFilteredRegionPtr());
    GetBbAction()->AddInputRegion(myOtsAlmIf.GetFilteredRegionPtr());

    // Register automatic region as output 
	GetBbAction()->AddOutputRegion(&myAutomaticTxPwrShutRegion, false);
}

CFG_OtsAutomaticTxPwrShutAction::~CFG_OtsAutomaticTxPwrShutAction()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
	GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
    GetBbAction()->RemoveInputRegion(myOtsOHAlmIf.GetFilteredRegionPtr());
    GetBbAction()->RemoveInputRegion(myOtsAlmIf.GetFilteredRegionPtr());

    delete myAtpsFsm;
}


FC_Object* CFG_OtsAutomaticTxPwrShutAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    bool hasChanged = false;
    CFG_Ots& aOtsConfig   = static_cast<CFG_Ots&>((*GetCfgIf().GetCfgRegion())[0]);
    CFG_OtsAutomaticTxPwrShut& aAutomaticTxPwrShut = myAutomaticTxPwrShutRegion[0];


    // ATPS: check if we are on OAM/OLIM(out) and check if ATPS is active
    bool anAtpsActive = false;
    if (aOtsConfig.GetCatpsEnable())
    {
        myAtpsFsm->Enable();
        anAtpsActive |= myAtpsFsm->IsShutdownActive();
    }
    else
        myAtpsFsm->Disable();

    // Update the CFG_OmsAutomaticCfg
    hasChanged |= aAutomaticTxPwrShut.SetAtpsActive(anAtpsActive);

    if (hasChanged)
    {
        myAutomaticTxPwrShutRegion.IncModificationCounter();
    }

    return NULL;
}


void CFG_OtsAutomaticTxPwrShutAction::Display(FC_Stream& theStream)
{
    myAtpsFsm->Display(theStream);
}