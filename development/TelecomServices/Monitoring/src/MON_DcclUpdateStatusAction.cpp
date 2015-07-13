// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_DcclIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_DcclUpdateStatusAction.h"
#include "../MON_DcclDefects.h"
#include "../MON_DcclCounters.h"
#include "../MON_DcclStatus.h"
#include "../MON_DcclConfig.h"
#include "../MON_Region.h"

MON_DcclUpdateStatusAction::MON_DcclUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_DcclRegion& theDcclPiiRegion,
                                                     MON_AppIf* theUpstreamLayerIf,
                                                     uint8      theNumLinks):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myDcclPiiRegion(theDcclPiiRegion),
    myNumLinks(theNumLinks)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myDcclPiiRegion);
    // If this is added back then Controller_AppIf::EnableFastRegionRefresh needs to be updated
    // to include this region.
    //GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

    for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)
    {
        myLastLinkDownState.push_back((uint32) true);
        myLastLinkIncompleteState.push_back((uint32) false);
    }
}

MON_DcclUpdateStatusAction::~MON_DcclUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myDcclPiiRegion);
    //GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_DcclUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}


FC_Object* MON_DcclUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{

  for (uint8 anIndex = 0; anIndex < myNumLinks; anIndex++)
  {

    MON_DcclDefects& aDefects     = static_cast<MON_DcclDefects&>((*GetMonIf().GetDefectsRegion())[anIndex]);
    MON_DcclStatus& aStatus       = static_cast<MON_DcclStatus&>((*GetMonIf().GetStatusRegion())[anIndex]);
    MON_DcclCounters& aCounters   = static_cast<MON_DcclCounters&>((*GetMonIf().GetCountersRegion())[anIndex]);
    MON_DcclConfig& aConfig       = static_cast<MON_DcclConfig&>((*GetMonIf().GetConfigRegion())[anIndex]);
    TSPII_DcclIf& aDcclPII        = myDcclPiiRegion[anIndex];

    bool hasDefectsChanged = false;
    bool hasStatusChanged = false;


    //--------------------------------------------------------------
    // CONFIG
    //
    // Currently no configuration


    // Only look at counters and defects if TSPII indicates something has changed.
    bool adcclDefectsChanged = true;
    // Remove comments below when TSPII and device driver code is ready
    // adcclDefectsChanged = aDcclPII.GetDefectsChanged();

    if (adcclDefectsChanged)
    {
        //--------------------------------------------------------------
        // COUNTERS
        aCounters.SetErrorCount(CT_TEL_DCCL_DROPPED_PACKETS,aDcclPII.GetDroppedPacketsCount());

        // Validate Counter region
        aCounters.Validate();



        //--------------------------------------------------------------
        // STATUS
        // Read current status
        //

        // Get the Protocol Link State
        CT_DCC_LinkState aProtocolLinkState = aDcclPII.GetProtocolLinkState();
        hasStatusChanged |= aStatus.SetProtocolLinkState(aProtocolLinkState);

        // Now get the Tunnel Session
        hasStatusChanged |= aStatus.SetTunnelSessionState(aDcclPII.GetTunnelSessionState());

        // Now get the magic number
        hasStatusChanged |= aStatus.SetMagicNumber(aDcclPII.GetMagicNumber());

        //Now get the dcc traffic selection state
        CT_DCC_BroadcastMode aSelection = aDcclPII.GetDccBroadcastMode();
        if (aSelection != CT_DCC_SLAVE)
        {
            //Selecting traffic from this facility
            hasStatusChanged |= aStatus.SetIsSelected(true);
        }
        else
        {
            //Not selecting traffic from this facility
            hasStatusChanged |= aStatus.SetIsSelected(false);
        }

        //--------------------------------------------------------------
        // DEFECTS (based on Status)
        // Read current defects

        //bool aUpstreamLayerFailTAState=false;
        //bool aUpstreamLayerFailNTAState=false;

        bool aLinkDownState=false;
        bool aLinkDownEvent=false;
        bool aLinkIncompleteState=false;
        bool aLinkIncompleteEvent=false;



        //uint32 aNewLinkDownCount   = aDcclPII.GetLinkDownCount();


// Currently, no upper layer
//
//        // Upstream layer in failure force an AIS
//        if (IsUpstreamLayerFailed())
//        {
//            aUpstreamLayerFailTAState = true;
//            aAISState = true;
//            aAISEvent = false;
//        }
//        else
//        {
//
            // Update Link Down State state
            if(aProtocolLinkState != CT_DCC_LINK_UP)
            {
                aLinkDownState = true;
            }
            if (myLastLinkDownState[anIndex] != aLinkDownState)
            {
                aLinkDownEvent = true;
            }

            // Update Link Incomplete state
            if(aProtocolLinkState == CT_DCC_LINK_INCOMPLETE)
            {
                aLinkIncompleteState = true;
            }
            if (myLastLinkIncompleteState[anIndex] != aLinkIncompleteState)
            {
                aLinkIncompleteEvent = true;
            }

//        }


// Currently, no upper layer
//
//        if (IsUpstreamLayerFailedNTA())
//        {
//            aUpstreamLayerFailNTAState = true;
//        }


        // Update local defect counts
        myLastLinkDownState[anIndex] = aLinkDownState;
        myLastLinkIncompleteState[anIndex] = aLinkIncompleteState;

        // Update actual defect
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DCCL_LINK_DOWN_DEFECT,  aLinkDownState,  aLinkDownEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DCCL_LINK_INCOMPLETE_DEFECT,  aLinkIncompleteState,  aLinkIncompleteEvent);
        //hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DCCL_UPPER_LAYER_FAIL_TA_DEFECT, aUpstreamLayerFailTAState, false);
        //hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DCCL_UPPER_LAYER_FAIL_NTA_DEFECT,aUpstreamLayerFailNTAState,false);
        //hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DCCL_LOCK,IsUpstreamLayerLocked(),false);

        // Validate defect object
        aDefects.Validate();


        if (hasDefectsChanged)
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

        if (hasStatusChanged)
        GetMonIf().GetStatusRegion()->IncModificationCounter();

        // Validate status object
        aStatus.Validate();


    }  // if (adcclDefectsChanged)

  }  // for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)

  return NULL;
}
