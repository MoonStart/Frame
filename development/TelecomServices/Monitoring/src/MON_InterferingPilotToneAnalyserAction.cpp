// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "Monitoring/MON_InterferingPilotToneAnalyserAction.h"
#include "Monitoring/MON_OchRequest.h"
#include "Monitoring/MON_OchResult.h"


#include "Monitoring/MON_OmsStatus.h"
#include "Monitoring/MON_OchPower.h"
#include "CommonPlatforms/SoftwareServices/T6100/T6100_CardIf.h"
#include "CommonPlatforms/SoftwareServices/T6100/T6100_TelecomIf.h"

#include <Monitoring/MON_OmsDefects.h>

MON_InterferingPilotToneAnalyserAction::MON_InterferingPilotToneAnalyserAction(MON_AppIf& theAppIf,
                                                                               MON_OchRequestRegion& theOchRequestRegion,
                                                                               MON_OchResultRegion& theOchResultRegion,
                                                                               MON_OchResultRegion& theOchIntermediateResultRegion,
                                                                               MON_OchResultRegion* theOchInterferingResultRegion,
                                                                               bool theBeforeAmp) :
    MON_UpdateStatusAction(theAppIf, NULL),
    myOchRequestRegion(theOchRequestRegion),
    myOchResultRegion(theOchResultRegion),
    myOchIntermediateResultRegion(theOchIntermediateResultRegion),
    myOchInterferingResultRegion(theOchInterferingResultRegion),
    myRequestId(0),
    myBeforeAmp(theBeforeAmp),
    myTraceEnabled(false)
{
    GetBbAction()->AddInputRegion(&myOchRequestRegion);
    GetBbAction()->AddInputRegion(&myOchIntermediateResultRegion);
    if(myOchInterferingResultRegion) GetBbAction()->AddInputRegion(myOchInterferingResultRegion);
    GetBbAction()->AddOutputRegion(&myOchResultRegion,false,false);
}


MON_InterferingPilotToneAnalyserAction::~MON_InterferingPilotToneAnalyserAction()
{
    GetBbAction()->RemoveInputRegion(&myOchRequestRegion);
    GetBbAction()->RemoveInputRegion(&myOchIntermediateResultRegion);
    if(myOchInterferingResultRegion) GetBbAction()->RemoveInputRegion(myOchInterferingResultRegion);
    GetBbAction()->RemoveOutputRegion(&myOchResultRegion);
}


FC_Object* MON_InterferingPilotToneAnalyserAction::Suspend(unsigned theRunReason,
                                                           FC_Object* theInvokerObj,
                                                           FC_Object* theParam)
{
    return NULL;
}

