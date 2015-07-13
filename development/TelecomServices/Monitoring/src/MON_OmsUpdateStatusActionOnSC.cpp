// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_PipeIf.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <ErrorService/FC_Error.h>
#include <CSM/CSM_CardStatus.h>
#include <CSM/CSM_AppIf.h>
#include "../MON_OmsUpdateStatusActionOnSC.h"
#include <Monitoring/MON_OmsDefects.h>
#include <Monitoring/MON_OmsStatus.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Region.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include "CsPii/CSPII_ShelfIF.h"


MON_OmsUpdateStatusActionOnSC::MON_OmsUpdateStatusActionOnSC(MON_AppIf& theMonIf,
                                                     TSPII_PipeRegion& thePipePiiRegion) :
    MON_UpdateStatusAction(theMonIf,NULL),
    myPipePiiRegion(thePipePiiRegion),
    myPiiOmsLosCount(0)
{
    GetBbAction()->AddInputRegion(&myPipePiiRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);    
}

MON_OmsUpdateStatusActionOnSC::~MON_OmsUpdateStatusActionOnSC()
{
    GetBbAction()->RemoveInputRegion(&myPipePiiRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
}

FC_Object* MON_OmsUpdateStatusActionOnSC::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}

FC_Object* MON_OmsUpdateStatusActionOnSC::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    MON_OmsDefects& aOmsDefects   = static_cast<MON_OmsDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_OmsStatus&  aOmsStatus    = static_cast<MON_OmsStatus&>((*GetMonIf().GetStatusRegion())[0]);
    TSPII_PipeIf& aPipePii        = myPipePiiRegion[0];

    bool hasDefectsChanged = false;
    bool hasStatusChanged = false;

    // reset states, only OMS LOS is supported.
    bool aOMSLosState=false;
    bool aOMSLosEvent=false;
    
    //--------------------------------------------------------------
    try
    {

        //--------------------------------------------------------------
        // DEFECTS
        uint32 aNewOmsLosInCount = aPipePii.GetLOS();
        
        // OMS-LOS state and count update
        if(myPiiOmsLosCount != aNewOmsLosInCount)
        {
            aOMSLosEvent = true;
            myPiiOmsLosCount = aNewOmsLosInCount;
        }
        if(aNewOmsLosInCount%2 != 0)
        {
            aOMSLosState = true;
        }

        // Update actual defect, so far, only OMS LOS is supported.
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_LOS_DEFECT, aOMSLosState, aOMSLosEvent);
        hasDefectsChanged |= aOmsDefects.Validate();

        if (hasDefectsChanged)
            GetMonIf().GetDefectsRegion()->IncModificationCounter();

        //--------------------------------------------------------------
        // STATUS
        // Read current status

        // OMS powers
        hasStatusChanged |= aOmsStatus.SetOmsInputPower(aPipePii.GetInputPower());
        hasStatusChanged |= aOmsStatus.SetActualGain(aPipePii.GetActualGain());
        hasStatusChanged |= aOmsStatus.SetConfiguredGain(aPipePii.GetGain());
        hasStatusChanged |= aOmsStatus.SetOmsOutputPower(aPipePii.GetOutputPower());

        // if OMS-LOS, indicate that output power is probably not valid
        if (aOMSLosState)
        {
            hasStatusChanged |= aOmsStatus.Invalidate();
        }
        else
        {
            //Validate object
            hasStatusChanged |= aOmsStatus.Validate();
        }

        if (hasStatusChanged)
            GetMonIf().GetStatusRegion()->IncModificationCounter();

    }
    catch (FC_HWError&)
    {
        hasDefectsChanged |= aOmsDefects.Invalidate();
        hasStatusChanged  |= aOmsStatus.Invalidate();
        if (hasDefectsChanged)
            GetMonIf().GetDefectsRegion()->IncModificationCounter();
        if (hasStatusChanged)
            GetMonIf().GetStatusRegion()->IncModificationCounter();
    }

    return NULL;
}
