// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_FecIf.h>
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbReason.h>
#include <T6100_CardIf.h>
#include <CsPii/CSPII_CardIF.h>
#include "../MON_OtuUpdateStatusAction.h"
#include "../MON_OtuDefects.h"
#include "../MON_OtuCounters.h"
#include "../MON_OtuStatus.h"
#include "../MON_OtuConfig.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"


MON_OtuUpdateStatusAction::MON_OtuUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_FecRegion& theFecPiiRegion,
                                                     MON_AppIf* theUpstreamLayerIf):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myFecPiiRegion(theFecPiiRegion),
    myPiiAISCount(0),
    myPiiLOFCount(0),
    myPiiLOMFCount(0),
    myPiiFECMCount(0),
    myPiiBDICount(0),
    myPiiBerSdCount(0),
    myPiiIAECount(0),
    myPiiMateDefectCount(0),
    myLastDispCompInitState(false),
    myGoodTraceMessageCounter(0),
    myBadTraceMessageCounter(0),
    myNumConsecTraceComp(1),
    myFirstRcvdOtuTrace(true),
    myTimCheckByMon(true)    
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myFecPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

    // For most cards, we'll try the default number of consectutive trace messages 
    // needed to accept a new/different trace to be one (1).  If this needs to change 
    // for any card, change it here
    //T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
    //if (aCardContext)
    //{
    //    if (aCardContext->GetCardFamily() == ?)
    //    {
    //        myNumConsecTraceComp = ?;
    //    }
    //}
    if (CSPII_CardIF::GetInstance()->GetCardFamily() == OSM_FAM) 
    {
        myTimCheckByMon = false;
    }
    
}

MON_OtuUpdateStatusAction::~MON_OtuUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myFecPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_OtuUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    // make sure we notify client that we have become invalid (g709 mode was disabled)
    MON_Object& aStatus = (*GetMonIf().GetStatusRegion())[0];
    bool hasStatusChanged = aStatus.Invalidate();
    if (hasStatusChanged)
        GetMonIf().GetStatusRegion()->IncModificationCounter();
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}

FC_Object* MON_OtuUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    //Update status of object in region
    UpdateObject(theRunReason);
    return NULL;
}

