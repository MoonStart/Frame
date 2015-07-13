// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_OTUUPDATESTATUSACTION_
#define _MON_OTUUPDATESTATUSACTION_

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
class TSPII_FecIf;

//This class is an action that reads the current state of the 
//OTU layer in the hardware and updates the OTU regions accordingly.
class MON_OtuUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_OtuUpdateStatusAction(MON_AppIf& theMonIf, 
                              TSPII_FecRegion& theFecPiiRegion,
                              MON_AppIf* theUpstreamLayerIf);

    //Virtual destructor of the class.
	virtual ~MON_OtuUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason);

private:

    TSPII_FecRegion& myFecPiiRegion;

    uint32 myNumConsecTraceComp;

	uint32 myGoodTraceMessageCounter;
	uint32 myBadTraceMessageCounter;

    // First time read of OTU-Trace from TSPII
    bool myFirstRcvdOtuTrace;

    //Local counts of defects read on PII
    uint32 myPiiAISCount;
    uint32 myPiiLOFCount;
    uint32 myPiiLOMFCount;
    uint32 myPiiFECMCount;
    uint32 myPiiBDICount;
    uint32 myPiiBerSdCount;
    uint32 myPiiIAECount;
    uint32 myPiiMateDefectCount;
    bool   myLastDispCompInitState;
    bool   myTimCheckByMon;
};

#endif /* _MON_OTUUPDATESTATUSACTION_ */
