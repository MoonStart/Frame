//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_UpdateStatusAction.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"
#include "../MON_Defects.h"
#include <Blackboard/FC_BbAction.h>
#include <Blackboard/FC_Blackboard.h>
#include <ErrorService/FC_Error.h>
#include <AppFramework/FC_Context.h>
#include <T6100_CardActiveRegion.h>

bool MON_UpdateStatusAction::myEnable = true;

//##ModelId=3C0FE66D03C0
MON_UpdateStatusAction::MON_UpdateStatusAction(MON_AppIf& theMonIf,
                                               MON_AppIf* theUpstreamLayerIf):
    myMonIf(theMonIf),
    myUpstreamLayerIf(theUpstreamLayerIf),
    myBbAction(NULL)
{
    SetInstanceName();

    myBbAction =  new FC_BbAction(this);
    myBbAction->AddInputRegion(&myMonIf.GetContextStatusRegion());

    // register action to upstream defect region for defect propagation.
    if (GetUpstreamLayerMonIf())
        GetBbAction()->AddInputRegion(GetUpstreamLayerMonIf()->GetDefectsRegion());
}

//##ModelId=3C0FE66D03DF
MON_UpdateStatusAction::~MON_UpdateStatusAction()
{
    myBbAction->RemoveInputRegion(&myMonIf.GetContextStatusRegion());
    if (GetUpstreamLayerMonIf())
        GetBbAction()->RemoveInputRegion(GetUpstreamLayerMonIf()->GetDefectsRegion());
    delete myBbAction;
}

void MON_UpdateStatusAction::SetInstanceName()
{
    itsInstanceName = myMonIf.GetContext().GetInstanceName();
    const FC_BbAppIf* aParent = myMonIf.GetContext().GetParent();
    while (aParent!=NULL)
    {
        itsInstanceName = string(aParent->GetBb().GetInstanceName()) + "/" + itsInstanceName;
        aParent = aParent->GetParent();
    }
}

//##ModelId=3C7170D501D1
bool MON_UpdateStatusAction::IsUpstreamLayerFailed() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerInDefects();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::IsUpstreamLayerFailedForMaintSig() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerForMaintSigInDefects();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::IsUpstreamLayerFailedNTA() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerInDefectsNTA();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::IsUpstreamLayerLocked() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerLocked();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::IsUpstreamLayerInternalFailed() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerInternalInDefects();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::IsUpstreamLayerInternalFailedForMaintSig() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );        
        return aUpStreamDefects.IsLayerInternalForMaintSigInDefects();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::IsUpstreamLayerInternalLocked() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerInternalLocked();
    }
    else
        return false;
}


bool MON_UpdateStatusAction::IsUpstreamLayerInternalPropagateNextLayer() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsInternalInPropagateNextLayerDefectsTA();
    }
    else
        return false;
}


bool MON_UpdateStatusAction::IsUpstreamLayerTermLpbk() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerInTermLpbk();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::IsUpstreamLayerDegrade() const
{
    // if region exist and is valid, check if first element is failed.
    if (myUpstreamLayerIf != NULL)
    {
        MON_Defects& aUpStreamDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[0] );
        return aUpStreamDefects.IsLayerInDegrade();
    }
    else
        return false;
}

bool MON_UpdateStatusAction::GetInternalRealTimeDefects(uint16 index, uint8 facNumber, CT_TEL_Defect theDefect)
{
    return false;
}

bool MON_UpdateStatusAction::GetExternalRealTimeDefects(uint16 index, uint8 facNumber, CT_TEL_Defect theDefect)
{
    return false;
}

void MON_UpdateStatusAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* MON_UpdateStatusAction::DoRunWithReason(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    // myEnable could be changed for debug purpose
    if (myEnable)
    {
        if (myMonIf.GetContextStatusRegion().GetActive())
            return Process(theRunReason, theInvokerObj, theParam);
        else
            return Suspend(theRunReason, theInvokerObj, theParam);
    }
    return NULL;
}

const char* MON_UpdateStatusAction::GetInstanceName(void ) const
{
    return itsInstanceName.c_str();
}
