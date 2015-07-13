// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_RSUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_RSUPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_RsIf;

//This class is an action that reads the current state of the 
//RS layer in the hardware and updates the RS regions 
//accordingly.
//##ModelId=3C164A850173
class MON_RsUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	//##ModelId=3C164B12000E
	MON_RsUpdateStatusAction(MON_AppIf& theMonIf, 
                             TSPII_RsRegion& theRsPiiRegion,
                             MON_AppIf* theUpstreamLayerIf,
                             MON_AppIf* theAltUpstreamLayerIf,
                             MON_AppIf* theIMUXLayerIf,
                             bool       theSuppressTlabAISRead);

	//##ModelId=3C3B52F6018B
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	//##ModelId=3C164B12002C
	virtual ~MON_RsUpdateStatusAction();

private:

    TSPII_RsRegion& myRsPiiRegion;

    MON_AppIf* myAltUpstreamLayerIf;
    MON_AppIf* myIMUXLayerIf;


    //Counters used to debounce Trace modification
    uint32 myGoodTraceMessageCounter;
    uint32 myBadTraceMessageCounter;

	//Local counts of defects read on PII
	uint32 myPiiOOFCount;
    uint32 myPiiLOSCount;
    uint32 myPiiLOFCount;
    uint32 myPiiTlabAISCount;
    uint32 myPiiGenAISCount;
    uint32 myPiiInternalGenAISCount;
    uint32 myPiiLocalFaultCount;
    uint32 myPiiRemoteFaultCount;
    uint32 myPiiInternalLOFCount;
    uint32 myPiiInternalCSFOPUCount;

    // First time read of RS-Trace from TSPII
    bool myFirstRcvdRsTrace;

    // This flag indicates whether to suppress TlabAIS reads to TSPII when there
    // are upper layer defects, which is normal behavior since it prevents
    // toggling of defects (that may cause automatic actions to run) when there
    // are higher (or more significant) defects (i.e., LOS).
    // This suppression is desired on cards that do not support Auto Rate Lock
    bool mySuppressTlabAISRead;
    bool myTimCheckByMon;
};



#endif /* _INC_MON_RSUPDATESTATUSACTION_3C164A850173_INCLUDED */
