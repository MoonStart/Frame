// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "Monitoring/MON_OchUpdateStatusAction.h"
#include "Monitoring/MON_OmsStatus.h"
#include "Monitoring/MON_OchStatus.h"
#include "Monitoring/MON_OchAltStatus.h"
#include "Monitoring/MON_OchDefects.h"
#include "Monitoring/MON_OchConfig.h"
#include "Monitoring/MON_AppIf.h"
#include "Monitoring/MON_PilotToneProcessingController.h"
#include <ErrorService/FC_Error.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <CSM/CSM_AppIf.h>
#include <TsPii/TSPII_PipeIf.h>

uint32 MON_OchUpdateStatusAction::theirRequestId = 0;

extern bool gInterferenceEnabled;

//##ModelId=3C7170EE01A6
MON_OchUpdateStatusAction::MON_OchUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_PilotToneRegion* theTspiiRegion,
                                                     TSPII_PipeRegion* theTspiiPipeRegion,
                                                     MON_OchAltStatusRegion* theAltOchRegion,
                                                     MON_OchStatusRegion* theRawOchStatusRegion,
                                                     MON_OchStatusRegion* theAmpOchStatusRegion,
                                                     MON_OmsStatusRegion* theAmpOmsStatusRegion,
                                                     MON_OchStatusRegion* theInterferingStatusRegion,
                                                     MON_AppIf* theOmsLayerIf):
    MON_UpdateStatusAction(theMonIf,NULL),
    myRegistrationDone(false),
    myRequest(NULL),
    myCSMRegion(NULL),
    myTspiiPipeRegion(theTspiiPipeRegion),
    myOmsLayerIf(theOmsLayerIf),
    myAmpOchStatusRegion(theAmpOchStatusRegion),
    myAmpOmsStatusRegion(theAmpOmsStatusRegion),
    myOlimOmsStatusRegion(NULL),
    myInterferingStatusRegion(theInterferingStatusRegion),
    myAltOchRegion(theAltOchRegion),
    myRawOchStatusRegion(theRawOchStatusRegion)
{
    GetBbAction()->AddInputRegion(GetMonIf().GetConfigRegion());
    if (myTspiiPipeRegion)
        GetBbAction()->AddInputRegion(myTspiiPipeRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetDefectsRegion(),false);
    if (myAltOchRegion)
        GetBbAction()->AddOutputRegion(myAltOchRegion,false);

    MON_OchConfigRegion* aConfigRegion = static_cast<MON_OchConfigRegion*>(GetMonIf().GetConfigRegion());
    //MON_OchStatusRegion* aStatusRegion = static_cast<MON_OchStatusRegion*>(GetMonIf().GetStatusRegion());

    //----------------------------------------------------------
    // optimization: CMM should monitor only 8 channels
    //----------------------------------------------------------
    uint32 aBandWidth=0;
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());
    FC_THROW_ERROR_IF(aCardContext==NULL, FC_RuntimeError, "Cannot get card context");
    if (aCardContext->GetCardFamily() == CMM_FAM)
    {
        aBandWidth = CT_TEL_CHANNEL_MUX_WAVELENGHT_CAPACITY;
        T6100_SlotIf* aSlotContext = dynamic_cast<T6100_SlotIf*>(aCardContext->GetParent());
        FC_THROW_ERROR_IF(aSlotContext==NULL, FC_RuntimeError, "Cannot get slot context");
        myCSMRegion = &aSlotContext->GetCsmApp().GetCardStatusRegion();
    }
    else
        aBandWidth = GetMonIf().GetConfigRegion()->Size();


    // register to CSM for wavelegnth support by the card
    if (myCSMRegion)
        GetBbAction()->AddInputRegion(myCSMRegion);


    // create request
    myRequest = new MON_PilotToneControllerRequest(aConfigRegion,
                                                   myRawOchStatusRegion,
                                                   theTspiiRegion,
                                                   aBandWidth);

    // For Calculating PerAmp Power (i.e., the LIAM), the Status of the OMS on
    // that card is sent from the subapplication.
    if(myOmsLayerIf) GetBbAction()->AddInputRegion(myOmsLayerIf->GetStatusRegion());

    // if we are and OLIM in an amplified system, we must take IAM power as source
    if (myAmpOchStatusRegion && myAmpOmsStatusRegion)
    {
        FC_THROW_ERROR_IF(myAmpOchStatusRegion->Size() != GetMonIf().GetStatusRegion()->Size(),
                          FC_RuntimeError,
                          "Och status region between OLIM and AMP must match");
        T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());

        if ( NULL!=aCardContext ) 
        {
            if (aCardContext->GetOmsIfPtr() && aCardContext->GetOmsIf().GetMonLineAppPtr())
            {
                myOlimOmsStatusRegion = static_cast<MON_OmsStatusRegion*> (aCardContext->GetOmsIf().GetMonLineApp().GetStatusRegion());
            }
        }
    }

    // we own the status region only if normal local monitoring is done
    if (!myOlimOmsStatusRegion)
    {
        GetBbAction()->AddInputRegion(myRawOchStatusRegion, false);
        GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(), false);
    }
    else
    {
        GetBbAction()->AddInputRegion(myOlimOmsStatusRegion, false);
        GetBbAction()->AddInputRegion(myAmpOchStatusRegion, false);
        GetBbAction()->AddInputRegion(myAmpOmsStatusRegion, false);
        GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion());
    }

    if (myInterferingStatusRegion)
    {
        FC_THROW_ERROR_IF(myInterferingStatusRegion->Size()!=GetMonIf().GetStatusRegion()->Size(),
                          FC_RuntimeError,
                          "Interfering and local region size must match");
        GetBbAction()->AddInputRegion(myInterferingStatusRegion, false);
    }

}

