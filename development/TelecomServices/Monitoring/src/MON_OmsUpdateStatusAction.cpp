// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_PipeIf.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <ErrorService/FC_Error.h>
#include <CSM/CSM_CardStatus.h>
#include <CSM/CSM_AppIf.h>
#include "../MON_OmsUpdateStatusAction.h"
#include <Monitoring/MON_OmsDefects.h>
#include <Monitoring/MON_OmsStatus.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Region.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include "CsPii/CSPII_ShelfIF.h"

#define MON_OPOVLD_THRESHOLD_MOAM_MIAM    850
#define MON_OPOVLD_THRESHOLD_RIAM         0
#define MON_OPOVLD_THRESHOLD_LIAM         900
#define MON_OPOVLD_THRESHOLD_LOAM         850
#define MON_OPOVLD_THRESHOLD_LRAM         50
#define MON_OPOVLD_THRESHOLD_LIAME        1150
#define MON_OPOVLD_THRESHOLD_LOAME        400
#define MON_OPOVLD_THRESHOLD_LRAME        350
#define MON_OPOVLD_THRESHOLD_ELRAME      -750
#define MON_OPOVLD_THRESHOLD_LOAME88      650
#define MON_OPOVLD_THRESHOLD_LIAME88      2050
#define MON_OPOVLD_THRESHOLD_LRAME88      650
#define MON_OPOVLD_THRESHOLD_ELRAME88    -250

#define MON_OPOVLD_THRESHOLD_OLAIR        1690
#define MON_OPOVLD_THRESHOLD_CCMIR        1690
#define MON_OPOVLD_THRESHOLD_OLAER       -810
#define MON_OPOVLD_THRESHOLD_CCMER       -810
#define MON_OPOVLD_THRESHOLD_CCM88IR      2000
#define MON_OPOVLD_THRESHOLD_CCM88LR      600
#define MON_OPOVLD_THRESHOLD_CCM88ER     -500
// In 7.1, start reading the thresholds from TSPII because the values 
// are different depending on the direction. New cards should follow this model
// and then no MON changes should be required for OPOVLD or AOPE 
// (unless there is a new family).
//#define MON_OPOVLD_THRESHOLD_OLALR        300
//#define MON_OPOVLD_THRESHOLD_CCMLR        300

#define MON_OPOVLD_THRESHOLD_OTSM         2000

#define MON_OPOVLD_THRESHOLD_OTHERS       500


MON_OmsUpdateStatusAction::MON_OmsUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_PipeRegion& thePipePiiRegion,
                                                     TSPII_OpticalRegion* thePump1Region,
                                                     TSPII_OpticalRegion* thePump2Region,
                                                     bool theHasAmplifierFlag):

    MON_UpdateStatusAction(theMonIf,NULL),
    myPipePiiRegion(thePipePiiRegion),
    myPump1Region(thePump1Region),
    myPump2Region(thePump2Region),
    myHasAmplifierFlag(theHasAmplifierFlag),
    myPiiOmsLosCount(0),
    myPiiOmsAltLosCount(0),
    myPiiOmsAltTwoLosCount(0),
    myPiiOmsAltThreeLosCount(0),
    myPiiOmsOutputPowerLimitedCount(0)
{
    GetBbAction()->AddInputRegion(&myPipePiiRegion);
    if(myPump1Region) GetBbAction()->AddInputRegion(myPump1Region);
    if(myPump2Region) GetBbAction()->AddInputRegion(myPump2Region);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(),false);

}

MON_OmsUpdateStatusAction::~MON_OmsUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myPipePiiRegion);
    if(myPump1Region) GetBbAction()->RemoveInputRegion(myPump1Region);
    if(myPump2Region) GetBbAction()->RemoveInputRegion(myPump2Region);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());

}

FC_Object* MON_OmsUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}

