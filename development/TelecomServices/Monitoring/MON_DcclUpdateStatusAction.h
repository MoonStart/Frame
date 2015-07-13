// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_DCCLlUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_DCCLUPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <vector>



// Forward declaration of class.
class TSPII_DcclIf;

// This class is an action that reads the current state of the 
// Dccl layer in the hardware and updates the Dccl regions 
// accordingly.
class MON_DcclUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	// Constructor.
	MON_DcclUpdateStatusAction(MON_AppIf& theMonIf, 
                              TSPII_DcclRegion& theDcclPiiRegion,
                              MON_AppIf*  theUpstreamLayerIf,
                              uint8       theNumLinks);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	// Virtual destructor of the class.
	virtual ~MON_DcclUpdateStatusAction();

private:

    TSPII_DcclRegion& myDcclPiiRegion;

    uint8 myNumLinks;

    // List of ids of Dccl 
    vector<uint16> myDcclIdList;

    // Local counts of defects read on PII
    // Use vectors rather than arrays
    vector<bool> myLastLinkDownState;
    vector<bool> myLastLinkIncompleteState;
};



#endif /* _INC_MON_DCCLUPDATESTATUSACTION_3C164A850173_INCLUDED */