//##ModelId=3C7170EE01D7
MON_OchUpdateStatusAction::~MON_OchUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(GetMonIf().GetConfigRegion());
    if (myTspiiPipeRegion)
        GetBbAction()->RemoveInputRegion(myTspiiPipeRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetDefectsRegion());
    if (myAltOchRegion)
        GetBbAction()->RemoveOutputRegion(myAltOchRegion);

    if (myCSMRegion)
        GetBbAction()->RemoveInputRegion(myCSMRegion);

    if(myOmsLayerIf) GetBbAction()->RemoveInputRegion(myOmsLayerIf->GetStatusRegion());

    if (!myOlimOmsStatusRegion)
    {
        GetBbAction()->RemoveInputRegion(myRawOchStatusRegion);
        GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    }
    else
    {
        GetBbAction()->RemoveInputRegion(myOlimOmsStatusRegion);
        GetBbAction()->RemoveInputRegion(myAmpOchStatusRegion);
        GetBbAction()->RemoveInputRegion(myAmpOmsStatusRegion);
        GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
    }

    if (myInterferingStatusRegion)
    {
        GetBbAction()->RemoveInputRegion(myInterferingStatusRegion);
    }

    delete myRequest;
}

FC_Object* MON_OchUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    // handle registration to Pilot tone processing controller
    if (!myOlimOmsStatusRegion && myRegistrationDone)
    {
        // register och status region to be updated periodically
        // This is only being done on cards that support pilot tone
        T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());

        if( NULL!=aCardContext ) 
        {
            if (aCardContext->GetCardFamily() == TRN_FAM ||
                aCardContext->GetCardFamily() == FGTMM_FAM)
            {
                MON_PilotToneProcessingController::GetInstance().Unregister(myRequest);
            }
        }

        myRegistrationDone = false;
    }

    GetMonIf().GetDefectsRegion()->Reset();
    GetMonIf().GetStatusRegion()->Reset();
    myRawOchStatusRegion->Reset();
    if (myAltOchRegion)
        myAltOchRegion->Reset();
    return NULL;
}

