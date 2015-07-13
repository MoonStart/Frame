// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_MsIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_MsUpdateStatusAction.h"
#include "../MON_MsDefects.h"
#include "../MON_MsCounters.h"
#include "../MON_MsStatus.h"
#include "../MON_MsConfig.h"
#include "../MON_Region.h"

MON_MsUpdateStatusAction::MON_MsUpdateStatusAction(MON_AppIf& theMonIf,
                                                   TSPII_MsRegion& theMsPiiRegion,
                                                   MON_AppIf* theUpstreamLayerIf,
                                                   MON_AppIf* theIMUXLayerIf):
	MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myMsPiiRegion(theMsPiiRegion),
    myIMUXLayerIf(theIMUXLayerIf),
  	myPiiAISCount(0),
    myPiiInternalAISLCount(0),
    myPiiPropreitaryInternalAISLCount(0),
    myPiiRDICount(0),
    myPiiSdBerCount(0),
    myPiiSfBerCount(0)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myMsPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    if(myIMUXLayerIf) GetBbAction()->AddInputRegion(myIMUXLayerIf->GetDefectsRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

}

MON_MsUpdateStatusAction::~MON_MsUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myMsPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    if(myIMUXLayerIf) GetBbAction()->RemoveInputRegion(myIMUXLayerIf->GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_MsUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}


