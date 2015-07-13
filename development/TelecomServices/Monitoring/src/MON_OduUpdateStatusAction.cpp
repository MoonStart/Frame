// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_DwIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <CsPii/CSPII_CardIF.h>
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbReason.h>
#include <T6100_CardIf.h>
#include "../MON_OduUpdateStatusAction.h"
#include "../MON_OduDefects.h"
#include "../MON_OduCounters.h"
#include "../MON_OduStatus.h"
#include "../MON_OduConfig.h"
#include "../MON_OtuDefects.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"


MON_OduUpdateStatusAction::MON_OduUpdateStatusAction(MON_AppIf&        theMonIf,
                                                     TSPII_DwRegion&   theDwPiiRegion,
                                                     MON_AppIf*        theUpstreamLayerIf,
                                                     MON_AppIf*        theIMUXLayerIf,
                                                     CT_NumberOfOdus   theOdusOnCard,
                                                     bool              theUpperLayerRemoteFlag,
                                                     bool              theUpperLayerPoolFlag,
                                                     CFG_OduCfgRegion* theOduConfigRegion):
    MON_UpdateStatusAction(theMonIf,theUpstreamLayerIf),
    myDwPiiRegion(theDwPiiRegion),
    myIMUXLayerIf(theIMUXLayerIf),
    myOdusOnCard(theOdusOnCard),
    myUpperLayerRemoteFlag(theUpperLayerRemoteFlag),
    myUpperLayerPoolFlag(theUpperLayerPoolFlag),
    myFirstPassFlag(true),
    myNumConsecTraceComp(1),
    myOduConfigRegion(theOduConfigRegion),
    myTimCheckByMon(true)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myDwPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    if(myIMUXLayerIf)     GetBbAction()->AddInputRegion(myIMUXLayerIf->GetDefectsRegion());
    if(myOduConfigRegion) GetBbAction()->AddInputRegion(myOduConfigRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

    myNextOdu = 0;
    myNbrOdu2Check = (uint8)myOdusOnCard;

    if (CSPII_CardIF::GetInstance()->GetCardType() == OSM20) 
    {
        /*For OSM20, update only part ODU in each UpdateObject so that it will not have big latency for protection
        each period(100ms) update 2 ODU0F; total 16 ODU0F; 
        each period(200ms) update 2 ODU1 ; total  8 ODU1;
        each period(400ms) update 1 ODU2 ; total  2 ODU2;*/ 
        if ( NUMBER_OF_POOLED_ODU0FS_ON_OSM20 == myOdusOnCard)//16 ODU0F;
        {
            myNbrOdu2Check /= 8;
        }
        else if ( NUMBER_OF_POOLED_ODU1S_ON_OSM20 == myOdusOnCard )//8 ODU1;
        {
            myNbrOdu2Check /= 4;
        }
        else if ( NUMBER_OF_POOLED_ODU2S_ON_OSM20 == myOdusOnCard )//2 ODU2
        {
            myNbrOdu2Check /= 2;
        }        
    }
    else if (CSPII_CardIF::GetInstance()->GetCardType() == OMMX) 
    {
        /*For OMM, update only part ODU in each UpdateObject so that it will not have big latency for protection
        each period(100ms) update 3 ODU0F; total 24 ODU0F; 
        each period(200ms) update 3 ODU1 ; total 12 ODU1;
        each period(400ms) update 1 ODU2 ; total  2 ODU2;*/ 
        if ( NUMBER_OF_POOLED_ODU0FS_ON_OMMX == myOdusOnCard)//24 ODU0F;
        {
            myNbrOdu2Check /= 8;
        }
        else if ( NUMBER_OF_POOLED_ODU1S_ON_OMMX == myOdusOnCard )//12 ODU1;
        {
            myNbrOdu2Check /= 4;
        }
        else if ( NUMBER_OF_POOLED_ODU2S_ON_OMMX == myOdusOnCard )//2 ODU2
        {
            myNbrOdu2Check /= 2;
        }        
    }
    else if (CSPII_CardIF::GetInstance()->GetCardType() == HGTMM || 
             CSPII_CardIF::GetInstance()->GetCardType() == HGTMMS) // Coriant HGTMMS
    {
        /*For HGTMM, update only part ODU in each UpdateObject so that it will not have big latency for protection
        each period(200ms) update 5 ODU0F; total 20 ODU0F; 
        each period(200ms) update 5 ODU2 ; total 20 ODU2;
        each period(400ms) update 2 ODU3 ; total 4  ODU3;
        each period(400ms) update 1 ODU4 ; total 1  ODU4;*/ 
        if ( NUMBER_OF_POOLED_ODU0FS_ON_HGTMM == myOdusOnCard)//20 ODUF;
        {
            myNbrOdu2Check /= 4;
        }
        else if ( NUMBER_OF_POOLED_ODU2S_ON_HGTMM == myOdusOnCard )//20 ODU2;
        {
            myNbrOdu2Check /= 4;
        }
        else if ( NUMBER_OF_POOLED_ODU3S_ON_HGTMM == myOdusOnCard )//4 ODU3
        {
            myNbrOdu2Check /= 2;
        }
        else if ( NUMBER_OF_POOLED_ODU4S_ON_HGTMM == myOdusOnCard )//4 ODU3
        {
            myNbrOdu2Check /= 1;
        }        
    }
    else if (CSPII_CardIF::GetInstance()->GetCardFamily() == OSM_FAM) 
    {
        /*
            For OSM2, update only part ODU in each UpdateObject so that it will not have big latency for protection
            each period(100ms) update 20 ODU0F; total 160 ODU0F; 
            each period(200ms) update 20 ODU1 ; total 80 ODU1;
        */ 
        if ( NUMBER_OF_POOLED_ODU0FS_ON_OSM2 == myOdusOnCard) // 160 ODUF;
        {
            myNbrOdu2Check /= 8;
        }
        else if ( NUMBER_OF_POOLED_ODU1S_ON_OSM2 == myOdusOnCard ) //80 ODU1;
        {
            myNbrOdu2Check /= 4;
        }      
        
        myTimCheckByMon = false;
    }

    for (uint32 anIndex = 0; anIndex < myOdusOnCard; anIndex++)
    {
        myGoodTraceMessageCounter.push_back((uint32) 0);
        myBadTraceMessageCounter.push_back((uint32) 0);
        myFirstRcvdOduTrace.push_back(true);
        myPiiAISCount.push_back((uint32) 0);
        myPiiLCKCount.push_back((uint32) 0);
        myPiiOCICount.push_back((uint32) 0);
        myPiiBDICount.push_back((uint32) 0);
        myPiiInternalAISCount.push_back((uint32) 0);
        myPiiSdBerCount.push_back((uint32) 0);
        myPiiSfBerCount.push_back((uint32) 0);
        myPiiPLMCount.push_back((uint32) 0);
        myPiiMSIMCount.push_back((uint32) 0);
        myPiiGenAISCount.push_back((uint32) 0);
        myPiiLOFLOMCount.push_back((uint32) 0);
        myPiiLOOMFICount.push_back((uint32) 0);
        myPiiTspiiDwInstance.push_back((uint16) 0);
        myLocalPRBSRXSessionCounter.push_back((uint32) 0);
        myPiiSSFforSGEOCount.push_back((uint32) 0);
    }

    // For most cards, we'll try the default number of consectutive trace messages 
    // needed to accept a new/different trace to be one (1).  If this needs to change 
    // for any card, change it here
    //T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
    //if (aCardContext)
    //{
    //    if (aCardContext->GetCardFamily() == ?)
    //    {
    //        myNumConsecTraceComp = ?;
    //    }
    //}
}