void MON_OtuUpdateStatusAction::UpdateObject(unsigned theRunReason)
{
    MON_OtuDefects& aDefects   = static_cast<MON_OtuDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_OtuStatus& aStatus     = static_cast<MON_OtuStatus&>((*GetMonIf().GetStatusRegion())[0]);
    MON_OtuCounters& aCounters = static_cast<MON_OtuCounters&>((*GetMonIf().GetCountersRegion())[0]);
    MON_OtuConfig& aConfig     = static_cast<MON_OtuConfig&>((*GetMonIf().GetConfigRegion())[0]);
    TSPII_FecIf& aFecPII       = myFecPiiRegion[0];
    bool hasDefectsChanged = false;

    static CT_G709Trace aTrace, aDefaultTrace; //tmp buffer

    //--------------------------------------------------------------
    // CONFIG
    //Configure defect region to fail on TIM defect
    hasDefectsChanged |= aDefects.SetLayerFailOnTimEnable(aConfig.GetLayerFailOnTIM());

    // set Fail Layer Bit Mask for OTU
    aDefects.SetFailLayerBitMask(aConfig.GetFailLayerBitMask());
    
    //--------------------------------------------------------------
    // COUNTERS
    // For 64 bits, always read the high bits last
    aCounters.SetErrorCount(CT_TEL_OTU_BEI, aFecPII.GetBeiCount());
    aCounters.SetErrorCount(CT_TEL_OTU_HIGH_BEI, aFecPII.GetHighBeiCount());
    aCounters.SetErrorCount(CT_TEL_OTU_BIP8, aFecPII.GetBip8Count());
    aCounters.SetErrorCount(CT_TEL_OTU_HIGH_BIP8, aFecPII.GetHighBip8Count());

    // other FEC counts
    aCounters.SetErrorCount(CT_TEL_OTU_BYTE_CORRECTIONS,aFecPII.GetFECCorrectedBytesCount());
    aCounters.SetErrorCount(CT_TEL_OTU_HIGH_BYTE_CORRECTIONS,aFecPII.GetHighFECCorrectedBytesCount());
    aCounters.SetErrorCount(CT_TEL_OTU_BIT_ERROR_ON_ONES,aFecPII.GetBitErrorCountOnOnes());
    aCounters.SetErrorCount(CT_TEL_OTU_HIGH_BIT_ERROR_ON_ONES,aFecPII.GetHighBitErrorCountOnOnes());
    aCounters.SetErrorCount(CT_TEL_OTU_BIT_ERROR_ON_ZEROS,aFecPII.GetBitErrorCountOnZeros());
    aCounters.SetErrorCount(CT_TEL_OTU_HIGH_BIT_ERROR_ON_ZEROS,aFecPII.GetHighBitErrorCountOnZeros());
    aCounters.SetErrorCount(CT_TEL_OTU_UNCORRECTABLE_RSFRAMES, aFecPII.GetNonCorrectableRSFrameCount());
    aCounters.SetErrorCount(CT_TEL_OTU_HIGH_UNCORRECTABLE_RSFRAMES, aFecPII.GetHighNonCorrectableRSFrameCount());

    //--------------------------------------------------------------
    // STATUS (Part A) - Dispersion Compensation State is turned into a defect, so reas it here.
    bool hasStatusChanged = false;

    // Note: Since Agent does not need the Dispersion Compensation State 
    // (it is turned into a defect and used for LED behavior)
    // do not look at the return of the SetDispCompState method to update the changed flag.  
    // Therefore, the Status region modification counter will not be incremented 
    // due to a Dispersion Compensation state change.
    CT_TEL_DispCompState aDispCompState = aFecPII.GetDispCompState();
    (void) aStatus.SetDispCompState(aDispCompState);


    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects
    bool aAISState=false, aLOFState=false, aLOMFState=false, aFECMState=false, aBDIState=false, aTIMState=false, aBerSdState=false, aIAEState=false, aMateDefectState=false;
    bool aAISEvent=false, aLOFEvent=false, aLOMFEvent=false, aFECMEvent=false, aBDIEvent=false, aTIMEvent=false, aBerSdEvent=false, aIAEEvent=false, aMateDefectEvent=false;

    bool aDispCompInitState=false;
    bool aDispCompInitEvent=false;

    uint32 aNewAISCount   = aFecPII.GetAIS();
    uint32 aNewLOFCount   = aFecPII.GetLOF();
    uint32 aNewLOMFCount  = aFecPII.GetLOMF();
    uint32 aNewFECMCount  = aFecPII.GetFECM();
    uint32 aNewBDICount   = aFecPII.GetBDI();
    uint32 aNewBerSdCount = aFecPII.GetBerSd();
    uint32 aNewIAECount   = aFecPII.GetIAE();
    uint32 aNewMateDefectCount  = aFecPII.GetMateDefect();
    // Note: Dispersion Compensation defect is based on Status

    // if upstream layer is fail, force a AIS
    if (IsUpstreamLayerFailed())
    {
        aAISState = true;
        aAISEvent = false;
    }
    else
    {
        // Update AIS state and count
        if(myPiiAISCount != aNewAISCount)
        {
            aAISEvent = true;
        }
        if(aNewAISCount%2 != 0)
        {
            aAISState = true;        
        }
    }
    // AIS cause automatic LOF
    if (aAISState)
    {
        aLOFState=true;
        aLOFEvent=false;
    }
    else
    {
        // Update LOF state and count
        if(myPiiLOFCount != aNewLOFCount)
        {
            aLOFEvent = true;
        }
        if(aNewLOFCount%2 != 0)
        {
            aLOFState = true;        
        }
    }

    // ignore any LOMF if LOF
    if (aLOFState)
    {
        aLOMFState=false;
        aLOMFEvent=false;
    }
    else
    {
        // Update LOMF state and count
        if(myPiiLOMFCount != aNewLOMFCount)
        {
            aLOMFEvent = true;
        }
        if(aNewLOMFCount%2 != 0)
        {
            aLOMFState = true;        
        }
    }

    // ignore any FECM if LOF
    if (aLOFState)
    {
        aFECMState=false;
        aFECMEvent=false;
    }
    else
    {
        // Update FECM state and count
        if(myPiiFECMCount != aNewFECMCount)
        {
            aFECMEvent = true;
        }
        if(aNewFECMCount%2 != 0)
        {
            aFECMState = true;        
        }
    }

    // ignore any BDI if LOF
    if (aLOFState) 
    {
        aBDIState=false;
        aBDIEvent=false;
    }
    else
    {
        // Update BDI state and count
        if(myPiiBDICount != aNewBDICount)
        {
            aBDIEvent = true;
        }
        if(aNewBDICount%2 != 0)
        {
            aBDIState = true;        
        }
    }
    // Update IAE state and count
    if(myPiiIAECount != aNewIAECount)
    {
        aIAEEvent = true;
    }
    if(aNewIAECount%2 != 0)
    {
        aIAEState = true;        
    }

    // ignore any BerSD if LOF
    if (aLOFState) 
    {
        aBerSdState=false;
        aBerSdEvent=false;
    }
    else
    {
        // Update BerSD state and count
        if(myPiiBerSdCount != aNewBerSdCount)
        {
            aBerSdEvent = true;
        }
        if(aNewBerSdCount%2 != 0)
        {
            aBerSdState = true;        
        }
    }

    // Update Mate Defect state and count
    if(myPiiMateDefectCount != aNewMateDefectCount)
    {
        aMateDefectEvent = true;
    }
    if(aNewMateDefectCount%2 != 0)
    {
        aMateDefectState = true;        
    }

    // Update Dispersion Compensation Init State state and event based on Status 
    // and old state.  The state will be true if in any of the init states.
    if( (aDispCompState ==  CT_TEL_DISP_COMP_TDC_INIT)   ||
        (aDispCompState ==  CT_TEL_DISP_COMP_DLI_INIT)   ||
        (aDispCompState ==  CT_TEL_DISP_COMP_DEMUX_INIT) )
    {
        aDispCompInitState = true;        
    }
    if(myLastDispCompInitState != aDispCompInitState)
    {
        aDispCompInitEvent = true;
    }

    // Update local defect counts
    myPiiAISCount  = aNewAISCount;
    myPiiBDICount  = aNewBDICount;
    myPiiLOFCount  = aNewLOFCount;
    myPiiLOMFCount  = aNewLOMFCount;
    myPiiFECMCount = aNewFECMCount;
    myPiiBerSdCount  = aNewBerSdCount;
    myPiiIAECount  = aNewIAECount;
    myPiiMateDefectCount  = aNewMateDefectCount;
    myLastDispCompInitState = aDispCompInitState;

    // update actual defect
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_FECM_DEFECT, aFECMState,  aFECMEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_LOF_DEFECT,  aLOFState,   aLOFEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_LOMF_DEFECT,  aLOMFState,   aLOMFEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_AIS_DEFECT,  aAISState,   aAISEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_BDI_DEFECT,  aBDIState,   aBDIEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_SDBER_DEFECT,aBerSdState, aBerSdEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_IAE_DEFECT,  aIAEState,   aIAEEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_MATE_DEFECT,  aMateDefectState,   aMateDefectEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_UPPER_LAYER_FAIL_TA_DEFECT, IsUpstreamLayerFailed(),   false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_UPPER_LAYER_FAIL_NTA_DEFECT,IsUpstreamLayerFailedNTA(),false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_LOCK,IsUpstreamLayerLocked(),false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, IsUpstreamLayerInternalFailed(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, IsUpstreamLayerInternalPropagateNextLayer(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_INTERNAL_LOCK,  IsUpstreamLayerInternalLocked(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_TERM_LPBK, IsUpstreamLayerTermLpbk(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_DISP_COMP_INIT, aDispCompInitState,  aDispCompInitEvent);
	hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerFailedForMaintSig(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerInternalFailedForMaintSig(), false);
	
    //--------------------------------------------------------------
    // STATUS - Part B (the rest of the story)

    // Note: Since Agent does not need the BER value (PM reads it by polling every second),
    // do not look at the return of the SetBER method to update the changed flag.  
    // Therefore, the Status region modification counter will not be incremented due to a BER change.
    (void) aStatus.SetBER(aFecPII.GetBER());

    aTrace = aFecPII.GetRxTrace();
    
    // Check if trace is valid and if there is no defects that could invalidate it
    if (aTrace.IsValid() && !aAISState && !aLOFState && !aLOMFState)
    {
        // if trace read from PII is different than the trace in OTU STATUS, update it
        if (!(aStatus.GetTraceMessage() == aTrace))
        {
            // at all time, if trace is the same for myNumConsecTraceComp times, set it in OTU STATUS
            if ((myFirstRcvdOtuTrace) || (++myGoodTraceMessageCounter >= myNumConsecTraceComp))
            {
		        hasStatusChanged |= aStatus.SetTraceMessage(aTrace);
                myGoodTraceMessageCounter = 0;
                myBadTraceMessageCounter = 0;
                myFirstRcvdOtuTrace = false;
            }
        }
        else
        {
            myGoodTraceMessageCounter = 0;
            myBadTraceMessageCounter = 0;
        }
    }
    else // it is not valid
    {
        myGoodTraceMessageCounter = 0;

        // previousTrace must be different (myNumConsecTraceComp + 1) times before updating OTU STATUS
        if (++myBadTraceMessageCounter >= (myNumConsecTraceComp + 1))  
    	    hasStatusChanged |= aStatus.SetTraceMessage(CT_G709StandardDefaultTrace::GetInstance());
    }

    // AIS and LOF disabled TIM
    if (aConfig.GetTIMMonitoringEnable() == false)
    {
        aTIMState = false;
        aTIMEvent = false;
    }
    else if(aAISState || aLOFState || aLOMFState)
    {
        aTIMState = true;
        aTIMEvent = false;
    }
    else
    {
        if(aStatus.GetTraceMessage().IsValid())
        {
            if (myTimCheckByMon)
            {
                aTIMState = aStatus.GetTraceMessage().CompareByTIMCriteraMode(aConfig.GetExpectedTrace(), aConfig.GetTimCriteria());
            }
            else
            {
                uint32 aNewTIMCount = aFecPII.GetTIM();
                if (aNewTIMCount%2 != 0)
                {
                    aTIMState = true;     
                }
            }
        }
        else
            aTIMState = true;
    }

    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OTU_TIM_DEFECT, aTIMState,  aTIMEvent);  
    hasDefectsChanged |= aDefects.Validate();
    hasStatusChanged  |= aStatus.Validate();


    if (hasDefectsChanged) 
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();

    // validate object
    aCounters.Validate();

}
