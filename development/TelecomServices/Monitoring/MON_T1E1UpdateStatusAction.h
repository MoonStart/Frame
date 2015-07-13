// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_T1E1UPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_T1E1UPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_T1E1If;

//This class is an action that reads the current state of the 
//T1E1 layer in the hardware and updates the T1E1 regions 
//accordingly.
class MON_T1E1UpdateStatusAction : public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_T1E1UpdateStatusAction(MON_AppIf& theMonIf, 
                               TSPII_T1E1Region& theT1E1PiiRegion,
                               MON_AppIf* theUpstreamLayerIf);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~MON_T1E1UpdateStatusAction();

    void UpdateObject(unsigned theRunReason, TSPII_T1E1If& theT1E1Pii);

private:

    TSPII_T1E1Region& myT1E1PiiRegion;

	//Local counts of defects read on PII
    uint32 myPiiLOSCount;
    uint32 myPiiLOFCount;
	uint32 myPiiAISCount;
	uint32 myPiiOffFreqCount;

};



#endif /* _INC_MON_T1E1UPDATESTATUSACTION_3C164A850173_INCLUDED */
