// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_TcmIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbReason.h>
#include "../MON_TcmUpdateStatusAction.h"
#include "../MON_TcmDefects.h"
#include "../MON_TcmCounters.h"
#include "../MON_TcmStatus.h"
#include "../MON_TcmConfig.h"
#include "../MON_OtuDefects.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include "../../Configuration/CFG_AppIf.h"


MON_TcmUpdateStatusAction::MON_TcmUpdateStatusAction(MON_AppIf&        theMonIf,
                                                     CT_IntfId         theIntfId,
                                                     TSPII_TcmRegion&  theTcmPiiRegion,
                                                     CT_NumberOfOdus   theTcmsInRegion,                                                     
                                                     CFG_TcmCfgRegion* theTcmConfigRegion):
    MON_UpdateStatusAction(theMonIf,NULL),
    myIntfId(theIntfId),
    myTcmPiiRegion(theTcmPiiRegion),
    myTcmsInRegion(theTcmsInRegion),
    myNumConsecTraceComp(1),    
    myTcmConfigRegion(theTcmConfigRegion),
    myFirstPassFlag(true)
{
    // register upstream layer as input for defect propagation
    GetBbAction()->AddInputRegion(&myTcmPiiRegion);
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    if(myTcmConfigRegion) GetBbAction()->AddInputRegion(myTcmConfigRegion);    
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetCountersRegion(),false);

    for (uint32 anIndex = 0; anIndex < myTcmsInRegion; anIndex++)
    {
        myGoodTraceMessageCounter.push_back((uint32) 0);
        myBadTraceMessageCounter.push_back((uint32) 0);
        myFirstRcvdTcmTrace.push_back(true);

        myPiiLTCCount.push_back((uint32) 0);
        myPiiAISCount.push_back((uint32) 0);
        myPiiLCKCount.push_back((uint32) 0);
        myPiiOCICount.push_back((uint32) 0);
        myPiiBDICount.push_back((uint32) 0);
        myPiiSdBerCount.push_back((uint32) 0);
        myPiiIAECount.push_back((uint32) 0);
        myPiiBIAECount.push_back((uint32) 0);
        myOldTcmId.push_back(CT_DEFAULT_ODU_ID);
        myNewTcmId.push_back(CT_DEFAULT_ODU_ID);
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
    
    // Alter the number of rounds for different cards.
    myInitialLayer = 0;
    myLastLayer    = 0;
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
    if (aCardContext)
    {
        // on OSM20, which supports ODU0/F, ODU1 and ODU2, so there will be 3 rounds.
        if((aCardContext->GetCardFamily() == SSM40_FAM) ||
           (aCardContext->GetCardFamily() == OMM_FAM))
        {
            myInitialLayer = 0;
            myLastLayer    = 2;
        }
        // on HGTM, which supports ODU4 only, so there will be only 1 rounds.
        else if(aCardContext->GetCardFamily() == ENH_TRN_FAM) 
        {
            myInitialLayer = 4;
            myLastLayer    = 4;
        }
        // on PSM, which supports ODU2 only, so there will be only 1 rounds.
        else if(aCardContext->GetCardFamily() == ENH_PACKET_FAM) 
        {
            myInitialLayer = 2;
            myLastLayer    = 2;
        }   
        // on HGTMM, which supports ODU2T and ODU4.
        else if(aCardContext->GetCardFamily() == HGTMM_FAM) 
        {            
            myInitialLayer = 0; // Support ODUFT on HGTMMS 
            myLastLayer    = 4;
        }
        // on OSM, which supports ODU0T,1T,2T,FT.
        else if(aCardContext->GetCardFamily() == OSM_FAM) 
        {            
            myInitialLayer = 0;
            myLastLayer    = 2;
        }

    }

    myRoundCount = myInitialLayer;
}

MON_TcmUpdateStatusAction::~MON_TcmUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myTcmPiiRegion);
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    if(myTcmConfigRegion) GetBbAction()->RemoveInputRegion(myTcmConfigRegion);    
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetCountersRegion());
}

FC_Object* MON_TcmUpdateStatusAction::Suspend(unsigned theRunReason,
                                              FC_Object* theInvokerObj,
                                              FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    GetMonIf().GetCountersRegion()->Reset();
    return NULL;
}

