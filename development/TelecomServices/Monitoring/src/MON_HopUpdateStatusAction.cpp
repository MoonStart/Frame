// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_HopIf.h>
#include <Blackboard/FC_BbReason.h>
#include <PII_TickTimer.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_HopUpdateStatusAction.h"
#include "../MON_HopDefects.h"
#include "../MON_HopCounters.h"
#include "../MON_HopStatus.h"
#include "../MON_HopConfig.h"
#include "../MON_Region.h"
#include <T6100_CardIf.h>
#include <CsPii/CSPII_CardIF.h>

const uint8  MON_DEFAULT_HOPS_PER_PASS  = 48;

MON_HopUpdateStatusAction::MON_HopUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_HopRegion& theHopPiiRegion,
                                                     MON_AppIf* theUpstreamLayerIf,
                                                     CT_NumberOfHops theHopsOnCard):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myHopPiiRegion(theHopPiiRegion),
    myFirstPassFlag(true),
    myHopsOnCard(theHopsOnCard)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myHopPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

    for (uint32 anIndex = 0; anIndex < myHopsOnCard; anIndex++)
    {
        myGoodTraceMessageCounter.push_back((uint32) 0);
        myBadTraceMessageCounter.push_back((uint32) 0);
        myPiiAISCount.push_back((uint32) 0);
        myPiiLOPCount.push_back((uint32) 0);
        myPiiUNEQCount.push_back((uint32) 0);
        myPiiPLMCount.push_back((uint32) 0);
        myPiiTIMCount.push_back((uint32) 0);
        myPiiRDICount.push_back((uint32) 0);
        myPiiSDBERCount.push_back((uint32) 0);
        myPiiSFBERCount.push_back((uint32) 0);

    }

    myNextHop = 0;
    myNbrHop2Check = myHopsOnCard;
    // Only alter the number of Hops to check on certain cards.
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
    if (aCardContext)
    {
        // On the SSM, the Hops can be split up (during the MON_UpdateStatusAction), so divide by 4.
        // Also, the update time (in the Tspii SubApplication) for the SSM was reduced for the 
        // facilities with 192 Hops so that each hops was still processed every second.
        // On other cards (SMTMU and SPFAB), the Hops could not be split up, so keep the number of
        // hops to check the same.
        if(aCardContext->GetCardFamily() == SSM_FAM)
        {
            if (myNbrHop2Check > uint16(MON_DEFAULT_HOPS_PER_PASS)) 
            {
                // If greater than default, just divide the number by 4
                // It should be 192, so 48 should be the value.
                myNbrHop2Check /= 4;
            }
        }
    }

    
}

MON_HopUpdateStatusAction::~MON_HopUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myHopPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_HopUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}


