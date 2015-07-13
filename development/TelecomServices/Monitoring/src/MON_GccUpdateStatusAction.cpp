// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_GccIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include "../MON_AppIf.h"
#include "../MON_GccUpdateStatusAction.h"
#include "../MON_GccDefects.h"
#include "../MON_GccCounters.h"
#include "../MON_GccStatus.h"
#include "../MON_GccConfig.h"
#include "../MON_Region.h"

MON_GccUpdateStatusAction::MON_GccUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_GccRegion& theGccPiiRegion,
                                                     MON_AppIf* theUpstreamLayerIf,
                                                     uint8      theNumLinks):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myGccPiiRegion(theGccPiiRegion),
    myNumLinks(theNumLinks)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myGccPiiRegion);
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

MON_GccUpdateStatusAction::~MON_GccUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myGccPiiRegion);
    //GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_GccUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}


FC_Object* MON_GccUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{

    for (uint8 anIndex = 0; anIndex < myNumLinks; anIndex++)
    {
        MON_GccDefects& aDefects     = static_cast<MON_GccDefects&>((*GetMonIf().GetDefectsRegion())[anIndex]);
        MON_GccStatus& aStatus       = static_cast<MON_GccStatus&>((*GetMonIf().GetStatusRegion())[anIndex]);
        MON_GccCounters& aCounters   = static_cast<MON_GccCounters&>((*GetMonIf().GetCountersRegion())[anIndex]);
        TSPII_GccIf& aGccPII         = myGccPiiRegion[anIndex];
        
        bool hasDefectsChanged = false;
        bool hasStatusChanged  = false;
        
        
        //--------------------------------------------------------------
        // CONFIG
        //
        // Currently no configuration
        
        
        //--------------------------------------------------------------
        // COUNTERS
        aCounters.SetErrorCount(CT_TEL_GCC_DROPPED_PACKETS,aGccPII.GetDroppedPacketsCount());
        
        // Validate Counter region
        aCounters.Validate();
        
        //--------------------------------------------------------------
        // STATUS
        // Read current status
        
        // Get the Protocol Link State
        CT_DCC_LinkState aProtocolLinkState = aGccPII.GetProtocolLinkState();
        hasStatusChanged |= aStatus.SetProtocolLinkState(aProtocolLinkState);
        
        // Now get the Tunnel Session
        hasStatusChanged |= aStatus.SetTunnelSessionState(aGccPII.GetTunnelSessionState());
        
        // Now get the magic number
        hasStatusChanged |= aStatus.SetMagicNumber(aGccPII.GetMagicNumber());
        
                
        //--------------------------------------------------------------
        // DEFECTS (based on Status)
        // Read current defects
        
        bool aLinkDownState=false;
        bool aLinkDownEvent=false;
        bool aLinkIncompleteState=false;
        bool aLinkIncompleteEvent=false;
        
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
        
        // Update local defect counts
        myLastLinkDownState[anIndex] = aLinkDownState;
        myLastLinkIncompleteState[anIndex] = aLinkIncompleteState;
        
        // Update actual defect
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GCC_LINK_DOWN_DEFECT,  aLinkDownState,  aLinkDownEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GCC_LINK_INCOMPLETE_DEFECT,  aLinkIncompleteState,  aLinkIncompleteEvent);
        
        // Validate defect object
        aDefects.Validate();
        
        
        if (hasDefectsChanged)
        GetMonIf().GetDefectsRegion()->IncModificationCounter();
        
        if (hasStatusChanged)
        GetMonIf().GetStatusRegion()->IncModificationCounter();
        
        // Validate status object
        aStatus.Validate();
        
    }  // for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)
   
    return NULL;
}
