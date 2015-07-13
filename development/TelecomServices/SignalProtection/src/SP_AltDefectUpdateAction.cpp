// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_AltDefectUpdateAction.h"
#include "../SP_Defects.h"
#include <Blackboard/FC_BbAction.h>
#include <Blackboard/FC_BbReason.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>

//##ModelId=3BBC9B0F02A0
SP_AltDefectUpdateAction::SP_AltDefectUpdateAction(SP_1plus1BaseApplication& theLineProtApp) :
myLineApp(theLineProtApp),
stopped(false)
{
    myBbAction = new FC_BbAction(this);
}

//##ModelId=38EDF51800A6
SP_AltDefectUpdateAction::~SP_AltDefectUpdateAction()
{
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_AltDefectUpdateAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3BBC9B3903A6
FC_Object* SP_AltDefectUpdateAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;

	//Do processing here
	myLineApp.GetAltDefectsRegion(CT_SP_WORKING_SIDE)->IncModificationCounter();
	myLineApp.GetAltDefectsRegion(CT_SP_PROTECTION_SIDE)->IncModificationCounter();
    return NULL;
}

void SP_AltDefectUpdateAction::UpdateDefects(SP_Defects* theDefects, int index, CT_IntfId theIntfId, CT_SP_1plus1Type theType, bool theForceInc)
{
	//Get the appropriate object in the appropriate region and update it
	SP_Defects* aDefects = NULL;
	uint32 aCount=0;
	bool aState=false;
	
	bool hasChanged = false;

	if (theType == CT_SP_OAPS)
	{
		SP_ProtectionSide theSide = (theIntfId == CT_LINE_SIDE_0 ||
                       theIntfId == CT_LINE_SIDE_2 ||
                       theIntfId == CT_LINE_SIDE_4 ||
                       theIntfId == CT_LINE_SIDE_6 ? CT_SP_WORKING_SIDE : CT_SP_PROTECTION_SIDE);

	    aCount = 0;aState = false;
		aDefects = static_cast<SP_Defects*>(&((*myLineApp.GetAltDefectsRegion(theSide))[index]));
		theDefects->GetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, &aCount, &aState);
		hasChanged |= aDefects->SetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, aState, aCount);
		aCount = 0;aState = false;
		theDefects->GetDefectStatus(CT_TEL_OTU_LOF_DEFECT, &aCount, &aState);
		hasChanged |= aDefects->SetDefectStatus(CT_TEL_OTU_LOF_DEFECT, aState, aCount);
		aDefects->Validate();
	}
	else if (theType == CT_SP_DPRING)
	{
		//Line side protection
		aCount = 0;aState = false;
		aDefects = static_cast<SP_Defects*>(&((*myLineApp.GetAltDefectsRegion(CT_SP_WORKING_SIDE))[index]));
		theDefects->GetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, &aCount, &aState);
		hasChanged |= aDefects->SetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, aState, aCount);
		aCount = 0;aState = false;
		theDefects->GetDefectStatus(CT_TEL_OTU_LOF_DEFECT, &aCount, &aState);
		hasChanged |= aDefects->SetDefectStatus(CT_TEL_OTU_LOF_DEFECT, aState, aCount);
		if (hasChanged || !aDefects->IsValid() || theForceInc)
			aDefects->IncDefectId();
		aDefects->Validate();

	    aCount = 0;aState = false;
		aDefects = static_cast<SP_Defects*>(&((*myLineApp.GetAltDefectsRegion(CT_SP_PROTECTION_SIDE))[index]));
		theDefects->GetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, &aCount, &aState);
		hasChanged |= aDefects->SetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, aState, aCount);
		aCount = 0;aState = false;
		theDefects->GetDefectStatus(CT_TEL_OTU_LOF_DEFECT, &aCount, &aState);
		hasChanged |= aDefects->SetDefectStatus(CT_TEL_OTU_LOF_DEFECT, aState, aCount);
		if (hasChanged || !aDefects->IsValid() || theForceInc)
			aDefects->IncDefectId();
		aDefects->Validate();

		hasChanged |= theForceInc;
	}

	if (hasChanged)
        GetBbAction()->RunWithReason(FC_BbReason::MODIFICATION, NULL,NULL);
}
