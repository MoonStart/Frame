// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_VcgIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_VcgUpdateStatusAction.h"
#include "../MON_VcgDefects.h"
#include "../MON_VcgConfig.h"
#include "../MON_Region.h"


MON_VcgUpdateStatusAction::MON_VcgUpdateStatusAction(MON_AppIf& theMonIf,
                                                     MON_AppIf* theUpstreamLayerIf,
                                                     uint16 theMaxVcgs):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myUpstreamLayerIf(theUpstreamLayerIf),
    myMaxVcgs(theMaxVcgs)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);

}

MON_VcgUpdateStatusAction::~MON_VcgUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
}

FC_Object* MON_VcgUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    return NULL;
}


FC_Object* MON_VcgUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
  for (uint16 anIndex = 0; anIndex < myMaxVcgs; anIndex++)
  {

    MON_VcgDefects& aDefects    = static_cast<MON_VcgDefects&>((*GetMonIf().GetDefectsRegion())[anIndex]);
    MON_VcgConfig&  aConfig     = static_cast<MON_VcgConfig&>((*GetMonIf().GetConfigRegion())[anIndex]);

    bool hasDefectsChanged = false;
    //bool vcgDefectsChanged = false;

    uint32 aHopDefectCount = 0;
    bool   aHopDefectState = false;
    CT_FAC_StsMap aHopList = aConfig.GetHopIdList();

    //--------------------------------------------------------------
    // CONFIG
    // Need to look at Config to decide action
    //

    // Only look at Hops if the Group is enabled
    if (aConfig.GetGroupOfHopsEnable())
    {
        //--------------------------------------------------------------
        // DEFECTS
        // Read current defects from upper layer and if any state is true, set the

        bool aAISState=false, aLOPState=false, aUNEQState=false;
        bool aPLMState=false, aTIMState=false, aRDIState=false;
        bool aSdBerState=false, aSfBerState=false;
        bool aUpstreamLayerFailTAState=false, aUpstreamLayerFailNTAState=false, aLockState=false;

        bool aAISEvent=false, aLOPEvent=false, aUNEQEvent=false;
        bool aPLMEvent=false, aTIMEvent=false, aRDIEvent=false;
        bool aSdBerEvent=false, aSfBerEvent=false;

        // Now loop through each Hop, beginning with the start channel of the entire 22V
        for (uint16 a2Index = 0; a2Index < 192; a2Index++)
        {
            if (myUpstreamLayerIf != NULL)
            {
                if (aHopList.IsInUse((uint8)a2Index))
                {
                    MON_Defects& aHopDefects = static_cast<MON_Defects&>( (*myUpstreamLayerIf->GetDefectsRegion())[a2Index] );

                    // Update AIS state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_AIS_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aAISState = true;
                    }

                    // Update LOP state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_LOP_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aLOPState = true;
                    }

                    // Update UNEQ state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_UNEQ_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aUNEQState = true;
                    }

                    // Update PLM state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_PLM_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                       aPLMState = true;
                    }

                    // Update TIM state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_TIM_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aTIMState = true;
                    }

                    // Update RDI state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_RDI_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aRDIState = true;
                    }

                    // Update SfBer state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_SFBER_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aSfBerState = true;
                    }

                    // Update SdBer state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_SDBER_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aSdBerState = true;
                    }

                    // Update Lock state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_UPPER_LAYER_FAIL_TA_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                       aUpstreamLayerFailTAState = true;
                    }

                    // Update Lock state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_UPPER_LAYER_FAIL_NTA_DEFECT, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aUpstreamLayerFailNTAState = true;
                    }

                    // Update Lock state
                    aHopDefects.GetDefectStatus(CT_TEL_HOP_LOCK, &aHopDefectCount, &aHopDefectState);
                    if(aHopDefectState)
                    {
                        aLockState = true;
                    }
                }

            }  // if (myUpstreamLayerIf != NULL)
        }  // for (uint16 a2Index = aStartChannel; a2Index < aStartChannel + CT_TEL_VCG_STS1_22V_HOP_CNT; a2Index++)

        // Update actual defect
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_AIS_DEFECT,  aAISState,  aAISEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_LOP_DEFECT,  aLOPState,  aLOPEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_UNEQ_DEFECT, aUNEQState, aUNEQEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_PLM_DEFECT,  aPLMState,  aPLMEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_TIM_DEFECT,  aTIMState,  aTIMEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_RDI_DEFECT,  aRDIState,  aRDIEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_SFBER_DEFECT,  aSfBerState,  aSfBerEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_SDBER_DEFECT,  aSdBerState,  aSdBerEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_UPPER_LAYER_FAIL_TA_DEFECT, aUpstreamLayerFailTAState, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_UPPER_LAYER_FAIL_NTA_DEFECT,aUpstreamLayerFailNTAState, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_LOCK, aLockState, false);

        // Validate defect object
        aDefects.Validate();

        //--------------------------------------------------------------
        // STATUS
        // No status


        if (hasDefectsChanged)
            GetMonIf().GetDefectsRegion()->IncModificationCounter();

    } // if (aConfig.GetGroupOfHopsEnable());

  }  // for (uint32 anIndex = 0; anIndex < myMaxVcgs; anIndex++)

  return NULL;
}