FC_Object* MON_MsUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    MON_MsDefects& aDefects   = static_cast<MON_MsDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_MsStatus& aStatus     = static_cast<MON_MsStatus&>((*GetMonIf().GetStatusRegion())[0]);
    MON_MsCounters& aCounters = static_cast<MON_MsCounters&>((*GetMonIf().GetCountersRegion())[0]);
    MON_MsConfig& aConfig     = static_cast<MON_MsConfig&>((*GetMonIf().GetConfigRegion())[0]);
    TSPII_MsIf& aMsPII        = myMsPiiRegion[0];
    bool hasDefectsChanged = false;

    uint32 aMsDefectCount = 0;
    bool   aMsDefectState = false;

    //--------------------------------------------------------------
    // CONFIG
    aMsPII.SetBerSfThreshold(aConfig.GetBerSfThreshold());
    aMsPII.SetBerSdThreshold(aConfig.GetBerSdThreshold());

    // set Fail Layer Bit Mask for MS
    aDefects.SetFailLayerBitMask(aConfig.GetFailLayerBitMask());

    //--------------------------------------------------------------
    // COUNTERS
    aCounters.SetErrorCount(CT_TEL_MS_B2,aMsPII.GetCvCount());
    aCounters.SetErrorCount(CT_TEL_MS_REI,aMsPII.GetReiCount());

    // Validate Counter region
    aCounters.Validate();

    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects

    bool aAISState=false, aInternalAISLState=false, aPropreitaryInternalAISLState=false;
    bool aAISEvent=false, aInternalAISLEvent=false, aPropreitaryInternalAISLEvent=false;
    bool aRDIState=false, aSdBerState=false, aSfBerState=false, aUpstreamLayerFailTAState=false;
    bool aRDIEvent=false, aSdBerEvent=false, aSfBerEvent=false, aUpstreamLayerFailNTAState=false;
    bool aIMUXLockState=false;

    uint32 aNewAISCount   = aMsPII.GetAis();
    uint32 aNewRDICount   = aMsPII.GetRdi();
    uint32 aNewSdBerCount = aMsPII.GetBerSd();    
    uint32 aNewSfBerCount = aMsPII.GetBerSf(); 

    bool aRefState=false;
    bool aRefEvent=false;
    bool aRefValid        = aMsPII.GetIsTimingRefValid();
 

    // If there, Update M layer defects with IMUX facility
    if(myIMUXLayerIf)
    {
        MON_Defects& aIMUXDefects = static_cast<MON_Defects&>( (*myIMUXLayerIf->GetDefectsRegion())[0] );

        // Update AIS state 
        aIMUXDefects.GetDefectStatus(CT_TEL_MS_AIS_DEFECT, &aMsDefectCount, &aMsDefectState);
        if(aMsDefectState)
        {
            aAISState = true;        
        }

        // Update Internal AIS-L state 
        aIMUXDefects.GetDefectStatus(CT_TEL_MS_INTERNAL_AISL_DEFECT, &aMsDefectCount, &aMsDefectState);
        if(aMsDefectState)
        {
            aInternalAISLState = true;        
        }

        // Update Internal AIS-L state 
        aIMUXDefects.GetDefectStatus(CT_TEL_MS_PROPRIETARY_INTERNAL_AISL_DEFECT, &aMsDefectCount, &aMsDefectState);
        if(aMsDefectState)
        {
            aPropreitaryInternalAISLState = true;        
        }

        // Update SFBER state 
        aIMUXDefects.GetDefectStatus(CT_TEL_MS_SFBER_DEFECT, &aMsDefectCount, &aMsDefectState);
        if(aMsDefectState)
        {
            aSfBerState = true;        
        }

        // Update SDBER state 
        aIMUXDefects.GetDefectStatus(CT_TEL_MS_SDBER_DEFECT, &aMsDefectCount, &aMsDefectState);
        if(aMsDefectState)
        {
            aSdBerState = true;        
        }

        // Update Lock state 
        aIMUXDefects.GetDefectStatus(CT_TEL_MS_LOCK, &aMsDefectCount, &aMsDefectState);
        if(aMsDefectState)
        {
            aIMUXLockState = true;        
        }

    }
    
    // Upstream layer in failure sets AIS state but not AIS event
    if (IsUpstreamLayerFailed())
    {
        aUpstreamLayerFailTAState = true;
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

    if (IsUpstreamLayerFailedNTA())
    {
        aUpstreamLayerFailNTAState = true;
    }

    // Update SfBer and SdBer state and count
    // When AIS state is true, set SFBer and SDBer states but not their events
    if (aAISState)
    {
        aSfBerState=true;
        aSfBerEvent=false;
        aSdBerState=true;
        aSdBerEvent=false;
    }
    else
    {
        // Update SfBer state and count based on TsPii
        if(myPiiSfBerCount != aNewSfBerCount)
        {
            aSfBerEvent = true;
        }
        if(aNewSfBerCount%2 != 0)
        {
            aSfBerState = true;        
        }
        
        // Update SdBer state and count based on TsPii
        if(myPiiSdBerCount != aNewSdBerCount)
        {
            aSdBerEvent = true;
        }
        if(aNewSdBerCount%2 != 0)
        {
            aSdBerState = true;        
        }
    }

    // Update RDI state and count
    if(myPiiRDICount != aNewRDICount)
    {
        aRDIEvent = true;
    }
    if(aNewRDICount%2 != 0)
    {
        aRDIState = true;        
    }

    // Update Ref state and count
    if (aRefValid == false) 
    {
        aRefState = true;
    }


    // Look at Line to Port Defect(s)
    // Update Internal AIS-L and Proprietary AIS-L state and count
    // if upstream layer is fail, force a AIS
    
    uint32 aNewInternalAISLCount   = aMsPII.GetInternalAis();
    uint32 aNewPropreitaryInternalAISLCount   = aMsPII.GetProprietaryInternalAis();

    // Update Internal AIS state and count
    if(myPiiInternalAISLCount != aNewInternalAISLCount)
    {
        aInternalAISLEvent = true;
    }
    if(aNewInternalAISLCount%2 != 0)
    {
        aInternalAISLState = true;        
    }

    // Update Proprietary Internal AIS state and count
    if(myPiiPropreitaryInternalAISLCount != aNewPropreitaryInternalAISLCount)
    {
        aPropreitaryInternalAISLEvent = true;
    }
    if(aNewPropreitaryInternalAISLCount%2 != 0)
    {
        aPropreitaryInternalAISLState = true;        
    }

    // Update local defect counts
    myPiiInternalAISLCount   = aNewInternalAISLCount;
    myPiiPropreitaryInternalAISLCount   = aNewPropreitaryInternalAISLCount;

    myPiiSfBerCount = aNewSfBerCount;
    myPiiSdBerCount = aNewSdBerCount;
    myPiiAISCount   = aNewAISCount;
    myPiiRDICount   = aNewRDICount;

    // Update actual defect
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_AIS_DEFECT,  aAISState,  aAISEvent);
    // Also have proprietary internal AIS cause regular internal AIS (Propritary is a special case,
    // but we still want the same behavior as regular internal AIS (i.e., alarm).
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_INTERNAL_AISL_DEFECT,  aInternalAISLState || aPropreitaryInternalAISLState,  aInternalAISLEvent || aPropreitaryInternalAISLEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_PROPRIETARY_INTERNAL_AISL_DEFECT,  aPropreitaryInternalAISLState,  aPropreitaryInternalAISLEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_RDI_DEFECT,  aRDIState,  aRDIEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_SFBER_DEFECT,  aSfBerState,  aSfBerEvent);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_SDBER_DEFECT,  aSdBerState,  aSdBerEvent); 
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_REF_DEFECT,  aRefState,  aRefEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_UPPER_LAYER_FAIL_TA_DEFECT, aUpstreamLayerFailTAState, false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_UPPER_LAYER_FAIL_NTA_DEFECT,aUpstreamLayerFailNTAState,false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_LOCK,IsUpstreamLayerLocked()||aIMUXLockState,false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, IsUpstreamLayerInternalFailed(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerInternalFailedForMaintSig(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_INTERNAL_LOCK, IsUpstreamLayerInternalLocked(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_TERM_LPBK, IsUpstreamLayerTermLpbk(), false);
	hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MS_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerFailedForMaintSig(), false);
	
    // Validate defect object
    aDefects.Validate();

    //--------------------------------------------------------------
    // STATUS
    bool hasStatusChanged = false;

    //Read K1 & K2 bytes from PII
    uint8 aK1            = aMsPII.GetK1RxByte();
    uint8 aK2            = aMsPII.GetK2RxByte();
    uint8 aRxCsi         = aMsPII.GetRxCsi();
    CT_FAC_RxSsm aRxSsm  = aMsPII.GetRxSsm();


    //Check if K1/K2 are valid
    if (!aAISState)
    {
        //If K1/K2 read from PII is different than the K1/K2 in STATUS region, update the status region
        if ((aStatus.GetK1RxByte() != aK1) || (aStatus.GetK2RxByte() != aK2))
        {
            hasStatusChanged |= aStatus.SetK1RxByte(aK1);
            hasStatusChanged |= aStatus.SetK2RxByte(aK2);
        }
    }

    //Only process SSM on an interface whose upper layer is good.  SSM toggles on the port-side of
    //an SMTMU when port-side LOS exists.
    if (IsUpstreamLayerFailed() == false)
    {
        //If Rx Ssm read from PII is different than the Rx Ssm in STATUS region, update the status region
        if (aStatus.GetRxSsm() != aRxSsm) 
        {
            hasStatusChanged |= aStatus.SetRxSsm(aRxSsm);
        }
    }

    //Only process CSI on an interface whose upper layer is good.
    //If Rx Csi read from PII is different than the Rx Csi in STATUS region, update the status region
    if (IsUpstreamLayerFailed() == false)
    {
        if (aStatus.GetRxCsi() != aRxCsi) 
		{
            hasStatusChanged |= aStatus.SetRxCsi(aRxCsi);
		}
	}
	else
	{
		hasStatusChanged |= aStatus.SetRxCsi(255); //Default invalid csi value
	}


    if (hasDefectsChanged) 
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();
    
    // Validate status object
    aStatus.Validate();

    return NULL;
}
