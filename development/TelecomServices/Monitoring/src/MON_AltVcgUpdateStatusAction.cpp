// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_VcgIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_AltVcgUpdateStatusAction.h"
#include "../MON_AltVcgDefects.h"
#include "../MON_VcgStatus.h"
#include "../MON_VcgConfig.h"
#include "../MON_Region.h"


MON_AltVcgUpdateStatusAction::MON_AltVcgUpdateStatusAction(MON_AppIf& theMonIf,
                                                           uint16 theMaxVcgs,
                                                           uint16 theNbrVcgs2Check,
                                                           TSPII_VcgRegion& theVcgPiiRegion):
    MON_UpdateStatusAction(theMonIf, NULL),
    myMaxVcgs(theMaxVcgs),
    myNbrVcgs2Check(theNbrVcgs2Check),
    myFirstPassFlag(true),
    myVcgPiiRegion(theVcgPiiRegion)
{

    //Reset local counters
    uint16 myMaxVcgs= CT_TEL_NBR_OF_VCGS;
#ifndef PSOSP
    myPiiTX_TLCCount.resize(theMaxVcgs);
    myPiiTX_PLCCount.resize(theMaxVcgs);
    myPiiRX_TLCCount.resize(theMaxVcgs);
    myPiiRX_PLCCount.resize(theMaxVcgs);
    myPiiLOS_AlignCount.resize(theMaxVcgs);
    myPiiTX_FOPCount.resize(theMaxVcgs);
    myPiiRX_FOPCount.resize(theMaxVcgs);

    myMaxVcgs= theMaxVcgs;
#endif
    for(uint32 i = 0;i<myMaxVcgs;i++)
    {
        myPiiTX_TLCCount[i]       = 0;
        myPiiTX_PLCCount[i]       = 0;
        myPiiRX_TLCCount[i]       = 0;
        myPiiRX_PLCCount[i]       = 0;
        myPiiLOS_AlignCount[i]    = 0;
        myPiiTX_FOPCount[i] = 0;
        myPiiRX_FOPCount[i] = 0;
    }

    myNextVcg = 0;

    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myVcgPiiRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);

}

MON_AltVcgUpdateStatusAction::~MON_AltVcgUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myVcgPiiRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
}

FC_Object* MON_AltVcgUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}


