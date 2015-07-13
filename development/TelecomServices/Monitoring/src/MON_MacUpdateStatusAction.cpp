// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_MacIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_MacUpdateStatusAction.h"
#include "../MON_MacDefects.h"
#include "../MON_MacStatus.h"
#include "../MON_Region.h"

const uint8 MAC_THROTTLE_FREQ = 4;

MON_MacUpdateStatusAction::MON_MacUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_MacRegion& theMacPiiRegion):
    MON_UpdateStatusAction(theMonIf,NULL),
    myPiiRFLinkFailCount(0),
    myPiiFefiCount(0),
    myLastLacpFail(false),
    myMacPiiRegion(theMacPiiRegion)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myMacPiiRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    myMacThrottle = 0;
}

MON_MacUpdateStatusAction::~MON_MacUpdateStatusAction()
{
    //GetBbAction()->RemoveInputRegion(&myMacPiiRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
}

FC_Object* MON_MacUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}


FC_Object* MON_MacUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    MON_MacStatus& aStatus = static_cast<MON_MacStatus&>((*GetMonIf().GetStatusRegion())[0]);
    MON_MacDefects& aDefects = static_cast<MON_MacDefects&>((*GetMonIf().GetDefectsRegion())[0]);

    TSPII_MacIf& aMacPII        = myMacPiiRegion[0];

    //--------------------------------------------------------------
    // STATUS
    bool hasStatusChanged = false;
    bool aLinkFailRxState = false;
    bool aOperAutoNeg = false;
    //MAC status from PII

    uint32 aLinkFailRxCount                 = aMacPII.GetLinkFailRx();

    //
    if (++myMacThrottle % MAC_THROTTLE_FREQ == 0)
    {
        CT_TEL_MAC_AUTONEGSTATUS aAutoNegStatus = aMacPII.GetAutoNegStatus();
        CT_TEL_DETECTED aAutoNegRmtSignal       = aMacPII.GetAutoNegRemoteSignal();
        CT_TEL_daHz aOperRate                   = aMacPII.GetOpRate();
        CT_TEL_MAC_DUPLEX_MODE aOperDuplex      = aMacPII.GetOpDuplexMode();
        CT_TEL_MAC_FLOWCTRL aOperFlowCtrl       = aMacPII.GetOpFlowCtrl();
        bool aOperAutoNeg                       = aMacPII.GetOpAutoNeg();
    

        // Check if auto negotiation status has changed and update status region if it has.
        if (aStatus.GetAutoNegStatus() != aAutoNegStatus)
        {
            hasStatusChanged |= aStatus.SetAutoNegStatus(aAutoNegStatus);
        }
        
        // Check if auto negotiation remote signal has changed and update status region if it has.
        if (aStatus.GetAutoNegRmtSignal() != aAutoNegRmtSignal)
        {
            hasStatusChanged |= aStatus.SetAutoNegRmtSignal(aAutoNegRmtSignal);
        }
        
        // Check if operational rate has changed and update status region if it has.
        if (aStatus.GetOperRate() != aOperRate)
        {
            hasStatusChanged |= aStatus.SetOperRate(aOperRate);
        }
        
        // Check if operational duplex mode has changed and update status region if it has.
        if (aStatus.GetOperDuplexMode() != aOperDuplex)
        {
            hasStatusChanged |= aStatus.SetOperDuplexMode(aOperDuplex);
        }
        
        // Check if operational flow control has changed and update status region if it has.
        if (aStatus.GetOperFlowCtrl() != aOperFlowCtrl)
        {
            hasStatusChanged |= aStatus.SetOperFlowCtrl(aOperFlowCtrl);
        }
        
        // Check if operational Auto Negotiation has changed and update status region if it has.
        if (aStatus.GetOperAutoNeg() != aOperAutoNeg)
        {
            hasStatusChanged |= aStatus.SetOperAutoNeg(aOperAutoNeg);
        }

        // For now, put the new Lacp Status fields in the throttled portion
        hasStatusChanged |= aStatus.SetPortLacpState(aMacPII.GetPortLacpState());
        hasStatusChanged |= aStatus.SetPortAggregationField(aMacPII.GetPortAggregationField());
        hasStatusChanged |= aStatus.SetPortLacpPriority(aMacPII.GetPortLacpPriority());
        hasStatusChanged |= aStatus.SetPartnerActiveFlag(aMacPII.GetPartnerActiveFlag());
        hasStatusChanged |= aStatus.SetPartnerSystemID(aMacPII.GetPartnerSystemID());
        hasStatusChanged |= aStatus.SetPartnerPortPriority(aMacPII.GetPartnerPortPriority());
        hasStatusChanged |= aStatus.SetPartnerOperationalKey(aMacPII.GetPartnerOperationalKey());
        hasStatusChanged |= aStatus.SetPartnerPortState(aMacPII.GetPartnerPortState());
        hasStatusChanged |= aStatus.SetLagActorSystemID(aMacPII.GetLagActorSystemID());
        hasStatusChanged |= aStatus.SetLagActorSystemPriority(aMacPII.GetLagActorSystemPriority());
        hasStatusChanged |= aStatus.SetLagActorOperationalKey(aMacPII.GetLagActorOperationalKey());
        hasStatusChanged |= aStatus.SetLagActorAdminKey(aMacPII.GetLagActorAdminKey());
        hasStatusChanged |= aStatus.SetLagPartnerSystemID(aMacPII.GetLagPartnerSystemID());
        hasStatusChanged |= aStatus.SetLagPartnerSystemPriority(aMacPII.GetLagPartnerSystemPriority());
        hasStatusChanged |= aStatus.SetLagPartnerOperationalKey(aMacPII.GetLagPartnerOperationalKey());
        hasStatusChanged |= aStatus.SetLagPartnerAdminKey(aMacPII.GetLagPartnerAdminKey());

    }
    // Check if Link Fail Rx has changed and update status region if it has.
    if(aLinkFailRxCount%2 != 0)
    {
        aLinkFailRxState = true;        
    }
    // Check if Link Fail Rx has changed and update status region if it has.
    if (aStatus.GetLinkFailRx() != aLinkFailRxState)
    {
        hasStatusChanged |= aStatus.SetLinkFailRx(aLinkFailRxState);
    }

    // Read the SFP/XFP Type and then set a boolean for whether
    // Software Auto Negotiation is running.
    CT_ETH_SFP_XFP_TYPE anEthSfpXfpType = aMacPII.GetEthSfpXfpType();
    aStatus.SetIsSoftwareAutoNegEnabled(anEthSfpXfpType);

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();
    
    // Validate status object
    aStatus.Validate();

    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects

    bool aRFLinkFailState=false;
    bool aFefiState=false;
    bool aLacpFailState=false;
    bool aRFLinkFailEvent=false;
    bool aFefiEvent=false;
    bool aLacpFailEvent=false;
    bool hasDefectsChanged = false;

    // Only read GetRFLinkFail if Software Auto Negotiation is Enabled.
    uint32 aNewRFLinkFailCount = 0;
    if (aStatus.GetIsSoftwareAutoNegEnabled()) 
    {
        aNewRFLinkFailCount = aMacPII.GetRFLinkFail();
    }
    uint32 aNewFefiCount = aMacPII.GetFefi();

    // Update FEFI state and count
    if(myPiiFefiCount != aNewFefiCount)
    {
        aFefiEvent = true;
    }
    if(aNewFefiCount%2 != 0) 
    {
        aFefiState = true;        
    }

    // Update LacpFail state and count based on Status and old count
    // if LACP State is Bundle AND Aggregation is Defaulted, then set defect.
    // if ( (aStatus.GetPortLacpState() == CT_TEL_LacpPortState_BUNDLE) &&
    if( GetAggreFieldDefaultedBit(aStatus.GetPortAggregationField()) )
    {
        aLacpFailState = true;        
    }
    if(myLastLacpFail != aLacpFailState)
    {
        aLacpFailEvent = true;
    }    

    // Update RFLinkFail state and count 
    if(myPiiRFLinkFailCount != aNewRFLinkFailCount)
    {
        aRFLinkFailEvent = true;
    }
    if(aNewRFLinkFailCount%2 != 0)
    {
        aRFLinkFailState = true;        
    }

    // Update local defect counts
    myPiiRFLinkFailCount = aNewRFLinkFailCount;
    myPiiFefiCount = aNewFefiCount;
    myLastLacpFail = aLacpFailState;

    // Update actual defect  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MAC_RFLINKFAIL_DEFECT,  aRFLinkFailState,  aRFLinkFailEvent);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MAC_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, IsUpstreamLayerInternalFailed(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MAC_INTERNAL_LOCK, IsUpstreamLayerInternalLocked(), false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_MAC_FEFI_DEFECT, aFefiState, aFefiEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_LACPFAIL_DEFECT, aLacpFailState, aLacpFailEvent);

    //--------------------------------------------------------------
    // STATUS - Part 2 (which updated the hasDefectsChanged flag)
    // Currently, only needed by Gfp AutomaticAction, which isn't monitoring status.
    // So mark the defects are changed when the Sfp/Xfp changes - which will wake up the Gfp action.
    hasDefectsChanged |= aStatus.SetEthSfpXfpType(anEthSfpXfpType);


    // Validate defect object
    aDefects.Validate();

    if (hasDefectsChanged) 
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    return NULL;
}
