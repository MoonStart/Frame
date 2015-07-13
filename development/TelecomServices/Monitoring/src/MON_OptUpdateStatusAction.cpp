// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_OpticalIf.h>
#include <ErrorService/FC_Error.h>
#include "../MON_OptUpdateStatusAction.h"
#include "../MON_OptDefects.h"
#include "../MON_OptStatus.h"
#include "../MON_OptConfig.h"
#include "../MON_OptProtConfig.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"
#include "../MON_OchStatus.h"
#include "../MON_OchMainDefects.h"
#include "Configuration/CFG_Opt.h"
#include "Configuration/CFG_OptAutoRateLock.h"
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <ITS/ITS_ConfigOnTrn.h>
#include <ITS/ITS_Region.h>




//##ModelId=3C3B52F8024E
MON_OptUpdateStatusAction::MON_OptUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_OpticalRegion& theOptPiiRegion,
                                                     CFG_OptAutoRateLockRegion* theAutoRateLockRegion,
                                                     T6100_TelecomIf* theOchMainApp,
                                                     CFG_OptCfgRegion* theOptConfigRegion,
                                                     ITS_ConfigRegionOnTrn* theItsConfigRegion,
                                                     vector<CT_Side>& thePossibleSidesVector,
                                                     MON_AppVector& theMonAppVector,
                                                     T6100_CardIf*  theCardContext,
                                                     uint8  theNumberOfMonPoolApps,
                                                     uint32 theNumberofMonRegions,
                                                     MON_AppIf* theMonPoolApp,
                                                     uint32 theThrottleID,
                                                     uint32 theThrottleFrequency,
                                                     bool theThrottleLossClkRead,
                                                     uint32 theNumberofPossibleSides,
                                                     MON_OptProtConfigRegion* theProtConfigRegion):
    MON_UpdateStatusAction(theMonIf,NULL),
    myOchMainApp(NULL),
    myOptConfigRegion(theOptConfigRegion),
    myItsConfigRegion(theItsConfigRegion),
    myOptPiiRegion(theOptPiiRegion),
    myPiiOptLosCount(0),
    myPiiLossOfClockCount(0),
    myOchStatusRegion(NULL),
    myCount(0),
    myThrottleID(theThrottleID),
    myThrottleFrequency(theThrottleFrequency),
    myPowerChangeTracker(false),
    myFirstGoodPowerRead(false),
    myFirstPassFlag(true),
    myAutoRateLockRegion(theAutoRateLockRegion),
    myThrottleLossClkRead(theThrottleLossClkRead),
    myProtConfigRegion(theProtConfigRegion),
    myPossibleSidesVector(thePossibleSidesVector),
    myNumberofPossibleSides(theNumberofPossibleSides),
    myMonPoolApp(theMonPoolApp),
    myMonAppVector(theMonAppVector),
    myCardContext(theCardContext),
    myNumberOfMonPoolApps(theNumberOfMonPoolApps),
    myNumberofMonRegions(theNumberofMonRegions),
    myPassesPerFiveSecs(25),
    myLocalPrbsRxSessionCounter(0),
    myMonOdufApp(NULL)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myOptPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    if(myProtConfigRegion)     GetBbAction()->AddInputRegion(myProtConfigRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);

    // also register to ochStatus region if TsPii is not supporting rx power
    if (!myOptPiiRegion[0].IsOpticalPowerReceivedSupported())
    {
        T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
        if (aCardContext)
        {
            // Skip retrieval of Och Context for SMTM and PACKET family.  This is because there is no 
            // OCH region for the M (shadow) facility case (where also there is no OpticalPowerReceivedSupported)
            if((aCardContext->GetCardFamily() != SMTM_FAM) &&
               (aCardContext->GetCardFamily() != PACKET_FAM) &&
               (aCardContext->GetCardFamily() != SSM_FAM) &&
               (aCardContext->GetCardFamily() != OTNM_FAM) )
            {
                T6100_TelecomIf* aOchContext = aCardContext->GetOchIfPtr();
                if (aOchContext)
                {
                    MON_AppIf& aMonIf = aOchContext->GetMonLineApp();
                    MON_Region* aRegion = aMonIf.GetStatusRegion();
                    myOchStatusRegion = static_cast<MON_OchStatusRegion*>(aRegion);
                }
            }
        }
    }

    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
    if (aCardContext)
    {
        if (aCardContext->GetCardFamily() == HDTG2_FAM && myNumberofMonRegions != 0)
        {
            myMonOdufApp = myMonAppVector[myNumberofMonRegions - 1];
            myNumberofMonRegions = myNumberofMonRegions - 1;
        }
    }

    if(myOchStatusRegion)      GetBbAction()->AddInputRegion(myOchStatusRegion);
    if(myOptConfigRegion)      GetBbAction()->AddInputRegion(myOptConfigRegion);
    if(myItsConfigRegion)      GetBbAction()->AddInputRegion(myItsConfigRegion,false);

    // Compute PassesPerSecond for throttling with different Tspii update periods.
    uint32 aTspiiUpdatePeriod = uint32(myOptPiiRegion[0].GetUpdatePeriod());
    if (aTspiiUpdatePeriod != 0) 
    {
        float aPassesPerSecond = float(1000) / aTspiiUpdatePeriod;
        // To get five seconds, multiply by five and round up.
        myPassesPerFiveSecs =  uint32((aPassesPerSecond * 5) + .49);
    }
}