FC_Object* MON_TcmUpdateStatusAction::Process(unsigned theRunReason,
                                              FC_Object* theInvokerObj,
                                              FC_Object* theParam)
{
    UpdateObject(theRunReason);
    return NULL;
}


void MON_TcmUpdateStatusAction::UpdateObject(unsigned theRunReason)
{
    CFG_Tcm* aTcmCfgObject = NULL;
    vector<CT_NumberOfOdus> aPositionList;    

    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
    if (aCardContext == NULL) 
    {
        return;
    }

    MON_Region* aTcmDefectsRegion = GetMonIf().GetDefectsRegion();
    MON_Region* aTcmStatusRegion = GetMonIf().GetStatusRegion();
    MON_Region* aTcmCountersRegion = GetMonIf().GetCountersRegion();
    MON_Region* aTcmConfigRegion = GetMonIf().GetConfigRegion();

    //Get odu intf ID.
    T6100_TelecomIf& aOduContext = aCardContext->GetOduIf();

    myTcmsInRegion = (myTcmsInRegion <= GetMonIf().GetConfigRegion()->Size()) ? myTcmsInRegion : GetMonIf().GetConfigRegion()->Size();
    // For a complete cycle, we need to go through all layer offsets.
    // This controls what layers are done per pass
    // Note that the first pass must do all the layer offsets to avoid problems with warm reset
    if (myRoundCount > myLastLayer)
    {
        myRoundCount = myInitialLayer;
        for (uint32 anIndex = 0; anIndex < myTcmsInRegion; anIndex++)
        {
            myNewTcmId[anIndex] = CT_DEFAULT_ODU_ID;
        }
    }

    uint16 aStartOduLayeOffset = myRoundCount;
    uint16 anEndOduLayerOffset  = myRoundCount + 1;

    if ((myFirstPassFlag) || (myRoundCount >= myLastLayer))
    {
        //anEndOduLayerOffset  =  CT_ODU_LayerEnd;
        anEndOduLayerOffset  =  myLastLayer;
        myRoundCount = myLastLayer;
    }   

    
    for (uint16 anOduLayerOffset = aStartOduLayeOffset; anOduLayerOffset <= anEndOduLayerOffset; anOduLayerOffset++)         
    {
        CT_IntfId anIntfId = (CT_IntfId)(CT_PORT_SIDE_30 + anOduLayerOffset);

        // HGTMMS don't support odu1 tcm.
        if(aCardContext->GetCardFamily() == HGTMM_FAM && anIntfId == CT_PORT_SIDE_31)
        {
            continue;
        }

        //Get the odu region.
        CFG_AppIf*  aPoolApp      = &aOduContext.GetCfgPortSideApp(anIntfId);

        //not all cards will have all layer offsets, so we skip the layer offset in this case.
        if( aPoolApp == NULL) 
            break;

        CFG_Region* aOduCfgRegion = aPoolApp->GetCfgRegion();
        CFG_Odu*    aOduCfgObject = NULL;

        //Iterate the odu objects in the odu region.
        for (uint16 anOduIndex  = 0; anOduIndex < aOduCfgRegion->Size(); anOduIndex++)
        {
            aOduCfgObject = (CFG_Odu*)&(*aOduCfgRegion)[bbindex_t(anOduIndex)];
    
            vector<CT_NumberOfOdus> aTcmProcList;
    
            for ( uint16 aDirectionOffset = 0; aDirectionOffset<2; aDirectionOffset++) 
            {
                CT_ODU_Direction anDirection = (CT_ODU_Direction)(CT_ODU_Direction_A + aDirectionOffset);

                if( anDirection == CT_ODU_Direction_A ) 
                    aTcmProcList = aOduCfgObject->GetOduTcmAProcList();
                else
                    aTcmProcList = aOduCfgObject->GetOduTcmBProcList();			

                //smart loop the tcm objects base on the proc list
                for (uint32 anProcListIndex  = 0; anProcListIndex < aTcmProcList.size(); anProcListIndex++)
                {
                    bbindex_t aTcmIndex = aTcmProcList[anProcListIndex];
           
                    if(aTcmIndex >= myTcmsInRegion)
                    {
                        FC_THROW_ERROR(FC_SWError, "MON_TcmUpdateStatusAction: aTcmIndex invalid");
                        continue;
                    }           
                     
                    MON_TcmDefects&  aDefects   = dynamic_cast<MON_TcmDefects&>((*aTcmDefectsRegion)[aTcmIndex]);
                    MON_TcmStatus&   aStatus    = dynamic_cast<MON_TcmStatus&>((*aTcmStatusRegion)[aTcmIndex]);
                    MON_TcmCounters& aCounters  = dynamic_cast<MON_TcmCounters&>((*aTcmCountersRegion)[aTcmIndex]);
                    MON_TcmConfig&   aConfig    = dynamic_cast<MON_TcmConfig&>((*aTcmConfigRegion)[aTcmIndex]);
           
                    //Find the tcm CFG object.
                    aTcmCfgObject = &(*myTcmConfigRegion)[aTcmIndex];
           
                    //Make sure the tcm CFG object is valid
                    if (aTcmCfgObject == NULL) 
                    {
                        FC_THROW_ERROR(FC_SWError, "MON_TcmUpdateStatusAction: aTcmCfgObject is NULL");
                        continue;
                    }
           
                    //if tcm id is is valid then doesn't call tspii.
                    CT_ODU_Identifier aNewTcmId = aTcmCfgObject->GetTcmIdentifier();

                    myNewTcmId[aTcmIndex] = aNewTcmId;
                    // Clear any instance where the TcmId changed from the last pass
                    if (myOldTcmId[aTcmIndex] != myNewTcmId[aTcmIndex])
                    {
                        ResetInstance(aTcmIndex);
                    }
                    
                    // Check for upper layer from a pool.
                    bool  aPoolUpperLayerFailed = false;
                    bool  aPoolUpperLayerNTA    = false;
                    bool  aPoolUpperLayerPNLTA  = false;
                    bool  aPoolUpperLayerLocked = false;
                    bool  aPoolUpperLayerInternalFailed = false;
                    bool  aPoolUpperLayerInternalPNLTA  = false;
                    bool  aPoolUpperLayerTermLpbked     = false;
                    bool  aPoolUpperLayerSignalDegrade  = false;
                    uint8 aPoolLockBitMask  = 0;
                    uint8 aPoolInternalLockBitMask = 0;
           
                    bool  myUpperLayerPoolFlag = true;
           
                    // Must have these to find the proper 
                    if ((myUpperLayerPoolFlag) && (aTcmCfgObject) && (aCardContext))
                    {
                        CT_ODU_ServerID aServerID = aTcmCfgObject->GetServerID();
                        MON_AppIf*      aPoolApp  = GetPoolApp(aServerID, aCardContext);
               
                        // Look at ServerID first
                        if (aPoolApp) 
                        {
                            if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)
                            {
                                // application found above, for OTU, always 1 instance.
                                MON_Defects& aULDefects  = static_cast<MON_Defects&>((*(aPoolApp)->GetDefectsRegion())[0]);
               
                                aPoolUpperLayerFailed = aULDefects.IsLayerInDefects();
                                aPoolUpperLayerLocked = aULDefects.IsLayerLocked();
                                aPoolUpperLayerInternalFailed = aULDefects.IsLayerInternalInDefects();
                                aPoolUpperLayerInternalPNLTA  = aULDefects.IsInternalInPropagateNextLayerDefectsTA();
                                aPoolUpperLayerTermLpbked     = aULDefects.IsLayerInTermLpbk();
                                aPoolUpperLayerSignalDegrade  = aULDefects.IsLayerInDegrade();
           
                                // if upper layer locked, set Otu bit in bit mask
                                if (aULDefects.IsLayerLocked())
                                {
                                    aPoolLockBitMask  = 0x80;
                                }
                                if (aULDefects.IsLayerInternalLocked())
                                {
                                    aPoolInternalLockBitMask  = 0x80;
                                }
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
                                {
                                    aPoolUpperLayerSignalDegrade        = aULRDefects.IsLayerInDegrade();
           
                                    if (aTcmCfgObject->GetTcmIdentifier().GetOduDirection() == CT_ODU_Direction_A)
                                    {
                                        aPoolUpperLayerFailed = (aULRDefects.IsLayerInDefects() ||
                                                                 aULRDefects.IsLayerLocked() ||
                                                                 //aULRDefects.IsAnyTcmLevelLocked(aULRDefects.GetLockBitMask()) ||
                                                                 aULRDefects.IsInPropagateNextLayerDefectsTA());
                                        aPoolUpperLayerNTA    = aULRDefects.IsLayerInDefectsNTA();
                                    }
                                    else
                                    {
                                        aPoolUpperLayerFailed = (aULRDefects.IsLayerInternalInDefects() ||
                                                                 aULRDefects.IsLayerInternalLocked() ||
                                                                 //aULRDefects.IsAnyTcmLevelLocked(aULRDefects.GetInternalLockBitMask()) ||
                                                                 aULRDefects.IsInternalInPropagateNextLayerDefectsTA());;
                                        aPoolUpperLayerNTA    = aULRDefects.IsLayerInternalInDefectsNTA();
                                    }  // if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu) 
           
                                    // All Internal Defects pass through as failing the layer 
                                    aPoolUpperLayerInternalFailed = (aULRDefects.IsLayerInternalInDefects() || 
                                                                     aULRDefects.IsLayerInternalLocked()    ||
                                                                     aULRDefects.IsInternalInPropagateNextLayerDefectsTA() );
           
                                    aPoolUpperLayerTermLpbked     = aULRDefects.IsLayerInTermLpbk();
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
                                    aPoolLockBitMask         = aULRDefects.GetLockBitMask();
                                    aPoolInternalLockBitMask = aULRDefects.GetInternalLockBitMask();
               
               
                                    // Check if the direct upper layer should be ignored
                                    // For example, for TCM, NIM and SRC-ONLY Tcm Mode should not 
                                    // look at defects from that layer 
                                    if (aULRDefects.IsIgnoreDirectUpperLayerDefects())
                                    {
                                        aPoolUpperLayerFailed = aUpperTADefectState;
                                        aPoolUpperLayerNTA    = aUpperNTADefectState;
                                        aPoolUpperLayerPNLTA  = aUpperPNLTADefectState;
                                    }
                                    else
                                    {
                                        // If here, it is MUX case or from a TCM, 
                                        aPoolUpperLayerFailed = aULRDefects.IsLayerInDefects();
                                        aPoolUpperLayerNTA    = (aULRDefects.IsLayerInDefectsNTA() ||
                                                                 aUpperNTADefectState); 
                                        aPoolUpperLayerPNLTA  = (aULRDefects.IsInPropagateNextLayerDefectsTA() ||
                                                                 aUpperPNLTADefectState);
                                    }  // (else part of) if (aULRDefects.IsIgnoreDirectUpperLayerDefects()) 
           
                                    aPoolUpperLayerSignalDegrade        = aULRDefects.IsLayerInDegrade();
           
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
                                    }
           
                                    // Internal Defects pass through because there are no internal defects for TCM
                                    // Note: Internal Lock was taken care of above
                                    aPoolUpperLayerInternalFailed = aULRDefects.IsLayerInternalInDefects();
                                    aPoolUpperLayerInternalPNLTA  = aULRDefects.IsInternalInPropagateNextLayerDefectsTA();
           
                                    aPoolUpperLayerTermLpbked     = aULRDefects.IsLayerInTermLpbk();

                                }  //  else if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)

                            }  //  (else part of) if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)

                        }  // if (aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)

                    }  //  if (aPoolApp)
                        
                    TSPII_TcmIf& aTcmPII   = myTcmPiiRegion[aTcmIndex];
           
                    bool hasDefectsChanged = false;
                    bool aLayerLockedState = false;
           
                    bool aNimState=false, aSrcState=false, aSnkState=false;
           
                    //--------------------------------------------------------------
                    // DEFECTS, Part A
                    // First, set flags and defect states depending on the TCM Mode
                    // 
                    // NIM modes are treated as defect. MON udpate action needs to be aware of it to set server layer fail defect
                    if ( (CT_TCM_MODE_SRC_SNK_NIM == aTcmCfgObject->GetTcmMode()) || (CT_TCM_MODE_SNK_NIM == aTcmCfgObject->GetTcmMode()) )
                    {
                        aDefects.SetDefectStatus(CT_TEL_TCM_NIM_MODE_DEFECT, true, false);
                        aNimState = true;
                    }
           
                    // SRC is treated as defect. MON udpate action needs to be aware of it to set server layer fail defect
                    if ( CT_TCM_MODE_SOURCE == aTcmCfgObject->GetTcmMode() )
                    {
                        aDefects.SetDefectStatus(CT_TEL_TCM_SRC_MODE_DEFECT, true, false);
                        aSrcState = true;
                    }
           
                    // SNK modes are treated as defect. MON udpate action needs to be aware of it 
                    if ( ( CT_TCM_MODE_SINK == aTcmCfgObject->GetTcmMode()) || (CT_TCM_MODE_SNK_NIM == aTcmCfgObject->GetTcmMode()) )
                    {
                        // Record the Sink State
                        aDefects.SetDefectStatus(CT_TEL_TCM_SNK_MODE_DEFECT, true, false);
                        aSnkState = true;
                    }
           
           
                    //--------------------------------------------------------------
                    // CONFIG
                    //Configure defect region to fail on TIM defect
                    hasDefectsChanged |= aDefects.SetLayerFailOnTimEnable(aConfig.GetLayerFailOnTIM());
                    hasDefectsChanged |= aDefects.SetLayerFailOnLtcEnable(aConfig.GetLayerFailOnLTC() || aTcmCfgObject->GetTcmLTCActEnabled());

           
                    uint8 aPos = 0xff; 
           
                    if(aConfig.GetLayerLocked())
                    { 
                        // Note: the LockBitMask is used to force LCK-ODU (regular) and the
                        // Lock State control sending internal maintenance signals (LCK-ODU
                        // if the lock propagates or AIS-ODU if the lock fail a client layer).
           
                        // In SNK and SNK_NIM mode: placing the ODUkT OOS does not set/change the lock bit mask 
                        if (!aSnkState) 
                        {
                            uint8 aSetMask = 1;
                            aPos = (uint8)(aTcmCfgObject->GetTcmIdentifier().GetTcmLevelEnum() - CT_TCM_Level_UNKNOWN);
           
                            // Note: SetLockBitMask is a defect and is done below.
                            aSetMask = aSetMask << aPos;
                            aPoolLockBitMask |= aSetMask;
                        }
                        
                        // Set the Lock state except in the following cases:
                        // In SRC_SNK_NIM and SNK_NIM: placing the ODUkT OOS does not set the Lock State  
                        // In SRC only mode, the lock bit mask is set, but the Lock state is not set 
                        if ((!aNimState) && (!aSrcState))
                        {
                            aLayerLockedState = true;
                        }
                    }
           
                    aLayerLockedState |= aPoolUpperLayerLocked;
           
                    //--------------------------------------------------------------
                    // COUNTERS
                    // IMPROV: interface for TCM counters
                    // For 64 bits, always read the high bits last
                    aCounters.SetErrorCount(CT_TEL_TCM_BEI,0);
                    aCounters.SetErrorCount(CT_TEL_TCM_HIGH_BEI,0);
                    aCounters.SetErrorCount(CT_TEL_TCM_BIP8,aTcmPII.GetBip8Count());            
                    aCounters.SetErrorCount(CT_TEL_TCM_HIGH_BIP8,aTcmPII.GetHighBip8Count());            
           
           
                    //--------------------------------------------------------------
                    // DEFECTS
                    // 
           
                    // Read current defects
                    bool aLTCState=false, aAISState=false, aBDIState=false, aLCKState=false, aOCIState=false, aTIMState=false, aSdBerState=false;
                    bool aLTCEvent=false, aAISEvent=false, aBDIEvent=false, aLCKEvent=false, aOCIEvent=false, aTIMEvent=false, aSdBerEvent=false;
           
                    bool aIAEState=false, aBIAEState=false;
                    bool aIAEEvent=false, aBIAEEvent=false;        
           
                    uint32 aNewLTCCount   = 0;
                    uint32 aNewAISCount   = 0;
                    uint32 aNewLCKCount   = 0;
                    uint32 aNewBDICount   = 0;
                    uint32 aNewOCICount   = 0;
                    uint32 aNewSdBerCount = 0;
                    uint32 aNewIAECount   = 0;
                    uint32 aNewBIAECount  = 0;
           
                    if ( CT_TCM_MODE_SOURCE != aTcmCfgObject->GetTcmMode() )
                    {
                        aNewLTCCount   = aTcmPII.GetLTC(); 
                        aNewAISCount   = aTcmPII.GetAIS(); 
                        aNewLCKCount   = aTcmPII.GetLCK();
                        aNewBDICount   = aTcmPII.GetBDI();
                        aNewOCICount   = aTcmPII.GetOCI();
                        aNewSdBerCount = aTcmPII.GetBerSd();    
                        aNewIAECount   = aTcmPII.GetIAE();    
                        aNewBIAECount  = aTcmPII.GetBIAE();            
                    }
           
                    // force AIS if upstream layer is failed except for source mode
                    if (aPoolUpperLayerFailed && (CT_TCM_MODE_SOURCE != aTcmCfgObject->GetTcmMode()))
                    {
                        aAISState = true;
                        aAISEvent = false;
                    }
                    else
                    {
                        // Update AIS state and count
                        if( (myPiiAISCount[aTcmIndex] != aNewAISCount) && 
                            (CT_TCM_MODE_SOURCE != aTcmCfgObject->GetTcmMode()) )
                        {
                            aAISEvent = true;
                        }
                        if(aNewAISCount%2 != 0)
                        {
                            aAISState = true;        
                        }
                    }  // if (aPoolUpperLayerFailed)
           
                    // force AIS if server layer is failed
                    
                    // Update LTC state and count
                    if ( CT_TCM_MODE_SOURCE != aTcmCfgObject->GetTcmMode() ) 
                    {
                        if (myPiiLTCCount[aTcmIndex] != aNewLTCCount) 
                        {
                            aLTCEvent = true;
                        }
                        if(aNewLTCCount%2 != 0)
                        {
                            aLTCState = true;        
                        }
                    }
                    else
                    {
                        aLTCEvent = false;
                        aLTCState = false;        
                    }

                    if ( aAISState || (CT_TCM_MODE_SOURCE == aTcmCfgObject->GetTcmMode()))
                    {    
                        aLCKEvent = false;
                        aLCKState = false;        
                        aOCIEvent = false;
                        aOCIState = false;        
                        aBDIState = false;
                        aBDIEvent = false;
                        aIAEState = false;
                        aIAEEvent = false;
                        aBIAEState = false;
                        aBIAEEvent = false;		    
                    }
                    else
                    {
                        // Update LCK state and count
                        if(myPiiLCKCount[aTcmIndex] != aNewLCKCount)
                        {
                            aLCKEvent = true;
                        }
                        if(aNewLCKCount%2 != 0)
                        {
                            aLCKState = true;        
                        }
           
                        // Update OCI state and count
                        if(myPiiOCICount[aTcmIndex] != aNewOCICount)
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
                        }
                        else
                        {
                            // Update BDI state and count
                            if(myPiiBDICount[aTcmIndex] != aNewBDICount)
                            {
                                aBDIEvent = true;
                            }
                            if(aNewBDICount%2 != 0)
                            {
                                aBDIState = true;        
                            }
                        }
           
                        // Update SdBer state and count
                        if(myPiiSdBerCount[aTcmIndex] != aNewSdBerCount)
                        {
                            aSdBerEvent = true;
                        }
                        if(aNewSdBerCount%2 != 0)
                        {
                            aSdBerState = true;        
                        }
           
                        // Update IAE state and count
                        if(myPiiIAECount[aTcmIndex] != aNewIAECount)
                        {
                            aIAEEvent = true;
                        }
                        if(aNewIAECount%2 != 0)
                        {
                            aIAEState = true;        
                        }
           
                        // Update BIAE state and count
                        if(myPiiBIAECount[aTcmIndex] != aNewBIAECount)
                        {
                            aBIAEEvent = true;
                        }
                        if(aNewBIAECount%2 != 0)
                        {
                            aBIAEState = true;        
                        }
                    }  // if ( aAISState )
           
                    if (CT_TCM_MODE_SOURCE != aTcmCfgObject->GetTcmMode()) 
                    {
                        myPiiLTCCount[aTcmIndex]   = aNewLTCCount; 
                        myPiiAISCount[aTcmIndex]   = aNewAISCount;
                        myPiiLCKCount[aTcmIndex]   = aNewLCKCount;
                        myPiiBDICount[aTcmIndex]   = aNewBDICount;
                        myPiiOCICount[aTcmIndex]   = aNewOCICount;
                        myPiiSdBerCount[aTcmIndex] = aNewSdBerCount;
                        myPiiIAECount[aTcmIndex]   = aNewIAECount;
                        myPiiBIAECount[aTcmIndex]  = aNewBIAECount;
                    }
           
                    // Update actual defect
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_LTC_DEFECT,   aLTCState,   aLTCEvent);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_AIS_DEFECT,   aAISState,   aAISEvent);        
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_LCK_DEFECT,   aLCKState,   aLCKEvent);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_OCI_DEFECT,   aOCIState,   aOCIEvent);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_BDI_DEFECT,   aBDIState,   aBDIEvent); 
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_SDBER_DEFECT, aSdBerState, aSdBerEvent);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_UPPER_LAYER_DEGRADE_DEFECT, aPoolUpperLayerSignalDegrade, false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_IAE_DEFECT,   aIAEState,   aIAEEvent);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_BIAE_DEFECT,  aBIAEState,  aBIAEEvent);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_LOCK, aLayerLockedState, false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_UPPER_LAYER_FAIL_TA_DEFECT,    aPoolUpperLayerFailed, false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_UPPER_LAYER_FAIL_NTA_DEFECT,   aPoolUpperLayerNTA,    false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, aPoolUpperLayerPNLTA,  false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, aPoolUpperLayerInternalFailed,  false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_INTERNAL_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, aPoolUpperLayerInternalPNLTA,  false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_NIM_MODE_DEFECT,  aNimState,     false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_SRC_MODE_DEFECT,  aSrcState,     false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_SNK_MODE_DEFECT,  aSnkState,     false);
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_TERM_LPBK, aPoolUpperLayerTermLpbked, false);
           
                    // Propagate the Regular and Internal Lock Bit Masks
                    hasDefectsChanged |= aDefects.SetLockBitMask(aPoolLockBitMask);
                    hasDefectsChanged |= aDefects.SetInternalLockBitMask(aPoolInternalLockBitMask);
           
                    // Fail SSG based on upper layer 
                    bool aSSGState = aPoolUpperLayerFailed || aPoolUpperLayerLocked ||
                                     aPoolUpperLayerNTA    || aPoolUpperLayerPNLTA; 
           
                    bool aSSDState = aPoolUpperLayerSignalDegrade;
           
                    //--------------------------------------------------------------
                    // STATUS
           
                    bool hasStatusChanged = false;
           
                    // Set Server Signal Fail and then write it down to TSPII, which needs it 
                    // to allow the SDBER state machine to work correctly on the OSM40
                    hasStatusChanged |= aStatus.SetServerSignalFail(aSSGState);
                    //Commented out, fw doesn't need this seting now.
                    //aTcmPII.SetTcmSsf(aSSGState);
           
                    hasStatusChanged |= aStatus.SetServerSignalDegrade(aSSDState);
           
                    // Note: Since Agent does not need the Delay value (PM reads it by polling every second),
                    // do not look at the return of the SetTcmDelay method to update the changed flag.  
                    // Therefore, the Status region modification counter will not be incremented due to a Delay change.
                    (void) aStatus.SetTcmDelay(aTcmPII.GetTcmDelay());
           
                    CT_G709Trace aTrace;
           
                    aTrace = aTcmPII.GetRxTrace();
           
                    // Check if trace is valid and if there is no defects that could invalidate it.In src mode, trace need not to be monitored.
                    if (aTrace.IsValid() && !aAISState && !aLCKState && !aOCIState && (CT_TCM_MODE_SOURCE != aTcmCfgObject->GetTcmMode()))
                    {
                        // if trace read from PII is different than the trace in TCM STATUS, update it
                        if (!(aStatus.GetTraceMessage() == aTrace))
                        {
                            // at all time, if trace is the same for myNumConsecTraceComp times, set it in TCM STATUS
                            if ((myFirstRcvdTcmTrace[aTcmIndex]) || (++myGoodTraceMessageCounter[aTcmIndex] >= myNumConsecTraceComp))
                            {
                                hasStatusChanged |= aStatus.SetTraceMessage(aTrace);
                                myGoodTraceMessageCounter[aTcmIndex] = 0;
                                myBadTraceMessageCounter[aTcmIndex] = 0;
                                myFirstRcvdTcmTrace[aTcmIndex] = false;
                            }
                        }
                        else
                        {
                            myGoodTraceMessageCounter[aTcmIndex] = 0;
                            myBadTraceMessageCounter[aTcmIndex] = 0;
                        }
                    }
                    else // it is not valid
                    {
                        myGoodTraceMessageCounter[aTcmIndex] = 0;
           
                        // previousTrace must be different (myNumConsecTraceComp + 1) times before updating TCM STATUS
                        if (++myBadTraceMessageCounter[aTcmIndex] >= (myNumConsecTraceComp + 1)) 
                        {                    
                            hasStatusChanged |= aStatus.SetTraceMessage(CT_G709DefaultTrace::GetInstance());
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
                            aTIMState = aStatus.GetTraceMessage().CompareByTIMCriteraMode(aConfig.GetExpectedTrace(), aConfig.GetTimCriteria());
                        }
           
                        else
                        {
                            aTIMState = true;
                        }
                    }
           
                    // validate object                    
                    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_TCM_TIM_DEFECT, aTIMState,  aTIMEvent);                      
           
                    if (hasDefectsChanged) 
                        GetMonIf().GetDefectsRegion()->IncModificationCounter();
           
                    if (hasStatusChanged) 
                        GetMonIf().GetStatusRegion()->IncModificationCounter();
           
                    //IMPROV: add incModCounter
                    aDefects.Validate();
                    aCounters.Validate();
                    aStatus.Validate();
           
                } // end of process list instances

            } // end of direction instances
            
        }// end of CFG Odu instances

    }// end of ODU K instances

    // Check and see if we are done with the cycle of all TCMs that are used using myRoundCount.
    // Needs to be incremented before checking.
    myRoundCount++;
    if (myRoundCount > myLastLayer)
    {
        for (uint16 anIndex = 0; anIndex < myTcmsInRegion; anIndex++)
        {
            // Clear any instances that were in use, but are not in this pass
            if ((myOldTcmId[anIndex] != CT_DEFAULT_ODU_ID) && (myNewTcmId[anIndex] == CT_DEFAULT_ODU_ID))
            {
                ResetInstance(anIndex);
            }
            myOldTcmId[anIndex] = myNewTcmId[anIndex];
        }
    }  // if (myRoundCount > myLastLayer)

    myFirstPassFlag = false;

}


