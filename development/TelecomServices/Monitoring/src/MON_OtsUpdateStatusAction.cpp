// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_OtsOHIf.h>
#include <TsPii/TSPII_OmsOHIf.h>
#include <ErrorService/FC_Error.h>
#include "../MON_OtsUpdateStatusAction.h"
#include "../MON_OtsOHDefects.h"
#include "../MON_OtsDefects.h"
#include "../MON_OtsConfig.h"
#include "../MON_OmsDefects.h"
#include "../MON_RsDefects.h"
#include "../MON_OtsStatus.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"
#include <ITS/ITS_AppIfBase.h>
#include <T6100_CardIf.h>

MON_OtsUpdateStatusAction::MON_OtsUpdateStatusAction(MON_AppIf& theMonIf,
                                                     MON_AppIf& theUpstreamLayerIf,
                                                     MON_OmsDefectsRegion& theOmsDefectsRegion,
                                                     TSPII_OtsOHRegion& theOtsPiiRegion,
                                                     TSPII_OmsOHRegion* theOmsPiiRegion,
                                                     MON_OtsOHDefectsRegion& theOtsOHDefectsRegion):
    MON_UpdateStatusAction(theMonIf,&theUpstreamLayerIf),
    myUpstreamLayerIf(theUpstreamLayerIf),
    myOmsDefectsRegion(theOmsDefectsRegion),
    myOtsPiiRegion(theOtsPiiRegion),
    myOmsPiiRegion(theOmsPiiRegion),
    myOtsOHDefectsRegion(theOtsOHDefectsRegion),
    myGoodTraceMessageCounter(0),
    myBadTraceMessageCounter(0),
    myPiiOtsBDIPCount(0),
    myPiiOtsBDIOCount(0),
    myPiiOtsPMICount(0),
    myPiiOmsFDIPCount(0),
    myPiiOmsFDIOCount(0),
    myPiiOmsPMICount(0)

