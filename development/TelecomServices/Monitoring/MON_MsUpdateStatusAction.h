// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_MSUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_MSUPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_MsIf;

//This class is an action that reads the current state of the 
//MS layer in the hardware and updates the MS regions 
//accordingly.
class MON_MsUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_MsUpdateStatusAction(MON_AppIf& theMonIf, 
                             TSPII_MsRegion& theMsPiiRegion,
                             MON_AppIf* theUpstreamLayerIf,
                             MON_AppIf* theIMUXLayerIf);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~MON_MsUpdateStatusAction();

private:

    TSPII_MsRegion& myMsPiiRegion;

    MON_AppIf* myIMUXLayerIf;

	//Local counts of defects read on PII
	uint32 myPiiAISCount;
    uint32 myPiiInternalAISLCount;
    uint32 myPiiPropreitaryInternalAISLCount;
	uint32 myPiiRDICount;
    uint32 myPiiSdBerCount;
    uint32 myPiiSfBerCount;
};



#endif /* _INC_MON_MSUPDATESTATUSACTION_3C164A850173_INCLUDED */
