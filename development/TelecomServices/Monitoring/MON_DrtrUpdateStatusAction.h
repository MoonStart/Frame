// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_DRTRUPDATESTATUSACTION_
#define _MON_DRTRUPDATESTATUSACTION_

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>

          
// Define constant here that later could be constructor parameters.
// This constant along with the Thottle will be used to control 
// access to hardware.  The access interval indicates the time between
// two updates for a given router.
// Note: assume 200 ms wakeup.
const uint32 MON_ROUTER_ACCESS_INTERVAL = 150;    // Access every 30 seconds

               
// Forward declaration of class.
class TSPII_DrtrIf;

//This class is an action that reads the current state of the 
//DRTR layer in the hardware and updates the DRTR regions accordingly.
class MON_DrtrUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_DrtrUpdateStatusAction(MON_AppIf& theMonIf,
                               TSPII_DrtrRegion& theDrtrPiiRegion,
                               MON_AppIf* theUpstreamLayerIf, 
                               uint8  theNumRouters = 1,
                               uint8  theThrottle   = 3,
                               uint8  theAccessInterval = 150);

    //Virtual destructor of the class.
	virtual ~MON_DrtrUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason);

private:

    TSPII_DrtrRegion& myDrtrPiiRegion;

    // Use this to vary the rate at which collection from TSPII is performed
    uint32 myCount;

    // The current router instance being processed.
    uint8 myCurrentRouterInstance;

    // The number of times during the complete router interval that the 
    // instances will be processed (myUpdateActionInterval) and it is also
    // used  to determine number of routers to process per call 
    // to UpdateObject (myNumRoutersToUpdate).
    uint8 myThrottle;

    // This number along with the Thottle will be used to control 
    // access to hardware.  The access interval indicates the time between
    // two updates for a given router.
    // Note: assume 200 ms wakeup.
    uint8 myAccessInterval;

    //
    uint8 myUpdateActionInterval;

    // 
    uint8 myNumRoutersToUpdate;

    // The number number of routers in an application
    uint8  myNumRouters;

    vector<uint32> myPiiRejectedAdjancencyCount;
    vector<uint32> myPiiAreaAddressMismatchCount;
    vector<uint32> myPiiMaxAreaAddressMismatchCount;
    vector<uint32> myPiiL1DatabaseOverloadCount;
    vector<uint32> myPiiL2DatabaseOverloadCount;
};

#endif /* _MON_DRTRUPDATESTATUSACTION_ */