void MON_TcmUpdateStatusAction::ResetInstance(uint16 theIndex)
{
    MON_TcmDefects&  aDefects   = static_cast<MON_TcmDefects&>((*GetMonIf().GetDefectsRegion())[theIndex ]);
    MON_TcmStatus&   aStatus    = static_cast<MON_TcmStatus&>((*GetMonIf().GetStatusRegion())[theIndex ]);
    MON_TcmCounters& aCounters  = static_cast<MON_TcmCounters&>((*GetMonIf().GetCountersRegion())[theIndex ]);
    MON_TcmConfig&   aConfig    = static_cast<MON_TcmConfig&>((*GetMonIf().GetConfigRegion())[theIndex ]);    
                
    aConfig.Reset();
    aCounters.Reset();
    aDefects.Reset();
    GetMonIf().GetDefectsRegion()->IncModificationCounter();
    aStatus.Reset();
    GetMonIf().GetStatusRegion()->IncModificationCounter();

    return;				
}


MON_AppIf* MON_TcmUpdateStatusAction::GetPoolApp(CT_ODU_ServerID theServerID,
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
            aPoolApp = &aOduContext.GetMonPortSideApp((CT_IntfId)aFac);
        }
        else if (theServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)
        {
            T6100_TelecomIf& aTcmContext = theCardContext->GetTcmIf();

            int aFac    = int(CT_PORT_SIDE_40);

            aPoolApp = &aTcmContext.GetMonPortSideApp((CT_IntfId)aFac);
        }

    }  // if (aServerID != CT_DEFAULT_ODU_SERVER_ID) 

    return aPoolApp;
}


