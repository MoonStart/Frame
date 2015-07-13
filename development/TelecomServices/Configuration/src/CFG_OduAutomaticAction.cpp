// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_OduAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_Dispatcher.h>

#include "../CFG_AppIf.h"
#include "../CFG_HoldOffTimer.h"
#include "../CFG_OduAutomatic.h"
#include "../CFG_OptAutomatic.h"
#include "../CFG_Opt.h"
#include "../CFG_Odu.h"

CFG_OduAutomaticAction::CFG_OduAutomaticAction(CFG_AppIf&      theCfgIf,
                                               MON_AppIf*      theIncomingMonApp,
                                               MON_AppIf*      theOtherSideIncomingMonApp,
                                               CFG_AppIf*      theOptCfgApp,
                                               CFG_AppIf*      theOptOtherSideCfgApp,
                                               MON_AppIf*      theIMUXOduMonApp,
                                               MON_AppIf*      theOtherSideOduMonApp,
                                               bool            theIsLineSideFlag,
                                               CT_NumberOfOdus theOdusOnCard,
                                               bool            theCreateGlueFlag): 
    CFG_HwRefreshAction(theCfgIf),
    myIncomingMonApp(theIncomingMonApp),
    myOtherSideIncomingMonApp(theOtherSideIncomingMonApp),
    myOptCfgApp(theOptCfgApp),
    myOptOtherSideCfgApp(theOptOtherSideCfgApp),
    myAllowNoOtherSide(false),
    myIMUXOduMonApp(theIMUXOduMonApp),
    myOtherSideOduMonApp(theOtherSideOduMonApp),
    myOdusOnCard(theOdusOnCard),
    myCreateGlueFlag(theCreateGlueFlag),
    myIsLineSideFlag(theIsLineSideFlag)
{
    GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());

    if (myIncomingMonApp) 
    {
        GetBbAction()->AddInputRegion(myIncomingMonApp->GetDefectsRegion());
        GetBbAction()->AddInputRegion(myIncomingMonApp->GetStatusRegion());
    }

    if (myOtherSideIncomingMonApp) 
    {
        GetBbAction()->AddInputRegion(myOtherSideIncomingMonApp->GetDefectsRegion());
    }

    if (myOptCfgApp) 
    {
        GetBbAction()->AddInputRegion(myOptCfgApp->GetCfgRegion());
    }

    if (myOptOtherSideCfgApp) 
    {
        GetBbAction()->AddInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
    }

    if (myIMUXOduMonApp) 
    {
        GetBbAction()->AddInputRegion(myIMUXOduMonApp->GetDefectsRegion());
    }

    if (myOtherSideOduMonApp) 
    {
        GetBbAction()->AddInputRegion(myOtherSideOduMonApp->GetDefectsRegion());
    }
    
    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_OduAutomaticAction::~CFG_OduAutomaticAction()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());

    if (myIncomingMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myIncomingMonApp->GetDefectsRegion());
        GetBbAction()->RemoveInputRegion(myIncomingMonApp->GetStatusRegion());
    }

    if (myOtherSideIncomingMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myOtherSideIncomingMonApp->GetDefectsRegion());
    }

    if (myOptCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myOptCfgApp->GetCfgRegion());
    }

    if (myOptOtherSideCfgApp) 
    {
        GetBbAction()->RemoveInputRegion(myOptOtherSideCfgApp->GetCfgRegion());
    }

    if (myIMUXOduMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myIMUXOduMonApp->GetDefectsRegion());
    }

    if (myOtherSideOduMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myOtherSideOduMonApp->GetDefectsRegion());
    }
    
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}