//##ModelId=3C7170EE01BA
FC_Object* MON_OchUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    // handle registration to Pilot tone processing controller
    if (!myOlimOmsStatusRegion && !myRegistrationDone)
    {
        // register och status region to be updated periodically
        // This is only being done on cards that support pilot tone
        T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());

        if( NULL != aCardContext) 
        {
            if (aCardContext->GetCardFamily() == TRN_FAM ||
            aCardContext->GetCardFamily() == FGTMM_FAM)
            {
                MON_PilotToneProcessingController::GetInstance().Register(myRequest);
            }
        }

        myRegistrationDone = true;
    }

    //OPTIMIZATION: make sure correct CMM wavelength offset is set
    if (myCSMRegion)
    {
        bool hasChanged = myRequest->SetFirstWavelength((*myCSMRegion)[0].GetCardWavelenght().GetWavelenghtGroupForCmm());
        if (hasChanged)
        {
            // make sure we invalidate old power values because wavelenght has changed
            GetMonIf().GetDefectsRegion()->Reset();
            GetMonIf().GetStatusRegion()->Reset();
            myRawOchStatusRegion->Reset();
        }
    }

    //Update status of each object in region
    MON_OchPower aMostPowerFull = GetMostPowerFullOfRegion(myRawOchStatusRegion);
    uint32 aSize = GetMonIf().GetStatusRegion()->Size();
    uint32 aIndex=0;
    while (aIndex<aSize)
    {
        UpdateObject(theRunReason, aIndex, aMostPowerFull);
        aIndex++;
    }
    GetMonIf().GetDefectsRegion()->UpdateNotify();

    return NULL;
}



