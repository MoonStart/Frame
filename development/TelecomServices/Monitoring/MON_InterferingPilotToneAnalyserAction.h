// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_INTERFERINGPILOTTONEANALYSERACTION_
#define _MON_INTERFERINGPILOTTONEANALYSERACTION_

#include "MON_Definitions.h"
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_UpdateStatusAction.h>
#include <TsPii/TSPII_Region.h>

class MON_OchRequest;
class MON_OchResult;

//This class is an action that handles last part of the on-demand 
//pilot tone ID power measurement request. It handles the response coming from
//the pilot tone actions and create the result using the power from the specified source
//and its interfering source. 
class MON_InterferingPilotToneAnalyserAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
    MON_InterferingPilotToneAnalyserAction(MON_AppIf& theAppIf,
                                           MON_OchRequestRegion& theOchRequestRegion,
                                           MON_OchResultRegion& theOchResultRegion,
                                           MON_OchResultRegion& theOchIntermediateResultRegion,
                                           MON_OchResultRegion* theOchInterferingResultRegion = NULL,
                                           bool theBeforeAmp = false);

	//Virtual destructor.
    virtual ~MON_InterferingPilotToneAnalyserAction();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    void EnableTrace(bool theTraceEnable);

private:

    //Regions
    MON_OchRequestRegion& myOchRequestRegion;
    MON_OchResultRegion& myOchResultRegion;
    MON_OchResultRegion& myOchIntermediateResultRegion;
    MON_OchResultRegion* myOchInterferingResultRegion;

    MON_RequestID myRequestId;
    bool myBeforeAmp;
    bool myTraceEnabled;
};

#endif /* _MON_INTERFERINGPILOTTONEANALYSERACTION_ */
