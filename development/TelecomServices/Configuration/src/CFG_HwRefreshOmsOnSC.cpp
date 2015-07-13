// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_PipeIf.h>
#include "../CFG_HwRefreshOmsOnSC.h"
#include "../CFG_Oms.h"
#include "../CFG_OmsAutomaticShutdown.h"
#include "../CFG_CmmOosAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include "../CFG_OptAutomatic.h"
#include <T6100_MainAppIf.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <T6100_PortShelfIf.h>
#include <T6100_PortShelfSlotIf.h>
#include <T6100_OpticalShelfIf.h>
#include <T6100_OpticalShelfSlotIf.h>
#include <CsPii/CSPII_CardIF.h>

CFG_HwRefreshOmsOnSC::CFG_HwRefreshOmsOnSC(CFG_AppIf& theCfgIf,
                                   CFG_OmsAutomaticShutdownRegion& theAutomaticShutdownRegion,
                                   CFG_OptAutomaticCfgRegion* thePumpRegion):

    CFG_HwRefreshAction(theCfgIf),
    myPumpRegion(thePumpRegion),
    myAutomaticShutdownRegion(theAutomaticShutdownRegion),
    myCardConfigRegion(NULL)
{
    T6100_SlotIf *aSlotApp = NULL;
    GetBbAction()->AddInputRegion(&myAutomaticShutdownRegion);

    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    if (myPumpRegion) GetBbAction()->AddOutputRegion(myPumpRegion);

    T6100_MainAppIf& aMainApp = T6100_MainAppIf::Instance();
    CT_ShelfId aShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
    CT_SlotId  aSlotId  = (CT_SlotId)CSPII_CardIF::GetInstance()->GetSlotId();

    if(aShelfId == OPTICAL_SHELF_1 ||
       aShelfId == OPTICAL_SHELF_2)
    {
        T6100_ShelfIf *aShelfApp = &(aMainApp.GetOpticalShelf(aShelfId));
        aSlotApp = &(static_cast<T6100_OpticalShelfIf*>(aShelfApp)->GetOSSlotIf(aSlotId));
        myCardConfigRegion = &aSlotApp->GetCsmApp().GetCardConfigStatusRegion();
    }
    else
    {
        T6100_ShelfIf *aShelfApp = &(aMainApp.GetPortShelf(aShelfId));
        aSlotApp = &(static_cast<T6100_PortShelfIf*>(aShelfApp)->GetPSSlotIf(aSlotId));
        myCardConfigRegion = &aSlotApp->GetCsmApp().GetCardConfigStatusRegion();
    }
    if (myCardConfigRegion)
    {
        GetBbAction()->AddInputRegion(myCardConfigRegion);
    }
}


CFG_HwRefreshOmsOnSC::~CFG_HwRefreshOmsOnSC()
{
    GetBbAction()->RemoveInputRegion(&myAutomaticShutdownRegion);
   
    if (myPumpRegion)
    { 
        GetBbAction()->RemoveOutputRegion(myPumpRegion);
    }
    
    if (myCardConfigRegion)
    {
        GetBbAction()->RemoveInputRegion(myCardConfigRegion);
    }

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}


FC_Object* CFG_HwRefreshOmsOnSC::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_OmsAutomaticShutdown& aOmsAutomaticShutdown = myAutomaticShutdownRegion[0];
    CSM_PersistentConfigStatus&  aCSMCfg = (*myCardConfigRegion)[0];

    bool aAutoShutdownOrder = aOmsAutomaticShutdown.GetAmplifierShutdown();
    bool aAutoOosScOrder  = (aCSMCfg.GetAdministrativeConfig() == CARD_LOCK);
    

    // update state of pumps
    if (myPumpRegion)
    {
        bool hasChanged = false;
        CFG_OptAutomatic& aAutomaticCfgObject = static_cast<CFG_OptAutomatic&>((*myPumpRegion)[0]);
        hasChanged = aAutomaticCfgObject.SetAutomaticLaserShutdown(aAutoShutdownOrder || aAutoOosScOrder);
        if(hasChanged)
        {
            myPumpRegion->IncModificationCounter();
        }
    }

    
    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}