{
    if(myOmsPiiRegion)
    {
        GetBbAction()->AddInputRegion(myOmsPiiRegion);
    }
    GetBbAction()->AddInputRegion(&myOtsPiiRegion);
    GetBbAction()->AddInputRegion(&myOmsDefectsRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(&myOtsOHDefectsRegion,false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);

}

MON_OtsUpdateStatusAction::~MON_OtsUpdateStatusAction()
{
    if(myOmsPiiRegion)
    {
        GetBbAction()->RemoveInputRegion(myOmsPiiRegion);
    }
    GetBbAction()->RemoveInputRegion(&myOtsPiiRegion);
    GetBbAction()->RemoveInputRegion(&myOmsDefectsRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(&myOtsOHDefectsRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
}

FC_Object* MON_OtsUpdateStatusAction::Suspend(unsigned theRunReason,
                                              FC_Object* theInvokerObj,
                                              FC_Object* theParam)
{
    myOtsOHDefectsRegion.Reset();
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}

FC_Object* MON_OtsUpdateStatusAction::Process(unsigned theRunReason,
                                              FC_Object* theInvokerObj,
                                              FC_Object* theParam)
{

    UpdateObject(theRunReason);

    return NULL;
}

void MON_OtsUpdateStatusAction::UpdateObject(unsigned theRunReason)
{

    MON_OtsOHDefects& aOtsOHDefects = myOtsOHDefectsRegion[0];
    MON_OtsDefects& aOtsDefects     = static_cast<MON_OtsDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_OtsStatus&  aStatus         = static_cast<MON_OtsStatus&>((*GetMonIf().GetStatusRegion())[0]);
    MON_OtsConfig& aConfig          = static_cast<MON_OtsConfig&>((*GetMonIf().GetConfigRegion())[0]);
    MON_RsDefects& aUpstreamDefects = static_cast<MON_RsDefects&>((*myUpstreamLayerIf.GetDefectsRegion())[0]);
    TSPII_OtsOHIf& aOtsPii          = myOtsPiiRegion[0];
    MON_OmsDefects& aOmsDefects     = myOmsDefectsRegion[0];
    TSPII_OmsOHIf* aOmsPii          = NULL;

    if(myOmsPiiRegion)
    {
        aOmsPii = &(*myOmsPiiRegion)[0];
    }

    bool aOtsLosState=false;
    bool aOtsLosEvent=false;
    bool aOtsBDIPState=false;
    bool aOtsBDIPEvent=false;
    bool aOtsBDIOState=false;
    bool aOtsBDIOEvent=false;
    bool aOtsBDIState=false;
    bool aOtsBDIEvent=false;
    bool aOtsPMIState=false;
    bool aOtsPMIEvent=false;
    bool aOtsTIMState=false;
    bool aOtsTIMEvent=false;
    bool aOmsFDIPState=false;
    bool aOmsFDIPEvent=false;
    bool aOmsFDIOState=false;
    bool aOmsFDIOEvent=false;
    bool aOmsPMIState=false;
    bool aOmsPMIEvent=false;

    static CT_G709Trace aTrace, aDefaultTrace; //tmp buffer

    //--------------------------------------------------------------
    // CONFIG
    // None for now
    //--------------------------------------------------------------
    // COUNTERS
    // None for now
    //--------------------------------------------------------------
    // STATUS
    bool hasStatusChanged = false;

    //Read trace from PII
    aTrace = aOtsPii.GetRxTTI();

    //Check if trace is valid and there is not OSC LOS
    if (aTrace.IsValid() && !IsUpstreamLayerFailed())
    {
        //If trace read from PII is different than the trace in STATUS region, update it
        if (!(aStatus.GetTraceMessage() == aTrace))
        {
            //At all time, if trace is the same for 5 times, set it in STATUS region
            if (++myGoodTraceMessageCounter == 4) 
            {
		        hasStatusChanged |= aStatus.SetTraceMessage(aTrace);
                myGoodTraceMessageCounter = 0;
                myBadTraceMessageCounter = 0;
            }
        }
        else
        {
            myGoodTraceMessageCounter = 0;
            myBadTraceMessageCounter = 0;
        }
    }
    else //Trace is not valid
    {
        myGoodTraceMessageCounter = 0;

        //PreviousTrace must be different 15 times before updating STATUS region
        if (++myBadTraceMessageCounter == 15) 
    	    hasStatusChanged |= aStatus.SetTraceMessage(aDefaultTrace);
    }

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();

    // Validate status object
    hasStatusChanged |= aStatus.Validate();    

    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects

    uint32 aNewOtsBDIPCount = aOtsPii.GetBDIP();
    uint32 aNewOtsBDIOCount = aOtsPii.GetBDIO();
    uint32 aNewOtsPMICount  = aOtsPii.GetPMI();
    uint32 aNewOmsFDIPCount = 0;
    uint32 aNewOmsFDIOCount = 0;
    uint32 aNewOmsPMICount  = 0;

    if(aOmsPii)
    {
        aNewOmsFDIPCount = aOmsPii->GetFDIP();
        aNewOmsFDIOCount = aOmsPii->GetFDIO();
        aNewOmsPMICount  = aOmsPii->GetPMI();
    }
        
    bool aOmsLosState = false;
    bool aOscLosState = false;
    uint32 aCount = 0;
    aOmsDefects.GetDefectStatus(CT_TEL_OMS_LOS_DEFECT, &aCount, &aOmsLosState);
    aUpstreamDefects.GetDefectStatus(CT_TEL_RS_LOS_DEFECT, &aCount, &aOscLosState);
    
    //OTS-LOS is made of OMS-LOS and OSC-LOS
    if(aOmsLosState && aOscLosState)
    {
        aOtsLosState = true;
        aOtsLosEvent = false;
    }

    //Disable all defects if upstream layer is failed
    if (IsUpstreamLayerFailed())
    {
        aOtsBDIPState=false;
        aOtsBDIPEvent=false;
        aOtsBDIOState=false;
        aOtsBDIOEvent=false;
        aOtsBDIState=false;
        aOtsBDIEvent=false;
        aOtsPMIState=false;
        aOtsPMIEvent=false;
        aOtsTIMState=false;
        aOtsTIMEvent=false;
        aOmsFDIPState=false;
        aOmsFDIPEvent=false;
        aOmsFDIOState=false;
        aOmsFDIOEvent=false;
        aOmsPMIState=false;
        aOmsPMIEvent=false;
    }
	else
	{

        // Update OTS BDI-P state and count
        if(myPiiOtsBDIPCount != aNewOtsBDIPCount)
        {
            aOtsBDIPEvent = true;
        }
        if(aNewOtsBDIPCount%2 != 0)
        {
            aOtsBDIPState = true;        
        }

        // Update OTS BDI-O state and count
        if(myPiiOtsBDIOCount != aNewOtsBDIOCount)
        {
            aOtsBDIOEvent = true;
        }
        if(aNewOtsBDIOCount%2 != 0)
        {
            aOtsBDIOState = true;        
        }

        // BDI is detected if both BDI-P and BDI-O are there.
		aOtsBDIState = aOtsBDIOState && aOtsBDIPState;
		aOtsBDIEvent = (aOtsBDIPState || aOtsBDIPEvent) && aOtsBDIOEvent
						||
					   (aOtsBDIOState || aOtsBDIOEvent) && aOtsBDIPEvent;

        // Update OTS PMI state and count
        if(myPiiOtsPMICount != aNewOtsPMICount)
        {
            aOtsPMIEvent = true;
        }
        if(aNewOtsPMICount%2 != 0)
        {
            aOtsPMIState = true;        
        }

        //Update TIM state and Count
        if (aConfig.GetTIMMonitoringEnable() == false)
        {
            aOtsTIMState=false;
            aOtsTIMEvent=false;
        }
        else
        {
            // Evaluate TIM only if trace is valid. NOTE: Default trace is not valid.
            if(aStatus.GetTraceMessage().IsValid())
            {
                aOtsTIMState = !(aStatus.GetTraceMessage().GetOperatorSpecific() == aConfig.GetExpectedTrace().GetOperatorSpecific());
            }
            else
            {
                aOtsTIMState = true;
            }
        }

        if (aOmsPii)
        {
            // Update OMS FDI-O state and count
            if(myPiiOmsFDIOCount != aNewOmsFDIOCount)
            {
                aOmsFDIOEvent = true;
            }
            if(aNewOmsFDIOCount%2 != 0)
            {
                aOmsFDIOState = true;        
            }

            // Update OMS FDI-P state and count
            if(myPiiOmsFDIPCount != aNewOmsFDIPCount)
            {
                aOmsFDIPEvent = true;
            }
            if(aNewOmsFDIPCount%2 != 0)
            {
                aOmsFDIPState = true;        
            }
        
            // Update OMS PMI state and count
            if(myPiiOmsPMICount != aNewOmsPMICount)
            {
                aOmsPMIEvent = true;
            }
            if(aNewOmsPMICount%2 != 0)
            {
                aOmsPMIState = true;        
            }            
        }
    }

    //Update local defect counts
    myPiiOtsBDIPCount = aNewOtsBDIPCount;
    myPiiOtsBDIOCount = aNewOtsBDIOCount;
    myPiiOtsPMICount  = aNewOtsPMICount;
    myPiiOmsFDIPCount = aNewOmsFDIPCount;
    myPiiOmsFDIOCount = aNewOmsFDIOCount;
    myPiiOmsPMICount  = aNewOmsPMICount;


    // update actual defect
    bool hasDefectsChanged = false;

    hasDefectsChanged |= aOtsDefects.SetDefectStatus(CT_TEL_OTS_LOS_DEFECT,         aOtsLosState,   aOtsLosEvent);

    bool hasOtsOHDefectsChanged = false;

    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OTS_TIM_DEFECT,         aOtsTIMState,   aOtsTIMEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OTS_BDIP_DEFECT,        aOtsBDIPState,  aOtsBDIPEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OTS_BDIO_DEFECT,        aOtsBDIOState,  aOtsBDIOEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OTS_BDI_DEFECT,         aOtsBDIState,   aOtsBDIEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OTS_PMI_DEFECT,         aOtsPMIState,   aOtsPMIEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OMS_FDIP_DEFECT,        aOmsFDIPState,  aOmsFDIPEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OMS_FDIO_DEFECT,        aOmsFDIOState,  aOmsFDIOEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.SetDefectStatus(CT_TEL_OMS_PMI_DEFECT,         aOmsPMIState,   aOmsPMIEvent);
    hasOtsOHDefectsChanged |= aOtsOHDefects.Validate();
    hasDefectsChanged |= aOtsDefects.Validate();

    if (hasDefectsChanged) 
    {
        GetMonIf().GetDefectsRegion()->IncModificationCounter();
    }
    
    if (hasOtsOHDefectsChanged) 
    {
        myOtsOHDefectsRegion.IncModificationCounter();
    }

    
}
   
