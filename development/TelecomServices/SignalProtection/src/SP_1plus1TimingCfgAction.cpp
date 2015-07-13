// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_1plus1TimingCfgAction.h"
#include "../SP_Application.h"
#include "../SP_ApplicationStatus.h"
#include "../SP_Utilities.h"
#include <Blackboard/FC_BbAction.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_SyncProt.h>
#include <ErrorService/FC_Error.h>


////-----Special action-------------------------------------------
SP_1plus1TimingCfgAction::SP_1plus1TimingCfgAction(	
	SP_Application& theApplIf,
    SP_ProtectionGroupConfigRegion& theConfigRegion,
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
	CFG_Region& theCfgRsRegion,
	CFG_Region& theCfgSyncProtRegion):
    myAppIf(theApplIf),
	myConfigRegion(theConfigRegion),
    myAppStatusRegion(theAppStatusRegion),
	myCfgRsRegion(theCfgRsRegion),
	myCfgSyncProtRegion(theCfgSyncProtRegion)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion(&myAppStatusRegion);
	myBbAction->AddInputRegion(&myCfgRsRegion);
}

//##ModelId=38EDF51800A6
SP_1plus1TimingCfgAction::~SP_1plus1TimingCfgAction()
{
	myBbAction->RemoveInputRegion(&myAppStatusRegion);
	myBbAction->RemoveInputRegion(&myCfgRsRegion);
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_1plus1TimingCfgAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_1plus1TimingCfgAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
	SP_ApplicationStatus& aAppStatus = static_cast<SP_ApplicationStatus&>(myAppStatusRegion[0]);
	SP_ProtectionGroupConfig& aConfig = static_cast<SP_ProtectionGroupConfig&>(myConfigRegion[0]);
	CFG_Rs& aCfgObject = static_cast<CFG_Rs&> (myCfgRsRegion[0]);
	CFG_SyncProt& theSyncProtObject = static_cast<CFG_SyncProt&> ( (myCfgSyncProtRegion)[0]); 

	if ( (aAppStatus.IsReady()) && (!aConfig.InUse()) )
	{
		CT_FAC_RxSsm txSSM;
		if (aCfgObject.GetSDHTrueMode() == true)
		{
			txSSM = GetFreeRunSsm(CT_TEL_SDH);
		}
		else
		{
			txSSM = GetFreeRunSsm(CT_TEL_SONET);
		}
		if ( (theSyncProtObject.GetSelectedRefSSM() != txSSM) || (!myCfgSyncProtRegion.IsValid()) )
		{
			theSyncProtObject.SetSelectedRefSSM(txSSM);
		    //Timing protection not configured
		    myCfgSyncProtRegion.IncModificationCounter();
		    myCfgSyncProtRegion.UpdateNotify();
		}
	}
	return NULL;
}