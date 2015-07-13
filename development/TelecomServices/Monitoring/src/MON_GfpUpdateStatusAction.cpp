// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_GfpIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include "../MON_AppIf.h"
#include "../MON_GfpUpdateStatusAction.h"
#include "../MON_GfpDefects.h"
#include "../MON_GfpCounters.h"
#include "../MON_Region.h"
#include "../MON_OptUpdateStatusAction.h"
#include "../MON_OptDefects.h"
#include "../MON_GfpConfig.h"
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <TsPii/TSPII_RsIf.h>
#include <TsPii/TSPII_MacIf.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <Configuration/CFG_Definitions.h>

MON_GfpUpdateStatusAction::MON_GfpUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_GfpRegion& theGfpPiiRegion,
                                                     MON_AppIf* theUpstreamLayerIf,
                                                     uint8 theNumGfps):
	MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myGfpPiiRegion(theGfpPiiRegion),
    myFirstPassFlag(true),
    myNumGfps(theNumGfps)
{
    //Reset local counters
    uint8 myNumGfps = CT_TEL_NBR_OF_VCGS;

#ifndef PSOSP
    myPiiLOFDCount.resize(theNumGfps);
    myPiiCsfLosCount.resize(theNumGfps);
    myPiiCsfLosyncCount.resize(theNumGfps);
    myPiiVirtualLOFDCount.resize(theNumGfps);
    myPiiCsfRFLinkFailCount.resize(theNumGfps);
    myPiiCsfRFOfflineCount.resize(theNumGfps);
    myPiiCsfRFAutoNegFailCount.resize(theNumGfps);
    myPiiCsfLinkFailRxCount.resize(theNumGfps);
    myPiiRFLinkFailCount.resize(theNumGfps);
    myPiiRFOfflineCount.resize(theNumGfps);
    myPiiRFAutoNegFailCount.resize(theNumGfps);
    myPiiLinkFailRxCount.resize(theNumGfps);
    myPiiFefiCount.resize(theNumGfps);
    myPiiCsfFefiCount.resize(theNumGfps);
    myPiiCsfFdiCount.resize(theNumGfps);
    myPiiCsfRdiCount.resize(theNumGfps);
	myPiiLocalAutoNegFailCount.resize(theNumGfps);
    myPiiPLMCount.resize(theNumGfps);
    myPiiLosAlignCount.resize(theNumGfps);
    myPiiSeqMisMatchCount.resize(theNumGfps);
    myPiiCoreHecCount.resize(theNumGfps);
    myPiiPliCount.resize(theNumGfps);

    myNumGfps = theNumGfps;
#endif
    for(uint32 i = 0;i<myNumGfps;i++)
    {
        myPiiLOFDCount[i]             = 0;
        myPiiCsfLosCount[i]           = 0;
        myPiiCsfLosyncCount[i]        = 0;
        myPiiVirtualLOFDCount[i]             = 0;
        myPiiCsfRFLinkFailCount[i]    = 0;
        myPiiCsfRFOfflineCount[i]     = 0;
        myPiiCsfRFAutoNegFailCount[i] = 0;
        myPiiCsfLinkFailRxCount[i]    = 0;
        myPiiRFLinkFailCount[i]       = 0;
        myPiiRFOfflineCount[i]        = 0;
        myPiiRFAutoNegFailCount[i]    = 0;
        myPiiLinkFailRxCount[i]       = 0;
        myPiiFefiCount[i]             = 0;
        myPiiCsfFefiCount[i]          = 0;
        myPiiCsfFdiCount[i]          = 0;
        myPiiCsfRdiCount[i]          = 0;
		myPiiLocalAutoNegFailCount[i] = 0;
        myPiiPLMCount[i]             = 0;
        myPiiLosAlignCount[i]             = 0;
        myPiiSeqMisMatchCount[i]             = 0;
        myPiiCoreHecCount[i]             = 0;
        myPiiPliCount[i]             = 0;
    }

    myNextGfp = 0;
    myNbrGfp2Check = myNumGfps;
    if (myNumGfps > 1) 
    {
        // For now, just split the number of gfps in half
        myNbrGfp2Check /= 2;
    }
    GetBbAction()->AddInputRegion(&myGfpPiiRegion);
    MON_Region * aMonConfigRegion = GetMonIf().GetConfigRegion();
    if (aMonConfigRegion != NULL)
    {
        GetBbAction()->AddInputRegion(aMonConfigRegion);     
    }
        
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
}

