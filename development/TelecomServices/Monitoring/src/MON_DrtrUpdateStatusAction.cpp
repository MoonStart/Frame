// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_DrtrIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_DrtrUpdateStatusAction.h"
#include "../MON_DrtrDefects.h"
#include "../MON_DrtrCounters.h"
#include "../MON_DrtrStatus.h"
#include "../MON_DrtrConfig.h"
#include "../MON_Region.h"

MON_DrtrUpdateStatusAction::MON_DrtrUpdateStatusAction(MON_AppIf& theMonIf,
                                                       TSPII_DrtrRegion& theDrtrPiiRegion,
                                                       MON_AppIf* theUpstreamLayerIf,
                                                       uint8      theNumRouters,
                                                       uint8      theThrottle,
                                                       uint8      theAccessInterval):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myDrtrPiiRegion(theDrtrPiiRegion),
    myCount(0),
    myCurrentRouterInstance(0),
    myThrottle(theThrottle),
    myAccessInterval(theAccessInterval),
    myUpdateActionInterval(0),
    myNumRoutersToUpdate(0),
    myNumRouters(theNumRouters)
{
    // Set defaults
    myUpdateActionInterval = 10; // Two Seconds ay 200 ms
    myNumRoutersToUpdate   = 1;  // One Router At a Time

    // Change defaults for accessing TSPII variables from Throttle
    // First, avoid division by zero
    if (myThrottle != 0)
    {
        // Interval has default value of 50 (10 sec).  Change only if
        // myThrottle is less than Access constant.
        if (myThrottle < MON_ROUTER_ACCESS_INTERVAL)
        {
            myUpdateActionInterval = MON_ROUTER_ACCESS_INTERVAL / myThrottle;
        }

        // Routers to Update has default value of 1. Change only if
        // myThrottle is less the number of routers.
        if (myThrottle < myNumRouters)
        {
            myNumRoutersToUpdate = myNumRouters / myThrottle;
        }
    }  // if (myThrottle != 0)

    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myDrtrPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

    for (uint32 anIndex = 0; anIndex < myNumRouters; anIndex++)
    {
        myPiiRejectedAdjancencyCount.push_back((uint32) 0);
        myPiiAreaAddressMismatchCount.push_back((uint32) 0);
        myPiiMaxAreaAddressMismatchCount.push_back((uint32) 0);
        myPiiL1DatabaseOverloadCount.push_back((uint32) 0);
        myPiiL2DatabaseOverloadCount.push_back((uint32) 0);
    }
}

MON_DrtrUpdateStatusAction::~MON_DrtrUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myDrtrPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_DrtrUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}


FC_Object* MON_DrtrUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    myCount++;
    if (myCount % myUpdateActionInterval == 0)
    {
        UpdateObject(theRunReason);
    }
    return NULL;
}