FC_Object* CFG_OduAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{
    bool hasChanged = false;

    myAllowNoOtherSide = true;

    // The automatic action would crash if the incoming MON application is NULL. The MON app is mandatory.
    FC_THROW_ERROR_IF(myIncomingMonApp==NULL, FC_RuntimeError, "The Incoming MON APP is NULL");

    MON_OduDefectsRegion*   aIncomingDefectMonRegion = static_cast<MON_OduDefectsRegion*>(myIncomingMonApp->GetDefectsRegion());
    MON_OduStatusRegion*    aIncomingStatusMonRegion = static_cast<MON_OduStatusRegion*>(myIncomingMonApp->GetStatusRegion());
    CFG_OduCfgRegion*       aOduCfgRegion = static_cast<CFG_OduCfgRegion*>(GetCfgIf().GetCfgRegion());
    FC_THROW_ERROR_IF(aIncomingDefectMonRegion==NULL, FC_RuntimeError, "Unable to retrieve MON Defect region");
    FC_THROW_ERROR_IF(aIncomingStatusMonRegion==NULL, FC_RuntimeError, "Unable to retrieve MON Status region");
    FC_THROW_ERROR_IF(aOduCfgRegion==NULL, FC_RuntimeError, "Unable to retrieve CFG region");

    for (uint16 anIndex = 0; anIndex < myOdusOnCard; anIndex++)
    {
        if (anIndex >= aOduCfgRegion->Size())
        {
            break;
        }
        bool aOduTerminating = false;
        bool aForceAIS = false;
        bool aForceLCK = false;
        bool aForceOCI = false;
        bool aForceBDI = false;
        bool aForceInternalAIS = false;
        bool aForceInternalLCK = false;
        bool aForceInternalOCI = false;
        bool aConsiderDefectsForBackwardInd       = false;
        bool aConsiderLockForExternalSignaling    = false;
        bool aConsiderLockForInternalSignaling    = false;
        bool aConsiderDefectsForInternalSignaling = false;
        bool aConsiderOppositeSide                = false;
        bool aConsiderOppositeSideForOCI          = false; 
        bool aLSPActive        = false;
        bool aDisableSignaling = false;

        uint32 aHoldOffDelay = CFG_DEFAULT_HOLDOFF_TIME_IS_ZERO;
        bool   aSetForceTASignalingActive = false;
        bool   aSetAltForceTASignalActive = false;

        CFG_OduAutomatic& aOduAutomaticConfig = static_cast<CFG_OduAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[bbindex_t(anIndex)]);
        CFG_Odu&          aOduConfig          = (*aOduCfgRegion)[bbindex_t(anIndex)];
        // Is this the correct MON region?
        MON_OduDefects&         aIncomingDefectsIf  = (*aIncomingDefectMonRegion)[bbindex_t(anIndex)];
        MON_OduStatus&          aIncomingStatusIf  = (*aIncomingStatusMonRegion)[bbindex_t(anIndex)];

        CFG_AppIf*  aOptCfgApp = NULL;
        if ((myOdusOnCard == NUMBER_OF_DEFAULT_ODUS) && (myCreateGlueFlag == false))
        {
            aOptCfgApp = myOptCfgApp;
        }       
        else  
        {
            // Need to find the correct OPT Config when this is a pooled ODU.
            if (aOduConfig.GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT) 
            {
                // A Pool client is an ODU instance that is related to a facility.  Agent supplies the facility ID
                // Retrieve Opt Layer on the card
                T6100_CardIf*    aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
                if (aCardContext)
                {
                    vector<CT_ODU_ServerID> aPositionList = aOduConfig.GetOduPositionList();
                    if (aPositionList.size() > 0) 
                    {
                        int aFac = int(aPositionList[0].GetPoolInstance());
                        aOptCfgApp = &(aCardContext->GetOptIf().GetCfgPortSideApp((CT_IntfId)aFac));
                    }                                         
                }              
            }  // if (aOduConfig.GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT)
            else if (aOduConfig.GetOduObjectType() == CT_ODU_POOL_MUX) 
            {   
                // A Mux instance is an ODU instance that is related to another Odu instance (in a higher Oduk region).
                // The higher Oduk layer has the information for finding the facilty.  Agent supplies the information
                // needed to retrieve Opt Layer on the card, but only when the Odu type is ODU_WITHIN_CLIENT.
                // This code mux keep looking for higher layer MUX instances to find the ODU_WITHIN_CLIENT instance.
                T6100_CardIf*    aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
                if (aCardContext)
                {
                    T6100_TelecomIf& aOduContext   = aCardContext->GetOduIf();
                    CFG_AppIf*       aNewPoolApp   = NULL;
                    CFG_Region*      aNewCfgRegion = static_cast<CFG_Region*> (GetCfgIf().GetCfgRegion());
                    uint16           aNewPoolIndex = anIndex;

                    for (uint8 aLoopKval = 0; aLoopKval < (uint8(CT_ODU_LayerEnd)); aLoopKval++)
                    {
                        CFG_Odu& aNewOduConfig = static_cast<CFG_Odu&>((*aNewCfgRegion)[bbindex_t(aNewPoolIndex)]);

                        CT_ODU_Identifier       aOduIdentifier  = aNewOduConfig.GetOduIdentifier();
                        vector<CT_ODU_ServerID> aPositionList   = aNewOduConfig.GetOduPositionList();

                        if ((aLoopKval == aOduIdentifier.GetOduKvalue()) && (aPositionList.size() > 0))
                        {
                            // Make sure the type is MUX and the Layer is Odu, which it should be for a MUX.
                            if ((aPositionList[0].GetIdTelecomLayer() == CT_ServerPool_Layer_Odu) &&
                                (aNewOduConfig.GetOduObjectType()     == CT_ODU_POOL_MUX))
                            {
                                // For Odu facility, the base is Port_Side_30 and then look at Kvalue
                                // to get the correct pool  (Odu0 is 30, Odu1 is 31. Odu2 is 32, Odu3 is 33, etc.).
                                uint8 aOduKvalue = aPositionList[0].GetOduKvalue();
                                int   aFac         = int(CT_PORT_SIDE_30) + int(aOduKvalue);
                                // ODU0 and ODUF share the same context.
                                if(aOduKvalue == CT_ODU_LayerF)
                                {
                                    aFac = CT_PORT_SIDE_30;
                                }
                                aNewPoolApp        = &aOduContext.GetCfgPortSideApp((CT_IntfId)aFac);
                                if (aNewPoolApp) 
                                {
                                    // Now use the instance from the PositionList (server ID) to find the correct instance.
                                    aNewCfgRegion = static_cast<CFG_Region*> (aNewPoolApp->GetCfgRegion());
                                    aNewPoolIndex = uint16(aPositionList[0].GetPoolInstance());
                                } // if (aNewPoolApp)
                                
                            }  //  if ((aPositionList[0].GetIdTelecomLayer() == CT_ServerPool_Layer_Odu) &&

                            // If the Layer in the PositionList is Otu, then stop looking for higher layers
                            else if (aPositionList[0].GetIdTelecomLayer() == CT_ServerPool_Layer_Otu) 
                            {
                                break;
                            }  //  if (aPositionList[0].GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)

                            // since CT_ODU_LayerF is defined a bigger number than all other type of ODU
                            // if it happens to be ODUF, then we let the loop go back to ODU2, note that 
                            // ODU2 is the lowest ODUk which is able to contain ODUF
                            if (aLoopKval == CT_ODU_LayerF)
                            {
                                aLoopKval = CT_ODU_Layer1;
                            }
                        }  // if ((aLoopKval == aOduIdentifier.GetOduKvalueEnum()) && (aPositionList.size() > 0))

                    }  //  for (uint8 aLoopKval = 0; aLoopKval < uint8(CT_ODU_LayerEnd); aLoopKval++)
                    
                    // Now we should have the highest ODU Application and it should be a CT_ODU_POOL_ODU_WITHIN_CLIENT type
                    CFG_Odu& aNewOduConfig = static_cast<CFG_Odu&>((*aNewCfgRegion)[bbindex_t(aNewPoolIndex)]);
                    if (aNewOduConfig.GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT) 
                    {
                        vector<CT_ODU_ServerID> aPositionList = aNewOduConfig.GetOduPositionList();
                        if (aPositionList.size() > 0)
                        {
                            int aFac   = int(aPositionList[0].GetPoolInstance());
                            aOptCfgApp = &(aCardContext->GetOptIf().GetCfgPortSideApp((CT_IntfId)aFac));
                        }
                    }  //  if (aNewOduConfig.GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT)

                }  //  if (aCardContext)

            }  //  else if (aOduConfig.GetOduObjectType() == CT_ODU_POOL_MUX)_
        }  // (else of) if (myOdusOnCard == NUMBER_OF_DEFAULT_ODUS) 


        if (aOptCfgApp) 
        {
            CFG_Opt&          aOptConfig     = static_cast<CFG_Opt&>((*aOptCfgApp->GetCfgRegion())[0]);
            CFG_OptAutomatic& aOptAutoConfig = static_cast<CFG_OptAutomatic&>((*aOptCfgApp->GetAutomaticCfgRegion())[0]);

            aLSPActive   |= aOptAutoConfig.GetLineSideProtExists();

            // Get HoldOffDelay in CFG Opt for ALS to use later in the method to hold maintenance signals
            aHoldOffDelay = aOptConfig.GetAlsHoldOffDelay();

            aConsiderLockForExternalSignaling    = (!aOptConfig.GetTerminalLoopBackEnable()) && (!aOptConfig.GetFacilityLoopBackEnable());
            aConsiderLockForInternalSignaling    = (!aOptConfig.GetTerminalLoopBackEnable());
            aConsiderDefectsForInternalSignaling = (!aOptConfig.GetTerminalLoopBackEnable());
            aConsiderDefectsForBackwardInd       = (!aOptConfig.GetTerminalLoopBackEnable());
            

            if (aOptConfig.GetPrbsRxEnable() || aOptConfig.GetPrbsTxEnable())
            {
                aDisableSignaling = true;
            }


            if (myOptOtherSideCfgApp) 
            {        
                CFG_Opt& aOptOtherSideConfig              = static_cast<CFG_Opt&>((*myOptOtherSideCfgApp->GetCfgRegion())[0]); 
                CFG_OptAutomatic& aOptOtherSideAutoConfig = static_cast<CFG_OptAutomatic&>((*myOptOtherSideCfgApp->GetAutomaticCfgRegion())[0]);

                aLSPActive |= aOptOtherSideAutoConfig.GetLineSideProtExists();

                aConsiderOppositeSide = ((!aOptOtherSideConfig.GetTerminalLoopBackEnable()) && 
                                         (aConsiderLockForExternalSignaling));

                if (aOptOtherSideConfig.GetPrbsRxEnable() || aOptOtherSideConfig.GetPrbsTxEnable())
                {
                    aDisableSignaling = true;
                }
            }
            else if (myAllowNoOtherSide)             
            {
                // when there is nothing there, consider opposite side
                aConsiderOppositeSide = aConsiderLockForExternalSignaling;
            }

            // Note: For 4.0.5, forcing ODU-OCI when other side is in defects or locked 
            // is only desired when Maintenance Propagation is off (old way of doing things) 
            // so that the new TlabAIS is not clobbered
            bool aConsiderOppositeSideForOCI = (aConsiderOppositeSide && (aOptConfig.GetMaintPropMode() == CT_TEL_MAINT_PROP_OFF));
        }  // if (aOptCfgApp) 
           // 
        else
        {
            // When there is not an Opt object (when the ODU is not within the Client),
            // then set the consider flags to true.
            // Note: there should not be an opposite side.
            // ?? should I put a condition around this (i.e., only when odu pools ??
            if ((aOduConfig.GetOduObjectType() == CT_ODU_POOL_CLIENT_INSIDE_ODU) || 
                (aOduConfig.GetOduObjectType() == CT_ODU_POOL_MUX)) 
            {
                aConsiderLockForExternalSignaling    = true;
                aConsiderLockForInternalSignaling    = true;
                aConsiderDefectsForInternalSignaling = true;
                aConsiderDefectsForBackwardInd       = true;
            }

        }  // else part of - if (aOptCfgApp)


        // Determine if this is a one-way cross connect with the direction of traffic being
        // toward the interior of the card (to the other side of the card).  In this case, 
        // we will supress backward indicators.
        bool aSuppressBackwardInd = (aIncomingDefectsIf.IsConnectedAsDst() && (!aIncomingDefectsIf.IsConnectedAsSrc()));

        // For the Client Inside Odu case, the framer is flipped and all defects and maintenance signaling is in the opposite direction.
        // Therefore, suppress when connected as a source and not as a destination 
        if (aOduConfig.GetOduObjectType() == CT_ODU_POOL_CLIENT_INSIDE_ODU) 
        {
            aSuppressBackwardInd = (!aIncomingDefectsIf.IsConnectedAsDst() && aIncomingDefectsIf.IsConnectedAsSrc());    
        }


        //Set 1 Way Drop XC.
        bool aDrop = (aIncomingDefectsIf.IsConnectedAsDst() && (!aIncomingDefectsIf.IsConnectedAsSrc()));

        //Set 1 Way Add XC
        bool aAdd  = (!aIncomingDefectsIf.IsConnectedAsDst() && (aIncomingDefectsIf.IsConnectedAsSrc()));


        // In most cases, the card is Odu Terminating, but we always check now.
        aOduTerminating =  aOduConfig.GetIsOduTerm();

        // New for 3.3 when adding Port Side Otu/Odu.  
        // There is different behavior depending on whether the cards is Odu terminating
        // or non-Odu terminating.  Most cases and all previous configuration that did 
        // not allow Port Side Otu/Odu are Odu terminating.  The code for that is below. 
        if (!aOduTerminating) 
        {
            // Exectute Non-Odu Terminating code

            // First, Signaling based on defects and/or lock from its own (incoming) facility       
            // Check for forcing ODU-LCK if:
            aForceLCK         |= (aIncomingDefectsIf.IsLayerLocked() || aIncomingDefectsIf.GetLockBitMask()          ||
                                  aIncomingDefectsIf.IsOtuLayerLocked(aIncomingDefectsIf.GetInternalLockBitMask()) ) && aConsiderLockForExternalSignaling;
            aForceInternalLCK |= (aIncomingDefectsIf.IsLayerLocked() || aIncomingDefectsIf.GetInternalLockBitMask()) && aConsiderLockForInternalSignaling;           

            if (aConsiderDefectsForInternalSignaling) 
            {
                // Note 1: Mon now handles how to fail the layer based on ODU Non-Terminating
                // Note 2: For ODU Non-Terminating, BDI is not sent.
                CT_ODU_ServerID myServerId = aOduConfig.GetServerID();
                // if the ODU is under the OTU or OCH-P, and only PLM exist, no maintenace signal inserted.
                if (myServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu && aIncomingDefectsIf.IsOnlyPlmFailLayer())
                {
                    aForceInternalAIS = false;
                }
                else
                {
                    aForceInternalAIS |= aIncomingDefectsIf.IsLayerForMaintSigInDefects();
                }
            }  // if (aConsiderDefectsForInternalSignaling)

            // Second, Signaling based on defects and/lock from the other side.
            if (aConsiderOppositeSide)
            {
                aForceLCK |= aIncomingDefectsIf.IsLayerInternalLocked();
                aForceAIS |= aIncomingDefectsIf.IsLayerInternalForMaintSigInDefects();

                if (myOtherSideOduMonApp) 
                {
                    MON_Defects& aOtherSideOduDefects = static_cast<MON_Defects&>((*myOtherSideOduMonApp->GetDefectsRegion())[0]);

                    aForceLCK |= aOtherSideOduDefects.IsLayerLocked();
                    // If we have the ODU layer defects (which should now be required for cards
                    // that can have an ODU non terminating client), then check that layer.
                    // If not, check the layer we have, which is probably the Rs layer.
                    aForceAIS |= aOtherSideOduDefects.IsLayerForMaintSigInDefects();
                }
            }  //  if (aConsiderOppositeSide && myOtherSideOduMonApp)
        }  // if (!aOduTerminating) 


        // Exectute Odu Terminating code, which was originally meant 
        // for the Line Side ONLY (OCH-P)
        // Note: aOduTerminating and myLineSideFlag are both default to true
        // so that other cards that do not have port side Otu/Odu will behave
        // as the had previously (which was Odu terminating).
        else if (aOduTerminating && myIsLineSideFlag) 
        {

            // Generally,  Force ODU-BDI on ODU layer failure
            // Since it was too difficult to determine when to force BDI from
            // the currect methods (i.e., PLM fails the layer, but does not force BDI;
            // whereas, TIM (noAIS) does not fail the layer, but does force BDI),
            // it was decided to have a new method in MON to determine which defects
            // force BDI.  Also, LayerLocked will now force BDI
            aForceBDI         |= ( (aIncomingDefectsIf.IsBDIForcedForDefectsForMaintSig() && aConsiderDefectsForBackwardInd)    || 
                                   (aIncomingDefectsIf.IsLayerLocked()         && aConsiderLockForExternalSignaling) );

            aForceInternalAIS |= aIncomingDefectsIf.IsLayerForMaintSigInDefects() && aConsiderDefectsForInternalSignaling;
 
            // Automatically force ODU-LCK if:
            // 1- Current side is locked and not in facility loopback and not in terminal loopback
            aForceLCK         |= (aIncomingDefectsIf.IsLayerLocked() || aIncomingDefectsIf.GetLockBitMask()) && aConsiderLockForExternalSignaling;
            aForceInternalAIS |= (aIncomingDefectsIf.IsLayerLocked() || aIncomingDefectsIf.GetLockBitMask()) && aConsiderLockForInternalSignaling;

            // Automatically force AIS if the internal AIS defect is present 
            // Should be used for multi-port transponders.
            aForceAIS         |= aIncomingDefectsIf.IsLayerInternalInDefects() && aConsiderLockForExternalSignaling;

            // Note: In 7.1, the non standard OCI is being removed on some cards and 
            // the maintenance signaling sent out will be based on Agent configuration.  
            if (myOtherSideIncomingMonApp)
            {
                MON_Defects& aOtherSideIncomingDefectsIf = static_cast<MON_Defects&>((*myOtherSideIncomingMonApp->GetDefectsRegion())[0]); 
                // Force maintenance signaling if:
                // 1- Other side not in terminal loopback and current side not in facility or terminal loopback
                // 2- and the other side is failed or locked
                //  
                // Note: the difference on sending AIS and OCI is the check for MAINT_PROP 
                // (see notes above for setting aConsiderOppositeSideForOCI)

                // Now decide what to send
                if (aOduConfig.GetTerminatedIndication() == CT_ODU_INDICATION_AIS)
                {
                    aForceAIS |= (aOtherSideIncomingDefectsIf.IsLayerForMaintSigInDefects() || aOtherSideIncomingDefectsIf.IsLayerLocked()) && aConsiderOppositeSide;
                }
                else if (aOduConfig.GetTerminatedIndication() == CT_ODU_INDICATION_OCI)
                {
                    aForceOCI |= (aOtherSideIncomingDefectsIf.IsLayerForMaintSigInDefects() || aOtherSideIncomingDefectsIf.IsLayerLocked()) && aConsiderOppositeSideForOCI;
                }
                else
                {
                    // Set these to false since for single port transponders, 
                    // they should only be looking at the other side (not internal)
                    aForceAIS = false;
                    aForceOCI = false;
                }
            }
        }  // else if (aOduTerminating && myIsLineSideFlag) 


        //If line side protection is configured, add a line side protection holdoff value
        //to the configured timer to give enough time for the protection switch to happen prior
        //to any action by CFG.
        if (aLSPActive)
        {
            aHoldOffDelay = aHoldOffDelay + LINE_SIDE_PROTECTION_HOLDOFF;
        }
        // For Traffic Affecting Maintenance Signlaing only, use ApplyConditionAfterHoldoff 
        // method to check if the Condition found should be applied based on the HoldOff Timer (Delay)
        // *** If internal OCI or Internal LCK are added, make sure this method is updated
        bool aHoldoffTimerActive = false;
        CFG_HoldOffTimer* aTimer = GetCfgIf().GetHoldOffTimer(anIndex);
        if (aTimer) 
        {
            aSetForceTASignalingActive = aTimer->ApplyConditionAfterHoldoff((aForceLCK || aForceOCI || aForceAIS), aHoldoffTimerActive, aHoldOffDelay);
        }
        else
        {
            aSetForceTASignalingActive = true;
        }

        // Now check for internal (alternate) direction       
        CFG_HoldOffTimer* aAltTimer = GetCfgIf().GetAltHoldOffTimer(anIndex);
        if (aAltTimer) 
        {
            aSetAltForceTASignalActive = aAltTimer->ApplyConditionAfterHoldoff((aForceInternalLCK || aForceInternalOCI || aForceInternalAIS), aHoldoffTimerActive, aHoldOffDelay);
        }
        else
        {
            aSetAltForceTASignalActive = true;
        }

        // If ApplyCondition method is is false, do not force maintenance signaling
        if (!aSetForceTASignalingActive)   
        {
            aForceLCK = false;
            aForceOCI = false;
            aForceAIS = false;

        }
        if (!aSetAltForceTASignalActive)   
        {

            aForceInternalLCK = false;
            aForceInternalOCI = false;
            aForceInternalAIS = false;
        }

        // ODU PRBS or NULL Signal enable will impact the ODU signaling.
        if ( aOduConfig.GetPrbsRxEnable() || 
             aOduConfig.GetPrbsTxEnable() || 
             aOduConfig.GetNULLSignalEnable() )
        { 
            uint32 aUpLayerFailCount = 0L, aUpLayerLockCount = 0L; 
            bool aUpLayerFailState = false, aUpLayerLockState = false;  
            uint32 aIntUpLayerFailCount = 0L, aIntUpLayerLockCount = 0L; 
            bool aIntUpLayerFailState = false, aIntUpLayerLockState = false; 
                                                   
            aIncomingDefectsIf.GetDefectStatus(CT_TEL_ODU_UPPER_LAYER_FAIL_FOR_MS_TA_DEFECT, &aUpLayerFailCount, &aUpLayerFailState);
            aIncomingDefectsIf.GetDefectStatus(CT_TEL_ODU_UPPER_LAYER_LOCK, &aUpLayerLockCount, &aUpLayerLockState);

            aIncomingDefectsIf.GetDefectStatus(CT_TEL_ODU_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, &aIntUpLayerFailCount, &aIntUpLayerFailState);
            aIncomingDefectsIf.GetDefectStatus(CT_TEL_ODU_INTERNAL_LOCK, &aIntUpLayerLockCount, &aIntUpLayerLockState);

            // When there are no upper layer defects, disable all maintenance signaling 
            if ( (!aUpLayerFailState)    && (!aUpLayerLockState ) && (!aIntUpLayerFailState) && (!aIntUpLayerLockState ) )
            {
                aDisableSignaling = true;
            }
            // Always disable forcing lock from the OOS that was required to enable the PRBS or NULL
            else
            {
                aForceLCK = false;
                aForceInternalLCK = false;
            }
        }

        // Also, if any PRBS BER Testing is turned on, don't force any signaling except the uplayer is in defect or locked, see line 370
        if (aDisableSignaling)   
        {
            aForceBDI = false;
            aForceLCK = false;
            aForceOCI = false;
            aForceAIS = false;
            aForceInternalLCK = false;
            aForceInternalOCI = false;
            aForceInternalAIS = false;
        } 
      
    
        hasChanged |= aOduAutomaticConfig.SetForceBDI(aForceBDI);
        hasChanged |= aOduAutomaticConfig.SetForceLCK(aForceLCK);
        hasChanged |= aOduAutomaticConfig.SetForceOCI(aForceOCI);
        hasChanged |= aOduAutomaticConfig.SetForceAIS(aForceAIS);

        hasChanged |= aOduAutomaticConfig.SetForceInternalLCK(aForceInternalLCK);
        hasChanged |= aOduAutomaticConfig.SetForceInternalOCI(aForceInternalOCI);
        hasChanged |= aOduAutomaticConfig.SetForceInternalAIS(aForceInternalAIS);

        hasChanged |= aOduAutomaticConfig.SetSuppressBackwardInd(aSuppressBackwardInd);       

        hasChanged |= aOduAutomaticConfig.SetDrop(aDrop);
        hasChanged |= aOduAutomaticConfig.SetAdd(aAdd);


        if (myIMUXOduMonApp) 
        { 
            //
            // If there is a IMUXOduMonApp, then there is special defect propagation for
            // the SMTM where we want to force internal ODU AIS in certain cases:
            // Force internal ODU AIS if:
            // 1- 
            // 2- 
            // 3-
              
            // First, check aIncomingDefectsIf (from ODU of its own application, the LINE_DWDM_OCHP)
            // for TIM-OTU (which will cause the ODU layer to have defects (upper layer)
            aForceInternalAIS |= aIncomingDefectsIf.IsLayerForMaintSigInDefects();

            // Now check if later is locked
            aForceInternalAIS |= aIncomingDefectsIf.IsLayerLocked();

            // Now check myIMUXOduMonApp (from IDU od the IMUX application)
            // for LOCK
            MON_Defects& aIMUXOduDefects = static_cast<MON_Defects&>((*myIMUXOduMonApp->GetDefectsRegion())[0]); 
            aForceInternalAIS |= (aIMUXOduDefects.IsLayerLocked());

            hasChanged |= aOduAutomaticConfig.SetForceInternalAIS(aForceInternalAIS);
        }

        if ( aOduConfig.GetTribAutoFallBack() && (aIncomingStatusIf.GetRxPayloadType() == CT_TEL_PSI_ODU_MULTI_STRUCT) ) 
        {
            hasChanged |= aOduAutomaticConfig.SetTribSize(CT_TEL_TS_2G5);
            hasChanged |= aOduAutomaticConfig.SetTxPayloadType(CT_TEL_PSI_ODU_MULTI_STRUCT);
        }
        else
        {
            hasChanged |= aOduAutomaticConfig.SetTribSize(CT_TEL_TS_UNKNOWN);
            hasChanged |= aOduAutomaticConfig.SetTxPayloadType(CT_TEL_PSI_UNAVAILABLE);
        }
    } // for (uint32 anIndex = 0; anIndex < myOdusOnCard; anIndex++)

 
    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }

    return NULL;
}


