// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_SYNCUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_SYNCUPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_ClkSelIf;

// This class is an action that reads the current state of the 
// SYNC layer in the hardware and updates the SYNC regions 
// accordingly.
class MON_SyncUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_SyncUpdateStatusAction(MON_AppIf& theMonIf, 
                               TSPII_ClkSelRegion& theClkSelPiiRegion,
                               MON_AppIf* theUpstreamLayerIf);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~MON_SyncUpdateStatusAction();

private:

    TSPII_ClkSelRegion& myClkSelPiiRegion;

	//Local status read on PII
    CT_TEL_ClkSelState myPiiCurrentState;

    //Local status read on PII
    CT_FAC_RxSsm       myPiiFreerunSsm;
};



#endif /* _INC_MON_SYNCUPDATESTATUSACTION_3C164A850173_INCLUDED */
