// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_OchOHIf.h>
#include <ErrorService/FC_Error.h>
#include "MON_OtsOchOHUpdateStatusAction.h"
#include "MON_OtsOchOHDefects.h"
#include "MON_AppIf.h"
#include "MON_Region.h"

MON_OtsOchOHUpdateStatusAction::MON_OtsOchOHUpdateStatusAction(MON_AppIf& theMonIf,
                                                               MON_AppIf& theUpstreamLayerIf,
                                                               TSPII_OchOHRegion& theOchOHPiiRegion,
                                                               MON_OtsOchOHDefectsRegion& theDefectsRegion):
    MON_UpdateStatusAction(theMonIf,&theUpstreamLayerIf),
    myOchOHPiiRegion(theOchOHPiiRegion),
    myDefectsRegion(theDefectsRegion)

{
    //Reset local counters
    for(uint32 i = 0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY;i++)
    {
        myPiiOchFDIPCount[i] = 0;
        myPiiOchFDIOCount[i] = 0;
        myPiiOchOCICount[i] = 0;
    }

    GetBbAction()->AddInputRegion(&myOchOHPiiRegion);
    GetBbAction()->AddOutputRegion(&myDefectsRegion,false);
}

MON_OtsOchOHUpdateStatusAction::~MON_OtsOchOHUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myOchOHPiiRegion);
    GetBbAction()->RemoveOutputRegion(&myDefectsRegion);
}

FC_Object* MON_OtsOchOHUpdateStatusAction::Suspend(unsigned theRunReason,
                                                   FC_Object* theInvokerObj,
                                                   FC_Object* theParam)
{
    myDefectsRegion.Reset();
    return NULL;
}

FC_Object* MON_OtsOchOHUpdateStatusAction::Process(unsigned theRunReason,
                                                   FC_Object* theInvokerObj,
                                                   FC_Object* theParam)
{
    uint32 aSize = myDefectsRegion.Size();

    //Update all objects of the region.
    for(uint8 aIndex=0; aIndex<aSize; aIndex++)
    {
        UpdateObject(theRunReason, aIndex);
    }

    return NULL;
}

void MON_OtsOchOHUpdateStatusAction::UpdateObject(unsigned theRunReason, uint8 theIndex)
{

    MON_OtsOchOHDefects& aDefects  = myDefectsRegion[theIndex];
    TSPII_OchOHIf& aOchOHPii       = myOchOHPiiRegion[theIndex];

    bool aOchFDIPState=false;
    bool aOchFDIPEvent=false;
    bool aOchFDIOState=false;
    bool aOchFDIOEvent=false;
    bool aOchOCIState=false;
    bool aOchOCIEvent=false;

    //--------------------------------------------------------------
    // CONFIG
    // None for now
    //--------------------------------------------------------------
    // COUNTERS
    // None for now
    //--------------------------------------------------------------
    // STATUS
    // None for now
    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects

    uint32 aNewOchFDIPCount = aOchOHPii.GetFDIP();
    uint32 aNewOchFDIOCount = aOchOHPii.GetFDIO();
    uint32 aNewOchOCICount  = aOchOHPii.GetOCI();

    //Disable all the defects on RS layer failure
    if(IsUpstreamLayerFailed())
    {
        aOchFDIPState = false;
        aOchFDIPEvent = false;
        aOchFDIOState = false;
        aOchFDIOEvent = false;
        aOchOCIState  = false;
        aOchOCIEvent  = false;
    }
    else
    {
        // Update OCH FDI-O state and count
        if(myPiiOchFDIOCount[theIndex] != aNewOchFDIOCount)
        {
            aOchFDIOEvent = true;
        }
        if(aNewOchFDIOCount%2 != 0)
        {
            aOchFDIOState = true;        
        }

        // Update OCH FDI-P state and count
        if(myPiiOchFDIPCount[theIndex] != aNewOchFDIPCount)
        {
            aOchFDIPEvent = true;
        }
        if(aNewOchFDIPCount%2 != 0)
        {
            aOchFDIPState = true;        
        }

        // Update OCH OCI state and count
        if(myPiiOchOCICount[theIndex] != aNewOchOCICount)
        {
            aOchOCIEvent = true;
        }
        if(aNewOchOCICount%2 != 0)
        {
            aOchOCIState = true;        
        }            
    }

    //Update local defect counts
    myPiiOchFDIPCount[theIndex] = aNewOchFDIPCount;
    myPiiOchFDIOCount[theIndex] = aNewOchFDIOCount;
    myPiiOchOCICount[theIndex]  = aNewOchOCICount;


    // update actual defect
    bool hasDefectsChanged = false;
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OCH_FDIP_DEFECT,aOchFDIPState,aOchFDIPEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OCH_FDIO_DEFECT,aOchFDIOState,aOchFDIOEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OCH_OCI_DEFECT, aOchOCIState, aOchOCIEvent);
    hasDefectsChanged |= aDefects.Validate();

    if (hasDefectsChanged) 
    {
        myDefectsRegion.IncModificationCounter();
    }

}
   
