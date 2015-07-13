// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SlotClockUsageConfigAction.h"
#include "../SP_Utilities.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_MainAppIf.h>
#include <T6100_ShelfIf.h>
#include <T6100_SlotIf.h>
#include <SignalProtection/SP_TimingModeRegion.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <CSM/CSM_ConfigStatus.h>
#include <SCFG/SCFG_AppIf.h>



///////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_SlotClockUsageConfigAction::SP_SlotClockUsageConfigAction(SP_TimingModeRegion& theTimingModeRegion, 
                                                             SCFG_ParamRegion* theSyncModeRegion,
                                                             CT_ShelfId theShelfId,
                                                             CT_SlotId theFirstSlot,
                                                             CT_SlotId theLastSlot):
	myTimingModeRegion(theTimingModeRegion),
    mySyncModeRegion(theSyncModeRegion),
    myShelfId(theShelfId),
    myFirstSlot(theFirstSlot),
    myLastSlot(theLastSlot)
{
    myBbAction = new FC_BbAction(this);

    T6100_ShelfIf* theShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(myShelfId);
    if (theShelfPtr)
    {
        for (CT_SlotId slot = theFirstSlot; slot<=theLastSlot;slot++)
        {
            T6100_SlotIf* theSlotPtr = theShelfPtr->GetSlotPtr(slot);
	        if (theSlotPtr)
		    {
		        CSM_CardConfigStatusRegion& theCsmRegion = theSlotPtr->GetCsmApp().GetCardConfigStatusRegion();
                myBbAction->AddInputRegion(&theCsmRegion, false);
            }
        }
    }
    myBbAction->AddInputRegion(mySyncModeRegion),
    myBbAction->AddOutputRegion(&myTimingModeRegion);
}

//##ModelId=38EDF51800A6
SP_SlotClockUsageConfigAction::~SP_SlotClockUsageConfigAction()
{
    T6100_ShelfIf* theShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(myShelfId);
    if (theShelfPtr)
    {
        for (CT_SlotId slot = myFirstSlot; slot<=myLastSlot;slot++)
        {
            T6100_SlotIf* theSlotPtr = theShelfPtr->GetSlotPtr(slot);
	        if (theSlotPtr)
		    {
		        CSM_CardConfigStatusRegion& theCsmRegion = theSlotPtr->GetCsmApp().GetCardConfigStatusRegion();
                myBbAction->RemoveInputRegion(&theCsmRegion);
            }
        }
    }
    
    myBbAction->RemoveOutputRegion(mySyncModeRegion);
	myBbAction->RemoveOutputRegion(&myTimingModeRegion);
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_SlotClockUsageConfigAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_SlotClockUsageConfigAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    T6100_ShelfIf* theShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(myShelfId);
    if (theShelfPtr)
    {
        for (CT_SlotId slot = myFirstSlot; slot<=myLastSlot;slot++)
        {
            T6100_SlotIf* theSlotPtr = theShelfPtr->GetSlotPtr(slot);
	        if (theSlotPtr)
		    {
		        CSM_CardConfigStatusRegion& theCsmRegion = theSlotPtr->GetCsmApp().GetCardConfigStatusRegion();
                if (theCsmRegion.IsValid())
                {
                    CSM_PersistentConfigStatus*  aCSMPtr = &(theCsmRegion[0]);

                    CT_CardFamily theCurCardFam = UNKNOWN_FAM;
                    if(aCSMPtr->IsCardProvisionned() == true)
			        {
		                list<CT_PartNumber>* aPnList = aCSMPtr->GetProvisionConfigList();
		                theCurCardFam = aPnList->front().GetCardFamily();
				    }

                    if (theCurCardFam != UNKNOWN_FAM)
                    {
                        if (theCurCardFam == SSM_FAM ||
                            theCurCardFam == SSM40_FAM ||
							theCurCardFam == FGSM_FAM)
                        {
                            if (myTimingModeRegion[slot-1].GetTimingMode() != CT_TEL_CLKMODE_SLAVE)
                            {
                                myTimingModeRegion[slot-1].SetTimingMode(CT_TEL_CLKMODE_SLAVE);
                                myTimingModeRegion.IncModificationCounter();
                            }                            
                        }
                        else if (theCurCardFam == CARD_FAM_CADM)
                        {
                            SCFG_ParamObject& theSyncMode = (*mySyncModeRegion)[0];
                            bool thruTiming = (theSyncMode.GetSyncOsc() == CT_SyncOsc_THRU);
                            if (thruTiming)
                            {
                                if (myTimingModeRegion[slot-1].GetTimingMode() != CT_TEL_CLKMODE_HOLDOVER)
                                {
                                    myTimingModeRegion[slot-1].SetTimingMode(CT_TEL_CLKMODE_HOLDOVER);
                                    myTimingModeRegion.IncModificationCounter();
                                }
                            }
                            else
                            {
                                if (myTimingModeRegion[slot-1].GetTimingMode() != CT_TEL_CLKMODE_SLAVE)
                                {
                                    myTimingModeRegion[slot-1].SetTimingMode(CT_TEL_CLKMODE_SLAVE);
                                    myTimingModeRegion.IncModificationCounter();
                                }
                            }
                        }
                        else
                        {
                            if (myTimingModeRegion[slot-1].GetTimingMode() != CT_TEL_CLKMODE_MASTER)
                            {
                                myTimingModeRegion[slot-1].SetTimingMode(CT_TEL_CLKMODE_MASTER);
                                myTimingModeRegion.IncModificationCounter();
                            }
                        }
                    }
                }
            }
        }
    }
	return NULL;
}