MON_OduUpdateStatusAction::~MON_OduUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myDwPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    if(myIMUXLayerIf)     GetBbAction()->RemoveInputRegion(myIMUXLayerIf->GetDefectsRegion());
    if(myOduConfigRegion) GetBbAction()->RemoveInputRegion(myOduConfigRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_OduUpdateStatusAction::Suspend(unsigned theRunReason,
                                              FC_Object* theInvokerObj,
                                              FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}

FC_Object* MON_OduUpdateStatusAction::Process(unsigned theRunReason,
                                              FC_Object* theInvokerObj,
                                              FC_Object* theParam)
{
    UpdateObject(theRunReason);
    return NULL;
}


void MON_OduUpdateStatusAction::UpdateObject(unsigned theRunReason)
{
    uint16 aTspiiDwInstance = 0;
    uint32 aNumTspiiInstancesInPool = myDwPiiRegion.Size();

    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());

    uint32 aStartIndex = 0; 
    uint32 anEndIndex = myOdusOnCard;
    if ((myOdusOnCard > 1) && (!myFirstPassFlag) && (myOdusOnCard != myNbrOdu2Check))
    {
        // When there is more than one instance, then loop through using myNbrOdu2Check
        // Make sure start and end are not past max
        // Set start to 0 if equal or past max
        // and set end to max if past max
        aStartIndex = myNextOdu;
        if (aStartIndex >= myOdusOnCard)
        {
            aStartIndex = 0;
        }
        // End is normally the number of Odus to check past the start
        anEndIndex = aStartIndex + myNbrOdu2Check;
        if (anEndIndex > myOdusOnCard)
        {
            anEndIndex = myOdusOnCard;
        }
        myNextOdu = (uint8)anEndIndex;
    }

    for (uint32 anIndex = aStartIndex; anIndex < anEndIndex; anIndex++)
    {
        CFG_Odu* aCfgObject = NULL;
        if (myOduConfigRegion) 
        {
            if (anIndex >= myOduConfigRegion->Size())
            {
                break;
            }
            // Find the CFG instance
            aCfgObject = &(*myOduConfigRegion)[bbindex_t(anIndex)];
        }

        MON_OduDefects& aDefects   = static_cast<MON_OduDefects&>((*GetMonIf().GetDefectsRegion())[bbindex_t(anIndex)]);
        MON_OduStatus& aStatus     = static_cast<MON_OduStatus&>((*GetMonIf().GetStatusRegion())[bbindex_t(anIndex)]);
        MON_OduCounters& aCounters = static_cast<MON_OduCounters&>((*GetMonIf().GetCountersRegion())[bbindex_t(anIndex)]);
        MON_OduConfig& aConfig     = static_cast<MON_OduConfig&>((*GetMonIf().GetConfigRegion())[bbindex_t(anIndex)]);

        // Find Tspii instance
        aTspiiDwInstance = uint16(CT_DEFAULT_ODU_POSITION);
        if (myOdusOnCard == 1) 
        {
            aTspiiDwInstance = 0;
        }
        else if (aCfgObject) 
        {
            // Check identifier if the CFG instance has the proper type
            if ((aCfgObject->GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT) || 
                (aCfgObject->GetOduObjectType() == CT_ODU_POOL_CLIENT_INSIDE_ODU) ||
                (aCfgObject->GetOduObjectType() == CT_ODU_POOL_MUX))
            {
                // This part finds the Tspii instance of the Pool
                CT_ODU_Identifier aOduIdentifier = aCfgObject->GetOduIdentifier();
                aTspiiDwInstance = TSPII_SubApplication::GetInstance()->GetOduPoolIndex(aOduIdentifier.GetIdValue());
            }  // if ((aCfgObject->GetOduObjectType() == 
        }  // if (myOdusOnCard == 

        // If the Tspii instance has changed, reset the regions
        if (myPiiTspiiDwInstance[anIndex] != aTspiiDwInstance) 
        {
            if(!myFirstPassFlag)
            {
                aConfig.Reset();
                aCounters.Reset();
                aDefects.Reset();
                GetMonIf().GetDefectsRegion()->IncModificationCounter();
                aStatus.Reset();
                GetMonIf().GetStatusRegion()->IncModificationCounter();
            }
            myPiiTspiiDwInstance[anIndex] = aTspiiDwInstance;
        }

        // If the is no Tspii instance (unassigned) or the instance is out of range, 
        // then skip to the next instance (nothing to look up)         
        if ((aTspiiDwInstance == uint16(CT_DEFAULT_ODU_POSITION)) ||
            (aTspiiDwInstance  > aNumTspiiInstancesInPool))
        {
            continue;
        }


        // Check for upper layer from a pool.
        bool  aPoolUpperLayerFailed = false;
        bool  aPoolUpperLayerFailedForMaintSig = false;
        bool  aPoolUpperLayerNTA    = false;
        bool  aPoolUpperLayerPNLTA  = false;
        bool  aPoolUpperLayerLocked = false;
        bool  aPoolUpperLayerDegrade = false;

        bool  aPoolUpperLayerInternalFailed = false;
        bool  aPoolUpperLayerInternalNTA    = false;
        bool  aPoolUpperLayerInternalPNLTA  = false;
        bool  aPoolUpperLayerInternalLocked = false;

        bool  aPoolUpperLayerTermLpbked = false;
        uint8 aPoolLockBitMask  = 0;
        uint8 aPoolInternalLockBitMask  = 0;

        // Must have these to find the proper 
        if ((myUpperLayerPoolFlag) && (aCfgObject) && (aCardContext))
        {
            CT_ODU_ServerID aServerID = aCfgObject->GetServerID();
            MON_AppIf*      aPoolApp  = GetPoolApp(aServerID, aCardContext);

            // Look at ServerID first
            if (aPoolApp) 
            {
                if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)
                {
                    // application found above, for OTU, always 1 instance.
                    MON_Defects& aULDefects  = static_cast<MON_Defects&>((*(aPoolApp)->GetDefectsRegion())[0]);

                    aPoolUpperLayerFailed = aULDefects.IsLayerInDefects();
                    aPoolUpperLayerFailedForMaintSig = aULDefects.IsLayerForMaintSigInDefects();  
                    aPoolUpperLayerLocked = aULDefects.IsLayerLocked();
                    aPoolUpperLayerInternalFailed = aULDefects.IsLayerInternalInDefects();
                    aPoolUpperLayerInternalPNLTA  = aULDefects.IsInternalInPropagateNextLayerDefectsTA();
                    aPoolUpperLayerInternalLocked = aULDefects.IsLayerInternalLocked();
                    aPoolUpperLayerTermLpbked     = aULDefects.IsLayerInTermLpbk();
                    aPoolUpperLayerDegrade        = aULDefects.IsLayerInDegrade();
                }
                else  
                {
                    // application found above, for ODU and Tcm applications, 
                    // use the instance from the server ID to find the correct instance.
                    uint16 aPoolIndex = aServerID.GetPoolInstance();
                    MON_Defects& aULRDefects = static_cast<MON_Defects&>((*(aPoolApp)->GetDefectsRegion())[aPoolIndex]);

                    uint32 aUpperTADefectCount  = 0L,    aUpperNTADefectCount = 0L,    aUpperPNLTADefectCount = 0L,    
                           aUpperNimDefectCount = 0L,    aUpperSrcDefectCount = 0L;
                    bool   aUpperTADefectState  = false, aUpperNTADefectState = false, aUpperPNLTADefectState = false, 
                           aUpperNimDefectState = false, aUpperSrcDefectState = false;

                    if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu) 
                    {   //MR184542 remove the aULRDefects.IsAnyTcmLevelLocked(aULRDefects.GetLockBitMask()) ||
                        //from the aPoolUpperLayerFailed
                        aPoolUpperLayerFailed = (aULRDefects.IsLayerInDefects() ||
                                                 aULRDefects.IsLayerLocked() ||                                                 
                                                 aULRDefects.IsInPropagateNextLayerDefectsTA());
                        aPoolUpperLayerFailedForMaintSig = (aULRDefects.IsLayerForMaintSigInDefects() ||
                                                            aULRDefects.IsLayerLocked() ||                                                 
                                                            aULRDefects.IsInPropagateNextLayerDefectsTA()); 
                        aPoolUpperLayerNTA    = aULRDefects.IsLayerInDefectsNTA();

                        aPoolUpperLayerInternalFailed = (aULRDefects.IsLayerInternalInDefects() ||
                                                         aULRDefects.IsLayerInternalLocked() ||
                                                         aULRDefects.IsAnyTcmLevelLocked(aULRDefects.GetInternalLockBitMask()) ||
                                                         aULRDefects.IsInternalInPropagateNextLayerDefectsTA());;
                        aPoolUpperLayerInternalNTA    = aULRDefects.IsLayerInternalInDefectsNTA();

                        aPoolUpperLayerTermLpbked     = aULRDefects.IsLayerInTermLpbk();
                        aPoolUpperLayerDegrade        = aULRDefects.IsLayerInDegrade();

                    }  // if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu)
                    else if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm) 
                    {
                        aULRDefects.GetDefectStatus(CT_TEL_TCM_UPPER_LAYER_FAIL_TA_DEFECT,  &aUpperTADefectCount,  &aUpperTADefectState);
                        aULRDefects.GetDefectStatus(CT_TEL_TCM_UPPER_LAYER_FAIL_NTA_DEFECT, &aUpperNTADefectCount, &aUpperNTADefectState);
                        aULRDefects.GetDefectStatus(CT_TEL_TCM_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, &aUpperPNLTADefectCount, &aUpperPNLTADefectState);
                        aULRDefects.GetDefectStatus(CT_TEL_TCM_NIM_MODE_DEFECT,  &aUpperNimDefectCount,  &aUpperNimDefectState);
                        aULRDefects.GetDefectStatus(CT_TEL_TCM_SRC_MODE_DEFECT,  &aUpperSrcDefectCount,  &aUpperSrcDefectState);

                        // if in same k-value, propagate server bit mask
                        // Read bit mask, but there isn't a need to write to it.
                        aPoolLockBitMask      = aULRDefects.GetLockBitMask();

                        // Check if the direct upper layer should be ignored
                        // For example, for TCM, NIM and SRC-ONLY Tcm Mode should not 
                        // look at defects from that layer 
                        if (aULRDefects.IsIgnoreDirectUpperLayerDefects())
                        {
                            aPoolUpperLayerFailed = aUpperTADefectState;
                            aPoolUpperLayerFailedForMaintSig = aUpperTADefectState;
                            aPoolUpperLayerNTA    = aUpperNTADefectState;
                            aPoolUpperLayerPNLTA  = aUpperPNLTADefectState;
                        }
                        else
                        {
                            aPoolUpperLayerFailed = aULRDefects.IsLayerInDefects();
                            aPoolUpperLayerFailedForMaintSig = aULRDefects.IsLayerForMaintSigInDefects(); 
                            aPoolUpperLayerNTA    = (aULRDefects.IsLayerInDefectsNTA() ||
                                                     aUpperNTADefectState);
                            aPoolUpperLayerPNLTA  = (aULRDefects.IsInPropagateNextLayerDefectsTA() ||
                                                     aUpperPNLTADefectState);
                        }  //  (else part of) if (aULRDefects.IsIgnoreDirectUpperLayerDefects())

                        aPoolUpperLayerTermLpbked =  aULRDefects.IsLayerInTermLpbk();
                        aPoolUpperLayerDegrade    =  aULRDefects.IsLayerInDegrade();

                        // If the server TCM mode is either SRC_SNK_NIM or SNK_NIM (NimDefect) 
                        // or SOURCE (SrcDefect), an upper layer lock does not fail the client, 
                        // but the lock is propagated; otherwise, an upper layer lock fails the layer.
                        if (aUpperNimDefectState || aUpperSrcDefectState) 
                        {
                            aPoolUpperLayerLocked |= aULRDefects.IsLayerLocked();
                        }
                        else
                        {
                            aPoolUpperLayerFailed |= aULRDefects.IsLayerLocked();
                            aPoolUpperLayerFailedForMaintSig = aPoolUpperLayerFailed;
                        }
                    }  // else if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)

                    // Internal Defects pass through because there are no internal defects for TCM
                    aPoolUpperLayerInternalFailed = aULRDefects.IsLayerInternalInDefects();
                    aPoolUpperLayerInternalPNLTA  = aULRDefects.IsInternalInPropagateNextLayerDefectsTA();
                    // Note: Internal Lock Bit Mask is taken care of below when there is a B direction TCM,
                    // but we have to check the internal lock for cards that have opposite sides 
                    // (which should not have B direction TCMs).  Let's hope they are mutually exclusive.
                    // Therefore, this call will set the internal lock bit mask from the internal bit mask
                    // (for pass through info fom the OTU layer).  The call below will get the information
                    // from the the normal bit mask.  That call is being changed to a |= as a precaution.
                    aPoolInternalLockBitMask      = aULRDefects.GetInternalLockBitMask();
                }  // (else part of) if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)
            }  //  if (aPoolApp)
            

            // Now look at the Alternate Server ID
            CT_ODU_ServerID anAltServerID = aCfgObject->GetAltServerID();
            aPoolApp = GetPoolApp(anAltServerID, aCardContext);
            if ((aPoolApp) && (anAltServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm))
            {
                uint16 aPoolIndex = anAltServerID.GetPoolInstance();
                MON_Defects& aULRDefects = static_cast<MON_Defects&>((*(aPoolApp)->GetDefectsRegion())[aPoolIndex]);

                uint32 aUpperTADefectCount  = 0L,    aUpperNTADefectCount = 0L,    aUpperPNLTADefectCount = 0L,    
                       aUpperNimDefectCount = 0L,    aUpperSrcDefectCount = 0L;
                bool   aUpperTADefectState  = false, aUpperNTADefectState = false, aUpperPNLTADefectState = false, 
                       aUpperNimDefectState = false, aUpperSrcDefectState = false;

                aULRDefects.GetDefectStatus(CT_TEL_TCM_UPPER_LAYER_FAIL_TA_DEFECT,  &aUpperTADefectCount,  &aUpperTADefectState);
                aULRDefects.GetDefectStatus(CT_TEL_TCM_UPPER_LAYER_FAIL_NTA_DEFECT, &aUpperNTADefectCount, &aUpperNTADefectState);
                aULRDefects.GetDefectStatus(CT_TEL_TCM_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, &aUpperPNLTADefectCount, &aUpperPNLTADefectState);
                aULRDefects.GetDefectStatus(CT_TEL_TCM_NIM_MODE_DEFECT,  &aUpperNimDefectCount,  &aUpperNimDefectState);
                aULRDefects.GetDefectStatus(CT_TEL_TCM_SRC_MODE_DEFECT,  &aUpperSrcDefectCount,  &aUpperSrcDefectState);

                // if in same k-value, propagate server bit mask
                // Read bit mask, but there isn't a need to write to it.
                aPoolInternalLockBitMask |= aULRDefects.GetLockBitMask();

                // Check if the direct upper layer should be ignored
                // For example, for TCM, NIM and SRC-ONLY Tcm Mode should not 
                // look at defects from that layer 
                if (aULRDefects.IsIgnoreDirectUpperLayerDefects())
                {
                    aPoolUpperLayerInternalFailed = aUpperTADefectState;
                    aPoolUpperLayerInternalNTA    = aUpperNTADefectState;
                    aPoolUpperLayerInternalPNLTA  = aUpperPNLTADefectState;
                }
                else
                {
                    // If here, it is MUX case or from a TCM, so the the Lock becomes a Fail
                    aPoolUpperLayerInternalFailed = aULRDefects.IsLayerInDefects() || aULRDefects.IsLayerLocked();
                    aPoolUpperLayerInternalNTA    = (aULRDefects.IsLayerInDefectsNTA() ||
                                                     aUpperNTADefectState);
                    aPoolUpperLayerInternalPNLTA  = (aULRDefects.IsInPropagateNextLayerDefectsTA() ||
                                                     aUpperPNLTADefectState);
                }  // if (aULRDefects.IsIgnoreDirectUpperLayerDefects())

                // If the server TCM mode is either SRC_SNK_NIM or SNK_NIM (NimDefect) 
                // or SOURCE (SrcDefect), an upper layer lock does not fail the client, 
                // but the lock is propagated; otherwise, an upper layer lock fails the layer.
                if (aUpperNimDefectState || aUpperSrcDefectState) 
                {
                    aPoolUpperLayerLocked |= aULRDefects.IsLayerLocked();
                }
                else
                {
                    //based on t71mr00179663, B side TCM lock should not cause ODU change to SGEO.
                    //aPoolUpperLayerFailed |= aULRDefects.IsLayerLocked();
                }
            }  //  if ((aPoolApp) && (anAltServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)) 

        }  // if ((myUpperLayerPoolFlag) && (aCfgObject) && (aCardContext))



        TSPII_DwIf& aDwPII     = myDwPiiRegion[aTspiiDwInstance];

        bool hasDefectsChanged = false;
        bool aLayerLockedState = false;
        bool aUpperLayerFailed = false;
        bool aUpperLayerFailedForMaintSig = false;
        bool aUpperLayerInternalFailed = false;
        bool aUpperLayerDegrade = false;


        //--------------------------------------------------------------
        // CONFIG
        //Configure defect region to fail on TIM defect
        hasDefectsChanged |= aDefects.SetLayerFailOnTimEnable(aConfig.GetLayerFailOnTIM());

        // set Fail Layer Bit Mask for ODU
        aDefects.SetFailLayerBitMask(aConfig.GetFailLayerBitMask()); 

        if(aConfig.GetLayerLocked())
        {   
            aLayerLockedState = true;
        }

        // New for 5.1.  Remote defects from another layer
        // If the upper layer is a remote facility, then the lock does 
        // not flow through and becomes a fail (see below for upper layer fail).
        // Therefore, check to make sure the lock does not propagate
        // if it is remote, but does when it is not (which is normal)
        // Note: if this logic is needed for other layers, then it can moved to the base class
        // Note 2: can be locked from a pooled client that is locked (set above)
        if (!myUpperLayerRemoteFlag) 
        {
            aLayerLockedState |= IsUpstreamLayerLocked() || aPoolUpperLayerLocked;
        }


        // Note: that Agent is now writing down cross connect informatiom, namely
        // bool SetIsConnectedAsSrc(bool theState);
        // bool SetIsConnectedAsDst(bool theState);
        // But this information is converted to a defect (see below) 
        // and not written down to TSPII
        // It is also used for SGEO state, so keep locals around for use
        bool aIsConnectedAsSrc    = aConfig.GetIsConnectedAsSrc();
        bool aIsConnectedAsDst    = aConfig.GetIsConnectedAsDst();


        //--------------------------------------------------------------
        // COUNTERS
        // IMPROV: interface for ODU counters
        // For 64 bits, always read the high bits last
        aCounters.SetErrorCount(CT_TEL_ODU_BEI,0);
        aCounters.SetErrorCount(CT_TEL_ODU_HIGH_BEI,0);
        aCounters.SetErrorCount(CT_TEL_ODU_BIP8,aDwPII.GetBip8Count());
        aCounters.SetErrorCount(CT_TEL_ODU_HIGH_BIP8,aDwPII.GetHighBip8Count());

        //--------------------------------------------------------------
        // DEFECTS
        // 
        // Set whether Odu is non terminating (determines above from CFG)
        aDefects.SetIsOduNonTerm(!aConfig.GetIsMonOduTerm());

        // Read current defects
        bool aAISState=false, aBDIState=false, aLCKState=false, aOCIState=false, aTIMState=false, aSdBerState=false, aSfBerState=false, aInternalAISState=false, aPLMState=false, aMSIMState=false, aGenAISState=false, aLOFLOMState=false, aLOOMFIState=false, aSSFforSGEOState=false;
        bool aAISEvent=false, aBDIEvent=false, aLCKEvent=false, aOCIEvent=false, aTIMEvent=false, aSdBerEvent=false, aSfBerEvent=false, aInternalAISEvent=false, aPLMEvent=false, aMSIMEvent=false, aGenAISEvent=false, aLOFLOMEvent=false, aLOOMFIEvent=false, aSSFforSGEOEvent=false;

        bool aIMUXLockState=false;

        uint32 aNewAISCount          = aDwPII.GetAIS();
        uint32 aNewLCKCount          = aDwPII.GetLCK();
        uint32 aNewBDICount          = aDwPII.GetBDI();
        uint32 aNewOCICount          = aDwPII.GetOCI();
        uint32 aNewSdBerCount        = aDwPII.GetBerSd();    
        uint32 aNewSfBerCount        = aDwPII.GetBerSf();
        uint32 aNewPLMCount          = aDwPII.GetPLM();
        uint32 aNewMSIMCount         = aDwPII.GetMSIM();
        uint32 aNewGenAISCount       = aDwPII.GetGenAIS();
        uint32 aNewLOFLOMCount       = aDwPII.GetLOFLOM();
        uint32 aNewLOOMFICount       = aDwPII.GetLOOMFI();
        uint32 aNewSSFforSGEOCount   = aDwPII.GetSSFforSGEO();

        // If there, Update M layer defects with IMUX facility
        if(myIMUXLayerIf)
        {
            MON_Defects& aIMUXDefects = static_cast<MON_Defects&>( (*myIMUXLayerIf->GetDefectsRegion())[0] ); 

            // Update aAISState usimg IMUX layer is in defect
            aAISState |= (aIMUXDefects.IsLayerInDefects());


            // Update Lock state using IMUX layer  
            aIMUXLockState |= (aIMUXDefects.IsLayerLocked());       
        }

        // New for 5.1.  Remote defects from another layer
        // The idea here is that if the upper layer is from another facility,
        // then the lock does not flow through and becomes a fail.
        if (myUpperLayerRemoteFlag) 
        {
            // If Upper Layer is Remote, then upper layer fails based on both lock and defects
            aUpperLayerFailed |= IsUpstreamLayerFailed() || IsUpstreamLayerLocked();
        }
        else
        {
            // otherwise, defects are processed as normal.
            // Note: can be failed from a pooled client or mux (set above)
            aUpperLayerFailed |= IsUpstreamLayerFailed() || aPoolUpperLayerFailed;
            aUpperLayerFailedForMaintSig |= IsUpstreamLayerFailedForMaintSig() || aPoolUpperLayerFailedForMaintSig;  
        }

        aUpperLayerDegrade |= IsUpstreamLayerDegrade() || aPoolUpperLayerDegrade;


        // Create the AIS defect if upstream layer is failed
        // Note: MSIM and LOFLOM are TA Adpation Layer defects which are
        // actually upper layer defects (for the currect layer), 
        // so they are treated similar to AIS.
        // Also, when the Upper Layer is not failed, those defects must be read.
        if (aUpperLayerFailed)
        {
            aAISState     = true; 
            aAISEvent     = false;
            aMSIMState    = false;
            aMSIMEvent    = false;
            aLOFLOMState  = false;
            aLOFLOMEvent  = false;
        }
        else
        {
            // Update AIS state and count
            if(myPiiAISCount[anIndex] != aNewAISCount)
            {
                aAISEvent = true;
            }
            if(aNewAISCount%2 != 0)
            {
                aAISState = true;        
            }

            // Update MSIM state and count
            if(myPiiMSIMCount[anIndex] != aNewMSIMCount)
            {
                aMSIMEvent = true;
            }
            if(aNewMSIMCount%2 != 0)
            {
                aMSIMState = true;        
            }

            // Update LOFLOM state and count
            if(myPiiLOFLOMCount[anIndex] != aNewLOFLOMCount)
            {
                aLOFLOMEvent = true;
            }
            if(aNewLOFLOMCount%2 != 0)
            {
                aLOFLOMState = true;        
            }

            // Update LOOMFI state and count
            if(myPiiLOOMFICount[anIndex] != aNewLOOMFICount)
            {
                aLOOMFIEvent = true;
            }
            if(aNewLOOMFICount%2 != 0)
            {
                aLOOMFIState = true;        
            }

        }  // (else of) if (aUpperLayerFailed)

        if (aAISState || aMSIMState || aLOFLOMState) 
        {
            aLCKEvent    = false;
            aLCKState    = false;        
            aOCIEvent    = false;
            aOCIState    = false;        
            aBDIState    = false;
            aBDIEvent    = false;
		    aSdBerState  = false;
            aSdBerEvent  = false;
		    aSfBerState  = false;
            aSfBerEvent  = false;
            aGenAISState = false;
            aGenAISEvent = false; 
            aPLMState    = false;
            aPLMEvent    = false;
        }  // if (aAISState || aMSIMState || aLOFLOMState)
        else
        {
            // Update LCK state and count
            if(myPiiLCKCount[anIndex] != aNewLCKCount)
            {
                aLCKEvent = true;
            }
            if(aNewLCKCount%2 != 0)
            {
                aLCKState = true;        
            }

            // Update OCI state and count
            if(myPiiOCICount[anIndex] != aNewOCICount)
            {
                aOCIEvent = true;
            }
            if(aNewOCICount%2 != 0)
            {
                aOCIState = true;        
            }

            // LCK or OCI disable BDI
            if (aLCKState || aOCIState)
            {
                aBDIState = false;
                aBDIEvent = false;
            }  // if (aLCKState || aOCIState)
            else
            {
                // Update BDI state and count
                if(myPiiBDICount[anIndex] != aNewBDICount)
                {
                    aBDIEvent = true;
                }
                if(aNewBDICount%2 != 0)
                {
                    aBDIState = true;        
                }

            }  // (else of) if (aLCKState || aOCIState)

            // Update SfBer state and count
            if(myPiiSfBerCount[anIndex] != aNewSfBerCount)
            {
                aSfBerEvent = true;
            }
            if(aNewSfBerCount%2 != 0)
            {
                aSfBerState = true;        
            }

            // Update SdBer state and count
            if(myPiiSdBerCount[anIndex] != aNewSdBerCount)
            {
                aSdBerEvent = true;
            }
            if(aNewSdBerCount%2 != 0)
            {
                aSdBerState = true;        
            }
            
            // Update Generic AIS state and count
            if(myPiiGenAISCount[anIndex] != aNewGenAISCount)
            {
                aGenAISEvent = true;
            }
            if(aNewGenAISCount%2 != 0)
            {
                aGenAISState = true;        
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


        }  // (else of) if (aAISState || aMSIMState || aLOFLOMState)


        // Update SSFforSGEO state and count
        // This SSFforSGEO state is introduced by HGTMM. There are internal ODU2 cross connections in one HGTMM.
        // If the line side detects MISM-ODU and LOFLOM, the line side is locked by the user, the client side's
        // GetSSFforSGEO() will return true and the status of client side ODU2 will be OOS-SGEO.
        // Even if AIS is true, SSFforSGEO still needs to be set.
        if(myPiiSSFforSGEOCount[anIndex] != aNewSSFforSGEOCount)
        {
            aSSFforSGEOEvent = true;
        }
        if(aNewSSFforSGEOCount%2 != 0)
        {
            aSSFforSGEOState = true;        
        }

        // Look at Line to Port Defect(s)
        // Update Internal AIS-L state and count
        // if upstream layer is fail, force a AIS   
        uint32 aNewInternalAISCount   = aDwPII.GetInternalAIS();

        // Note: can be internal failed from a pooled client (set above)
        if (IsUpstreamLayerInternalFailed() || aPoolUpperLayerInternalFailed)
        {
            aUpperLayerInternalFailed = true;
            aInternalAISState = true;
            aInternalAISEvent = false;
        }
        else
        {
            // Update Internal AIS state and count
            if(myPiiInternalAISCount[anIndex] != aNewInternalAISCount)
            {
                aInternalAISEvent = true;
            }
            if(aNewInternalAISCount%2 != 0)
            {
                aInternalAISState = true;        
            }
        } //  if (IsUpstreamLayerInternalFailed())


        // Update local defect counts
        myPiiInternalAISCount[anIndex]   = aNewInternalAISCount;

        myPiiAISCount[anIndex]    = aNewAISCount;
        myPiiLCKCount[anIndex]    = aNewLCKCount;
        myPiiBDICount[anIndex]    = aNewBDICount;
        myPiiOCICount[anIndex]    = aNewOCICount;
        myPiiSfBerCount[anIndex]  = aNewSfBerCount;
        myPiiSdBerCount[anIndex]  = aNewSdBerCount;
        myPiiPLMCount[anIndex]    = aNewPLMCount;
        myPiiMSIMCount[anIndex]   = aNewMSIMCount;
        myPiiLOFLOMCount[anIndex] = aNewLOFLOMCount;
        myPiiGenAISCount[anIndex] = aNewGenAISCount;
        myPiiLOOMFICount[anIndex] = aNewLOOMFICount;
        myPiiSSFforSGEOCount[anIndex]    = aNewSSFforSGEOCount;


        // Update actual defect
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_AIS_DEFECT,   aAISState,   aAISEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_BDI_DEFECT,   aBDIState,   aBDIEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_LCK_DEFECT,   aLCKState,   aLCKEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_OCI_DEFECT,   aOCIState,   aOCIEvent); 
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_SFBER_DEFECT, aSfBerState, aSfBerEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, aSdBerState, aSdBerEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_UPPER_LAYER_DEGRADE_DEFECT, aUpperLayerDegrade, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT, aUpperLayerFailed,  false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, aUpperLayerFailedForMaintSig,  false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_UPPER_LAYER_LOCK, IsUpstreamLayerLocked() || aPoolUpperLayerLocked, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_UPPER_LAYER_FAIL_NTA_DEFECT,IsUpstreamLayerFailedNTA()||aPoolUpperLayerNTA, false);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT,aPoolUpperLayerPNLTA, false);          
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_LOCK, aLayerLockedState||aIMUXLockState, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_IS_SRC, aIsConnectedAsSrc, false);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_IS_DST, aIsConnectedAsDst, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, aUpperLayerInternalFailed, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_NTA_DEFECT,aPoolUpperLayerInternalNTA, false);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT,aPoolUpperLayerInternalPNLTA, false); 
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_INTERNAL_LOCK, IsUpstreamLayerInternalLocked() || aPoolUpperLayerInternalLocked, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_TERM_LPBK, IsUpstreamLayerTermLpbk() || aPoolUpperLayerTermLpbked, false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_INTERNAL_AIS_DEFECT,   aInternalAISState,   aInternalAISEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_PLM_DEFECT,    aPLMState,    aPLMEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_MSIM_DEFECT,   aMSIMState,   aMSIMEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_LOFLOM_DEFECT, aLOFLOMState, aLOFLOMEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_GENAIS_DEFECT, aGenAISState, aGenAISEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_LOOMFI_DEFECT, aLOOMFIState, aLOOMFIEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_SSF_DEFECT, aSSFforSGEOState, aSSFforSGEOEvent);
		hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerInternalFailedForMaintSig(), false);

        // For TCM that are put OOS, we need to keep the Lock Bit Mask
        hasDefectsChanged |= aDefects.SetLockBitMask(aPoolLockBitMask);
        hasDefectsChanged |= aDefects.SetInternalLockBitMask(aPoolInternalLockBitMask);


        // Fail SSG based on upper layer (check just about everything) ,
        // First, set it to false (off) and only allow SSGState to be set (on)
        // for the following conditions for cross connects:
        // 1. SRC == true  and DEST == true  (2-way cross connect)
        // 2. SRC == true  and DEST == false (1-way add)
        // 3. SRC == false and DEST == false (no corss connect, but ODU-OTU is mapped)
        // This will mean the 1-way drop will not have SSG state set
        bool aSSGState = false;
        bool aSSDState = false;

        if ( ((aIsConnectedAsSrc == true)  && (aIsConnectedAsDst == true))   ||
             ((aIsConnectedAsSrc == true)  && (aIsConnectedAsDst == false))  ||
             ((aIsConnectedAsSrc == false) && (aIsConnectedAsDst == false))  )
        {
            // All internal upper layer defects are removed from determining  SGEO (see MR 170017 for details). 
            // In the future, there would be two separate entities if we want to consider internal defects at the ODU layer.
            aSSGState = IsUpstreamLayerFailedNTA() || aUpperLayerFailed      ||
                        aPoolUpperLayerNTA         || aPoolUpperLayerPNLTA   ||
                        IsUpstreamLayerLocked()    || aPoolUpperLayerLocked ;

            aSSDState = aUpperLayerDegrade;    //Equals to (IsUpstreamLayerDegrade() || aPoolUpperLayerDegrade)
        }

        // SSFforSGEO state is added in MR183191 for HGTMM. For HGTMM, if line side ODU2 detect MISM-ODU and LOFLOM or it is locked
        // by the user, then client side ODU2 SSFforSGEO state will be true, and client ODU2 state should be SGEO.
        aSSGState |= aSSFforSGEOState;

        //--------------------------------------------------------------
        // STATUS

        bool hasStatusChanged = false;
        hasStatusChanged |= aStatus.SetRxPayloadType(aDwPII.GetRxPayloadType());
        hasStatusChanged |= aStatus.SetActTribSize(aDwPII.GetODUTsSize());
        hasStatusChanged |= aStatus.SetServerSignalFail(aSSGState);
        hasStatusChanged |= aStatus.SetServerSignalDegrade(aSSDState);

        if( aCfgObject )
        {
            if( aCfgObject->GetTribAutoFallBack() && (aStatus.GetRxPayloadType() == CT_TEL_PSI_ODU_MULTI_STRUCT) )
            {
                hasStatusChanged |= aStatus.SetAutoFallbackStatus(true);
            }
            else
            {
                hasStatusChanged |= aStatus.SetAutoFallbackStatus(false);
            }
        }

        // Note: Since Agent does not need the Delay value (PM reads it by polling every second),
        // do not look at the return of the SetPathDelay method to update the changed flag.  
        // Therefore, the Status region modification counter will not be incremented due to a Delay change.
        (void) aStatus.SetPathDelay(aDwPII.GetPathDelay());

        CT_G709Trace aTrace;

        aTrace = aDwPII.GetRxTrace();

        // Check if trace is valid and if there is no defects that could invalidate it
        if (aTrace.IsValid() && !aAISState && !aLCKState && !aOCIState)
        {
            // if trace read from PII is different than the trace in ODU STATUS, update it
            if (!(aStatus.GetTraceMessage() == aTrace))
            {
                // at all time, if trace is the same for myNumConsecTraceComp times, set it in ODU STATUS
                if ((myFirstRcvdOduTrace[anIndex]) || (++myGoodTraceMessageCounter[anIndex] >= myNumConsecTraceComp))
                {
                    hasStatusChanged |= aStatus.SetTraceMessage(aTrace);
                    myGoodTraceMessageCounter[anIndex] = 0;
                    myBadTraceMessageCounter[anIndex] = 0;
                    myFirstRcvdOduTrace[anIndex] = false;
                }
            }
            else
            {
                myGoodTraceMessageCounter[anIndex] = 0;
                myBadTraceMessageCounter[anIndex] = 0;
            }
        }
        else // it is not valid
        {
            myGoodTraceMessageCounter[anIndex] = 0;

            // previousTrace must be different (myNumConsecTraceComp + 1) times before updating ODU STATUS
            if (++myBadTraceMessageCounter[anIndex] >= (myNumConsecTraceComp + 1))  
            {                    
                hasStatusChanged |= aStatus.SetTraceMessage(CT_G709StandardDefaultTrace::GetInstance());
            }
        }

        // AIS LCK and OCI disabled TIM
        if (aConfig.GetTIMMonitoringEnable() == false)
        {
            aTIMState = false;
            aTIMEvent = false;
        }
        else if (aAISState || aLCKState || aOCIState)
        {
            aTIMState = true;
            aTIMEvent = false;
        }
        else
        {
            // Update TIM defect only if trace is valid. NOTE: Default trace is invalid.
            if (aStatus.GetTraceMessage().IsValid())
            {
                if (myTimCheckByMon)
                {
                    aTIMState = aStatus.GetTraceMessage().CompareByTIMCriteraMode(aConfig.GetExpectedTrace(), aConfig.GetTimCriteria());
                }
                else
                {
                    uint32 aNewTIMCount = aDwPII.GetTIM();
                    if (aNewTIMCount%2 != 0)
                    {
                        aTIMState = true;     
                    }
                }
            }
        
            else
            {
                aTIMState = true;
            }
        }


        // the clear is now based on the session counter changing, which is controlled by Agent and written to TSPII via CFG.
        if (aDwPII.GetPRBSRXSessionCounter() != myLocalPRBSRXSessionCounter[anIndex])
        {
            hasStatusChanged |= aStatus.SetPrbsRxMostSignifCount(0);
            hasStatusChanged |= aStatus.SetPrbsRxLeastSignifCount(0);
            hasStatusChanged |= aStatus.SetPrbsRxTimeInterval(0);
            myLocalPRBSRXSessionCounter[anIndex] = aDwPII.GetPRBSRXSessionCounter();
            aStatus.SetPrbsRxFirstSync(false);   // Used locally - don't update hasStatusChanged
        }

        // Only update if PRBS Rx Enable is on (true)
        if (aDwPII.GetPRBSRXEnable())
        {
            uint32 aCountHigh, aCountLow, aTime;

            aDwPII.GetPrbsRxErrors(aCountHigh, aCountLow, aTime);
            hasStatusChanged |= aStatus.SetPrbsRxMostSignifCount(aCountHigh);
            hasStatusChanged |= aStatus.SetPrbsRxLeastSignifCount(aCountLow);
            hasStatusChanged |= aStatus.SetPrbsRxTimeInterval(aTime);

            uint32 aPrbsRxLosyncCount = aDwPII.GetPrbsRxLosync();

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


        // validate object
        hasDefectsChanged |= aDefects.Validate();
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_ODU_TIM_DEFECT, aTIMState,  aTIMEvent);  
        hasStatusChanged  |= aStatus.Validate();

        if (hasDefectsChanged) 
            GetMonIf().GetDefectsRegion()->IncModificationCounter();

        if (hasStatusChanged) 
            GetMonIf().GetStatusRegion()->IncModificationCounter();

        //IMPROV: add incModCounter
        aCounters.Validate();
        aStatus.Validate();
    }  // for (uint32 anIndex = 0; anIndex < myOdusOnCard; anIndex++)

    myFirstPassFlag = false;
}


