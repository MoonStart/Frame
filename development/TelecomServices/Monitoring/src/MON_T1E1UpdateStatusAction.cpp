// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_T1E1If.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_T1E1UpdateStatusAction.h"
#include "../MON_T1E1Defects.h"
#include "../MON_T1E1Status.h"
#include "../MON_T1E1Config.h"
#include "../MON_Region.h"

MON_T1E1UpdateStatusAction::MON_T1E1UpdateStatusAction(MON_AppIf& theMonIf,
                                                       TSPII_T1E1Region& theT1E1PiiRegion,
                                                       MON_AppIf* theUpstreamLayerIf):
	MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myT1E1PiiRegion(theT1E1PiiRegion),
    myPiiLOSCount(0),
  	myPiiLOFCount(0),
    myPiiAISCount(0),
	myPiiOffFreqCount(0)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myT1E1PiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
}

MON_T1E1UpdateStatusAction::~MON_T1E1UpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myT1E1PiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
}

FC_Object* MON_T1E1UpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}


FC_Object* MON_T1E1UpdateStatusAction::Process(unsigned theRunReason,
                                               FC_Object* theInvokerObj,
                                               FC_Object* theParam)
{
    MON_T1E1Defects& aDefects   = static_cast<MON_T1E1Defects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_T1E1Status&  aStatus    = static_cast<MON_T1E1Status&>((*GetMonIf().GetStatusRegion())[0]);
    MON_T1E1Config&  aConfig    = static_cast<MON_T1E1Config&>((*GetMonIf().GetConfigRegion())[0]);
    TSPII_T1E1If&    aT1E1PII   = myT1E1PiiRegion[0];
    bool hasDefectsChanged      = false;

    //--------------------------------------------------------------
    // CONFIG
    // none for now
   
    //--------------------------------------------------------------


    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects

    bool aLayerLockedState = false;

    if(aConfig.GetLayerLocked())
    {   
        aLayerLockedState = true;
    }


    bool aLOSState=false, aLOFState=false, aAISState=false, aOffFreqState = false;
    bool aLOSEvent=false, aLOFEvent=false, aAISEvent=false, aOffFreqEvent = false;

    uint32 aNewLOSCount     = aT1E1PII.GetLos();
    uint32 aNewLOFCount     = aT1E1PII.GetLof();   
    uint32 aNewAISCount     = aT1E1PII.GetAis();
	uint32 aNewOffFreqCount = aT1E1PII.GetOffFreq();
    
    // Update LOS state and count
    if(myPiiLOSCount != aNewLOSCount)
    {
        aLOSEvent = true;
    }
    if(aNewLOSCount%2 != 0)
    {
        aLOSState = true;        
    }


    // LOS cause automatic LOF and AIS and OFF Freq
    if (aLOSState)
    {
        aLOFState=true;
        aLOFEvent=false;
        aAISState=true;
        aAISEvent=false;
		aOffFreqState = true;
        aOffFreqEvent = false;
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


        // Update AIS state and count
        if(myPiiAISCount != aNewAISCount)
        {
            aAISEvent = true;
        }
        if(aNewAISCount%2 != 0)
        {
            aAISState = true;             
        }

		// Update Off Freq state and count
        if(myPiiOffFreqCount != aNewOffFreqCount)
        {
            aOffFreqEvent = true;
        }
        if(aNewOffFreqCount%2 != 0)
        {
            aOffFreqState = true;             
        }

    }

    // Update local defect counts
    myPiiLOSCount     = aNewLOSCount;
    myPiiLOFCount     = aNewLOFCount;
    myPiiAISCount     = aNewAISCount;
	myPiiOffFreqCount = aNewOffFreqCount;


    // Update actual defect
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_T1E1_LOS_DEFECT,       aLOSState,         aLOSEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_T1E1_LOF_DEFECT,       aLOFState,         aLOFEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_T1E1_AIS_DEFECT,       aAISState,         aAISEvent); 
	hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_T1E1_OFF_FREQ_DEFECT,  aOffFreqState,     aOffFreqEvent);  

    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_T1E1_LOCK,        aLayerLockedState, false);

    // Validate defect object
    aDefects.Validate();

    //--------------------------------------------------------------
    // STATUS
    bool hasStatusChanged = false;

    //Read SSM value from PII
    CT_FAC_RxSsm aSsm = aT1E1PII.GetRxSsm();

    //Check if SSM are valid
    if (!aLOSState)
    {
        //If SSM read from PII is different than the SSM in STATUS region, update the status region
        if (aStatus.GetRxSsm() != aSsm)
        {
            hasStatusChanged |= aStatus.SetRxSsm(aSsm);
        }
    }

    if (hasDefectsChanged) 
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();
    
    // Validate status object
    aStatus.Validate();

    return NULL;
}