FC_Object* MON_InterferingPilotToneAnalyserAction::Process(unsigned theRunReason,
                                                           FC_Object* theInvokerObj,
                                                           FC_Object* theParam)
{
    MON_OchRequest& aRequest = myOchRequestRegion[0];
    MON_OchResult& aResult = myOchResultRegion[0];
    MON_OchResult& aIntermediateResult = myOchIntermediateResultRegion[0];
    MON_OchResult* aInterferenceResult = NULL;
    if(myOchInterferingResultRegion) aInterferenceResult = &(*myOchInterferingResultRegion)[0];
    
    bool aResultObjectInvalid = false;
    bool aRequestDifferent = false;
    MON_RequestID aRequestId = aRequest.GetRequestID();
    
    // Ignore request if it was already processed
    if(aRequestId == myRequestId)
        return NULL;

    // Verify if the intermediate result and interfering result finished collection
    aResultObjectInvalid |= !aIntermediateResult.IsValidated();
    if(aInterferenceResult && aRequest.GetInterferenceAnalyserEnable())
        aResultObjectInvalid |= !aInterferenceResult->IsValidated();

    // Verify that request IDs of the result regions correspond the the request that we have to process
    aRequestDifferent |= (aRequestId != aIntermediateResult.GetRequestInformation().GetRequestId());
    if(myOchInterferingResultRegion && aRequest.GetInterferenceAnalyserEnable())
        aRequestDifferent |= (aRequestId != aInterferenceResult->GetRequestInformation().GetRequestId());
        

    if(!(aResultObjectInvalid || aRequestDifferent))
    {
        //Clear result object before writing to it
        aResult.Reset();

        if(myBeforeAmp)
        {
            //get the gain
            T6100_CardIf* aCardIf = dynamic_cast<T6100_CardIf*>(GetMonIf().GetContext().GetParent());

            if(aCardIf->GetCardFamily() == LIAM_FAM)
            {
                MON_OmsStatusRegion* myStatusRegion   = static_cast<MON_OmsStatusRegion*>(aCardIf->GetOmsIf().GetMonLineApp().GetStatusRegion());
                MON_OmsDefectsRegion* myDefectsRegion = static_cast<MON_OmsDefectsRegion*>(aCardIf->GetOmsIf().GetMonLineApp().GetDefectsRegion());

                if(myStatusRegion)
                {
                    MON_OmsStatus& aOmsStatus   = (*myStatusRegion)[0];
                    MON_OmsDefects& aOmsDefects = (*myDefectsRegion)[0];

                    CT_TEL_mBm aGain = aOmsStatus.GetConfiguredGain();

                    bool aOmsAfterAmpLosState = false;
                    uint32 aCount = 0;
                    aOmsDefects.GetDefectStatus(CT_TEL_OMS_LOS_AFTER_AMPLI_DEFECT, &aCount, &aOmsAfterAmpLosState);

                    CT_TEL_mBm LSR_Amplitude = TRAFFIC_DEFAULT_POWER;
                    CT_TEL_mBm LSR_Snr       = TRAFFIC_DEFAULT_POWER;

                    if(!aRequest.GetInterferenceAnalyserEnable())
                    {
                        const MON_OchPower& aPower = aIntermediateResult.GetMostPowerfullId(aInterferenceResult);

                        if(!aOmsAfterAmpLosState)
                        {
                            LSR_Amplitude = aPower.GetAmplitude()-aGain;
                            LSR_Snr       = aPower.GetSnr();
                        }

                        MON_OchPower* aBeforeAmpPower = new MON_OchPower(aPower.GetTraceId(), LSR_Amplitude, LSR_Snr);

                        MON_OchPower& rBeforeAmpPower = (*aBeforeAmpPower);

                        if(myTraceEnabled)
                        {
                            fc_cout << endl << endl << "\rBefore Amp; Non-Interference Analysis..." << endl;
                            fc_cout << "\r\tLOS: " << "Output LOS is " << DISPLAY_BOOL(aOmsAfterAmpLosState) << endl;
                            fc_cout << "\r\tID : " << rBeforeAmpPower.GetTraceId() << " After Amp = " << aPower.GetTraceId() << endl;
                            fc_cout << "\r\tPwr: " << DISPLAY_MBM(rBeforeAmpPower.GetAmplitude()) << " dBm; Gain = " << DISPLAY_MBM(aGain) << " dBm; After Amp = " << DISPLAY_MBM(aPower.GetAmplitude()) << " dBm" << endl;
                            fc_cout << "\r\tSNR: " << DISPLAY_MBM(rBeforeAmpPower.GetSnr()) << " dB; After Amp = " << DISPLAY_MBM(aPower.GetSnr()) << " dBm" << endl << endl;
                        }

                        aIntermediateResult.SetTraceIdPowers(rBeforeAmpPower);
                        aResult = aIntermediateResult;
                    }
                    else
                    {
                        //Find the most powerfull ID considering interference
                        const MON_OchPower& aPower = aIntermediateResult.GetMostPowerfullId(aInterferenceResult);
                        MON_PilotToneProcessorRequest aPilotToneRequest = aIntermediateResult.GetRequestInformation();

                        if(!aOmsAfterAmpLosState)
                        {
                            LSR_Amplitude = aPower.GetAmplitude()-aGain;
                            LSR_Snr       = aPower.GetSnr();
                        }

                        MON_OchPower* aBeforeAmpPower = new MON_OchPower(aPower.GetTraceId(), LSR_Amplitude, LSR_Snr);
                        MON_OchPower& rBeforeAmpPower = (*aBeforeAmpPower);

                        if(myTraceEnabled)
                        {
                            fc_cout << endl << endl << "\rBefore Amp; Interference Analysis..." << endl;
                            fc_cout << "\r\tLOS: " << "Output LOS is " << DISPLAY_BOOL(aOmsAfterAmpLosState) << endl;
                            fc_cout << "\r\tID : " << rBeforeAmpPower.GetTraceId() << " After Amp = " << aPower.GetTraceId() << endl;
                            fc_cout << "\r\tPwr: " << DISPLAY_MBM(rBeforeAmpPower.GetAmplitude()) << " dBm; Gain = " << DISPLAY_MBM(aGain) << " dBm; After Amp = " << DISPLAY_MBM(aPower.GetAmplitude()) << " dBm" << endl;
                            fc_cout << "\r\tSNR: " << DISPLAY_MBM(rBeforeAmpPower.GetSnr()) << " dB; After Amp = " << DISPLAY_MBM(aPower.GetSnr()) << " dBm" << endl << endl;
                        }

                        //Fill the result region with the most powerfull power
                        aResult.SetTraceIdPowers(rBeforeAmpPower);

                        aResult.SetRequestInformation(aPilotToneRequest);
                        aResult.SetChannelId(aRequest.GetChannelId());
                    }

                }
                else
                    return NULL;
            }
            else
                return NULL;
        }
        else
        {
            if(!aRequest.GetInterferenceAnalyserEnable())
                aResult = aIntermediateResult;
            else
            {
                //Find the most powerfull ID considering interference
                const MON_OchPower& aPower = aIntermediateResult.GetMostPowerfullId(aInterferenceResult);
                MON_PilotToneProcessorRequest aPilotToneRequest = aIntermediateResult.GetRequestInformation();
    
                if(myTraceEnabled)
                {
                    fc_cout << endl << endl << "\rInterfering PilotTone Analyser..." << endl;
                    fc_cout << "\r\tID : " << aPower.GetTraceId() << endl;
                    fc_cout << "\r\tPwr: " << DISPLAY_MBM(aPower.GetAmplitude()) << " dBm" << endl;
                    fc_cout << "\r\tSNR: " << DISPLAY_MBM(aPower.GetSnr()) << " dB" << endl << endl;
                }

                //Fill the result region with the most powerfull power
                aResult.SetTraceIdPowers(aPower);
                aResult.SetRequestInformation(aPilotToneRequest);
                aResult.SetChannelId(aRequest.GetChannelId());
            }
        }

        //Update request ID
		myRequestId = aRequest.GetRequestID();

        //Validate the object and notify the region
        aResult.Validate();
        myOchResultRegion.IncModificationCounter();
        myOchResultRegion.UpdateNotify();
    }

    return NULL;
}

void MON_InterferingPilotToneAnalyserAction::EnableTrace(bool theTraceEnable)
{
    myTraceEnabled = theTraceEnable;

    if(myTraceEnabled)
        fc_cout << "MON_InterferingPilotToneAnalyserAction: Tracing ENABLED..." << endl;
    else
        fc_cout << "MON_InterferingPilotToneAnalyserAction: Tracing DISABLED..." << endl;
}
