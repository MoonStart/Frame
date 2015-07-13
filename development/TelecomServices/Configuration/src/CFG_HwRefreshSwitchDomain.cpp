// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_SwitchIf.h>
#include "../CFG_HwRefreshSwitchDomain.h"
#include "../CFG_SwitchDomain.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_CardInventory.h>
#include <CommonTypes/CT_SwitchDomainMap.h>
#include <CsPii/CSPII_CardIF.h>
#include <CsPii/CSPII_SysCfgParamIF.h>

CFG_HwRefreshSwitchDomain::CFG_HwRefreshSwitchDomain(CFG_SwitchDomainSubApplication& theSubApp,
                                                     TSPII_SwitchRegion* theSwitchPiiRegion)
:mySubApp(theSubApp)
,myBbAction(NULL)
,mySwitchPiiRegion(theSwitchPiiRegion)
{
    // create BB action
    myBbAction =  new FC_BbAction(this);
    myBbAction->AddInputRegion(mySubApp.GetCfgRegion());
    myBbAction->AddOutputRegion(mySubApp.GetOutputCfgRegion());
    myCardFamily = CSPII_CardIF::GetInstance()->GetCardFamily();
}


CFG_HwRefreshSwitchDomain::~CFG_HwRefreshSwitchDomain()
{
    myBbAction->RemoveInputRegion(mySubApp.GetCfgRegion());
    myBbAction->RemoveOutputRegion(mySubApp.GetOutputCfgRegion());
    delete myBbAction;
}

FC_Object* CFG_HwRefreshSwitchDomain::DoRunWithReason(unsigned theRunReason,
                                                FC_Object* theInvokerObj,
                                                FC_Object* theParam)
{
    CFG_SwitchDomain& aCfgObject = static_cast<CFG_SwitchDomain&>((*mySubApp.GetCfgRegion())[0]);

    if (mySwitchPiiRegion != NULL)
    {
        TSPII_SwitchIf& aSwitchDomainPiiObject = (*mySwitchPiiRegion)[0];

        // retrieve our relative information
        CT_ShelfId aShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
        CT_SlotId aSlotId = CSPII_CardIF::GetInstance()->GetSlotId();
        CT_SubCardType aSubCardtype = CSPII_CardIF::GetInstance()->GetSubCardType();

        //Set the switch mode for this card
        CT_TEL_SwitchMode aSwitchMode = aCfgObject.GetSwitchMode(aSlotId);
        aSwitchDomainPiiObject.SetSwitchMode(aSwitchMode);

        //-- Set the OSI Port assignment
        for(CT_SlotId aSubSlot = 1; aSubSlot <= MAX_NUM_CXP_ON_UFABC; aSubSlot++)
        {
            CT_ShelfId aMappedShelfId = aCfgObject.GetLinkMap(aSlotId, aSubSlot).GetShelfId();
            aSwitchDomainPiiObject.SetOsiPortAssignment(aSubSlot, aMappedShelfId);
        }

        //-- Set the link enable status
        CT_SlotId aEndSubSlot = 0;
        if(aSubCardtype == UFAB_O)
        {
            aEndSubSlot = MAX_NUM_CXP_ON_UFABO;
        }
        else if(aSubCardtype == UFAB_C)
        {
            aEndSubSlot = MAX_NUM_CXP_ON_UFABC;

            //-- Set the card status for the CSS shelf.
            for(uint8 aSlotIdx = UFAB_C_FIRST; aSlotIdx <= UFAB_C_LAST; aSlotIdx+=2)
            {
                // This loops through all ufab slots on the switchshelf
                bool bSlotStatus = aCfgObject.GetCardOperState(aSlotIdx);
                aSwitchDomainPiiObject.SetSlotEnabled(aSlotIdx-1, bSlotStatus);
            }

        }
        for(CT_SlotId aSubSlot = 1; aSubSlot <= aEndSubSlot; aSubSlot++)
        {
            bool bLinkStat = aCfgObject.GetLinkOperState(aSlotId, aSubSlot);
            aSwitchDomainPiiObject.SetOsiEnabled((uint8)aSubSlot, bLinkStat);

            CT_CableLength aCableLength = CT_CABLELENGTH_UNKNOWN;

            aSwitchDomainPiiObject.SetCableLength(aSubSlot, aCfgObject.GetCableLength(aSlotId, aSubSlot));
            aSwitchDomainPiiObject.SetOtherSideHwRev(aSubSlot, aCfgObject.GetRemoteHwRev(aSlotId, aSubSlot));
        }
    }

    mySubApp.GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}