//##ModelId=3C7170EE01CD
void MON_OchUpdateStatusAction::UpdateObject(unsigned theRunReason, uint32 theIndex, const MON_OchPower& theMostPowerFullOfRegion)
{
    MON_OchDefects& aDefects   = static_cast<MON_OchDefects&>((*GetMonIf().GetDefectsRegion())[(bbindex_t)theIndex]);
    MON_OchStatus& aStatus     = static_cast<MON_OchStatus&>((*GetMonIf().GetStatusRegion())[(bbindex_t)theIndex]);
    MON_OchStatus& aRawStatus  = static_cast<MON_OchStatus&>((*myRawOchStatusRegion)[(bbindex_t)theIndex]);
    MON_OchConfig& aConfig     = static_cast<MON_OchConfig&>((*GetMonIf().GetConfigRegion())[(bbindex_t)(theIndex+myRequest->GetFirstWavelength())]);

    //--------------------------------------------------------------
    // STATUSES
    // Read current statuses

    // Invalidate status region if the monitoring is disabled
    if(aConfig.GetExpectedChannelId() == UNKNOWN_WAVELENGHT)
    {
        aStatus.Invalidate();
        aStatus.Reset();
        aRawStatus.Invalidate();
        aRawStatus.Reset();
    }
    else
    {
        bool hasStatusChanged = false;
        if (myOlimOmsStatusRegion)
        {
            // update status regions using IAM och status
            MON_OchStatus& aAmpOchStatus     = static_cast<MON_OchStatus&>((*myAmpOchStatusRegion)[(bbindex_t)theIndex]);
            MON_OmsStatus& aAmpOmsStatus     = static_cast<MON_OmsStatus&>((*myAmpOmsStatusRegion)[0]);
            MON_OmsStatus& aOlimOmsStatus    = static_cast<MON_OmsStatus&>((*myOlimOmsStatusRegion)[0]);

            // if regions are valid and data is validated
            if (myAmpOchStatusRegion->IsValid() &&
                myAmpOmsStatusRegion->IsValid() &&
                myOlimOmsStatusRegion->IsValid() &&
                aAmpOchStatus.IsValidated() &&
                aAmpOmsStatus.IsValidated() &&
                aOlimOmsStatus.IsValidated())
            {

                // compute power gain between olim and amp
                CT_TEL_mBm aPowerGain = aAmpOmsStatus.GetOmsOutputPower() - aOlimOmsStatus.GetOmsOutputPower();

                // copy Amp och power and boost it by this power drop
                aStatus = aAmpOchStatus;
                aStatus.Boost(-1 * aPowerGain);

                // force changed unconditionaly since these are all analog value
                // NOTE: for performance issue, no temporary copy is keep a side
                // because calling constructor is no very efficient
                hasStatusChanged = true;
            }
            // region or power level are not valid
            // invalidate ours
            else
            {
                hasStatusChanged |= aStatus.Invalidate();
            }
        }
        else
        {
            if (aRawStatus.IsValidated())
            {
                //--------------------------------------------------------------
                // Interference due to cross-modulation
                // We need to ignore any signal 16 dB under
                // the most powerfull signal present.
                // This is needed because we may read cross-modulation of this
                // powerfull signal on other frequencies.
                //--------------------------------------------------------------
                CT_TEL_mBm aRawPower = aRawStatus.GetPower();
                aStatus = aRawStatus;
                if ((aRawPower != TRAFFIC_DEFAULT_POWER) &&
                    (aRawPower + 1600 < (theMostPowerFullOfRegion.GetAmplitude())))
                {
                    // clear powers in it
                    aStatus.ClearPowersLevels();
                }
                // force changed unconditionaly since these are all analog value
                // NOTE: for performance issue, no temporary copy is keep a side
                // because calling constructor is no very efficient
                hasStatusChanged = true;

            }
            else
            {
                hasStatusChanged |= aStatus.Invalidate();
            }

        }
        if (hasStatusChanged)
            GetMonIf().GetStatusRegion()->IncModificationCounter();

        // Calculate the PreAmp Power when the Oms Layer us given
        // (i.e., for the LIAM).  This is done by finding the power
        // (from the OCH layer) and subtracting the gain (from the OMS layer).
        if (myOmsLayerIf)
        {
            // compute power gain from the OMS region
            MON_OmsStatus& aOmsStatus = static_cast<MON_OmsStatus&>( (*myOmsLayerIf->GetStatusRegion())[0] );

            CT_TEL_mBm aPowerGain = aOmsStatus.GetActualGain();

            // get the power measurement from the OCH region
            CT_TEL_mBm aPowerReading = aStatus.GetPower();

            // Calculate PreAmp Power and then write to the Status Region
            CT_TEL_mBm aPreAmpPower = TRAFFIC_DEFAULT_POWER;
            if (aPowerReading != TRAFFIC_DEFAULT_POWER)
            {
                aPreAmpPower = aPowerReading - aPowerGain;
            }

            hasStatusChanged |= aStatus.SetPreAmpPower(aPreAmpPower);
        }
    }

    //--------------------------------------------------------------
    // ALT STATUS
    if (myAltOchRegion && myTspiiPipeRegion)
    {
        MON_OchAltStatus& aAltStatus  = static_cast<MON_OchAltStatus&>((*myAltOchRegion)[(bbindex_t)theIndex]);
        TSPII_PipeIf& aPipePii = (*myTspiiPipeRegion)[0];
        uint32 aEvoaIndex = theIndex;

        //If gain is not supported by PII for this index, take the last gain supported.
        //Ex: For QUAD with 4 objects in region but only 1 gain in PII
        if(theIndex >= aPipePii.GetNumberOfEvoa())
        {
            aEvoaIndex = aPipePii.GetNumberOfEvoa() - 1;
        }

        // make sure we catch any throws from legacy PII
        bool hasAltStatusChanged = false;

        try
        {
            // this is what was written from Config not what is the hardware configuration
            hasAltStatusChanged |= aAltStatus.SetActualGain(aPipePii.GetActualEvoa(aEvoaIndex));

            // this value is read from hardware
            CT_TEL_mBm atmpConfiguredEvoa = aPipePii.GetEvoa(aEvoaIndex);
            if (atmpConfiguredEvoa != TRAFFIC_DEFAULT_POWER)
            {
                hasAltStatusChanged |= aAltStatus.SetConfiguredGain(atmpConfiguredEvoa);
                hasAltStatusChanged |= aAltStatus.Validate();
            }
        }
        catch (FC_HWError&)
        {
            hasAltStatusChanged |= aAltStatus.Invalidate();
        }
        if (hasAltStatusChanged)
            myAltOchRegion->IncModificationCounter();

    }


    //--------------------------------------------------------------
    // DEFECTS
    // Read current defects
    bool hasDefectsChanged = false;
    bool aLossPwrState       = false;
    bool aDebugTraceDetected = false;
    if (aStatus.IsValidated() || (aConfig.GetExpectedChannelId() != UNKNOWN_WAVELENGHT))
    {
        // get previous defect state
        uint32 aCount=0;
        aDefects.GetDefectStatus(CT_TEL_OCH_LOSS_PTONE_DEFECT, &aCount, &aLossPwrState);

        // consider source of interference if region and object is valid
        MON_OchStatus* aInterferenceStatus=NULL;
        if (myInterferingStatusRegion && myInterferingStatusRegion->IsValid() && gInterferenceEnabled && aConfig.GetInterferenceEnable())
        {
            aInterferenceStatus     = &(*myInterferingStatusRegion)[(bbindex_t)theIndex];
            if (!aInterferenceStatus->IsValidated())
                aInterferenceStatus = NULL;
        }

        // get most powerfull signal ID
        const MON_OchPower& aPower = aStatus.GetMostPowerfullId(aInterferenceStatus);

        // get current S/N ration
        CT_TEL_mBm aSignalToNoiseRatio = aPower.GetSnr();
        CT_TEL_mBm aPowerLevel = aPower.GetAmplitude();

        // get current loss defect threshold
        CT_TEL_mBm aMinimumSN = aConfig.GetMinimumSNRatio();
        CT_TEL_mBm aLossThreshold = aConfig.GetLossOfInputPowerThreshold();

        // if defect is already set, clear it only if S/N ratio exceed threshold +1 dB
        // or if level exceeds threshold from 1 dB
        // to avoid toggling
        if (aLossPwrState)
        {
            aMinimumSN +=  1*CT_TEL_POWER_FACTOR;
            aLossThreshold +=  1*CT_TEL_POWER_FACTOR;
            if ( (aPowerLevel > aLossThreshold) &&
                  (aSignalToNoiseRatio > aMinimumSN))
                aLossPwrState = false;
        }
        // otherwise compare with normal thresholds
        else
        {
            if ((aPowerLevel < aLossThreshold) ||
                (aSignalToNoiseRatio < aMinimumSN))
                aLossPwrState = true;
        }

        // When no LOSS, update detected ID and debug trace detected
        if (!aLossPwrState)
        {
            aDebugTraceDetected = (aPower.GetTraceId() == MON_ID_DEBUG);
            hasDefectsChanged |= aDefects.SetDetectedId(aPower.GetTraceId());
        }
        else
        {
            // set value to a stable one
            hasDefectsChanged |= aDefects.SetDetectedId(MON_ID_FIRST);
        }

        hasDefectsChanged |= aDefects.Validate();

    }
    else
    {
        hasDefectsChanged |= aDefects.Invalidate();
        aDefects.Reset();
    }

    // update actual defect
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OCH_LOSS_PTONE_DEFECT,           aLossPwrState,       0);
    hasDefectsChanged |= aDefects.SetDefectStatus(CT_TEL_OCH_DEBUG_TRACE_DETECTED_DEFECT, aDebugTraceDetected, 0);
    if (hasDefectsChanged)
        GetMonIf().GetDefectsRegion()->IncModificationCounter();

}


MON_OchPower MON_OchUpdateStatusAction::GetMostPowerFullOfRegion(const MON_OchStatusRegion* theOchStatusRegion)
{
    // scan through the all the powers to find the most power full of all
    uint32 aSize = theOchStatusRegion->Size();
    MON_OchPower aPowerfull(MON_ID_FIRST);
    uint32 aIndex=0;
    while (aIndex<aSize)
    {
        MON_OchStatus& aStatus     = static_cast<MON_OchStatus&>((*theOchStatusRegion)[(bbindex_t)aIndex]);

        // find the most powerfull valid value
        if (aStatus.IsValidated())
        {
            if (aPowerfull < aStatus.GetMostPowerfullId())
                aPowerfull = aStatus.GetMostPowerfullId();
        }
        aIndex++;
    }
    return aPowerfull;
}
