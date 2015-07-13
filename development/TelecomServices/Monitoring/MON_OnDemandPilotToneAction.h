// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_ONDEMANDPILOTTONEACTION_
#define _MON_ONDEMANDPILOTTONEACTION_

#include "MON_Definitions.h"
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_UpdateStatusAction.h>
#include <Monitoring/MON_PilotToneAction.h>
#include <TsPii/TSPII_Region.h>

class MON_OchRequest;
class MON_OchResult;

//This class is an action that handles first part of the on-demand 
//pilot tone ID power measurement request. It takes care for requesting 
//two high priority power measurement in the pilot tone processor controller:
//the power from the specified source and the one from the interfering source. 
class MON_OnDemandPilotToneAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
    MON_OnDemandPilotToneAction(MON_AppIf& theAppIf,
                                MON_OchRequestRegion& theOchRequestRegion,
                                MON_OchResultRegion& theOchIntermediateResultRegion,
                                TSPII_PilotToneRegion& thePilotTonePiiRegion,
                                MON_OchResultRegion* theOchInterferingResultRegion = NULL,
                                TSPII_PilotToneRegion* theInterferingPilotTonePiiRegion = NULL);

	//Virtual destructor.
    virtual ~MON_OnDemandPilotToneAction();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    void Menu(int argc, char ** argv);

private:

    //Regions
    MON_OchRequestRegion& myOchRequestRegion;
    MON_OchResultRegion& myOchIntermediateResultRegion;
    MON_OchResultRegion* myOchInterferingResultRegion;
    TSPII_PilotToneRegion& myPilotTonePiiRegion;
    TSPII_PilotToneRegion* myInterferingPilotTonePiiRegion;

    //Actions
    MON_PilotToneAction* myPilotToneAction;
    MON_PilotToneAction* myInterferingPilotToneAction;
    
    MON_RequestID myRequestId;
};

#endif /* _MON_ONDEMANDPILOTTONEACTION_ */