FC_Object* MON_HopUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{

  FC_Milliseconds startTime;
  MON_HopStatus& aStatusDbg = static_cast<MON_HopStatus&>((*GetMonIf().GetStatusRegion())[0]);
  if(aStatusDbg.IsDebugFlagSet())
      startTime = PII_TickTimer::readTimer();

  uint16 aStartIndex = 0;
  uint16 anEndIndex = myHopsOnCard;
  if ((myHopsOnCard > myNbrHop2Check) && (!myFirstPassFlag))
  {
      // When there is more than default instances, then loop through using myNbrGfp2Check
      // Make sure start and end are not past max
      // Set start to 0 if equal or past max
      // and set end to max if past max
      aStartIndex = myNextHop;
      if (aStartIndex >= myHopsOnCard)
      {
          aStartIndex = 0;
      }
      // End is normally the number of hops to check past the start
      anEndIndex = aStartIndex + myNbrHop2Check;
      if (anEndIndex > myHopsOnCard)
      {
          anEndIndex = myHopsOnCard;
      }
      myNextHop = anEndIndex;
  }

  for (uint16 anIndex = aStartIndex; anIndex < anEndIndex; anIndex++)      
  {
    MON_HopDefects& aDefects    = static_cast<MON_HopDefects&>((*GetMonIf().GetDefectsRegion())[(bbindex_t)anIndex]);
    MON_HopStatus& aStatus      = static_cast<MON_HopStatus&>((*GetMonIf().GetStatusRegion())[(bbindex_t)anIndex]);
    MON_HopCounters& aCounters  = static_cast<MON_HopCounters&>((*GetMonIf().GetCountersRegion())[(bbindex_t)anIndex]);
    MON_HopConfig& aConfig      = static_cast<MON_HopConfig&>((*GetMonIf().GetConfigRegion())[(bbindex_t)anIndex]);
    TSPII_HopIf& aHopPII        = myHopPiiRegion[(bbindex_t)anIndex];

    bool hasDefectsChanged = false;
    bool hasStatusChanged = false;

    static CT_SONET64ByteTrace aTrace, aDefaultTrace; //tmp buffer


    //--------------------------------------------------------------
    // CONFIG
    //
    // Monitoring Configuration moved to CFG for perfomance reasons.
    // Calls included BER SF Theshold, BER SD Threhhold, and Expected C2.

    // Note that Trace is not being moved since expected trace does not get
    // wriiten to TSPII.

    // Also Note that Agent is now writing down cross connect informatiom, namely
    // bool SetIsConnectedAsSrc(bool theState);
    // bool SetIsConnectedAsDst(bool theState);
    // But this information is converted to a defect (see below)
    // and not written down to TSPII


    // Only look at counters and defects if TSPII indicates something has changed.
    bool hopDefectsChanged = true;
    // Remove comments below when TSPII and device driver code is ready
    // hopDefectsChanged = aHopPII.GetDefectsChanged();

    if (hopDefectsChanged)
    {
        //--------------------------------------------------------------
        // COUNTERS
        aCounters.SetErrorCount(CT_TEL_HOP_B3,aHopPII.GetCvCount());
        aCounters.SetErrorCount(CT_TEL_HOP_REI,aHopPII.GetReiCount());
        aCounters.SetErrorCount(CT_TEL_HOP_PPJ_GEN,aHopPII.GetPpjgCount());
        aCounters.SetErrorCount(CT_TEL_HOP_NPJ_GEN,aHopPII.GetNpjgCount());
        aCounters.SetErrorCount(CT_TEL_HOP_PPJ_DET,aHopPII.GetPpjdCount());
        aCounters.SetErrorCount(CT_TEL_HOP_NPJ_DET,aHopPII.GetNpjdCount());

        // Validate Counter region
        aCounters.Validate();

        //--------------------------------------------------------------
        // DEFECTS
        // Read current defects

        bool aUpstreamLayerFailTAState=false;
        bool aUpstreamLayerFailNTAState=false;
        bool aAISState=false, aLOPState=false, aUNEQState=false;
        bool aPLMState=false, aRDIState=false;
        bool aSdBerState=false, aSfBerState=false;

        bool aAISEvent=false, aLOPEvent=false, aUNEQEvent=false;
        bool aPLMEvent=false, aRDIEvent=false;
        bool aSdBerEvent=false, aSfBerEvent=false;


        uint32 aNewAISCount   = aHopPII.GetAis();
        uint32 aNewLOPCount   = aHopPII.GetLop();
        uint32 aNewUNEQCount  = aHopPII.GetUneq();
        uint32 aNewPLMCount   = aHopPII.GetPlm();
        uint32 aNewRDICount   = aHopPII.GetRdi();
        uint32 aNewSdBerCount = aHopPII.GetBerSd();
        uint32 aNewSfBerCount = aHopPII.GetBerSf();

        // Upstream layer in failure force an AIS
        if (IsUpstreamLayerFailed())
        {
            aUpstreamLayerFailTAState = true;
            aAISState = true;
            aAISEvent = false;
        }
        else
        {
            // Update Ais state and count
            if(myPiiAISCount[anIndex] != aNewAISCount)
            {
                aAISEvent = true;
            }
            if(aNewAISCount%2 != 0)
            {
                aAISState = true;
            }
        }

        // Update LOP state and count
        if(myPiiLOPCount[anIndex] != aNewLOPCount)
        {
            aLOPEvent = true;
        }
        if(aNewLOPCount%2 != 0)
        {
            aLOPState = true;
        }


        // Update UNEQ state and count
        if(myPiiUNEQCount[anIndex] != aNewUNEQCount)
        {
            aUNEQEvent = true;
        }
        if(aNewUNEQCount%2 != 0)
        {
            aUNEQState = true;
        }

        // Update PLM state and count
        if(myPiiPLMCount[anIndex] != aNewPLMCount)
        {
            aPLMEvent = true;
        }
        if(aNewPLMCount%2 != 0)
        {
            aPLMState = true;
        }

        // Update RDI state and count
        if(myPiiRDICount[anIndex] != aNewRDICount)
        {
           aRDIEvent = true;
        }
        if(aNewRDICount%2 != 0)
        {
            aRDIState = true;
        }

        if (IsUpstreamLayerFailedNTA())
        {
            aUpstreamLayerFailNTAState = true;
        }

        // Update SfBer state and count
        if(myPiiSFBERCount[anIndex] != aNewSfBerCount)
        {
            aSfBerEvent = true;
        }
        if(aNewSfBerCount%2 != 0)
        {
            aSfBerState = true;
        }

        // Update SdBer state and count
        if(myPiiSDBERCount[anIndex] != aNewSdBerCount)
        {
            aSdBerEvent = true;
        }
        if(aNewSdBerCount%2 != 0)
        {
           aSdBerState = true;
        }

        // Update local defect counts
        myPiiAISCount[anIndex]     = aNewAISCount;
        myPiiLOPCount[anIndex]     = aNewLOPCount;
        myPiiUNEQCount[anIndex]    = aNewUNEQCount;
        myPiiPLMCount[anIndex]     = aNewPLMCount;
        myPiiRDICount[anIndex]     = aNewRDICount;
        myPiiSFBERCount[anIndex]   = aNewSfBerCount;
        myPiiSDBERCount[anIndex]   = aNewSdBerCount;

        // Update actual defect
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_AIS_DEFECT,  aAISState,  aAISEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_LOP_DEFECT,  aLOPState,  aLOPEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_UNEQ_DEFECT, aUNEQState, aUNEQEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_PLM_DEFECT,  aPLMState,  aPLMEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_RDI_DEFECT,  aRDIState,  aRDIEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_SFBER_DEFECT,  aSfBerState,  aSfBerEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_SDBER_DEFECT,  aSdBerState,  aSdBerEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_UPPER_LAYER_FAIL_TA_DEFECT, aUpstreamLayerFailTAState, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_UPPER_LAYER_FAIL_NTA_DEFECT,aUpstreamLayerFailNTAState,false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_LOCK,IsUpstreamLayerLocked(),false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_IS_SRC,aConfig.GetIsConnectedAsSrc(),false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_IS_DST,aConfig.GetIsConnectedAsDst(),false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, IsUpstreamLayerInternalFailed(), false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_INTERNAL_LOCK, IsUpstreamLayerInternalLocked(), false);


        // Validate defect object
        aDefects.Validate();


#if 0
// For now, take our path trace

        //--------------------------------------------------------------
        // STATUS


        //Read trace from PII
        aTrace = aHopPII.GetRxTrace();

        //Check if trace is valid
        // Check code for vaild trace (SONET and SDH are different)
        if (aTrace.IsValid() && !aAISState && !aLOPState)
        {
            //If trace read from PII is different than the trace in STATUS region, update it
            if (!(aStatus.GetReceivedTrace() == aTrace))
            {
                // At all time, if trace is the same for 5 times, set it in STATUS region
                if (++myGoodTraceMessageCounter[anIndex] == 4)
                {
                    hasStatusChanged |= aStatus.SetReceivedTrace(aTrace);
                    myGoodTraceMessageCounter[anIndex] = 0;
                    myBadTraceMessageCounter[anIndex] = 0;
                }
            }
            else
            {
                myGoodTraceMessageCounter[anIndex] = 0;
                myBadTraceMessageCounter[anIndex] = 0;
            }
        }
        else // Trace is not valid
        {
            myGoodTraceMessageCounter[anIndex] = 0;

            // PreviousTrace must be different 15 times before updating STATUS region
            if (++myBadTraceMessageCounter[anIndex] == 15)
                hasStatusChanged |= aStatus.SetReceivedTrace(aDefaultTrace);
        }

        // AIS and LOP disabled TIM
        if(aAISEvent || aLOPState)
        {
            aTIMState=false;
            aTIMEvent=false;
        }
        else if (aConfig.GetTIMMonitoringEnable() == false)
        {
            aTIMState=false;
            aTIMEvent=false;
        }
        else
        {
            //Update TIM state and Count
            if(aStatus.GetReceivedTrace().IsValid())
            {
                aTIMState = !(aStatus.GetReceivedTrace() == aConfig.GetExpectedTrace());
            }
            else
            {
                aTIMState  = false;
            }

        }

        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_HOP_TIM_DEFECT,  aTIMState,  aTIMEvent);
#endif


        if (hasDefectsChanged)
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

        if (hasStatusChanged)
        GetMonIf().GetStatusRegion()->IncModificationCounter();

        // Validate status object
        aStatus.Validate();


    }  // if (hopDefectsChanged)

  }  // for (uint32 anIndex = 0; anIndex < myHopsOnCard; anIndex++)

  if(aStatusDbg.IsDebugFlagSet())
      aStatusDbg.SetProcessTime(PII_TickTimer::readTimer() - startTime);

  myFirstPassFlag = false;
  return NULL;
}
