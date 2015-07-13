// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_ClkSelIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_SyncUpdateStatusAction.h"
#include "../MON_SyncDefects.h"
#include "../MON_SyncStatus.h"
#include "../MON_Region.h"

MON_SyncUpdateStatusAction::MON_SyncUpdateStatusAction(MON_AppIf& theMonIf,
                                                   TSPII_ClkSelRegion& theClkSelPiiRegion,
                                                   MON_AppIf* theUpstreamLayerIf):
	MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myClkSelPiiRegion(theClkSelPiiRegion),
  	myPiiCurrentState(CT_TEL_CLKSEL_STATE_FREERUN)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myClkSelPiiRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
}

MON_SyncUpdateStatusAction::~MON_SyncUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myClkSelPiiRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
}

FC_Object* MON_SyncUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}


FC_Object* MON_SyncUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    MON_SyncDefects& aDefects   = static_cast<MON_SyncDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_SyncStatus& aStatus     = static_cast<MON_SyncStatus&>((*GetMonIf().GetStatusRegion())[0]);
    TSPII_ClkSelIf& aClkSelPII  = myClkSelPiiRegion[0];
    bool hasDefectsChanged = false;

    //--------------------------------------------------------------
    // SET UP and READ PII

    bool hasStatusChanged=false;

    bool aFreerunState=false, aHoldoverState=false;
    bool aFreerunEvent=false, aHoldoverEvent=false;

    //Read Current State from PII
    CT_TEL_ClkSelState aCurrentState = aClkSelPII.GetTimingState();


    //--------------------------------------------------------------
    // STATUS

     //If current state read from PII is different than the current state in STATUS region, update the status region
    if (aStatus.GetCurrentState() != aCurrentState)  
    {
        hasStatusChanged |= aStatus.SetCurrentState(aCurrentState);
    }


    //Read Freerun SSM from PII
    CT_FAC_RxSsm aFreerunSsm = aClkSelPII.GetFreerunSsm();

    //If current Freerun read from PII is different than the current state in STATUS region, update the status region
    if (aStatus.GetFreerunSsm() != aFreerunSsm)  
    {
        hasStatusChanged |= aStatus.SetFreerunSsm(aFreerunSsm);
    }


	//Read clock mode from PII
	CT_TEL_ClkMode aClockMode = aClkSelPII.GetClockMode();
	if (aStatus.GetClockMode() != aClockMode)
	{
		hasStatusChanged |= aStatus.SetClockMode(aClockMode);
	}

	//Read mate clock mode from PII
	aClockMode = aClkSelPII.GetMateClockMode();
	if (aStatus.GetMateClockMode() != aClockMode)
	{
		hasStatusChanged |= aStatus.SetMateClockMode(aClockMode);
	}


    // Validate status object
    aStatus.Validate();

    //--------------------------------------------------------------
    // DEFECTS (based on STATUS)

    // Upstream layer in failure, do not look at defect
    if (IsUpstreamLayerFailed())
    {
        aFreerunState = false;
        aFreerunEvent = false;
        aHoldoverState = false;
        aHoldoverEvent = false;
    }
    else
    {
        // Update Holdover and Freerun Based on Current State
        if (aCurrentState == CT_TEL_CLKSEL_STATE_FREERUN) 
        {
            aFreerunState = true;
        }

        else if (aCurrentState == CT_TEL_CLKSEL_STATE_HOLDOVER) 
        {
            aHoldoverState = true;
        }
        else
        {
            aFreerunState = false;
            aHoldoverState = false;
        }
    }

    // Update actual defect
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_SYNC_FREERUN_DEFECT,  aFreerunState,  aFreerunEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_SYNC_HOLDOVER_DEFECT,  aHoldoverState,  aHoldoverEvent);

    // Validate defect object
    aDefects.Validate();


    // Update local variables (in this case, status)
    myPiiCurrentState = aCurrentState;


    // Update modification counts, if necessary
    if (hasDefectsChanged) 
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();
    

    return NULL;
}
