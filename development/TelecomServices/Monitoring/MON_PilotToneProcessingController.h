// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_PILOTTONEPROCESSINGCONTROLLER_3C4827CA01AA_INCLUDED
#define _INC_MON_PILOTTONEPROCESSINGCONTROLLER_3C4827CA01AA_INCLUDED

#include <Monitoring/MON_AppIf.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include "MON_PilotToneAction.h"
#include "MON_PilotToneControllerRequest.h"
#include <list>
 
class FC_Stream;

using namespace std;




//This class is a responsible for providing a prioritized 
//processing interface with the pilot tone task. It allows to 
//place a high or low priority pilot tone measurement 
//request. It provides power measurement through a callback 
//fashion. There is a single instance of this controller for 
//each pilot task of the system.
//##ModelId=3C4827CA01AA
class MON_PilotToneProcessingController : public FC_Action
{
public:

	//##ModelId=3C7170DC03D0
    static MON_PilotToneProcessingController& GetInstance();

	//Override of Run method from FC_Action.
	//##ModelId=3C7170DC03DA
    void Run(FC_Object* theObject = NULL);
	//##ModelId=3C7170DD0006
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);


	//Virtual destructor.
	//##ModelId=3C7170DD0042
    virtual ~MON_PilotToneProcessingController();

    void Register(MON_PilotToneControllerRequest* theRequest);
    void Unregister(MON_PilotToneControllerRequest* theRequest);

    static void SetMaxSimultenousRequest(uint32 theMax);

    void Display( FC_Stream& theStream );
    void ResetStats();
private:
	//Constructor.
	//##ModelId=3C7170DD00F6
    MON_PilotToneProcessingController();

	//##ModelId=3C7170DD0133
    list<MON_PilotToneAction*> myFreePilotToneActionList;

    static MON_PilotToneProcessingController* myInstance;

    list<MON_PilotToneControllerRequest*> myRequestList;
    list<MON_PilotToneControllerRequest*>::iterator myNextRequest;
    CT_Wavelength myChannelId;
    static uint32 myMaxSimultenousRequest;
};


#endif /* _INC_MON_PILOTTONEPROCESSINGCONTROLLER_3C4827CA01AA_INCLUDED */