MON_GfpUpdateStatusAction::~MON_GfpUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myGfpPiiRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
}

FC_Object* MON_GfpUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    return NULL;
}


FC_Object* MON_GfpUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    // Loop thru all of the GFPs.
    uint16 aStartIndex = 0;
    uint16 anEndIndex = myNumGfps;

    if ((myNumGfps > 1) && (!myFirstPassFlag))
    {
        // When there is more than one instance, then loop through using myNbrGfp2Check
        // Make sure start and end are not past max
        // Set start to 0 if equal or past max
        // and set end to max if past max
        aStartIndex = myNextGfp;
        if (aStartIndex >= myNumGfps)
        {
            aStartIndex = 0;
        }
        // End is normally the number of vcgs to check past the start
        anEndIndex = aStartIndex + myNbrGfp2Check;
        if (anEndIndex > myNumGfps)
        {
            anEndIndex = myNumGfps;
        }
        myNextGfp = anEndIndex;
    }

    for (uint16 anIndex = 0; anIndex < myNumGfps; anIndex++)      
    {

        TSPII_GfpIf& aGfpPII = myGfpPiiRegion[anIndex];

        // This loop now will loop through all Gfps, but will select which ones
        // to process. Always do the range between aStartIndex and anEndIndex (initially half), 
        // but also process all EPLs each time.  Therefore this code will skip indices
        // that are outside the range and are not EPL (which will have the default port index).
        if ((myNumGfps > 1) && (!myFirstPassFlag))
        {
            if ((anIndex < aStartIndex) || (anIndex > (anEndIndex-1))) 
            {
                if (aGfpPII.GetPortIndex() == CFG_GFP_DEFAULT_PORT_INDEX) 
                {
                    // If the Port Index is default, then it is not EPL, skip it.
                    continue;
                }
            }
        }  //  if ((myNumGfps > 1) && (!myFirstPassFlag))


        MON_GfpCounters& aCounters = static_cast<MON_GfpCounters&>((*GetMonIf().GetCountersRegion())[anIndex]);
        MON_GfpDefects& aDefects   = static_cast<MON_GfpDefects&>((*GetMonIf().GetDefectsRegion())[anIndex]);
        
        bool hasDefectsChanged = false;

        // set Fail Layer Bit Mask for GFP
        MON_Region * aMonConfigRegion = GetMonIf().GetConfigRegion();
        if (aMonConfigRegion != NULL)
        {
            MON_GfpConfig& aConfig = static_cast<MON_GfpConfig&>((*aMonConfigRegion)[anIndex]);
            aDefects.SetFailLayerBitMask(aConfig.GetFailLayerBitMask());        
        }
        
        //--------------------------------------------------------------
        // COUNTERS
        aCounters.SetErrorCount(CT_TEL_GFP_10BERROR,aGfpPII.Get10BErrorCount());

        // Validate Counter region
        aCounters.Validate();

        //--------------------------------------------------------------
        // DEFECTS
        // Read current defects

        bool aLOFDState=false, aCsfLosState=false, aCsfLosyncState=false, aVirtualLOFDState=false;
        bool aCsfRFLinkFailState=false, aCsfRFOfflineState=false, aCsfRFAutoNegFailState=false, aCsfLinkFailRxState=false;
        bool aRFLinkFailState=false, aRFOfflineState=false, aRFAutoNegFailState=false, aLinkFailRxState=false;
        bool aFefiState=false, aCsfFefiState=false, aCsfFdiState=false, aCsfRdiState=false;
        bool aLocalAutoNegFailState = false, aPLMState=false, aLosAlignState=false, aSeqMisMatchState=false, aCoreHecState=false, aPliState=false;

        bool aLOFDEvent=false, aCsfLosEvent=false, aCsfLosyncEvent=false, aVirtualLOFDEvent=false;
        bool aCsfRFLinkFailEvent=false, aCsfRFOfflineEvent=false, aCsfRFAutoNegFailEvent=false, aCsfLinkFailRxEvent=false;
        bool aRFLinkFailEvent=false, aRFOfflineEvent=false, aRFAutoNegFailEvent=false, aLinkFailRxEvent=false;
        bool aFefiEvent=false, aCsfFefiEvent=false, aCsfFdiEvent=false, aCsfRdiEvent=false;
        bool aLocalAutoNegFailEvent=false, aPLMEvent=false, aLosAlignEvent=false, aSeqMisMatchEvent=false, aCoreHecEvent=false, aPliEvent=false;

        uint32 aNewLOFDCount   = aGfpPII.GetLofd();
        uint32 aNewCsfLosCount   = aGfpPII.GetCsfLos();
        uint32 aNewCsfLosyncCount = aGfpPII.GetCsfLosync();    
        uint32 aNewVirtualLOFDCount   = aGfpPII.GetVirtualLofd();
        uint32 aNewCsfRFLinkFailCount = aGfpPII.GetCsfTrdiRfLinkFail();
        uint32 aNewCsfRFOfflineCount = aGfpPII.GetCsfTrdiRfOffline();
        uint32 aNewCsfRFAutoNegFailCount = aGfpPII.GetCsfTrdiRfAnFail();
        uint32 aNewCsfLinkFailRxCount = aGfpPII.GetCsfTrdiCr0();
        uint32 aNewRFLinkFailCount = aGfpPII.GetRFLinkFail();
        uint32 aNewRFOfflineCount = aGfpPII.GetRFOffline();
        uint32 aNewRFAutoNegFailCount = aGfpPII.GetRFAutoNegotiationFail();
        uint32 aNewLinkFailRxCount = aGfpPII.GetLinkFailRx();
        bool aAutoNeg = aGfpPII.GetAutoNegotiationEnabled();
        uint32 aNewFefiCount = aGfpPII.GetFefi();
        uint32 aNewCsfFefiCount = aGfpPII.GetCsfFefi();
        uint32 aNewCsfFdiCount = aGfpPII.GetCsfFdi();
        uint32 aNewCsfRdiCount = aGfpPII.GetCsfRdi();
        uint32 aNewLocalAutoNegFailCount = aGfpPII.GetAutoNegotiationFail();
        uint32 aNewPLMCount   = aGfpPII.GetPlm();
        uint32 aNewLosAlignCount   = aGfpPII.GetLosAlign();
        uint32 aNewSeqMisMatchCount   = aGfpPII.GetSeqMisMatch();
        uint32 aNewCoreHecCount   = aGfpPII.GetCoreHec();
        uint32 aNewPliCount   = aGfpPII.GetPli();

        // Update LOFD state and count
        if(myPiiLOFDCount[anIndex] != aNewLOFDCount)
        {
            aLOFDEvent = true;
        }
        if(aNewLOFDCount%2 != 0)
        {
            aLOFDState = true;        
        }

        // Update CSF-LOS state and count
        if(myPiiCsfLosCount[anIndex] != aNewCsfLosCount)
        {
            aCsfLosEvent = true;
        }
        if(aNewCsfLosCount%2 != 0)
        {
            aCsfLosState = true;        
        }

        // Update VirtualLOFD state and count
        if(myPiiVirtualLOFDCount[anIndex] != aNewVirtualLOFDCount)
        {
            aVirtualLOFDEvent = true;
        }
        if(aNewVirtualLOFDCount%2 != 0)
        {
            aVirtualLOFDState = true;        
        }

        // Update CSF-LOSYNC state and count
        if(myPiiCsfLosyncCount[anIndex] != aNewCsfLosyncCount)
        {
            aCsfLosyncEvent = true;
        }
        if(aNewCsfLosyncCount%2 != 0)
        {
            aCsfLosyncState = true;        
        }

        // Update CSF FDI state and count
        if(myPiiCsfFdiCount[anIndex] != aNewCsfFdiCount)
        {
            aCsfFdiEvent = true;
        }
        if(aNewCsfFdiCount%2 != 0) 
        {
            aCsfFdiState = true;        
        }

        // Update CSF RDI state and count
        if(myPiiCsfRdiCount[anIndex] != aNewCsfRdiCount)
        {
            aCsfRdiEvent = true;
        }
        if(aNewCsfRdiCount%2 != 0) 
        {
            aCsfRdiState = true;        
        }


        // Update CSF-TRDI (RFLinkFail) state and count
        if(myPiiCsfRFLinkFailCount[anIndex] != aNewCsfRFLinkFailCount)
        {
            aCsfRFLinkFailEvent = true;
        }
        if(aNewCsfRFLinkFailCount%2 != 0)
        {
            aCsfRFLinkFailState = true;        
        }

        // Update CSF-TRDI (RFOffline) state and count
        if(myPiiCsfRFOfflineCount[anIndex] != aNewCsfRFOfflineCount)
        {
            aCsfRFOfflineEvent = true;
        }
        if(aNewCsfRFOfflineCount%2 != 0)
        {
            aCsfRFOfflineState = true;        
        }
    
        // Update CSF-TRDI (RFAutoNegFail) state and count
        if(myPiiCsfRFAutoNegFailCount[anIndex] != aNewCsfRFAutoNegFailCount)
        {
            aCsfRFAutoNegFailEvent = true;
        }
        if(aNewCsfRFAutoNegFailCount%2 != 0)
        {
            aCsfRFAutoNegFailState = true;        
        }

        // Update CSF-TRDI (LinkFailRx) state and count
        if(myPiiCsfLinkFailRxCount[anIndex] != aNewCsfLinkFailRxCount)
        {
            aCsfLinkFailRxEvent = true;
        }
        if(aNewCsfLinkFailRxCount%2 != 0)
        {
            aCsfLinkFailRxState = true;        
        }

        // Update FEFI state and count
        if(myPiiFefiCount[anIndex] != aNewFefiCount)
        {
            aFefiEvent = true;
        }
        if(aNewFefiCount%2 != 0) 
        {
            aFefiState = true;        
        }

        // Update CSF FEFI state and count
        if(myPiiCsfFefiCount[anIndex] != aNewCsfFefiCount)
        {
            aCsfFefiEvent = true;
        }
        if(aNewCsfFefiCount%2 != 0) 
        {
            aCsfFefiState = true;        
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

        // Update Loss Alignment state and count
        if(myPiiLosAlignCount[anIndex] != aNewLosAlignCount)
        {
            aLosAlignEvent = true;
        }
        if(aNewLosAlignCount%2 != 0)
        {
            aLosAlignState = true;        
        }

        // Update Sequence MisMatch state and count
        if(myPiiSeqMisMatchCount[anIndex] != aNewSeqMisMatchCount)
        {
            aSeqMisMatchEvent = true;
        }
        if(aNewSeqMisMatchCount%2 != 0)
        {
            aSeqMisMatchState = true;        
        }

        // Update Core Hec (cHEC) state and count
        if(myPiiCoreHecCount[anIndex] != aNewCoreHecCount)
        {
            aCoreHecEvent = true;
        }
        if(aNewCoreHecCount%2 != 0)
        {
            aCoreHecState = true;        
        }

        // Update Pli (Payload Length Ind) state and count
        if(myPiiPliCount[anIndex] != aNewPliCount)
        {
            aPliEvent = true;
        }
        if(aNewPliCount%2 != 0)
        {
            aPliState = true;        
        }


        // Only read Auto-Negotiation defects if we are doing Auto-Negotiation, as hardware can
        // return us back these defects even though Auto-Negotiation was not enabled.
        if(aAutoNeg)
        {

            // Update LocalAutoNegFail state and count
            if(myPiiLocalAutoNegFailCount[anIndex] != aNewLocalAutoNegFailCount)
            {
                aLocalAutoNegFailEvent = true;
            }
            if(aNewLocalAutoNegFailCount%2 != 0)
            {
                aLocalAutoNegFailState = true;        
            }

            // Update RFLinkFail state and count
            if(myPiiRFLinkFailCount[anIndex] != aNewRFLinkFailCount)
            {
                aRFLinkFailEvent = true;
            }
            if(aNewRFLinkFailCount%2 != 0)
            {
                aRFLinkFailState = true;        
            }

            // Update RFOffline state and count
            if(myPiiRFOfflineCount[anIndex] != aNewRFOfflineCount)
            {
                aRFOfflineEvent = true;
            }
            if(aNewRFOfflineCount%2 != 0)
            {
                aRFOfflineState = true;        
            }
    
            // Update RFAutoNegFail state and count
            if(myPiiRFAutoNegFailCount[anIndex] != aNewRFAutoNegFailCount)
            {
                aRFAutoNegFailEvent = true;
            }
            if(aNewRFAutoNegFailCount%2 != 0)
            {
                aRFAutoNegFailState = true;        
            }

            // Update LinkFailRx state and count
            if(myPiiLinkFailRxCount[anIndex] != aNewLinkFailRxCount)
            {
                aLinkFailRxEvent = true;
            }
            if(aNewLinkFailRxCount%2 != 0)
            {
                aLinkFailRxState = true;        
            }
        }
        else
        {
            aRFLinkFailEvent = false;
            aRFLinkFailState = false;        
            aRFOfflineEvent = false;
            aRFOfflineState = false;        
            aRFAutoNegFailEvent = false;
            aRFAutoNegFailState = false;        
            aLinkFailRxEvent = false;
            aLinkFailRxState = false;     
            aLocalAutoNegFailEvent = false;
            aLocalAutoNegFailState = false;        
        }

        // Update local defect counts
        myPiiLOFDCount[anIndex] = aNewLOFDCount;
        myPiiCsfLosCount[anIndex] = aNewCsfLosCount;
        myPiiCsfLosyncCount[anIndex] = aNewCsfLosyncCount;
        myPiiVirtualLOFDCount[anIndex] = aNewVirtualLOFDCount;
        myPiiCsfRFLinkFailCount[anIndex] = aNewCsfRFLinkFailCount;
        myPiiCsfRFOfflineCount[anIndex] = aNewCsfRFOfflineCount;
        myPiiCsfRFAutoNegFailCount[anIndex] = aNewCsfRFAutoNegFailCount;
        myPiiCsfLinkFailRxCount[anIndex] = aNewCsfLinkFailRxCount;
        myPiiRFLinkFailCount[anIndex] = aNewRFLinkFailCount;
        myPiiRFOfflineCount[anIndex] = aNewRFOfflineCount;
        myPiiRFAutoNegFailCount[anIndex] = aNewRFAutoNegFailCount;
        myPiiLinkFailRxCount[anIndex] = aNewLinkFailRxCount;
        myPiiFefiCount[anIndex] = aNewFefiCount;
        myPiiCsfFefiCount[anIndex] = aNewCsfFefiCount;
        myPiiCsfFdiCount[anIndex] = aNewCsfFdiCount;
        myPiiCsfRdiCount[anIndex] = aNewCsfRdiCount;
		myPiiLocalAutoNegFailCount[anIndex] = aNewLocalAutoNegFailCount;
        myPiiPLMCount[anIndex] = aNewPLMCount;
        myPiiLosAlignCount[anIndex] = aNewLosAlignCount;
        myPiiSeqMisMatchCount[anIndex] = aNewSeqMisMatchCount;
        myPiiCoreHecCount[anIndex] = aNewCoreHecCount;
        myPiiPliCount[anIndex] = aNewPliCount;

        // Update actual defect
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_LOFD_DEFECT,  aLOFDState,  aLOFDEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_LOS_DEFECT,  aCsfLosState,  aCsfLosEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_LOSYNC_DEFECT,  aCsfLosyncState,  aCsfLosyncEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_VIRTUAL_LOFD_DEFECT,  aVirtualLOFDState,  aVirtualLOFDEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_TRDI_RFLINKFAIL_DEFECT,  aCsfRFLinkFailState,  aCsfRFLinkFailEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_TRDI_RFOFFLINE_DEFECT,  aCsfRFOfflineState,  aCsfRFOfflineEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_TRDI_RFAUTONEGFAIL_DEFECT,  aCsfRFAutoNegFailState,  aCsfRFAutoNegFailEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_TRDI_CR0_DEFECT,  aCsfLinkFailRxState,  aCsfLinkFailRxEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_RFLINKFAIL_DEFECT,  aRFLinkFailState,  aRFLinkFailEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_RFOFFLINE_DEFECT,  aRFOfflineState,  aRFOfflineEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_RFAUTONEGFAIL_DEFECT,  aRFAutoNegFailState,  aRFAutoNegFailEvent);  
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_LINKFAILRX_DEFECT,  aLinkFailRxState,  aLinkFailRxEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, IsUpstreamLayerInternalFailed(), false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_INTERNAL_LOCK, IsUpstreamLayerInternalLocked(), false);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_FEFI_DEFECT, aFefiState, aFefiEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_FEFI_DEFECT, aCsfFefiState, aCsfFefiEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_FDI_DEFECT, aCsfFdiState, aCsfFdiEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CSF_RDI_DEFECT, aCsfRdiState, aCsfRdiEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_ANF_DEFECT, aLocalAutoNegFailState, aLocalAutoNegFailEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_PLM_DEFECT, aPLMState, aPLMEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_LOS_ALIGN, aLosAlignState, aLosAlignEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_VCG_SEQMISMATCH, aSeqMisMatchState, aSeqMisMatchEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_CORE_HEC_DEFECT, aCoreHecState, aCoreHecEvent);
        hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_PLI_DEFECT, aPliState, aPliEvent);
		hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerFailedForMaintSig(), false);
    	hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, IsUpstreamLayerInternalFailedForMaintSig(), false);

        // Validate defect object
        aDefects.Validate();

        if (hasDefectsChanged) 
            GetMonIf().GetDefectsRegion()->IncModificationCounter();

    }

    myFirstPassFlag = false;
    return NULL;
}


