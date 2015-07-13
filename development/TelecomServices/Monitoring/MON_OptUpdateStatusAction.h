// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_OPTUPDATESTATUSACTION_3C164AC100E3_INCLUDED
#define _INC_MON_OPTUPDATESTATUSACTION_3C164AC100E3_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>
#include "MON_Definitions.h"
#include "Configuration/CFG_Definitions.h"
#include "ITS/ITS_Definitions.h"
#include <T6100_TelecomIf.h>

// Since the throttling of hardware access is only being done on OPSM, 
// define some constants here that later could be constructor parameters.
// For OPSM, assume 200 ms wakeup.
// These constants along with the ThottleID and ThrottleFrequency will be 
// used to control access to hardware.
const uint32 MON_STATUS_ACCESS_INTERVAL = 4;    // Access every 800 ms


// Forward declaration of class.
class TSPII_OpticalIf;

//This action handle the refresh of its Optical defect and 
//status object.
//##ModelId=3C3B52F80044
class MON_OptUpdateStatusAction 
: public MON_UpdateStatusAction
{
    typedef vector<MON_AppIf*> MON_AppVector;

public:
	//Constructor for .
	//##ModelId=3C3B52F8024E
	MON_OptUpdateStatusAction(MON_AppIf& theMonIf, 
                              TSPII_OpticalRegion& theOptPiiRegion,
                              CFG_OptAutoRateLockRegion* theAutoRateLockRegion,
                              T6100_TelecomIf* theOchMainApp,
                              CFG_OptCfgRegion* theOptConfigRegion,
                              ITS_ConfigRegionOnTrn* theItsConfigRegion,
                              vector<CT_Side>& thePossibleSidesVector,
                              MON_AppVector& theMonAppVector,
                              T6100_CardIf*  theCardContext,
                              uint8  theNumberOfMonPoolApps = 0,
                              uint32 theNumberofMonRegions  = 0,
                              MON_AppIf* thePoolApp = NULL,
                              uint32 theThrottleID = 0,
                              uint32 theThrottleFrequency = MON_STATUS_ACCESS_INTERVAL,
                              bool theThrottleLossClkRead = true,
                              uint32 theNumberofPossibleSides = 0,
                              MON_OptProtConfigRegion* theProtConfigRegion = NULL);

	//##ModelId=3C3B52F80262
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	//##ModelId=3C3B52F8026D
	virtual ~MON_OptUpdateStatusAction();

	//##ModelId=3C7170E603A2
    void UpdateObject(unsigned theRunReason, TSPII_OpticalIf& theOptPii);

private:

    TSPII_OpticalRegion& myOptPiiRegion;

    MON_OptProtConfigRegion* myProtConfigRegion;

    uint32 myPiiOptLosCount;
    uint32 myPiiLossOfClockCount;
    MON_OchStatusRegion* myOchStatusRegion;
    CFG_OptAutoRateLockRegion* myAutoRateLockRegion;

    T6100_TelecomIf* myOchMainApp;

    CFG_OptCfgRegion* myOptConfigRegion;
    ITS_ConfigRegionOnTrn* myItsConfigRegion;

    uint32 myCount;
    bool   myPowerChangeTracker;

    // Used to indicate the first good read input power from TSPII
    bool   myFirstGoodPowerRead;
    bool   myFirstPassFlag;

    uint32 myThrottleID;
    uint32 myThrottleFrequency;

    vector<CT_Side> myPossibleSidesVector;
    uint32          myNumberofPossibleSides;

    MON_AppIf*     myMonPoolApp;
    T6100_CardIf*  myCardContext;
    uint8          myNumberOfMonPoolApps;
    uint32         myNumberofMonRegions;
    MON_AppVector  myMonAppVector;

    // Used to indicate whether loss of clock reads are throttled
    bool myThrottleLossClkRead;

    uint32 myPassesPerFiveSecs;

    uint32 myLocalPrbsRxSessionCounter;
    MON_AppIf *myMonOdufApp;
};



#endif /* _INC_MON_OPTUPDATESTATUSACTION_3C164AC100E3_INCLUDED */
