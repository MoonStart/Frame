// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_HOPUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_HOPUPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <vector>



// Forward declaration of class.
class TSPII_HopIf;

// This class is an action that reads the current state of the 
// HOP layer in the hardware and updates the HOP regions 
// accordingly.
class MON_HopUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	// Constructor.
	MON_HopUpdateStatusAction(MON_AppIf& theMonIf, 
                              TSPII_HopRegion& theHopPiiRegion,
                              MON_AppIf* theUpstreamLayerIf,
                              CT_NumberOfHops theHopsOnCard);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	// Virtual destructor of the class.
	virtual ~MON_HopUpdateStatusAction();

private:

    TSPII_HopRegion& myHopPiiRegion;

    CT_NumberOfHops myHopsOnCard;
    uint16 myNextHop;
    uint16 myNbrHop2Check;

    bool myFirstPassFlag;

    // List of ids of HOPs representing my VCG
    vector<uint16> myHopIdList;

    // Counters used to debounce Trace modification
    // Use vectors rather than arrays
    vector<uint32> myGoodTraceMessageCounter;
    vector<uint32> myBadTraceMessageCounter;

    // Local counts of defects read on PII
    // Use vectors rather than arrays
    vector<uint32> myPiiAISCount;
    vector<uint32> myPiiLOPCount;
    vector<uint32> myPiiUNEQCount;
    vector<uint32> myPiiPLMCount;
    vector<uint32> myPiiTIMCount;
    vector<uint32> myPiiRDICount;
    vector<uint32> myPiiSDBERCount;
    vector<uint32> myPiiSFBERCount;
};



#endif /* _INC_MON_HOPUPDATESTATUSACTION_3C164A850173_INCLUDED */