bool MON_GfpUpdateStatusAction::GetInternalRealTimeDefects(uint16 index, uint8 facNumber, CT_TEL_Defect theDefect)
{
    TSPII_GfpIf& aGfpPII = myGfpPiiRegion[index];

    // Only read defects that fail the layer
    // bool aIsLayerFail =  myLOFDState  || myCsfLosState || myCsfLosyncState || myVirtualLOFDState 
    //                   || myPLMState   || myCsfFdiState || myCsfRdiState    || myUpperLayerInternalFailTAState;
    uint32 aNewLOFDCount   = aGfpPII.GetLofd();
    uint32 aNewCsfLosCount   = aGfpPII.GetCsfLos();
    uint32 aNewCsfLosyncCount = aGfpPII.GetCsfLosync();    
    uint32 aNewVirtualLOFDCount   = aGfpPII.GetVirtualLofd();
    uint32 aNewCsfFdiCount = aGfpPII.GetCsfFdi();
    uint32 aNewCsfRdiCount = aGfpPII.GetCsfRdi();
    uint32 aNewPLMCount   = aGfpPII.GetPlm();

    // For now, if any are odd (meaning defect is on), return 1
    if ( (aNewLOFDCount%2        != 0) ||
         (aNewCsfLosCount%2      != 0) ||
         (aNewCsfLosyncCount%2   != 0) ||
         (aNewVirtualLOFDCount%2 != 0) ||
         (aNewCsfFdiCount%2      != 0) ||
         (aNewCsfRdiCount%2      != 0) ||
         (aNewPLMCount%2         != 0) ||
         (IsUpstreamLayerInternalFailed()) )
    {
        return(true);
    }

    return(false);
}

