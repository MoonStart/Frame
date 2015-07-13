// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_RsIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include <CsPii/CSPII_CardIF.h>
#include "../MON_AppIf.h"
#include "../MON_RsUpdateStatusAction.h"
#include "../MON_RsDefects.h"
#include "../MON_RsCounters.h"
#include "../MON_RsStatus.h"
#include "../MON_RsConfig.h"
#include "../MON_Region.h"

//##ModelId=3C164B12000E
MON_RsUpdateStatusAction::MON_RsUpdateStatusAction(MON_AppIf& theMonIf,
                                                   TSPII_RsRegion& theRsPiiRegion,
                                                   MON_AppIf* theUpstreamLayerIf,
                                                   MON_AppIf* theAltUpstreamLayerIf,
                                                   MON_AppIf* theIMUXLayerIf,
                                                   bool       theSuppressTlabAISRead):
	MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myRsPiiRegion(theRsPiiRegion),
    myAltUpstreamLayerIf(theAltUpstreamLayerIf),
    myIMUXLayerIf(theIMUXLayerIf),
    myGoodTraceMessageCounter(0),
    myBadTraceMessageCounter(0),
  	myPiiOOFCount(0),
    myPiiLOSCount(0),
    myPiiLOFCount(0),
    myPiiTlabAISCount(0),
    myPiiGenAISCount(0),
    myPiiInternalGenAISCount(0),
    myPiiInternalLOFCount(0),
    myPiiInternalCSFOPUCount(0),
    myPiiLocalFaultCount(0),
    myPiiRemoteFaultCount(0),
    myFirstRcvdRsTrace(true),
    mySuppressTlabAISRead(theSuppressTlabAISRead),
    myTimCheckByMon(true)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myRsPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    if(myAltUpstreamLayerIf) GetBbAction()->AddInputRegion(myAltUpstreamLayerIf->GetDefectsRegion());
    if(myIMUXLayerIf) GetBbAction()->AddInputRegion(myIMUXLayerIf->GetDefectsRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

    if (CSPII_CardIF::GetInstance()->GetCardFamily() == OSM_FAM) 
    {
        myTimCheckByMon = false;
    }    
}

//##ModelId=3C164B12002C
MON_RsUpdateStatusAction::~MON_RsUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myRsPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    if(myAltUpstreamLayerIf) GetBbAction()->RemoveInputRegion(myAltUpstreamLayerIf->GetDefectsRegion());
    if(myIMUXLayerIf) GetBbAction()->RemoveInputRegion(myIMUXLayerIf->GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_RsUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}


