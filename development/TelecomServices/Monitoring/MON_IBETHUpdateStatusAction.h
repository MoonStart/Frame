// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_IBETHUPDATESTATUSACTION_INCLUDED
#define _INC_MON_IBETHUPDATESTATUSACTION_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <vector>



// Forward declaration of class.
class TSPII_IBETHIf;


class MON_IBETHUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	// Constructor.
	MON_IBETHUpdateStatusAction(MON_AppIf& theMonIf, 
                              TSPII_IBETHRegion& theIBETHPiiRegion,
                              MON_AppIf*  theUpstreamLayerIf,
                              uint8       theNumLinks);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	// Virtual destructor of the class.
	virtual ~MON_IBETHUpdateStatusAction();

private:

    TSPII_IBETHRegion& myIBETHPiiRegion;

    uint8 myNumLinks;

    // List of ids of IBETH
    vector<uint16> myIBETHIdList;

    // Local counts of defects read on PII
    // Use vectors rather than arrays
    vector<bool> myLastLinkDownState;
    vector<bool> myLastLinkIncompleteState;
};



#endif 