bool MON_GfpUpdateStatusAction::GetExternalRealTimeDefects(uint16 index, uint8 facNumber, CT_TEL_Defect theDefect)
{
    bool aOptLayerFailState = false;
    bool aOptLOSState = false;
    bool aRsLOSState = false;
    bool aLOFState = false;
    bool aLinkFailRxState  = false;
    bool aFefiState = false;
    bool aMacFefiState = false;
    bool hasDefectsChanged = false;
    bool aDefectState = false; 
    bool aAutoNeg = false;
    uint32 aDefectCount = 0;

    TSPII_OpticalRegion* theOptPiiRegion;
    TSPII_RsRegion* theRsPiiRegion;
    TSPII_MacRegion* theMacPiiRegion;
    TSPII_GfpIf& aGfpPII = myGfpPiiRegion[index];

    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());

    switch (theDefect)
    {
    case CT_TEL_RS_LOS_DEFECT:
        theOptPiiRegion = TSPII_SubApplication::GetInstance()->GetOptical(TSPII_PORT_SIDE_0+facNumber);
        if (theOptPiiRegion)
        {
            TSPII_OpticalIf& aOptPII = (*theOptPiiRegion)[0]; 
            aDefectCount = aOptPII.GetOptLOS();
            if (aDefectCount%2 != 0)
            {
                aOptLOSState = true;        
            }
        }

        theRsPiiRegion  = TSPII_SubApplication::GetInstance()->GetRs(TSPII_PORT_SIDE_0+facNumber);
        if (theRsPiiRegion)
        {
            TSPII_RsIf& aRsPII  = (*theRsPiiRegion)[0]; 
            aDefectCount = aRsPII.GetLOS();
            if (aDefectCount%2 != 0)
            {
                aRsLOSState = true;        
            }
        }  // if (theRsPiiRegion)

        if (aCardContext)
        {
            MON_AppIf* aOptMonApp     = NULL;
            aOptMonApp = &(aCardContext->GetOptIf().GetMonPortSideApp((CT_IntfId)facNumber)); 
            if (aOptMonApp)
            {
                MON_OptDefects& aOptDefects  = static_cast<MON_OptDefects&>((*(aOptMonApp)->GetDefectsRegion())[0]);    
                aOptDefects.GetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT, &aDefectCount, &aOptLayerFailState);
            }
        }  // if (aCardContext)

        // Here, simulate UpperLayerFail, which sets the Rs LOS defect.
        // For SSM and SMTMU, the Upper Layer for Rs is the Opt Layer.
        // In the Opt Layer in 7.1, only Opt LOS and Opt Upper Layet Fail
        // fails the layer, so check against those defect (read above).
        aDefectState = (aOptLOSState || aRsLOSState || aOptLayerFailState);
        break;

    case CT_TEL_RS_LOF_DEFECT:
        theRsPiiRegion  = TSPII_SubApplication::GetInstance()->GetRs(TSPII_PORT_SIDE_0+facNumber);
        if (theRsPiiRegion)
        {
            TSPII_RsIf& aRsPII  = (*theRsPiiRegion)[0]; 
            aDefectCount = aRsPII.GetLOF();
            if (aDefectCount%2 != 0)
            {
                aLOFState = true;        
            }
        }  // if (theRsPiiRegion)
        aDefectState = aLOFState;
        break;

    case CT_TEL_GFP_LINKFAILRX_DEFECT:
        aAutoNeg = aGfpPII.GetAutoNegotiationEnabled();

        // Link Fail Rx is only read when AutoNeg is on.
        if (aAutoNeg)
        {
            aDefectCount = aGfpPII.GetLinkFailRx();
            if (aDefectCount%2 != 0)
            {
                aLinkFailRxState = true;        
            }
        }
        aDefectState = aLinkFailRxState;
        break;

    case CT_TEL_GFP_FEFI_DEFECT:
        aDefectCount = aGfpPII.GetFefi();
        if (aDefectCount%2 != 0)
        {
            aFefiState = true;        
        }
        aDefectState = aFefiState;
        break;

    case CT_TEL_MAC_FEFI_DEFECT:
        theMacPiiRegion  = TSPII_SubApplication::GetInstance()->GetMac(TSPII_PORT_SIDE_0+facNumber);
        if (theMacPiiRegion)
        {
            TSPII_MacIf& aMacPII  = (*theMacPiiRegion)[0]; 
            aDefectCount = aMacPII.GetFefi();
            if (aDefectCount%2 != 0)
            {
                aMacFefiState = true; 
            }
        }  // if (theMacPiiRegion)
        aDefectState = aMacFefiState;
        break;

    default:
        aDefectState = false;
        break;
    }  // switch (theDefect)

    return(aDefectState);
}
