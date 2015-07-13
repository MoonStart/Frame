// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_OptProtCfgAction.h"
#include "../SP_Application.h"
#include "../SP_ApplicationStatus.h"
#include "../SP_Utilities.h"
#include "../SP_1plus1ProtectionGroupConfig.h"
#include <Blackboard/FC_BbAction.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_OptProt.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_OptConfig.h>
#include <Monitoring/MON_AppIf.h>
#include <ErrorService/FC_Error.h>


SP_OptProtCfgAction::SP_OptProtCfgAction(	
	SP_Application& theApplIf,
    SP_ProtectionGroupConfigRegion& theConfigRegion,
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
    CT_ShelfId theShelfId,
    CT_SlotId theSlotId,
    CT_IntfId thePortId,
    uint8 theStartIndex,
    uint8 theNumNodes):
    myAppIf(theApplIf),
	myConfigRegion(theConfigRegion),
    myAppStatusRegion(theAppStatusRegion),
    myShelfId (theShelfId),
    mySlotId (theSlotId),
    myPortId(thePortId),
    myStartIndex(theStartIndex),
    myNumNodes(theNumNodes)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion(&myAppStatusRegion);
	//Add mon opt port region as input
	MON_Region* theMonConfigRegion = myAppIf.GetCardContext().GetOptIf().GetMonPortSideApp(myPortId).GetConfigRegion();
    if (theMonConfigRegion)
    {
        myBbAction->AddInputRegion(theMonConfigRegion);
    }
}

//##ModelId=38EDF51800A6
SP_OptProtCfgAction::~SP_OptProtCfgAction()
{
	myBbAction->RemoveInputRegion(&myAppStatusRegion);
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_OptProtCfgAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_OptProtCfgAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
	//SP_ApplicationStatus& aAppStatus = static_cast<SP_ApplicationStatus&>(myAppStatusRegion[0]);
	CFG_Region* theOptRegion = myAppIf.GetCardContext().GetOptIf().GetCfgPortSideApp(myPortId).GetProtCfgRegion();
	CFG_OptProt& theOptProtObject = static_cast<CFG_OptProt&> ( (*theOptRegion)[0]); 

        // remove ready check because it will disable all port laser if ycable has non-complete config 
	//if ( (aAppStatus.IsReady()) && (!IsYCableProtectionConfiguredOnPort()) )
	if ( !IsYCableProtectionConfiguredOnPort() )
	{
		if ( !theOptRegion->IsValid() )
		{
			theOptProtObject.SetForceLaserShutdown(false);
		    //Y Cable protection not configured
		    theOptRegion->IncModificationCounter();
		    theOptRegion->UpdateNotify();
		}
		else
		{
			//If the force laser shutdown is set, then check if the facility is IS,
			//Clear the force laser shutdown if facility is IS
            if (theOptProtObject.GetForceLaserShutdown() == true)
			{
				MON_Region* theConfigRegion = myAppIf.GetCardContext().GetOptIf().GetMonPortSideApp(myPortId).GetConfigRegion();
                if (theConfigRegion)
                {
                    MON_OptConfig* aMonOptConfigObject = static_cast<MON_OptConfig*>(&((*theConfigRegion)[0]));
				    if (aMonOptConfigObject->GetLayerLocked() == false)
				    {
				        theOptProtObject.SetForceLaserShutdown(false);
		                //Y Cable protection not configured
		                theOptRegion->IncModificationCounter();
		                theOptRegion->UpdateNotify();
				    }
                }
			}
		}
	}
	return NULL;
}

bool SP_OptProtCfgAction::IsYCableProtectionConfiguredOnPort()
{
    bool isConfigured = false;
    uint8 i;
    for (i=myStartIndex;i<(myStartIndex+myNumNodes);i++)
    {
        SP_1plus1ProtectionGroupConfig& aConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(myConfigRegion[i]);
        if (aConfig.InUse())
        {
            if (aConfig.Get1plus1Type() == CT_SP_YCABLE)
            {
                if ( (aConfig.GetSources().working.GetPortId() == myPortId &&
                      aConfig.GetSources().working.GetSlotId() == mySlotId &&
                      aConfig.GetSources().working.GetShelfId() == myShelfId) ||
                     
                      (aConfig.GetSources().protection.GetPortId() == myPortId &&
                      aConfig.GetSources().protection.GetSlotId() == mySlotId &&
                      aConfig.GetSources().protection.GetShelfId() == myShelfId)
                   )
                {
                    isConfigured = true;
                    break;
                }

            }
        }
    }
    return isConfigured;
}
