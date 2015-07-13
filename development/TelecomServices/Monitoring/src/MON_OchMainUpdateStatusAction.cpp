// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "Monitoring/MON_OchMainUpdateStatusAction.h"
#include "Monitoring/MON_OtsOHDefects.h"
#include "Monitoring/MON_OtsOchOHDefects.h"
#include "Monitoring/MON_OchMainDefects.h"
#include "Monitoring/MON_AppIf.h"
#include "Monitoring/MON_SubNodeParameters.h"
#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <T6100_Dispatcher.h>


MON_OchMainUpdateStatusAction::MON_OchMainUpdateStatusAction(MON_AppIf& theMonIf,
                                                             MON_OtsOHDefectsRegion*    theOtsOHDefectsRegion,
                                                             MON_OtsOchOHDefectsRegion* theOtsOchOHDefectsRegion):
    MON_UpdateStatusAction(theMonIf,NULL),
    myOtsOHDefectsRegion(theOtsOHDefectsRegion),
    myOtsOchOHDefectsRegion(theOtsOchOHDefectsRegion)
{
    if (myOtsOHDefectsRegion) GetBbAction()->AddInputRegion(myOtsOHDefectsRegion);
    if (myOtsOchOHDefectsRegion) GetBbAction()->AddInputRegion(myOtsOchOHDefectsRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
}

MON_OchMainUpdateStatusAction::~MON_OchMainUpdateStatusAction()
{
    if (myOtsOHDefectsRegion) GetBbAction()->RemoveInputRegion(myOtsOHDefectsRegion);
    if (myOtsOchOHDefectsRegion) GetBbAction()->RemoveInputRegion(myOtsOchOHDefectsRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
}

FC_Object* MON_OchMainUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    return NULL;
}

FC_Object* MON_OchMainUpdateStatusAction::Process(unsigned theRunReason,
                                                  FC_Object* theInvokerObj,
                                                  FC_Object* theParam)
{
    if(!MON_SubNodeParameters::GetInstance().IsSubNodeParametersReady())
        return NULL;

    uint32 aSize = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();

    //Size may need to be adjusted based on the size of the input myOtsOchOHDefectsRegion. There are situations
    //during complex subnode migrations where the oms wavelength capacity changes. Since the input region may be transferred
    //from a different module (OSC), the size of the region may reflect the old wavelength capacity. We adjust the
    //size here to pick the lower number of the two.
    if (myOtsOchOHDefectsRegion)
    {
        uint32 inputOtsOchRegionSize = myOtsOchOHDefectsRegion->Size();
        if (inputOtsOchRegionSize < aSize)
            aSize = inputOtsOchRegionSize;
    }

    //Update all objects of the region.
    for(uint8 aIndex=0; aIndex<aSize; aIndex++)
    {
        UpdateObject(theRunReason, aIndex);
    }

    return NULL;
}



void MON_OchMainUpdateStatusAction::UpdateObject(unsigned theRunReason, uint32 theIndex)
{
    MON_OchMainDefects& aOchMainDefects    = static_cast<MON_OchMainDefects&>((*GetMonIf().GetDefectsRegion())[(bbindex_t)theIndex]);
    MON_OtsOHDefects* aOtsOHDefects        = NULL;
    MON_OtsOchOHDefects* aOtsOchOHDefects  = NULL;

    if(myOtsOHDefectsRegion) aOtsOHDefects = static_cast<MON_OtsOHDefects*>(&(*myOtsOHDefectsRegion)[0]);
    if(myOtsOchOHDefectsRegion) aOtsOchOHDefects = static_cast<MON_OtsOchOHDefects*>(&(*myOtsOchOHDefectsRegion)[(bbindex_t)theIndex]);

    //--------------------------------------------------------------
    // CONFIG
    // Read current config
    // None for now

    //--------------------------------------------------------------
    // STATUSES
    // Read current statuses
    // None for now

    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects
    bool hasDefectsChanged = false;
    bool aOchChannelFailState = false;
    bool aOchChannelFailEvent = false;

    uint32 aCount = 0;

    bool aOtsTimState = false;
    bool aOtsPmiState = false;
    bool aOmsFdipState = false;
    bool aOchFdipState = false;
    bool aOchOciState = false;

    if(aOtsOHDefects)
    {
        aOtsOHDefects->GetDefectStatus(CT_TEL_OTS_TIM_DEFECT, &aCount, &aOtsTimState);
        aOtsOHDefects->GetDefectStatus(CT_TEL_OTS_PMI_DEFECT,&aCount, &aOtsPmiState);
        aOtsOHDefects->GetDefectStatus(CT_TEL_OMS_FDIP_DEFECT,&aCount, &aOmsFdipState);
    }
    if(aOtsOchOHDefects)
    {
        aOtsOchOHDefects->GetDefectStatus(CT_TEL_OCH_FDIP_DEFECT,&aCount, &aOchFdipState);
        aOtsOchOHDefects->GetDefectStatus(CT_TEL_OCH_OCI_DEFECT, &aCount, &aOchOciState);
    }
    // Update Och Signalling defect
    aOchChannelFailState = aOtsTimState || aOmsFdipState || aOtsPmiState || aOchFdipState || aOchOciState;

    // Update actual defect
    hasDefectsChanged |= aOchMainDefects.SetDefectStatus(CT_TEL_OCH_CHANNEL_FAIL_DEFECT, aOchChannelFailState, aOchChannelFailEvent);

    hasDefectsChanged |= aOchMainDefects.Validate();

    if (hasDefectsChanged)
        GetMonIf().GetDefectsRegion()->IncModificationCounter();


}