void MON_DrtrUpdateStatusAction::UpdateObject(unsigned theRunReason)
{

  // Here, cycle through the number of instances that have been
  // directed from above
  uint8 anIndex;
  for (anIndex = 0; anIndex < myNumRoutersToUpdate; anIndex++)
  {
    // Check the current routing instance to process.
    // If the router instance is out of bounds, reset it (to 0)
    // Note: myCurrentRouterInstance is incremented at the end of the for loop.
    if (myCurrentRouterInstance >= myNumRouters)
    {
        myCurrentRouterInstance = 0;
    }

    MON_DrtrDefects& aDefects     = static_cast<MON_DrtrDefects&>((*GetMonIf().GetDefectsRegion())[myCurrentRouterInstance]);
    MON_DrtrStatus& aStatus       = static_cast<MON_DrtrStatus&>((*GetMonIf().GetStatusRegion())[myCurrentRouterInstance]);
    MON_DrtrCounters& aCounters   = static_cast<MON_DrtrCounters&>((*GetMonIf().GetCountersRegion())[myCurrentRouterInstance]);
    MON_DrtrConfig& aConfig       = static_cast<MON_DrtrConfig&>((*GetMonIf().GetConfigRegion())[myCurrentRouterInstance]);
    TSPII_DrtrIf& aDrtrPII        = myDrtrPiiRegion[myCurrentRouterInstance];

    bool hasDefectsChanged = false;
    bool hasStatusChanged = false;


    //--------------------------------------------------------------
    // CONFIG
    //
    // Currently no configuration


    // Only look at counters and defects if TSPII indicates something has changed.
    bool aDefectsChanged = true;
    // Remove comments below when TSPII and device driver code is ready
    // aDefectsChanged = aDrtrPII.GetDefectsChanged();

    if (aDefectsChanged)
    {
        //--------------------------------------------------------------
        // COUNTERS
        aCounters.SetErrorCount(CT_TEL_DRTR_RESOLUTION_FAILURE,aDrtrPII.GetResolutionFailureCount());

        // Validate Counter region
        aCounters.Validate();



        //--------------------------------------------------------------
        // STATUS
        // Read current status
        //

        hasStatusChanged |= aStatus.SetLevel1_RouterState(aDrtrPII.GetLevel1_RouterState());
        hasStatusChanged |= aStatus.SetLevel2_RouterState(aDrtrPII.GetLevel2_RouterState());


        hasStatusChanged |= aStatus.SetSequenceNumber(aDrtrPII.GetSequenceNumber());

        //--------------------------------------------------------------
        // DEFECTS
        // Read current defects

        //bool aUpstreamLayerFailTAState=false;
        //bool aUpstreamLayerFailNTAState=false;

        bool aRejectedAdjancencyState=false;
        bool aAreaAddressMismatchState=false;
        bool aMaxAreaAddressMismatchState=false;
        bool aL1DatabaseOverloadState=false;
        bool aL2DatabaseOverloadState=false;

        bool aRejectedAdjancencyEvent=false;
        bool aAreaAddressMismatchEvent=false;
        bool aMaxAreaAddressMismatchEvent=false;
        bool aL1DatabaseOverloadEvent=false;
        bool aL2DatabaseOverloadEvent=false;

        uint32 aNewRejectedAdjancencyCount     = aDrtrPII.GetRejectedAdjancency();
        uint32 aNewAreaAddressMismatchCount    = aDrtrPII.GetAreaAddressMismatch();
        uint32 aNewMaxAreaAddressMismatchCount = aDrtrPII.GetMaxAreaAddressMismatch();
        uint32 aNewL1DatabaseOverloadCount     = aDrtrPII.GetL1DatabaseOverload();
        uint32 aNewL2DatabaseOverloadCount     = aDrtrPII.GetL2DatabaseOverload();

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
            // Update state and count
//        }

            if(myPiiRejectedAdjancencyCount[myCurrentRouterInstance] != aNewRejectedAdjancencyCount)
            {
                aRejectedAdjancencyEvent = true;
            }
            if(aNewRejectedAdjancencyCount%2 != 0)
            {
                aRejectedAdjancencyState = true;
            }

            if(myPiiAreaAddressMismatchCount[myCurrentRouterInstance] != aNewAreaAddressMismatchCount)
            {
                aAreaAddressMismatchEvent = true;
            }
            if(aNewAreaAddressMismatchCount%2 != 0)
            {
                aAreaAddressMismatchState = true;
            }

            if(myPiiMaxAreaAddressMismatchCount[myCurrentRouterInstance] != aNewMaxAreaAddressMismatchCount)
            {
                aMaxAreaAddressMismatchEvent = true;
            }
            if(aNewMaxAreaAddressMismatchCount%2 != 0)
            {
                aMaxAreaAddressMismatchState = true;
            }

            if(myPiiL1DatabaseOverloadCount[myCurrentRouterInstance] != aNewL1DatabaseOverloadCount)
            {
                aL1DatabaseOverloadEvent = true;
            }
            if(aNewL1DatabaseOverloadCount%2 != 0)
            {
                aL1DatabaseOverloadState = true;
            }

            if(myPiiL2DatabaseOverloadCount[myCurrentRouterInstance] != aNewL2DatabaseOverloadCount)
            {
                aL2DatabaseOverloadEvent = true;
            }
            if(aNewL2DatabaseOverloadCount%2 != 0)
            {
                aL2DatabaseOverloadState = true;
            }

// Currently, no upper layer
//
//        if (IsUpstreamLayerFailedNTA())
//        {
//            aUpstreamLayerFailNTAState = true;
//        }

        // Update local defect counts

        myPiiRejectedAdjancencyCount[myCurrentRouterInstance]     = aNewRejectedAdjancencyCount;
        myPiiAreaAddressMismatchCount[myCurrentRouterInstance]    = aNewAreaAddressMismatchCount;
        myPiiMaxAreaAddressMismatchCount[myCurrentRouterInstance] = aNewMaxAreaAddressMismatchCount;
        myPiiL1DatabaseOverloadCount[myCurrentRouterInstance]     = aNewL1DatabaseOverloadCount;
        myPiiL2DatabaseOverloadCount[myCurrentRouterInstance]     = aNewL2DatabaseOverloadCount;

        // Update actual defect
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DRTR_REJECTED_ADJ_DEFECT,   aRejectedAdjancencyState,  aRejectedAdjancencyEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DRTR_AREA_MISMATCH_DEFECT,  aAreaAddressMismatchState, aAreaAddressMismatchEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DRTR_MAX_AREA_ADDR_DEFECT,  aMaxAreaAddressMismatchState,  aMaxAreaAddressMismatchEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DRTR_L1DB_OVERLOAD_DEFECT,  aL1DatabaseOverloadState,  aL1DatabaseOverloadEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_DRTR_L2DB_OVERLOAD_DEFECT,  aL2DatabaseOverloadState,  aL2DatabaseOverloadEvent);

        // Validate defect object
        aDefects.Validate();


        if (hasDefectsChanged)
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

        if (hasStatusChanged)
        GetMonIf().GetStatusRegion()->IncModificationCounter();

        // Validate status object
        aStatus.Validate();


    }  // if (aDefectsChanged)

    // Increment myCurrentRouterInstance for the next iteration of the loop.
    myCurrentRouterInstance++;

  }  // for (uint32 anIndex = 0; anIndex < myNumRouters; anIndex++)

}