//##ModelId=3C3B52F8026D
MON_OptUpdateStatusAction::~MON_OptUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myOptPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    if(myProtConfigRegion)     GetBbAction()->RemoveInputRegion(myProtConfigRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    if(myOchStatusRegion)      GetBbAction()->RemoveInputRegion(myOchStatusRegion);
    if(myOptConfigRegion)      GetBbAction()->RemoveInputRegion(myOptConfigRegion);
    if(myItsConfigRegion)      GetBbAction()->RemoveInputRegion(myItsConfigRegion);
}

FC_Object* MON_OptUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}

//##ModelId=3C3B52F80262
FC_Object* MON_OptUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    //Update status of each object in region
    myCount++;
    UpdateObject(theRunReason, myOptPiiRegion[0]);

    return NULL;
}

//##ModelId=3C7170E603A2
void MON_OptUpdateStatusAction::UpdateObject(unsigned theRunReason, TSPII_OpticalIf& theOptPii)
{
    MON_OptDefects& aDefects   = static_cast<MON_OptDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_OptStatus& aStatus     = static_cast<MON_OptStatus&>((*GetMonIf().GetStatusRegion())[0]);
    MON_OptConfig& aConfig     = static_cast<MON_OptConfig&>((*GetMonIf().GetConfigRegion())[0]);

    CFG_OptAutoRateLock* aAutoRateLock = NULL;
    CFG_Opt* aCfgOpt = NULL;
    bool aLSPActive = false;

    if (myAutoRateLockRegion) 
    {
        aAutoRateLock = &(*myAutoRateLockRegion)[0];
    }
    if (myOptConfigRegion) 
    {
        aCfgOpt = &(*myOptConfigRegion)[0];
    }

    // set Fail Layer Bit Mask for OPT
    aDefects.SetFailLayerBitMask(aConfig.GetFailLayerBitMask());

    //Retrieve information related to upper layer
    if (myItsConfigRegion)
    {
        ITS_ConfigOnTrn& aItsConfig = (*myItsConfigRegion)[0];
        bool aRegionValid = myItsConfigRegion->IsValid();

        if (aRegionValid)
            aLSPActive = aItsConfig.GetInfo(ITS_LSP);
    } //myItsConfigRegion


    bool aInternalLayerFailState      = false;
    bool aInternalLayerFailStateForMS = false;
    bool aInternalLayerLockedState    = false;
    bool aInternalPropNextLayerState  = false;
    if (myNumberofMonRegions) 
    {
        // This code checks the opposite side Mon regions (in myMonAppVector or myMonPoolApp) 
        // to look for layer fail and/or layer lock.  If present, then these conditions are 
        // propogated to this region as an internal layer fail and/or lock, respectively.
        // This is being added for the OTNM and FGTMM to handle dynamic opposite side 
        // and expanded for HDTG.
        bool   anyLayerFailed        = false;
        bool   anyLayerFailedForMS   = false;
        bool   anyLayerLocked        = false;
        bool   anyLayerPropNextLayer = false;

        uint16 anOppositeSideBitMask = aConfig.GetOppositeSideBitMask();

        // Per ports set TSPII  Set connection mapping.
        theOptPii.SetConnectionMap(anOppositeSideBitMask);

		if (myProtConfigRegion) 
        {
            MON_OptProtConfig& aProtConfig = static_cast<MON_OptProtConfig&>((*myProtConfigRegion)[0]);
            if (aProtConfig.GetProtectionEnable()) 
            {
                anOppositeSideBitMask = aProtConfig.GetOppositeSideBitMask();
            }
        }

        // Run through each application 
        for (uint16 i = 0; i < myNumberofMonRegions; i++) 
        {
            // First check Opposite Side Bit Mask to see if the Application 
            // is linked to this facility
            // Plus, make sure we should consider the opposite side
            if (aConfig.IsOppositeSidePositionSet(anOppositeSideBitMask, i) && (!aConfig.GetIgnoreOppositeSide()))
            {
                // Here get Mon Region based on the type of opposite side is being checked
                if (aConfig.GetOppositeSideIsPooled())
                {
                    if (myMonPoolApp)
                    {
                        MON_Defects& aOppositeSideDefectsIf = static_cast<MON_Defects&>((*(myMonPoolApp)->GetDefectsRegion())[i]);

                        if (!aOppositeSideDefectsIf.IsLayerInTermLpbk())
                        {
                            if (aOppositeSideDefectsIf.IsLayerInDefects() ) 
                            {
                                anyLayerFailed = true;
                            }
                            if (aOppositeSideDefectsIf.IsLayerForMaintSigInDefects() ) 
                            {
                                anyLayerFailedForMS = true;
                            }
                            if (aOppositeSideDefectsIf.IsLayerLocked() )
                            {
                                anyLayerLocked = true;
                            }
                            if (aOppositeSideDefectsIf.IsInPropagateNextLayerDefectsTA() )
                            {
                                anyLayerPropNextLayer = true;
                            }
                        }
                    }

                    if (myMonOdufApp)
                    {
                        MON_Defects& aOppositeSideodufDefectsIf = static_cast<MON_Defects&>((*(myMonOdufApp)->GetDefectsRegion())[i]);
                        if (!aOppositeSideodufDefectsIf.IsLayerInTermLpbk())
                        {
                            if (aOppositeSideodufDefectsIf.IsLayerInDefects() ) 
                            {
                                anyLayerFailed = true;
                            }
                            if (aOppositeSideodufDefectsIf.IsLayerForMaintSigInDefects() ) 
                            {
                                anyLayerFailedForMS = true;
                            }
                            if (aOppositeSideodufDefectsIf.IsLayerLocked() )
                            {
                                anyLayerLocked = true;
                            }
                            if (aOppositeSideodufDefectsIf.IsInPropagateNextLayerDefectsTA() )
                            {
                                anyLayerPropNextLayer = true;
                            }
                        }
                    }
                }
                else
                {
                    // Make sure there is something in the vector
                    if (!myMonAppVector.empty())
                    {
                        MON_Defects& aOppositeSideDefectsIf = static_cast<MON_Defects&>((*(myMonAppVector[i])->GetDefectsRegion())[0]);

                        if (!aOppositeSideDefectsIf.IsLayerInTermLpbk())
                        {
                            if (aOppositeSideDefectsIf.IsLayerInDefects() )
                            {
                                anyLayerFailed = true;
                            }
                            if (aOppositeSideDefectsIf.IsLayerForMaintSigInDefects() )
                            {
                                anyLayerFailedForMS = true;
                            }
                            if (aOppositeSideDefectsIf.IsLayerLocked() )
                            {
                                anyLayerLocked = true;
                            }
                            if (aOppositeSideDefectsIf.IsInPropagateNextLayerDefectsTA() )
                            {
                                anyLayerPropNextLayer = true;
                            }
                        }
                    }
                }  // else of if (aConfig.GetOppositeSideIsPooled())

            }  //  if IsOppositeSidePositionSet(i)
        }  // for (uint32 i = 0; i < myNumberofMonApps; i++)

        //Update defects related to failure of upper layer
        aInternalLayerFailState      = anyLayerFailed;
        aInternalLayerFailStateForMS = anyLayerFailedForMS;
        aInternalLayerLockedState    = anyLayerLocked;
        aInternalPropNextLayerState  = anyLayerPropNextLayer;
    } // if (myNumberofMonRegions)

    if (myCardContext && myNumberOfMonPoolApps && (!aConfig.GetIgnoreOppositeSide())) 
    {
        //If here, we have to look at the OppositeSideServerID to find the
        // correct application (via Oduk value) and the correct instance
        // to get the region.
        // 
        CT_ODU_ServerID aServerID = aConfig.GetOppositeSideServerID();
        CT_ServerPool_Layer aLayer = aServerID.GetIdTelecomLayer();
        uint8  aKvalue    = aServerID.GetOduKvalue();
        uint16 anInstance = aServerID.GetPoolInstance();
        if ((aServerID != CT_DEFAULT_ODU_SERVER_ID) &&
            (aLayer == CT_ServerPool_Layer_Odu))
        {
            int aFac = int(CT_PORT_SIDE_30) + int(aKvalue);
            // ODU0 and ODUF share the same context.
            if(aKvalue == CT_ODU_LayerF)
            {
                aFac = CT_PORT_SIDE_30;
            }
            MON_AppIf* aOduMonPoolApp  = &(myCardContext->GetOduIf().GetMonPortSideApp((CT_IntfId)aFac));

            if (aOduMonPoolApp) 
            {
                MON_Defects& aOppositeSideDefectsIf = static_cast<MON_Defects&>((*(aOduMonPoolApp)->GetDefectsRegion())[anInstance]);
                if (aOppositeSideDefectsIf.IsLayerInDefects() )
                {
                    aInternalLayerFailState = true;
                }
                if (aOppositeSideDefectsIf.IsLayerForMaintSigInDefects() )
                {
                    aInternalLayerFailStateForMS = true;
                }
                if (aOppositeSideDefectsIf.IsLayerLocked() )
                {
                    aInternalLayerLockedState = true;
                }
                if (aOppositeSideDefectsIf.IsInPropagateNextLayerDefectsTA() )
                {
                    aInternalPropNextLayerState = true;
                }
            }
        }
    }

    bool aLossLightState=false, aPiiLossLightState=false, aLossClkState=false, aLossLockState=false, aSdPwrState=false, aMFAState=false;
    bool aLossLightEvent=false, aPiiLossLightEvent=false, aLossClkEvent=false, aLossLockEvent=false, aSdPwrEvent=false, aMFAEvent=false;
    bool aUpperLayerFailTAState = false;
    bool aUpperLayerFailNTAState = false;
    bool aLayerLockedState = false;
    bool aLayerTermLpbkState = false;

    //--------------------------------------------------------------
    // CONFIG
    // Back to no configuration (being sent down to TSPII)

    //--------------------------------------------------------------
    // DEFECTS, Part A  (moved up before Status in 3.2.1)
    // because aLossLightState is now used in Status

    // Read current defect
    uint32 aNewOptLosCount = theOptPii.GetOptLOS();

    //Update defects related to failure of upper layer
    // Removed due to MR 227366
    // Note 1: The only method that was used by OchMainDefects was IsLayerInDefectsNTA()
    // and MR 227366 was wriiten to disable the current implemenation of optical failures 
    // driving OTU and ODU maintenance signals. 
    // Note 2: All the code to retrieve the OCH Main Defect region (aUpperLayerDefects)
    // was removed with this MR
    //if (aUpperLayerDefects)
    //{
    //    aUpperLayerFailTAState = aUpperLayerDefects->IsLayerInDefects() || aUpperLayerDefects->IsInPropagateNextLayerDefectsTA();
    //    aUpperLayerFailNTAState = aUpperLayerDefects->IsLayerInDefectsNTA();
    //}

    //Layer fail is disabled when line side protection exists
    if ((IsUpstreamLayerFailed()) || (aConfig.GetUpperLayerFailed() && !aLSPActive))
    {
        aUpperLayerFailTAState = true;
        aLossLightState = true;
        aLossLightEvent = false;
    }
    else
    {
        // Update Loss of light state and count update
        if(myPiiOptLosCount != aNewOptLosCount)
        {
            aLossLightEvent = true;
        }
        if(aNewOptLosCount%2 != 0)
        {
            aLossLightState = true; 
        }
    }

    //--------------------------------------------------------------
    // As a Service to Signal Alarm, please keep track of the 
    // actual Pii Opt Los Count/Event information irregardles
    // of any other indicators or UpperLayer issues.
    //--------------------------------------------------------------
    if ( myPiiOptLosCount != aNewOptLosCount )
    {
        aPiiLossLightEvent = true;
    }
    if ( aNewOptLosCount%2 != 0 ) // Odd=LOS!
    {
        aPiiLossLightState = true; 
    }
    
    //--------------------------------------------------------------
    // STATUS
    // Read current status

    bool hasStatusChanged = false;
    bool hasPowerChanged = false;
    bool aValidate = false;
    if (theOptPii.IsOpticalPowerReceivedSupported())
    {
        CT_TEL_mBm aOldTotalInputPower = aStatus.GetTotalInputPower();

        // The default for throttle ID is 0, so normally, the power level will be
        // read everytime.  If set (initially only on the OPSM), then the calls
        // to TSPII will be staggered using the ThrottleID and access interval,
        // myThrottleFrequency.
        if ( ( myThrottleID == 0 ) ||
             ( ((myCount + myThrottleID) % myThrottleFrequency ) == 0 ) ||
             ( myFirstPassFlag == true) )
        {
            hasPowerChanged |= aStatus.SetLevel(CT_TEL_OPT_INPUT_POWER_STATUS, theOptPii.GetOpticalPowerReceived());
        }

        aValidate = true;

        // Set Signal Degrade Power Defect based on:
        //     - Total Input Power 
        //     - State of the Signal Degrade Pwer Defect
        //     - SdPwr Threshold
        //     - SdPwr Clearing Delta
        uint32 aCurrentSdPwrCount = 0;
        bool   aCurrentSdPwrState = false;
                      
        CT_TEL_mBm aNewTotalInputPower = aStatus.GetTotalInputPower();
        CT_TEL_mBm aSdPwrThreshold     = aConfig.GetSdPwrThreshold();

        aDefects.GetDefectStatus(CT_TEL_OPT_SDPWR_DEFECT, &aCurrentSdPwrCount, &aCurrentSdPwrState);
        // If the defect is set (true), then the power must rise above the
        // configured threshold plus a clearing delta.
        if (aCurrentSdPwrState)
        {
            aSdPwrThreshold = aSdPwrThreshold + CT_TEL_SDPWR_THRESHOLD_CLEARING_DELTA;
        }

        // Find the first power read that is not the default power
        // This is used to set the SdPwerState and is needed to not
        // set the SdPwr defect during warm reset
        if ((myFirstGoodPowerRead == false) && (aNewTotalInputPower > TRAFFIC_DEFAULT_POWER))
        {    
            myFirstGoodPowerRead = true;
        }

        // Set the defect state if it below the power is below the calculated threshold.
        // Note 1: since the state is initialized to false, the defect is cleared by not
        // being set here.
        // Note 2: At this time, the Event is not used; therefore, keep it false.
        if (aNewTotalInputPower < aSdPwrThreshold) 
        {
            if (myFirstGoodPowerRead) 
            {   
            aSdPwrState = true;
            aSdPwrEvent = false;
            }
        }
     
        // Now the SetTotalInputPower, which is called from SetLevel, returns boolean when 
        // power changes, plus it keeps track if it was a significant change (via the GetSignifPowerChange
        // method.  These values will be used along with keeping track how many times through this
        // action has run to determine when to set the hasStatusChanged flag. 
        if (hasPowerChanged) 
        {
            // Add in the fact that we ignore significant change when there is Loss of Light
            if ((aStatus.GetSignifPowerChange()) && (!aLossLightState))
            {
                hasStatusChanged |= true;
                myPowerChangeTracker = false;
            }
            else
            {
                myPowerChangeTracker = true;
            }
        }

        // Always update the has changed flag after a certain time (12 x 5 sec = 1 minute)
        if ((myCount % (myPassesPerFiveSecs*12) == 0) && (myPowerChangeTracker))
        {
            hasStatusChanged |= true;
            myPowerChangeTracker = false;
        }
    }
    else
    {
        if (myOchStatusRegion)
        {
            MON_OchStatus& aOchStatus = static_cast<MON_OchStatus&>((*myOchStatusRegion)[0]);
            if (aOchStatus.IsValidated())
            {
                aStatus.SetLevel(CT_TEL_OPT_INPUT_POWER_STATUS, aOchStatus.GetPower());
                aValidate = true;
            }
        }
    }
   
    // If the auto rate lock feature is trying to lock, do not get the bit rate.
    if (aAutoRateLock && (aAutoRateLock->GetLockState() == CFG_RATE_NOT_LOCKED))
    {
        hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS, 0);     
    }
    else
    {
        hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS, theOptPii.GetBitRate());
    }

    // The MRTM supports port side automatic bit rate lock feature, and it 
    // is a tricky beast. The current detected rate value is read from HW and set in
    // MON status if and only if a fixed rate port side facility is provisioned or a 
    // port side variable rate facility is provisioned and locked. If the auto rate 
    // lock down attribute in CFG is set, then the facility is a variable rate facility. 
    // On a fixed rate facility, the provisioned signal rate attribute in CFG is a nonzero 
    // value. Note all this automatic bit rate applies only to port side MRTM. The one
    // condition that distinguishes the port side MRTM is the presence of auto rate lock
    // attribute region.
    bool portSideMrtm = false;
    bool rateLockedVarRateFac = false;
    bool presentFixedRateFac = false;

    if (aCfgOpt) 
    {
        // If the automatic bit rate lock region is available,this action is representing
        // port side interface of an MRTM. Determine if there is a fixed rate facility 
        // present or a variable rate facility present and locked.
        if (aAutoRateLock) 
        {
            portSideMrtm = true;
            rateLockedVarRateFac = (aCfgOpt->GetAutoRateLockDown()) &&
                                   (aAutoRateLock->GetLockState() == CFG_RATE_LOCKED);
            presentFixedRateFac = (aCfgOpt->GetSignalRate() != 0);
        }
    }
    
    // For all OPT that are not port side MRTM, read the current bit rate from HW.
    // For all OPT that are port side MRTM, check for the flags described above.
    if ((!portSideMrtm) || rateLockedVarRateFac || presentFixedRateFac)
    {
        hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS, theOptPii.GetBitRate());
    }
    else
    {
        hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS, 0);     
    }

    // Check PRBS BER Every 5 seconds (based on myCount 
    // incremented every 200 ms (5 iterations per second)
    // Use Throttle ID to stagger updating the facilities 
    if ((myCount + (myThrottleID * 2)) % myPassesPerFiveSecs == 0) 
    {
        // the clear is now based on the session counter changing, which is controlled by Agent and written to TSPII via CFG.
        if (theOptPii.GetPrbsRxSessionCounter() != myLocalPrbsRxSessionCounter)
        {
            hasStatusChanged |= aStatus.SetPrbsRxMostSignifCount(0);
            hasStatusChanged |= aStatus.SetPrbsRxLeastSignifCount(0);
            hasStatusChanged |= aStatus.SetPrbsRxTimeInterval(0);
            myLocalPrbsRxSessionCounter = theOptPii.GetPrbsRxSessionCounter();
            aStatus.SetPrbsRxFirstSync(false);   // Used locally - don't update hasStatusChanged
        }

        // Only update if PRBS Rx Enable is on (true)
        if (theOptPii.GetPrbsRxEnable())
        {
            uint32 aCountHigh, aCountLow, aTime;

            theOptPii.GetPrbsRxErrors(aCountHigh, aCountLow, aTime);
            hasStatusChanged |= aStatus.SetPrbsRxMostSignifCount(aCountHigh);
            hasStatusChanged |= aStatus.SetPrbsRxLeastSignifCount(aCountLow);
            hasStatusChanged |= aStatus.SetPrbsRxTimeInterval(aTime);

            uint32 aPrbsRxLosyncCount = theOptPii.GetPrbsRxLosync();

            // If INSYNC
            if (aPrbsRxLosyncCount % 2 == 0)
            {
                // If this is first time going INSYNC, set FirstSync = true
                // and store the current LosyncCount.
                if (aStatus.GetPrbsRxFirstSync() == false)
                {
                    aStatus.SetPrbsRxFirstSync(true);                          // Used locally - don't update hasStatusChanged
                    aStatus.SetPrbsRxFirstSyncLosyncCount(aPrbsRxLosyncCount); // Used locally - don't update hasStatusChanged
                    hasStatusChanged |= aStatus.SetPrbsRxLosync(CT_TEL_PRBS_INSYNC);
                }

                // Else we were already INSYNC, so change to ERRSYNC only if count 
                // indicates an out-of-sync and back in-sync transition occurred.
                else
                {
                    if (aPrbsRxLosyncCount != aStatus.GetPrbsRxFirstSyncLosyncCount())
                    {
                        hasStatusChanged |= aStatus.SetPrbsRxLosync(CT_TEL_PRBS_ERRINSYNC);
                    }
                }
           }
           // Else OUTSYNC
           else
           {
               hasStatusChanged |= aStatus.SetPrbsRxLosync(CT_TEL_PRBS_OUTSYNC);
           }
        }
        else
        {
            // If PRBS Receiver is not enabled, we must be out of sync
            hasStatusChanged |= aStatus.SetPrbsRxLosync(CT_TEL_PRBS_OUTSYNC);
            aStatus.SetPrbsRxFirstSync(false);   // Used locally - don't update hasStatusChanged
        }
    } // if ((myCount + (myThrottleID * 2)) % 25 == 0)

    // The default for throttle ID is 0, so normally, the power level will be
    // read everytime.  If set, then the calls to TSPII will be staggered using
    // the ThrottleID and access interval, myThrottleFrequency.
    if ( ( myThrottleID == 0 ) ||
         ( ((myCount + myThrottleID) % myThrottleFrequency ) == 0 ) )
    {
        CT_TEL_mBm aPower;

        if(theOptPii.IsOpticalPowerTransmittedSupported())
        {
            aPower = theOptPii.GetOpticalPowerTransmitted();
            hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_OUTPUT_POWER_STATUS, aPower);
        }

        if(theOptPii.IsOpticalPowerTransmittedByPeerSupported())
        {
            aPower = theOptPii.GetOpticalPowerTransmittedByPeer();
            hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_PEER_OUTPUT_POWER_STATUS, aPower);

            aPower = theOptPii.GetOmsPowerTransmittedByPeer();
            hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_PEER_OMS_OUTPUT_POWER_STATUS, aPower);

            aPower = theOptPii.GetOmsPowerTransmitted();
            hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_OMS_OUTPUT_POWER_STATUS, aPower);
        }
    }

    // The default for throttle ID is 0, so normally, the power level will be
    // read everytime.  If set, then the calls to TSPII will be staggered using
    // the ThrottleID and access interval, myThrottleFrequency.
    if ( ( myThrottleID == 0 ) ||
         ( ((myCount + myThrottleID) % myThrottleFrequency ) == 0 ) )
    {
        CT_TEL_mBm aActualGain = 0;

        if(theOptPii.IsOpticalActualGainSupported())
        {
            aActualGain = theOptPii.GetOpticalActualGain();
            hasStatusChanged |= aStatus.SetLevel(CT_TEL_OPT_ACTUAL_GAIN_STATUS, aActualGain);

            // Check if we should be sending back the GAIN to Agent, currently only the AIM module
            // supports GAIN, so this code could be moved in the future if needed.
            bool aLaserState = theOptPii.GetLaserState();
            if ((aLossLightState) || (!aLaserState))
                aValidate = false;
        }
    }


    // The default for throttle ID is 0, so normally, the power level will be
    // read everytime.  If set, then the calls to TSPII will be staggered using
    // the ThrottleID and access interval, myThrottleFrequency.
    // Note: this assumes IsOpticalPowerReceivedSupported is true so that the
    // status region is updated every 15 seconds.  Therefore, it looks only for 
    // significant power changes.
    if ( ( myThrottleID == 0 ) ||
         ( ((myCount + myThrottleID) % myThrottleFrequency ) == 1 ) )
    {
        if(theOptPii.IsLanePowerSupported())
        {
            // Get all four lane power measurements.  If any have a significant changes 
            // have occurred, set the Status change flag 
            (void) aStatus.SetLevel(CT_TEL_OPT_RX_LANE_LOW_POWER_STATUS,  theOptPii.GetLaneLowReceivedPower());
            (void) aStatus.SetLevel(CT_TEL_OPT_RX_LANE_HIGH_POWER_STATUS, theOptPii.GetLaneHighReceivedPower());
            (void) aStatus.SetLevel(CT_TEL_OPT_TX_LANE_LOW_POWER_STATUS,  theOptPii.GetLaneLowTransmittedPower());
            (void) aStatus.SetLevel(CT_TEL_OPT_TX_LANE_HIGH_POWER_STATUS, theOptPii.GetLaneHighTransmittedPower());

            (void) aStatus.SetLaneReceivedPower(theOptPii.GetLaneReceivedPower());
            (void) aStatus.SetLaneTransmittedPower(theOptPii.GetLaneTransmittedPower());
            hasStatusChanged |= (aStatus.GetRxLaneSignifPowerChange() || aStatus.GetTxLaneSignifPowerChange());

            if (aStatus.GetRxLoisLaneSignifPowerChange() || aStatus.GetRxHighLaneSignifPowerChange() ||
                aStatus.GetTxLoisLaneSignifPowerChange() || aStatus.GetTxHighLaneSignifPowerChange() ) 
            {
                hasStatusChanged |= true;
            }
        }
    }


    // Read if this is a single or dual OCM
    hasStatusChanged |= aStatus.SetIsDualOcmPresent(theOptPii.GetIsDualOcmPresent());


    // Last, read the Chromatic Dispersion and Differential Group Delay
    hasStatusChanged |= aStatus.SetChromaticDispersion(theOptPii.GetChromaticDispersion());
    hasStatusChanged |= aStatus.SetDifferentialGroupDelay(theOptPii.GetDifferentialGroupDelay());

    // Seriously, this is the last thing.  Read new parameters for 100 Gig
    // Note: Since Agent does not need the these values (for debug right now),
    // do not look at the return of these methods to update the changed flag.  
    // Therefore, the Status region modification counter will not be incremented due to a BER change.
    (void) aStatus.Set2ndOrderPolarModeDispersion(theOptPii.Get2ndOrderPolarModeDispersion());
    (void) aStatus.SetStateOfPolarization(theOptPii.GetStateOfPolarization());
    (void) aStatus.SetPolarDependentLoss(theOptPii.GetPolarDependentLoss());
    (void) aStatus.SetQvalue(theOptPii.GetQvalue());
    (void) aStatus.SetCarrierFrequencyOffset(theOptPii.GetCarrierFrequencyOffset());
    (void) aStatus.SetSignalNoiseRatio(theOptPii.GetSignalNoiseRatio());

    
    if (aValidate)
        hasStatusChanged |= aStatus.Validate();
    else
        hasStatusChanged |= aStatus.Invalidate();

    if (hasStatusChanged) 
        GetMonIf().GetStatusRegion()->IncModificationCounter();


    //--------------------------------------------------------------
    // DEFECTS, Part B
    // Continue with the regularly scheduled defects
    // (Note: beginning part was moved up due to aLossLightState
    // being used in Status)

    uint32 aNewLossOfClkCount = myPiiLossOfClockCount;

    //Retrieve Loss Of Clock from Pii once every sec if throttling
    //of loss of clock reads is allowed. Otherwise read everytime
    if (myThrottleLossClkRead)
    {
        if (myCount%5 == 0)
        {
            aNewLossOfClkCount = theOptPii.GetLossOfClock();
        }
    }
    else
    {
        aNewLossOfClkCount = theOptPii.GetLossOfClock();
    }

    if (aLossLightState)
    {
        aLossClkState = true;
        aLossClkEvent = false;
    }
    else
    {
        //Loss of clock state and count update
        if(myPiiLossOfClockCount != aNewLossOfClkCount)
        {
            aLossClkEvent = true;
        }
        if(aNewLossOfClkCount%2 != 0)
        {
            aLossClkState = true;        
        }
    }


    if(aConfig.GetLayerLocked())
    {   
        aLayerLockedState = true;
    }

    if(theOptPii. GetTerminalLoopbackEnable ())
    {   
        aLayerTermLpbkState = true;
    }

    bool aOldLossLockDefect = false;
    uint32 aCount = 0;
    aDefects.GetDefectStatus(CT_TEL_OPT_LOSS_LOCK_DEFECT,&aCount,&aOldLossLockDefect);

    //Update Loss Lock defect and count (default to false)
    if(myAutoRateLockRegion)
    {
        if(aAutoRateLock->GetLockState() == CFG_RATE_NOT_LOCKED)
        {
            aLossLockState = true;
        }

        if(aOldLossLockDefect != aLossLockState)
        {
            aLossLockEvent = true;
        }
    }


    // Do not raise MFA defect on a LOSS CLK or a LOSS LIGHT
    if (aLossLightState || aLossClkState)
    {
        aMFAState = false;
        aMFAEvent = false;
    }


    // Update local defect counts
    myPiiOptLosCount = aNewOptLosCount;
    myPiiLossOfClockCount = aNewLossOfClkCount;

    // update actual defect
    bool hasDefectsChanged = false;
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_LOSS_CLK_DEFECT, aLossClkState, aLossClkEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_LOSS_LOCK_DEFECT, aLossLockState, aLossLockEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, aLossLightState, aLossLightEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_PII_OPT_LOSS_LIGHT_DEFECT, aPiiLossLightState, aPiiLossLightEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_SDPWR_DEFECT, aSdPwrState, aSdPwrEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_MISMATCH_FACILITY_DEFECT, aMFAState, aMFAEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT, aUpperLayerFailTAState,   false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, aUpperLayerFailTAState,   false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT,aUpperLayerFailNTAState,false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_LOCK,aLayerLockedState,false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT,aInternalLayerFailState||aConfig.GetInternalUpperLayerFailed(),false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT,aInternalLayerFailStateForMS||aConfig.GetInternalUpperLayerFailed(),false); 
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_INTERNAL_LOCK,aInternalLayerLockedState,false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT,aInternalPropNextLayerState,false);  
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OPT_TERM_LPBK,aLayerTermLpbkState,false);  
    hasDefectsChanged |= aDefects.Validate();
    
    if (hasDefectsChanged) 
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

    myFirstPassFlag = false;
}
