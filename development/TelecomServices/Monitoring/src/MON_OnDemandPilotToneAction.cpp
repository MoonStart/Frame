// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "Monitoring/MON_OnDemandPilotToneAction.h"
#include "Monitoring/MON_OchRequest.h"
#include "Monitoring/MON_OchResult.h"

MON_OnDemandPilotToneAction::MON_OnDemandPilotToneAction(MON_AppIf& theAppIf,
                                                         MON_OchRequestRegion& theOchRequestRegion,
                                                         MON_OchResultRegion& theOchIntermediateResultRegion,
                                                         TSPII_PilotToneRegion& thePilotTonePiiRegion,
                                                         MON_OchResultRegion* theOchInterferingResultRegion,
                                                         TSPII_PilotToneRegion* theInterferingPilotTonePiiRegion):
    MON_UpdateStatusAction(theAppIf, NULL),
    myOchRequestRegion(theOchRequestRegion),
    myOchIntermediateResultRegion(theOchIntermediateResultRegion),
    myPilotTonePiiRegion(thePilotTonePiiRegion),
    myOchInterferingResultRegion(theOchInterferingResultRegion),
    myInterferingPilotTonePiiRegion(theInterferingPilotTonePiiRegion),
    myPilotToneAction(NULL),
    myInterferingPilotToneAction(NULL),
    myRequestId(0)
{
    myPilotToneAction = new MON_PilotToneAction();
    myInterferingPilotToneAction = new MON_PilotToneAction();

    GetBbAction()->AddInputRegion(&myOchRequestRegion);
    GetBbAction()->AddOutputRegion(&myOchIntermediateResultRegion, false, false);
    if(myOchInterferingResultRegion) GetBbAction()->AddOutputRegion(myOchInterferingResultRegion, false, false);
}


MON_OnDemandPilotToneAction::~MON_OnDemandPilotToneAction()
{
    GetBbAction()->RemoveInputRegion(&myOchRequestRegion);
    GetBbAction()->RemoveOutputRegion(&myOchIntermediateResultRegion);
    if(myOchInterferingResultRegion) GetBbAction()->RemoveOutputRegion(myOchInterferingResultRegion);

    delete myPilotToneAction;
    delete myInterferingPilotToneAction;
}


FC_Object* MON_OnDemandPilotToneAction::Suspend(unsigned theRunReason,
                                                FC_Object* theInvokerObj,
                                                FC_Object* theParam)
{
    return NULL;
}

FC_Object* MON_OnDemandPilotToneAction::Process(unsigned theRunReason,
                                                FC_Object* theInvokerObj,
                                                FC_Object* theParam)
{
    // Ignore request if it was already processed
    if (myOchRequestRegion[0].GetRequestID() == myRequestId)
        return NULL;
    else
        myRequestId = myOchRequestRegion[0].GetRequestID();

    // Prepare request for the channel
    MON_PilotToneProcessorRequest aPilotToneRequest(myOchRequestRegion[0].GetChannelId(),
                                                    myOchRequestRegion[0].GetRequestID(),
                                                    MON_PT_EXACTMODE_NUM_SAMPLE,
                                                    TSPII_PT_HIGH_PRIORITY);

    //Invalidate the region because we start a new collection
    myOchIntermediateResultRegion[0].Invalidate();
    //Save request information into result region for later use
    myOchIntermediateResultRegion[0].SetRequestInformation(aPilotToneRequest);
    //Start collection
    myPilotToneAction->Collect(aPilotToneRequest, &myOchIntermediateResultRegion, 0, &myPilotTonePiiRegion, NULL);

    //Repeat the same for interfering result region if available
    if(myOchInterferingResultRegion && myOchRequestRegion[0].GetInterferenceAnalyserEnable())
    {
        //Invalidate the region because we start a new collection
        (*myOchInterferingResultRegion)[0].Invalidate();
        //Save request information into result region for later use
        (*myOchInterferingResultRegion)[0].SetRequestInformation(aPilotToneRequest);
        //Starts collection
        myInterferingPilotToneAction->Collect(aPilotToneRequest, myOchInterferingResultRegion, 0, myInterferingPilotTonePiiRegion, NULL);
    }

    return NULL;
}

void MON_OnDemandPilotToneAction::Menu(int argc, char ** argv)
{
    myPilotToneAction->Menu(argc,argv);
}
