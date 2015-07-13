// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_GfpAutomaticAction.h"
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_LacpTypes.h>
#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_AppIf.h>
#include "../CFG_AppIf.h"
#include "../CFG_HoldOffTimer.h"
#include "../CFG_Gfp.h"
#include "../CFG_Rs.h"
#include "../CFG_Opt.h"
#include "../CFG_OptAutomatic.h"
#include "../CFG_Evc.h"
#include "../CFG_Mac.h"
#include "../CFG_GfpAutomatic.h"
#include "../CFG_EvcAutomatic.h"
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_MacDefects.h>
#include <Monitoring/MON_MacStatus.h>
#include <Monitoring/MON_GfpUpdateStatusAction.h>
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_Dispatcher.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>

extern "C"
{
    extern uint32 TMBget_timestamp( void );
    extern uint32 TMBusec_since( uint32 timestamp );
}

CFG_GfpAutomaticAction::CFG_GfpAutomaticAction(CFG_AppIf& theCfgIf,
                                               CFG_AppIf* theOptCfgApp,
                                               MON_AppIf* theRsMonApp,
                                               MON_AppIf* theGfpMonApp,
                                               MON_AppIf* theMsOtherSideMonApp,
                                               CFG_AppIf* theOptOtherSideCfgApp,
                                               CT_IntfId  theIntfId,
                                               T6100_TelecomIf* theRsApp,
                                               T6100_TelecomIf* theOptApp,
                                               T6100_TelecomIf* theMacApp,
                                               CFG_AppIf* theEvcCfgApp,
                                               uint8 theNumPorts,
                                               unsigned int theNumEvcs,
                                               uint8 theNumGfps,
                                               CFG_AppIf* theRsCfgApp) :
    CFG_HwRefreshAction(theCfgIf),
    myOptCfgApp(theOptCfgApp),
    myRsMonApp(theRsMonApp),
    myGfpMonApp(theGfpMonApp),
    myMsOtherSideMonApp(theMsOtherSideMonApp),
    myOptOtherSideCfgApp(theOptOtherSideCfgApp),
    myIntfId(theIntfId),
    myRsApp(theRsApp),
    myOptApp(theOptApp),
    myMacApp(theMacApp),
    myEvcCfgApp(theEvcCfgApp),
    myRsCfgApp(theRsCfgApp),
    myNumPorts(theNumPorts),
    myNumEvcs(theNumEvcs),
    myNumGfps(theNumGfps),
    myNeedRealTimeDefectsDuringHoldoff(false),
    myRealTimeDefectReadPasses(0),
    myNormalReadPasses(0), 
    myAltRealTimeDefectReadPasses(0),
    myAltNormalReadPasses(0),
    myWakeUpAction(NULL),
    myProcess(NULL)
{

    // register about config changes or defect changes
    GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());

    if (myOptCfgApp)
    {
        myProcess      = new FC_OneShotProcess(*GetBbAction(), gHighDispatcher);
        myWakeUpAction = new FC_WakeUpProcessAction(*myProcess);
        CFG_Region* theOptCfgRegion = myOptCfgApp->GetCfgRegion();
        theOptCfgRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theOptCfgRegion);
    }

    if (myRsCfgApp)
	{
        CFG_Region* theRsCfgRegion = myRsCfgApp->GetCfgRegion();
        theRsCfgRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theRsCfgRegion);
    }

    if (myRsMonApp)
    {
        MON_Region* theRsMonRegion = myRsMonApp->GetDefectsRegion();
        theRsMonRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theRsMonRegion);
    }

    if (myMsOtherSideMonApp)
    {
        GetBbAction()->AddInputRegion(myMsOtherSideMonApp->GetDefectsRegion());
    }

    if (myOptOtherSideCfgApp)
    {
        GetBbAction()->AddInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
    }

    if (myRsApp && myOptApp && myEvcCfgApp && myMacApp)
    {

        myProcess      = new FC_OneShotProcess(*GetBbAction(), gHighDispatcher);
        myWakeUpAction = new FC_WakeUpProcessAction(*myProcess);

        CFG_Region* theEvcCfgRegion = myEvcCfgApp->GetAutomaticCfgRegion();
        theEvcCfgRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theEvcCfgRegion);

        uint32 i = 0;
        // Initialize Region Arrays to NULL
        for (i = 0; i < theNumPorts; i++)
        {
            myOptCfgObject[i] =       NULL;
            myRsCfgObject[i]  =       NULL;
            myRsMonObject[i]  =       NULL;
            myMacMonObject[i] =       NULL;
            myMacMonStatus[i] =       NULL;
        } //   for (uint32 i = 0; i < 13; i++)

        // Now fill in the appropriate arrays
        // (based on the number of ports)
        for (i = 0; i < myNumPorts; i++)
        {
            CFG_AppIf* OptCfgApp = NULL;
            OptCfgApp = &myOptApp->GetCfgPortSideApp(CT_IntfId(i));
            if (OptCfgApp)
            {
                myOptCfgObject[i] = OptCfgApp->GetCfgRegion();
                myOptCfgObject[i]->AddObserver(myWakeUpAction);
                // Add the Region as an Input Region
                if(myOptCfgObject[i])  GetBbAction()->AddInputRegion(myOptCfgObject[i]);
            }

            CFG_AppIf* RsCfgApp = NULL;
            RsCfgApp = &myRsApp->GetCfgPortSideApp(CT_IntfId(i));
            if (RsCfgApp)
            {
                myRsCfgObject[i] = RsCfgApp->GetCfgRegion();
                myRsCfgObject[i]->AddObserver(myWakeUpAction);
                // Add the Region as an Input Region
                if(myRsCfgObject[i])  GetBbAction()->AddInputRegion(myRsCfgObject[i]);
            }

            MON_AppIf* RsMonApp = NULL;
            RsMonApp = &myRsApp->GetMonPortSideApp(CT_IntfId(i));
            if (RsMonApp)
            {
                myRsMonObject[i] = RsMonApp->GetDefectsRegion();
                myRsMonObject[i]->AddObserver(myWakeUpAction);
                // Add the Region as an Input Region
                if(myRsMonObject[i])  GetBbAction()->AddInputRegion(myRsMonObject[i]);
            }

            MON_AppIf* MacMonApp = NULL;
            MacMonApp = &myMacApp->GetMonPortSideApp(CT_IntfId(i));
            if (MacMonApp)
            {
                myMacMonObject[i] = MacMonApp->GetDefectsRegion();
                myMacMonObject[i]->AddObserver(myWakeUpAction);
                // Add the Region as an Input Region
                if(myMacMonObject[i])  GetBbAction()->AddInputRegion(myMacMonObject[i]);
                // Also need Status region
                // Note: the needed information will trigger the Mac Defects, 
                // so we don't need to add another input region.
                myMacMonStatus[i] = MacMonApp->GetStatusRegion();
            }

            CFG_AppIf* MacCfgApp = NULL;
            MacCfgApp = &myMacApp->GetCfgPortSideApp(CT_IntfId(i));
            if (MacCfgApp)
            {
                myMacCfgObject[i] = MacCfgApp->GetCfgRegion();
                myMacCfgObject[i]->AddObserver(myWakeUpAction);
                // Add the Region as an Input Region
                if(myMacCfgObject[i])  GetBbAction()->AddInputRegion(myMacCfgObject[i]);
            }

        }  //  for (i = 0; i < myNumPorts; i++)

    }

    if (myGfpMonApp)
    {
        MON_Region* theGfpMonRegion = myGfpMonApp->GetDefectsRegion();
        theGfpMonRegion->AddObserver(myWakeUpAction);
        GetBbAction()->AddInputRegion(theGfpMonRegion);
    }

    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());

    // Initialize bool to indicate if holdoff timer is active for that instance
    uint32 i = 0;
    for (i = 0; i < CT_TEL_NBR_OF_GFPS; i++)
    {
        myHoldoffTimerActive[i] = false;
        myAltHoldoffTimerActive[i] = false;
    } 

    // Read Real Time defects for the Gfp on the SSM and SMTM families
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {
        if((aCardContext->GetCardFamily() == SMTM_FAM) ||
           (aCardContext->GetCardFamily() == SSM_FAM)  )
        {
            myNeedRealTimeDefectsDuringHoldoff = true;
        }
    } // if (aCardContext)
}

