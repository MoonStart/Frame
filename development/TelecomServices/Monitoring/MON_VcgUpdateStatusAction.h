// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_VCGUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_VCGUPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <CommonTypes/CT_FacilityIds.h>


// This class is an action that reads the current state of the 
// VCG layer in the hardware and updates the VCG regions 
// accordingly.
class MON_VcgUpdateStatusAction : public MON_UpdateStatusAction
{
public:

	// Constructor.
	MON_VcgUpdateStatusAction(MON_AppIf& theMonIf, 
                              MON_AppIf* theUpstreamLayerIf,
                              uint16 theMaxVcgs);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	// Virtual destructor of the class.
	virtual ~MON_VcgUpdateStatusAction();

private:

    MON_AppIf* myUpstreamLayerIf;
    uint16 myMaxVcgs;

    // List of ids of VCGs representing my VCG
    vector<uint16> myVcgIdList;

};



#endif /* _INC_MON_VCGUPDATESTATUSACTION_3C164A850173_INCLUDED */