//##ModelId=3C3B52F6018B
FC_Object* MON_RsUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    MON_RsDefects& aDefects   = static_cast<MON_RsDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_RsStatus& aStatus     = static_cast<MON_RsStatus&>((*GetMonIf().GetStatusRegion())[0]);
    MON_RsCounters& aCounters = static_cast<MON_RsCounters&>((*GetMonIf().GetCountersRegion())[0]);
    MON_RsConfig& aConfig     = static_cast<MON_RsConfig&>((*GetMonIf().GetConfigRegion())[0]);

    TSPII_RsIf& aRsPII        = myRsPiiRegion[0];
    bool hasDefectsChanged = false;

    uint32 aRsDefectCount = 0;
    bool   aRsDefectState = false;

    static CT_SDH16ByteTrace aTrace, aDefaultTrace; //tmp buffer

    //--------------------------------------------------------------
    // CONFIG
    //Configure defect region to fail on TIM defect
    hasDefectsChanged |= aDefects.SetLayerFailOnTimEnable(aConfig.GetLayerFailOnTIM());

    // set Fail Layer Bit Mask for RS
    aDefects.SetFailLayerBitMask(aConfig.GetFailLayerBitMask());

    // Note that Agent is now writing down cross connect informatiom, namely
    // bool SetIsConnectedAsSrc(bool theState);
    // bool SetIsConnectedAsDst(bool theState);
    // But this information is converted to a defect (see below) 
    // and not written down to TSPII

    //--------------------------------------------------------------
    // COUNTERS
    // For 64 bits, always read the high bits last
    aCounters.SetErrorCount(CT_TEL_RS_B1,aRsPII.GetCVCount());
    aCounters.SetErrorCount(CT_TEL_RS_HIGH_B1,aRsPII.GetHighCVCount());

    // Validate Counter region
    aCounters.Validate();

    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects

    bool aAISTxState=false, aTlabAISTxState=false, aLOSState=false, aPiiLOSState=false, aLOFState=false, aOOFState=false, aTlabAISState=false, aTIMState=false;
    bool aAISTxEvent=false, aTlabAISTxEvent=false, aLOSEvent=false, aPiiLOSEvent=false, aLOFEvent=false, aOOFEvent=false, aTlabAISEvent=false, aTIMEvent=false;
    bool aUpperLayerFailTAState=false;
    bool aUpperLayerFailNTAState=false;
    bool aUpperLayerLocked=false;
    bool aIMUXLockState=false;
    bool aUpperInternalInPropagateNextLayer=false;

    bool aInternalLOFState=false;
    bool aInternalLOFEvent=false;
    bool aInternalCSFOPUState=false;
    bool aInternalCSFOPUEvent=false;
    bool aLocalFaultState=false;
    bool aRemoteFaultState=false;
    bool aLocalFaultEvent=false;
    bool aRemoteFaultEvent=false;

    bool aGenAISState = false;
    bool aGenAISEvent = false;

    bool aInternalGenAISState = false;
    bool aInternalGenAISEvent = false;


    uint32 aNewOOFCount = aRsPII.GetOOF();
    uint32 aNewLOSCount = aRsPII.GetLOS();
    uint32 aNewLOFCount = aRsPII.GetLOF();    
    uint32 aNewTlabAISCount = aRsPII.GetTlabAISRx();    
    
    uint32 aNewInternalLOFCount  = aRsPII.GetInternalLOF();
    uint32 aNewInternalCSFOPUCount  = aRsPII.GetInternalCSFOPU();

    uint32 aNewLocalFaultCount  = aRsPII.GetLocalFault();
    uint32 aNewRemoteFaultCount = aRsPII.GetRemoteFault();

    uint32 aNewGenAisCount = aRsPII.GetGENAIS();
    uint32 aNewInternalGenAisCount = aRsPII.GetInternalGENAIS();
    
    // If there, Update M layer defects with IMUX facility
    if(myIMUXLayerIf)
    {
        MON_Defects& aIMUXDefects = static_cast<MON_Defects&>( (*myIMUXLayerIf->GetDefectsRegion())[0] );

        // Update LOS state 
        aIMUXDefects.GetDefectStatus(CT_TEL_RS_LOS_DEFECT, &aRsDefectCount, &aRsDefectState);
        if(aRsDefectState)
        {
            aLOSState = true;        
        }

        // Update LOF state 
        aIMUXDefects.GetDefectStatus(CT_TEL_RS_LOF_DEFECT, &aRsDefectCount, &aRsDefectState);
        if(aRsDefectState)
        {
            aLOFState = true;        
        }

        // Update TlabAIS state 
        aIMUXDefects.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT, &aRsDefectCount, &aRsDefectState);
        if(aRsDefectState)
        {
            aTlabAISState = true;        
        }

        // Update Lock state 
        aIMUXDefects.GetDefectStatus(CT_TEL_RS_LOCK, &aRsDefectCount, &aRsDefectState);
        if(aRsDefectState)
        {
            aIMUXLockState = true;        
        }

        // Update GenAIS state 
        aIMUXDefects.GetDefectStatus(CT_TEL_RS_GENAIS_DEFECT, &aRsDefectCount, &aRsDefectState);
        if(aRsDefectState)
        {
            aGenAISState = true;        
        }

    }

    // Update Upstream or Alternate Upstream layer defects
    if(myAltUpstreamLayerIf)
    {
        MON_Defects& aAltUpstreamDefects = static_cast<MON_Defects&>( (*myAltUpstreamLayerIf->GetDefectsRegion())[0] );

        if(aAltUpstreamDefects.IsLayerInDefects())
        {
            aUpperLayerFailTAState = true;
            aLOSState = true;
            aLOSEvent = false;
        }

        if(aAltUpstreamDefects.IsLayerInDefectsNTA())
        {
            aUpperLayerFailNTAState = true;
        }

        if(aAltUpstreamDefects.IsLayerLocked())
        {
            aUpperLayerLocked = true;
        }
    }
    if (IsUpstreamLayerFailed())
    {
        aUpperLayerFailTAState = true;
        aLOSState = true;
        aLOSEvent = false;
    }
    if (IsUpstreamLayerFailedNTA())
    {
        aUpperLayerFailNTAState = true;
    }
    if (IsUpstreamLayerLocked())
    {
        aUpperLayerLocked = true;
    }
    if (IsUpstreamLayerInternalPropagateNextLayer())
    {
        aUpperInternalInPropagateNextLayer = true;
    }

    if(!aLOSState)
    {
        // Update Los state and count
        if(myPiiLOSCount != aNewLOSCount)
        {
            aLOSEvent = true;
        }
        if(aNewLOSCount%2 != 0)
        {
            aLOSState = true;        
        }
    }

    //--------------------------------------------------------------
    // As a Service to PM, please keep track of the 
    // actual Pii RS Los Count/Event information irregardles
    // of any other indicators or UpperLayer issues.
    //--------------------------------------------------------------
    if(myPiiLOSCount != aNewLOSCount)
    {
        aPiiLOSEvent = true;
    }
    if(aNewLOSCount%2 != 0)
    {
        aPiiLOSState = true;        
    }

    // LOS cause automatic LOF and OOF
	// NOTE: LOS (and Upstream Layer failure) do not cause
	// automatic TLAB AIS. This is so that auto-rate lock
	// algorithm has an indication of the true defects on
	// an interface.
    if (aLOSState)
    {
        aLOFState=true;
        aLOFEvent=false;
        aOOFState=true;
        aOOFEvent=false;
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

        // Update OOF state and count
        if(myPiiOOFCount != aNewOOFCount)
        {
            aOOFEvent = true;
        }
        if(aNewOOFCount%2 != 0)
        {
            aOOFState = true;        
        }
    }


    // Update TlabAIS state and count
    // Note: On cards that support AutoRateLock, MON needs to always read 
    // TSPII for the value (even if there is an higher/upper layer defect).
    // This is because TlabAIS is used to kick the Auto Rate Lock process 
    // and could be off when the a defect like OPT LosClk is on.
    //
    // However, on cards that don't support AutoRateLock, it is desirable 
    // that MON supressed the TlabAIS read from TSPII and automatically
    // sets the  defect state when a higher/upper layer defect is present,
    // which is limit processing time in case this defect toggles
    // and constantly runs CFG Automatic Actions. 
    // 
    // The behavior is controlled by the mySuppressTlabAISRead variable,
    // which is set up in the SubApplication method when this action 
    // is created. 
    if (mySuppressTlabAISRead && aLOSState)
    {
        aTlabAISState=true;
        aTlabAISEvent=false;
    }
    // When desires (i.e., on an AutoRateLock card or when there
    // are no higher defects, read TlabAIS from TSPII
    else
    {
        if(myPiiTlabAISCount != aNewTlabAISCount)
        {
            aTlabAISEvent = true;
        }
        if(aNewTlabAISCount%2 != 0)
        {
            aTlabAISState = true;        
        }
    }

    // Update AIS transmitted defect
    aAISTxState = aRsPII.GetForceAIS();
    // Update AIS transmitted defect
    aTlabAISTxState = aRsPII.GetForceTlabAIS();


    // Update Internal LOF state and count
    if(myPiiInternalLOFCount != aNewInternalLOFCount)
    {
        aInternalLOFEvent = true;
    }
    if(aNewInternalLOFCount%2 != 0)
    {
        aInternalLOFState = true;        
    }

    // Update Internal CSF-OPU state and count
    if(myPiiInternalCSFOPUCount != aNewInternalCSFOPUCount)
    {
        aInternalCSFOPUEvent = true;
    }
    if(aNewInternalCSFOPUCount%2 != 0)
    {
        aInternalCSFOPUState = true;        
    }

    // Update GEN-AIS state and count
    if(myPiiGenAISCount != aNewGenAisCount)
    {
        aGenAISEvent = true;
    }
    if(aNewGenAisCount%2 != 0)
    {
        aGenAISState = true;        
    }

    // Update Internal GEN-AIS state and count
    if(myPiiInternalGenAISCount != aNewInternalGenAisCount)
    {
        aInternalGenAISEvent = true;
    }
    if(aNewInternalGenAisCount%2 != 0)
    {
        aInternalGenAISState = true;        
    }

    if(!aLocalFaultState)
    {
        // Update Local Fault state and count
        if(myPiiLocalFaultCount != aNewLocalFaultCount)
        {
            aLocalFaultEvent = true;
        }
        if(aNewLocalFaultCount%2 != 0)
        {
            aLocalFaultState = true;        
        }
    }

    if(!aRemoteFaultState)
    {
        // Update Remote Fault state and count
        if(myPiiRemoteFaultCount != aNewRemoteFaultCount)
        {
            aRemoteFaultEvent = true;
        }
        if(aNewRemoteFaultCount%2 != 0)
        {
            aRemoteFaultState = true;        
        }
    }

    // Update local defect counts
    myPiiOOFCount = aNewOOFCount;
    myPiiLOSCount = aNewLOSCount;
    myPiiLOFCount = aNewLOFCount;
    myPiiTlabAISCount = aNewTlabAISCount;
    myPiiInternalLOFCount  = aNewInternalLOFCount;
    myPiiInternalCSFOPUCount  = aNewInternalCSFOPUCount;
    myPiiLocalFaultCount  = aNewLocalFaultCount;
    myPiiRemoteFaultCount = aNewRemoteFaultCount;
    myPiiGenAISCount = aNewGenAisCount;
    myPiiInternalGenAISCount = aNewInternalGenAisCount;

    // Update actual defect
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_AIS_TX_DEFECT,  aAISTxState,  aAISTxEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_TLABAIS_TX_DEFECT,  aTlabAISTxState,  aTlabAISTxEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_LOS_DEFECT,  aLOSState,  aLOSEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_PII_RS_LOS_DEFECT,  aPiiLOSState,  aPiiLOSEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_LOF_DEFECT,  aLOFState,  aLOFEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_OOF_DEFECT,  aOOFState,  aOOFEvent);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT,  aTlabAISState,  aTlabAISEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_GENAIS_DEFECT , aGenAISState, aGenAISEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_INTERNAL_GENAIS_DEFECT , aInternalGenAISState, aInternalGenAISEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_UPPER_LAYER_FAIL_TA_DEFECT, aUpperLayerFailTAState, false);
	hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerFailedForMaintSig(), false);
	hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_UPPER_LAYER_FAIL_NTA_DEFECT,aUpperLayerFailNTAState,false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_LOCK,aUpperLayerLocked||aIMUXLockState,false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_IS_SRC,aConfig.GetIsConnectedAsSrc(),false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_IS_DST,aConfig.GetIsConnectedAsDst(),false);
    // Note: aUpperInternalInPropagateNextLayer fails the internal upper layer and does not pass through the Rs layer
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, IsUpstreamLayerInternalFailed()||aUpperInternalInPropagateNextLayer, false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerInternalFailedForMaintSig()||aUpperInternalInPropagateNextLayer, false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_INTERNAL_LOCK, IsUpstreamLayerInternalLocked(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, false, false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_TERM_LPBK, IsUpstreamLayerTermLpbk(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_INTERNAL_LOF_DEFECT,  aInternalLOFState,  aInternalLOFEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_INTERNAL_CSF_OPU_DEFECT,  aInternalCSFOPUState,  aInternalCSFOPUEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_LOCAL_FAULT_DEFECT,  aLocalFaultState,  aLocalFaultEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_REMOTE_FAULT_DEFECT, aRemoteFaultState, aRemoteFaultEvent);
    

    // Validate defect object
    hasDefectsChanged |= aDefects.Validate();

    //--------------------------------------------------------------
    // STATUS
    bool hasStatusChanged = false;

    //Read trace from PII
    aTrace = aRsPII.GetRxTrace();
	//Read signal type
	CT_TEL_SignalType aSignalType = aRsPII.GetSignalType();

    //Check if trace is valid
    if (aTrace.IsValid() && !aLOSState && !aLOFState && (aSignalType != CT_TEL_SIGNAL_UNKNOWN))
    {
        //If trace read from PII is different than the trace in STATUS region, update it
        if ((!(aStatus.GetReceivedTrace() == aTrace)) || (!(aStatus.GetReceivedTrace().IsValid() == aTrace.IsValid())))
        {
            //At all time, if trace is the same for 5 times, set it in STATUS region
            if ((myFirstRcvdRsTrace) || (++myGoodTraceMessageCounter == 4))
            {
                hasStatusChanged |= aStatus.SetReceivedTrace(aTrace);
                myGoodTraceMessageCounter = 0;
                myBadTraceMessageCounter = 0;
                myFirstRcvdRsTrace = false;
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

        //PreviousTrace must be different 30 times before updating STATUS region
        if (++myBadTraceMessageCounter == 30)
		{
    	    hasStatusChanged |= aStatus.SetReceivedTrace(aDefaultTrace);
    }

		//Soak defect before allowing layer to be failed
		if (myBadTraceMessageCounter < 30)
		{
			//Disable configuring defect region to fail on TIM defect
            aDefects.SetLayerFailOnTimEnable(false);
		}
    }

    // LOS and LOF and TlabAIS disabled TIM
    if (aConfig.GetTIMMonitoringEnable() == false)
    {
        aTIMState = false;
        aTIMEvent = false;
    }
	else if (aSignalType == CT_TEL_SIGNAL_UNKNOWN)
	{
		aTIMState = false;
        aTIMEvent = false;
	}
    else if(aLOSState || aLOFState || aTlabAISState )
    {
        aTIMState = true;
        aTIMEvent = false;
    }
    else
    {
        //Update TIM state and Count
        if((aStatus.GetReceivedTrace().IsValid()) && (aTrace.IsValid()))
        {
            if (myTimCheckByMon)
            {
                aTIMState = !(aStatus.GetReceivedTrace() == aConfig.GetExpectedTrace());
            }
            else
            {  
                uint32 aNewTIMCount = aRsPII.GetTIM();
                if (aNewTIMCount%2 != 0)
                {
                    aTIMState = true;     
                }
            }
        }
        else
        {
            aTIMState  = true;
        }
    }

    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_RS_TIM_DEFECT,  aTIMState,  aTIMEvent);  
    hasStatusChanged |= aStatus.Validate();


    if (hasDefectsChanged) 
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();
    

    return NULL;
}