MON_AppIf* MON_OduUpdateStatusAction::GetPoolApp(CT_ODU_ServerID theServerID,
                                                 T6100_CardIf*   theCardContext)
{
    MON_AppIf* aPoolApp = NULL;

    if (theServerID != CT_DEFAULT_ODU_SERVER_ID) 
    {
        if (theServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)
        {
            // For Otu facility, the instance is the facility number
            T6100_TelecomIf& aOtuContext = theCardContext->GetOtuIf();

            int aFac = CT_PORT_SIDE_0 + int(theServerID.GetPoolInstance());
            aPoolApp = &aOtuContext.GetMonPortSideApp((CT_IntfId)aFac);
        }
        else if (theServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu)
        {
            // For Odu facility, the base is Port_Side_30 and then look at Kvalue
            // to get the correct pool
            // Odu0 is 30, Odu1 is 31. Odu2 is 32, Odu3 is 33.
            T6100_TelecomIf& aOduContext = theCardContext->GetOduIf();

            uint8  aKvalue  = theServerID.GetOduKvalue();
            int    aFac     = int(CT_PORT_SIDE_30) + int(aKvalue);
            // ODU0 and ODUF share the same context.
            if(aKvalue == CT_ODU_LayerF)
            {
                aFac = CT_PORT_SIDE_30;
            }
            aPoolApp = &aOduContext.GetMonPortSideApp((CT_IntfId)aFac);
        }
        else if (theServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)
        {
            // For Tcm, Odus are base Port_Side_40 and the direction indicates the
            // correct pool (Direction A is 40 and Direction B is 41).
            // For other kvalues, the same pattern, but the base changes:
            // Odu1 has base of 50, Odu2 has base of 60, and Odu3 has base 70.
            T6100_TelecomIf& aTcmContext = theCardContext->GetTcmIf();

            int aFac    = int(CT_PORT_SIDE_40);

            aPoolApp = &aTcmContext.GetMonPortSideApp((CT_IntfId)aFac);
        }

    }  // if (aServerID != CT_DEFAULT_ODU_SERVER_ID) 

    return aPoolApp;
}