FC_Object* MON_AltVcgUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    FC_Milliseconds startTime;
    MON_VcgConfig& aConfig = static_cast<MON_VcgConfig&>((*GetMonIf().GetConfigRegion())[0]);
    if(aConfig.IsDebugFlagSet())
        startTime = PII_TickTimer::readTimer();


  bool hasStatusChanged = false;
  bool hasDefectsChanged = false;

  uint16 aStartIndex = 0;
  uint16 anEndIndex  = myMaxVcgs;
  if ((myMaxVcgs > 1) && (!myFirstPassFlag))
  {
      // Make sure start and end are not past max
      // Set start to 0 if equal or past max
      // and set end to max if past max
      aStartIndex = myNextVcg;
      if (aStartIndex >= myMaxVcgs)
      {
          aStartIndex = 0;
      }
      // End is normally the number of vcgs to check past the start
      anEndIndex = aStartIndex + myNbrVcgs2Check;
      if (anEndIndex > myMaxVcgs)
      {
          anEndIndex = myMaxVcgs;
      }
      myNextVcg = anEndIndex;
  }

  for (uint16 anIndex = aStartIndex; anIndex < anEndIndex; anIndex++)
  {

  MON_VcgStatus&  aStatus     = static_cast<MON_VcgStatus&>((*GetMonIf().GetStatusRegion())[anIndex]);
  TSPII_VcgIf& aVcgPii        = myVcgPiiRegion[anIndex];
  MON_AltVcgDefects& aDefects = static_cast<MON_AltVcgDefects&>((*GetMonIf().GetDefectsRegion())[anIndex]);

        bool hasMembersChanged = false;

  bool aMNDDefect = false, aLOS_MF_AlignDefect = false, aSeqMisMatchDefect = false;
  bool aMNDChange = false, aLOS_MF_AlignChange = false, aSeqMisMatchChange = false;

  uint16 aNumActiveTxMbrs = aVcgPii.GetNumActiveTxMbrs();
  uint16 aNumActiveRxMbrs = aVcgPii.GetNumActiveRxMbrs();
  bool aLcasActive        = aVcgPii.GetLcasRxDetected();

  // Check if numnber of Active TX Members has changed and update status region if it has.
  if (aStatus.GetNumActiveTxMbrs() != aNumActiveTxMbrs)
  {
      hasStatusChanged |= aStatus.SetNumActiveTxMbrs(aNumActiveTxMbrs);
  }

  // Check if numnber of Active RX Members has changed and update status region if it has.
  if (aStatus.GetNumActiveRxMbrs() != aNumActiveRxMbrs)
  {
      hasStatusChanged |= aStatus.SetNumActiveRxMbrs(aNumActiveRxMbrs);
  }

  // Check if the status of Lcas active has changed and update status region if it has.
  if (aStatus.GetLcasDetected() != aLcasActive)
  {
      hasStatusChanged |= aStatus.SetLcasDetected(aLcasActive);
  }


        // Get Tspii Member List
        vector<uint16> aPiiMbrList = aVcgPii.GetMembers();
        uint32 numberOfPiiMbrs = aPiiMbrList.size();

        // Get the current (which is now previous) MON Status Member List
        vector<CT_Vcg_Mbr> aPrevMonMbrList = aStatus.GetMbrList();
        uint32 numberOfPrevMonMbrs = aPrevMonMbrList.size();

        // If the size is different, something has changed.
        if (numberOfPiiMbrs != numberOfPrevMonMbrs)
        {
            hasMembersChanged = true;
            hasStatusChanged = true;
        }

        // Now Clear the current members and build vector again
        aStatus.ClearMemberList();


    // Retrieve each Mbr Status.
        for (uint32 i = 0; i < numberOfPiiMbrs; i++)
    {
            CT_Vcg_Mbr anOldVcgMbr;
            CT_Vcg_Mbr aNewVcgMbr;

            // As long as the members have not changed, then check if each
            // member of the previous list matches the one being built
            if (!hasMembersChanged)
            {
                if (i < numberOfPrevMonMbrs)
                {
                    anOldVcgMbr = aPrevMonMbrList[i];
                }
                else
                {
                    hasMembersChanged = true;
                }
            }  // if (!hasMembersChanged)

            uint16 aMbrIdx = aPiiMbrList[i];

            uint32 aPiiTxSeqNbr           = aVcgPii.GetTxSeqNbr(aMbrIdx);
            uint32 aPiiRxSeqNbr           = aVcgPii.GetRxSeqNbr(aMbrIdx);
            uint32 aPiiRxDifferentalDelay = aVcgPii.GetRxDiffDelay(aMbrIdx);
            CT_TEL_VCG_STATE aPiiTxState  = aVcgPii.GetTxState(aMbrIdx);
            CT_TEL_VCG_STATE aPiiRxState  = aVcgPii.GetRxState(aMbrIdx);
            // force a Fail state if sequence is out of order 
            // (TSPII is not always reporting Fail when only 1 direction is removed)
            if (aPiiTxSeqNbr > numberOfPiiMbrs)
            {
                aPiiTxState = CT_TEL_VCG_ST_FAIL;
            }

            uint32 aPiiLOS_MF_AlignCount  = aVcgPii.GetLosMfAlign(aMbrIdx);
            uint32 aPiiSeqMisMatchCount  = aVcgPii.GetSeqMisMatch(aMbrIdx);
        uint32 aPiiMNDMatchCount     = aVcgPii.GetMbrNotDskew(aMbrIdx);

            aNewVcgMbr.SetVcgMbrInfo(aMbrIdx, aPiiTxSeqNbr, aPiiRxSeqNbr,
                                     aPiiRxDifferentalDelay, aPiiTxState, aPiiRxState,
                                     aPiiSeqMisMatchCount, aPiiLOS_MF_AlignCount, aPiiMNDMatchCount);

            aStatus.AddNewVcgMember(aNewVcgMbr);


            // Regardless of whether members have changed,
            // always look for defect (based on defect counts)
            // in the same manner
        if(aPiiSeqMisMatchCount%2 != 0)
        {
          aSeqMisMatchDefect = true;
        }
        if(aPiiLOS_MF_AlignCount%2 != 0)
        {
          aLOS_MF_AlignDefect = true;
        }
        if(aPiiMNDMatchCount%2 != 0)
        {
          aMNDDefect = true;
        }

            // Now look for changes between Tspii and the old status member
            // Before we check the members against each other, the member ID should match
            if (aMbrIdx != anOldVcgMbr.GetMbrId())
            {
                hasMembersChanged =  true;
            }

            if (!hasMembersChanged)
            {
                // Check if TX seqence number, RX seqence number,
                // differental delay,  TX State, or  RX State have changed
                hasStatusChanged |= (aPiiTxSeqNbr != anOldVcgMbr.GetTxSeqNbr());

                hasStatusChanged |= (aPiiRxSeqNbr != anOldVcgMbr.GetRxSeqNbr());

                hasStatusChanged |= (aPiiRxDifferentalDelay != anOldVcgMbr.GetRxDifferentalDelay());

                hasStatusChanged |= (aPiiTxState != anOldVcgMbr.GetTxState());

                hasStatusChanged |= (aPiiRxState != anOldVcgMbr.GetRxState());

                // Now set defects (change and defects).
                if (aPiiSeqMisMatchCount != anOldVcgMbr.GetSeqMisMatchCount())
                {
                    hasStatusChanged   = true;
                    aSeqMisMatchChange = true;
                }

                if (aPiiLOS_MF_AlignCount != anOldVcgMbr.GetLOS_MF_AlignCount())
                {
                    hasStatusChanged    = true;
                    aLOS_MF_AlignChange = true;
                }

                if (aPiiMNDMatchCount != anOldVcgMbr.GetMNDCount())
                {
                    hasStatusChanged   = true;
                    aMNDChange         = true;
                }

            }  //  eif (!hasMembersChanged)
            else
            {
                hasStatusChanged    = true;
                aLOS_MF_AlignChange = true;
                aSeqMisMatchChange  = true;
                aMNDChange          = true;
            }  //  else of --  if (!hasMembersChanged)

        }  // for (uint32 i = 0; i < numberOfMbrs; i++)



    // Per VCG Mbr Defects
    bool aLOS_MF_AlignState = false, aSeqMisMatchState = false, aMNDState = false;
    bool aLOS_MF_AlignEvent = false, aSeqMisMatchEvent = false, aMNDEvent = false;

    // MON_AltVcgDefects& aDefects = static_cast<MON_AltVcgDefects&>((*GetMonIf().GetDefectsRegion())[anIndex]);

        // Perform hierarchy checks based on Rq 941 of SSM SRS
        // LOM [highest], then MND, then SQM [lowest]
        if (aLOS_MF_AlignDefect)
        {
            aLOS_MF_AlignState = true;
        }
        else
        {
            if (aMNDDefect)
            {
                aMNDState = true;
            }
            else
            {
                if (aSeqMisMatchDefect)
                {
                    aSeqMisMatchState = true;
                }
            }
        }  // else of -- if (aLOS_MF_AlignDefect)


        // Now see if there was a change in any of the fields.
        // P.S. Not really sure this is what is needed, but it probably doesn't hurt
        if (aLOS_MF_AlignChange)
        {
            aLOS_MF_AlignEvent = true;
        }

        if (aMNDChange)
        {
           aMNDEvent = true;
        }

        if (aSeqMisMatchChange)
        {
           aSeqMisMatchEvent = true;
        }

        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_LOS_MF_ALIGN,  aLOS_MF_AlignState,  aLOS_MF_AlignEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_MBR_NOT_DESKEWABLE,   aMNDState,   aMNDEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_SEQMISMATCH,   aSeqMisMatchState,   aSeqMisMatchEvent);

    bool aActive = aVcgPii.GetActiveVcg();

    // Check if the status of Lcas active has changed and update status region if it has.
    if (aStatus.GetActive() != aActive)
    {
        hasStatusChanged |= aStatus.SetActive(aActive);
    }


    // Per VCG Defects
    bool aTX_TLCState = false, aTX_PLCState = false, aRX_TLCState = false, aRX_PLCState = false;
    bool aLOS_AlignState = false, aTX_FOPState = false, aRX_FOPState = false;

    bool aTX_TLCEvent = false, aTX_PLCEvent = false, aRX_TLCEvent = false, aRX_PLCEvent = false;
    bool aLOS_AlignEvent = false, aTX_FOPEvent = false, aRX_FOPEvent = false;

    // Only process this vcg if it is configured
        if ( (aVcgPii.GetVcatType() == CT_TEL_VCAT_STS1) || (aVcgPii.GetVcatType() == CT_TEL_VCAT_STS3C) || (aVcgPii.GetVcatType() == CT_TEL_VCAT_STS12C) ||
             (aVcgPii.GetVcatType() == CT_TEL_VCAT_DS3) || (aVcgPii.GetVcatType() == CT_TEL_VCAT_E3) )
    {
      // Read current defects
      uint32 aPiiTX_TLCCount       = aVcgPii.GetTxTlc();
      uint32 aPiiTX_PLCCount       = aVcgPii.GetTxPlc();
      uint32 aPiiRX_TLCCount       = aVcgPii.GetRxTlc();
      uint32 aPiiRX_PLCCount       = aVcgPii.GetRxPlc();
      uint32 aPiiLOS_AlignCount    = aVcgPii.GetLosAlign();
      uint32 aPiiTX_FOPCount       = aVcgPii.GetTxFop();
      uint32 aPiiRX_FOPCount       = aVcgPii.GetRxFop();

      // Update TX TLC state and count
      if(myPiiTX_TLCCount[anIndex] != aPiiTX_TLCCount)
      {
          aTX_TLCEvent = true;
      }
      // Mask TLC defect if there are no members from the Tspii GetMembers vector
            if ((aPiiTX_TLCCount%2 != 0) && (numberOfPiiMbrs > 0))
      {
          aTX_TLCState = true;
      }

      // Update TX PLC state and count
      if(myPiiTX_PLCCount[anIndex]  != aPiiTX_PLCCount)
      {
          aTX_PLCEvent = true;
      }
      if(aPiiTX_PLCCount%2 != 0)
      {
          aTX_PLCState = true;
      }

      // Update RX TLC state and count
      if(myPiiRX_TLCCount[anIndex]  != aPiiRX_TLCCount)
      {
          aRX_TLCEvent = true;
      }
      // Mask TLC defect if there are no members from the Tspii GetMembers vector
            if ((aPiiRX_TLCCount%2 != 0) && (numberOfPiiMbrs > 0))
      {
          aRX_TLCState = true;
      }

      // Update RX PLC state and count
      if(myPiiRX_PLCCount[anIndex]  != aPiiRX_PLCCount)
      {
          aRX_PLCEvent = true;
      }
      if(aPiiRX_PLCCount%2 != 0)
      {
          aRX_PLCState = true;
      }

      // Update Los Alignment TLC state and count
      if(myPiiLOS_AlignCount[anIndex]  != aPiiLOS_AlignCount)
      {
          aLOS_AlignEvent = true;
      }
      if(aPiiLOS_AlignCount%2 != 0)
      {
          aLOS_AlignState = true;
      }

      // Update TX FOP state and count
      if(myPiiTX_FOPCount[anIndex] != aPiiTX_FOPCount)
      {
          aTX_FOPEvent = true;
      }
      if(aPiiTX_FOPCount%2 != 0)
      {
          aTX_FOPState = true;
      }

      // Update RX FOP state and count
      if(myPiiRX_FOPCount[anIndex]  != aPiiRX_FOPCount)
      {
          aRX_FOPEvent = true;
      }
      if(aPiiRX_FOPCount%2 != 0)
      {
          aRX_FOPState = true;
      }

      // Update local defect counts
      myPiiTX_TLCCount[anIndex]  = aPiiTX_TLCCount;
      myPiiTX_PLCCount[anIndex]  = aPiiTX_PLCCount;
      myPiiRX_TLCCount[anIndex]  = aPiiRX_TLCCount;
      myPiiRX_PLCCount[anIndex]  = aPiiRX_PLCCount;
      myPiiLOS_AlignCount[anIndex]  = aPiiLOS_AlignCount;
      myPiiTX_FOPCount[anIndex]  = aPiiTX_FOPCount;
      myPiiRX_FOPCount[anIndex]  = aPiiRX_FOPCount;

    } // if vcg is configured
          // if ( (aVcgPii.GetVcatType() == CT_TEL_VCAT_STS1) || (aVcgPii.GetVcatType() == CT_TEL_VCAT_STS3C) || (aVcgPii.GetVcatType() == CT_TEL_VCAT_STS12C) ||

    // Update actual defect
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_TX_TLC,        aTX_TLCState,        aTX_TLCEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_TX_PLC,        aTX_PLCState,        aTX_PLCEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_RX_TLC,        aRX_TLCState,        aRX_TLCEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_RX_PLC,        aRX_PLCState,        aRX_PLCEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_LOS_ALIGN,     aLOS_AlignState,     aLOS_AlignEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_TX_FOP,        aTX_FOPState,        aTX_FOPEvent);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_RX_FOP,        aRX_FOPState,        aRX_FOPEvent);

    bool aIsConnectedAsSrc       = aVcgPii.GetIsConnAsSrc();
    bool aIsConnectedAsDest      = aVcgPii.GetIsConnAsDest();

    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_IS_SRC,aIsConnectedAsSrc,false);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_IS_DST,aIsConnectedAsDest,false);


    // Validate defect object
    aDefects.Validate();

    // Validate status object
    aStatus.Validate();

  }  //   for (uint16 anIndex = aStartIndex; anIndex < anEndIndex; anIndex++)

  // Calculate the vcg for next invocation
  // Always check all of the Tspii instances for the refresh
  for (uint16 anIndex = 0; anIndex < myMaxVcgs; anIndex++)
  {
      MON_VcgStatus& aStatus = static_cast<MON_VcgStatus&>((*GetMonIf().GetStatusRegion())[anIndex]);
      TSPII_VcgIf&   aVcgPii = myVcgPiiRegion[anIndex];

      // Even though this is a status field, mark hasDefectsChanged so that
      // the EvcAutomaticAction will run (it had the defects as an input region)
      hasDefectsChanged |= aStatus.SetForceEvcRefresh(aVcgPii.GetForceEvcRefreshAndClearForce());

      // To speed up respnse time for vcg resequencing recovery go check for sequence mismatch
      // on all active VCG
      // only check VCGs with more than 1 member

      if (( aVcgPii.GetActiveVcg()) && (aVcgPii.GetNumActiveRxMbrs() >1))
      {
          aVcgPii.CheckSeqMsMatch();
      }
  }


  if (hasDefectsChanged)
    {
      GetMonIf().GetDefectsRegion()->IncModificationCounter();
    }

  if (hasStatusChanged)
    {
      GetMonIf().GetStatusRegion()->IncModificationCounter();
    }

  if(aConfig.IsDebugFlagSet())
    {
      aConfig.SetProcessTime(PII_TickTimer::readTimer() - startTime);
    }

  myFirstPassFlag = false;
  return NULL;
}