CFG_GfpAutomaticAction::~CFG_GfpAutomaticAction()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());

    if (myRsCfgApp)
    {
        myRsCfgApp->GetCfgRegion()->RemoveObserver(myWakeUpAction);
    }
    if (myRsMonApp)
    {
        myRsMonApp->GetDefectsRegion()->RemoveObserver(myWakeUpAction);
    }
    if (myGfpMonApp)
    {
        myGfpMonApp->GetDefectsRegion()->RemoveObserver(myWakeUpAction);
    }
    if (myMsOtherSideMonApp)
    {
        myMsOtherSideMonApp->GetDefectsRegion()->RemoveObserver(myWakeUpAction);
    }
    if (myOptOtherSideCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
    }
    if (myOptCfgApp)
    {
        myOptCfgApp->GetCfgRegion()->RemoveObserver(myWakeUpAction);
    }
    if (myOptCfgApp || myRsMonApp)
    {
        delete myWakeUpAction;
        delete myProcess;
    }
    else
    {
        if (myRsApp && myOptApp && myEvcCfgApp && myMacApp)
        {
            myEvcCfgApp->GetAutomaticCfgRegion()->RemoveObserver(myWakeUpAction);

            for (uint32 i = 0; i < myNumPorts; i++)
            {
                if(myOptCfgObject[i])       myOptCfgObject[i]->RemoveObserver(myWakeUpAction);
                if(myRsCfgObject[i])        myRsCfgObject[i]->RemoveObserver(myWakeUpAction);
                if(myRsMonObject[i])        myRsMonObject[i]->RemoveObserver(myWakeUpAction);
                if(myMacMonObject[i])       myMacMonObject[i]->RemoveObserver(myWakeUpAction);
                if(myMacCfgObject[i])       myMacCfgObject[i]->RemoveObserver(myWakeUpAction);
            }  //  for (uint32 i = 0; i < myNumPorts; i++)

            delete myWakeUpAction;
            delete myProcess;
        }
    }

    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_GfpAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{

     bool     aDebug = false;
     bool     aRealTimeDefectsRead = false;
     bool     aReadAltRealTimeDefects = false;
     uint32   aStartTime = 0;
     CFG_Gfp& aFirstCfgObject = static_cast<CFG_Gfp&>((*GetCfgIf().GetCfgRegion())[0]);
     if(aFirstCfgObject.IsDebugFlagSet())
     {
         aDebug = true;
         aStartTime = TMBget_timestamp();
     }

    // Loop thru all of the EVCs. CONSIDER LOOPING THRU VCG'S INSTEAD.
    for (uint8 anIndex = 0; anIndex < myNumGfps; anIndex++)
    {
        uint32 aDefectCount       = 0L;
        bool aForce10BError       = false;
        bool aForceGenericLayerFail = false;
        bool aDefectState         = false;
        bool aInjectMaintenance   = false;
        bool aForceIdle           = false;
        bool aPrbsEnabled         = false;
        bool aForceAutoNegSignal  = false;
        bool aOneWayGbe           = false;
        bool aDisableExternalErrorSignaling   = false; //this controls both the 10B and GenericLayerFail signaling
        bool aSetForceTASignalingActive       = false;
        bool aSetAltForceTASignalActive       = false;
        CT_TEL_GfpClientMgmt aClientMgmtFrame = CT_TEL_GFP_CMGMT_NONE;
        uint8 aFacilityPortIdx                = CFG_GFP_DEFAULT_PORT_INDEX;

        uint32 aHoldOffDelay      = CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO;
        bool aLSPActive           = false;
        bool aForceCsfFefi        = false;

        CFG_Region* aOptCfgRegion = NULL;
        MON_Region* aRsMonRegion  = NULL;
        MON_Region* aMacMonRegion = NULL;
        MON_Region* aMacStatusRegion = NULL;
        CFG_Region* aMacCfgRegion = NULL;
        MON_Region* aGfpMonRegion = NULL;
        CFG_Region* aRsCfgRegion  = NULL;

        CFG_GfpAutomatic& aAutomaticCfgObject   = static_cast<CFG_GfpAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[anIndex]);
        CFG_Gfp& aCfgObject = static_cast<CFG_Gfp&>((*GetCfgIf().GetCfgRegion())[anIndex]);


        if (myOptCfgApp)
        {
            aOptCfgRegion = myOptCfgApp->GetCfgRegion();
            if (myRsCfgApp) 
            {
                aRsCfgRegion = myRsCfgApp->GetCfgRegion();
            }
        }
        else if (myRsApp && myOptApp && myEvcCfgApp)
        {
            CFG_EvcAutomatic& aEvcAutoConfig = static_cast<CFG_EvcAutomatic&>((*myEvcCfgApp->GetAutomaticCfgRegion())[0]);
            uint8 aPortIdx = aEvcAutoConfig.GetPortIdx(anIndex);

            if (aPortIdx != CT_INTF_ID_UNKNOWN)
            {
                aAutomaticCfgObject.SetPortIndex(aPortIdx);
                aOptCfgRegion  = myOptCfgObject[aPortIdx];
                aRsCfgRegion   = myRsCfgObject[aPortIdx];
                aRsMonRegion   = myRsMonObject[aPortIdx];
                aMacMonRegion  = myMacMonObject[aPortIdx];
                aMacStatusRegion = myMacMonStatus[aPortIdx];
                aMacCfgRegion  = myMacCfgObject[aPortIdx];
            }
            else
            {
                aAutomaticCfgObject.SetPortIndex(CFG_GFP_DEFAULT_PORT_INDEX);
            }
        }

        if (myRsMonApp)
        {
            aRsMonRegion = myRsMonApp->GetDefectsRegion();
        }

        if (myGfpMonApp)
        {
            aGfpMonRegion = myGfpMonApp->GetDefectsRegion();
        }


        if (aOptCfgRegion)
        {

            CFG_Opt& aOptCfgObject = static_cast<CFG_Opt&>((*aOptCfgRegion)[0]);

            if (aOptCfgObject.GetPrbsRxEnable() || aOptCfgObject.GetPrbsTxEnable())
            {
                aPrbsEnabled = true;
            }

            // Get HoldOffDelay in CFG Opt for ALS to use later in the method
            // to hold off forcing AIS-L
            aHoldOffDelay = aOptCfgObject.GetAlsHoldOffDelay();



            if (myOptOtherSideCfgApp) 
            {
                CFG_Opt& aOptOtherSideConfig = static_cast<CFG_Opt&>((*myOptOtherSideCfgApp->GetCfgRegion())[0]);
                // If line side has terminal loopback, then don't force maintenance signaling
                aDisableExternalErrorSignaling = aOptOtherSideConfig.GetTerminalLoopBackEnable();

                // Not completely sure of this code, but put it here for now.
                if (aOptOtherSideConfig.GetPrbsRxEnable() || aOptOtherSideConfig.GetPrbsTxEnable())
                {
                    aPrbsEnabled = true;
                }

                CFG_OptAutomatic& aOptOtherSideAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptOtherSideCfgApp->GetAutomaticCfgRegion())[0]);
                //If line side protection is configured, add a line side protection holdoff value
                //to the configured timer to give enough time for the protection switch to happen prior
                //to any action by CFG.
                aLSPActive = aOptOtherSideAutoConfig.GetLineSideProtExists();
                
            }  // if (myOptOtherSideCfgApp)



            if (!aOptCfgObject.GetFacilityLoopBackEnable() && !aPrbsEnabled)
            {

                // Check for one way cross connection (in the add direction), which means
                // it is not a destination from the perspective og the center of the card
                // If found, force idle codes and disable 8b/10b illegal code signaling.
                if (aRsMonRegion)
                {
                    if (aRsMonRegion->IsValid())
                    {
                        MON_RsDefects& aRsMonObject  = static_cast<MON_RsDefects&>((*aRsMonRegion)[0]);
                        // These methods help determine if there is a one-way cross connect and are based on
                        // the facilities perspective of the circuit toward the interior of the card
                        if (!aRsMonObject.IsConnectedAsDst())
                        {
                            //MR219914 add addition check for OTNM
                            aDisableExternalErrorSignaling = DoubleCheckDisableExternalErrorSignaling(aRsMonObject.IsConnectedAsSrc(), aRsMonObject.IsConnectedAsDst());

                            // In accordance with 802.3 requirements, do not force idle
                            // for framed data traffic.
                            if (aCfgObject.GetFramingMode() != CT_TEL_GFP_FRAMING_FRAMED)
                            {
                                aForceIdle = true;
                            }
                        }

                        // Check if there is a one-way cross connect going to the router, if there
                        // is then we need to indicate this to TSPII.
                        if ((aRsMonObject.IsConnectedAsDst()) && (!aRsMonObject.IsConnectedAsSrc()))
                        {
                            aOneWayGbe = true;
                        }
                    }
                }
            }  //  if (!aOptCfgObject.GetFacilityLoopBackEnable() && !aPrbsEnabled)


            // If GFP channel is enabled, then determine current CSF mode based
            // on MON RS information. If not enabled, then CSF mode is irrelavent
            // and should be set to not force CSF.
            if (aCfgObject.GetEnableMode())
            {
                // Check that Auto-Negotiation is enabled, before checking for defects.
                // A new method was added to the Mac Status region to indication if 
                // software Auto Negotiation should be enabled, which is based on 
                // the ETH Sfp/Xfp type
                bool aMacAutoNegEnabled = false;
                if (aMacStatusRegion)
                {
                    if (aMacStatusRegion->IsValid())
                    {
                        MON_MacStatus& aMacMonStatus = static_cast<MON_MacStatus&>((*aMacStatusRegion)[0]);
                        aMacAutoNegEnabled = aMacMonStatus.GetIsSoftwareAutoNegEnabled();
                    } // if (aMacStatusRegion->IsValid())
                }  // if (aMacStatusRegion)
                aAutomaticCfgObject.SetMacAutoNegEnabled(aMacAutoNegEnabled);

                MON_UpdateStatusAction* anUpdateAction = NULL;
                // If necessary, Read real time defects 
                if (myNeedRealTimeDefectsDuringHoldoff && myAltHoldoffTimerActive[anIndex])
                {
                    if (myGfpMonApp)
                    {
                        anUpdateAction = myGfpMonApp->GetUpdateStatusAction();
                        if (anUpdateAction)
                        {
                            // Find Port Number based on whether it is a pool or 1-1 mapping.
                            if (myIntfId == CT_PORT_SIDE_32)
                            {
                                aFacilityPortIdx = aAutomaticCfgObject.GetPortIndex();
                            }
                            else
                            {
                                aFacilityPortIdx = myIntfId;
                            }
                            // Only read Real Time External Defects if there is a valid port number
                            if (aFacilityPortIdx != CFG_GFP_DEFAULT_PORT_INDEX)
                            {
                                aReadAltRealTimeDefects = true;
                            }
                        }  // if (anAction)
                    }  // if (myGfpMonApp)
                }  //  if (myNeedRealTimeDefectsDuringHoldoff && myAltHoldoffTimerActive[anIndex])

                // Check for need to force CSF frames.
                if (aRsMonRegion)
                {
                    if (aRsMonRegion->IsValid())
                    {
                        MON_RsDefects& aRsMonObject  = static_cast<MON_RsDefects&>((*aRsMonRegion)[0]);

                        aClientMgmtFrame = CT_TEL_GFP_CMGMT_NONE;
                        aInjectMaintenance = false;

                        // If in terminal loopback, then do not send ClientMgmtFrame
                        if (!aOptCfgObject.GetTerminalLoopBackEnable())
                        {
                            // Set force client management frame. First check for RS-LOS and RS Lock State then
                            // check for RS-LOF (Loss of sync). CSF-LOS takes precedence over CSF-LOSYNC.
                            aDefectState = aRsMonObject.GetDefectForMaintSig(CT_TEL_RS_LOS_DEFECT);
                            if (aReadAltRealTimeDefects && anUpdateAction)
                            {
                                aDefectState = (*anUpdateAction).GetExternalRealTimeDefects(anIndex, aFacilityPortIdx, CT_TEL_RS_LOS_DEFECT);
                            }
                            if ( ((!aCfgObject.GetIgnoreLosLosyncFlag()) && aDefectState) || aRsMonObject.IsLayerLocked() )                             
                            {
                                aClientMgmtFrame = CT_TEL_GFP_CMGMT_CSF_LOS;
                            }
                            else
                            {
                                // Look for LoSync first
                                aDefectState = aRsMonObject.GetDefectForMaintSig(CT_TEL_RS_LOF_DEFECT);
                                if (aReadAltRealTimeDefects && anUpdateAction)
                                {
                                    aDefectState = (*anUpdateAction).GetExternalRealTimeDefects(anIndex, aFacilityPortIdx, CT_TEL_RS_LOF_DEFECT);
                                }
                                // Only check LOF if not an SSM with AN enabled
                                if ((!aCfgObject.GetIgnoreLosLosyncFlag()) && (!aMacAutoNegEnabled)  && (aDefectState))                                
                                {
                                    aClientMgmtFrame = CT_TEL_GFP_CMGMT_CSF_LOSYNC;
                                }
                                else
                                {
                                    // Now check fot Local Fault and Remote Fault, but only for certain signal types
                                    CT_TEL_SignalType aSignalType = CT_TEL_SIGNAL_UNKNOWN;
                                    if (aRsCfgRegion)
                                    {
                                        if (aRsCfgRegion->IsValid()) 
                                        {
                                            CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*aRsCfgRegion)[0]);
                                            aSignalType = aRsCfgObject.GetSignalType();
                                        }
                                    }  //  if (myRsCfgApp)

                                    if (aSignalType == CT_TEL_SIGNAL_TGLAN_FRAME_STD) 
                                    {
                                        uint32 aLfCount = 0L,    aRfCount = 0L;
                                        bool   aLfState = false, aRfState = false;
                                        aLfState = aRsMonObject.GetDefectForMaintSig(CT_TEL_RS_LOCAL_FAULT_DEFECT);
                                        aRfState = aRsMonObject.GetDefectForMaintSig(CT_TEL_RS_REMOTE_FAULT_DEFECT);
                                        if (aLfState)
                                        {
                                            aClientMgmtFrame = CT_TEL_GFP_CMGMT_CSF_FDI;
                                        }
                                        else if (aRfState)
                                        {
                                            aClientMgmtFrame = CT_TEL_GFP_CMGMT_CSF_RDI;
                                        }
                                    }  //  if (aRsCfgRegion->IsValid())
                                }  //  else   -- of if (aDefectState)
                                   //         -- which was looking to send CSF-LOSYNC

                                // MR 109032.  This code is re-arraged to give the FEFI defect higher priority than LOF (Loss of Sync)
                                // So, if FEFI defect is present, send CSF-FEFI rather than CSF-LOSYNC (overwrites CT_TEL_GFP_CMGMT_CSF_LOSYNC)
                                if ((aMacMonRegion) && (aMacCfgRegion))
                                {
                                    // check FEFI at MAC layer to force CSF FEFI
                                    if (aMacMonRegion->IsValid())
                                    {
                                        MON_Defects& aMacMonObject = static_cast<MON_MacDefects&>((*aMacMonRegion)[0]);

                                        aMacMonObject.GetDefectStatus(CT_TEL_MAC_FEFI_DEFECT, &aDefectCount, &aDefectState);
                                        if (aReadAltRealTimeDefects && anUpdateAction)
                                        {
                                            aDefectState = (*anUpdateAction).GetExternalRealTimeDefects(anIndex, aFacilityPortIdx, CT_TEL_MAC_FEFI_DEFECT);
                                        }
                                        aForceCsfFefi |= aDefectState;
                                    }//aGfpMonRegion->IsValid()
                                }
                                else
                                {
                                    // check FEFI to force CSF FEFI
                                    if (aGfpMonRegion && (aGfpMonRegion->IsValid()))
                                    {
                                        MON_Defects& aGfpMonObject = static_cast<MON_Defects&>((*aGfpMonRegion)[anIndex]);

                                        aDefectState = aGfpMonObject.GetDefectForMaintSig(CT_TEL_GFP_FEFI_DEFECT);
                                        if (aReadAltRealTimeDefects && anUpdateAction)
                                        {
                                            aDefectState = (*anUpdateAction).GetExternalRealTimeDefects(anIndex, aFacilityPortIdx, CT_TEL_GFP_FEFI_DEFECT);
                                        }
                                        aForceCsfFefi |= aDefectState;                                   
                                    }//aGfpMonRegion->IsValid()
                                }  // else   -- of if ((aMacMonRegion) && (aMacCfgRegion))
                                   //        -- which was checking to see if CSF-FEFI should be sent

                                if (aForceCsfFefi)
                                {
                                    aClientMgmtFrame = CT_TEL_GFP_CMGMT_CSF_FEFI;
                                }

                            }  // else   -- of if ((aDefectState || aRsMonObject.IsLayerLocked()))
                               //        -- which was looking to send CSF-LOS

                            // Now check if a client management frame 
                            if (aClientMgmtFrame != CT_TEL_GFP_CMGMT_NONE)
                            {
                                aInjectMaintenance = true;
                            }

                        }  //  if (!aOptCfgObject.GetTerminalLoopBackEnable())

                        // Force 8B/10B, GenericLayerFail illegal code on port side intf if 
                        // facility is locked or the Gfp layer is failed (i.e., CSF defects are received
                        // or the internal layer is locked) and facility loopback is off.
                        // Note: Now, Force 8B/10B and GenericLayerFail are the same and one may be removed.
                        aForce10BError = false;
                        aForceGenericLayerFail = false;
                        if (!aOptCfgObject.GetFacilityLoopBackEnable())
                        {
                            if (!aOptCfgObject.GetTerminalLoopBackEnable())
                            {
                                if (aRsMonObject.IsLayerLocked())
                                {
                                    aForce10BError = true;
                                    aForceGenericLayerFail = true;
                                }
                            }  // if (!aOptCfgObject.GetTerminalLoopBackEnable())
                               //
                            if (aGfpMonRegion)
                            {
                                if (aGfpMonRegion->IsValid())
                                {
                                    MON_Defects& aGfpMonObject = static_cast<MON_Defects&>((*aGfpMonRegion)[anIndex]);
                                    bool a10bErrorCause = false;
                                    bool isGfpLayerInDefects = false;

                                    if ((myNeedRealTimeDefectsDuringHoldoff) && myHoldoffTimerActive[anIndex])
                                    {
                                        if (myGfpMonApp)
                                        {
                                            MON_UpdateStatusAction* anAction = myGfpMonApp->GetUpdateStatusAction();
                                            if (anAction)
                                            {
                                                isGfpLayerInDefects = (*anAction).GetInternalRealTimeDefects(anIndex);
                                                aRealTimeDefectsRead = true;
                                            }
                                        }  // if (myGfpMonApp)
                                    }
                                    else
                                    {
                                        isGfpLayerInDefects = aGfpMonObject.IsLayerForMaintSigInDefects();
                                    }

                                    if ( isGfpLayerInDefects || aGfpMonObject.IsLayerInternalLocked() ) 
                                    {
                                        aForce10BError = true;
                                        aForceGenericLayerFail = true;
                                    }

                                    // Check CSF FEFI to fail the layer if the defect exists 
                                    // and Prop Fefi is disabled.
                                   aDefectState = aGfpMonObject.GetDefectForMaintSig(CT_TEL_GFP_CSF_FEFI_DEFECT);
                                   aForceGenericLayerFail |= (aDefectState && (!aOptCfgObject.GetPropFefiEnabled()));    
                                }
                            }  // if (myGfpMonApp)
                               //
                            if (myMsOtherSideMonApp)
                            {
                                MON_Region* aMsOtherSideMonRegion = myMsOtherSideMonApp->GetDefectsRegion();
                                if (aMsOtherSideMonRegion->IsValid())
                                {
                                    MON_Defects& aMsOtherSideMonObject = static_cast<MON_Defects&>((*aMsOtherSideMonRegion)[0]);
                                    if (aMsOtherSideMonObject.IsLayerForMaintSigInDefects() || aMsOtherSideMonObject.IsLayerLocked())
                                    {
                                        aForce10BError = true;
                                        aForceGenericLayerFail = true;
                                    }
                                }
                            }  //if (myMsOtherSideMonApp)
                        }  // if (!aOptCfgObject.GetFacilityLoopBackEnable())

                        if (aPrbsEnabled)
                        {
                            // If PRBS is Enabled, don't send any maintenance signaling
                            aDisableExternalErrorSignaling = true;
                            aClientMgmtFrame = CT_TEL_GFP_CMGMT_NONE;
                        }

                        if (aDisableExternalErrorSignaling) 
                        {
                            aForce10BError = false;
                            aForceGenericLayerFail = false;
                        }
                        aAutomaticCfgObject.SetForceIdle(aForceIdle);
                    }  // if (aRsMonRegion->IsValid())
                }  //  if (aRsMonRegion)

                if (aOneWayGbe)
                {
                    aAutomaticCfgObject.SetOneWayGbe(true);
                }
                else
                {
                    aAutomaticCfgObject.SetOneWayGbe(false);
                }



                if ((aCfgObject.GetAutoNegotiationEnabled() || aMacAutoNegEnabled) && (aGfpMonRegion) && (!aPrbsEnabled))
                {
                    // Determine if any maintenance signals are required to be sent (Line Side).
                    if (aGfpMonRegion->IsValid())
                    {
                        MON_Defects& aGfpMonObject  = static_cast<MON_Defects&>((*aGfpMonRegion)[anIndex]);

                        // Check if we are already sending a CSF, i.e. CSF-LOS, CSF-LOSYNC.
                        // WARNING: This statement was originally written to not override CSF-LOS and CSF-LOSYNC, which both
                        // force maintenance signaling on the far end.  Post 6.2, there are other maintenance signals that 
                        // could be sent (CSF-FDI, CSF-RDI, etc.) that make the aInjectMaintenance variable true.  This statement
                        // should still be OK, but it may depend on what maintenance signals can be forced during auto negotiation.
                        // If any maintenance signal sets aInjectMaintenance but does not force maintnenace signals at the far end, 
                        // then this condition may need to be changed. 
                        if (!aInjectMaintenance)
                        {
                            aDefectState = aGfpMonObject.GetDefectForMaintSig(CT_TEL_GFP_LINKFAILRX_DEFECT);
                            if (aReadAltRealTimeDefects && anUpdateAction)
                            {
                                aDefectState = (*anUpdateAction).GetExternalRealTimeDefects(anIndex, aFacilityPortIdx, CT_TEL_GFP_LINKFAILRX_DEFECT);
                            }
                            aInjectMaintenance = (aDefectState && !aOptCfgObject.GetTerminalLoopBackEnable());
                            if (aInjectMaintenance)
                            {
                                aClientMgmtFrame = CT_TEL_GFP_CMGMT_CSF_LOS;
                            }

                            // Removed commented out Auto-Negotiationlogic that is NOT supported.
                            // In case it's needed in the future, see pre 7.0 labels.

                        } // aInjectMaintenance

                        // Check if any port side signals need to be forces
                        aDefectState = aGfpMonObject.GetDefectForMaintSig(CT_TEL_GFP_CSF_LOS_DEFECT);

                        aForceAutoNegSignal = (aDefectState && !aOptCfgObject.GetTerminalLoopBackEnable());
                        if (aForceAutoNegSignal)
                        {
                            aAutomaticCfgObject.SetForceLinkFailTx(true);
                            aForce10BError = false;
                            aForceGenericLayerFail = false;
                            // If we are forcing LinkFailTx, don't force anything else
                            // in the ingress direction.
                            // For now, do this only for SSM, which will have the
                            // aMacAutoNegEnabled flag set.
                            if (aMacAutoNegEnabled) 
                            {
                                aClientMgmtFrame = CT_TEL_GFP_CMGMT_NONE;
                            }
                        }
                        else
                        {
                            aAutomaticCfgObject.SetForceLinkFailTx(false);
                        }

                        // Removed commented out Auto-Negotiationlogic that is NOT supported.
                        // In case it's needed in the future, see pre 7.0 labels.

                    } // aGfpMonRegion->IsValid()

                }
                else
                {
                    //Disable this when Auto-Neg not being used.
                    aAutomaticCfgObject.SetForceLinkFailTx(false);

                }  // else    -- of if ((aCfgObject.GetAutoNegotiationEnabled()) && (aGfpMonRegion) && (!aPrbsEnabled))


                // Moved in 7.0 to be common for AutoNegotiationEnabled or not.
                // 
                // For Traffic Affecting Maintenance Signlaing only, use ApplyConditionAfterHoldoff
                // method to check if the Condition found should be applied based on the HoldOff Timer (Delay)
                // When Auto-Negotiation is enabled then CSF messages use the Hold Off Timer.
                if (aLSPActive)
                {
                    aHoldOffDelay = aHoldOffDelay + LINE_SIDE_PROTECTION_HOLDOFF;
                }

                bool aHoldoffTimerActive = false;
                CFG_HoldOffTimer* aTimer = GetCfgIf().GetHoldOffTimer(anIndex);
                if (aTimer) 
                {
                    aSetForceTASignalingActive = aTimer->ApplyConditionAfterHoldoff((aForce10BError || aForceGenericLayerFail), aHoldoffTimerActive, aHoldOffDelay);
                }
                else
                {
                    aSetForceTASignalingActive = true;
                }
                // This is needed for LOFD toggling, which is only relevant for SetForce10BError,
                // which is controlled by the aSetForceTASignalingActive flag (or the normal holdoff timer).
                myHoldoffTimerActive[anIndex] = aHoldoffTimerActive;

                // Now check for internal (alternate) direction       
                bool anAltHoldoffTimerActive = false;
                CFG_HoldOffTimer* aAltTimer = GetCfgIf().GetAltHoldOffTimer(anIndex);
                if (aAltTimer) 
                {
                    aSetAltForceTASignalActive = aAltTimer->ApplyConditionAfterHoldoff(aInjectMaintenance, anAltHoldoffTimerActive, aHoldOffDelay);
                }
                else
                {
                    aSetAltForceTASignalActive = true;
                }
                // This is needed for LinkFailRx or LOF toggling, which is only relevant for aInjectMaintenance,
                // which is controlled by the aSetAltForceTASignalActive flag (or the alternate holdoff timer).
                myAltHoldoffTimerActive[anIndex] = anAltHoldoffTimerActive;

                if (aSetForceTASignalingActive)
                {
                    aAutomaticCfgObject.SetForce10BError(aForce10BError);
                    aAutomaticCfgObject.SetForceGenericLayerFail(aForceGenericLayerFail);
                }
                else
                {
                    aAutomaticCfgObject.SetForce10BError(false);
                    aAutomaticCfgObject.SetForceGenericLayerFail(false);
                }

                if (aSetAltForceTASignalActive)   
                {
                    aAutomaticCfgObject.SetForceClientMgmtFrame(aClientMgmtFrame);
                }
                else
                {
                    aAutomaticCfgObject.SetForceClientMgmtFrame(CT_TEL_GFP_CMGMT_NONE);
                }

            }  // if (aCfgObject.GetEnableMode())
            else
            {
                aAutomaticCfgObject.SetForceClientMgmtFrame(CT_TEL_GFP_CMGMT_NONE);
                aAutomaticCfgObject.SetForce10BError(false);
                aAutomaticCfgObject.SetForceGenericLayerFail(false);
                aAutomaticCfgObject.SetForceIdle(false);
                aAutomaticCfgObject.SetForceLinkFailTx(false);
                aAutomaticCfgObject.SetOneWayGbe(false);
                //aAutomaticCfgObject.SetForceRemoteFault(???)
            }  //  else    -- of if (aCfgObject.GetEnableMode())

        }  // if (aOptCfgRegion)
        else
        {
            aAutomaticCfgObject.SetForceClientMgmtFrame(CT_TEL_GFP_CMGMT_NONE);
            aAutomaticCfgObject.SetForce10BError(false);
            aAutomaticCfgObject.SetForceGenericLayerFail(false);
            aAutomaticCfgObject.SetForceIdle(false);
            aAutomaticCfgObject.SetForceLinkFailTx(false);
            aAutomaticCfgObject.SetOneWayGbe(false);
            //aAutomaticCfgObject.SetForceRemoteFault(???)
        }  //  else    -- of if (aCfgObject.GetEnableMode())
    } // for (uint8 anIndex = 0; anIndex < myNumGfps; anIndex++)

    GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();

    if (aRealTimeDefectsRead)
        myRealTimeDefectReadPasses++;
    else
        myNormalReadPasses++;

    if (aReadAltRealTimeDefects)
        myAltRealTimeDefectReadPasses++;
    else
        myAltNormalReadPasses++;

    if (aDebug)
    {
        // aFirstCfgObject.SetProcessTime(TMBusec_since(aStartTime),  aRealTimeDefectsRead,    myRealTimeDefectReadPasses,    myNormalReadPasses);
        aFirstCfgObject.SetProcessTime(TMBusec_since(aStartTime), aReadAltRealTimeDefects, myAltRealTimeDefectReadPasses, myAltNormalReadPasses);
    }

    return NULL;
}

// check if no xc
bool CFG_GfpAutomaticAction::DoubleCheckDisableExternalErrorSignaling(bool isSrc, bool isDst)
{
    bool aDisableExternalErrorSignalingDoubleCheck = true;
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {
        if(aCardContext->GetCardFamily() == OTNM_FAM)
        {
            if (!isSrc && !isDst)  //no xc
            {
                aDisableExternalErrorSignalingDoubleCheck = false;
            }
    }
    } // if (aCardContext)
    return aDisableExternalErrorSignalingDoubleCheck;
}


