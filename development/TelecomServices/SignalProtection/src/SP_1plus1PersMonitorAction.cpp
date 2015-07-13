// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_1plus1PersMonitorAction.h"
#include "../SP_SelectorPositionRegion.h"
#include <T6100_Dispatcher.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <T6100_Services.h>
#include <Blackboard/FC_PersStatusRegion.h>
#include <Blackboard/FC_PersistentRegionManager.h>


////-----Special action-------------------------------------------
//##ModelId=3BBC9B0F02A0
SP_1plus1PersMonitorAction::SP_1plus1PersMonitorAction(
	SP_SelectorPositionRegion& theSelectorPosnRegion,
	SP_SelectorPositionRegion* theAltSelectorPosnRegion):
    theirSelectorPosnRegion(theSelectorPosnRegion),
	theirAltSelectorPosnRegion(theAltSelectorPosnRegion),
	myIsProcessed(false)
{
    myProcess = new FC_TimedProcess(*this, gTimerDispatcher, 30*1000);
    myProcess->WakeUp();
}

//##ModelId=38EDF51800A6
SP_1plus1PersMonitorAction::~SP_1plus1PersMonitorAction()
{
	myProcess->SuspendImmediate();
	delete myProcess;
}

//##ModelId=3B8BC9D30390
void SP_1plus1PersMonitorAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_1plus1PersMonitorAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
	FC_BbPersStatus::Status persStatus = T6100_Services::GetInstance()->GetPersRegManCfg().GetStatusRegion().GetStatus();
	if(persStatus == FC_BbPersStatus::READY || persStatus == FC_BbPersStatus::PS_ERROR)
	{
		if (!myIsProcessed)
		{
		    if (!theirSelectorPosnRegion.IsValid())
			{
                theirSelectorPosnRegion.IncModificationCounter();
                theirSelectorPosnRegion.UpdateNotify();
			}

			if (theirAltSelectorPosnRegion)
			{
				 if (!theirAltSelectorPosnRegion->IsValid())
				 {
                     theirAltSelectorPosnRegion->IncModificationCounter();
                     theirAltSelectorPosnRegion->UpdateNotify();
				 }
			}

			ValidateSpecificRegions();

		    myIsProcessed = true;
		    myProcess->Suspend();
		}
	}
	else
	{
		myProcess->WakeUp();
	}
	return NULL;
}

void SP_1plus1PersMonitorAction::ValidateSpecificRegions()
{
}
