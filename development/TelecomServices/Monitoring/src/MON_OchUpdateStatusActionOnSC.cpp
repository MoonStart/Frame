// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "Monitoring/MON_OchUpdateStatusActionOnSC.h"
#include "Monitoring/MON_OchAltStatus.h"
#include "Monitoring/MON_AppIf.h"
#include <ErrorService/FC_Error.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <CSM/CSM_AppIf.h>
#include <TsPii/TSPII_PipeIf.h>

MON_OchUpdateStatusActionOnSC::MON_OchUpdateStatusActionOnSC(MON_AppIf& theMonIf,
                                                     TSPII_PipeRegion* theTspiiPipeRegion,
                                                     MON_OchAltStatusRegion* theAltOchRegion):
    MON_UpdateStatusAction(theMonIf,NULL),
    myTspiiPipeRegion(theTspiiPipeRegion),
    myAltOchRegion(theAltOchRegion)

{
    if (myTspiiPipeRegion)
        GetBbAction()->AddInputRegion(myTspiiPipeRegion);
    
    if (myAltOchRegion)
        GetBbAction()->AddOutputRegion(myAltOchRegion,false);
}

MON_OchUpdateStatusActionOnSC::~MON_OchUpdateStatusActionOnSC()
{
    if (myTspiiPipeRegion)
        GetBbAction()->RemoveInputRegion(myTspiiPipeRegion);
  
    if (myAltOchRegion)
        GetBbAction()->RemoveOutputRegion(myAltOchRegion);
}

FC_Object* MON_OchUpdateStatusActionOnSC::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
      
    if (myAltOchRegion)
        myAltOchRegion->Reset();
    return NULL;
}

FC_Object* MON_OchUpdateStatusActionOnSC::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    uint32 aSize = myAltOchRegion->Size();
    uint32 aIndex=0;
    while (aIndex<aSize)
    {
        UpdateObject(theRunReason, aIndex);
        aIndex++;
    }

    return NULL;
}

void MON_OchUpdateStatusActionOnSC::UpdateObject(unsigned theRunReason, uint32 theIndex)
{
    //--------------------------------------------------------------
    // ALT STATUS
    if (myAltOchRegion && myTspiiPipeRegion)
    {
        MON_OchAltStatus& aAltStatus  = static_cast<MON_OchAltStatus&>((*myAltOchRegion)[(bbindex_t)theIndex]);
        TSPII_PipeIf& aPipePii = (*myTspiiPipeRegion)[0];
        bool hasAltStatusChanged = false;

        try
        {
            hasAltStatusChanged |= aAltStatus.SetActualGain(aPipePii.GetActualGain(theIndex));

            CT_TEL_mBm atmpConfiguredGain = aPipePii.GetEvoa(theIndex);
            hasAltStatusChanged |= aAltStatus.SetConfiguredGain(atmpConfiguredGain);
            
            if (atmpConfiguredGain != TRAFFIC_DEFAULT_POWER)
            {
                hasAltStatusChanged |= aAltStatus.Validate();
            }
            
        }
        catch (FC_HWError&)
        {
            hasAltStatusChanged |= aAltStatus.Invalidate();
        }
        if (hasAltStatusChanged)
            myAltOchRegion->IncModificationCounter();
    }

}