FC_Object* MON_OmsUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    MON_OmsDefects& aOmsDefects   = static_cast<MON_OmsDefects&>((*GetMonIf().GetDefectsRegion())[0]);
    MON_OmsStatus&  aOmsStatus    = static_cast<MON_OmsStatus&>((*GetMonIf().GetStatusRegion())[0]);
    TSPII_PipeIf& aPipePii        = myPipePiiRegion[0];

    T6100_CardIf& aCardIf = static_cast<T6100_CardIf&> (*GetMonIf().GetContext().GetParent());
    T6100_SlotIf& aSlotIf = static_cast<T6100_SlotIf&> (*aCardIf.GetParent());
    CT_PartNumber aPartNumber;
    CSPII_ShelfIF::GetInstance()->GetPartNumber(aSlotIf.GetSlotId(), &aPartNumber);

    CSM_CardStatusRegion& aCardStatusRegion = aSlotIf.GetCsmApp().GetCardStatusRegion();
    CSM_CardStatus& aCardStatus = aCardStatusRegion[0];
    CT_TEL_mBm aOpovldThreshold = CT_TEL_POWER_UNAVAILABLE;
    // Newly defined CT_TEL_DEFAULT_AOPE_THRESHOLD is set to 999900, which is so high 
    // that it will turn off the defect.  
    CT_TEL_mBm maxAggregateOutputPower = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    bool hasDefectsChanged = false;
    bool hasStatusChanged = false;

    // reset states
    bool aOMSLosState=false;
    bool aOMSLosEvent=false;
    bool aOMSAprState=false;
    bool aOMSAprEvent=false;
    bool aOMSAltLosState=false;
    bool aOMSAltLosEvent=false;
    bool aOMSAltTwoLosState=false;
    bool aOMSAltTwoLosEvent=false;
    bool aOMSAltThreeLosState=false;
    bool aOMSAltThreeLosEvent=false;
    bool aOMSLosAfterAmpliState=false;
    bool aOMSLosAfterAmpliEvent=false;
    bool aOMSOutputPowerLimitedState=false;
    bool aOMSOutputPowerLimitedEvent=false;
    bool aOMSOpovldState=false;
    bool aOMSOpovldEvent=false;
    bool aOMSAopeState=false;
    bool aOMSAopeEvent=false;
    //--------------------------------------------------------------
    try // for motherboard
    {

        //--------------------------------------------------------------
        // DEFECTS
        // Read current defects

        // Assume that there is always two LOS values
        // GetLOS(2), etc is below because it is only available for certain cards.
        uint32 aNewOmsLosInCount = aPipePii.GetLOS();
        uint32 aNewOmsAltLosCount = aPipePii.GetLOS(1);
        uint32 aNewOmsOutputPowerLimitedCount = aPipePii.GetOutputPowerLimited();
        //uint32 aOpovldThresholdAdjustment = aPipePii.GetOpticalOverloadThreshold();

        // OMS-LOS state and count update
        if(myPiiOmsLosCount != aNewOmsLosInCount)
        {
            aOMSLosEvent = true;
        }
        if(aNewOmsLosInCount%2 != 0)
        {
            aOMSLosState = true;
        }

        // OSC-LOS Port to Line state and count update
        if(myPiiOmsAltLosCount != aNewOmsAltLosCount)
        {
            aOMSAltLosEvent = true;
        }
        if(aNewOmsAltLosCount%2 != 0)
        {
            aOMSAltLosState = true;
        }

        // Output Power Limited state and count update
        if(myPiiOmsOutputPowerLimitedCount != aNewOmsOutputPowerLimitedCount)
        {
            aOMSOutputPowerLimitedEvent = true;
        }
        if(aNewOmsOutputPowerLimitedCount%2 != 0)
        {
            aOMSOutputPowerLimitedState = true;
        }


        uint32 aNumberofLOS = aPipePii.GetNumberOfLOS();
        //For more LOS values, check to make sure they are there.
        // 
        uint32 aNewOmsAltTwoLosCount = 0;
        if (aNumberofLOS >= 3) 
        {
            aNewOmsAltTwoLosCount = aPipePii.GetLOS(2);
        }

        uint32 aNewOmsAltThreeLosCount = 0;
        if (aNumberofLOS >= 4) 
        {
            aNewOmsAltThreeLosCount = aPipePii.GetLOS(3);
        }

        // Note: will be needed when new AltTwo defect is added
        // OMS-LOS state and count update
        if(myPiiOmsAltTwoLosCount != aNewOmsAltTwoLosCount)
        {
            aOMSAltTwoLosEvent = true;
        }
        if(aNewOmsAltTwoLosCount%2 != 0)
        {
            aOMSAltTwoLosState = true;
        }
            

        if(myPiiOmsAltThreeLosCount != aNewOmsAltThreeLosCount)
        {
            aOMSAltThreeLosEvent = true;
        }
        if(aNewOmsAltThreeLosCount%2 != 0)
        {
            aOMSAltThreeLosState = true;
        }
        myPiiOmsAltTwoLosCount = aNewOmsAltTwoLosCount;
        myPiiOmsAltThreeLosCount = aNewOmsAltThreeLosCount;


        //OMS-APR state and count update
        bool Pump1Enable = true;
        bool Pump2Enable = true;

        // this block of code looks incorrect, but it isn't. The assumption
        // is that if a module does have a pump2, pump1 will always be present
        // and correctly indicate IsDefault() state for both pumps.
        if (myPump1Region)
        {
            if(!(*myPump1Region)[0].IsDefault())
                Pump1Enable = (*myPump1Region)[0].GetLaserState();
            if(myPump2Region && !(*myPump1Region)[0].IsDefault())
                Pump2Enable = (*myPump2Region)[0].GetLaserState();
        }

        if((!Pump1Enable && !Pump2Enable) || aOMSOutputPowerLimitedState)
        {
            aOMSAprState = true;
            aOMSAprEvent = false;
        }

        // OMS-LOS After Ampli state and count update
        // Added the AltTwoLosState to the equation since it is available
        // for some cards.
        if(aOMSLosState || aOMSAltTwoLosState || (!Pump1Enable && !Pump2Enable))
        {
            aOMSLosAfterAmpliState = true;
            aOMSLosAfterAmpliEvent = false;
        }


        //Set the OPOVLD and AOPE thresholds based on type of Amplifier
        //Note: Since LIAM and LRAM have two pipes and only one has amplifier,
        //use the myHasAmplifierFlag to determine the correct direction
        //(see CommonPlatforms/TelecomServices/Monitoring/src/MON_OmsSubApplication.cpp)
        //
        //Note 2: Now that both OPOVLD and AOPE thresholds are different on some cards 
        //based on the direction of the pipe, MON will read TSPII for the thresholds.
        //This is because MON does not have the concept of the pipes direction.
        //Going forward, the recommendation is to read it from TSPII.  For older cards, 
        //MON will set the thresholds.

        CT_CardFamily theFam = aCardIf.GetCardFamily();
        CT_CardType theCard = aCardStatus.GetCardType();
        CT_SubCardType theSubCard = aPartNumber.GetSubCardType();

        if((theFam == IAM_FAM) || (theFam == OAM_FAM)  ||
           (theFam == CCM_FAM) || (theFam == CADM_FAM) ||
           (theFam == LIAM_FAM && myHasAmplifierFlag))
        {
            //Retrieve the card type from CSM
            if(theCard == MIAM || theCard == MOAM)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_MOAM_MIAM;
            }
            else if(theCard == RIAM)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_RIAM;
            }
            else if(theCard == LIAM)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_LIAM;
            }
            else if(theCard == LOAM)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_LOAM;
            }
            else if(theCard == LRAM)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_LRAM;
            }
            else if(theCard == LIAME)
            {
                if (theSubCard == NUM_CHANNELS_88) 
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_LIAME88;
                    maxAggregateOutputPower = aPipePii.GetAopeThreshold();
                }
                else
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_LIAME;
                    maxAggregateOutputPower = CT_TEL_MAX_POWER_LIAME_FAM;
                }

            }
            else if(theCard == LOAME)
            {
                if (theSubCard == NUM_CHANNELS_88)
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_LOAME88;
                    //maxAggregateOutputPower = CT_TEL_MAX_POWER_LOAME88;
                    maxAggregateOutputPower = aPipePii.GetAopeThreshold();
                }
                else
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_LOAME;
                    maxAggregateOutputPower = CT_TEL_MAX_POWER_LOAME;
                }
            }
            else if(theCard == LRAME)
            {
                if (theSubCard == NUM_CHANNELS_88) 
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_LRAME88;
                    maxAggregateOutputPower = aPipePii.GetAopeThreshold();
                }
                else
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_LRAME;
                    maxAggregateOutputPower = CT_TEL_MAX_POWER_LIAME_FAM;
                }
            }
            else if(theCard == ELRAME)
            {
                if (theSubCard == NUM_CHANNELS_88) 
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_ELRAME88;
                    maxAggregateOutputPower = aPipePii.GetAopeThreshold();
                }
                else
                {
                    aOpovldThreshold = MON_OPOVLD_THRESHOLD_ELRAME;
                    maxAggregateOutputPower = CT_TEL_MAX_POWER_LIAME_FAM;
                }
            }
            else if(theCard == OLAIR)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_OLAIR;
                maxAggregateOutputPower = CT_TEL_MAX_POWER_CCM_FAM;
            }
            else if(theCard == OLALR)
            {
                aOpovldThreshold = aPipePii.GetOpticalOverloadThreshold();
                maxAggregateOutputPower = CT_TEL_MAX_POWER_CCM_FAM;
            }
            else if(theCard == OLAER)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_OLAER;
                maxAggregateOutputPower = CT_TEL_MAX_POWER_CCM_FAM;
            }
            
            else if(theCard == CCMIR)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_CCMIR;
                maxAggregateOutputPower = CT_TEL_MAX_POWER_CCM_FAM;
            }
            else if(theCard == CCMLR)
            {
                aOpovldThreshold = aPipePii.GetOpticalOverloadThreshold();
                maxAggregateOutputPower = CT_TEL_MAX_POWER_CCM_FAM;
            }
            else if(theCard == CCMER)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_CCMER;
                maxAggregateOutputPower = CT_TEL_MAX_POWER_CCM_FAM;
            }           
            else if(theCard == CCM88IR)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_CCM88IR;
            }
            else if(theCard == CCM88LR)
            {
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_CCM88LR;
            }
            else if(theCard == CCM88ER)
            {                                              
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_CCM88ER;
            }
            else if(theCard == OTSM)
            {                                              
                aOpovldThreshold = MON_OPOVLD_THRESHOLD_OTSM;
            }
            else
            {
                // Newer cards should fall into here and always get thresholds from TSPII
                // First few are OADMF8, DXOADM, and OADM88 (+8D)
                aOpovldThreshold = aPipePii.GetOpticalOverloadThreshold();
                maxAggregateOutputPower = aPipePii.GetAopeThreshold();
            }

            // This code removed in 7.1 so that MON can get the real OPOVLD threshold 
            // from TSPII for certain cards
            //Apply Adjustment TSPII provided, there should only be a value in this for CCM-LR and OLA-LR
            //aOpovldThreshold += aOpovldThresholdAdjustment;
        }
        else
        {
            aOpovldThreshold = CT_TEL_POWER_UNAVAILABLE;
        }

        //OMS-OPOVLD state update (NOTE: Only applicable on AMPLIFIERS)
        if(aOpovldThreshold != CT_TEL_POWER_UNAVAILABLE && aPipePii.GetInputPower() > aOpovldThreshold)
        {
            aOMSOpovldState = true;
            aOMSOpovldEvent = false;
        }

        // Note on AOPE (repeated from above - where maxAggregateOutputPower was set).  
        // For some new cards, the AOPE threshold will be read from TSPII
        // because there will be certain cases that the threshold will be different 
        // based on direction and this action does not have that concept.  For new cards,
        // the recommendation is to read it from TSPII.  For older cards, this might be confusing
        // because TSPII will show a bogus value that MON will ignore.  
        // If this really makes you angry, there is a suggestion box.
        //OMS-AOPE state and count update
        if(aPipePii.GetOutputPower() > maxAggregateOutputPower)
        {
            aOMSAopeState = true;
            aOMSAopeEvent = false;
        }


        // Update local defect counts
        myPiiOmsLosCount = aNewOmsLosInCount;
        myPiiOmsAltLosCount = aNewOmsAltLosCount;
        myPiiOmsOutputPowerLimitedCount = aNewOmsOutputPowerLimitedCount;

        // Update actual defect
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_LOS_DEFECT, aOMSLosState, aOMSLosEvent);
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_APR_DEFECT, aOMSAprState, aOMSAprEvent);
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_ALT_LOS_DEFECT, aOMSAltLosState, aOMSAltLosEvent);
        // Note: will be needed when new AltTwo defect is added
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_ALT_TWO_LOS_DEFECT, aOMSAltTwoLosState, aOMSAltTwoLosEvent);
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_ALT_THREE_LOS_DEFECT, aOMSAltThreeLosState, aOMSAltThreeLosEvent);
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_LOS_AFTER_AMPLI_DEFECT, aOMSLosAfterAmpliState, aOMSLosAfterAmpliEvent);
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_OUTPUT_POWER_LIMITED_DEFECT, aOMSOutputPowerLimitedState, aOMSOutputPowerLimitedEvent);
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_OPOVLD_DEFECT, aOMSOpovldState, aOMSOpovldEvent);
        hasDefectsChanged |= aOmsDefects.SetDefectStatus(CT_TEL_OMS_AOPE_DEFECT, aOMSAopeState, aOMSAopeEvent);
        hasDefectsChanged |= aOmsDefects.Validate();
        if (hasDefectsChanged)
            GetMonIf().GetDefectsRegion()->IncModificationCounter();

        //--------------------------------------------------------------
        // STATUS
        // Read current status

        // OMS powers
        hasStatusChanged |= aOmsStatus.SetOmsInputPower(aPipePii.GetInputPower());
        hasStatusChanged |= aOmsStatus.SetOmsAlternatePower(aPipePii.GetAlternatePower());
        hasStatusChanged |= aOmsStatus.SetDcmInputPower(aPipePii.GetDcmInputPower());
        hasStatusChanged |= aOmsStatus.SetDcmOutputPower(aPipePii.GetDcmOutputPower());
        hasStatusChanged |= aOmsStatus.SetActualGain(aPipePii.GetActualGain());
        hasStatusChanged |= aOmsStatus.SetConfiguredGain(aPipePii.GetGain());
        hasStatusChanged |= aOmsStatus.SetGainTilt(aPipePii.GetGainTilt());
        hasStatusChanged |= aOmsStatus.SetMinGain(aPipePii.GetMinGain());
        hasStatusChanged |= aOmsStatus.SetMaxGain(aPipePii.GetMaxGain());
        hasStatusChanged |= aOmsStatus.SetActualGroupEvoa(aPipePii.GetActualGroupEvoa());
        hasStatusChanged |= aOmsStatus.SetConfiguredGroupEvoa(aPipePii.GetGroupEvoa());

        // Store the OpovldThreshold, this includes the adjustment (if any) TSPII provide
        hasStatusChanged |= aOmsStatus.SetOpovldThreshold(aOpovldThreshold);
        // Store the AOPE Threshold, this includes the adjustment (if any) TSPII provide
        hasStatusChanged |= aOmsStatus.SetAopeThreshold(maxAggregateOutputPower);

        //Get output power
        //NOTE: Output power is not reliable on MIAM, RIAM and MOAM so retrieve it using the gain and the input power.
        //      Do the same for LIAM, LRAM, and LOAM, but only in the L2P direction for the LIAM and LRAM.
        //      For the LIAM and LRAM, use the myHasAmplifierFlag to determine the correct direction
        //      (see CommonPlatforms/TelecomServices/Monitoring/src/MON_OmsSubApplication.cpp)
        //      For now, CCM card will get the value based on TSPII in both directions
        // NOTE 2: MR 84673 requests enhanced amplifiers ( LIAME, LRAME, and ELRAME )
        // always read output power from TSPII.  I was told it's reliable.
        if(((theCard  == MIAM)  ||
            (theCard  == RIAM)  ||
            (theCard  == MOAM)  ||
            ((theCard == LIAM)  && myHasAmplifierFlag) ||
            ((theCard == LRAM)  && myHasAmplifierFlag) ||
            (theCard  == LOAME) ||
            ((theCard == OLAIR) && myHasAmplifierFlag) ||
            ((theCard == OLALR) && myHasAmplifierFlag) ||
            ((theCard == OLAER) && myHasAmplifierFlag) ||
            (theCard  == LOAM)  )
           && !aOMSAprState)
        {
            hasStatusChanged |= aOmsStatus.SetOmsOutputPower(aPipePii.GetInputPower() + aPipePii.GetGain());
        }
        else
        {
            hasStatusChanged |= aOmsStatus.SetOmsOutputPower(aPipePii.GetOutputPower());
        }

        // if OMS-LOS, indicate that output power is probably not valid
        if (aOMSLosState || aOMSLosAfterAmpliState)
        {
            hasStatusChanged |= aOmsStatus.Invalidate();
        }
        else
        {
            //Validate object
            hasStatusChanged |= aOmsStatus.Validate();
        }
        // Always Validate PM 
        hasStatusChanged |= aOmsStatus.ForPmValidate();

        if (hasStatusChanged)
            GetMonIf().GetStatusRegion()->IncModificationCounter();

    }
    catch (FC_HWError&)
    {
        hasDefectsChanged |= aOmsDefects.Invalidate();
        hasStatusChanged  |= aOmsStatus.Invalidate();
        if (hasDefectsChanged)
            GetMonIf().GetDefectsRegion()->IncModificationCounter();
        if (hasStatusChanged)
            GetMonIf().GetStatusRegion()->IncModificationCounter();
    }

    return NULL;
}

